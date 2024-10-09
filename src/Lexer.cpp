#include <iostream>
#include <cstring>
#include "Lexer.hpp"

Lexer::Lexer::Lexer(std::string &content)
    : content(content),
      cursor(0),
      line(0),
      start_of_line(0)
{
}

std::vector<Lexer::Token> Lexer::Lexer::tokenize()
{
    std::vector<Token> tokens;
    while (!this->content.empty()) {
        Token token = this->nextToken();
        if (token.type == TK_EOS)
            break;
        tokens.push_back(token);
    }
    return tokens;
}

void Lexer::Lexer::leftTrim()
{
    while (this->cursor < this->content.size() &&
        Token::isSkippable(this->content[this->cursor])) {
        this->cursor++;
    }
}

Lexer::Token Lexer::Lexer::nextToken()
{
    this->leftTrim();
    if (this->cursor >= this->content.size())
        return Token(TK_EOS);
    char ch = this->content[this->cursor];

    if (ch == '\n' || ch == ';') {
        while (this->cursor < this->content.size() && (
            this->content[this->cursor] == '\n' || this->content[this->cursor] == ';')) {
            this->cursor++;
            this->line++;
            this->start_of_line = this->cursor;
        }
        return {std::string(";"), TK_SEMICOLON, this->line, (this->start_of_line - this->cursor) - 1};
    }

    if (ch == '\'' || ch == '"') {
        std::string value;
        size_t backslash = 0;
        this->cursor++;
        while (this->cursor < this->content.size() &&
            (this->content[this->cursor] != ch || backslash % 2 != 0)) {
            backslash = (this->content[this->cursor] == '\\' ? backslash + 1 : 0);
            value += this->content[this->cursor];
            this->cursor++;
        }
        this->cursor++;
        return {value, TK_STRING, this->line, (this->start_of_line - this->cursor) - value.size()};
    }

    if (Token::isSymbolStart(ch)) {
        std::string value;
        while (this->cursor < this->content.size() &&
            Token::isSymbol(this->content[this->cursor])) {
            value += this->content[this->cursor];
            this->cursor++;
        }
        if (Token::isAlpha(value)) {
            TokenType type = Token::isKeyword(value);
            if (type != TK_NOT_FOUND)
                return {value, type, this->line, (this->start_of_line - this->cursor) - value.size()};
            return {value, TK_IDENTIFIER, this->line, (this->start_of_line - this->cursor) - value.size()};
        }
    }
    if (isdigit(ch) || (ch == '.' && isdigit(this->content[this->cursor + 1]))) {
        std::string value;
        while (this->cursor < this->content.size() &&
            isalnum(this->content[this->cursor]) || this->content[this->cursor] == '-') {
            value += this->content[this->cursor];
            this->cursor++;
        }
        return {value, TK_NUMBER, this->line, (this->start_of_line - this->cursor) - value.size()};
    }

    for (size_t i = TK_QUAD_OP_LAST; i > TK_SIMPLE_OP_FIRST ; i--) {
        if (TokenValue[i] == nullptr)
            continue;
        if (this->content.compare(this->cursor, strlen(TokenValue[i]), TokenValue[i]) == 0) {
            this->cursor += strlen(TokenValue[i]);
            return {TokenValue[i], static_cast<TokenType>(i), this->line, (this->start_of_line - this->cursor) - strlen(TokenValue[i])};
        }
    }
    return {};
}
