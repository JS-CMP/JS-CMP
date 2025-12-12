#include "types/objects/JsJSON.hpp"

#include "internals/Object.hpp"
#include "internals/PropertyProxy.hpp"
#include "types/objects/Error/JsSyntaxError.hpp"
#include "types/objects/Error/JsTypeError.hpp"
#include "types/objects/JsArray.hpp"
#include "types/objects/JsObject.hpp"
#include "utils/Convert.hpp"
#include "utils/Is.hpp"

#include <algorithm>
#include <cmath>

namespace JS {


JS::Any JSON::parse(const JS::Any& thisArg, const JS::Any& args) {
    (void)thisArg;

    std::u16string jText = JS::CONVERT::ToString(args[u"0"]);

    JS::Any unfiltered = ParseJSONText(jText);

    JS::Any reviverArg = args[u"1"];
    if (JS::IS::Callable(reviverArg)) {

        auto root = JS::InternalObject::create<JS::Object>();

        root->defineOwnProperty(u"", JS::DataDescriptor{unfiltered, true, true, true}, false);

        auto reviver = std::get<std::shared_ptr<JS::InternalObject>>(reviverArg.getValue());

        return Walk(root, u"", reviver);
    }

    return unfiltered;
}


JS::Any JSON::Walk(const std::shared_ptr<JS::InternalObject>& holder, const std::u16string& name,
                   const std::shared_ptr<JS::InternalObject>& reviver) {

    JS::Any val = holder->get(name);

    if (std::holds_alternative<std::shared_ptr<JS::InternalObject>>(val.getValue())) {
        auto valObj = std::get<std::shared_ptr<JS::InternalObject>>(val.getValue());

        if (valObj->class_name == ARRAY_CLASS_NAME) {

            uint32_t len = JS::CONVERT::ToUint32(valObj->get(u"length"));
            for (uint32_t i = 0; i < len; ++i) {
                std::u16string iStr = JS::CONVERT::ToString(JS::Any(static_cast<double>(i)));
                JS::Any newElement = Walk(valObj, iStr, reviver);
                if (std::holds_alternative<JS::Undefined>(newElement.getValue())) {
                    valObj->deleteProperty(iStr, false);
                } else {
                    valObj->defineOwnProperty(iStr, JS::DataDescriptor{newElement, true, true, true}, false);
                }
            }
        } else {

            std::vector<std::u16string> keys;
            for (const auto& [key, attr] : *valObj->properties) {
                bool enumerable = std::visit(
                    [](const auto& desc) {
                        return desc.enumerable;
                    },
                    attr);
                if (enumerable) {
                    keys.push_back(key);
                }
            }

            for (const auto& P : keys) {
                JS::Any newElement = Walk(valObj, P, reviver);
                if (std::holds_alternative<JS::Undefined>(newElement.getValue())) {
                    valObj->deleteProperty(P, false);
                } else {
                    valObj->defineOwnProperty(P, JS::DataDescriptor{newElement, true, true, true}, false);
                }
            }
        }
    }

    auto argsArray = JS::Arguments::CreateArgumentsObject({JS::Any(name), val});
    return reviver->call_function(JS::Any(holder), argsArray);
}


JS::Any JSON::stringify(const JS::Any& thisArg, const JS::Any& args) {
    (void)thisArg;

    std::vector<std::shared_ptr<JS::InternalObject>> stack;

    std::u16string indent = u"";

    std::vector<std::u16string>* propertyList = nullptr;
    std::shared_ptr<JS::InternalObject> replacerFunction = nullptr;

    JS::Any value = args[u"0"];
    JS::Any replacer = args[u"1"];
    JS::Any space = args[u"2"];

    if (std::holds_alternative<std::shared_ptr<JS::InternalObject>>(replacer.getValue())) {
        auto replacerObj = std::get<std::shared_ptr<JS::InternalObject>>(replacer.getValue());

        if (JS::IS::Callable(replacer)) {
            replacerFunction = replacerObj;
        } else if (replacerObj->class_name == ARRAY_CLASS_NAME) {
            propertyList = new std::vector<std::u16string>();
            uint32_t len = JS::CONVERT::ToUint32(replacerObj->get(u"length"));
            for (uint32_t i = 0; i < len; ++i) {
                JS::Any v = replacerObj->get(JS::CONVERT::ToString(JS::Any(static_cast<double>(i))));
                std::u16string item;
                bool hasItem = false;

                if (std::holds_alternative<Rope>(v.getValue())) {
                    item = JS::CONVERT::ToString(v);
                    hasItem = true;
                } else if (std::holds_alternative<double>(v.getValue())) {
                    item = JS::CONVERT::ToString(v);
                    hasItem = true;
                } else if (std::holds_alternative<std::shared_ptr<JS::InternalObject>>(v.getValue())) {
                    auto vObj = std::get<std::shared_ptr<JS::InternalObject>>(v.getValue());
                    if (vObj->class_name == STRING_CLASS_NAME || vObj->class_name == NUMBER_CLASS_NAME) {
                        item = JS::CONVERT::ToString(v);
                        hasItem = true;
                    }
                }

                if (hasItem) {

                    if (std::find(propertyList->begin(), propertyList->end(), item) == propertyList->end()) {
                        propertyList->push_back(item);
                    }
                }
            }
        }
    }

    std::u16string gap = u"";

    if (std::holds_alternative<std::shared_ptr<JS::InternalObject>>(space.getValue())) {
        auto spaceObj = std::get<std::shared_ptr<JS::InternalObject>>(space.getValue());
        if (spaceObj->class_name == NUMBER_CLASS_NAME) {
            space = JS::Any(JS::CONVERT::ToNumber(space));
        } else if (spaceObj->class_name == STRING_CLASS_NAME) {
            space = JS::Any(JS::CONVERT::ToString(space));
        }
    }

    if (std::holds_alternative<double>(space.getValue())) {
        double spaceNum = std::get<double>(space.getValue());
        int spaceInt = static_cast<int>(std::min(10.0, std::floor(spaceNum)));
        if (spaceInt > 0) {
            gap = std::u16string(spaceInt, u' ');
        }
    } else if (std::holds_alternative<Rope>(space.getValue())) {
        std::u16string spaceStr = JS::CONVERT::ToString(space);
        if (spaceStr.length() <= 10) {
            gap = spaceStr;
        } else {
            gap = spaceStr.substr(0, 10);
        }
    }

    auto wrapper = JS::InternalObject::create<JS::Object>();
    wrapper->defineOwnProperty(u"", JS::DataDescriptor{value, true, true, true}, false);

    JS::Any result = Str(u"", wrapper, stack, indent, gap, replacerFunction, propertyList);

    delete propertyList;

    return result;
}


JS::Any JSON::Str(const std::u16string& key, const std::shared_ptr<JS::InternalObject>& holder,
                  std::vector<std::shared_ptr<JS::InternalObject>>& stack, std::u16string& indent,
                  const std::u16string& gap, const std::shared_ptr<JS::InternalObject>& replacerFunction,
                  const std::vector<std::u16string>* propertyList) {

    JS::Any value = holder->get(key);

    if (std::holds_alternative<std::shared_ptr<JS::InternalObject>>(value.getValue())) {
        auto valueObj = std::get<std::shared_ptr<JS::InternalObject>>(value.getValue());
        JS::Any toJSON = valueObj->get(u"toJSON");
        if (JS::IS::Callable(toJSON)) {
            auto toJSONFunc = std::get<std::shared_ptr<JS::InternalObject>>(toJSON.getValue());
            auto argsArray = JS::Arguments::CreateArgumentsObject({JS::Any(key)});
            value = toJSONFunc->call_function(value, argsArray);
        }
    }

    if (replacerFunction != nullptr) {
        auto argsArray = JS::Arguments::CreateArgumentsObject({JS::Any(key), value});
        value = replacerFunction->call_function(JS::Any(holder), argsArray);
    }

    if (std::holds_alternative<std::shared_ptr<JS::InternalObject>>(value.getValue())) {
        auto valueObj = std::get<std::shared_ptr<JS::InternalObject>>(value.getValue());
        if (valueObj->class_name == NUMBER_CLASS_NAME) {
            value = JS::Any(JS::CONVERT::ToNumber(value));
        } else if (valueObj->class_name == STRING_CLASS_NAME) {
            value = JS::Any(JS::CONVERT::ToString(value));
        } else if (valueObj->class_name == BOOL_CLASS_NAME) {

            if (std::holds_alternative<bool>(valueObj->primitiveValue)) {
                value = JS::Any(std::get<bool>(valueObj->primitiveValue));
            }
        }
    }

    if (std::holds_alternative<JS::Null>(value.getValue())) {
        return JS::Any(u"null");
    }

    if (std::holds_alternative<bool>(value.getValue())) {
        return std::get<bool>(value.getValue()) ? JS::Any(u"true") : JS::Any(u"false");
    }

    if (std::holds_alternative<Rope>(value.getValue())) {
        return JS::Any(Quote(JS::CONVERT::ToString(value)));
    }

    if (std::holds_alternative<double>(value.getValue())) {
        double num = std::get<double>(value.getValue());
        if (std::isfinite(num)) {
            return JS::Any(JS::CONVERT::ToString(value));
        }
        return JS::Any(u"null");
    }

    if (std::holds_alternative<std::shared_ptr<JS::InternalObject>>(value.getValue())) {
        auto valueObj = std::get<std::shared_ptr<JS::InternalObject>>(value.getValue());
        if (!JS::IS::Callable(value)) {
            if (valueObj->class_name == ARRAY_CLASS_NAME) {
                return JS::Any(JA(valueObj, stack, indent, gap, replacerFunction, propertyList));
            }
            return JS::Any(JO(valueObj, stack, indent, gap, replacerFunction, propertyList));
        }
    }

    return JS::Any(JS::Undefined{});
}


std::u16string JSON::Quote(const std::u16string& value) {
    std::u16string product = u"\"";

    for (char16_t C : value) {
        if (C == u'"' || C == u'\\') {
            product += u'\\';
            product += C;
        } else if (C == u'\b') {
            product += u"\\b";
        } else if (C == u'\f') {
            product += u"\\f";
        } else if (C == u'\n') {
            product += u"\\n";
        } else if (C == u'\r') {
            product += u"\\r";
        } else if (C == u'\t') {
            product += u"\\t";
        } else if (C < u' ') {

            product += u"\\u";
            std::u16string hex;
            for (int i = 3; i >= 0; --i) {
                int digit = (C >> (i * 4)) & 0xF;
                hex += static_cast<char16_t>(digit < 10 ? u'0' + digit : u'a' + digit - 10);
            }
            product += hex;
        } else {
            product += C;
        }
    }

    product += u'"';
    return product;
}


std::u16string JSON::JO(const std::shared_ptr<JS::InternalObject>& value,
                        std::vector<std::shared_ptr<JS::InternalObject>>& stack, std::u16string& indent,
                        const std::u16string& gap, const std::shared_ptr<JS::InternalObject>& replacerFunction,
                        const std::vector<std::u16string>* propertyList) {

    for (const auto& item : stack) {
        if (item.get() == value.get()) {
            throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Converting circular structure to JSON")));
        }
    }

    stack.push_back(value);

    std::u16string stepback = indent;

    indent = indent + gap;

    std::vector<std::u16string> K;
    if (propertyList != nullptr) {
        K = *propertyList;
    } else {
        for (const auto& [key, attr] : *value->properties) {
            bool enumerable = std::visit(
                [](const auto& desc) {
                    return desc.enumerable;
                },
                attr);
            if (enumerable) {
                K.push_back(key);
            }
        }
    }

    std::vector<std::u16string> partial;

    for (const auto& P : K) {
        JS::Any strP = Str(P, value, stack, indent, gap, replacerFunction, propertyList);
        if (!std::holds_alternative<JS::Undefined>(strP.getValue())) {
            std::u16string member = Quote(P);
            member += u':';
            if (!gap.empty()) {
                member += u' ';
            }
            member += JS::CONVERT::ToString(strP);
            partial.push_back(member);
        }
    }

    std::u16string final;
    if (partial.empty()) {
        final = u"{}";
    } else if (gap.empty()) {
        std::u16string properties;
        for (size_t i = 0; i < partial.size(); ++i) {
            if (i > 0) {
                properties += u',';
            }
            properties += partial[i];
        }
        final = u"{" + properties + u"}";
    } else {
        std::u16string separator = u",\n" + indent;
        std::u16string properties;
        for (size_t i = 0; i < partial.size(); ++i) {
            if (i > 0) {
                properties += separator;
            }
            properties += partial[i];
        }
        final = u"{\n" + indent + properties + u"\n" + stepback + u"}";
    }

    stack.pop_back();

    indent = stepback;

    return final;
}


std::u16string JSON::JA(const std::shared_ptr<JS::InternalObject>& value,
                        std::vector<std::shared_ptr<JS::InternalObject>>& stack, std::u16string& indent,
                        const std::u16string& gap, const std::shared_ptr<JS::InternalObject>& replacerFunction,
                        const std::vector<std::u16string>* propertyList) {

    for (const auto& item : stack) {
        if (item.get() == value.get()) {
            throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any(u"Converting circular structure to JSON")));
        }
    }

    stack.push_back(value);

    std::u16string stepback = indent;

    indent = indent + gap;

    std::vector<std::u16string> partial;

    uint32_t len = JS::CONVERT::ToUint32(value->get(u"length"));

    for (uint32_t index = 0; index < len; ++index) {
        std::u16string indexStr = JS::CONVERT::ToString(JS::Any(static_cast<double>(index)));
        JS::Any strP = Str(indexStr, value, stack, indent, gap, replacerFunction, propertyList);
        if (std::holds_alternative<JS::Undefined>(strP.getValue())) {
            partial.emplace_back(u"null");
        } else {
            partial.push_back(JS::CONVERT::ToString(strP));
        }
    }

    std::u16string final;
    if (partial.empty()) {
        final = u"[]";
    } else if (gap.empty()) {
        std::u16string properties;
        for (size_t i = 0; i < partial.size(); ++i) {
            if (i > 0) {
                properties += u',';
            }
            properties += partial[i];
        }
        final = u"[" + properties + u"]";
    } else {
        std::u16string separator = u",\n" + indent;
        std::u16string properties;
        for (size_t i = 0; i < partial.size(); ++i) {
            if (i > 0) {
                properties += separator;
            }
            properties += partial[i];
        }
        final = u"[\n" + indent + properties + u"\n" + stepback + u"]";
    }

    stack.pop_back();

    indent = stepback;

    return final;
}


