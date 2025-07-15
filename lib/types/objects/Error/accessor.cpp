#include "internals/PropertyProxy.hpp"
#include "types/objects/Error/JsError.hpp"

JS::Any JS::Error::internal_call(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::make_shared<JS::Error>(args[u"0"]));
}

JS::Any JS::Error::internal_constructor(const JS::Any& thisArgs, const JS::Any& args) {
    return JS::Any(std::make_shared<JS::Error>(args[u"0"]));
}