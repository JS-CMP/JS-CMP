#include "internals/PropertyProxy.hpp"
#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsObject.hpp"

#include <utility>

namespace JS {

Object::Object(const std::unordered_map<std::u16string, JS::Any>& properties)
    : JS::InternalObject({}, getPrototypeProperties(), OBJECT_CLASS_NAME, true) {
    for (const auto& [key, value] : properties) {
        this->InternalObject::put(key, value);
    }
}

} // namespace JS