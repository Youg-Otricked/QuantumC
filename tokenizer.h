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
    using AnyNode = std::variant<
        std::monostate, 
        NumberNode, 
        StringNode,
        CharNode,
        BoolNode,
        std::unique_ptr<BinOpNode>, 
        std::unique_ptr<UnaryOpNode>,
        std::unique_ptr<VarAccessNode>,
        std::unique_ptr<VarAssignNode>,
        std::unique_ptr<AssignExprNode>,
        std::unique_ptr<IfNode>
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
        BOOL,
        QBOOL,
        PLUS,
        MINUS,
        MUL,
        DIV,
        POWER,
        LPAREN,
        RPAREN,
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
        IF,
        ELSE,
        LBRACE,
        RBRACE,
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
        AnyNode left_node;
        Token op_tok;
        AnyNode right_node;

        BinOpNode(AnyNode left, Token op, AnyNode right) 
            : left_node(std::move(left)), 
            op_tok(std::move(op)), 
            right_node(std::move(right)) {}
            
        std::string print();
    };
    class UnaryOpNode {
        public:
        Token op_tok;
        AnyNode node;
        UnaryOpNode(Token op_tok, AnyNode node);
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
    class IfNode {
    public:
        std::optional<AnyNode> init; // optional init statement (e.g., "int a = 5")
        AnyNode condition;
        std::unique_ptr<StatementsNode> then_branch;
        std::vector<std::pair<AnyNode, std::unique_ptr<StatementsNode>>> elif_branches;
        std::unique_ptr<StatementsNode> else_branch; // nullptr if none

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
//////////////////////////////////////////////////////////////////////////////////////////////
// PARSE RESULT /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    class ParseResult;
    using Prs = std::variant<std::monostate, ParseResult, NumberNode, StringNode, CharNode, BoolNode, std::unique_ptr<BinOpNode>, std::unique_ptr<tkz::Error>, std::unique_ptr<UnaryOpNode>, std::unique_ptr<VarAccessNode>, std::unique_ptr<VarAssignNode>, std::unique_ptr<AssignExprNode>, std::unique_ptr<StatementsNode>, std::unique_ptr<IfNode>>;
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
        Prs bin_op(std::function<Prs()> func, 
                   std::initializer_list<TokenType> ops);
        Prs logical_and();
        Prs logical_or();
        Aer parse();
        Prs statement();
        Prs assignment_expr();
        
    };
//////////////////////////////////////////////////////////////////////////////////////////////
// VALUES ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
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
    template <typename T> class Number;
    using NumberVariant = std::variant<Number<int>, Number<float>, Number<double>, StringValue, CharValue, BoolValue>;
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
            frames.back()[name] = { type, val, is_const };
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
                    sym_it->second.value = new_val;
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
        std::string get_type_name(const NumberVariant& val) {
            return std::visit([](auto&& arg) -> std::string {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, Number<int>>)    return "int";
                if constexpr (std::is_same_v<T, Number<float>>)  return "float";
                if constexpr (std::is_same_v<T, Number<double>>) return "double";
                if constexpr (std::is_same_v<T, StringValue>)    return "string";
                if constexpr (std::is_same_v<T, CharValue>)      return "char";
                if constexpr (std::is_same_v<T, BoolValue>)      return "bool";
                return "unknown";
            }, val);
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
        NumberVariant operator()(CharNode& node);
        NumberVariant operator()(BoolNode& node);
        NumberVariant operator()(std::unique_ptr<AssignExprNode>& node);
        NumberVariant operator()(std::unique_ptr<IfNode>& node); 
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
    };
}
#endif