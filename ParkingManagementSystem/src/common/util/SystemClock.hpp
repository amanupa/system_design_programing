#pragma once

#include "IClock.hpp"

namespace pms {

/**
 * @class SystemClock
 * @brief Production IClock backed by the real wall clock.
 *
 * Header-only: the implementation is a single trivial forwarding call, so there
 * is no benefit to a separate translation unit.
 */
class SystemClock : public IClock {
public:
    TimePoint now() const noexcept override { return Clock::now(); }
};

}  // namespace pms
