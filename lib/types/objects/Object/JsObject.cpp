#include "types/objects/JsObject.hpp"
#include "types/objects/JsFunction.hpp"
#include "utils/Convert.hpp"

namespace JS {

void Object::init() {
    (*properties)["getPrototypeOf"] = JS::Attribute(JS::Any(
        std::make_shared<JS::Function>(JS::Function([self = shared_from_this()](const std::vector<JS::Any>& args) {
            if (args.empty() || args[0].getValue().index() != JS::OBJECT) {
                throw std::runtime_error(
                    "TypeError: Object.getPrototypeOf called on non-object"); // TODO: make this a JS error
            }
            return std::get<std::shared_ptr<JS::Object>>(args[0].getValue())->getPrototype();
        }))));

    (*properties)["getOwnPropertyDescriptor"] = JS::Attribute(JS::Any(
        std::make_shared<JS::Function>(JS::Function([self = shared_from_this()](const std::vector<JS::Any>& args) {
            if (args.empty() || args[0].getValue().index() != JS::OBJECT) {
                throw std::runtime_error(
                    "TypeError: Object.getOwnPropertyDescriptor called on non-object"); // TODO: make this a JS error
            }
            std::shared_ptr<JS::Object> obj = std::get<std::shared_ptr<JS::Object>>(args[0].getValue());
            if (args.size() < 2) {
                return JS::Any();
            }
            return obj->getPropertyDescriptor(JS::CONVERT::ToString(args[1]));
        }))));

    (*properties)["getOwnPropertyNames"] = JS::Attribute(JS::Any(
        std::make_shared<JS::Function>(JS::Function([self = shared_from_this()](const std::vector<JS::Any>& args) {
            return JS::Any(); // TODO: implement this need ARRAY for it
        }))));

    (*properties)["create"] = JS::Attribute(JS::Any(
        std::make_shared<JS::Function>(JS::Function([self = shared_from_this()](const std::vector<JS::Any>& args) {
            if (args.empty() || args[0].getValue().index() != JS::OBJECT) {
                throw std::runtime_error("TypeError: Object.create called on non-object"); // TODO: make this a JS error
            }
            std::shared_ptr<JS::Object> obj = std::get<std::shared_ptr<JS::Object>>(args[0].getValue());
            if (args.size() < 2) {
                return obj->create();
            }
            std::shared_ptr<JS::Object> proto = std::get<std::shared_ptr<JS::Object>>(args[1].getValue());
            return obj->create(proto);
        }))));
}

JS::Any Object::getPrototype() { // TODO https://262.ecma-international.org/5.1/#sec-15.2.3.2
    return {};
}
JS::Any Object::getPropertyDescriptor(std::string key) {
    if (properties->find(key) == properties->end()) {
        return {};
    }
    return JS::Any(std::make_shared<JS::Object>(properties->at(key)));
}

JS::Any Object::create() {
    // should return himself
    return JS::Any(shared_from_this());
}

JS::Any Object::create(std::shared_ptr<JS::Object> properties) {
    JS::Any obj = JS::Any(shared_from_this());
    // for (auto& [key, value] : *properties) { // this should copy the attribute set to the new object with enumerable
    // }
    return obj;
}
} // namespace JS