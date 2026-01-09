#include "internals/PropertyProxy.hpp"
#include "types/objects/Error/JsRangeError.hpp"
#include "types/objects/Error/JsTypeError.hpp"
#include "types/objects/JsDate.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <array>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace JS {

// Helper function to get day name
static const char* getDayName(int weekday) {
    static const std::array<const char*, 7> days = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    return days[weekday];
}

// Helper function to get month name
static const char* getMonthName(int month) {
    static const std::array<const char*, 12> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    return months[month];
}

// Helper to format timezone offset
static std::string formatTimezoneOffset(double t) {
    double offset = DateOperators::LocalTZA() + DateOperators::DaylightSavingTA(t);
    int offsetMinutes = static_cast<int>(offset / DateOperators::msPerMinute);
    int offsetHours = std::abs(offsetMinutes) / 60;
    int offsetMins = std::abs(offsetMinutes) % 60;
    char sign = offsetMinutes >= 0 ? '+' : '-';
    std::ostringstream oss;
    oss << sign << std::setfill('0') << std::setw(2) << offsetHours << std::setw(2) << offsetMins;
    return oss.str();
}

JS::Any Date::toString(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.toString called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::u16string(u"Invalid Date"));
    }

    double localT = DateOperators::LocalTime(t);
    int year = DateOperators::YearFromTime(localT);
    int month = DateOperators::MonthFromTime(localT);
    int date = DateOperators::DateFromTime(localT);
    int weekday = DateOperators::WeekDay(localT);
    int hours = DateOperators::HourFromTime(localT);
    int minutes = DateOperators::MinFromTime(localT);
    int seconds = DateOperators::SecFromTime(localT);

    std::ostringstream oss;
    oss << getDayName(weekday) << " " << getMonthName(month) << " " << std::setfill('0') << std::setw(2) << date << " " << year << " " << std::setw(2) << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2) << seconds << " GMT" << formatTimezoneOffset(t);

    return JS::Any(oss.str());
}

JS::Any Date::toDateString(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.toDateString called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::u16string(u"Invalid Date"));
    }

    double localT = DateOperators::LocalTime(t);
    int year = DateOperators::YearFromTime(localT);
    int month = DateOperators::MonthFromTime(localT);
    int date = DateOperators::DateFromTime(localT);
    int weekday = DateOperators::WeekDay(localT);

    std::ostringstream oss;
    oss << getDayName(weekday) << " " << getMonthName(month) << " " << std::setfill('0') << std::setw(2) << date << " " << year;

    return JS::Any(oss.str());
}

JS::Any Date::toTimeString(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.toTimeString called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::u16string(u"Invalid Date"));
    }

    double localT = DateOperators::LocalTime(t);
    int hours = DateOperators::HourFromTime(localT);
    int minutes = DateOperators::MinFromTime(localT);
    int seconds = DateOperators::SecFromTime(localT);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2) << seconds << " GMT" << formatTimezoneOffset(t);

    return JS::Any(oss.str());
}

JS::Any Date::toLocaleString(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.toLocaleString called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::u16string(u"Invalid Date"));
    }

    double localT = DateOperators::LocalTime(t);
    int year = DateOperators::YearFromTime(localT);
    int month = DateOperators::MonthFromTime(localT);
    int date = DateOperators::DateFromTime(localT);
    int hours = DateOperators::HourFromTime(localT);
    int minutes = DateOperators::MinFromTime(localT);
    int seconds = DateOperators::SecFromTime(localT);

    // Format: M/D/YYYY, H:MM:SS AM/PM (locale-dependent, simplified)
    std::ostringstream oss;
    int displayHour = hours % 12;
    if (displayHour == 0) {
        displayHour = 12;
    }
    const char* ampm = hours >= 12 ? "PM" : "AM";

    oss << (month + 1) << "/" << date << "/" << year << ", " << displayHour << ":" << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << seconds << " " << ampm;

    return JS::Any(oss.str());
}

