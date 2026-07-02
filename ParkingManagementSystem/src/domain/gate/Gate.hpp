#pragma once

#include <memory>
#include <string>

#include "common/enums/GateStatus.hpp"
#include "common/enums/GateType.hpp"
#include "domain/gate/GateState.hpp"

namespace pms {

/**
 * @class Gate
 * @brief Abstract base + State-pattern CONTEXT for a physical access gate.
 *
 * Responsibilities:
 *   - Identity (id) and category (type).
 *   - Hold the current GateState and delegate transitions/queries to it.
 *
 * It deliberately knows nothing about spots, tickets, or payments — admitting a
 * vehicle is an application workflow, not a gate's job. The gate only models the
 * barrier's identity and operational state (SRP).
 *
 * Construction is protected: a bare Gate has no entry/exit capability, so you
 * must instantiate a concrete EntryGate/ExitGate/EntryExitGate.
 *
 * SOLID: SRP, OCP (new gate kinds/states without editing this), DIP (managers
 * depend on Gate, not concretes).
 */
class Gate {
public:
    virtual ~Gate() = default;

    Gate(const Gate&) = delete;
    Gate& operator=(const Gate&) = delete;

    const std::string& id() const noexcept { return id_; }
    GateType type() const noexcept { return type_; }
    GateStatus status() const noexcept { return state_->status(); }
    bool canServe() const noexcept { return state_->canServe(); }

    // State transitions — each delegates to the current state object, which
    // either returns the next state or throws on an illegal transition.
    void open() { state_ = state_->open(); }
    void close() { state_ = state_->close(); }
    void sendToMaintenance() { state_ = state_->sendToMaintenance(); }
    void enable() { state_ = state_->enable(); }
    void disable() { state_ = state_->disable(); }

protected:
    Gate(std::string id, GateType type);

private:
    std::string id_;
    GateType type_;
    std::unique_ptr<GateState> state_;
};

}  // namespace pms
