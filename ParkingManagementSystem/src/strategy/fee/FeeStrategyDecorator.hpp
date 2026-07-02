#pragma once

#include <memory>
#include <utility>

#include "common/exceptions/ParkingException.hpp"
#include "strategy/fee/IFeeStrategy.hpp"

namespace pms {

/**
 * @class FeeStrategyDecorator
 * @brief Base for fee adjustments that wrap another IFeeStrategy.
 *
 * Pattern: Decorator. A decorator IS-A IFeeStrategy and HAS-A inner
 * IFeeStrategy, so adjustments (VIP discount, EV surcharge, loyalty points, …)
 * stack in any order — `Electric(Vip(Hourly()))` — without any pricing scheme
 * knowing those concerns exist (OCP). Still abstract: concrete decorators supply
 * computeFee()/name().
 */
class FeeStrategyDecorator : public IFeeStrategy {
public:
    explicit FeeStrategyDecorator(std::unique_ptr<IFeeStrategy> inner)
        : inner_(std::move(inner)) {
        if (!inner_) {
            throw InvalidArgumentException("FeeStrategyDecorator: inner is null");
        }
    }

protected:
    Money baseFee(const FeeContext& context) const {
        return inner_->computeFee(context);
    }
    const IFeeStrategy& inner() const noexcept { return *inner_; }

private:
    std::unique_ptr<IFeeStrategy> inner_;
};

}  // namespace pms
