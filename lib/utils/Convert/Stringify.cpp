#include "utils/Convert.hpp"
#include "utils/Is.hpp"
#include "utils/Compare.hpp"
#include "internals/Object.hpp"

std::u16string JS::CONVERT::Stringify(const JS::Any& any) {
    switch (any.getValue().index()) {
        case NUMBER:
            return JS::CONVERT::ToString(std::get<double>(any.getValue()));
        case STRING:
            return ToString(std::get<Rope>(any.getValue()));
        case BOOLEAN:
            return ToString(std::get<bool>(any.getValue()));
        case UNDEFINED:
            return ToString(JS::Undefined());
        case NULL_TYPE:
            return ToString(JS::Null());
        default:
            auto io = std::get<std::shared_ptr<JS::InternalObject>>(any.getValue());
            if (io->class_name == u"Object") {
                return ObjectToString(io);
            } else if (io->class_name == u"Array") {
                return ArrayToString(io);
            } else if (io->class_name == u"Function") {
                return FunctionToString(io);
            } else {
                return u"[Object " + io->class_name + u"]";
            }
    }
}
