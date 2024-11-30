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
#include <iostream>
#include <sstream>
#include <cstdint>

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

class Any;
class Object;
class Array;

using FunctionType =
    std::function<JS::Any(const std::vector<JS::Any>&)>; /**< Type alias for JavaScript-like functions. */
/** @cond */                                             // Hide from Doxygen
struct Undefined {};                                     /**< Represents an undefined value. */
/** @endcond */
using Null = std::nullptr_t; /**< Type alias for a null value. */
using Value = std::variant<double, Rope, bool, JS::Undefined, JS::Null,
                           std::shared_ptr<JS::Object>>; /**< Union of all possible types Any can hold. */
} // namespace JS

#endif // TYPES_HPP
