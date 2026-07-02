#pragma once

#include "common/util/Money.hpp"
#include "strategy/fee/FeeStrategyDecorator.hpp"

namespace pms {

/**
 * @class ElectricSurchargeFeeStrategy
 * @brief Decorator that adds a flat charging surcharge for vehicles that need
 *        charging.
 *
 * Applies ONLY when the vehicle requires charging, so it composes cleanly with
 * any base scheme and any other decorator (e.g. wrapped around a VIP discount).
 */
class ElectricSurchargeFeeStrategy final : public FeeStrategyDecorator {
public:
    ElectricSurchargeFeeStrategy(std::unique_ptr<IFeeStrategy> inner,
                                 Money chargingSurcharge);

    Money computeFee(const FeeContext& context) const override;
    std::string name() const override;

private:
    Money surcharge_;
};

}  // namespace pms
