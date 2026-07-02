#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "common/enums/VehicleType.hpp"
#include "domain/vehicle/Vehicle.hpp"

namespace pms {

/**
 * @class VehicleFactory
 * @brief Creates Vehicle instances from a (type, plate) request.
 *
 * Pattern: registry-based Factory.
 *   Each VehicleType maps to a "creator" callable. `create()` looks up the
 *   creator and invokes it. Registering a new type is a one-liner; no existing
 *   code is edited.
 *
 * Why a registry instead of a switch-statement factory (or GoF Factory Method):
 *   - A `switch (type)` factory must be EDITED for every new type — that is the
 *     exact OCP violation we want to avoid.
 *   - Classic Factory Method puts creation in a virtual override per product
 *     subclass; that shines when the *caller* is itself polymorphic (e.g. each
 *     Gate creates its own Ticket — we use it there). Here the caller just has a
 *     type tag, so a data-driven registry is the cleaner, more extensible fit.
 *
 * Ownership: returns unique_ptr<Vehicle> — the caller owns the result (RAII).
 *
 * SOLID: SRP (only constructs vehicles), OCP (extend by registration), DIP
 * (returns the Vehicle abstraction, never a concrete type).
 */
class VehicleFactory {
public:
    /// A creator turns a license plate into an owned Vehicle.
    using Creator = std::function<std::unique_ptr<Vehicle>(const std::string& plate)>;

    /// Register (or replace) the creator for a vehicle type.
    void registerType(VehicleType type, Creator creator);

    /// True if a creator is registered for the given type.
    bool isRegistered(VehicleType type) const noexcept;

    /// Create a vehicle of the requested type.
    /// @throws InvalidArgumentException if the type has no registered creator.
    std::unique_ptr<Vehicle> create(VehicleType type, const std::string& plate) const;

    /// Build a factory pre-loaded with all built-in vehicle types.
    static VehicleFactory createDefault();

private:
    std::unordered_map<VehicleType, Creator> creators_;
};

}  // namespace pms
