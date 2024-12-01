#include "../../../../includes/types/JsAny.hpp"

int stringToNumber(const std::string& str) {
    if (str.empty()) {
        throw std::invalid_argument("La chaîne est vide");
    }

    if (str.size() > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        uint32_t result;
        std::stringstream ss;
        ss << std::hex << str.substr(2);
        ss >> result;
        if (ss.fail()) {
            return 0;
        }
        return static_cast<int>(result & 0xFFFFFFFF);
    }

    else if (str.size() > 2 && str[0] == '0' && (str[1] == 'b' || str[1] == 'B')) {
        uint32_t result = 0;
        for (size_t i = 2; i < str.size(); ++i) {
            if (str[i] != '0' && str[i] != '1') {
                return 0;
            }
            result = (result << 1) | (str[i] - '0');
        }
        return static_cast<int>(result & 0xFFFFFFFF);
    }

    else {
        try {
            long long result = std::stoll(str);
            return static_cast<int>(result & 0xFFFFFFFF);
        } catch (...) { return 0; }
    }
}

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
                                       stringToNumber(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(static_cast<int>(std::get<double>(this->value)) &
                                       static_cast<int>(std::get<bool>(other.value)));
                    default:
                        return JS::Any(0);
                }
            case STRING:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(stringToNumber(std::get<Rope>(this->value).toString()) &
                                       static_cast<int>(std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(stringToNumber(std::get<Rope>(this->value).toString()) &
                                       stringToNumber(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(stringToNumber(std::get<Rope>(this->value).toString()) &
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
                                       stringToNumber(std::get<Rope>(other.value).toString()));
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
                int lhs = stringToNumber(std::get<Rope>(this->value).toString());
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
                int lhs = stringToNumber(std::get<Rope>(this->value).toString());
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
        int rhs = stringToNumber(std::string(value));
        switch (this->value.index()) {
            case NUMBER: {
                int lhs = static_cast<int>(std::get<double>(this->value));
                return JS::Any(lhs & rhs);
            }
            case STRING: {
                int lhs = stringToNumber(std::get<Rope>(this->value).toString());
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
                int lhs = stringToNumber(std::get<Rope>(this->value).toString());
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
                int rhs = stringToNumber(std::get<Rope>(any.value).toString());
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
                int rhs = stringToNumber(std::get<Rope>(any.value).toString());
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
        int lhs = stringToNumber(std::string(value));
        switch (any.value.index()) {
            case NUMBER: {
                int rhs = static_cast<int>(std::get<double>(any.value));
                return JS::Any(lhs & rhs);
            }
            case STRING: {
                int rhs = stringToNumber(std::get<Rope>(any.value).toString());
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
                int rhs = stringToNumber(std::get<Rope>(any.value).toString());
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
