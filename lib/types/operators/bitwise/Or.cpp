#include "../../../../includes/types/JsAny.hpp"
#include "../../../../includes/utils/Convert.hpp"

JS::Any JS::Any::operator|(const JS::Any& other) const {
    return JS::Any(JS::CONVERT::ToInt32(*this) | JS::CONVERT::ToInt32(other));
}

JS::Any JS::Any::operator|(int value) const {
    return JS::Any(JS::CONVERT::ToInt32(*this) | JS::CONVERT::ToInt32(value));
}

JS::Any JS::Any::operator|(double value) const {
    return JS::Any(JS::CONVERT::ToInt32(*this) | JS::CONVERT::ToInt32(value));
}

JS::Any JS::Any::operator|(const char* value) const {
    return JS::Any(JS::CONVERT::ToInt32(*this) | JS::CONVERT::ToInt32(value));
}

JS::Any JS::Any::operator|(bool value) const {
    return JS::Any(JS::CONVERT::ToInt32(*this) | JS::CONVERT::ToInt32(value));
}

JS::Any JS::Any::operator|(JS::Null value) const { return *this | 0; }

JS::Any JS::Any::operator|(JS::Undefined value) const { return *this | 0; }

namespace JS {
JS::Any operator|(int value, const JS::Any& any) {
    return JS::Any(JS::CONVERT::ToInt32(value) | JS::CONVERT::ToInt32(any));
}

JS::Any operator|(double value, const JS::Any& any) {
    return JS::Any(JS::CONVERT::ToInt32(value) | JS::CONVERT::ToInt32(any));
}

JS::Any operator|(const char* value, const JS::Any& any) {
    return JS::Any(JS::CONVERT::ToInt32(value) | JS::CONVERT::ToInt32(any));
}

JS::Any operator|(bool value, const JS::Any& any) {
    return JS::Any(JS::CONVERT::ToInt32(value) | JS::CONVERT::ToInt32(any));
}

JS::Any operator|(JS::Null value, const JS::Any& any) {
    return JS::Any(JS::CONVERT::ToInt32(value) | JS::CONVERT::ToInt32(any));
}

JS::Any operator|(JS::Undefined value, const JS::Any& any) {
    return JS::Any(JS::CONVERT::ToInt32(value) | JS::CONVERT::ToInt32(any));
}
} // namespace JS