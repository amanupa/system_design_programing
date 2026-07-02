#pragma once

#include <string>

#include "common/enums/PaymentMethod.hpp"
#include "common/enums/PaymentStatus.hpp"
#include "common/util/Money.hpp"
#include "common/util/Time.hpp"

namespace pms {

/**
 * @class Payment
 * @brief Immutable-ish record of one settlement attempt against a ticket.
 *
 * Fields are set at creation and never change, except a Success may transition
 * to Refunded via markRefunded(). (A stricter audit system would append a
 * separate reversal record instead of mutating; we keep one record + a guarded
 * transition for simplicity — KISS — and document the trade-off here.)
 *
 * SOLID: SRP (it is just the settlement record). Identity = payment id.
 */
class Payment {
public:
    Payment(std::string id, std::string ticketId, Money amount,
            PaymentMethod method, PaymentStatus status, std::string reference,
            TimePoint timestamp);

    const std::string& id() const noexcept { return id_; }
    const std::string& ticketId() const noexcept { return ticketId_; }
    Money amount() const noexcept { return amount_; }
    PaymentMethod method() const noexcept { return method_; }
    PaymentStatus status() const noexcept { return status_; }
    const std::string& reference() const noexcept { return reference_; }
    TimePoint timestamp() const noexcept { return timestamp_; }

    bool isSuccessful() const noexcept { return status_ == PaymentStatus::Success; }

    /// @throws InvalidArgumentException if the payment is not currently Success.
    void markRefunded();

private:
    std::string id_;
    std::string ticketId_;
    Money amount_;
    PaymentMethod method_;
    PaymentStatus status_;
    std::string reference_;
    TimePoint timestamp_;
};

}  // namespace pms
