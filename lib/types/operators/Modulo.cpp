#include "../../../includes/types/JsAny.hpp"

JS::Any JS::Any::operator%(const JS::Any& other) const {
    switch (this->value.index()) {
        case NUMBER:
            switch (other.value.index()) {
                case NUMBER:
                    return JS::Any(std::fmod(std::get<double>(this->value), std::get<double>(other.value)));
                case STRING:
                    return JS::Any(
                        std::fmod(std::get<double>(this->value), std::stod(std::get<Rope>(other.value).toString())));
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
                        std::fmod(std::stod(std::get<Rope>(this->value).toString()), std::get<double>(other.value)));
                case STRING:
                    return JS::Any(std::fmod(std::stod(std::get<Rope>(this->value).toString()),
                                             std::stod(std::get<Rope>(other.value).toString())));
                case BOOL:
                    return JS::Any(std::fmod(std::stod(std::get<Rope>(this->value).toString()),
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
                                             std::stod(std::get<Rope>(other.value).toString())));
                case BOOL:
                    return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)),
                                             static_cast<double>(std::get<bool>(other.value))));
                default:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
            }
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator%(int value) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::fmod(std::get<double>(this->value), static_cast<double>(value)));
        case STRING:
            return JS::Any(std::fmod(std::stod(std::get<Rope>(this->value).toString()), static_cast<double>(value)));
        case BOOL:
            return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), static_cast<double>(value)));
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator%(double value) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::fmod(std::get<double>(this->value), value));
        case STRING:
            return JS::Any(std::fmod(std::stod(std::get<Rope>(this->value).toString()), value));
        case BOOL:
            return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), value));
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator%(std::string value) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::fmod(std::get<double>(this->value), std::stod(value)));
        case STRING:
            return JS::Any(std::fmod(std::stod(std::get<Rope>(this->value).toString()), std::stod(value)));
        case BOOL:
            return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), std::stod(value)));
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator%(bool value) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::fmod(std::get<double>(this->value), static_cast<double>(value)));
        case STRING:
            return JS::Any(std::fmod(std::stod(std::get<Rope>(this->value).toString()), static_cast<double>(value)));
        case BOOL:
            return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), static_cast<double>(value)));
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator%(JS::Null) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::fmod(std::get<double>(this->value), 0));
        case STRING:
            return JS::Any(std::fmod(std::stod(std::get<Rope>(this->value).toString()), 0));
        case BOOL:
            return JS::Any(std::fmod(static_cast<double>(std::get<bool>(this->value)), 0));
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

JS::Any JS::Any::operator%(JS::Undefined) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::fmod(std::get<double>(this->value), std::numeric_limits<double>::quiet_NaN()));
        case STRING:
            return JS::Any(
                std::fmod(std::stod(std::get<Rope>(this->value).toString()), std::numeric_limits<double>::quiet_NaN()));
        case BOOL:
            return JS::Any(
                std::fmod(static_cast<double>(std::get<bool>(this->value)), std::numeric_limits<double>::quiet_NaN()));
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

namespace JS {
Any operator%(int value, JS::Any const& any) {
    switch (any.value.index()) {
        case NUMBER:
            return JS::Any(std::fmod(value, std::get<double>(any.value)));
        case STRING:
            return JS::Any(std::fmod(static_cast<double>(value), std::stod(std::get<Rope>(any.value).toString())));
        case BOOL:
            return JS::Any(std::fmod(static_cast<double>(value), static_cast<double>(std::get<bool>(any.value))));
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(double value, JS::Any const& any) {
    switch (any.value.index()) {
        case NUMBER:
            return JS::Any(std::fmod(value, std::get<double>(any.value)));
        case STRING:
            return JS::Any(std::fmod(value, std::stod(std::get<Rope>(any.value).toString())));
        case BOOL:
            return JS::Any(std::fmod(value, static_cast<double>(std::get<bool>(any.value))));
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(std::string value, JS::Any const& any) {
    switch (any.value.index()) {
        case NUMBER:
            return JS::Any(std::fmod(std::stod(value), std::get<double>(any.value)));
        case STRING:
            return JS::Any(std::fmod(std::stod(value), std::stod(std::get<Rope>(any.value).toString())));
        case BOOL:
            return JS::Any(std::fmod(std::stod(value), static_cast<double>(std::get<bool>(any.value))));
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(bool value, JS::Any const& any) {
    switch (any.value.index()) {
        case NUMBER:
            return JS::Any(std::fmod(static_cast<double>(value), std::get<double>(any.value)));
        case STRING:
            return JS::Any(std::fmod(static_cast<double>(value), std::stod(std::get<Rope>(any.value).toString())));
        case BOOL:
            return JS::Any(std::fmod(static_cast<double>(value), static_cast<double>(std::get<bool>(any.value))));
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(JS::Null value, JS::Any const& any) {
    switch (any.value.index()) {
        case NUMBER:
            return JS::Any(std::fmod(0, std::get<double>(any.value)));
        case STRING:
            return JS::Any(std::fmod(0, std::stod(std::get<Rope>(any.value).toString())));
        case BOOL:
            return JS::Any(std::fmod(0, static_cast<double>(std::get<bool>(any.value))));
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}

Any operator%(JS::Undefined value, JS::Any const& any) {
    switch (any.value.index()) {
        case NUMBER:
            return JS::Any(std::fmod(std::numeric_limits<double>::quiet_NaN(), std::get<double>(any.value)));
        case STRING:
            return JS::Any(
                std::fmod(std::numeric_limits<double>::quiet_NaN(), std::stod(std::get<Rope>(any.value).toString())));
        case BOOL:
            return JS::Any(
                std::fmod(std::numeric_limits<double>::quiet_NaN(), static_cast<double>(std::get<bool>(any.value))));
        default:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
}
} // namespace JS