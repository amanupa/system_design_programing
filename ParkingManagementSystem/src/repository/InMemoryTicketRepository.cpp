#include "repository/InMemoryTicketRepository.hpp"

namespace pms {

InMemoryTicketRepository::InMemoryTicketRepository()
    : store_([](const Ticket& t) { return t.id(); }) {}

void InMemoryTicketRepository::add(std::shared_ptr<Ticket> ticket) {
    store_.add(std::move(ticket));
}

std::shared_ptr<Ticket> InMemoryTicketRepository::findById(
    const std::string& ticketId) const {
    return store_.findById(ticketId);
}

std::vector<std::shared_ptr<Ticket>> InMemoryTicketRepository::findAll() const {
    return store_.findAll();
}

std::size_t InMemoryTicketRepository::count() const { return store_.count(); }

std::shared_ptr<Ticket> InMemoryTicketRepository::findActiveByPlate(
    const std::string& licensePlate) const {
    for (const std::shared_ptr<Ticket>& ticket : store_.findAll()) {
        if (ticket->isActive() &&
            ticket->vehicle().licensePlate() == licensePlate) {
            return ticket;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Ticket>> InMemoryTicketRepository::activeTickets()
    const {
    std::vector<std::shared_ptr<Ticket>> active;
    for (const std::shared_ptr<Ticket>& ticket : store_.findAll()) {
        if (ticket->isActive()) {
            active.push_back(ticket);
        }
    }
    return active;
}

}  // namespace pms
