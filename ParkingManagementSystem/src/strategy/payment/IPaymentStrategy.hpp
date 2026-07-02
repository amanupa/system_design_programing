#pragma once

#include <string>

#include "common/enums/PaymentMethod.hpp"
#include "common/util/Money.hpp"

namespace pms {

/// Outcome of attempting a payment through a channel.
struct PaymentResult {
    bool success;
    std::string reference;  // gateway/transaction reference for the record
    std::string message;    // human-readable detail (esp. on failure)
};

/**
 * @class IPaymentStrategy
 * @brief Strategy for settling an amount through one channel (cash/card/UPI/…).
 *
 * Pattern: Strategy. Each channel encapsulates its own processing rules behind a
 * uniform pay() call, so PaymentManager never branches on the method — adding a
 * channel is a new strategy + a registration (OCP).
 *
 * Strategies are pure of infrastructure (no repo/clock/id); they just process
 * and report. Persisting the record is PaymentManager's job (SRP).
 */
class IPaymentStrategy {
public:
    virtual ~IPaymentStrategy() = default;

    virtual PaymentResult pay(const Money& amount) = 0;
    virtual PaymentMethod method() const noexcept = 0;
};

}  // namespace pms
