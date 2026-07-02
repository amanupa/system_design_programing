#pragma once

#include <string>

namespace pms {

/**
 * @class IEntryGate
 * @brief Capability interface: a gate through which vehicles may ENTER.
 *
 * Pattern/principle: Interface Segregation.
 *   Only entry-capable gates implement this. Application code that issues a
 *   parking ticket will accept an `IEntryGate&`, so the compiler — not a runtime
 *   `if (gate.type == Entry)` — guarantees an exit-only gate can never be used
 *   to admit a vehicle. The capability is expressed in the type, not checked.
 */
class IEntryGate {
public:
    virtual ~IEntryGate() = default;

    virtual const std::string& gateId() const noexcept = 0;

    /// True when the gate is operational AND may admit entries right now.
    virtual bool canServeEntry() const noexcept = 0;
};

}  // namespace pms
