#ifndef JS_CMP_ALPHA_CONSOLE_HPP
#define JS_CMP_ALPHA_CONSOLE_HPP

#include <iostream>
#include <types/objects/JsObject.hpp>
#include <types/objects/JsFunction.hpp>

class Console : public JS::Object {
public:
    Console() {
        this->operator[]("log") = JS::Any(std::make_shared<JS::Function>(
            JS::Function([](const std::vector<JS::Any>& args) -> JS::Any {
                bool is_last = false;
                size_t num_args = args.size();
                size_t counter = 0;

                for (const auto& arg : args) {
                    print_with_space(arg, ++counter == num_args);
                }

                std::cout << "\n";
                return {};
            })));
    };
    ~Console() override = default;
private:
    static const std::function<void(const JS::Any&, bool)> print_with_space;
};

const std::function<void(const JS::Any&, bool)> Console::print_with_space = [](const JS::Any& arg, bool is_last) {
    std::cout << arg.toString();
    if (!is_last) {
        std::cout << " ";
    }
};

#endif // JS_CMP_ALPHA_CONSOLE_HPP