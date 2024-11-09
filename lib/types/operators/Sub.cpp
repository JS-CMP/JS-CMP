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

JS::Any JS::Any::operator-(std::string value) const {
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
}

JS::Any JS::Any::operator-(bool value) const {
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
}

JS::Any JS::Any::operator-(JS::Null) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::get<double>(this->value));
        case STRING:
            return JS::Any(std::stod(std::get<Rope>(this->value).toString()));
        case BOOL:
            return JS::Any(static_cast<double>(std::get<bool>(this->value)));
        case NULL_TYPE:
            return JS::Any(0.0);
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}
JS::Any JS::Any::operator-(JS::Undefined) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::get<double>(this->value));
        case STRING:
            return JS::Any(std::stod(std::get<Rope>(this->value).toString()));
        case BOOL:
            return JS::Any(static_cast<double>(std::get<bool>(this->value)));
        case NULL_TYPE:
            return JS::Any(0.0);
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

namespace JS {
JS::Any operator-(int value, JS::Any const& any) {
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
}

JS::Any operator-(double value, JS::Any const& any) {
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
}

JS::Any operator-(std::string value, JS::Any const& any) {
    switch (any.getValue().index()) {
        case NUMBER:
            return JS::Any(std::stod(value) - std::get<double>(any.getValue()));
        case STRING:
            return JS::Any(std::stod(value) - std::stod(std::get<Rope>(any.getValue()).toString()));
        case BOOL:
            return JS::Any(std::stod(value) - static_cast<double>(std::get<bool>(any.getValue())));
        case NULL_TYPE:
            return JS::Any(std::stod(value)); // String - Null is treated as Number
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any operator-(bool value, JS::Any const& any) {
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
}

JS::Any operator-(JS::Null value, JS::Any const& any) {
    switch (any.getValue().index()) {
        case NUMBER:
            return JS::Any(-std::get<double>(any.getValue())); // Null - Number is -Number
        case STRING:
            return JS::Any(-std::stod(std::get<Rope>(any.getValue()).toString())); // Null - String is -String
        case BOOL:
            return JS::Any(-static_cast<double>(std::get<bool>(any.getValue()))); // Null - Boolean is -Boolean
        case NULL_TYPE:
            return JS::Any(0.0); // Null - Null is 0
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any operator-(JS::Undefined value, JS::Any const& any) {
    switch (any.getValue().index()) {
        case NUMBER:
            return JS::Any(std::get<double>(any.getValue()));
        case STRING:
            return JS::Any(std::stod(std::get<Rope>(any.getValue()).toString()));
        case BOOL:
            return JS::Any(static_cast<double>(std::get<bool>(any.getValue())));
        case NULL_TYPE:
            return JS::Any(0.0);
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}
} // namespace JS
