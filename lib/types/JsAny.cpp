#include "../../includes/types/JsAny.hpp"
#include "../../includes/types/Objects/JsFunction.hpp"
#include <cmath>

namespace JS {
    std::ostream& operator<<(std::ostream& os, const Any& any) {
        os << any.toString();
        return os;
    }
}

bool JS::Any::operator==(const JS::Any& other) const {
    switch (this->value.index()) {
        case NUMBER:

            switch (other.value.index()) {
                case NUMBER:
                    return std::get<double>(this->value) == std::get<double>(other.value);
                case STRING:
                    return std::get<double>(this->value) == std::stod(std::get<Rope>(other.value).toString());
                case BOOL:
                    return std::get<double>(this->value) == static_cast<double>(std::get<bool>(other.value));
                default:
                    return false; // Invalid type
            }
        case STRING:

            switch (other.value.index()) {
                case NUMBER:
                    return std::stod(std::get<Rope>(this->value).toString()) == std::get<double>(other.value);
                case STRING:
                    return std::get<Rope>(this->value) == std::get<Rope>(other.value);
                case BOOL:
                    return std::stod(std::get<Rope>(this->value).toString()) ==
                           static_cast<double>(std::get<bool>(other.value));
                default:
                    return false; // Invalid type
            }
        case BOOL:

            switch (other.value.index()) {
                case NUMBER:
                    return static_cast<double>(std::get<bool>(this->value)) == std::get<double>(other.value);
                case STRING:
                    return static_cast<double>(std::get<bool>(this->value)) ==
                           std::stod(std::get<Rope>(other.value).toString());
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

std::string JS::Any::toString() const {
    switch (this->value.index()) {
        case NUMBER:
            return std::isnan(std::get<double>(this->value)) ? "NaN"
                   : std::isinf(std::get<double>(this->value))
                       ? std::get<double>(this->value) < 0 ? "-Infinity" : "Infinity"
                       : std::to_string(std::get<double>(this->value));
        case STRING:
            return std::get<Rope>(this->value).toString();
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

JS::Any& JS::Any::operator[](const std::string& key) const {
    if (this->value.index() == OBJECT) {
        return std::get<std::shared_ptr<JS::Object>>(this->value)->operator[](key);
    }
    throw std::runtime_error("Value is not an object");
}

JS::Any& JS::Any::operator[](size_t index) const {
    if (this->value.index() == OBJECT) {
        return std::get<std::shared_ptr<JS::Object>>(this->value)->operator[](index);
    }
    throw std::runtime_error("Value is not an object");
}

JS::Any JS::Any::helper(std::vector<JS::Any> &args) const {
    if (value.index() == JS::OBJECT && std::get<std::shared_ptr<JS::Object>>(value)->isCallable()) {
        return std::dynamic_pointer_cast<JS::Function>(std::get<std::shared_ptr<JS::Object>>(value))->operator()(args);
    }
    throw std::runtime_error("Value is not a function");
}