#pragma once

#include "strategy/payment/IPaymentStrategy.hpp"

namespace pms {

/// Card settlement via a (simulated) gateway. Succeeds for any positive amount.
class CardPayment final : public IPaymentStrategy {
public:
    PaymentResult pay(const Money& amount) override {
        if (amount <= Money::zero()) {
            return {false, "", "Card declined: non-positive amount"};
        }
        return {true, "CARD-AUTH", "Card authorised"};
    }

    PaymentMethod method() const noexcept override { return PaymentMethod::Card; }
};

}  // namespace pms
