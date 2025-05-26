#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Any::operator==(const JS::Any& other) const {
    switch (this->value.index()) {
        case NUMBER:
            switch (other.value.index()) {
                case NUMBER:
                    return JS::Any(std::get<double>(this->value) == std::get<double>(other.value));
                case STRING:
                    return JS::Any(std::get<double>(this->value) == std::stod(JS::CONVERT::ToUtf8(std::get<Rope>(other.value).toString())));
                case BOOLEAN:
                    return JS::Any(std::get<double>(this->value) == static_cast<double>(std::get<bool>(other.value)));
                default:
                    return JS::Any(false); // Invalid type
            }
        case STRING:
            switch (other.value.index()) {
                case NUMBER:
                    return JS::Any(std::stod(JS::CONVERT::ToUtf8(std::get<Rope>(this->value).toString())) == std::get<double>(other.value));
                case STRING:
                    return JS::Any(std::get<Rope>(this->value) == std::get<Rope>(other.value));
                case BOOLEAN:
                    return JS::Any(std::stod(JS::CONVERT::ToUtf8(std::get<Rope>(this->value).toString())) ==
                                   static_cast<double>(std::get<bool>(other.value)));
                default:
                    return JS::Any(false); // Invalid type
            }
        case BOOLEAN:
            switch (other.value.index()) {
                case NUMBER:
                    return JS::Any(static_cast<double>(std::get<bool>(this->value)) == std::get<double>(other.value));
                case STRING:
                    return JS::Any(static_cast<double>(std::get<bool>(this->value)) ==
                                   std::stod(JS::CONVERT::ToUtf8(std::get<Rope>(other.value).toString())));
                case BOOLEAN:
                    return JS::Any(std::get<bool>(this->value) == std::get<bool>(other.value));
                default:
                    return JS::Any(false); // Invalid type
            }
        case UNDEFINED:
            switch (other.value.index()) {
                case UNDEFINED:
                    return JS::Any(true);
                default:
                    return JS::Any(false); // Invalid type
            }
        case NULL_TYPE:
            switch (other.value.index()) {
                case NULL_TYPE:
                    return JS::Any(true);
                default:
                    return JS::Any(false); // Invalid type
            }
        default:
            return JS::Any(false); // Invalid type
    }
}