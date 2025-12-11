#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsDate.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <chrono>
#include <cmath>

namespace JS {

Date::Date() : InternalObject({}, getPrototypeProperties(), u"Date", true) {
    auto nowMilliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    primitiveValue = static_cast<double>(nowMilliseconds);
}

Date::Date(const JS::Any& value) : InternalObject({}, getPrototypeProperties(), u"Date", true) {
    JS::Any v = CONVERT::ToPrimitive(value);
    double V;

    if (COMPARE::Type(v, JS::STRING)) {
        std::string dateString = CONVERT::ToUtf8(CONVERT::ToString(v));
        V = CONVERT::ToNumber(Date::parse(JS::Any(), JS::Any(std::make_shared<JS::InternalObject>(
            std::unordered_map<std::u16string, JS::Attribute>{{u"0", JS::DataDescriptor{v, true, true, true}}},
            nullptr, u"Arguments", true))));
    } else {
        V = CONVERT::ToNumber(v);
    }

    primitiveValue = DateOperators::TimeClip(V);
}

Date::Date(JS::Any year, JS::Any month, JS::Any day, JS::Any hours, JS::Any minutes, JS::Any seconds, JS::Any milliseconds) : InternalObject({}, getPrototypeProperties(), u"Date", true) {
    double y = CONVERT::ToNumber(year);
    double m = CONVERT::ToNumber(month);
    double dt = !COMPARE::Type(day, JS::UNDEFINED) ? CONVERT::ToNumber(day) : 1;
    double h = !COMPARE::Type(hours, JS::UNDEFINED) ? CONVERT::ToNumber(hours) : 0;
    double min = !COMPARE::Type(minutes, JS::UNDEFINED) ? CONVERT::ToNumber(minutes) : 0;
    double s = !COMPARE::Type(seconds, JS::UNDEFINED) ? CONVERT::ToNumber(seconds) : 0;
    double milli = !COMPARE::Type(milliseconds, JS::UNDEFINED) ? CONVERT::ToNumber(milliseconds) : 0;

    // If y is not NaN and 0 ≤ ToInteger(y) ≤ 99, then let yr be 1900+ToInteger(y); otherwise, let yr be y
    double yr;
    if (!std::isnan(y)) {
        int yi = CONVERT::ToInteger(JS::Any(y));
        if (yi >= 0 && yi <= 99) {
            yr = 1900 + yi;
        } else {
            yr = y;
        }
    } else {
        yr = y;
    }

    // Let finalDate be MakeDate(MakeDay(yr, m, dt), MakeTime(h, min, s, milli))
    double dayValue = DateOperators::MakeDay(static_cast<int>(yr), static_cast<int>(m), static_cast<int>(dt));
    double timeValue = DateOperators::MakeTime(h, min, s, milli);
    double finalDate = DateOperators::MakeDate(static_cast<int>(dayValue), timeValue);

    primitiveValue = DateOperators::TimeClip(DateOperators::UTC(finalDate));
}

} // namespace JS