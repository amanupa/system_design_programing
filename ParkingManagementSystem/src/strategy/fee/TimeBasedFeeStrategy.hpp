#pragma once

#include "strategy/fee/IFeeStrategy.hpp"

namespace pms {

/**
 * @class TimeBasedFeeStrategy
 * @brief Template Method base for any duration-driven pricing scheme.
 *
 * Pattern: Template Method.
 *   computeFee() is `final` — it fixes the *algorithm shape* that all
 *   time-based schemes share:
 *       units      = billableUnits(duration)     // how granular? (hooks)
 *       subtotal   = ratePerUnit(context) * units // how much per unit? (hook)
 *       fee        = max(subtotal, minimumCharge) // never below the floor (hook)
 *   Subclasses cannot reorder or skip these steps; they only fill the hooks.
 *   That is exactly the guarantee Template Method gives over copy-pasting the
 *   skeleton into each scheme.
 *
 * The protected ceil helpers are shared by all subclasses (DRY).
 */
class TimeBasedFeeStrategy : public IFeeStrategy {
public:
    Money computeFee(const FeeContext& context) const final;

protected:
    /// Number of chargeable units for the parked duration (rounded UP).
    virtual long long billableUnits(Duration parked) const = 0;

    /// Price of one unit; may depend on the context (e.g. weekend vs weekday).
    virtual Money ratePerUnit(const FeeContext& context) const = 0;

    /// Lower bound applied to the subtotal. Default: no floor.
    virtual Money minimumCharge() const { return Money::zero(); }

    static long long ceilToHours(Duration parked) noexcept;
    static long long ceilToDays(Duration parked) noexcept;
};

}  // namespace pms
