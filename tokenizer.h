#ifndef TOKEN_H
#define TOKEN_H
#include <memory>
#include <string>
#include <list>
#include <variant>
#include <functional>
#include <vector>
#include <type_traits>
#include <optional>
#include <cmath>
#include <map>
#include <iostream>
#include <mutex>
#include <unordered_map>
bool isCharInSet(char, const std::string &);

namespace tkz {
//////////////////////////////////////////////////////////////////////////////////////////////
// POSITION /////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    class Position {
        public:
        std::string Filename;
        std::string Filetxt;
        int index;
        int line;
        int column;
        int length = 1;
        Position();
        std::string arrow_string() const;
        Position(std::string, std::string, int, int, int);
        void advance(char current_char);
        Position copy();
    };
    class ListNode;
    class NumberNode;
    class BinOpNode;
    class UnaryOpNode;
    class StatementsNode;
    class VarAssignNode;
    class VarAccessNode;
    class StringNode;
    class CharNode;
    class AssignExprNode;
    class BoolNode;
    class IfNode;
    class SwitchNode;
    class BreakNode;
    class WhileNode;
    class ForNode;
    class CallNode;
    class QOutExprNode;
    //class ForeachNode;
    class ContinueNode;
    class FuncDefNode;
    class QOutNode;
    class ReturnNode;
    class MultiReturnNode;
    class MultiVarDeclNode;
    using AnyNode = std::variant<
        std::monostate, 
        NumberNode, 
        StringNode,
        CharNode,
        BoolNode,
        QOutNode,
        std::unique_ptr<BinOpNode>, 
        std::unique_ptr<UnaryOpNode>,
        std::unique_ptr<VarAccessNode>,
        std::unique_ptr<VarAssignNode>,
        std::unique_ptr<AssignExprNode>,
        std::unique_ptr<IfNode>,
        std::unique_ptr<StatementsNode>,
        std::unique_ptr<SwitchNode>,
        std::unique_ptr<BreakNode>,
        std::unique_ptr<WhileNode>,    
        std::unique_ptr<ForNode>,       
       // std::unique_ptr<ForeachNode>,  
        std::unique_ptr<ContinueNode>,   
        std::unique_ptr<CallNode>,
        std::shared_ptr<FuncDefNode>,
        std::unique_ptr<QOutExprNode>,
        std::unique_ptr<ReturnNode>,
        std::unique_ptr<MultiReturnNode>,
        std::unique_ptr<MultiVarDeclNode>
    >;
    class StatementsNode {
    public:
        std::vector<AnyNode> statements;
        bool is_block = false;

        StatementsNode(std::vector<AnyNode> stmts, bool is_block = false)
            : statements(std::move(stmts)), is_block(is_block) {}

        std::string print();
    };

    enum class Keywords {
        INT,
        STRING,
        FLOAT,
        DOUBLE,
        CHAR,
        MAP,
        LIST,
        ARRAY,
        VOID,
        ENUM,
        CLASS,
        STRUCT,
        BOOL,
        QBOOL
    };
    inline std::string bad_chars = " \t\n\r";
    inline std::string DIGITS = "0123456789";
    inline std::string LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    inline std::string LETTERSDIGITS = LETTERS + DIGITS;
    enum class TokenType {
        INT,
        STRING,
        FLOAT,
        DOUBLE,
        CHAR,
        MAP,
        LIST,
        ARRAY,
        VOID,
        ENUM,
        CLASS,
        STRUCT,
        ARROW,
        BOOL,
        QBOOL,
        PLUS,
        MINUS,
        MUL,
        DIV,
        POWER,
        LPAREN,
        RPAREN,
        LSHIFT,
        RSHIFT,
        SCOPE,
        SEMICOLON,
        DEF,
        INCREMENT,
        DECREMENT,
        IDENTIFIER,
        KEYWORD,
        PLUS_EQ,
        MINUS_EQ,
        MUL_EQ,
        DIV_EQ,
        MOD,
        MOD_EQ,
        EQ_TO,
        NOT_EQ,
        MORE,
        LESS,
        MORE_EQ,
        LESS_EQ,
        AND,
        OR,
        NOT,
        EQ,
        FSTRING,
        SWITCH,
        CASE,
        DEFAULT,
        IF,
        ELSE,
        LBRACE,
        RBRACE,
        COLON,
        BREAK,
        FUNC,
        COMMA,
        EOFT
    };
    TokenType stringToTokenType(const std::string& str);
    class Token {
        public: 
        TokenType type;
        std::string value;
        Position pos;
        Token();
        Token(TokenType t, std::string val, Position p);
        bool operator==(const Token&) const = default;
        std::string print() const;
    };

