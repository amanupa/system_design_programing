#pragma once

#include "strategy/fee/FeeStrategyDecorator.hpp"

namespace pms {

/**
 * @class VipDiscountFeeStrategy
 * @brief Decorator that gives privileged vehicles a percentage discount.
 *
 * The discount applies ONLY when the vehicle is privileged, so a single
 * instance can wrap the base scheme for the whole lot and naturally leaves
 * ordinary vehicles unaffected.
 */
class VipDiscountFeeStrategy final : public FeeStrategyDecorator {
public:
    VipDiscountFeeStrategy(std::unique_ptr<IFeeStrategy> inner, int discountPercent);

    Money computeFee(const FeeContext& context) const override;
    std::string name() const override;

private:
    int discountPercent_;
};

}  // namespace pms
