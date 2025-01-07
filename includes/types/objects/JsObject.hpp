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
    static JS::Any getPropertyOf(const std::vector<JS::Any>& args);
    static JS::Any getOwnPropertyDescriptor(const std::vector<JS::Any>& args);
    static JS::Any getOwnPropertyNames(const std::vector<JS::Any>& args);
    static JS::Any create(const std::vector<JS::Any>& args);
    static JS::Any defineProperty(const std::vector<JS::Any>& args);
    static JS::Any defineProperties(const std::vector<JS::Any>& args);
    static JS::Any seal(const std::vector<JS::Any>& args);
    static JS::Any freeze(const std::vector<JS::Any>& args);
    static JS::Any preventExtensions(const std::vector<JS::Any>& args);
    static JS::Any isSealed(const std::vector<JS::Any>& args);
    static JS::Any isFrozen(const std::vector<JS::Any>& args);
    static JS::Any isExtensible(const std::vector<JS::Any>& args);
    static JS::Any keys(const std::vector<JS::Any>& args);
    /** @brief Constructor a new object */
    JS::Any constuctor(std::vector<JS::Any> args);
    ///@}
    /**
     * @name Methods
     * These methods provide additional functionality to the object
     */
    ///@{
    /** @brief init functions in the properties, made for inherited class */
    virtual void init();
    ///@}





private:
    std::vector<std::pair<std::string,FunctionType>> functions = {
        {"getPropertyOf", std::bind(&Object::getPropertyOf, std::placeholders::_1)},
        {"getOwnPropertyDescriptor", std::bind(&Object::getOwnPropertyDescriptor, std::placeholders::_1)},
        {"getOwnPropertyNames", std::bind(&Object::getOwnPropertyNames, std::placeholders::_1)},
        {"create", std::bind(&Object::create, std::placeholders::_1)},
        {"defineProperty", std::bind(&Object::defineProperty, std::placeholders::_1)},
        {"defineProperties", std::bind(&Object::defineProperties, std::placeholders::_1)},
        {"seal", std::bind(&Object::seal, std::placeholders::_1)},
        {"freeze", std::bind(&Object::freeze, std::placeholders::_1)},
        {"preventExtensions", std::bind(&Object::preventExtensions, std::placeholders::_1)},
        {"isSealed", std::bind(&Object::isSealed, std::placeholders::_1)},
        {"isFrozen", std::bind(&Object::isFrozen, std::placeholders::_1)},
        {"isExtensible", std::bind(&Object::isExtensible, std::placeholders::_1)},
        {"keys", std::bind(&Object::keys, std::placeholders::_1)},
    };
};
} // namespace JS

#endif // JSOBJECT_HPP
