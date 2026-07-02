#pragma once

#include "repository/ITicketRepository.hpp"
#include "repository/InMemoryRepository.hpp"

namespace pms {

/**
 * @class InMemoryTicketRepository
 * @brief ITicketRepository backed by a generic InMemoryRepository (composition).
 *
 * CRUD is delegated to the embedded generic store; only the ticket-specific
 * queries are implemented here. This reuses tested storage code without
 * inheriting it (composition over inheritance, Rule 5) and sidesteps the
 * diamond that direct multiple inheritance would create.
 */
class InMemoryTicketRepository : public ITicketRepository {
public:
    InMemoryTicketRepository();

    void add(std::shared_ptr<Ticket> ticket) override;
    std::shared_ptr<Ticket> findById(const std::string& ticketId) const override;
    std::vector<std::shared_ptr<Ticket>> findAll() const override;
    std::size_t count() const override;

    std::shared_ptr<Ticket> findActiveByPlate(
        const std::string& licensePlate) const override;
    std::vector<std::shared_ptr<Ticket>> activeTickets() const override;

private:
    InMemoryRepository<Ticket, std::string> store_;
};

}  // namespace pms
