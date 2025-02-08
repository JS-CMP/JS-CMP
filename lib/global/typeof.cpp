#include "types/JsAny.hpp"

namespace JS::GLOBAL {
JS::Any global_typeof(const std::vector<JS::Any>& args) {
    switch (args[0].getValue().index()) {
        case JS::NUMBER:
            return JS::Any("number");
        case JS::STRING:
            return JS::Any("string");
        case JS::BOOL:
            return JS::Any("boolean");
        case JS::UNDEFINED:
            return JS::Any("undefined");
        case JS::NULL_TYPE:
            return JS::Any("object");
        default:
            return JS::Any("object");
    }
}
} // namespace JS::GLOBAL