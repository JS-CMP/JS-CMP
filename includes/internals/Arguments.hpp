#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include "types/Types.hpp"

namespace JS::Arguments {
    /**
     * @brief Creates an arguments object from a list of arguments, a function, and an environment.
     * @param args The list of arguments to create the arguments object from.
     * @param func The function that the arguments object is associated with. (unused if strict is true)
     * @param names The names of the arguments. (unused if strict is true)
     * @param env The environment of the function. (unused if strict is true)
     * @param strict Whether the arguments object is in strict mode. (default is true)
     * @return The arguments object created from the list of arguments.
     */
    JS::Any CreateArgumentsObject(const std::vector<JS::Any>& args,
                                         const std::shared_ptr<JS::InternalObject>& func = nullptr,
                                         const std::vector<std::string>& names = {},
                                         const std::shared_ptr<JS::InternalObject>& env = nullptr,
                                         bool strict = true);
} // namespace JS::Arguments
#endif //ARGUMENTS_HPP