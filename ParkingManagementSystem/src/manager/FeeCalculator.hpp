#pragma once

#include <memory>
#include <string>

#include "common/logging/ILogger.hpp"
#include "common/util/Money.hpp"
#include "common/util/Time.hpp"
#include "domain/ticket/Ticket.hpp"
#include "domain/vehicle/Vehicle.hpp"
#include "strategy/fee/IFeeStrategy.hpp"

namespace pms {

/**
 * @class FeeCalculator
 * @brief Prices a (closed) ticket using its injected, possibly-composed strategy.
 *
 * It owns one IFeeStrategy — which may itself be a stack of decorators over a
 * base scheme — and turns a Ticket into a FeeContext for it. The pricing policy
 * is swappable at runtime (setStrategy), so switching the whole lot from hourly
 * to weekend pricing is a one-line change with no edits here (OCP).
 *
 * Collaborators (injected): IFeeStrategy (owned), ILogger&.
 * SOLID: SRP (turn a ticket into a price), DIP, OCP.
 */
class FeeCalculator {
public:
    FeeCalculator(std::unique_ptr<IFeeStrategy> strategy, ILogger& logger);

    FeeCalculator(const FeeCalculator&) = delete;
    FeeCalculator& operator=(const FeeCalculator&) = delete;

    /// Price a parking interval directly — used to quote a fee at exit BEFORE the
    /// ticket is closed (so payment can be taken first). Pure, no side effects.
    Money quote(const Vehicle& vehicle, TimePoint entry, TimePoint exit) const;

    /// Price a closed ticket (delegates to quote()).
    /// @throws InvalidArgumentException if the ticket has not been closed (no exit).
    Money computeFor(const Ticket& ticket) const;

    void setStrategy(std::unique_ptr<IFeeStrategy> strategy);
    std::string strategyName() const { return strategy_->name(); }

private:
    std::unique_ptr<IFeeStrategy> strategy_;
    ILogger& logger_;
};

}  // namespace pms
