#include "utils/Convert.hpp"
#include "utils/Is.hpp"
#include "utils/Compare.hpp"
#include "internals/Object.hpp"

std::u16string JS::CONVERT::ObjectToString(std::shared_ptr<const JS::InternalObject> internalObject) {
    std::u16string result = u"{ ";
    bool first = true;

    for (const auto& [key, descriptor] : *internalObject->properties) {
        // Check if enumerable
        if (JS::IS::DataDescriptor(descriptor) && std::get<JS::DataDescriptor>(descriptor).enumerable ||
            JS::IS::AccessorDescriptor(descriptor) && std::get<JS::AccessorDescriptor>(descriptor).enumerable) {
            auto it = internalObject->get(key);

            if (!first) result += u", ";
            result += JS::CONVERT::ToString(key) + u": " + JS::CONVERT::Stringify(it);
            first = false;
        }
    }

    result += u" }";
    return result;
}

std::u16string JS::CONVERT::ArrayToString(std::shared_ptr<const JS::InternalObject> internalObject) {
    std::u16string result = u"[ ";
    auto len = internalObject->get(u"length");
    bool first = true;

    for (uint32_t i = 0; i < JS::CONVERT::ToUint32(len); ++i) {
        auto value = internalObject->get(JS::CONVERT::ToString(i));
        if (!first) result += u", ";
        first = false;
        result += JS::CONVERT::Stringify(value);
    }

    result += u" ]";
    return result;
}

std::u16string JS::CONVERT::FunctionToString(std::shared_ptr<const JS::InternalObject> internalObject) {
    std::u16string result = u"[Function: " + internalObject->class_name + u"]";
    return result;
}