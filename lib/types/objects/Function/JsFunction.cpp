#include "types/objects/JsFunction.hpp"
#include <utility>

namespace JS {
Function::Function(FunctionType f) : JS::InternalObject({}, nullptr, "Function", true) { call = std::move(f); }

Function::Function(const Function& f) : JS::InternalObject({}, nullptr, "Function", true) { call = std::move(f); }

Function::Function(Function&& f) noexcept : JS::InternalObject({}, nullptr, "Function", true) {
    call = std::move(f.call);
}

Function& Function::operator=(const Function& function) {
    this->call = function.call;
    return *this;
}

Function& Function::operator=(Function&& f) noexcept {
    this->call = std::move(f.call);
    return *this;
}
} // namespace JS