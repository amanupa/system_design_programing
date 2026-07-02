#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "common/enums/GateType.hpp"
#include "domain/gate/Gate.hpp"

namespace pms {

/**
 * @class GateFactory
 * @brief Registry-based factory for gates, keyed by GateType.
 *
 * Same shape as VehicleFactory/SpotFactory: a new gate kind is a registration,
 * not an edit to a switch (OCP). Returns unique_ptr<Gate> (the caller, usually
 * GateManager, takes ownership).
 */
class GateFactory {
public:
    using Creator = std::function<std::unique_ptr<Gate>(const std::string& id)>;

    void registerType(GateType type, Creator creator);
    bool isRegistered(GateType type) const noexcept;

    /// @throws InvalidArgumentException if the type has no registered creator.
    std::unique_ptr<Gate> create(GateType type, const std::string& id) const;

    static GateFactory createDefault();

private:
    std::unordered_map<GateType, Creator> creators_;
};

}  // namespace pms
