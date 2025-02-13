#include "types/objects/Boolean/JsBoolean.hpp"
#include "types/objects/Function/JsFunction.hpp"

JS::Any JS::Boolean::toString(const std::vector<JS::Any>& args) {
    return JS::Any("bool");
}

JS::Any JS::Boolean::valueOf(const std::vector<JS::Any>& args) {
    throw std::runtime_error("not implemented");
}
