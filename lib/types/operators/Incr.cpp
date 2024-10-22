#include "../../../includes/types/JsAny.hpp"

JS::Any &JS::Any::operator++() {
    try {
        switch (this->value.index()) {
            case NUMBER:
                ++std::get<double>(this->value);
                break;
            case STRING:
                this->value = static_cast<double>(std::stod(std::get<std::string>(this->value)) + 1);
                break;
            case BOOL:
                this->value = static_cast<double>(std::get<bool>(this->value) + 1);
                break;
            case NULL_TYPE:
                this->value = static_cast<double>(1);
                break;
            default:
                break;
        }
    } catch (const std::invalid_argument &e) {
        value = std::numeric_limits<double>::quiet_NaN();
    }
    return *this;
}

JS::Any &JS::Any::operator++(int) {
    try {
        switch (this->value.index()) {
            case NUMBER:
                std::get<double>(this->value)++;
                break;
            case STRING:
                this->value = static_cast<double>(std::stod(std::get<std::string>(this->value)) + 1);
                break;
            case BOOL:
                this->value = static_cast<double>(std::get<bool>(this->value) + 1);
                break;
            case NULL_TYPE:
                this->value = static_cast<double>(1);
                break;
            default:
                break;
        }
    } catch (const std::invalid_argument &e) {
        value = std::numeric_limits<double>::quiet_NaN();
    }
    return *this;
}