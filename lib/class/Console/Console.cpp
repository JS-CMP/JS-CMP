#include "class/Console/Console.hpp"

JS::Any Console::log(const std::vector<JS::Any>& args) {
    auto print_with_space = [](const JS::Any& arg, bool is_last) {
        std::cout << arg.toString();
        if (!is_last) {
            std::cout << " ";
        }
    };

    size_t num_args = args.size();
    size_t counter = 0;

    for (const auto& arg : args) {
        print_with_space(arg, ++counter == num_args);
    }

    std::cout << "\n";
    return {};
}

JS::Any Console::error(const std::vector<JS::Any>& args) {
    auto print_with_space = [](const JS::Any& arg, bool is_last) {
        std::cerr << arg.toString();
        if (!is_last) {
            std::cerr << " ";
        }
    };

    size_t num_args = args.size();
    size_t counter = 0;

    for (const auto& arg : args) {
        print_with_space(arg, ++counter == num_args);
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
