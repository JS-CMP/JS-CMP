#include <cmath>
#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Operator::operator%(const JS::Operator& other) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                switch (other.getValue().index()) {
                    case NUMBER:
                        return JS::Any(std::fmod(std::get<double>(this->getValue()), std::get<double>(other.getValue())));
                    case STRING:
                        return JS::Any(std::fmod(std::get<double>(this->getValue()), JS::CONVERT::ToNumber(std::get<Rope>(other.getValue()))));
                    case BOOLEAN:
                        return JS::Any(std::fmod(std::get<double>(this->getValue()), static_cast<double>(std::get<bool>(other.getValue()))));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case STRING:
                switch (other.getValue().index()) {
                    case NUMBER:
                        return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())), std::get<double>(other.getValue())));
                    case STRING:
                        return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())), JS::CONVERT::ToNumber(std::get<Rope>(other.getValue()))));
                    case BOOLEAN:
                        return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())), static_cast<double>(std::get<bool>(other.getValue()))));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case BOOLEAN:
                switch (other.getValue().index()) {
                    case NUMBER:
                        return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->getValue())), std::get<double>(other.getValue())));
                    case STRING:
                        return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->getValue())), JS::CONVERT::ToNumber(std::get<Rope>(other.getValue()))));
                    case BOOLEAN:
                        return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->getValue())), static_cast<double>(std::get<bool>(other.getValue()))));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case NULL_TYPE:
                switch (other.getValue().index()) {
                    case NUMBER:
                        return JS::Any(std::fmod(0, std::get<double>(other.getValue())));
                    case STRING:
                        return JS::Any(std::fmod(0, JS::CONVERT::ToNumber(std::get<Rope>(other.getValue()))));
                    case BOOLEAN:
                        return JS::Any(std::fmod(0, static_cast<double>(std::get<bool>(other.getValue()))));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator%(int value) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->getValue()), static_cast<double>(value)));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())), static_cast<double>(value)));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->getValue())), static_cast<double>(value)));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, static_cast<double>(value)));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator%(double value) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->getValue()), value));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())), value));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->getValue())), value));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator%(const char* value) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->getValue()), JS::CONVERT::ToNumber(value)));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())), JS::CONVERT::ToNumber(value)));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->getValue())), JS::CONVERT::ToNumber(value)));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, JS::CONVERT::ToNumber(value)));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator%(const char16_t* value) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->getValue()), JS::CONVERT::ToNumber(value)));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())), JS::CONVERT::ToNumber(value)));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->getValue())), JS::CONVERT::ToNumber(value)));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, JS::CONVERT::ToNumber(value)));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator%(const std::u16string& value) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->getValue()), JS::CONVERT::ToNumber(value)));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())), JS::CONVERT::ToNumber(value)));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->getValue())), JS::CONVERT::ToNumber(value)));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, JS::CONVERT::ToNumber(value)));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator%(bool value) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->getValue()), static_cast<double>(value)));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())), static_cast<double>(value)));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->getValue())), static_cast<double>(value)));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, static_cast<double>(value)));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator%(JS::Null) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->getValue()), 0));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())), 0));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->getValue())), 0));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator%(JS::Undefined /*unused*/) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->getValue()), std::numeric_limits<double>::quiet_NaN()));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())), std::numeric_limits<double>::quiet_NaN()));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->getValue())), std::numeric_limits<double>::quiet_NaN()));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

namespace JS {
Any operator%(int value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(value, std::get<double>(any.getValue())));
            case STRING:
                return JS::Any(std::fmod(static_cast<double>(value), JS::CONVERT::ToNumber(std::get<Rope>(any.getValue()))));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(value), static_cast<double>(std::get<bool>(any.getValue()))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(double value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(value, std::get<double>(any.getValue())));
            case STRING:
                return JS::Any(std::fmod(value, JS::CONVERT::ToNumber(std::get<Rope>(any.getValue()))));
            case BOOLEAN:
                return JS::Any(std::fmod(value, static_cast<double>(std::get<bool>(any.getValue()))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(const char* value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), std::get<double>(any.getValue())));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), JS::CONVERT::ToNumber(std::get<Rope>(any.getValue()))));
            case BOOLEAN:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), static_cast<double>(std::get<bool>(any.getValue()))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(const char16_t* value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), std::get<double>(any.getValue())));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), JS::CONVERT::ToNumber(std::get<Rope>(any.getValue()))));
            case BOOLEAN:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), static_cast<double>(std::get<bool>(any.getValue()))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(const std::u16string& value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), std::get<double>(any.getValue())));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), JS::CONVERT::ToNumber(std::get<Rope>(any.getValue()))));
            case BOOLEAN:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), static_cast<double>(std::get<bool>(any.getValue()))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(bool value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(static_cast<double>(value), std::get<double>(any.getValue())));
            case STRING:
                return JS::Any(std::fmod(static_cast<double>(value), JS::CONVERT::ToNumber(std::get<Rope>(any.getValue()))));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(value), static_cast<double>(std::get<bool>(any.getValue()))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(JS::Null value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(0, std::get<double>(any.getValue())));
            case STRING:
                return JS::Any(std::fmod(0, JS::CONVERT::ToNumber(std::get<Rope>(any.getValue()))));
            case BOOLEAN:
                return JS::Any(std::fmod(0, static_cast<double>(std::get<bool>(any.getValue()))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(JS::Undefined value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::numeric_limits<double>::quiet_NaN(), std::get<double>(any.getValue())));
            case STRING:
                return JS::Any(std::fmod(std::numeric_limits<double>::quiet_NaN(), JS::CONVERT::ToNumber(std::get<Rope>(any.getValue()))));
            case BOOLEAN:
                return JS::Any(std::fmod(std::numeric_limits<double>::quiet_NaN(), static_cast<double>(std::get<bool>(any.getValue()))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}
} // namespace JS