JS::Any JSON::ParseJSONText(const std::u16string& text) {
    size_t pos = 0;
    SkipWhitespace(text, pos);
    JS::Any result = ParseJSONValue(text, pos);
    SkipWhitespace(text, pos);

    if (pos != text.length()) {
        throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Unexpected token in JSON")));
    }

    return result;
}

void JSON::SkipWhitespace(const std::u16string& text, size_t& pos) {

    while (pos < text.length()) {
        char16_t c = text[pos];
        if (c == u'\t' || c == u'\r' || c == u'\n' || c == u' ') {
            ++pos;
        } else {
            break;
        }
    }
}

JS::Any JSON::ParseJSONValue(const std::u16string& text, size_t& pos) {
    SkipWhitespace(text, pos);

    if (pos >= text.length()) {
        throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Unexpected end of JSON input")));
    }

    char16_t c = text[pos];

    if (c == u'{') {
        return ParseJSONObject(text, pos);
    } else if (c == u'[') {
        return ParseJSONArray(text, pos);
    } else if (c == u'"') {
        return JS::Any(ParseJSONString(text, pos));
    } else if (c == u'-' || (c >= u'0' && c <= u'9')) {
        return ParseJSONNumber(text, pos);
    } else if (c == u't' || c == u'f' || c == u'n') {
        return ParseJSONLiteral(text, pos);
    }

    throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Unexpected token in JSON")));
}

