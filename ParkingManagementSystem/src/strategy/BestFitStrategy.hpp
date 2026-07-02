#pragma once

#include "strategy/ISpotAllocationStrategy.hpp"

namespace pms {

/**
 * @class BestFitStrategy
 * @brief Minimise wasted resources: pick the tightest, least-premium spot.
 *
 * Ranking (lexicographically smallest wins):
 *   1. capacity gap        — prefer the smallest spot that still fits
 *                            (don't burn a Large spot on a bike).
 *   2. charging waste      — avoid occupying a charging spot with a non-EV.
 *   3. premium (VIP) waste — avoid occupying a VIP spot with a non-VIP.
 *   4. floor, then id      — deterministic tie-break (reproducible tests).
 *
 * This is the *policy* that ParkingSpot deliberately did NOT encode — proving
 * the Phase-3 entity/policy split pays off: the same spots support a different
 * policy just by swapping this object.
 */
class BestFitStrategy final : public ISpotAllocationStrategy {
public:
    ParkingSpot* selectSpot(
        const Vehicle& vehicle,
        const std::vector<ParkingSpot*>& candidates) const override;

    std::string name() const override { return "BestFit"; }
};

}  // namespace pms
