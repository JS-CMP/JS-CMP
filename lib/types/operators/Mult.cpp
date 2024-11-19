#include "../../../includes/types/JsAny.hpp"

JS::Any JS::Any::operator*(const JS::Any& other) const {
    // TODO: change with infinite precision the stol
    try {
        switch (this->value.index()) {
            case NUMBER:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<double>(this->value) * std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<double>(this->value) *
                                       std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::get<double>(this->value) * std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(0);
                    default:
                        throw std::runtime_error("Invalid types for multiplication");
                }
            case STRING:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::stod(std::get<Rope>(this->value).toString()) *
                                       std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::stod(std::get<Rope>(this->value).toString()) *
                                       std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::stod(std::get<Rope>(this->value).toString()) * std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(0);
                    default:
                        throw std::runtime_error("Invalid types for multiplication");
                }
            case BOOL:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<bool>(this->value) * std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<bool>(this->value) * std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::get<bool>(this->value) * std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(0);
                    default:
                        throw std::runtime_error("Invalid types for multiplication");
                }
            case NULL_TYPE:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(0.0);
                    case STRING:
                        return JS::Any(0.0);
                    case BOOL:
                        return JS::Any(0.0);
                    case FUNCTION:
                        return JS::Any(0.0);
                    case NULL_TYPE:
                        return JS::Any(0);
                    default:
                        throw std::runtime_error("Invalid types for multiplication");
                }
            default:
                throw std::runtime_error("Invalid types for multiplication");
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    } catch (const std::runtime_error& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle multiplication
                                                                  // of invalid types
    }
}

JS::Any JS::Any::operator*(int value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) * value);
            case STRING:
                return JS::Any(std::stod(std::get<Rope>(this->value).toString()) * value);
            case BOOL:
                return JS::Any(std::get<bool>(this->value) * value);
            case NULL_TYPE:
                return JS::Any(0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

JS::Any JS::Any::operator*(double value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) * value);
            case STRING:
                return JS::Any(std::stod(std::get<Rope>(this->value).toString()) * value);
            case BOOL:
                return JS::Any(std::get<bool>(this->value) * value);
            case NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

JS::Any JS::Any::operator*(const char* value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) * std::stod(value));
            case STRING:
                return JS::Any(std::stod(std::get<Rope>(this->value).toString()) * std::stod(value));
            case BOOL:
                return JS::Any(std::get<bool>(this->value) * std::stod(value));
            case NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

JS::Any JS::Any::operator*(bool value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) * static_cast<double>(value));
            case STRING:
                return JS::Any(std::stod(std::get<Rope>(this->value).toString()) * static_cast<double>(value));
            case BOOL:
                return JS::Any(std::get<bool>(this->value) * value);
            case NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

JS::Any JS::Any::operator*(JS::Null) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::get<double>(this->value) * 0.0);
        case STRING:
            return JS::Any(std::stod(std::get<Rope>(this->value).toString()) * 0.0);
        case BOOL:
            return JS::Any(std::get<bool>(this->value) * 0.0);
        case NULL_TYPE:
            return JS::Any(0);
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
    }
}

JS::Any JS::Any::operator*(JS::Undefined) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::get<double>(this->value) * 0.0);
        case STRING:
            return JS::Any(std::stod(std::get<Rope>(this->value).toString()) * 0.0);
        case BOOL:
            return JS::Any(std::get<bool>(this->value) * 0.0);
        case NULL_TYPE:
            return JS::Any(0);
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
    }
}

namespace JS {
Any operator*(int value, const JS::Any& any) {
    try {
        switch (any.getValue().index()) {
            case JS::NUMBER:
                return JS::Any(value * std::get<double>(any.getValue()));
            case JS::STRING:
                return JS::Any(value * std::stod(std::get<Rope>(any.getValue()).toString()));
            case JS::BOOL:
                return JS::Any(value * std::get<bool>(any.getValue()));
            case JS::NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

Any operator*(double value, const JS::Any& any) {
    try {
        switch (any.getValue().index()) {
            case JS::NUMBER:
                return JS::Any(value * std::get<double>(any.getValue()));
            case JS::STRING:
                return JS::Any(value * std::stod(std::get<Rope>(any.getValue()).toString()));
            case JS::BOOL:
                return JS::Any(value * std::get<bool>(any.getValue()));
            case JS::NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

Any operator*(const char* value, const JS::Any& any) {
    try {
        switch (any.getValue().index()) {
            case JS::NUMBER:
                return JS::Any(std::stod(value) * std::get<double>(any.getValue()));
            case JS::STRING:
                return JS::Any(std::stod(value) * std::stod(std::get<Rope>(any.getValue()).toString()));
            case JS::BOOL:
                return JS::Any(std::stod(value) * std::get<bool>(any.getValue()));
            case JS::NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

Any operator*(bool value, const JS::Any& any) {
    try {
        switch (any.getValue().index()) {
            case JS::NUMBER:
                return JS::Any(static_cast<double>(value) * std::get<double>(any.getValue()));
            case JS::STRING:
                return JS::Any(static_cast<double>(value) * std::stod(std::get<Rope>(any.getValue()).toString()));
            case JS::BOOL:
                return JS::Any(value * std::get<bool>(any.getValue()));
            case JS::NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle conversion errors
    }
}

Any operator*(JS::Null value, const JS::Any& any) {
    switch (any.getValue().index()) {
        case JS::NUMBER:
            return JS::Any(0.0 * std::get<double>(any.getValue()));
        case JS::STRING:
            return JS::Any(0.0 * std::stod(std::get<Rope>(any.getValue()).toString()));
        case JS::BOOL:
            return JS::Any(0.0 * std::get<bool>(any.getValue()));
        case JS::NULL_TYPE:
            return JS::Any(0);
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
    }
}

Any operator*(JS::Undefined value, const JS::Any& any) {
    switch (any.getValue().index()) {
        case JS::NUMBER:
            return JS::Any(0.0 * std::get<double>(any.getValue()));
        case JS::STRING:
            return JS::Any(0.0 * std::stod(std::get<Rope>(any.getValue()).toString()));
        case JS::BOOL:
            return JS::Any(0.0 * std::get<bool>(any.getValue()));
        case JS::NULL_TYPE:
            return JS::Any(0);
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Invalid type
    }
}
} // namespace JS
