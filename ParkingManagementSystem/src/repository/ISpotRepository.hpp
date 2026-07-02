#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "domain/floor/ParkingFloor.hpp"
#include "domain/spot/ParkingSpot.hpp"

namespace pms {

/**
 * @class ISpotRepository
 * @brief Storage/retrieval abstraction for the parking inventory (floors+spots).
 *
 * Why it exists:
 *   The inventory's *source* (hard-coded config now; a SQL/Mongo load later) is
 *   an infrastructure concern. By depending on this interface, SpotManager and
 *   the rest of the domain never learn where spots come from — swap the impl,
 *   nothing else changes. That is the Repository pattern serving Dependency
 *   Inversion.
 *
 * Scope: this repository owns the inventory aggregate (floors, which own spots)
 * and exposes lookups + aggregate counts. *Selection* of a spot is NOT here —
 * that is the allocation Strategy's job.
 *
 * SOLID: SRP (storage/retrieval only), DIP (clients depend on this contract),
 * ISP (a small, query-focused surface).
 */
class ISpotRepository {
public:
    virtual ~ISpotRepository() = default;

    /// Add a fully-built floor (with its spots) to the inventory.
    virtual void addFloor(std::unique_ptr<ParkingFloor> floor) = 0;

    /// Non-owning view of all floors, in insertion order.
    virtual std::vector<ParkingFloor*> floors() const = 0;

    /// Locate a spot by id across all floors, or nullptr. Non-owning.
    virtual ParkingSpot* findSpotById(const std::string& id) const = 0;

    virtual std::size_t totalSpots() const = 0;
    virtual std::size_t availableCount() const = 0;
    virtual std::size_t occupiedCount() const = 0;
};

}  // namespace pms
