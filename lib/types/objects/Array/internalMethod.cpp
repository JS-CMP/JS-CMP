#include "internals/Object.hpp"
#include "types/objects/JsArray.hpp"
#include "utils/Convert.hpp"

#include <types/objects/Function/JsFunction.hpp>

std::u16string JS::Array::getContent() const {
    return JS::CONVERT::ArrayToString(shared_from_this());
}

std::shared_ptr<JS::Function> JS::Array::getConstructor() {
    auto prototype = Function::getPrototypeProperties();
    static auto constructor = JS::InternalObject::create<JS::Function>([](const JS::Any& thisArg, const JS::Any& args) -> JS::Any { return JS::Any(InternalObject::create<Array>(args)); }, 1, ARRAY_CLASS_NAME, prototype);

    constructor->class_name = ARRAY_CLASS_NAME;
    constructor->extensible = true;
    constructor->prototype = prototype;
    constructor->properties = std::make_shared<JS::Properties>(JS::Properties{{u"length", JS::DataDescriptor{JS::Any(1), true, false, false}}, {u"name", JS::DataDescriptor{JS::Any(ARRAY_CLASS_NAME), false, false, false}}, {u"isArray", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Array::isArray, 1, u"isArray")), true, true, true}}, {u"prototype", JS::DataDescriptor(JS::Any(Array::getPrototypeProperties(constructor)), false, false, false)}});
    return constructor;
}
