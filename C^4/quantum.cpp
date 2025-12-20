#include <iostream>
#include <string>
#include "./tokenizer.h"
int main() {
    while (true) {
        std::cout << "Quantum C: ";
        std::string code;
        if (!std::getline(std::cin, code)) break; 
        if (code.empty()) continue;
        tkz::Ler tokens = tkz::run(code);
        if (tokens.Tkns.empty() && tokens.error != nullptr) {
            std::cout << "\n" << tokens.error->as_string() << '\n';
        } else if(tokens.Tkns.empty()) {
            std::cout << "\nERROR\n"; 
        } else {
            std::cout << "\n[";
            for (tkz::Token token : tokens.Tkns) {
                std::cout << token.print() << ", ";
            }
            std::cout << "]\n";
        }
    }
    return 0;
}