#pragma once

#include "repository/IPaymentRepository.hpp"
#include "repository/InMemoryRepository.hpp"

namespace pms {

/**
 * @class InMemoryPaymentRepository
 * @brief IPaymentRepository backed by the generic InMemoryRepository (composition).
 *
 * Identical shape to InMemoryTicketRepository — proof the generic store pays off:
 * a second entity gets persistence + lookup with only its bespoke query written
 * by hand.
 */
class InMemoryPaymentRepository : public IPaymentRepository {
public:
    InMemoryPaymentRepository();

    void add(std::shared_ptr<Payment> payment) override;
    std::shared_ptr<Payment> findById(const std::string& paymentId) const override;
    std::vector<std::shared_ptr<Payment>> findAll() const override;
    std::size_t count() const override;

    std::vector<std::shared_ptr<Payment>> findByTicketId(
        const std::string& ticketId) const override;

private:
    InMemoryRepository<Payment, std::string> store_;
};

}  // namespace pms
