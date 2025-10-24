#include <types/objects/Function/JsFunction.hpp>
#include <utils/Compare.hpp>

#include "internals/Object.hpp"
#include "types/objects/JsString.hpp"
#include "utils/Convert.hpp"

std::u16string JS::String::getContent() const {
    return JS::CONVERT::ToString(this->primitiveValue);
}

std::shared_ptr<JS::Function> JS::String::getConstructor() {
    auto prototype = Function::getPrototypeProperties();
    static auto constructor = JS::InternalObject::create<JS::Function>([](const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
        if (JS::COMPARE::Type(args[u"0"], JS::UNDEFINED)) {
            return JS::Any(JS::InternalObject::create<JS::String>());
        }
        return JS::Any(JS::InternalObject::create<JS::String>(args[u"0"]));
    }, 1, STRING_CLASS_NAME, prototype);

    constructor->class_name = STRING_CLASS_NAME;
    constructor->extensible = true;
    constructor->prototype = prototype;
    constructor->properties = std::make_shared<JS::Properties>(JS::Properties{
        {u"length", JS::DataDescriptor{JS::Any(0), true, false, false}},
        {u"name", JS::DataDescriptor{JS::Any(STRING_CLASS_NAME), false, false, false}},
        {u"fromCharCode", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::String::fromCharCode, 1, u"fromCharCode")), true, true, true}},
        {u"prototype", JS::DataDescriptor(JS::Any(String::getPrototypeProperties(constructor)), false, false, false)}
    });
    return constructor;
}