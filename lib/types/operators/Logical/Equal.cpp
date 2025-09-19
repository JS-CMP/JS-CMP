#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Operator::operator==(const JS::Operator& other) const {
    switch (this->getValue().index()) {
        case NUMBER:
            switch (other.getValue().index()) {
                case NUMBER:
                    return JS::Any(std::get<double>(this->getValue()) == std::get<double>(other.getValue()));
                case STRING: {
                    Rope otherRope = std::get<Rope>(other.getValue());
                    return JS::Any(std::get<double>(this->getValue()) ==
                                   (otherRope.length() == 0 ? 0 : std::stod(JS::CONVERT::ToUtf8(otherRope.toString()))));
                }
                case BOOLEAN:
                    return JS::Any(std::get<double>(this->getValue()) ==
                                   static_cast<double>(std::get<bool>(other.getValue())));
                default:
                    return JS::Any(false); // Invalid type
            }
        case STRING: {
            Rope thisRope = std::get<Rope>(this->getValue());
            switch (other.getValue().index()) {
                case NUMBER:
                    return JS::Any((thisRope.length() == 0 ? 0 : std::stod(JS::CONVERT::ToUtf8(thisRope.toString()))) ==
                                   std::get<double>(other.getValue()));
                case STRING:
                    return JS::Any(thisRope == std::get<Rope>(other.getValue()));
                case BOOLEAN:
                    return JS::Any((thisRope.length() == 0 ? 0 : std::stod(JS::CONVERT::ToUtf8(thisRope.toString()))) ==
                                   static_cast<double>(std::get<bool>(other.getValue())));
                default:
                    return JS::Any(false); // Invalid type
            }}
        case BOOLEAN:
            switch (other.getValue().index()) {
                case NUMBER:
                    return JS::Any(static_cast<double>(std::get<bool>(this->getValue())) ==
                                   std::get<double>(other.getValue()));
                case STRING: {
                    Rope otherRope = std::get<Rope>(other.getValue());
                    return JS::Any(static_cast<double>(std::get<bool>(this->getValue())) ==
                                   (otherRope.length() == 0 ? 0 : std::stod(JS::CONVERT::ToUtf8(otherRope.toString()))));
                }
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