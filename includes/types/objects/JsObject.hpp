#ifndef JSOBJECT_HPP
#define JSOBJECT_HPP

#include "../JsAny.hpp"
#include "../Types.hpp"

namespace JS {
/**
 * @class Object
 * @brief Represents a JavaScript-like object in C++.
 *
 * The `Object` class represents a JavaScript-like object in C++. It provides methods to access and modify properties of
 * the object. It also provides methods to check if a property exists, and if it's callable.
 */
class Object {
public:
    /**
     * @name Constructors
     * These constructors create a new Object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the object with an empty map */
    Object() = default;
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

    /**
     * @name Methods
     * These methods provide additional functionality to the object
     */
    ///@{
    /** @brief init functions in the properties, made for inherited class */
    virtual void init() {};
    /** @brief Check if the object is callable */
    [[nodiscard]] virtual bool isCallable() const;
    /** @brief Check if the object has a property */
    [[nodiscard]] bool hasProperty(const std::string& key) const;

protected:
    std::shared_ptr<std::unordered_map<std::string, JS::Any>> properties =
        std::make_shared<std::unordered_map<std::string, JS::Any>>(); /**< The properties of the object. */
};
} // namespace JS

#endif // JSOBJECT_HPP
