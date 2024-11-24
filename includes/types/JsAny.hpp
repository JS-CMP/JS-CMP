#ifndef JSANY_HPP
#define JSANY_HPP

#include "../class/Rope/Rope.hpp"

#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <variant>

namespace JS {

class Any;

/**
 * Enum representing the types that can be held by an instance of JS::Any.
 */
enum Types {
    NUMBER,    /**< Represents a numeric type (double). */
    STRING,    /**< Represents a string type. */
    BOOL,      /**< Represents a boolean type. */
    FUNCTION,  /**< Represents a function type. */
    UNDEFINED, /**< Represents an undefined type. */
    NULL_TYPE  /**< Represents a null type. */
};

using Function = std::function<JS::Any(const std::vector<JS::Any>&)>; /**< Type alias for JavaScript-like functions. */
using Object =
    std::unordered_map<std::string, std::shared_ptr<JS::Any>>; /**< Type alias for an object (dictionary) type. */
/** @cond */                                                   // Hide from Doxygen
struct Undefined {};                                           /**< Represents an undefined value. */
/** @endcond */
using Null = std::nullptr_t; /**< Type alias for a null value. */

using Value = std::variant<double, Rope, bool, JS::Function, JS::Undefined,
                           JS::Null>; /**< Union of all possible types Any can hold. */

/**
 * @class Any
 * @brief Represents a JavaScript-like variant type in C++ that can hold multiple types of values.
 *
 * The `Any` class can hold values of various types, similar to JavaScript's dynamic typing.
 * It provides overloaded operators for arithmetic and comparison, making it easy to work
 * with in a JavaScript-like syntax.
 */
class Any {
private:
    JS::Value value; /**< Holds the current value of this Any instance. */

public:
    /**
     * @name Constructors
     * These constructors create a new Any object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the value to undefined */
    Any() : value(JS::Undefined{}) {};
    /** @brief Constructor for int */
    explicit Any(int v) : value(static_cast<double>(v)) {};
    /** @brief Constructor for double */
    explicit Any(double v) : value(v) {};
    /** @brief Constructor for Rope */
    explicit Any(Rope& v) : value(v) {};
    /** @brief Constructor for Rope */
    explicit Any(Rope v) : value(v) {};
    /** @brief Constructor for string */
    explicit Any(const std::string& v) : value(Rope(v)) {};
    /** @brief Constructor for string */
    explicit Any(const char* v) : value(Rope(v)) {};
    /** @brief Constructor for bool */
    explicit Any(bool v) : value(v) {};
    /** @brief Constructor for function */
    explicit Any(JS::Function v) : value(v) {};
    /** @brief Constructor for undefined */
    explicit Any(JS::Undefined v) : value(JS::Undefined{}) {};
    /** @brief Constructor for null */
    explicit Any(JS::Null v) : value(JS::Null{}) {};
    ///@}

    /**
     * @name Arithmetic operators +
     */
    ///@{
    /** @brief Addition operator Any + Any */
    JS::Any operator+(const JS::Any& other) const;
    /** @brief Addition operator Any + int */
    JS::Any operator+(int value) const;
    /** @brief Addition operator Any + double */
    JS::Any operator+(double value) const;
    /** @brief Addition operator Any + string */
    JS::Any operator+(const char* value) const;
    /** @brief Addition operator Any + bool */
    JS::Any operator+(bool value) const;
    /** @brief Addition operator Any + null */
    JS::Any operator+(JS::Null) const;
    /** @brief Addition operator Any + undefined */
    JS::Any operator+(JS::Undefined) const;
    /** @brief Addition operator int + Any */
    friend JS::Any operator+(int value, JS::Any const& any);
    /** @brief Addition operator double + Any */
    friend JS::Any operator+(double value, JS::Any const& any);
    /** @brief Addition operator string + Any */
    friend JS::Any operator+(const char* value, JS::Any const& any);
    /** @brief Addition operator bool + Any */
    friend JS::Any operator+(bool value, JS::Any const& any);
    /** @brief Addition operator null + Any */
    friend JS::Any operator+(JS::Null, JS::Any const& any);
    /** @brief Addition operator undefined + Any */
    friend JS::Any operator+(JS::Undefined, JS::Any const& any);
    ///@}

