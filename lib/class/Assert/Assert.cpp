//
// Created by Simon BANDIERA on 24/11/2024.
//

#include "class/Assert/Assert.hpp"

assert::assert() : JS::Object() {
    this->operator[]("equal") = JS::Any(std::make_shared<JS::Function>(JS::Function(equalHelper)));
    this->operator[]("notEqual") = JS::Any(std::make_shared<JS::Function>(JS::Function(notEqualHelper)));
}

// equals
JS::Any assert::equalHelper(const std::vector<JS::Any> &args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
    }
    if (args[0] != args[1] && (!Helper::isNaN(args[0]) || !Helper::isNaN(args[1]))) {
        innerFail(args[0], args[1], args.size() == 3 ? args[2] : JS::Any(JS::Undefined()), "==");
    }
    return {};
}

JS::Any assert::notEqualHelper(const std::vector<JS::Any> &args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
    }
    if (args[0] == args[1] && (Helper::isNaN(args[0]) && Helper::isNaN(args[1]))) {
        innerFail(args[0], args[1], args.size() == 3 ? args[2] : JS::Any(JS::Undefined()), "!=");
    }
    return {};
}

// stictEquals
JS::Any assert::strictEqualHelper(const std::vector<JS::Any> &args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
    }
    if (!Helper::ObjectIs(args[0], args[1])) {
        innerFail(args[0], args[1], args.size() == 3 ? args[2] : JS::Any(JS::Undefined()), "strictEqual");
    }
    return {};
}

JS::Any assert::notStrictEqualHelper(const std::vector<JS::Any> &args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
    }
    if (Helper::ObjectIs(args[0], args[1])) {
        innerFail(args[0], args[1], args.size() == 3 ? args[2] : JS::Any(JS::Undefined()), "notStrictEqual");
    }
    return {};
}

// deepEquals TODO: make the message automatique depending on the ope
JS::Any assert::deepEqualHelper(const std::vector<JS::Any> &args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
    }
    if (isDeepEqual(args[0], args[1])) {
        innerFail(args[0], args[1], args.size() == 3 ? args[2] : JS::Any(JS::Undefined()), "deepEqual");
    }
    return {};
}

JS::Any assert::notDeepEqualHelper(const std::vector<JS::Any> &args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
    }
    if (!isDeepEqual(args[0], args[1])) {
        innerFail(args[0], args[1], args.size() == 3 ? args[2] : JS::Any(JS::Undefined()), "notDeepEqual");
    }
    return {};
}

// deep strict equals
JS::Any assert::deepStrictEqualHelper(const std::vector<JS::Any> &args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
    }
    if (!isDeepEqual(args[0], args[1], true)) {
        innerFail(args[0], args[1], args.size() == 3 ? args[2] : JS::Any(JS::Undefined()), "deepStrictEqual");
    }
    return {};
}

JS::Any assert::notStrictDeepEqualHelper(const std::vector<JS::Any> &args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)", "ERR_MISSING_ARGS");
    }
    if (isDeepEqual(args[0], args[1], true)) {
        innerFail(args[0], args[1], args.size() == 3 ? args[2] : JS::Any(JS::Undefined()), "notDeepStrictEqual");
    }
    return {};
}

// other
JS::Any assert::okHelper(const std::vector<JS::Any> &args) {
    if (args.empty()) {
        throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
                        R"(No value argument passed to `assert.ok()`)", "ERR_MISSING_ARGS");
    }
    if (!args[0]) {
        innerFail(args[0], JS::Any(true),
                  args.size() == 2 ? args[1] : JS::Any("The expression evaluated to a falsy value"), "ok");
    }
    return {};
}

JS::Any assert::failHelper(const std::vector<JS::Any> &args) {
    // TODO : handle if args[0] is a throwable, make throwable js::any
    if (args.size() == 1) {
        innerFail(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), args[0], "fail");
    }
    innerFail(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), "fail");
    return {};
}

JS::Any assert::ifErrorHelper(const std::vector<JS::Any> &args) {
    if (args.size() != 1) {
        throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()),
                        R"(The "value" argument must be specified.)", "ERR_MISSING_ARGS");
    }
    if (!(Helper::type_of(args[0]) == "undefined") && !Helper::isNull(args[0])) {
        innerFail(args[0], JS::Any(JS::Undefined()), JS::Any("ifError got unwanted exception" + args[0].toString()),
                  "ifError");
    }
    return {};
}

JS::Any assert::throwsHelper(const std::vector<JS::Any> &args) {
    // TODO:: handle obj properties, regexp class
    if (args.size() < 1) {
        throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), R"(The "fn" argument must be specified.)",
                        "ERR_MISSING_ARGS");
    }
    if (Helper::type_of(args[0]) != "function") {
        throw TypeError(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), R"(The "fn" argument must be a function.)",
                        "ERR_INVALID_ARG_TYPE");
    }
    JS::Any fn = args[0];
    if (args.size() == 1) {
        try {
            fn();
        } catch (const JS::Any& e) { return {}; }
        innerFail(JS::Any(JS::Undefined()), JS::Any(JS::Undefined()), JS::Any("Missing expected exception"), "throws");
    }
    return {};
}

// private
void assert::innerFail(const JS::Any& actual, const JS::Any& expected, const JS::Any& message,
                       const std::string& operator_) {
    auto msg = Helper::isUndefined(message) ? actual.toString() + " " + operator_ + " " + expected.toString()
                                            : message.toString();
    throw AssertionError(actual, expected, msg, operator_);
}

bool assert::isDeepEqual(const JS::Any& actual, const JS::Any& expected, bool strict) {
    // Check for strict equality (===).
    if (actual.strictEq(expected)) {
        return actual.strictNeq(JS::Any(0)) || Helper::ObjectIs(actual, expected) || !strict;
    }

    // Handle NaN
    if (strict && Helper::isNumber(actual) && Helper::isNumber(expected)) {
        return Helper::NumberIsNaN(actual) && Helper::NumberIsNaN(expected);
    }

    // Type and null
    if (strict) {
        if (!Helper::isObject(actual) || !Helper::isObject(expected) || Helper::isNull(actual) ||
            Helper::isNull(expected)) {
            return false;
        }
        // TODO: prototype check
        //        if (actual.getPrototype() != expected.getPrototype()) {
        //            return false;
        //        }
    } else {
        // Loose comparison - handle primitives and null.
        if (Helper::isNull(actual) || Helper::isObject(actual)) {
            if (Helper::isNull(expected) || Helper::isObject(expected)) {
                return actual == expected || (Helper::NumberIsNaN(actual) && Helper::NumberIsNaN(expected));
            }
            return false;
        }
        if (Helper::isNull(expected) || !Helper::isObject(expected)) {
            return false;
        }
    }

    // TODO: replace by type tag [object x] (Object.prototype.toString.call behavior) to differentiate between objects
    std::string actualTag = Helper::type_of(actual);
    std::string expectedTag = Helper::type_of(expected);
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
