#include "types/objects/JsDate.hpp"
#include "utils/Convert.hpp"
#include "utils/Compare.hpp"
#include "internals/PropertyProxy.hpp"
#include <cmath>
#include <chrono>

namespace JS {

JS::Any Date::parse(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("Date::parse not implemented");
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
        yr = 1900+CONVERT::ToInteger(year);
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
