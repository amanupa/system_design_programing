#pragma once

#include "strategy/ISpotAllocationStrategy.hpp"

namespace pms {

/**
 * @class NearestFirstStrategy
 * @brief Minimise walking distance: pick the lowest floor, then lowest id.
 *
 * A deliberately different policy from BestFit — same inputs, different choice —
 * to demonstrate that allocation behaviour is fully pluggable. Ignores waste; a
 * mall that prioritises customer convenience over spot utilisation would use this.
 */
class NearestFirstStrategy final : public ISpotAllocationStrategy {
public:
    ParkingSpot* selectSpot(
        const Vehicle& vehicle,
        const std::vector<ParkingSpot*>& candidates) const override;

    std::string name() const override { return "NearestFirst"; }
};

}  // namespace pms
