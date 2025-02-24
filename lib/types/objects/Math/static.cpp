#include "internals/PropertyProxy.hpp"
#include "types/objects/JsMath.hpp"

#include <cmath>
#include <cstdlib>
#include <limits>
#include <random>

namespace JS {
JS::Any Math::abs(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::fabs(JS::CONVERT::ToNumber(args["0"])));
}

JS::Any Math::acos(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::acos(JS::CONVERT::ToNumber(args["0"])));
}

JS::Any Math::asin(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::asin(JS::CONVERT::ToNumber(args["0"])));
}

JS::Any Math::atan(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::atan(JS::CONVERT::ToNumber(args["0"])));
}

JS::Any Math::atan2(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::atan2(JS::CONVERT::ToNumber(args["0"]), JS::CONVERT::ToNumber(args["1"])));
}

JS::Any Math::ceil(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::ceil(JS::CONVERT::ToNumber(args["0"])));
}

JS::Any Math::cos(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::cos(JS::CONVERT::ToNumber(args["0"])));
}

JS::Any Math::exp(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::exp(JS::CONVERT::ToNumber(args["0"])));
}

JS::Any Math::floor(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::floor(JS::CONVERT::ToNumber(args["0"])));
}

JS::Any Math::log(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::log(JS::CONVERT::ToNumber(args["0"])));
}

JS::Any Math::random(const JS::Any& thisArg, const JS::Any& args) {
    (void)args;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(0.0, 1.0);

    return JS::Any(dis(gen));
}

JS::Any Math::max(const JS::Any& thisArg, const JS::Any& args) {
    double maxValue = -std::numeric_limits<double>::infinity();
    for (uint32_t i = 0; i < JS::CONVERT::ToUint32(args["length"]); ++i) {
        double num = JS::CONVERT::ToNumber(args[i]);
        if (std::isnan(num)) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
        if (num > maxValue || (num == 0.0 && std::signbit(maxValue))) {
            maxValue = num;
        }
    }
    return JS::Any(maxValue);
}

JS::Any Math::min(const JS::Any& thisArg, const JS::Any& args) {
    double minValue = std::numeric_limits<double>::infinity();
    for (uint32_t i = 0; i < JS::CONVERT::ToUint32(args["length"]); ++i) {
        double num = JS::CONVERT::ToNumber(args[i]);
        if (std::isnan(num)) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
        if (num < minValue || (num == 0.0 && !std::signbit(minValue))) {
            minValue = num;
        }
    }
    return JS::Any(minValue);
}

JS::Any Math::pow(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::pow(JS::CONVERT::ToNumber(args["0"]), JS::CONVERT::ToNumber(args["1"])));
}

JS::Any Math::round(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::round(JS::CONVERT::ToNumber(args["0"])));
}

JS::Any Math::sin(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::sin(JS::CONVERT::ToNumber(args["0"])));
}

JS::Any Math::sqrt(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::sqrt(JS::CONVERT::ToNumber(args["0"])));
}

JS::Any Math::tan(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::tan(JS::CONVERT::ToNumber(args["0"])));
}
} // namespace JS
