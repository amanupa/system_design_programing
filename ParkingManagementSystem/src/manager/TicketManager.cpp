#include "manager/TicketManager.hpp"

#include <memory>
#include <utility>

#include "common/exceptions/ParkingException.hpp"
#include "domain/ticket/TicketBuilder.hpp"

namespace pms {

TicketManager::TicketManager(ITicketRepository& repository, IClock& clock,
                             IIdGenerator& idGenerator, ILogger& logger)
    : repository_(repository),
      clock_(clock),
      idGenerator_(idGenerator),
      logger_(logger) {}

std::shared_ptr<Ticket> TicketManager::issue(
    const std::shared_ptr<const Vehicle>& vehicle, const ParkingSpot& spot,
    const std::string& entryGateId) {
    if (!vehicle) {
        throw InvalidArgumentException("TicketManager::issue: vehicle is null");
    }
    Ticket built = TicketBuilder()
                       .id(idGenerator_.nextId("TKT"))
                       .vehicle(vehicle)
                       .spotId(spot.id())
                       .floorNumber(spot.floorNumber())
                       .entryGateId(entryGateId)
                       .entryTime(clock_.now())
                       .build();

    auto ticket = std::make_shared<Ticket>(std::move(built));
    repository_.add(ticket);
    logger_.info("Issued ticket " + ticket->id() + " for " +
                 vehicle->licensePlate() + " at spot " + spot.id() + " (gate " +
                 entryGateId + ")");
    return ticket;
}

std::shared_ptr<Ticket> TicketManager::close(const std::string& ticketId,
                                             const std::string& exitGateId) {
    std::shared_ptr<Ticket> ticket = repository_.findById(ticketId);
    if (!ticket) {
        throw TicketNotFoundException("Unknown ticket id: " + ticketId);
    }
    ticket->close(clock_.now(), exitGateId);
    const auto secs = ticket->duration().value_or(Duration::zero()).count();
    logger_.info("Closed ticket " + ticketId + " at gate " + exitGateId +
                 " (parked " + std::to_string(secs) + "s)");
    return ticket;
}

std::shared_ptr<Ticket> TicketManager::find(const std::string& ticketId) const {
    std::shared_ptr<Ticket> ticket = repository_.findById(ticketId);
    if (!ticket) {
        throw TicketNotFoundException("Unknown ticket id: " + ticketId);
    }
    return ticket;
}

std::shared_ptr<Ticket> TicketManager::findActiveByPlate(
    const std::string& plate) const {
    return repository_.findActiveByPlate(plate);
}

std::size_t TicketManager::activeCount() const {
    return repository_.activeTickets().size();
}

}  // namespace pms
