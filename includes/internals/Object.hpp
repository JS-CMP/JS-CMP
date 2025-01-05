#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Attribute.hpp"
#include "types/JsAny.hpp"
#include "types/Types.hpp"

#include <optional>
#include <utility>

namespace JS {

using Properties = std::unordered_map<std::string, JS::Attribute>;

/**
 * @class InternalObject
 * @brief Represents a base object for all JavaScript-like objects in C++.
 *
 * The `InternalObject` class represents a JavaScript-like object in C++. It provides methods to access and modify
 * properties of the object. It also provides methods to check if a property exists, and if it's callable.
 */
class InternalObject {
public:
    /**
     * @name Constructors
     * These constructors create a new Object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the object with an empty map */
    InternalObject(JS::Properties properties = {}, std::shared_ptr<JS::InternalObject> prototype = nullptr,
                    std::string class_name = "Object", bool extensible = true);
    /** @brief Attribute constructor */
    explicit InternalObject(const JS::Attribute& attribute);

    /** @brief Copy constructor */
    InternalObject(const JS::Object& other);
    /** @brief Move constructor */
    InternalObject(const InternalObject& object);
    /** @brief Move constructor */
    InternalObject(JS::InternalObject&& other) noexcept;
    /** @brief Move operator */
    InternalObject& operator=(JS::InternalObject&& other) noexcept;
    ///@}

    /**
     * @brief The destructor for the object defaulted
     */
    virtual ~InternalObject() = default;

    /**
     * @name Accessors
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Accessors to properties with string of object in stored in value */
    virtual JS::PropertyProxy operator[](const std::string& key);
    /** @brief Accessors to properties with number of object in stored in value */
    virtual JS::PropertyProxy operator[](size_t index);
    ///@}

    /**
     * @name Internal Properties Common to All Objects
     * These methods provide access to the internal properties of the object
     */
    ///@{
    /** @brief Get a property of the object https://262.ecma-international.org/5.1/#sec-8.12.1 */
    std::optional<JS::Attribute> getOwnProperty(const std::string& key) const;
    /** @brief Get a property of the object with all the parent included
     * https://262.ecma-international.org/5.1/#sec-8.12.2 */
    std::optional<JS::Attribute> getProperty(const std::string& key) const;
    /** @brief Get a property of the object with all the parent included and all the checks for descriptor
     * https://262.ecma-international.org/5.1/#sec-8.12.3 */
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
    JS::Any defaultValue(const JS::Types& hint);
    /** @brief Get the default value of the object https://262.ecma-international.org/5.1/#sec-8.12.8 */
    JS::Any defaultValue();
    /** @brief Define a property in the object https://262.ecma-international.org/5.1/#sec-8.12.9 */
    bool defineOwnProperty(const std::string& key, Attribute attribute, bool is_throw = false);
    ///@}

    /**
     * @name Methods
     * These methods provide additional functionality to the object
     */
    ///@{
    /** @brief Check if the object is callable */
    virtual bool isCallable() const;
    ///@}

    /**
     * @name Getters
     * These methods provide access to the internal properties of the object
     */
    JS::InternalObject &getInteralObject() {
        return *this;
    }

protected:
    std::shared_ptr<JS::Properties> properties; /**< The properties of the object. */
    std::shared_ptr<JS::InternalObject> prototype; /**< The prototype of the object. */
    std::string class_name;                        /**< The class name of the object. */
    bool extensible{};                               /**< Whether the object is extensible. */
};
} // namespace JS

#endif // OBJECT_HPP
