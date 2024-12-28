#ifndef JS_CMP_URIEXEPTION_HPP
#define JS_CMP_URIEXEPTION_HPP

#include <exception>
#include <string>
#include <utility>

class URIException : public std::exception {
public:
    explicit URIException(std::string message) : message(std::move(message)) {}

    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }

private:
    std::string message;
};

#endif // JS_CMP_URIEXEPTION_HPP
