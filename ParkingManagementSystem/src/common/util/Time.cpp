#include "Time.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>

namespace pms {

namespace {

std::tm toUtcTm(const TimePoint& tp) {
    const std::time_t t = Clock::to_time_t(tp);
    std::tm tmUtc{};
#if defined(_WIN32)
    gmtime_s(&tmUtc, &t);
#else
    gmtime_r(&t, &tmUtc);
#endif
    return tmUtc;
}

}  // namespace

std::string formatTimestamp(const TimePoint& tp) {
    const std::tm tmUtc = toUtcTm(tp);
    std::ostringstream out;
    out << std::put_time(&tmUtc, "%Y-%m-%d %H:%M:%S");
    return out.str();
}

std::string toDateString(const TimePoint& tp) {
    const std::tm tmUtc = toUtcTm(tp);
    std::ostringstream out;
    out << std::put_time(&tmUtc, "%Y-%m-%d");
    return out.str();
}

bool isWeekend(const TimePoint& tp) {
    const std::tm tmUtc = toUtcTm(tp);
    return tmUtc.tm_wday == 0 || tmUtc.tm_wday == 6;  // Sunday=0, Saturday=6
}

TimePoint makeTimePoint(int year, int month, int day, int hour, int minute,
                        int second) {
    std::tm tm{};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;
#if defined(_WIN32)
    const std::time_t t = _mkgmtime(&tm);
#else
    const std::time_t t = timegm(&tm);  // interpret fields as UTC
#endif
    return Clock::from_time_t(t);
}

}  // namespace pms
