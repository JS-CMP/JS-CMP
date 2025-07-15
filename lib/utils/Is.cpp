#include "types/objects/JsObject.hpp"
#include "utils/Compare.hpp"

#include <cmath>
#include <utils/Convert.hpp>

namespace JS::IS {
bool Primitive(const JS::Operator& a) {
    return a.getValue().index() == JS::NUMBER || a.getValue().index() == JS::STRING ||
           a.getValue().index() == JS::BOOLEAN;
}

bool Callable(const JS::Operator& a) {
    return JS::COMPARE::Type(a, JS::OBJECT) &&
           std::get<std::shared_ptr<JS::InternalObject>>(a.getValue())->isCallable();
}

bool Callable(const JS::Value& a) {
    return a.index() == JS::OBJECT && std::get<std::shared_ptr<JS::InternalObject>>(a)->isCallable();
}

bool Callable(const std::shared_ptr<JS::InternalObject>& a) {
    return a->isCallable();
}

bool AccessorDescriptor(const JS::Attribute& a) {
    if (a.index() == JS::ACCESSOR_DESCRIPTOR) {
        JS::AccessorDescriptor ad = std::get<JS::AccessorDescriptor>(a);
        return ad.get != nullptr || ad.set != nullptr;
    }
    return false;
}

bool DataDescriptor(const JS::Attribute& a) {
    if (a.index() == JS::DATA_DESCRIPTOR) {
        return true;
    }
    return false;
}

bool GenericDescriptor(const JS::Attribute& a) {
    return !DataDescriptor(a) && !AccessorDescriptor(a);
}

bool ArrayIndex(const std::u16string& key) {
    uint32_t index = JS::CONVERT::ToUint32(key);
    return JS::CONVERT::ToString(index) == key && index != std::numeric_limits<uint32_t>::max();
}
} // namespace JS::IS
