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
class Object : public JS::InternalObject, public std::enable_shared_from_this<JS::Object> {
public:
    /**
     * @name Constructors
     * These constructors create a new Object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the object with an empty map */
    Object();
    /** @brief Constructor for properties */
    explicit Object(std::unordered_map<std::string, JS::Any> properties);
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
     * @name Methods to make static methods of the Object built-in
     */
    ///@{
    /** @brief Returns the prototype of the object https://262.ecma-international.org/5.1/#sec-15.2.3.1 */
    static JS::Any getPrototypeOf(const std::vector<JS::Any>& args);
    /** @brief Returns a property descriptor of the object https://262.ecma-international.org/5.1/#sec-15.2.3.2 */
    static JS::Any getOwnPropertyDescriptor(const std::vector<JS::Any>& args);
    /** @brief Returns the property names of the object https://262.ecma-international.org/5.1/#sec-15.2.3.3 */
    static JS::Any getOwnPropertyNames(const std::vector<JS::Any>& args);
    /** @brief Creates a new object with the given prototype https://262.ecma-international.org/5.1/#sec-15.2.3.4 */
    static JS::Any create(const std::vector<JS::Any>& args);
    /** @brief Defines a property on the object https://262.ecma-international.org/5.1/#sec-15.2.3.5 */
    static JS::Any defineProperty(const std::vector<JS::Any>& args);
    /** @brief Defines multiple properties on the object https://262.ecma-international.org/5.1/#sec-15.2.3.6 */
    static JS::Any defineProperties(const std::vector<JS::Any>& args);
    /** @brief Seals the object https://262.ecma-international.org/5.1/#sec-15.2.3.7 */
    static JS::Any seal(const std::vector<JS::Any>& args);
    /** @brief Freezes the object https://262.ecma-international.org/5.1/#sec-15.2.3.8 */
    static JS::Any freeze(const std::vector<JS::Any>& args);
    /** @brief Prevents extensions on the object https://262.ecma-international.org/5.1/#sec-15.2.3.9 */
    static JS::Any preventExtensions(const std::vector<JS::Any>& args);
    /** @brief Checks if the object is sealed https://262.ecma-international.org/5.1/#sec-15.2.3.10 */
    static JS::Any isSealed(const std::vector<JS::Any>& args);
    /** @brief Checks if the object is frozen https://262.ecma-international.org/5.1/#sec-15.2.3.11 */
    static JS::Any isFrozen(const std::vector<JS::Any>& args);
    /** @brief Checks if the object is extensible https://262.ecma-international.org/5.1/#sec-15.2.3.12 */
    static JS::Any isExtensible(const std::vector<JS::Any>& args);
    /** @brief Returns the keys of the object https://262.ecma-international.org/5.1/#sec-15.2.3.13 */
    static JS::Any keys(const std::vector<JS::Any>& args);
    ///@}

    /**
     * @name Methods to make prototype methods of the Object built-in
     */
    ///@{
    /** @brief Returns the prototype of the object https://262.ecma-international.org/5.1/#sec-15.2.4.2 */
    JS::Any toString(const std::vector<JS::Any>& args);
    /** @brief Returns the locale string of it https://262.ecma-international.org/5.1/#sec-15.2.4.3 */
    JS::Any toLocaleString(const std::vector<JS::Any>& args);
    /** @brief Returns the value of the object https://262.ecma-international.org/5.1/#sec-15.2.4.4 */
    JS::Any valueOf(const std::vector<JS::Any>& args);
    /** @brief Returns if the object has a property https://262.ecma-international.org/5.1/#sec-15.2.4.5 */
    JS::Any hasOwnProperty(const std::vector<JS::Any>& args);
    /** @brief Returns if the object is in the prototype chain https://262.ecma-international.org/5.1/#sec-15.2.4.6 */
    JS::Any isPrototypeOf(const std::vector<JS::Any>& args);
    /** @brief Returns if the property is enumerable https://262.ecma-international.org/5.1/#sec-15.2.4.7 */
    JS::Any propertyIsEnumerable(const std::vector<JS::Any>& args);
    ///@}

    /**
     * @name Methods
     * These methods provide additional functionality to the object
     */
    ///@{
    /** @brief init functions in the properties, made for inherited class */
    virtual void init();
    ///@}
};

} // namespace JS

#endif // JSOBJECT_HPP
