#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

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
                                       JS::CONVERT::ToNumber(std::get<Rope>(other.value)));
                    case BOOLEAN:
                        return JS::Any(std::get<double>(this->value) * std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(0);
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case STRING:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) *
                                       std::get<double>(other.value));
                    case STRING:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) *
                                       JS::CONVERT::ToNumber(std::get<Rope>(other.value)));
                    case BOOLEAN:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) *
                                       std::get<bool>(other.value));
                    case NULL_TYPE:
                        JS::CONVERT::ToNumber(std::get<Rope>(this->value));
                        return JS::Any(0);
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case BOOLEAN:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<bool>(this->value) * std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<bool>(this->value) *
                                       JS::CONVERT::ToNumber(std::get<Rope>(other.value)));
                    case BOOLEAN:
                        return JS::Any(std::get<bool>(this->value) * std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(0);
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case NULL_TYPE:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(0);
                    case STRING:
                        JS::CONVERT::ToNumber(std::get<Rope>(other.value));
                        return JS::Any(0);
                    case BOOLEAN:
                        return JS::Any(0);
                    case NULL_TYPE:
                        return JS::Any(0);
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator*(int value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) * value);
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) * value);
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->value) * value);
            case NULL_TYPE:
                return JS::Any(0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator*(double value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) * value);
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) * value);
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->value) * value);
            case NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator*(const char* value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) * JS::CONVERT::ToNumber(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) * JS::CONVERT::ToNumber(value));
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->value) * JS::CONVERT::ToNumber(value));
            case NULL_TYPE: {
                JS::CONVERT::ToNumber(value);
                return JS::Any(0);
            }
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator*(const char16_t* value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) * JS::CONVERT::ToNumber(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) * JS::CONVERT::ToNumber(value));
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->value) * JS::CONVERT::ToNumber(value));
            case NULL_TYPE: {
                JS::CONVERT::ToNumber(value);
                return JS::Any(0);
            }
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator*(const std::u16string& value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) * JS::CONVERT::ToNumber(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) * JS::CONVERT::ToNumber(value));
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->value) * JS::CONVERT::ToNumber(value));
            case NULL_TYPE: {
                JS::CONVERT::ToNumber(value);
                return JS::Any(0);
            }
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator*(bool value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) * static_cast<double>(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) * static_cast<double>(value));
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->value) * value);
            case NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator*(JS::Null) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) * 0.0);
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) * 0.0);
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->value) * 0.0);
            case NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator*(JS::Undefined /*unused*/) const {
    return JS::Any(std::numeric_limits<double>::quiet_NaN());
}

namespace JS {
Any operator*(int value, const JS::Any& any) {
    try {
        switch (any.getValue().index()) {
            case JS::NUMBER:
                return JS::Any(value * std::get<double>(any.getValue()));
            case JS::STRING:
                return JS::Any(value * JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case JS::BOOLEAN:
                return JS::Any(value * std::get<bool>(any.getValue()));
            case JS::NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator*(double value, const JS::Any& any) {
    try {
        switch (any.getValue().index()) {
            case JS::NUMBER:
                return JS::Any(value * std::get<double>(any.getValue()));
            case JS::STRING:
                return JS::Any(value * JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case JS::BOOLEAN:
                return JS::Any(value * std::get<bool>(any.getValue()));
            case JS::NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator*(const char* value, const JS::Any& any) {
    try {
        switch (any.getValue().index()) {
            case JS::NUMBER:
                return JS::Any(JS::CONVERT::ToNumber(value) * std::get<double>(any.getValue()));
            case JS::STRING:
                return JS::Any(JS::CONVERT::ToNumber(value) * JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case JS::BOOLEAN:
                return JS::Any(JS::CONVERT::ToNumber(value) * std::get<bool>(any.getValue()));
            case JS::NULL_TYPE:
                JS::CONVERT::ToNumber(value);
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator*(const char16_t* value, const JS::Any& any) {
    try {
        switch (any.getValue().index()) {
            case JS::NUMBER:
                return JS::Any(JS::CONVERT::ToNumber(value) * std::get<double>(any.getValue()));
            case JS::STRING:
                return JS::Any(JS::CONVERT::ToNumber(value) * JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case JS::BOOLEAN:
                return JS::Any(JS::CONVERT::ToNumber(value) * std::get<bool>(any.getValue()));
            case JS::NULL_TYPE:
                JS::CONVERT::ToNumber(value);
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator*(const std::u16string& value, const JS::Any& any) {
    try {
        switch (any.getValue().index()) {
            case JS::NUMBER:
                return JS::Any(JS::CONVERT::ToNumber(value) * std::get<double>(any.getValue()));
            case JS::STRING:
                return JS::Any(JS::CONVERT::ToNumber(value) * JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case JS::BOOLEAN:
                return JS::Any(JS::CONVERT::ToNumber(value) * std::get<bool>(any.getValue()));
            case JS::NULL_TYPE:
                JS::CONVERT::ToNumber(value);
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator*(bool value, const JS::Any& any) {
    try {
        switch (any.getValue().index()) {
            case JS::NUMBER:
                return JS::Any(static_cast<double>(value) * std::get<double>(any.getValue()));
            case JS::STRING:
                return JS::Any(static_cast<double>(value) * JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case JS::BOOLEAN:
                return JS::Any(value * std::get<bool>(any.getValue()));
            case JS::NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator*(JS::Null, const JS::Any& any) {
    try {
        switch (any.getValue().index()) {
            case JS::NUMBER:
                return JS::Any(0.0 * std::get<double>(any.getValue()));
            case JS::STRING:
                return JS::Any(0.0 * JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case JS::BOOLEAN:
                return JS::Any(0.0 * std::get<bool>(any.getValue()));
            case JS::NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator*(JS::Undefined /*unused*/, const JS::Any& /*unused*/) {
    return JS::Any(std::numeric_limits<double>::quiet_NaN());
}
} // namespace JS
