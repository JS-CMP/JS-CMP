#include "types/objects/JsFunction.hpp"
#include "types/objects/Error/JsRangeError.hpp"

JS::Any JS::RangeError::toString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}
