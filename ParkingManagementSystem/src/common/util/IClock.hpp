#pragma once

#include "Time.hpp"

namespace pms {

/**
 * @class IClock
 * @brief Abstraction over "what time is it now".
 *
 * Why it exists:
 *   Time is an external dependency. Code that reads the wall clock directly is
 *   untestable (you can't make "now" be a fixed value) and non-deterministic.
 *   Injecting an IClock lets fee/ticket logic be tested with a controllable
 *   clock (return a fixed entry time, advance it, assert the fee).
 *
 * SOLID: DIP — domain logic depends on this contract, not on
 * std::chrono::system_clock::now().
 */
class IClock {
public:
    virtual ~IClock() = default;
    virtual TimePoint now() const noexcept = 0;
};

}  // namespace pms
