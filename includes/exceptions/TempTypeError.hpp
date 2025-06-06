#ifndef JS_CMP_TYPEERROR_HPP
#define JS_CMP_TYPEERROR_HPP

#include "IAssertion.hpp"

class TempTypeError : public IAssertion {
public:
    explicit TempTypeError(const JS::Any& actual, const JS::Any& expected, const std::u16string& message,
                       const std::u16string& ope, const std::u16string& code = u"ERR_TYPE_ERROR")
        : IAssertion(actual, expected, message, ope, code, u"TypeError") {}
};

#endif // JS_CMP_TYPEERROR_HPP
