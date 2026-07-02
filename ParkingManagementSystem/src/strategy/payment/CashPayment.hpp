#pragma once

#include "strategy/payment/IPaymentStrategy.hpp"

namespace pms {

/// Cash settlement at the booth. Succeeds for any positive amount.
class CashPayment final : public IPaymentStrategy {
public:
    PaymentResult pay(const Money& amount) override {
        if (amount <= Money::zero()) {
            return {false, "", "Cash amount must be positive"};
        }
        return {true, "CASH-RECEIPT", "Cash accepted"};
    }

    PaymentMethod method() const noexcept override { return PaymentMethod::Cash; }
};

}  // namespace pms
