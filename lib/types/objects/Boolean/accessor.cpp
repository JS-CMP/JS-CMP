#include "internals/PropertyProxy.hpp"
#include "types/objects/JsBoolean.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

JS::Any JS::Boolean::internal_call(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(CONVERT::ToBoolean(args[u"0"]));
}

JS::Any JS::Boolean::internal_constructor(const JS::Any& thisArgs, const JS::Any& args) {
    return JS::Any(JS::Boolean(args[u"0"]));
}