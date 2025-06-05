#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Any::operator/(const JS::Any& other) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<double>(this->value) / std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<double>(this->value) /
                                       JS::CONVERT::ToNumber(std::get<Rope>(other.value)));
                    case BOOLEAN:
                        return JS::Any(std::get<double>(this->value) / std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(std::get<double>(this->value) == 0 ? std::numeric_limits<double>::quiet_NaN()
                                                                          : std::numeric_limits<double>::infinity());
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case STRING:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value).toString()) /
                                       std::get<double>(other.value));
                    case STRING:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value).toString()) /
                                       JS::CONVERT::ToNumber(std::get<Rope>(other.value).toString()));
                    case BOOLEAN:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value).toString()) /
                                       std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value).toString()) == 0
                                           ? std::numeric_limits<double>::quiet_NaN()
                                           : std::numeric_limits<double>::infinity());
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case BOOLEAN:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<bool>(this->value) / std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<bool>(this->value) /
                                       JS::CONVERT::ToNumber(std::get<Rope>(other.value).toString()));
                    case BOOLEAN:
                        return JS::Any(std::get<bool>(this->value) / static_cast<double>(std::get<bool>(other.value)));
                    case NULL_TYPE:
                        return JS::Any(std::get<bool>(this->value) ? std::numeric_limits<double>::infinity()
                                                                   : std::numeric_limits<double>::quiet_NaN());
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case NULL_TYPE:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<double>(other.value) == 0 ? std::numeric_limits<double>::quiet_NaN()
                                                                          : 0);
                    case STRING:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(other.value).toString()) == 0
                                           ? std::numeric_limits<double>::quiet_NaN()
                                           : 0);
                    case BOOLEAN:
                        return JS::Any(std::get<bool>(other.value) ? 0 : std::numeric_limits<double>::quiet_NaN());
                    case NULL_TYPE:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }

            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator/(int value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / value);
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) / value);
            case BOOLEAN:
                return value == 0 ? !std::get<bool>(this->value) ? JS::Any(std::numeric_limits<double>::quiet_NaN())
                                                                 : JS::Any(std::numeric_limits<double>::infinity())
                                  : JS::Any(std::get<bool>(this->value) / value);
            case NULL_TYPE:
                return JS::Any(0.0 / static_cast<double>(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator/(double value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / value);
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) / value);
            case BOOLEAN:
                return value == 0 ? !std::get<bool>(this->value) ? JS::Any(std::numeric_limits<double>::quiet_NaN())
                                                                 : JS::Any(std::numeric_limits<double>::infinity())
                                  : JS::Any(std::get<bool>(this->value) / value);
            case NULL_TYPE:
                return JS::Any(0.0 / value);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator/(const char* value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / JS::CONVERT::ToNumber(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) / JS::CONVERT::ToNumber(value));
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->value) / JS::CONVERT::ToNumber(value));
            case NULL_TYPE:
                return JS::Any(0.0 / JS::CONVERT::ToNumber(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator/(const char16_t* value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / JS::CONVERT::ToNumber(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) / JS::CONVERT::ToNumber(value));
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->value) / JS::CONVERT::ToNumber(value));
            case NULL_TYPE:
                return JS::Any(0.0 / JS::CONVERT::ToNumber(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator/(const std::u16string& value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / JS::CONVERT::ToNumber(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) / JS::CONVERT::ToNumber(value));
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->value) / JS::CONVERT::ToNumber(value));
            case NULL_TYPE:
                return JS::Any(0.0 / JS::CONVERT::ToNumber(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator/(bool value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / static_cast<double>(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) / static_cast<double>(value));
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->value) / static_cast<double>(value));
            case NULL_TYPE:
                return JS::Any(0.0 / static_cast<double>(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator/(JS::Null) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / 0.0);
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->value)) / 0.0);
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->value) / 0.0);
            case NULL_TYPE:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator/(JS::Undefined /*unused*/) const {
    return JS::Any(std::numeric_limits<double>::quiet_NaN());
}

namespace JS {
Any operator/(int value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(value / std::get<double>(any.value));
            case STRING:
                return JS::Any(value / JS::CONVERT::ToNumber(std::get<Rope>(any.value)));
            case BOOLEAN:
                return JS::Any(value / static_cast<double>(std::get<bool>(any.value)));
            case NULL_TYPE:
                return JS::Any(value / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(double value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(value / std::get<double>(any.value));
            case STRING:
                return JS::Any(value / JS::CONVERT::ToNumber(std::get<Rope>(any.value)));
            case BOOLEAN:
                return JS::Any(value / static_cast<double>(std::get<bool>(any.value)));
            case NULL_TYPE:
                return JS::Any(value / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(const char* value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(JS::CONVERT::ToNumber(value) / std::get<double>(any.value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(value) / JS::CONVERT::ToNumber(std::get<Rope>(any.value)));
            case BOOLEAN:
                return JS::Any(JS::CONVERT::ToNumber(value) / static_cast<double>(std::get<bool>(any.value)));
            case NULL_TYPE:
                return JS::Any(JS::CONVERT::ToNumber(value) / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(const char16_t* value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(JS::CONVERT::ToNumber(value) / std::get<double>(any.value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(value) / JS::CONVERT::ToNumber(std::get<Rope>(any.value)));
            case BOOLEAN:
                return JS::Any(JS::CONVERT::ToNumber(value) / static_cast<double>(std::get<bool>(any.value)));
            case NULL_TYPE:
                return JS::Any(JS::CONVERT::ToNumber(value) / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(const std::u16string& value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(JS::CONVERT::ToNumber(value) / std::get<double>(any.value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(value) / JS::CONVERT::ToNumber(std::get<Rope>(any.value)));
            case BOOLEAN:
                return JS::Any(JS::CONVERT::ToNumber(value) / static_cast<double>(std::get<bool>(any.value)));
            case NULL_TYPE:
                return JS::Any(JS::CONVERT::ToNumber(value) / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(bool value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(static_cast<double>(value) / std::get<double>(any.value));
            case STRING:
                return JS::Any(static_cast<double>(value) / JS::CONVERT::ToNumber(std::get<Rope>(any.value)));
            case BOOLEAN:
                return JS::Any(value / static_cast<double>(std::get<bool>(any.value)));
            case NULL_TYPE:
                return JS::Any(value / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(JS::Null, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(0 / std::get<double>(any.value));
            case STRING:
                return JS::Any(0 / JS::CONVERT::ToNumber(std::get<Rope>(any.value)));
            case BOOLEAN:
                return JS::Any(0 / static_cast<double>(std::get<bool>(any.value)));
            case NULL_TYPE:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(JS::Undefined /*unused*/, JS::Any const& /*unused*/) {
    return JS::Any(std::numeric_limits<double>::quiet_NaN());
}
} // namespace JS