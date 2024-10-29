#include "../../../includes/types/JsAny.hpp"

JS::Any JS::Any::operator+(const JS::Any &other) const
{
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
                case STRING:{
                    return JS::Any(std::get<Rope>(this->value) + std::get<Rope>(other.value));
                }
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
    return JS::Any();
}