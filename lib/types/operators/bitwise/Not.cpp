#include "../../../../includes/types/JsAny.hpp"
#include "../../../../includes/utils/Convert.hpp"

JS::Any JS::Any::operator~() const {
    try {
        switch (this->value.index()) {
            case NUMBER: {
                return JS::Any(~static_cast<int>(std::get<double>(this->value)));
            }
            case STRING: {
                int number = JS::CONVERT::ToInteger(std::get<Rope>(this->value).toString());
                return JS::Any(~number);
            }
            case BOOL: {
                return JS::Any(~static_cast<int>(std::get<bool>(this->value)));
            }
            default:
                return JS::Any(0);
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}
