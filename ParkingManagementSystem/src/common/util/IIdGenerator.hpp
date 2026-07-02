#pragma once

#include <string>

namespace pms {

/**
 * @class IIdGenerator
 * @brief Abstraction that mints unique, human-friendly identifiers.
 *
 * Why an interface:
 *   IDs are another non-deterministic dependency. Tests want predictable IDs
 *   ("TKT-000001"); production wants collision-free ones. Injecting the
 *   generator keeps managers (Ticket/Gate/...) free of ID policy (SRP) and
 *   swappable (e.g. switch to UUIDs later without touching callers — OCP).
 */
class IIdGenerator {
public:
    virtual ~IIdGenerator() = default;

    /// Returns the next id for the given logical prefix, e.g.
    /// nextId("TKT") -> "TKT-000001", "TKT-000002", ...
    /// Sequences are independent per prefix.
    virtual std::string nextId(const std::string& prefix) = 0;
};

}  // namespace pms
