#include "strategy/fee/HolidayFeeStrategy.hpp"

#include "common/util/Time.hpp"

namespace pms {

Money HolidayFeeStrategy::ratePerUnit(const FeeContext& context) const {
    const std::string date = toDateString(context.entryTime);
    return holidays_.count(date) > 0 ? holidayRate_ : normalRate_;
}

}  // namespace pms
