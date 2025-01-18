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

PropertyProxy PropertyProxy::operator[](const std::string& key) const {
    JS::Any any = obj_->get(key_);
    if (any.getValue().index() == JS::OBJECT) {
        return PropertyProxy(std::get<std::shared_ptr<JS::InternalObject>>(any.getValue()), key);
    }
    throw std::runtime_error("Property is not an object");
}
JS::Any PropertyProxy::call(const std::vector<JS::Any>& args) const {
    JS::Any any = obj_->get(key_);
    JS::Value value = any.getValue();
    if (value.index() == JS::OBJECT && std::get<std::shared_ptr<JS::InternalObject>>(value)->isCallable()) {
        JS::Any thisArg = JS::Any(obj_);
        std::vector<JS::Any> arguments = {thisArg};
        arguments.insert(arguments.end(), args.begin(), args.end());
        return std::get<std::shared_ptr<JS::InternalObject>>(value)->operator()(arguments);
    }
    throw std::runtime_error("Value is not a function");
}

std::ostream& operator<<(std::ostream& os, const PropertyProxy& proxy) {
    os << static_cast<JS::Any>(proxy);
    return os;
}
} // namespace JS