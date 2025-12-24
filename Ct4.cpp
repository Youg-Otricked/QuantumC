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
#include <type_traits>
#include <vector>
#include <map>
bool isCharInSet(char c, const std::string &charSet) {
    return charSet.find(c) != std::string::npos;
}
namespace tkz {
//////////////////////////////////////////////////////////////////////////////////////////////
// POSITION /////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    Position::Position() {

    }
    std::string Position::arrow_string() const {
        std::string result;

        // find line start
        int start = this->index;
        while (start > 0 && this->Filetxt[start - 1] != '\n') start--;

        // find line end
        int end = this->index;
        while (end < (int)this->Filetxt.size() && this->Filetxt[end] != '\n') end++;

        std::string line = this->Filetxt.substr(start, end - start);

        result += line + "\n";
        result += std::string(this->column, ' ');
        result += std::string(std::max(1, this->length), '^');
        result += "\n";
        return result;
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
    Token::Token(TokenType t, std::string val, Position p)
    : type(t), value(val), pos(p)
    {
        this->pos.length = val.size();
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
    std::string RTError::as_string() {
        std::string result;
        result += "Runtime Error: " + this->details + "\n";
        result += "File " + this->pos.Filename +
                ", line " + std::to_string(this->pos.line + 1) +
                ", col " + std::to_string(this->pos.column + 1) + "\n\n";
        result += this->pos.arrow_string();
        return result;
    }
    std::string MissingSemicolonError::as_string() {
        std::string result;
        result += "Missing Semicolon on";
        result += "File " + this->pos.Filename +
                ", line " + std::to_string(this->pos.line + 1) +
                ", col " + std::to_string(this->pos.column + 1) + "\n\n";
        result += this->pos.arrow_string();
        return result;
    }
    std::string InvalidSyntaxError::as_string() {
        std::string result;
        result += "Invalid Syntax: " + this->details + "\n";
        result += "File " + this->pos.Filename +
                ", line " + std::to_string(this->pos.line + 1) +
                ", col " + std::to_string(this->pos.column + 1) + "\n\n";
        result += this->pos.arrow_string();
        return result;
    }
    std::string IllegalCharError::as_string() {
        std::string result;
        result += "Illegal Charecter: " + this->details + "\n";
        result += "File " + this->pos.Filename +
                ", line " + std::to_string(this->pos.line + 1) +
                ", col " + std::to_string(this->pos.column + 1) + "\n\n";
        result += this->pos.arrow_string();
        return result;
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
            else if constexpr (std::is_same_v<T, StringNode>) {
                return arg.print();
            } 
            else if constexpr (std::is_same_v<T, CharNode>) {
                return arg.print();
            } 
            else if constexpr (std::is_same_v<T, BoolNode>) { 
                return arg.print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<BinOpNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<UnaryOpNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<StatementsNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<VarAccessNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<VarAssignNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<AssignExprNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<IfNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::monostate>) {
                return "<empty>";
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<WhileNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ForNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ContinueNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<BreakNode>>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<SwitchNode>>) {
                return arg->print();
            } else {
                return "<unknown>"; 
            }
        }, node);
    }
    std::string VarAssignNode::print() {
        return "(" + this->type_tok.print() + " " + this->var_name_tok.print() + " " + printAny(this->value_node) + ")";
    }
    std::string VarAccessNode::print() {
        return "(" + this->var_name_tok.print() + ")";
    }
    NumberNode::NumberNode(Token tok) {
        this->tok = tok;
    }
    std::string CharNode::print() {
        return this->tok.print();
    }
    std::string NumberNode::print() {
        return this->tok.print();
    }
    std::string BinOpNode::print() {
        return "(" + printAny(left_node) + " " + op_tok.print() + " " + printAny(right_node) + ")";
    }
    std::string UnaryOpNode::print() {
        return std::string{"("} + this->op_tok.print() + ", " + printAny(this->node) + ")";
    }
    std::string StatementsNode::print() {
        std::string res = "[";
        for (size_t i = 0; i < statements.size(); i++) {
            res += printAny(statements[i]);
            if (i < statements.size() - 1) {
                res += ", ";
            }
        }
        res += "]";
        return res;
    }
    std::string StringNode::print() {
        return "(" + this->tok.print() + ")";
    }
    StringNode::StringNode(Token tok) {
        this->tok = tok;
    }
    BoolNode::BoolNode(Token tok) {
        this->tok = tok;
    }
    std::string BoolNode::print() {
        return "(" + this->tok.print() + ")";
    }
    std::string IfNode::print() {
        std::string res = "(if ";
        if (init.has_value()) {
            res += "init=" + printAny(init.value()) + "; ";
        }
        res += printAny(this->condition) + " " + this->then_branch->print();
        for (auto &p : this->elif_branches) {
            res += " elif " + printAny(p.first) + " " + p.second->print();
        }
        if (this->else_branch) {
            res += " else " + this->else_branch->print();
        }
        res += ")";
        return res;
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
            else if constexpr (std::is_constructible_v<AnyNode, T>) {
                return AnyNode{std::move(arg)};
            }
            else {
                return AnyNode{std::monostate{}};
            }
        }, std::move(res_variant));
    }
    
    Prs ParseResult::success(AnyNode node) {
        this->node = std::move(node);
        return std::visit([](auto&& arg) -> Prs {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::monostate>) {
                return Prs{std::monostate{}};
            } else if constexpr (std::is_same_v<T, NumberNode>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, StringNode>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, CharNode>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, BoolNode>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<BinOpNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<UnaryOpNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<VarAccessNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<VarAssignNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<AssignExprNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<StatementsNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<IfNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<BreakNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<SwitchNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<WhileNode>>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ForNode>>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ContinueNode>>) {
                return Prs{std::move(arg)};
            } else {
                return Prs{std::monostate{}};
            }
        }, std::move(this->node));
    }
    Prs ParseResult::to_prs() {
        if (this->error) {
            return tkz::Prs{std::move(this->error)};
        }
        return std::visit([](auto&& arg) -> Prs {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::monostate>) {
                return Prs{std::monostate{}};
            } else if constexpr (std::is_same_v<T, NumberNode>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, StringNode>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, CharNode>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, BoolNode>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<BinOpNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<UnaryOpNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<VarAccessNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<VarAssignNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<AssignExprNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<StatementsNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<IfNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<BreakNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<SwitchNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<WhileNode>>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ForNode>>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ContinueNode>>) {
                return Prs{std::move(arg)};
            } else {
                return Prs{std::monostate{}};
            }
        }, std::move(this->node));
    }
    void ParseResult::failure(std::unique_ptr<Error> error) {
        this->error = std::move(error);
    }
    TokenType stringToTokenType(const std::string& str) {
        static const std::unordered_map<std::string, TokenType> stringToEnum = {
            {"INT", TokenType::INT}, {"STRING", TokenType::STRING}, {"FLOAT", TokenType::FLOAT},
            {"DOUBLE", TokenType::DOUBLE}, {"CHAR", TokenType::CHAR}, {"MAP", TokenType::MAP},
            {"LIST", TokenType::LIST}, {"ARRAY", TokenType::ARRAY}, {"VOID", TokenType::VOID},
            {"ENUM", TokenType::ENUM}, {"CLASS", TokenType::CLASS}, {"STRUCT", TokenType::STRUCT},
            {"BOOL", TokenType::BOOL}, {"QBOOL", TokenType::QBOOL}, {"PLUS", TokenType::PLUS},
            {"MINUS", TokenType::MINUS}, {"MUL", TokenType::MUL}, {"DIV", TokenType::DIV},
            {"POWER", TokenType::POWER}, {"LPAREN", TokenType::LPAREN}, {"RPAREN", TokenType::RPAREN},
            {"SEMICOLON", TokenType::SEMICOLON}, {"DEF", TokenType::DEF}, {"INCREMENT", TokenType::INCREMENT},
            {"DECREMENT", TokenType::DECREMENT}, {"IDENTIFIER", TokenType::IDENTIFIER},
            {"KEYWORD", TokenType::KEYWORD}, {"EQ", TokenType::EQ}, {"EOFT", TokenType::EOFT}
        };

        auto it = stringToEnum.find(str);
        if (it != stringToEnum.end()) {
            return it->second;
        }
        throw std::invalid_argument("Unknown TokenType string: " + str);
    }
    struct ScopeGuard {
        Context* ctx;
        bool active;
        ScopeGuard(Context* c) : ctx(c), active(false) {
            if (ctx) {
                ctx->push_scope();
                active = true;
            }
        }
        void dismiss() { active = false; }
        ~ScopeGuard() {
            if (ctx && active) ctx->pop_scope();
        }
    };
