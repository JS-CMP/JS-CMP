#ifndef JS_CMP_JSBOOLEAN_HPP
#define JS_CMP_JSBOOLEAN_HPP

#include "internals/Object.hpp"

namespace JS {
/**
 * @class Boolean
 * @brief Represent the boolean object in C++
 *
 * The `Boolean` class represents a JavaScript-like boolean object in C++. It provides the different methods define in
 * the ECMA of the boolean. It also provides a method to get an internal object that hold the methods of the property
 * prototype.
 *
 * https://262.ecma-international.org/5.1/#sec-15.6
 */
class Boolean : public JS::InternalObject {
public:
    /**
     * @name Constructors
     * These constructors create a new Object with the given value
     */
    ///@{
    /** @brief Constructor that take a value */
    explicit Boolean(const JS::Any& value = Any(false));
    ///@}

    /** @brief The destructor for the boolean defaulted */
    ~Boolean() override = default;

    /**
     * @name Methods to make prototype methods of the Object built-in
     */
    ///@{
    /** @brief Returns the prototype of the boolean https://262.ecma-international.org/5.1/#sec-15.6.4.2 */
    static JS::Any toString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the value of the boolean https://262.ecma-international.org/5.1/#sec-15.6.4.3 */
    static JS::Any valueOf(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    [[nodiscard]] std::u16string getContent() const override;

    /** @brief Function to get the methods of the property prototype */
    static std::shared_ptr<JS::InternalObject>& getPrototypeProperties();

    /**
     * @name Methods that represent the functions needed for calling and constructing
     */
    ///@{
    /** @brief Function that represent the constructor of the Object */
    static Any internal_constructor(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Function that is used when object is call as a function */
    static Any internal_call(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /** @brief Get the instance of the global error. */
    [[nodiscard]] static std::shared_ptr<JS::Function> getConstructor();
};
} // namespace JS

#endif // JS_CMP_JSBOOLEAN_HPP
