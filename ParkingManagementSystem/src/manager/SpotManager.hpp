#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "common/logging/ILogger.hpp"
#include "domain/event/ParkingEvent.hpp"
#include "domain/spot/ParkingSpot.hpp"
#include "domain/vehicle/Vehicle.hpp"
#include "observer/IParkingSubject.hpp"
#include "observer/ParkingEventPublisher.hpp"
#include "repository/ISpotRepository.hpp"
#include "strategy/ISpotAllocationStrategy.hpp"

namespace pms {

/**
 * @class SpotManager
 * @brief Orchestrates spot allocation: gather candidates -> apply policy -> assign.
 *
 * Collaborators (all injected — Dependency Injection):
 *   - ISpotRepository&          : the inventory source (non-owning; lives in the
 *                                 composition root and outlives the manager).
 *   - ISpotAllocationStrategy   : the selection policy (OWNED via unique_ptr so
 *                                 it can be hot-swapped with setStrategy()).
 *   - ILogger&                  : diagnostics sink.
 *
 * Why a manager (vs. doing this in ParkingLot/ParkingFloor):
 *   It isolates the single responsibility "turn a vehicle into an occupied spot"
 *   and keeps that logic in one testable place. ParkingLot will merely delegate.
 *
 * SOLID: SRP, DIP (depends on three abstractions), OCP (swap strategy/repo).
 */
class SpotManager {
public:
    SpotManager(ISpotRepository& repository,
                std::unique_ptr<ISpotAllocationStrategy> strategy,
                ILogger& logger);

    SpotManager(const SpotManager&) = delete;
    SpotManager& operator=(const SpotManager&) = delete;

    /**
     * Find and occupy a spot for the vehicle.
     * @returns the chosen spot (non-owning); the spot now co-owns the vehicle.
     * @throws SpotUnavailableException if no suitable spot exists.
     */
    ParkingSpot* allocate(const std::shared_ptr<const Vehicle>& vehicle);

    /**
     * Free a spot by id and return its previous occupant.
     * @throws SpotUnavailableException if the spot is unknown or already free.
     */
    std::shared_ptr<const Vehicle> release(const std::string& spotId);

    /// Replace the allocation policy at runtime (Strategy swap).
    void setStrategy(std::unique_ptr<ISpotAllocationStrategy> strategy);
    std::string strategyName() const { return strategy_->name(); }

    /// The event source observers (e.g. display boards) subscribe to. Exposed as
    /// the interface so callers can't reach the publisher's publish() side.
    IParkingSubject& events() noexcept { return publisher_; }

    std::size_t totalSpots() const { return repository_.totalSpots(); }
    std::size_t availableCount() const { return repository_.availableCount(); }
    std::size_t occupiedCount() const { return repository_.occupiedCount(); }

private:
    std::vector<ParkingSpot*> gatherCandidates(const Vehicle& vehicle) const;
    LotAvailability buildAvailability() const;
    void publishEvent(ParkingEventType type, const ParkingSpot& spot,
                      const std::string& licensePlate);

    ISpotRepository& repository_;
    std::unique_ptr<ISpotAllocationStrategy> strategy_;
    ILogger& logger_;
    ParkingEventPublisher publisher_;
};

}  // namespace pms
