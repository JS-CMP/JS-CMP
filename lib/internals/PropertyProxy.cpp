#include "internals/PropertyProxy.hpp"

#include "internals/Object.hpp"
#include "types/objects/JsObject.hpp"

namespace JS {

PropertyProxy& PropertyProxy::operator=(const Any& value) {
    obj_->put(key_, value);
    return *this;
}

PropertyProxy::operator JS::Any() { return obj_->get(key_); }

PropertyProxy::operator JS::Any() const { return obj_->get(key_); }

PropertyProxy PropertyProxy::operator[](const std::u16string& key) const {
    JS::Any any = obj_->get(key_);
    if (any.getValue().index() == JS::OBJECT) {
        return PropertyProxy(std::get<std::shared_ptr<JS::InternalObject>>(any.getValue()), key);
    }
    throw std::runtime_error("Property is not an object");
}
JS::Any PropertyProxy::call(const JS::Any& args) const {
    JS::Value value = obj_->get(key_).getValue();
    if (value.index() == JS::OBJECT) {
        auto Obj = std::get<std::shared_ptr<JS::InternalObject>>(value);
        if (Obj->isCallable()) {
            return Obj->call_function(JS::Any(obj_), args);
        }
    }
    throw std::runtime_error("Value is not a function");
}

JS::Any PropertyProxy::constructor(const JS::Any& args) const {
    JS::Value value = obj_->get(key_).getValue();
    if (value.index() == JS::OBJECT) {
        auto Obj = std::get<std::shared_ptr<JS::InternalObject>>(value);
        if (Obj->construct != nullptr) {
            return Obj->construct(JS::Any(obj_), args);
        }
    }
    throw std::runtime_error("Value does not have a constructor");
}

JS::Value PropertyProxy::getValue() const { return obj_->get(key_).getValue(); }

std::ostream& operator<<(std::ostream& os, const PropertyProxy& proxy) {
    os << static_cast<JS::Any>(proxy);
    return os;
}

bool PropertyProxy::operator==(const PropertyProxy& property_proxy) const {
    JS::Any lhs = obj_->get(key_);
    JS::Any rhs = property_proxy.obj_->get(property_proxy.key_);
    return lhs == rhs;
}

JS::Any PropertyProxy::operator!() const {
    const JS::Any any = obj_->get(key_);
    return !any;
}

} // namespace JS