#ifndef JS_CMP_URIEXEPTION_HPP
#define JS_CMP_URIEXEPTION_HPP

#include <exception>
#include <string>
#include <utility>

/**
 * @class URIException
 * @brief Represents an exception thrown by the URI class.
 *
 * The `URIException` class represents an exception thrown by the URI class.
 */
class URIException : public std::exception {
public:
    /**
     * @brief Constructs a new URIException with the specified message.
     * @param message The exception message.
     */
    explicit URIException(std::string  message) : message(std::move(message)) {}
    /**
     * @brief Returns the exception message.
     * @return The exception message.
     */
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

#endif // JS_CMP_URIEXEPTION_HPP
