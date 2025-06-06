#include "types/objects/JsDate.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"
#include "internals/PropertyProxy.hpp"
#include <cmath>

namespace JS {

JS::Any Date::toString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::getUTCSeconds not implemented");
}

JS::Any Date::toDateString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::getUTCSeconds not implemented");
}

JS::Any Date::toTimeString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::getUTCSeconds not implemented");
}

JS::Any Date::toLocaleString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::getUTCSeconds not implemented");
}

JS::Any Date::toLocaleDateString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::toLocaleDateString not implemented");
}

JS::Any Date::toLocaleTimeString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::toLocaleTimeString not implemented");
}

JS::Any Date::valueOf(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.valueOf called on incompatible Object"); // TODO: throw TypeError
    }
    return JS::Any(std::get<double>(O->primitiveValue));
}

JS::Any Date::getTime(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getTime called on incompatible Object"); // TODO: throw TypeError
    }
    return JS::Any(std::get<double>(O->primitiveValue));
}

JS::Any Date::getFullYear(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getFullYear called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::YearFromTime(DateOperators::LocalTime(t)));
}

JS::Any Date::getUTCFullYear(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getUTCFullYear called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::YearFromTime(t));
}

JS::Any Date::getMonth(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getMonth called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::MonthFromTime(DateOperators::LocalTime(t)));
}

JS::Any Date::getUTCMonth(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getUTCMonth called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::MonthFromTime(t));
}

JS::Any Date::getDate(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getDate called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::DateFromTime(DateOperators::LocalTime(t)));
}

JS::Any Date::getUTCDate(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getUTCDate called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::DateFromTime(t));
}

JS::Any Date::getDay(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getDay called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::WeekDay(DateOperators::LocalTime(t)));
}

JS::Any Date::getUTCDay(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getUTCDay called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::WeekDay(t));
}

JS::Any Date::getHours(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getHours called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::HourFromTime(DateOperators::LocalTime(t)));
}

JS::Any Date::getUTCHours(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getUTCHours called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::HourFromTime(t));
}

JS::Any Date::getMinutes(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getMinutes called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::MinFromTime(DateOperators::LocalTime(t)));
}

JS::Any Date::getUTCMinutes(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getUTCMinutes called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::MinFromTime(t));
}

JS::Any Date::getSeconds(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getSeconds called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::SecFromTime(DateOperators::LocalTime(t)));
}

JS::Any Date::getUTCSeconds(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getUTCSeconds called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::SecFromTime(t));
}

JS::Any Date::getMilliseconds(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getMilliseconds called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::msFromTime(DateOperators::LocalTime(t)));
}

JS::Any Date::getUTCMilliseconds(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getUTCMilliseconds called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(DateOperators::msFromTime(t));
}

JS::Any Date::getTimezoneOffset(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getTimezoneOffset called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any((t - DateOperators::LocalTime(t)) / DateOperators::msPerMinute);
}

JS::Any Date::setTime(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.getTimezoneOffset called on incompatible Object"); // TODO: throw TypeError
    }
    double t = CONVERT::ToNumber(args[u"0"]);
    double v = DateOperators::TimeClip(t);
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::setMilliseconds(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setMilliseconds called on incompatible Object"); // TODO: throw TypeError
    }
    double t = DateOperators::LocalTime(std::get<double>(O->primitiveValue));
    double time = DateOperators::MakeTime(DateOperators::HourFromTime(t), DateOperators::MinFromTime(t), DateOperators::SecFromTime(t), CONVERT::ToNumber(args[u"0"]));
    double u = DateOperators::TimeClip(DateOperators::UTC(DateOperators::MakeDate(DateOperators::Day(t), time)));
    O->primitiveValue = u;
    return JS::Any(u);
}

