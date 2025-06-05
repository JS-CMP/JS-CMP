//
// Created by Simon BANDIERA on 24/11/2024.
//

#ifndef JS_CMP_ASSERTIONERROR_HPP
#define JS_CMP_ASSERTIONERROR_HPP

#include "IAssertion.hpp"

class AssertionError : public IAssertion {
public:
    explicit AssertionError(const JS::Any& actual, const JS::Any& expected, const std::u16string& message,
                            const std::u16string& ope, const std::u16string& code = u"ERR_ASSERTION")
        : IAssertion(actual, expected, message, ope, code, u"AssertionError") {}
};

#endif // JS_CMP_ASSERTIONERROR_HPP
