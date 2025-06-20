#include "internals/PropertyProxy.hpp"
#include "types/JsAny.hpp"
#include "utils/Convert.hpp"

#include <iostream>

namespace JS::GLOBAL {

JS::Any parseInt(const JS::Any& thisArgs, const JS::Any& args) {
    std::u16string inputString = JS::CONVERT::ToString(args[u"0"]);
    int radix = JS::CONVERT::ToInteger(args[u"1"]);

    try {
        size_t start = inputString.find_first_not_of(u" \t\n\r");
        if (start == std::u16string::npos) {
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
        std::u16string S = inputString.substr(start);

        int sign = 1;
        if (!S.empty() && (S[0] == '-' || S[0] == '+')) {
            sign = (S[0] == '-') ? -1 : 1;
            S = S.substr(1);
        }

        bool stripPrefix = true;
        if (radix != 0) {
            if (radix < 2 || radix > 36) {
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
            }
            if (radix != 16) {
                stripPrefix = false;
            }
        } else {
            radix = 10;
        }

        if (stripPrefix && S.size() >= 2 && S[0] == '0' && (S[1] == 'x' || S[1] == 'X')) {
            radix = 16;
            S = S.substr(2);
        }

        std::u16string Z;
        for (char c : S) {
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
        for (char c : Z) {
            int digit = (std::isdigit(c)) ? c - '0' : std::tolower(c) - 'a' + 10;
            mathInt = mathInt * radix + digit;
        }

        return JS::Any(sign * mathInt);
    } catch (const std::exception&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}
} // namespace JS::GLOBAL