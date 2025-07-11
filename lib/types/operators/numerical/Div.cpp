#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

JS::Any JS::Operator::operator/(const JS::Operator& other) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                switch (other.getValue().index()) {
                    case NUMBER:
                        return JS::Any(std::get<double>(this->getValue()) / std::get<double>(other.getValue()));
                    case STRING:
                        return JS::Any(std::get<double>(this->getValue()) /
                                       JS::CONVERT::ToNumber(std::get<Rope>(other.getValue())));
                    case BOOLEAN:
                        return JS::Any(std::get<double>(this->getValue()) / std::get<bool>(other.getValue()));
                    case NULL_TYPE:
                        return JS::Any(std::get<double>(this->getValue()) == 0 ? std::numeric_limits<double>::quiet_NaN()
                                                                          : std::numeric_limits<double>::infinity());
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case STRING:

                switch (other.getValue().index()) {
                    case NUMBER:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue()).toString()) /
                                       std::get<double>(other.getValue()));
                    case STRING:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue()).toString()) /
                                       JS::CONVERT::ToNumber(std::get<Rope>(other.getValue()).toString()));
                    case BOOLEAN:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue()).toString()) /
                                       std::get<bool>(other.getValue()));
                    case NULL_TYPE:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue()).toString()) == 0
                                           ? std::numeric_limits<double>::quiet_NaN()
                                           : std::numeric_limits<double>::infinity());
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case BOOLEAN:

                switch (other.getValue().index()) {
                    case NUMBER:
                        return JS::Any(std::get<bool>(this->getValue()) / std::get<double>(other.getValue()));
                    case STRING:
                        return JS::Any(std::get<bool>(this->getValue()) /
                                       JS::CONVERT::ToNumber(std::get<Rope>(other.getValue()).toString()));
                    case BOOLEAN:
                        return JS::Any(std::get<bool>(this->getValue()) / static_cast<double>(std::get<bool>(other.getValue())));
                    case NULL_TYPE:
                        return JS::Any(std::get<bool>(this->getValue()) ? std::numeric_limits<double>::infinity()
                                                                   : std::numeric_limits<double>::quiet_NaN());
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case NULL_TYPE:
                switch (other.getValue().index()) {
                    case NUMBER:
                        return JS::Any(std::get<double>(other.getValue()) == 0 ? std::numeric_limits<double>::quiet_NaN()
                                                                          : 0);
                    case STRING:
                        return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(other.getValue()).toString()) == 0
                                           ? std::numeric_limits<double>::quiet_NaN()
                                           : 0);
                    case BOOLEAN:
                        return JS::Any(std::get<bool>(other.getValue()) ? 0 : std::numeric_limits<double>::quiet_NaN());
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

JS::Any JS::Operator::operator/(int value) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->getValue()) / value);
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())) / value);
            case BOOLEAN:
                return value == 0 ? !std::get<bool>(this->getValue()) ? JS::Any(std::numeric_limits<double>::quiet_NaN())
                                                                 : JS::Any(std::numeric_limits<double>::infinity())
                                  : JS::Any(std::get<bool>(this->getValue()) / value);
            case NULL_TYPE:
                return JS::Any(0.0 / static_cast<double>(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator/(double value) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->getValue()) / value);
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())) / value);
            case BOOLEAN:
                return value == 0 ? !std::get<bool>(this->getValue()) ? JS::Any(std::numeric_limits<double>::quiet_NaN())
                                                                 : JS::Any(std::numeric_limits<double>::infinity())
                                  : JS::Any(std::get<bool>(this->getValue()) / value);
            case NULL_TYPE:
                return JS::Any(0.0 / value);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator/(const char* value) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->getValue()) / JS::CONVERT::ToNumber(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())) / JS::CONVERT::ToNumber(value));
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->getValue()) / JS::CONVERT::ToNumber(value));
            case NULL_TYPE:
                return JS::Any(0.0 / JS::CONVERT::ToNumber(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator/(const char16_t* value) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->getValue()) / JS::CONVERT::ToNumber(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())) / JS::CONVERT::ToNumber(value));
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->getValue()) / JS::CONVERT::ToNumber(value));
            case NULL_TYPE:
                return JS::Any(0.0 / JS::CONVERT::ToNumber(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator/(const std::u16string& value) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->getValue()) / JS::CONVERT::ToNumber(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())) / JS::CONVERT::ToNumber(value));
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->getValue()) / JS::CONVERT::ToNumber(value));
            case NULL_TYPE:
                return JS::Any(0.0 / JS::CONVERT::ToNumber(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator/(bool value) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->getValue()) / static_cast<double>(value));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())) / static_cast<double>(value));
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->getValue()) / static_cast<double>(value));
            case NULL_TYPE:
                return JS::Any(0.0 / static_cast<double>(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator/(JS::Null) const {
    try {
        switch (this->getValue().index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->getValue()) / 0.0);
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(std::get<Rope>(this->getValue())) / 0.0);
            case BOOLEAN:
                return JS::Any(std::get<bool>(this->getValue()) / 0.0);
            case NULL_TYPE:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Operator::operator/(JS::Undefined /*unused*/) const {
    return JS::Any(std::numeric_limits<double>::quiet_NaN());
}

namespace JS {
Any operator/(int value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(value / std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(value / JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case BOOLEAN:
                return JS::Any(value / static_cast<double>(std::get<bool>(any.getValue())));
            case NULL_TYPE:
                return JS::Any(value / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(double value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(value / std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(value / JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case BOOLEAN:
                return JS::Any(value / static_cast<double>(std::get<bool>(any.getValue())));
            case NULL_TYPE:
                return JS::Any(value / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(const char* value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(JS::CONVERT::ToNumber(value) / std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(value) / JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case BOOLEAN:
                return JS::Any(JS::CONVERT::ToNumber(value) / static_cast<double>(std::get<bool>(any.getValue())));
            case NULL_TYPE:
                return JS::Any(JS::CONVERT::ToNumber(value) / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(const char16_t* value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(JS::CONVERT::ToNumber(value) / std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(value) / JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case BOOLEAN:
                return JS::Any(JS::CONVERT::ToNumber(value) / static_cast<double>(std::get<bool>(any.getValue())));
            case NULL_TYPE:
                return JS::Any(JS::CONVERT::ToNumber(value) / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(const std::u16string& value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(JS::CONVERT::ToNumber(value) / std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(JS::CONVERT::ToNumber(value) / JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case BOOLEAN:
                return JS::Any(JS::CONVERT::ToNumber(value) / static_cast<double>(std::get<bool>(any.getValue())));
            case NULL_TYPE:
                return JS::Any(JS::CONVERT::ToNumber(value) / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(bool value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(static_cast<double>(value) / std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(static_cast<double>(value) / JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case BOOLEAN:
                return JS::Any(value / static_cast<double>(std::get<bool>(any.getValue())));
            case NULL_TYPE:
                return JS::Any(value / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator/(JS::Null, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case NUMBER:
                return JS::Any(0 / std::get<double>(any.getValue()));
            case STRING:
                return JS::Any(0 / JS::CONVERT::ToNumber(std::get<Rope>(any.getValue())));
            case BOOLEAN:
                return JS::Any(0 / static_cast<double>(std::get<bool>(any.getValue())));
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