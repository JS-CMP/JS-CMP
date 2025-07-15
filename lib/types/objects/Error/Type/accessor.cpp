#include "internals/PropertyProxy.hpp"
#include "types/objects/Error/JsTypeError.hpp"

JS::Any JS::TypeError::internal_call(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::make_shared<JS::TypeError>(args[u"0"]));
}

JS::Any JS::TypeError::internal_constructor(const JS::Any& thisArgs, const JS::Any& args) {
    return JS::Any(std::make_shared<JS::TypeError>(args[u"0"]));
}