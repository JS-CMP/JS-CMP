#include <types/objects/Function/JsFunction.hpp>

#include "internals/Object.hpp"
#include "types/objects/JsArray.hpp"
#include "utils/Convert.hpp"

std::u16string JS::Array::getContent() const {
    return JS::CONVERT::ArrayToString(shared_from_this());
}

std::shared_ptr<JS::Function> JS::Array::getConstructor() {
    auto prototype = Function::getPrototypeProperties();
    static auto constructor = std::make_shared<JS::Function>([] (const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
        return JS::Any(std::make_shared<JS::Array>(args));
    }, 1, ARRAY_CLASS_NAME, prototype);

    constructor->class_name = ARRAY_CLASS_NAME;
    constructor->extensible = true;
    constructor->prototype = prototype;
    constructor->properties = std::make_shared<JS::Properties>(JS::Properties{
        {u"length", JS::DataDescriptor{JS::Any(1), true, false, false}},
        {u"name", JS::DataDescriptor{JS::Any(ARRAY_CLASS_NAME), false, false, false}},
        {u"isArray", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::isArray)), true, true, true}},
    });
    return constructor;
}

