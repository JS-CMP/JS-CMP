#include "internals/Attribute.hpp"
#include "internals/Object.hpp"
#include "utils/Compare.hpp"
#include "utils/Is.hpp"

#include <types/objects/Error/JsNativeError.hpp>
#include <types/objects/Error/JsTypeError.hpp>
#include <types/objects/Function/JsFunction.hpp>
#include <unordered_set>
#include <utils/Convert.hpp>

namespace JS {
std::optional<JS::Attribute> JS::InternalObject::getOwnProperty(const std::u16string& key) const {

    if (!properties->contains(key)) {
        return std::nullopt;
    }
    return properties->at(key);
}

std::optional<JS::Attribute> InternalObject::getProperty(const std::u16string& key) const {
    auto prop = this->getOwnProperty(key);
    if (prop.has_value()) {
        return prop;
    }
    if (this->prototype == nullptr) {
        return std::nullopt;
    }
    static thread_local std::unordered_set<const InternalObject*> visited;
    if (visited.contains(this)) {
        return std::nullopt;
    }
    visited.insert(this);
    auto result = this->prototype->getProperty(key);
    visited.erase(this);
    return result;
}

JS::Any InternalObject::get(const std::u16string& key) const {
    auto desc = this->getProperty(key);
    if (!desc.has_value()) {
        return JS::Any(JS::Undefined{});
    }
    if (JS::IS::DataDescriptor(desc.value())) {
        return std::get<JS::DataDescriptor>(desc.value()).value;
    }
    if (JS::IS::AccessorDescriptor(desc.value())) {
        JS::AccessorDescriptor accessor = std::get<JS::AccessorDescriptor>(desc.value());
        return accessor.get == nullptr ? JS::Any(JS::Undefined{}) : (*accessor.get)();
    }
    throw std::runtime_error("Descriptor type cannot be determined");
}

bool InternalObject::canPut(const std::u16string& key) const {
    auto desc = this->getOwnProperty(key);
    if (desc.has_value()) {
        if (JS::IS::AccessorDescriptor(desc.value())) {
            return std::get<JS::AccessorDescriptor>(desc.value()).set != nullptr;
        }
        if (JS::IS::DataDescriptor(desc.value())) {
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
    if (JS::IS::AccessorDescriptor(inherited.value())) {
        return std::get<JS::AccessorDescriptor>(inherited.value()).set != nullptr;
    }
    if (JS::IS::DataDescriptor(inherited.value())) {
        return std::get<JS::DataDescriptor>(inherited.value()).writable;
    }
    throw std::runtime_error("Unexpected descriptor type");
}

void InternalObject::put(const std::u16string& key, const Any& value, bool is_throw) {
    bool canPut = this->canPut(key);
    if (!canPut) {
        if (is_throw) {
            throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Cannot put value")));
        }
        return;
    }
    auto ownDesc = this->getOwnProperty(key);
    if (ownDesc.has_value() && JS::IS::DataDescriptor(ownDesc.value())) {
        JS::DataDescriptor desc = std::get<JS::DataDescriptor>(ownDesc.value());
        desc.value = value;
        this->defineOwnProperty(key, desc, is_throw);
        return;
    }
    auto desc = this->getProperty(key);
    if (desc.has_value() && JS::IS::AccessorDescriptor(desc.value())) {
        JS::AccessorDescriptor accessor = std::get<JS::AccessorDescriptor>(desc.value());
        if (accessor.set == nullptr || !JS::IS::Callable(accessor.set)) {
            throw std::runtime_error("Unexpected descriptor type set of accessor descriptor is null");
        }
        accessor.set->call_function(JS::Any(shared_from_this()), JS::Arguments::CreateArgumentsObject({JS::Any(value)}));
        return;
    }
    this->defineOwnProperty(key, JS::DataDescriptor{value, true, true, true}, is_throw);
}

bool InternalObject::hasProperty(const std::u16string& key) const {
    return this->getProperty(key).has_value();
}

bool InternalObject::deleteProperty(const std::u16string& key, bool is_throw) {
    auto desc = this->getOwnProperty(key);
    if (!desc.has_value()) {
        return true;
    }
    if ((desc.value().index() == JS::DATA_DESCRIPTOR && std::get<JS::DataDescriptor>(desc.value()).configurable) || (desc.value().index() == JS::ACCESSOR_DESCRIPTOR && std::get<JS::AccessorDescriptor>(desc.value()).configurable)) {
        properties->erase(key);
        return true;
    }
    if (is_throw) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Cannot delete property")));
    }
    return false;
}

JS::Any InternalObject::defaultValue(const Types& hint) {
    switch (hint) {
        case STRING: {
            JS::Any toString = this->get(u"toString");
            if (JS::IS::Callable(toString)) {
                JS::Any str = std::get<std::shared_ptr<JS::InternalObject>>(toString.getValue())->call_function(JS::Any(shared_from_this()), JS::Arguments::CreateArgumentsObject({}));
                if (JS::IS::Primitive(str)) {
                    return str;
                }
            }
            JS::Any valueOf = this->get(u"valueOf");
            if (JS::IS::Callable(valueOf)) {
                JS::Any val = std::get<std::shared_ptr<JS::InternalObject>>(valueOf.getValue())->call_function(JS::Any(shared_from_this()), JS::Arguments::CreateArgumentsObject({}));
                if (JS::IS::Primitive(val)) {
                    return val;
                }
            }
            throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Cannot convert to primitive")));
        }
        case NUMBER: {
            JS::Any valueOf = this->get(u"valueOf");
            if (JS::IS::Callable(valueOf)) {
                JS::Any val = std::get<std::shared_ptr<JS::InternalObject>>(valueOf.getValue())->call_function(JS::Any(shared_from_this()), JS::Arguments::CreateArgumentsObject({}));
                if (JS::IS::Primitive(val)) {
                    return val;
                }
            }
            JS::Any toString = this->get(u"toString");
            if (JS::IS::Callable(toString)) {
                JS::Any str = std::get<std::shared_ptr<JS::InternalObject>>(toString.getValue())->call_function(JS::Any(shared_from_this()), JS::Arguments::CreateArgumentsObject({}));
                if (JS::IS::Primitive(str)) {
                    return str;
                }
            }
            throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Cannot convert to primitive")));
        }
        default:
            return this->defaultValue();
    }
}

JS::Any InternalObject::defaultValue() {
    if (this->class_name == u"Date") {
        return this->defaultValue(JS::STRING);
    }
    return this->defaultValue(JS::NUMBER);
}

bool InternalObject::defineOwnProperty(const std::u16string& key, Attribute desc, bool is_throw) {
    auto current = this->InternalObject::getOwnProperty(key);
    bool extensible = this->extensible;

    if (!current.has_value() && !extensible) {
        if (is_throw) {
            throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Cannot define property")));
        }
        return false;
    }

    if (!current.has_value() && extensible) {
        if (JS::IS::GenericDescriptor(desc) || JS::IS::DataDescriptor(desc)) {
            (*properties)[key] = JS::DataDescriptor{std::get<JS::DataDescriptor>(desc).value, std::get<JS::DataDescriptor>(desc).writable, std::get<JS::DataDescriptor>(desc).enumerable, std::get<JS::DataDescriptor>(desc).configurable};
        } else {
            (*properties)[key] = JS::AccessorDescriptor{std::get<JS::AccessorDescriptor>(desc).set, std::get<JS::AccessorDescriptor>(desc).get, std::get<JS::AccessorDescriptor>(desc).enumerable, std::get<JS::AccessorDescriptor>(desc).configurable};
        }
        return true;
    }

    if (JS::COMPARE::SameValue(desc, current.value())) {
        return true;
    }
    auto currentDesc = current.value();

    bool descEnumerable = JS::IS::DataDescriptor(desc) ? std::get<JS::DataDescriptor>(desc).enumerable : std::get<JS::AccessorDescriptor>(desc).enumerable;
    bool currentEnumerable = JS::IS::DataDescriptor(currentDesc) ? std::get<JS::DataDescriptor>(currentDesc).enumerable : std::get<JS::AccessorDescriptor>(currentDesc).enumerable;
    bool descConfigurable = JS::IS::DataDescriptor(desc) ? std::get<JS::DataDescriptor>(desc).configurable : std::get<JS::AccessorDescriptor>(desc).configurable;
    bool currentConfigurable = JS::IS::DataDescriptor(currentDesc) ? std::get<JS::DataDescriptor>(currentDesc).configurable : std::get<JS::AccessorDescriptor>(currentDesc).configurable;

    if (!currentConfigurable) {
        if (descConfigurable || descEnumerable != currentEnumerable) {
            if (is_throw) {
                throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Cannot redefine property")));
            }
            return false;
        }
    }

    if (JS::IS::GenericDescriptor(desc)) {
        // No further validation required
    } else if (JS::IS::DataDescriptor(currentDesc) != JS::IS::DataDescriptor(desc)) {
        if (!currentConfigurable) {
            if (is_throw) {
                throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Cannot redefine property")));
            }
            return false;
        }
        if (JS::IS::DataDescriptor(currentDesc)) {
            JS::AccessorDescriptor newDesc = std::get<JS::AccessorDescriptor>(desc);
            newDesc.configurable = currentConfigurable;
            newDesc.enumerable = currentEnumerable;
        } else {
            JS::DataDescriptor newDesc = std::get<JS::DataDescriptor>(desc);
            newDesc.configurable = currentConfigurable;
            newDesc.enumerable = currentEnumerable;
        }
    } else if (JS::IS::DataDescriptor(currentDesc)) {
        auto oldDesc = std::get<JS::DataDescriptor>(currentDesc);
        auto newDesc = std::get<JS::DataDescriptor>(desc);
        if (!oldDesc.configurable) {
            if (!oldDesc.writable && newDesc.writable) {
                if (is_throw) {
                    throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Cannot redefine property")));
                }
                return false;
            }
            if (!oldDesc.writable && !JS::COMPARE::SameValue(newDesc.value, oldDesc.value)) {
                if (is_throw) {
                    throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Cannot redefine property")));
                }
                return false;
            }
        }
    } else {
        auto oldDesc = std::get<JS::AccessorDescriptor>(currentDesc);
        auto newDesc = std::get<JS::AccessorDescriptor>(desc);
        if (!oldDesc.configurable) {
            if (newDesc.get && JS::COMPARE::SameValue(newDesc.get, oldDesc.get)) {
                if (is_throw) {
                    throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Cannot redefine property")));
                }
                return false;
            }
            if (newDesc.set && newDesc.set != oldDesc.set) {
                if (is_throw) {
                    throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Cannot redefine property")));
                }
                return false;
            }
        }
    }
    (*properties)[key] = desc;
    return true;
}

bool InternalObject::hasInstance(const JS::Any& value) const {
    throw JS::Any(JS::InternalObject::create<JS::NativeError>(JS::Any("hasInstance not implemented for this object")));
}

std::optional<JS::Match> InternalObject::match(const std::u16string& string, uint32_t index) const {
    throw JS::Any(JS::InternalObject::create<JS::NativeError>(JS::Any("match not implemented for this object")));
}

std::u16string InternalObject::getContent() const {
    throw JS::Any(JS::InternalObject::create<JS::NativeError>(JS::Any("getContent not implemented for this object")));
}

void InternalObject::initialize(std::shared_ptr<JS::InternalObject> prototype) {}

} // namespace JS