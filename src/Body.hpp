#ifndef BODY_HPP
#define BODY_HPP

#include <vector>
#include "Token.hpp"
#include <iostream>

namespace Lexer {

    class Body {
    public:
        Body() = default;
        std::vector<Token> value;
        bool no_return = true;
        friend std::ostream &operator<<(std::ostream &os, const Body &body);
    };
}

#endif //BODY_HPP
