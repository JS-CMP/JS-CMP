#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

template <JS::AllowedType T>
JS::Any JS::Any::operator||(T other) const {
    return JS::CONVERT::ToBoolean(*this) ? *this : JS::Any(other);
}

namespace JS {
template <JS::AllowedType T>
JS::Any operator||(T value, JS::Any const& any) {
    return JS::CONVERT::ToBoolean(value) ? JS::Any(value) : JS::Any(any);
}

} // namespace JS