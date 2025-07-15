#include "internals/PropertyProxy.hpp"
#include "types/objects/Error/JsSyntaxError.hpp"

JS::Any JS::SyntaxError::internal_call(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::make_shared<JS::SyntaxError>(args[u"0"]));
}

JS::Any JS::SyntaxError::internal_constructor(const JS::Any& thisArgs, const JS::Any& args) {
    return JS::Any(std::make_shared<JS::SyntaxError>(args[u"0"]));
}