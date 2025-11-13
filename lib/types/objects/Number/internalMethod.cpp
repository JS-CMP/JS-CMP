#include "internals/Object.hpp"
#include "types/objects/JsNumber.hpp"
#include "utils/Convert.hpp"

#include <types/objects/Function/JsFunction.hpp>
#include <utils/Compare.hpp>

std::u16string JS::Number::getContent() const {
    return JS::CONVERT::ToString(this->primitiveValue);
}

std::shared_ptr<JS::Function> JS::Number::getConstructor() {
    auto prototype = Function::getPrototypeProperties();
    static auto constructor = JS::InternalObject::create<JS::Function>(
        [](const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
            if (JS::COMPARE::Type(args[u"0"], JS::UNDEFINED)) {
                return JS::Any(JS::InternalObject::create<JS::Number>());
            }
            return JS::Any(JS::InternalObject::create<JS::Number>(args[u"0"]));
        },
        1, NUMBER_CLASS_NAME, prototype);

    constructor->class_name = NUMBER_CLASS_NAME;
    constructor->extensible = true;
    constructor->prototype = prototype;
    constructor->properties = std::make_shared<JS::Properties>(JS::Properties{{u"length", JS::DataDescriptor{JS::Any(1), true, false, false}}, {u"name", JS::DataDescriptor{JS::Any(ERROR_CLASS_NAME), false, false, false}}, {u"MAX_VALUE", JS::DataDescriptor{JS::Any(JS::Number::MAX_VALUE), false, false, false}}, {u"MIN_VALUE", JS::DataDescriptor{JS::Any(JS::Number::MIN_VALUE), false, false, false}}, {u"NaN", JS::DataDescriptor{JS::Any(JS::Number::NaN), false, false, false}}, {u"NEGATIVE_INFINITY", JS::DataDescriptor{JS::Any(JS::Number::NEGATIVE_INFINITY), false, false, false}}, {u"POSITIVE_INFINITY", JS::DataDescriptor{JS::Any(JS::Number::POSITIVE_INFINITY), false, false, false}}, {u"prototype", JS::DataDescriptor(JS::Any(Number::getPrototypeProperties(constructor)), false, false, false)}});
    return constructor;
}