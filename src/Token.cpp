#include "Token.hpp"

#include <utility>

Lexer::Token::Token()
    : value(),
      type(TK_EOS),
      line(0),
      column(0)
{
}

Lexer::Token::Token(Lexer::TokenType type) : value(), type(type), line(0), column(0)
{
}

Lexer::Token::Token(
    std::string value, TokenType type, unsigned long line, unsigned long column
)
    : value(std::move(value)),
      type(type),
      line(line),
      column(column)
{
}

bool Lexer::Token::isSkippable(char ch)
{
    return ch == ' ' || ch == '\t';
}

bool Lexer::Token::isSymbolStart(char ch)
{
    return isalpha(ch) || ch == '_';
}

bool Lexer::Token::isSymbol(char ch)
{
    return isalnum(ch) || ch == '_';
}



bool Lexer::Token::isAlpha(const std::string &str)
{
    for (char ch: str) {
        if (!isalpha(ch))
            return false;
    }
    return true;
}

Lexer::TokenType Lexer::Token::isKeyword(const std::string &str)
{
    for (int i = TK_QUAD_OP_LAST + 1; i < TK_NUMBER; i++) {
        if (TokenValue[i] == nullptr)
            continue;
        if (str == TokenValue[i])
            return static_cast<TokenType>(i);
    }
    return TK_NOT_FOUND;
}