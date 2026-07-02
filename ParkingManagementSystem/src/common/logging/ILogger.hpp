#pragma once

#include <string>

namespace pms {

/// Severity of a log record, ordered from most to least verbose.
enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warn,
    Error
};

inline std::string toString(LogLevel level) {
    switch (level) {
        case LogLevel::Trace: return "TRACE";
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Info:  return "INFO";
        case LogLevel::Warn:  return "WARN";
        case LogLevel::Error: return "ERROR";
    }
    return "?????";
}

/**
 * @class ILogger
 * @brief Abstraction over "where do diagnostics go".
 *
 * Purpose:
 *   Decouple every class from a concrete sink (console, file, syslog, a test
 *   spy). Classes depend on this contract; the sink is injected. This is the
 *   Dependency Inversion Principle in its simplest form and the reason we can
 *   assert on logs in unit tests.
 *
 * SOLID:
 *   - DIP: high-level code depends on ILogger, not std::cout.
 *   - ISP: the interface is one focused method; the convenience helpers below
 *          are non-virtual sugar built on top of it, so implementers override
 *          exactly one function.
 *
 * The convenience methods (info/warn/...) are intentionally NON-virtual: they
 * are pure forwarding helpers (Template-Method-lite) so every logger gets them
 * for free and they cannot be inconsistently overridden.
 */
class ILogger {
public:
    virtual ~ILogger() = default;

    /// The single primitive every concrete logger must implement.
    virtual void log(LogLevel level, const std::string& message) = 0;

    void trace(const std::string& message) { log(LogLevel::Trace, message); }
    void debug(const std::string& message) { log(LogLevel::Debug, message); }
    void info(const std::string& message)  { log(LogLevel::Info, message); }
    void warn(const std::string& message)  { log(LogLevel::Warn, message); }
    void error(const std::string& message) { log(LogLevel::Error, message); }
};

}  // namespace pms
