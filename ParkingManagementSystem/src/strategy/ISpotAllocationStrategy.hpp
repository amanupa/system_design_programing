#pragma once

#include <string>
#include <vector>

#include "domain/spot/ParkingSpot.hpp"
#include "domain/vehicle/Vehicle.hpp"

namespace pms {

/**
 * @class ISpotAllocationStrategy
 * @brief Policy that picks ONE spot for a vehicle from fitting candidates.
 *
 * Pattern: Strategy.
 *   Allocation policy varies independently of the rest of the system (best-fit
 *   today, nearest-to-lift tomorrow, demand-based pricing-aware later). Encoding
 *   each policy as an interchangeable object lets SpotManager swap behaviour at
 *   runtime without conditionals — the textbook reason to choose Strategy over a
 *   growing `if/switch` block in the manager.
 *
 * Contract:
 *   - `candidates` are guaranteed by the caller to be free AND physically able
 *     to hold the vehicle (canFit already true). The strategy applies *business
 *     preference* on top (waste avoidance, VIP access, proximity).
 *   - Returns a pointer from `candidates`, or nullptr if it declines them all.
 *   - Pure/const: a strategy holds no mutable per-call state and must not modify
 *     the spots (assignment is the manager's job) — easy to reason about & test.
 *
 * SOLID: SRP (selection only), OCP (new policy = new class), DIP, ISP.
 */
class ISpotAllocationStrategy {
public:
    virtual ~ISpotAllocationStrategy() = default;

    virtual ParkingSpot* selectSpot(
        const Vehicle& vehicle,
        const std::vector<ParkingSpot*>& candidates) const = 0;

    /// Human-readable identity (also used to compose decorator names).
    virtual std::string name() const = 0;
};

}  // namespace pms
