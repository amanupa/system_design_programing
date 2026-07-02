#include "manager/SpotManager.hpp"

#include <utility>

#include "common/exceptions/ParkingException.hpp"
#include "domain/floor/ParkingFloor.hpp"

namespace pms {

SpotManager::SpotManager(ISpotRepository& repository,
                         std::unique_ptr<ISpotAllocationStrategy> strategy,
                         ILogger& logger)
    : repository_(repository), strategy_(std::move(strategy)), logger_(logger) {
    if (!strategy_) {
        throw InvalidArgumentException("SpotManager: strategy must not be null");
    }
}

std::vector<ParkingSpot*> SpotManager::gatherCandidates(
    const Vehicle& vehicle) const {
    std::vector<ParkingSpot*> candidates;
    for (ParkingFloor* floor : repository_.floors()) {
        std::vector<ParkingSpot*> floorCandidates = floor->availableSpotsFor(vehicle);
        candidates.insert(candidates.end(), floorCandidates.begin(),
                          floorCandidates.end());
    }
    return candidates;
}

ParkingSpot* SpotManager::allocate(
    const std::shared_ptr<const Vehicle>& vehicle) {
    if (!vehicle) {
        throw InvalidArgumentException("SpotManager::allocate: vehicle is null");
    }
    const std::vector<ParkingSpot*> candidates = gatherCandidates(*vehicle);
    ParkingSpot* chosen = strategy_->selectSpot(*vehicle, candidates);
    if (chosen == nullptr) {
        throw SpotUnavailableException(
            "No suitable spot for vehicle " + vehicle->licensePlate() +
            " (" + std::to_string(candidates.size()) + " candidate(s) rejected by " +
            strategy_->name() + ")");
    }
    chosen->assign(vehicle);
    logger_.info("Allocated spot " + chosen->id() + " (" + toString(chosen->type()) +
                 ") to " + vehicle->licensePlate() + " via " + strategy_->name());
    publishEvent(ParkingEventType::VehicleParked, *chosen, vehicle->licensePlate());
    return chosen;
}

std::shared_ptr<const Vehicle> SpotManager::release(const std::string& spotId) {
    ParkingSpot* spot = repository_.findSpotById(spotId);
    if (spot == nullptr) {
        throw SpotUnavailableException("Unknown spot id: " + spotId);
    }
    std::shared_ptr<const Vehicle> previous = spot->release();
    const std::string plate = previous ? previous->licensePlate() : "empty";
    logger_.info("Released spot " + spotId + " (was " + plate + ")");
    publishEvent(ParkingEventType::VehicleExited, *spot, plate);
    return previous;
}

LotAvailability SpotManager::buildAvailability() const {
    LotAvailability availability;
    availability.totalSpots = repository_.totalSpots();
    availability.availableSpots = repository_.availableCount();
    for (ParkingFloor* floor : repository_.floors()) {
        availability.availableVip += floor->availableCountByType(SpotType::Vip);
        availability.availableElectric +=
            floor->availableCountByType(SpotType::Electric);
    }
    return availability;
}

void SpotManager::publishEvent(ParkingEventType type, const ParkingSpot& spot,
                               const std::string& licensePlate) {
    const ParkingEvent event{type,          spot.id(),   spot.type(),
                             spot.floorNumber(), licensePlate, buildAvailability()};
    publisher_.publish(event);
}

void SpotManager::setStrategy(std::unique_ptr<ISpotAllocationStrategy> strategy) {
    if (!strategy) {
        throw InvalidArgumentException("SpotManager::setStrategy: strategy is null");
    }
    logger_.info("Allocation strategy changed: " + strategy_->name() + " -> " +
                 strategy->name());
    strategy_ = std::move(strategy);
}

}  // namespace pms
