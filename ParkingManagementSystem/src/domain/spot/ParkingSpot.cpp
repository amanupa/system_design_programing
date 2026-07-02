#include "domain/spot/ParkingSpot.hpp"

#include <utility>

#include "common/exceptions/ParkingException.hpp"

namespace pms {

ParkingSpot::ParkingSpot(std::string id, int floorNumber, SpotType type,
                         VehicleSize capacity, bool hasCharging)
    : id_(std::move(id)),
      floorNumber_(floorNumber),
      type_(type),
      capacity_(capacity),
      hasCharging_(hasCharging) {
    if (id_.empty()) {
        throw InvalidArgumentException("ParkingSpot: id must not be empty");
    }
}

bool ParkingSpot::canFit(const Vehicle& vehicle) const noexcept {
    // VehicleSize and the spot's capacity are ordered (Small < Medium < Large):
    // the vehicle must not exceed the spot's footprint...
    const bool sizeOk =
        static_cast<int>(vehicle.size()) <= static_cast<int>(capacity_);
    // ...and a charging-dependent vehicle needs a charging-capable spot.
    const bool chargingOk = !vehicle.requiresCharging() || hasCharging_;
    return sizeOk && chargingOk;
}

void ParkingSpot::assign(std::shared_ptr<const Vehicle> vehicle) {
    if (!vehicle) {
        throw InvalidArgumentException("ParkingSpot::assign: vehicle is null");
    }
    if (occupied_) {
        throw SpotUnavailableException("Spot " + id_ + " is already occupied");
    }
    if (!canFit(*vehicle)) {
        throw SpotUnavailableException(
            "Vehicle " + vehicle->licensePlate() + " does not fit spot " + id_);
    }
    vehicle_ = std::move(vehicle);
    occupied_ = true;
}

std::shared_ptr<const Vehicle> ParkingSpot::release() {
    if (!occupied_) {
        throw SpotUnavailableException("Spot " + id_ + " is already free");
    }
    occupied_ = false;
    std::shared_ptr<const Vehicle> previous = std::move(vehicle_);
    vehicle_.reset();
    return previous;
}

}  // namespace pms
