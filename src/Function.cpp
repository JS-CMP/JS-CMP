#include "Function.hpp"

std::ostream &Lexer::operator<<(
    std::ostream &os, const Lexer::Function &function
)
{
    os << TypeNames[function.return_type] << " " << function.name << "(";
    for (size_t i = 0; i < function.args.size(); i++) {
        os << TypeNames[function.args[i].type] << " " << function.args[i].name;
        if (i < function.args.size() - 1)
            os << ", ";
    }
    os << ") {";
    os << function.body;
    os << "}" << std::endl;
    return os;
}
