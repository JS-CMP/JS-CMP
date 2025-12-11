#include "internals/Object.hpp"
#include "types/objects/JsDate.hpp"
#include "types/objects/JsObject.hpp"
#include "utils/Convert.hpp"
#include "utils/Is.hpp"

#include <types/objects/Function/JsFunction.hpp>
#include <utils/Compare.hpp>

std::u16string JS::Date::getContent() const {
    return JS::CONVERT::ToString(std::get<double>(this->primitiveValue)); // TODO format date string
}

std::shared_ptr<JS::Function> JS::Date::getConstructor() {
    static auto constructor = JS::InternalObject::create<JS::Function>(
        [](const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
            // Get the number of arguments
            JS::Any lengthAny = args[u"length"];
            int length = COMPARE::Type(lengthAny, JS::UNDEFINED) ? 0 : CONVERT::ToInteger(lengthAny);

            if (length == 0) {
                // new Date() - create with current time
                return JS::Any(JS::InternalObject::create<JS::Date>());
            } else if (length == 1) {
                // new Date(value) - create from single value
                JS::Any value = args[u"0"];
                return JS::Any(JS::InternalObject::create<JS::Date>(value));
            } else {
                // new Date(year, month, ...) - create from components
                JS::Any year = args[u"0"];
                JS::Any month = args[u"1"];
                JS::Any day = length > 2 ? args[u"2"] : JS::Any();
                JS::Any hours = length > 3 ? args[u"3"] : JS::Any();
                JS::Any minutes = length > 4 ? args[u"4"] : JS::Any();
                JS::Any seconds = length > 5 ? args[u"5"] : JS::Any();
                JS::Any milliseconds = length > 6 ? args[u"6"] : JS::Any();

                return JS::Any(JS::InternalObject::create<JS::Date>(year, month, day, hours, minutes, seconds, milliseconds));
            }
        },
        7, DATE_CLASS_NAME, nullptr);

    static bool initialized = false;
    if (!initialized) {
        initialized = true;

        auto prototype = Function::getPrototypeProperties(constructor);
        auto datePrototype = Date::getPrototypeProperties();

        // Set constructor property on the Date prototype
        datePrototype->defineOwnProperty(u"constructor", JS::DataDescriptor{JS::Any(constructor), true, false, true}, true);

        constructor->class_name = DATE_CLASS_NAME;
        constructor->extensible = true;
        constructor->prototype = prototype;
        constructor->properties = std::make_shared<JS::Properties>(JS::Properties({
            {u"length", JS::DataDescriptor{JS::Any(7), false, false, false}},
            {u"name", JS::DataDescriptor{JS::Any(DATE_CLASS_NAME), false, false, false}},
            {u"parse", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Date::parse, 1, u"parse")), true, false, true}},
            {u"UTC", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Date::UTC, 7, u"UTC")), true, false, true}},
            {u"now", JS::DataDescriptor{JS::Any(JS::InternalObject::create<JS::Function>(JS::Date::now, 0, u"now")), true, false, true}},
            {u"prototype", JS::DataDescriptor(JS::Any(datePrototype), false, false, false)}
        }));
    }

    return constructor;
}