    /**
     * @name Subtraction operators -
     * These operators perform subtraction operations on the value of the `Any` object.
     */
    ///@{
    /** @brief Subtraction operator Any - Any */
    JS::Any operator-(const JS::Any& other) const;
    /** @brief Subtraction operator Any - int */
    JS::Any operator-(int value) const;
    /** @brief Subtraction operator Any - double */
    JS::Any operator-(double value) const;
    /** @brief Subtraction operator Any - string */
    JS::Any operator-(const char* value) const;
    /** @brief Subtraction operator Any - bool */
    JS::Any operator-(bool value) const;
    /** @brief Subtraction operator Any - null */
    JS::Any operator-(JS::Null) const;
    /** @brief Subtraction operator Any - undefined */
    JS::Any operator-(JS::Undefined) const;
    /** @brief Subtraction operator int - Any */
    friend JS::Any operator-(int value, JS::Any const& any);
    /** @brief Subtraction operator double - Any */
    friend JS::Any operator-(double value, JS::Any const& any);
    /** @brief Subtraction operator string - Any */
    friend JS::Any operator-(const char* value, JS::Any const& any);
    /** @brief Subtraction operator bool - Any */
    friend JS::Any operator-(bool value, JS::Any const& any);
    /** @brief Subtraction operator null - Any */
    friend JS::Any operator-(JS::Null, JS::Any const& any);
    /** @brief Subtraction operator undefined - Any */
    friend JS::Any operator-(JS::Undefined, JS::Any const& any);
    ///@}

    /**
     * @name Multiplication operators *
     * These operators perform multiplication operations on the value of the `Any` object.
     */
    ///@{
    /** @brief Multiplication operator Any * Any */
    JS::Any operator*(const JS::Any& other) const;
    /** @brief Multiplication operator Any * int */
    JS::Any operator*(int value) const;
    /** @brief Multiplication operator Any * double */
    JS::Any operator*(double value) const;
    /** @brief Multiplication operator Any * string */
    JS::Any operator*(const char* value) const;
    /** @brief Multiplication operator Any * bool */
    JS::Any operator*(bool value) const;
    /** @brief Multiplication operator Any * null */
    JS::Any operator*(JS::Null) const;
    /** @brief Multiplication operator Any * undefined */
    JS::Any operator*(JS::Undefined) const;
    /** @brief Multiplication operator int * Any */
    friend JS::Any operator*(int value, JS::Any const& any);
    /** @brief Multiplication operator double * Any */
    friend JS::Any operator*(double value, JS::Any const& any);
    /** @brief Multiplication operator string * Any */
    friend JS::Any operator*(const char* value, JS::Any const& any);
    /** @brief Multiplication operator bool * Any */
    friend JS::Any operator*(bool value, JS::Any const& any);
    /** @brief Multiplication operator null * Any */
    friend JS::Any operator*(JS::Null value, JS::Any const& any);
    /** @brief Multiplication operator undefined * Any */
    friend JS::Any operator*(JS::Undefined value, JS::Any const& any);
    ///@}

