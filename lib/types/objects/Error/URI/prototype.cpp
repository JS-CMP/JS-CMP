#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/Error/JsURIError.hpp"

JS::Any JS::UriError::toString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}
