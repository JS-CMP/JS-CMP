#include "types/objects/JsString.hpp"

// override
std::optional<JS::Attribute> JS::String::getOwnProperty(const std::string& key) const {
    auto desc = JS::InternalObject::getOwnProperty(key);
    if (desc.has_value()) {
        return desc;
    }
    if (JS::CONVERT::ToString(abs(JS::CONVERT::ToInteger(key))) == key) {
        return std::nullopt;
    }
    if (this->primitiveValue.index() != JS::STRING) {
        throw std::runtime_error("Unexpected primitive value"); // should not happen
    }
    Rope str = std::get<Rope>(this->primitiveValue);
    int index = JS::CONVERT::ToInteger(key);
    int len = str.length();
    if (len <= index) {
        return std::nullopt;
    }
    auto resultStr = str.toString()[index]; // TODO:: make [] operator in ropes
    return JS::DataDescriptor(JS::Any(resultStr), false, false, false);
}

// static
JS::Any JS::String::fromCharCode(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

// prototype methods
JS::Any JS::String::toString(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::valueOf(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::charAt(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::charCodeAt(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::concat(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::indexOf(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::lastIndexOf(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::localeCompare(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::match(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::replace(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::search(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::slice(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::split(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::substring(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::toLowerCase(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::toLocaleLowerCase(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::toUpperCase(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::toLocaleUpperCase(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }

JS::Any JS::String::trim(const std::vector<JS::Any>& args) { throw std::runtime_error("not implemented"); }
