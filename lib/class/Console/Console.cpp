#include "class/Console/Console.hpp"

void Console::print_with_space(const JS::Any& arg, bool is_last, std::ostream& os) {
    os << arg.toString();
    if (!is_last) {
        os << " ";
    }
}

JS::Any Console::log(const std::vector<JS::Any>& args) {
    size_t num_args = args.size();
    size_t counter = 0;

    for (const auto& arg : args) {
        print_with_space(arg, ++counter == num_args, std::cout);
    }

    std::cout << "\n";
    return {};
}

JS::Any Console::error(const std::vector<JS::Any>& args) {
    size_t num_args = args.size();
    size_t counter = 0;

    for (const auto& arg : args) {
        print_with_space(arg, ++counter == num_args, std::cerr);
    }

    std::cerr << "\n";
    return {};
}

JS::Any Console::clear(const std::vector<JS::Any>& args) {
    if (!isatty(fileno(stdout))) {
        return {};
    }
    std::cout << "\033[2J\033[1;1H";
    return {};
}

Console::Console() {
    this->operator[]("log") = JS::Any(std::make_shared<JS::Function>(JS::Function(log)));
    this->operator[]("error") = JS::Any(std::make_shared<JS::Function>(JS::Function(error)));
    this->operator[]("clear") = JS::Any(std::make_shared<JS::Function>(JS::Function(clear)));
}