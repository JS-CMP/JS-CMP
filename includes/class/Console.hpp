#ifndef JS_CMP_ALPHA_CONSOLE_HPP
#define JS_CMP_ALPHA_CONSOLE_HPP

#include <iostream>
#include <types/objects/JsObject.hpp>
#include <types/objects/JsFunction.hpp>

/**
 * @class console
 * @brief A simple logging class that provides static methods to print messages to the console.
 *
 * This class encapsulates the logging functionality and provides a single method to log messages
 * of various types. It ensures that the output is formatted correctly with spaces between arguments.
 */
class Console : public JS::Object {
public:
    /**
     * @brief Logs messages to the console.
     *
     * This method accepts a variable number of arguments of any type and prints them to the console
     * with a space separating each argument. A newline is printed at the end.
     *
     * @tparam Args Variadic template parameter for the types of arguments.
     * @param args The arguments to log. Can be of any type.
     *
     * Example usage:
     * @code
     * console::log("Hello,", "world!", 42);
     * @endcode
     */
    Console() {
        this->operator[]("log") = JS::Any(std::make_shared<JS::Function>(
            JS::Function([](const std::vector<JS::Any>& args) -> JS::Any {
                auto print_with_space = [](const JS::Any& arg, bool is_last) {
                    std::cout << arg.toString();
                    if (!is_last) {
                        std::cout << " ";
                    }
                };

                bool is_last = false;
                size_t num_args = args.size();
                size_t counter = 0;

                for (const auto& arg : args) {
                    print_with_space(arg, ++counter == num_args);
                }

                std::cout << "\n";
                return {};
            })));
        this->operator[]("error") = JS::Any(std::make_shared<JS::Function>(
            JS::Function([](const std::vector<JS::Any>& args) -> JS::Any {
                auto print_with_space = [](const JS::Any& arg, bool is_last) {
                    std::cerr << arg.toString();
                    if (!is_last) {
                        std::cerr << " ";
                    }
                };

                bool is_last = false;
                size_t num_args = args.size();
                size_t counter = 0;

                for (const auto& arg : args) {
                    print_with_space(arg, ++counter == num_args);
                }

                std::cerr << "\n";
                return {};
            })));
        this->operator[]("clear") = JS::Any(std::make_shared<JS::Function>(
            JS::Function([](const std::vector<JS::Any>& args) -> JS::Any {
                std::system("clear");
                return {};
            })));
    };
    ~Console() override = default;
private:
};



#endif // JS_CMP_ALPHA_CONSOLE_HPP