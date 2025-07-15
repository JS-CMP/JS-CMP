#include "types/objects/Error/JsURIError.hpp"
#include "types/objects/Function/JsFunction.hpp"

std::shared_ptr<JS::InternalObject>& JS::URIError::getPrototypeProperties() {
    static std::unordered_map<std::u16string, JS::Attribute> properties_prototype = {
        {u"name", JS::DataDescriptor{JS::Any("URIError"), true, false, true}},
        {u"constructor", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::URIError::internal_constructor)),
                                            true, false, true}}};

    static std::shared_ptr<JS::InternalObject> protoInstance =
        std::make_shared<JS::InternalObject>(properties_prototype, JS::Error::getPrototypeProperties(), u"Error", true);

    return protoInstance;
}
