#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

DECLARE_1FUNC(JS::Any JS::Any::operator&&, const {
    return !JS::CONVERT::ToBoolean(*this) ? *this : JS::Any(value);
})

namespace JS {
template <typename T>
JS::Any operator&&(T value, JS::Any const& any) {
    return !JS::CONVERT::ToBoolean(value) ? JS::Any(value) : JS::Any(any);
}

DECLARE_2FUNC(template JS::Any operator&&,)
} // namespace JS