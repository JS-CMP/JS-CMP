#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Any::operator<(const JS::Any& other) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<double>(this->value) < std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<double>(this->value) <
                                       JS::CONVERT::ToNumber(std::get<Rope>(other.value)));
                    case BOOLEAN:
                        return JS::Any(std::get<double>(this->value) <
                                       static_cast<double>(std::get<bool>(other.value)));
                    case FUNCTION:
                        return JS::Any(JS::CONVERT::ToString(*this).compare(JS::CONVERT::ToString(other)) < 0);
                    default:
                        return JS::Any(false);
                }
            case STRING:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) <
                                       std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<Rope>(this->value).compare(std::get<Rope>(other.value)) < 0);
                    case BOOLEAN:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) <
                                       std::get<bool>(other.value));
                    case FUNCTION:
                        return JS::Any(
                            std::get<Rope>(this->value).toString().compare(std::get<Rope>(other.value).toString()) < 0);
                    default:
                        return JS::Any(false);
                }
            case BOOLEAN:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<bool>(this->value) <
                                       static_cast<long long int>(std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(std::get<bool>(this->value) <
                                       static_cast<long long int>(JS::CONVERT::ToNumber(std::get<Rope>(other.value))));
                    case BOOLEAN:
                        return JS::Any(std::get<bool>(this->value) < std::get<bool>(other.value));
                    case FUNCTION:
                        return JS::Any(JS::CONVERT::ToString(*this).compare(JS::CONVERT::ToString(other)) < 0);
                    default:
                        return JS::Any(false);
                }
            case NULL_TYPE:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(0.0 < std::get<double>(other.value));
                    case STRING:
                        return JS::Any(0.0 < JS::CONVERT::ToNumber(std::get<Rope>(other.value)));
                    case BOOLEAN:
                        return JS::Any(0 < std::get<bool>(other.value));
                    default:
                        return JS::Any(false);
                }
            default:
                return JS::Any(false);
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(false);
    }
}