#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <boost/program_options.hpp>
#include <filesystem>
#include <iostream>
#include <list>
#include <numeric>
#include <optional>
#include <array>

namespace po = boost::program_options;

/**
 * @brief Enum defining various option flags.
 */
typedef enum {
    OPTION_FLAG_PREPROCESS = 0x1, /**< Flag for preprocessing option. */
} option_flag_t;

/** @brief Commonly used compilers. */
static const std::array<const char*, 4> commonCompilers = {"g++", "clang++", "cl"};

/**
 * @class Options
 * @brief Handles parsing and storage of command-line options and settings.
 */
class Options {
public:
    /**
     * @brief Constructs the Options object from command-line arguments and environment variables.
     * @param argc Argument count.
     * @param argv Argument vector.
     * @param env Environment variables.
     */
    Options(int argc, char** argv, char** env);

    /** @brief Parses command-line arguments and sets options */
    void parse();

    /** @brief Prints usage information for the program. */
    void printUsage();

    /** @brief Prints the version information of the program. */
    static void printVersion();

    /** @brief Default destructor. */
    ~Options() = default;

    /**
     * @brief Gets the filename option.
     * @return The specified filename.
     */
    [[nodiscard]] std::string getFilename() const { return this->filename; }

    /**
     * @brief Gets the output filename option.
     * @return The specified output filename.
     */
    [[nodiscard]] std::string getOutputFilename() const { return this->outputFilename; }

    /**
     * @brief Gets the option flags.
     * @return The option flags.
     */
    [[nodiscard]] uint32_t getFlags() const { return this->flags; }

    /**
     * @brief Gets the compiler option.
     * @return The specified compiler.
     */
    [[nodiscard]] std::string getCompiler() const { return this->compiler; }

    /**
     * @brief Gets the compiler arguments option.
     * @return The specified compiler arguments.
     */
    [[nodiscard]] std::string getCompilerArgs() const { return this->compilerArgs; }

private:
    /**
     * @brief Extracts compiler-related options from the arguments.
     * @return Status code.
     */
    int extractCompilerOptions();

    /**
     * @brief Finds a compiler from the common compilers list.
     * @return An optional string that holds the compiler path if found.
     */
    std::optional<std::string> findCompiler();

    uint32_t flags = 0; /**< Flags set for various options. */

    std::string filename;        /**< Filename specified in the options. */
    std::string outputFilename;  /**< Output filename specified in the options. */
    std::string compiler;        /**< Compiler specified in the options. */
    std::string compilerArgs;    /**< Compiler arguments specified in the options. */

    po::options_description desc_argv; /**< Options description for argument parsing. */
    po::variables_map vm_argv;         /**< Variable map for storing parsed arguments. */
    int argc; /**< Argument count. */
    char** argv; /**< Argument vector. */
};

#endif // OPTIONS_HPP