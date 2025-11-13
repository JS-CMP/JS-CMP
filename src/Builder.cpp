#include "Builder.hpp"

Builder::Builder(const Options& options) : options(options) {}

void Builder::build() {
    std::string content = read_all(this->options.getFilename());
    Lexer::Lexer lexer(content);
    std::vector<Lexer::Token> tokens = lexer.tokenize();

    Lexer::AST::Parser parser(tokens);
    std::vector<Lexer::AST::Stmt::Ptr> ast;
    try {
        while (!parser.isAtEnd()) {
            auto stmt = parser.parseStatement();
            ast.push_back(std::move(stmt));
        }
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError: " << e.what() << "\033[0m\n";
        std::exit(1);
    }
    std::string program;
    try {
        Lexer::Opt::Optimizer optimizer(ast);
        program = optimizer.transpile();
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError: " << e.what() << "\033[0m\n";
        std::exit(1);
    }
    if (this->options.getFlags() & OPTION_FLAG_PREPROCESS) {
        std::cout << program << '\n';
        return;
    }
    std::string inputFilename = this->options.getFilename() + std::string(".cpp");
    std::ofstream outputFile(inputFilename);
    outputFile << program;
    outputFile.close();

    std::cout << "Compiler Found: " << this->options.getCompiler() << '\n';
    std::cout << "Compiling " << this->options.getFilename() << " to " << this->options.getOutputFilename() << '\n';
    compiling(inputFilename);
}

void Builder::compiling(const std::string& inputFilename) const {
    std::string customArgs = this->options.getCompilerArgs().empty() ? std::string(" -w -O3 -std=c++20 ") // -w to disable warnings, -O3 for optimization, -std=c++20 for C++20 standard
                                                                     : std::string(" -w -O3 -std=c++20 ") + this->options.getCompilerArgs();
    std::string compiler = this->options.getCompiler();
    std::string outputFilename = options.getOutputFilename();
    std::string command = compiler + customArgs + inputFilename + std::string(" -o ") + outputFilename +
                          std::string(" -Iincludes -Isubmodules/SyntaxSmith/includes -L./ -ljscmp $(pkg-config --libs "
                                      "icu-uc icu-i18n) -DBOOST_REGEX_NO_LIB");

    system(command.c_str());
}

std::string Builder::read_all(const std::string& filename) {

    std::string content;
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        throw std::runtime_error("File not found: " + filename);
    }

    while (inputFile.good()) {
        std::string line;
        std::getline(inputFile, line);
        content += line + '\n';
    }
    inputFile.close();
    return content;
}