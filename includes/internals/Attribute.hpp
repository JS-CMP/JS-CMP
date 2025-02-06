#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include "types/JsAny.hpp"

namespace JS {

/**
 * @class DataDescriptor
 * @brief Represents data properties of a JavaScript object.
 *
 * DataDescriptor is used to define properties that have a value, which may be writable,
 * enumerable, and configurable.
 */
class DataDescriptor {
public:
    /** @brief Default constructor. */
    DataDescriptor() = default;
    /**
     * @brief Constructor with a value parameter.
     * @param value The initial value of the property.
     */
    DataDescriptor(const JS::Any& value) : value(value){};
    /**
     * @brief Constructor with full property attributes.
     * @param value The initial value of the property.
     * @param writable Whether the property value can be changed.
     * @param enumerable Whether the property will be included in enumeration operations.
     * @param configurable Whether the property can be deleted or changed to an accessor property.
     */
    DataDescriptor(const JS::Any& value, bool writable, bool enumerable, bool configurable)
        : value(value), writable(writable), enumerable(enumerable), configurable(configurable){};
    /**
     * @brief Constructor with a shared pointer to a JavaScript object value.
     * @param value The initial value of the property.
     */
    DataDescriptor(std::shared_ptr<JS::InternalObject> value) : value(value){};

    JS::Any value = JS::Any(JS::Undefined{}); /**< The value of the property. */
    bool writable = false;                    /**< Whether the property value can be changed. */
    bool enumerable = false;                  /**< Whether the property will be included in enumeration operations. */
    bool configurable = false; /**< Whether the property can be deleted or changed to an accessor property. */
};

/**
 * @class AccessorDescriptor
 * @brief Represents accessor properties of a JavaScript object.
 *
 * AccessorDescriptor is used to define properties that have a getter and/or a setter function,
 * which may be enumerable and configurable.
 */
class AccessorDescriptor {
public:
    /** @brief Default constructor. */
    AccessorDescriptor() = default;
    /**
     * @brief Constructor with get and set functions, and other attributes.
     * @param get The getter function for the property.
     * @param set The setter function for the property.
     * @param enumerable Whether the property will be included in enumeration operations.
     * @param configurable Whether the property can be deleted or changed to a data property.
     */
    AccessorDescriptor(std::shared_ptr<JS::InternalObject> get, std::shared_ptr<JS::InternalObject> set,
                       bool enumerable, bool configurable)
        : get(std::move(get)), set(std::move(set)), enumerable(enumerable), configurable(configurable){};

    std::shared_ptr<JS::InternalObject> get; /**< The getter function for the property. */
    std::shared_ptr<JS::InternalObject> set; /**< The setter function for the property. */
    bool enumerable = false;                 /**< Whether the property will be included in enumeration operations. */
    bool configurable = false;               /**< Whether the property can be deleted or changed to a data property. */
};

/**
 * @enum AttributeTypes
 * @brief Represents the types of JavaScript object properties.
 */
enum AttributeTypes {
    DATA_DESCRIPTOR,    /**< Represents a data property. */
    ACCESSOR_DESCRIPTOR /**< Represents an accessor property. */
};

/**
 * @typedef Attribute
 * @brief Represents a JavaScript object property, which can be a data property or an accessor property.
 */
using Attribute = std::variant<DataDescriptor, AccessorDescriptor>;

} // namespace JS

#endif // ATTRIBUTE_HPP
