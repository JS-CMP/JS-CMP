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
    Error();
    /** @brief Constructor that take a value */
    explicit Error(const JS::Any& value);
    /** @brief Constructor for properties */
    explicit Error(const std::unordered_map<std::string, JS::Attribute>& properties);
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
};

} // namespace JS


#endif //ERROR_HPP
