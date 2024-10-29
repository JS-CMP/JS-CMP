#include "../../../includes/types/JsAny.hpp"

JS::Any JS::Any::operator-(const JS::Any& other) const {
    // TODO: check float precision
    // change with infinite precision the stod
    try {
        switch (this->value.index()) {
            case NUMBER:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<double>(this->value) - std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<double>(this->value) -
                                       std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::get<double>(this->value) -
                                       static_cast<double>(std::get<bool>(other.value)));
                    case NULL_TYPE:
                        return JS::Any(std::get<double>(this->value)); // Number - Null is Number
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case STRING:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::stod(std::get<Rope>(other.value).toString()) -
                                       std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::stod(std::get<Rope>(other.value).toString()) -
                                       std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::stod(std::get<Rope>(other.value).toString()) - std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(
                            std::stod(std::get<Rope>(other.value).toString())); // String - Null is treated as
                                                                                // Number, if stod throw nan
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case BOOL:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<bool>(this->value) - std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<bool>(this->value) - std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::get<bool>(this->value) - std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(std::get<bool>(this->value)); // Boolean - Null is
                                                                     // treated as Boolean
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case NULL_TYPE:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(-std::get<double>(other.value)); // Null - Number is -Number
                    case STRING:
                        return JS::Any(-std::stod(std::get<Rope>(other.value).toString())); // Null - String is -String
                    case BOOL:
                        return JS::Any(-static_cast<double>(std::get<bool>(other.value))); // Null - Boolean is -Boolean
                    case NULL_TYPE:
                        return JS::Any(0.0); // Null - Null is 0
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion
                                                                  // errors
    }
}