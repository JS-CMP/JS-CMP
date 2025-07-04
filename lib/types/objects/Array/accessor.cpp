#include "internals/PropertyProxy.hpp"
#include "types/objects/JsArray.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

JS::Any JS::Array::internal_call(const JS::Any& thisArg, const JS::Any& args) {
    return internal_constructor(thisArg, args);
}

JS::Any JS::Array::internal_constructor(const JS::Any& thisArgs, const JS::Any& args) {
    return JS::Any(std::make_shared<JS::Array>(args));
}