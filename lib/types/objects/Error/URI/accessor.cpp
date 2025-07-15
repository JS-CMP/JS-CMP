#include "internals/PropertyProxy.hpp"
#include "types/objects/Error/JsURIError.hpp"

JS::Any JS::URIError::internal_call(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::make_shared<JS::URIError>(args[u"0"]));
}

JS::Any JS::URIError::internal_constructor(const JS::Any& thisArgs, const JS::Any& args) {
    return JS::Any(std::make_shared<JS::URIError>(args[u"0"]));
}