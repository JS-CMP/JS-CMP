#ifndef JS_CMP_JSNUMBER_HPP
#define JS_CMP_JSNUMBER_HPP

#include "internals/Object.hpp"

#include <cmath>

namespace JS {
/**
 * @class Number
 * @brief Represent the number object in C++
 *
 * The `Number` class represents a JavaScript-like number object in C++. It provides the different methods define in the
 * ECMA of the number. It also provides a method to get an internal object that hold the methods of the property
 * prototype.
 *
 * https://262.ecma-international.org/5.1/#sec-15.7
 */
class Number : public JS::InternalObject {
public:
    /**
     * @name Constructors
     * These constructors create a new Object with the given value
     */
    ///@{
    /** @brief Constructor that take a value */
    explicit Number(const JS::Any& value = JS::Any(0.0));
    ///@}

    /** @brief The destructor for the number defaulted */
    ~Number() override = default;

    /**
     * @name Methods to make prototype methods of the Object built-in
     */
    ///@{
    /** @brief Returns the prototype of the boolean https://262.ecma-international.org/5.1/#sec-15.7.4.2 */
    static JS::Any toString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the locale string of it https://262.ecma-international.org/5.1/#sec-15.7.4.3 */
    static JS::Any toLocaleString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the value of the number https://262.ecma-international.org/5.1/#sec-15.7.4.4 */
    static JS::Any valueOf(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Return a String containing this Number value represented in decimal fixed-point
     * https://262.ecma-international.org/5.1/#sec-15.7.4.5 */
    static JS::Any toFixed(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Return a String containing this Number value represented in decimal exponential notation
     * https://262.ecma-international.org/5.1/#sec-15.7.4.6 */
    static JS::Any toExponential(const JS::Any& thisArg, const JS::Any& args);
    /** @brief eturn a String containing this Number value represented either in decimal exponential notation
     * https://262.ecma-international.org/5.1/#sec-15.7.4.7 */
    static JS::Any toPrecision(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /** @brief Returns the content of the object formatted to a string. */
    [[nodiscard]] std::u16string getContent() const override;

    /** @brief Function to get the methods of the property prototype */
    static std::shared_ptr<JS::InternalObject>& getPrototypeProperties();


    /** @brief Get the instance of the global object. */
    [[nodiscard]] static std::shared_ptr<JS::Function> getConstructor();

    /**
     * @name Static variable of the Number object
     */
    ///@{
    constexpr static double MAX_VALUE =
        1.7976931348623157e308;                 /**< Represents the maximum value of a number in JavaScript */
    constexpr static double MIN_VALUE = 5e-324; /**< Represents the minimum value of a number in JavaScript */
    constexpr static double NaN = NAN;          /**< Represents NaN in JavaScript */
    constexpr static double NEGATIVE_INFINITY = -INFINITY; /**< Represents the negative infinity in JavaScript */
    constexpr static double POSITIVE_INFINITY = INFINITY;  /**< Represents the positive infinity in JavaScript */
    ///@}
};
} // namespace JS

#endif // JS_CMP_JSNUMBER_HPP
