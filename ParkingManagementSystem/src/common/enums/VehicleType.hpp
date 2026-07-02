#pragma once

#include <string>

namespace pms {

/**
 * @enum VehicleType
 * @brief Shared vocabulary identifying the kind of a vehicle.
 *
 * Design note (OCP):
 *   This enum is *data*, not *behavior*. Vehicle behaviour lives in polymorphic
 *   classes (see Phase 2) wired through a factory/registry. Adding a new type
 *   therefore means: add one enumerator here + one new class + one factory
 *   registration, with NO edits to existing business logic. The enum acts as a
 *   compact, switch-friendly tag and a stable serialization key.
 *
 *   VIP and ElectricVehicle are listed as types per the project spec, but note
 *   they are conceptually *attributes* of a vehicle. The Decorator-based
 *   alternative is discussed when we reach pricing/display.
 */
enum class VehicleType {
    Bike,
    Car,
    Suv,
    Truck,
    ElectricVehicle,
    Vip
};

/// Human-readable name. Kept next to the enum for high cohesion (the enum and
/// its string projection change together).
inline std::string toString(VehicleType type) {
    switch (type) {
        case VehicleType::Bike:            return "Bike";
        case VehicleType::Car:             return "Car";
        case VehicleType::Suv:             return "SUV";
        case VehicleType::Truck:           return "Truck";
        case VehicleType::ElectricVehicle: return "ElectricVehicle";
        case VehicleType::Vip:             return "VIP";
    }
    return "Unknown";
}

}  // namespace pms
