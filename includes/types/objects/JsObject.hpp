#ifndef JSOBJECT_HPP
#define JSOBJECT_HPP

#include "internals/Attribute.hpp"
#include "internals/Object.hpp"

namespace JS {

/**
 * @class Object
 * @brief Represents a JavaScript-like object in C++.
 *
 * The `Object` class represents a JavaScript-like object in C++. It provides methods to access and modify properties of
 * the object. It also provides methods to check if a property exists, and if it's callable.
 */
class Object : public JS::InternalObject, public std::enable_shared_from_this<JS::Object> {
public:
    /**
     * @name Constructors
     * These constructors create a new Object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the object with an empty map */
    Object();
    /** @brief InternalObject constructor */
    explicit Object(const JS::InternalObject& internalObject);
    /** @brief Attribute constructor */
    explicit Object(const JS::Attribute& attribute);
    ///@}

    /**
     * @brief The destructor for the object defaulted
     */
    ~Object() = default;


    /**
     * Call operator for the object
     * @param args The arguments to pass to the function
     * @return The result of the function call
     */
    JS::Any operator()(const std::vector<JS::Any>& args);

    /**
     * @name Methods to make static methods of the Object built-in
     */
    ///@{
    /** @brief Get the prototype of the object */
    JS::Any getPrototype();
    /** @brief Get the property descriptor of the object */
    JS::Any getPropertyDescriptor(std::string key);
    /** @brief Get the property names of the object */
    JS::Any create();
    /** @brief Create a new object */
    JS::Any create(std::shared_ptr<JS::Object> properties);
    ///@}

    /**
     * @name Methods
     * These methods provide additional functionality to the object
     */
    ///@{
    /** @brief init functions in the properties, made for inherited class */
    virtual void init();
};
} // namespace JS

#endif // JSOBJECT_HPP
