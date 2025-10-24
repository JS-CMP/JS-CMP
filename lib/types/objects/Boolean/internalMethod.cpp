#include "internals/Object.hpp"
#include "types/objects/JsBoolean.hpp"
#include "utils/Convert.hpp"

#include <utils/Compare.hpp>
#include <types/objects/Function/JsFunction.hpp>

std::u16string JS::Boolean::getContent() const {
    return JS::CONVERT::ToString(this->primitiveValue);
}

std::shared_ptr<JS::Function> JS::Boolean::getConstructor() {
    auto prototype = Function::getPrototypeProperties();

    static auto constructor = JS::InternalObject::create<JS::Function>( [] (const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
        return JS::Any(JS::InternalObject::create<JS::Boolean>(args[u"0"]));
    }, 1, BOOL_CLASS_NAME, prototype);

    constructor->class_name = BOOL_CLASS_NAME;
    constructor->extensible = true;
    constructor->prototype = prototype;
    constructor->properties = std::make_shared<JS::Properties>(JS::Properties{
        {u"length", JS::DataDescriptor{JS::Any(1), true, false, false}},
        {u"name", JS::DataDescriptor{JS::Any(BOOL_CLASS_NAME), false, false, false}},
        {u"prototype", JS::DataDescriptor(JS::Any(Boolean::getPrototypeProperties(constructor)), false, false, false)}
    });
    return constructor;
}