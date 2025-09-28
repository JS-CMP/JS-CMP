#ifndef JSREFERENCEERROR_HPP
#define JSREFERENCEERROR_HPP

#include "types/objects/Error/JsError.hpp"

namespace JS {
/**
 * @class ReferenceError
 * @brief Represents a JavaScript ReferenceError in C++.
 *
 * The `ReferenceError` class represents an ReferenceError in C++. it inherits from `Error` and just have a different
 * name.
 */
class ReferenceError : public JS::Error {
public:
    /**
     * @name Constructors
     * These constructors create a new Error with the given value
     */
    ///@{
    /** @brief Constructor that take a value */
    explicit ReferenceError(const JS::Any& value);
    /** @brief Constructor for properties */
    explicit ReferenceError(const std::unordered_map<std::u16string, JS::Attribute>& properties);
    ///@}

    /** @brief The destructor for the Error defaulted */
    ~ReferenceError() override = default;

    /**
     * @brief Static function to create the prototype properties object for an Error type
     * @param name The name of the error type (e.g., "Error", etc.)
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

    /** @brief Get the instance of the global error. */
    [[nodiscard]] static std::shared_ptr<JS::Function> getConstructor();
};

} // namespace JS

#endif // JSREFERENCEERROR_HPP
