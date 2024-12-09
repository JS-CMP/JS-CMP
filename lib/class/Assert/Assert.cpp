//
// Created by Simon BANDIERA on 24/11/2024.
//

#include "class/Assert/Assert.hpp"

Assert::Assert() : JS::Object() {
    this->operator[]("equal") = JS::Any(std::make_shared<JS::Function>(JS::Function(equal)));
    this->operator[]("notEqual") = JS::Any(std::make_shared<JS::Function>(JS::Function(notEqual)));
}

// equals
JS::Any Assert::equal(const std::vector<JS::Any>& args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()),
                        JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)",
                        "ERR_MISSING_ARGS");
    }
    if (args[0] != args[1] && (!Helper::isNaN(args[0]) || !Helper::isNaN(args[1]))) {
        innerFail(args[0],
                  args[1],
                  args.size() == 3 ? args[2] : JS::Any(JS::Undefined()),
                  "==");
    }
    return {};
}

JS::Any Assert::notEqual(const std::vector<JS::Any>& args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()),
                        JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)",
                        "ERR_MISSING_ARGS");
    }
    if (args[0] == args[1] && (Helper::isNaN(args[0]) && Helper::isNaN(args[1]))) {
        innerFail(args[0],
                  args[1],
                  args.size() == 3 ? args[2] : JS::Any(JS::Undefined()),
                  "!=");
    }
    return {};
}

// stictEquals
JS::Any Assert::strictEqual(const std::vector<JS::Any> &args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()),
                        JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)",
                        "ERR_MISSING_ARGS");
    }
    if (!Helper::ObjectIs(args[0], args[1])) {
        innerFail(args[0],
                  args[1],
                  args.size() == 3 ? args[2] : JS::Any(JS::Undefined()),
                  "strictEqual");
    }
    return {};
}

JS::Any Assert::notStrictEqual(const std::vector<JS::Any> &args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()),
                        JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)",
                        "ERR_MISSING_ARGS");
    }
    if (Helper::ObjectIs(args[0], args[1])) {
        innerFail(args[0],
                  args[1],
                  args.size() == 3 ? args[2] : JS::Any(JS::Undefined()),
                  "notStrictEqual");
    }
    return {};
}

// deepEquals TODO: make the message automatique depending on the ope
JS::Any Assert::deepEqual(const std::vector<JS::Any>& args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()),
                        JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)",
                        "ERR_MISSING_ARGS");
    }
    if (isDeepEqual(args[0], args[1])) {
        innerFail(args[0],
                  args[1],
                  args.size() == 3 ? args[2] : JS::Any(JS::Undefined()),
                  "deepEqual");
    }
    return {};
}

// private
void Assert::innerFail(const JS::Any& actual, const JS::Any &expected,
                       const JS::Any &message, const std::string& operator_) {
    auto msg = Helper::isUndefined(message) ? actual.toString() + " " + operator_ + " " + expected.toString() : message.toString();
    throw AssertionError(actual, expected, msg, operator_);
}

bool Assert::isDeepEqual(const JS::Any& actual, const JS::Any& expected) {
    if (actual.strictEq(expected)) {
        return actual.strictNeq(JS::Any(0));
    }
    if (actual.getValue().index() != expected.getValue().index()) {
        return false;
    }
    switch (actual.getValue().index()) {
        case JS::NUMBER:
            return std::get<double>(actual.getValue()) == std::get<double>(expected.getValue());
        case JS::STRING:
            return std::get<Rope>(actual.getValue()) == std::get<Rope>(expected.getValue());
        case JS::BOOL:
            return std::get<bool>(actual.getValue()) == std::get<bool>(expected.getValue());
        case JS::UNDEFINED:
            return true;
        case JS::NULL_TYPE:
            return true;
        case JS::OBJECT:
            return true;
        default:
            return false;
    }
}