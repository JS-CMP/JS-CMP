#include "types/objects/JsDate.hpp"
#include "utils/Convert.hpp"

namespace JS {

JS::Any Date::parse(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::parse not implemented");
}

JS::Any Date::UTC(const JS::Any& thisArg, const JS::Any& args) {

    double y = CONVERT::ToNumber(args[0]);
    double m = CONVERT::ToNumber(args[1]);
    
}

JS::Any Date::now(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::now not implemented");
}

} // namespace JS
