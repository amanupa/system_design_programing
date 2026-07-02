#pragma once

#include "strategy/fee/TimeBasedFeeStrategy.hpp"

namespace pms {

/**
 * @class WeekendFeeStrategy
 * @brief Hourly pricing whose per-hour rate depends on whether entry was on a
 *        weekend.
 *
 * Demonstrates a Template Method hook (ratePerUnit) using the FeeContext to vary
 * one step of the otherwise-shared algorithm — no skeleton duplication.
 */
class WeekendFeeStrategy final : public TimeBasedFeeStrategy {
public:
    WeekendFeeStrategy(Money weekdayRate, Money weekendRate) noexcept
        : weekdayRate_(weekdayRate), weekendRate_(weekendRate) {}

    std::string name() const override { return "Weekend"; }

protected:
    long long billableUnits(Duration parked) const override {
        return ceilToHours(parked);
    }
    Money ratePerUnit(const FeeContext& context) const override;
    Money minimumCharge() const override { return weekdayRate_; }

private:
    Money weekdayRate_;
    Money weekendRate_;
};

}  // namespace pms
