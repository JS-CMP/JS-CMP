//
// Created by Simon BANDIERA on 24/11/2024.
//

#include "class/Assert/Assert.hpp"

Assert::Assert() : JS::Object() {
    this->operator[]("equal") = JS::Any(std::make_shared<JS::Function>(JS::Function(equal)));
    this->operator[]("notEqual") = JS::Any(std::make_shared<JS::Function>(JS::Function(notEqual)));
}

JS::Any Assert::equal(const std::vector<JS::Any>& args) {
    if (args.size() < 2) {
        throw TypeError(JS::Any(JS::Undefined()),
                        JS::Any(JS::Undefined()),
                        R"(The "actual" and "expected" arguments must be specified.)",
                        "ERR_MISSING_ARGS");
    }
    if (args[0] != args[1] && (!args[0].isNan() || ! args[1].isNan())) {
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
    if (args[0] == args[1] && (args[0].isNan() && args[1].isNan())) {
        innerFail(args[0],
                  args[1],
                  args.size() == 3 ? args[2] : JS::Any(JS::Undefined()),
                  "!=");
    }
    return {};
}

void Assert::innerFail(const JS::Any& actual, const JS::Any &expected,
                       const JS::Any &message, const std::string& operator_) {
    auto msg = message.isUndefined() ? actual.toString() + " " + operator_ + " " + expected.toString() : message.toString();
    throw AssertionError(actual, expected, msg, operator_);
}