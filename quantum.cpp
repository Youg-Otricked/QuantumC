#include <iostream>
#include <string>
#include "./tokenizer.h"
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>

std::string read_file(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
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
            std::cout << R"(
          _____ ___  _  _   
         / ____|__ \| || |  
        | |       ) | || |_ 
        | |      / /|__   _|
        | |____ / /_   | |  
         \_____|____|  |_|  
        Quantum C (C⁴) v3.2

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
        )" << std::endl;
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
        } else if (arg == "--help" || arg == "-h") {
        std::cout << R"(
Quantum C Interpreter v3.2

Usage: qc [options] <file>

Options:
  -v, --version       Show version information
  -h, --help          Show this help message
  -d, --demo          Run the demo file (syntax.qc)
  -lt, --loose-types  Enable loose type checking
  -nc, --no-context   Disable context tracking
  -a, --ast           Print the AST (Abstract Syntax Tree)
  -tkn, --tokens      Print the token stream
  -t, --time          Show compilation time
In Code:
  When writing code, you can use these same options as inline keywords at the top of your file:
  // @no-context == -nc
  // @looser-types == -lt
  // @print-ast == -a
  // @print-tokens == -tkn
  // @show-time == -t
  // @quiet == -q
  quiet silences non debug output
Examples:
  qc main.qc          Run main.qc
  qc -d               Run the demo
  qc -v               Show version
  qc --ast test.qc    Show AST for test.qc
        )" << std::endl;
        return 0;
    } else {
            filename = arg;
        }
    }
    
    if (filename.empty()) {
        // REPL mode
        std::cout << "Quantum C REPL v3.2" << std::endl;
        if (!config.use_context) {
            std::cout << "(Context disabled)" << std::endl;
        }
        
        while (true) {
            std::cout << "qc> ";
            std::string line;
            std::getline(std::cin, line);
            
            if (line == "exit") break;
            
            auto result = tkz::run("<stdin>", line, config); 
            
            if (result.ast.error) {
                std::cout << result.ast.error->as_string() << std::endl;
            } else {
                if (!config.quiet_mode) { 
                    std::cout << result.res << std::endl;
                }
            }
        }
    } else {
        // File mode
        std::string code = read_file(filename);
        auto result = tkz::run(filename, code, config);
        
        if (result.ast.error) {
            std::cout << result.ast.error->as_string() << std::endl;
            return 1;
        }
        
        if (!config.quiet_mode) {  
            std::cout << result.res << std::endl;
        }
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
