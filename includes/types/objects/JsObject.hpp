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
    /** @brief Constructor for properties with a given set of properties */
    explicit Object(const std::unordered_map<std::u16string, JS::Any>& properties = {});
    ///@}

    /** @brief The destructor for the object defaulted */
    ~Object() override = default;

    /**
     * @name Methods to make static methods of the Object built-in
     */
    ///@{
    /** @brief Returns the prototype of the object https://262.ecma-international.org/5.1/#sec-15.2.3.1 */
    static JS::Any getPrototypeOf(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns a property descriptor of the object https://262.ecma-international.org/5.1/#sec-15.2.3.2 */
    static JS::Any getOwnPropertyDescriptor(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the property names of the object https://262.ecma-international.org/5.1/#sec-15.2.3.3 */
    static JS::Any getOwnPropertyNames(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Creates a new object with the given prototype https://262.ecma-international.org/5.1/#sec-15.2.3.4 */
    static JS::Any create(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Defines a property on the object https://262.ecma-international.org/5.1/#sec-15.2.3.5 */
    static JS::Any defineProperty(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Defines multiple properties on the object https://262.ecma-international.org/5.1/#sec-15.2.3.6 */
    static JS::Any defineProperties(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Seals the object https://262.ecma-international.org/5.1/#sec-15.2.3.7 */
    static JS::Any seal(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Freezes the object https://262.ecma-international.org/5.1/#sec-15.2.3.8 */
    static JS::Any freeze(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Prevents extensions on the object https://262.ecma-international.org/5.1/#sec-15.2.3.9 */
    static JS::Any preventExtensions(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Checks if the object is sealed https://262.ecma-international.org/5.1/#sec-15.2.3.10 */
    static JS::Any isSealed(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Checks if the object is frozen https://262.ecma-international.org/5.1/#sec-15.2.3.11 */
    static JS::Any isFrozen(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Checks if the object is extensible https://262.ecma-international.org/5.1/#sec-15.2.3.12 */
    static JS::Any isExtensible(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the keys of the object https://262.ecma-international.org/5.1/#sec-15.2.3.13 */
    static JS::Any keys(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /** @brief Function to get the methods of the property prototype */
    static std::shared_ptr<JS::InternalObject>& getPrototypeProperties(const std::shared_ptr<JS::InternalObject>& prototype = nullptr);

    /**
     * @name Methods to make prototype methods of the Object built-in
     */
    ///@{
    /** @brief Returns the stringified version of the object https://262.ecma-international.org/5.1/#sec-15.2.4.2 */
    static JS::Any toString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the locale string of it https://262.ecma-international.org/5.1/#sec-15.2.4.3 */
    static JS::Any toLocaleString(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns the value of the object https://262.ecma-international.org/5.1/#sec-15.2.4.4 */
    static JS::Any valueOf(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns if the object has a property https://262.ecma-international.org/5.1/#sec-15.2.4.5 */
    static JS::Any hasOwnProperty(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns if the object is in the prototype chain https://262.ecma-international.org/5.1/#sec-15.2.4.6 */
    static JS::Any isPrototypeOf(const JS::Any& thisArg, const JS::Any& args);
    /** @brief Returns if the property is enumerable https://262.ecma-international.org/5.1/#sec-15.2.4.7 */
    static JS::Any propertyIsEnumerable(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /**
     * @name Methods that represent the functions needed for calling and constructing
     */
    ///@{
    /** @brief Function that represent the constructor of the Object */
    static Any internal_constructor(const JS::Any& thisArgs, const JS::Any& args);
    /** @brief Function that is used when object is call as a function */
    static Any internal_call(const JS::Any& thisArg, const JS::Any& args);
    ///@}

    /** @brief Returns the content of the object formatted to a string. */
    [[nodiscard]] std::u16string getContent() const override;
    /** @brief Get the instance of the global object. */
    [[nodiscard]] static std::shared_ptr<JS::Function> getConstructor();
};

} // namespace JS

#endif // JSOBJECT_HPP
