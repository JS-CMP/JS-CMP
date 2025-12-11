#include "types/objects/Function/JsFunction.hpp"
#include "types/objects/JsDate.hpp"

std::shared_ptr<JS::InternalObject>& JS::Date::getPrototypeProperties() {
    static std::shared_ptr<JS::InternalObject> instance = nullptr;

    if (instance == nullptr) {
        instance = std::make_shared<JS::InternalObject>(JS::Properties{}, JS::Object::getPrototypeProperties(), u"Date", true);

        // Note: constructor will be set by getConstructor to avoid circular dependency
        instance->defineOwnProperty(u"toString",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::toString, 0, u"toString")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"toDateString",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::toDateString, 0, u"toDateString")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"toTimeString",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::toTimeString, 0, u"toTimeString")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"toLocaleString",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::toLocaleString, 0, u"toLocaleString")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"toLocaleDateString",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::toLocaleDateString, 0, u"toLocaleDateString")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"toLocaleTimeString",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::toLocaleTimeString, 0, u"toLocaleTimeString")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"valueOf",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::valueOf, 0, u"valueOf")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getTime",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getTime, 0, u"getTime")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getFullYear",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getFullYear, 0, u"getFullYear")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getUTCFullYear",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getUTCFullYear, 0, u"getUTCFullYear")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getMonth",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getMonth, 0, u"getMonth")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getUTCMonth",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getUTCMonth, 0, u"getUTCMonth")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getDate",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getDate, 0, u"getDate")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getUTCDate",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getUTCDate, 0, u"getUTCDate")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getDay",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getDay, 0, u"getDay")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getUTCDay",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getUTCDay, 0, u"getUTCDay")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getHours",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getHours, 0, u"getHours")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getUTCHours",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getUTCHours, 0, u"getUTCHours")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getMinutes",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getMinutes, 0, u"getMinutes")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getUTCMinutes",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getUTCMinutes, 0, u"getUTCMinutes")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getSeconds",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getSeconds, 0, u"getSeconds")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getUTCSeconds",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getUTCSeconds, 0, u"getUTCSeconds")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getMilliseconds",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getMilliseconds, 0, u"getMilliseconds")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getUTCMilliseconds",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getUTCMilliseconds, 0, u"getUTCMilliseconds")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"getTimezoneOffset",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::getTimezoneOffset, 0, u"getTimezoneOffset")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setTime",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setTime, 1, u"setTime")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setMilliseconds",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setMilliseconds, 1, u"setMilliseconds")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setUTCMilliseconds",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setUTCMilliseconds, 1, u"setUTCMilliseconds")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setSeconds",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setSeconds, 2, u"setSeconds")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setUTCSeconds",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setUTCSeconds, 2, u"setUTCSeconds")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setMinutes",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setMinutes, 3, u"setMinutes")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setUTCMinutes",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setUTCMinutes, 3, u"setUTCMinutes")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setHours",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setHours, 4, u"setHours")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setUTCHours",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setUTCHours, 4, u"setUTCHours")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setDate",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setDate, 1, u"setDate")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setUTCDate",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setUTCDate, 1, u"setUTCDate")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setMonth",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setMonth, 2, u"setMonth")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setUTCMonth",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setUTCMonth, 2, u"setUTCMonth")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setFullYear",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setFullYear, 3, u"setFullYear")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"setUTCFullYear",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::setUTCFullYear, 3, u"setUTCFullYear")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"toUTCString",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::toUTCString, 0, u"toUTCString")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"toISOString",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::toISOString, 0, u"toISOString")), true, false, true}, true);
                                                                                     instance->defineOwnProperty(u"toJSON",
            JS::DataDescriptor{JS::Any(std::make_shared<JS::Function>(JS::Date::toJSON, 1, u"toJSON")), true, false, true}, true);
    }

    return instance;
}