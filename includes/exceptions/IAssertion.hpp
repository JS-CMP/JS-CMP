#ifndef JS_CMP_IASSERTION_HPP
#define JS_CMP_IASSERTION_HPP

#include "types/JsAny.hpp"
#include "utils/Convert.hpp"

#include <exception>
#include <string>
#include <utility>

// TODO: declaration in cpp
class IAssertion : public std::exception {
public:
    IAssertion(JS::Any act, JS::Any exp, std::u16string msg, std::u16string ope, std::u16string cd, std::u16string nm)
        : actual(std::move(act)), expected(std::move(exp)), operator_(std::move(ope)), message(std::move(msg)),
          code(std::move(cd)), name(std::move(nm)) {}
    ~IAssertion() override = default;

    [[nodiscard]] const char* what() const noexcept override {
        if (cachedMessage_.empty()) {
            cachedMessage_ = JS::CONVERT::ToUtf8(errMessage());
        }
        return cachedMessage_.c_str();
    }
    [[nodiscard]] const char* getCode() const noexcept {
        if (cachedCode_.empty()) {
            cachedCode_ = JS::CONVERT::ToUtf8(code);
        }
        return cachedCode_.c_str();
    }
    [[nodiscard]] const char* getMessage() const noexcept {
        if (cachedMessage_.empty()) {
            cachedMessage_ = JS::CONVERT::ToUtf8(message);
        }
        return cachedMessage_.c_str();
    }
    [[nodiscard]] const char* getName() const noexcept {
        if (cachedName_.empty()) {
            cachedName_ = JS::CONVERT::ToUtf8(name);
        }
        return cachedName_.c_str();
    }
    [[nodiscard]] const char* getOperator() const noexcept {
        if (cachedOperator_.empty()) {
            cachedOperator_ = JS::CONVERT::ToUtf8(operator_);
        }
        return cachedOperator_.c_str();
    }
    [[nodiscard]] std::u16string getActual() const noexcept { return JS::CONVERT::ToString(actual); }
    [[nodiscard]] std::u16string getExpected() const noexcept { return JS::CONVERT::ToString(expected); }
    [[nodiscard]] std::u16string errMessage() const noexcept { return name + u" [" + code + u"]: " + message; }

protected:
    JS::Any actual;
    JS::Any expected;

    std::u16string operator_;
    mutable std::string cachedOperator_;

    std::u16string message;
    mutable std::string cachedMessage_;

    std::u16string code;
    mutable std::string cachedCode_;

    std::u16string name;
    mutable std::string cachedName_;
};

#endif // JS_CMP_IASSERTION_HPP