//////////////////////////////////////////////////////////////////////////////////////////////
// ERRORS ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
   
    class Error {
        public:
        Position pos;
        std::string error_name;
        std::string details;
        Error(std::string err, std::string details, Position pos);
        virtual std::string as_string();
        virtual ~Error() = default;
    };
    class IllegalCharError : public Error { 
    public:
        IllegalCharError(std::string details, Position pos) : Error("Illegal Character", details, pos) {}
        std::string as_string() override;
    };
    class InvalidSyntaxError : public Error { 
    public:
        InvalidSyntaxError(std::string details, Position pos) : Error("Invalid Syntax: ", details, pos) {}
        std::string as_string() override;
    };
    class MissingSemicolonError : public Error {
    public:
        MissingSemicolonError(Position pos) : Error("Expected Semicolon on line and char", " ", pos) {}
        std::string as_string() override;
    };
    class RTError : public Error {
    public:
        RTError(std::string d, Position pos) : Error("Error: ", d, pos) {}
        std::string as_string() override;
    };
    struct Ler {
        std::list<Token> Tkns;
        std::unique_ptr<Error> error;
    };
    struct Aer {
        std::unique_ptr<StatementsNode> statements;
        std::unique_ptr<Error> error;
    };
    struct Mer {
        Aer ast;
        Ler tokens;
        std::string res;
    };
//////////////////////////////////////////////////////////////////////////////////////////////
// NODES ////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    
    class QOutNode {
    public:
        std::string print() { return "std::qout"; }
    };
    std::string printAny(AnyNode& node);
    class CharNode {
        public:
        Token tok;

        CharNode(Token t) : tok(t) {}
        std::string print();
    };
    class NumberNode {
        public:
        Token tok;
        NumberNode(Token tok);
        std::string print();
    };
    class StringNode {
        public:
        Token tok;
        StringNode (Token tok);
        std::string print();
    };
    
    class BoolNode {
        public:
        Token tok;
        BoolNode (Token tok);
        std::string print();
    };
    class BinOpNode {
    public:
        bool is_f;
        AnyNode left_node;
        Token op_tok;
        AnyNode right_node;

        BinOpNode(AnyNode left, Token op, AnyNode right, bool is_f = false) 
            : left_node(std::move(left)), 
            op_tok(std::move(op)), 
            right_node(std::move(right)) {this->is_f = is_f;}
            
        std::string print();
    };
    class UnaryOpNode {
    public:
        Token op_tok;
        AnyNode node;
        bool is_postfix;   // NEW

        UnaryOpNode(Token op, AnyNode n, bool postfix = false)
            : op_tok(op), node(std::move(n)), is_postfix(postfix) {}
        std::string print();
    };
    class AssignExprNode {
        public:
        Token var_name;
        AnyNode value;

        std::string print() {
            return "(" + var_name.print() + " = " + printAny(value) + ")";
        }
    };
    class VarAssignNode {
    public:
        bool is_const;
        Token type_tok;
        Token var_name_tok;
        AnyNode value_node;
        
        VarAssignNode(bool is_const, Token type, Token name, AnyNode value)
            : is_const(is_const),
            type_tok(std::move(type)), 
            var_name_tok(std::move(name)), 
            value_node(std::move(value)) {}
        
        std::string print();
    };

    class VarAccessNode {
    public:
        Token var_name_tok;
        
        VarAccessNode(Token name) : var_name_tok(std::move(name)) {}
        
        std::string print();
    };
    class QOutExprNode {
    public:
        std::vector<AnyNode> values;
        
        QOutExprNode(std::vector<AnyNode> vals) 
            : values(std::move(vals)) {}
        
        std::string print() {
            return "std::qout << (values)";
        }
    };
    class IfNode {
    public:
        std::optional<AnyNode> init;
        AnyNode condition;
        std::unique_ptr<StatementsNode> then_branch;
        std::vector<std::pair<AnyNode, std::unique_ptr<StatementsNode>>> elif_branches;
        std::unique_ptr<StatementsNode> else_branch; 

        IfNode(std::optional<AnyNode> init_node,
            AnyNode cond,
            std::unique_ptr<StatementsNode> then_b,
            std::vector<std::pair<AnyNode, std::unique_ptr<StatementsNode>>> elifs = {},
            std::unique_ptr<StatementsNode> else_b = nullptr)
            : init(std::move(init_node)),
            condition(std::move(cond)),
            then_branch(std::move(then_b)),
            elif_branches(std::move(elifs)),
            else_branch(std::move(else_b)) {}

        std::string print();
    };
    struct CaseLabel {
        AnyNode expr;
    };

    class SwitchNode {
    public:
        AnyNode value;
        struct Section {
            std::vector<CaseLabel> cases;
            bool is_default = false;
            std::unique_ptr<StatementsNode> body;
        };
        std::vector<Section> sections;

        std::string print() {return printAny(value);}
    };

    class BreakNode {
        public:
            Token tok;
            BreakNode(Token t) : tok(std::move(t)) {}
            std::string print() { return "(break)"; }
        };
    class WhileNode {
    public:
        AnyNode condition;
        std::unique_ptr<StatementsNode> body;

        WhileNode(AnyNode cond, std::unique_ptr<StatementsNode> b)
            : condition(std::move(cond)), body(std::move(b)) {}

        std::string print() {
            return "(while " + printAny(condition) + " " + body->print() + ")";
        }
    };

    class ForNode {
    public:
        std::optional<AnyNode> init;
        AnyNode condition;
        std::optional<AnyNode> update;
        std::unique_ptr<StatementsNode> body;

        ForNode(std::optional<AnyNode> i,
                AnyNode cond,
                std::optional<AnyNode> u,
                std::unique_ptr<StatementsNode> b)
            : init(std::move(i)),
            condition(std::move(cond)),
            update(std::move(u)),
            body(std::move(b)) {}

        std::string print() {
        std::string res = "(for ";
        if (this->init.has_value()) {
            res += "init=" + printAny(this->init.value()) + "; ";
        }
        res += printAny(this->condition) + "; ";
        if (update.has_value()) {
            res += printAny(update.value());
        }
        res += ")";
        return res;
        }
    };

    class ContinueNode {
    public:
        Token tok;
        ContinueNode(Token t) : tok(std::move(t)) {}
        std::string print() { return "(continue)"; }
    };
    struct Parameter {
    Token type;
    Token name;
    std::optional<AnyNode> default_value;  
};

