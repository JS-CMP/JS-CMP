#include "../../../includes/types/JsAny.hpp"
#include "../../class/Helper.hpp"

JS::Any JS::Any::operator/(const JS::Any& other) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<double>(this->value) / std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<double>(this->value) / Helper::stod(std::get<Rope>(other.value)));
                    case BOOL:
                        return JS::Any(std::get<double>(this->value) / std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(std::get<double>(this->value) == 0 ? std::numeric_limits<double>::quiet_NaN()
                                                                          : std::numeric_limits<double>::infinity());
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Undefined case
                }
            case STRING:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(Helper::stod(std::get<Rope>(this->value).toString()) /
                                       std::get<double>(other.value));
                    case STRING:
                        return JS::Any(Helper::stod(std::get<Rope>(this->value).toString()) /
                                       Helper::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(Helper::stod(std::get<Rope>(this->value).toString()) /
                                       std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(Helper::stod(std::get<Rope>(this->value).toString()) == 0
                                           ? std::numeric_limits<double>::quiet_NaN()
                                           : std::numeric_limits<double>::infinity());
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case BOOL:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<bool>(this->value) / std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<bool>(this->value) /
                                       Helper::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::get<bool>(this->value) / static_cast<double>(std::get<bool>(other.value)));
                    case NULL_TYPE:
                        return JS::Any(std::get<bool>(this->value) ? std::numeric_limits<double>::infinity()
                                                                   : std::numeric_limits<double>::quiet_NaN());
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case NULL_TYPE:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<double>(other.value) == 0 ? std::numeric_limits<double>::quiet_NaN()
                                                                          : 0);
                    case STRING:
                        return JS::Any(Helper::stod(std::get<Rope>(other.value).toString()) == 0
                                           ? std::numeric_limits<double>::quiet_NaN()
                                           : 0);
                    case BOOL:
                        return JS::Any(std::get<bool>(other.value) ? 0 : std::numeric_limits<double>::quiet_NaN());
                    case NULL_TYPE:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }

            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN()); // For undefined cases, return NaN
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Catch invalid conversions
    }
}

JS::Any JS::Any::operator/(int value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / value);
            case STRING:
                return JS::Any(Helper::stod(std::get<Rope>(this->value)) / value);
            case BOOL:
                return value == 0 ? !std::get<bool>(this->value) ? JS::Any(std::numeric_limits<double>::quiet_NaN())
                                                                 : JS::Any(std::numeric_limits<double>::infinity())
                                  : JS::Any(std::get<bool>(this->value) / value);
            case NULL_TYPE:
                return JS::Any(0.0 / static_cast<double>(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator/(double value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / value);
            case STRING:
                return JS::Any(Helper::stod(std::get<Rope>(this->value)) / value);
            case BOOL:
                return value == 0 ? !std::get<bool>(this->value) ? JS::Any(std::numeric_limits<double>::quiet_NaN())
                                                                 : JS::Any(std::numeric_limits<double>::infinity())
                                  : JS::Any(std::get<bool>(this->value) / value);
            case NULL_TYPE:
                return JS::Any(0.0 / value);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator/(const char* value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / Helper::stod(value));
            case STRING:
                return JS::Any(Helper::stod(std::get<Rope>(this->value)) / Helper::stod(value));
            case BOOL:
                return JS::Any(std::get<bool>(this->value) / Helper::stod(value));
            case NULL_TYPE:
                return JS::Any(0.0 / Helper::stod(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator/(bool value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / static_cast<double>(value));
            case STRING:
                return JS::Any(Helper::stod(std::get<Rope>(this->value)) / static_cast<double>(value));
            case BOOL:
                return JS::Any(std::get<bool>(this->value) / static_cast<double>(value));
            case NULL_TYPE:
                return JS::Any(0.0 / static_cast<double>(value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator/(JS::Null) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::get<double>(this->value) / 0.0);
            case STRING:
                return JS::Any(Helper::stod(std::get<Rope>(this->value)) / 0.0);
            case BOOL:
                return JS::Any(std::get<bool>(this->value) / 0.0);
            case NULL_TYPE:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator/(JS::Undefined) const { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }

namespace JS {
Any operator/(int value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(value / std::get<double>(any.value));
            case STRING:
                return JS::Any(value / Helper::stod(std::get<Rope>(any.value)));
            case BOOL:
                return JS::Any(value / static_cast<double>(std::get<bool>(any.value)));
            case NULL_TYPE:
                return JS::Any(value / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator/(double value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(value / std::get<double>(any.value));
            case STRING:
                return JS::Any(value / Helper::stod(std::get<Rope>(any.value)));
            case BOOL:
                return JS::Any(value / std::get<bool>(any.value));
            case NULL_TYPE:
                return JS::Any(value / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator/(const char* value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(Helper::stod(value) / std::get<double>(any.value));
            case STRING:
                return JS::Any(Helper::stod(value) / Helper::stod(std::get<Rope>(any.value)));
            case BOOL:
                return JS::Any(Helper::stod(value) / std::get<bool>(any.value));
            case NULL_TYPE:
                return JS::Any(Helper::stod(value) / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator/(bool value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(static_cast<double>(value) / std::get<double>(any.value));
            case STRING:
                return JS::Any(static_cast<double>(value) / Helper::stod(std::get<Rope>(any.value)));
            case BOOL:
                return JS::Any(value / static_cast<double>(std::get<bool>(any.value)));
            case NULL_TYPE:
                return JS::Any(value / 0.0);
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator/(JS::Null, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(0 / std::get<double>(any.value));
            case STRING:
                return JS::Any(0 / Helper::stod(std::get<Rope>(any.value)));
            case BOOL:
                return JS::Any(0 / static_cast<double>(std::get<bool>(any.value)));
            case NULL_TYPE:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument& e) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator/(JS::Undefined, JS::Any const&) {
    return JS::Any(std::numeric_limits<double>::quiet_NaN());
}
} // namespace JS