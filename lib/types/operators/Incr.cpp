#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any& JS::Any::operator++() {
    try {
        switch (this->value.index()) {
            case NUMBER:
                ++std::get<double>(this->value);
                break;
            case STRING:
                this->value = static_cast<double>(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) + 1);
                break;
            case BOOLEAN:
                this->value = static_cast<double>(std::get<bool>(this->value) + 1);
                break;
            case NULL_TYPE:
                this->value = static_cast<double>(1);
                break;
            default:
                break;
        }
    } catch (const std::invalid_argument& e) { value = std::numeric_limits<double>::quiet_NaN(); }
    return *this;
}

const JS::Any& JS::Any::operator++(int) {
    try {
        switch (this->value.index()) {
            case NUMBER:
                std::get<double>(this->value)++;
                break;
            case STRING:
                this->value = static_cast<double>(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) + 1);
                break;
            case BOOLEAN:
                this->value = static_cast<double>(std::get<bool>(this->value) + 1);
                break;
            case NULL_TYPE:
                this->value = static_cast<double>(1);
                break;
            default:
                break;
        }
    } catch (const std::invalid_argument& e) { value = std::numeric_limits<double>::quiet_NaN(); }
    return *this;
}