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
    /** @brief Constructor that take a value */
    explicit SyntaxError(const JS::Any& value);
    ///@}

    /** @brief The destructor for the Error defaulted */
    ~SyntaxError() override = default;

    /**
     * @brief Static function to create the prototype properties object for an Error type
     * @param name The name of the error type (e.g., "Error", "SyntaxError", etc.)
     * @return A shared pointer to an InternalObject with the prototype properties
     */
    static std::shared_ptr<JS::InternalObject>& getPrototypeProperties();

    /** @brief Get the instance of the global error. */
    [[nodiscard]] static std::shared_ptr<JS::Function> getConstructor();
};

} // namespace JS

#endif // JSSYNTAXERROR_HPP
