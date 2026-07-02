#pragma once

#include <stdexcept>
#include <string>

namespace pms {

/**
 * @class ParkingException
 * @brief Root of the project's exception hierarchy.
 *
 * Purpose:
 *   Give the whole system a single, catchable base so callers can choose their
 *   granularity (`catch (const ParkingException&)` for "any domain error" or a
 *   specific subtype for targeted handling).
 *
 * Why exceptions over magic return values:
 *   - Error paths cannot be silently ignored (a forgotten `-1` check can).
 *   - Constructors can fail meaningfully (no two-phase init).
 *   - Business logic stays readable: the happy path isn't drowned in checks.
 *
 * Derives from std::runtime_error so it composes with the standard library and
 * carries a `what()` message for free.
 *
 * SOLID: SRP (each subtype names exactly one failure mode), LSP (any subtype is
 * usable wherever ParkingException is expected).
 */
class ParkingException : public std::runtime_error {
public:
    explicit ParkingException(const std::string& message)
        : std::runtime_error(message) {}
};

/// No spot of a compatible type is currently free.
class SpotUnavailableException : public ParkingException {
public:
    explicit SpotUnavailableException(const std::string& message)
        : ParkingException(message) {}
};

/// The requested gate cannot service the request (closed/maintenance/wrong type).
class GateUnavailableException : public ParkingException {
public:
    explicit GateUnavailableException(const std::string& message)
        : ParkingException(message) {}
};

/// A ticket lookup failed.
class TicketNotFoundException : public ParkingException {
public:
    explicit TicketNotFoundException(const std::string& message)
        : ParkingException(message) {}
};

/// A vehicle lookup failed.
class VehicleNotFoundException : public ParkingException {
public:
    explicit VehicleNotFoundException(const std::string& message)
        : ParkingException(message) {}
};

/// Payment was attempted but not completed.
class PaymentFailedException : public ParkingException {
public:
    explicit PaymentFailedException(const std::string& message)
        : ParkingException(message) {}
};

/// Configuration is missing or internally inconsistent.
class InvalidConfigurationException : public ParkingException {
public:
    explicit InvalidConfigurationException(const std::string& message)
        : ParkingException(message) {}
};

/// A required argument violated a precondition.
class InvalidArgumentException : public ParkingException {
public:
    explicit InvalidArgumentException(const std::string& message)
        : ParkingException(message) {}
};

}  // namespace pms
