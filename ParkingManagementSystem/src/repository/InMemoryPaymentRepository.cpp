#include "repository/InMemoryPaymentRepository.hpp"

namespace pms {

InMemoryPaymentRepository::InMemoryPaymentRepository()
    : store_([](const Payment& p) { return p.id(); }) {}

void InMemoryPaymentRepository::add(std::shared_ptr<Payment> payment) {
    store_.add(std::move(payment));
}

std::shared_ptr<Payment> InMemoryPaymentRepository::findById(
    const std::string& paymentId) const {
    return store_.findById(paymentId);
}

std::vector<std::shared_ptr<Payment>> InMemoryPaymentRepository::findAll() const {
    return store_.findAll();
}

std::size_t InMemoryPaymentRepository::count() const { return store_.count(); }

std::vector<std::shared_ptr<Payment>> InMemoryPaymentRepository::findByTicketId(
    const std::string& ticketId) const {
    std::vector<std::shared_ptr<Payment>> result;
    for (const std::shared_ptr<Payment>& payment : store_.findAll()) {
        if (payment->ticketId() == ticketId) {
            result.push_back(payment);
        }
    }
    return result;
}

}  // namespace pms
