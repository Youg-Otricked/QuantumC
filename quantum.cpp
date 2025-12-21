#include <iostream>
#include <string>
#include "./tokenizer.h"
#include <algorithm>
#include <iterator>
int main() {
    while (true) {
        std::cout << "Quantum C: ";
        std::string code;
        if (!std::getline(std::cin, code)) break; 
        if (code.empty()) continue;

        tkz::Mer ast = tkz::run("<stdin>", code);
        if (ast.tokens.error != nullptr) { 
            std::cout << "\n" << ast.tokens.error->as_string() << "\n";
            continue;
        }
        if (ast.ast.error != nullptr) {
            std::cout << '\n' << ast.ast.error->as_string() << '\n';
            continue;
        }
        if (ast.tokens.Tkns.empty()) {
            std::cout << "\nAll whitespace" << '\n';
            continue;
        }
        if (!ast.res.empty()) {
            std::cout << '\n' << ast.res << '\n';
        } else if (ast.ast.AST.has_value()) {
            tkz::AnyNode& node = *ast.ast.AST.value(); 
            std::string result = tkz::printAny(node);
            std::cout << '\n' << result << '\n';
        } else {
            std::cout << '\n' << "Honestly, what the heck did you type to produce absolutly no errors or output";
        }
    }
    return 0;
}