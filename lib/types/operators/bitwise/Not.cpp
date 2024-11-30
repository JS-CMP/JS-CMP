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

JS::Any JS::Any::operator~() const {
    try {
        switch (this->value.index()) {
            case NUMBER: {
                // Application de ~ sur un NUMBER
                return JS::Any(~static_cast<int>(std::get<double>(this->value)));
            }
            case STRING: {
                // Conversion de la chaîne en nombre, puis application de ~
                int number = stringToNumber(std::get<Rope>(this->value).toString());
                return JS::Any(~number);
            }
            case BOOL: {
                // Conversion du booléen en int (true -> 1, false -> 0), puis application de ~
                return JS::Any(~static_cast<int>(std::get<bool>(this->value)));
            }
            default:
                // Retourne 0 pour les types non supportés
                return JS::Any(0);
        }
    } catch (const std::invalid_argument &e) {
        // En cas d'erreur de conversion, retourne NaN
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}
