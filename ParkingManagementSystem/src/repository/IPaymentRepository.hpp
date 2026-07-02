#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "domain/payment/Payment.hpp"

namespace pms {

/**
 * @class IPaymentRepository
 * @brief Focused storage contract for payment records.
 *
 * Mirrors ITicketRepository: a minimal ISP interface plus a payment-specific
 * query, implemented by composing the generic InMemoryRepository.
 */
class IPaymentRepository {
public:
    virtual ~IPaymentRepository() = default;

    virtual void add(std::shared_ptr<Payment> payment) = 0;
    virtual std::shared_ptr<Payment> findById(const std::string& paymentId) const = 0;
    virtual std::vector<std::shared_ptr<Payment>> findAll() const = 0;
    virtual std::size_t count() const = 0;

    /// All payment records (incl. failed/refunded) for a given ticket.
    virtual std::vector<std::shared_ptr<Payment>> findByTicketId(
        const std::string& ticketId) const = 0;
};

}  // namespace pms
