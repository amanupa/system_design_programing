#pragma once

#include <memory>
#include <string>

#include "common/enums/PaymentMethod.hpp"
#include "common/logging/ILogger.hpp"
#include "common/util/IClock.hpp"
#include "common/util/Money.hpp"
#include "domain/gate/IEntryGate.hpp"
#include "domain/gate/IExitGate.hpp"
#include "domain/payment/Payment.hpp"
#include "domain/ticket/Ticket.hpp"
#include "domain/vehicle/Vehicle.hpp"
#include "manager/FeeCalculator.hpp"
#include "manager/PaymentManager.hpp"
#include "manager/SpotManager.hpp"
#include "manager/TicketManager.hpp"

namespace pms {

/// What a completed exit produces.
struct ExitReceipt {
    std::shared_ptr<Ticket> ticket;
    Money fee;
    std::shared_ptr<Payment> payment;
};

/**
 * @class ParkingService
 * @brief Application layer — orchestrates the park and exit use-cases.
 *
 * It owns no data and contains no business rules; it sequences the managers in
 * the right order and guarantees the cross-manager invariants (rollback on a
 * failed entry; pay-before-exit). All collaborators are injected (DI).
 *
 * The use-case signatures enforce capability via the ISP gate interfaces:
 *   - parkVehicle requires an IEntryGate&  -> an exit-only gate cannot compile.
 *   - exitVehicle requires an IExitGate&.
 *
 * SOLID: SRP (use-case orchestration), DIP (depends on managers, all abstract
 * underneath), OCP (managers/strategies swap beneath it untouched).
 */
class ParkingService {
public:
    ParkingService(SpotManager& spotManager, TicketManager& ticketManager,
                   FeeCalculator& feeCalculator, PaymentManager& paymentManager,
                   IClock& clock, ILogger& logger) noexcept;

    ParkingService(const ParkingService&) = delete;
    ParkingService& operator=(const ParkingService&) = delete;

    /**
     * Admit a vehicle: allocate a spot then issue a ticket. If ticket issue
     * fails, the spot allocation is rolled back (no orphaned occupancy).
     * @throws GateUnavailableException if the gate cannot serve entries.
     * @throws SpotUnavailableException if the lot is full for this vehicle.
     */
    std::shared_ptr<Ticket> parkVehicle(IEntryGate& entryGate,
                                        std::shared_ptr<const Vehicle> vehicle);

    /**
     * Process an exit: quote the fee, take payment, then close the ticket and
     * free the spot. Nothing is mutated until payment succeeds.
     * @throws GateUnavailableException if the gate cannot serve exits.
     * @throws TicketNotFoundException  if the ticket id is unknown.
     * @throws InvalidArgumentException if the ticket was already closed.
     * @throws PaymentFailedException   if payment is declined (car stays inside).
     */
    ExitReceipt exitVehicle(IExitGate& exitGate, const std::string& ticketId,
                            PaymentMethod method);

private:
    SpotManager& spotManager_;
    TicketManager& ticketManager_;
    FeeCalculator& feeCalculator_;
    PaymentManager& paymentManager_;
    IClock& clock_;
    ILogger& logger_;
};

}  // namespace pms
