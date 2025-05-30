#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsDate.hpp"
#include "utils/Convert.hpp"

namespace JS {

Date::Date() : InternalObject({}, getPrototypeProperties(), u"Date", true) {
    // TODO: Implement
}

Date::Date(const JS::Any& value) : InternalObject({}, getPrototypeProperties(), u"Date", true) {
    // TODO: Implement
}

Date::Date(const std::unordered_map<std::u16string, JS::Any>& properties) 
    : InternalObject({}, getPrototypeProperties(), u"Date", true) {
    // TODO: Implement
}

Date::Date(JS::Any year, JS::Any month, JS::Any day, JS::Any hours,
           JS::Any minutes, JS::Any seconds, JS::Any milliseconds) 
    : InternalObject({}, getPrototypeProperties(), u"Date", true) {
    // TODO: Implement
}

} // namespace JS