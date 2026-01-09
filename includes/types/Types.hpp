#ifndef TYPES_HPP
#define TYPES_HPP

#include "../class/Rope/Rope.hpp"

#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace JS {
/**
 * Enum representing the types that can be held by an instance of JS::Any.
 */

// js class names of all objects
#define FUNCTION_CLASS_NAME u"Function"
#define OBJECT_CLASS_NAME u"Object"
#define NUMBER_CLASS_NAME u"Number"
#define STRING_CLASS_NAME u"String"
#define BOOL_CLASS_NAME u"Boolean"
#define ARRAY_CLASS_NAME u"Array"
#define ERROR_CLASS_NAME u"Error"
#define REGEXP_CLASS_NAME u"RegExp"
#define MATH_CLASS_NAME u"Math"
#define DATE_CLASS_NAME u"Date"
#define JSON_CLASS_NAME u"JSON"

enum Types : std::uint8_t {
    NUMBER,    /**< Represents a numeric type (double). */
    STRING,    /**< Represents a string type. */
    BOOLEAN,   /**< Represents a boolean type. */
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
enum AttributeTypes : std::uint8_t {
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
class Number;
class String;
class Boolean;

class Any;

using FunctionType = std::function<JS::Any(const JS::Any&, const JS::Any&)>; /**< Type alias for JavaScript-like functions. */
/** @cond */                                                                 // Hide from Doxygen
struct Undefined {};                                                         /**< Represents an undefined value. */
/** @endcond */
using Null = std::nullptr_t;                                                                                  /**< Type alias for a null value. */
using Value = std::variant<double, Rope, bool, JS::Undefined, JS::Null, std::shared_ptr<JS::InternalObject>>; /**< Union of all possible types Any can hold. */
} // namespace JS

#endif // TYPES_HPP
