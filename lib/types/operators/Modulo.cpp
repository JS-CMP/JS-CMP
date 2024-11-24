#include "../../../includes/types/JsAny.hpp"
#include "../../class/Helper.hpp"

JS::Any JS::Any::operator%(const JS::Any& other) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::fmod(std::get<double>(this->value), std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(
                            std::fmod(std::get<double>(this->value), Helper::stod(std::get<Rope>(other.value))));
                    case BOOL:
                        return JS::Any(
                            std::fmod(std::get<double>(this->value), static_cast<double>(std::get<bool>(other.value))));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case STRING:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(
                            std::fmod(Helper::stod(std::get<Rope>(this->value)), std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(std::fmod(Helper::stod(std::get<Rope>(this->value)),
                                                 Helper::stod(std::get<Rope>(other.value))));
                    case BOOL:
                        return JS::Any(std::fmod(Helper::stod(std::get<Rope>(this->value)),
                                                 static_cast<double>(std::get<bool>(other.value))));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case BOOL:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(
                            std::fmod(static_cast<double>(std::get<bool>(this->value)), std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)),
                                                 Helper::stod(std::get<Rope>(other.value))));
                    case BOOL:
                        return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)),
                                                 static_cast<double>(std::get<bool>(other.value))));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            case NULL_TYPE:
                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::fmod(0, std::get<double>(other.value)));
                    case STRING:
                        return JS::Any(std::fmod(0, Helper::stod(std::get<Rope>(other.value))));
                    case BOOL:
                        return JS::Any(std::fmod(0, static_cast<double>(std::get<bool>(other.value))));
                    default:
                        return JS::Any(std::numeric_limits<double>::quiet_NaN());
                }
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator%(int value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), static_cast<double>(value)));
            case STRING:
                return JS::Any(std::fmod(Helper::stod(std::get<Rope>(this->value)), static_cast<double>(value)));
            case BOOL:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), static_cast<double>(value)));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, static_cast<double>(value)));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator%(double value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), value));
            case STRING:
                return JS::Any(std::fmod(Helper::stod(std::get<Rope>(this->value)), value));
            case BOOL:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), value));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, value));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator%(const char* value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), Helper::stod(value)));
            case STRING:
                return JS::Any(std::fmod(Helper::stod(std::get<Rope>(this->value)), Helper::stod(value)));
            case BOOL:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), Helper::stod(value)));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, Helper::stod(value)));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator%(bool value) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), static_cast<double>(value)));
            case STRING:
                return JS::Any(std::fmod(Helper::stod(std::get<Rope>(this->value)), static_cast<double>(value)));
            case BOOL:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), static_cast<double>(value)));
            case NULL_TYPE:
                return JS::Any(std::fmod(0, static_cast<double>(value)));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator%(JS::Null) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), 0));
            case STRING:
                return JS::Any(std::fmod(Helper::stod(std::get<Rope>(this->value)), 0));
            case BOOL:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), 0));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

JS::Any JS::Any::operator%(JS::Undefined) const {
    try {
        switch (this->value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::get<double>(this->value), std::numeric_limits<double>::quiet_NaN()));
            case STRING:
                return JS::Any(
                    std::fmod(Helper::stod(std::get<Rope>(this->value)), std::numeric_limits<double>::quiet_NaN()));
            case BOOL:
                return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)),
                                         std::numeric_limits<double>::quiet_NaN()));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

namespace JS {
Any operator%(int value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(value, std::get<double>(any.value)));
            case STRING:
                return JS::Any(std::fmod(static_cast<double>(value), Helper::stod(std::get<Rope>(any.value))));
            case BOOL:
                return JS::Any(std::fmod(static_cast<double>(value), static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator%(double value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(value, std::get<double>(any.value)));
            case STRING:
                return JS::Any(std::fmod(value, Helper::stod(std::get<Rope>(any.value))));
            case BOOL:
                return JS::Any(std::fmod(value, static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator%(const char* value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(Helper::stod(value), std::get<double>(any.value)));
            case STRING:
                return JS::Any(std::fmod(Helper::stod(value), Helper::stod(std::get<Rope>(any.value))));
            case BOOL:
                return JS::Any(std::fmod(Helper::stod(value), static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator%(bool value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(static_cast<double>(value), std::get<double>(any.value)));
            case STRING:
                return JS::Any(std::fmod(static_cast<double>(value), Helper::stod(std::get<Rope>(any.value))));
            case BOOL:
                return JS::Any(std::fmod(static_cast<double>(value), static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator%(JS::Null value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(0, std::get<double>(any.value)));
            case STRING:
                return JS::Any(std::fmod(0, Helper::stod(std::get<Rope>(any.value))));
            case BOOL:
                return JS::Any(std::fmod(0, static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}

Any operator%(JS::Undefined value, JS::Any const& any) {
    try {
        switch (any.value.index()) {
            case NUMBER:
                return JS::Any(std::fmod(std::numeric_limits<double>::quiet_NaN(), std::get<double>(any.value)));
            case STRING:
                return JS::Any(
                    std::fmod(std::numeric_limits<double>::quiet_NaN(), Helper::stod(std::get<Rope>(any.value))));
            case BOOL:
                return JS::Any(std::fmod(std::numeric_limits<double>::quiet_NaN(),
                                         static_cast<double>(std::get<bool>(any.value))));
            default:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
        }
    } catch (const std::invalid_argument&) { return JS::Any(std::numeric_limits<double>::quiet_NaN()); }
}
} // namespace JS
