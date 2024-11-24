#include "../../../includes/types/JsAny.hpp"
#include "../../class/Helper.hpp"

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
                        return JS::Any(std::get<double>(this->value) - Helper::stod(std::get<Rope>(other.value)));
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
                        return JS::Any(Helper::stod(std::get<Rope>(this->value)) - std::get<double>(other.value));
                    case STRING:
                        return JS::Any(Helper::stod(std::get<Rope>(this->value)) - Helper::stod(std::get<Rope>(other.value)));
                    case BOOL:
                        return JS::Any(Helper::stod(std::get<Rope>(this->value)) -
                                       static_cast<double>(std::get<bool>(other.value)));
                    case NULL_TYPE:
                        return JS::Any(Helper::stod(std::get<Rope>(this->value))); // String - Null is String if String is not 0
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case BOOL:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<bool>(this->value) - std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<bool>(this->value)  - Helper::stod(std::get<Rope>(other.value)));
                    case BOOL:
                        return JS::Any(std::get<bool>(this->value) - std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(static_cast<double>(std::get<bool>(this->value))); // Boolean - Null is treated as Boolean
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case NULL_TYPE:
                switch (other.value.index()) {
                    case NUMBER: {
                        double num = std::get<double>(other.value);
                        return JS::Any(num == 0 ? 0 : -num); // Null - Number is -Number if Number is not 0
                    }
                    case STRING: {
                        double num = Helper::stod(std::get<Rope>(other.value));
                        return JS::Any(num == 0 ? 0 : -num); // Null - String is -String if String is not 0
                    }
                    case BOOL: {
                        double num = static_cast<double>(std::get<bool>(other.value));
                        return JS::Any(num == 0 ? 0 : -num); // Null - Boolean is -Boolean if Boolean is not 0
                    }
                    case NULL_TYPE:
                        return JS::Any(0); // Null - Null is 0
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

JS::Any JS::Any::operator-(int value) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::get<double>(this->value) - value);
        case STRING:
            return JS::Any(std::stod(std::get<Rope>(this->value).toString()) - value);
        case BOOL:
            return JS::Any(static_cast<double>(std::get<bool>(this->value)) - value);
        case NULL_TYPE:
            return JS::Any(-value); // Null - Number is -Number
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
    }
}

JS::Any JS::Any::operator-(double value) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::get<double>(this->value) - value);
        case STRING:
            return JS::Any(std::stod(std::get<Rope>(this->value).toString()) - value);
        case BOOL:
            return JS::Any(static_cast<double>(std::get<bool>(this->value)) - value);
        case NULL_TYPE:
            return JS::Any(-value); // Null - Number is -Number
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
    }
}

JS::Any JS::Any::operator-(const char* value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) - std::stod(value));
            case STRING:
                return JS::Any(std::stod(std::get<Rope>(this->value).toString()) - std::stod(value));
            case BOOL:
                return JS::Any(static_cast<double>(std::get<bool>(this->value)) - std::stod(value));
            case NULL_TYPE:
                return JS::Any(-std::stod(value)); // Null - String is -String
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

JS::Any JS::Any::operator-(bool value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) - static_cast<double>(value));
            case STRING:
                return JS::Any(std::stod(std::get<Rope>(this->value).toString()) - static_cast<double>(value));
            case BOOL:
                return JS::Any(static_cast<double>(std::get<bool>(this->value)) - static_cast<double>(value));
            case NULL_TYPE:
                return JS::Any(-static_cast<double>(value)); // Null - Boolean is -Boolean
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

JS::Any JS::Any::operator-(JS::Null) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value));
            case STRING:
                return JS::Any(std::stod(std::get<Rope>(this->value).toString()));
            case BOOL:
                return JS::Any(static_cast<double>(std::get<bool>(this->value)));
            case NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}
JS::Any JS::Any::operator-(JS::Undefined) const { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }

namespace JS {
JS::Any operator-(int value, JS::Any const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(value - std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(value - std::stod(std::get<Rope>(any.getValue()).toString()));
            case BOOL:
                return JS::Any(static_cast<double>(value) - std::get<bool>(any.getValue()));
            case NULL_TYPE:
                return JS::Any(value); // Number - Null is Number
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

JS::Any operator-(double value, JS::Any const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(value - std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(value - std::stod(std::get<Rope>(any.getValue()).toString()));
            case BOOL:
                return JS::Any(value - static_cast<double>(std::get<bool>(any.getValue())));
            case NULL_TYPE:
                return JS::Any(value); // Number - Null is Number
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

JS::Any operator-(bool value, JS::Any const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(static_cast<double>(value) - std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(static_cast<double>(value) - std::stod(std::get<Rope>(any.getValue()).toString()));
            case BOOL:
                return JS::Any(static_cast<double>(value) - static_cast<double>(std::get<bool>(any.getValue())));
            case NULL_TYPE:
                return JS::Any(static_cast<double>(value)); // Boolean - Null is treated as Boolean
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

JS::Any operator-(JS::Null, JS::Any const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(-std::get<double>(any.getValue())); // Null - Number is -Number
            case STRING:
                return JS::Any(-std::stod(std::get<Rope>(any.getValue()).toString())); // Null - String is -String
            case BOOL:
                return JS::Any(-static_cast<double>(std::get<bool>(any.getValue()))); // Null - Boolean is -Boolean
            case NULL_TYPE:
                return JS::Any(0); // Null - Null is 0
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

JS::Any operator-(JS::Undefined, JS::Any const& any) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
} // namespace JS
