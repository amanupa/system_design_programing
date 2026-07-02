#pragma once

#include <memory>

#include "config/ConfigTypes.hpp"
#include "strategy/fee/IFeeStrategy.hpp"

namespace pms {

/**
 * @class FeeStrategyFactory
 * @brief Assembles the composed fee strategy described by a PricingConfig.
 *
 * Picks the base scheme (hourly/daily/weekend/holiday) then conditionally wraps
 * it with the VIP-discount and EV-surcharge decorators per the config flags.
 * This is the one place that knows how to turn pricing *data* into the
 * Strategy/Decorator object graph — keeping that assembly logic out of the
 * facade (SRP) and reusable/testable on its own.
 */
class FeeStrategyFactory {
public:
    static std::unique_ptr<IFeeStrategy> build(const PricingConfig& pricing);
};

}  // namespace pms
