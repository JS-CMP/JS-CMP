#include "../../../../includes/types/JsAny.hpp"
#include "../../../../includes/utils/Convert.hpp"

JS::Any JS::Any::operator&(const JS::Any& other) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(static_cast<int>(std::get<double>(this->value)) &
                                       static_cast<int>(std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(static_cast<int>(std::get<double>(this->value)) &
                                       JS::CONVERT::ToInteger(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(static_cast<int>(std::get<double>(this->value)) &
                                       static_cast<int>(std::get<bool>(other.value)));
                    default:
                        return JS::Any(0);
                }
            case STRING:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(JS::CONVERT::ToInteger(std::get<Rope>(this->value).toString()) &
                                       static_cast<int>(std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(JS::CONVERT::ToInteger(std::get<Rope>(this->value).toString()) &
                                       JS::CONVERT::ToInteger(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(JS::CONVERT::ToInteger(std::get<Rope>(this->value).toString()) &
                                       static_cast<int>(std::get<bool>(other.value)));
                    default:
                        return JS::Any(0);
                }
            case BOOL:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(static_cast<int>(std::get<bool>(this->value)) &
                                       static_cast<int>(std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(static_cast<int>(std::get<bool>(this->value)) &
                                       JS::CONVERT::ToInteger(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(static_cast<int>(std::get<bool>(this->value)) &
                                       static_cast<int>(std::get<bool>(other.value)));
                    default:
                        return JS::Any(0);
                }
            default:
                return JS::Any(0);
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator&(int value) const {
    try {
        switch (this->value.index()) {
            case NUMBER: {
                int lhs = static_cast<int>(std::get<double>(this->value));
                return JS::Any(lhs & value);
            }
            case STRING: {
                int lhs = JS::CONVERT::ToInteger(std::get<Rope>(this->value).toString());
                return JS::Any(lhs & value);
            }
            case BOOL: {
                int lhs = static_cast<int>(std::get<bool>(this->value));
                return JS::Any(lhs & value);
            }
            default:
                return JS::Any(0);
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator&(double value) const {
    try {
        switch (this->value.index()) {
            case NUMBER: {
                int lhs = static_cast<int>(std::get<double>(this->value));
                return JS::Any(lhs & static_cast<int>(value));
            }
            case STRING: {
                int lhs = JS::CONVERT::ToInteger(std::get<Rope>(this->value).toString());
                return JS::Any(lhs & static_cast<int>(value));
            }
            case BOOL: {
                int lhs = static_cast<int>(std::get<bool>(this->value));
                return JS::Any(lhs & static_cast<int>(value));
            }
            default:
                return JS::Any(0);
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator&(const char* value) const {
    try {
        int rhs = JS::CONVERT::ToInteger(std::string(value));
        switch (this->value.index()) {
            case NUMBER: {
                int lhs = static_cast<int>(std::get<double>(this->value));
                return JS::Any(lhs & rhs);
            }
            case STRING: {
                int lhs = JS::CONVERT::ToInteger(std::get<Rope>(this->value).toString());
                return JS::Any(lhs & rhs);
            }
            case BOOL: {
                int lhs = static_cast<int>(std::get<bool>(this->value));
                return JS::Any(lhs & rhs);
            }
            default:
                return JS::Any(0);
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator&(bool value) const {
    try {
        int rhs = static_cast<int>(value);
        switch (this->value.index()) {
            case NUMBER: {
                int lhs = static_cast<int>(std::get<double>(this->value));
                return JS::Any(lhs & rhs);
            }
            case STRING: {
                int lhs = JS::CONVERT::ToInteger(std::get<Rope>(this->value).toString());
                return JS::Any(lhs & rhs);
            }
            case BOOL: {
                int lhs = static_cast<int>(std::get<bool>(this->value));
                return JS::Any(lhs & rhs);
            }
            default:
                return JS::Any(0);
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator&(JS::Null) const { return *this & 0; }

JS::Any JS::Any::operator&(JS::Undefined) const { return *this & 0; }

namespace JS {
JS::Any operator&(int value, const JS::Any& any) {
    try {
        switch (any.value.index()) {
            case NUMBER: {
                int rhs = static_cast<int>(std::get<double>(any.value));
                return JS::Any(value & rhs);
            }
            case STRING: {
                int rhs = JS::CONVERT::ToInteger(std::get<Rope>(any.value).toString());
                return JS::Any(value & rhs);
            }
            case BOOL: {
                int rhs = static_cast<int>(std::get<bool>(any.value));
                return JS::Any(value & rhs);
            }
            default:
                return JS::Any(0);
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any operator&(double value, const JS::Any& any) {
    try {
        int lhs = static_cast<int>(value);
        switch (any.value.index()) {
            case NUMBER: {
                int rhs = static_cast<int>(std::get<double>(any.value));
                return JS::Any(lhs & rhs);
            }
            case STRING: {
                int rhs = JS::CONVERT::ToInteger(std::get<Rope>(any.value).toString());
                return JS::Any(lhs & rhs);
            }
            case BOOL: {
                int rhs = static_cast<int>(std::get<bool>(any.value));
                return JS::Any(lhs & rhs);
            }
            default:
                return JS::Any(0);
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any operator&(const char* value, const JS::Any& any) {
    try {
        int lhs = JS::CONVERT::ToInteger(std::string(value));
        switch (any.value.index()) {
            case NUMBER: {
                int rhs = static_cast<int>(std::get<double>(any.value));
                return JS::Any(lhs & rhs);
            }
            case STRING: {
                int rhs = JS::CONVERT::ToInteger(std::get<Rope>(any.value).toString());
                return JS::Any(lhs & rhs);
            }
            case BOOL: {
                int rhs = static_cast<int>(std::get<bool>(any.value));
                return JS::Any(lhs & rhs);
            }
            default:
                return JS::Any(0);
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any operator&(bool value, const JS::Any& any) {
    try {
        int lhs = static_cast<int>(value);
        switch (any.value.index()) {
            case NUMBER: {
                int rhs = static_cast<int>(std::get<double>(any.value));
                return JS::Any(lhs & rhs);
            }
            case STRING: {
                int rhs = JS::CONVERT::ToInteger(std::get<Rope>(any.value).toString());
                return JS::Any(lhs & rhs);
            }
            case BOOL: {
                int rhs = static_cast<int>(std::get<bool>(any.value));
                return JS::Any(lhs & rhs);
            }
            default:
                return JS::Any(0);
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any operator&(JS::Null, const JS::Any& any) { return JS::Any(0) & any; }

JS::Any operator&(JS::Undefined, const JS::Any& any) { return JS::Any(0) & any; }

} // namespace JS
