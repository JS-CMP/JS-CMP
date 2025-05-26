#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

template <typename T>
JS::Any JS::Any::operator-(T other) const {
    return JS::Any(JS::CONVERT::ToNumber(*this) - JS::CONVERT::ToNumber(other));
}

DECLARE_1FUNC(template JS::Any JS::Any::operator-, const)

namespace JS {
template <typename T>
JS::Any operator-(T value, JS::Any const& any) {
    return JS::Any(JS::CONVERT::ToNumber(value) - JS::CONVERT::ToNumber(any));
}

DECLARE_2FUNC(template JS::Any operator-,)
} // namespace JS
