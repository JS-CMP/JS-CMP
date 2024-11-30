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
        } catch (...) {
            return 0;
        }
    }
}

JS::Any JS::Any::operator|(const JS::Any &other) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(static_cast<int>(std::get<double>(this->value)) |
                                       static_cast<int>(std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(static_cast<int>(std::get<double>(this->value)) |
                                       stringToNumber(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(static_cast<int>(std::get<double>(this->value)) |
                                       static_cast<int>(std::get<bool>(other.value)));
                    default:
                        return JS::Any(0);
                }
            case STRING:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(stringToNumber(std::get<Rope>(this->value).toString()) |
                                       static_cast<int>(std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(stringToNumber(std::get<Rope>(this->value).toString()) |
                                       stringToNumber(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(stringToNumber(std::get<Rope>(this->value).toString()) |
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
                                       stringToNumber(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(static_cast<int>(std::get<bool>(this->value)) |
                                       static_cast<int>(std::get<bool>(other.value)));
                    default:
                        return JS::Any(0);
                }
            default:
                return JS::Any(0);
        }
    } catch (const std::invalid_argument &e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}
