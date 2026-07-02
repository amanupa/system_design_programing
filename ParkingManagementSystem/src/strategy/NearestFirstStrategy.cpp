#include "strategy/NearestFirstStrategy.hpp"

#include <tuple>

namespace pms {

ParkingSpot* NearestFirstStrategy::selectSpot(
    const Vehicle& /*vehicle*/,
    const std::vector<ParkingSpot*>& candidates) const {
    ParkingSpot* best = nullptr;
    std::tuple<int, std::string> bestKey;
    for (ParkingSpot* spot : candidates) {
        std::tuple<int, std::string> key{spot->floorNumber(), spot->id()};
        if (best == nullptr || key < bestKey) {
            best = spot;
            bestKey = std::move(key);
        }
    }
    return best;
}

}  // namespace pms
