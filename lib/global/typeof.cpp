#include "internals/PropertyProxy.hpp"
#include "types/JsAny.hpp"

namespace JS::GLOBAL {
JS::Any global_typeof(JS::Any a) {
    switch (a.getValue().index()) {
        case JS::NUMBER:
            return JS::Any("number");
        case JS::STRING:
            return JS::Any("string");
        case JS::BOOLEAN:
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