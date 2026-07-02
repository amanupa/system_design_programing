#pragma once

#include <memory>

#include "common/enums/GateStatus.hpp"

namespace pms {

/**
 * @class GateState
 * @brief State pattern — base for a gate's operational state.
 *
 * Each transition returns the NEXT state object (or throws on an illegal move).
 * The base implements every transition as "reject", so a concrete state only
 * overrides the moves that are legal from it — the legal-transition table lives
 * in the type system, not in `if (status == ...)` chains spread across the code.
 *
 * Why State over an enum + switch:
 *   Behaviour that varies by status (canServe, which transitions are allowed)
 *   is localised in one class per status. Adding a status (e.g. "Reserved")
 *   means adding a class, not editing every switch — Open/Closed Principle.
 *
 * States are immutable, behaviourless-data-free objects, so they are cheap to
 * create and trivially shareable; we simply swap the context's pointer.
 */
class GateState {
public:
    virtual ~GateState() = default;

    virtual GateStatus status() const noexcept = 0;
    virtual bool canServe() const noexcept { return false; }

    virtual std::unique_ptr<GateState> open() const { return reject("open"); }
    virtual std::unique_ptr<GateState> close() const { return reject("close"); }
    virtual std::unique_ptr<GateState> sendToMaintenance() const {
        return reject("maintenance");
    }
    virtual std::unique_ptr<GateState> enable() const { return reject("enable"); }
    virtual std::unique_ptr<GateState> disable() const { return reject("disable"); }

protected:
    /// Always throws GateUnavailableException; typed return keeps callers clean.
    std::unique_ptr<GateState> reject(const char* operation) const;
};

/// Serving traffic. The only state where canServe() is true.
class OpenState final : public GateState {
public:
    GateStatus status() const noexcept override { return GateStatus::Open; }
    bool canServe() const noexcept override { return true; }
    std::unique_ptr<GateState> open() const override;
    std::unique_ptr<GateState> close() const override;
    std::unique_ptr<GateState> sendToMaintenance() const override;
    std::unique_ptr<GateState> enable() const override;
    std::unique_ptr<GateState> disable() const override;
};

/// Barrier down but in service; can be reopened.
class ClosedState final : public GateState {
public:
    GateStatus status() const noexcept override { return GateStatus::Closed; }
    std::unique_ptr<GateState> open() const override;
    std::unique_ptr<GateState> close() const override;
    std::unique_ptr<GateState> sendToMaintenance() const override;
    std::unique_ptr<GateState> enable() const override;
    std::unique_ptr<GateState> disable() const override;
};

/// Under service; rejects open/close until re-enabled.
class MaintenanceState final : public GateState {
public:
    GateStatus status() const noexcept override { return GateStatus::Maintenance; }
    std::unique_ptr<GateState> sendToMaintenance() const override;
    std::unique_ptr<GateState> enable() const override;
    std::unique_ptr<GateState> disable() const override;
};

/// Administratively removed from rotation; only enable/disable apply.
class DisabledState final : public GateState {
public:
    GateStatus status() const noexcept override { return GateStatus::Disabled; }
    std::unique_ptr<GateState> enable() const override;
    std::unique_ptr<GateState> disable() const override;
};

}  // namespace pms
