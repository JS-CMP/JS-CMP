#include "../../../includes/types/JsAny.hpp"

bool JS::Any::operator<(const JS::Any &other) const
{
    try {
        switch (this->value.index()) {
            case NUMBER:
                switch (other.value.index()) {
                    case NUMBER:
                        return std::get<double>(this->value) < std::get<double>(other.value);
                    case STRING:
                        return std::get<double>(this->value) < std::stod(std::get<Rope>(other.value).toString());
                    case BOOL:
                        return std::get<double>(this->value) < static_cast<double>(std::get<bool>(other.value));
                    case FUNCTION:
                        return this->toString().compare(other.toString()) < 0;
                    default:
                        return false;
                }
            case STRING:
                switch (other.value.index()) {
                    case NUMBER:
                        return std::stod(std::get<Rope>(this->value).toString()) < std::get<double>(other.value);
                    case STRING:
                        return std::get<Rope>(this->value).toString().compare(std::get<Rope>(other.value).toString()) < 0;
                    case BOOL:
                        return std::stod(std::get<Rope>(this->value).toString()) < std::get<bool>(other.value);
                    case FUNCTION:
                        return std::get<Rope>(this->value).toString().compare(std::get<Rope>(other.value).toString()) < 0;
                    default:
                        return false;
                }
            case BOOL:
                switch (other.value.index()) {
                    case NUMBER:
                        return std::get<bool>(this->value) < static_cast<long long int>(std::get<double>(other.value));
                    case STRING:
                        return std::get<bool>(this->value) < static_cast<long long int>(std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return std::get<bool>(this->value) < std::get<bool>(other.value);
                    case FUNCTION:
                        return this->toString().compare(other.toString()) < 0;
                    default:
                        return false;
                }
            case NULL_TYPE:
                switch (other.value.index()) {
                    case NUMBER:
                        return 0.0 < std::get<double>(other.value);
                    case STRING:
                        return 0.0 < std::stod(std::get<Rope>(other.value).toString());
                    case BOOL:
                        return 0 < std::get<bool>(other.value);
                    default:
                        return false;
                }
            default: // handle function and undefined
                return false;
        }
    } catch (const std::invalid_argument &e) {
        return false;
    }
}
