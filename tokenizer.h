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
#include <vector>
#include <map>
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
        Position();
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
    using AnyNode = std::variant<
        std::monostate, 
        NumberNode, 
        StringNode,
        CharNode,
        std::unique_ptr<BinOpNode>, 
        std::unique_ptr<UnaryOpNode>,
        std::unique_ptr<VarAccessNode>,
        std::unique_ptr<VarAssignNode>,
        std::unique_ptr<AssignExprNode>
    >;
    class StatementsNode {
    public:
        std::vector<AnyNode> statements;
        
        StatementsNode(std::vector<AnyNode> stmts) 
            : statements(std::move(stmts)) {}
        
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
        EQ,
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
        std::string as_string();
        virtual ~Error() = default;
    };
    class IllegalCharError : public Error { 
    public:
        IllegalCharError(std::string details, Position pos) : Error("Illegal Character", details, pos) {}
    };
    class InvalidSyntaxError : public Error { 
    public:
        InvalidSyntaxError(std::string details, Position pos) : Error("Invalid Syntax: ", details, pos) {}
    };
    class MissingSemicolonError : public Error {
    public:
        MissingSemicolonError(Position pos) : Error("Expected Semicolon on line and char", " ", pos) {}
    };
    class RTError : public Error {
    public:
        RTError(std::string d, Position pos) : Error("Error: ", d, pos) {}
    };
    struct Ler {
        std::list<Token> Tkns;
        std::unique_ptr<Error> error;
    };
    struct Aer {
        std::unique_ptr<StatementsNode> statements;  // ← Not AnyNode!
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
        Token type_tok;
        Token var_name_tok;
        AnyNode value_node;
        
        VarAssignNode(Token type, Token name, AnyNode value)
            : type_tok(std::move(type)), 
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
//////////////////////////////////////////////////////////////////////////////////////////////
// PARSE RESULT /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    class ParseResult;
    using Prs = std::variant<std::monostate, ParseResult, NumberNode, StringNode, CharNode, std::unique_ptr<BinOpNode>, std::unique_ptr<tkz::Error>, std::unique_ptr<UnaryOpNode>, std::unique_ptr<VarAccessNode>, std::unique_ptr<VarAssignNode>, std::unique_ptr<AssignExprNode>>;
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
        Prs expr();
        Prs atom();
        Prs power();
        Prs bin_op(std::function<Prs()> func, TokenType type1, TokenType type2);
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
    using NumberVariant = std::variant<Number<int>, Number<float>, Number<double>, StringValue>;
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
        if (op == TokenType::POWER) {
            // Check 0^negative
            if (L.value == 0 && R.value < 0) { 
                throw RTError("Cannot raise zero to negative power", L.pos);
            }
            return L.power_by(R);
        }
        throw RTError("Unknown operator", L.pos);
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// CONTEXT //////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    struct Symbol {
        std::string declared_type;
        NumberVariant value;
    };

    class Context {
        std::unordered_map<std::string, Symbol> symbols;
    public:
        std::string get_type_name(const NumberVariant& val) {
            return std::visit([](auto&& arg) -> std::string {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, Number<int>>) return "int";
                if constexpr (std::is_same_v<T, StringValue>) return "string";
                if constexpr (std::is_same_v<T, CharValue>) return "char"; // Add this!
                return "unknown";
            }, val);
        }
        void define(const std::string& name, const std::string& type, NumberVariant val) {
            symbols[name] = {type, val};
        }
        NumberVariant get(const std::string& name, Position pos) {
            auto it = symbols.find(name);
            if (it != symbols.end()) {
                return it->second.value;
            }
            throw RTError("Undefined variable: '" + name + "'", pos);
        }
        void set(const std::string& name, NumberVariant new_val, Position pos) {
            if (symbols.find(name) == symbols.end()) {
                throw RTError("Undefined variable: " + name, pos);
            }
            std::string expected = symbols[name].declared_type;
            std::string actual = this->get_type_name(new_val); // Helper to get "int", "string", etc.

            if (expected != actual) {
                throw RTError("Type Mismatch: Cannot assign " + actual + " to variable of type " + expected, pos);
            }
            
            symbols[name].value = new_val;
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
        NumberVariant operator()(std::unique_ptr<AssignExprNode>& node);
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