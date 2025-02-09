#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

template <JS::AllowedType T>
JS::Any JS::Any::operator-(T other) const {
    return JS::Any(JS::CONVERT::ToNumber(*this) - JS::CONVERT::ToNumber(other));
}

namespace JS {
template <JS::AllowedType T>
JS::Any operator-(T value, JS::Any const& any) {
    return JS::Any(JS::CONVERT::ToNumber(value) - JS::CONVERT::ToNumber(any));
}
} // namespace JS
