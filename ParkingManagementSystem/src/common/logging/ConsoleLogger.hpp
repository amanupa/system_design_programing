#pragma once

#include <mutex>

#include "ILogger.hpp"

namespace pms {

/**
 * @class ConsoleLogger
 * @brief Thread-safe ILogger that writes to std::clog.
 *
 * Responsibilities:
 *   - Format records as "[<level>] <message>".
 *   - Drop records below a configurable minimum level.
 *   - Serialize writes so interleaved threads don't corrupt a line.
 *
 * Collaborators: ILogger (implements).
 *
 * Why a separate .cpp: the body pulls in <iostream>; keeping that out of the
 * header avoids leaking heavy includes into every translation unit that only
 * needs the ILogger contract.
 */
class ConsoleLogger : public ILogger {
public:
    explicit ConsoleLogger(LogLevel minLevel = LogLevel::Info) noexcept;

    void log(LogLevel level, const std::string& message) override;

    void setMinLevel(LogLevel level) noexcept;
    LogLevel minLevel() const noexcept;

private:
    LogLevel minLevel_;
    std::mutex mutex_;
};

}  // namespace pms
