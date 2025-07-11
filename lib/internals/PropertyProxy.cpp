#include "internals/PropertyProxy.hpp"

#include "internals/Object.hpp"
#include "types/objects/JsObject.hpp"

#include <utils/Is.hpp>

namespace JS {

PropertyProxy& PropertyProxy::operator=(const Any& value) {
    obj_->put(key_, value);
    return *this;
}

PropertyProxy::operator JS::Any() {
    return obj_->get(key_);
}

PropertyProxy::operator JS::Any() const {
    return obj_->get(key_);
}

JS::Any PropertyProxy::get() const {
    return obj_->get(key_);
}

JS::Any& PropertyProxy::get() {
    return obj_->get(key_).get();
}

JS::Value PropertyProxy::getValue() const {
    return obj_->get(key_).getValue();
}

void PropertyProxy::set(const JS::Any& value) {
    obj_->put(key_, value);
}

void PropertyProxy::setValue(const JS::Value& value) {
    JS::Any tmp;
    tmp.setValue(value);
    obj_->put(key_, tmp);
}

} // namespace JS