#include "types/objects/JsDate.hpp"

namespace JS {

JS::Any Date::parse(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::parse not implemented");
}

JS::Any Date::UTC(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::UTC not implemented");
}

JS::Any Date::now(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::now not implemented");
}

} // namespace JS


