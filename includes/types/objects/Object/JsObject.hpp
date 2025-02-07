#ifndef JSOBJECT_HPP
#define JSOBJECT_HPP

#include "internals/Attribute.hpp"
#include "internals/Object.hpp"
#include "internals/PropertyProxy.hpp"

namespace JS {

/**
 * @class Object
 * @brief Represents a JavaScript-like object in C++.
 *
 * The `Object` class represents a JavaScript-like object in C++. It provides methods to access and modify properties of
 * the object. It also provides methods to check if a property exists, and if it's callable.
 */
class Object : public JS::InternalObject {
public:
    /**
     * @name Constructors
     * These constructors create a new Object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the object with an empty map */
    Object();
    /** @brief Constructor for properties */
    explicit Object(const std::unordered_map<std::string, JS::Any>& properties);
    /** @brief InternalObject constructor */
    explicit Object(const JS::InternalObject&& internalObject);
    /** @brief Attribute constructor */
    explicit Object(const JS::Attribute& attribute);
    ///@}

    /**
     * @brief The destructor for the object defaulted
     */
    ~Object() override = default;
};

} // namespace JS

#endif // JSOBJECT_HPP
