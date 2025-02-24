#include "types/JsAny.hpp"

#include <cmath>

namespace JS::CONVERT {
std::string ToString(int value) { return (std::ostringstream() << value).str(); }
std::string ToString(double value) {
    return std::isnan(value)   ? "NaN"
           : std::isinf(value) ? value < 0 ? "-Infinity" : "Infinity"
                               : (std::ostringstream() << value).str();
}
std::string ToString(const Rope& rope) { return rope.toString(); }
std::string ToString(bool value) { return value ? "true" : "false"; }
std::string ToString(const JS::Null&) { return "null"; }
std::string ToString(const JS::Undefined&) { return "undefined"; }
std::string ToString(const JS::Any& any) {
    // https://262.ecma-international.org/5.1/#sec-9.8
    switch (any.getValue().index()) {
        case NUMBER:
            return JS::CONVERT::ToString(std::get<double>(any.getValue()));
        case STRING:
            return ToString(std::get<Rope>(any.getValue()));
        case BOOL:
            return ToString(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToString(JS::Undefined());
        case NULL_TYPE:
            return ToString(JS::Null());
        default:
            return "[Object]";
    }
}
} // namespace JS::CONVERT
