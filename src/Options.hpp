#ifndef OPTIONS_HPP
#define OPTIONS_HPP
#include <boost/program_options.hpp>
#include <iostream>
#include <filesystem>
#include <list>
#include <optional>
#include <numeric>

namespace po = boost::program_options;


typedef enum {
    OPTION_FLAG_PREPROCESS = 0x1,
} option_flag_t;


static const std::array<const char *, 4> commonCompilers = {"g++", "clang++", "cl"};

class Options {
public:
    Options(int argc, char * * argv, char * * env);

    void parse();
    void printUsage();
    static void printVersion();

    ~Options() = default;

    [[nodiscard]] std::string getFilename() const {
        return this->filename;
    }

    [[nodiscard]] std::string getOutputFilename() const {
        return this->outputFilename;
    }

    [[nodiscard]] uint32_t getFlags() const {
        return this->flags;
    }

    [[nodiscard]] std::string getCompiler() const {
        return this->compiler;
    }

    [[nodiscard]] std::string getCompilerArgs() const {
        return this->compilerArgs;
    }

private:
    int extractCompilerOptions();
    std::optional<std::string> findCompiler();

    uint32_t flags = 0;

    std::string filename;
    std::string outputFilename;
    std::string compiler;
    std::string compilerArgs;

    po::options_description desc_argv;
    po::variables_map vm_argv;
    int argc;
    char * * argv;
};

#endif //OPTIONS_HPP