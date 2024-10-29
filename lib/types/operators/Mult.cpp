#include "../../../includes/types/JsAny.hpp"

JS::Any JS::Any::operator*(const JS::Any& other) const {
    // TODO: change with infinite precision the stol
    try {
        switch (this->value.index()) {
            case NUMBER:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<double>(this->value) * std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<double>(this->value) *
                                       std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::get<double>(this->value) * std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(0.0);
                    default:
                        throw std::runtime_error("Invalid types for multiplication");
                }
            case STRING:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::stod(std::get<Rope>(this->value).toString()) *
                                       std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::stod(std::get<Rope>(this->value).toString()) *
                                       std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::stod(std::get<Rope>(this->value).toString()) * std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(0.0);
                    default:
                        throw std::runtime_error("Invalid types for multiplication");
                }
            case BOOL:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(std::get<bool>(this->value) * std::get<double>(other.value));
                    case STRING:
                        return JS::Any(std::get<bool>(this->value) * std::stod(std::get<Rope>(other.value).toString()));
                    case BOOL:
                        return JS::Any(std::get<bool>(this->value) * std::get<bool>(other.value));
                    case NULL_TYPE:
                        return JS::Any(0);
                    default:
                        throw std::runtime_error("Invalid types for multiplication");
                }
            case NULL_TYPE:

                switch (other.value.index()) {
                    case NUMBER:
                        return JS::Any(0.0);
                    case STRING:
                        return JS::Any(0.0);
                    case BOOL:
                        return JS::Any(0.0);
                    case FUNCTION:
                        return JS::Any(0.0);
                    case NULL_TYPE:
                        return JS::Any(0.0);
                    default:
                        throw std::runtime_error("Invalid types for multiplication");
                }
            default:
                throw std::runtime_error("Invalid types for multiplication");
        }
    } catch (const std::invalid_argument& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN());
    } catch (const std::runtime_error& e) {
        return JS::Any(std::numeric_limits<double>::quiet_NaN()); // Handle multiplication
                                                                  // of invalid types
    }
}