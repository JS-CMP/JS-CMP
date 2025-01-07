#include "types/objects/JsObject.hpp"
#include "utils/Convert.hpp"

namespace JS {
JS::Any Object::operator()(const std::vector<JS::Any>& args) {
    // if the first value of is null or undefined, return an empty object
    if (args.empty() || args[0].getValue().index() == JS::UNDEFINED || args[0].getValue().index() == JS::NULL_TYPE) {
        return JS::Any(std::make_shared<JS::Object>());
    }
    return JS::CONVERT::ToObject(args[0]);
}
JS::Any Object::constuctor(std::vector<JS::Any> args) {
    const JS::Any arg = args[0];
    switch (arg.getValue().index()) {
        case JS::OBJECT:
            return arg;
        case JS::BOOL:
        case JS::NUMBER:
        case JS::STRING:
            return JS::CONVERT::ToObject(arg);
        default:
            return JS::Any(std::make_shared<JS::Object>());
    }
}
} // namespace JS