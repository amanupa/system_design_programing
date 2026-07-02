#pragma once

#include "strategy/payment/IPaymentStrategy.hpp"

namespace pms {

/// UPI settlement via a (simulated) VPA collect request. Succeeds for any
/// positive amount.
class UpiPayment final : public IPaymentStrategy {
public:
    PaymentResult pay(const Money& amount) override {
        if (amount <= Money::zero()) {
            return {false, "", "UPI failed: non-positive amount"};
        }
        return {true, "UPI-TXN", "UPI collect successful"};
    }

    PaymentMethod method() const noexcept override { return PaymentMethod::Upi; }
};

}  // namespace pms
