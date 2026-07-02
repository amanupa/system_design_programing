#pragma once

#include <chrono>

#include "common/util/Time.hpp"
#include "domain/vehicle/Vehicle.hpp"

namespace pms {

/**
 * @struct FeeContext
 * @brief Immutable inputs a fee strategy needs to price one parking session.
 *
 * Deliberately a small DTO rather than the Ticket entity: pricing depends only
 * on when the vehicle was parked and what it is — not on ticket identity or
 * storage. This decoupling lets us quote a fee before any ticket exists and lets
 * tests build a context by hand (deterministic, no clock needed).
 */
struct FeeContext {
    TimePoint entryTime;
    TimePoint exitTime;
    const Vehicle& vehicle;

    Duration duration() const noexcept {
        return std::chrono::duration_cast<Duration>(exitTime - entryTime);
    }
};

}  // namespace pms
