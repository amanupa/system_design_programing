#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "common/enums/SpotType.hpp"
#include "domain/spot/ParkingSpot.hpp"
#include "domain/vehicle/Vehicle.hpp"

namespace pms {

/**
 * @class ParkingFloor
 * @brief Owns the spots on one physical level and answers read-only queries.
 *
 * Responsibilities:
 *   - Own its spots (composition: floor lifetime governs spot lifetime).
 *   - Report counts and locate spots.
 *   - Offer *candidate* spots that physically fit a vehicle.
 *
 * What it does NOT do:
 *   - Choose which candidate to use (preference, VIP, waste-avoidance) — that is
 *     the allocation Strategy's job (Phase 4). The floor only filters by
 *     physical fit + availability; ordering/selection is policy.
 *
 * SOLID: SRP (a floor is a spot container + queries), DIP (works through the
 * Vehicle/ParkingSpot abstractions).
 *
 * Law of Demeter: callers ask the floor for counts/candidates rather than
 * reaching into its internal vector.
 */
class ParkingFloor {
public:
    explicit ParkingFloor(int floorNumber) noexcept : floorNumber_(floorNumber) {}

    ParkingFloor(const ParkingFloor&) = delete;
    ParkingFloor& operator=(const ParkingFloor&) = delete;

    int floorNumber() const noexcept { return floorNumber_; }

    /// Take ownership of a spot. @throws InvalidArgumentException if null.
    void addSpot(std::unique_ptr<ParkingSpot> spot);

    std::size_t totalSpots() const noexcept { return spots_.size(); }
    std::size_t occupiedCount() const noexcept;
    std::size_t availableCount() const noexcept;
    std::size_t availableCountByType(SpotType type) const noexcept;

    /// Free spots (any type) that can physically hold the vehicle. Non-owning.
    std::vector<ParkingSpot*> availableSpotsFor(const Vehicle& vehicle) const;

    /// All spots (non-owning view) — for display/stats iteration.
    std::vector<ParkingSpot*> allSpots() const;

    /// Locate a spot by id, or nullptr. Non-owning.
    ParkingSpot* findSpotById(const std::string& id) const noexcept;

private:
    int floorNumber_;
    std::vector<std::unique_ptr<ParkingSpot>> spots_;
};

}  // namespace pms