JS::Any Date::toLocaleDateString(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.toLocaleDateString called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::u16string(u"Invalid Date"));
    }

    double localT = DateOperators::LocalTime(t);
    int year = DateOperators::YearFromTime(localT);
    int month = DateOperators::MonthFromTime(localT);
    int date = DateOperators::DateFromTime(localT);

    // Format: M/D/YYYY (locale-dependent, simplified)
    std::ostringstream oss;
    oss << (month + 1) << "/" << date << "/" << year;

    return JS::Any(oss.str());
}

JS::Any Date::toLocaleTimeString(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.toLocaleTimeString called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::u16string(u"Invalid Date"));
    }

    double localT = DateOperators::LocalTime(t);
    int hours = DateOperators::HourFromTime(localT);
    int minutes = DateOperators::MinFromTime(localT);
    int seconds = DateOperators::SecFromTime(localT);

    // Format: H:MM:SS AM/PM (locale-dependent, simplified)
    std::ostringstream oss;
    int displayHour = hours % 12;
    if (displayHour == 0) {
        displayHour = 12;
    }
    const char* ampm = hours >= 12 ? "PM" : "AM";

    oss << displayHour << ":" << std::setfill('0') << std::setw(2) << minutes << ":" << std::setw(2) << seconds << " " << ampm;

    return JS::Any(oss.str());
}

JS::Any Date::valueOf(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.valueOf called on incompatible Object")));
    }
    return JS::Any(std::get<double>(O->primitiveValue));
}

JS::Any Date::getTime(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getTime called on incompatible Object")));
    }
    return JS::Any(std::get<double>(O->primitiveValue));
}

JS::Any Date::getFullYear(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getFullYear called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getUTCFullYear called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getMonth called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getUTCMonth called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getDate called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getUTCDate called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getDay called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getUTCDay called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getHours called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getUTCHours called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getMinutes called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getUTCMinutes called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getSeconds called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getUTCSeconds called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getMilliseconds called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getUTCMilliseconds called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.getTimezoneOffset called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setTime called on incompatible Object")));
    }
    double t = CONVERT::ToNumber(args[u"0"]);
    double v = DateOperators::TimeClip(t);
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::setMilliseconds(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setMilliseconds called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setUTCMilliseconds called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setSeconds called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setUTCSeconds called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    double s = CONVERT::ToNumber(args[u"0"]);
    double milli = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"1"]) : DateOperators::msFromTime(t);
    double date = DateOperators::MakeDate(DateOperators::Day(t), DateOperators::MakeTime(DateOperators::HourFromTime(t), DateOperators::MinFromTime(t), s, milli));
    double v = DateOperators::TimeClip(date);
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::setMinutes(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setMinutes called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setUTCMinutes called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    double m = CONVERT::ToNumber(args[u"0"]);
    double s = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"1"]) : DateOperators::SecFromTime(t);
    double milli = !JS::COMPARE::Type(args[u"2"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"2"]) : DateOperators::msFromTime(t);
    double date = DateOperators::MakeDate(DateOperators::Day(t), DateOperators::MakeTime(DateOperators::HourFromTime(t), m, s, milli));
    double v = DateOperators::TimeClip(date);
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::setHours(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setHours called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setUTCHours called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    double h = CONVERT::ToNumber(args[u"0"]);
    double m = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"1"]) : DateOperators::MinFromTime(t);
    double s = !JS::COMPARE::Type(args[u"2"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"2"]) : DateOperators::SecFromTime(t);
    double milli = !JS::COMPARE::Type(args[u"3"], JS::UNDEFINED) ? CONVERT::ToNumber(args[u"3"]) : DateOperators::msFromTime(t);
    double newDate = DateOperators::MakeDate(DateOperators::Day(t), DateOperators::MakeTime(h, m, s, milli));
    double v = DateOperators::TimeClip(newDate);
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::setDate(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setDate called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setUTCDate called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    int dt = CONVERT::ToInteger(args[u"0"]);
    double newDate = DateOperators::MakeDate(DateOperators::MakeDay(DateOperators::YearFromTime(t), DateOperators::MonthFromTime(t), dt), DateOperators::TimeWithinDay(t));
    double v = DateOperators::TimeClip(newDate);
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::setMonth(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setMonth called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setUTCMonth called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    int m = CONVERT::ToInteger(args[u"0"]);
    int dt = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToInteger(args[u"1"]) : DateOperators::DateFromTime(t);
    double newDate = DateOperators::MakeDate(DateOperators::MakeDay(DateOperators::YearFromTime(t), m, dt), DateOperators::TimeWithinDay(t));
    double v = DateOperators::TimeClip(newDate);
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::setFullYear(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setFullYear called on incompatible Object")));
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
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.setUTCFullYear called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        t = +0;
    }
    int y = CONVERT::ToInteger(args[u"0"]);
    int m = !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED) ? CONVERT::ToInteger(args[u"1"]) : DateOperators::MonthFromTime(t);
    int dt = !JS::COMPARE::Type(args[u"2"], JS::UNDEFINED) ? CONVERT::ToInteger(args[u"2"]) : DateOperators::DateFromTime(t);
    double newDate = DateOperators::MakeDate(DateOperators::MakeDay(y, m, dt), DateOperators::TimeWithinDay(t));
    double v = DateOperators::TimeClip(newDate);
    O->primitiveValue = v;
    return JS::Any(v);
}

