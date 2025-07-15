#include "class/Assert/assert.hpp"

#include "customOperators/CustomOperators.hpp"
#include "global/globalFunctions.hpp"
#include "internals/PropertyProxy.hpp"
#include "types/JsAny.hpp"
#include "types/objects/Function/JsFunction.hpp"

namespace JS {
assert::assert(const JS::Properties& properties)
    : JS::InternalObject(properties, JS::Function::getPrototypeProperties(), u"Assert") {}

JS::Any assert::fail(const JS::Any& thisArgs, const JS::Any& args) {
    // TODO : handle if args[0] is a throwable, make throwable js::any
    const double length = JS::CONVERT::ToNumber(args[u"length"]);
    if (length == 1) {
        innerFail(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), args[0], u"fail");
    }
    innerFail(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), u"fail");
    return {};
}

JS::Any assert::ok(const JS::Any& thisArgs, const JS::Any& args) {
    const double length = JS::CONVERT::ToNumber(args[u"length"]);
    if (length == 0) {
        throw JS::Any(std::make_shared<JS::TypeError>(JS::Any(u"(No value argument passed to `Assert.ok()`)")));
    }
    if (!args[0]) {
        innerFail(args[0], JS::Any(true), length == 2 ? args[1] : JS::Any("The expression evaluated to a falsy value"),
                  u"ok");
    }
    return {};
}

// equals
JS::Any assert::equal(const JS::Any& thisArgs, const JS::Any& args) {
    const double length = JS::CONVERT::ToNumber(args[u"length"]);
    if (length < 2) {
        throw JS::Any(std::make_shared<JS::TypeError>(
            JS::Any(u"(The \"actual\" and \"expected\" arguments must be specified.)")));
    }

    if (args[0] != args[1] && (!JS::GLOBAL::isNaN(JS::Any(), JS::Arguments::CreateArgumentsObject({args[0]})) ||
                               !JS::GLOBAL::isNaN(JS::Any(), JS::Arguments::CreateArgumentsObject({args[1]})))) {
        innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), u"==");
    }
    return {};
}

JS::Any assert::notEqual(const JS::Any& thisArgs, const JS::Any& args) {
    const double length = JS::CONVERT::ToNumber(args[u"length"]);
    if (length < 2) {
        throw JS::Any(std::make_shared<JS::TypeError>(
            JS::Any(u"(The \"actual\" and \"expected\" arguments must be specified.)")));
    }
    if (args[0] == args[1] || (JS::GLOBAL::isNaN(JS::Any(), JS::Arguments::CreateArgumentsObject({args[0]})) &&
                               JS::GLOBAL::isNaN(JS::Any(), JS::Arguments::CreateArgumentsObject({args[1]})))) {
        innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), u"!=");
    }
    return {};
}

// deepEquals TODO: make the message automatique depending on the ope
JS::Any assert::deepEqual(const JS::Any& thisArgs, const JS::Any& args) {
    const double length = JS::CONVERT::ToNumber(args[u"length"]);
    if (length < 2) {
        throw JS::Any(std::make_shared<JS::TypeError>(
            JS::Any(u"(The \"actual\" and \"expected\" arguments must be specified.)")));
    }
    if (isDeepEqual(args[0], args[1])) {
        innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), u"deepEqual");
    }
    return {};
}

JS::Any assert::notDeepEqual(const JS::Any& thisArgs, const JS::Any& args) {
    const double length = JS::CONVERT::ToNumber(args[u"length"]);
    if (length < 2) {
        throw JS::Any(std::make_shared<JS::TypeError>(
            JS::Any(u"(The \"actual\" and \"expected\" arguments must be specified.)")));
    }
    if (!isDeepEqual(args[0], args[1])) {
        innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), u"notDeepEqual");
    }
    return {};
}

// strictEquals
JS::Any assert::strictEqual(const JS::Any& thisArgs, const JS::Any& args) {
    const double length = JS::CONVERT::ToNumber(args[u"length"]);
    if (length < 2) {
        throw JS::Any(std::make_shared<JS::TypeError>(
            JS::Any(u"(The \"actual\" and \"expected\" arguments must be specified.)")));
    }
    if (!JS::COMPARE::SameValue(args[0], args[1])) {
        innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), u"strictEqual");
    }
    return {};
}

