#include "types/objects/Function/JsFunctionBinded.hpp"


namespace JS {
JS::Any FunctionBinded::get(const std::string& key) const {
    if (key == "caller") {
        throw std::runtime_error("TypeError: Cannot access 'caller' or 'arguments.callee' in strict mode"); // TypeError
    }
    return InternalObject::get(key);
}
} // namespace JS