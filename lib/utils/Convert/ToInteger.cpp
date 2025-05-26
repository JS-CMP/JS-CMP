#include "types/JsAny.hpp"

#include <cmath>
#include <utils/Convert.hpp>

namespace JS::CONVERT {
int ToInteger(int value) { return value; }
int ToInteger(double value) { return std::isnan(value) ? 0 : value < 0 ? -std::floor(-value) : std::floor(value); }
int ToInteger(const std::string& str) { return ToInteger(ToNumber(str)); }
int ToInteger(const Rope& rope) { return ToInteger(rope.toString()); }
int ToInteger(bool value) { return value ? 1 : 0; }
int ToInteger(const JS::Null& /*unused*/) { return 0; }
int ToInteger(const JS::Undefined& /*unused*/) { return 0; }

int ToInteger(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.4
    switch (any.getValue().index()) {
        case NUMBER:
            return ToInteger(std::get<double>(any.getValue()));
        case STRING:
            return ToInteger(std::get<Rope>(any.getValue()));
        case BOOLEAN:
            return ToInteger(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToInteger(JS::Undefined());
        case NULL_TYPE:
            return ToInteger(JS::Null());
        default:
            return 0;
    }
}
} // namespace JS::CONVERT