JS::Any JSON::ParseJSONObject(const std::u16string& text, size_t& pos) {

    if (text[pos] != u'{') {
        throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Expected '{'")));
    }
    ++pos;
    SkipWhitespace(text, pos);

    auto obj = JS::InternalObject::create<JS::Object>();

    if (pos < text.length() && text[pos] == u'}') {
        ++pos;
        return JS::Any(obj);
    }

    while (true) {
        SkipWhitespace(text, pos);

        if (pos >= text.length() || text[pos] != u'"') {
            throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Expected string key in object")));
        }
        std::u16string key = ParseJSONString(text, pos);

        SkipWhitespace(text, pos);

        if (pos >= text.length() || text[pos] != u':') {
            throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Expected ':' after key")));
        }
        ++pos;

        SkipWhitespace(text, pos);

        JS::Any value = ParseJSONValue(text, pos);

        obj->defineOwnProperty(key, JS::DataDescriptor{value, true, true, true}, false);

        SkipWhitespace(text, pos);

        if (pos >= text.length()) {
            throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Unexpected end of JSON input")));
        }

        if (text[pos] == u'}') {
            ++pos;
            break;
        } else if (text[pos] == u',') {
            ++pos;
        } else {
            throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Expected ',' or '}' in object")));
        }
    }

    return JS::Any(obj);
}

