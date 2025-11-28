#ifndef JS_DATE_HPP

#include "internals/Attribute.hpp"
#include "internals/Object.hpp"

namespace JS {
/**
 * @class Date
 * @brief Represents the date object in C++
 *
 * The `Date` class represents a JavaScript-like date object in C++. It provides the different methods defined in
 * the ECMAScript specification for the Date object. It also provides a method to get an internal object that holds
 * the methods of the property prototype.
 *
 * https://262.ecma-international.org/5.1/#sec-15.9
 */
class Date : public JS::InternalObject {
public:
    /**
     * @name Constructors
     * These constructors create a new Date object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the object with an empty map */
    Date();
    /** @brief Constructor that initializes the object with a given value */
    explicit Date(const JS::Any& value);
    /** @brief Constructor that initializes the object with a given set of properties */
    explicit Date(const std::unordered_map<std::u16string, JS::Any>& properties);
    /** @brief  */
    explicit Date(JS::Any year, JS::Any month, JS::Any day = JS::Any(), JS::Any hours = JS::Any(), JS::Any minutes = JS::Any(), JS::Any seconds = JS::Any(), JS::Any milliseconds = JS::Any());
    ///@}

    /** @brief The destructor for the object defaulted */
    ~Date() override = default;

    /**
     * @name Prototype methods of the Date object built-in
     */
    ///@{
    /** @brief Returns a string representing the specified Date object.
     * https://262.ecma-international.org/5.1/#sec-15.9.4.2*/
    static JS::Any toString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a string representing the specified Date object's date portion.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.3*/
    static JS::Any toDateString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a string representing the specified Date object's time portion.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.4*/
    static JS::Any toTimeString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a string with a language-sensitive representation of this date.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.5*/
    static JS::Any toLocaleString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a string with a language-sensitive representation of this date's date portion.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.6*/
    static JS::Any toLocaleDateString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a string with a language-sensitive representation of this date's time portion.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.7*/
    static JS::Any toLocaleTimeString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the primitive value of the specified Date object.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.8*/
    static JS::Any valueOf(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the number of milliseconds since 1 January 1970 00:00:00 UTC.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.9*/
    static JS::Any getTime(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the year of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.10*/
    static JS::Any getFullYear(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the year of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.11*/
    static JS::Any getUTCFullYear(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the month of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.12*/
    static JS::Any getMonth(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the month of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.13*/
    static JS::Any getUTCMonth(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the day of the month of the specified Date object.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.14*/
    static JS::Any getDate(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the day of the month of the specified Date object.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.15*/
    static JS::Any getUTCDate(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the day of the week of the specified Date object.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.16*/
    static JS::Any getDay(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the day of the week of the specified Date object.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.17*/
    static JS::Any getUTCDay(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the hour of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.18*/
    static JS::Any getHours(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the hour of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.19*/
    static JS::Any getUTCHours(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the minute of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.20*/
    static JS::Any getMinutes(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the minute of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.21*/
    static JS::Any getUTCMinutes(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the second of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.22*/
    static JS::Any getSeconds(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the second of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.23*/
    static JS::Any getUTCSeconds(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the millisecond of the specified Date object.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.24*/
    static JS::Any getMilliseconds(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the millisecond of the specified Date object.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.25*/
    static JS::Any getUTCMilliseconds(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the timezone offset of the specified Date object.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.26*/
    static JS::Any getTimezoneOffset(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the Date object to the time represented by a number.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.27*/
    static JS::Any setTime(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the milliseconds of the specified Date object.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.28*/
    static JS::Any setMilliseconds(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the milliseconds of the specified Date object.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.29*/
    static JS::Any setUTCMilliseconds(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the seconds of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.30*/
    static JS::Any setSeconds(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the seconds of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.31*/
    static JS::Any setUTCSeconds(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the minutes of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.32*/
    static JS::Any setMinutes(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the minutes of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.33*/
    static JS::Any setUTCMinutes(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the hours of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.34*/
    static JS::Any setHours(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the hours of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.35*/
    static JS::Any setUTCHours(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the date of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.36*/
    static JS::Any setDate(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the date of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.37*/
    static JS::Any setUTCDate(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the month of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.38*/
    static JS::Any setMonth(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the month of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.39*/
    static JS::Any setUTCMonth(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the year of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.40*/
    static JS::Any setFullYear(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Sets the year of the specified Date object. https://262.ecma-international.org/5.1/#sec-15.9.5.41*/
    static JS::Any setUTCFullYear(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a string representing the specified Date object in UTC time.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.42*/
    static JS::Any toUTCString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a string representing the specified Date object in ISO format.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.43*/
    static JS::Any toISOString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a string representing the specified Date object in JSON format.
     * https://262.ecma-international.org/5.1/#sec-15.9.5.44*/
    static JS::Any toJSON(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /**
     * @name Static methods of the Date object built-in
     */
    ///@{
    /** @brief Parses a string and returns the number of milliseconds since 1 January 1970 00:00:00 UTC.
     * https://262.ecma-international.org/5.1/#sec-15.9.4.2*/
    static JS::Any parse(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the number of milliseconds since 1 January 1970 00:00:00 UTC.
     * https://262.ecma-international.org/5.1/#sec-15.9.4.3*/
    static JS::Any UTC(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the number of milliseconds since 1 January 1970 00:00:00 UTC.
     * https://262.ecma-international.org/5.1/#sec-15.9.4.4*/
    static JS::Any now(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /** @brief Returns a shared pointer to the prototype properties of the Date object. */
    static std::shared_ptr<JS::InternalObject>& getPrototypeProperties();
};

namespace DateOperators {
/**
 * @name Absctract operators
 */
///@{
/** @brief Returns the number of days*/
int Day(double t);
/** @brief Returns the number of milliseconds since midnight. */
double TimeWithinDay(double t);
/** @brief Returns the number of days in the specified year. */
double DaysInYear(int y);
/** @brief Return the day of the year. */
double DayFromYear(int y);
/** @brief Return the time of the start of the year. */
double TimeFromYear(int y);
/** @brief Return a time value determined by a year */
int YearFromTime(double t);
/** @brief Return true if the specified year is a leap year. */
bool InLeapYear(double t);
/** @brief Return the month number (0-11). */
int MonthFromTime(double t);
/** @brief Return the day within the year (0-365). */
double DayWithinYear(double t);
/** @brief Return the date number (1-31). */
int DateFromTime(double t);
/** @brief Return the weekday (0-6, 0 is Sunday). */
int WeekDay(double t);
/** @brief Return the local time zone adjustment in milliseconds. */
double LocalTZA();
/** @brief Return the daylight saving time adjustment in milliseconds. */
double DaylightSavingTA(double t);
/** @brief Convert UTC time to local time. */
double LocalTime(double t);
/** @brief Convert local time to UTC. */
double UTC(double t);
/** @brief Return the hour (0-23). */
int HourFromTime(double t);
/** @brief Return the minute (0-59). */
int MinFromTime(double t);
/** @brief Return the second (0-59). */
int SecFromTime(double t);
/** @brief Return the millisecond (0-999). */
int msFromTime(double t);
/** @brief Calculate the number of ms from its four arguments. */
JS::Any MakeTime(JS::Any hour, JS::Any min, JS::Any sec, JS::Any ms);
/** @brief Calculate the number of ms from its four arguments. */
double MakeTime(double hour, double min, double sec, double ms);
/** @brief Calculate the number of ms from its three arguments. */
JS::Any MakeDay(JS::Any year, JS::Any month, JS::Any date);
/** @brief Calculate the number of ms from its three arguments. */
int MakeDay(int year, int month, int date);
/** @brief Calculate the number of ms from its two arguments */
JS::Any MakeDate(JS::Any day, JS::Any time);
/** @brief Calculate the number of ms from its two arguments */
double MakeDate(int day, double time);
/** @brief Clips the time value to the range 0 to 86400000. */
JS::Any TimeClip(JS::Any time);
/** @brief Clips the time value to the range 0 to 86400000. */
double TimeClip(double time);
///@}

/**
 * @name Constant Value
 */
///@{
static const double msPerDay = 86400000;
static const double msPerSecond = 1000;
static const double msPerMinute = 60000;
static const double msPerHour = 3600000;
static const int HoursPerDay = 24;
static const int MinutesPerHour = 60;
static const int SecondsPerMinute = 60;
///@}
} // namespace DateOperators
} // namespace JS
#endif // JS_CMP_JSSTRING_HPP
