#include "types/objects/JsBoolean.hpp"
#include "types/objects/Function/JsFunction.hpp"

JS::Any JS::Boolean::toString(const JS::Any& thisArg, const JS::Any& args) { return JS::Any("bool"); }

JS::Any JS::Boolean::valueOf(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}
