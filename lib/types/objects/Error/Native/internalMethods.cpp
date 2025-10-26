#include "internals/Object.hpp"
#include "types/objects/Error/JsNativeError.hpp"
#include "utils/Convert.hpp"
#include "utils/Is.hpp"

#include <types/objects/Function/JsFunction.hpp>
#include <utils/Compare.hpp>

std::shared_ptr<JS::Function> JS::NativeError::getConstructor() {
    auto prototype = Function::getPrototypeProperties();
    static auto constructor = JS::InternalObject::create<JS::Function>([](const JS::Any& thisArg, const JS::Any& args) -> JS::Any { return JS::Any(JS::InternalObject::create<JS::NativeError>(args[u"0"])); }, 1, ERROR_CLASS_NAME, prototype);

    constructor->class_name = ERROR_CLASS_NAME;
    constructor->extensible = true;
    constructor->prototype = prototype;
    constructor->properties = std::make_shared<JS::Properties>(JS::Properties{
        {u"length", JS::DataDescriptor{JS::Any(1), false, false, false}},
        {u"name", JS::DataDescriptor{JS::Any("NativeError"), false, false, false}},
    });
    return constructor;
}
