#pragma once

#include <cstddef>
#include <string>

#include "common/enums/SpotType.hpp"

namespace pms {

/// What happened to the lot.
enum class ParkingEventType {
    VehicleParked,
    VehicleExited
};

inline std::string toString(ParkingEventType type) {
    switch (type) {
        case ParkingEventType::VehicleParked: return "parked";
        case ParkingEventType::VehicleExited: return "exited";
    }
    return "?";
}

/**
 * @struct LotAvailability
 * @brief Aggregate availability snapshot carried by every event (push model).
 *
 * Boards render straight from this, so they never query the lot themselves —
 * which is what keeps them decoupled from SpotManager/the repository.
 */
struct LotAvailability {
    std::size_t totalSpots = 0;
    std::size_t availableSpots = 0;
    std::size_t availableVip = 0;
    std::size_t availableElectric = 0;
};

/**
 * @struct ParkingEvent
 * @brief Immutable notification of a lot change: the delta + a state snapshot.
 *
 * A plain value object (DTO). Domain-level so the publisher (SpotManager) can
 * create it without depending on the display layer at all.
 */
struct ParkingEvent {
    ParkingEventType type;
    std::string spotId;
    SpotType spotType;
    int floorNumber;
    std::string licensePlate;
    LotAvailability availability;
};

}  // namespace pms
