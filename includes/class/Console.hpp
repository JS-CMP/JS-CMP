#ifndef JS_CMP_ALPHA_CONSOLE_HPP
#define JS_CMP_ALPHA_CONSOLE_HPP

#include <iostream>

class console { // TODO: change initial to capital letter
    public:
        template<class... Args>
        static void log(Args... args)
        {
            auto print_with_space = [](const auto& arg, bool is_last) {
                std::cout << arg;
                if (!is_last) {
                    std::cout << " ";
                }
            };

            bool is_last = false;
            size_t num_args = sizeof...(args);
            size_t counter = 0;

            ((print_with_space(args, ++counter == num_args)), ...);
            std::cout << "\n";
        }
    private:
        console() = default;
        ~console() = default;
};


#endif //JS_CMP_ALPHA_CONSOLE_HPP
