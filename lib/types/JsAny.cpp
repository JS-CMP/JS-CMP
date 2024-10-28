#include <cmath>
#include "../../includes/types/JsAny.hpp"

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

namespace JS {
    std::ostream &operator<<(std::ostream &os, const Any &any)
    {
        os << any.toString();
        return os;
    }
}







