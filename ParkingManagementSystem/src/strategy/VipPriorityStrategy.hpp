#pragma once

#include <memory>

#include "strategy/ISpotAllocationStrategy.hpp"

namespace pms {

/**
 * @class VipPriorityStrategy
 * @brief Decorator adding VIP access rules on top of any inner strategy.
 *
 * Pattern: Decorator (over the Strategy interface).
 *   It IS-A ISpotAllocationStrategy and HAS-A inner ISpotAllocationStrategy,
 *   so it can wrap BestFit, NearestFirst, or even another decorator. The VIP
 *   concern is layered in without touching the wrapped policies — Open/Closed
 *   at its cleanest, and exactly when Decorator is justified (an orthogonal,
 *   composable concern rather than a new monolithic policy).
 *
 * Behaviour:
 *   - Privileged vehicle  : prefer VIP spots; if any exist, choose among those
 *                           via the inner policy, else fall back to all candidates.
 *   - Ordinary vehicle    : VIP spots are RESERVED — they are filtered out before
 *                           delegating, so a VIP space is never spent on a non-VIP.
 *
 * SOLID: OCP (new behaviour by composition), LSP (still a valid strategy), SRP
 * (only the VIP concern), DIP (depends on the strategy abstraction it wraps).
 */
class VipPriorityStrategy final : public ISpotAllocationStrategy {
public:
    explicit VipPriorityStrategy(std::unique_ptr<ISpotAllocationStrategy> inner);

    ParkingSpot* selectSpot(
        const Vehicle& vehicle,
        const std::vector<ParkingSpot*>& candidates) const override;

    std::string name() const override;

private:
    std::unique_ptr<ISpotAllocationStrategy> inner_;
};

}  // namespace pms
