#pragma once

#include <chrono>
#include <string>

namespace pms {

/// Project-wide time vocabulary. Centralised so a future switch of clock source
/// (e.g. to a monotonic or TAI clock) touches exactly one place (DRY).
using Clock     = std::chrono::system_clock;
using TimePoint = std::chrono::system_clock::time_point;
using Duration  = std::chrono::seconds;

/// Format a time point as "YYYY-MM-DD HH:MM:SS" in UTC.
/// Free function (not a method) — it depends only on the public type, so per the
/// Law of Demeter / minimal-interface principle it lives outside any class.
std::string formatTimestamp(const TimePoint& tp);

/// "YYYY-MM-DD" (UTC) — the calendar-day key used by holiday pricing.
std::string toDateString(const TimePoint& tp);

/// True if the UTC date of tp falls on Saturday or Sunday.
bool isWeekend(const TimePoint& tp);

/// Construct a UTC time point from calendar fields — used by tests/demos to pin
/// deterministic absolute times (e.g. "a Saturday at 10:00").
TimePoint makeTimePoint(int year, int month, int day, int hour = 0,
                        int minute = 0, int second = 0);

}  // namespace pms