//////////////////////////////////////////////////////////////////////////////////////////////
// PARSER ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    AnyNode default_value_for_type(const Token& type_tok, const Position& pos) {
        if (type_tok.value == "string") 
            return AnyNode{StringNode(Token(TokenType::STRING, "", pos))};  // by value
        if (type_tok.value == "char") 
            return AnyNode{CharNode(Token(TokenType::CHAR, "\0", pos))};     // by value
        if (type_tok.value == "float")
            return AnyNode{NumberNode(Token(TokenType::FLOAT, "0.0f", pos))}; // by value
        if (type_tok.value == "double")
            return AnyNode{NumberNode(Token(TokenType::DOUBLE, "0.0", pos))}; // by value
        if (type_tok.value == "bool")
            return AnyNode{NumberNode(Token(TokenType::BOOL, "", pos))};      // by value
        return AnyNode{NumberNode(Token(TokenType::INT, "0", pos))};          // by value
    }
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
    // EDIT FOR NEW STUFF VVVVVVVVVVVVVVVVVVVV
    Prs Parser::if_expr() {
        auto has_semicolon_before_closing_paren = [this]() -> bool {
            size_t idx = static_cast<size_t>(std::distance(this->tokens.begin(), this->it));
            int depth = 0;
            for (size_t i = idx; i < this->tokens.size(); ++i) {
                auto it = this->tokens.begin();
                std::advance(it, i);   
                const Token &t = *it;
                if (t.type == TokenType::LPAREN) {
                    ++depth;
                } else if (t.type == TokenType::RPAREN) {
                    if (depth == 0) {
                        return false;
                    }
                    --depth;
                } else if (t.type == TokenType::SEMICOLON && depth == 0) {
                    return true;
                }
            }
            return false;
        };
        ParseResult res;
        if (!(this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "if")) {
            res.failure(std::make_unique<InvalidSyntaxError>("Expected 'if'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance(); 

        if (this->current_tok.type != TokenType::LPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("Expected '(' after 'if'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        

        std::optional<AnyNode> init_node = std::nullopt;

        if (has_semicolon_before_closing_paren()) {
            if (this->current_tok.type == TokenType::KEYWORD &&
                (this->current_tok.value == "const" ||
                this->current_tok.value == "int" ||
                this->current_tok.value == "float" ||
                this->current_tok.value == "double" ||
                this->current_tok.value == "bool" ||
                this->current_tok.value == "string" ||
                this->current_tok.value == "char")) {

                bool is_const = false;
                Token tok = this->current_tok;
                if (tok.value == "const") {
                    is_const = true;
                    this->advance();
                    tok = this->current_tok;
                    if (tok.type != TokenType::KEYWORD) {
                        res.failure(std::make_unique<InvalidSyntaxError>("Expected type after 'const' in if-init", this->current_tok.pos));
                        return res.to_prs();
                    }
                }
                Token type_tok = tok;
                this->advance();

                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>("Expected identifier in if-init", this->current_tok.pos));
                    return res.to_prs();
                }
                Token var_name = this->current_tok;
                this->advance();

                AnyNode value;
                if (this->current_tok.type == TokenType::EQ) {
                    this->advance();
                    value = res.reg(this->logical_or());
                    if (res.error) return res.to_prs();
                } else {
                    if (is_const) {
                        res.failure(std::make_unique<InvalidSyntaxError>("const variables must be initialized in if-init", var_name.pos));
                        return res.to_prs();
                    }
                    value = default_value_for_type(type_tok, var_name.pos);
                }

                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(std::make_unique<InvalidSyntaxError>("Expected ';' after if-init declaration", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance(); 

                init_node = AnyNode{std::make_unique<VarAssignNode>(is_const, type_tok, var_name, std::move(value))};
            } else {
                AnyNode expr_init = res.reg(this->assignment_expr());
                if (res.error) return res.to_prs();

                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(std::make_unique<InvalidSyntaxError>("Expected ';' after if-init expression", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance(); 
                init_node = std::move(expr_init);
            }
        }

        AnyNode condition = res.reg(this->logical_or());
        if (res.error) return res.to_prs();

        if (this->current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("Expected ')' after condition", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance(); 

        

        std::unique_ptr<StatementsNode> then_branch;
        if (!parse_block_into(then_branch, res)) return res.to_prs();

        std::vector<std::pair<AnyNode, std::unique_ptr<StatementsNode>>> elifs;
        std::unique_ptr<StatementsNode> else_branch = nullptr;

        while (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "else") {
            this->advance(); 
            if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "if") {
                this->advance();
                if (this->current_tok.type != TokenType::LPAREN) {
                    res.failure(std::make_unique<InvalidSyntaxError>("Expected '(' after 'else if'", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                AnyNode elif_cond = res.reg(this->logical_or());
                if (res.error) return res.to_prs();
                if (this->current_tok.type != TokenType::RPAREN) {
                    res.failure(std::make_unique<InvalidSyntaxError>("Expected ')' after 'else if' condition", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                std::unique_ptr<StatementsNode> elif_block;
                if (!parse_block_into(elif_block, res)) return res.to_prs();
                elifs.emplace_back(std::move(elif_cond), std::move(elif_block));
                continue;
            } else {
                if (!parse_block_into(else_branch, res)) return res.to_prs();
                break;
            }
        }

        auto ifnode = std::make_unique<IfNode>(std::move(init_node), std::move(condition), std::move(then_branch), std::move(elifs), std::move(else_branch));
        return res.success(std::move(ifnode));
    }
    Prs Parser::switch_stmt() {
        ParseResult res;
        if (!(current_tok.type == TokenType::KEYWORD && current_tok.value == "switch")) {
            res.failure(std::make_unique<InvalidSyntaxError>("Expected 'switch'", current_tok.pos));
            return res.to_prs();
        }
        advance();

        if (current_tok.type != TokenType::LPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("Expected '(' after 'switch'", current_tok.pos));
            return res.to_prs();
        }
        advance();

        AnyNode value = res.reg(this->logical_or());
        if (res.error) return res.to_prs();

        if (current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("Expected ')' after switch expression", current_tok.pos));
            return res.to_prs();
        }
        advance();

        if (current_tok.type != TokenType::LBRACE) {
            res.failure(std::make_unique<InvalidSyntaxError>("Expected '{' after switch(...)", current_tok.pos));
            return res.to_prs();
        }
        advance();

        std::vector<SwitchNode::Section> sections;

        while (this->current_tok.type != TokenType::RBRACE && this->current_tok.type != TokenType::EOFT) {
            SwitchNode::Section section;
            bool saw_label = false;
            while (this->current_tok.type == TokenType::KEYWORD &&
                (this->current_tok.value == "case" || this->current_tok.value == "default")) {

                saw_label = true;

                if (current_tok.value == "default") {
                    this->advance();
                    if (current_tok.type != TokenType::COLON  &&
                        current_tok.type != TokenType::SEMICOLON ) {
                    }
                    section.is_default = true;
                    this->advance();
                    break; 
                } else { 
                    advance();
                    AnyNode case_expr = res.reg(this->logical_or());
                    if (res.error) return res.to_prs();

                    if (current_tok.type != TokenType::COLON ) {
                        res.failure(std::make_unique<InvalidSyntaxError>("Expected ':' after case expression", current_tok.pos));
                        return res.to_prs();
                    }
                    advance();

                    section.cases.push_back(CaseLabel{std::move(case_expr)});
                }
            }

            if (!saw_label) {
                res.failure(std::make_unique<InvalidSyntaxError>("Expected 'case' or 'default' inside switch", current_tok.pos));
                return res.to_prs();
            }
            std::vector<AnyNode> stmts;
            while (current_tok.type != TokenType::RBRACE &&
                !(current_tok.type == TokenType::KEYWORD &&
                    (current_tok.value == "case" || current_tok.value == "default"))) {

                Prs st = this->statement();
                if (std::holds_alternative<std::unique_ptr<Error>>(st)) {
                    res.failure(std::get<std::unique_ptr<Error>>(std::move(st)));
                    return res.to_prs();
                }
                AnyNode any_stmt = std::visit([](auto&& arg) -> AnyNode {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_constructible_v<AnyNode, T>) {
                        return AnyNode(std::move(arg));
                    }
                    return std::monostate{};
                }, std::move(st));
                stmts.push_back(std::move(any_stmt));
            }

            section.body = std::make_unique<StatementsNode>(std::move(stmts), true);
            sections.push_back(std::move(section));
        }

        if (current_tok.type != TokenType::RBRACE) {
            res.failure(std::make_unique<InvalidSyntaxError>("Expected '}' after switch body", current_tok.pos));
            return res.to_prs();
        }
        advance();

        auto sw = std::make_unique<SwitchNode>();
        sw->value = std::move(value);
        sw->sections = std::move(sections);
        return res.success(std::move(sw));
    }
    Prs Parser::while_stmt() {
        ParseResult res;
        if (!(current_tok.type == TokenType::KEYWORD && current_tok.value == "while")) {
            res.failure(std::make_unique<InvalidSyntaxError>("Expected 'while'", current_tok.pos));
            return res.to_prs();
        }
        advance();

        if (current_tok.type != TokenType::LPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("Expected '(' after 'while'", current_tok.pos));
            return res.to_prs();
        }
        advance();

        AnyNode cond = res.reg(this->logical_or());
        if (res.error) return res.to_prs();

        if (current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("Expected ')' after while condition", current_tok.pos));
            return res.to_prs();
        }
        advance();

        std::unique_ptr<StatementsNode> body;
        if (!this->parse_block_into(body, res)) return res.to_prs();

        auto wn = std::make_unique<WhileNode>(std::move(cond), std::move(body));
        return res.success(std::move(wn));
    }
    Prs Parser::for_stmt() {
        ParseResult res;

        if (!(current_tok.type == TokenType::KEYWORD && current_tok.value == "for")) {
            res.failure(std::make_unique<InvalidSyntaxError>("Expected 'for'", current_tok.pos));
            return res.to_prs();
        }
        advance();

        if (current_tok.type != TokenType::LPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("Expected '(' after 'for'", current_tok.pos));
            return res.to_prs();
        }
        advance();

        std::optional<AnyNode> init;
        std::optional<AnyNode> update;
        AnyNode condition;

        if (current_tok.type != TokenType::SEMICOLON) {
            if (current_tok.type == TokenType::KEYWORD &&
                (current_tok.value == "const" ||
                current_tok.value == "int"   ||
                current_tok.value == "float" ||
                current_tok.value == "double"||
                current_tok.value == "bool"  ||
                current_tok.value == "string"||
                current_tok.value == "char")) {

                bool is_const = false;
                Token tok = current_tok;

                if (tok.value == "const") {
                    is_const = true;
                    advance();
                    tok = current_tok;
                    if (tok.type != TokenType::KEYWORD) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Expected type after 'const' in for-init", current_tok.pos));
                        return res.to_prs();
                    }
                }

                Token type_tok = tok;
                advance();

                if (current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected identifier in for-init", current_tok.pos));
                    return res.to_prs();
                }

                Token var_name = current_tok;
                advance();

                AnyNode value;
                if (current_tok.type == TokenType::EQ) {
                    advance();
                    value = res.reg(this->logical_or());
                    if (res.error) return res.to_prs();
                } else {
                    if (is_const) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "const variables must be initialized in for-init", var_name.pos));
                        return res.to_prs();
                    }
                    value = default_value_for_type(type_tok, var_name.pos);
                }

                init = AnyNode{
                    std::make_unique<VarAssignNode>(is_const, type_tok, var_name, std::move(value))
                };
            } else {
                AnyNode expr_init = res.reg(this->assignment_expr());
                if (res.error) return res.to_prs();
                init = std::move(expr_init);
            }
        }

        if (current_tok.type != TokenType::SEMICOLON) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "Expected ';' after for-init", current_tok.pos));
            return res.to_prs();
        }
        advance();

        if (current_tok.type == TokenType::SEMICOLON) {
            condition = AnyNode{ BoolNode(Token(TokenType::BOOL, "true", current_tok.pos)) };
        } else {
            condition = res.reg(this->logical_or());
            if (res.error) return res.to_prs();
        }

        if (current_tok.type != TokenType::SEMICOLON) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "Expected ';' after for condition", current_tok.pos));
            return res.to_prs();
        }
        advance();

        if (current_tok.type != TokenType::RPAREN) {
            AnyNode upd_expr = res.reg(this->assignment_expr());
            if (res.error) return res.to_prs();
            update = std::move(upd_expr);
        } 

        if (current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "Expected ')' after for header", current_tok.pos));
            return res.to_prs();
        }
        advance();

        auto parse_block = [&](std::unique_ptr<StatementsNode>& out_block) -> bool {
            if (this->current_tok.type == TokenType::LBRACE) {
                this->advance();
                std::vector<AnyNode> stmts;
                while (this->current_tok.type != TokenType::RBRACE &&
                    this->current_tok.type != TokenType::EOFT) {
                    Prs st = this->statement();
                    if (std::holds_alternative<std::unique_ptr<Error>>(st)) {
                        res.failure(std::get<std::unique_ptr<Error>>(std::move(st)));
                        return false;
                    }
                    AnyNode any_stmt = std::visit([](auto&& arg) -> AnyNode {
                        using T = std::decay_t<decltype(arg)>;
                        if constexpr (std::is_constructible_v<AnyNode, T>) {
                            return AnyNode(std::move(arg));
                        }
                        return std::monostate{};
                    }, std::move(st));
                    stmts.push_back(std::move(any_stmt));
                }
                if (this->current_tok.type != TokenType::RBRACE) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected '}' after for body", this->current_tok.pos));
                    return false;
                }
                this->advance();
                out_block = std::make_unique<StatementsNode>(std::move(stmts), true);
                return true;
            } else {
                Prs st = this->statement();
                if (std::holds_alternative<std::unique_ptr<Error>>(st)) {
                    res.failure(std::get<std::unique_ptr<Error>>(std::move(st)));
                    return false;
                }
                AnyNode any_stmt = std::visit([](auto&& arg) -> AnyNode {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_constructible_v<AnyNode, T>) {
                        return AnyNode(std::move(arg));
                    }
                    return std::monostate{};
                }, std::move(st));
                std::vector<AnyNode> stmts;
                stmts.push_back(std::move(any_stmt));
                out_block = std::make_unique<StatementsNode>(std::move(stmts), false);
                return true;
            }
        };

        std::unique_ptr<StatementsNode> body;
        if (!parse_block(body)) return res.to_prs();

        auto fn = std::make_unique<ForNode>(
            std::move(init),
            std::move(condition),
            std::move(update),
            std::move(body)
        );
        return res.success(std::move(fn));
    }
    Prs Parser::atom() {
        ParseResult res = ParseResult();
        Token tok = this->current_tok;
        
        if (tok.type == TokenType::INT || tok.type == TokenType::FLOAT || tok.type == TokenType::DOUBLE) {
            this->advance();
            return res.success(NumberNode(tok));
        }  else if (tok.type == TokenType::STRING) {
            this->advance();
            return res.success(StringNode(tok));
        }
        else if (tok.type == TokenType::IDENTIFIER) {
            this->advance();
            if (current_tok.type == TokenType::INCREMENT ||
                current_tok.type == TokenType::DECREMENT) {

                Token op = current_tok;
                this->advance();

                return res.success(std::make_unique<AssignExprNode>(
                    tok,
                    std::make_unique<UnaryOpNode>(op,
                        std::make_unique<VarAccessNode>(tok))
                ));
            }

            return res.success(std::make_unique<VarAccessNode>(tok));
        } else if (tok.type == TokenType::CHAR) {
            this->advance();
            return res.success(CharNode(tok));
        } else if (tok.type == TokenType::BOOL) {
            this->advance();
            return res.success(BoolNode(tok));
        } else if (tok.type == TokenType::LPAREN) {
            this->advance();
            AnyNode any_expr = res.reg(this->logical_or()); 
            if (res.error) return res.to_prs();
            Prs expr = std::visit([](auto&& arg) -> Prs {
                return std::forward<decltype(arg)>(arg);
            }, std::move(any_expr));
            if (this->current_tok.type == TokenType::RPAREN) {
                this->advance();
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
            InvalidSyntaxError("Expected an String, Char, Boolean, Int, Float, Double, '+', '-', Identifier, or '('", tok.pos)
        ));
        return res.to_prs(); 
    }
    
    Prs Parser::power() {
        ParseResult res;
        AnyNode left = res.reg(this->atom());
        if (res.error) return res.to_prs();
        
        if (this->current_tok.type == TokenType::POWER) {
            Token op_tok = this->current_tok;
            this->advance();

            AnyNode right = res.reg(this->factor()); 
            if (res.error) return res.to_prs();
            left = std::make_unique<BinOpNode>(std::move(left), op_tok, std::move(right));
        }
        
        return res.success(std::move(left));
    }
    Prs Parser::factor() {
        ParseResult res;
        Token tok = this->current_tok;

        if (tok.type == TokenType::PLUS || tok.type == TokenType::MINUS ||
            tok.type == TokenType::NOT) {
            
            this->advance();
            AnyNode factor_node = res.reg(this->factor());
            if (res.error) return res.to_prs();
            return res.success(std::make_unique<UnaryOpNode>(tok, std::move(factor_node)));
        }
        if (current_tok.type == TokenType::INCREMENT ||
            current_tok.type == TokenType::DECREMENT) {

            Token op = current_tok;
            advance();

            AnyNode operand = res.reg(this->factor());
            if (res.error) return res.to_prs();

            return res.success(
                std::make_unique<UnaryOpNode>(op, std::move(operand), false) 
            );
        }


        return this->power();
    }
    Prs Parser::term() {
        return this->bin_op([this]() { return this->factor(); }, 
                            {TokenType::DIV, 
                            TokenType::MUL, 
                            TokenType::MOD});
    }
    Prs Parser::logical_and() {
        ParseResult res;
        AnyNode left = res.reg(this->comparison());
        if (res.error) return res.to_prs();

        while (this->current_tok.type == TokenType::AND) {
            Token op_tok = this->current_tok;
            this->advance();
            AnyNode right = res.reg(this->comparison());
            if (res.error) return res.to_prs();
            
            left = std::make_unique<BinOpNode>(std::move(left), op_tok, std::move(right));
        }

        return res.success(std::move(left));
    }

    Prs Parser::logical_or() {
        ParseResult res;
        AnyNode left = res.reg(this->logical_and());
        if (res.error) return res.to_prs();

        while (this->current_tok.type == TokenType::OR) {
            Token op_tok = this->current_tok;
            this->advance();
            AnyNode right = res.reg(this->logical_and());
            if (res.error) return res.to_prs();
            
            left = std::make_unique<BinOpNode>(std::move(left), op_tok, std::move(right));
        }

        return res.success(std::move(left));
    }
    Prs Parser::comparison() {
        ParseResult res;
        AnyNode left = res.reg(this->expr());
        if (res.error) return res.to_prs();

        while (this->current_tok.type == TokenType::EQ_TO ||
            this->current_tok.type == TokenType::NOT_EQ ||
            this->current_tok.type == TokenType::LESS ||
            this->current_tok.type == TokenType::LESS_EQ ||
            this->current_tok.type == TokenType::MORE ||
            this->current_tok.type == TokenType::MORE_EQ) {
            
            Token op_tok = this->current_tok;
            this->advance();
            AnyNode right = res.reg(this->expr());
            if (res.error) return res.to_prs();
            
            left = std::make_unique<BinOpNode>(std::move(left), op_tok, std::move(right));
        }

        return res.success(std::move(left));
    }
    Prs Parser::expr() {
        ParseResult res;
        AnyNode left = res.reg(this->term());
        if (res.error) return res.to_prs();

        while (this->current_tok.type != TokenType::SEMICOLON &&
            (this->current_tok.type == TokenType::PLUS || this->current_tok.type == TokenType::MINUS)) {
            Token op_tok = this->current_tok;
            this->advance();

            AnyNode right = res.reg(this->term());
            if (res.error) return res.to_prs();
            left = std::make_unique<BinOpNode>(std::move(left), op_tok, std::move(right));
        }

        return res.success(std::move(left));
    }
    Prs Parser::bin_op(std::function<Prs()> func, 
                   std::initializer_list<TokenType> ops) {
        ParseResult res;
        AnyNode left = res.reg(func());
        if (res.error) return res.to_prs();

        while (std::find(ops.begin(), ops.end(), this->current_tok.type) != ops.end()) {
            Token op_tok = this->current_tok;
            this->advance();
            
            AnyNode right = res.reg(func());
            if (res.error) return res.to_prs();

            left = std::make_unique<BinOpNode>(std::move(left), op_tok, std::move(right));
        }

        return res.success(std::move(left));
    }
    Prs Parser::assignment_expr() {
        ParseResult res;
        AnyNode left = res.reg(this->logical_or());
        if (res.error) return res.to_prs();
        if (this->current_tok.type == TokenType::EQ ||
            this->current_tok.type == TokenType::PLUS_EQ ||
            this->current_tok.type == TokenType::MINUS_EQ ||
            this->current_tok.type == TokenType::MUL_EQ ||
            this->current_tok.type == TokenType::DIV_EQ ||
            this->current_tok.type == TokenType::MOD_EQ) {
            if (!std::holds_alternative<std::unique_ptr<VarAccessNode>>(left)) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Left side of assignment must be a variable",
                    this->current_tok.pos
                ));
                return res.to_prs();
            }

            Token var = std::get<std::unique_ptr<VarAccessNode>>(left)->var_name_tok;
            Token op_tok = this->current_tok;
            this->advance();
            AnyNode right;
            if (op_tok.type == TokenType::EQ) {
                auto next_it = std::next(it);
                if (this->current_tok.type == TokenType::IDENTIFIER &&
                    next_it != tokens.end() && next_it->type == TokenType::EQ) {
                    right = res.reg(this->assignment_expr());
                } else {
                    right = res.reg(this->expr());
                }
            } else {
                right = res.reg(this->expr());
            }
            
            if (res.error) return res.to_prs();

            if (op_tok.type != TokenType::EQ) {
                TokenType binop_type;
                if (op_tok.type == TokenType::PLUS_EQ) binop_type = TokenType::PLUS;
                else if (op_tok.type == TokenType::MINUS_EQ) binop_type = TokenType::MINUS;
                else if (op_tok.type == TokenType::MUL_EQ) binop_type = TokenType::MUL;
                else if (op_tok.type == TokenType::DIV_EQ) binop_type = TokenType::DIV;
                else if (op_tok.type == TokenType::MOD_EQ) binop_type = TokenType::MOD;
                
                Token binop_tok(binop_type, "", op_tok.pos);
                AnyNode var_access = std::make_unique<VarAccessNode>(var);
                AnyNode expanded = std::make_unique<BinOpNode>(
                    std::move(var_access), 
                    binop_tok, 
                    std::move(right)
                );
                
                return res.success(std::make_unique<AssignExprNode>(var, std::move(expanded)));
            }

            return res.success(std::make_unique<AssignExprNode>(var, std::move(right)));
        }

        return res.success(std::move(left));
    }
    Prs Parser::statement() {
        ParseResult res;
        Token tok = this->current_tok;
        if (tok.type == TokenType::KEYWORD && tok.value == "if") {
            return this->if_expr();
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "switch") {
            return this->switch_stmt();
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "while") {
            return this->while_stmt();
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "for") {
            return this->for_stmt();
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "continue") {
            this->advance();
            if (current_tok.type != TokenType::SEMICOLON) {
                res.failure(std::make_unique<MissingSemicolonError>(current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            return res.success(std::make_unique<ContinueNode>(tok));
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "break") {
            this->advance();
            if (current_tok.type != TokenType::SEMICOLON) {
                res.failure(std::make_unique<MissingSemicolonError>(current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            return res.success(std::make_unique<BreakNode>(tok));
        }
        // Variable declaration: int x = 5; or const int x = 5;
        if (tok.type == TokenType::KEYWORD) {
            bool is_const = false;
            
            // Check for const
            if (tok.value == "const") {
                is_const = true;
                this->advance();
                tok = this->current_tok;
                
                if (tok.type != TokenType::KEYWORD) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected type after 'const'", this->current_tok.pos));
                    return res.to_prs();
                }
            }
            
            Token type_tok = tok;
            this->advance();
            
            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected identifier", this->current_tok.pos));
                return res.to_prs();
            }

            Token var_name = this->current_tok;
            this->advance();

            AnyNode value;
            if (this->current_tok.type == TokenType::EQ) {
                this->advance();
                value = res.reg(this->logical_or());
                if (res.error) return res.to_prs();
            } else {
                if (is_const) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "const variables must be initialized", var_name.pos));
                    return res.to_prs();
                }
                value = default_value_for_type(type_tok, var_name.pos);
            }
            
            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                return res.to_prs();
            }

            this->advance(); 
            return res.success(std::make_unique<VarAssignNode>(
                is_const, type_tok, var_name, std::move(value)));
        }

        // Assignment or compound assignment: x = 5; or x += 5;
        if (tok.type == TokenType::IDENTIFIER) {
            auto next_it = std::next(it);
            if (next_it != tokens.end() && 
                (next_it->type == TokenType::EQ ||
                next_it->type == TokenType::PLUS_EQ ||
                next_it->type == TokenType::MINUS_EQ ||
                next_it->type == TokenType::MUL_EQ ||
                next_it->type == TokenType::DIV_EQ ||
                next_it->type == TokenType::MOD_EQ)) {
                
                AnyNode assign_node = res.reg(this->assignment_expr());
                if (res.error) return res.to_prs();

                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                    return res.to_prs();
                }

                this->advance();
                return res.success(std::move(assign_node));
            }
        }

        // Expression statement: 2 + 3;
        AnyNode node = res.reg(this->logical_or()); 
        if (res.error) return res.to_prs();

        if (this->current_tok.type == TokenType::SEMICOLON) {
            this->advance(); 
            return res.success(std::move(node));
        }

        res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
        return res.to_prs();
    }

    Aer Parser::parse() {
        std::vector<AnyNode> stmts;
        
        while (this->current_tok.type != TokenType::EOFT) {
            Prs result = this->statement();

            if (std::holds_alternative<std::unique_ptr<Error>>(result)) {
                return Aer{
                    nullptr, 
                    std::get<std::unique_ptr<Error>>(std::move(result))
                };
            }

            AnyNode stmt = std::visit([](auto&& arg) -> AnyNode {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_constructible_v<AnyNode, T>) {
                    return AnyNode(std::move(arg));
                }
                return std::monostate{}; 
            }, std::move(result));
            
            stmts.push_back(std::move(stmt));
        }
                
        return Aer{
            std::make_unique<StatementsNode>(std::move(stmts)),
            nullptr
        };
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// VALUES ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    Number<T>::Number(T val) : value(val), pos("", "", 0, 0, 0) {}

    template <typename T>
    Number<T>& Number<T>::set_pos(Position p) { 
        this->pos = p;
        return *this;
    }

    template <typename T>
    std::string Number<T>::print() {
        return std::to_string(this->value);
    }

    // Explicit instantiations
    template class Number<int>;
    template class Number<float>;
    template class Number<double>;

