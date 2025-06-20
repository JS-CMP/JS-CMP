#include <cmath>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Any::operator%(const JS::Any& other) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::fmod(std::get<double>(this->value), std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(std::fmod(std::get<double>(this->value),
                                                 JS::CONVERT::ToNumber(std::get<Rope>(other.value))));
                    case BOOLEAN:
                        return JS::Any(
                            std::fmod(std::get<double>(this->value), static_cast<double>(std::get<bool>(other.value))));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case STRING:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->value)),
                                                 std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->value)),
                                                 JS::CONVERT::ToNumber(std::get<Rope>(other.value))));
                    case BOOLEAN:
                        return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->value)),
                                                 static_cast<double>(std::get<bool>(other.value))));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case BOOLEAN:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(
                            std::fmod(static_cast<double>(std::get<bool>(this->value)), std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)),
                                                 JS::CONVERT::ToNumber(std::get<Rope>(other.value))));
                    case BOOLEAN:
                        return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)),
                                                 static_cast<double>(std::get<bool>(other.value))));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case NULL_TYPE:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::fmod(0, std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(std::fmod(0, JS::CONVERT::ToNumber(std::get<Rope>(other.value))));
                    case BOOLEAN:
                        return JS::Any(std::fmod(0, static_cast<double>(std::get<bool>(other.value))));
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

JS::Any JS::Any::operator%(int value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), static_cast<double>(value)));
            case STRING:
                return JS::Any(
                    std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->value)), static_cast<double>(value)));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), static_cast<double>(value)));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, static_cast<double>(value)));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator%(double value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), value));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->value)), value));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), value));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator%(const char* value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), JS::CONVERT::ToNumber(value)));
            case STRING:
                return JS::Any(
                    std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->value)), JS::CONVERT::ToNumber(value)));
            case BOOLEAN:
                return JS::Any(
                    std::fmod(static_cast<double>(std::get<bool>(this->value)), JS::CONVERT::ToNumber(value)));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, JS::CONVERT::ToNumber(value)));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator%(const char16_t* value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), JS::CONVERT::ToNumber(value)));
            case STRING:
                return JS::Any(
                    std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->value)), JS::CONVERT::ToNumber(value)));
            case BOOLEAN:
                return JS::Any(
                    std::fmod(static_cast<double>(std::get<bool>(this->value)), JS::CONVERT::ToNumber(value)));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, JS::CONVERT::ToNumber(value)));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator%(const std::u16string& value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), JS::CONVERT::ToNumber(value)));
            case STRING:
                return JS::Any(
                    std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->value)), JS::CONVERT::ToNumber(value)));
            case BOOLEAN:
                return JS::Any(
                    std::fmod(static_cast<double>(std::get<bool>(this->value)), JS::CONVERT::ToNumber(value)));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, JS::CONVERT::ToNumber(value)));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator%(bool value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), static_cast<double>(value)));
            case STRING:
                return JS::Any(
                    std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->value)), static_cast<double>(value)));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), static_cast<double>(value)));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, static_cast<double>(value)));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator%(JS::Null) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), 0));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->value)), 0));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), 0));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator%(JS::Undefined /*unused*/) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), std::numeric_limits<double>::quiet_NaN()));
            case STRING:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(std::get<Rope>(this->value)),
                                         std::numeric_limits<double>::quiet_NaN()));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)),
                                         std::numeric_limits<double>::quiet_NaN()));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

namespace JS {
Any operator%(int value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(value, std::get<double>(any.value)));
            case STRING:
                return JS::Any(std::fmod(static_cast<double>(value), JS::CONVERT::ToNumber(std::get<Rope>(any.value))));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(value), static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(double value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(value, std::get<double>(any.value)));
            case STRING:
                return JS::Any(std::fmod(value, JS::CONVERT::ToNumber(std::get<Rope>(any.value))));
            case BOOLEAN:
                return JS::Any(std::fmod(value, static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(const char* value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), std::get<double>(any.value)));
            case STRING:
                return JS::Any(
                    std::fmod(JS::CONVERT::ToNumber(value), JS::CONVERT::ToNumber(std::get<Rope>(any.value))));
            case BOOLEAN:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(const char16_t* value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), std::get<double>(any.value)));
            case STRING:
                return JS::Any(
                    std::fmod(JS::CONVERT::ToNumber(value), JS::CONVERT::ToNumber(std::get<Rope>(any.value))));
            case BOOLEAN:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(const std::u16string& value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), std::get<double>(any.value)));
            case STRING:
                return JS::Any(
                    std::fmod(JS::CONVERT::ToNumber(value), JS::CONVERT::ToNumber(std::get<Rope>(any.value))));
            case BOOLEAN:
                return JS::Any(std::fmod(JS::CONVERT::ToNumber(value), static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(bool value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(static_cast<double>(value), std::get<double>(any.value)));
            case STRING:
                return JS::Any(std::fmod(static_cast<double>(value), JS::CONVERT::ToNumber(std::get<Rope>(any.value))));
            case BOOLEAN:
                return JS::Any(std::fmod(static_cast<double>(value), static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(JS::Null value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(0, std::get<double>(any.value)));
            case STRING:
                return JS::Any(std::fmod(0, JS::CONVERT::ToNumber(std::get<Rope>(any.value))));
            case BOOLEAN:
                return JS::Any(std::fmod(0, static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(JS::Undefined value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::numeric_limits<double>::quiet_NaN(), std::get<double>(any.value)));
            case STRING:
                return JS::Any(std::fmod(std::numeric_limits<double>::quiet_NaN(),
                                         JS::CONVERT::ToNumber(std::get<Rope>(any.value))));
            case BOOLEAN:
                return JS::Any(std::fmod(std::numeric_limits<double>::quiet_NaN(),
                                         static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}
} // namespace JS
