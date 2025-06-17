#ifndef JSANY_HPP
#define JSANY_HPP

#include "Types.hpp"
#include "internals/Arguments.hpp"
#include "utils/Declaration.hpp"

namespace JS {
/**
 * @class Any
 * @brief Represents a JavaScript-like variant type in C++ that can hold multiple types of values.
 *
 * The `Any` class can hold values of various types, similar to JavaScript's dynamic typing.
 * It provides overloaded operators for arithmetic and comparison, making it easy to work
 * with in a JavaScript-like syntax.
 */
class Any : public std::exception {
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
    /** @brief Constructor for unsigned int */
    explicit Any(unsigned int v) : value(static_cast<double>(v)){};
    /** @brief Constructor for double */
    explicit Any(double v) : value(v){};
    /** @brief Constructor for Rope */
    explicit Any(Rope& v) : value(v){};
    /** @brief Constructor for Rope */
    explicit Any(Rope v) : value(v){};
    /** @brief Constructor for string */
    explicit Any(const std::string& v) : value(Rope(v)){};
    /** @brief Constructor for u16string */
    explicit Any(const std::u16string& v) : value(Rope(v)){};
    /** @brief Constructor for string */
    explicit Any(const char* v) : value(Rope(v)){};
    /** @brief Constructor for const char16_t */
    explicit Any(const char16_t* v) : value(Rope(v)){};
    /** @brief Constructor for bool */
    explicit Any(bool v) : value(v){};
    /** @brief Constructor for undefined */
    explicit Any(JS::Undefined v) : value(JS::Undefined{}){};
    /** @brief Constructor for null */
    explicit Any(JS::Null v) : value(JS::Null{}){};
    /** @brief Constructor for object taking a shared_ptr */
    explicit Any(std::shared_ptr<JS::InternalObject> v);
    explicit Any(const JS::Object& v);
    explicit Any(const JS::Array& v);
    explicit Any(const JS::Function& v);

    explicit Any(const JS::Number& v);
    explicit Any(const JS::Boolean& v);
    explicit Any(const JS::String& v);
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
    /** @brief Bitwise AND operator Any & T */
    DECLARE_1FUNC(JS::Any operator&, const);
    /** @brief Bitwise AND operator T & Any */
    DECLARE_2FUNC(friend JS::Any operator&, )

    /** @brief Bitwise OR operator Any | T */
    DECLARE_1FUNC(JS::Any operator|, const);
    /** @brief Bitwise OR operator T | Any */
    DECLARE_2FUNC(friend JS::Any operator|, )

    /** @brief Bitwise XOR operator Any ^ T */
    DECLARE_1FUNC(JS::Any operator^, const);
    /** @brief Bitwise XOR operator T ^ Any */
    DECLARE_2FUNC(friend JS::Any operator^, )

    /** @brief Bitwise NOT operator ~a */
    JS::Any operator~() const;

    /** @brief Logical NOT operator !a */
    JS::Any operator!() const;

    /** @brief Bitwise left shift operator Any << T */
    DECLARE_1FUNC(JS::Any operator<<, const);
    /** @brief Bitwise left shift operator T << Any */
    DECLARE_2FUNC(friend JS::Any operator<<, )

    /** @brief Bitwise right shift operator a >> b */
    DECLARE_1FUNC(JS::Any operator>>, const);
    /** @brief Bitwise right shift operator int >> Any */
    DECLARE_2FUNC(friend JS::Any operator>>, )
    ///@}

    /**
     * @name Arithmetic operators +
     */
    ///@{
    /** @brief Addition operator Any + T */
    DECLARE_1FUNC(JS::Any operator+, const);
    /** @brief Addition operator T + Any */
    DECLARE_2FUNC(friend JS::Any operator+, )
    ///@}

    /**
     * @name std::error override methods what
     */
    [[nodiscard]] const char* what() const noexcept override;


    /**
     * @name Unary + operator
     * This operator returns the value of the `Any` object as a number.
     */
    JS::Any operator+() const;
    /**
     * @name Unary - operator
     * This operator returns the negation of the value of the `Any` object.
     */
    JS::Any operator-() const;

    /**
     * @name Subtraction operators -
     * These operators perform subtraction operations on the value of the `Any` object.
     */
    ///@{
    /** @brief Subtraction operator Any - T */
    DECLARE_1FUNC(JS::Any operator-, const);
    /** @brief Subtraction operator T - Any */
    DECLARE_2FUNC(friend JS::Any operator-, )
    ///@}

    /**
     * @name Multiplication operators *
     * These operators perform multiplication operations on the value of the `Any` object.
     */
    ///@{
    /** @brief Multiplication operator Any * T */
    DECLARE_1FUNC(JS::Any operator*, const);
    /** @brief Multiplication operator T * Any */
    DECLARE_2FUNC(friend JS::Any operator*, )
    ///@}

    /**
     * @name Division operators /
     * These operators perform division operations on the value of the `Any` object.
     */
    ///@{
    /** @brief Division operator Any / T */
    DECLARE_1FUNC(JS::Any operator/, const);
    /** @brief Division operator T / Any */
    DECLARE_2FUNC(friend JS::Any operator/, )
    ///@}

    /**
     * @name Modulus operators %
     * These operators perform modulus operations on the value of the `Any` object.
     */
    ///@{
    /** @brief Modulus operator Any % T */
    DECLARE_1FUNC(JS::Any operator%, const);
    /** @brief Modulus operator T % Any */
    DECLARE_2FUNC(friend JS::Any operator%, )
    ///@}

    /**
     * @name Binary Logical operators
     * These operators perform binary logical operations on the value of the 'Any' object.
     */
    ///@{
    /** @brief And operator Any && T*/
    DECLARE_1FUNC(JS::Any operator&&, const);
    /** @brief And operator T && Any */
    DECLARE_2FUNC(friend JS::Any operator&&, )

    /** @brief Or operator Any || T */
    DECLARE_1FUNC(JS::Any operator||, const)
    /** @brief Or operator T || Any */
    DECLARE_2FUNC(friend JS::Any operator||, )
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
    DECLARE_1FUNC(JS::PropertyProxy operator[], const)
    ///@}

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