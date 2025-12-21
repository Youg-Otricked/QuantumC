//////////////////////////////////////////////////////////////////////////////////////////////
// TOKENS ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
#include "tokenizer.h"
#include <string>
#include <format>
#include <iostream>
#include <list>
#include <memory>
#include <variant>
#include <functional>
#include <optional>
#include <typeinfo>
bool isCharInSet(char c, const std::string &charSet) {
    return charSet.find(c) != std::string::npos;
}
namespace tkz {
    //////////////////////////////////////////////////////////////////////////////////////////////
// POSITION /////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    Position::Position() {

    }
    Position::Position(std::string Filename, std::string Filetxt, int index, int line, int column) {
        this->Filename = Filename;
        this->Filetxt = Filetxt;
        this->index = index;
        this->line = line;
        this->column = column;
    }

    void Position::advance(char current_char) {
        this->index ++;
        this->column ++;
        if (current_char == '\n') {
            this->line ++;
            this->column = 0;
        }
    }
    Position Position::copy() {
        return Position(this->Filename, this->Filetxt, this->index, this->line, this->column);
    }
    Token::Token() {}
    Token::Token(TokenType t, std::string val, Position p) {
        this->type = t;
        this->value = val;
        this->pos = p;
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
    Error::Error(std::string err, std::string details, Position pos) {
        this->details = details;
        this->error_name = err;
        this->pos = pos.copy();
    }
    std::string Error::as_string() {
        return std::format("{}: {} (File {}, Line {}:{})", this->error_name, this->details, this->pos.Filename, this->pos.line, this->pos.column);
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// NODES ////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    std::string printAny(AnyNode& node) {
        return std::visit([](auto&& arg) -> std::string {
            using T = std::decay_t<decltype(arg)>;
            
            if constexpr (std::is_same_v<T, NumberNode>) {
                return arg.print();
            } 
            else if constexpr (std::is_same_v<T, std::unique_ptr<BinOpNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<UnaryOpNode>>) {
                return arg->print();
            }
            else {
                return "<empty>"; 
            }
        }, node);
    }
    NumberNode::NumberNode(Token tok) {
        this->tok = tok;
    }
    std::string NumberNode::print() {
        return this->tok.print();
    }
    std::string BinOpNode::print() {
        return "(" + printAny(left_node) + " " + op_tok.print() + " " + printAny(right_node) + ")";
    }
    UnaryOpNode::UnaryOpNode(Token op_tok, AnyNode node) {
      this->op_tok = op_tok;
      this->node = std::move(node);  
    }
    std::string UnaryOpNode::print() {
        return std::string{"("} + this->op_tok.print() + ", " + printAny(this->node) + ")";
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// PARSE RESULT /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    AnyNode ParseResult::reg_node(AnyNode res) {
        return res;
    }
    AnyNode ParseResult::reg(Prs res_variant) {
        if (std::holds_alternative<std::unique_ptr<tkz::Error>>(res_variant)) {
            this->error = std::move(std::get<std::unique_ptr<tkz::Error>>(res_variant));
            return std::monostate{};
        }
        return std::visit([this](auto&& arg) -> AnyNode {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::monostate> || 
                        std::is_same_v<T, std::unique_ptr<tkz::Error>> || 
                        std::is_same_v<T, ParseResult>) {
                return AnyNode{std::monostate{}};
            } 
            else if constexpr (std::is_same_v<T, UnaryOpNode>) { 
                return AnyNode{std::make_unique<UnaryOpNode>(std::move(arg))};
            }
            else {
                return AnyNode{std::move(arg)};
            }
        }, std::move(res_variant)); 
    }
    
    Prs ParseResult::success(AnyNode node) {
        this->node = std::move(node);
        return std::visit([](auto&& arg) -> tkz::Prs {
            return tkz::Prs{std::move(arg)}; 
        }, std::move(this->node));
    }
    Prs ParseResult::to_prs() {
        if (this->error) {
            return tkz::Prs{std::move(this->error)}; 
        }
        
        return std::visit([](auto&& arg) -> tkz::Prs {
            return tkz::Prs{std::move(arg)};
        }, std::move(this->node));
    }
    void ParseResult::failure(std::unique_ptr<Error> error) {
        this->error = std::move(error);
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// PARSER ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    Parser::Parser(std::list<Token> tokens) {
        this->tokens = tokens;
        this->it = this->tokens.begin();
        this->current_tok = *it;
    }
    Token Parser::advance() {
        Position last_pos = this->current_tok.pos;
        if (it != tokens.end()) {
            ++it;
        }
        if (it != tokens.end()) {
            this->current_tok = *it;
        } else {
            this->current_tok = Token(TokenType::EOFT, "", last_pos); 
        }
        return this->current_tok;
    }
    Prs Parser::factor() {
        ParseResult res = ParseResult();
        Token tok = this->current_tok;

        if (tok.type == TokenType::PLUS || tok.type == TokenType::MINUS) {
            this->advance();
            AnyNode factor_node = res.reg(this->factor()); 
            if (res.error) return res.to_prs();
            return res.success(std::make_unique<UnaryOpNode>(tok, std::move(factor_node)));

        } else if (tok.type == TokenType::INT || tok.type == TokenType::FLOAT || tok.type == TokenType::DOUBLE) {
            this->advance();
            return res.success(NumberNode(tok));
        } else if (tok.type == TokenType::LPAREN) {
            res.reg_node(this->advance());
            AnyNode any_expr = res.reg(this->expr());
            if (res.error) return res.to_prs();
            Prs expr = std::visit([](auto&& arg) -> Prs {
                return std::forward<decltype(arg)>(arg);
            }, std::move(any_expr));
            if (this->current_tok.type == TokenType::RPAREN) {
                res.reg_node(this->advance());
                AnyNode any_node = std::visit([](auto&& arg) -> AnyNode {
                    using T = std::decay_t<decltype(arg)>;
                    
                    if constexpr (std::is_constructible_v<AnyNode, T>) {
                        return std::forward<decltype(arg)>(arg);
                    } else {
                        return std::monostate{}; 
                    }
                }, std::move(expr));

            return res.success(std::move(any_node));
            } else {
                res.failure(std::make_unique<InvalidSyntaxError>(InvalidSyntaxError(
                    "Expected ')'", this->current_tok.pos
                )));
                return res.to_prs();
            }
        }
        res.failure(std::make_unique<InvalidSyntaxError>(
            InvalidSyntaxError("Expected an Int Float or double", tok.pos)
        ));
        return res.to_prs(); 
    }
    Prs Parser::term() {
        return this->bin_op([this]() { return this->factor(); }, TokenType::DIV, TokenType::MUL);
    }
    Prs Parser::expr() {
        return this->bin_op([this]() { return this->term(); }, TokenType::PLUS, TokenType::MINUS);
    }
    Prs Parser::bin_op(std::function<Prs()> func, TokenType type1, TokenType type2) {
        ParseResult res;
        AnyNode left = res.reg(func());
        if (res.error) return res.to_prs();

        while (this->current_tok.type == type1 || this->current_tok.type == type2) {
            Token op_tok = this->current_tok;
            this->advance();
            
            AnyNode right = res.reg(func());
            if (res.error) return res.to_prs();

            left = std::make_unique<BinOpNode>(std::move(left), op_tok, std::move(right));
        }

        return res.success(std::move(left));
    }
    Aer Parser::parse() {
        Prs result = this->expr();
        if (std::holds_alternative<std::unique_ptr<Error>>(result)) {
            return Aer{
                std::nullopt, 
                std::get<std::unique_ptr<Error>>(std::move(result))
            };
        }
        AnyNode ast = std::visit([](auto&& arg) -> AnyNode {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, NumberNode> || 
                        std::is_same_v<T, std::unique_ptr<BinOpNode>> ||
                        std::is_same_v<T, std::unique_ptr<UnaryOpNode>> || 
                        std::is_same_v<T, std::monostate>) {
                return std::move(arg);
            }
            return std::monostate{}; 
        }, std::move(result));
        if (this->current_tok.type != TokenType::EOFT) {
            return Aer{
                std::nullopt, 
                std::make_unique<InvalidSyntaxError>(
                    "Expected + - / or *", 
                    this->current_tok.pos 
                )
            };
        }
        return Aer{
            std::make_unique<tkz::AnyNode>(std::move(ast)), 
            nullptr
        };
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// THE ACTUAL FRIGGEN INTERPRETER ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    void Interpreter::visit_NumberNode(NumberNode node) {
        std::cout << "\nNumber Node found" << node.print() << '\n';
    }
    void Interpreter::visit_BinOpNode(BinOpNode node) {
        std::cout << "\nBinOp Node found" << node.print() << '\n';
    }
    void Interpreter::visit_UnaryOpNode(UnaryOpNode node) {
        std::cout << "\nUnaryOp Node found" << node.print() << '\n';
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// RUN //////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    Mer run(std::string file, std::string text) {
    Lexer lexer(text, file);
    Ler resp = lexer.make_tokens();
    if (resp.error != nullptr) {
        return Mer{
            Aer{std::nullopt, std::move(resp.error)}, 
            std::move(resp)
        };
    }
    
    Parser parser(resp.Tkns);
    Aer ast = parser.parse();
    
    return Mer{
        std::move(ast),
        std::move(resp)
    };
}


