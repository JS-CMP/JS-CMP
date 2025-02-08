#ifndef JS_CMP_MATH_HPP
#define JS_CMP_MATH_HPP

#include "utils/Convert.hpp"

#include <vector>

namespace JS {
/**
 * @class Math
 * @brief Provides mathematical functions similar to JavaScript's Math object.
 *
 * The Math class offers a set of static methods that mimic the behavior of the JavaScript Math object.
 * Each function accepts a vector of JS::Any arguments to simulate JavaScript's dynamic typing.
 * The methods implement mathematical operations such as trigonometric functions, exponentiation,
 * logarithm, rounding, and random number generation.
 */
class Math {
public:
    /**
     * @brief Returns the absolute value of the given number.
     * @param args A vector containing a single JS::Any element representing the number.
     * @return A JS::Any containing the absolute value.
     */
    static JS::Any abs(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the arccosine (in radians) of the given number.
     * @param args A vector containing a single JS::Any element representing the number.
     * @return A JS::Any containing the arccosine.
     */
    static JS::Any acos(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the arcsine (in radians) of the given number.
     * @param args A vector containing a single JS::Any element representing the number.
     * @return A JS::Any containing the arcsine.
     */
    static JS::Any asin(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the arctangent (in radians) of the given number.
     * @param args A vector containing a single JS::Any element representing the number.
     * @return A JS::Any containing the arctangent.
     */
    static JS::Any atan(const std::vector<JS::Any>& args);

    /**
     * @brief Returns an approximation of the arctangent of the quotient y/x.
     *
     * The first argument is interpreted as y and the second as x. The signs of y and x are used
     * to determine the quadrant of the result. The returned value is in radians and lies within the range [-π, +π].
     *
     * @param args A vector containing two JS::Any elements: [y, x].
     * @return A JS::Any containing the result.
     */
    static JS::Any atan2(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the smallest integer greater than or equal to the given number.
     * @param args A vector containing a single JS::Any element representing the number.
     * @return A JS::Any containing the ceiling value.
     */
    static JS::Any ceil(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the cosine of the given angle (in radians).
     * @param args A vector containing a single JS::Any element representing the angle.
     * @return A JS::Any containing the cosine value.
     */
    static JS::Any cos(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the exponential of the given number.
     * @param args A vector containing a single JS::Any element representing the exponent.
     * @return A JS::Any containing e raised to the power of the given number.
     */
    static JS::Any exp(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the largest integer less than or equal to the given number.
     * @param args A vector containing a single JS::Any element representing the number.
     * @return A JS::Any containing the floor value.
     */
    static JS::Any floor(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the natural logarithm (base e) of the given number.
     * @param args A vector containing a single JS::Any element representing the number.
     * @return A JS::Any containing the logarithm.
     */
    static JS::Any log(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the maximum value among the given arguments.
     * @param args A vector of JS::Any elements representing numbers.
     * @return A JS::Any containing the maximum value.
     */
    static JS::Any max(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the minimum value among the given arguments.
     * @param args A vector of JS::Any elements representing numbers.
     * @return A JS::Any containing the minimum value.
     */
    static JS::Any min(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the result of raising the base to the power of the exponent.
     * @param args A vector containing two JS::Any elements: [base, exponent].
     * @return A JS::Any containing the result.
     */
    static JS::Any pow(const std::vector<JS::Any>& args);

    /**
     * @brief Returns a pseudo-random number in the interval [0, 1).
     * @param args A vector of JS::Any (arguments are ignored).
     * @return A JS::Any containing a pseudo-random number.
     */
    static JS::Any random(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the given number rounded to the nearest integer.
     * @param args A vector containing a single JS::Any element representing the number.
     * @return A JS::Any containing the rounded number.
     */
    static JS::Any round(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the sine of the given angle (in radians).
     * @param args A vector containing a single JS::Any element representing the angle.
     * @return A JS::Any containing the sine value.
     */
    static JS::Any sin(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the square root of the given number.
     * @param args A vector containing a single JS::Any element representing the number.
     * @return A JS::Any containing the square root.
     */
    static JS::Any sqrt(const std::vector<JS::Any>& args);

    /**
     * @brief Returns the tangent of the given angle (in radians).
     * @param args A vector containing a single JS::Any element representing the angle.
     * @return A JS::Any containing the tangent value.
     */
    static JS::Any tan(const std::vector<JS::Any>& args);

    // Read-only mathematical constants
    constexpr static double E = 2.7182818284590452354;
    constexpr static double LN10 = 2.302585092994046;
    constexpr static double LN2 = 0.6931471805599453;
    constexpr static double LOG2e = 2.302585092994046;
    constexpr static double LOG10E = 0.4342944819032518;
    constexpr static double PI = 3.1415926535897932;
    constexpr static double SQRT1_2 = 0.7071067811865476;
    constexpr static double SQRT2 = 1.4142135623730951;
};
} // namespace JS

#endif // JS_CMP_MATH_HPP
