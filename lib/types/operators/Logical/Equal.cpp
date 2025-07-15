#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Operator::operator==(const JS::Operator& other) const {
    switch (this->getValue().index()) {
        case NUMBER:
            switch (other.getValue().index()) {
                case NUMBER:
                    return JS::Any(std::get<double>(this->getValue()) == std::get<double>(other.getValue()));
                case STRING:
                    return JS::Any(std::get<double>(this->getValue()) ==
                                   std::stod(JS::CONVERT::ToUtf8(std::get<Rope>(other.getValue()).toString())));
                case BOOLEAN:
                    return JS::Any(std::get<double>(this->getValue()) ==
                                   static_cast<double>(std::get<bool>(other.getValue())));
                default:
                    return JS::Any(false); // Invalid type
            }
        case STRING:
            switch (other.getValue().index()) {
                case NUMBER:
                    return JS::Any(std::stod(JS::CONVERT::ToUtf8(std::get<Rope>(this->getValue()).toString())) ==
                                   std::get<double>(other.getValue()));
                case STRING:
                    return JS::Any(std::get<Rope>(this->getValue()) == std::get<Rope>(other.getValue()));
                case BOOLEAN:
                    return JS::Any(std::stod(JS::CONVERT::ToUtf8(std::get<Rope>(this->getValue()).toString())) ==
                                   static_cast<double>(std::get<bool>(other.getValue())));
                default:
                    return JS::Any(false); // Invalid type
            }
        case BOOLEAN:
            switch (other.getValue().index()) {
                case NUMBER:
                    return JS::Any(static_cast<double>(std::get<bool>(this->getValue())) ==
                                   std::get<double>(other.getValue()));
                case STRING:
                    return JS::Any(static_cast<double>(std::get<bool>(this->getValue())) ==
                                   std::stod(JS::CONVERT::ToUtf8(std::get<Rope>(other.getValue()).toString())));
                case BOOLEAN:
                    return JS::Any(std::get<bool>(this->getValue()) == std::get<bool>(other.getValue()));
                default:
                    return JS::Any(false); // Invalid type
            }
        case UNDEFINED:
            switch (other.getValue().index()) {
                case UNDEFINED:
                    return JS::Any(true);
                default:
                    return JS::Any(false); // Invalid type
            }
        case NULL_TYPE:
            switch (other.getValue().index()) {
                case NULL_TYPE:
                    return JS::Any(true);
                default:
                    return JS::Any(false); // Invalid type
            }
        default:
            return JS::Any(false); // Invalid type
    }
}