    /**
     * @name Division operators /
     * These operators perform division operations on the value of the `Any` object.
     */
    ///@{
    /** @brief Division operator Any / Any */
    JS::Any operator/(const JS::Any& other) const;
    /** @brief Division operator Any / int */
    JS::Any operator/(int value) const;
    /** @brief Division operator Any / double */
    JS::Any operator/(double value) const;
    /** @brief Division operator Any / string */
    JS::Any operator/(const char* value) const;
    /** @brief Division operator Any / bool */
    JS::Any operator/(bool value) const;
    /** @brief Division operator Any / null */
    JS::Any operator/(JS::Null) const;
    /** @brief Division operator Any / undefined */
    JS::Any operator/(JS::Undefined) const;
    /** @brief Division operator int / Any */
    friend JS::Any operator/(int value, JS::Any const& any);
    /** @brief Division operator double / Any */
    friend JS::Any operator/(double value, JS::Any const& any);
    /** @brief Division operator string / Any */
    friend JS::Any operator/(const char* value, JS::Any const& any);
    /** @brief Division operator bool / Any */
    friend JS::Any operator/(bool value, JS::Any const& any);
    /** @brief Division operator null / Any */
    friend JS::Any operator/(JS::Null value, JS::Any const& any);
    /** @brief Division operator undefined / Any */
    friend JS::Any operator/(JS::Undefined value, JS::Any const& any);
    ///@}

    /**
     * @name Modulus operators %
     * These operators perform modulus operations on the value of the `Any` object.
     */
    ///@{
    /** @brief Modulus operator Any % Any */
    JS::Any operator%(const JS::Any& other) const;
    /** @brief Modulus operator Any % int */
    JS::Any operator%(int value) const;
    /** @brief Modulus operator Any % double */
    JS::Any operator%(double value) const;
    /** @brief Modulus operator Any % string */
    JS::Any operator%(const char* value) const;
    /** @brief Modulus operator Any % bool */
    JS::Any operator%(bool value) const;
    /** @brief Modulus operator Any % null */
    JS::Any operator%(JS::Null) const;
    /** @brief Modulus operator Any % undefined */
    JS::Any operator%(JS::Undefined) const;
    /** @brief Modulus operator int % Any */
    friend JS::Any operator%(int value, JS::Any const& any);
    /** @brief Modulus operator double % Any */
    friend JS::Any operator%(double value, JS::Any const& any);
    /** @brief Modulus operator string % Any */
    friend JS::Any operator%(const char* value, JS::Any const& any);
    /** @brief Modulus operator bool % Any */
    friend JS::Any operator%(bool value, JS::Any const& any);
    /** @brief Modulus operator null % Any */
    friend JS::Any operator%(JS::Null value, JS::Any const& any);
    /** @brief Modulus operator undefined % Any */
    friend JS::Any operator%(JS::Undefined value, JS::Any const& any);
    ///@}

    /**
     * @name Arithmetic operators
     * These operators perform arithmetic operations on the value of the `Any` object.
     */
    ///@{
    /** @brief Addition operator ++a */
    JS::Any& operator++();
    /** @brief Addition operator a++ */
    const JS::Any& operator++(int);
    /** @brief Subtraction operator --a */
    JS::Any& operator--();
    /** @brief Subtraction operator a-- */
    const JS::Any& operator--(int);
    ///@}

    /**
     * @name Comparison operators
     * These operators compare the value of the `Any` object with another `Any` object.
     */
    /** @brief Comparison operator a < b */
    bool operator<(const JS::Any& other) const;
    /** @brief Modulus operator a > b */
    bool operator>(const JS::Any& other) const;
    /** @brief Modulus operator a == b */
    bool operator==(const JS::Any& other) const;
    ///@}
    /**
     * @brief Calls the function stored in the `Any` object with the given arguments.
     * @param args The arguments to pass to the function.
     * @return The result of the function call.
     */
    JS::Any operator()(std::vector<JS::Any>& args);

    /**
     * @brief Friend function for outputting `Any` object to a stream.
     * @param os Output stream.
     * @param any The `Any` object to output.
     * @return Output stream with `Any` value representation.
     */
    friend std::ostream& operator<<(std::ostream& os, const JS::Any& any);

    /**
     * @brief Gets the value of the `Any` object.
     * @return The value of the `Any` object.
     */
    [[nodiscard]] JS::Value getValue() const;
    /**
     * @brief Converts the `Any` object to a string.
     * @return String representation of the `Any` value.
     */
    [[nodiscard]] std::string toString() const;
};
} // namespace JS

#endif // JSANY_HPP