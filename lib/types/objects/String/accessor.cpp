#include "internals/PropertyProxy.hpp"
#include "types/objects/JsString.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

JS::Any JS::String::internal_call(const JS::Any& thisArg, const JS::Any& args) {
    if (JS::COMPARE::Type(thisArg, JS::UNDEFINED)) {
        return JS::Any(JS::String());
    }
    return JS::Any(CONVERT::ToString(args[u"0"]));
}

JS::Any JS::String::internal_constructor(const JS::Any& thisArgs, const JS::Any& args) {
    if (JS::COMPARE::Type(args[u"0"], JS::UNDEFINED)) {
        return JS::Any(std::make_shared<JS::String>());
    }
    return JS::Any(std::make_shared<JS::String>(args[u"0"]));
}