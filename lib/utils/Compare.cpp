#include "utils/Compare.hpp"

#include "types/objects/JsObject.hpp"

#include <cmath>
#include <types/objects/Error/JsTypeError.hpp>

namespace JS::COMPARE {
bool Type(const JS::Operator& a, const JS::Operator& b) {
    return a.getValue().index() == b.getValue().index();
}

bool Type(const JS::Operator& a, const JS::Types& b) {
    return a.getValue().index() == b;
}

bool Type(const JS::Types& a, const JS::Operator& b) {
    return a == b.getValue().index();
}

bool Object(const JS::Operator& obj, const std::u16string& class_name) {
    return obj.getValue().index() == JS::OBJECT &&
           std::get<std::shared_ptr<JS::InternalObject>>(obj.getValue())->class_name == class_name;
}

bool SameValue(const double& a, const double& b) {
    if (std::isnan(a) && std::isnan(b)) {
        return true;
    }
    if (a == 0.0 && b == 0.0) {
        return std::signbit(a) == std::signbit(b);
    }
    return a == b;
}

bool SameValue(const Rope& a, const Rope& b) {
    return a == b;
}

bool SameValue(const bool& a, const bool& b) {
    return a == b;
}

bool SameValue(JS::Undefined a, JS::Undefined b) {
    return true;
}

bool SameValue(JS::Null a, JS::Null b) {
    return true;
}

bool SameValue(const std::shared_ptr<JS::InternalObject>& a, const std::shared_ptr<JS::InternalObject>& b) {
    return a.get() == b.get();
}

bool SameValue(const JS::Operator& a, const JS::Operator& b) {
    if (!JS::COMPARE::Type(a, b)) {
        return false;
    }
    switch (a.getValue().index()) {
        case JS::NUMBER:
            return SameValue(std::get<double>(a.getValue()), std::get<double>(b.getValue()));
        case JS::STRING:
            return SameValue(std::get<Rope>(a.getValue()), std::get<Rope>(b.getValue()));
        case JS::BOOLEAN:
            return SameValue(std::get<bool>(a.getValue()), std::get<bool>(b.getValue()));
        case JS::UNDEFINED:
            return true;
        case JS::NULL_TYPE:
            return true;
        case JS::OBJECT:
            return SameValue(std::get<std::shared_ptr<JS::InternalObject>>(a.getValue()),
                             std::get<std::shared_ptr<JS::InternalObject>>(b.getValue()));
    }
    return false;
}

bool SameValue(const JS::Attribute& a, const JS::Attribute& b) {
    if (a.index() != b.index()) {
        return false;
    }
    switch (a.index()) {
        case JS::DATA_DESCRIPTOR: {
            JS::DataDescriptor ad_a = std::get<JS::DataDescriptor>(a);
            JS::DataDescriptor ad_b = std::get<JS::DataDescriptor>(b);
            return SameValue(ad_a.value, ad_b.value) && ad_a.writable == ad_b.writable &&
                   ad_a.enumerable == ad_b.enumerable && ad_a.configurable == ad_b.configurable;
        }
        case JS::ACCESSOR_DESCRIPTOR: {
            JS::AccessorDescriptor ad_a = std::get<JS::AccessorDescriptor>(a);
            JS::AccessorDescriptor ad_b = std::get<JS::AccessorDescriptor>(b);
            return SameValue(ad_a.get, ad_b.get) && SameValue(ad_a.set, ad_b.set) &&
                   ad_a.enumerable == ad_b.enumerable && ad_a.configurable == ad_b.configurable;
        }
    }
    return false;
}

void CheckObjectCoercible(const JS::Operator& any) {
    switch (any.getValue().index()) {
        case JS::UNDEFINED:
        case JS::NULL_TYPE:
            throw JS::Any(std::make_shared<JS::TypeError>(JS::Any("Cannot convert undefined or null to object")));
        default:
            return;
    }
}
} // namespace JS::COMPARE