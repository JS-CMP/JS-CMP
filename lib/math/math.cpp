#include "../includes/math/math.hpp"

JS::Any Math::abs(const JS::Any &x) {
    double value = JS::CONVERT::ToNumber(x);
    if (std::isnan(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    if (!std::isfinite(value))
        return JS::Any(std::numeric_limits<double>::infinity());
    return JS::Any(std::fabs(value));
}

JS::Any Math::acos(const JS::Any &x) {
    double value = JS::CONVERT::ToNumber(x);
    if (std::isnan(value) || value > 1 || value < -1)
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::acos(value));
}

JS::Any Math::asin(const JS::Any &x) {
    double value = JS::CONVERT::ToNumber(x);
    if (std::isnan(value) || value > 1 || value < -1)
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::asin(value));
}

JS::Any Math::atan(const JS::Any &x) {
    double value = JS::CONVERT::ToNumber(x);
    if (std::isnan(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    if (value == 0.0 || value == -0.0)
        return JS::Any(value);
    return JS::Any(std::atan(value));
}

JS::Any Math::atan2(const JS::Any &y, const JS::Any &x) {
//TODO atan2 function
//    double yValue = JS::CONVERT::ToNumber(y);
//    double xValue = JS::CONVERT::ToNumber(x);
//    if (std::isnan(yValue) || std::isnan(xValue))
//        return JS::Any(std::numeric_limits<double>::quiet_NaN());
//    if (yValue == 0.0 && xValue == 0.0)
//        return JS::Any(std::copysign(0.0, yValue));
//    return JS::Any(std::atan2(yValue, xValue));
}

JS::Any Math::ceil(const JS::Any &x) {
    double value = JS::CONVERT::ToNumber(x);
    if (std::isnan(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::ceil(value));
}

JS::Any Math::cos(const JS::Any &x) {
    double value = JS::CONVERT::ToNumber(x);
    if (std::isnan(value) || !std::isfinite(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::cos(value));
}

JS::Any Math::exp(const JS::Any &x) {
    double value = JS::CONVERT::ToNumber(x);
    if (isnan(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    if (value == 0.0)
        return JS::Any(1.0);
    if (value == std::numeric_limits<double>::infinity())
        return JS::Any(std::numeric_limits<double>::infinity());
    if (value == -std::numeric_limits<double>::infinity())
        return JS::Any(0.0);

    double result = std::exp(value);
    return result < std::numeric_limits<double>::min() ? JS::Any(0.0) : JS::Any(result);
}


JS::Any Math::floor(const JS::Any &x) {
    double value = JS::CONVERT::ToNumber(x);
    if (std::isnan(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::floor(value));
}

JS::Any Math::log(const JS::Any &x) {
    double value = JS::CONVERT::ToNumber(x);
    if (std::isnan(value) || value < 0)
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    if (value == 0.0)
        return JS::Any(-std::numeric_limits<double>::infinity());
    return JS::Any(std::log(value));
}

JS::Any Math::random() {
    return JS::Any(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX));
}

JS::Any Math::round(const JS::Any &x) {
    double value = JS::CONVERT::ToNumber(x);
    if (std::isnan(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::round(value));
}

JS::Any Math::sin(const JS::Any &x) {
    double value = JS::CONVERT::ToNumber(x);
    if (std::isnan(value) || !std::isfinite(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::sin(value));
}

JS::Any Math::sqrt(const JS::Any &x) {
    double value = JS::CONVERT::ToNumber(x);
    if (std::isnan(value) || value < 0)
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::sqrt(value));
}

JS::Any Math::tan(const JS::Any &x) {
    double value = JS::CONVERT::ToNumber(x);
    if (std::isnan(value) || !std::isfinite(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::tan(value));
}
