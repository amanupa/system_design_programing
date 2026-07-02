#include "manager/FeeCalculator.hpp"

#include <utility>

#include "common/exceptions/ParkingException.hpp"
#include "strategy/fee/FeeContext.hpp"

namespace pms {

FeeCalculator::FeeCalculator(std::unique_ptr<IFeeStrategy> strategy,
                             ILogger& logger)
    : strategy_(std::move(strategy)), logger_(logger) {
    if (!strategy_) {
        throw InvalidArgumentException("FeeCalculator: strategy must not be null");
    }
}

Money FeeCalculator::quote(const Vehicle& vehicle, TimePoint entry,
                           TimePoint exit) const {
    const FeeContext context{entry, exit, vehicle};
    return strategy_->computeFee(context);  // pure: no logging/side effects
}

Money FeeCalculator::computeFor(const Ticket& ticket) const {
    if (!ticket.exitTime().has_value()) {
        throw InvalidArgumentException(
            "FeeCalculator: ticket " + ticket.id() + " is not closed");
    }
    const Money fee = quote(ticket.vehicle(), ticket.entryTime(), *ticket.exitTime());
    logger_.info("Fee for ticket " + ticket.id() + " (" + strategy_->name() +
                 "): " + fee.toString());
    return fee;
}

void FeeCalculator::setStrategy(std::unique_ptr<IFeeStrategy> strategy) {
    if (!strategy) {
        throw InvalidArgumentException("FeeCalculator::setStrategy: strategy is null");
    }
    strategy_ = std::move(strategy);
}

}  // namespace pms
