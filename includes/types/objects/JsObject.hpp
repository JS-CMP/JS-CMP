#ifndef JSOBJECT_HPP
#define JSOBJECT_HPP

#include "../Types.hpp"
#include "types/JsAny.hpp"

#include <utility>

namespace JS {
class Attribute {
public:
    Attribute() = default;
    Attribute(const JS::Any& value) : value(value) {};
    Attribute(std::shared_ptr<JS::Object> value) {};
    JS::Any value;
    bool writable = true;
    bool enumerable = true;
    bool configurable = true;
};

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
    virtual JS::Any& operator[](const std::string& key);
    /** @brief Accessors to properties with number of object in stored in value */
    virtual JS::Any& operator[](size_t index);
    ///@}

    JS::Any operator()(const std::vector<JS::Any>& args);

    JS::Any getPrototype();
    JS::Any getPropertyDescriptor(std::string key);
    JS::Any create();
    JS::Any create(std::shared_ptr<JS::Object> properties);

    // internal methods
    JS::Any defineOwnProperty(std::string key, Attribute attribute, bool is_throw = false);

    /**
     * @name Methods
     * These methods provide additional functionality to the object
     */
    ///@{
    /** @brief init functions in the properties, made for inherited class */
    virtual void init();

    virtual bool isCallable() const;

protected:
    std::shared_ptr<std::unordered_map<std::string, JS::Attribute>> properties =
        std::make_shared<std::unordered_map<std::string, JS::Attribute>>(); /**< The properties of the object. */
};
} // namespace JS

#endif // JSOBJECT_HPP
