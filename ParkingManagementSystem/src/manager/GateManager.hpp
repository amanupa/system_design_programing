#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "common/logging/ILogger.hpp"
#include "domain/gate/Gate.hpp"
#include "domain/gate/IEntryGate.hpp"
#include "domain/gate/IExitGate.hpp"

namespace pms {

/**
 * @class GateManager
 * @brief Owns and administers the lot's gates.
 *
 * Single responsibility: the gate registry + lifecycle operations
 * (add/remove/enable/disable/maintenance/open/close, lookup, availability).
 * It does not park or charge anyone — it just manages the gates themselves.
 *
 * Dynamic add/remove of gates and per-gate state changes are first-class, as the
 * spec requires. All state changes go through the gate's State machine, so the
 * manager never duplicates transition rules (DRY).
 *
 * Collaborator: ILogger& (injected). Owns gates via unique_ptr (RAII).
 *
 * SOLID: SRP, OCP (new gate kinds need no manager change), DIP.
 */
class GateManager {
public:
    explicit GateManager(ILogger& logger) noexcept;

    GateManager(const GateManager&) = delete;
    GateManager& operator=(const GateManager&) = delete;

    /// @throws InvalidArgumentException if null or the id already exists.
    void addGate(std::unique_ptr<Gate> gate);

    /// Remove a gate by id; returns true if one was removed.
    bool removeGate(const std::string& id);

    /// Locate a gate by id, or nullptr. Non-owning.
    Gate* findGate(const std::string& id) const noexcept;

    // Lifecycle operations — each resolves the gate then drives its State machine.
    // @throws GateUnavailableException if the gate is unknown or the transition
    //         is illegal from its current state.
    void openGate(const std::string& id);
    void closeGate(const std::string& id);
    void enableGate(const std::string& id);
    void disableGate(const std::string& id);
    void sendToMaintenance(const std::string& id);

    std::vector<Gate*> listGates() const;
    std::vector<Gate*> listAvailableGates() const;  // canServe() == true
    std::size_t count() const noexcept { return gates_.size(); }

    /// Resolve a gate to its capability interface. The dynamic_cast is the single
    /// runtime check (gate ids are dynamic); callers then use the typed interface,
    /// so the ISP guarantee holds at compile time from there on.
    /// @throws GateUnavailableException if unknown or lacking the capability.
    IEntryGate& requireEntryGate(const std::string& id) const;
    IExitGate& requireExitGate(const std::string& id) const;

private:
    Gate& requireGate(const std::string& id) const;

    ILogger& logger_;
    std::vector<std::unique_ptr<Gate>> gates_;
};

}  // namespace pms
