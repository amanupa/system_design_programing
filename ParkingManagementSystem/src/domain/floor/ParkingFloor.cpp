#include "domain/floor/ParkingFloor.hpp"

#include <algorithm>

#include "common/exceptions/ParkingException.hpp"

namespace pms {

void ParkingFloor::addSpot(std::unique_ptr<ParkingSpot> spot) {
    if (!spot) {
        throw InvalidArgumentException("ParkingFloor::addSpot: spot is null");
    }
    spots_.push_back(std::move(spot));
}

std::size_t ParkingFloor::occupiedCount() const noexcept {
    return static_cast<std::size_t>(std::count_if(
        spots_.begin(), spots_.end(),
        [](const std::unique_ptr<ParkingSpot>& s) { return s->isOccupied(); }));
}

std::size_t ParkingFloor::availableCount() const noexcept {
    return spots_.size() - occupiedCount();
}

std::size_t ParkingFloor::availableCountByType(SpotType type) const noexcept {
    return static_cast<std::size_t>(std::count_if(
        spots_.begin(), spots_.end(),
        [type](const std::unique_ptr<ParkingSpot>& s) {
            return !s->isOccupied() && s->type() == type;
        }));
}

std::vector<ParkingSpot*> ParkingFloor::availableSpotsFor(
    const Vehicle& vehicle) const {
    std::vector<ParkingSpot*> candidates;
    for (const std::unique_ptr<ParkingSpot>& spot : spots_) {
        if (!spot->isOccupied() && spot->canFit(vehicle)) {
            candidates.push_back(spot.get());
        }
    }
    return candidates;
}

std::vector<ParkingSpot*> ParkingFloor::allSpots() const {
    std::vector<ParkingSpot*> view;
    view.reserve(spots_.size());
    for (const std::unique_ptr<ParkingSpot>& spot : spots_) {
        view.push_back(spot.get());
    }
    return view;
}

ParkingSpot* ParkingFloor::findSpotById(const std::string& id) const noexcept {
    for (const std::unique_ptr<ParkingSpot>& spot : spots_) {
        if (spot->id() == id) {
            return spot.get();
        }
    }
    return nullptr;
}

}  // namespace pms
