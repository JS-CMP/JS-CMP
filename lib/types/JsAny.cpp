#include <types/JsAny.hpp>

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

JS::Value JS::Any::getValue() const { return this->value; }

std::string JS::Any::toString() const {
    switch (this->value.index()) {
        case NUMBER:
            return std::to_string(std::get<double>(this->value));
        case STRING:
            return std::get<Rope>(this->value).toString();
        case BOOL:
            return std::get<bool>(this->value) ? "true" : "false";
        case UNDEFINED:
            return "undefined";
        case NULL_TYPE:
            return "null";
        default:
            return "Invalid type";
    }
}