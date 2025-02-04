#include "../includes/math/math.hpp"
#include <cmath>
#include <cstdlib>
#include <limits>
#include <random>

JS::Any Math::abs(const std::vector<JS::Any>& args) {
    if (args.empty())
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double value = JS::CONVERT::ToNumber(args[1]);
    if (std::isnan(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    if (!std::isfinite(value))
        return JS::Any(std::numeric_limits<double>::infinity());
    return JS::Any(std::fabs(value));
}

JS::Any Math::acos(const std::vector<JS::Any>& args) {
    if (args.empty())
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double value = JS::CONVERT::ToNumber(args[1]);
    if (std::isnan(value) || value > 1 || value < -1)
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::acos(value));
}

JS::Any Math::asin(const std::vector<JS::Any>& args) {
    if (args.empty())
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double value = JS::CONVERT::ToNumber(args[1]);
    if (std::isnan(value) || value > 1 || value < -1)
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::asin(value));
}

JS::Any Math::atan(const std::vector<JS::Any>& args) {
    if (args.empty())
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double value = JS::CONVERT::ToNumber(args[1]);
    if (std::isnan(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    if (value == 0.0 || value == -0.0)
        return JS::Any(value);
    return JS::Any(std::atan(value));
}

JS::Any Math::atan2(const std::vector<JS::Any>& args) {
    if (args.size() < 3)
        return JS::Any(std::numeric_limits<double>::quiet_NaN());

    double y = JS::CONVERT::ToNumber(args[1]);
    double x = JS::CONVERT::ToNumber(args[2]);

    if (std::isnan(y) || std::isnan(x) && y != 0)
        return JS::Any(std::numeric_limits<double>::quiet_NaN());

    if (y == 0.0) {
        bool yPositive = !std::signbit(y);
        if (x == 0.0) {
            if (!std::signbit(x))
                return JS::Any(yPositive ? 0.0 : -0.0);
            else
                return JS::Any(yPositive ? Math::PI : -Math::PI);
        }
        if (x > 0.0)
            return JS::Any(yPositive ? 0.0 : -0.0);
        else if (x < 0.0)
            return JS::Any(yPositive ? Math::PI : -Math::PI);
    }

    if (x == 0.0) {
        return JS::Any(y > 0.0 ? (Math::PI / 2.0) : (-Math::PI / 2.0));
    }

    if (std::isfinite(y) && std::isinf(x)) {
        if (x > 0)
            return JS::Any(y > 0.0 ? 0.0 : -0.0);
        else
            return JS::Any(y > 0.0 ? Math::PI : -Math::PI);
    }

    if (std::isinf(y) && std::isfinite(x)) {
        return JS::Any(y > 0.0 ? (Math::PI / 2.0) : (-Math::PI / 2.0));
    }

    if (std::isinf(y) && std::isinf(x)) {
        if (y > 0.0 && x > 0.0)
            return JS::Any(Math::PI / 4.0);
        if (y > 0.0 && x < 0.0)
            return JS::Any(3.0 * Math::PI / 4.0);
        if (y < 0.0 && x > 0.0)
            return JS::Any(-Math::PI / 4.0);
        if (y < 0.0 && x < 0.0)
            return JS::Any(-3.0 * Math::PI / 4.0);
    }

    double result = std::atan2(y, x);

    return JS::Any(result);
}


JS::Any Math::ceil(const std::vector<JS::Any>& args) {
    if (args.empty())
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double value = JS::CONVERT::ToNumber(args[1]);
    if (std::isnan(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::ceil(value));
}

JS::Any Math::cos(const std::vector<JS::Any>& args) {
    if (args.empty())
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double value = JS::CONVERT::ToNumber(args[1]);
    if (std::isnan(value) || !std::isfinite(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::cos(value));
}

JS::Any Math::exp(const std::vector<JS::Any>& args) {
    if (args.empty())
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double value = JS::CONVERT::ToNumber(args[1]);
    if (std::isnan(value))
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

JS::Any Math::floor(const std::vector<JS::Any>& args) {
    if (args.empty())
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double value = JS::CONVERT::ToNumber(args[1]);
    if (std::isnan(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::floor(value));
}

JS::Any Math::log(const std::vector<JS::Any>& args) {
    if (args.empty())
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double value = JS::CONVERT::ToNumber(args[1]);
    if (std::isnan(value) || value < 0)
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    if (value == 0.0)
        return JS::Any(-std::numeric_limits<double>::infinity());
    return JS::Any(std::log(value));
}

JS::Any Math::random(const std::vector<JS::Any>& args) {
    (void)args;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(0.0, 1.0);

    return JS::Any(dis(gen));
}

JS::Any Math::max(const std::vector<JS::Any>& args) {
    if (args.empty()) {
        return JS::Any(-std::numeric_limits<double>::infinity());
    }

    double maxValue = -std::numeric_limits<double>::infinity();
    for (size_t i = 1; i < args.size(); ++i) {
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

JS::Any Math::min(const std::vector<JS::Any>& args) {
    if (args.empty()) {
        return JS::Any(std::numeric_limits<double>::infinity());
    }

    double minValue = std::numeric_limits<double>::infinity();
    for (size_t i = 1; i < args.size(); ++i) {
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

JS::Any Math::pow(const std::vector<JS::Any>& args) {
    if (args.size() < 2)
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double base = JS::CONVERT::ToNumber(args[1]);
    double exponent = JS::CONVERT::ToNumber(args[2]);

    if (std::isnan(exponent))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    if (exponent == 0.0)
        return JS::Any(1.0);
    if (std::isnan(base) && exponent != 0.0)
        return JS::Any(std::numeric_limits<double>::quiet_NaN());

    double absBase = std::abs(base);

    if (absBase > 1 && exponent == std::numeric_limits<double>::infinity())
        return JS::Any(std::numeric_limits<double>::infinity());
    if (absBase > 1 && exponent == -std::numeric_limits<double>::infinity())
        return JS::Any(0.0);
    if (absBase == 1 && std::isinf(exponent))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    if (absBase < 1 && exponent == std::numeric_limits<double>::infinity())
        return JS::Any(0.0);
    if (absBase < 1 && exponent == -std::numeric_limits<double>::infinity())
        return JS::Any(std::numeric_limits<double>::infinity());

    if (base == std::numeric_limits<double>::infinity() && exponent > 0)
        return JS::Any(std::numeric_limits<double>::infinity());
    if (base == std::numeric_limits<double>::infinity() && exponent < 0)
        return JS::Any(0.0);

    if (base == -std::numeric_limits<double>::infinity() && exponent > 0) {
        return std::fmod(exponent, 2.0) == 1.0 ? JS::Any(-std::numeric_limits<double>::infinity())
                                               : JS::Any(std::numeric_limits<double>::infinity());
    }
    if (base == -std::numeric_limits<double>::infinity() && exponent < 0) {
        return std::fmod(exponent, 2.0) == 1.0 ? JS::Any(-0.0)
                                               : JS::Any(0.0);
    }

    if (base == 0.0 && exponent > 0)
        return JS::Any(0.0);
    if (base == 0.0 && exponent < 0)
        return JS::Any(std::numeric_limits<double>::infinity());

    if (base == -0.0 && exponent > 0) {
        return std::fmod(exponent, 2.0) == 1.0 ? JS::Any(-0.0)
                                               : JS::Any(0.0);
    }
    if (base == -0.0 && exponent < 0) {
        return std::fmod(exponent, 2.0) == 1.0 ? JS::Any(-std::numeric_limits<double>::infinity())
                                               : JS::Any(std::numeric_limits<double>::infinity());
    }

    if (base < 0 && std::isfinite(base) && std::isfinite(exponent) && std::fmod(exponent, 1.0) != 0.0) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }

    return JS::Any(std::pow(base, exponent));
}

JS::Any Math::round(const std::vector<JS::Any>& args) {
    if (args.empty())
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double value = JS::CONVERT::ToNumber(args[1]);
    if (std::isnan(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::round(value));
}

JS::Any Math::sin(const std::vector<JS::Any>& args) {
    if (args.empty())
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double value = JS::CONVERT::ToNumber(args[1]);
    if (std::isnan(value) || !std::isfinite(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::sin(value));
}

JS::Any Math::sqrt(const std::vector<JS::Any>& args) {
    if (args.empty())
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double value = JS::CONVERT::ToNumber(args[1]);
    if (std::isnan(value) || value < 0)
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::sqrt(value));
}

JS::Any Math::tan(const std::vector<JS::Any>& args) {
    if (args.empty())
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    double value = JS::CONVERT::ToNumber(args[1]);
    if (std::isnan(value) || !std::isfinite(value))
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    return JS::Any(std::tan(value));
}
