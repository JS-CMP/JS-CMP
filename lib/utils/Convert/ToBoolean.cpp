#include "types/JsAny.hpp"

#include <cmath>

namespace JS::CONVERT {
const bool ToBoolean(int value) { return value != 0; }
bool ToBoolean(double value) { return !std::isnan(value) && value != 0; }
bool ToBoolean(bool value) { return value; }
bool ToBoolean(unsigned int value) { return value != 0; }
bool ToBoolean(const char* str) { return str != nullptr && *str != '\0'; }
bool ToBoolean(const char16_t* str) { return str != nullptr && *str != u'\0'; }
bool ToBoolean(const std::string& str) { return !str.empty(); }
bool ToBoolean(const std::u16string& str) { return !str.empty(); }
bool ToBoolean(const Rope& rope) { return ToBoolean(rope.toString()); }
bool ToBoolean(JS::Null /*unused*/) { return false; }
bool ToBoolean(JS::Undefined /*unused*/) { return false; }
bool ToBoolean(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.2
    switch (any.getValue().index()) {
        case NUMBER:
            return ToBoolean(std::get<double>(any.getValue()));
        case STRING:
            return ToBoolean(std::get<Rope>(any.getValue()));
        case BOOLEAN:
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