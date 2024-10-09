#include "Include.hpp"

#include <utility>

std::ostream &operator<<(std::ostream &os, const Include &include)
{
    os << "#include \"" << include.path << "\"" << std::endl;
    return os;
}

Include::Include(std::string path) : path(std::move(path))
{
}
