#include "internals/PropertyProxy.hpp"
#include "types/objects/Error/JsNativeError.hpp"

JS::Any JS::NativeError::internal_call(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(std::make_shared<JS::NativeError>(args[u"0"]));
}

JS::Any JS::NativeError::internal_constructor(const JS::Any& thisArgs, const JS::Any& args) {
    return JS::Any(std::make_shared<JS::NativeError>(args[u"0"]));
}