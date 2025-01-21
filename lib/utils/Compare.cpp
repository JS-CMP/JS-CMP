#include "utils/Compare.hpp"

#include "types/objects/JsObject.hpp"

#include <cmath>

namespace JS::COMPARE {
bool Type(const JS::Any& a, const JS::Any& b) { return a.getValue().index() == b.getValue().index(); }

bool Type(const JS::Any& a, const JS::Types& b) { return a.getValue().index() == b; }

bool Type(const JS::Types& a, const JS::Any& b) { return a == b.getValue().index(); }
bool IsPrimitive(const JS::Any& a) {
    return a.getValue().index() == JS::NUMBER || a.getValue().index() == JS::STRING || a.getValue().index() == JS::BOOL;
}

bool IsCallable(const JS::Any& a) {
    if (JS::COMPARE::Type(a, JS::OBJECT)) {
        return std::get<std::shared_ptr<JS::InternalObject>>(a.getValue())->isCallable();
    } else {
        return false;
    }
}

bool IsAccessorDescriptor(const JS::Attribute& a) {
    if (a.index() == JS::ACCESSOR_DESCRIPTOR) {
        JS::AccessorDescriptor ad = std::get<JS::AccessorDescriptor>(a);
        return ad.get != nullptr || ad.set != nullptr;
    }
    return false;
}

bool IsDataDescriptor(const JS::Attribute& a) {
    if (a.index() == JS::DATA_DESCRIPTOR) {
        return !JS::COMPARE::Type(std::get<JS::DataDescriptor>(a).value, JS::UNDEFINED);
    }
    return false;
}

bool IsGenericDescriptor(const JS::Attribute& a) { return !IsDataDescriptor(a) && !IsAccessorDescriptor(a); }

bool SameValue(const JS::Any& a, const JS::Any& b) {
    if (!JS::COMPARE::Type(a, b)) {
        return false;
    }
    switch (a.getValue().index()) {
        case JS::NUMBER: {
            double a_val = std::get<double>(a.getValue());
            double b_val = std::get<double>(b.getValue());
            if (std::isnan(a_val) && std::isnan(b_val)) {
                return true;
            }
            if (a_val == 0.0 && b_val == 0.0) {
                return std::signbit(a_val) == std::signbit(b_val);
            }
            return a_val == b_val;
        }
        case JS::STRING:
            return std::get<Rope>(a.getValue()) == std::get<Rope>(b.getValue());
        case JS::BOOL:
            return std::get<bool>(a.getValue()) == std::get<bool>(b.getValue());
        case JS::UNDEFINED:
            return true;
        case JS::NULL_TYPE:
            return true;
        case JS::OBJECT:
            return std::get<std::shared_ptr<JS::InternalObject>>(a.getValue()).get() ==
                   std::get<std::shared_ptr<JS::InternalObject>>(b.getValue()).get();
    }
    return false;
}
} // namespace JS::COMPARE