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
    bool use_context = true;
    std::string filename = "";
    
    // Parse arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--no-context" || arg == "-nc") {
            use_context = false;
        } else if (arg == "--version" || arg == "-v") {
            std::cout << R"(
   _____ ___  _  _   
  / ____|__ \| || |  
 | |       ) | || |_ 
 | |      / /|__   _|
 | |____ / /_   | |  
  \_____|____|  |_|  
        Quantum C (C⁴) v1.0

        The 4th Evolution of C
        More Powerful Than Explosives
        Now turing complete.
        Functions comming: NOW
        Beter syntax guide comming: SOON
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
        } else {
            filename = arg;
        }
    }
    
    if (filename.empty()) {
        // REPL mode
        std::cout << "Quantum C REPL v1.0" << std::endl;
        if (!use_context) {
            std::cout << "(Context disabled)" << std::endl;
        }
        
        while (true) {
            std::cout << "qc> ";
            std::string line;
            std::getline(std::cin, line);
            
            if (line == "exit") break;
            
            auto result = tkz::run("<stdin>", line, use_context);
            
            if (result.ast.error) {
                std::cout << result.ast.error->as_string() << std::endl;
            } else {
                std::cout << result.res;
            }
        }
    } else {
        // File mode
        std::string code = read_file(filename);
        auto result = tkz::run(filename, code, use_context);
        
        if (result.ast.error) {
            std::cout << result.ast.error->as_string() << std::endl;
            return 1;
        }
        
        std::cout << result.res;
    }
    
    return 0;
}