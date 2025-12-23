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
            else if constexpr (std::is_same_v<T, StringNode>) {
                return arg.print();
            } 
            else if constexpr (std::is_same_v<T, CharNode>) {
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
            else if constexpr (std::is_same_v<T, std::monostate>) {
                return "<empty>";
            }
            else {
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
    UnaryOpNode::UnaryOpNode(Token op_tok, AnyNode node) {
      this->op_tok = op_tok;
      this->node = std::move(node);  
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
            return res.success(std::make_unique<VarAccessNode>(tok));
        } else if (tok.type == TokenType::CHAR) {
            this->advance();
            return res.success(CharNode(tok));
        } else if (tok.type == TokenType::LPAREN) {
            this->advance();
            AnyNode any_expr = res.reg(this->expr());
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
            InvalidSyntaxError("Expected an Int Float Double '+', '-', Identifier, or '('", tok.pos)
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

        // Handle unary operators (including ++ and --)
        if (tok.type == TokenType::PLUS || tok.type == TokenType::MINUS ||
            tok.type == TokenType::INCREMENT || tok.type == TokenType::DECREMENT) {
            this->advance();
            AnyNode factor_node = res.reg(this->factor());  
            if (res.error) return res.to_prs();
            return res.success(std::make_unique<UnaryOpNode>(tok, std::move(factor_node)));
        }

        return this->power();
    }
    Prs Parser::term() {
        return this->bin_op([this]() { return this->factor(); }, TokenType::DIV, TokenType::MUL);
    }
    Prs Parser::expr() {
        ParseResult res;
        AnyNode left = res.reg(this->term());
        if (res.error) return res.to_prs();

        // Only keep parsing + and -, but never consume a semicolon
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
    Prs Parser::assignment_expr() {
        ParseResult res;

        // Parse the left side (this calls expr but we ensure expr won't pass semicolon)
        AnyNode left = res.reg(this->expr());
        if (res.error) return res.to_prs();

        // If the next token is '=', create an AssignExpr
        if (this->current_tok.type == TokenType::EQ) {
            // Left must be a variable
            if (!std::holds_alternative<std::unique_ptr<VarAccessNode>>(left)) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Left side of assignment must be a variable",
                    this->current_tok.pos
                ));
                return res.to_prs();
            }

            Token var = std::get<std::unique_ptr<VarAccessNode>>(left)->var_name_tok;
            this->advance();  // consume '='

            // Right side: if another '=' follows on an identifier, recurse
            AnyNode right;
            auto next_it = std::next(it);
            if (this->current_tok.type == TokenType::IDENTIFIER &&
                next_it != tokens.end() && next_it->type == TokenType::EQ) {
                right = res.reg(this->assignment_expr());
            } else {
                right = res.reg(this->expr());  // expr that stops at semicolon
            }

            if (res.error) return res.to_prs();
            return res.success(std::make_unique<AssignExprNode>(var, std::move(right)));
        }

        return res.success(std::move(left));
    }
    Prs Parser::statement() {
        ParseResult res;
        Token tok = this->current_tok;

        if (tok.type == TokenType::KEYWORD) {
            Token type_tok = tok;
            this->advance();

            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(std::make_unique<InvalidSyntaxError>("Expected identifier", this->current_tok.pos));
                return res.to_prs();
            }

            Token var_name = this->current_tok;
            this->advance();

            AnyNode value;
            if (this->current_tok.type == TokenType::EQ) {
                this->advance();
                value = res.reg(this->expr());
                if (res.error) return res.to_prs();
            } else {
                value = default_value_for_type(type_tok, var_name.pos);
            }

            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                return res.to_prs();
            }

            this->advance(); 
            return res.success(std::make_unique<VarAssignNode>(type_tok, var_name, std::move(value)));
        }

        // Handle assignments: var = expr;
        if (tok.type == TokenType::IDENTIFIER) {
            auto next_it = std::next(it);
            if (next_it != tokens.end() && next_it->type == TokenType::EQ) {
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

        // Expression statement: expr;
        AnyNode node = res.reg(this->expr());
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

    NumberVariant Interpreter::process(AnyNode& node) {
        return std::visit(*this, node);
    }

    NumberVariant Interpreter::operator()(NumberNode& node) {
        const std::string& s = node.tok.value;

        try {
            if (!s.empty() && (s.back() == 'f' || s.back() == 'F')) {
                float val = std::stof(s);
                return Number<float>(val).set_pos(node.tok.pos);
            }
            
            if (s.find('.') != std::string::npos) {
                double val = std::stod(s);
                return Number<double>(val).set_pos(node.tok.pos);
            }
            
            int val = std::stoi(s);
            return Number<int>(val).set_pos(node.tok.pos);
        } catch (const std::out_of_range& e) {
        throw RTError(
            "Number is too large (Overflow)", node.tok.pos
        );
        return Number<int>(0);}
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<StatementsNode>& node) {
        NumberVariant last_result = Number<int>(0);
        
        for (auto& stmt : node->statements) {
            last_result = this->process(stmt);
        }
        
        return last_result;
    }
    
    NumberVariant Interpreter::operator()(std::unique_ptr<VarAssignNode>& node) {
        NumberVariant value = this->process(node->value_node);

        if (node->type_tok.type == TokenType::IDENTIFIER) {
            context->set(node->var_name_tok.value, value, node->var_name_tok.pos);
        } 
        else {
            context->define(node->var_name_tok.value, node->type_tok.value, value);
        }
        
        return value;
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
            auto result = this->process(stmt);
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
            }
            else if constexpr (std::is_same_v<T1, std::monostate> || std::is_same_v<T2, std::monostate>) {
                throw RTError("Operation on uninitialized value", node->op_tok.pos);
            }
            else{ 
                return handle_binop(L, R, node->op_tok.type, this->error);
            }
        }, left, right);
    }
    NumberVariant Interpreter::operator()(tkz::CharNode& node) {
        if (node.tok.value.empty()) return Number<int>(0);
        
        // If your lexer provides the raw escape sequence like "\n"
        std::string s = node.tok.value;
        int char_val = 0;
        
        if (s.size() > 1 && s[0] == '\\') {
            switch (s[1]) {
                case 'n': char_val = '\n'; break;
                case 't': char_val = '\t'; break;
                case 'r': char_val = '\r'; break;
                case '\'': char_val = '\''; break;
                case '\\': char_val = '\\'; break;
                default: char_val = s[1];
            }
        } else {
            char_val = static_cast<int>(s[0]);
        }
        
        return Number<int>(char_val).set_pos(node.tok.pos);
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
        NumberVariant number = this->process(node->node);

        return std::visit([&node](const auto& n) -> NumberVariant {
            using T = std::decay_t<decltype(n)>;
            if constexpr (!std::is_same_v<T, StringValue> && !std::is_same_v<T, std::monostate>) {
                if (node->op_tok.type == TokenType::MINUS) {
                    return n.multed_by(Number<int>(-1));
                }
                if (node->op_tok.type == TokenType::INCREMENT) {
                    return n.added_to(Number<int>(1));
                }
                if (node->op_tok.type == TokenType::DECREMENT) {
                    return n.subbed_by(Number<int>(1));
                }
                return n;
            } else {
                throw RTError("Unary operator not supported for strings", node->op_tok.pos);
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
//////////////////////////////////////////////////////////////////////////////////////////////
// RUN //////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    Mer run(std::string file, std::string text, bool use_context) { 
        if (text.starts_with("// @no-context") || text.starts_with("# no-context")) {
            use_context = false;
        }
        // Lexer
        Lexer lexer(text, file);
        Ler resp = lexer.make_tokens();
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
        if (id == "int" || id == "float" || id == "double" || id == "bool" || 
            id == "string" || id == "qbool" || id == "void" || id == "char" ||
            id == "if" || id == "else" || id == "while" || id == "for" || 
            id == "return" || id == "qif" || id == "qswitch" || 
            id == "class" || id == "struct" || id == "enum") {
            return Token(TokenType::KEYWORD, id, start_pos);
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
            throw RTError("Expected closing single quote", this->pos);
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
                            advance();
                            tokens.push_back(Token(TokenType::INCREMENT, "++", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::PLUS, "", start_pos));
                        }
                        break;

                    case '-':
                        this->advance();
                        if (current_char == '-') {
                            advance();
                            tokens.push_back(Token(TokenType::DECREMENT, "--", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::MINUS, "", start_pos));
                        }
                        break;
                    case '*':
                        this->advance();
                        if (current_char == '*') {
                            advance();
                            tokens.push_back(Token(TokenType::POWER, "**", start_pos));
                            break;
                        }
                        tokens.push_back(Token(TokenType::MUL, "", start_pos));
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
                        } else {
                            tokens.push_back(Token(TokenType::DIV, "", start_pos));
                        }
                        break;
                    case '=':
                        this->advance();
                        tokens.push_back(Token(TokenType::EQ, "", start_pos));
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


