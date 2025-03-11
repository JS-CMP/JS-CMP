#include "types/objects/JsFunction.hpp"
#include "types/objects/JsNumber.hpp"

#include <iomanip>
#include <utils/Compare.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Number::toString(const JS::Any& thisArg, const JS::Any& args) {
    if ((!JS::COMPARE::Type(thisArg, JS::OBJECT) ||
         std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->class_name != "Number") &&
        !JS::COMPARE::Type(thisArg, JS::NUMBER)) {
        throw std::runtime_error("TypeError: Number.prototype.toString is not generic"); // TODO: TypeError
    }
    double num = JS::CONVERT::ToNumber(thisArg);
    if (JS::COMPARE::Type(args["0"], JS::UNDEFINED)) {
        return JS::Any(JS::CONVERT::ToString(num));
    }
    int radix = JS::CONVERT::ToInteger(args["0"]);
    if (radix < 2 || radix > 36) {
        throw std::runtime_error("RangeError: radix must be an integer between 2 and 36"); // TODO: RangeError
    }
    // TODO: implement radix conversion like in 9.8.1 JS::CONVERT::ToString(num, radix);
}

JS::Any JS::Number::toLocaleString(const JS::Any& thisArg, const JS::Any& args) { return toString(thisArg, args); }

JS::Any JS::Number::valueOf(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(thisArg, JS::OBJECT) ||
        std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->class_name != "Number") {
        throw std::runtime_error("TypeError: Number.prototype.valueOf is not generic");
    }
    return thisArg;
}

JS::Any JS::Number::toFixed(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(thisArg, JS::OBJECT) ||
        std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->class_name != "Number") {
        throw std::runtime_error("TypeError: Number.prototype.toFixed is not generic"); // TODO: TypeError
    }
    int fractionDigits = 0;
    if (!JS::COMPARE::Type(args["0"], JS::UNDEFINED)) {
        fractionDigits = JS::CONVERT::ToInteger(args["0"]);
    }
    if (fractionDigits < 0 || fractionDigits > 20) {
        throw std::runtime_error("RangeError: fractionDigits must be an integer between 0 and 20"); // TODO: RangeError
    }
    double num = JS::CONVERT::ToNumber(thisArg);
    if (std::isnan(num)) {
        return JS::Any("NaN");
    }
    std::string s;
    if (num < 0) {
        s = "-";
        num = -num;
    }
    std::string m;
    if (num >= 10e21) {
        m = JS::CONVERT::ToString(num);
    } else {
        // Let n be an integer for which the exact mathematical value of n ÷ 10f – x is as close to zero as possible.
        long double factor = std::pow(10.0L, fractionDigits); // 10^f
        long double temp = num * factor;                      // n = x * 10^f
        long double n_ld = std::floor(temp + 0.5L);           // round to nearest integer
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(0) << n_ld;
        m = oss.str();
        if (fractionDigits != 0) {
            int k = m.length();
            if (k <= fractionDigits) {
                std::string z(fractionDigits + 1 - k, '0');
                m = z + m;
                k = fractionDigits + 1;
            }
            std::string a = m.substr(0, k - fractionDigits);
            std::string b = m.substr(k - fractionDigits);
            m = a + "." + b;
        }
    }
    return JS::Any(s + m);
}

JS::Any JS::Number::toExponential(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(thisArg, JS::OBJECT) ||
        std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue())->class_name != "Number") {
        throw std::runtime_error("TypeError: Number.prototype.toExponential is not generic"); // TODO: TypeError
    }
    double num = JS::CONVERT::ToNumber(thisArg);
    if (std::isnan(num)) {
        return JS::Any("NaN");
    }
    int fractionDigits = 0;
    if (!JS::COMPARE::Type(args["0"], JS::UNDEFINED)) {
        fractionDigits = JS::CONVERT::ToInteger(args["0"]);
    }
    if (fractionDigits < 0 || fractionDigits > 20) {
        throw std::runtime_error("RangeError: fractionDigits must be an integer between 0 and 20"); // TODO: RangeError
    }
    std::string s = "";
    if (num < 0) {
        s = "-";
        num = -num;
    }
    if (num == std::numeric_limits<double>::infinity()) {
        return JS::Any(s + "Infinity");
    }
    std::string m;
    int e;
    if (num == 0.0) {
        fractionDigits = 0;
        m = "0";
    } else {
        double n;
        if (!JS::COMPARE::Type(args["0"], JS::UNDEFINED)) {
            // TODO: implement the following
        } else {
            // TODO: implement the following
        }
        m = JS::CONVERT::ToString(n);
    }
    if (fractionDigits != 0) {
        m = m[0] + "." + m.substr(1);
    }
    std::string c;
    std::string d;
    if (e == 0) {
        c = "+";
        d = "0";
    } else {
        if (e > 0) {
            c = "+";
        } else {
            c = "-";
            e = -e;
        }
        d = JS::CONVERT::ToString(e);
    }
    m = m + "e" + c + d;
    return JS::Any(s + m);
}

JS::Any JS::Number::toPrecision(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}
