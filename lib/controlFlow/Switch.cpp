#include "controlFlow/Switch.hpp"
#include "utils/Convert.hpp"

namespace JS {
std::size_t Hash::operator()(const std::optional<JS::Any>& key) const {
    if (!key.has_value()) {
        return 0; // Handle nullopt case
    }
    JS::Any keyValue = key.value();
    switch (keyValue.getValue().index()) {
        case JS::NUMBER:
            return std::hash<double>{}(std::get<double>(keyValue.getValue()));
        case JS::STRING:
            return std::hash<std::string>{}(JS::CONVERT::ToString(std::get<Rope>(keyValue.getValue()))); // TODO change to this when hash is added to Rope std::hash<Rope>{}(std::get<Rope>(key.getValue()));
        case JS::BOOLEAN:
            return std::hash<bool>{}(std::get<bool>(keyValue.getValue()));
        case JS::UNDEFINED:
            return 0xdeadbeef; // Arbitrary value for undefined
        case JS::NULL_TYPE:
            return 0xfeedface; // Arbitrary value for null
        case JS::OBJECT:
            return std::hash<void*>{}(std::get<std::shared_ptr<JS::InternalObject>>(keyValue.getValue()).get());
        default:
            throw std::invalid_argument("Unsupported type for hashing"); // TODO Native Error
    }
}

bool StrictEqual::operator()(const std::optional<JS::Any>& rhs, const std::optional<JS::Any>& lhs) const {
    if (!rhs.has_value() || !lhs.has_value()) {
        return !rhs.has_value() && !lhs.has_value(); // Both must be nullopt to be strictly equal
    }
    JS::Any rhsValue = rhs.value();
    JS::Any lhsValue = lhs.value();
    return rhsValue.strictEq(lhsValue); // TODO: remove and rework when custom operator merged
}
} // namespace JS