//
// Created by Simon BANDIERA on 24/11/2024.
//

#ifndef JS_CMP_AASSERTION_HPP
#define JS_CMP_AASSERTION_HPP

#include <exception>
#include <string>
#include <utility>
#include "types/JsAny.hpp"

// TODO: declaration in cpp
class IAssertion: public std::exception {
public:
    IAssertion(JS::Any act,
               JS::Any exp,
               std::string msg,
               std::string ope,
               std::string cd,
               std::string nm): message(std::move(msg)), code(std::move(cd)), name(std::move(nm)), actual(std::move(act)), expected(std::move(exp)), operator_(std::move(ope)) {}
    ~IAssertion() override = default;

    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }

    [[nodiscard]] const char *getCode() const noexcept { return code.c_str(); }
    [[nodiscard]] const char *getMessage() const noexcept { return message.c_str(); }
    [[nodiscard]] const char *getName() const noexcept { return name.c_str(); }
    [[nodiscard]] const char *getOperator() const noexcept { return operator_.c_str(); }
    [[nodiscard]] std::string getActual() const noexcept { return actual.toString(); }
    [[nodiscard]] std::string getExpected() const noexcept { return expected.toString(); }
    [[nodiscard]] std::string errMessage() const noexcept { return name + " [" + code + "]: " + message; }
protected:
    JS::Any actual;
    JS::Any expected;
    std::string operator_;
    std::string message;
    std::string code;
    std::string name;
};

#endif //JS_CMP_AASSERTION_HPP
