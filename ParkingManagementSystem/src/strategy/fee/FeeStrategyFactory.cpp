#include "strategy/fee/FeeStrategyFactory.hpp"

#include "common/exceptions/ParkingException.hpp"
#include "strategy/fee/DailyFeeStrategy.hpp"
#include "strategy/fee/ElectricSurchargeFeeStrategy.hpp"
#include "strategy/fee/HolidayFeeStrategy.hpp"
#include "strategy/fee/HourlyFeeStrategy.hpp"
#include "strategy/fee/VipDiscountFeeStrategy.hpp"
#include "strategy/fee/WeekendFeeStrategy.hpp"

namespace pms {

std::unique_ptr<IFeeStrategy> FeeStrategyFactory::build(
    const PricingConfig& pricing) {
    // 1. Base scheme.
    std::unique_ptr<IFeeStrategy> strategy;
    switch (pricing.scheme) {
        case PricingScheme::Hourly:
            strategy = std::make_unique<HourlyFeeStrategy>(pricing.baseRate);
            break;
        case PricingScheme::Daily:
            strategy = std::make_unique<DailyFeeStrategy>(pricing.baseRate);
            break;
        case PricingScheme::Weekend:
            strategy = std::make_unique<WeekendFeeStrategy>(pricing.baseRate,
                                                            pricing.premiumRate);
            break;
        case PricingScheme::Holiday:
            strategy = std::make_unique<HolidayFeeStrategy>(
                pricing.baseRate, pricing.premiumRate, pricing.holidays);
            break;
    }
    if (!strategy) {
        throw InvalidConfigurationException("FeeStrategyFactory: unknown scheme");
    }

    // 2. Optional adjustment decorators (order: VIP discount, then EV surcharge).
    if (pricing.vipDiscountEnabled) {
        strategy = std::make_unique<VipDiscountFeeStrategy>(
            std::move(strategy), pricing.vipDiscountPercent);
    }
    if (pricing.electricSurchargeEnabled) {
        strategy = std::make_unique<ElectricSurchargeFeeStrategy>(
            std::move(strategy), pricing.electricSurcharge);
    }
    return strategy;
}

}  // namespace pms
