#include <iostream>
#include <fstream>
#include "src/Lexer.hpp"
#include "src/Program.hpp"
#include "src/Options.hpp"

std::string read_all(const std::string &filename)
{
    std::string content;
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file, file need to be the second arguments !" << std::endl;
        exit(1);
    }

    while (inputFile.good()) {
        std::string line;
        std::getline(inputFile, line);
        content += line + "\n";
    }
    inputFile.close();
    return content;
}

int main(int argc, char **argv, char **env) {
    Options options(argc, argv, env);
    try {
        options.parse();
    } catch (const std::runtime_error& e) {
        std::cerr << "JS_CMP: " << e.what() << std::endl;
        options.printUsage();
        exit(1);
    }

    try {
        std::string content = read_all(options.getFilename());
        Lexer::Lexer lexer(content);
        std::vector<Lexer::Token> tokens = lexer.tokenize();

        Lexer::Program program(tokens);
        program.parse();
        if (options.getFlags() & OPTION_FLAG_PREPROCESS) {
            std::cout << program << std::endl;
        } else {
            std::string inputFilename = options.getFilename() + std::string(".cpp");
            std::ofstream outputFile(inputFilename);
            outputFile << program;
            outputFile.close();
            std::cout << "Compiler Found: " << options.getCompiler() << std::endl;
            std::cout << "Compiling " << options.getFilename() << " to " << options.getOutputFilename() << std::endl;
            std::string command = options.getCompiler() + (
                !options.getCompilerArgs().empty() ?
                    std::string(" ") + options.getCompilerArgs() :
                    std::string(" -Ofast ")
            ) + inputFilename + std::string(" -o ") + options.getOutputFilename() + std::string(" -Iincludes -L./ -lJS_CMP");
            std::cout << "Command: " << command << std::endl;
            std::system(command.c_str());
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
