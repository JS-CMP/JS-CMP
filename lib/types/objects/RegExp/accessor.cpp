#include "types/objects/JsRegExp.hpp"
#include "utils/Compare.hpp"
#include "internals/PropertyProxy.hpp"

JS::Any JS::RegExp::internal_call(const JS::Any& thisArg, const JS::Any& args) {
    if (JS::COMPARE::Object(args[u"0"], u"RegExp") && !JS::COMPARE::Type(args[u"1"], JS::UNDEFINED)) {
        return args[u"0"];
    }
    return JS::Any(std::make_shared<JS::RegExp>(args[u"0"], args[u"1"]));
}

JS::Any JS::RegExp::internal_constructor(const JS::Any& thisArgs, const JS::Any& args) {
    return JS::Any(std::make_shared<JS::RegExp>(args[u"0"], args[u"1"]));
}