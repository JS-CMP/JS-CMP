#include "Options.hpp"

Options::Options(int argc, char **argv, char **env) : desc_argv("Allowed options"), compilerArgs()
{
   this->argc = argc;
   this->argv = argv;
   this->desc_argv.add_options()
      ("help,h", "produce help message")
      ("version,v", "print version information")
      ("preprocess,E", "preprocess only; do not compile")
      ("CXX,c", po::value <std::string>(), "specify the compiler to use")
      ("output,o", po::value <std::string>(), "place the output into <file>");

   this->argc = extractCompilerOptions();
   auto parsed = po::command_line_parser(argc, argv)
                 .options(this->desc_argv)
                 .allow_unregistered()
                 .run();
   po::store(parsed, this->vm_argv);
   po::notify(this->vm_argv);
}

void Options::parse()
{
   // Parse the command line options
   if (this->vm_argv.count("help"))
   {
      this->printUsage();
      std::exit(0);
   }
   if (this->vm_argv.count("version"))
   {
      Options::printVersion();
      std::exit(0);
   }
   if (this->argc < 2)
   {
      throw std::runtime_error("No input file.");
   }
   else if (!std::filesystem::exists(this->argv[1]))
   {
      throw std::runtime_error("File does not exist.");
   }
   this->filename = this->argv[1];
   if (this->vm_argv.count("preprocess"))
   {
      this->flags |= OPTION_FLAG_PREPROCESS;
   }
   if (this->vm_argv.count("output"))
   {
      this->outputFilename = this->vm_argv["output"].as <std::string>();
   }
   else
   {
      this->outputFilename = this->filename.substr(0, this->filename.find_last_of('.'));
   }

   // Parse the environment options
   // TODO: can be cached

   if (this->vm_argv.count("CXX"))
   {
      this->compiler = this->vm_argv["CXX"].as <std::string>();
   }
   else if (std::getenv("CXX") != nullptr)
   {
      this->compiler = std::getenv("CXX");
   }
   else
   {
      auto compiler = findCompiler();
      if (compiler.has_value())
      {
         this->compiler = compiler.value();
      }
      else
      {
         throw std::runtime_error("No compiler found. Compiler tested: " + std::accumulate(std::begin(commonCompilers), std::end(commonCompilers), std::string("")));
      }
   }
}

int Options::extractCompilerOptions()
{
   bool hasDoubleDash = false;
   int  nextArgc      = argc;
   for (int i = 1; i < argc; ++i)
   {
      std::string arg = argv[i];
      if (hasDoubleDash)
      {
         compilerArgs += arg + " ";
      }
      if (arg == "--")
      {
         hasDoubleDash = true;
         nextArgc      = i;
      }
   }
   return(nextArgc);
}

void Options::printUsage()
{
   std::cout << "Usage: js_cmp <file> [options]" << std::endl;
   this->desc_argv.print(std::cout);
   std::cout << "  -- <compiler options> Pass the remaining arguments to the compiler" << std::endl;
}

void Options::printVersion()
{
   std::cout << "JS_CMP version " << JS_CMP_VERSION << std::endl;
}

std::optional <std::string> Options::findCompiler()
{
   for (const auto&compiler : commonCompilers)
   {
      std::string compilerPath = std::string(compiler);
      if (std::system((compilerPath + std::string(
            #ifdef _WIN32
                          " --version >nul 2>&1"
            #else
                          " --version > /dev/null 2>&1"
            #endif
                          )).c_str()) == 0)
      {
         return(std::string(compiler));
      }
   }
   return(std::nullopt);
}
