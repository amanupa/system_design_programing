#pragma once

#include "strategy/fee/TimeBasedFeeStrategy.hpp"

namespace pms {

/**
 * @class DailyFeeStrategy
 * @brief Flat per-day pricing, rounded up to the next day, min one day.
 *
 * Same skeleton as HourlyFeeStrategy — only the granularity hook differs,
 * which is the whole point of Template Method.
 */
class DailyFeeStrategy final : public TimeBasedFeeStrategy {
public:
    explicit DailyFeeStrategy(Money dailyRate) noexcept : rate_(dailyRate) {}

    std::string name() const override { return "Daily"; }

protected:
    long long billableUnits(Duration parked) const override {
        return ceilToDays(parked);
    }
    Money ratePerUnit(const FeeContext&) const override { return rate_; }
    Money minimumCharge() const override { return rate_; }  // at least one day

private:
    Money rate_;
};

}  // namespace pms