JS::Any assert::notStrictEqual(const JS::Any& thisArgs, const JS::Any& args) {
    const double length = JS::CONVERT::ToNumber(args[u"length"]);
    if (length < 2) {
        throw JS::Any(std::make_shared<JS::TypeError>(
            JS::Any(u"(The \"actual\" and \"expected\" arguments must be specified.)")));
    }
    if (JS::COMPARE::SameValue(args[0], args[1])) {
        innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), u"notStrictEqual");
    }
    return {};
}

// other
JS::Any assert::ifError(const JS::Any& thisArgs, const JS::Any& args) {
    const double length = JS::CONVERT::ToNumber(args[u"length"]);
    if (length != 1) {
        throw JS::Any(std::make_shared<JS::TypeError>(JS::Any(u"(The \"value\" argument must be specified.)")));
    }
    if (!JS::COMPARE::Type(args[0], JS::UNDEFINED) && !JS::COMPARE::Type(args[0], JS::NULL_TYPE)) {
        innerFail(args[0], JS::Any(JS::Undefined()),
                  JS::Any(u"ifError got unwanted exception" + JS::CONVERT::ToString(args[0])), u"ifError");
    }
    return {};
}

JS::Any assert::throws(const JS::Any& thisArgs, const JS::Any& args) {
    // TODO:: handle obj properties, regexp class
    const double length = JS::CONVERT::ToNumber(args[u"length"]);
    if (length < 1) {
        throw JS::Any(std::make_shared<JS::TypeError>(JS::Any(u"(The \"fn\" argument must be specified.)")));
    }
    if (!JS::COMPARE::Object(args[0], u"Function")) {
        throw JS::Any(std::make_shared<JS::TypeError>(JS::Any(u"(The \"fn\" argument must be a function.)")));
    }
    JS::Any fn = args[0];
    if (length == 1) {
        try {
            fn();
        } catch (const std::exception& e) {
            return {};
        }
        innerFail(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), JS::Any("Missing expected exception"), u"throws");
    }
    return {};
}

JS::Any assert::doesNotThrow(const JS::Any& thisArgs, const JS::Any& args) {
    const double length = JS::CONVERT::ToNumber(args[u"length"]);
    if (length < 1) {
        throw JS::Any(std::make_shared<JS::TypeError>(JS::Any(u"(The \"fn\" argument must be specified.)")));
    }
    if (!JS::COMPARE::Object(args[0], u"Function")) {
        throw JS::Any(std::make_shared<JS::TypeError>(JS::Any(u"(The \"fn\" argument must be a function.)")));
    }
    JS::Any fn = args[0];
    if (length == 1) {
        try {
            fn();
        } catch (const std::exception& e) {
            innerFail(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), JS::Any("Missing expected exception"),
                      u"doesNotThrow");
            return {};
        }
    }
    return {};
}

// Not needed for ES5 Error
JS::Any assert::deepStrictEqual(const JS::Any& thisArgs, const JS::Any& args) {
    const double length = JS::CONVERT::ToNumber(args[u"length"]);
    if (length < 2) {
        throw JS::Any(std::make_shared<JS::TypeError>(
            JS::Any(u"(The \"actual\" and \"expected\" arguments must be specified.)")));
    }
    if (!isDeepEqual(args[0], args[1], true)) {
        innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), u"deepStrictEqual");
    }
    return {};
}

JS::Any assert::notStrictDeepEqual(const JS::Any& thisArgs, const JS::Any& args) {
    const double length = JS::CONVERT::ToNumber(args[u"length"]);
    if (length < 2) {
        throw JS::Any(std::make_shared<JS::TypeError>(
            JS::Any(u"(The \"actual\" and \"expected\" arguments must be specified.)")));
    }
    if (isDeepEqual(args[0], args[1], true)) {
        innerFail(args[0], args[1], length == 3 ? args[2] : JS::Any(JS::Undefined()), u"notDeepStrictEqual");
    }
    return {};
}

// Test262 Asserts
JS::Any assert::sameValue(const JS::Any& actual, const JS::Any& expected) {
    try {
        if (_sameValue(actual, expected)) {
            return {};
        } else {
            innerFail(actual, expected, JS::Any(JS::Undefined()), u"sameValue");
        }
    } catch (const JS::Any& e) {
        innerFail(actual, expected, e, u"sameValue");
    }
    return {};
}

// private
bool assert::_sameValue(const JS::Any& actual, const JS::Any& expected) {
    if (JS::GLOBAL::isNaN(JS::Any(), JS::Arguments::CreateArgumentsObject({actual})) &&
        JS::GLOBAL::isNaN(JS::Any(), JS::Arguments::CreateArgumentsObject({expected}))) {
        return true;
    }
    return JS::COMPARE::SameValue(actual, expected);
}

