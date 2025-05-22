#ifndef JS_CMP_GLOBAL_HPP
#define JS_CMP_GLOBAL_HPP

#include "global/console.hpp"
#include "globalFunctions.hpp"
#include "types/JsAny.hpp"
#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsBoolean.hpp"
#include "types/objects/JsMath.hpp"
#include "types/objects/JsNumber.hpp"
#include "types/objects/JsObject.hpp"
#include "types/objects/JsString.hpp"

// TODO fix this create Object to inherit from Function
JS::Any Object = JS::Any(std::make_shared<JS::Object>(std::unordered_map<std::string, JS::Any>{
    {"getPrototypeOf", JS::Any(std::make_shared<JS::Function>(JS::Object::getPrototypeOf))},
    {"getOwnPropertyDescriptor", JS::Any(std::make_shared<JS::Function>(JS::Object::getOwnPropertyDescriptor))},
    {"getOwnPropertyNames", JS::Any(std::make_shared<JS::Function>(JS::Object::getOwnPropertyNames))},
    {"create", JS::Any(std::make_shared<JS::Function>(JS::Object::create))},
    {"defineProperty", JS::Any(std::make_shared<JS::Function>(JS::Object::defineProperty))},
    {"defineProperties", JS::Any(std::make_shared<JS::Function>(JS::Object::defineProperties))},
    {"seal", JS::Any(std::make_shared<JS::Function>(JS::Object::seal))},
    {"freeze", JS::Any(std::make_shared<JS::Function>(JS::Object::freeze))},
    {"preventExtensions", JS::Any(std::make_shared<JS::Function>(JS::Object::preventExtensions))},
    {"isSealed", JS::Any(std::make_shared<JS::Function>(JS::Object::isSealed))},
    {"isFrozen", JS::Any(std::make_shared<JS::Function>(JS::Object::isFrozen))},
    {"isExtensible", JS::Any(std::make_shared<JS::Function>(JS::Object::isExtensible))},
    {"keys", JS::Any(std::make_shared<JS::Function>(JS::Object::keys))},
}));
JS::Any String = JS::Any(std::make_shared<JS::String>(std::unordered_map<std::string, JS::Any>{
    {"fromCharCode", JS::Any(std::make_shared<JS::Function>(JS::String::fromCharCode))}}));
JS::Any Number = JS::Any(std::make_shared<JS::Number>(std::unordered_map<std::string, JS::Attribute>{
    {"MAX_VALUE", JS::DataDescriptor{JS::Any(JS::Number::MAX_VALUE), false, false, false}},
    {"MIN_VALUE", JS::DataDescriptor{JS::Any(JS::Number::MIN_VALUE), false, false, false}},
    {"NaN", JS::DataDescriptor{JS::Any(JS::Number::NaN), false, false, false}},
    {"NEGATIVE_INFINITY", JS::DataDescriptor{JS::Any(JS::Number::NEGATIVE_INFINITY), false, false, false}},
    {"POSITIVE_INFINITY", JS::DataDescriptor{JS::Any(JS::Number::POSITIVE_INFINITY), false, false, false}},

}));
JS::Any Boolean = JS::Any(std::make_shared<JS::Boolean>());

JS::Any Math = JS::Any(std::make_shared<JS::InternalObject>(
    std::unordered_map<std::string, JS::Attribute>{
        {"abs", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::abs)), true, true, true}},
        {"acos", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::acos)), true, true, true}},
        {"asin", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::asin)), true, true, true}},
        {"atan", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::atan)), true, true, true}},
        {"atan2", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::atan2)), true, true, true}},
        {"ceil", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::ceil)), true, true, true}},
        {"cos", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::cos)), true, true, true}},
        {"exp", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::exp)), true, true, true}},
        {"floor", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::floor)), true, true, true}},
        {"log", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::log)), true, true, true}},
        {"max", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::max)), true, true, true}},
        {"min", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::min)), true, true, true}},
        {"pow", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::pow)), true, true, true}},
        {"random", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::random)), true, true, true}},
        {"round", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::round)), true, true, true}},
        {"sin", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::sin)), true, true, true}},
        {"sqrt", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::sqrt)), true, true, true}},
        {"tan", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::tan)), true, true, true}},
        {"PI", JS::DataDescriptor{JS::Any(M_PI), false, false, false}},
        {"E", JS::DataDescriptor{JS::Any(M_E), false, false, false}},
        {"LN2", JS::DataDescriptor{JS::Any(M_LN2), false, false, false}},
        {"LN10", JS::DataDescriptor{JS::Any(M_LN10), false, false, false}},
        {"LOG2E", JS::DataDescriptor{JS::Any(M_LOG2E), false, false, false}},
        {"LOG10E", JS::DataDescriptor{JS::Any(M_LOG10E), false, false, false}},
        {"SQRT1_2", JS::DataDescriptor{JS::Any(M_SQRT1_2), false, false, false}},
        {"SQRT2", JS::DataDescriptor{JS::Any(M_SQRT2), false, false, false}},
    },
    nullptr, "Math", true)); // TODO Make math inherit from Object

JS::Any console = JS::Any(std::make_shared<JS::Object>(std::unordered_map<std::string, JS::Any>{
    {"log", JS::Any(std::make_shared<JS::Function>(JS::console::log))},
}));

JS::Any NaN = JS::Any(std::numeric_limits<double>::quiet_NaN());
JS::Any Infinity = JS::Any(std::numeric_limits<double>::infinity());
JS::Any undefined = JS::Any(JS::Undefined{});

JS::Any isNaN = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::isNaN));
JS::Any parseInt = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::parseInt));
JS::Any parseFloat = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::parseFloat));
JS::Any isFinite = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::isFinite));
JS::Any global_typeof = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::global_typeof));
JS::Any encodeURI = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::encodeURI));
JS::Any decodeURI = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::decodeURI));
JS::Any encodeURIComponent = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::encodeURIComponent));
JS::Any decodeURIComponent = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::decodeURIComponent));

JS::Any global = JS::Any(std::make_shared<JS::Object>(std::unordered_map<std::string, JS::Any>{
    {"isNaN", isNaN},
    {"parseInt", parseInt},
    {"parseFloat", parseFloat},
    {"isFinite", isFinite},
    {"NaN", NaN},
    {"Infinity", Infinity},
    {"undefined", undefined},
    {"Object", Object},
    {"Math", Math},
    {"encodeURI", encodeURI},
    {"decodeURI", decodeURI},
    {"encodeURIComponent", encodeURIComponent},
    {"decodeURIComponent", decodeURIComponent},
}));

#endif // JS_CMP_GLOBAL_HPP