JS::Any Date::setUTCMilliseconds(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setUTCMilliseconds called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    double time = DateOperators::MakeTime(DateOperators::HourFromTime(t), DateOperators::MinFromTime(t), DateOperators::SecFromTime(t), CONVERT::ToNumber(args[u"0"]));
    double v = DateOperators::TimeClip(DateOperators::MakeDate(DateOperators::Day(t), time));
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::setSeconds(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setSeconds called on incompatible Object"); // TODO: throw TypeError
    }
    double t = DateOperators::LocalTime(std::get<double>(O->primitiveValue));
    double s = CONVERT::ToNumber(args[u"0"]);
    double milli = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"1"]) : DateOperators::msFromTime(t);
    double date = DateOperators::MakeDate(DateOperators::Day(t), DateOperators::MakeTime(DateOperators::HourFromTime(t), DateOperators::MinFromTime(t), s, milli));
    double u = DateOperators::TimeClip(DateOperators::UTC(date));
    O->primitiveValue = u;
    return JS::Any(u);
}

JS::Any Date::setUTCSeconds(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setUTCSeconds called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    double s = CONVERT::ToNumber(args[u"0"]);
    double milli = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"1"]) : DateOperators::msFromTime(t);
    double date = DateOperators::MakeDate(DateOperators::Day(t), DateOperators::MakeTime(DateOperators::HourFromTime(t), DateOperators::MinFromTime(t), s, milli));
    double v = DateOperators::TimeClip(DateOperators::UTC(date));
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::setMinutes(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setMinutes called on incompatible Object"); // TODO: throw TypeError
    }
    double t = DateOperators::LocalTime(std::get<double>(O->primitiveValue));
    double m = CONVERT::ToNumber(args[u"0"]);
    double s = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"1"]) : DateOperators::SecFromTime(t);
    double milli = !JS::COMPARE::Type(args[u"2"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"2"]) : DateOperators::msFromTime(t);
    double date = DateOperators::MakeDate(DateOperators::Day(t), DateOperators::MakeTime(DateOperators::HourFromTime(t), m, s, milli));
    double u = DateOperators::TimeClip(DateOperators::UTC(date));
    O->primitiveValue = u;
    return JS::Any(u);
}

JS::Any Date::setUTCMinutes(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setUTCMinutes called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    double m = CONVERT::ToNumber(args[u"0"]);
    double s = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"1"]) : DateOperators::SecFromTime(t);
    double milli = !JS::COMPARE::Type(args[u"2"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"2"]) : DateOperators::msFromTime(t);
    double date = DateOperators::MakeDate(DateOperators::Day(t), DateOperators::MakeTime(DateOperators::HourFromTime(t), m, s, milli));
    double v = DateOperators::TimeClip(DateOperators::UTC(date));
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::setHours(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setHours called on incompatible Object"); // TODO: throw TypeError
    }
    double t = DateOperators::LocalTime(std::get<double>(O->primitiveValue));
    double h = CONVERT::ToNumber(args[u"0"]);
    double m = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"1"]) : DateOperators::MinFromTime(t);
    double s = !JS::COMPARE::Type(args[u"2"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"2"]) : DateOperators::SecFromTime(t);
    double milli = !JS::COMPARE::Type(args[u"3"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"3"]) : DateOperators::msFromTime(t);
    double date = DateOperators::MakeDate(DateOperators::Day(t), DateOperators::MakeTime(h, m, s, milli));
    double u = DateOperators::TimeClip(DateOperators::UTC(date));
    O->primitiveValue = u;
    return JS::Any(u);
}

JS::Any Date::setUTCHours(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setUTCHours called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    double h = CONVERT::ToNumber(args[u"0"]);
    double m = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"1"]) : DateOperators::MinFromTime(t);
    double s = !JS::COMPARE::Type(args[u"2"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"2"]) : DateOperators::SecFromTime(t);
    double milli = !JS::COMPARE::Type(args[u"3"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"3"]) : DateOperators::msFromTime(t);
    double date = DateOperators::MakeDate(DateOperators::Day(t), DateOperators::MakeTime(h, m, s, milli));
    double v = DateOperators::TimeClip(DateOperators::UTC(date));
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::setDate(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setDate called on incompatible Object"); // TODO: throw TypeError
    }
    double t = DateOperators::LocalTime(std::get<double>(O->primitiveValue));
    int dt = CONVERT::ToInteger(args[u"0"]);
    double date = DateOperators::MakeDate(DateOperators::MakeDay(DateOperators::YearFromTime(t), DateOperators::MonthFromTime(t), dt), DateOperators::TimeWithinDay(t));
    double u = DateOperators::TimeClip(DateOperators::UTC(date));
    O->primitiveValue = u;
    return JS::Any(u);
}

