#pragma once

#include <set>
#include <string>

#include "strategy/fee/TimeBasedFeeStrategy.hpp"

namespace pms {

/**
 * @class HolidayFeeStrategy
 * @brief Hourly pricing with a premium rate on a configured set of holidays.
 *
 * Holidays are injected as a set of "YYYY-MM-DD" strings (configuration data),
 * so the same class serves any calendar without code changes (OCP / data-driven).
 */
class HolidayFeeStrategy final : public TimeBasedFeeStrategy {
public:
    HolidayFeeStrategy(Money normalRate, Money holidayRate,
                       std::set<std::string> holidays)
        : normalRate_(normalRate),
          holidayRate_(holidayRate),
          holidays_(std::move(holidays)) {}

    std::string name() const override { return "Holiday"; }

protected:
    long long billableUnits(Duration parked) const override {
        return ceilToHours(parked);
    }
    Money ratePerUnit(const FeeContext& context) const override;
    Money minimumCharge() const override { return normalRate_; }

private:
    Money normalRate_;
    Money holidayRate_;
    std::set<std::string> holidays_;
};

}  // namespace pms
