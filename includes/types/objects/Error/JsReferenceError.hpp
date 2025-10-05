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
    ///@}

    /** @brief The destructor for the Error defaulted */
    ~ReferenceError() override = default;

    /**
     * @brief Static function to create the prototype properties object for an Error type
     * @param name The name of the error type (e.g., "Error", etc.)
     * @return A shared pointer to an InternalObject with the prototype properties
     */
    static std::shared_ptr<JS::InternalObject>& getPrototypeProperties();

    /** @brief Get the instance of the global error. */
    [[nodiscard]] static std::shared_ptr<JS::Function> getConstructor();
};

} // namespace JS

#endif // JSREFERENCEERROR_HPP
