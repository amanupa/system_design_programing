#include "SequentialIdGenerator.hpp"

#include <iomanip>
#include <sstream>

namespace pms {

std::string SequentialIdGenerator::nextId(const std::string& prefix) {
    std::uint64_t value;
    {
        std::lock_guard<std::mutex> guard(mutex_);
        value = ++counters_[prefix];  // value-initialised to 0 on first access
    }
    std::ostringstream out;
    out << prefix << '-' << std::setw(6) << std::setfill('0') << value;
    return out.str();
}

}  // namespace pms
