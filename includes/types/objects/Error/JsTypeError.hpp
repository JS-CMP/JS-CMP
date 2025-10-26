#ifndef JSTYPEERROR_HPP
#define JSTYPEERROR_HPP

#include "types/objects/Error/JsError.hpp"

namespace JS {
/**
 * @class TypeError
 * @brief Represents a JavaScript TypeError in C++.
 *
 * The `TypeError` class represents an TypeError in C++. it inherits from `Error` and just have a different name.
 */
class TypeError : public JS::Error {
public:
    /**
     * @name Constructors
     * These constructors create a new Error with the given value
     */
    ///@{
    /** @brief Constructor that take a value */
    explicit TypeError(const JS::Any& value);
    ///@}

    /** @brief The destructor for the Error defaulted */
    ~TypeError() override = default;

    /**
     * @brief Static function to create the prototype properties object for an Error type
     * @return A shared pointer to an InternalObject with the prototype properties
     */
    static std::shared_ptr<JS::InternalObject>& getPrototypeProperties();

    /** @brief Get the instance of the global error. */
    [[nodiscard]] static std::shared_ptr<JS::Function> getConstructor();
};

} // namespace JS

#endif // JSTYPEERROR_HPP
