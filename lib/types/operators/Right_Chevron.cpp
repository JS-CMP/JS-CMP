#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

bool JS::Any::operator>(const JS::Any& other) const {
    try {
        switch (this->value.index()) {
            case NUMBER:

                switch (other.value.index()) {
                    case NUMBER:
                        return std::get<double>(this->value) > std::get<double>(other.value);
                    case STRING:
                        return std::get<double>(this->value) > JS::CONVERT::ToNumber(std::get<Rope>(other.value));
                    case BOOLEAN:
                        return static_cast<long long int>(std::get<double>(this->value)) > std::get<bool>(other.value);
                    case NULL_TYPE:
                        return static_cast<long long int>(std::get<double>(this->value)) > 0;
                    default:
                        return false;
                }
            case STRING:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::CONVERT::ToNumber(std::get<Rope>(this->value)) > std::get<double>(other.value);
                    case STRING:
                        return std::get<Rope>(this->value).compare(std::get<Rope>(other.value)) > 0;
                    case BOOLEAN:
                        return static_cast<long long int>(JS::CONVERT::ToNumber(std::get<Rope>(this->value))) >
                               std::get<bool>(other.value);
                    case FUNCTION:
                        return JS::CONVERT::ToString(*this).compare(JS::CONVERT::ToString(other)) > 0;
                    case NULL_TYPE: // TODO: fix narrowing conversion
                        return std::numeric_limits<double>::quiet_NaN();
                    default:
                        return false;
                }
            case BOOLEAN:

                switch (other.value.index()) {
                    case NUMBER:
                        return std::get<bool>(this->value) > static_cast<long long int>(std::get<double>(other.value));
                    case STRING:
                        return std::get<bool>(this->value) >
                               static_cast<long long int>(JS::CONVERT::ToNumber(std::get<Rope>(other.value)));
                    case BOOLEAN:
                        return std::get<bool>(this->value) > std::get<bool>(other.value);
                    case FUNCTION:
                        return JS::CONVERT::ToString(*this).compare(JS::CONVERT::ToString(other)) > 0;
                    case NULL_TYPE:
                        return std::get<bool>(this->value) > false;

                    default:
                        return false;
                }
            case NULL_TYPE:

                switch (other.value.index()) {
                    case NUMBER:
                        return 0.0 > std::get<double>(other.value);
                    case STRING:
                        return 0.0 > JS::CONVERT::ToNumber(std::get<Rope>(other.value));
                    case BOOLEAN:
                        return false < std::get<bool>(other.value);
                    default:
                        return false;
                }
            default:
                return false;
        }
    } catch (const std::invalid_argument&) { return false; }
}