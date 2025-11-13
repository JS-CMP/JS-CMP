#ifndef JSRANGEERROR_HPP
#define JSRANGEERROR_HPP

#include "types/objects/Error/JsError.hpp"

namespace JS {

/**
 * @class RangeError
 * @brief Represents a JavaScript NativeError in C++.
 *
 * The `RangeError` class represents an NativeError in C++. it inherits from `Error` and just have a different name.
 */
class RangeError : public JS::Error {
public:
    /**
     * @name Constructors
     * These constructors create a new Error with the given value
     */
    ///@{
    /** @brief Constructor that take a value */
    explicit RangeError(const JS::Any& value);
    ///@}

    /** @brief The destructor for the Error defaulted */
    ~RangeError() override = default;

    /**
     * @brief Static function to create the prototype properties object for an Error type
     * @return A shared pointer to an InternalObject with the prototype properties
     */
    static std::shared_ptr<JS::InternalObject>& getPrototypeProperties();

    /** @brief Get the instance of the global error. */
    [[nodiscard]] static std::shared_ptr<JS::Function> getConstructor();
};

} // namespace JS

#endif // JSRANGEERROR_HPP
