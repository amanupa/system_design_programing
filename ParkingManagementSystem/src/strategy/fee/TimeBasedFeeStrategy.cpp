#include "strategy/fee/TimeBasedFeeStrategy.hpp"

#include <algorithm>

namespace pms {

Money TimeBasedFeeStrategy::computeFee(const FeeContext& context) const {
    const long long units = billableUnits(context.duration());
    const Money subtotal = ratePerUnit(context) * units;
    return std::max(subtotal, minimumCharge());
}

long long TimeBasedFeeStrategy::ceilToHours(Duration parked) noexcept {
    const long long seconds = parked.count();
    if (seconds <= 0) {
        return 0;
    }
    constexpr long long kSecondsPerHour = 3600;
    return (seconds + kSecondsPerHour - 1) / kSecondsPerHour;
}

long long TimeBasedFeeStrategy::ceilToDays(Duration parked) noexcept {
    const long long seconds = parked.count();
    if (seconds <= 0) {
        return 0;
    }
    constexpr long long kSecondsPerDay = 86400;
    return (seconds + kSecondsPerDay - 1) / kSecondsPerDay;
}

}  // namespace pms
