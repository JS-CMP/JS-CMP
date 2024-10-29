#include "Builder.hpp"

Builder::Builder(const Options &options)
    : options(options)
{
}

void Builder::build()
{
    std::string content = read_all(this->options.getFilename());
    Lexer::Lexer lexer(content);
    std::vector<Lexer::Token> tokens = lexer.tokenize();

    Lexer::Program program(tokens);
    program.parse();
    if (this->options.getFlags() & OPTION_FLAG_PREPROCESS) {
        std::cout << program << std::endl;
        return;
    }
    std::string inputFilename = this->options.getFilename() + std::string(".cpp");
    std::ofstream outputFile(inputFilename);
    outputFile << program;
    outputFile.close();

    std::cout << "Compiler Found: " << this->options.getCompiler() << std::endl;
    std::cout << "Compiling " << this->options.getFilename() << " to " << this->options.getOutputFilename() << std::endl;
    compiling(inputFilename);
}

void Builder::compiling(const std::string &inputFilename) const
{
    std::string customArgs = this->options.getCompilerArgs().empty() ?
        std::string(" -Ofast -std=c++23 ") :
        std::string(" -Ofast -std=c++23 ") + this->options.getCompilerArgs();
    std::string compiler = this->options.getCompiler();
    std::string outputFilename = options.getOutputFilename();
    std::string command = compiler + customArgs + inputFilename + std::string(" -o ") + outputFilename + std::string(" -Iincludes -L./ -ljscmp");
    system(command.c_str());
}

std::string Builder::read_all(const std::string &filename)
{

    std::string content;
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        throw std::runtime_error("File not found: " + filename);
    }

    while (inputFile.good()) {
        std::string line;
        std::getline(inputFile, line);
        content += line + "\n";
    }
    inputFile.close();
    return content;
}
