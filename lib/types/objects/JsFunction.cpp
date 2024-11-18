#include <types/objects/JsFunction.hpp>
#include <utility>

namespace JS {
Function::Function(FunctionType f) : function(std::move(f)) {}
Function::Function(Function& f) : function(f.function) {}
Function::Function(Function&& f) noexcept : function(std::move(f.function)) {}
Function& Function::operator=(const Function& f) {
    this->function = f.function;
    return *this;
}
Function& Function::operator=(Function&& f) noexcept {
    this->function = std::move(f.function);
    return *this;
}
bool Function::isCallable() const { return true; }
} // namespace JS
