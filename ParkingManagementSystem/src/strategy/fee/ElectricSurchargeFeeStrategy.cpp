#include "strategy/fee/ElectricSurchargeFeeStrategy.hpp"

namespace pms {

ElectricSurchargeFeeStrategy::ElectricSurchargeFeeStrategy(
    std::unique_ptr<IFeeStrategy> inner, Money chargingSurcharge)
    : FeeStrategyDecorator(std::move(inner)), surcharge_(chargingSurcharge) {}

Money ElectricSurchargeFeeStrategy::computeFee(const FeeContext& context) const {
    const Money base = baseFee(context);
    if (!context.vehicle.requiresCharging()) {
        return base;  // surcharge only for charging vehicles
    }
    return base + surcharge_;
}

std::string ElectricSurchargeFeeStrategy::name() const {
    return "Electric(" + inner().name() + ")";
}

}  // namespace pms
