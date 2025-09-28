#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsArray.hpp"
#include "utils/Convert.hpp"

#include <stdexcept>
#include <types/objects/Error/JsRangeError.hpp>
#include <utils/Compare.hpp>

namespace JS {

Array::Array(const JS::Any& args)
    : InternalObject(
          {
              {u"length", JS::DataDescriptor{JS::Any(0), true, false, false}},
          },
          getPrototypeProperties(), ARRAY_CLASS_NAME, true) {
    auto len = CONVERT::ToUint32(args[u"length"]);
    if (len == 1) {
        auto value = args[u"0"];
        if (JS::COMPARE::Type(value, JS::NUMBER)) {
            const double lengthValue = JS::CONVERT::ToNumber(len);
            const uint32_t uintLength = JS::CONVERT::ToUint32(len);
            if (lengthValue != uintLength) {
                throw JS::Any(std::make_shared<JS::RangeError>(JS::Any(u"Invalid array length")));
            }
            this->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(uintLength), true, false, false});
        } else {
            this->defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(1), true, false, false});
            this->defineOwnProperty(u"0", JS::DataDescriptor{value, true, true, true});
        }
    } else {
        for (uint32_t i = 0; i < len; ++i) {
            this->defineOwnProperty(JS::CONVERT::ToString(i), JS::DataDescriptor{args[i], true, true, true});
        }
    }
}

Array::Array(const std::vector<JS::Any>& data)
    : InternalObject({{u"length", JS::DataDescriptor{JS::Any(static_cast<uint32_t>(data.size())), true, false, false}}},
                     getPrototypeProperties(), ARRAY_CLASS_NAME, true) {
    uint32_t length = data.size();
    for (uint32_t i = 0; i < length; ++i) {
        this->defineOwnProperty(JS::CONVERT::ToString(i), JS::DataDescriptor{data[i], true, true, true});
    }
}

} // namespace JS
