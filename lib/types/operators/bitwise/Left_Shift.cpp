#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

template <typename T>
JS::Any JS::Any::operator<<(T other) const {
    return JS::Any(JS::CONVERT::ToInt32(*this) << (JS::CONVERT::ToUint32(other) & 0x1F));
}
template JS::Any JS::Any::operator<<(int) const;
template JS::Any JS::Any::operator<<(double) const;
template JS::Any JS::Any::operator<<(const char*) const;
template JS::Any JS::Any::operator<<(bool) const;
template JS::Any JS::Any::operator<<(JS::Null) const;
template JS::Any JS::Any::operator<<(JS::Undefined) const;
template JS::Any JS::Any::operator<<(JS::Any) const;
template JS::Any JS::Any::operator<<(const JS::Any&) const;

namespace JS {
template <typename T>
JS::Any operator<<(T value, const JS::Any& any) {
    return JS::Any(JS::CONVERT::ToInt32(value) << (JS::CONVERT::ToUint32(any) & 0x1F));
}

template JS::Any operator<<(int, const JS::Any&);
template JS::Any operator<<(double, const JS::Any&);
template JS::Any operator<<(const char*, const JS::Any&);
template JS::Any operator<<(bool, const JS::Any&);
template JS::Any operator<<(JS::Null, const JS::Any&);
template JS::Any operator<<(JS::Undefined, const JS::Any&);
} // namespace JS