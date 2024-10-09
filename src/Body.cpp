#include "Body.hpp"
#include "Program.hpp"

std::ostream &Lexer::operator<<(std::ostream &os, const Lexer::Body &body)
{
    size_t i = 0;
    bool ret = false;
    while (body.value[i].type == TK_SEMICOLON)
        i++;
    for (; i < body.value.size(); i++) {
        Types type;

        switch (body.value[i].type) {
        case TK_TRUE_LITERAL:
        case TK_FALSE_LITERAL:
        case TK_NUMBER:
            type = JS_ANY;
            os << TypeNames[type] << "(" << body.value[i].value << ")";
            break;
        case TK_STRING:
            type = JS_ANY;
            os << TypeNames[type] << "(\"" << body.value[i].value << "\")";
            break;
        case TK_NULL_LITERAL:
            type = JS_ANY;
            os << TypeNames[type] << " " << body.value[i + 1].value
                << body.value[i + 2].value << TypeNames[type] << "(nullptr)";
            break;
        case TK_UNDEFINED_LITERAL:
            type = JS_ANY;
            os << TypeNames[type] << " " << body.value[i + 1].value
                << body.value[i + 2].value << TypeNames[type] << "()";
            break;
        case TK_PERIOD:
            os << "::";
            break;
        case TK_CONST:
            os << "const ";
        case TK_LET:
        case TK_VAR:
            if (i + 3 > body.value.size())
                throw std::runtime_error("the JavaScript code contain a feature that is not yet implemented.");
            switch (body.value[i + 3].type) {
            case TK_TRUE_LITERAL:
            case TK_FALSE_LITERAL:
            case TK_NUMBER:
                type = JS_ANY;
                os << TypeNames[type] << " " << body.value[i + 1].value
                    << body.value[i + 2].value << TypeNames[type] << "("
                    << body.value[i + 3].value << ")";
                break;
            case TK_STRING:
                type = JS_ANY;
                os << TypeNames[type] << " " << body.value[i + 1].value
                    << body.value[i + 2].value << TypeNames[type] << "(\""
                    << body.value[i + 3].value << "\")";
                break;
            case TK_NULL_LITERAL:
                type = JS_ANY;
                os << TypeNames[type] << " " << body.value[i + 1].value
                    << body.value[i + 2].value << TypeNames[type]
                    << "(nullptr)";
                break;
            case TK_UNDEFINED_LITERAL:
                i += 1;
            default:
                type = JS_ANY;
                os << TypeNames[type] << " " << body.value[i + 1].value
                    << body.value[i + 2].value << TypeNames[type] << "()";
                i-= 2;
                break;
            }
            i += 3;
            break;
        case TK_RETURN:
            ret = true;
            if (i + 1 > body.value.size()) {
                throw std::runtime_error(
                    "the JavaScript code contain a feature that is not yet implemented.");
            }
            switch (body.value[i + 1].type) {
            case TK_EOL:
            case TK_SEMICOLON:
                os << "return JS::Any();";
                i++;
                break;
            default:
                break;
            }
        default:
            os << body.value[i].value;
        }
        if (Token::isKeyword(body.value[i].value) != TK_NOT_FOUND)
            os << " ";
    }
    if (!ret && body.no_return)
        os << "return JS::Any();";
    return os;
}
