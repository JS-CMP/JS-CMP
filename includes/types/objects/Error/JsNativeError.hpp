#ifndef JSNATIVEERROR_HPP
#define JSNATIVEERROR_HPP

#include "types/objects/Error/JsError.hpp"

namespace JS {

/**
 * @class NativeError
 * @brief Represents a JavaScript NativeError in C++.
 *
 * The `NativeError` class represents an NativeError in C++. it inherits from `Error` and just have a different name.
 */
class NativeError : public JS::Error {
public:
    /**
     * @name Constructors
     * These constructors create a new Error with the given value
     */
    ///@{
    /** @brief Default constructor initializes the NativeError */
    NativeError();
    /** @brief Constructor that take a value */
    explicit NativeError(const JS::Any& value);
    /** @brief Constructor for properties */
    explicit NativeError(const std::unordered_map<std::u16string, JS::Attribute>& properties);
    ///@}

    /** @brief The destructor for the Error defaulted */
    ~NativeError() override = default;

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
};

} // namespace JS

#endif // JSNATIVEERROR_HPP
