#ifndef JS_CMP_ALPHA_CONSOLE_HPP
#define JS_CMP_ALPHA_CONSOLE_HPP

#include "types/JsAny.hpp"

#include <iostream>

namespace JS {
/**
 * @class Console
 * @brief A simple logging class that provides static methods to print messages to the console.
 *
 * This class encapsulates the logging functionality and provides a single method to log messages
 * of various types. It ensures that the output is formatted correctly with spaces between arguments.
 */
class console {
public:
    /**
     * @brief Logs messages to the console.
     *
     * This method accepts a variable number of arguments of any type and prints them to the console
     * with a space separating each argument. A newline is printed at the end.
     *
     * @param this The `this` object.
     * @param args The arguments to log.
     *
     * Example usage:
     * @code
     * console::log("Hello,", "world!", 42);
     * @endcode
     */
    static JS::Any log(const JS::Any& thisArg, const JS::Any& args);

private:
    console() = default;  ///< Private constructor to prevent instantiation.
    ~console() = default; ///< Private destructor to prevent deletion.
};

#endif // JS_CMP_ALPHA_CONSOLE_HPP
} // namespace JS