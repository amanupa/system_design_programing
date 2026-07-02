#pragma once

#include <cstddef>
#include <memory>
#include <string>

#include "common/logging/ILogger.hpp"
#include "common/util/IClock.hpp"
#include "common/util/IIdGenerator.hpp"
#include "domain/spot/ParkingSpot.hpp"
#include "domain/ticket/Ticket.hpp"
#include "domain/vehicle/Vehicle.hpp"
#include "repository/ITicketRepository.hpp"

namespace pms {

/**
 * @class TicketManager
 * @brief Issues, closes, and looks up tickets.
 *
 * Single responsibility: the ticket lifecycle. It stamps entry/exit times from
 * the injected IClock and mints ids from the injected IIdGenerator — both
 * abstractions, so tests can drive deterministic time and ids.
 *
 * Collaborators (all injected — DI): ITicketRepository&, IClock&,
 * IIdGenerator&, ILogger&.
 *
 * SOLID: SRP, DIP (four abstractions, zero concretions), OCP (swap repo/clock).
 */
class TicketManager {
public:
    TicketManager(ITicketRepository& repository, IClock& clock,
                  IIdGenerator& idGenerator, ILogger& logger);

    TicketManager(const TicketManager&) = delete;
    TicketManager& operator=(const TicketManager&) = delete;

    /**
     * Issue an Active ticket for a vehicle that has just been parked.
     * @param spot the spot the vehicle now occupies (read for id + floor).
     * @throws InvalidArgumentException via the builder if inputs are invalid.
     */
    std::shared_ptr<Ticket> issue(const std::shared_ptr<const Vehicle>& vehicle,
                                  const ParkingSpot& spot,
                                  const std::string& entryGateId);

    /**
     * Close a ticket on exit (stamps exit time from the clock).
     * @throws TicketNotFoundException if the id is unknown.
     */
    std::shared_ptr<Ticket> close(const std::string& ticketId,
                                  const std::string& exitGateId);

    /// Lookup that throws if absent (use when the ticket must exist).
    std::shared_ptr<Ticket> find(const std::string& ticketId) const;

    /// The active ticket for a plate, or nullptr.
    std::shared_ptr<Ticket> findActiveByPlate(const std::string& plate) const;

    std::size_t activeCount() const;
    std::size_t totalCount() const { return repository_.count(); }

private:
    ITicketRepository& repository_;
    IClock& clock_;
    IIdGenerator& idGenerator_;
    ILogger& logger_;
};

}  // namespace pms
