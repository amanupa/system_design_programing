#include "domain/gate/GateState.hpp"

#include <string>

#include "common/exceptions/ParkingException.hpp"

namespace pms {

std::unique_ptr<GateState> GateState::reject(const char* operation) const {
    throw GateUnavailableException(std::string("Illegal gate transition '") +
                                   operation + "' from state " + toString(status()));
}

// --- OpenState ---------------------------------------------------------------
std::unique_ptr<GateState> OpenState::open() const {
    return std::make_unique<OpenState>();  // idempotent
}
std::unique_ptr<GateState> OpenState::close() const {
    return std::make_unique<ClosedState>();
}
std::unique_ptr<GateState> OpenState::sendToMaintenance() const {
    return std::make_unique<MaintenanceState>();
}
std::unique_ptr<GateState> OpenState::enable() const {
    return std::make_unique<OpenState>();  // already serving
}
std::unique_ptr<GateState> OpenState::disable() const {
    return std::make_unique<DisabledState>();
}

// --- ClosedState -------------------------------------------------------------
std::unique_ptr<GateState> ClosedState::open() const {
    return std::make_unique<OpenState>();
}
std::unique_ptr<GateState> ClosedState::close() const {
    return std::make_unique<ClosedState>();  // idempotent
}
std::unique_ptr<GateState> ClosedState::sendToMaintenance() const {
    return std::make_unique<MaintenanceState>();
}
std::unique_ptr<GateState> ClosedState::enable() const {
    return std::make_unique<OpenState>();
}
std::unique_ptr<GateState> ClosedState::disable() const {
    return std::make_unique<DisabledState>();
}

// --- MaintenanceState --------------------------------------------------------
std::unique_ptr<GateState> MaintenanceState::sendToMaintenance() const {
    return std::make_unique<MaintenanceState>();  // idempotent
}
std::unique_ptr<GateState> MaintenanceState::enable() const {
    return std::make_unique<OpenState>();  // back in service
}
std::unique_ptr<GateState> MaintenanceState::disable() const {
    return std::make_unique<DisabledState>();
}

// --- DisabledState -----------------------------------------------------------
std::unique_ptr<GateState> DisabledState::enable() const {
    return std::make_unique<OpenState>();  // re-activated
}
std::unique_ptr<GateState> DisabledState::disable() const {
    return std::make_unique<DisabledState>();  // idempotent
}

}  // namespace pms
