#include "ConsoleLogger.hpp"

#include <iostream>

namespace pms {

ConsoleLogger::ConsoleLogger(LogLevel minLevel) noexcept
    : minLevel_(minLevel) {}

void ConsoleLogger::log(LogLevel level, const std::string& message) {
    // Filter first (cheap) so suppressed records never take the lock.
    if (static_cast<int>(level) < static_cast<int>(minLevel_)) {
        return;
    }
    std::lock_guard<std::mutex> guard(mutex_);
    std::clog << '[' << toString(level) << "] " << message << '\n';
}

void ConsoleLogger::setMinLevel(LogLevel level) noexcept {
    std::lock_guard<std::mutex> guard(mutex_);
    minLevel_ = level;
}

LogLevel ConsoleLogger::minLevel() const noexcept {
    return minLevel_;
}

}  // namespace pms
