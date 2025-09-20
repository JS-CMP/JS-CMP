#ifndef JS_CMP_GLOBAL_HPP
#define JS_CMP_GLOBAL_HPP

#include "class/Assert/assert.hpp"
#include "global/console.hpp"
#include "globalFunctions.hpp"
#include "types/JsAny.hpp"
#include "types/objects/Error/JsError.hpp"
#include "types/objects/Error/JsNativeError.hpp"
#include "types/objects/Error/JsRangeError.hpp"
#include "types/objects/Error/JsReferenceError.hpp"
#include "types/objects/Error/JsSyntaxError.hpp"
#include "types/objects/Error/JsTypeError.hpp"
#include "types/objects/Error/JsURIError.hpp"
#include "types/objects/Types.hpp"

JS::Any Object = JS::Any(std::make_shared<JS::Object>(JS::Properties{
    {u"length", JS::DataDescriptor{JS::Any(1), false, false, false}},
    {u"name", JS::DataDescriptor{JS::Any(OBJECT_CLASS_NAME), false, false, false}},
    {u"keys", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::keys)), true, false, true}},
    {u"create", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::create)), true, false, true}},
    {u"defineProperty",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::defineProperty)), true, false, true}},
    {u"defineProperties",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::defineProperties)), true, false, true}},
    {u"freeze", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::freeze)), true, false, true}},
    {u"getPrototypeOf",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::getPrototypeOf)), true, false, true}},
    {u"getOwnPropertyDescriptor",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::getOwnPropertyDescriptor)), true, false,
                        true}},
    {u"getOwnPropertyNames",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::getOwnPropertyNames)), true, false, true}},
    {u"isSealed", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::isSealed)), true, false, true}},
    {u"isFrozen", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::isFrozen)), true, false, true}},
    {u"isExtensible",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::isExtensible)), true, false, true}},
    {u"preventExtensions",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::preventExtensions)), true, false, true}},
    {u"seal", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Object::seal)), true, false, true}},
}));

JS::Any Function = JS::Any(std::make_shared<JS::Function>(JS::Properties{
    {u"length", JS::DataDescriptor{JS::Any(1), false, false, false}},
    {u"name", JS::DataDescriptor{JS::Any(FUNCTION_CLASS_NAME), false, false, false}},
}));

JS::Any Array = JS::Any(std::make_shared<JS::Array>(JS::Properties{
    {u"length", JS::DataDescriptor{JS::Any(1), true, false, false}},
    {u"name", JS::DataDescriptor{JS::Any(ARRAY_CLASS_NAME), false, false, false}},
    {u"isArray", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Array::isArray)), true, true, true}},
}));

JS::Any String = JS::Any(std::make_shared<JS::String>(JS::Properties{
    {u"length", JS::DataDescriptor{JS::Any(0), true, false, false}},
    {u"name", JS::DataDescriptor{JS::Any(STRING_CLASS_NAME), false, false, false}},
    {u"fromCharCode",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::String::fromCharCode)), true, true, true}},
}));

JS::Any Number = JS::Any(std::make_shared<JS::Number>(JS::Properties{
    {u"length", JS::DataDescriptor{JS::Any(1), true, false, false}},
    {u"name", JS::DataDescriptor{JS::Any(ERROR_CLASS_NAME), false, false, false}},
    {u"MAX_VALUE", JS::DataDescriptor{JS::Any(JS::Number::MAX_VALUE), false, false, false}},
    {u"MIN_VALUE", JS::DataDescriptor{JS::Any(JS::Number::MIN_VALUE), false, false, false}},
    {u"NaN", JS::DataDescriptor{JS::Any(JS::Number::NaN), false, false, false}},
    {u"NEGATIVE_INFINITY", JS::DataDescriptor{JS::Any(JS::Number::NEGATIVE_INFINITY), false, false, false}},
    {u"POSITIVE_INFINITY", JS::DataDescriptor{JS::Any(JS::Number::POSITIVE_INFINITY), false, false, false}},
}));
JS::Any Boolean = JS::Any(std::make_shared<JS::Boolean>(JS::Properties{
    {u"length", JS::DataDescriptor{JS::Any(1), true, false, false}},
    {u"name", JS::DataDescriptor{JS::Any(BOOL_CLASS_NAME), false, false, false}},
}));
//
JS::Any Error = JS::Any(std::make_shared<JS::Error>(JS::Properties{
    {u"length", JS::DataDescriptor{JS::Any(1), false, false, false}},
    {u"name", JS::DataDescriptor{JS::Any(ERROR_CLASS_NAME), false, false, false}},
}));

// NativeError is not expected to be used directly, but it is the base class for all native errors.

JS::Any RangeError = JS::Any(std::make_shared<JS::RangeError>(JS::Properties{
    {u"length", JS::DataDescriptor{JS::Any(1), false, false, false}},
    {u"name", JS::DataDescriptor{JS::Any(u"RangeError"), false, false, false}},
}));

JS::Any ReferenceError = JS::Any(std::make_shared<JS::ReferenceError>(JS::Properties{
    {u"length", JS::DataDescriptor{JS::Any(1), false, false, false}},
    {u"name", JS::DataDescriptor{JS::Any(u"ReferenceError"), false, false, false}},
}));

JS::Any SyntaxError = JS::Any(std::make_shared<JS::SyntaxError>(JS::Properties{
    {u"length", JS::DataDescriptor{JS::Any(1), false, false, false}},
    {u"name", JS::DataDescriptor{JS::Any(u"SyntaxError"), false, false, false}},
}));

JS::Any TypeError = JS::Any(std::make_shared<JS::TypeError>(JS::Properties{
    {u"length", JS::DataDescriptor{JS::Any(1), false, false, false}},
    {u"name", JS::DataDescriptor{JS::Any(u"TypeError"), false, false, false}},
}));

JS::Any URIError = JS::Any(std::make_shared<JS::URIError>(JS::Properties{
    {u"length", JS::DataDescriptor{JS::Any(1), false, false, false}},
    {u"name", JS::DataDescriptor{JS::Any(u"URIError"), false, false, false}},
}));

JS::Any Math = JS::Any(std::make_shared<JS::InternalObject>(
    JS::Properties{
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
    JS::Object::getPrototypeProperties(), ERROR_CLASS_NAME, true)); // TODO Make math inherit from Object

// TODO add prototype and AssertionError function
JS::Any assert = JS::Any(std::make_shared<JS::assert>(JS::Properties{
    {u"length", JS::DataDescriptor{JS::Any(2), false, false, false}},
    {u"name", JS::DataDescriptor{JS::Any(u"Assert"), false, false, false}},
    {u"fail", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::assert::fail)), true, true, true}},
    {u"ok", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::assert::ok)), true, true, true}},
    {u"equal", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::assert::equal)), true, true, true}},
    {u"notEqual", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::assert::notEqual)), true, true, true}},
    {u"deepEqual",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::assert::deepEqual)), true, true, true}},
    {u"notDeepEqual",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::assert::notDeepEqual)), true, true, true}},
    {u"strictEqual",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::assert::strictEqual)), true, true, true}},
    {u"notStrictEqual",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::assert::notStrictEqual)), true, true, true}},
    {u"throws", JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::assert::throws)), true, true, true}},
    {u"doesNotThrow",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::assert::doesNotThrow)), true, true, true}},
    {u"sameValue",
     JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::assert::sameValue)), true, true, true}},
}));

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