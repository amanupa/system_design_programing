#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "common/enums/SpotType.hpp"
#include "domain/spot/ParkingSpot.hpp"

namespace pms {

/**
 * @class SpotFactory
 * @brief Registry-based factory for ParkingSpot instances.
 *
 * Mirrors VehicleFactory: each SpotType maps to a creator that builds the
 * concrete spot given an id and floor number. Adding a new spot kind is a
 * single registration — no existing code changes (OCP).
 *
 * Ownership: returns unique_ptr<ParkingSpot>; the caller (typically a
 * ParkingFloor) takes ownership.
 */
class SpotFactory {
public:
    using Creator =
        std::function<std::unique_ptr<ParkingSpot>(const std::string& id, int floor)>;

    void registerType(SpotType type, Creator creator);
    bool isRegistered(SpotType type) const noexcept;

    /// @throws InvalidArgumentException if the type has no registered creator.
    std::unique_ptr<ParkingSpot> create(SpotType type, const std::string& id,
                                        int floor) const;

    /// Factory pre-loaded with all built-in spot types.
    static SpotFactory createDefault();

private:
    std::unordered_map<SpotType, Creator> creators_;
};

}  // namespace pms
