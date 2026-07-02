#pragma once

#include <string>
#include <utility>

#include "domain/gate/Gate.hpp"
#include "domain/gate/IEntryGate.hpp"
#include "domain/gate/IExitGate.hpp"

namespace pms {

/**
 * A gate that may do BOTH. It implements both capability interfaces, so it can
 * stand in wherever an IEntryGate or an IExitGate is required (LSP). The single
 * gateId() override satisfies the same-signature method from both interfaces.
 */
class EntryExitGate final : public Gate, public IEntryGate, public IExitGate {
public:
    explicit EntryExitGate(std::string id)
        : Gate(std::move(id), GateType::EntryExit) {}

    const std::string& gateId() const noexcept override { return id(); }
    bool canServeEntry() const noexcept override { return canServe(); }
    bool canServeExit() const noexcept override { return canServe(); }
};

}  // namespace pms
