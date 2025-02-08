#include <cmath>
#include "types/JsAny.hpp"

namespace JS::CONVERT {
bool ToBoolean(int value) { return value != 0; }
bool ToBoolean(double value) { return !std::isnan(value) && value != 0; }
bool ToBoolean(const std::string& str) { return !str.empty(); }
bool ToBoolean(const Rope& rope) { return ToBoolean(rope.toString()); }
bool ToBoolean(bool value) { return value; }
bool ToBoolean(const JS::Null&) { return false; }
bool ToBoolean(const JS::Undefined&) { return false; }
bool ToBoolean(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.2
    switch (any.getValue().index()) {
        case NUMBER:
            return ToBoolean(std::get<double>(any.getValue()));
        case STRING:
            return ToBoolean(std::get<Rope>(any.getValue()));
        case BOOL:
            return ToBoolean(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToBoolean(JS::Undefined());
        case NULL_TYPE:
            return ToBoolean(JS::Null());
        default:
            return true;
    }
}
} // namespace JS::CONVERT