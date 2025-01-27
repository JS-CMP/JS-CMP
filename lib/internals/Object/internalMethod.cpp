#include "internals/Attribute.hpp"
#include "internals/Object.hpp"
#include "utils/Compare.hpp"

namespace JS {
std::optional<JS::Attribute> JS::InternalObject::getOwnProperty(const std::string& key) const {

    if (!properties->contains(key)) {
        return std::nullopt;
    }
    return properties->at(key);
}

std::optional<JS::Attribute> InternalObject::getProperty(const std::string& key) const {
    auto prop = this->getOwnProperty(key);
    if (prop.has_value()) {
        return prop;
    }
    if (this->prototype == nullptr) {
        return std::nullopt;
    }
    return this->prototype->getProperty(key);
}

JS::Any InternalObject::get(const std::string& key) const {
    auto desc = this->getProperty(key);
    if (!desc.has_value()) {
        return JS::Any(JS::Undefined{});
    }
    if (JS::COMPARE::IsDataDescriptor(desc.value())) {
        return std::get<JS::DataDescriptor>(desc.value()).value;
    }
    if (JS::COMPARE::IsAccessorDescriptor(desc.value())) {
        JS::AccessorDescriptor accessor = std::get<JS::AccessorDescriptor>(desc.value());
        return accessor.get == nullptr ? JS::Any(JS::Undefined{}) : (*accessor.get)();
    }
    throw std::runtime_error("Descriptor type cannot be determined");
}

bool InternalObject::canPut(const std::string& key) const {
    auto desc = this->getOwnProperty(key);
    if (desc.has_value()) {
        if (JS::COMPARE::IsAccessorDescriptor(desc.value())) {
            return std::get<JS::AccessorDescriptor>(desc.value()).set != nullptr;
        }
        if (JS::COMPARE::IsDataDescriptor(desc.value())) {
            return std::get<JS::DataDescriptor>(desc.value()).writable;
        }
        throw std::runtime_error("Unexpected descriptor type");
    }
    if (this->prototype == nullptr) {
        return this->extensible;
    }
    auto inherited = this->prototype->getProperty(key);
    if (!inherited.has_value()) {
        return this->extensible;
    }
    if (JS::COMPARE::IsAccessorDescriptor(inherited.value())) {
        return std::get<JS::AccessorDescriptor>(inherited.value()).set != nullptr;
    }
    if (JS::COMPARE::IsDataDescriptor(inherited.value())) {
        return std::get<JS::DataDescriptor>(inherited.value()).writable;
    }
    throw std::runtime_error("Unexpected descriptor type");
}

void InternalObject::put(const std::string& key, const Any& value, bool is_throw) {
    bool canPut = this->canPut(key);
    if (!canPut) {
        if (is_throw) {
            throw std::runtime_error("Cannot put value"); // TODO: TypeError
        }
        return;
    }
    auto ownDesc = this->getOwnProperty(key);
    if (ownDesc.has_value() && JS::COMPARE::IsDataDescriptor(ownDesc.value())) {
        this->defineOwnProperty(key, JS::DataDescriptor{value}, is_throw);
        return;
    }
    auto desc = this->getProperty(key);
    if (desc.has_value() && JS::COMPARE::IsAccessorDescriptor(desc.value())) {
        JS::AccessorDescriptor accessor = std::get<JS::AccessorDescriptor>(desc.value());
        if (accessor.set == nullptr) {
            throw std::runtime_error("Unexpected descriptor type set of accessor descriptor is null");
        }
        (*accessor.set)(value);
        return;
    } else {
        this->defineOwnProperty(key, JS::DataDescriptor{value, true, true, true}, is_throw);
    }
}

bool InternalObject::hasProperty(const std::string& key) const { return this->getProperty(key).has_value(); }

bool InternalObject::deleteProperty(const std::string& key, bool is_throw) {
    auto desc = this->getOwnProperty(key);
    if (!desc.has_value()) {
        return true;
    }
    if ((desc.value().index() == JS::DATA_DESCRIPTOR && !std::get<JS::DataDescriptor>(desc.value()).configurable) ||
        (desc.value().index() == JS::ACCESSOR_DESCRIPTOR &&
         !std::get<JS::AccessorDescriptor>(desc.value()).configurable)) {
        properties->erase(key);
        return true;
    }
    if (is_throw) {
        throw std::runtime_error("Cannot delete property"); // TODO: TypeError
    }
    return false;
}
JS::Any InternalObject::defaultValue(const Types& hint) {
    switch (hint) {
        case STRING: {
            JS::Any toString = this->get("toString");
            if (JS::COMPARE::IsCallable(toString)) {
                JS::Any str = toString(JS::Any(shared_from_this()));
                if (JS::COMPARE::IsPrimitive(str)) {
                    return str;
                }
            }
            JS::Any valueOf = this->get("valueOf");
            if (JS::COMPARE::IsCallable(valueOf)) {
                JS::Any val = valueOf(JS::Any(shared_from_this()));
                if (JS::COMPARE::IsPrimitive(val)) {
                    return val;
                }
            }
            throw std::runtime_error("Cannot convert to primitive"); // TODO: TypeError
        }
        case NUMBER: {
            JS::Any valueOf = this->get("valueOf");
            if (JS::COMPARE::IsCallable(valueOf)) {
                JS::Any val = valueOf(JS::Any(shared_from_this()));
                if (JS::COMPARE::IsPrimitive(val)) {
                    return val;
                }
            }
            JS::Any toString = this->get("toString");
            if (JS::COMPARE::IsCallable(toString)) {
                JS::Any str = toString(JS::Any(shared_from_this()));
                if (JS::COMPARE::IsPrimitive(str)) {
                    return str;
                }
            }
            throw std::runtime_error("Cannot convert to primitive"); // TODO: TypeError
        }
        default:
            return this->defaultValue();
    }
}

JS::Any InternalObject::defaultValue() {
    if (this->class_name == "Date") {
        return this->defaultValue(JS::STRING);
    }
    return this->defaultValue(JS::NUMBER);
}

bool InternalObject::defineOwnProperty(const std::string& key, Attribute desc, bool is_throw) {
    auto current = this->getOwnProperty(key);
    bool extensible = this->extensible;

    if (!current.has_value() && !extensible) {
        if (is_throw) {
            throw std::runtime_error("Cannot define property"); // TypeError
        }
        return false;
    }

    if (!current.has_value() && extensible) {
        if (JS::COMPARE::IsGenericDescriptor(desc) || JS::COMPARE::IsDataDescriptor(desc)) {
            (*properties)[key] = JS::DataDescriptor{
                std::get<JS::DataDescriptor>(desc).value, std::get<JS::DataDescriptor>(desc).writable,
                std::get<JS::DataDescriptor>(desc).enumerable, std::get<JS::DataDescriptor>(desc).configurable};
        } else {
            (*properties)[key] = JS::AccessorDescriptor{
                std::get<JS::AccessorDescriptor>(desc).set, std::get<JS::AccessorDescriptor>(desc).get,
                std::get<JS::AccessorDescriptor>(desc).enumerable, std::get<JS::AccessorDescriptor>(desc).configurable};
        }
        return true;
    }
    if (JS::COMPARE::IsDataDescriptor(current.value()) && JS::COMPARE::IsDataDescriptor(desc)) {
        JS::DataDescriptor currentDesc = std::get<JS::DataDescriptor>(current.value());
        JS::DataDescriptor newDesc = std::get<JS::DataDescriptor>(desc);
        if (!currentDesc.configurable) {
            if (!newDesc.configurable) {
                if (newDesc.writable != currentDesc.writable) {
                    if (is_throw) {
                        throw std::runtime_error("Cannot define property"); // TypeError
                    }
                    return false;
                }
                if (!newDesc.writable) {
                    if (newDesc.value != currentDesc.value) {
                        if (is_throw) {
                            throw std::runtime_error("Cannot define property"); // TypeError
                        }
                        return false;
                    }
                }
            }
        }
        properties->operator[](key) =
            JS::DataDescriptor{newDesc.value, newDesc.writable, newDesc.enumerable, newDesc.configurable};
    } else if (JS::COMPARE::IsAccessorDescriptor(current.value()) && JS::COMPARE::IsAccessorDescriptor(desc)) {
        JS::AccessorDescriptor currentDesc = std::get<JS::AccessorDescriptor>(current.value());
        JS::AccessorDescriptor newDesc = std::get<JS::AccessorDescriptor>(desc);
        if (!currentDesc.configurable) {
            if (!newDesc.configurable) {
                if (newDesc.set.get() != currentDesc.set.get() || newDesc.get.get() != currentDesc.get.get()) {
                    if (is_throw) {
                        throw std::runtime_error("Cannot define property"); // TypeError
                    }
                    return false;
                }
            }
        }
        properties->operator[](key) =
            JS::AccessorDescriptor{newDesc.set, newDesc.get, newDesc.enumerable, newDesc.configurable};

    } else {
        if (JS::COMPARE::IsDataDescriptor(current.value())) {
            JS::DataDescriptor currentDesc = std::get<JS::DataDescriptor>(current.value());
            if (!currentDesc.configurable) {
                if (is_throw) {
                    throw std::runtime_error("Cannot define property"); // TypeError
                }
                return false;
            }
            JS::AccessorDescriptor newDesc = std::get<JS::AccessorDescriptor>(desc);
            (*properties)[key] =
                JS::AccessorDescriptor{newDesc.get, newDesc.set, currentDesc.enumerable, currentDesc.configurable};
        } else {
            JS::AccessorDescriptor currentDesc = std::get<JS::AccessorDescriptor>(current.value());
            if (!currentDesc.configurable) {
                if (is_throw) {
                    throw std::runtime_error("Cannot define property"); // TypeError
                }
                return false;
            }
            JS::DataDescriptor newDesc = std::get<JS::DataDescriptor>(desc);
            (*properties)[key] =
                JS::DataDescriptor{newDesc.value, false, currentDesc.enumerable, currentDesc.configurable};
        }
    }
    return true;
}
} // namespace JS