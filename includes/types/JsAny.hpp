#ifndef JSANY_HPP
#define JSANY_HPP

#include "Types.hpp"
#include "./objects/JsObject.hpp"

namespace JS {
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
    explicit Any(std::shared_ptr<JS::Object> v);
    explicit Any(const JS::Object& v);
    Any(const JS::Any& v);
    Any(const JS::Any&& v) noexcept;
    JS::Any& operator=(const JS::Any& other);
    JS::Any& operator=(JS::Any&& other) noexcept;
    ///@}

    /**
     * @name Arithmetic Operators
     * These operators perform basic arithmetic like in JavaScript
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
    /** @brief Addition operator a + b */
    JS::Any operator+(const JS::Any& other) const;
    /** @brief Subtraction operator a - b */
    JS::Any operator-(const JS::Any& other) const;
    /** @brief Multiplication operator a * b */
    JS::Any operator*(const JS::Any& other) const;
    /** @brief Division operator a / b */
    JS::Any operator/(const JS::Any& other) const;
    /** @brief Modulus operator a < b */
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
    template <typename... Args>
    JS::Any operator()(Args&&... args) {
        std::vector<JS::Any> arguments = { JS::Any(std::forward<Args>(args))... };
        return helper(arguments);
    }

    JS::Any& operator[](const std::string& key) const;
    JS::Any& operator[](size_t index) const;


    /**
     * @brief Friend function for outputting `Any` object to a stream.
     * @param os Output stream.
     * @param any The `Any` object to output.
     * @return Output stream with `Any` value representation.
     */
    friend std::ostream& operator<<(std::ostream& os, const JS::Any& any);

    /**
     * @brief Converts the `Any` object to a string.
     * @return String representation of the `Any` value.
     */
    [[nodiscard]] std::string toString();
private:
    JS::Value value; /**< Holds the current value of this Any instance. */
    JS::Any helper(std::vector<JS::Any>& args) const;
};
} // namespace JS

#endif // JSANY_HPP