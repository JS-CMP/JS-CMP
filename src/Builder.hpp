#ifndef BUILDER_HPP
#define BUILDER_HPP

#include "Options.hpp"
#include "Lexer.hpp"
#include "Program.hpp"
#include <fstream>
#include <iostream>

class Builder {
public:
    Builder(const Options &options);

    void build();

    //TODO: move it to an utils class
    static std::string read_all(const std::string &filename);

private:
    Options options;
    void compiling(const std::string &inputFilename) const;

};

#endif //BUILDER_HPP