#include "internals/PropertyProxy.hpp"

#include "internals/Object.hpp"
#include "types/objects/JsObject.hpp"
#include "utils/Convert.hpp"

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

JS::Any JS::PropertyProxy::call(const JS::Any& args) const {
    if (JS::IS::Callable(this->getValue())) {
        return std::get<std::shared_ptr<JS::InternalObject>>(this->getValue())
            ->call_function(JS::Any(this->obj_), args); // TODO fix this to pass the correct this aka global object
    }
    throw std::runtime_error("Value is not a function");
}

// Accessors
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
    obj_->put(key_, value, true);
}

void PropertyProxy::setValue(const JS::Value& value) {
    JS::Any tmp;
    tmp.setValue(value);
    obj_->put(key_, tmp);
}

} // namespace JS