//////////////////////////////////////////////////////////////////////////////////////////////
// LEXER ////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    Lexer::Lexer(std::string text, std::string filename) {
        this->Filename = filename;
        this->pos = Position(filename, text, -1, 0, -1);
        this->text = text;
        this->current_char = '\0';
        this->advance();
    }

    void Lexer::advance() {
        this->pos.advance(this->current_char);
        if (this->pos.index < this->text.length()){
            this->current_char = this->text[pos.index];
        } else {
            this->current_char = '\0';
        }
    }
    Token Lexer::make_number() {
        Position start_pos = this->pos.copy();
        std::string num = "";
        int dot_count = 0;
        bool is_float = false;
        while (this->current_char != '\0' && isCharInSet(this->current_char, DIGITS + ".f")) {
            if (this->current_char == '.') {
                if (dot_count == 1) {
                    this->advance();
                    break;
                }
                dot_count ++;
                num += ".";
                this->advance();
            } else if (this->current_char == 'f') {
                is_float = true;
                this->advance();
                break;
            } else {
                num += this->current_char;
                this->advance();
            }
        }
        if (dot_count == 1) {
            if (is_float) {
                return Token(TokenType::FLOAT, num, start_pos);
            }
            return Token(TokenType::DOUBLE, num, start_pos);
        }
        return Token(TokenType::INT, num, start_pos);
    }
    Ler Lexer::make_tokens() {
        std::list<Token> tokens;

        while (this->current_char != '\0') {
            Position start_pos = this->pos.copy();
            if (isCharInSet(this->current_char, bad_chars)) {
                this->advance();
                continue;
            } else if (isCharInSet(this->current_char, DIGITS)) {
                tokens.push_back(this->make_number());
                continue;
            } else {
                switch (this->current_char) {
                    case '+':
                        tokens.push_back(Token(TokenType::PLUS, "", start_pos));
                        this->advance();
                        break;
                    case '-':
                        tokens.push_back(Token(TokenType::MINUS, "", start_pos));
                        this->advance();
                        break;
                    case '*':
                        tokens.push_back(Token(TokenType::MUL, "", start_pos));
                        this->advance();
                        break;
                    case '/':
                        tokens.push_back(Token(TokenType::DIV, "", start_pos));
                        this->advance();
                        break;
                    case '(':
                        tokens.push_back(Token(TokenType::LPAREN, "", start_pos));
                        this->advance();
                        break;
                    case ')':
                        tokens.push_back(Token(TokenType::RPAREN, "", start_pos));
                        this->advance();
                        break;
                    case ';':
                        tokens.push_back(Token(TokenType::SEMICOLON, "", start_pos));
                        this->advance();
                        break;
                    default:
                        std::string unknown = std::string(1, this->current_char);
                        this->advance();
                        return Ler {std::list<Token>(), std::make_unique<IllegalCharError>(unknown, this->pos)};
                }
            }
        }
        tokens.push_back(Token(TokenType::EOFT, "", this->pos));
        return Ler {tokens, NULL};

    }
    
};


