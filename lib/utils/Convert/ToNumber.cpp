#include "types/JsAny.hpp"

#include <cmath>

namespace JS::CONVERT {
double ToNumber(int value) { return value; }
double ToNumber(double value) { return value; }
double ToNumber(const std::string& str) {
    if (str.empty()) {
        throw std::invalid_argument("La chaîne est vide");
    }

    if (str.size() > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        int result;
        std::stringstream ss;
        ss << std::hex << str.substr(2);
        ss >> result;
        if (ss.fail()) {
            return 0;
        }
        return result;
    } else if (str.size() > 2 && str[0] == '0' && (str[1] == 'b' || str[1] == 'B')) {
        int result = 0;
        for (size_t i = 2; i < str.size(); ++i) {
            if (str[i] != '0' && str[i] != '1') {
                return 0;
            }
            result = (result << 1) | (str[i] - '0');
        }
        return result;
    } else {
        try {
            if (str.find('.') != std::string::npos) {
                double result = std::stod(str);
                return static_cast<int>(result);
            } else {
                long long result = std::stoll(str);
                return static_cast<int>(result);
            }
        } catch (...) { return 0; }
    }
}

double ToNumber(const Rope& rope) { return ToNumber(rope.toString()); }
double ToNumber(bool value) { return static_cast<double>(value); }
double ToNumber(const JS::Null& /*unused*/) { return 0; }
double ToNumber(const JS::Undefined& /*unused*/) { return std::numeric_limits<double>::quiet_NaN(); }
double ToNumber(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.3
    switch (any.getValue().index()) {
        case NUMBER:
            return std::get<double>(any.getValue());
        case STRING:
            return ToNumber(std::get<Rope>(any.getValue()));
        case BOOLEAN:
            return ToNumber(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToNumber(JS::Undefined());
        case NULL_TYPE:
            return ToNumber(JS::Null());
        default:
            return std::numeric_limits<double>::quiet_NaN();
    }
}
} // namespace JS::CONVERT