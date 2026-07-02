#pragma once

#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>

#include "IIdGenerator.hpp"

namespace pms {

/**
 * @class SequentialIdGenerator
 * @brief Thread-safe IIdGenerator producing zero-padded per-prefix sequences.
 *
 * Responsibilities:
 *   - Maintain an independent monotonic counter per prefix.
 *   - Format ids as "<prefix>-<6-digit-zero-padded-number>".
 *
 * Thread-safety: a single mutex guards the prefix->counter map. The critical
 * section is tiny (one map lookup + increment), so contention is negligible at
 * realistic gate throughput; if it ever mattered we'd shard per prefix.
 *
 * Collaborators: IIdGenerator (implements).
 */
class SequentialIdGenerator : public IIdGenerator {
public:
    std::string nextId(const std::string& prefix) override;

private:
    std::mutex mutex_;
    std::unordered_map<std::string, std::uint64_t> counters_;
};

}  // namespace pms