JS::Any JSON::ParseJSONArray(const std::u16string& text, size_t& pos) {

    if (text[pos] != u'[') {
        throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Expected '['")));
    }
    ++pos;
    SkipWhitespace(text, pos);

    std::vector<JS::Any> elements;

    if (pos < text.length() && text[pos] == u']') {
        ++pos;
        return JS::Any(JS::InternalObject::create<JS::Array>(elements));
    }

    while (true) {
        SkipWhitespace(text, pos);

        JS::Any value = ParseJSONValue(text, pos);
        elements.push_back(value);

        SkipWhitespace(text, pos);

        if (pos >= text.length()) {
            throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Unexpected end of JSON input")));
        }

        if (text[pos] == u']') {
            ++pos;
            break;
        } else if (text[pos] == u',') {
            ++pos;
        } else {
            throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Expected ',' or ']' in array")));
        }
    }

    return JS::Any(JS::InternalObject::create<JS::Array>(elements));
}

std::u16string JSON::ParseJSONString(const std::u16string& text, size_t& pos) {

    if (text[pos] != u'"') {
        throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Expected '\"'")));
    }
    ++pos;

    std::u16string result;

    while (pos < text.length()) {
        char16_t c = text[pos];

        if (c == u'"') {
            ++pos;
            return result;
        } else if (c == u'\\') {
            ++pos;
            if (pos >= text.length()) {
                throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Unexpected end of string")));
            }

            char16_t escaped = text[pos];
            ++pos;

            switch (escaped) {
                case u'"':
                    result += u'"';
                    break;
                case u'\\':
                    result += u'\\';
                    break;
                case u'/':
                    result += u'/';
                    break;
                case u'b':
                    result += u'\b';
                    break;
                case u'f':
                    result += u'\f';
                    break;
                case u'n':
                    result += u'\n';
                    break;
                case u'r':
                    result += u'\r';
                    break;
                case u't':
                    result += u'\t';
                    break;
                case u'u':
                    result += ParseUnicodeEscape(text, pos);
                    break;
                default:
                    throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Invalid escape sequence")));
            }
        } else if (c < 0x0020) {

            throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Control character in string")));
        } else {
            result += c;
            ++pos;
        }
    }

    throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Unterminated string")));
}

