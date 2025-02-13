#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include "types/Types.hpp"

#include <optional>

namespace JS {

using Properties = std::unordered_map<std::string, JS::Attribute>;

/**
 * @class IObject
 * @brief Represents a base object for all JavaScript-like objects in C++.
 *
 * The `IObject` class represents a JavaScript-like object in C++. It provides methods to access and modify
 * properties of the object. It also provides methods to check if a property exists, and if it's callable.
 */
class IObject {
public:
    virtual ~IObject() = default;

    /**
     * @name Accessors
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Accessors to properties with string of object in stored in value */
    virtual JS::PropertyProxy operator[](const std::string& key) = 0;
    /** @brief Accessors to properties with number of object in stored in value */
    virtual JS::PropertyProxy operator[](size_t index) = 0;
    ///@}

    /**
     * @name Internal Properties Common to All Objects
     * These methods provide access to the internal properties of the object
     */
    ///@{
    /** @brief Get a property of the object https://262.ecma-international.org/5.1/#sec-8.12.1 */
    [[nodiscard]] virtual std::optional<JS::Attribute> getOwnProperty(const std::string& key) const = 0;
    /** @brief Get a property of the object with all the parent included
     * https://262.ecma-international.org/5.1/#sec-8.12.2 */
    [[nodiscard]] virtual std::optional<JS::Attribute> getProperty(const std::string& key) const = 0;
    /** @brief Get a property of the object with all the parent included and all the checks for descriptor
     * https://262.ecma-international.org/5.1/#sec-8.12.3 */
    [[nodiscard]] virtual JS::Any get(const std::string& key) const = 0;
    /** @brief Check if a property can be put in the object https://262.ecma-international.org/5.1/#sec-8.12.4 */
    [[nodiscard]] virtual bool canPut(const std::string& key) const = 0;
    /** @brief Put a property in the object https://262.ecma-international.org/5.1/#sec-8.12.5 */
    virtual void put(const std::string& key, const JS::Any& value, bool is_throw = false) = 0;
    /** @brief Check if a property exists in the object https://262.ecma-international.org/5.1/#sec-8.12.6 */
    [[nodiscard]] virtual bool hasProperty(const std::string& key) const = 0;
    /** @brief Delete a property in the object https://262.ecma-international.org/5.1/#sec-8.12.7 */
    virtual bool deleteProperty(const std::string& key, bool is_throw = false) = 0;
    /** @brief Get the default value of the object https://262.ecma-international.org/5.1/#sec-8.12.8 */
    virtual JS::Any defaultValue(const JS::Types& hint) = 0;
    /** @brief Get the default value of the object https://262.ecma-international.org/5.1/#sec-8.12.8 */
    virtual JS::Any defaultValue() = 0;
    /** @brief Define a property in the object https://262.ecma-international.org/5.1/#sec-8.12.9 */
    virtual bool defineOwnProperty(const std::string& key, JS::Attribute attribute, bool is_throw = false) = 0;
    ///@}

    /**
     * @name Internal Utility Methods
     */
    ///@{
    /** @brief check if the object is callable */
    [[nodiscard]] virtual bool isCallable() const = 0;
    ///@}
};
} // namespace JS
#endif // IOBJECT_HPP
