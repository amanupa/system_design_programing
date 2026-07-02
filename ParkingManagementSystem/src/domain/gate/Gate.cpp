#include "domain/gate/Gate.hpp"

#include <utility>

#include "common/exceptions/ParkingException.hpp"

namespace pms {

Gate::Gate(std::string id, GateType type)
    : id_(std::move(id)),
      type_(type),
      state_(std::make_unique<OpenState>()) {  // a new gate starts ready to serve
    if (id_.empty()) {
        throw InvalidArgumentException("Gate: id must not be empty");
    }
}

}  // namespace pms
