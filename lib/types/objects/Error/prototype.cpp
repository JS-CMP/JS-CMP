#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/Error/JsError.hpp"

JS::Any JS::Error::toString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}
