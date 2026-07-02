#pragma once

#include <string>

namespace pms {

/**
 * @enum VehicleSize
 * @brief Intrinsic physical footprint of a vehicle.
 *
 * Separate from VehicleType on purpose: size is the property that actually
 * drives spot compatibility, and several distinct types share a size (a Car and
 * a VIP car are both Medium). Keeping size orthogonal lets the allocation
 * Strategy (Phase 4) reason about "does it fit" without switching on type.
 */
enum class VehicleSize {
    Small,   // bikes / scooters
    Medium,  // cars
    Large    // SUVs, trucks, vans
};

inline std::string toString(VehicleSize size) {
    switch (size) {
        case VehicleSize::Small:  return "Small";
        case VehicleSize::Medium: return "Medium";
        case VehicleSize::Large:  return "Large";
    }
    return "Unknown";
}

}  // namespace pms
