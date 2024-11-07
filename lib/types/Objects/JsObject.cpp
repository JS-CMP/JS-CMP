//#include "types/Objects/JsObject.hpp"
#include "../../../includes/types/Objects/JsObject.hpp" // test compile

namespace JS {
    JS::Any& Object::operator[](const std::string& key) {
        return properties[key];
    }

    JS::Any& Object::operator[](size_t index) {
        return properties[std::to_string(index)];
    }

    bool Object::hasProperty(const std::string& key) const {
        return properties.find(key) != properties.end();
    }

    bool Object::isCallable() const {
        return false;
    }
}



//const JS::Any& Object::operator[](const std::string& key) const {
//    auto it = properties.find(key);
//    if (it != properties.end()) {
//        return it->second;
//    }
//    throw std::out_of_range("Property not found.");
//}
//
//JS::Any& Object::operator[](const char* key) {
//    return properties[key];
//}
//
//const JS::Any& Object::operator[](const char* key) const {
//    auto it = properties.find(key);
//    if (it != properties.end()) {
//        return it->second;
//    }
//    throw std::out_of_range("Property not found.");
//}
//
//JS::Any& Object::operator[](size_t index) {
//    return properties[std::to_string(index)];
//}
//
//const JS::Any& Object::operator[](size_t index) const {
//    auto it = properties.find(std::to_string(index));
//    if (it != properties.end()) {
//        return it->second;
//    }
//    throw std::out_of_range("Property not found.");
//}
//
//JS::Any& Object::operator[](int index) {
//    return properties[std::to_string(index)];
//}
//
//const JS::Any& Object::operator[](int index) const {
//    auto it = properties.find(std::to_string(index));
//    if (it != properties.end()) {
//        return it->second;
//    }
//    throw std::out_of_range("Property not found.");
//}