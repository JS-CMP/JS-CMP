#ifndef JSANY_HPP
#define JSANY_HPP

#include "Types.hpp"
#include "internals/Arguments.hpp"

namespace JS {

template <typename T>
using JSAnyAmbiguous = std::enable_if_t<!std::is_same_v<T, JS::Any>, JS::Any>;

/**
 * @class Any
 * @brief Represents a JavaScript-like variant type in C++ that can hold multiple types of values.
 *
 * The `Any` class can hold values of various types, similar to JavaScript's dynamic typing.
 * It provides overloaded operators for arithmetic and comparison, making it easy to work
 * with in a JavaScript-like syntax.
 */
class Any {
public:
    /**
     * @name Constructors
     * These constructors create a new Any object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the value to undefined */
    Any() : value(JS::Undefined{}){};
    /** @brief Constructor for int */
    explicit Any(int v) : value(static_cast<double>(v)){};
    /** @brief Constructor for double */
    explicit Any(double v) : value(v){};
    /** @brief Constructor for Rope */
    explicit Any(Rope& v) : value(v){};
    /** @brief Constructor for Rope */
    explicit Any(Rope v) : value(v){};
    /** @brief Constructor for string */
    explicit Any(const std::string& v) : value(Rope(v)){};
    /** @brief Constructor for string */
    explicit Any(const char* v) : value(Rope(v)){};
    /** @brief Constructor for bool */
    explicit Any(bool v) : value(v){};
    /** @brief Constructor for undefined */
    explicit Any(JS::Undefined v) : value(JS::Undefined{}){};
    /** @brief Constructor for null */
    explicit Any(JS::Null v) : value(JS::Null{}){};
    /** @brief Constructor for object taking a shared_ptr */
    explicit Any(std::shared_ptr<JS::InternalObject> v);
    /** @brief Constructor for object */
    explicit Any(const JS::InternalObject& v);
    /** @brief Copy constructor */
    Any(const JS::Any& v);
    /** @brief Move constructor */
    Any(const JS::Any&& v) noexcept;
    /** @brief Copy constructor */
    JS::Any& operator=(const JS::Any& other);
    /** @brief Move constructor */
    JS::Any& operator=(JS::Any&& other) noexcept;
    /** @brief boolean conversion operator */
    operator bool(); // NOLINT(hicpp-explicit-conversions)
    ///@}

    /**
     * @name Bitewise Operators
     * These operators perform bitwise operations like in JavaScript
     */
    ///@{
    /** @brief Bitwise AND operator a & b */
    template <typename T>
    JS::Any operator&(T other) const;
    /** @brief Bitwise AND operator T & Any */
    template <typename T>
    friend JSAnyAmbiguous<T> operator&(T value, JS::Any const& any);

    /** @brief Bitwise OR operator a | b */
    template <typename T>
    JS::Any operator|(T other) const;
    /** @brief Bitwise OR operator T | Any */
    template <typename T>
    friend JSAnyAmbiguous<T> operator|(T value, JS::Any const& any);

    /** @brief Bitwise XOR operator a ^ b */
    template <typename T>
    JS::Any operator^(T other) const;
    /** @brief Bitwise XOR operator T ^ Any */
    template <typename T>
    friend JSAnyAmbiguous<T> operator^(T value, JS::Any const& any);

    /** @brief Bitwise NOT operator ~a */
    JS::Any operator~() const;

    /** @brief Logical NOT operator !a */
    JS::Any operator!() const;

    /** @brief Bitwise left shift operator a << b */
    template <typename T>
    JS::Any operator<<(T other) const;
    /** @brief Bitwise left shift operator T << Any */
    template <typename T>
    friend JSAnyAmbiguous<T> operator<<(T value, JS::Any const& any);

    /** @brief Bitwise right shift operator a >> b */
    template <typename T>
    JS::Any operator>>(T other) const;
    /** @brief Bitwise right shift operator int >> Any */
    template <typename T>
    friend JSAnyAmbiguous<T> operator>>(T value, JS::Any const& any);

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
    JS::Any operator+(JS::Undefined /*unused*/) const;
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
    friend JS::Any operator+(JS::Undefined /*unused*/, JS::Any const& any);
    ///@}

