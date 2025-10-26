#include "utils/Compare.hpp"

#include <types/objects/Function/JsFunction.hpp>
#include <utility>

namespace JS {

Function::Function(FunctionType f, int length, const std::u16string& name) : JS::InternalObject({}, getPrototypeProperties(), FUNCTION_CLASS_NAME, true) {
    construct = [f](const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
        auto obj = JS::InternalObject::create<JS::Object>();
        if (JS::COMPARE::Type(thisArg, JS::OBJECT)) {
            auto funcObj = std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue());
            if (funcObj && funcObj->hasProperty(u"prototype")) {
                JS::Any proto = funcObj->get(u"prototype");
                if (JS::COMPARE::Type(proto, JS::OBJECT)) {
                    obj->prototype = std::move(std::get<std::shared_ptr<JS::InternalObject>>(proto.getValue()));
                }
            }
        }
        JS::Any result = f(JS::Any(obj), args);
        if (JS::COMPARE::Type(result, JS::OBJECT)) {
            return result;
        }
        return JS::Any(obj);
    };
    call_function = std::move(f);
    JS::InternalObject::defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(length), false, false, false}, false);
    JS::InternalObject::defineOwnProperty(u"name", JS::DataDescriptor{JS::Any(name), false, false, false}, false);
}

Function::Function(FunctionType f, int length, const std::u16string& name, const std::shared_ptr<InternalObject>& prototype) : JS::InternalObject({}, prototype, FUNCTION_CLASS_NAME, true) {
    construct = [f](const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
        auto obj = JS::InternalObject::create<JS::Object>();
        if (JS::COMPARE::Type(thisArg, JS::OBJECT)) {
            auto funcObj = std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue());
            if (funcObj && funcObj->hasProperty(u"prototype")) {
                JS::Any proto = funcObj->get(u"prototype");
                if (JS::COMPARE::Type(proto, JS::OBJECT)) {
                    obj->prototype = std::move(std::get<std::shared_ptr<JS::InternalObject>>(proto.getValue()));
                }
            }
        }
        JS::Any result = f(JS::Any(obj), args);
        if (JS::COMPARE::Type(result, JS::OBJECT)) {
            return result;
        }
        return JS::Any(obj);
    };
    call_function = std::move(f);
    JS::InternalObject::defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(length), false, false, false}, false);
    JS::InternalObject::defineOwnProperty(u"name", JS::DataDescriptor{JS::Any(name), false, false, false}, false);
}

void Function::initialize(std::shared_ptr<InternalObject> prototype) {
    this->defineOwnProperty(u"prototype", JS::DataDescriptor{JS::Any(prototype ? prototype : getPrototypePropertiesCopy(shared_from_this(), this->prototype)), true, false, false}, true);
}

} // namespace JS