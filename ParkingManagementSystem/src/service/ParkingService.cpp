#include "service/ParkingService.hpp"

#include <utility>

#include "common/exceptions/ParkingException.hpp"
#include "domain/spot/ParkingSpot.hpp"

namespace pms {

ParkingService::ParkingService(SpotManager& spotManager,
                               TicketManager& ticketManager,
                               FeeCalculator& feeCalculator,
                               PaymentManager& paymentManager, IClock& clock,
                               ILogger& logger) noexcept
    : spotManager_(spotManager),
      ticketManager_(ticketManager),
      feeCalculator_(feeCalculator),
      paymentManager_(paymentManager),
      clock_(clock),
      logger_(logger) {}

std::shared_ptr<Ticket> ParkingService::parkVehicle(
    IEntryGate& entryGate, std::shared_ptr<const Vehicle> vehicle) {
    if (!vehicle) {
        throw InvalidArgumentException("ParkingService::parkVehicle: vehicle is null");
    }
    if (!entryGate.canServeEntry()) {
        throw GateUnavailableException("Entry gate " + entryGate.gateId() +
                                       " cannot serve entries right now");
    }

    ParkingSpot* spot = spotManager_.allocate(vehicle);  // throws if full
    try {
        std::shared_ptr<Ticket> ticket =
            ticketManager_.issue(vehicle, *spot, entryGate.gateId());
        logger_.info("ENTRY ok: " + vehicle->licensePlate() + " -> spot " +
                     spot->id() + ", ticket " + ticket->id() + " (gate " +
                     entryGate.gateId() + ")");
        return ticket;
    } catch (...) {
        // Ticketing failed after the spot was taken — undo the allocation so the
        // lot does not leak an occupied-but-untracked spot.
        spotManager_.release(spot->id());
        logger_.warn("ENTRY rolled back: released spot " + spot->id() +
                     " after ticket issue failed");
        throw;
    }
}

ExitReceipt ParkingService::exitVehicle(IExitGate& exitGate,
                                        const std::string& ticketId,
                                        PaymentMethod method) {
    if (!exitGate.canServeExit()) {
        throw GateUnavailableException("Exit gate " + exitGate.gateId() +
                                       " cannot serve exits right now");
    }

    std::shared_ptr<Ticket> ticket = ticketManager_.find(ticketId);  // throws if unknown
    if (ticket->isClosed()) {
        throw InvalidArgumentException("Ticket " + ticketId + " has already exited");
    }

    // Quote first, take payment, and only then mutate state — a declined payment
    // leaves the vehicle inside, unpaid, and the call is safely retryable.
    const TimePoint exitTime = clock_.now();
    const Money fee =
        feeCalculator_.quote(ticket->vehicle(), ticket->entryTime(), exitTime);
    std::shared_ptr<Payment> payment =
        paymentManager_.process(ticketId, fee, method);  // throws on decline

    ticketManager_.close(ticketId, exitGate.gateId());
    spotManager_.release(ticket->spotId());

    logger_.info("EXIT ok: ticket " + ticketId + ", fee " + fee.toString() +
                 ", paid via " + toString(method) + " (gate " + exitGate.gateId() +
                 ")");
    return ExitReceipt{ticket, fee, payment};
}

}  // namespace pms
