#ifndef JS_CMP_ALPHA_CONSOLE_HPP
#define JS_CMP_ALPHA_CONSOLE_HPP

#include "types/objects/JsFunction.hpp"
#include "types/objects/JsObject.hpp"

#include <iostream>
#include <unistd.h>

/**
 * @class console
 * @brief A simple logging class that provides static methods to print messages to the console.
 *
 * This class encapsulates the logging functionality and provides a single method to log messages
 * of various types. It ensures that the output is formatted correctly with spaces between arguments.
 */
// TODO: https://nodejs.org/docs/latest/api/console.html
class Console : public JS::Object {
public:
    /**
     * @brief Constructs a new Console object.
     *
     * This constructor initializes the object with the log, error, and clear methods.
     */
    Console();
    /**
     * @brief Destroys the Console object.
     */
    ~Console() override = default;

    /**
     * @brief Logs messages to the console.
     *
     * This method accepts a variable number of arguments of any type and prints them to the console
     * with a space separating each argument. A newline is printed at the end.
     *
     * @param args The arguments to log.
     *
     * Example usage:
     * @code
     * auto console = Console();
     * console.log("Hello,", "world!", 42);
     * @endcode
     */
    static JS::Any log(const std::vector<JS::Any>& args);
    /**
     * @brief Logs error messages to the console.
     *
     * This method accepts a variable number of arguments of any type and prints them to the console
     * with a space separating each argument. A newline is printed at the end.
     *
     * @param args The arguments to log.
     *
     * Example usage:
     * @code
     * auto console = Console();
     * console.error("Hello,", "world!", 42);
     * @endcode
     */
    static JS::Any error(const std::vector<JS::Any>& args);
    /**
     * @brief Clears the console output.
     *
     * This method clears the console output by sending the ANSI escape sequence for clearing the
     * screen and moving the cursor to the top left corner.
     *
     * @param args Unused.
     *
     * Example usage:
     * @code
     * auto console = Console();
     * console.clear();
     * @endcode
     */
    static JS::Any clear(const std::vector<JS::Any>& args);

private:
};

#endif // JS_CMP_ALPHA_CONSOLE_HPP