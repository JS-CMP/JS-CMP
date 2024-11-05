#include "../../../includes/types/JsAny.hpp"

JS::Any JS::Any::operator+(const JS::Any& other) const {
    switch (this->value.index()) {
        case NUMBER:
            switch (other.value.index()) {
                case NUMBER:
                    return JS::Any(std::get<double>(this->value) + std::get<double>(other.value));
                case STRING:
                    return JS::Any(this->toString() + std::get<Rope>(other.value));
                case BOOL:
                    return JS::Any(std::get<double>(this->value) + std::get<bool>(other.value));
                case FUNCTION:
                    return JS::Any(this->toString() + other.toString());
                case UNDEFINED:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
                case NULL_TYPE:
                    return JS::Any(std::get<double>(this->value));
            }
            break;
        case STRING:
            switch (other.value.index()) {
                case NUMBER:
                    return JS::Any(std::get<Rope>(this->value) + other.toString());
                case STRING:
                    return JS::Any(std::get<Rope>(this->value) + std::get<Rope>(other.value));
                default:
                    return JS::Any(std::get<Rope>(this->value) + other.toString());
            }
            break;
        case BOOL:
            switch (other.value.index()) {
                case NUMBER:
                    return JS::Any(std::get<bool>(this->value) + std::get<double>(other.value));
                case STRING:
                    return JS::Any(this->toString() + std::get<Rope>(other.value));
                case BOOL:
                    return JS::Any(std::get<bool>(this->value) + std::get<bool>(other.value));
                case FUNCTION: // TODO
                // console.log(true + (() => {})) -> "true() =&gt; {}"
                case NULL_TYPE:
                    return JS::Any(static_cast<double>(std::get<bool>(this->value)));
            }
            break;
        case FUNCTION:
            switch (other.value.index()) {
                case NUMBER:
                    return JS::Any(this->toString() + other.toString());
                case STRING:
                    return JS::Any(this->toString() + std::get<Rope>(other.value));
                case BOOL:
                    return JS::Any(this->toString() + other.toString());
                case FUNCTION:
                    return JS::Any(this->toString() + other.toString());
                case UNDEFINED:
                    return JS::Any(this->toString() + other.toString());
                case NULL_TYPE:
                    return JS::Any(this->toString() + other.toString());
            }
            break;
        case NULL_TYPE:
            switch (other.value.index()) {
                case NUMBER:
                    return JS::Any(std::get<double>(other.value));
                case STRING:
                    return JS::Any(this->toString() + std::get<Rope>(other.value));
                case BOOL:
                    return JS::Any(static_cast<double>(std::get<bool>(other.value)));
                case FUNCTION:
                    return JS::Any(this->toString() + other.toString());
                case UNDEFINED:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
                case NULL_TYPE:
                    return JS::Any(0);
            }
            break;
        case UNDEFINED:
            switch (other.value.index()) {
                case NUMBER:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
                case STRING:
                    return JS::Any(this->toString() + std::get<Rope>(other.value));
                case BOOL:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
                case FUNCTION:
                    return JS::Any(this->toString() + other.toString());
                case UNDEFINED:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
                case NULL_TYPE:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
            }
            break;
    }
    return {};
}

JS::Any JS::Any::operator+(int value) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::get<double>(this->value) + value);
        case STRING:
            return JS::Any(std::get<Rope>(this->value) + std::to_string(value));
        case BOOL:
            return JS::Any(std::get<bool>(this->value) + value);
        case FUNCTION:
            return JS::Any(this->toString() + std::to_string(value));
        case UNDEFINED:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case NULL_TYPE:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return {};
}

JS::Any JS::Any::operator+(std::string value) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(this->toString() + value);
        case STRING:
            return JS::Any(std::get<Rope>(this->value) + value);
        case BOOL:
            return JS::Any(this->toString() + value);
        case FUNCTION:
            return JS::Any(this->toString() + value);
        case UNDEFINED:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case NULL_TYPE:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return {};
}

JS::Any JS::Any::operator+(bool value) const {
    switch (this->value.index()) {
        case NUMBER:
            return JS::Any(std::get<double>(this->value) + value);
        case STRING:
            return JS::Any(std::get<Rope>(this->value) + std::to_string(value));
        case BOOL:
            return JS::Any(std::get<bool>(this->value) + value);
        case FUNCTION:
            return JS::Any(this->toString() + std::to_string(value));
        case UNDEFINED:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case NULL_TYPE:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return {};
}

JS::Any operator+(const int value, const JS::Any& any) {
    switch (any.getValue().index()) {
        case JS::NUMBER:
            return JS::Any(value + std::get<double>(any.getValue()));
        case JS::STRING:
            return JS::Any(std::to_string(value) + std::get<Rope>(any.getValue()));
        case JS::BOOL:
            return JS::Any(value + std::get<bool>(any.getValue()));
        case JS::FUNCTION:
            return JS::Any(std::to_string(value) + any.toString());
        case JS::UNDEFINED:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case JS::NULL_TYPE:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return {};
}