#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Operator::operator>(const JS::Operator& other) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:

                switch (other.getValue().index()) {
                    case NUMBER:
                        return JS::Any(std::get<double>(this->getValue()) > std::get<double>(other.getValue()));
                    case STRING:
                        return JS::Any(std::get<double>(this->getValue()) > JS::CONVERT::ToNumber(std::get<Rope>(other.getValue())));
                    case BOOLEAN:
                        return JS::Any(static_cast<long long int>(std::get<double>(this->getValue())) > std::get<bool>(other.getValue()));
                    case NULL_TYPE:
                        return JS::Any(static_cast<long long int>(std::get<double>(this->getValue())) > 0);
                    default:
                        return JS::Any(false);
                }
            case STRING:

                switch (other.getValue().index()) {
                    case NUMBER:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())) > std::get<double>(other.getValue()));
                    case STRING:
                        return JS::Any(std::get<Rope>(this->getValue()).compare(std::get<Rope>(other.getValue())) > 0);
                    case BOOLEAN:
                        return JS::Any(static_cast<long long int>(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue()))) > std::get<bool>(other.getValue()));
                    case FUNCTION:
                        return JS::Any(JS::CONVERT::ToString(*this).compare(JS::CONVERT::ToString(other)) > 0);
                    case NULL_TYPE: // TODO: fix narrowing conversion
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                    default:
                        return JS::Any(false);
                }
            case BOOLEAN:

                switch (other.getValue().index()) {
                    case NUMBER:
                        return JS::Any(std::get<bool>(this->getValue()) > static_cast<long long int>(std::get<double>(other.getValue())));
                    case STRING:
                        return JS::Any(std::get<bool>(this->getValue()) > static_cast<long long int>(JS::CONVERT::ToNumber(std::get<Rope>(other.getValue()))));
                    case BOOLEAN:
                        return JS::Any(std::get<bool>(this->getValue()) > std::get<bool>(other.getValue()));
                    case FUNCTION:
                        return JS::Any(JS::CONVERT::ToString(*this).compare(JS::CONVERT::ToString(other)) > 0);
                    case NULL_TYPE:
                        return JS::Any(std::get<bool>(this->getValue()) > false);

                    default:
                        return JS::Any(false);
                }
            case NULL_TYPE:

                switch (other.getValue().index()) {
                    case NUMBER:
                        return JS::Any(0.0 > std::get<double>(other.getValue()));
                    case STRING:
                        return JS::Any(0.0 > JS::CONVERT::ToNumber(std::get<Rope>(other.getValue())));
                    case BOOLEAN:
                        return JS::Any(false < std::get<bool>(other.getValue()));
                    default:
                        return JS::Any(false);
                }
            default:
                return JS::Any(false);
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(false);
    }
}