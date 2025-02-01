#include "../includes/types/JsAny.hpp"
#include "../includes/utils/Convert.hpp"

JS::Any JS::Any::operator&&(const JS::Any &other) const {
    if (!JS::CONVERT::ToBoolean(*this))
        return *this;
    return other;
}

JS::Any JS::Any::operator&&(int value) const {
    if (!JS::CONVERT::ToBoolean(*this))
        return *this;
    return JS::Any(value);
}

JS::Any JS::Any::operator&&(double value) const {
    if (!JS::CONVERT::ToBoolean(*this))
        return *this;
    return JS::Any(value);
}

JS::Any JS::Any::operator&&(const char* value) const {
    if (!JS::CONVERT::ToBoolean(*this))
        return *this;
    return JS::Any(value);
}

JS::Any JS::Any::operator&&(bool value) const {
    if (!JS::CONVERT::ToBoolean(*this))
        return *this;
    return JS::Any(value);
}

JS::Any JS::Any::operator&&(JS::Null value) const {
    if (!JS::CONVERT::ToBoolean(*this))
        return *this;
    return JS::Any(value);
}

JS::Any JS::Any::operator&&(JS::Undefined value) const {
    if (!JS::CONVERT::ToBoolean(*this))
        return *this;
    return JS::Any(value);
}

namespace JS{

    Any operator%(int value, JS::Any const& any) {
        if (!JS::CONVERT::ToBoolean(value))
            return JS::Any(value);
        return JS::Any(any);
    }

    Any operator%(double value, JS::Any const& any) {
        if (!JS::CONVERT::ToBoolean(value))
            return JS::Any(value);
        return JS::Any(any);
    }

    Any operator%(const char* value, JS::Any const& any) {
        if (!JS::CONVERT::ToBoolean(value))
            return JS::Any(value);
        return JS::Any(any);
    }

    Any operator%(bool value, JS::Any const& any) {
        if (!JS::CONVERT::ToBoolean(value))
            return JS::Any(value);
        return JS::Any(any);
    }

    Any operator%(Null value, JS::Any const& any) {
        if (!JS::CONVERT::ToBoolean(value))
            return JS::Any(value);
        return JS::Any(any);
    }

    Any operator%(Undefined value, JS::Any const& any) {
        if (!JS::CONVERT::ToBoolean(value))
            return JS::Any(value);
        return JS::Any(any);
    }
}