    /**
     * @name Unary + operator
     * This operator returns the value of the `Any` object as a number.
     */
    JS::Any operator+() const;

    /**
     * @name Subtraction operators -
     * These operators perform subtraction operations on the value of the `Any` object.
     */
    ///@{
    /** @brief Subtraction operator Any - Any */
    template <typename T>
    JS::Any operator-(T other) const;
    /** @brief Subtraction operator Any - Undefined */
    JS::Any operator-(JS::Undefined /*unused*/) const;
    /** @brief Subtraction operator T - Any */
    template <typename T>
    friend JSAnyAmbiguous<T> operator-(T value, JS::Any const& any);
    /** @brief Subtraction operator Undefined - Any */
    friend JS::Any operator-(JS::Undefined /*unused*/, JS::Any const& any);
    ///@}

    /**
     * @name Unary - operator
     * This operator returns the negation of the value of the `Any` object.
     */
    JS::Any operator-() const;

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
    JS::Any operator*(JS::Undefined /*unused*/) const;
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
    JS::Any operator/(JS::Undefined /*unused*/) const;
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
    JS::Any operator%(JS::Undefined /*unused*/) const;
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
     * @name Binary Logical operators
     * These operators perform binary logical operations on the value of the 'Any' object.
     */
    ///@{
    /** @brief And operator Any && T*/
    template <typename T>
    JS::Any operator&&(T other) const;
    /** @brief And operator T && Any */
    template <typename T>
    friend JSAnyAmbiguous<T> operator&&(T value, JS::Any const& any);

    /** @brief Or operator Any || T */
    template <typename T>
    JS::Any operator||(T other) const;
    /** @brief Or operator T || Any */
    template <typename T>
    friend JSAnyAmbiguous<T> operator||(T value, JS::Any const& any);
    ///@}

    /**
     * @name Arithmetic operators
     * These operators perform arithmetic operations on the value of the `Any` object.
     */
    ///@{
    /** @brief Addition operator ++a */
    JS::Any& operator++();
    /** @brief Addition operator a++ */
    JS::Any operator++(int);
    /** @brief Subtraction operator --a */
    JS::Any& operator--();
    /** @brief Subtraction operator a-- */
    JS::Any operator--(int);
    ///@}

    /**
     * @name Comparaison operators
     * These operators compare the value of the `Any` object with another `Any` object.
     */
    /** @brief Comparaison operator a < b */
    JS::Any operator<(const JS::Any& other) const;
    /** @brief Comparaison operator a > b */
    JS::Any operator>(const JS::Any& other) const;
    /** @brief Comparaison operator a == b */
    JS::Any operator==(const JS::Any& other) const;
    /** @brief Comparaison operator a != b */
    JS::Any operator!=(const JS::Any& other) const;
    ///@}

    // todo: remove when custom operator merged
    /** @brief strict equality operator a === b */
    [[nodiscard]] bool strictEq(const JS::Any& other) const;
    /** @brief strict inequality operator a !== b */
    [[nodiscard]] bool strictNeq(const JS::Any& other) const;

    /**
     * @name Accessors
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Accessors to call function stored in properties on an object stored in value */
    template <typename... Args>
    JS::Any operator()(Args&&... args) {
        return call(JS::Arguments::CreateArgumentsObject(std::vector<JS::Any>{std::move(args)...}));
    }
    /** @brief Accessors to call function stored in properties on an object stored in value */
    JS::Any call(const JS::Any& args) const;

    /** @brief Accessors to constructor function stored in properties on an object stored in value */
    JS::Any constructor(const JS::Any& args) const;

    /** @brief Accessors to properties of object in stored in value */
    template <typename T>
    JS::PropertyProxy operator[](T key) const;

    ///@}

    /**
     * @name Conversion operators
     * These operators convert the value of the `Any` object to another type.
     */
    ///@{

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

private:
    JS::Value value; /**< Holds the current value of this Any instance. */
};
} // namespace JS

#endif // JSANY_HPP