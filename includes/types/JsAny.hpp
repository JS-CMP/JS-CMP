#ifndef JSANY_HPP
#define JSANY_HPP

#include "Types.hpp"
#include "internals/Operator.hpp"

namespace JS {
/**
 * @class Any
 * @brief Represents a JavaScript-like variant type in C++ that can hold multiple types of values.
 *
 * The `Any` class can hold values of various types, similar to JavaScript's dynamic typing.
 * It provides overloaded operators for arithmetic and comparison, making it easy to work
 * with in a JavaScript-like syntax.
 */
class Any : public Operator, public std::exception {
public:
    /**
     * @name Constructors
     * These constructors create a new Any object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the value to undefined */
    Any() : value(JS::Undefined{}) {}
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
    /** @brief Constructor for Operator */
    explicit Any(const Operator &any) : value(any.getValue()) {}
    /** @brief Copy constructor */
    Any(const JS::Any& v);
    /** @brief Move constructor */
    Any(const JS::Any&& v) noexcept;
    /** @brief Copy constructor */
    JS::Any& operator=(const JS::Any& other);
    /** @brief Move constructor */
    JS::Any& operator=(JS::Any&& other) noexcept;

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
    ///@}

    /** @name Getters
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Get the value of the property */
    JS::Any& get() override;
    /** @brief Get the value of the property */
    JS::Any get() const override;
    /** @brief Get the value of the property */
    JS::Value getValue() const override;
    ///@}

    /** @name Setters
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Set the value of the property */
    void set(const JS::Any& value) override;
    /** @brief Set the value of the property */
    void setValue(const JS::Value& value) override;
    ///@}

private:
    JS::Value value; /**< Holds the current value of this Any instance. */
};
} // namespace JS

#endif // JSANY_HPP