//////////////////////////////////////////////////////////////////
// INTERPRETER //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
    bool is_truthy(const NumberVariant& val) {
        return std::visit([](auto&& v) -> bool {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, BoolValue>) {
                return v.value;
            } else if constexpr (std::is_same_v<T, Number<int>> || 
                                std::is_same_v<T, Number<float>> || 
                                std::is_same_v<T, Number<double>>) {
                return v.value != 0;
            } else if constexpr (std::is_same_v<T, StringValue>) {
                return !v.value.empty();
            }
            return false;
        }, val);
    }
    bool values_equal(const NumberVariant& a,
                  const NumberVariant& b,
                  const Position& pos)
    {
        if (a.index() != b.index()) {
            throw RTError("Cannot compare values of different types in switch/case", pos);
        }

        return std::visit([&](auto&& v) -> bool {
            using T = std::decay_t<decltype(v)>;

            if constexpr (std::is_same_v<T, StringValue>) {
                return v.value == std::get<StringValue>(b).value;
            } else if constexpr (std::is_same_v<T, CharValue>) {
                return v.value == std::get<CharValue>(b).value;
            } else if constexpr (std::is_same_v<T, BoolValue>) {
                return v.value == std::get<BoolValue>(b).value;
            } else if constexpr (
                std::is_same_v<T, Number<int>> ||
                std::is_same_v<T, Number<float>> ||
                std::is_same_v<T, Number<double>>
            ) {
                return static_cast<double>(v.value)
                    == static_cast<double>(std::get<T>(b).value);
            } else {
                throw RTError("Invalid switch comparison type", pos);
            }
        }, a);
    }
    NumberVariant Interpreter::process(AnyNode& node) {
        return std::visit(*this, node);
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<BreakNode>& node) {
        throw RTError("Unexpected 'break' outside loop or switch",
                    node ? node->tok.pos : Position());
    }
    ExecResult Interpreter::exec_stmt_in_loop_or_switch(AnyNode& node) {
        return std::visit([this](auto& n) -> ExecResult {
            using T = std::decay_t<decltype(n)>;

            if constexpr (std::is_same_v<T, std::monostate>) {
                return {};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<BreakNode>>) {
                return { Number<int>(0), true, false };
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ContinueNode>>) {
                return { Number<int>(0), false, true };
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<StatementsNode>>) {
                return exec_stmt_in_loop_or_switch(*n);
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<IfNode>>) {
                return exec_stmt_in_loop_or_switch(*n);
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<SwitchNode>>) {
                return exec_stmt_in_loop_or_switch(*n);
            }
            else {
                NumberVariant v = (*this)(n); 
                return { std::move(v), false, false };
            }


        }, node);
    }
    ExecResult Interpreter::exec_stmt_in_loop_or_switch(StatementsNode& block) {
        NumberVariant last = Number<int>(0);

        for (auto& stmt : block.statements) {
            ExecResult r = exec_stmt_in_loop_or_switch(stmt);
            last = std::move(r.value);

            if (r.did_break || r.did_continue)
                return r;
        }
        return { std::move(last), false, false };
    }
    ExecResult Interpreter::exec_stmt_in_loop_or_switch(IfNode& ifn) {

        if (ifn.init.has_value())
            process(ifn.init.value());

        if (is_truthy(process(ifn.condition))) {
            return exec_stmt_in_loop_or_switch(*ifn.then_branch);
        }

        for (auto& [cond, body] : ifn.elif_branches) {
            if (is_truthy(process(cond))) {
                return exec_stmt_in_loop_or_switch(*body);
            }
        }

        if (ifn.else_branch) {
            return exec_stmt_in_loop_or_switch(*ifn.else_branch);
        }

        return {};
    }
    ExecResult Interpreter::exec_stmt_in_loop_or_switch(SwitchNode& sw) {
        NumberVariant v = process(sw.value);

        for (auto& sec : sw.sections) {
            bool match = sec.is_default;

            for (auto& c : sec.cases) {
                Position expr_pos = std::visit([](auto& n) -> Position {
                    using T = std::decay_t<decltype(n)>;
                    if constexpr (requires { n.tok; }) {
                        return n.tok.pos;
                    } else if constexpr (requires { n->tok; }) {
                        return n->tok.pos;
                    } else {
                        return Position();
                    }
                }, c.expr);
                if (values_equal(process(c.expr), v, expr_pos)) {
                    match = true;
                    break;
                }
            }

            if (match) {
                AnyNode body = std::move(sec.body);
                ExecResult r = exec_stmt_in_loop_or_switch(body);
                

                if (r.did_break)
                    return { r.value, false, false };

                return r;
            }
        }
        return {};
    }




    NumberVariant Interpreter::operator()(std::unique_ptr<ContinueNode>& node) {
        throw RTError("Unexpected 'continue' outside loop",
                    node ? node->tok.pos : Position());
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<WhileNode>& node) {
        if (!node) return Number<int>(0);

        NumberVariant last = Number<int>(0);

        while (true) {
            NumberVariant cond_val = this->process(node->condition);
            if (!is_truthy(cond_val)) break;

            for (auto& stmt : node->body->statements) {
                ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                last = std::move(r.value);

                if (r.did_break) {
                    return last;
                }
                if (r.did_continue) {
                    goto while_update; 
                }
            }

        while_update:
            ;
        }

        return last;
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<ForNode>& node) {
        if (!node) return Number<int>(0);

        ScopeGuard guard(this->context); 
        NumberVariant last = Number<int>(0);

        if (node->init.has_value()) {
            last = this->process(node->init.value());
        }

        while (true) {
            NumberVariant cond_val = this->process(node->condition);
            if (!is_truthy(cond_val)) break;

            for (auto& stmt : node->body->statements) {
                ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                last = std::move(r.value);

                if (r.did_break) {
                    return last;      
                }
                if (r.did_continue) {
                    goto for_update;   
                }
            }

        for_update:
            if (node->update.has_value()) {
                last = this->process(node->update.value());
            }
        }

        return last;
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<SwitchNode>& node) {
        if (!node) return Number<int>(0);

        NumberVariant switch_val = this->process(node->value);

        int start_index = -1;
        int default_index = -1;
        for (int i = 0; i < (int)node->sections.size(); ++i) {
            auto& sec = node->sections[i];

            if (sec.is_default) {
                if (default_index == -1) default_index = i;
                continue;
            }

            for (auto& lbl : sec.cases) {
                NumberVariant case_val = this->process(lbl.expr);
                if (values_equal(switch_val, case_val, Position())) {
                    start_index = i;
                    break;
                }
            }
            if (start_index != -1) break;
        }

        if (start_index == -1) start_index = default_index;
        if (start_index == -1) return Number<int>(0); 

        NumberVariant last = Number<int>(0);

        for (int i = start_index; i < (int)node->sections.size(); ++i) {
            auto& sec = node->sections[i];
            if (!sec.body) continue;

            for (auto& stmt : sec.body->statements) {
                ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                last = std::move(r.value);
                if (r.did_break) {
                    return last;
                }
            }
        }

        return last;
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<VarAssignNode>& node) {
        NumberVariant value = this->process(node->value_node);
        
        std::string declaredType = node->type_tok.value;
        std::string actualType   = context->get_type_name(value);
        if (declaredType == "float" && actualType != "float") {
            throw RTError("Type mismatch: expected float literal", node->var_name_tok.pos);
        }
        if (declaredType == "double" && (actualType != "float" && actualType != "double")) {
            throw RTError("Type mismatch: expected double literal", node->var_name_tok.pos);
        }
        if (declaredType == "int" && (actualType != "int")) {
            throw RTError("Type mismatch: expected int literal", node->var_name_tok.pos);
        }
        if (declaredType == "bool" && actualType != "bool") {
            throw RTError("Type mismatch: expected bool literal", node->var_name_tok.pos);
        }
        
        context->define(node->var_name_tok.value, declaredType, value, node->is_const);
        return value;
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<StatementsNode>& node) {
        NumberVariant last_result = Number<int>(0);
        
        for (auto& stmt : node->statements) {
            ExecResult r = exec_stmt_in_loop_or_switch(stmt);
            last_result = r.value;

            if (r.did_break || r.did_continue)
                return last_result;
        }
        
        return last_result;
    }
    
    NumberVariant Interpreter::operator()(NumberNode& node) {
        const std::string& s = node.tok.value;

        try {
            if (node.tok.type == TokenType::FLOAT) {
                float val = std::stof(s);
                return Number<float>(val).set_pos(node.tok.pos);
            }
            if (s.find('.') != std::string::npos) {
                double val = std::stod(s);
                return Number<double>(val).set_pos(node.tok.pos);
            }

            int val = std::stoi(s);
            return Number<int>(val).set_pos(node.tok.pos);

        } catch (const std::out_of_range&) {
            throw RTError("Number is too large or too small (Overflow/Underflow)", node.tok.pos);
        }
    }

    NumberVariant Interpreter::operator()(std::unique_ptr<VarAccessNode>& node) {
        if (!context) {
            throw RTError("Context not initialized", node->var_name_tok.pos);
        }
        return context->get(node->var_name_tok.value, node->var_name_tok.pos);
    }
    std::string Interpreter::run_statements(std::unique_ptr<StatementsNode>& node) {
        std::string output = "";
        
        for (auto& stmt : node->statements) {
            ExecResult r = exec_stmt_in_loop_or_switch(stmt);
            auto result = r.value;

            output += std::visit([](auto&& val) -> std::string {
                using T = std::decay_t<decltype(val)>;
                if constexpr (std::is_same_v<T, std::monostate>) {
                    return "";
                } else {
                    return val.print() + "\n";
                }
            }, result);
        }
        
        return output;
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<BinOpNode>& node) {
        if (!node) return Number<int>(0);
        if (node->op_tok.type == TokenType::AND) {
            NumberVariant left = this->process(node->left_node);
            if (!is_truthy(left)) return BoolValue("false");
                NumberVariant right = this->process(node->right_node);
                return BoolValue(is_truthy(right) ? "true" : "false");
        }
    
        if (node->op_tok.type == TokenType::OR) {
            NumberVariant left = this->process(node->left_node);
            if (is_truthy(left)) return BoolValue("true");
                NumberVariant right = this->process(node->right_node);
                return BoolValue(is_truthy(right) ? "true" : "false");
        }
        NumberVariant left = this->process(node->left_node);
        NumberVariant right = this->process(node->right_node);

        return std::visit([this, &node](const auto& L, const auto& R) -> NumberVariant {
            using T1 = std::decay_t<decltype(L)>;
            using T2 = std::decay_t<decltype(R)>;
            if constexpr (std::is_same_v<T1, StringValue> && std::is_same_v<T2, StringValue>) {
                if (node->op_tok.type == TokenType::PLUS) {
                    return StringValue(L.value + R.value).set_pos(node->op_tok.pos);
                }
                throw RTError("Only '+' is supported for strings", node->op_tok.pos);
            } else if constexpr (std::is_same_v<T1, StringValue> ^ std::is_same_v<T2, StringValue>) {
                throw RTError("Cannot add string to number", node->op_tok.pos);
            } else if constexpr (std::is_same_v<T1, CharValue> || std::is_same_v<T2, CharValue>) {
                throw RTError("Cannot preform arithmetic on a Char", node->op_tok.pos);
            }
            else if constexpr (std::is_same_v<T1, std::monostate> || std::is_same_v<T2, std::monostate>) {
                throw RTError("Operation on uninitialized value", node->op_tok.pos);
            }
            else if constexpr (std::is_same_v<T1, BoolValue> || std::is_same_v<T2, BoolValue>) { 
                throw RTError("Cannot preform arithmetic operations on a Boolean", node->op_tok.pos);
            }
            else{ 
                return handle_binop(L, R, node->op_tok.type, this->error);
            }
        }, left, right);
    }
    NumberVariant Interpreter::operator()(tkz::CharNode& node) {
        CharValue cv(node.tok.value);
        return cv.set_pos(node.tok.pos);
    }
    NumberVariant Interpreter::operator()(tkz::BoolNode& node) {
        return BoolValue(node.tok.value).set_pos(node.tok.pos);
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<AssignExprNode>& node) {
        if (!node) return Number<int>(0);
        NumberVariant value = this->process(node->value);
        context->set(
            node->var_name.value,
            value,
            node->var_name.pos
        );

        return value;
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<UnaryOpNode>& node) {
        if (!node) return Number<int>(0);

        if (node->op_tok.type == TokenType::NOT) {
            NumberVariant val = this->process(node->node);
            return std::visit([](const auto& n) -> NumberVariant {
                return BoolValue(is_truthy(n) ? "false" : "true");
            }, val);
        }

        if (node->op_tok.type == TokenType::INCREMENT ||
            node->op_tok.type == TokenType::DECREMENT) {

            auto* var = std::get_if<std::unique_ptr<VarAccessNode>>(&node->node);
            if (!var) {
                throw RTError("Increment/decrement must target a variable",
                            node->op_tok.pos);
            }

            const std::string name = (*var)->var_name_tok.value;
            Position pos = (*var)->var_name_tok.pos;

            NumberVariant old_val = context->get(name, pos);

            NumberVariant new_val = std::visit([&](auto& n) -> NumberVariant {
                using T = std::decay_t<decltype(n)>;
                if constexpr (
                    !std::is_same_v<T, StringValue> &&
                    !std::is_same_v<T, CharValue> &&
                    !std::is_same_v<T, BoolValue>
                ) {
                    if (node->op_tok.type == TokenType::INCREMENT)
                        return n.added_to(Number<int>(1));
                    else
                        return n.subbed_by(Number<int>(1));
                }
                throw RTError("Invalid operand for ++/--", pos);
            }, old_val);

            context->set(name, new_val, pos);

            return node->is_postfix ? old_val : new_val;
        }

        NumberVariant number = this->process(node->node);

        return std::visit([&node](const auto& n) -> NumberVariant {
            using T = std::decay_t<decltype(n)>;

            if constexpr (
                !std::is_same_v<T, StringValue> &&
                !std::is_same_v<T, CharValue> &&
                !std::is_same_v<T, BoolValue> &&
                !std::is_same_v<T, std::monostate>
            ) {
                if (node->op_tok.type == TokenType::MINUS) {
                    return n.multed_by(Number<int>(-1));
                }
                return n;
            } else {
                throw RTError("Unary operator not supported for this type",
                            node->op_tok.pos);
            }
        }, number);
    }


    NumberVariant Interpreter::operator()(StringNode& node) {
        return StringValue(node.tok.value).set_pos(node.tok.pos);
    }
    NumberVariant Interpreter::operator()(std::monostate) {
        std::cerr << "Empty AST node encountered\n";
        return Number<int>(0);
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<IfNode>& node) {
        if (!node) return Number<int>(0);

        bool created_init_scope = false;
        ScopeGuard guard(this->context); 
        if (!node->init.has_value()) {
            guard.dismiss();
        } else {
            created_init_scope = true;
            this->process(node->init.value());
        }

        NumberVariant cond_val = this->process(node->condition);
        if (is_truthy(cond_val)) {
            NumberVariant last = Number<int>(0);
            for (auto& stmt : node->then_branch->statements) {
                ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                last = std::move(r.value);
                if (r.did_break || r.did_continue) {
                    return last;
                }
            }
            return last;
        }

        for (auto &p : node->elif_branches) {
            NumberVariant ev = this->process(p.first);
            if (is_truthy(ev)) {
                NumberVariant last = Number<int>(0);
                for (auto& stmt : p.second->statements) {
                    ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                    last = std::move(r.value);
                    if (r.did_break || r.did_continue) {
                        return last;
                    }
                }
                return last;
            }
        }

        if (node->else_branch) {
            NumberVariant last = Number<int>(0);
            for (auto& stmt : node->else_branch->statements) {
                ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                last = std::move(r.value);
                if (r.did_break || r.did_continue) {
                    return last;
                }
            }
            return last;
        }

        return Number<int>(0);
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// RUN //////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    Mer run(std::string file, std::string text, bool use_context) { 
        if (text.starts_with("// @no-context") || text.starts_with("# no-context")) {
            use_context = false;
        }
        Lexer lexer(text, file);
        Ler resp;
        try {
            resp = lexer.make_tokens();
        } catch(InvalidSyntaxError& e) {
            std::cout << '\n' << e.as_string() << '\n';
            return Mer{Aer{nullptr, nullptr}, std::move(resp), ""};
        }
        if (resp.error != nullptr) {
            return Mer{Aer{nullptr, std::move(resp.error)}, std::move(resp), ""};
        }
        
        // Parser
        Parser parser(resp.Tkns);
        Aer ast = parser.parse();
        if (ast.error) {
            return Mer{std::move(ast), std::move(resp), ""};
        }
        Context* ctx = use_context ? new Context() : nullptr;
        Interpreter interpreter(ctx);
        
        std::string output = "";
        if (ast.statements != nullptr) {
            try {
                for (auto& stmt : ast.statements->statements) {
                    auto result = interpreter.process(stmt);
                    
                    output += std::visit([](auto&& val) -> std::string {
                        using T = std::decay_t<decltype(val)>;
                        if constexpr (std::is_same_v<T, std::monostate>) {
                            return "";
                        } else {
                            return val.print() + "\n";
                        }
                    }, result);
                }
            } catch (RTError& e) {
                std::cout << e.as_string() << std::endl;
                if (ctx) delete ctx;
                ast.error = std::make_unique<RTError>(e);
                return Mer{std::move(ast), std::move(resp), ""};
            }
        }
        
        if (ctx) delete ctx;
        return Mer{std::move(ast), std::move(resp), output};
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
    Token Lexer::make_identifier() {
        std::string id = "";
        Position start_pos = this->pos.copy();
        while (this->current_char != '\0' && 
            (isalnum(this->current_char) || this->current_char == '_')) {
            id += this->current_char;
            this->advance();
        }
        if (id == "int" || id == "float" || id == "double" || id == "bool" || id == "case" ||
            id == "string" || id == "qbool" || id == "void" || id == "char" || id == "break" ||
            id == "if" || id == "else" || id == "while" || id == "for" || id == "switch" ||
            id == "return" || id == "qif" || id == "qswitch" || id == "const" || id == "default" ||
            id == "class" || id == "struct" || id == "enum" || id == "long" || id == "short" ||
            id == "continue") {
            return Token(TokenType::KEYWORD, id, start_pos);
        }
        if (id == "true" || id == "false") {
            return Token(TokenType::BOOL, id, start_pos);
        }
        return Token(TokenType::IDENTIFIER, id, start_pos);
    }
    Token Lexer::make_string() {
        std::string str = "";
        Position start_pos = this->pos.copy();
        bool escape_character = false;
        
        this->advance();

        while (this->current_char != '\0' && (this->current_char != '"' || escape_character)) {
            if (escape_character) {
                switch (this->current_char) {
                    case 'n': str += '\n'; break;
                    case 't': str += '\t'; break;
                    case 'r': str += '\r'; break;
                    case '\\': str += '\\'; break;
                    case '"': str += '\"'; break;
                    default: str += this->current_char; break;
                }
                escape_character = false;
            } else {
                if (this->current_char == '\\') {
                    escape_character = true;
                } else {
                    str += this->current_char;
                }
            }
            this->advance();
        }

        if (this->current_char != '"') {
            this->advance();
            throw IllegalCharError("Expected \"", this->pos);
        }

        this->advance();
        return Token(TokenType::STRING, str, start_pos);
    }
    Token Lexer::make_char() {
        Position start_pos = this->pos.copy();
        this->advance();

        std::string val = "";
        if (this->current_char == '\\') {
            this->advance();
            switch (this->current_char) {
                case 'n':  val = "\n"; break;
                case 't':  val = "\t"; break;
                case 'r':  val = "\r"; break;
                case '\'': val = "\'"; break;
                case '\\': val = "\\"; break;
                default:   val = std::string(1, this->current_char); break;
            }
            this->advance();
        } else {
            val = std::string(1, this->current_char);
            this->advance();
        }
        if (this->current_char != '\'') {
            throw IllegalCharError("Expected closing single quote", this->pos);
        }
        this->advance();
        
        return Token(TokenType::CHAR, val, start_pos);
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
            } else if (isCharInSet(this->current_char, LETTERS + "_")) {
                tokens.push_back(this->make_identifier());
            } else if (this->current_char == '"') {
                tokens.push_back(this->make_string());
                continue;
            } else if(this->current_char == '\'') {
                tokens.push_back(this->make_char());
            } else {
                switch (this->current_char) {
                    case '+':
                        this->advance();
                        if (current_char == '+') {
                            this->advance();
                            tokens.push_back(Token(TokenType::INCREMENT, "++", start_pos));
                        } else if (current_char == '=') {
                            this->advance();
                            tokens.push_back(Token(TokenType::PLUS_EQ, "+=", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::PLUS, "", start_pos));
                        }
                        break;

                    case '-':
                        this->advance();
                        if (current_char == '-') {
                            this->advance();
                            tokens.push_back(Token(TokenType::DECREMENT, "--", start_pos));
                        } else if (current_char == '=') {
                            this->advance();
                            tokens.push_back(Token(TokenType::MINUS_EQ, "-=", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::MINUS, "", start_pos));
                        }
                        break;
                    case '*':
                        this->advance();
                        if (current_char == '*') {
                            this->advance();
                            tokens.push_back(Token(TokenType::POWER, "**", start_pos));
                            break;
                        } else if (current_char == '=') {
                            this->advance();
                            tokens.push_back(Token(TokenType::MUL_EQ, "*=", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::MUL, "", start_pos));
                            break;
                        }
                        break;
                    case '/':
                        this->advance();
                        if (this->current_char == '/') {
                            while (this->current_char != '\0' && this->current_char != '\n') {
                                this->advance();
                            }
                            continue;
                        } else if (this->current_char == '*') {
                            this->advance();
                            while (this->current_char != '\0') {
                                if (this->current_char == '*') {
                                    this->advance();
                                    if (this->current_char == '/') {
                                        this->advance();
                                        break;
                                    }
                                } else {
                                    this->advance();
                                }
                            }
                            continue;
                        } else if (current_char == '=') {
                            this->advance();
                            tokens.push_back(Token(TokenType::DIV_EQ, "/=", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::DIV, "", start_pos));
                        }
                        break;
                    case '=':
                        this->advance();
                        if (current_char == '=') {
                            this->advance();
                            tokens.push_back(Token(TokenType::EQ_TO, "==", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::EQ, "", start_pos));
                            break;
                        }
                        break;
                    case '!':
                        this->advance();
                        if (current_char == '=') {
                            this->advance();
                            tokens.push_back(Token(TokenType::NOT_EQ, "!=", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::NOT, "!", start_pos));
                            break;
                        }
                        break;
                    case '>':
                        this->advance();
                        if (current_char == '=') {
                            this->advance();
                            tokens.push_back(Token(TokenType::MORE_EQ, ">=", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::MORE, "", start_pos));
                            break;
                        }
                        break;
                    case '<':
                        this->advance();
                        if (current_char == '=') {
                            this->advance();
                            tokens.push_back(Token(TokenType::LESS_EQ, "<=", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::LESS, "", start_pos));
                            break;
                        }
                        break;
                    case '(':
                        tokens.push_back(Token(TokenType::LPAREN, "", start_pos));
                        this->advance();
                        break;
                    case ')':
                        tokens.push_back(Token(TokenType::RPAREN, "", start_pos));
                        this->advance();
                        break;
                    case '{':
                        tokens.push_back(Token(TokenType::LBRACE, "{", start_pos));
                        this->advance();
                        break;
                    case '}':
                        tokens.push_back(Token(TokenType::RBRACE, "}", start_pos));
                        this->advance();
                        break;
                    case '%':
                        this->advance();
                        if (current_char == '=') {
                            this->advance();
                            tokens.push_back(Token(TokenType::MOD_EQ, "%=", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::MOD, "", start_pos));
                            break;
                        }
                        break;
                    case '&':
                        this->advance();
                        if (current_char == '&') {
                            this->advance();
                            tokens.push_back(Token(TokenType::AND, "&&", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::DEF, "&", start_pos));
                            break;
                        }
                        break;
                    case '|':
                        this->advance();
                        if (current_char == '|') {
                            this->advance();
                            tokens.push_back(Token(TokenType::OR, "||", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::DEF, "|", start_pos));
                            break;
                        }
                        break;
                    case ':':
                        this->advance();
                        tokens.push_back(Token(TokenType::COLON, ":", start_pos));
                        break;
                    case ';':
                        tokens.push_back(Token(TokenType::SEMICOLON, "", start_pos));
                        this->advance();
                        break;
                    default:
                        std::string unknown = std::string(1, this->current_char);
                        return Ler {std::list<Token>(), std::make_unique<IllegalCharError>(unknown, this->pos)};
                }
            }
        }
        tokens.push_back(Token(TokenType::EOFT, "", this->pos));
        return Ler {tokens, NULL};

    }
    
};


