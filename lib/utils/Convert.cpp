#include "types/objects/JsObject.hpp"

#include <cmath>
#include <sstream>
#include <string>
#include <utils/Compare.hpp>
#include <utils/Convert.hpp>
#include "utils/Is.hpp"

namespace JS::CONVERT {

JS::Any ToPrimitive(const JS::Any& any) { // https://262.ecma-international.org/5.1/#sec-9.1
    if (JS::COMPARE::Type(any, JS::OBJECT)) {
        return JS::Any(std::get<std::shared_ptr<JS::InternalObject>>(any.getValue())); // TODO
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

std::string ToString(int value) { return (std::ostringstream() << value).str(); }
std::string ToString(double value) {
    return std::isnan(value)   ? "NaN"
           : std::isinf(value) ? value < 0 ? "-Infinity" : "Infinity"
                               : (std::ostringstream() << value).str();
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
JS::Any FromPropertyDescriptor(const AccessorDescriptor& desc) { // https://262.ecma-international.org/5.1/#sec-8.10.4
    if (desc.get == nullptr && desc.set == nullptr) {
        return {};
    }
    JS::Object obj;
    obj.put("get", desc.get == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(*desc.get));
    obj.put("set", desc.set == nullptr ? JS::Any(JS::Undefined{}) : JS::Any(*desc.set));
    obj.put("enumerable", JS::Any(desc.enumerable));
    obj.put("configurable", JS::Any(desc.configurable));
    return JS::Any(obj);
}

JS::Any FromPropertyDescriptor(const JS::Attribute& desc) { // https://262.ecma-international.org/5.1/#sec-8.10.4
    if (desc.index() == JS::DATA_DESCRIPTOR) {
        return FromPropertyDescriptor(std::get<JS::DataDescriptor>(desc));
    }
    if (desc.index() == JS::ACCESSOR_DESCRIPTOR) {
        return FromPropertyDescriptor(std::get<JS::AccessorDescriptor>(desc));
    }
    return {};
}

JS::Any FromPropertyDescriptor(const JS::DataDescriptor& desc) { // https://262.ecma-international.org/5.1/#sec-8.10.4
    JS::Object obj;
    obj.put("value", desc.value);
    obj.put("writable", JS::Any(desc.writable));
    obj.put("enumerable", JS::Any(desc.enumerable));
    obj.put("configurable", JS::Any(desc.configurable));
    return JS::Any(obj);
}
JS::Attribute ToPropertyDescriptor(const Any& desc) {
    if (!COMPARE::Type(desc, OBJECT)) {
        throw std::runtime_error("TypeError: Property descriptor must be an object"); // TODO: make this a JS error
    }
    std::shared_ptr<JS::InternalObject> obj = std::get<std::shared_ptr<JS::InternalObject>>(desc.getValue());
    JS::DataDescriptor data;
    JS::AccessorDescriptor accessor;
    bool get_or_set = false;
    bool value_or_writable = false;
    if (obj->hasProperty("enumerable")) {
        data.enumerable = ToBoolean(obj->get("value"));
        accessor.enumerable = ToBoolean(obj->get("value"));
    }
    if (obj->hasProperty("configurable")) {
        data.configurable = ToBoolean(obj->get("configurable"));
        accessor.configurable = ToBoolean(obj->get("configurable"));
    }
    if ((value_or_writable = value_or_writable || obj->hasProperty("value"))) {
        data.value = obj->get("value");
    }
    if ((value_or_writable = value_or_writable || obj->hasProperty("writable"))) {
        data.writable = ToBoolean(obj->get("writable"));
    }
    if ((get_or_set = get_or_set || obj->hasProperty("get"))) {
        JS::Any tmp = obj->get("get");
        if (COMPARE::Type(tmp, UNDEFINED) || JS::IS::Callable(tmp)) {
            accessor.get = std::make_shared<JS::Object>(tmp);
        } else {
            throw std::runtime_error("TypeError: get must be callable or undefined"); // TODO: make this a JS error
        }
    }
    if ((get_or_set = get_or_set || obj->hasProperty("set"))) {
        JS::Any tmp = obj->get("set");
        if (COMPARE::Type(tmp, UNDEFINED) || JS::IS::Callable(tmp)) {
            accessor.set = std::make_shared<JS::Object>(tmp);
        } else {
            throw std::runtime_error("TypeError: set must be callable or undefined"); // TODO: make this a JS error
        }
    }
    if (get_or_set) {
        if (value_or_writable) {
            throw std::runtime_error(
                "TypeError: Property descriptor cannot be both accessor and data descriptor"); // TODO: make this a JS
                                                                                               // error
        }
        return accessor;
    }
    return data;
}

} // namespace JS::CONVERT