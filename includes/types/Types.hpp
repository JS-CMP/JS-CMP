#ifndef TYPES_HPP
#define TYPES_HPP

#include <functional>
#include <variant>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "../class/Rope/Rope.hpp"

namespace JS {
    enum Types {
        NUMBER,
        STRING,
        BOOL,
        UNDEFINED,
        NULL_TYPE,
        OBJECT,

        // unused
        FUNCTION,
    };

    class Any;
    class Object;
    class Array;

    using FunctionType = std::function<JS::Any(const std::vector<JS::Any> &)>;
    struct Undefined {};
    using Null = std::nullptr_t;
    using Value = std::variant<double, Rope, bool, JS::Undefined, JS::Null, std::shared_ptr<JS::Object>>;
}

#endif // TYPES_HPP
