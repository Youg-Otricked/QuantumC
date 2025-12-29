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
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<FuncDefNode>>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<CallNode>>) {
                return arg->print();
            } 
            else if constexpr (std::is_same_v<T, std::unique_ptr<QOutNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<QOutExprNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ReturnNode>>) {
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
    struct ReturnException {
        tkz::NumberVariant value;
        ReturnException(tkz::NumberVariant v) : value(std::move(v)) {}
    };
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
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<FuncDefNode>>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<CallNode>>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, QOutNode>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<QOutExprNode>>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ReturnNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MultiVarDeclNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MultiReturnNode>>) {  // ← ADD THIS!
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
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<FuncDefNode>>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<CallNode>>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, QOutNode>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<QOutExprNode>>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ReturnNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MultiVarDeclNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MultiReturnNode>>) {  // ← ADD THIS!
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
            {"KEYWORD", TokenType::KEYWORD}, {"EQ", TokenType::EQ}, {"EOFT", TokenType::EOFT}, {"ARROW", TokenType::ARROW}
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
                    value = res.reg(this->qout_expr());
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
                    value = res.reg(this->qout_expr());
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
    Prs Parser::func_def(Token return_type, std::optional<Token> func_name) {
        std::vector<Token> return_types = {return_type};
        return this->func_def_multi(return_types, func_name);
    }
    Prs Parser::call(AnyNode node_to_call) {
        ParseResult res;
        
        this->advance(); 
        
        std::list<AnyNode> args;
        
        
        if (this->current_tok.type != TokenType::RPAREN) {
            
            AnyNode arg = res.reg(this->logical_or());
            if (res.error) return res.to_prs();
            args.push_back(std::move(arg));
            
            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();  
                
                arg = res.reg(this->logical_or());
                if (res.error) return res.to_prs();
                args.push_back(std::move(arg));
            }
        }
        
        if (this->current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "Expected ')' after function arguments", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();  
        
        return res.success(std::make_unique<CallNode>(
            std::move(node_to_call), std::move(args)));
    }
    Prs Parser::qout_expr() {
        ParseResult res;
        AnyNode left = res.reg(this->logical_or());  
        if (res.error) return res.to_prs();
        if (std::holds_alternative<QOutNode>(left)) {
            std::vector<AnyNode> values;
            
            while (this->current_tok.type == TokenType::LSHIFT) {
                this->advance();  
                AnyNode value = res.reg(this->logical_or());
                if (res.error) return res.to_prs();
                values.push_back(std::move(value));
            }
            return res.success(std::make_unique<QOutExprNode>(std::move(values)));
        }
        
        return res.success(std::move(left));
    }
    Prs Parser::atom() {
        ParseResult res = ParseResult();
        Token tok = this->current_tok;
        if (tok.value == "std") {
            this->advance();
            if (this->current_tok.type == TokenType::SCOPE) {
                this->advance();
                if (this->current_tok.value == "qout") {
                    this->advance();
                    return res.success(QOutNode());
                }
            }
        }
        if (tok.type == TokenType::INT || tok.type == TokenType::FLOAT || tok.type == TokenType::DOUBLE) {
            this->advance();
            return res.success(NumberNode(tok));
        }  else if (tok.type == TokenType::STRING) {
            this->advance();
            return res.success(StringNode(tok));
        }
        else if (tok.type == TokenType::IDENTIFIER) {
            this->advance();
            if (this->current_tok.type == TokenType::LPAREN) {
                return this->call(std::make_unique<VarAccessNode>(tok));
            }
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

            if (this->current_tok.type == TokenType::RPAREN) {
                this->advance();
                return res.success(std::move(any_expr));
            } else {
                res.failure(std::make_unique<InvalidSyntaxError>(InvalidSyntaxError(
                    "Expected ')'", this->current_tok.pos
                )));
                return res.to_prs();
            }
        }
        else if (tok.type == TokenType::FSTRING) {
            this->advance();

            std::vector<std::string> parts;
            std::vector<std::string> exprs;

            std::string current = "";
            bool in_expr = false;

            for (char c : tok.value) {
                if (c == '\x01') {
                    if (in_expr) exprs.push_back(current);
                    else parts.push_back(current);
                    current = "";
                    in_expr = !in_expr;
                } else {
                    current += c;
                }
            }

            if (!current.empty()) {
                if (in_expr) exprs.push_back(current);
                else parts.push_back(current);
            }

            if (parts.empty()) parts.push_back("");

            AnyNode result = StringNode(Token(TokenType::STRING, parts[0], tok.pos));

            size_t num_exprs = exprs.size();

            for (size_t i = 0; i < num_exprs; i++) {
                Lexer expr_lexer(exprs[i], "<fstring>");
                auto expr_tokens = expr_lexer.make_tokens();
                Parser expr_parser(expr_tokens.Tkns);
                AnyNode expr_node = res.reg(expr_parser.logical_or());
                if (res.error) return res.to_prs();

                result = std::make_unique<BinOpNode>(
                    std::move(result),
                    Token(TokenType::PLUS, "+", tok.pos),
                    std::move(expr_node),
                    true
                );

                if (i + 1 < parts.size()) {
                    result = std::make_unique<BinOpNode>(
                        std::move(result),
                        Token(TokenType::PLUS, "+", tok.pos),
                        StringNode(Token(TokenType::STRING, parts[i + 1], tok.pos)),
                        true
                    );
                }
            }

            return res.success(std::move(result));
        }


        else if (tok.type == TokenType::KEYWORD && tok.value == "fn") {
            ParseResult pres;
            this->advance();

            Prs fn_pr = this->func_def(Token(TokenType::KEYWORD, "auto", tok.pos), std::nullopt);

            if (std::holds_alternative<std::unique_ptr<tkz::Error>>(fn_pr)) {
                return fn_pr;
            }

            if (!std::holds_alternative<std::shared_ptr<FuncDefNode>>(fn_pr)) {
                auto fn_ptr = std::get<std::shared_ptr<FuncDefNode>>(std::move(fn_pr));
                AnyNode fn_node = fn_ptr;

                if (this->current_tok.type == TokenType::LPAREN) {
                    return this->call(std::move(fn_node));
                }

                return pres.success(std::move(fn_node)); 
            }
            auto fn_ptr = std::get<std::shared_ptr<FuncDefNode>>(std::move(fn_pr));
            AnyNode fn_node = AnyNode{std::move(fn_ptr)};

            if (this->current_tok.type == TokenType::LPAREN) {
                return this->call(std::move(fn_node));
            }

            return pres.success(std::move(fn_node));
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
    Prs Parser::return_stmt() {
        ParseResult res;
        Position start_pos = this->current_tok.pos;
        
        this->advance();
        
        if (this->current_tok.type == TokenType::SEMICOLON) {
            this->advance();
            return res.success(std::make_unique<ReturnNode>(
                std::monostate{}, start_pos));
        }
        
        std::vector<AnyNode> values;
        values.push_back(res.reg(this->logical_or()));
        if (res.error) {
            return res.to_prs();
        }
        
        
        while (this->current_tok.type == TokenType::COMMA) {
            this->advance();
            values.push_back(res.reg(this->logical_or()));
            if (res.error) return res.to_prs();
        }
        
        
        if (this->current_tok.type != TokenType::SEMICOLON) {
            res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        
        if (values.size() == 1) {
            return res.success(std::make_unique<ReturnNode>(
                std::move(values[0]), start_pos));
        }

        return res.success(std::make_unique<MultiReturnNode>(
            std::move(values), start_pos));
    }
    Prs Parser::assignment_expr() {
        ParseResult res;
    
        AnyNode left = res.reg(this->qout_expr());
    
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
    static bool is_statement_node(const Prs& st) {
        return std::visit([](auto&& arg) -> bool {
            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, std::unique_ptr<Error>>) {
                return true;
            }

            if constexpr (std::is_same_v<T, ParseResult> ||
                        std::is_same_v<T, std::monostate>) {
                return false;
            }

            return true;
        }, st);
    }
    AnyNode to_any_node(Prs&& prs) {
        return std::visit([](auto&& arg) -> AnyNode {
            using T = std::decay_t<decltype(arg)>;
            

            if constexpr (std::is_same_v<T, std::unique_ptr<tkz::Error>>) {
                return std::monostate{};
            } else if constexpr (std::is_same_v<T, tkz::ParseResult>) {
                return std::move(arg.node);
            } else if constexpr (
                std::is_same_v<T, tkz::QOutNode> ||
                std::is_same_v<T, std::unique_ptr<tkz::BinOpNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::UnaryOpNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::VarAccessNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::VarAssignNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::AssignExprNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::IfNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::StatementsNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::SwitchNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::BreakNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::WhileNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::ForNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::ContinueNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::CallNode>> ||
                std::is_same_v<T, std::shared_ptr<tkz::FuncDefNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::QOutExprNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::ReturnNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::MultiReturnNode>> ||
                std::is_same_v<T, std::unique_ptr<tkz::MultiVarDeclNode>>
            ) {
                return std::move(arg);
            } else {
                return arg;
            }
        }, std::move(prs));
    }


    Prs Parser::func_def_multi(std::vector<Token> return_types, std::optional<Token> func_name) {
        ParseResult res;
        this->advance();  
        
        std::list<Parameter> params;
        
        if (this->current_tok.type != TokenType::RPAREN) {
            Token param_type = this->current_tok;
            this->advance();
            Token param_name = this->current_tok;
            this->advance();
            
            std::optional<AnyNode> default_val;
            if (this->current_tok.type == TokenType::EQ) {
                this->advance(); 
                default_val = res.reg(this->logical_or());
                if (res.error) return res.to_prs();
            }
            
            params.push_back({param_type, param_name, std::move(default_val)});
            
            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                
                param_type = this->current_tok;
                this->advance();
                param_name = this->current_tok;
                this->advance();
                
                default_val = std::nullopt;
                if (this->current_tok.type == TokenType::EQ) {
                    this->advance();
                    default_val = res.reg(this->logical_or());
                    if (res.error) return res.to_prs();
                }
                
                params.push_back({param_type, param_name, std::move(default_val)});
            }
        }
        
        if (this->current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "Expected ')' after parameters", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance(); 
        
        if (this->current_tok.type != TokenType::LBRACE) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "Expected '{' to start function body", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();  
        
        std::vector<AnyNode> body_stmts;
        while (true) {
            if (this->current_tok.type == TokenType::RBRACE)
                break;

            if (this->current_tok.type == TokenType::EOFT) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Unexpected end of file in function body",
                    this->current_tok.pos
                ));
                return res.to_prs();
            }

            Prs st = this->statement();

            if (std::holds_alternative<std::unique_ptr<Error>>(st)) {
                res.failure(std::get<std::unique_ptr<Error>>(std::move(st)));
                return res.to_prs();
            }

            if (!is_statement_node(st)) {
                continue;
            }

            AnyNode node = to_any_node(std::move(st));

            if (std::holds_alternative<std::monostate>(node)) {
                continue;
            }

            body_stmts.push_back(std::move(node));
        }

        if (this->current_tok.type != TokenType::RBRACE) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "Expected '}' to end function body", this->current_tok.pos));
            return res.to_prs();
        }
        
        auto body = std::make_unique<StatementsNode>(std::move(body_stmts));
        this->advance();  
        
        return res.success(std::make_unique<FuncDefNode>(
            return_types,  
            func_name, 
            std::move(params), 
            std::move(body)));
    }
    Prs Parser::statement() {
        ParseResult res;
        Token tok = this->current_tok;
        if (tok.type == TokenType::KEYWORD && tok.value == "fn") {
            this->advance();
            
            if (this->current_tok.type != TokenType::LPAREN) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected '(' after 'fn'", this->current_tok.pos));
                return res.to_prs();
            }
            
            Token dummy_return_type(TokenType::KEYWORD, "auto", tok.pos);
            std::vector<Token> return_types = {dummy_return_type};
            return this->func_def_multi(return_types, std::nullopt);
}
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
        if (tok.type == TokenType::KEYWORD && tok.value == "return") {
            return this->return_stmt();
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

            std::vector<Token> return_types = {type_tok};
            if (this->current_tok.type == TokenType::COMMA) {
                while (this->current_tok.type == TokenType::COMMA) {
                    this->advance();
                    
                    if (this->current_tok.type != TokenType::KEYWORD) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Expected type", this->current_tok.pos));
                        return res.to_prs();
                    }
                    
                    return_types.push_back(this->current_tok);
                    this->advance();
                }
                
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected identifier", this->current_tok.pos));
                    return res.to_prs();
                }
                
                Token name_tok = this->current_tok;
                this->advance();
                
                if (this->current_tok.type == TokenType::LPAREN) {
                    auto func_def = res.reg(this->func_def_multi(return_types, name_tok));
                    if (res.error) return res.to_prs();
                    return res.success(std::move(func_def));
                }
                
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Invalid syntax: use 'int x, string y = ...' for multi-variable declarations",
                    name_tok.pos));
                return res.to_prs();
            }

            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected identifier", this->current_tok.pos));
                return res.to_prs();
            }

            Token name_tok = this->current_tok;
            this->advance();

            if (this->current_tok.type == TokenType::LPAREN) {
                auto func_def = res.reg(this->func_def_multi(return_types, name_tok));
                if (res.error) return res.to_prs();
                return res.success(std::move(func_def));
            }
            std::vector<Token> var_names = {name_tok};

            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                
                if (this->current_tok.type != TokenType::KEYWORD) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected type", this->current_tok.pos));
                    return res.to_prs();
                }
                return_types.push_back(this->current_tok);
                this->advance();
                
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected identifier", this->current_tok.pos));
                    return res.to_prs();
                }
                var_names.push_back(this->current_tok);
                this->advance();
            }

            
            AnyNode value;
            if (this->current_tok.type == TokenType::LPAREN) {
                auto func_def = res.reg(this->func_def_multi(return_types, std::make_optional(var_names[0])));
                if (res.error) return res.to_prs();
                return res.success(std::move(func_def));
            }
            if (this->current_tok.type == TokenType::EQ) {
                this->advance();
                value = res.reg(this->qout_expr());
                if (res.error) return res.to_prs();
            } else {
                if (is_const) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "const variables must be initialized", var_names[0].pos));
                    return res.to_prs();
                }
                value = default_value_for_type(type_tok, var_names[0].pos);
            }
            
            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                return res.to_prs();
            }

            this->advance();  
            if (return_types.size() > 1 || var_names.size() > 1) {
                
                
                if (return_types.size() != var_names.size()) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Number of types must match number of variables", var_names[0].pos));
                    return res.to_prs();
                }
                return res.success(std::make_unique<MultiVarDeclNode>(
                    is_const, return_types, var_names, std::move(value)));
            } else {
                return res.success(std::make_unique<VarAssignNode>(
                    is_const, return_types[0], var_names[0], std::move(value)));
            }
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
        AnyNode node = res.reg(this->assignment_expr()); 
        if (res.error) return res.to_prs();

        if (this->current_tok.type == TokenType::SEMICOLON) {
            this->advance(); 
            return res.success(std::move(node));
        }

        res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
        return res.to_prs();
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
        bool has_main = false;
        std::shared_ptr<FuncDefNode> main_func_ptr = nullptr;
        
        while (this->current_tok.type != TokenType::EOFT) {
            Prs result = this->statement();
            
            if (std::holds_alternative<std::unique_ptr<Error>>(result)) {
                return Aer{nullptr, std::get<std::unique_ptr<Error>>(std::move(result))};
            }

            AnyNode stmt = std::visit([&has_main, &main_func_ptr](auto&& arg) -> AnyNode {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, std::shared_ptr<FuncDefNode>>) {
                    if (arg->name_tok.has_value() && arg->name_tok->value == "main") {
                        if (arg->return_types.empty() || arg->return_types[0].value != "int") {
                            std::string actual = arg->return_types.empty() ? "void" : arg->return_types[0].value;
                            throw InvalidSyntaxError("main() must return int, not " + actual, 
                                                    arg->return_types.empty() ? Position() : arg->return_types[0].pos);
                        }
                        if (!arg->params.empty()) {
                            throw InvalidSyntaxError("main() must have no parameters", 
                                arg->return_types.empty() ? Position() : arg->return_types[0].pos);
                        }
                        has_main = true;
                        main_func_ptr = arg;
                    }
                }
                
                if constexpr (std::is_constructible_v<AnyNode, T>) {
                    return AnyNode(std::move(arg));
                }
                return std::monostate{}; 
            }, std::move(result));
            
            stmts.push_back(std::move(stmt));
        }
        
        if (!has_main) {
            return Aer{nullptr, std::make_unique<Error>(
                "Missing main function", 
                "Program must have an 'int main()' function", 
                Position())};
        }
        
        return Aer{std::make_unique<StatementsNode>(std::move(stmts)), nullptr};
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
            } else if constexpr (std::is_same_v<T, MultiValue>) { 
                return true; 
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
            } else if constexpr (std::is_same_v<T, std::shared_ptr<MultiValue>>) {
                throw RTError("Cannot compare multi-values in switch", pos);
            } else {
                throw RTError("Invalid switch comparison type", pos);
            }
        }, a);
    }
    NumberVariant Interpreter::process(AnyNode& node) {
        
        return std::visit([this](auto& n) -> NumberVariant {
            using T = std::decay_t<decltype(n)>;
            return (*this)(n);
        }, node);
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<BreakNode>& node) {
        throw RTError("Unexpected 'break' outside loop or switch",
                    node ? node->tok.pos : Position());
    }
    NumberVariant Interpreter::operator()(std::shared_ptr<FuncDefNode>& node) {
        if (!node) return std::move(Number<int>(0));

        if (node->name_tok.has_value()) {
            context->define_function(node->name_tok->value, node);
            return std::move(Number<int>(0));
        }

        FunctionValue fv(node);
        return std::move(fv);
    }
    ExecResult Interpreter::exec_stmt_in_loop_or_switch(AnyNode& node) {
        return std::visit([this](auto& n) -> ExecResult {
            using T = std::decay_t<decltype(n)>;

            if constexpr (std::is_same_v<T, std::monostate>) {
                return {};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<BreakNode>>) {
                return { Number<int>(0), true, false, false };
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ContinueNode>>) {
                return { Number<int>(0), false, true, false };
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
            else if constexpr (std::is_same_v<T, std::unique_ptr<ReturnNode>>) {
                NumberVariant v;
                if (!n) v = Number<int>(0);
                else {
                    if (std::holds_alternative<std::monostate>(n->value)) {
                        v = VoidValue().set_pos(n->pos);
                    } else {
                        v = (*this)(n);
                    }
                }
                return ExecResult(std::move(v), false, false, true);
            }
            else {
                NumberVariant v = (*this)(n);
                return ExecResult(std::move(v), false, false, false);
            }
        }, node);
    }
    ExecResult Interpreter::exec_stmt_in_loop_or_switch(StatementsNode& block) {
        NumberVariant last = Number<int>(0);

        for (auto& stmt : block.statements) {
            ExecResult r = exec_stmt_in_loop_or_switch(stmt);
            last = std::move(r.value);

            if (r.did_break || r.did_continue || r.did_return)
                return r;
        }
        return { std::move(last), false, false, false };
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<VarAssignNode>& node) {
        if (!node) return std::move(Number<int>(0));
        NumberVariant value = this->process(node->value_node);

        std::string declaredType = node->type_tok.value;
        std::string actualType = context->get_type_name(value);

        if (declaredType != "auto") {
            bool type_matches = false;
            
            if (declaredType == "float" && actualType == "float") {
                type_matches = true;
            } else if (declaredType == "double" && (actualType == "float" || actualType == "double")) {
                type_matches = true;
            } else if (declaredType == "int" && actualType == "int") {
                type_matches = true;
            } else if (declaredType == "bool" && actualType == "bool") {
                type_matches = true;
            } else if (declaredType == "string" && actualType == "string") {
                type_matches = true;
            } else if (declaredType == "char" && actualType == "char") {
                type_matches = true;
            } else if (declaredType == "function" && actualType == "function") {
                type_matches = true;
            }
            
            if (!type_matches) {
                throw RTError(
                    "Type mismatch: expected " + declaredType + ", got " + actualType,
                    node->var_name_tok.pos
                );
            }
        }

        context->define(node->var_name_tok.value, 
                        declaredType == "auto" ? actualType : declaredType, 
                        std::move(value), 
                        node->is_const);
        return std::move(value);
    }
    ExecResult Interpreter::exec_stmt_in_loop_or_switch(IfNode& ifn) {
        if (ifn.init.has_value())
            process(ifn.init.value());

        NumberVariant cond_val = this->process(ifn.condition);
        if (is_truthy(cond_val)) {
            return exec_stmt_in_loop_or_switch(*ifn.then_branch);
        }

        for (auto& [cond, body] : ifn.elif_branches) {
            NumberVariant ev = this->process(cond);
            if (is_truthy(ev)) {
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
                    return { std::move(r.value), false, false, false };

                return r;
            }
        }
        return {};
    }




    NumberVariant Interpreter::operator()(std::unique_ptr<ContinueNode>& node) {
        throw RTError("Unexpected 'continue' outside loop",
                    node ? node->tok.pos : Position());
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<MultiReturnNode>& node) {
        
        std::vector<NumberVariant> return_values;
        for (size_t i = 0; i < node->values.size(); i++) {
            auto val = this->process(node->values[i]);
            return_values.push_back(std::move(val));
        }
        
        throw MultiReturnException(std::move(return_values));
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<WhileNode>& node) {
        if (!node) return std::move(Number<int>(0));

        NumberVariant last = Number<int>(0);

        while (true) {
            NumberVariant cond_val = this->process(node->condition);
            if (!is_truthy(cond_val)) break;

            for (auto& stmt : node->body->statements) {
                ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                last = std::move(r.value);

                if (r.did_break) {
                    return std::move(last);
                }
                if (r.did_continue) {
                    goto while_update; 
                }
            }

        while_update:
            ;
        }

        return std::move(last);
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<QOutExprNode>& node) {
        if (!node) return std::move(Number<int>(0));
        
        for (auto& val : node->values) {
            NumberVariant result = this->process(val);
            std::cout << std::visit([](auto&& v) -> std::string {if constexpr (requires { v->print(); }) {return v->print();} else {return v.print();}}, std::move(result));
        }
        
        return std::move(Number<int>(0));
    }
    NumberVariant Interpreter::operator()(QOutNode& node) {
        return std::move(Number<int>(0));
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<ForNode>& node) {
        if (!node) return std::move(Number<int>(0));

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
                    return std::move(last);      
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

        return std::move(last);
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<SwitchNode>& node) {
        if (!node) return std::move(Number<int>(0));

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
                    return std::move(last);
                }
            }
        }

        return last;
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<ReturnNode>& node) {
        if (!node) return std::move(Number<int>(0));

        if (std::holds_alternative<std::monostate>(node->value)) {
            throw ReturnException(VoidValue().set_pos(node->pos));
        }

        NumberVariant val = this->process(node->value);
        throw ReturnException(std::move(val));
    }
    NumberVariant def_value_for_type(const std::string& type_name) {
        if (type_name == "int") return Number<int>(0);
        else if (type_name == "float") return Number<float>(0.0f);
        else if (type_name == "double") return Number<double>(0.0);
        else if (type_name == "string") return StringValue("");
        else if (type_name == "char") return CharValue("");
        else if (type_name == "bool") return BoolValue("");
        else return VoidValue();
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<CallNode>& node) {
        if (!node) return Number<int>(0);

        NumberVariant target_val;
        std::string func_name = "<anonymous>";

        if (std::holds_alternative<std::unique_ptr<VarAccessNode>>(node->node_to_call)) {
            auto& varacc = std::get<std::unique_ptr<VarAccessNode>>(node->node_to_call);
            func_name = varacc->var_name_tok.value;

            if (func_name == "print" || func_name == "println") {
                for (auto& arg : node->arg_nodes)
                    std::cout << std::visit([](auto&& v) -> std::string { 
                        if constexpr (requires { v->print(); }) return v->print();
                        else return v.print(); 
                    }, this->process(arg));
                if (func_name == "println") std::cout << std::endl;
                return Number<int>(0);
            }

            try { target_val = context->get(func_name, varacc->var_name_tok.pos); }
            catch (RTError&) {
                auto func = context->get_function(func_name);
                if (!func) throw RTError("Undefined function: '" + func_name + "'", Position());
                target_val = FunctionValue(func);
            }
        } else {
            target_val = this->process(node->node_to_call);
        }

        if (!std::holds_alternative<FunctionValue>(target_val))
            throw RTError("Can only call functions", Position());

        FunctionValue fval = std::get<FunctionValue>(target_val);
        if (!fval.func) throw RTError("Invalid function value", Position());

        auto func = fval.func;
        context->push_scope();
        
        try {
            
            for (size_t i = 0; i < func->params.size(); i++) {
                NumberVariant value;
                auto it_param = func->params.begin();
                std::advance(it_param, i);

                if (i < node->arg_nodes.size()) {
                    auto it_arg = node->arg_nodes.begin();
                    std::advance(it_arg, i);
                    value = this->process(*it_arg);
                }
                else if (it_param->default_value.has_value()) {
                    value = this->process(it_param->default_value.value());
                }
                else throw RTError("Missing argument", Position());

                std::string expected_type = it_param->type.value;
                std::string actual_type = context->get_type_name(value);

                if (expected_type == "auto") {
                    context->define(it_param->name.value, actual_type, value);
                } else {
                    if (expected_type != actual_type) {
                        context->pop_scope();
                        throw RTError("Argument type mismatch", Position());
                    }
                    context->define(it_param->name.value, expected_type, value);
                }
            }
            for (auto& stmt : func->body->statements) {
                this->process(stmt);
            }
            
            
            if (func->return_types.size() > 1) {
                std::vector<NumberVariant> defaults;
                for (auto& rt : func->return_types)
                    defaults.push_back(def_value_for_type(rt.value));
                context->pop_scope();
                return std::make_shared<MultiValue>(std::move(defaults));
            } else if (func->return_types.size() == 1) {
                context->pop_scope();
                return def_value_for_type(func->return_types[0].value);
            } else {
                context->pop_scope();
                return VoidValue();
            }
            
        } catch (ReturnException& re) {
            context->pop_scope();
            return std::move(re.value);
            
        } catch (MultiReturnException& mre) {
            context->pop_scope();
            return std::make_shared<MultiValue>(std::move(mre.values));
            
        } catch (...) {
            context->pop_scope();
            throw;
        }
    }

    NumberVariant Interpreter::operator()(std::unique_ptr<StatementsNode>& node) {
        NumberVariant last_result = Number<int>(0);
        
        for (auto& stmt : node->statements) {
            ExecResult r = exec_stmt_in_loop_or_switch(stmt);
            last_result = std::move(r.value);

            if (r.did_break || r.did_continue)
                return std::move(last_result);
        }
        
        return std::move(last_result);
    }
    
    NumberVariant Interpreter::operator()(NumberNode& node) {
        const std::string& s = node.tok.value;

        try {
            if (node.tok.type == TokenType::FLOAT) {
                float val = std::stof(s);
                return std::move(Number<float>(val).set_pos(node.tok.pos));
            }
            if (s.find('.') != std::string::npos) {
                double val = std::stod(s);
                return std::move(Number<double>(val).set_pos(node.tok.pos));
            }

            int val = std::stoi(s);
            return std::move(Number<int>(val).set_pos(node.tok.pos));

        } catch (const std::out_of_range&) {
            throw RTError("Number is too large or too small (Overflow/Underflow)", node.tok.pos);
        }
    }

    NumberVariant Interpreter::operator()(std::unique_ptr<VarAccessNode>& node) {
        if (!context) {
            throw RTError("Context not initialized", node->var_name_tok.pos);
        }
        auto result = context->get(node->var_name_tok.value, node->var_name_tok.pos);
        return result;
    }


    std::string Interpreter::run_statements(std::unique_ptr<StatementsNode>& node) {
        std::string output = "";
        
        for (auto& stmt : node->statements) {
            ExecResult r = exec_stmt_in_loop_or_switch(stmt);
            auto result = std::move(r.value);

            output += std::visit([](auto&& val) -> std::string {
                using T = std::decay_t<decltype(val)>;
                if constexpr (std::is_same_v<T, std::monostate>) {
                    return "";
                } else if constexpr (std::is_same_v<T, std::shared_ptr<MultiValue>>) {
                    return val->print() + "\n";
                } else {
                    return val.print() + "\n";
                }
            }, result);
        }
        
        return output;
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<BinOpNode>& node) {
        if (!node) return std::move(Number<int>(0));
        if (node->op_tok.type == TokenType::AND) {
            NumberVariant left = std::move(this->process(node->left_node));
            if (!is_truthy(left)) return std::move(BoolValue("false"));
                NumberVariant right = std::move(this->process(node->right_node));
                return std::move(BoolValue(is_truthy(right) ? "true" : "false"));
        }
    
        if (node->op_tok.type == TokenType::OR) {
            NumberVariant left = std::move(this->process(node->left_node));
            if (is_truthy(left)) return std::move(BoolValue("true"));
                NumberVariant right = std::move(this->process(node->right_node));
                return std::move(BoolValue(is_truthy(right) ? "true" : "false"));
        }
        NumberVariant left = std::move(this->process(node->left_node));
        NumberVariant right = std::move(this->process(node->right_node));

        return std::visit([this, &node](const auto& L, const auto& R) -> NumberVariant {
            using T1 = std::decay_t<decltype(L)>;
            using T2 = std::decay_t<decltype(R)>;
            if (node->is_f) {
                auto to_string_variant = [](auto&& v) -> std::string {
                    using T = std::decay_t<decltype(v)>;
                    if constexpr (std::is_same_v<T, Number<int>> ||
                                std::is_same_v<T, Number<double>> ||
                                std::is_same_v<T, Number<float>>)
                        return std::to_string(v.value);
                    else if constexpr (std::is_same_v<T, CharValue>)
                        return std::string(1, v.value);
                    else if constexpr (std::is_same_v<T, BoolValue>)
                        return v.value ? "true" : "false";
                    else if constexpr (std::is_same_v<T, StringValue>)
                        return v.value;
                    else if constexpr (std::is_same_v<T, VoidValue>)
                        return "<void>";
                    else
                        return "<unknown>";
                };

                auto l_str = std::move(to_string_variant(L));
                auto r_str = std::move(to_string_variant(R));

                return std::move(StringValue(l_str + r_str).set_pos(node->op_tok.pos));
            }

            else if constexpr (std::is_same_v<T1, StringValue> && std::is_same_v<T2, StringValue>) {
                if (node->op_tok.type == TokenType::PLUS) {
                    return std::move(StringValue(L.value + R.value).set_pos(node->op_tok.pos));
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
            else if constexpr (std::is_same_v<T1, FunctionValue> || std::is_same_v<T2, FunctionValue>) { 
                throw RTError("Cannot preform arithmetic operations on a Function", node->op_tok.pos);
            }
            else if constexpr (std::is_same_v<T1, VoidValue> || std::is_same_v<T2, VoidValue>) { 
                throw RTError("Cannot preform arithmetic operations on nothing", node->op_tok.pos);
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<MultiValue>> || std::is_same_v<T2, std::shared_ptr<MultiValue>>) { 
                throw RTError("How ius a return value in this function", node->op_tok.pos);
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<MultiValue>> || 
                            std::is_same_v<T2, std::shared_ptr<MultiValue>>) {
                throw RTError("Cannot perform arithmetic on multi-return values", node->op_tok.pos);
            }
            else{ 
                return std::move(handle_binop(L, R, node->op_tok.type, this->error));
            }
        }, left, right);
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<MultiVarDeclNode>& node) {

        std::shared_ptr<MultiValue> mv;

        try {
            auto result = this->process(node->value);
            mv = std::get_if<std::shared_ptr<MultiValue>>(&result)
                    ? std::move(*std::get_if<std::shared_ptr<MultiValue>>(&result))
                    : nullptr;
        } catch (MultiReturnException& mre) {
            mv = std::make_shared<MultiValue>(std::move(mre.values));
        }

        if (!mv) {
            throw RTError("Expected multi-return value", node->var_names[0].pos);
        }

        if (mv->values.size() != node->var_names.size()) {
            throw RTError(
                "Expected " + std::to_string(node->var_names.size()) +
                " values, got " + std::to_string(mv->values.size()),
                node->var_names[0].pos
            );
        }

        for (size_t i = 0; i < node->var_names.size(); i++) {

            context->define(
                node->var_names[i].value,
                node->type_toks[i].value,
                std::move(mv->values[i]),
                node->is_const
            );
        }

        return VoidValue();
    }
    NumberVariant Interpreter::operator()(tkz::CharNode& node) {
        CharValue cv(node.tok.value);
        return std::move(cv.set_pos(node.tok.pos));
    }
    NumberVariant Interpreter::operator()(tkz::BoolNode& node) {
        return std::move(BoolValue(node.tok.value).set_pos(node.tok.pos));
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<AssignExprNode>& node) {
        if (!node) return Number<int>(0);
        NumberVariant value = std::move(this->process(node->value));
        context->set(node->var_name.value, std::move(value), node->var_name.pos);

        return std::move(value);
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<UnaryOpNode>& node) {
        if (!node) return Number<int>(0);
        
        if (node->op_tok.type == TokenType::NOT) {
            
            NumberVariant val = std::move(this->process(node->node));
            return std::visit([&](auto&& n) -> NumberVariant {
                using T = std::decay_t<decltype(n)>;
                if constexpr (std::is_same_v<T, std::shared_ptr<MultiValue>>) {
                    throw RTError("Cannot use ! operator on multi-return values", node->op_tok.pos);
                } else {
                    return std::move(BoolValue(is_truthy(n) ? "false" : "true"));
                }
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

            NumberVariant old_val = std::move(context->get(name, pos));

            NumberVariant new_val = std::move(std::visit([&](auto& n) -> NumberVariant {
                using T = std::decay_t<decltype(n)>;
                if constexpr (
                    !std::is_same_v<T, StringValue> &&
                    !std::is_same_v<T, CharValue> &&
                    !std::is_same_v<T, BoolValue> &&
                    !std::is_same_v<T, FunctionValue> &&
                    !std::is_same_v<T, VoidValue> &&
                    !std::is_same_v<T, std::shared_ptr<MultiValue>>
                ) {
                    if (node->op_tok.type == TokenType::INCREMENT)
                        return std::move(n.added_to(Number<int>(1)));
                    else
                        return std::move(n.subbed_by(Number<int>(1)));
                }
                throw RTError("Invalid operand for ++/--", pos);
            }, old_val));

            context->set(name, std::move(new_val), pos);
            return std::move(node->is_postfix ? old_val : new_val);
        }

        NumberVariant number = std::move(this->process(node->node));

        return std::move(std::visit([&node](const auto& n) -> NumberVariant {
            using T = std::decay_t<decltype(n)>;

            if constexpr (
                !std::is_same_v<T, StringValue> &&
                !std::is_same_v<T, CharValue> &&
                !std::is_same_v<T, BoolValue> &&
                !std::is_same_v<T, FunctionValue> &&
                !std::is_same_v<T, VoidValue> &&
                !std::is_same_v<T, std::monostate> &&
                !std::is_same_v<T, std::shared_ptr<MultiValue>>
            ) {
                if (node->op_tok.type == TokenType::MINUS) {
                    return std::move(n.multed_by(Number<int>(-1)));
                }
                return std::move(n);
            } else {
                throw RTError("Unary operator not supported for this type",
                            node->op_tok.pos);
            }
        }, number));
    }


    NumberVariant Interpreter::operator()(StringNode& node) {
        return std::move(StringValue(node.tok.value).set_pos(node.tok.pos));
    }
    NumberVariant Interpreter::operator()(std::monostate) {
        std::cerr << "Empty AST node encountered\n";
        return std::move(Number<int>(0));
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<IfNode>& node) {
        if (!node) return std::move(Number<int>(0));

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
                    return std::move(last);
                }
            }
            return std::move(last);
        }

        for (auto &p : node->elif_branches) {
            NumberVariant ev = this->process(p.first);
            if (is_truthy(ev)) {
                NumberVariant last = Number<int>(0);
                for (auto& stmt : p.second->statements) {
                    ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                    last = std::move(r.value);
                    if (r.did_break || r.did_continue) {
                        return std::move(last);
                    }
                }
                return std::move(last);
            }
        }

        if (node->else_branch) {
            NumberVariant last = std::move(Number<int>(0));
            for (auto& stmt : node->else_branch->statements) {
                ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                last = std::move(r.value);
                if (r.did_break || r.did_continue) {
                    return std::move(last);
                }
            }
            return std::move(last);
        }

        return std::move(Number<int>(0));
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
        
        Parser parser(resp.Tkns);
        Aer ast = parser.parse();
        if (ast.error) {
            return Mer{std::move(ast), std::move(resp), ""};
        }
        
        Context* ctx = new Context();
        Interpreter interpreter(ctx);
        
        std::string output = "";
        int exit_code = 0;
        
        try {
            for (auto& stmt : ast.statements->statements) {
                if (std::holds_alternative<std::shared_ptr<FuncDefNode>>(stmt)) {
                    interpreter.process(stmt);
                }
            }
            std::shared_ptr<FuncDefNode> main_func = ctx->get_function("main");
            if (!main_func) {
                throw RTError("No main() function found", Position());
            }
            auto main_call_node = std::make_unique<CallNode>(
                std::make_unique<VarAccessNode>(Token(TokenType::IDENTIFIER, "main", Position())),
                std::list<AnyNode>{}
            );
            AnyNode node_variant = std::move(main_call_node);
            NumberVariant result = std::move(interpreter.process(node_variant));
            
            exit_code = std::visit([](auto&& v) -> int {
                using T = std::decay_t<decltype(v)>;
                if constexpr (std::is_same_v<T, Number<int>>) {
                    return v.value;
                }
                return 0;
            }, result);
            
            output = "Program exited with code: " + std::to_string(exit_code);
            
        } catch (RTError& e) {
            std::cout << e.as_string() << std::endl;
            delete ctx;
            return Mer{std::move(ast), std::move(resp), ""};
        }
        
        delete ctx;
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
            id == "fn" || id == "continue" || id == "auto") {
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
    Token Lexer::make_fstring() {
        Position start_pos = this->pos.copy();
        this->advance(); 

        std::vector<std::string> parts;
        std::vector<std::string> exprs;

        std::string current = "";
        bool escape = false;

        while (this->current_char != '\0' && (this->current_char != '"' || escape)) {
            if (escape) {
                switch (this->current_char) {
                    case 'n': current += '\n'; break;
                    case 't': current += '\t'; break;
                    case 'r': current += '\r'; break;
                    case '\\': current += '\\'; break;
                    case '"': current += '"'; break;
                    default: current += this->current_char; break;
                }
                escape = false;
                this->advance();
                continue;
            }

            if (this->current_char == '\\') {
                escape = true;
                this->advance();
                continue;
            }

            if (this->current_char == '{' && this->text[this->pos.index + 1] == '{') {
                current += '{';
                this->advance();
                this->advance();
                continue;
            }

            if (this->current_char == '}' && this->text[this->pos.index + 1] == '}') {
                current += '}';
                this->advance();
                this->advance();
                continue;
            }

            if (this->current_char == '{') {
                parts.push_back(current);
                current = "";
                this->advance(); 

                std::string expr = "";
                int brace_depth = 1;

                while (this->current_char != '\0' && brace_depth > 0) {
                    if (this->current_char == '{') brace_depth++;
                    else if (this->current_char == '}') brace_depth--;

                    if (brace_depth > 0) expr += this->current_char;

                    this->advance();
                }

                if (brace_depth != 0)
                    throw IllegalCharError("Unclosed brace in f-string", this->pos);

                exprs.push_back(expr);
            } else {
                current += this->current_char;
                this->advance();
            }
        }

        parts.push_back(current);

        if (this->current_char != '"') throw IllegalCharError("Unterminated f-string", this->pos);
        this->advance(); 
        std::string encoded = "";
        for (size_t i = 0; i < parts.size(); i++) {
            encoded += parts[i];
            if (i < exprs.size()) encoded += "\x01" + exprs[i] + "\x01";
        }

        return Token(TokenType::FSTRING, encoded, start_pos);
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
            } else if (this->current_char == 'f' && this->text[this->pos.index + 1] == '"') {
                this->advance();
                tokens.push_back(this->make_fstring());
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
                        }  else if (current_char == '>') {
                            this->advance();
                            tokens.push_back(Token(TokenType::ARROW, "->", start_pos));
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
                        if (current_char == '<') {
                            this->advance();
                            tokens.push_back(Token(TokenType::LSHIFT, "<<", start_pos));
                        } else if (current_char == '=') {
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
                    case ',':
                        this->advance();
                        tokens.push_back(Token(TokenType::COMMA, ",", start_pos));
                        break;
                    case ':':
                        this->advance();
                        if (current_char == ':') {
                            this->advance();
                            tokens.push_back(Token(TokenType::SCOPE, "::", start_pos));
                            break;
                        } else {
                            tokens.push_back(Token(TokenType::COLON, ":", start_pos));
                        }
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