class FuncDefNode {
    public:
        std::vector<Token> return_types; 
        std::optional<Token> name_tok;
        std::list<Parameter> params;
        std::unique_ptr<StatementsNode> body;
        Position pos;
        
        FuncDefNode(std::vector<Token> ret_types, std::optional<Token> name, 
                    std::list<Parameter> parameters, 
                    std::unique_ptr<StatementsNode> func_body) 
            : return_types(std::move(ret_types)),
            name_tok(std::move(name)),
            params(std::move(parameters)),
            body(std::move(func_body)) {}
        
        std::string print() {
            std::string result = "";
            for (size_t i = 0; i < return_types.size(); i++) {
                result += return_types[i].value;
                if (i < return_types.size() - 1) result += ", ";
            }
            result += " " + (name_tok ? name_tok->value : "lambda") + "(params) {" + body->print() + "}";
            return result;
        }
        
        bool is_multi_return() const { return return_types.size() > 1; }
    };
    std::string printAny(AnyNode& node);    
    class CallNode {
    public:
        AnyNode node_to_call;
        std::list<AnyNode> arg_nodes;
        
        CallNode(AnyNode node, std::list<AnyNode> args) 
            : node_to_call(std::move(node)), arg_nodes(std::move(args)) {}
        
        std::string print() {
            return printAny(node_to_call) + "(args)";
        }
    };
    class MultiReturnNode {
    public:
        std::vector<AnyNode> values;
        Position pos;
        
        MultiReturnNode(std::vector<AnyNode> vals, Position p)
            : values(std::move(vals)), pos(p) {}
        
        std::string print() {
            std::string result = "return ";
            for (size_t i = 0; i < values.size(); i++) {
                result += printAny(values[i]);
                if (i < values.size() - 1) result += ", ";
            }
            return result + ";";
        }
    };    
    class MultiVarDeclNode {
    public:
        bool is_const;
        std::vector<Token> type_toks;   
        std::vector<Token> var_names;   
        AnyNode value;                   
        
        MultiVarDeclNode(
            bool is_const,
            std::vector<Token> type_toks,
            std::vector<Token> var_names,
            AnyNode value
        ) : is_const(is_const),
            type_toks(std::move(type_toks)),
            var_names(std::move(var_names)),
            value(std::move(value)) {}
    };
