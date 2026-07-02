#include "manager/GateManager.hpp"

#include <algorithm>
#include <utility>

#include "common/exceptions/ParkingException.hpp"

namespace pms {

GateManager::GateManager(ILogger& logger) noexcept : logger_(logger) {}

void GateManager::addGate(std::unique_ptr<Gate> gate) {
    if (!gate) {
        throw InvalidArgumentException("GateManager::addGate: gate is null");
    }
    if (findGate(gate->id()) != nullptr) {
        throw InvalidArgumentException("GateManager: duplicate gate id " + gate->id());
    }
    logger_.info("Added gate " + gate->id() + " (" + toString(gate->type()) +
                 ", " + toString(gate->status()) + ")");
    gates_.push_back(std::move(gate));
}

bool GateManager::removeGate(const std::string& id) {
    const auto it = std::find_if(
        gates_.begin(), gates_.end(),
        [&id](const std::unique_ptr<Gate>& g) { return g->id() == id; });
    if (it == gates_.end()) {
        return false;
    }
    gates_.erase(it);
    logger_.info("Removed gate " + id);
    return true;
}

Gate* GateManager::findGate(const std::string& id) const noexcept {
    for (const std::unique_ptr<Gate>& gate : gates_) {
        if (gate->id() == id) {
            return gate.get();
        }
    }
    return nullptr;
}

Gate& GateManager::requireGate(const std::string& id) const {
    Gate* gate = findGate(id);
    if (gate == nullptr) {
        throw GateUnavailableException("Unknown gate id: " + id);
    }
    return *gate;
}

void GateManager::openGate(const std::string& id) {
    Gate& gate = requireGate(id);
    gate.open();
    logger_.info("Gate " + id + " opened -> " + toString(gate.status()));
}

void GateManager::closeGate(const std::string& id) {
    Gate& gate = requireGate(id);
    gate.close();
    logger_.info("Gate " + id + " closed -> " + toString(gate.status()));
}

void GateManager::enableGate(const std::string& id) {
    Gate& gate = requireGate(id);
    gate.enable();
    logger_.info("Gate " + id + " enabled -> " + toString(gate.status()));
}

void GateManager::disableGate(const std::string& id) {
    Gate& gate = requireGate(id);
    gate.disable();
    logger_.info("Gate " + id + " disabled -> " + toString(gate.status()));
}

void GateManager::sendToMaintenance(const std::string& id) {
    Gate& gate = requireGate(id);
    gate.sendToMaintenance();
    logger_.info("Gate " + id + " -> " + toString(gate.status()));
}

std::vector<Gate*> GateManager::listGates() const {
    std::vector<Gate*> view;
    view.reserve(gates_.size());
    for (const std::unique_ptr<Gate>& gate : gates_) {
        view.push_back(gate.get());
    }
    return view;
}

std::vector<Gate*> GateManager::listAvailableGates() const {
    std::vector<Gate*> view;
    for (const std::unique_ptr<Gate>& gate : gates_) {
        if (gate->canServe()) {
            view.push_back(gate.get());
        }
    }
    return view;
}

IEntryGate& GateManager::requireEntryGate(const std::string& id) const {
    Gate& gate = requireGate(id);
    auto* entry = dynamic_cast<IEntryGate*>(&gate);
    if (entry == nullptr) {
        throw GateUnavailableException("Gate " + id + " is not entry-capable");
    }
    return *entry;
}

IExitGate& GateManager::requireExitGate(const std::string& id) const {
    Gate& gate = requireGate(id);
    auto* exit = dynamic_cast<IExitGate*>(&gate);
    if (exit == nullptr) {
        throw GateUnavailableException("Gate " + id + " is not exit-capable");
    }
    return *exit;
}

}  // namespace pms
