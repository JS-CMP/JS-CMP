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

PropertyProxy PropertyProxy::operator[](const std::string& key) {
    JS::Any any = obj_->get(key_);
    if (any.getValue().index() == JS::OBJECT) {
        return PropertyProxy(std::get<std::shared_ptr<JS::InternalObject>>(any.getValue()), key);
    }
    throw std::runtime_error("Property is not an object");
}
JS::Any PropertyProxy::call(const std::vector<JS::Any>& args) const {
    JS::Any any = obj_->get(key_);
    return any.call(args);
}

std::ostream& operator<<(std::ostream& os, const PropertyProxy& proxy) {
    os << static_cast<JS::Any>(proxy);
    return os;
}
} // namespace JS