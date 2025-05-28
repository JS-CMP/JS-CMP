#include "types/objects/JsArray.hpp"

#include <utils/Compare.hpp>

// static
JS::Any JS::Array::isArray(const JS::Any& thisArg, const JS::Any& args) {
    JS::Any arg = args[u"0"];
    if (!JS::COMPARE::Type(arg, JS::OBJECT)) {
        return JS::Any(false);
    }
    return JS::Any(std::get<std::shared_ptr<JS::InternalObject>>(arg.getValue())->class_name == u"Array");
}