#include <cmath>
#include "../../includes/types/JsAny.hpp"
#include "../../includes/types/JsObject.hpp"
#include "../../includes/types/JsArray.hpp"

namespace JS {
    Any::Any() : value(JS::Undefined{}) {}
    Any::Any(int v) : value(static_cast<double>(v)) {}
    Any::Any(double v) : value(v) {}
    Any::Any(const std::string& v) : value(v) {}
    Any::Any(const char* v) : value(std::string(v)) {}
    Any::Any(bool v) : value(v) {}
    Any::Any(JS::Function v) : value(v) {}
    Any::Any(JS::Undefined v) : value(JS::Undefined{}) {}
    Any::Any(JS::Null v) : value(JS::Null{}) {}
    Any::Any(const JS::Object& v) : value(std::make_shared<JS::Object>(v)) {}
}


bool JS::Any::operator==(const JS::Any &other) const
{
    switch (this->value.index()) {
        case NUMBER:
            switch (other.value.index()) {
                case NUMBER:
                    return std::get<double>(this->value) == std::get<double>(other.value);
                case STRING:
                    return std::get<double>(this->value) == std::stod(std::get<std::string>(other.value));
                case BOOL:
                    return std::get<double>(this->value) == static_cast<double>(std::get<bool>(other.value));
                default:
                    return false; // Invalid type
            }
        case STRING:
            switch (other.value.index()) {
                case NUMBER:
                    return std::stod(std::get<std::string>(this->value)) == std::get<double>(other.value);
                case STRING:
                    return std::get<std::string>(this->value) == std::get<std::string>(other.value);
                case BOOL:
                    return std::stod(std::get<std::string>(this->value)) == static_cast<double>(std::get<bool>(other.value));
                default:
                    return false; // Invalid type
            }
        case BOOL:
            switch (other.value.index()) {
                case NUMBER:
                    return static_cast<double>(std::get<bool>(this->value)) == std::get<double>(other.value);
                case STRING:
                    return static_cast<double>(std::get<bool>(this->value)) == std::stod(std::get<std::string>(other.value));
                case BOOL:
                    return std::get<bool>(this->value) == std::get<bool>(other.value);
                default:
                    return false; // Invalid type
            }
        case UNDEFINED:
            switch (other.value.index()) {
                case UNDEFINED:
                    return true;
                default:
                    return false; // Invalid type
            }
        case NULL_TYPE:
            switch (other.value.index()) {
                case NULL_TYPE:
                    return true;
                default:
                    return false; // Invalid type
            }
        default:
            return false; // Invalid type
    }
}

JS::Any JS::Any::operator()(std::vector<JS::Any> &args)
{
    if (!std::holds_alternative<JS::Function>(value)) {
        throw std::runtime_error("Value is not a function");
    }
    return std::get<JS::Function>(value)(args);
}

std::string JS::Any::toString() const
{
    switch (this->value.index()) {
        case NUMBER:
            return std::isnan(std::get<double>(this->value)) ? "NaN" :
                   std::isinf(std::get<double>(this->value)) ? std::get<double>(this->value) < 0 ?
                                   "-Infinity" :
                                   "Infinity" :
                   std::to_string(std::get<double>(this->value));
        case STRING:
            return std::get<std::string>(this->value);
        case BOOL:
            return std::get<bool>(this->value) ? "true" : "false";
        case FUNCTION:
            return "[Function]";
        case UNDEFINED:
            return "undefined";
        case NULL_TYPE:
            return "null";
        default:
            return "[Object]";
    }
}

std::ostream &JS::operator<<(std::ostream &os, const JS::Any &any)
{
    os << any.toString();
    return os;
}

JS::Any &JS::Any::operator[](const std::string &key)
{
    if (std::holds_alternative<std::shared_ptr<JS::Object>>(value)) {
        return std::get<std::shared_ptr<JS::Object>>(value)->operator[](key);
    }
    throw std::runtime_error("Value is not an object");
}

const JS::Any &JS::Any::operator[](const std::string &key) const
{
    if (std::holds_alternative<std::shared_ptr<JS::Object>>(value)) {
        return std::get<std::shared_ptr<JS::Object>>(value)->operator[](key);
    }
    throw std::runtime_error("Value is not an object");
}

JS::Any &JS::Any::operator[](const char *key)
{
    return this->operator[](std::string(key));
}

const JS::Any &JS::Any::operator[](const char *key) const
{
    return this->operator[](std::string(key));
}

JS::Any &JS::Any::operator[](size_t index)
{
    if (std::holds_alternative<std::shared_ptr<JS::Object>>(value)) {
        return std::get<std::shared_ptr<JS::Object>>(value)->operator[](index);
    }
    throw std::runtime_error("Value is not an array");
}

const JS::Any &JS::Any::operator[](size_t index) const
{
    if (std::holds_alternative<std::shared_ptr<JS::Object>>(value)) {
        return std::get<std::shared_ptr<JS::Object>>(value)->operator[](index);
    }
    throw std::runtime_error("Value is not an array");
}

JS::Any &JS::Any::operator[](int index)
{
    if (std::holds_alternative<std::shared_ptr<JS::Object>>(value)) {
        return std::get<std::shared_ptr<JS::Object>>(value)->operator[](index);
    }
    throw std::runtime_error("Value is not an array");
}

const JS::Any &JS::Any::operator[](int index) const
{
    if (std::holds_alternative<std::shared_ptr<JS::Object>>(value)) {
        return std::get<std::shared_ptr<JS::Object>>(value)->operator[](index);
    }
    throw std::runtime_error("Value is not an array");
}






