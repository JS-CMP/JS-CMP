#include "types/objects/JsObject.hpp"
#include "utils/Convert.hpp"
namespace JS {

JS::Any Object::operator[](const std::string& key) { return this->get(key); }

JS::Any Object::operator[](size_t index) { return this->get(std::to_string(index)); }

JS::Any Object::operator()(const std::vector<JS::Any>& args) {
    // if the first value of is null or undefined, return an empty object
    if (args.empty() || args[0].getValue().index() == JS::UNDEFINED || args[0].getValue().index() == JS::NULL_TYPE) {
        return JS::Any(std::make_shared<JS::Object>());
    }
    return JS::CONVERT::ToObject(args[0]);
}
} // namespace JS