//////////////////////////////////////////////////////////////////////////////////////////////
// PARSE RESULT /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    class ParseResult;
    using Prs = std::variant<std::monostate, ParseResult, NumberNode, StringNode, CharNode, BoolNode, std::unique_ptr<BinOpNode>, std::unique_ptr<tkz::Error>, std::unique_ptr<UnaryOpNode>, std::unique_ptr<VarAccessNode>, std::unique_ptr<VarAssignNode>, std::unique_ptr<AssignExprNode>, std::unique_ptr<StatementsNode>, std::unique_ptr<IfNode>, std::unique_ptr<BreakNode>, std::unique_ptr<SwitchNode>, std::unique_ptr<WhileNode>, std::unique_ptr<ForNode>, std::unique_ptr<ContinueNode>, std::unique_ptr<CallNode>,
        std::shared_ptr<FuncDefNode>, QOutNode, std::unique_ptr<QOutExprNode>, std::unique_ptr<ReturnNode>,
        std::unique_ptr<MultiReturnNode>,
        std::unique_ptr<MultiVarDeclNode>>;
    class ParseResult {
        public:
        AnyNode node;
        std::unique_ptr<Error> error;
        ParseResult() = default;
        AnyNode reg_node(AnyNode res);
        AnyNode reg(Prs res);
        Prs success(AnyNode node);
        void failure(std::unique_ptr<Error>);
        Prs to_prs();
        
    };
// Int err //////////////////////////////////////////////////////////////////////////////////

    class InterpEer {
        public:
        std::unique_ptr<Error> err;
        Position pos;
        InterpEer() {}
        void fail(std::unique_ptr<Error> err, Position pos) {
            this->err = std::move(err);
            this->pos = pos;
        }
    };
//////////////////////////////////////////////////////////////////////////////////////////////
// PARSER ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    class Parser {
        public:
        std::list<Token>::iterator it;
        Token current_tok;
        std::list<Token> tokens;
        Parser(std::list<Token> tokens);
        Token advance();
        Prs factor();
        Prs term();
        Prs comparison();
        Prs expr();
        Prs atom();
        Prs power();
        Prs if_expr();
        Prs return_stmt();
        Prs bin_op(std::function<Prs()> func, 
                   std::initializer_list<TokenType> ops);
        Prs logical_and();
        Prs qout_expr();
        Prs logical_or();
        Prs switch_stmt();
        Aer parse();
        Prs statement();
        Prs while_stmt();
        Prs for_stmt();
        Prs call(AnyNode node_to_call);
        Prs func_def(Token return_type, std::optional<Token> func_name);
        Prs func_def_multi(std::vector<Token> return_type, std::optional<Token> func_name);
        inline AnyNode prs_to_anynode(Prs&& st) {
            return std::visit([](auto&& arg) -> AnyNode {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_constructible_v<AnyNode, T>) {
                    return AnyNode(std::move(arg));
                }
                return std::monostate{};
            }, std::move(st));
        }
        bool parse_block_into(std::unique_ptr<StatementsNode>& out_block, ParseResult& res) {
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
                    AnyNode any_stmt = prs_to_anynode(std::move(st));
                    stmts.push_back(std::move(any_stmt));
                }
                if (this->current_tok.type != TokenType::RBRACE) {
                    res.failure(std::make_unique<InvalidSyntaxError>("Expected '}' after block", this->current_tok.pos));
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
                AnyNode any_stmt = prs_to_anynode(std::move(st));  // ← CHANGED!
                std::vector<AnyNode> stmts;
                stmts.push_back(std::move(any_stmt));
                out_block = std::make_unique<StatementsNode>(std::move(stmts), false);
                return true;
            }
        }
        Prs assignment_expr();
        
    };
