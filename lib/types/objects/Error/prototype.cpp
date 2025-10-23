#include "types/objects/Error/JsError.hpp"
#include "types/objects/Error/JsTypeError.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

JS::Any JS::Error::toString(const JS::Any& thisArg, const JS::Any& args) {
    if (!JS::COMPARE::Type(thisArg, JS::OBJECT)) {
        throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("this is not an Error object")));
    }
    std::shared_ptr<JS::InternalObject> O = std::get<std::shared_ptr<JS::InternalObject>>(thisArg.getValue());
    JS::Any name = O->get(u"name");
    std::u16string nameStr;
    if (JS::COMPARE::Type(name, JS::UNDEFINED)) {
        nameStr = u"Error";
    } else {
        nameStr = JS::CONVERT::ToString(name);
    }
    JS::Any msg = O->get(u"message");
    std::u16string msgStr;
    if (JS::COMPARE::Type(msg, JS::UNDEFINED)) {
        msgStr = u"";
    } else {
        msgStr = JS::CONVERT::ToString(msg);
    }
    if (nameStr.empty()) {
        return JS::Any(msgStr);
    } else if (msgStr.empty()) {
        return JS::Any(nameStr);
    }
    return JS::Any(nameStr + u": " + msgStr);
}
