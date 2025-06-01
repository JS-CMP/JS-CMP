#include "types/objects/JsArray.hpp"
#include "utils/Convert.hpp"

#include <stdexcept>
#include <utils/Compare.hpp>

namespace JS {

Array::Array()
    : InternalObject({{u"length", JS::DataDescriptor{JS::Any(0), true, false, false}}}, getPrototypeProperties(),
                     u"Array", true) {}

Array::Array(const JS::Any& len)
    : InternalObject(
          {
              {u"length", JS::DataDescriptor{JS::Any(1), true, false, false}},
          },
          getPrototypeProperties(), u"Array", true) {
    if (JS::COMPARE::Type(len, JS::NUMBER)) {
        double lengthValue = JS::CONVERT::ToNumber(len);
        uint32_t uintLength = JS::CONVERT::ToUint32(len);
        if (lengthValue != uintLength) {
            throw std::range_error("Invalid array length"); // TODO: Handle this error properly
        }
        this->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(uintLength), true, false, false});
    } else {
        this->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(1), true, false, false});
        this->defineOwnProperty(u"0", JS::DataDescriptor{len, true, true, true});
    }
}

Array::Array(const std::vector<JS::Any>& data)
    : InternalObject({{u"length", JS::DataDescriptor{JS::Any(static_cast<uint32_t>(data.size())), true, false, false}}},
                     getPrototypeProperties(), u"Array", true) {
    uint32_t length = data.size();
    for (uint32_t i = 0; i < length; ++i) {
        this->defineOwnProperty(JS::CONVERT::ToString(i), JS::DataDescriptor{data[i], true, true, true});
    }
}

} // namespace JS
