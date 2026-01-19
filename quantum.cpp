#include <iostream>
#include <string>
#include "./tokenizer.h"
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <format>
#include <ranges>
#include <thread>
#include <chrono>
#include <atomic>
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

#include <random>
bool slow = false;
void slow_print(const std::string& text, const std::string& color = "\033[0m", int min_delay_ms = 100, int max_delay_ms = 450) {
    if (!slow) {
        std::cout << color << text << RESET;
    } else {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> chunk_size_dist(1, 5);
        std::uniform_int_distribution<int> delay_dist(min_delay_ms, max_delay_ms);

        size_t i = 0;
        while (i < text.size()) {
            int chunk_size = chunk_size_dist(rng);
            if (i + chunk_size > text.size()) chunk_size = text.size() - i;

            std::cout << color << text.substr(i, chunk_size) << "\033[0m" << std::flush;

            i += chunk_size;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_dist(rng)));
        }
        std::cout << std::endl;
    }
}

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
std::atomic<bool> running{true};
    void spinner() {
        std::vector<char> frames{'-', '\\', '|', '/'};
        size_t i = 0;
        while (running) {
            std::cout << "\r" << frames[i % frames.size()] << " Running..." << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            i++;
        }
        std::cout << "\r" << std::endl; // clear line
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
            std::ifstream file("logo.txt");
            if (file.is_open()) {
                std::string line;
                while (std::getline(file, line)) {
                    std::cout << line << "\n";
                }
                file.close();
            }
            std::cout << CYAN << R"( 
    ,o888888o.     8 8888      88        .8.          b.             8 8888888 8888888888 8 8888      88        ,8.       ,8.                    ,o88888o.    
 . 8888     `88.   8 8888      88       .888.         888o.          8       8 8888       8 8888      88       ,888.     ,888.                  888     `88.  
,8 8888       `8b  8 8888      88      :88888.        Y88888o.       8       8 8888       8 8888      88      .`8888.   .`8888.              ,8 888       `8. 
88 8888        `8b 8 8888      88     . `88888.       .`Y888888o.    8       8 8888       8 8888      88     ,8.`8888. ,8.`8888.             88 888           
88 8888         88 8 8888      88    .8. `88888.      8o. `Y888888o. 8       8 8888       8 8888      88    ,8'8.`8888,8^8.`8888.            88 888           
88 8888     `8. 88 8 8888      88   .8`8. `88888.     8`Y8o. `Y88888o8       8 8888       8 8888      88   ,8' `8.`8888' `8.`8888.           88 888           
88 8888      `8,8P 8 8888      88  .8' `8. `88888.    8   `Y8o. `Y8888       8 8888       8 8888      88  ,8'   `8.`88'   `8.`8888.          88 888           
`8 8888       ;8P  ` 8888     ,8P .8'   `8. `88888.   8      `Y8o. `Y8       8 8888       ` 8888     ,8P ,8'     `8.`'     `8.`8888.         `8 888       .8' 
 ` 8888     ,88'8.   8888   ,d8P .888888888. `88888.  8         `Y8o.`       8 8888         8888   ,d8P ,8'       `8        `8.`8888.           888     ,88'  
    `8888888P'  `8.   `Y88888P' .8'       `8. `88888. 8            `Yo       8 8888          `Y88888P' ,8'         `         `8.`8888.          `888888P'  
        Quantum C (C⁴) v7.0.0

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
        } else if (arg == "--bst" || arg == "-b") {
            config.bst = true;
        } else if (arg == "--suspense" || arg == "-s") {
            slow = true;
        } else if (arg == "--help" || arg == "-h") {
        std::cout << GREEN << R"(
Quantum C Interpreter v7.0.0

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
  -s, --suspense      Slowly print the Error codes.
  -b, --bst           Bst style ast (warning, very top heavy) msut be used in congunction with -a/ast
In Code:
  When writing code, you can use these same options as inline keywords at the top of your file:
  // @no-context == -nc
  // @looser-types == -lt
  // @print-ast == -a
  // @print-tokens == -tkn
  // @show-time == -t
  // @quiet == -q
  // @raw-ast == -r
  // @bst-ast == -b
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
        std::vector<std::string> history;
        std::cout << GREEN << "Quantum C REPL v7.0.0" << RESET << std::endl;
        std::cout << CYAN << "Type !@run to execute, !@clear to discard buffer, exit to quit" << RESET << std::endl;
        if (!config.use_context) {
            std::cout << CYAN << "(Context disabled)" << RESET << std::endl;
        }
        
        std::string code_buffer;

        while (true) {
            std::cout << BOLD << BLUE << (code_buffer.empty() ? "qc" : "-") << "[" << code_buffer.size() << " chars]>" << RESET;
            std::string line;
            std::getline(std::cin, line);

            if (line == "exit") break;

            if (line == "!@run") {
                std::thread spin_thread(spinner);
                running = true;
                history.push_back(code_buffer);
                auto result = tkz::run("<stdin>", code_buffer, config);
                running = false;
                spin_thread.join();
                bool has_fatal = false;
                bool has_warnings = false;

                slow_print("=== Diagnostics ===\n", BOLD);

                if (!result.errors.empty()) {
                    for (const auto& diag : result.errors) {
                        std::string color;

                        if (diag.level == "Warning") {
                            color = YELLOW;
                            has_warnings = true;
                        } else if (diag.level == "Error") {
                            color = MAGENTA;
                            has_fatal = true;
                        } else if (diag.level == "Severe") {
                            color = RED;
                            has_fatal = true;
                        } else if (diag.level == "Fatal") {
                            color = RED;
                            has_fatal = true;
                        }

                        slow_print(const_cast<tkz::RTError&>(diag.error).as_string() + "\n", color);
                    }
                }
                if (result.ast.error) {
                    slow_print(result.ast.error->as_string() + "\n", RED);
                    has_fatal = true;
                }

                slow_print("==============\n", BOLD);
                slow_print("= Error Code =\n", BOLD);

                if (has_fatal) {
                    slow_print("Program exited with code 1\n", RED);
                    slow_print("==============\n", BOLD);
                    code_buffer.clear();
                    return 1;
                } else if (has_warnings) {
                    slow_print(result.res + "\n", YELLOW);
                } else {
                    slow_print(result.res + "\n", GREEN);
                }

                slow_print("==============\n", BOLD);
                code_buffer.clear();
            } else if (line == "!@showbuffer") {
                std::istringstream iss(code_buffer);
                std::string buf_line;
                size_t lnum = 1;
                while (std::getline(iss, buf_line)) {
                    std::cout << lnum++ << ": " << buf_line << "\n";
                }
                continue;
            } else if (line == "!@history") {
                for (size_t i = 0; i < history.size(); ++i)
                    std::cout << i+1 << ": " << history[i] << "\n";
                continue;
            } else if (line == "!@last") {
                if (!history.empty())
                    std::cout << history.back() << "\n";
                else
                    std::cout << "[No previous input]\n";
                continue;
            } else if (line == "!@help") {
                std::cout << GREEN 
                        << "REPL Commands:\n"
                        << "  !@run       → Execute current buffer\n"
                        << "  !@clear     → Clear buffer\n"
                        << "  !@showbuffer→ Show buffer with line numbers\n"
                        << "  exit        → Quit REPL\n"
                        << RESET;
                continue;
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

        bool has_fatal = false;
        bool has_warnings = false;

        slow_print("=== Diagnostics ===\n", BOLD);

        for (const auto& diag : result.errors) {
            std::string color;

            if (diag.level == "Warning") {
                color = YELLOW;
                has_warnings = true;
            } else if (diag.level == "Error") {
                color = MAGENTA;
                has_fatal = true;
            } else if (diag.level == "Severe") {
                color = RED;
                has_fatal = true;
            } else if (diag.level == "Fatal") {
                color = RED;
                has_fatal = true;
            }

            slow_print(const_cast<tkz::RTError&>(diag.error).as_string() + "\n", color);
        }
        if (result.ast.error) {
            slow_print(result.ast.error->as_string() + "\n", RED);
            has_fatal = true;
        }

        slow_print("==============\n", BOLD);
        slow_print("= Error Code =\n", BOLD);

        if (has_fatal) {
            slow_print("Program exited with code 1\n", RED);
            slow_print("==============\n", BOLD);
            return 1;
        } else if (has_warnings) {
            slow_print(result.res + "\n", YELLOW);
        } else {
            slow_print(result.res + "\n", GREEN);
        }

        slow_print("==============\n", BOLD);

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
        
        auto result = tkz::run("<wasm>", code, tkz::RunConfig{true, false, false, false, true, false, false, false});
        
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
