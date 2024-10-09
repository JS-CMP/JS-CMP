#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>
#include <iostream>

#include "Program.hpp"
#include "Body.hpp"

namespace Lexer {
    struct arg {
        std::string name;
        Types type;
    };
    class Function {
    public:
        Function() = default;
        std::string name;
        std::vector<arg> args;
        Body body;
        Types return_type = JS_ANY_REF;

        friend std::ostream &operator<<(std::ostream &os, const Function &function);
    };
}
#endif //FUNCTION_HPP
