#include "internals/PropertyProxy.hpp"
#include "types/objects/JsNumber.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

JS::Any JS::Number::internal_call(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(CONVERT::ToNumber(args[u"0"]));
}

JS::Any JS::Number::internal_constructor(const JS::Any& thisArgs, const JS::Any& args) {
    if (JS::COMPARE::Type(args[u"0"], JS::UNDEFINED)) {
        return JS::Any(std::make_shared<JS::Number>());
    }
    return JS::Any(std::make_shared<JS::Number>(args[u"0"]));
}