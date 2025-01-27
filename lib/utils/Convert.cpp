#include "utils/Convert.hpp"

#include "utils/Compare.hpp"
#include <cmath>
#include <sstream>
#include <string>
#define APPLY_MODULO_UINT32(value) ((uint32_t)((value) % 0x100000000))

namespace JS::CONVERT {

JS::Any ToPrimitive(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.1
    if (JS::COMPARE::Type(any, JS::OBJECT)) {
        return JS::Any(std::get<std::shared_ptr<JS::Object>>(any.getValue())); // TODO
    }
    return any;
}

bool ToBoolean(int value) { return value != 0; }
bool ToBoolean(double value) { return !std::isnan(value) && value != 0; }
bool ToBoolean(const std::string& str) { return !str.empty(); }
bool ToBoolean(const Rope& rope) { return ToBoolean(rope.toString()); }
bool ToBoolean(bool value) { return value; }
bool ToBoolean(const JS::Null&) { return false; }
bool ToBoolean(const JS::Undefined&) { return false; }
bool ToBoolean(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.2
    switch (any.getValue().index()) {
        case NUMBER:
            return ToBoolean(std::get<double>(any.getValue()));
        case STRING:
            return ToBoolean(std::get<Rope>(any.getValue()));
        case BOOL:
            return ToBoolean(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToBoolean(JS::Undefined());
        case NULL_TYPE:
            return ToBoolean(JS::Null());
        default:
            return true;
    }
}

double ToNumber(int value) { return static_cast<double>(value); }
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
    }

    else if (str.size() > 2 && str[0] == '0' && (str[1] == 'b' || str[1] == 'B')) {
        int result = 0;
        for (size_t i = 2; i < str.size(); ++i) {
            if (str[i] != '0' && str[i] != '1') {
                return 0;
            }
            result = (result << 1) | (str[i] - '0');
        }
        return result;
    }

    else {
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
double ToNumber(const JS::Null&) { return 0; }
double ToNumber(const JS::Undefined&) { return std::numeric_limits<double>::quiet_NaN(); }
double ToNumber(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.3
    switch (any.getValue().index()) {
        case NUMBER:
            return std::get<double>(any.getValue());
        case STRING:
            return ToNumber(std::get<Rope>(any.getValue()));
        case BOOL:
            return ToNumber(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToNumber(JS::Undefined());
        case NULL_TYPE:
            return ToNumber(JS::Null());
        default:
            return std::numeric_limits<double>::quiet_NaN();
    }
}

int ToInteger(int value) { return value; }
int ToInteger(double value) { return std::isnan(value) ? 0 : value < 0 ? -std::floor(-value) : std::floor(value); }
int ToInteger(const std::string& str) { return ToInteger(ToNumber(str)); }
int ToInteger(const Rope& rope) { return ToInteger(rope.toString()); }
int ToInteger(bool value) { return value ? 1 : 0; }
int ToInteger(const JS::Null&) { return 0; }
int ToInteger(const JS::Undefined&) { return 0; }
int ToInteger(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.4
    switch (any.getValue().index()) {
        case NUMBER:
            return ToInteger(std::get<double>(any.getValue()));
        case STRING:
            return ToInteger(std::get<Rope>(any.getValue()));
        case BOOL:
            return ToInteger(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToInteger(JS::Undefined());
        case NULL_TYPE:
            return ToInteger(JS::Null());
        default:
            return 0;
    }
}

uint32_t ToUint32(int value) { return APPLY_MODULO_UINT32(value < 0 ? -static_cast<int64_t>(value) : value); }
uint32_t ToUint32(double value) {
    try {
        if (std::isnan(value) || value == 0 || !std::isfinite(value)) {
            return 0;
        }
        double posInt = std::signbit(value) ? -std::floor(std::abs(value)) : std::floor(std::abs(value));
        return APPLY_MODULO_UINT32(static_cast<int64_t>(posInt));
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; }
    return 0;
}
uint32_t ToUint32(const std::string& str) { return ToUint32(ToNumber(str)); }
uint32_t ToUint32(const Rope& rope) { return ToUint32(rope.toString()); }
uint32_t ToUint32(bool value) { return value ? 1 : 0; }
uint32_t ToUint32(const JS::Null&) { return 0; }
uint32_t ToUint32(const JS::Undefined&) { return 0; }
uint32_t ToUint32(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.6
    switch (any.getValue().index()) {
        case NUMBER:
            return ToUint32(std::get<double>(any.getValue()));
        case STRING:
            return ToUint32(std::get<Rope>(any.getValue()));
        case BOOL:
            return ToUint32(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToUint32(JS::Undefined());
        case NULL_TYPE:
            return ToUint32(JS::Null());
        default:
            return 0;
    }
}

template <typename T>
int32_t ToInt32(T value) {
    double temp = ToNumber(value);

    if (!std::isfinite(temp) || std::isnan(temp) || temp == 0) {
        return 0;
    }
    double posInt = std::copysign(std::floor(std::fabs(temp)), temp);
    constexpr double two32 = 4294967296.0;
    double int32bit = std::fmod(posInt, two32);
    if (int32bit < 0) {
        int32bit += two32;
    }
    constexpr double two31 = 2147483648.0;
    if (int32bit >= two31) {
        return static_cast<int32_t>(int32bit - two32);
    }
    return static_cast<int32_t>(int32bit);
}
template int32_t ToInt32(int);
template int32_t ToInt32(double);
template int32_t ToInt32(std::string);
template int32_t ToInt32(Rope);
template int32_t ToInt32(JS::Null);
template int32_t ToInt32(JS::Undefined);
template int32_t ToInt32(JS::Any);

std::string ToString(int value) { return static_cast<std::ostringstream>((std::ostringstream() << value)).str(); }
std::string ToString(double value) {
    return std::isnan(value)   ? "NaN"
           : std::isinf(value) ? value < 0 ? "-Infinity" : "Infinity"
                               : static_cast<std::ostringstream>((std::ostringstream() << value)).str();
}
std::string ToString(const Rope& rope) { return rope.toString(); }
std::string ToString(bool value) { return value ? "true" : "false"; }
std::string ToString(const JS::Null&) { return "null"; }
std::string ToString(const JS::Undefined&) { return "undefined"; }
std::string ToString(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.8

    switch (any.getValue().index()) {
        case NUMBER:
            return JS::CONVERT::ToString(std::get<double>(any.getValue()));
        case STRING:
            return ToString(std::get<Rope>(any.getValue()));
        case BOOL:
            return ToString(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToString(JS::Undefined());
        case NULL_TYPE:
            return ToString(JS::Null());
        default:
            return "[Object]";
    }
}

JS::Any ToObject(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.9
    if (any.getValue().index() == JS::OBJECT) {
        return any;
    }
    return JS::Any(any); // TODO should return the Object kind like Boolean primitive with value
}

} // namespace JS::CONVERT