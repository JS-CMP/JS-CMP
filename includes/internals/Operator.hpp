#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "Arguments.hpp"
#include "types/Types.hpp"
#include "utils/Declaration.hpp"

namespace JS {
/**
 * @class Operator
 * @brief Represents a JavaScript-like operator in C++ that can perform various operations on values.
 *
 * The `Operator` class provides a set of methods and operators that mimic JavaScript's behavior,
 * allowing for bitwise, arithmetic, logical, and comparison operations on values of type `Any`.
 */
class Operator : public std::exception {
public:
    /** @name Getters
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Get the value of the property */
    virtual JS::Any& get() = 0;
    /** @brief Get the value of the property */
    virtual JS::Any get() const = 0;
    /** @brief Get the value of the property */
    virtual JS::Value getValue() const = 0;
    ///@}

    /** @name Setters
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Set the value of the property */
    virtual void set(const JS::Any& value) = 0;
    /** @brief Set the value of the property */
    virtual void setValue(const JS::Value& value) = 0;
    ///@}

    /**
     * @name Bitwise Operators
     * These operators perform bitwise operations like in JavaScript
     */
    ///@{
    /** @brief Bitwise AND operator Any & T */
    DECLARE_1FUNC(JS::Any operator&, const);
    /** @brief Bitwise AND operator T & Any */
    DECLARE_2FUNC(friend JS::Any operator&, );

    /** @brief Bitwise OR operator Any | T */
    DECLARE_1FUNC(JS::Any operator|, const);
    /** @brief Bitwise OR operator T | Any */
    DECLARE_2FUNC(friend JS::Any operator|, );

    /** @brief Bitwise XOR operator Any ^ T */
    DECLARE_1FUNC(JS::Any operator^, const);
    /** @brief Bitwise XOR operator T ^ Any */
    DECLARE_2FUNC(friend JS::Any operator^, );

    /** @brief Bitwise NOT operator ~a */
    JS::Any operator~() const;

    /** @brief Logical NOT operator !a */
    JS::Any operator!() const;

    /** @brief Bitwise left shift operator Any << T */
    DECLARE_1FUNC(JS::Any operator<<, const);
    /** @brief Bitwise left shift operator T << Any */
    DECLARE_2FUNC(friend JS::Any operator<<, );

    /** @brief Bitwise right shift operator a >> b */
    DECLARE_1FUNC(JS::Any operator>>, const);
    /** @brief Bitwise right shift operator int >> Any */
    DECLARE_2FUNC(friend JS::Any operator>>, );
    ///@}

    /**
     * @name Arithmetic operators +
     */
    ///@{
    /** @brief Addition operator Any + T */
    DECLARE_1FUNC(JS::Any operator+, const);
    /** @brief Addition operator T + Any */
    DECLARE_2FUNC(friend JS::Any operator+, );
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
    /** @brief Subtraction operator Any - T */
    DECLARE_1FUNC(JS::Any operator-, const);
    /** @brief Subtraction operator T - Any */
    DECLARE_2FUNC(friend JS::Any operator-, );
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
    /** @brief Multiplication operator Any * T */
    DECLARE_1FUNC(JS::Any operator*, const);
    /** @brief Multiplication operator T * Any */
    DECLARE_2FUNC(friend JS::Any operator*, );
    ///@}

    /**
     * @name Division operators /
     * These operators perform division operations on the value of the `Any` object.
     */
    ///@{
    /** @brief Division operator Any / T */
    DECLARE_1FUNC(JS::Any operator/, const);
    /** @brief Division operator T / Any */
    DECLARE_2FUNC(friend JS::Any operator/, );
    ///@}

    /**
     * @name Modulus operators %
     * These operators perform modulus operations on the value of the `Any` object.
     */
    ///@{
    /** @brief Modulus operator Any % T */
    DECLARE_1FUNC(JS::Any operator%, const);
    /** @brief Modulus operator T % Any */
    DECLARE_2FUNC(friend JS::Any operator%, );
    ///@}

    /**
     * @name Binary Logical operators
     * These operators perform binary logical operations on the value of the 'Any' object.
     */
    ///@{
    /** @brief And operator Any && T*/
    DECLARE_1FUNC(JS::Any operator&&, const);
    /** @brief And operator T && Any */
    DECLARE_2FUNC(friend JS::Any operator&&, );

    /** @brief Or operator Any || T */
    DECLARE_1FUNC(JS::Any operator||, const);
    /** @brief Or operator T || Any */
    DECLARE_2FUNC(friend JS::Any operator||, );
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
    JS::Any operator<(const JS::Operator& other) const;
    /** @brief Comparaison operator a > b */
    JS::Any operator>(const JS::Operator& other) const;
    /** @brief Comparaison operator a == b */
    JS::Any operator==(const JS::Operator& other) const;
    /** @brief Comparaison operator a != b */
    JS::Any operator!=(const JS::Operator& other) const;
    ///@}

    /**
     * @name Accessors
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Accessors to call function stored in properties on an object stored in value */
    virtual JS::Any call(const JS::Any& args) const;
    /** @brief Accessors to constructor function stored in properties on an object stored in value */
    JS::Any constructor(const JS::Any& args) const;
    /** @brief Accessors to properties of object in stored in value */
    DECLARE_1FUNC(JS::PropertyProxy operator[], const);
    ///@}

    /**
     * @name Conversion operators
     * These operators convert the value of the `Any` object to another type.
     */
    ///@{
    /** @brief boolean conversion operator */
    operator bool(); // NOLINT(hicpp-explicit-conversions)
    ///@}

    /**
     * @brief Friend function for outputting `Any` object to a stream.
     * @param os Output stream.
     * @param any The `Any` object to output.
     * @return Output stream with `Any` value representation.
     */
    friend std::ostream& operator<<(std::ostream& os, const JS::Operator& any);

    /** @brief Exception handling method to get the error message */
    const char* what() const noexcept override;
};
} // namespace JS
#endif // OPERATOR_HPP
