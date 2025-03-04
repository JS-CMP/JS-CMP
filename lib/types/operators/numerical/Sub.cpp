#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

template <typename T>
JS::Any JS::Any::operator-(T other) const {
    return JS::Any(JS::CONVERT::ToNumber(*this) - JS::CONVERT::ToNumber(other));
}

template JS::Any JS::Any::operator-(int) const;
template JS::Any JS::Any::operator-(double) const;
template JS::Any JS::Any::operator-(const char*) const;
template JS::Any JS::Any::operator-(bool) const;
template JS::Any JS::Any::operator-(JS::Null) const;
template JS::Any JS::Any::operator-(JS::Any) const;
template JS::Any JS::Any::operator-(const JS::Any&) const;

JS::Any JS::Any::operator-(JS::Undefined /*unused*/) const { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }

namespace JS {
template <typename T>
JS::Any operator-(T value, JS::Any const& any) {
    return JS::Any(JS::CONVERT::ToNumber(value) - JS::CONVERT::ToNumber(any));
}

template JS::Any operator-(int, JS::Any const&);
template JS::Any operator-(double, JS::Any const&);
template JS::Any operator-(const char*, JS::Any const&);
template JS::Any operator-(bool, JS::Any const&);
template JS::Any operator-(JS::Null, JS::Any const&);

JS::Any operator-(JS::Undefined /*unused*/, JS::Any const& /*unused*/) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
} // namespace JS
