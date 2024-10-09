#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>
#include "Token.hpp"

namespace Lexer {
    class Lexer {
    public:
        Lexer(std::string &content);
        ~Lexer() = default;

        std::vector<Token> tokenize();
        Token nextToken();

        void leftTrim();

        std::string content;
        size_t cursor;
        size_t line;
        size_t start_of_line;

    };
}

#endif //LEXER_HPP
