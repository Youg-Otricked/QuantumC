#ifndef TOKEN_H
#define TOKEN_H
#include <memory>
#include <string>
#include <list>
#include <variant>
#include <functional>
#include <type_traits>
#include <optional>
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
    class NumberNode;
    class BinOpNode;
    class UnaryOpNode;
    using AnyNode = std::variant<std::monostate, NumberNode, std::unique_ptr<BinOpNode>, std::unique_ptr<UnaryOpNode>>;
    inline std::string bad_chars = " \t";
    inline std::string DIGITS = "0123456789";
    enum class TokenType {
        INT,
        FLOAT,
        DOUBLE,
        PLUS,
        MINUS,
        MUL,
        DIV,
        LPAREN,
        RPAREN,
        SEMICOLON,
        EOFT
    };
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
        RTError(Position pos) : Error("Error: ", " ", pos) {}
    };
    struct Ler {
        std::list<Token> Tkns;
        std::unique_ptr<Error> error;
    };
    struct Aer {
        std::optional<std::unique_ptr<AnyNode>> AST;
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
    class NumberNode {
        public:
        Token tok;
        NumberNode(Token tok);
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
//////////////////////////////////////////////////////////////////////////////////////////////
// PARSE RESULT /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    class ParseResult;
    using Prs = std::variant<std::monostate, ParseResult, NumberNode, std::unique_ptr<BinOpNode>, std::unique_ptr<tkz::Error>, std::unique_ptr<UnaryOpNode>>;
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
        Prs bin_op(std::function<Prs()> func, TokenType type1, TokenType type2);
        Aer parse();
        
    };
//////////////////////////////////////////////////////////////////////////////////////////////
// VALUES ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T> class Number;
    using NumberVariant = std::variant<Number<int>, Number<float>, Number<double>>;
    template <typename T>
    class Number {
    public:
        T value;
        Position pos;

        using value_type = T; 

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
    };

    

    template <typename T, typename U>
    NumberVariant handle_binop(const Number<T>& L, const Number<U>& R, TokenType op) {
        if (op == TokenType::PLUS)  return L.added_to(R);
        if (op == TokenType::MINUS) return L.subbed_by(R);
        if (op == TokenType::MUL)   return L.multed_by(R);
        if (op == TokenType::DIV)   return L.dived_by(R);
        return Number<int>(0);
    }
//////////////////////////////////////////////////////////////////////////////////////////////
// INTERPRETER CLASS ////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    class Interpreter {
    public:
        NumberVariant process(AnyNode& node);
        NumberVariant operator()(NumberNode& node);
        NumberVariant operator()(std::unique_ptr<BinOpNode>& node);
        NumberVariant operator()(std::unique_ptr<UnaryOpNode>& node);
        NumberVariant operator()(std::monostate);
    };
//////////////////////////////////////////////////////////////////////////////////////////////
// RUN// ////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    Mer run(std::string text, std::string filename);

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

        Ler make_tokens();

        Token make_number();
    };
}
#endif