#pragma once

#include <string>

namespace pms {

/**
 * @class IExitGate
 * @brief Capability interface: a gate through which vehicles may EXIT.
 *
 * The mirror of IEntryGate. Exit/payment workflows accept an `IExitGate&`, so
 * only exit-capable gates can process an exit — enforced at compile time (ISP).
 */
class IExitGate {
public:
    virtual ~IExitGate() = default;

    virtual const std::string& gateId() const noexcept = 0;

    /// True when the gate is operational AND may process exits right now.
    virtual bool canServeExit() const noexcept = 0;
};

}  // namespace pms
