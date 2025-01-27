#ifndef TYPES_HPP
#define TYPES_HPP

#include "../class/Rope/Rope.hpp"

#include <functional>
#include <limits>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace JS {
/**
 * Enum representing the types that can be held by an instance of JS::Any.
 */
enum Types {
    NUMBER,    /**< Represents a numeric type (double). */
    STRING,    /**< Represents a string type. */
    BOOL,      /**< Represents a boolean type. */
    UNDEFINED, /**< Represents an undefined type. */
    NULL_TYPE, /**< Represents a null type. */
    OBJECT,    /**< Represents an object type. */

    // unused, keep for now because TODO: we need to remove it from all operators
    FUNCTION,
};

/**
 * @enum AttributeTypes
 * @brief Represents the types of JavaScript object properties.
 */
enum AttributeTypes {
    DATA_DESCRIPTOR,    /**< Represents a data property. */
    ACCESSOR_DESCRIPTOR /**< Represents an accessor property. */
};

class DataDescriptor;
class AccessorDescriptor;

/**
 * @typedef Attribute
 * @brief Represents a JavaScript object property, which can be a data property or an accessor property.
 */
using Attribute = std::variant<DataDescriptor, AccessorDescriptor>;

class InternalObject;
class PropertyProxy;

class Object;
class Function;
class Array;

class Any;

using FunctionType =
    std::function<JS::Any(const JS::Any&, const JS::Any&)>; /**< Type alias for JavaScript-like functions. */
/** @cond */                                                // Hide from Doxygen
struct Undefined {};                                        /**< Represents an undefined value. */
/** @endcond */
using Null = std::nullptr_t; /**< Type alias for a null value. */
using Value = std::variant<double, Rope, bool, JS::Undefined, JS::Null,
                           std::shared_ptr<JS::InternalObject>>; /**< Union of all possible types Any can hold. */
} // namespace JS

#endif // TYPES_HPP
