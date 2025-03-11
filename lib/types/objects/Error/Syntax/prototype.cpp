#include "types/objects/JsFunction.hpp"
#include "types/objects/Error/JsSyntaxError.hpp"

JS::Any JS::SyntaxError::toString(const JS::Any& thisArg, const JS::Any& args) {
    throw std::runtime_error("not implemented");
}
