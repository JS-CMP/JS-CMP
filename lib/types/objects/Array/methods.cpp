#include "types/objects/JsArray.hpp"
#include "types/objects/JsObject.hpp"
#include "utils/Compare.hpp"
#include "utils/Convert.hpp"

#include <algorithm>
#include <stdexcept>
#include <utils/Is.hpp>

namespace JS {

bool Array::defineOwnProperty(const std::u16string& key, JS::Attribute attribute, bool is_throw) {
    std::optional<JS::Attribute> oldLenDesc = this->getOwnProperty(u"length");
    if (!oldLenDesc.has_value() || !JS::IS::DataDescriptor(oldLenDesc.value())) {
        if (is_throw) {
            throw std::runtime_error("Cannot define property on Array: length is not a data descriptor");
            // TODO: TypeError
        }
        return false;
    }
    uint32_t oldLen = JS::CONVERT::ToUint32(std::get<JS::DataDescriptor>(oldLenDesc.value()).value);
    if (key == u"length") {
        if (!JS::IS::DataDescriptor(attribute)) {
            return this->InternalObject::defineOwnProperty(key, attribute, is_throw);
        }
        JS::DataDescriptor newLenDesc = std::get<JS::DataDescriptor>(attribute);
        uint32_t newLen = JS::CONVERT::ToUint32(newLenDesc.value);
        if (newLen != JS::CONVERT::ToNumber(newLenDesc.value)) {
            if (is_throw) {
                throw std::range_error("Invalid array length"); // TODO: Handle this error properly
            }
            return false;
        }
        if (newLen >= oldLen) {
            return this->InternalObject::defineOwnProperty(u"length", newLenDesc, is_throw);
        }
        if (!std::get<JS::DataDescriptor>(oldLenDesc.value()).writable) {
            if (is_throw) {
                throw std::runtime_error("Cannot redefine property: length is not writable"); // TODO: TypeError
            }
            return false;
        }
        bool newWritable = newLenDesc.writable;
        if (newLenDesc.writable) {
            newLenDesc.writable = true; // Set writable to true for the next steps
        } else {
            newWritable = false; // We will set it to false later if needed
        }
        bool succeeded = this->InternalObject::defineOwnProperty(u"length", newLenDesc, false);
        if (!succeeded) {
            return false;
        }
        while (newLen < oldLen) {
            oldLen--;
            std::u16string oldLenStr = JS::CONVERT::ToString(oldLen);
            bool deleteSucceeded = this->deleteProperty(oldLenStr, false);
            if (!deleteSucceeded) {
                newLenDesc.value = JS::Any(oldLen + 1);
                if (!newWritable) {
                    newLenDesc.writable = false;
                }
                this->InternalObject::defineOwnProperty(u"length", newLenDesc, false);
                if (is_throw) {
                    throw std::runtime_error("Cannot delete property: length"); // TODO: TypeError
                }
                return false;
            }
        }
        if (!newWritable) {
            this->InternalObject::defineOwnProperty(u"length", JS::DataDescriptor{JS::Any(false), false, false, true},
                                                    false);
        }
        return true;
    }
    if (JS::IS::ArrayIndex(key)) {
        uint32_t index = JS::CONVERT::ToUint32(key);
        if (index >= oldLen && !std::get<JS::DataDescriptor>(oldLenDesc.value()).writable) {
            if (is_throw) {
                throw std::runtime_error("Cannot define property: length is not writable"); // TODO: TypeError
            }
            return false;
        }
        bool succeeded = this->InternalObject::defineOwnProperty(key, attribute, false);
        if (!succeeded) {
            return false;
        }
        if (index >= oldLen) {
            JS::DataDescriptor oldLenDescValue = std::get<JS::DataDescriptor>(oldLenDesc.value());
            oldLenDescValue.value = JS::Any(index + 1);
            this->InternalObject::defineOwnProperty(u"length", oldLenDescValue, false);
        }
        return true;
    }
    return this->InternalObject::defineOwnProperty(key, attribute, is_throw);
}

// prototype methods
JS::Any Array::toString(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<JS::InternalObject> array = JS::CONVERT::ToObject(thisArg);
    JS::Any func = array->get(u"join");
    if (!JS::IS::Callable(func)) {
        return JS::Object::toString(thisArg, args);
    }
    std::shared_ptr<JS::InternalObject> funcObj = std::get<std::shared_ptr<JS::InternalObject>>(func.getValue());
    return funcObj->call_function(JS::Any(array), JS::Arguments::CreateArgumentsObject({}));
}

JS::Any Array::toLocaleString(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<JS::InternalObject> array = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(array->get(u"length"));
    if (len == 0) {
        return JS::Any(u"");
    }

    JS::Any firstElement = array->get(u"0");
    std::u16string R;
    if (JS::COMPARE::Type(firstElement, JS::UNDEFINED) || JS::COMPARE::Type(firstElement, JS::NULL_TYPE)) {
        R = u"";
    } else {
        std::shared_ptr<JS::InternalObject> elementObj = JS::CONVERT::ToObject(firstElement);
        JS::Any func = elementObj->get(u"toLocaleString");
        if (!JS::IS::Callable(func)) {
            throw std::runtime_error("TypeError: toLocaleString is not callable"); // TODO: Handle this error properly
        }
        // This can be optimized to return a string because next is R + a string so R became a string in all the case
        R = JS::CONVERT::ToString(std::get<std::shared_ptr<JS::InternalObject>>(func.getValue())
                                      ->call_function(JS::Any(elementObj), JS::Arguments::CreateArgumentsObject({})));
    }
    uint32_t k = 1;
    while (k < len) {
        std::u16string S = R + JS::ArraySeparator; // Use the default separator
        JS::Any nextElement = array->get(JS::CONVERT::ToString(k));
        if (JS::COMPARE::Type(nextElement, JS::UNDEFINED) || JS::COMPARE::Type(nextElement, JS::NULL_TYPE)) {
            R = u"";
        } else {
            std::shared_ptr<JS::InternalObject> elementObj = JS::CONVERT::ToObject(nextElement);
            JS::Any func = elementObj->get(u"toLocaleString");
            if (!JS::IS::Callable(func)) {
                throw std::runtime_error("TypeError: toLocaleString is not callable");
                // TODO: Handle this error properly
            }
            R = JS::CONVERT::ToString(
                std::get<std::shared_ptr<JS::InternalObject>>(func.getValue())
                    ->call_function(JS::Any(elementObj), JS::Arguments::CreateArgumentsObject({})));
        }
        R.insert(0, S); // faster that R = S + R
        k++;
    }
    return JS::Any(R);
}

JS::Any Array::concat(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    std::shared_ptr<JS::InternalObject> A = std::make_shared<JS::Array>();
    uint32_t n = 0;
    std::vector<JS::Any> items = {JS::Any(O)};
    uint32_t length = JS::CONVERT::ToUint32(O->get(u"length"));
    for (uint32_t i = 0; i < length; ++i) {
        items.push_back(O->get(JS::CONVERT::ToString(i)));
    }
    while (!items.empty()) {
        JS::Any E = items.front();
        items.erase(items.begin());
        if (JS::COMPARE::Object(E, u"Array")) {
            std::shared_ptr<JS::InternalObject> arrayObj = std::get<std::shared_ptr<JS::InternalObject>>(E.getValue());
            uint32_t k = 0;
            uint32_t len = JS::CONVERT::ToUint32(arrayObj->get(u"length"));
            while (k < len) {
                std::u16string P = JS::CONVERT::ToString(k);
                if (arrayObj->hasProperty(P)) {
                    JS::Any subElement = arrayObj->get(P);
                    A->defineOwnProperty(JS::CONVERT::ToString(n), JS::DataDescriptor{subElement, true, true, true},
                                         false);
                    n++;
                }
                k++;
            }
        } else {
            A->defineOwnProperty(JS::CONVERT::ToString(n), JS::DataDescriptor{E, true, true, true}, false);
            n++;
        }
    }
    return JS::Any(A);
}

JS::Any Array::join(const JS::Any& thisArg, const JS::Any& args) {

    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    if (len == 0) {
        return JS::Any(u"");
    }
    std::u16string sep = JS::COMPARE::Type(args[u"0"], JS::UNDEFINED) ? JS::ArraySeparator : JS::CONVERT::ToString(args[u"0"]);
    JS::Any element0 = O->get(u"0");
    std::u16string R = JS::COMPARE::Type(element0, JS::UNDEFINED) || JS::COMPARE::Type(element0, JS::NULL_TYPE)
                           ? u""
                           : JS::CONVERT::ToString(element0);
    uint32_t k = 1;
    while (k < len) {
        std::u16string S = R + sep;
        JS::Any element = O->get(JS::CONVERT::ToString(k));
        std::u16string next = JS::COMPARE::Type(element, JS::UNDEFINED) || JS::COMPARE::Type(element, JS::NULL_TYPE)
                                  ? u""
                                  : JS::CONVERT::ToString(element);
        R = S + next;
        k++;
    }
    return JS::Any(R);
}

JS::Any Array::pop(const JS::Any& thisArg, const JS::Any& args) {

    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    if (len == 0) {
        O->put(u"length", JS::Any(0), true);
        return JS::Any(JS::UNDEFINED);
    }
    std::u16string indx = JS::CONVERT::ToString(len - 1);
    JS::Any element = O->get(indx);
    O->deleteProperty(indx, true);
    O->put(u"length", JS::Any(len - 1), true);
    return element;
}

JS::Any Array::push(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t n = JS::CONVERT::ToUint32(O->get(u"length"));
    uint32_t length = JS::CONVERT::ToUint32(args[u"length"]);
    for (uint32_t i = 0; i < length; ++i) {
        O->put(JS::CONVERT::ToString(n), args[JS::CONVERT::ToString(i)], true);
        n++;
    }
    O->put(u"length", JS::Any(n), true);
    return JS::Any(n);
}

JS::Any Array::reverse(const JS::Any& thisArg, const JS::Any& args) {

    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    uint32_t middle = len / 2;
    uint32_t lower = 0;
    while (lower != middle) {
        uint32_t upper = len - lower - 1;
        std::u16string upperP = JS::CONVERT::ToString(upper);
        std::u16string lowerP = JS::CONVERT::ToString(lower);
        JS::Any lowerValue = O->get(lowerP);
        JS::Any upperValue = O->get(upperP);
        bool lowerExists = O->hasProperty(lowerP);
        bool upperExists = O->hasProperty(upperP);
        if (lowerExists && upperExists) {
            O->put(lowerP, upperValue, true);
            O->put(upperP, lowerValue, true);
        } else if (!lowerExists && upperExists) {
            O->put(lowerP, upperValue, true);
            O->deleteProperty(upperP, true);
        } else if (lowerExists && !upperExists) {
            O->deleteProperty(lowerP, true);
            O->put(upperP, lowerValue, true);
        }
        // else: both are false, no action required
        lower++;
    }
    return JS::Any(O);
}

JS::Any Array::shift(const JS::Any& thisArg, const JS::Any& args) {

    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    if (len == 0) {
        O->put(u"length", JS::Any(0), true);
        return JS::Any(JS::UNDEFINED);
    }
    JS::Any first = O->get(u"0");
    uint32_t k = 1;
    while (k < len) {
        std::u16string from = JS::CONVERT::ToString(k);
        std::u16string to = JS::CONVERT::ToString(k - 1);
        if (O->hasProperty(from)) {
            JS::Any fromVal = O->get(from);
            O->put(to, fromVal, true);
        } else {
            O->deleteProperty(to, true);
        }
        k++;
    }
    O->deleteProperty(JS::CONVERT::ToString(len - 1), true);
    O->put(u"length", JS::Any(len - 1), true);
    return first;
}

JS::Any Array::slice(const JS::Any& thisArg, const JS::Any& args) {
    JS::Any start = args[u"0"];
    JS::Any end = args[u"1"];
    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    std::shared_ptr<JS::InternalObject> A = std::make_shared<JS::Array>();
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    int relativeStart = JS::CONVERT::ToInteger(args[u"0"]);
    uint32_t k = (relativeStart < 0) ? std::max(static_cast<int32_t>(len + relativeStart), 0)
                                     : std::min(static_cast<uint32_t>(relativeStart), len);
    int relativeEnd = (JS::COMPARE::Type(end, JS::UNDEFINED)) ? static_cast<int>(len) : JS::CONVERT::ToInteger(end);
    uint32_t final = (relativeEnd < 0) ? std::max(static_cast<int32_t>(len + relativeEnd), 0)
                                       : std::min(static_cast<uint32_t>(relativeEnd), len);
    uint32_t n = 0;
    while (k < final) {
        std::u16string Pk = JS::CONVERT::ToString(k);
        if (O->hasProperty(Pk)) {
            JS::Any kValue = O->get(Pk);
            A->defineOwnProperty(JS::CONVERT::ToString(n), JS::DataDescriptor{kValue, true, true, true}, false);
        }
        k++;
        n++;
    }
    return JS::Any(A);
}

JS::Any Array::sort(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<JS::InternalObject> obj = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(obj->get(u"length"));
    std::vector<std::pair<std::u16string, JS::Any>> elements;
    for (uint32_t i = 0; i < len; ++i) {
        std::u16string key = JS::CONVERT::ToString(i);
        elements.emplace_back(key, obj->get(key));
    }
    if (JS::COMPARE::Type(args[u"0"], JS::UNDEFINED)) {
        auto compareFn = [](const JS::Any& a, const JS::Any& b) {
            if (JS::COMPARE::Type(a, JS::UNDEFINED) && JS::COMPARE::Type(b, JS::UNDEFINED)) {
                return 0;
            }
            if (JS::COMPARE::Type(a, JS::UNDEFINED)) {
                return 1;
            }
            if (JS::COMPARE::Type(b, JS::UNDEFINED)) {
                return -1;
            }
            return JS::CONVERT::ToString(a) < JS::CONVERT::ToString(b) ? -1 : 1;
        };
        std::ranges::sort(elements, [&compareFn](const std::pair<std::u16string, JS::Any>& a,
                                                 const std::pair<std::u16string, JS::Any>& b) {
            return compareFn(a.second, b.second) < 0;
        });
    } else if (JS::COMPARE::Type(args[u"0"], JS::OBJECT)) {
        if (!JS::IS::Callable(args[u"0"])) {
            throw std::runtime_error("TypeError: compare function is not callable"); // TODO: Handle this error properly
        }
        auto compareFn = std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
        std::ranges::sort(elements, [&compareFn](const std::pair<std::u16string, JS::Any>& a,
                                                 const std::pair<std::u16string, JS::Any>& b) {
            return JS::CONVERT::ToInteger(compareFn->call_function(
                       JS::Any(), JS::Arguments::CreateArgumentsObject({a.second, b.second}))) < 0;
        });
    } else {
        throw std::runtime_error("TypeError: compare function is not callable"); // TODO: Handle this error properly
    }
    uint32_t index = 0;
    for (const auto& [key, value] : elements) {
        obj->put(JS::CONVERT::ToString(index), value, true);
        index++;
    }
    return JS::Any(obj);
}

JS::Any Array::splice(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    std::shared_ptr<JS::InternalObject> A = std::make_shared<JS::Array>();
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    int relativeStart = JS::CONVERT::ToInteger(args[u"0"]);
    int actualStart = (relativeStart < 0) ? std::max(static_cast<int>(len) + relativeStart, 0)
                                          : std::min(relativeStart, static_cast<int>(len));
    int actualDeleteCount =
        std::min(std::max(JS::CONVERT::ToInteger(args[u"1"]), 0), static_cast<int>(len) - actualStart);
    int k = 0;
    while (actualDeleteCount > 0) {
        std::u16string from = JS::CONVERT::ToString(actualStart + actualDeleteCount - 1);
        if (O->hasProperty(from)) {
            JS::Any fromValue = O->get(from);
            A->defineOwnProperty(JS::CONVERT::ToString(k),
                                 JS::DataDescriptor{fromValue, true, true, true}, false);
        }
        actualDeleteCount--;
        k++;
    }
    std::vector<JS::Any> items;
    for (uint32_t i = 2; i < len; ++i) {
        items.push_back(args[JS::CONVERT::ToString(i)]);
    }
    uint32_t itemCount = items.size();
    if (itemCount < actualDeleteCount) {
        int k = actualStart;
        while (k < (len - actualDeleteCount)) {
            std::u16string from = JS::CONVERT::ToString(k + actualDeleteCount);
            std::u16string to = JS::CONVERT::ToString(k + itemCount);
            if (O->hasProperty(from)) {
                JS::Any fromValue = O->get(from);
                O->put(to, fromValue, true);
            } else {
                O->deleteProperty(to, true);
            }
            k++;
        }
        uint32_t k2 = len;
        while (k2 > (len - actualDeleteCount + itemCount)) {
            O->deleteProperty(JS::CONVERT::ToString(k2 - 1), true);
            k2--;
        }
    } else if (itemCount > actualDeleteCount) {
        int k = len - actualDeleteCount;
        while (k > actualStart) {
            std::u16string from = JS::CONVERT::ToString(k + actualDeleteCount - 1);
            std::u16string to = JS::CONVERT::ToString(k + itemCount - 1);
            if (O->hasProperty(from)) {
                JS::Any fromValue = O->get(from);
                O->put(to, fromValue, true);
            } else {
                O->deleteProperty(to, true);
            }
            k--;
        }
    }
    k = actualStart;
    while (!items.empty()) {
        JS::Any E = items.front();
        items.erase(items.begin());
        O->put(JS::CONVERT::ToString(k), E, true);
        k++;
    }
    O->put(u"length", JS::Any(len - actualDeleteCount + itemCount), true);
    return JS::Any(A);
}

JS::Any Array::unshift(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    uint32_t argCount = JS::CONVERT::ToUint32(args[u"length"]);
    uint32_t k = len;
    while (k > 0) {
        std::u16string from = JS::CONVERT::ToString(k - 1);
        std::u16string to = JS::CONVERT::ToString(k + argCount - 1);
        if (O->hasProperty(from)) {
            JS::Any fromValue = O->get(from);
            O->put(to, fromValue, true);
        } else {
            O->deleteProperty(to, true);
        }
        k--;
    }
    uint32_t j = 0;
    std::vector<JS::Any> items;
    for (uint32_t i = 0; i < argCount; ++i) {
        items.push_back(args[JS::CONVERT::ToString(i)]);
    }
    while (!items.empty()) {
        JS::Any E = items.front();
        items.erase(items.begin());
        O->put(JS::CONVERT::ToString(j), E, true);
        j++;
    }
    O->put(u"length", JS::Any(len + argCount), true);
    return JS::Any(len + argCount);
}

JS::Any Array::indexOf(const JS::Any& thisArg, const JS::Any& args) {

    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    if (len == 0) {
        return JS::Any(-1);
    }
    int n = JS::COMPARE::Type(args[u"0"], JS::UNDEFINED) ? 0 : JS::CONVERT::ToInteger(args[u"0"]);
    if (n >= static_cast<int>(len)) {
        return JS::Any(-1);
    }
    int k = (n >= 0) ? n : std::max(static_cast<int>(len - std::abs(n)), 0);
    while (k < len) {
        if (O->hasProperty(JS::CONVERT::ToString(k))) {
            JS::Any elementK = O->get(JS::CONVERT::ToString(k));
            if (elementK.strictEq(args[u"0"])) {
                return JS::Any(k);
            }
        }
        k++;
    }
    return JS::Any(-1);
}

JS::Any Array::lastIndexOf(const JS::Any& thisArg, const JS::Any& args) {

    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    if (len == 0) {
        return JS::Any(-1);
    }
    int n =
        JS::COMPARE::Type(args[u"0"], JS::UNDEFINED) ? static_cast<int>(len - 1) : JS::CONVERT::ToInteger(args[u"0"]);
    int k = (n >= 0) ? std::min(n, static_cast<int>(len - 1)) : static_cast<int>(len - std::abs(n));
    while (k >= 0) {
        if (O->hasProperty(JS::CONVERT::ToString(k))) {
            JS::Any elementK = O->get(JS::CONVERT::ToString(k));
            if (elementK.strictEq(args[u"0"])) {
                return JS::Any(k);
            }
        }
        k--;
    }
    return JS::Any(-1);
}

JS::Any Array::every(const JS::Any& thisArg, const JS::Any& args) {

    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    if (!JS::IS::Callable(args[u"0"])) {
        throw std::runtime_error("TypeError: callback function is not callable");
    }
    std::shared_ptr<JS::InternalObject> callbackFn =
        std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    uint32_t k = 0;
    while (k < len) {
        std::u16string Pk = JS::CONVERT::ToString(k);
        if (O->hasProperty(Pk)) {
            JS::Any kValue = O->get(Pk);
            JS::Any testResult = callbackFn->call_function(
                thisArg, JS::Arguments::CreateArgumentsObject({kValue, JS::Any(k), JS::Any(O)}));
            if (!JS::CONVERT::ToBoolean(testResult)) {
                return JS::Any(false);
            }
        }
        k++;
    }
    return JS::Any(true);
}

JS::Any Array::some(const JS::Any& thisArg, const JS::Any& args) {

    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    if (!JS::IS::Callable(args[u"0"])) {
        throw std::runtime_error("TypeError: callback function is not callable");
    }
    std::shared_ptr<JS::InternalObject> callbackFn =
        std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    uint32_t k = 0;
    while (k < len) {
        std::u16string Pk = JS::CONVERT::ToString(k);
        if (O->hasProperty(Pk)) {
            JS::Any kValue = O->get(Pk);
            JS::Any testResult = callbackFn->call_function(
                thisArg, JS::Arguments::CreateArgumentsObject({kValue, JS::Any(k), JS::Any(O)}));
            if (JS::CONVERT::ToBoolean(testResult)) {
                return JS::Any(true);
            }
        }
        k++;
    }
    return JS::Any(false);
}

JS::Any Array::forEach(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    if (!JS::IS::Callable(args[u"0"])) {
        throw std::runtime_error("TypeError: callback function is not callable");
    }
    std::shared_ptr<JS::InternalObject> callbackFn =
        std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    uint32_t k = 0;
    while (k < len) {
        std::u16string Pk = JS::CONVERT::ToString(k);
        if (O->hasProperty(Pk)) {
            JS::Any kValue = O->get(Pk);
            callbackFn->call_function(thisArg, JS::Arguments::CreateArgumentsObject({kValue, JS::Any(k), JS::Any(O)}));
        }
        k++;
    }
    return {};
}

JS::Any Array::map(const JS::Any& thisArg, const JS::Any& args) {

    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    if (!JS::IS::Callable(args[u"0"])) {
        throw std::runtime_error("TypeError: callback function is not callable");
    }
    std::shared_ptr<JS::InternalObject> callbackFn =
        std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    std::shared_ptr<JS::InternalObject> A = std::make_shared<JS::Array>();
    uint32_t k = 0;
    while (k < len) {
        std::u16string Pk = JS::CONVERT::ToString(k);
        if (O->hasProperty(Pk)) {
            JS::Any kValue = O->get(Pk);
            JS::Any mappedValue = callbackFn->call_function(
                thisArg, JS::Arguments::CreateArgumentsObject({kValue, JS::Any(k), JS::Any(O)}));
            A->defineOwnProperty(Pk, JS::DataDescriptor{mappedValue, true, true, true}, false);
        }
        k++;
    }
    return JS::Any(A);
}

JS::Any Array::filter(const JS::Any& thisArg, const JS::Any& args) {

    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    if (!JS::IS::Callable(args[u"0"])) {
        throw std::runtime_error("TypeError: callback function is not callable");
    }
    std::shared_ptr<JS::InternalObject> callbackFn =
        std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    std::shared_ptr<JS::InternalObject> A = std::make_shared<JS::Array>();
    uint32_t k = 0;
    uint32_t to = 0;
    while (k < len) {
        std::u16string Pk = JS::CONVERT::ToString(k);
        if (O->hasProperty(Pk)) {
            JS::Any kValue = O->get(Pk);
            JS::Any selected = callbackFn->call_function(
                thisArg, JS::Arguments::CreateArgumentsObject({kValue, JS::Any(k), JS::Any(O)}));
            if (JS::CONVERT::ToBoolean(selected)) {
                A->defineOwnProperty(JS::CONVERT::ToString(to), JS::DataDescriptor{kValue, true, true, true}, false);
                to++;
            }
        }
        k++;
    }
    return JS::Any(A);
}

JS::Any Array::reduce(const JS::Any& thisArg, const JS::Any& args) {

    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    if (!JS::IS::Callable(args[u"0"])) {
        throw std::runtime_error("TypeError: callback function is not callable");
    }
    std::shared_ptr<JS::InternalObject> callbackFn =
        std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    JS::Any initialValue = args[u"1"];
    uint32_t k = 0;
    JS::Any accumulator;
    if (!JS::COMPARE::Type(initialValue, JS::UNDEFINED)) {
        accumulator = initialValue;
    } else {
        bool kPresent = false;
        while (!kPresent && k < len) {
            std::u16string Pk = JS::CONVERT::ToString(k);
            kPresent = O->hasProperty(Pk);
            if (kPresent) {
                accumulator = O->get(Pk);
            }
            k++;
        }
        if (!kPresent) {
            throw std::runtime_error("TypeError: reduce called on empty array with no initial value");
        }
    }
    while (k < len) {
        std::u16string Pk = JS::CONVERT::ToString(k);
        if (O->hasProperty(Pk)) {
            JS::Any kValue = O->get(Pk);
            accumulator = callbackFn->call_function(
                JS::Any(), JS::Arguments::CreateArgumentsObject({accumulator, kValue, JS::Any(k), JS::Any(O)}));
        }
        k++;
    }
    return accumulator;
}

JS::Any Array::reduceRight(const JS::Any& thisArg, const JS::Any& args) {
    std::shared_ptr<JS::InternalObject> O = JS::CONVERT::ToObject(thisArg);
    uint32_t len = JS::CONVERT::ToUint32(O->get(u"length"));
    if (!JS::IS::Callable(args[u"0"])) {
        throw std::runtime_error("TypeError: callback function is not callable");
    }
    std::shared_ptr<JS::InternalObject> callbackFn =
        std::get<std::shared_ptr<JS::InternalObject>>(args[u"0"].getValue());
    JS::Any initialValue = args[u"1"];
    int k = static_cast<int>(len) - 1;
    JS::Any accumulator;
    if (!JS::COMPARE::Type(initialValue, JS::UNDEFINED)) {
        accumulator = initialValue;
    } else {
        bool kPresent = false;
        while (!kPresent && k >= 0) {
            std::u16string Pk = JS::CONVERT::ToString(k);
            kPresent = O->hasProperty(Pk);
            if (kPresent) {
                accumulator = O->get(Pk);
            }
            k--;
        }
        if (!kPresent) {
            throw std::runtime_error("TypeError: reduceRight called on empty array with no initial value");
        }
    }
    while (k >= 0) {
        std::u16string Pk = JS::CONVERT::ToString(k);
        if (O->hasProperty(Pk)) {
            JS::Any kValue = O->get(Pk);
            accumulator = callbackFn->call_function(
                JS::Any(), JS::Arguments::CreateArgumentsObject({accumulator, kValue, JS::Any(k), JS::Any(O)}));
        }
        k--;
    }
    return accumulator;
}

} // namespace JS