#include "../../includes/global/global_parseFloat.hpp"

JS::Any global_parseFloat(JS::Any inputStringAny) {
    std::string inputString = JS::CONVERT::ToString(inputStringAny);
    try {
        size_t start = inputString.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
        std::string trimmedString = inputString.substr(start);

        if (trimmedString == "NaN") {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
        if (trimmedString == "Infinity") {
            return JS::Any(std::numeric_limits<double>::infinity());
        }
        if (trimmedString == "-Infinity") {
            return JS::Any(-std::numeric_limits<double>::infinity());
        }

        int sign = 1;
        if (!trimmedString.empty() && (trimmedString[0] == '-' || trimmedString[0] == '+')) {
            sign = (trimmedString[0] == '-') ? -1 : 1;
            trimmedString = trimmedString.substr(1);
        }

        std::string numberString;
        bool hasDecimalPoint = false;
        bool hasExponent = false;

        for (size_t i = 0; i < trimmedString.size(); ++i) {
            char c = trimmedString[i];
            if (std::isdigit(c)) {
                numberString += c;
            } else if (c == '.' && !hasDecimalPoint && !hasExponent) {
                numberString += c;
                hasDecimalPoint = true;
            } else if ((c == 'e' || c == 'E') && !hasExponent) {
                numberString += c;
                hasExponent = true;

                if (i + 1 < trimmedString.size() && (trimmedString[i + 1] == '+' || trimmedString[i + 1] == '-')) {
                    numberString += trimmedString[++i];
                }
            } else {
                break;
            }
        }

        if (std::count(numberString.begin(), numberString.end(), '.') > 1 ||
            (hasExponent && (numberString.back() == 'e' || numberString.back() == 'E'))) {
            numberString.pop_back();
        }

        if (numberString.empty() || numberString == ".") {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }

        try {
            double result = std::stod(numberString) * sign;

            if (result == std::numeric_limits<double>::infinity()) {
                return JS::Any(std::numeric_limits<double>::infinity());
            }
            if (result == -std::numeric_limits<double>::infinity()) {
                return JS::Any(-std::numeric_limits<double>::infinity());
            }

            return JS::Any(result);
        } catch (const std::out_of_range&) {
            return JS::Any((sign > 0) ? std::numeric_limits<double>::infinity()
                                      : -std::numeric_limits<double>::infinity());
        } catch (const std::exception&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
    } catch (const std::exception&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}
