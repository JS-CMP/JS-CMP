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

inline auto Object = JS::Any(JS::Object::getConstructor());
inline auto Array = JS::Any(JS::Array::getConstructor());
inline auto Function = JS::Any(JS::Function::getConstructor());
inline auto String = JS::Any(JS::String::getConstructor());
inline auto Number = JS::Any(JS::Number::getConstructor());
inline auto Boolean = JS::Any(JS::Boolean::getConstructor());

inline auto Error = JS::Any(JS::Error::getConstructor());
// NativeError is not expected to be used directly, but it is the base class for all native errors.
inline auto RangeError = JS::Any(JS::RangeError::getConstructor());
inline auto ReferenceError = JS::Any(JS::ReferenceError::getConstructor());
inline auto SyntaxError = JS::Any(JS::SyntaxError::getConstructor());
inline auto TypeError = JS::Any(JS::TypeError::getConstructor());
inline auto URIError = JS::Any(JS::URIError::getConstructor());


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
inline auto assert = JS::Any(std::make_shared<JS::assert>(JS::Properties{
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

inline auto console = JS::Any(std::make_shared<JS::Object>(std::unordered_map<std::u16string, JS::Any>{
    {u"log", JS::Any(std::make_shared<JS::Function>(JS::console::log))},
}));

inline auto NaN = JS::Any(std::numeric_limits<double>::quiet_NaN());
inline auto Infinity = JS::Any(std::numeric_limits<double>::infinity());
inline auto undefined = JS::Any(JS::Undefined{});

inline auto isNaN = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::isNaN));
inline auto parseInt = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::parseInt));
inline auto parseFloat = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::parseFloat));
inline auto isFinite = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::isFinite));
inline auto encodeURI = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::encodeURI));
inline auto decodeURI = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::decodeURI));
inline auto encodeURIComponent = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::encodeURIComponent));
inline auto decodeURIComponent = JS::Any(std::make_shared<JS::Function>(JS::GLOBAL::decodeURIComponent));

inline auto global = JS::Any(std::make_shared<JS::Object>(std::unordered_map<std::u16string, JS::Any>{
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


// debug for now , remove eventually
inline void displayPrototypeChain(JS::Any obj) {
    JS::Any currentObj = obj;
    JS::Any index = JS::Any(0);
    console[u"log"](JS::Any(u"Prototype chain:"));
    while (currentObj != JS::Any(JS::Null{})) {
        console[u"log"](JS::Any("level"), index, currentObj["toString"]());
        currentObj = Object["getPrototypeOf"](currentObj);
        index++;
    }
}

#endif // JS_CMP_GLOBAL_HPP