JS::Any Date::toUTCString(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.toUTCString called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    if (std::isnan(t)) {
        return JS::Any(std::u16string(u"Invalid Date"));
    }

    int year = DateOperators::YearFromTime(t);
    int month = DateOperators::MonthFromTime(t);
    int date = DateOperators::DateFromTime(t);
    int weekday = DateOperators::WeekDay(t);
    int hours = DateOperators::HourFromTime(t);
    int minutes = DateOperators::MinFromTime(t);
    int seconds = DateOperators::SecFromTime(t);

    std::ostringstream oss;
    oss << getDayName(weekday) << ", " << std::setfill('0') << std::setw(2) << date << " " << getMonthName(month) << " " << year << " " << std::setw(2) << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2) << seconds << " GMT";

    return JS::Any(oss.str());
}

JS::Any Date::toISOString(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);
    if (O->class_name != u"Date") {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Date.prototype.toISOString called on incompatible Object")));
    }
    double t = std::get<double>(O->primitiveValue);
    if (!std::isfinite(t)) {
        throw JS::Any(JS::InternalObject::create<JS::RangeError>(JS::Any(u"Invalid time value")));
    }

    int year = DateOperators::YearFromTime(t);
    int month = DateOperators::MonthFromTime(t);
    int date = DateOperators::DateFromTime(t);
    int hours = DateOperators::HourFromTime(t);
    int minutes = DateOperators::MinFromTime(t);
    int seconds = DateOperators::SecFromTime(t);
    int milliseconds = DateOperators::msFromTime(t);

    std::ostringstream oss;

    if (year < 0 || year > 9999) {
        char sign = year >= 0 ? '+' : '-';
        oss << sign << std::setfill('0') << std::setw(6) << std::abs(year);
    } else {
        oss << std::setfill('0') << std::setw(4) << year;
    }

    oss << "-" << std::setw(2) << (month + 1) << "-" << std::setw(2) << date << "T" << std::setw(2) << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2) << seconds << "." << std::setw(3) << milliseconds << "Z";

    return JS::Any(oss.str());
}

JS::Any Date::toJSON(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<InternalObject> O = CONVERT::ToObject(thisArg);

    JS::Any tv = CONVERT::ToPrimitive(thisArg, JS::NUMBER);

    if (COMPARE::Type(tv, JS::NUMBER)) {
        double tvNum = CONVERT::ToNumber(tv);
        if (!std::isfinite(tvNum)) {
            return JS::Any(JS::Null{});
        }
    }

    return toISOString(thisArg, args);
}

} // namespace JS
