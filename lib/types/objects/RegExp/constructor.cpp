#include "internals/Attribute.hpp"
#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsRegExp.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <types/objects/Error/JsTypeError.hpp>

namespace JS {
RegExp::RegExp(const JS::Any& pattern, const JS::Any& flags)
    : JS::InternalObject({}, getPrototypeProperties(), REGEXP_CLASS_NAME, true) {
    if (JS::COMPARE::Type(pattern, JS::OBJECT) &&
        std::get<std::shared_ptr<JS::InternalObject>>(pattern.getValue())->class_name == REGEXP_CLASS_NAME) {
        if (JS::COMPARE::Type(flags, JS::UNDEFINED)) {
            auto RegExpObj = std::get<std::shared_ptr<JS::InternalObject>>(pattern.getValue());
            std::u16string P = JS::CONVERT::ToString(RegExpObj->get(u"source"));
        } else {
            throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Invalid flags for RegExp")));
        }
    } else {
        std::u16string P = JS::CONVERT::ToString(pattern);
        std::u16string F = JS::CONVERT::ToString(flags);

        // Validate the pattern and flags
        bool global = F.find(u'g') != std::u16string::npos;
        bool ignoreCase = F.find(u'i') != std::u16string::npos;
        bool multiline = F.find(u'm') != std::u16string::npos;

        if (F.find_first_not_of(u"gim") != std::u16string::npos || (global && F.find(u'g') != F.find_last_of(u'g')) ||
            (ignoreCase && F.find(u'i') != F.find_last_of(u'i')) ||
            (multiline && F.find(u'm') != F.find_last_of(u'm'))) {
            throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Invalid regular expression flags")));
        }
        boost::regex_constants::syntax_option_type opt =
            boost::regex_constants::ECMAScript | boost::regex_constants::optimize;
        if (ignoreCase) {
            opt |= boost::regex_constants::icase;
        }
        boost::u32regex expr = boost::make_u32regex(P, opt);
        if (expr.status() != 0) {
            throw JS::Any(JS::InternalObject::create<JS::TypeError>(JS::Any("Invalid regular expression pattern")));
        }

        this->defineOwnProperty(u"source", JS::DataDescriptor{JS::Any(P), false, false, false});
        this->defineOwnProperty(u"global", JS::DataDescriptor{JS::Any(global), false, false, false});
        this->defineOwnProperty(u"ignoreCase", JS::DataDescriptor{JS::Any(ignoreCase), false, false, false});
        this->defineOwnProperty(u"multiline", JS::DataDescriptor{JS::Any(multiline), false, false, false});
        this->defineOwnProperty(u"lastIndex", JS::DataDescriptor{JS::Any(0), true, false, false});
    }
}
} // namespace JS