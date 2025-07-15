#ifndef JSSYNTAXERROR_HPP
#define JSSYNTAXERROR_HPP

#include "types/objects/Error/JsError.hpp"

namespace JS {
/**
 * @class SyntaxError
 * @brief Represents a JavaScript SyntaxError in C++.
 *
 * The `SyntaxError` class represents an SyntaxError in C++. it inherits from `Error` and just have a different name.
 */
class SyntaxError : public JS::Error {
public:
    /**
     * @name Constructors
     * These constructors create a new Error with the given value
     */
    ///@{
    /** @brief Default constructor initializes the SyntaxError */
    SyntaxError();
    /** @brief Constructor that take a value */
    explicit SyntaxError(const JS::Any& value);
    /** @brief Constructor for properties */
    explicit SyntaxError(const std::unordered_map<std::u16string, JS::Attribute>& properties);
    ///@}

    /** @brief The destructor for the Error defaulted */
    ~SyntaxError() override = default;

    /**
     * @brief Static function to create the prototype properties object for an Error type
     * @param name The name of the error type (e.g., "Error", "SyntaxError", etc.)
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

#endif // JSSYNTAXERROR_HPP
