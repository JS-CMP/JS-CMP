#include "../../../includes/types/JsAny.hpp"

JS::Any JS::Any::operator/(const JS::Any& other) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<double>(this->value) / std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<double>(this->value) /
                                       std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::get<double>(this->value) / std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(std::numeric_limits<double>::infinity());
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Undefined
                                                                                  // case
                }
            case STRING:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::stod(std::get<Rope>(this->value).toString()) /
                                       std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::stod(std::get<Rope>(this->value).toString()) /
                                       std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::stod(std::get<Rope>(this->value).toString()) / std::get<bool>(other.value));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case BOOL:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<bool>(this->value) / std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<bool>(this->value) / std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::get<bool>(this->value) / std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(std::numeric_limits<double>::infinity());
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case NULL_TYPE:
                return JS::Any(0); // Division by null always returns 0

            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // For undefined cases, return NaN
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Catch invalid
                                                                  // conversions
    }
}

JS::Any JS::Any::operator/(int value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / value);
            case STRING:
                return JS::Any(std::stod(std::get<Rope>(this->value).toString()) / value);
            case BOOL:
                return value == 0 ? JS::Any(std::numeric_limits<double>::infinity())
                                  : JS::Any(std::get<bool>(this->value) / value);
            case NULL_TYPE:
                return JS::Any(std::numeric_limits<double>::infinity());
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator/(double value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / value);
            case STRING:
                return JS::Any(std::stod(std::get<Rope>(this->value).toString()) / value);
            case BOOL:
                return JS::Any(std::get<bool>(this->value) / value);
            case NULL_TYPE:
                return JS::Any(std::numeric_limits<double>::infinity());
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator/(const char* value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / std::stod(value));
            case STRING:
                return JS::Any(std::stod(std::get<Rope>(this->value).toString()) / std::stod(value));
            case BOOL:
                return JS::Any(std::get<bool>(this->value) / std::stod(value));
            case NULL_TYPE:
                return JS::Any(std::numeric_limits<double>::infinity());
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator/(bool value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / static_cast<double>(value));
            case STRING:
                return JS::Any(std::stod(std::get<Rope>(this->value).toString()) / static_cast<double>(value));
            case BOOL: {
                bool thisValue = std::get<bool>(this->value);
                return JS::Any(thisValue && !value   ? std::numeric_limits<double>::infinity()
                               : thisValue && value  ? 1
                               : !thisValue && value ? 0
                                                     : std::numeric_limits<double>::quiet_NaN());
            }
            case NULL_TYPE:
                return JS::Any(std::numeric_limits<double>::infinity());
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator/(JS::Null) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::get<double>(this->value) / 0.0);
        case STRING:
            return JS::Any(std::stod(std::get<Rope>(this->value).toString()) / 0.0);
        case BOOL:
            return std::get<bool>(this->value) ? JS::Any(std::numeric_limits<double>::infinity())
                                               : JS::Any(std::numeric_limits<double>::quiet_NaN());
        case NULL_TYPE:
            return JS::Any(std::numeric_limits<double>::quiet_NaN()); // NULL / NULL -> NaN
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator/(JS::Undefined) const { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }

namespace JS {
Any operator/(int value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(value / std::get<double>(any.value));
            case STRING:
                return JS::Any(value / std::stod(std::get<Rope>(any.value).toString()));
            case BOOL:
                return JS::Any(value / std::get<bool>(any.value));
            case NULL_TYPE:
                return JS::Any(std::numeric_limits<double>::infinity());
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator/(double value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(value / std::get<double>(any.value));
            case STRING:
                return JS::Any(value / std::stod(std::get<Rope>(any.value).toString()));
            case BOOL:
                return JS::Any(value / std::get<bool>(any.value));
            case NULL_TYPE:
                return JS::Any(std::numeric_limits<double>::infinity());
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator/(const char* value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::stod(value) / std::get<double>(any.value));
            case STRING:
                return JS::Any(std::stod(value) / std::stod(std::get<Rope>(any.value).toString()));
            case BOOL:
                return JS::Any(std::stod(value) / std::get<bool>(any.value));
            case NULL_TYPE:
                return JS::Any(std::numeric_limits<double>::infinity());
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator/(bool value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(static_cast<double>(value) / std::get<double>(any.value));
            case STRING:
                return JS::Any(static_cast<double>(value) / std::stod(std::get<Rope>(any.value).toString()));
            case BOOL:
                return JS::Any(value / std::get<bool>(any.value));
            case NULL_TYPE:
                return JS::Any(std::numeric_limits<double>::infinity());
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator/(JS::Null value, JS::Any const& any) {
    switch (any.value.index()) {
        case NUMBER:
            return JS::Any(0 / std::get<double>(any.value));
        case STRING:
            return JS::Any(0 / std::stod(std::get<Rope>(any.value).toString()));
        case BOOL:
            return JS::Any(0 / std::get<bool>(any.value));
        case NULL_TYPE:
            return JS::Any(std::numeric_limits<double>::infinity());
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(JS::Undefined value, JS::Any const& any) {
    switch (any.value.index()) {
        case NUMBER:
            return JS::Any(0 / std::get<double>(any.value));
        case STRING:
            return JS::Any(0 / std::stod(std::get<Rope>(any.value).toString()));
        case BOOL:
            return JS::Any(0 / std::get<bool>(any.value));
        case NULL_TYPE:
            return JS::Any(std::numeric_limits<double>::infinity());
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}
} // namespace JS