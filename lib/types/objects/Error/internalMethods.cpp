#include "internals/Object.hpp"
#include "types/objects/Error/JsError.hpp"
#include "utils/Convert.hpp"
#include "utils/Is.hpp"

#include <utils/Compare.hpp>
#include <types/objects/Function/JsFunction.hpp>

std::shared_ptr<JS::Function> JS::Error::getConstructor() {
    auto prototype = Function::getPrototypeProperties();
    static auto constructor = JS::InternalObject::create<JS::Function>( [] (const JS::Any& thisArg, const JS::Any& args) -> JS::Any {
	return JS::Any(JS::InternalObject::create<JS::Error>(args[u"0"]));
    }, 1, ERROR_CLASS_NAME, prototype);

    constructor->class_name = ERROR_CLASS_NAME;
    constructor->extensible = true;
    constructor->prototype = prototype;
    constructor->properties = std::make_shared<JS::Properties>(JS::Properties{
    	{u"length", JS::DataDescriptor{JS::Any(1), false, false, false}},
    	{u"name", JS::DataDescriptor{JS::Any(ERROR_CLASS_NAME), false, false, false}},
        {u"prototype", JS::DataDescriptor(JS::Any(Error::getPrototypeProperties(constructor)), false, false, false)}
	});
    return constructor;
}
