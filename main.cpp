#include <iostream>
#include <fstream>
#include "src/Lexer.hpp"
#include "src/Program.hpp"

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

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Not enough arguments provided." << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    bool isPreprocessor = false;
    std::string outputFilename;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h") {
            std::cout << "Usage: " << argv[0] << "filename [options]" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "  -E          Preprocess only; do not compile" << std::endl;
            std::cout << "  -o <file>   Place the output into <file>" << std::endl;
            return 0;
        }
        if (arg == "-E") {
            isPreprocessor = true;
        } else if (arg == "-o") {
            if (i + 1 < argc) {
                outputFilename = argv[++i];
            } else {
                    std::cerr << "-o option requires an argument." << std::endl;
                return 1;
            }
        }
    }
    try {
        std::string content = read_all(filename);
        Lexer::Lexer lexer(content);
        std::vector<Lexer::Token> tokens = lexer.tokenize();

        Lexer::Program program(tokens);
        program.parse();
        if (isPreprocessor) {
            std::cout << program << std::endl;
        } else {
            if (outputFilename.empty()) {
                outputFilename = "a.out";
            }
            std::string inputFilename = filename + ".cpp";
            std::ofstream outputFile(inputFilename);
            outputFile << program;
            outputFile.close();
            #ifdef _WIN64
            throw std::runtime_error("Windows 64-bit is not supported.");
            #elif _WIN32
            throw std::runtime_error("Windows 32-bit is not supported.");
            #elif __APPLE__
            system(("clang++ -g -Ofast -std=c++17 -o " + outputFilename + " " + inputFilename + " -Iincludes -L./ -lJS_CMP 2>/dev/null; if [ $? -ne 0 ]; then echo \"the JavaScript code contain a feature that is not yet implemented.\"; fi").c_str());
            #elif __linux
            system(("g++ -g -Ofast -o " + outputFilename + " " + inputFilename +
                " -Iincludes -L./ -lJS_CMP").c_str());
            #endif
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
