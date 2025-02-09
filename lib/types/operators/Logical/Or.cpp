#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

template <typename T>
JS::Any JS::Any::operator||(T other) const {
    return JS::CONVERT::ToBoolean(*this) ? *this : JS::Any(other);
}

template JS::Any JS::Any::operator||(const JS::Any&) const;
template JS::Any JS::Any::operator||(int) const;
template JS::Any JS::Any::operator||(double) const;
template JS::Any JS::Any::operator||(const char*) const;
template JS::Any JS::Any::operator||(bool) const;
template JS::Any JS::Any::operator||(JS::Null) const;
template JS::Any JS::Any::operator||(JS::Undefined) const;

namespace JS {
template <typename T>
JS::Any operator||(T value, JS::Any const& any) {
    return JS::CONVERT::ToBoolean(value) ? JS::Any(value) : JS::Any(any);
}

template JS::Any operator||(int, JS::Any const&);
template JS::Any operator||(double, JS::Any const&);
template JS::Any operator||(const char*, JS::Any const&);
template JS::Any operator||(bool, JS::Any const&);
template JS::Any operator||(JS::Null, JS::Any const&);
template JS::Any operator||(JS::Undefined, JS::Any const&);
} // namespace JS