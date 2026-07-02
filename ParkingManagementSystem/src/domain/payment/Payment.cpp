#include "domain/payment/Payment.hpp"

#include <utility>

#include "common/exceptions/ParkingException.hpp"

namespace pms {

Payment::Payment(std::string id, std::string ticketId, Money amount,
                 PaymentMethod method, PaymentStatus status,
                 std::string reference, TimePoint timestamp)
    : id_(std::move(id)),
      ticketId_(std::move(ticketId)),
      amount_(amount),
      method_(method),
      status_(status),
      reference_(std::move(reference)),
      timestamp_(timestamp) {
    if (id_.empty()) {
        throw InvalidArgumentException("Payment: id must not be empty");
    }
    if (ticketId_.empty()) {
        throw InvalidArgumentException("Payment: ticketId must not be empty");
    }
}

void Payment::markRefunded() {
    if (status_ != PaymentStatus::Success) {
        throw InvalidArgumentException(
            "Payment " + id_ + ": only a successful payment can be refunded");
    }
    status_ = PaymentStatus::Refunded;
}

}  // namespace pms
