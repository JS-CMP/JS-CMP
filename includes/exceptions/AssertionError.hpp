//
// Created by Simon BANDIERA on 24/11/2024.
//

#ifndef JS_CMP_ASSERTIONERROR_HPP
#define JS_CMP_ASSERTIONERROR_HPP

#include "IAssertion.hpp"

class AssertionError : public IAssertion {
public:
    explicit AssertionError(const JS::Any& actual, const JS::Any& expected, const std::string& message,
                            const std::string& ope, const std::string& code = "ERR_ASSERTION")
        : IAssertion(actual, expected, message, ope, code, "AssertionError") {}
};

#endif // JS_CMP_ASSERTIONERROR_HPP
