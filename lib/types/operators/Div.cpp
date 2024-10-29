#include "../../../includes/types/JsAny.hpp"

JS::Any JS::Any::operator/(const JS::Any& other) const {
    try {
        switch (this->value.index()) {
            case NUMBER:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<double>(this->value) / std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<double>(this->value) / std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::get<double>(this->value) / std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(std::numeric_limits<double>::infinity());
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Undefined
                                                                                  // case
                }
            case STRING:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::stod(std::get<Rope>(this->value).toString()) /
                                       std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::stod(std::get<Rope>(this->value).toString()) /
                                       std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::stod(std::get<Rope>(this->value).toString()) / std::get<bool>(other.value));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case BOOL:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<bool>(this->value) / std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<bool>(this->value) / std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::get<bool>(this->value) / std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(std::numeric_limits<double>::infinity());
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case NULL_TYPE:
                return JS::Any(0); // Division by null always returns 0

            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // For undefined cases, return NaN
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Catch invalid
                                                                  // conversions
    }
}