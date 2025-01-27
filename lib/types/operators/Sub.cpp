#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Any::operator-(const JS::Any& other) const {
    // TODO: check float precision
    // change with infinite precision the stod
    return JS::Any(JS::CONVERT::ToNumber(*this) - JS::CONVERT::ToNumber(other));
}

JS::Any JS::Any::operator-(int value) const {
    return JS::Any(JS::CONVERT::ToNumber(*this) - JS::CONVERT::ToNumber(value));
}

JS::Any JS::Any::operator-(double value) const {
    return JS::Any(JS::CONVERT::ToNumber(*this) - JS::CONVERT::ToNumber(value));
}

JS::Any JS::Any::operator-(const char* value) const {
    return JS::Any(JS::CONVERT::ToNumber(*this) - JS::CONVERT::ToNumber(value));
}

JS::Any JS::Any::operator-(bool value) const {
    return JS::Any(JS::CONVERT::ToNumber(*this) - JS::CONVERT::ToNumber(value));
}

JS::Any JS::Any::operator-(JS::Null value) const {
    return JS::Any(JS::CONVERT::ToNumber(*this) - JS::CONVERT::ToNumber(value));
}

JS::Any JS::Any::operator-(JS::Undefined) const { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }

namespace JS {
JS::Any operator-(int value, JS::Any const& any) {
    return JS::Any(JS::CONVERT::ToNumber(value) - JS::CONVERT::ToNumber(any));
}

JS::Any operator-(double value, JS::Any const& any) {
    return JS::Any(JS::CONVERT::ToNumber(value) - JS::CONVERT::ToNumber(any));
}

JS::Any operator-(bool value, JS::Any const& any) {
    return JS::Any(JS::CONVERT::ToNumber(value) - JS::CONVERT::ToNumber(any));
}

JS::Any operator-(const char* value, JS::Any const& any) {
    return JS::Any(JS::CONVERT::ToNumber(value) - JS::CONVERT::ToNumber(any));
}

JS::Any operator-(JS::Null value, JS::Any const& any) {
    return JS::Any(JS::CONVERT::ToNumber(value) - JS::CONVERT::ToNumber(any));
}

JS::Any operator-(JS::Undefined, JS::Any const&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
} // namespace JS
