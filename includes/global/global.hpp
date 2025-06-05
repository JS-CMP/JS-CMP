#ifndef JS_CMP_GLOBAL_HPP
#define JS_CMP_GLOBAL_HPP

#include "global/console.hpp"
#include "globalFunctions.hpp"
#include "types/JsAny.hpp"
#include "types/objects/Types.hpp"

// TODO fix this create Object to inherit from Function
JS::Any Object = JS::Any(std::make_shared<JS::Object>(std::unordered_map<std::u16string, JS::Any>{
    {u"getPrototypeOf", JS::Any(std::make_shared<JS::Function>(JS::Object::getPrototypeOf))},
    {u"getOwnPropertyDescriptor", JS::Any(std::make_shared<JS::Function>(JS::Object::getOwnPropertyDescriptor))},
    {u"getOwnPropertyNames", JS::Any(std::make_shared<JS::Function>(JS::Object::getOwnPropertyNames))},
    {u"create", JS::Any(std::make_shared<JS::Function>(JS::Object::create))},
    {u"defineProperty", JS::Any(std::make_shared<JS::Function>(JS::Object::defineProperty))},
    {u"defineProperties", JS::Any(std::make_shared<JS::Function>(JS::Object::defineProperties))},
    {u"seal", JS::Any(std::make_shared<JS::Function>(JS::Object::seal))},
    {u"freeze", JS::Any(std::make_shared<JS::Function>(JS::Object::freeze))},
    {u"preventExtensions", JS::Any(std::make_shared<JS::Function>(JS::Object::preventExtensions))},
    {u"isSealed", JS::Any(std::make_shared<JS::Function>(JS::Object::isSealed))},
    {u"isFrozen", JS::Any(std::make_shared<JS::Function>(JS::Object::isFrozen))},
    {u"isExtensible", JS::Any(std::make_shared<JS::Function>(JS::Object::isExtensible))},
    {u"keys", JS::Any(std::make_shared<JS::Function>(JS::Object::keys))},
}));

JS::Any Array = JS::Any(std::make_shared<JS::InternalObject>(
    std::unordered_map<std::u16string, JS::Attribute>{
        {u"isArray", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::isArray)), true, true, true}},
        {u"length", JS::DataDescriptor{JS::Any(0), true, false, false}}},
    nullptr, u"Array", true));

JS::Any String = JS::Any(std::make_shared<JS::String>(std::unordered_map<std::u16string, JS::Any>{
    {u"fromCharCode", JS::Any(std::make_shared<JS::Function>(JS::String::fromCharCode))}}));

JS::Any Number = JS::Any(std::make_shared<JS::Number>(std::unordered_map<std::u16string, JS::Attribute>{
    {u"MAX_VALUE", JS::DataDescriptor{JS::Any(JS::Number::MAX_VALUE), false, false, false}},
    {u"MIN_VALUE", JS::DataDescriptor{JS::Any(JS::Number::MIN_VALUE), false, false, false}},
    {u"NaN", JS::DataDescriptor{JS::Any(JS::Number::NaN), false, false, false}},
    {u"NEGATIVE_INFINITY", JS::DataDescriptor{JS::Any(JS::Number::NEGATIVE_INFINITY), false, false, false}},
    {u"POSITIVE_INFINITY", JS::DataDescriptor{JS::Any(JS::Number::POSITIVE_INFINITY), false, false, false}},

}));
JS::Any Boolean = JS::Any(std::make_shared<JS::Boolean>());

JS::Any Math = JS::Any(std::make_shared<JS::InternalObject>(
    std::unordered_map<std::u16string, JS::Attribute>{
        {u"abs", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::abs)), true, true, true}},
        {u"acos", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::acos)), true, true, true}},
        {u"asin", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::asin)), true, true, true}},
        {u"atan", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::atan)), true, true, true}},
        {u"atan2", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::atan2)), true, true, true}},
        {u"ceil", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::ceil)), true, true, true}},
        {u"cos", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::cos)), true, true, true}},
        {u"exp", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::exp)), true, true, true}},
        {u"floor", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::floor)), true, true, true}},
        {u"log", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::log)), true, true, true}},
        {u"max", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::max)), true, true, true}},
        {u"min", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::min)), true, true, true}},
        {u"pow", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::pow)), true, true, true}},
        {u"random", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::random)), true, true, true}},
        {u"round", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::round)), true, true, true}},
        {u"sin", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::sin)), true, true, true}},
        {u"sqrt", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::sqrt)), true, true, true}},
        {u"tan", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Math::tan)), true, true, true}},
        {u"PI", JS::DataDescriptor{JS::Any(M_PI), false, false, false}},
        {u"E", JS::DataDescriptor{JS::Any(M_E), false, false, false}},
        {u"LN2", JS::DataDescriptor{JS::Any(M_LN2), false, false, false}},
        {u"LN10", JS::DataDescriptor{JS::Any(M_LN10), false, false, false}},
        {u"LOG2E", JS::DataDescriptor{JS::Any(M_LOG2E), false, false, false}},
        {u"LOG10E", JS::DataDescriptor{JS::Any(M_LOG10E), false, false, false}},
        {u"SQRT1_2", JS::DataDescriptor{JS::Any(M_SQRT1_2), false, false, false}},
        {u"SQRT2", JS::DataDescriptor{JS::Any(M_SQRT2), false, false, false}},
    },
    nullptr, u"Math", true)); // TODO Make math inherit from Object

JS::Any console = JS::Any(std::make_shared<JS::Object>(std::unordered_map<std::u16string, JS::Any>{
    {u"log", JS::Any(std::make_shared<JS::Function>(JS::console::log))},
}));

JS::Any NaN = JS::Any(std::numeric_limits<double>::quiet_NaN());
JS::Any Infinity = JS::Any(std::numeric_limits<double>::infinity());
JS::Any undefined = JS::Any(JS::Undefined{});

JS::Any isNaN = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::isNaN));
JS::Any parseInt = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::parseInt));
JS::Any parseFloat = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::parseFloat));
JS::Any isFinite = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::isFinite));
JS::Any encodeURI = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::encodeURI));
JS::Any decodeURI = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::decodeURI));
JS::Any encodeURIComponent = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::encodeURIComponent));
JS::Any decodeURIComponent = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::decodeURIComponent));

JS::Any global = JS::Any(std::make_shared<JS::Object>(std::unordered_map<std::u16string, JS::Any>{
    {u"isNaN", isNaN},
    {u"parseInt", parseInt},
    {u"parseFloat", parseFloat},
    {u"isFinite", isFinite},
    {u"NaN", NaN},
    {u"Infinity", Infinity},
    {u"undefined", undefined},
    {u"Object", Object},
    {u"Array", Array},
    {u"Math", Math},
    {u"encodeURI", encodeURI},
    {u"decodeURI", decodeURI},
    {u"encodeURIComponent", encodeURIComponent},
    {u"decodeURIComponent", decodeURIComponent},
}));

#endif // JS_CMP_GLOBAL_HPP