//////////////////////////////////////////////////////////////////////////////////////////////
// VALUES ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
class VoidValue {
    public:
        Position pos;
        VoidValue() : pos("", "", 0, 0, 0) {}
        VoidValue& set_pos(Position p) { this->pos = p; return *this; }
        std::string print() const { return ""; }
};
class FunctionValue {
    public:
        std::shared_ptr<FuncDefNode> func;
        Position pos;
        FunctionValue(std::shared_ptr<FuncDefNode> f = nullptr) : func(f), pos("", "", 0, 0, 0) {}
        FunctionValue& set_pos(Position p) { this->pos = p; return *this; }
        std::string print() const { return "<function>"; }
};
class CharValue {
public:
    char value;
    Position pos;
    CharValue(std::string val) : pos("", "", 0, 0, 0) {
        if (!val.empty()) {
            this->value = val[0];
        } else {
            this->value = '\0';
        }
    }

    CharValue& set_pos(Position p) { 
        this->pos = p; 
        return *this; 
    }
    std::string print() const { 
        return std::string(1, value); 
    }
}; 
class BoolValue {
    public:
    bool value;
    Position pos;
    BoolValue(std::string val) : pos("", "", 0, 0, 0) {
        if (!val.empty()) {
            if (val == "true") {
                value = true;
            } else if (val == "false") {
                value = false;
            } else {
                throw RTError("Expected Boolean value to be either true or false", pos);
            }
        } else {
            this->value = '\0';
        }
    }
    BoolValue& set_pos(Position p) { 
        this->pos = p; 
        return *this; 
    }
    std::string print() const { 
        return this->value ? "true" : "false";
    }
};  
class StringValue {
    public:
        std::string value;
        Position pos;

        StringValue(std::string val) : value(val), pos("", "", 0, 0, 0) {}
        
        StringValue& set_pos(Position p) { 
            this->pos = p; 
            return *this; 
        }

