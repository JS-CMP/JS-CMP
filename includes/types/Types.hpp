#ifndef TYPES_HPP
#define TYPES_HPP

#include <functional>
#include <variant>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace JS {
    enum Types {
        NUMBER,
        STRING,
        BOOL,
        FUNCTION,
        UNDEFINED,
        NULL_TYPE,
        OBJECT,
        ARRAY
    };

    class Any;
    class Object;
    class Array;

    using Function = std::function<JS::Any(const std::vector<JS::Any>&)>;
    struct Undefined {};
    using Null = std::nullptr_t;
    using Value = std::variant<double, std::string, bool, JS::Function, JS::Undefined, JS::Null,  std::shared_ptr<JS::Object>>;
}

#endif // TYPES_HPP