void assert::innerFail(const JS::Any& actual, const JS::Any& expected, const JS::Any& message,
                       const std::u16string& operator_) {
    auto msg = JS::COMPARE::Type(message, JS::UNDEFINED)
                   ? JS::CONVERT::ToString(actual) + u" " + operator_ + u" " + JS::CONVERT::ToString(expected)
                   : JS::CONVERT::ToString(message);
    throw JS::Any(std::make_shared<JS::Error>(
        JS::Properties{
            {u"name", JS::DataDescriptor{JS::Any(u"AssertionError"), false, false, false}},
            {u"message", JS::DataDescriptor{JS::Any(msg), true, true, true}},
            {u"actual", JS::DataDescriptor{actual, true, true, true}},
            {u"expected", JS::DataDescriptor{expected, true, true, true}},
            {u"operator", JS::DataDescriptor{JS::Any(operator_), true, true, true}},
        },
        JS::Object::getPrototypeProperties()));
    // throw AssertionError(actual, expected, msg, operator_);
}

bool assert::isDeepEqual(const JS::Any& actual, const JS::Any& expected, bool strict) {
    // Check for strict equality (===).
    if (actual strictEq expected) {
        return actual strictNeq JS::Any(0) || JS::COMPARE::SameValue(actual, expected) || !strict;
    }

    // Handle NaN
    if (strict && JS::COMPARE::Type(actual, JS::NUMBER) && JS::COMPARE::Type(expected, JS::NUMBER)) {
        return JS::GLOBAL::isNaN(JS::Any(), JS::Arguments::CreateArgumentsObject({actual})) &&
               JS::GLOBAL::isNaN(JS::Any(), JS::Arguments::CreateArgumentsObject({expected}));
    }

    // Type and null
    bool actualObj = JS::COMPARE::Type(actual, JS::OBJECT);
    bool expectedObj = JS::COMPARE::Type(expected, JS::OBJECT);
    bool actualNull = JS::COMPARE::Type(actual, JS::NULL_TYPE);
    bool expectedNull = JS::COMPARE::Type(expected, JS::NULL_TYPE);
    if (strict) {
        if (!actualObj || !expectedObj || actualNull || expectedNull) {
            return false;
        }
        // TODO: prototype check
        //        if (actual.getPrototype() != expected.getPrototype()) {
        //            return false;
        //        }
    } else {
        // Loose comparison - handle primitives and null.
        if (actualNull || actualObj) {
            if (expectedNull || expectedObj) {
                return actual == expected ||
                       (JS::GLOBAL::isNaN(JS::Any(), JS::Arguments::CreateArgumentsObject({actual})) &&
                        JS::GLOBAL::isNaN(JS::Any(), JS::Arguments::CreateArgumentsObject({expected})));
            }
            return false;
        }
        if (expectedNull || !expectedObj) {
            return false;
        }
    }

    // TODO: replace by type tag [object x] (Object.prototype.toString.call behavior) to differentiate between objects
    JS::Any actualTag = actual[u"toString"]();
    JS::Any expectedTag = expected[u"toString"]();
    if (actualTag != expectedTag) {
        return false;
    }

    // Array
    //    if (actual.isArray()) {
    //        if (!expected.isArray() || actual.length() != expected.length()) {
    //            return false;
    //        }
    //        // Compare keys and values.
    //        auto keys1 = actual.getOwnKeys(strict);
    //        auto keys2 = expected.getOwnKeys(strict);
    //        if (keys1.size() != keys2.size()) {
    //            return false;
    //        }
    //        for (size_t i = 0; i < actual.length(); ++i) {
    //            if (!isDeepEqual(actual[i], expected[i], strict)) {
    //                return false;
    //            }
    //        }
    //        return true;
    //    }

    // Object
    //    if (actualTag == "object") {
    //        auto keys1 = actual.getOwnKeys(strict);
    //        auto keys2 = expected.getOwnKeys(strict);
    //        if (keys1.size() != keys2.size()) {
    //            return false;
    //        }
    //        for (const auto& key : keys1) {
    //            if (!expected.hasKey(key) || !isDeepEqual(actual[key], expected[key], strict)) {
    //                return false;
    //            }
    //        }
    //        return true;
    //    }

    // TODO: Handle
    //  [ ] date,
    //  [ ] Regexp,
    //  [ ] set,
    //  [ ] map,
    //  [ ] Buffer,
    //  [ ] TypedArray,
    //  [ ] Boxed primitives,
    //  [ ] special types like URL or CryptoKey
    return false;
}
} // namespace JS
