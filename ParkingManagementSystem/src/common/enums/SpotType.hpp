#pragma once

#include <string>

namespace pms {

/**
 * @enum SpotType
 * @brief The physical category of a parking spot.
 *
 * A spot's type constrains which vehicles may occupy it. The mapping
 * (vehicle -> compatible spots) is a *policy* and therefore lives in an
 * allocation strategy (Phase 4), not hard-coded here.
 */
enum class SpotType {
    Bike,
    Compact,      // small cars
    Car,
    Large,        // SUVs / vans
    Truck,
    Electric,     // has a charging point
    Vip,
    Handicapped
};

inline std::string toString(SpotType type) {
    switch (type) {
        case SpotType::Bike:        return "Bike";
        case SpotType::Compact:     return "Compact";
        case SpotType::Car:         return "Car";
        case SpotType::Large:       return "Large";
        case SpotType::Truck:       return "Truck";
        case SpotType::Electric:    return "Electric";
        case SpotType::Vip:         return "VIP";
        case SpotType::Handicapped: return "Handicapped";
    }
    return "Unknown";
}

}  // namespace pms
