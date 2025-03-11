// //
// // Created by Simon BANDIERA on 24/11/2024.
// //
//
// #include "class/Assert/Assert.hpp"
//
// assert::assert() : JS::Object() {
//     this->operator[]("equal") = JS::Any(std::make_shared<JS::Function>(JS::Function(equalHelper)));
//     this->operator[]("notEqual") = JS::Any(std::make_shared<JS::Function>(JS::Function(notEqualHelper)));
// }
//
// // equals
// JS::Any assert::equalHelper(const JS::Any& thisArgs, const JS::Any& args) {
//     const double length = JS::CONVERT::ToNumber(args["length"]);
//     if (length < 2) {
//         throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
//                         R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
//     }
//     JS::Any a = args[0]; // done to fix property proxy issues
//     JS::Any b = args[1];
//     if (a != b && (!isNaN(args[0]) || !isNaN(args[1]))) {
//         innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), "==");
//     }
//     return {};
// }
//
// JS::Any assert::notEqualHelper(const JS::Any& thisArgs, const JS::Any& args) {
//     const double length = JS::CONVERT::ToNumber(args["length"]);
//     if (length < 2) {
//         throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
//                         R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
//     }
//     if (args[0] == args[1] || (isNaN(args[0]) && isNaN(args[1]))) {
//         innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), "!=");
//     }
//     return {};
// }
//
// // stictEquals
// JS::Any assert::strictEqualHelper(const JS::Any& thisArgs, const JS::Any& args) {
//     const double length = JS::CONVERT::ToNumber(args["length"]);
//     if (length < 2) {
//         throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
//                         R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
//     }
//     if (!JS::COMPARE::SameValue(args[0], args[1])) {
//         innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), "strictEqual");
//     }
//     return {};
// }
//
// JS::Any assert::notStrictEqualHelper(const JS::Any& thisArgs, const JS::Any& args) {
//     const double length = JS::CONVERT::ToNumber(args["length"]);
//     if (length < 2) {
//         throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
//                         R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
//     }
//     if (JS::COMPARE::SameValue(args[0], args[1])) {
//         innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), "notStrictEqual");
//     }
//     return {};
// }
//
// // deepEquals TODO: make the message automatique depending on the ope
// JS::Any assert::deepEqualHelper(const JS::Any& thisArgs, const JS::Any& args) {
//     const double length = JS::CONVERT::ToNumber(args["length"]);
//     if (length < 2) {
//         throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
//                         R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
//     }
//     if (isDeepEqual(args[0], args[1])) {
//         innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), "deepEqual");
//     }
//     return {};
// }
//
// JS::Any assert::notDeepEqualHelper(const JS::Any& thisArgs, const JS::Any& args) {
//     const double length = JS::CONVERT::ToNumber(args["length"]);
//     if (length < 2) {
//         throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
//                         R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
//     }
//     if (!isDeepEqual(args[0], args[1])) {
//         innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), "notDeepEqual");
//     }
//     return {};
// }
//
// // deep strict equals
// JS::Any assert::deepStrictEqualHelper(const JS::Any& thisArgs, const JS::Any& args) {
//     const double length = JS::CONVERT::ToNumber(args["length"]);
//     if (length < 2) {
//         throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
//                         R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
//     }
//     if (!isDeepEqual(args[0], args[1], true)) {
//         innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), "deepStrictEqual");
//     }
//     return {};
// }
//
// JS::Any assert::notStrictDeepEqualHelper(const JS::Any& thisArgs, const JS::Any& args) {
//     const double length = JS::CONVERT::ToNumber(args["length"]);
//     if (length < 2) {
//         throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
//                         R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
//     }
//     if (isDeepEqual(args[0], args[1], true)) {
//         innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), "notDeepStrictEqual");
//     }
//     return {};
// }
//
// // other
// JS::Any assert::okHelper(const JS::Any& thisArgs, const JS::Any& args) {
//     const double length = JS::CONVERT::ToNumber(args["length"]);
//     if (length == 0) {
//         throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
//                         R"(No value argument passed to `assert.ok()`)", "ERR_MISSING_ARGS");
//     }
//     if (!args[0]) {
//         innerFail(args[0], JS::Any(true), length == 2 ? args[1] : JS::Any("The expression evaluated to a falsy value"),
//                   "ok");
//     }
//     return {};
// }
//
// JS::Any assert::failHelper(const JS::Any& thisArgs, const JS::Any& args) {
//     // TODO : handle if args[0] is a throwable, make throwable js::any
//     const double length = JS::CONVERT::ToNumber(args["length"]);
//     if (length == 1) {
//         innerFail(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), args[0], "fail");
//     }
//     innerFail(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), "fail");
//     return {};
// }
//
// JS::Any assert::ifErrorHelper(const JS::Any& thisArgs, const JS::Any& args) {
//     const double length = JS::CONVERT::ToNumber(args["length"]);
//     if (length != 1) {
//         throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
//                         R"(The "value" argument must be specified.)", "ERR_MISSING_ARGS");
//     }
//     if (!JS::COMPARE::Type(args[0], JS::UNDEFINED) && !JS::COMPARE::Type(args[0], JS::NULL_TYPE)) {
//         innerFail(args[0], JS::Any(JS::Undefined()),
//                   JS::Any("ifError got unwanted exception" + JS::CONVERT::ToString(args[0])), "ifError");
//     }
//     return {};
// }
//
// JS::Any assert::throwsHelper(const JS::Any& thisArgs, const JS::Any& args) {
//     // TODO:: handle obj properties, regexp class
//     const double length = JS::CONVERT::ToNumber(args["length"]);
//     if (length < 1) {
//         throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), R"(The "fn" argument must be specified.)",
//                         "ERR_MISSING_ARGS");
//     }
//     if (JS::COMPARE::Type(args[0], JS::OBJECT) &&
//         std::get<std::shared_ptr<JS::InternalObject>>(args[0].getValue())->class_name == "Function") {
//         throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), R"(The "fn" argument must be a function.)",
//                         "ERR_INVALID_ARG_TYPE");
//     }
//     JS::Any fn = args[0];
//     if (length == 1) {
//         try {
//             fn();
//         } catch (const JS::Any& e) { return {}; }
//         innerFail(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), JS::Any("Missing expected exception"), "throws");
//     }
//     return {};
// }
//
// // Test262 asserts
// JS::Any assert::sameValueHelper(const JS::Any& actual, const JS::Any& expected) {
//     try {
//         if (_sameValue(actual, expected)) {
//             return {};
//         } else {
//             innerFail(actual, expected, JS::Any(JS::Undefined()), "sameValue");
//         }
//     } catch (const JS::Any& e) { innerFail(actual, expected, e, "sameValue"); }
//     return {};
// }
//
// // private
// bool assert::_sameValue(const JS::Any& actual, const JS::Any& expected) {
//     if (isNaN(actual) && isNaN(expected)) {
//         return true;
//     }
//     return JS::COMPARE::SameValue(actual, expected);
// }
//
// void assert::innerFail(const JS::Any& actual, const JS::Any& expected, const JS::Any& message,
//                        const std::string& operator_) {
//     auto msg = JS::COMPARE::Type(message, JS::UNDEFINED)
//                    ? JS::CONVERT::ToString(actual) + " " + operator_ + " " + JS::CONVERT::ToString(expected)
//                    : JS::CONVERT::ToString(message);
//     throw AssertionError(actual, expected, msg, operator_);
// }
//
// bool assert::isDeepEqual(const JS::Any& actual, const JS::Any& expected, bool strict) {
//     // Check for strict equality (===).
//     if (actual.strictEq(expected)) {
//         return actual.strictNeq(JS::Any(0)) || JS::COMPARE::SameValue(actual, expected) || !strict;
//     }
//
//     // Handle NaN
//     if (strict && JS::COMPARE::Type(actual, JS::NUMBER) && JS::COMPARE::Type(expected, JS::NUMBER)) {
//         return isNaN(actual) && isNaN(expected);
//     }
//
//     // Type and null
//     bool actualObj = JS::COMPARE::Type(actual, JS::OBJECT);
//     bool expectedObj = JS::COMPARE::Type(expected, JS::OBJECT);
//     bool actualNull = JS::COMPARE::Type(actual, JS::NULL_TYPE);
//     bool expectedNull = JS::COMPARE::Type(expected, JS::NULL_TYPE);
//     if (strict) {
//         if (!actualObj || !expectedObj || actualNull || expectedNull) {
//             return false;
//         }
//         // TODO: prototype check
//         //        if (actual.getPrototype() != expected.getPrototype()) {
//         //            return false;
//         //        }
//     } else {
//         // Loose comparison - handle primitives and null.
//         if (actualNull || actualObj) {
//             if (expectedNull || expectedObj) {
//                 return actual == expected || (isNaN(actual) && isNaN(expected));
//             }
//             return false;
//         }
//         if (expectedNull || !expectedObj) {
//             return false;
//         }
//     }
//
//     // TODO: replace by type tag [object x] (Object.prototype.toString.call behavior) to differentiate between objects
//     JS::Any actualTag = actual["toString"]();
//     JS::Any expectedTag = expected["toString"]();
//     if (actualTag != expectedTag) {
//         return false;
//     }
//
//     // Array
//     //    if (actual.isArray()) {
//     //        if (!expected.isArray() || actual.length() != expected.length()) {
//     //            return false;
//     //        }
//     //        // Compare keys and values.
//     //        auto keys1 = actual.getOwnKeys(strict);
//     //        auto keys2 = expected.getOwnKeys(strict);
//     //        if (keys1.size() != keys2.size()) {
//     //            return false;
//     //        }
//     //        for (size_t i = 0; i < actual.length(); ++i) {
//     //            if (!isDeepEqual(actual[i], expected[i], strict)) {
//     //                return false;
//     //            }
//     //        }
//     //        return true;
//     //    }
//
//     // Object
//     //    if (actualTag == "object") {
//     //        auto keys1 = actual.getOwnKeys(strict);
//     //        auto keys2 = expected.getOwnKeys(strict);
//     //        if (keys1.size() != keys2.size()) {
//     //            return false;
//     //        }
//     //        for (const auto& key : keys1) {
//     //            if (!expected.hasKey(key) || !isDeepEqual(actual[key], expected[key], strict)) {
//     //                return false;
//     //            }
//     //        }
//     //        return true;
//     //    }
//
//     // TODO: Handle
//     //  [ ] date,
//     //  [ ] Regexp,
//     //  [ ] set,
//     //  [ ] map,
//     //  [ ] Buffer,
//     //  [ ] TypedArray,
//     //  [ ] Boxed primitives,
//     //  [ ] special types like URL or CryptoKey
//     return false;
// }
