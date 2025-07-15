#include "utils/Compare.hpp"

#include <types/objects/Function/JsFunction.hpp>
#include <utility>

namespace JS {

Function::Function() : JS::InternalObject({}, getPrototypeProperties(), u"Function", true) {
    call_function = [](const JS::Any&, const JS::Any&) -> JS::Any { return JS::Any(std::make_shared<JS::Object>()); };
    construct = [](const JS::Any&, const JS::Any&) -> JS::Any { return JS::Any(JS::Undefined{}); };
    JS::InternalObject::defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(0), false, false, false}, false);
    JS::InternalObject::defineOwnProperty(u"name", JS::DataDescriptor{JS::Any(u"anonymous"), false, false, false},
                                          false);
    JS::InternalObject::defineOwnProperty(
        u"prototype", JS::DataDescriptor{JS::Any(getPrototypeProperties()), false, false, false}, false);
}

Function::Function(FunctionType f, int length, const std::u16string& name)
    : JS::InternalObject({}, getPrototypeProperties(), u"Function", true) {
    construct = [f](const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
        auto obj = std::make_shared<JS::Object>();
        if (JS::COMPARE::Type(thisArg, JS::OBJECT)) {
            auto funcObj = std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue());
            if (funcObj && funcObj->hasProperty(u"prototype")) {
                JS::Any proto = funcObj->get(u"prototype");
                if (JS::COMPARE::Type(proto, JS::OBJECT)) {
                    obj->prototype = std::get<std::shared_ptr<JS::InternalObject>>(proto.getValue());
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
    JS::InternalObject::defineOwnProperty(
        u"prototype", JS::DataDescriptor{JS::Any(getPrototypeProperties()), false, false, false}, false);
}
Function::Function(FunctionType f, std::shared_ptr<InternalObject> prototype)
    : JS::InternalObject({}, prototype, u"Function", true) {
    construct = [f](const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
        auto obj = std::make_shared<JS::Object>();
        if (JS::COMPARE::Type(thisArg, JS::OBJECT)) {
            auto funcObj = std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue());
            if (funcObj && funcObj->hasProperty(u"prototype")) {
                JS::Any proto = funcObj->get(u"prototype");
                if (JS::COMPARE::Type(proto, JS::OBJECT)) {
                    obj->prototype = std::get<std::shared_ptr<JS::InternalObject>>(proto.getValue());
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
    // TODO add length and name properties if needed
}

// Static constructor for Function
Function::Function(const JS::Properties& properties)
    : JS::InternalObject(properties, getPrototypeProperties(), u"Function", true) {
    InternalObject::defineOwnProperty(
        u"prototype", JS::DataDescriptor{JS::Any(getPrototypeProperties()), false, false, false}, false);
    this->call_function = &JS::Function::internal_constructor;
    this->construct = &JS::Function::internal_constructor;
}

Function::Function(Function&& f) noexcept : JS::InternalObject({}, getPrototypeProperties(), u"Function", true) {
    call_function = std::move(f.call_function);
}

Function& Function::operator=(const Function& function) {
    if (this == &function) {
        return *this;
    }
    this->call_function = function.call_function;
    return *this;
}

Function& Function::operator=(Function&& f) noexcept {
    this->call_function = std::move(f.call_function);
    return *this;
}
} // namespace JS