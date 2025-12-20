//////////////////////////////////////////////////////////////////////////////////////////////
// TOKENS ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
#include "tokenizer.h"
#include <string>
#include <format>
#include <iostream>
#include <list>
#include <memory>
bool isCharInSet(char c, const std::string &charSet) {
    return charSet.find(c) != std::string::npos;
}
namespace tkz {
    
    Token::Token(TokenType t, std::string val) {
        this->type = t;
        this->value = val;
    }
    std::string Token::print() const {
        if (this->value.empty()) {
            return std::format("{}", static_cast<int>(this->type));
        } else {
            return std::format("{}:{}", static_cast<int>(this->type), this->value);
        }
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// ERRORS ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    Error::Error(std::string err, std::string details) {
        this->details = details;
        this->error_name = err;
    }
    std::string Error::as_string() {
        return std::format("{}: {}", this->error_name, this->details);
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// RUN// ////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    Ler run(std::string text) {
        Lexer lexer(text);
        return lexer.make_tokens();
        
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// LEXER ////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    Lexer::Lexer(std::string text) {
        this->text = text;
        this->pos = -1;
        this->current_char = '\0';
        this->advance();
    }

    void Lexer::advance() {
        this->pos++;
        if (this->pos < this->text.length()){
            this->current_char = this->text[pos];
        } else {
            this->current_char = '\0';
        }
    }
    Token Lexer::make_number() {
        std::string num = "";
        int dot_count = 0;
        bool is_float = false;
        while (this->current_char != '\0' && isCharInSet(this->current_char, DIGITS + ".f")) {
            if (this->current_char == '.') {
                if (dot_count == 1) {
                    break;
                }
                dot_count ++;
                num += ".";
                this->advance();
            } else if (this->current_char == 'f') {
                is_float = true;
                break;
            } else {
                num += this->current_char;
                this->advance();
            }
        }
        if (dot_count == 1) {
            if (is_float) {
                return Token(TokenType::FLOAT, num);
            }
            return Token(TokenType::DOUBLE, num);
        }
        return Token(TokenType::INT, num);
    }
    Ler Lexer::make_tokens() {
        std::list<Token> tokens;

        while (this->current_char != '\0') {
            if (isCharInSet(this->current_char, bad_chars)) {
                this->advance();
                continue;
            } else if (isCharInSet(this->current_char, DIGITS)) {
                tokens.push_back(this->make_number());
                this->advance();
                continue;
            } else {
                switch (this->current_char) {
                    case '+':
                        tokens.push_back(Token(TokenType::PLUS, ""));
                        this->advance();
                        break;
                    case '-':
                        tokens.push_back(Token(TokenType::MINUS, ""));
                        this->advance();
                        break;
                    case '*':
                        tokens.push_back(Token(TokenType::MUL, ""));
                        this->advance();
                        break;
                    case '/':
                        tokens.push_back(Token(TokenType::DIV, ""));
                        this->advance();
                        break;
                    case '(':
                        tokens.push_back(Token(TokenType::LPAREN, ""));
                        this->advance();
                        break;
                    case ')':
                        tokens.push_back(Token(TokenType::RPAREN, ""));
                        this->advance();
                        break;
                    case ';':
                        tokens.push_back(Token(TokenType::SEMICOLON, ""));
                        this->advance();
                        break;
                    default:
                        std::string unknown = std::string(1, this->current_char);
                        this->advance();
                        return Ler {std::list<Token>(), std::make_unique<IllegalCharError>(unknown)};
                }
            }
        }

        return Ler {tokens, NULL};
    }
    
};


