#include "strategy/fee/VipDiscountFeeStrategy.hpp"

#include "common/exceptions/ParkingException.hpp"

namespace pms {

VipDiscountFeeStrategy::VipDiscountFeeStrategy(std::unique_ptr<IFeeStrategy> inner,
                                               int discountPercent)
    : FeeStrategyDecorator(std::move(inner)), discountPercent_(discountPercent) {
    if (discountPercent_ < 0 || discountPercent_ > 100) {
        throw InvalidArgumentException(
            "VipDiscountFeeStrategy: discount percent must be in [0, 100]");
    }
}

Money VipDiscountFeeStrategy::computeFee(const FeeContext& context) const {
    const Money base = baseFee(context);
    if (!context.vehicle.isPrivileged()) {
        return base;  // discount only for VIPs
    }
    return base - base.percent(discountPercent_);
}

std::string VipDiscountFeeStrategy::name() const {
    return "Vip(" + inner().name() + ")";
}

}  // namespace pms
