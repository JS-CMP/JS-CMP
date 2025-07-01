#include "types/objects/Function/JsFunction.hpp"

std::shared_ptr<JS::InternalObject>& JS::Object::getPrototypeProperties() {
    static std::unordered_map<std::u16string, JS::Any> properties_prototype = {
        {u"toString", JS::Any(std::make_shared<JS::Function>(Function::toString))},
        {u"apply", JS::Any(std::make_shared<JS::Function>(Function::apply))},
        {u"bind", JS::Any(std::make_shared<JS::Function>(Function::bind))},
        {u"call", JS::Any(std::make_shared<JS::Function>(Function::call))},
    };
    static std::shared_ptr<JS::InternalObject> instance = std::make_shared<JS::InternalObject>(properties_prototype);

    return instance;
}