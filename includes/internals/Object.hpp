#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "types/JsAny.hpp"
#include "types/Types.hpp"

#include <optional>
#include <utility>

namespace JS {
using   Properties = std::unordered_map<std::u16string, JS::Attribute>;

/**
 * @class InternalObject
 * @brief Represents a base object for all JavaScript-like objects in C++.
 *
 * The `InternalObject` class represents a JavaScript-like object in C++. It provides methods to access and modify
 * properties of the object. It also provides methods to check if a property exists, and if it's callable.
 */
class InternalObject : public std::enable_shared_from_this<JS::InternalObject> {
public:
    /**
     * @name Constructors
     * These constructors create a new Object with the given value
     */
    ///@{
    /** @brief Default constructor initializes the object with an empty map */
    explicit InternalObject(JS::Properties properties = {}, std::shared_ptr<JS::InternalObject> prototype = nullptr,
                            std::u16string class_name = u"Object", bool extensible = true);
    explicit InternalObject(const std::unordered_map<std::u16string, JS::Any>& properties = {});
    /** @brief Attribute constructor */
    explicit InternalObject(const JS::Attribute& attribute);

    /** @brief Copy constructor */
    InternalObject(const JS::InternalObject& other);
    /** @brief Move constructor */
    InternalObject(JS::InternalObject&& other) noexcept;
    /** @brief Move operator */
    InternalObject& operator=(JS::InternalObject&& other) noexcept;
    ///@}

    /** @brief The destructor for the object defaulted */
    virtual ~InternalObject() = default;

    /**
     * @name Accessors
     * These methods provide access to the properties of the object
     */
    ///@{
    /** @brief Accessors to properties with string of object in stored in value */
    JS::PropertyProxy operator[](const std::u16string& key);
    /** @brief Call operator for the object */
    template <typename... Args>
    JS::Any operator()(Args... args) {
        return call_function(JS::Any(JS::Undefined{}),
                             JS::Arguments::CreateArgumentsObject(std::vector<JS::Any>{std::move(args)...}));
    }
    ///@}

    /**
     * @name Internal Properties Common to All Objects
     * These methods provide access to the internal properties of the object
     */
    ///@{
    /** @brief Get a property of the object https://262.ecma-international.org/5.1/#sec-8.12.1 */
    [[nodiscard]] virtual std::optional<JS::Attribute> getOwnProperty(const std::u16string& key) const;
    /** @brief Get a property of the object with all the parent included
     * https://262.ecma-international.org/5.1/#sec-8.12.2 */
    [[nodiscard]] virtual std::optional<JS::Attribute> getProperty(const std::u16string& key) const;
    /** @brief Get a property of the object with all the parent included and all the checks for descriptor
     * https://262.ecma-international.org/5.1/#sec-8.12.3 */
    [[nodiscard]] virtual JS::Any get(const std::u16string& key) const;
    /** @brief Check if a property can be put in the object https://262.ecma-international.org/5.1/#sec-8.12.4 */
    [[nodiscard]] virtual bool canPut(const std::u16string& key) const;
    /** @brief Put a property in the object https://262.ecma-international.org/5.1/#sec-8.12.5 */
    virtual void put(const std::u16string& key, const JS::Any& value, bool is_throw = false);
    /** @brief Check if a property exists in the object https://262.ecma-international.org/5.1/#sec-8.12.6 */
    [[nodiscard]] virtual bool hasProperty(const std::u16string& key) const;
    /** @brief Delete a property in the object https://262.ecma-international.org/5.1/#sec-8.12.7 */
    virtual bool deleteProperty(const std::u16string& key, bool is_throw = false);
    /** @brief Get the default value of the object https://262.ecma-international.org/5.1/#sec-8.12.8 */
    virtual JS::Any defaultValue(const JS::Types& hint);
    /** @brief Get the default value of the object https://262.ecma-international.org/5.1/#sec-8.12.8 */
    virtual JS::Any defaultValue();
    /** @brief Define a property in the object https://262.ecma-international.org/5.1/#sec-8.12.9 */
    virtual bool defineOwnProperty(const std::u16string& key, JS::Attribute attribute, bool is_throw = false);
    ///@}

    /**
     * @name Internal Methods Specific to certain Objects
     * All of this methods throw a TypeError if the object is not of the correct type
     */
    ///@{
    /** @brief check if the object is likely created by this object, only Function implements this */
    [[nodiscard]] virtual bool hasInstance(const JS::Any& value) const;
    ///@}

    /**
     * @name Internal Utility Methods
     */
    ///@{
    /** @brief check if the object is callable */
    [[nodiscard]] virtual bool isCallable() const;
    ///@}

    std::shared_ptr<JS::Properties> properties;    /**< The properties of the object. */
    std::shared_ptr<JS::InternalObject> prototype; /**< The prototype of the object. */
    FunctionType call_function;                    /**< The call function of the object. */
    FunctionType construct;                        /**< The construct function of the object. */
    std::u16string class_name;                     /**< The class name of the object. */
    bool extensible;                               /**< Whether the object is extensible. */
    JS::Value primitiveValue; /**< The primitive value of the object. (Only Defined for Some Objects) */
    std::shared_ptr<JS::InternalObject> parameter_map; /**< The parameter map of the object. */
};
} // namespace JS

#endif // OBJECT_HPP