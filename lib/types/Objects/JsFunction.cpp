//#include "types/Objects/JsFunction.hpp"
#include "../../../includes/types/Objects/JsFunction.hpp" // test compile

namespace JS {
    Function::Function(FunctionType function) : function(function) {}

    bool Function::isCallable() const {
        return true;
    }
}
