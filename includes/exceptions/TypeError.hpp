//
// Created by Simon BANDIERA on 24/11/2024.
//

#ifndef JS_CMP_TYPEERROR_HPP
#define JS_CMP_TYPEERROR_HPP

#include "IAssertion.hpp"

class TypeError : public IAssertion {
public:
    explicit TypeError(const JS::Any& actual, const JS::Any& expected, const std::string& message,
                       const std::string& ope, const std::string& code = "ERR_TYPE_ERROR")
        : IAssertion(actual, expected, message, ope, code, "TypeError") {}
};

#endif // JS_CMP_TYPEERROR_HPP