JS::Any Date::setUTCDate(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setUTCDate called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    int dt = CONVERT::ToInteger(args[u"0"]);
    double date = DateOperators::MakeDate(DateOperators::MakeDay(DateOperators::YearFromTime(t), DateOperators::MonthFromTime(t), dt), DateOperators::TimeWithinDay(t));
    double v = DateOperators::TimeClip(DateOperators::UTC(date));
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::setMonth(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setMonth called on incompatible Object"); // TODO: throw TypeError
    }
    double t = DateOperators::LocalTime(std::get<double>(O->primitiveValue));
    int m = CONVERT::ToInteger(args[u"0"]);
    int dt = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToInteger(args[u"1"]) : DateOperators::DateFromTime(t);
    double newDate = DateOperators::MakeDate(DateOperators::MakeDay(DateOperators::YearFromTime(t), m, dt), DateOperators::TimeWithinDay(t));
    double u = DateOperators::TimeClip(DateOperators::UTC(newDate));
    O->primitiveValue = u;
    return JS::Any(u);
}

JS::Any Date::setUTCMonth(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setUTCMonth called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    int m = CONVERT::ToInteger(args[u"0"]);
    int dt = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToInteger(args[u"1"]) : DateOperators::DateFromTime(t);
    double newDate = DateOperators::MakeDate(DateOperators::MakeDay(DateOperators::YearFromTime(t), m, dt), DateOperators::TimeWithinDay(t));
    double v = DateOperators::TimeClip(DateOperators::UTC(newDate));
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::setFullYear(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setFullYear called on incompatible Object"); // TODO: throw TypeError
    }
    double t = DateOperators::LocalTime(std::get<double>(O->primitiveValue));
    if (std::isnan(t)) {
        t = +0;
    }
    int y = CONVERT::ToInteger(args[u"0"]);
    int m = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToInteger(args[u"1"]) : DateOperators::MonthFromTime(t);
    int dt = !JS::COMPARE::Type(args[u"2"], JS::UNDEFINED) ? CONVERT::ToInteger(args[u"2"]) : DateOperators::DateFromTime(t);
    double newDate = DateOperators::MakeDate(DateOperators::MakeDay(y, m, dt), DateOperators::TimeWithinDay(t));
    double u = DateOperators::TimeClip(DateOperators::UTC(newDate));
    O->primitiveValue = u;
    return JS::Any(u);
}

JS::Any Date::setUTCFullYear(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw std::runtime_error("TypeError: Date.prototype.setUTCFullYear called on incompatible Object"); // TODO: throw TypeError
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        t = +0;
    }
    int y = CONVERT::ToInteger(args[u"0"]);
    int m = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToInteger(args[u"1"]) : DateOperators::MonthFromTime(t);
    int dt = !JS::COMPARE::Type(args[u"2"], JS::UNDEFINED) ? CONVERT::ToInteger(args[u"2"]) : DateOperators::DateFromTime(t);
    double newDate = DateOperators::MakeDate(DateOperators::MakeDay(y, m, dt), DateOperators::TimeWithinDay(t));
    double v = DateOperators::TimeClip(DateOperators::UTC(newDate));
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::toUTCString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::toUTCString not implemented");
}

JS::Any Date::toISOString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::toISOString not implemented");
}

JS::Any Date::toJSON(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::toJSON not implemented");
}

} // namespace JS




