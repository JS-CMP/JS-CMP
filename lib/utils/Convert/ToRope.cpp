#include "class/Rope/Rope.hpp"
#include "types/JsAny.hpp"
#include "utils/Convert.hpp"

#include <cmath>

namespace JS::CONVERT {
Rope ToRope(int value) {
    return Rope(JS::CONVERT::ToString(value));
}
Rope ToRope(double value) {
    return Rope(JS::CONVERT::ToString(value));
}
Rope ToRope(bool value) {
    return Rope(JS::CONVERT::ToString(value));
}
Rope ToRope(unsigned int value) {
    return Rope(JS::CONVERT::ToString(value));
}
Rope ToRope(const char* value) {
    return Rope(JS::CONVERT::ToUtf16(value));
}
Rope ToRope(const char16_t* value) {
    return Rope(value);
}
Rope ToRope(const std::string& value) {
    return Rope(JS::CONVERT::ToUtf16(value));
}
Rope ToRope(const Rope& value) {
    return value;
}
Rope ToRope(JS::Null /*unused*/) {
    return Rope(u"null");
}
Rope ToRope(JS::Undefined /*unused*/) {
    return Rope(u"undefined");
}
Rope ToRope(const JS::Any& any) {
    switch (any.getValue().index()) {
        case NUMBER:
            return JS::CONVERT::ToRope(std::get<double>(any.getValue()));
        case STRING:
            return ToRope(std::get<Rope>(any.getValue()));
        case BOOLEAN:
            return ToRope(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToRope(JS::Undefined());
        case NULL_TYPE:
            return ToRope(JS::Null());
        default:
            return ToRope(ToPrimitive(any, JS::STRING)); // Convert to primitive with STRING hint
    }
}
} // namespace JS::CONVERT
