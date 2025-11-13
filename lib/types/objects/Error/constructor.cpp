#include "types/objects/Error/JsError.hpp"
#include "types/objects/Function/JsFunction.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

namespace JS {
Error::Error(const JS::Any& value, const std::shared_ptr<JS::InternalObject>& prototype) : JS::InternalObject({}, prototype == nullptr ? JS::Error::getPrototypeProperties() : prototype, ERROR_CLASS_NAME, true) {
    if (JS::COMPARE::Type(value, JS::UNDEFINED)) {
        return;
    }
    this->InternalObject::defineOwnProperty(u"message", JS::DataDescriptor{JS::Any(JS::CONVERT::ToString(value)), false, false, false});
}
} // namespace JS