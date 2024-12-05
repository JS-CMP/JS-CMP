#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

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
                                       JS::CONVERT::ToNumber(std::get<Rope>(other.value)));
                    case BOOL:
                        return JS::Any(std::get<double>(this->value) -
                                       static_cast<double>(std::get<bool>(other.value)));
                    case NULL_TYPE:
                        return JS::Any(std::get<double>(this->value));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case STRING:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) -
                                       std::get<double>(other.value));
                    case STRING:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) -
                                       JS::CONVERT::ToNumber(std::get<Rope>(other.value)));
                    case BOOL:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) -
                                       static_cast<double>(std::get<bool>(other.value)));
                    case NULL_TYPE:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case BOOL:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<bool>(this->value) - std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<bool>(this->value) -
                                       JS::CONVERT::ToNumber(std::get<Rope>(other.value)));
                    case BOOL:
                        return JS::Any(std::get<bool>(this->value) - std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(static_cast<double>(std::get<bool>(this->value)));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case NULL_TYPE:
                switch (other.value.index()) {
                    case NUMBER: {
                        double num = std::get<double>(other.value);
                        return JS::Any(num == 0 ? 0 : -num);
                    }
                    case STRING: {
                        double num = JS::CONVERT::ToNumber(std::get<Rope>(other.value));
                        return JS::Any(num == 0 ? 0 : -num);
                    }
                    case BOOL: {
                        double num = static_cast<double>(std::get<bool>(other.value));
                        return JS::Any(num == 0 ? 0 : -num);
                    }
                    case NULL_TYPE:
                        return JS::Any(0);
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator-(int value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) - value);
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) - value);
            case BOOL:
                return JS::Any(static_cast<double>(std::get<bool>(this->value)) - value);
            case NULL_TYPE: {
                return JS::Any(value == 0 ? 0 : -value);
            }
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator-(double value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) - value);
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) - value);
            case BOOL:
                return JS::Any(static_cast<double>(std::get<bool>(this->value)) - value);
            case NULL_TYPE: {
                return JS::Any(value == 0 ? 0 : -value);
            }
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator-(const char* value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) - JS::CONVERT::ToNumber(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) - JS::CONVERT::ToNumber(value));
            case BOOL:
                return JS::Any(static_cast<double>(std::get<bool>(this->value)) - JS::CONVERT::ToNumber(value));
            case NULL_TYPE: {
                double num = JS::CONVERT::ToNumber(value);
                return JS::Any(num == 0 ? 0 : -num);
            }
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator-(bool value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) - static_cast<double>(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) - static_cast<double>(value));
            case BOOL:
                return JS::Any(static_cast<double>(std::get<bool>(this->value)) - static_cast<double>(value));
            case NULL_TYPE: {
                double num = static_cast<double>(value);
                return JS::Any(num == 0 ? 0 : -num);
            }
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator-(JS::Null) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)));
            case BOOL:
                return JS::Any(static_cast<double>(std::get<bool>(this->value)));
            case NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}
JS::Any JS::Any::operator-(JS::Undefined) const { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }

namespace JS {
JS::Any operator-(int value, JS::Any const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(value - std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(value - JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case BOOL:
                return JS::Any(static_cast<double>(value) - std::get<bool>(any.getValue()));
            case NULL_TYPE:
                return JS::Any(value);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any operator-(double value, JS::Any const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(value - std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(value - JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case BOOL:
                return JS::Any(value - static_cast<double>(std::get<bool>(any.getValue())));
            case NULL_TYPE:
                return JS::Any(value);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any operator-(bool value, JS::Any const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(static_cast<double>(value) - std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(static_cast<double>(value) - JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case BOOL:
                return JS::Any(static_cast<double>(value) - static_cast<double>(std::get<bool>(any.getValue())));
            case NULL_TYPE:
                return JS::Any(static_cast<double>(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any operator-(const char* value, JS::Any const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(JS::CONVERT::ToNumber(value) - std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(value) - JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case BOOL:
                return JS::Any(JS::CONVERT::ToNumber(value) - static_cast<double>(std::get<bool>(any.getValue())));
            case NULL_TYPE:
                return JS::Any(JS::CONVERT::ToNumber(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any operator-(JS::Null, JS::Any const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER: {
                double num = std::get<double>(any.getValue());
                return JS::Any(num == 0 ? 0 : -num);
            }
            case STRING: {
                double num = JS::CONVERT::ToNumber(std::get<Rope>(any.getValue()));
                return JS::Any(num == 0 ? 0 : -num);
            }
            case BOOL: {
                double num = static_cast<double>(std::get<bool>(any.getValue()));
                return JS::Any(num == 0 ? 0 : -num);
            }
            case NULL_TYPE:
                return JS::Any(0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any operator-(JS::Undefined, JS::Any const&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
} // namespace JS
