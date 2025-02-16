#include <utils/Convert.hpp>

#include <types/JsAny.hpp>

JS::Value JS::Any::getValue() const { return this->value; }


namespace JS {
std::ostream& operator<<(std::ostream& os, const Any& any) {
    os << JS::CONVERT::ToString(any);
    return os;
}
} // namespace JS