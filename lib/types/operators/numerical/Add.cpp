#include <internals/Operator.hpp>
#include <types/JsAny.hpp>
#include <utils/Convert.hpp>

// TODO when ToPrimitive is implemented refactor this

JS::Any JS::Operator::operator+(const JS::Operator& other) const {
    switch (this->getValue().index()) {
        case NUMBER:
            switch (other.getValue().index()) {
                case NUMBER:
                    return JS::Any(std::get<double>(this->getValue()) + std::get<double>(other.getValue()));
                case STRING:
                    return JS::Any(JS::CONVERT::ToString(*this) + std::get<Rope>(other.getValue()));
                case BOOLEAN:
                    return JS::Any(std::get<double>(this->getValue()) + std::get<bool>(other.getValue()));
                case FUNCTION:
                    return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(other));
                case UNDEFINED:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
                case NULL_TYPE:
                    return JS::Any(std::get<double>(this->getValue()));
            }
            break;
        case STRING:
            switch (other.getValue().index()) {
                case STRING:
                    return JS::Any(std::get<Rope>(this->getValue()) + std::get<Rope>(other.getValue()));
                default:
                    return JS::Any(std::get<Rope>(this->getValue()) + JS::CONVERT::ToRope(other));
            }
            break;
        case BOOLEAN:
            switch (other.getValue().index()) {
                case NUMBER:
                    return JS::Any(std::get<bool>(this->getValue()) + std::get<double>(other.getValue()));
                case STRING:
                    return JS::Any(JS::CONVERT::ToString(*this) + std::get<Rope>(other.getValue()));
                case BOOLEAN:
                    return JS::Any(std::get<bool>(this->getValue()) + std::get<bool>(other.getValue()));
                case FUNCTION: // TODO
                // console.log(true + (() => {})) -> "true() =&gt; {}"
                case UNDEFINED:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
                case NULL_TYPE:
                    return JS::Any(static_cast<double>(std::get<bool>(this->getValue())));
            }
            break;
        case FUNCTION:
            switch (other.getValue().index()) {
                case NUMBER:
                    return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(other));
                case STRING:
                    return JS::Any(JS::CONVERT::ToString(*this) + std::get<Rope>(other.getValue()));
                case BOOLEAN:
                    return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(other));
                case FUNCTION:
                    return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(other));
                case UNDEFINED:
                    return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(other));
                case NULL_TYPE:
                    return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(other));
            }
            break;
        case NULL_TYPE:
            switch (other.getValue().index()) {
                case NUMBER:
                    return JS::Any(std::get<double>(other.getValue()));
                case STRING:
                    return JS::Any(JS::CONVERT::ToString(*this) + std::get<Rope>(other.getValue()));
                case BOOLEAN:
                    return JS::Any(static_cast<double>(std::get<bool>(other.getValue())));
                case FUNCTION:
                    return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(other));
                case UNDEFINED:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
                case NULL_TYPE:
                    return JS::Any(0);
            }
            break;
        case UNDEFINED:
            switch (other.getValue().index()) {
                case NUMBER:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
                case STRING:
                    return JS::Any(JS::CONVERT::ToString(*this) + std::get<Rope>(other.getValue()));
                case BOOLEAN:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
                case FUNCTION:
                    return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(other));
                case UNDEFINED:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
                case NULL_TYPE:
                    return JS::Any(std::numeric_limits<double>::quiet_NaN());
            }
            break;
    }
    return {};
}

JS::Any JS::Operator::operator+(int value) const {
    switch (this->getValue().index()) {
        case NUMBER:
            return JS::Any(std::get<double>(this->getValue()) + value);
        case STRING:
            return JS::Any(std::get<Rope>(this->getValue()) + JS::CONVERT::ToRope(value));
        case BOOLEAN:
            return JS::Any(std::get<bool>(this->getValue()) + value);
        case UNDEFINED:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case NULL_TYPE:
            return JS::Any(value);
    }
    return {};
}

JS::Any JS::Operator::operator+(double value) const {
    switch (this->getValue().index()) {
        case NUMBER:
            return JS::Any(std::get<double>(this->getValue()) + value);
        case STRING:
            return JS::Any(std::get<Rope>(this->getValue()) + JS::CONVERT::ToRope(value));
        case BOOLEAN:
            return JS::Any(std::get<bool>(this->getValue()) + value);
        case FUNCTION:
            return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(value));
        case UNDEFINED:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case NULL_TYPE:
            return JS::Any(value);
    }
    return {};
}

JS::Any JS::Operator::operator+(bool value) const {
    switch (this->getValue().index()) {
        case NUMBER:
            return JS::Any(std::get<double>(this->getValue()) + value);
        case STRING:
            return JS::Any(std::get<Rope>(this->getValue()) + JS::CONVERT::ToRope(value));
        case BOOLEAN:
            return JS::Any(std::get<bool>(this->getValue()) + value);
        case FUNCTION:
            return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(value));
        case UNDEFINED:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case NULL_TYPE:
            return JS::Any(static_cast<double>(value));
    }
    return {};
}

JS::Any JS::Operator::operator+(const char* value) const {
    return this->operator+(JS::CONVERT::ToUtf16(value));
}

JS::Any JS::Operator::operator+(const char16_t* value) const {
    return this->operator+(std::u16string(value));
}

JS::Any JS::Operator::operator+(const std::u16string& value) const {
    switch (this->getValue().index()) {
        case NUMBER:
            return JS::Any(JS::CONVERT::ToString(*this) + value);
        case STRING:
            return JS::Any(std::get<Rope>(this->getValue()) + value);
        case BOOLEAN:
            return JS::Any(JS::CONVERT::ToString(*this) + value);
        case FUNCTION:
            return JS::Any(JS::CONVERT::ToString(*this) + value);
        case UNDEFINED:
            return JS::Any(JS::CONVERT::ToString(*this) + value);
        case NULL_TYPE:
            return JS::Any(JS::CONVERT::ToString(*this) + value);
    }
    return {};
}

