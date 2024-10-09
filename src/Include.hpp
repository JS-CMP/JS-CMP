#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <string>
#include <iostream>

class Include {
public:
    Include(std::string path);

    std::string path;

    friend std::ostream &operator<<(std::ostream &os, const Include &include);
};

#endif //INCLUDE_HPP
