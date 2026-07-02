#include "repository/InMemorySpotRepository.hpp"

#include "common/exceptions/ParkingException.hpp"

namespace pms {

void InMemorySpotRepository::addFloor(std::unique_ptr<ParkingFloor> floor) {
    if (!floor) {
        throw InvalidArgumentException("InMemorySpotRepository: floor is null");
    }
    floors_.push_back(std::move(floor));
}

std::vector<ParkingFloor*> InMemorySpotRepository::floors() const {
    std::vector<ParkingFloor*> view;
    view.reserve(floors_.size());
    for (const std::unique_ptr<ParkingFloor>& floor : floors_) {
        view.push_back(floor.get());
    }
    return view;
}

ParkingSpot* InMemorySpotRepository::findSpotById(const std::string& id) const {
    for (const std::unique_ptr<ParkingFloor>& floor : floors_) {
        if (ParkingSpot* spot = floor->findSpotById(id)) {
            return spot;
        }
    }
    return nullptr;
}

std::size_t InMemorySpotRepository::totalSpots() const {
    std::size_t total = 0;
    for (const std::unique_ptr<ParkingFloor>& floor : floors_) {
        total += floor->totalSpots();
    }
    return total;
}

std::size_t InMemorySpotRepository::availableCount() const {
    std::size_t total = 0;
    for (const std::unique_ptr<ParkingFloor>& floor : floors_) {
        total += floor->availableCount();
    }
    return total;
}

std::size_t InMemorySpotRepository::occupiedCount() const {
    std::size_t total = 0;
    for (const std::unique_ptr<ParkingFloor>& floor : floors_) {
        total += floor->occupiedCount();
    }
    return total;
}

}  // namespace pms
