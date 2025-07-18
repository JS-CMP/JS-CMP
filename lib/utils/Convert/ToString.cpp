#include "internals/Object.hpp"
#include "internals/Operator.hpp"
#include "types/JsAny.hpp"
#include "utils/Convert.hpp"
#include "utils/Is.hpp"

#include <cmath>

namespace JS::CONVERT {
std::u16string ToString(int value) {
    return JS::CONVERT::ToUtf16((std::ostringstream() << value).str());
}
std::u16string ToString(double value) {
    return std::isnan(value)   ? u"NaN"
           : std::isinf(value) ? value < 0 ? u"-Infinity" : u"Infinity"
                               : JS::CONVERT::ToUtf16((std::ostringstream() << value).str());
}
std::u16string ToString(bool value) {
    return value ? u"true" : u"false";
}
std::u16string ToString(unsigned int value) {
    return JS::CONVERT::ToUtf16((std::ostringstream() << value).str());
}
std::u16string ToString(const char* value) {
    return JS::CONVERT::ToUtf16(value);
}
std::u16string ToString(const char16_t* value) {
    return {value};
}
std::u16string ToString(const std::string& value) {
    return JS::CONVERT::ToUtf16(value);
}
std::u16string ToString(const std::u16string& value) {
    return value;
}
std::u16string ToString(const Rope& rope) {
    return rope.toString();
}
std::u16string ToString(JS::Null /*unused*/) {
    return u"null";
}
std::u16string ToString(JS::Undefined /*unused*/) {
    return u"undefined";
}

std::u16string ToString(JS::Value value) {
    switch (value.index()) {
        case JS::NUMBER:
            return ToString(std::get<double>(value));
        case JS::STRING:
            return ToString(std::get<Rope>(value));
        case JS::BOOLEAN:
            return ToString(std::get<bool>(value));
        case JS::UNDEFINED:
            return ToString(JS::Undefined());
        case JS::NULL_TYPE:
            return ToString(JS::Null());
        default:
            return u"[Object]";
    }
}

std::u16string ToString(const JS::Operator& any) {
    // https://262.ecma-international.org/5.1/#sec-9.8
    switch (any.getValue().index()) {
        case NUMBER:
            return JS::CONVERT::ToString(std::get<double>(any.getValue()));
        case STRING:
            return ToString(std::get<Rope>(any.getValue()));
        case BOOLEAN:
            return ToString(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToString(JS::Undefined());
        case NULL_TYPE:
            return ToString(JS::Null());
        default:
            return ToString(ToPrimitive(any.get(), JS::STRING)); // Convert to primitive with STRING hint
    }
}
} // namespace JS::CONVERT
