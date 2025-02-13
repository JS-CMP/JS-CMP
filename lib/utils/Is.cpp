#include "types/objects/JsObject.hpp"
#include "utils/Compare.hpp"

#include <cmath>

namespace JS::IS {
bool Primitive(const JS::Any& a) {
    return a.getValue().index() == JS::NUMBER || a.getValue().index() == JS::STRING || a.getValue().index() == JS::BOOLEAN;
}

bool Callable(const JS::Any& a) {
    if (JS::COMPARE::Type(a, JS::OBJECT)) {
        return std::get<std::shared_ptr<JS::InternalObject>>(a.getValue())->isCallable();
    } else {
        return false;
    }
}

bool Callable(const std::shared_ptr<JS::InternalObject>& a) { return a->isCallable(); }

bool AccessorDescriptor(const JS::Attribute& a) {
    if (a.index() == JS::ACCESSOR_DESCRIPTOR) {
        JS::AccessorDescriptor ad = std::get<JS::AccessorDescriptor>(a);
        return ad.get != nullptr || ad.set != nullptr;
    }
    return false;
}

bool DataDescriptor(const JS::Attribute& a) {
    if (a.index() == JS::DATA_DESCRIPTOR) {
        return !JS::COMPARE::Type(std::get<JS::DataDescriptor>(a).value, JS::UNDEFINED);
    }
    return false;
}

bool GenericDescriptor(const JS::Attribute& a) { return !DataDescriptor(a) && !AccessorDescriptor(a); }
} // namespace JS::IS
