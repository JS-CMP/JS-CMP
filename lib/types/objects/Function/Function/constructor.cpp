#include <types/objects/Function/JsFunction.hpp>
#include <utility>

namespace JS {

std::unordered_map<std::string, JS::Any> function_properties_prototype = {
    {"toString", JS::Any(std::make_shared<JS::Function>(Function::toString))},
    {"apply", JS::Any(std::make_shared<JS::Function>(Function::apply))},
    {"bind", JS::Any(std::make_shared<JS::Function>(Function::bind))},
    {"call", JS::Any(std::make_shared<JS::Function>(Function::call))},
};
std::shared_ptr<JS::InternalObject> function_prototype = std::make_shared<JS::Object>(function_properties_prototype);

Function::Function() : JS::InternalObject({}, JS::function_prototype, "Function", true) {
    call_function = [](const JS::Any&, const JS::Any&) -> JS::Any { return JS::Any(JS::Undefined{}); };
    JS::InternalObject::defineOwnProperty("length", JS::DataDescriptor{JS::Any(0), false, false, false}, false);
}

// TODO: Implement the correct call to constructor
Function::Function(FunctionType f, int length) : JS::InternalObject({}, JS::function_prototype, "Function", true) {
    call_function = std::move(f);
    JS::InternalObject::defineOwnProperty("length", JS::DataDescriptor{JS::Any(length), false, false, false}, false);
}

Function::Function(Function&& f) noexcept : JS::InternalObject({}, JS::function_prototype, "Function", true) {
    call_function = std::move(f.call_function);
}

Function& Function::operator=(const Function& function) {
    this->call_function = function.call_function;
    return *this;
}

Function& Function::operator=(Function&& f) noexcept {
    this->call_function = std::move(f.call_function);
    return *this;
}
} // namespace JS