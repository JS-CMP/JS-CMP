#ifndef JSOBJECT_HPP
#define JSOBJECT_HPP

#include "../Types.hpp"
#include "types/Attribute.hpp"
#include "types/JsAny.hpp"

#include <optional>
#include <utility>

namespace JS {
/**
 * @class Object
 * @brief Represents a JavaScript-like object in C++.
 *
 * The `Object` class represents a JavaScript-like object in C++. It provides methods to access and modify properties of
 * the object. It also provides methods to check if a property exists, and if it's callable.
 */
class Object : public std::enable_shared_from_this<Object> {
public:
    /**
     * @name Constructors
     * These constructors create a new Object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the object with an empty map */
    Object() = default;
    /** @brief Attribute constructor */
    explicit Object(const JS::Attribute& attribute);

    /** @brief Copy constructor */
    Object(const JS::Object& other);
    /** @brief Move constructor */
    Object& operator=(const JS::Object& other);
    /** @brief Move constructor */
    Object(JS::Object&& other) noexcept;
    /** @brief Move constructor */
    Object& operator=(JS::Object&& other) noexcept;
    ///@}

    /**
     * @brief The destructor for the object defaulted
     */
    virtual ~Object() = default;

    /**
     * @name Accessors
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Accessors to properties with string of object in stored in value */
    virtual JS::Any operator[](const std::string& key);
    /** @brief Accessors to properties with number of object in stored in value */
    virtual JS::Any operator[](size_t index);
    ///@}

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
     * @name Internal Properties Common to All Objects
     * These methods provide access to the internal properties of the object
     */
    ///@{
    /** @brief Get a property of the object https://262.ecma-international.org/5.1/#sec-8.12.1 */
    std::optional<JS::Attribute> getOwnProperty(const std::string& key) const;
    /** @brief Get a property of the object with all the parent included https://262.ecma-international.org/5.1/#sec-8.12.2 */
    std::optional<JS::Attribute> getProperty(const std::string& key) const;
    /** @brief Get a property of the object with all the parent included and all the checks for descriptor https://262.ecma-international.org/5.1/#sec-8.12.3 */
    JS::Any get(const std::string& key) const;
    /** @brief Check if a property can be put in the object https://262.ecma-international.org/5.1/#sec-8.12.4 */
    bool canPut(const std::string& key) const;
    /** @brief Put a property in the object https://262.ecma-international.org/5.1/#sec-8.12.5 */
    void put(const std::string& key, const JS::Any& value, bool is_throw = false);
    /** @brief Check if a property exists in the object https://262.ecma-international.org/5.1/#sec-8.12.6 */
    bool hasProperty(const std::string& key) const;
    /** @brief Delete a property in the object https://262.ecma-international.org/5.1/#sec-8.12.7 */
    bool deleteProperty(const std::string& key, bool is_throw = false);
    /** @brief Get the default value of the object https://262.ecma-international.org/5.1/#sec-8.12.8 */
    JS::Any defaultValue(const JS::Types& hint) const;
    /** @brief Get the default value of the object https://262.ecma-international.org/5.1/#sec-8.12.8 */
    JS::Any defaultValue() const;
    /** @brief Define a property in the object https://262.ecma-international.org/5.1/#sec-8.12.9 */
    bool defineOwnProperty(const std::string& key, Attribute attribute, bool is_throw = false);
    ///@}

    /**
     * @name Methods
     * These methods provide additional functionality to the object
     */
    ///@{
    /** @brief init functions in the properties, made for inherited class */
    virtual void init();
    /** @brief Check if the object is callable */
    virtual bool isCallable() const;
    ///@}

protected:
    std::shared_ptr<std::unordered_map<std::string, JS::Attribute>> properties =
        std::make_shared<std::unordered_map<std::string, JS::Attribute>>(); /**< The properties of the object. */

    // Internal Properties Common to All Objects
    std::shared_ptr<JS::Object> prototype = nullptr; /**< The prototype of the object. */
    std::string class_name = "Object";               /**< The class name of the object. */
    bool extensible = true;                          /**< Whether the object is extensible. */
};
} // namespace JS

#endif // JSOBJECT_HPP
