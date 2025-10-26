#ifndef BUILDER_HPP
#define BUILDER_HPP

#include "AST/Parser.hpp"
#include "Optimization/Optimizer.hpp"
#include "Options.hpp"
#include "Tokenizer/Lexer.hpp"

#include <fstream>
#include <iostream>

/**
 * @class Builder
 * @brief Responsible for compiling and building programs based on specified options.
 */
class Builder {
public:
    /**
     * @brief Constructs a Builder with the specified options.
     * @param options The options to control the build process.
     */
    explicit Builder(const Options& options);

    /**
     * @brief Initiates the build process using configured options.
     */
    void build();

    /**
     * @brief Reads the entire content of a file into a string.
     * @param filename The name of the file to read.
     * @return The complete content of the file as a string.
     * @note This static method could be moved to a utility class for reusability.
     */
    static std::string read_all(const std::string& filename);

private:
    Options options; /**< Configuration options for the build process. */

    /**
     * @brief Performs the compilation on the given input file.
     * @param inputFilename The name of the input file to compile.
     */
    void compiling(const std::string& inputFilename) const;
};

#endif // BUILDER_HPP