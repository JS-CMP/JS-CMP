#include "../../../../includes/types/JsAny.hpp"
#include "../../../../includes/utils/Convert.hpp"

JS::Any JS::Any::operator!() const {
    try {
        switch (this->value.index()) {
            case NUMBER: {
                return JS::Any(!JS::CONVERT::ToBoolean((std::get<double>(this->value))));
            }
            case STRING: {
                return JS::Any(!JS::CONVERT::ToBoolean(std::get<Rope>(this->value).toString()));
            }
            case BOOL: {
                return JS::Any(!std::get<bool>(this->value));
            }
            default:
                return JS::Any(true);
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}