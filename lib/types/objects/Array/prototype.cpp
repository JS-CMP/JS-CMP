#include "internals/PropertyProxy.hpp"
#include "types/objects/JsArray.hpp"

#include <utils/Compare.hpp>

// static
JS::Any JS::Array::isArray(const JS::Any& thisArg, const JS::Any& args) {
    return JS::Any(JS::COMPARE::Object(args[u"0"], u"Array"));
}