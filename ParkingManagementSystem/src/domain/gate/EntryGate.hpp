#pragma once

#include <string>
#include <utility>

#include "domain/gate/Gate.hpp"
#include "domain/gate/IEntryGate.hpp"

namespace pms {

/// A gate that may only ADMIT vehicles. Implements IEntryGate, not IExitGate —
/// so it is impossible to pass one to an exit workflow (ISP, compile-checked).
class EntryGate final : public Gate, public IEntryGate {
public:
    explicit EntryGate(std::string id)
        : Gate(std::move(id), GateType::Entry) {}

    const std::string& gateId() const noexcept override { return id(); }
    bool canServeEntry() const noexcept override { return canServe(); }
};

}  // namespace pms
