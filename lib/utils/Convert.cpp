#include <cmath>
#include <sstream>
#include <string>
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

namespace JS::CONVERT {

JS::Any ToPrimitive(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.1
    if (JS::COMPARE::Type(any, JS::OBJECT)) {
        return JS::Any(std::get<std::shared_ptr<JS::Object>>(any.getValue())); // TODO
    }
    return any;
}

inline bool ToBoolean(int value) { return value != 0; }
inline bool ToBoolean(double value) { return !std::isnan(value) && value != 0; }
inline bool ToBoolean(const std::string& str) { return !str.empty(); }
inline bool ToBoolean(const Rope& rope) { return ToBoolean(rope.toString()); }
inline bool ToBoolean(bool value) { return value; }
inline bool ToBoolean(const JS::Null&) { return false; }
inline bool ToBoolean(const JS::Undefined&) { return false; }
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

inline double ToNumber(int value) { return static_cast<double>(value); }
inline double ToNumber(double value) { return value; }
inline double ToNumber(const std::string& str) { return !str.empty() ? std::stod(str) : 0; }
inline double ToNumber(const Rope& rope) { return ToNumber(rope.toString()); }
inline double ToNumber(bool value) { return static_cast<double>(value); }
inline double ToNumber(const JS::Null&) { return 0; }
inline double ToNumber(const JS::Undefined&) { return std::numeric_limits<double>::quiet_NaN(); }
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

inline int ToInteger(int value) { return value; }
inline int ToInteger(double value) {
    return std::isnan(value) ? 0 : value < 0 ? -std::floor(-value) : std::floor(value);
}
inline int ToInteger(const std::string& str) { return ToInteger(ToNumber(str)); }
inline int ToInteger(const Rope& rope) { return ToInteger(rope.toString()); }
inline int ToInteger(bool value) { return value ? 1 : 0; }
inline int ToInteger(const JS::Null&) { return 0; }
inline int ToInteger(const JS::Undefined&) { return 0; }
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

inline std::string ToString(int value) {
    return static_cast<std::ostringstream>((std::ostringstream() << value)).str();
}
inline std::string ToString(double value) {
    return std::isnan(value)   ? "NaN"
           : std::isinf(value) ? value < 0 ? "-Infinity" : "Infinity"
                               : static_cast<std::ostringstream>((std::ostringstream() << value)).str();
}
inline std::string ToString(const Rope& rope) { return rope.toString(); }
inline std::string ToString(bool value) { return value ? "true" : "false"; }
inline std::string ToString(const JS::Null&) { return "null"; }
inline std::string ToString(const JS::Undefined&) { return "undefined"; }

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