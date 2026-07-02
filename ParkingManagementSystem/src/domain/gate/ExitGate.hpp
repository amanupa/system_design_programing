#pragma once

#include <string>
#include <utility>

#include "domain/gate/Gate.hpp"
#include "domain/gate/IExitGate.hpp"

namespace pms {

/// A gate that may only PROCESS EXITS. Implements IExitGate only.
class ExitGate final : public Gate, public IExitGate {
public:
    explicit ExitGate(std::string id)
        : Gate(std::move(id), GateType::Exit) {}

    const std::string& gateId() const noexcept override { return id(); }
    bool canServeExit() const noexcept override { return canServe(); }
};

}  // namespace pms