JS::Any JS::Operator::operator+(JS::Null) const {
    switch (this->getValue().index()) {
        case NUMBER:
            return JS::Any(std::get<double>(this->getValue()));
        case STRING:
            return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(JS::Null()));
        case BOOLEAN:
            return JS::Any(static_cast<double>(std::get<bool>(this->getValue())));
        case FUNCTION:
            return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(JS::Null()));
        case UNDEFINED:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case NULL_TYPE:
            return JS::Any(0);
    }
    return {};
}

JS::Any JS::Operator::operator+(JS::Undefined /*unused*/) const {
    switch (this->getValue().index()) {
        case NUMBER:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case STRING:
            return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(JS::Undefined()));
        case BOOLEAN:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case FUNCTION:
            return JS::Any(JS::CONVERT::ToString(*this) + JS::CONVERT::ToString(JS::Undefined()));
        case UNDEFINED:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case NULL_TYPE:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return {};
}

namespace JS {
JS::Any operator+(int value, JS::Operator const& any) {
    switch (any.getValue().index()) {
        case JS::NUMBER:
            return JS::Any(value + std::get<double>(any.getValue()));
        case JS::STRING:
            return JS::Any(JS::CONVERT::ToString(value) + std::get<Rope>(any.getValue()));
        case JS::BOOLEAN:
            return JS::Any(value + std::get<bool>(any.getValue()));
        case JS::FUNCTION:
            return JS::Any(JS::CONVERT::ToString(value) + JS::CONVERT::ToString(any));
        case JS::UNDEFINED:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case JS::NULL_TYPE:
            return JS::Any(value);
    }
    return {};
}

JS::Any operator+(double value, JS::Operator const& any) {
    switch (any.getValue().index()) {
        case JS::NUMBER:
            return JS::Any(value + std::get<double>(any.getValue()));
        case JS::STRING:
            return JS::Any(JS::CONVERT::ToString(value) + std::get<Rope>(any.getValue()));
        case JS::BOOLEAN:
            return JS::Any(value + std::get<bool>(any.getValue()));
        case JS::FUNCTION:
            return JS::Any(JS::CONVERT::ToString(value) + JS::CONVERT::ToString(any));
        case JS::UNDEFINED:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case JS::NULL_TYPE:
            return JS::Any(value);
    }
    return {};
}

JS::Any operator+(const char* value, JS::Operator const& any) {
    return JS::CONVERT::ToUtf16(value) + any;
}

JS::Any operator+(const char16_t* value, JS::Operator const& any) {
    return std::u16string(value) + JS::Any(any);
}

JS::Any operator+(const std::u16string& value, JS::Operator const& any) {
    switch (any.getValue().index()) {
        case JS::NUMBER:
            return JS::Any(value + JS::CONVERT::ToString(any));
        case JS::STRING:
            return JS::Any(value + std::get<Rope>(any.getValue()));
        case JS::BOOLEAN:
            return JS::Any(value + JS::CONVERT::ToString(any));
        case JS::FUNCTION:
            return JS::Any(value + JS::CONVERT::ToString(any));
        case JS::UNDEFINED:
            return JS::Any(value + JS::CONVERT::ToString(any));
        case JS::NULL_TYPE:
            return JS::Any(value + JS::CONVERT::ToString(any));
    }
    return {};
}

JS::Any operator+(bool value, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case JS::NUMBER:
                return JS::Any(value + std::get<double>(any.getValue()));
            case JS::STRING:
                return JS::Any(JS::CONVERT::ToString(value) + std::get<Rope>(any.getValue()));
            case JS::BOOLEAN:
                return JS::Any(value + std::get<bool>(any.getValue()));
            case JS::FUNCTION:
                return JS::Any(JS::CONVERT::ToString(value) + JS::CONVERT::ToString(any));
            case JS::UNDEFINED:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
            case JS::NULL_TYPE:
                return JS::Any(static_cast<double>(value));
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return {};
}

JS::Any operator+(JS::Null, JS::Operator const& any) {
    try {
        switch (any.getValue().index()) {
            case JS::NUMBER:
                return JS::Any(std::get<double>(any.getValue()));
            case JS::STRING:
                return JS::Any(JS::CONVERT::ToString(JS::Null()) + std::get<Rope>(any.getValue()));
            case JS::BOOLEAN:
                return JS::Any(static_cast<double>(std::get<bool>(any.getValue())));
            case JS::FUNCTION:
                return JS::Any(JS::CONVERT::ToString(JS::Null()) + JS::CONVERT::ToString(any));
            case JS::UNDEFINED:
                return JS::Any(std::numeric_limits<double>::quiet_NaN());
            case JS::NULL_TYPE:
                return JS::Any(0);
        }
    } catch (const std::invalid_argument&) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return {};
}

JS::Any operator+(JS::Undefined /*unused*/, JS::Operator const& any) {
    switch (any.getValue().index()) {
        case JS::NUMBER:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case JS::STRING:
            return JS::Any(JS::CONVERT::ToString(JS::Undefined()) + std::get<Rope>(any.getValue()));
        case JS::BOOLEAN:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case JS::FUNCTION:
            return JS::Any(JS::CONVERT::ToString(JS::Undefined()) + JS::CONVERT::ToString(any));
        case JS::UNDEFINED:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
        case JS::NULL_TYPE:
            return JS::Any(std::numeric_limits<double>::quiet_NaN());
    }
    return {};
}
} // namespace JS