char16_t JSON::ParseUnicodeEscape(const std::u16string& text, size_t& pos) {
    if (pos + 4 > text.length()) {
        throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Invalid unicode escape")));
    }

    uint16_t codePoint = 0;
    for (int i = 0; i < 4; ++i) {
        char16_t c = text[pos + i];
        codePoint <<= 4;
        if (c >= u'0' && c <= u'9') {
            codePoint |= (c - u'0');
        } else if (c >= u'a' && c <= u'f') {
            codePoint |= (c - u'a' + 10);
        } else if (c >= u'A' && c <= u'F') {
            codePoint |= (c - u'A' + 10);
        } else {
            throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Invalid unicode escape")));
        }
    }
    pos += 4;

    return static_cast<char16_t>(codePoint);
}

JS::Any JSON::ParseJSONNumber(const std::u16string& text, size_t& pos) {
    size_t start = pos;

    if (pos < text.length() && text[pos] == u'-') {
        ++pos;
    }

    if (pos < text.length() && text[pos] == u'0') {
        ++pos;
    } else if (pos < text.length() && text[pos] >= u'1' && text[pos] <= u'9') {
        ++pos;
        while (pos < text.length() && text[pos] >= u'0' && text[pos] <= u'9') {
            ++pos;
        }
    } else {
        throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Invalid number")));
    }

    if (pos < text.length() && text[pos] == u'.') {
        ++pos;
        if (pos >= text.length() || text[pos] < u'0' || text[pos] > u'9') {
            throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Invalid number")));
        }
        while (pos < text.length() && text[pos] >= u'0' && text[pos] <= u'9') {
            ++pos;
        }
    }

    if (pos < text.length() && (text[pos] == u'e' || text[pos] == u'E')) {
        ++pos;
        if (pos < text.length() && (text[pos] == u'+' || text[pos] == u'-')) {
            ++pos;
        }
        if (pos >= text.length() || text[pos] < u'0' || text[pos] > u'9') {
            throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Invalid number")));
        }
        while (pos < text.length() && text[pos] >= u'0' && text[pos] <= u'9') {
            ++pos;
        }
    }

    std::u16string numStr = text.substr(start, pos - start);
    std::string utf8Str = JS::CONVERT::ToUtf8(numStr);

    try {
        double num = std::stod(utf8Str);
        return JS::Any(num);
    } catch (...) {
        throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Invalid number")));
    }
}

JS::Any JSON::ParseJSONLiteral(const std::u16string& text, size_t& pos) {
    if (text.substr(pos, 4) == u"true") {
        pos += 4;
        return JS::Any(true);
    } else if (text.substr(pos, 5) == u"false") {
        pos += 5;
        return JS::Any(false);
    } else if (text.substr(pos, 4) == u"null") {
        pos += 4;
        return JS::Any(JS::Null{});
    }

    throw JS::Any(JS::InternalObject::create<JS::SyntaxError>(JS::Any(u"Unexpected token in JSON")));
}

} // namespace JS