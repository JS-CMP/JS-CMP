#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Attribute.hpp"
#include "IObject.hpp"
#include "types/JsAny.hpp"
#include "types/Types.hpp"

#include <utility>

namespace JS {
/**
 * @class InternalObject
 * @brief Represents a base object for all JavaScript-like objects in C++.
 *
 * The `InternalObject` class represents a JavaScript-like object in C++. It provides methods to access and modify
 * properties of the object. It also provides methods to check if a property exists, and if it's callable.
 */
class InternalObject : public JS::IObject, public std::enable_shared_from_this<JS::InternalObject> {
public:
    /**
     * @name Constructors
     * These constructors create a new Object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the object with an empty map */
    explicit InternalObject(JS::Properties properties = {}, std::shared_ptr<JS::InternalObject> prototype = nullptr,
                            std::string class_name = "Object", bool extensible = true);
    /** @brief Attribute constructor */
    explicit InternalObject(const JS::Attribute& attribute);

    /** @brief Copy constructor */
    InternalObject(const JS::InternalObject& other);
    /** @brief Move constructor */
    InternalObject(JS::InternalObject&& other) noexcept;
    /** @brief Move operator */
    InternalObject& operator=(JS::InternalObject&& other) noexcept;
    ///@}

    /**
     * @name Accessors
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Accessors to properties with string of object in stored in value */
    JS::PropertyProxy operator[](const std::string& key) override;
    /** @brief Accessors to properties with number of object in stored in value */
    JS::PropertyProxy operator[](size_t index) override;
    /** @brief Call operator for the object */
    template <typename... Args>
    JS::Any operator()(Args... args) {
        std::vector<JS::Any> arguments = {std::forward<Args>(args)...};
        return call(arguments);
    }

    ///@}

    /**
     * @name Internal Properties Common to All Objects
     * These methods provide access to the internal properties of the object
     */
    ///@{
    /** @brief Get a property of the object https://262.ecma-international.org/5.1/#sec-8.12.1 */
    [[nodiscard]] std::optional<JS::Attribute> getOwnProperty(const std::string& key) const override;
    /** @brief Get a property of the object with all the parent included
     * https://262.ecma-international.org/5.1/#sec-8.12.2 */
    [[nodiscard]] std::optional<JS::Attribute> getProperty(const std::string& key) const override;
    /** @brief Get a property of the object with all the parent included and all the checks for descriptor
     * https://262.ecma-international.org/5.1/#sec-8.12.3 */
    [[nodiscard]] JS::Any get(const std::string& key) const override;
    /** @brief Check if a property can be put in the object https://262.ecma-international.org/5.1/#sec-8.12.4 */
    [[nodiscard]] bool canPut(const std::string& key) const override;
    /** @brief Put a property in the object https://262.ecma-international.org/5.1/#sec-8.12.5 */
    void put(const std::string& key, const JS::Any& value, bool is_throw = false) override;
    /** @brief Check if a property exists in the object https://262.ecma-international.org/5.1/#sec-8.12.6 */
    [[nodiscard]] bool hasProperty(const std::string& key) const override;
    /** @brief Delete a property in the object https://262.ecma-international.org/5.1/#sec-8.12.7 */
    bool deleteProperty(const std::string& key, bool is_throw = false) override;
    /** @brief Get the default value of the object https://262.ecma-international.org/5.1/#sec-8.12.8 */
    JS::Any defaultValue(const JS::Types& hint) override;
    /** @brief Get the default value of the object https://262.ecma-international.org/5.1/#sec-8.12.8 */
    JS::Any defaultValue() override;
    /** @brief Define a property in the object https://262.ecma-international.org/5.1/#sec-8.12.9 */
    bool defineOwnProperty(const std::string& key, JS::Attribute attribute, bool is_throw = false) override;
    ///@}

    /**
     * @name Internal Utility Methods
     */
    ///@{
    /** @brief check if the object is callable */
    [[nodiscard]] bool isCallable() const override;
    ///@}

    std::shared_ptr<JS::Properties> properties;    /**< The properties of the object. */
    std::shared_ptr<JS::InternalObject> prototype; /**< The prototype of the object. */
    FunctionType call;                             /**< The call function of the object. */
    FunctionType construct;                        /**< The construct function of the object. */
    std::string class_name;                        /**< The class name of the object. */
    bool extensible;                               /**< Whether the object is extensible. */
};
} // namespace JS

#endif // OBJECT_HPP