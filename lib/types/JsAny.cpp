#include "utils/Convert.hpp"

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
        case OBJECT:
            switch (other.value.index()) {
                case OBJECT:
                    return &std::get<std::shared_ptr<InternalObject>>(this->value) ==
                           &std::get<std::shared_ptr<InternalObject>>(other.value);
                default:
                    return false; // Invalid type
            }
        default:
            return false; // Invalid type
    }
}

bool JS::Any::strictEq(const JS::Any& other) const {
    // TODO: handle identity
    std::cout << value.index() << " " << other.value.index() << std::endl;
    if (this->value.index() != other.value.index()) {
        return false;
    }
    switch (this->value.index()) {
        case NUMBER:
            return std::get<double>(this->value) == std::get<double>(other.value);
        case STRING:
            return std::get<Rope>(this->value) == std::get<Rope>(other.value);
        case BOOL:
            return std::get<bool>(this->value) == std::get<bool>(other.value);
        case UNDEFINED:
            return true;
        case NULL_TYPE:
            return true;
        case OBJECT:
            return &std::get<std::shared_ptr<InternalObject>>(this->value) ==
                   &std::get<std::shared_ptr<InternalObject>>(other.value);
        default:
            return false;
    }
}

bool JS::Any::strictNeq(const JS::Any& other) const { return !this->strictEq(other); }

bool JS::Any::operator!() const {
    switch (this->value.index()) {
        case NUMBER:
            return std::get<double>(this->value) == 0;
        case STRING:
            return std::get<Rope>(this->value).toString().empty();
        case BOOL:
            return !std::get<bool>(this->value);
        case UNDEFINED:
            return true;
        case NULL_TYPE:
            return true;
        case OBJECT:
            return false;
        default:
            return false;
    }
}

JS::Value JS::Any::getValue() const { return this->value; }