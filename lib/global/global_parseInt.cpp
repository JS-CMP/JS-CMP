#include "../../includes/global/global_parseInt.hpp"

JS::Any global_parseInt(const std::string& inputString, int radix = 0) {
    try {
        size_t start = inputString.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
        std::string S = inputString.substr(start);

        int sign = 1;
        if (!S.empty() && (S[0] == '-' || S[0] == '+')) {
            sign = (S[0] == '-') ? -1 : 1;
            S = S.substr(1); // Remove the sign
        }

        bool stripPrefix = true;
        if (radix != 0) {
            if (radix < 2 || radix > 36) {
                std::numeric_limits<double>::quiet_NaN();
            }
            if (radix != 16) {
                stripPrefix = false;
            }
        } else {
            radix = 10;
        }

        if (stripPrefix && S.size() >= 2 && (S[0] == '0') && (S[1] == 'x' || S[1] == 'X')) {
            radix = 16;
            S = S.substr(2);
        }

        std::string Z;
        for (char c: S) {
            int digit;
            if (std::isdigit(c)) {
                digit = c - '0';
            } else if (std::isalpha(c)) {
                digit = std::tolower(c) - 'a' + 10;
            } else {
                break;
            }

            if (digit >= radix) {
                break;
            }
            Z += c;
        }

        if (Z.empty()) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }

        int mathInt = 0;
        for (char c: Z) {
            int digit = (std::isdigit(c)) ? c - '0' : std::tolower(c) - 'a' + 10;
            mathInt = mathInt * radix + digit;
        }

        int result = sign * mathInt;
        /*std::cout << result << std::endl;*/
        return JS::Any(result);
    } catch (const std::exception& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}