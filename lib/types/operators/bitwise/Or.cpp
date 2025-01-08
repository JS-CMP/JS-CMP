#include "../../../../includes/types/JsAny.hpp"
#include "../../../../includes/utils/Convert.hpp"

JS::Any JS::Any::operator|(const JS::Any& other) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(static_cast<int>(std::get<double>(this->value)) |
                                       static_cast<int>(std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(static_cast<int>(std::get<double>(this->value)) |
                                       JS::CONVERT::ToInteger(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(static_cast<int>(std::get<double>(this->value)) |
                                       static_cast<int>(std::get<bool>(other.value)));
                    default:
                        return JS::Any(0);
                }
            case STRING:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(JS::CONVERT::ToInteger(std::get<Rope>(this->value).toString()) |
                                       static_cast<int>(std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(JS::CONVERT::ToInteger(std::get<Rope>(this->value).toString()) |
                                       JS::CONVERT::ToInteger(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(JS::CONVERT::ToInteger(std::get<Rope>(this->value).toString()) |
                                       static_cast<int>(std::get<bool>(other.value)));
                    default:
                        return JS::Any(0);
                }
            case BOOL:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(static_cast<int>(std::get<bool>(this->value)) |
                                       static_cast<int>(std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(static_cast<int>(std::get<bool>(this->value)) |
                                       JS::CONVERT::ToInteger(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(static_cast<int>(std::get<bool>(this->value)) |
                                       static_cast<int>(std::get<bool>(other.value)));
                    default:
                        return JS::Any(0);
                }
            default:
                return JS::Any(0);
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator|(int value) const {
    try {
        switch (this->value.index()) {
            case NUMBER: {
                int lhs = static_cast<int>(std::get<double>(this->value));
                return JS::Any(lhs | value);
            }
            case STRING: {
                int lhs = JS::CONVERT::ToInteger(std::get<Rope>(this->value).toString());
                return JS::Any(lhs | value);
            }
            case BOOL: {
                int lhs = static_cast<int>(std::get<bool>(this->value));
                return JS::Any(lhs | value);
            }
            default:
                return JS::Any(value); // Si JS::Any est null/undefined, retourne `value`
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator|(double value) const { return *this | static_cast<int>(value); }

JS::Any JS::Any::operator|(const char* value) const {
    int rhs = JS::CONVERT::ToInteger(std::string(value));
    return *this | rhs;
}

JS::Any JS::Any::operator|(bool value) const {
    int rhs = static_cast<int>(value);
    return *this | rhs;
}

JS::Any JS::Any::operator|(JS::Null) const { return *this | 0; }

JS::Any JS::Any::operator|(JS::Undefined) const { return *this | 0; }

namespace JS {
JS::Any operator|(int value, const JS::Any& any) { return any | value; }

JS::Any operator|(double value, const JS::Any& any) { return any | static_cast<int>(value); }

JS::Any operator|(const char* value, const JS::Any& any) {
    int lhs = JS::CONVERT::ToInteger(std::string(value));
    return any | lhs;
}

JS::Any operator|(bool value, const JS::Any& any) { return any | static_cast<int>(value); }

JS::Any operator|(JS::Null, const JS::Any& any) { return any | 0; }

JS::Any operator|(JS::Undefined, const JS::Any& any) { return any | 0; }
} // namespace JS