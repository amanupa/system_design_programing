#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "domain/ticket/Ticket.hpp"

namespace pms {

/**
 * @class ITicketRepository
 * @brief Focused storage contract for tickets.
 *
 * Deliberately a *separate, minimal* interface (not `IRepository<Ticket,...>`)
 * so ticket clients see only the operations they need (Interface Segregation)
 * plus ticket-specific queries. The in-memory implementation reuses the generic
 * InMemoryRepository internally by composition — avoiding the multiple-
 * inheritance "repository diamond" while still sharing the CRUD code (DRY).
 *
 * SOLID: ISP (small, intent-revealing surface), DIP (clients depend on this).
 */
class ITicketRepository {
public:
    virtual ~ITicketRepository() = default;

    virtual void add(std::shared_ptr<Ticket> ticket) = 0;
    virtual std::shared_ptr<Ticket> findById(const std::string& ticketId) const = 0;
    virtual std::vector<std::shared_ptr<Ticket>> findAll() const = 0;
    virtual std::size_t count() const = 0;

    /// The single Active ticket for a plate, or nullptr (a vehicle parks once).
    virtual std::shared_ptr<Ticket> findActiveByPlate(
        const std::string& licensePlate) const = 0;

    /// All currently-active (un-exited) tickets.
    virtual std::vector<std::shared_ptr<Ticket>> activeTickets() const = 0;
};

}  // namespace pms
