#include "../../includes/global/globalFunctions.hpp"
#include "../../includes/types/JsAny.hpp"

JS::Undefined global_void(const JS::Any& args) {
    JS::Any value = args[0];
    (void)value;
    return JS::Undefined();
}