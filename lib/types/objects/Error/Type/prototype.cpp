#include "types/objects/JsFunction.hpp"
#include "types/objects/Error/JsTypeError.hpp"

JS::Any JS::TypeError::toString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}
