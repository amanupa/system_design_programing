#pragma once

#include "strategy/fee/TimeBasedFeeStrategy.hpp"

namespace pms {

/**
 * @class HourlyFeeStrategy
 * @brief Flat per-hour pricing, rounded up to the next hour, min one hour.
 *
 * Only fills the Template Method hooks — the algorithm itself is inherited.
 */
class HourlyFeeStrategy final : public TimeBasedFeeStrategy {
public:
    explicit HourlyFeeStrategy(Money hourlyRate) noexcept : rate_(hourlyRate) {}

    std::string name() const override { return "Hourly"; }

protected:
    long long billableUnits(Duration parked) const override {
        return ceilToHours(parked);
    }
    Money ratePerUnit(const FeeContext&) const override { return rate_; }
    Money minimumCharge() const override { return rate_; }  // at least one hour

private:
    Money rate_;
};

}  // namespace pms