        std::string print() const { return value; }
    };
    class MultiValue;
    template <typename T> class Number;
    using NumberVariant = std::variant<
        Number<int>, Number<float>, Number<double>,
        StringValue, CharValue, BoolValue,
        FunctionValue, VoidValue, std::shared_ptr<MultiValue>
    >;
    template <typename T>
    class Number {
    public:
        T value;
        Position pos;

        using value_type = T; 
        Number() : value(0), pos("", "", 0, 0, 0) {}
        Number(T val);
        Number<T>& set_pos(Position p);
        std::string print();

        template <typename U>
        auto added_to(const Number<U>& other) const {
            using CommonT = std::common_type_t<T, U>;
            return Number<CommonT>(static_cast<CommonT>(this->value) + other.value);
        }

        template <typename U>
        auto subbed_by(const Number<U>& other) const {
            using CommonT = std::common_type_t<T, U>;
            return Number<CommonT>(static_cast<CommonT>(this->value) - other.value);
        }

        template <typename U>
        auto multed_by(const Number<U>& other) const {
            using CommonT = std::common_type_t<T, U>;
            return Number<CommonT>(static_cast<CommonT>(this->value) * other.value);
        }

        template <typename U>
        auto dived_by(const Number<U>& other) const {
            using CommonT = std::common_type_t<T, U>;
            return Number<CommonT>(static_cast<CommonT>(this->value) / other.value);
        }
        template <typename U>
        auto power_by(const Number<U>& other) const {
            using CommonT = std::common_type_t<T, U>;
            auto result = std::pow(this->value, other.value);
            if (std::isinf(result)) {
                throw RTError("Result too large (overflow)", pos);
            }
            if (std::isnan(result)) {
                throw RTError("Invalid operation (NaN)", pos);
            }
            return Number<CommonT>(static_cast<CommonT>(result));
        }
        template <typename U>
        auto modded_by(const Number<U>& other) const {
            using CommonT = std::common_type_t<T, U>;
            if constexpr (std::is_floating_point_v<CommonT>) {
                return Number<CommonT>(std::fmod(static_cast<CommonT>(this->value), other.value));
            } else {
                return Number<CommonT>(static_cast<CommonT>(this->value) % other.value);
            }
        }

    };
    class MultiValue {
    public:
        std::vector<NumberVariant> values;
        
        MultiValue(std::vector<NumberVariant>&& vals) : values(std::move(vals)) {}
        
        std::string print() const {
            std::string result = "(";
            for (size_t i = 0; i < values.size(); i++) {
                result += std::visit([](auto&& v) -> std::string {
                    using T = std::decay_t<decltype(v)>;
                    
                    if constexpr (requires { v->print(); }) {
                        return v->print();  
                    }
                    else if constexpr (requires { v.print(); }) {
                        return v.print();   
                    }
                    else {
                        return "<unknown>";
                    }
                }, values[i]);
                
                if (i < values.size() - 1) result += ", ";
            }
            return result + ")";
        }
    };
    
    struct ExecResult {
        NumberVariant value;
        bool did_break;
        bool did_continue;
        bool did_return;
        ExecResult() : value(Number<int>(0)), did_break(false), did_continue(false), did_return(false) {}
        ExecResult(NumberVariant v, bool b, bool c, bool r = false)
            : value(std::move(v)), did_break(b), did_continue(c), did_return(r) {}
    };
    class MultiReturnException {
    public:
        std::vector<NumberVariant> values;
        
        MultiReturnException(std::vector<NumberVariant> vals) 
            : values(std::move(vals)) {}
    };

    template <typename T, typename U>
    NumberVariant handle_binop(const Number<T>& L, const Number<U>& R, TokenType op, InterpEer& error) {
        if (op == TokenType::PLUS) return L.added_to(R);
        if (op == TokenType::MINUS) return L.subbed_by(R);
        if (op == TokenType::MUL) return L.multed_by(R);
        if (op == TokenType::DIV) {
            if (R.value == 0) {
                throw RTError("Division by zero", R.pos);
            }
            return L.dived_by(R);
        }
        if (op == TokenType::MOD) { 
            if (R.value == 0) {
                throw RTError("Modulo by zero", R.pos);
            }
            return L.modded_by(R);
        }
        if (op == TokenType::POWER) {
            if (L.value == 0 && R.value < 0) {
                throw RTError("Cannot raise zero to negative power", L.pos);
            }
            return L.power_by(R);
        }
           if (op == TokenType::EQ_TO) {
        return BoolValue(L.value == R.value ? "true" : "false").set_pos(L.pos);
        }
        if (op == TokenType::NOT_EQ) {
            return BoolValue(L.value != R.value ? "true" : "false").set_pos(L.pos);
        }
        if (op == TokenType::LESS) {
            return BoolValue(L.value < R.value ? "true" : "false").set_pos(L.pos);
        }
        if (op == TokenType::LESS_EQ) {
            return BoolValue(L.value <= R.value ? "true" : "false").set_pos(L.pos);
        }
        if (op == TokenType::MORE) {
            return BoolValue(L.value > R.value ? "true" : "false").set_pos(L.pos);
        }
        if (op == TokenType::MORE_EQ) {
            return BoolValue(L.value >= R.value ? "true" : "false").set_pos(L.pos);
        }
        
        throw RTError("Unknown operator", L.pos);
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// CONTEXT //////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    struct Symbol {
        std::string declared_type;
        NumberVariant value;
        bool is_const; 
    };

    class Context {
        std::vector<std::unordered_map<std::string, Symbol>> frames;
        std::unordered_map<std::string, std::shared_ptr<FuncDefNode>> functions;
    public:
        Context() {
            frames.emplace_back(); 
        }
        void push_scope() {
            frames.emplace_back();
        }
        void pop_scope() {
            if (frames.size() > 1) frames.pop_back();
        }
        void define(const std::string& name, const std::string& type,
                    NumberVariant val, bool is_const = false) {
            frames.back()[name] = { type, std::move(val), is_const };
        }
        void set(const std::string& name, NumberVariant new_val, Position pos) {
            for (auto it = frames.rbegin(); it != frames.rend(); ++it) {
                auto sym_it = it->find(name);
                if (sym_it != it->end()) {
                    if (sym_it->second.is_const) {
                        throw RTError("Cannot assign to const variable '" + name + "'", pos);
                    }
                    std::string expected = sym_it->second.declared_type;
                    std::string actual = get_type_name(new_val);
                    if (expected != actual) {
                        throw RTError("Type mismatch: cannot assign " + actual + " to " + expected, pos);
                    }
                    sym_it->second.value = std::move(new_val);
                    return;
                }
            }
            throw RTError("Undefined variable: '" + name + "'", pos);
        }
        NumberVariant get(const std::string& name, Position pos) {
            for (auto it = frames.rbegin(); it != frames.rend(); ++it) {
                auto sym_it = it->find(name);
                if (sym_it != it->end()) {
                    return sym_it->second.value;
                }
            }
            throw RTError("Undefined variable: '" + name + "'", pos);
        }
        void define_function(const std::string& name, std::shared_ptr<FuncDefNode> func) {
            functions[name] = std::move(func);
        }
        
        std::shared_ptr<FuncDefNode> get_function(const std::string& name) {
            auto it = functions.find(name);
            if (it != functions.end()) return it->second;
            return nullptr;
        }
        std::string get_type_name(const NumberVariant& val) {
            return std::visit([](auto&& arg) -> std::string {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, Number<int>>)    return "int";
                if constexpr (std::is_same_v<T, Number<float>>)  return "float";
                if constexpr (std::is_same_v<T, Number<double>>) return "double";
                if constexpr (std::is_same_v<T, StringValue>)    return "string";
                if constexpr (std::is_same_v<T, CharValue>)      return "char";
                if constexpr (std::is_same_v<T, BoolValue>)      return "bool";
                if constexpr (std::is_same_v<T, FunctionValue>)  return "function";
                if constexpr (std::is_same_v<T, VoidValue>)      return "void";
                if constexpr (std::is_same_v<T, std::shared_ptr<MultiValue>>)     return "multi";  
                return "unknown";
            }, val);
        }
    };
    
    class ReturnNode {
    public:
        AnyNode value;  
        Position pos;
        
        ReturnNode(AnyNode val, Position p) 
            : value(std::move(val)), pos(p) {}
        
        std::string print() {
            return "return " + printAny(value);
        }
    };
