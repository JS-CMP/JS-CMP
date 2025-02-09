#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

template <JS::AllowedType T>
JS::Any JS::Any::operator&(T other) const {
    return JS::Any(JS::CONVERT::ToInt32(*this) & JS::CONVERT::ToInt32(other));
}
namespace JS {
template <JS::AllowedType T>
JS::Any operator&(T value, const JS::Any& any) {
    return JS::Any(JS::CONVERT::ToInt32(value) & JS::CONVERT::ToInt32(any));
}
} // namespace JS
