#include "types/JsAny.hpp"
#include "internals/PropertyProxy.hpp"

JS::Any global_void(const JS::Any &thisArgs, const JS::Any &args) {
    static_cast<void>(args["0"]);
    return JS::Any(JS::Undefined{}); // undefined
}