#include "types/objects/JsDate.hpp"
#include "utils/Convert.hpp"

#include <cmath>
#include <unicode/calendar.h>
#include <unicode/timezone.h>

namespace JS::DateOperators {
int Day(double t) {
    return std::floor(t / JS::DateOperators::msPerDay);
}

double TimeWithinDay(double t) {
    return std::fmod(t, JS::DateOperators::msPerDay);
}

double DaysInYear(int y) {
    if ((y % 4) != 0) {
        return 365;
    } else if ((y % 100) != 0) {
        return 366;
    } else if ((y % 400) != 0) {
        return 365;
    }
    return 366;
}

double DayFromYear(int y) {
    return 365 * (y - 1970) + std::floor((y - 1969) / 4) - std::floor((y - 1901) / 100) + std::floor((y - 1601) / 400);
}

double TimeFromYear(int y) {
    return JS::DateOperators::msPerDay * DayFromYear(y);
}

int YearFromTime(double t) {
    int low = -285616;
    int high = 285616;

    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (TimeFromYear(mid) <= t) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }

    return low;
}

bool InLeapYear(double t) {
    return DaysInYear(YearFromTime(t)) == 366;
}

int MonthFromTime(double t) {
    double day = DayWithinYear(t);
    bool leap = InLeapYear(t);

    if (day < 31) {
        return 0;
    }
    if (day < 59 + leap) {
        return 1;
    }
    if (day < 90 + leap) {
        return 2;
    }
    if (day < 120 + leap) {
        return 3;
    }
    if (day < 151 + leap) {
        return 4;
    }
    if (day < 181 + leap) {
        return 5;
    }
    if (day < 212 + leap) {
        return 6;
    }
    if (day < 243 + leap) {
        return 7;
    }
    if (day < 273 + leap) {
        return 8;
    }
    if (day < 304 + leap) {
        return 9;
    }
    if (day < 334 + leap) {
        return 10;
    }
    return 11;
}

double DayWithinYear(double t) {
    return Day(t) - DayFromYear(YearFromTime(t));
}

int DateFromTime(double t) {
    double day = DayWithinYear(t);
    bool leap = InLeapYear(t);
    int month = MonthFromTime(t);

    switch (month) {
        case 0:
            return day + 1;
        case 1:
            return day - 30;
        case 2:
            return day - 58 - leap;
        case 3:
            return day - 89 - leap;
        case 4:
            return day - 119 - leap;
        case 5:
            return day - 150 - leap;
        case 6:
            return day - 180 - leap;
        case 7:
            return day - 211 - leap;
        case 8:
            return day - 242 - leap;
        case 9:
            return day - 272 - leap;
        case 10:
            return day - 303 - leap;
        case 11:
            return day - 333 - leap;
        default:
            return 1;
    }
}

int WeekDay(double t) {
    return ((Day(t) + 4) % 7);
}

double LocalTZA() {
    UErrorCode status = U_ZERO_ERROR;
    icu::TimeZone* tz = icu::TimeZone::createDefault();
    int32_t rawOffset, dstOffset;
    UDate now = icu::Calendar::getNow();
    tz->getOffset(now, false, rawOffset, dstOffset, status);
    delete tz;
    return rawOffset;
}

double DaylightSavingTA(double t) {
    UErrorCode status = U_ZERO_ERROR;
    icu::TimeZone* tz = icu::TimeZone::createDefault();
    int32_t rawOffset, dstOffset;
    UDate date = t;
    tz->getOffset(date, false, rawOffset, dstOffset, status);
    delete tz;

    double dstAdjustment = dstOffset;
    return dstAdjustment;
}

double LocalTime(double t) {
    return t + LocalTZA() + DaylightSavingTA(t);
}

double UTC(double t) {
    return t - LocalTZA() - DaylightSavingTA(t - LocalTZA());
}

int HourFromTime(double t) {
    return static_cast<int>(std::floor(t / msPerHour)) % HoursPerDay;
}

