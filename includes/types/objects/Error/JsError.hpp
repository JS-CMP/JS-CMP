#ifndef ERROR_HPP
#define ERROR_HPP

#include "internals/Object.hpp"

namespace JS {
/**
 * @class Error
 * @brief Represents a JavaScript Error in C++.
 *
 * The `Error` class represents an Error in C++. It will be inherited by all types of error like
 * `SyntaxError`, `ReferenceError`, `TypeError`, etc.
 */
class Error : public JS::InternalObject {
public:
    /**
     * @name Constructors
     * These constructors create a new Error with the given value
     */
    ///@{
    /** @brief Default constructor initializes the Error */
    explicit Error(const std::shared_ptr<JS::InternalObject>& prototype = nullptr);
    /** @brief Constructor that take a value */
    explicit Error(const JS::Any& value, const std::shared_ptr<JS::InternalObject>& prototype = nullptr);
    /** @brief Constructor for properties */
    explicit Error(const std::unordered_map<std::u16string, JS::Attribute>& properties,
                   const std::shared_ptr<JS::InternalObject>& prototype = nullptr);
    ///@}

    /** @brief The destructor for the Error defaulted */
    ~Error() override = default;

    /**
     * @name Methods to make prototype methods of the Error
     */
    ///@{
    /** @brief Returns the prototype of the boolean https://262.ecma-international.org/5.1/#sec-15.7.4.2 */
    static JS::Any toString(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /**
     * @brief Static function to create the prototype properties object for an Error type
     * @param name The name of the error type (e.g., "Error", "NativeError", etc.)
     * @return A shared pointer to an InternalObject with the prototype properties
     */
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
};

} // namespace JS

#endif // ERROR_HPP
