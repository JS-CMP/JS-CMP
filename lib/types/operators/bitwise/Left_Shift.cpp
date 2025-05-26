#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

template <typename T>
JS::Any JS::Any::operator<<(T other) const {
    return JS::Any(JS::CONVERT::ToInt32(*this) << (JS::CONVERT::ToUint32(other) & 0x1F));
}
DECLARE_1FUNC(template JS::Any JS::Any::operator<<, const)

namespace JS {
template <typename T>
JS::Any operator<<(T value, const JS::Any& any) {
    return JS::Any(JS::CONVERT::ToInt32(value) << (JS::CONVERT::ToUint32(any) & 0x1F));
}

DECLARE_2FUNC(template JS::Any operator<<,)
} // namespace JS