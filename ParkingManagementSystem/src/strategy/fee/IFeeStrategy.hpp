#pragma once

#include <string>

#include "common/util/Money.hpp"
#include "strategy/fee/FeeContext.hpp"

namespace pms {

/**
 * @class IFeeStrategy
 * @brief Strategy that prices a single parking session.
 *
 * Pattern: Strategy. Pricing policy (hourly / daily / weekend / holiday / VIP /
 * EV / future schemes) varies independently of everything else, so it is an
 * interchangeable object. The fee calculator holds one and never branches on
 * "what kind of pricing is this" — new schemes are new classes (OCP).
 *
 * Pure & const: a strategy is a referentially-transparent function of its
 * context, which makes pricing reproducible and unit-testable.
 */
class IFeeStrategy {
public:
    virtual ~IFeeStrategy() = default;

    virtual Money computeFee(const FeeContext& context) const = 0;
    virtual std::string name() const = 0;
};

}  // namespace pms
