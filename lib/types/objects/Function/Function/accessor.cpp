#include "internals/PropertyProxy.hpp"
#include "types/objects/Function/JsFunction.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

JS::Any JS::Function::internal_call(const JS::Any& thisArg, const JS::Any& args) {
    return internal_constructor(thisArg, args);
}

JS::Any JS::Function::internal_constructor(const JS::Any& thisArgs, const JS::Any& args) {
    auto len = CONVERT::ToUint32(args[u"length"]);
    if (len == 1) {
        return JS::Any(std::make_shared<JS::Function>());
    }
    throw std::runtime_error("Not implemented"); // TODO:: Fix + change error
}