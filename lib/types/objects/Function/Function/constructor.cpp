#include <types/objects/Function/JsFunction.hpp>
#include <utility>

namespace JS {

Function::Function() : JS::InternalObject({}, getPrototypeProperties(), u"Function", true) {
    call_function = [](const JS::Any&, const JS::Any&) -> JS::Any { return JS::Any(JS::Undefined{}); };
    construct = [](const JS::Any&, const JS::Any&) -> JS::Any { return JS::Any(JS::Undefined{}); };
    JS::InternalObject::defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(0), false, false, false}, false);
}

// TODO: Implement the correct call to constructor
Function::Function(FunctionType f, int length) : JS::InternalObject({}, getPrototypeProperties(), u"Function", true) {
    construct = f; // TODO : fix the fact that you can't double move
    call_function = std::move(f);
    JS::InternalObject::defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(length), false, false, false}, false);
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