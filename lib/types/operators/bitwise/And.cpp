#include "../../../includes/types/JsAny.hpp"

JS::Any JS::Any::operator&(const JS::Any& other) const {
    switch (this->value.index()) {
        case NUMBER:
            switch (other.value.index()) {
                case NUMBER:
                    return JS::Any(static_cast<double>(static_cast<int>(std::get<double>(this->value)) & static_cast<int>(std::get<double>(other.value))));
                case STRING:
                    return JS::Any(static_cast<double>(static_cast<int>(std::get<double>(this->value)) & std::get<Rope>(other.value).toInt()));
                case BOOL:
                    return JS::Any(static_cast<double>(static_cast<int>(std::get<double>(this->value)) & static_cast<int>(std::get<bool>(other.value))));
                case FUNCTION:
                    return JS::Any(static_cast<double>(static_cast<int>(std::get<double>(this->value)) & static_cast<int>(other.value.index())));
                case UNDEFINED:
                    return JS::Any(static_cast<double>(static_cast<int>(std::get<double>(this->value)) & 0));
                case NULL_TYPE:
                    return JS::Any(static_cast<double>(static_cast<int>(std::get<double>(this->value)) & 0));
            }
            break;
        case STRING:
            switch (other.value.index()) {
                case NUMBER:
                    return JS::Any(std::get<Rope>(this->value).toInt() & static_cast<int>(std::get<double>(other.value)));
                case STRING:
                    return JS::Any(std::get<Rope>(this->value).toInt() & std::get<Rope>(other.value).toInt());
                default:
                    return JS::Any(std::get<Rope>(this->value).toInt() & 0);
            }
            break;
        case BOOL:
            switch (other.value.index()) {
                case NUMBER:
                    return JS::Any(static_cast<double>(static_cast<int>(std::get<bool>(this->value)) &
                                                       static_cast<int>(std::get<double>(other.value))));
                case STRING:
                    return JS::Any(static_cast<double>(static_cast<int>(std::get<bool>(this->value)) &
                                                       std::get<Rope>(other.value).toInt()));
                case BOOL:
                    return JS::Any(static_cast<double>(static_cast<int>(std::get<bool>(this->value)) &
                                                       static_cast<int>(std::get<bool>(other.value))));
                case FUNCTION: // TODO
            }
            break;
        default:
            return JS::Any(0);
    }
    return JS::Any(0);
}