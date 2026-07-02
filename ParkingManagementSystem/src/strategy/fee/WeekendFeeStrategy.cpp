#include "strategy/fee/WeekendFeeStrategy.hpp"

#include "common/util/Time.hpp"

namespace pms {

Money WeekendFeeStrategy::ratePerUnit(const FeeContext& context) const {
    return isWeekend(context.entryTime) ? weekendRate_ : weekdayRate_;
}

}  // namespace pms