int MinFromTime(double t) {
    return static_cast<int>(std::floor(t / msPerMinute)) % MinutesPerHour;
}

int SecFromTime(double t) {
    return static_cast<int>(std::floor(t / msPerSecond)) % SecondsPerMinute;
}

int msFromTime(double t) {
    return static_cast<int>(t) % static_cast<int>(msPerSecond);
}

JS::Any MakeTime(JS::Any hour, JS::Any min, JS::Any sec, JS::Any ms) {
    int h = JS::CONVERT::ToInteger(hour);
    int m = JS::CONVERT::ToInteger(min);
    int s = JS::CONVERT::ToInteger(sec);
    int mms = JS::CONVERT::ToInteger(ms);
    if (!std::isfinite(h) || !std::isfinite(m) || !std::isfinite(s) || !std::isfinite(mms)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(h * msPerHour + m * msPerMinute + s * msPerSecond + mms);
}

double MakeTime(double hour, double min, double sec, double ms) {
    if (!std::isfinite(hour) || !std::isfinite(min) || !std::isfinite(sec) || !std::isfinite(ms)) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return hour * msPerHour + min * msPerMinute + sec * msPerSecond + ms;
}

JS::Any MakeDay(JS::Any year, JS::Any month, JS::Any date) {
    int y = JS::CONVERT::ToInteger(year);
    int m = JS::CONVERT::ToInteger(month);
    int dt = JS::CONVERT::ToInteger(date);
    if (!std::isfinite(y) || !std::isfinite(m) || !std::isfinite(dt)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    int ym = y + static_cast<int>(std::floor(m / 12.0));
    int mn = static_cast<int>(std::fmod(m, 12.0));
    if (mn < 0) mn += 12;  // Handle negative month values
    double t = TimeFromYear(ym);
    const int maxOffsetDays = 400;

    for (int i = 0; i < maxOffsetDays; ++i) {
        double current = t + i * JS::DateOperators::msPerDay;
        if (YearFromTime(current) == ym && MonthFromTime(current) == mn && DateFromTime(current) == 1) {
            int day = static_cast<int>(std::floor(current / JS::DateOperators::msPerDay));
            return JS::Any(static_cast<double>(day + dt - 1));
        }
    }
    return JS::Any(std::numeric_limits<double>::quiet_NaN());
}

int MakeDay(int year, int month, int date) {
    if (!std::isfinite(year) || !std::isfinite(month) || !std::isfinite(date)) {
        return std::numeric_limits<int>::quiet_NaN();
    }
    int ym = year + static_cast<int>(std::floor(month / 12.0));
    int mn = static_cast<int>(std::fmod(month, 12.0));
    if (mn < 0) {
        mn += 12;  // Handle negative month values
    }
    double t = TimeFromYear(ym);
    const int maxOffsetDays = 400;

    for (int i = 0; i < maxOffsetDays; ++i) {
        double current = t + i * JS::DateOperators::msPerDay;
        if (YearFromTime(current) == ym && MonthFromTime(current) == mn && DateFromTime(current) == 1) {
            int day = static_cast<int>(std::floor(current / JS::DateOperators::msPerDay));
            return day + date - 1;
        }
    }
    return std::numeric_limits<int>::quiet_NaN();
}

JS::Any MakeDate(JS::Any day, JS::Any time) {
    int d = JS::CONVERT::ToInteger(day);
    int t = JS::CONVERT::ToInteger(time);
    if (!std::isfinite(d) || !std::isfinite(t)) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(d * JS::DateOperators::msPerDay + t);
}

double MakeDate(int day, double time) {
    if (!std::isfinite(day) || !std::isfinite(time)) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return day * JS::DateOperators::msPerDay + time;
}

JS::Any TimeClip(JS::Any time) {
    int result = JS::CONVERT::ToInteger(time);
    if (!std::isfinite(result) || std::abs(result) > 8.64E15) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return JS::Any(result);
}

double TimeClip(double time) {
    if (!std::isfinite(time) || std::abs(time) > 8.64E15) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return time;
}
} // namespace JS::DateOperators