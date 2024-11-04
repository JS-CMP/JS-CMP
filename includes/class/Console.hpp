#ifndef JS_CMP_ALPHA_CONSOLE_HPP
#define JS_CMP_ALPHA_CONSOLE_HPP

#include <iostream>

/**
 * @class console
 * @brief A simple logging class that provides static methods to print messages to the console.
 *
 * This class encapsulates the logging functionality and provides a single method to log messages
 * of various types. It ensures that the output is formatted correctly with spaces between arguments.
 */
class console { // TODO: change initial to capital letter
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
    template <class... Args>
    static void log(Args... args) {
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
    console() = default; ///< Private constructor to prevent instantiation.
    ~console() = default; ///< Private destructor to prevent deletion.
};

#endif // JS_CMP_ALPHA_CONSOLE_HPP
