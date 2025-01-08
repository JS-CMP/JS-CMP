#include "internals/Object.hpp"
#include "types/objects/JsFunction.hpp"
#include "utils/Convert.hpp"

namespace JS {

void Object::init() {
    for (const auto& func : functions) {
        this->put(func.first, JS::Any(std::make_shared<JS::Function>(func.second)), true);
    }
}
} // namespace JS