//////////////////////////////////////////////////////////////////////////////////////////////
// INTERPRETER CLASS ////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    class Interpreter {
        Context* context;
    public:
        Interpreter(Context* ctx = nullptr) : context(ctx) {}
        InterpEer error = InterpEer();
        NumberVariant process(AnyNode& node);
        NumberVariant operator()(NumberNode& node);
        NumberVariant operator()(std::unique_ptr<BinOpNode>& node);
        NumberVariant operator()(std::unique_ptr<UnaryOpNode>& node);
        NumberVariant operator()(std::monostate);
        NumberVariant operator()(std::unique_ptr<StatementsNode>& node);
        NumberVariant operator()(std::unique_ptr<VarAssignNode>& node);
        NumberVariant operator()(std::unique_ptr<VarAccessNode>& node);
        NumberVariant operator()(StringNode& node);
        NumberVariant operator()(std::shared_ptr<FuncDefNode>& node);
        NumberVariant operator()(std::unique_ptr<CallNode>& node);
        NumberVariant operator()(std::unique_ptr<ReturnNode>& node);
        NumberVariant operator()(CharNode& node);
        NumberVariant operator()(BoolNode& node);
        NumberVariant operator()(QOutNode& node);
        NumberVariant operator()(std::unique_ptr<MultiVarDeclNode>& node);
        NumberVariant operator()(std::unique_ptr<QOutExprNode>& node);
        NumberVariant operator()(std::unique_ptr<AssignExprNode>& node);
        NumberVariant operator()(std::unique_ptr<IfNode>& node);
        NumberVariant operator()(std::unique_ptr<SwitchNode>& node); 
        NumberVariant operator()(std::unique_ptr<BreakNode>& node); 
        NumberVariant operator()(std::unique_ptr<ContinueNode>& node);
        NumberVariant operator()(std::unique_ptr<WhileNode>& node);
        NumberVariant operator()(std::unique_ptr<ForNode>& node);
        NumberVariant operator()(std::unique_ptr<MultiReturnNode>& node);
        ExecResult exec_stmt_in_loop_or_switch(AnyNode& node);
        ExecResult exec_stmt_in_loop_or_switch(StatementsNode& block);
        ExecResult exec_stmt_in_loop_or_switch(IfNode& ifn);
        ExecResult exec_stmt_in_loop_or_switch(SwitchNode& sw);
        std::string run_statements(std::unique_ptr<StatementsNode>& node);
    };
//////////////////////////////////////////////////////////////////////////////////////////////
// RUN// ////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    Mer run(std::string file, std::string text, bool use_context = true);

//////////////////////////////////////////////////////////////////////////////////////////////
// LEXER ////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    class Lexer {
        public:
        std::string Filename;
        std::string text;
        Position pos;
        char current_char;
        Lexer(std::string text, std::string filename);

        void advance();
        Token make_char();
        Token make_string();
        Ler make_tokens();
        Token make_identifier();
        Token make_number();
        Token make_fstring();
    };
}
#endif