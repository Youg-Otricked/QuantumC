#include <iostream>
#include <string>
#include "./tokenizer.h"
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <format>
#include <ranges>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#if defined(_WIN32) || defined(_WIN64)
    #include <print>
#endif
std::string read_file(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << YELLOW << "Error: Could not open file '" << filename << "'" << RESET <<  std::endl;
        exit(1);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
int main(int argc, char* argv[]) {
    tkz::RunConfig config;
    std::string filename = "";
    
    // Parse arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--no-context" || arg == "-nc") {
            config.use_context = false;
        } else if (arg == "--version" || arg == "-v") {
            std::cout << CYAN << R"(
          _____ ___  _  _   
         / ____|__ \| || |  
        | |       ) | || |_ 
        | |      / /|__   _|
        | |____ / /_   | |  
         \_____|____|  |_|  
        Quantum C (C⁴) v5.0.2

        The 4th Evolution of C
        More Powerful Than Explosives
        Now turing complete.
        Functions comming: NOW
        Beter syntax guide comming: NOW
        
        Now on a higher version than Geometry Dash
        Now officaly past version 1(byte)
        Features:
        ✓ C++ Performance -- without the 20 #includes
        ✓ C# Ergonomics  
        ✓ Rust Safety
        ✓ Quantum Booleans
        ✓ Multi-return
        ✓ Type Unions

        github.com/Youg-Otricked/QuantumC
        )" << RESET << std::endl;
            return 0;
        } else if (arg == "--loose-types" || arg == "-lt") {
            config.looser_types = true;
        } else if (arg == "--demo" || arg == "-d") {
            filename = "./syntax.qc";
        } else if (arg == "--ast" || arg == "-a") {
            config.print_ast = true;
        } else if (arg == "--quiet" || arg == "-q") {
            config.quiet_mode = true;
        } else if (arg == "--tokens" || arg == "-tkn") {
            config.print_tokens = true;
        } else if (arg == "--time" || arg == "-t") {
            config.show_time = true;
        } 
        else if (arg == "--raw" || arg == "-r") {
            config.raw = true;
        } else if (arg == "--help" || arg == "-h") {
        std::cout << GREEN << R"(
Quantum C Interpreter v5.0

Usage: ./qc [options] <file>

Options:
  -v, --version       Show version information
  -h, --help          Show this help message
  -d, --demo          Run the demo file (syntax.qc)
  -lt, --loose-types  Enable loose type checking
  -nc, --no-context   Disable context tracking
  -a, --ast           Print the AST (Abstract Syntax Tree)
  -tkn, --tokens      Print the token stream
  -t, --time          Show compilation time
  -r, --raw           Don't pretty print the AST. (must be used in congunction with -a/--ast)
In Code:
  When writing code, you can use these same options as inline keywords at the top of your file:
  // @no-context == -nc
  // @looser-types == -lt
  // @print-ast == -a
  // @print-tokens == -tkn
  // @show-time == -t
  // @quiet == -q
  // @raw-ast == -r
  quiet silences non debug output
Examples:
  qc main.qc          Run main.qc
  qc -d               Run the demo
  qc -v               Show version
  qc --ast test.qc    Show AST for test.qc
        )" << RESET << std::endl;
        return 0;
    } else {
            filename = arg;
        }
    }
    
    if (filename.empty()) {
        // REPL mode
        std::cout << GREEN << "Quantum C REPL v5.0.2" << RESET << std::endl;
        std::cout << CYAN << "Type !@run to execute, !@clear to discard buffer, exit to quit" << RESET << std::endl;
        if (!config.use_context) {
            std::cout << CYAN << "(Context disabled)" << RESET << std::endl;
        }
        
        std::string code_buffer;

        while (true) {
            std::cout << (code_buffer.empty() ? "qc" : "-") << "[" << code_buffer.size() << " lines]>";
            std::string line;
            std::getline(std::cin, line);

            if (line == "exit") break;

            if (line == "!@run") {
                auto result = tkz::run("<stdin>", code_buffer, config);

                std::cout << BOLD << "=== Output ===" << RESET << std::endl;
                if (result.ast.error) {
                    std::cout << RED << result.ast.error->as_string() << RESET << std::endl;
                } else {
                    if (!config.quiet_mode) std::cout << GREEN << result.res << RESET << std::endl;
                }
                std::cout << BOLD << "===============" << RESET << std::endl;
                code_buffer.clear();
            } else if (line == "!@clear") {
                code_buffer.clear();
                std::cout << YELLOW << "[Buffer cleared]" << RESET << std::endl;
            } else {
                code_buffer += line + "\n";
            }
        }

    } else {
        // File mode
        std::string code = read_file(filename);
        auto result = tkz::run(filename, code, config);
        std::cout << BOLD << "=== Output ===" << RESET << std::endl;
        if (result.ast.error) {
            std::cout << RED << result.ast.error->as_string() << RESET << std::endl;
            return 1;
        }
        
        if (!config.quiet_mode) {  
            std::cout << GREEN << result.res << RESET << std::endl;
        }
        std::cout << BOLD << "===============" << RESET << std::endl;
    }
    
    return 0;
}
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <sstream>

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    const char* run_quantum_code(const char* code) {
        static std::string output;
        output.clear();
        
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
        
        auto result = tkz::run("<wasm>", code, tkz::RunConfig{});
        
        if (result.ast.error) {
            output = result.ast.error->as_string();
        } else {
            output = buffer.str() + result.res;
        }
        
        std::cout.rdbuf(old);
        return output.c_str();
    }
}
#endif
