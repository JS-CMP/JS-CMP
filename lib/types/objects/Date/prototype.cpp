#include "internals/PropertyProxy.hpp"
#include "types/objects/JsDate.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <chrono>
#include <cmath>

namespace JS {
bool Date::get_number(std::string& dateString, size_t& index, int& number) {
    size_t start = index;
    number = 0;
    while (index < dateString.size() && isdigit(dateString[index])) {
        number = number * 10 + (dateString[index] - '0');
        ++index;
    }
    return index == start;
}

JS::Any Date::parse(const JS::Any& thisArg, const JS::Any& args) {
    std::string dateString = CONVERT::ToUtf8(CONVERT::ToString(args[u"0"]));
    if (dateString.empty()) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    char firstChar = dateString[0];
    bool isExtendedYear = false;
    if (!(isExtendedYear = (firstChar == '+' || firstChar == '-')) && !isdigit(firstChar)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }

    size_t index;
    size_t size = dateString.size();
    int year = 0, month = 1, day = 1, hours = 0, minutes = 0, seconds = 0, milliseconds = 0;

    do {
        if (isExtendedYear) {
            index = 1;
        } else {
            index = 0;
        }
        if (get_number(dateString, index, year) || year > 999999) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
        if (isExtendedYear) {
            if (firstChar == '-') {
                year = -year;
            }
        }
        if ((index + 1) >= size || dateString[index] != '-') {
            break;
        }
        ++index;
        if (get_number(dateString, index, month) || month < 1 || month > 12) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
        if ((index + 1) >= size || dateString[index] != '-') {
            break;
        }
        ++index;
        if (get_number(dateString, index, day) || day < 1 || day > 31) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
        if ((index + 1) >= size || dateString[index] != 'T') {
            break;
        }
        ++index;
        if (get_number(dateString, index, hours) || hours < 0 || hours > 24) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
        if ((index + 1) >= size || dateString[index] != ':') {
            break;
        }
        ++index;
        if (get_number(dateString, index, minutes) || minutes < 0 || minutes > 59) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
        if ((index + 1) >= size || dateString[index] != ':') {
            break;
        }
        ++index;
        if (get_number(dateString, index, seconds) || seconds < 0 || seconds > 59) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
        if ((index + 1) >= size || dateString[index] != '.') {
            break;
        }
        ++index;
        if (get_number(dateString, index, milliseconds) || milliseconds < 0 || milliseconds > 999) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
        if ((index + 1) >= size || dateString[index] != 'Z') {
            break;
        }
    } while (false);
    return JS::Any(DateOperators::TimeClip(DateOperators::UTC(DateOperators::MakeDate(DateOperators::MakeDay(year, month - 1, day), DateOperators::MakeTime(hours, minutes, seconds, milliseconds)))));
}

JS::Any Date::UTC(const JS::Any& thisArg, const JS::Any& args) {
    double year = CONVERT::ToNumber(args[u"0"]);
    int month = CONVERT::ToInteger(args[u"1"]);
    int date = !COMPARE::Type(args[u"2"], UNDEFINED) ? CONVERT::ToInteger(args[u"2"]) : 1;
    double hours = !COMPARE::Type(args[u"3"], UNDEFINED) ? CONVERT::ToNumber(args[u"3"]) : 0;
    double minutes = !COMPARE::Type(args[u"4"], UNDEFINED) ? CONVERT::ToNumber(args[u"4"]) : 0;
    double seconds = !COMPARE::Type(args[u"5"], UNDEFINED) ? CONVERT::ToNumber(args[u"5"]) : 0;
    double milliseconds = !COMPARE::Type(args[u"6"], UNDEFINED) ? CONVERT::ToNumber(args[u"6"]) : 0;

    int yr = CONVERT::ToInteger(year);
    if (!std::isnan(year) && year >= 0 && year <= 99) {
        yr = 1900 + CONVERT::ToInteger(year);
    }

    double day = DateOperators::MakeDay(yr, month, date);
    double time = DateOperators::MakeTime(hours, minutes, seconds, milliseconds);
    double utcTime = DateOperators::TimeClip(DateOperators::MakeDate(day, time));

    return JS::Any(utcTime);
}

JS::Any Date::now(const JS::Any& thisArg, const JS::Any& args) {
    auto nowMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    double now = DateOperators::TimeClip(DateOperators::UTC(DateOperators::MakeDate(DateOperators::Day(nowMilliseconds), 0)));
    return JS::Any(now);
}

} // namespace JS