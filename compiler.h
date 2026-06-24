#ifndef TOKEN_H
#define TOKEN_H
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <optional>
#include <ranges>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>
#ifdef ENABLE_LLVM
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/IR/IntrinsicsX86.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#endif
#if defined(_WIN32) || defined(_WIN64)
#include <print>
#endif
bool isCharInSet(char, const std::string&);

namespace tkz {
//////////////////////////////////////////////////////////////////////////////////////////////
// POSITION /////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename V> T* safe_get(V& variant) {
    auto ptr_to_ptr = std::get_if<T*>(&variant);
    if (ptr_to_ptr != nullptr) { return *ptr_to_ptr; }
    return nullptr;
}
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
    bool operator==(const Position&) const = default;
};

// Forward declarations
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
class ContinueNode;
class FuncDefNode;
class QInNode;
class ReturnNode;
class MultiReturnNode;
class MultiVarDeclNode;
class ArrayDeclNode;
class ArrayLiteralNode;
class ArrayAccessNode;
class ListDeclNode;
class MethodCallNode;
class PropertyAccessNode;
class SpreadNode;
class NamespaceNode;
class ForeachNode;
class QBoolNode;
class QIfNode;
class QSwitchNode;
class MapDeclNode;
class ArrayAssignNode;
class SeedCallNode;
class RandomCallNode;
class FieldAssignNode;
class MapLiteralNode;
class TryCatchNode;
class RefVarDeclNode;
class NullptrNode;
using AnyNode = std::variant<std::monostate, NumberNode, StringNode, CharNode, BoolNode, QInNode, QBoolNode, RefVarDeclNode, NullptrNode, BinOpNode*,
                             UnaryOpNode*, VarAccessNode*, VarAssignNode*, AssignExprNode*, IfNode*, QIfNode*, StatementsNode*, SwitchNode*,
                             QSwitchNode*, BreakNode*, WhileNode*, ForNode*, ContinueNode*, CallNode*, FuncDefNode*, ReturnNode*, MultiReturnNode*,
                             MultiVarDeclNode*, ArrayDeclNode*, ListDeclNode*, ArrayLiteralNode*, ArrayAccessNode*, MethodCallNode*,
                             PropertyAccessNode*, SpreadNode*, ForeachNode*, MapDeclNode*, ArrayAssignNode*, SeedCallNode*, RandomCallNode*,
                             FieldAssignNode*, MapLiteralNode*, NamespaceNode*, TryCatchNode*>;

//////////////////////////////////////////////////////////////////////////////////////////////
// ENUMS & CONSTANTS ////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
enum class Keywords { INT, STRING, FLOAT, DOUBLE, CHAR, MAP, LIST, ARRAY, VOID, ENUM, CLASS, STRUCT, BOOL, QBOOL };

inline std::string bad_chars = " \t\n\r";
inline std::string DIGITS = "0123456789";
inline std::string LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
inline std::string LETTERSDIGITS = LETTERS + DIGITS;

enum class TokenType {
    INT,
    STRING,
    FLOAT,
    ADDR_T,
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
    AMPERSAND,
    STAR,
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
    SIZEOF,
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
    XOR,
    BITWISE_NOT,
    BITWISE_XOR,
    R_ROT,
    L_ROT,
    LOGICAL_RSHIFT,
    VARADIC,
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
    LBRACKET,
    RBRACKET,
    COLON,
    BREAK,
    FUNC,
    COMMA,
    DOT,
    AT,
    QAND,
    QOR,
    COLLAPSE_AND,
    COLLAPSE_OR,
    QEQEQ,
    QNEQ,
    QNOT,
    QXOR,
    PIPE,
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
class CTError : public Error {
  public:
    CTError(std::string d, Position pos) : Error("Error: ", d, pos) {}

    std::string as_string() override {
        std::string result;
        result += "Compile-time Error: " + this->details + "\n";
        result += "File " + this->pos.Filename + ", line " + std::to_string(this->pos.line + 1) + ", col " + std::to_string(this->pos.column + 1) +
                  "\n\n";
        result += this->pos.arrow_string();
        return result;
    }
};
struct Ler {
    std::vector<Token> Tkns;
    Error* error;
};
struct StructField {
    std::string name;
    std::string type;
};
struct EnumEntry {
    std::string memberName;
    std::string typeAtom;
};
struct ClassField {
    std::string name;
    std::string type;
    std::string access;
};
struct Parameter;
struct ClassMethodInfo {
    Token name_tok;
    std::vector<Parameter> params;
    std::vector<Token> return_types;
    StatementsNode* body;
    bool is_constructor = false;
    std::string access;
    bool is_final = false;
};

enum class UserTypeKind { Struct, Alias, Union, Enum, Class };

struct UnionMember {
    std::string type;
};

struct UserTypeInfo {
    UserTypeKind kind;
    std::vector<StructField> fields;
    std::string aliasTarget;
    std::vector<UnionMember> members;
    std::vector<EnumEntry> enumEntries;
    std::vector<ClassField> classFields;
    std::vector<ClassMethodInfo> classMethods;
    std::string baseClassName = "";
    std::string namespace_path;
    bool is_abstract_class = false;
    bool is_final_class = false;
};

struct Aer {
    StatementsNode* statements;
    Error* error;
    std::unordered_map<std::string, UserTypeInfo> user_types;
};
struct Diagnostic {
    Error* error = nullptr;
    std::string level;
};
struct Mer {
    Aer ast;
    Ler tokens;
    std::string res;
    std::vector<Diagnostic> errors;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// VALUE NODES //////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
std::string printAny(const AnyNode& node);
class QInNode {
  public:
    QInNode() {}

    std::string print() const { return "std::qin"; }
};
class CharNode {
  public:
    Token tok;
    CharNode(Token t) : tok(t) {}
    std::string print() const;
};

class NumberNode {
  public:
    Token tok;
    NumberNode(Token tok);
    std::string print() const;
};

class StringNode {
  public:
    Token tok;
    StringNode(Token tok);
    std::string print() const;
};

class BoolNode {
  public:
    Token tok;
    BoolNode(Token tok);
    std::string print() const;
};
class QBoolNode {
  public:
    Token tok;
    QBoolNode(Token tok);
    std::string print() const;
};
class NullptrNode {
  public:
    Position pos;
    NullptrNode(Position p) : pos(p) {}
    std::string print() const { return "nullptr"; }
};
class RefVarDeclNode {
  public:
    Token type_tok;
    Token var_name_tok;
    Token target_tok;
    Position pos;

    RefVarDeclNode(Token type, Token name, Token target, Position p) : var_name_tok(name), target_tok(target), pos(p) {
        type.value.erase(type.value.find_last_not_of('&') + 1);
        this->type_tok = type;
    }
    std::string print() const { return this->type_tok.value; }
};
//////////////////////////////////////////////////////////////////////////////////////////////
// StatementsNode ///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
class StatementsNode {
  public:
    std::vector<AnyNode> statements;
    bool is_block = false;

    StatementsNode(std::vector<AnyNode> stmts, bool is_block = false) : statements(stmts), is_block(is_block) {}

    std::string print() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// OTHER NODES //////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
struct Parameter {
    Token type;
    Token name;
    std::optional<AnyNode> default_value;
    struct FunctionSignature {
        std::vector<Token> return_types;
        std::vector<Parameter> params;
    };
    std::optional<FunctionSignature> signature;
};
struct ParamTypeInfo {
    Token type;
    struct FunctionSignature {
        std::vector<Token> return_types;
        std::vector<ParamTypeInfo> params;
    };
    Token name;
    std::optional<FunctionSignature> signature;
};
class BinOpNode {
  public:
    bool is_f;
    AnyNode left_node;
    Token op_tok;
    AnyNode right_node;

    BinOpNode(AnyNode left, Token op, AnyNode right, bool is_f = false) : left_node(left), op_tok(op), right_node(right) { this->is_f = is_f; }

    std::string print() const;
};

class UnaryOpNode {
  public:
    Token op_tok;
    AnyNode node;
    bool is_postfix;

    UnaryOpNode(Token op, AnyNode n, bool postfix = false) : op_tok(op), node(n), is_postfix(postfix) {}
    std::string print() const;
};

class AssignExprNode {
  public:
    AnyNode target;
    AnyNode value;
    Token op_tok;
    AssignExprNode(AnyNode t, Token op, AnyNode v) : target(t), op_tok(op), value(v) {}

    std::string print() { return "(" + printAny(target) + " = " + printAny(value) + ")"; }
};

class VarAssignNode {
  public:
    bool is_const;
    Token type_tok;
    Token var_name_tok;
    AnyNode value_node;

    VarAssignNode(bool is_const, Token type, Token name, AnyNode value) : is_const(is_const), type_tok(type), var_name_tok(name), value_node(value) {}

    std::string print() const;
};

class VarAccessNode {
  public:
    Token var_name_tok;

    VarAccessNode(Token name) : var_name_tok(name) {}

    std::string print() const;
};

class IfNode {
  public:
    std::optional<AnyNode> init;
    AnyNode condition;
    StatementsNode* then_branch;
    std::vector<std::pair<AnyNode, StatementsNode*>> elif_branches;
    StatementsNode* else_branch;

    IfNode(std::optional<AnyNode> init_node, AnyNode cond, StatementsNode* then_b, std::vector<std::pair<AnyNode, StatementsNode*>> elifs = {},
           StatementsNode* else_b = nullptr)
        : init(init_node), condition(cond), then_branch(then_b), elif_branches(elifs), else_branch(else_b) {}

    std::string print() const;
};
class QIfNode {
  public:
    std::optional<AnyNode> init;
    AnyNode condition;
    StatementsNode* then_branch;
    std::vector<std::pair<AnyNode, StatementsNode*>> qelif_branches;
    StatementsNode* qelse_branch;

    QIfNode(std::optional<AnyNode> init_stmt, AnyNode cond, StatementsNode* then_b, std::vector<std::pair<AnyNode, StatementsNode*>> qelif_b,
            StatementsNode* qelse_b)
        : init(init_stmt), condition(cond), then_branch(then_b), qelif_branches(qelif_b), qelse_branch(qelse_b) {}

    std::string print() const { return "qif (...)"; }
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
        StatementsNode* body;
    };
    std::vector<Section> sections;

    std::string print() { return printAny(value); }
};
class QSwitchNode {
  public:
    AnyNode value;
    StatementsNode* case_t;
    StatementsNode* case_f;
    StatementsNode* case_n;
    StatementsNode* case_b;

    QSwitchNode(AnyNode val, StatementsNode* t, StatementsNode* f, StatementsNode* n, StatementsNode* b)
        : value(val), case_t(t), case_f(f), case_n(n), case_b(b) {}

    std::string print() const { return "qswitch (...)"; }
};

class BreakNode {
  public:
    Token tok;
    BreakNode(Token t) : tok(t) {}
    std::string print() { return "(break)"; }
};

class WhileNode {
  public:
    AnyNode condition;
    StatementsNode* body;

    WhileNode(AnyNode cond, StatementsNode* b) : condition(cond), body(b) {}

    std::string print() { return "(while " + printAny(condition) + " " + body->print() + ")"; }
};
class TryCatchNode {
  public:
    StatementsNode* try_body;
    std::string catch_var_name;
    std::string catch_var_type;
    StatementsNode* catch_body;
    Token tok;
    Position pos;

    TryCatchNode(StatementsNode* try_b, std::string var_name, std::string var_type, StatementsNode* catch_b, Token t, Position p)
        : try_body(try_b), catch_var_name(var_name), catch_var_type(var_type), catch_body(catch_b), tok(t), pos(p) {}
    std::string print() { return "try {\n\t" + try_body->print() + "\n} catch {\n\t" + catch_body->print() + "\n}"; }
};
class ForNode {
  public:
    std::optional<AnyNode> init;
    AnyNode condition;
    std::optional<AnyNode> update;
    StatementsNode* body;

    ForNode(std::optional<AnyNode> i, AnyNode cond, std::optional<AnyNode> u, StatementsNode* b) : init(i), condition(cond), update(u), body(b) {}

    std::string print() {
        std::string res = "(for ";
        if (this->init.has_value()) { res += "init=" + printAny(this->init.value()) + "; "; }
        res += printAny(this->condition) + "; ";
        if (update.has_value()) { res += printAny(update.value()); }
        res += ")";
        return res;
    }
};

class ContinueNode {
  public:
    Token tok;
    ContinueNode(Token t) : tok(t) {}
    std::string print() { return "(continue)"; }
};

class FuncDefNode {
  public:
    std::vector<Token> return_types;
    std::optional<Token> name_tok;
    std::list<Parameter> params;
    StatementsNode* body;
    std::string namespace_path;
    Position pos;
    bool is_extern = false;
    bool is_foreign = false;
    FuncDefNode(std::vector<Token> ret_types, std::optional<Token> name, std::list<Parameter> parameters, StatementsNode* func_body,
                std::string ns = "", bool is_ex = false, bool is_f = false)
        : return_types(ret_types), name_tok(name), params(parameters), body(func_body), namespace_path(ns) {
        this->is_extern = is_ex;
        this->is_foreign = is_f;
    }
    std::string print() {
        std::string result = "";
        for (size_t i = 0; i < return_types.size(); i++) {
            result += return_types[i].value;
            if (i < return_types.size() - 1) result += ", ";
        }
        result += " " + (name_tok ? name_tok->value : "lambda") + "(";
        for (auto& param : params) { result += param.name.value; }
        result += "{" + body->print() + "}";
        return result;
    }

    bool is_multi_return() const { return return_types.size() > 1; }
};

class CallNode {
  public:
    AnyNode node_to_call;
    std::list<AnyNode> arg_nodes;

    CallNode(AnyNode node, std::list<AnyNode> args) : node_to_call(node), arg_nodes(args) {}

    std::string print() { return printAny(node_to_call) + "(args)"; }
};
class MultiReturnNode {
  public:
    std::vector<AnyNode> values;
    Position pos;

    MultiReturnNode(std::vector<AnyNode> vals, Position p) : values(vals), pos(p) {}

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

    MultiVarDeclNode(bool is_const, std::vector<Token> type_toks, std::vector<Token> var_names, AnyNode value)
        : is_const(is_const), type_toks(type_toks), var_names(var_names), value(value) {}
};
class ArrayDeclNode {
  public:
    bool is_const;
    Token type_tok;
    Token var_name_tok;
    AnyNode value;

    int dimensions;
    std::vector<std::optional<int>> sizes;

    ArrayDeclNode(bool is_const, Token type_tok, Token var_name_tok, AnyNode value, int dims, std::vector<std::optional<int>> sizes)
        : is_const(is_const), type_tok(type_tok), var_name_tok(var_name_tok), value(value), dimensions(dims), sizes(sizes) {}
    std::string print() {
        std::string type_str = type_tok.value;
        std::string name_str = var_name_tok.value;
        for (int i = 0; i < dimensions; ++i) {
            name_str += "[";
            if (sizes[i].has_value()) name_str += std::to_string(*sizes[i]);
            name_str += "]";
        }

        std::string result = type_str + " " + name_str;
        result += " = " + printAny(value);
        return result;
    }
};

class ListDeclNode {
  public:
    bool is_const;
    Token type_tok;
    Token var_name_tok;
    AnyNode value;

    ListDeclNode(bool is_const, Token type_tok, Token var_name_tok, AnyNode value)
        : is_const(is_const), type_tok(type_tok), var_name_tok(var_name_tok), value(value) {}

    std::string print() { return type_tok.value + " " + var_name_tok.value + " = " + printAny(value); }
};
class ArrayLiteralNode {
  public:
    std::vector<AnyNode> elements;
    Position pos;

    ArrayLiteralNode(std::vector<AnyNode> elems, Position p) : elements(elems), pos(p) {}

    std::string print() {
        std::string result = "[";
        for (size_t i = 0; i < elements.size(); i++) {
            result += printAny(elements[i]);
            if (i < elements.size() - 1) result += ", ";
        }
        return result + "]";
    }
};
class MapLiteralNode {
  public:
    std::vector<std::pair<AnyNode, AnyNode>> pairs;
    Position pos;

    MapLiteralNode(std::vector<std::pair<AnyNode, AnyNode>> p, Position pos) : pairs(p), pos(pos) {}

    std::string print() const { return "map<>"; }
};
class ArrayAccessNode {
  public:
    AnyNode base;
    std::vector<AnyNode> indices;

    ArrayAccessNode(AnyNode base_node, std::vector<AnyNode> idxs) : base(base_node), indices(idxs) {}

    std::string print() {
        std::string s = printAny(base) + "[";
        for (size_t i = 0; i < indices.size(); ++i) {
            s += printAny(indices[i]);
            if (i != indices.size() - 1) s += ", ";
        }
        s += "]";
        return s;
    }
};
class MethodCallNode {
  public:
    AnyNode base;
    Token method_name;
    std::vector<AnyNode> args;

    MethodCallNode(AnyNode base_node, Token method, std::vector<AnyNode> arguments) : base(base_node), method_name(method), args(arguments) {}

    std::string print() { return printAny(base) + "." + method_name.value + "(...)"; }
};
class ReturnNode {
  public:
    AnyNode value;
    Position pos;

    ReturnNode(AnyNode val, Position p) : value(val), pos(p) {}

    std::string print() { return "return " + printAny(value); }
};
class PropertyAccessNode {
  public:
    AnyNode* base;
    Token property_name;
    Token base_name_tok;
    PropertyAccessNode(AnyNode base_node, Token base_name, Token prop)
        : base(new AnyNode(base_node)), base_name_tok(base_name), property_name(prop) {}

    std::string print() { return printAny(*base) + "." + property_name.value; }
};
class SpreadNode {
  public:
    AnyNode expr;

    SpreadNode(AnyNode expression) : expr(expression) {}

    std::string print() { return "@" + printAny(expr); }
};
class ForeachNode {
  public:
    Token elem_type;
    Token elem_name;
    AnyNode collection;
    AnyNode body;

    ForeachNode(Token type, Token name, AnyNode coll, AnyNode body_stmt) : elem_type(type), elem_name(name), collection(coll), body(body_stmt) {}

    std::string print() { return "foreach (" + elem_type.value + " " + elem_name.value + " in ...)"; }
};
class MapDeclNode {
  public:
    bool is_const;
    Token key_type;
    Token value_type;
    Token var_name;
    std::vector<std::pair<AnyNode, AnyNode>> init_pairs;

    MapDeclNode(bool is_const, Token k_type, Token v_type, Token name, std::vector<std::pair<AnyNode, AnyNode>> pairs)
        : is_const(is_const), key_type(k_type), value_type(v_type), var_name(name), init_pairs(pairs) {}

    std::string print() const { return "map<" + key_type.value + ", " + value_type.value + "> " + var_name.value; }
};
class FieldAssignNode {
  public:
    AnyNode base;
    Token field_name;
    AnyNode value;

    FieldAssignNode(AnyNode b, Token f, AnyNode v) : base(b), field_name(f), value(v) {}
    std::string print() const { return printAny(base) + "." + field_name.value + " = " + printAny(value); }
};
class ArrayAssignNode {
  public:
    AnyNode array_access;
    AnyNode value;

    ArrayAssignNode(AnyNode access, AnyNode val) : array_access(access), value(val) {}

    std::string print() const { return "array_assign"; }
};
class RandomCallNode {
  public:
    std::vector<AnyNode> args;

    RandomCallNode(std::vector<AnyNode> a) : args(a) {}

    std::string print() const { return "random()"; }
};

class SeedCallNode {
  public:
    AnyNode value;

    SeedCallNode(AnyNode val) : value(val) {}

    std::string print() const { return "seed()"; }
};
class NamespaceNode {
  public:
    std::string name;
    std::vector<AnyNode> body;

    NamespaceNode(std::string name, std::vector<AnyNode> body) : name(name), body(body) {}
    std::string print() { return "namespace " + name; }
};

//////////////////////////////////////////////////////////////////////////////////////////////
// PARSE RESULT /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
class ParseResult;
using Prs = std::variant<std::monostate, ParseResult, NumberNode, StringNode, CharNode, BoolNode, BinOpNode*, Error*, UnaryOpNode*, VarAccessNode*,
                         VarAssignNode*, AssignExprNode*, StatementsNode*, IfNode*, BreakNode*, SwitchNode*, WhileNode*, ForNode*, ContinueNode*,
                         CallNode*, FuncDefNode*, ReturnNode*, MultiReturnNode*, MultiVarDeclNode*, ArrayDeclNode*, ArrayLiteralNode*,
                         ArrayAccessNode*, ListDeclNode*, MethodCallNode*, PropertyAccessNode*, SpreadNode*, ForeachNode*, QBoolNode, QInNode,
                         QIfNode*, QSwitchNode*, MapDeclNode*, ArrayAssignNode*, SeedCallNode*, RandomCallNode*, FieldAssignNode*, MapLiteralNode*,
                         NamespaceNode*, TryCatchNode*, RefVarDeclNode, NullptrNode>;

class ParseResult {
  public:
    AnyNode node;
    Error* error = nullptr;
    ParseResult() = default;
    AnyNode reg_node(AnyNode res);
    AnyNode reg(Prs res);
    Prs success(AnyNode node);
    void failure(Error*);
    Prs to_prs();
};

class InterpEer {
  public:
    Error* err;
    Position pos;
    InterpEer() {}
    void fail(Error* err, Position pos) {
        this->err = err;
        this->pos = pos;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////
// PARSER ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
class Parser {
  public:
    AnyNode default_value_for_type(const Token& type_tok, const Position& pos);
    std::vector<std::string> namespaceStack;
    size_t index = 0;
    int tmp_counter = 0;
    std::unordered_map<std::string, UserTypeInfo> user_types;
    Token current_tok;
    std::vector<Token> tokens;
    std::string currentNamespace;
    Parser(std::vector<Token> tokens, std::unordered_map<std::string, UserTypeInfo> user_types = {});
    std::string qualify_name(const std::string& name);
    bool is_known_type(const std::string& name) const {
        if (user_types.count(name)) return true;
        std::string ns;
        for (int i = (int)namespaceStack.size() - 1; i >= 0; --i) {
            ns = namespaceStack[i] + (ns.empty() ? "" : "::" + ns);
            for (auto& [k, info] : user_types) {
                if (k == name && info.namespace_path == ns) { return true; }
            }
        }

        return false;
    }
    Token peek(int offset = 1) {
        size_t peek_idx = this->index + offset;
        if (peek_idx < this->tokens.size()) { return this->tokens[peek_idx]; }
        return this->current_tok;
    }
    std::optional<std::string> try_parse_qualified_name() {
        if (current_tok.type != TokenType::IDENTIFIER) return std::nullopt;

        std::string qualified = current_tok.value;
        size_t i = index;

        while (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::SCOPE) {
            if (i + 2 >= tokens.size()) return std::nullopt;
            qualified += "::" + tokens[i + 2].value;
            i += 2;
        }

        return qualified;
    }
    Token consume_qualified_name() {
        if (current_tok.type != TokenType::IDENTIFIER) { throw InvalidSyntaxError("Expected identifier", current_tok.pos); }

        Position start_pos = current_tok.pos;
        std::string qualified = current_tok.value;
        this->advance();
        while (current_tok.type == TokenType::SCOPE) {
            this->advance();

            if (current_tok.type != TokenType::IDENTIFIER) { throw InvalidSyntaxError("Expected identifier after '::'", current_tok.pos); }

            qualified += "::" + current_tok.value;
            this->advance();
        }

        return Token(TokenType::IDENTIFIER, qualified, start_pos);
    }
    UserTypeInfo* find_type(const std::string& name) {
        if (name.find("::") != std::string::npos) {
            if (user_types.count(name)) { return &user_types[name]; }
            return nullptr;
        }

        // Try current namespace
        if (!currentNamespace.empty()) {
            std::string key = currentNamespace + "::" + name;
            if (user_types.count(key)) { return &user_types[key]; }
        }

        // Try parent namespaces
        for (int i = namespaceStack.size() - 1; i >= 0; --i) {
            std::string ns;
            for (int j = 0; j <= i; ++j) {
                if (j > 0) ns += "::";
                ns += namespaceStack[j];
            }
            std::string key = ns + "::" + name;
            if (user_types.count(key)) { return &user_types[key]; }
        }

        // Try global
        if (user_types.count(name)) { return &user_types[name]; }

        return nullptr;
    }
    bool is_known_qualified_type(const std::string& full) const {
        auto pos = full.rfind("::");
        if (pos == std::string::npos) return false;

        std::string ns = full.substr(0, pos);
        std::string name = full.substr(pos + 2);

        for (auto& [k, info] : user_types) {
            if (k == name && info.namespace_path == ns) { return true; }
        }

        return false;
    }

    Token advance();
    Prs factor();
    Prs term();
    Prs comparison();
    Prs expr();
    Prs atom();
    Prs power();
    Prs if_expr();
    Prs return_stmt();
    Prs bin_op(std::function<Prs()> func, std::initializer_list<TokenType> ops);
    Prs logical_and();
    Prs qif_expr();
    Prs bitwise();
    Prs qout_expr();
    Prs qin_expr();
    Prs logical_or();
    Prs switch_stmt();
    Prs qswitch_stmt();
    Aer parse();
    Prs statement();
    Prs while_stmt();
    Prs for_stmt();
    Prs try_catch_expr();
    Prs array_literal();
    Prs call(AnyNode node_to_call);
    Prs func_def(Token return_type, std::optional<Token> func_name);
    Prs func_def_multi(std::vector<Token> return_type, std::optional<Token> func_name);
    Parameter parse_parameter(bool type_only);
    bool in_extern = false;
    bool in_foreign = false;
    inline AnyNode prs_to_anynode(Prs st) {
        return std::visit(
            [](auto arg) -> AnyNode {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_constructible_v<AnyNode, T>) { return AnyNode(arg); }
                return std::monostate{};
            },
            st);
    }

    bool parse_block_into(StatementsNode*& out_block, ParseResult& res) {
        if (this->current_tok.type == TokenType::LBRACE) {
            this->advance();
            std::vector<AnyNode> stmts;
            while (this->current_tok.type != TokenType::RBRACE && this->current_tok.type != TokenType::EOFT) {
                Prs st = this->statement();
                if (std::holds_alternative<Error*>(st)) {
                    res.failure(std::get<Error*>(st));
                    return false;
                }
                AnyNode any_stmt = prs_to_anynode(st);
                stmts.push_back(any_stmt);
            }
            if (this->current_tok.type != TokenType::RBRACE) {
                res.failure(new InvalidSyntaxError("Expected '}' after block", this->current_tok.pos));
                return false;
            }
            this->advance();
            out_block = new StatementsNode(stmts, true);
            return true;
        } else {
            Prs st = this->statement();
            if (std::holds_alternative<Error*>(st)) {
                res.failure(std::get<Error*>(st));
                return false;
            }
            AnyNode any_stmt = prs_to_anynode(st);
            std::vector<AnyNode> stmts;
            stmts.push_back(any_stmt);
            out_block = new StatementsNode(stmts, false);
            return true;
        }
    }
    Prs assignment_expr();
};

struct RunConfig {
    bool use_context = true;
    bool looser_types = false;
    bool print_ast = false;
    bool print_tokens = false;
    bool show_time = false;
    bool quiet_mode = false;
    bool raw = false;
    bool bst = false;
    bool compile_mode = true;
    bool interpret_mode = false;
    bool compile_only = false;
    bool object_only = false;
    bool debug = false;
    bool optimize = true;
    std::string opt_level = "O2";
    std::string output_file = "a.out";
    bool output_wasm = false;
};
//////////////////////////////////////////////////////////////////////////////////////////////
// COMPILER /////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_LLVM
struct AsmOp {
    bool isOutput;
    int index;
    char kind;
};
struct FunctionSignature {
    llvm::FunctionType* type;
    std::vector<llvm::Value*> defaultValues;
};

class LLVMCompiler {
  public:
    llvm::LLVMContext& context;
    llvm::Module* module;
    llvm::IRBuilder<>* builder;
    bool startsWithQIn(const AnyNode& node) {
        if (auto bin = std::get_if<BinOpNode*>(&node)) { return startsWithQIn((*bin)->left_node); }
        if (auto qin = std::get_if<QInNode>(&node)) { return true; }
        return false;
    }
    void generateStructReprFunctions();
    llvm::Value* callStringConcat(llvm::Value* a, llvm::Value* b);
    void createUserTypes();
    llvm::Value* convertToString(llvm::Value* val, AnyNode& expr);
    LLVMCompiler(std::unordered_map<std::string, UserTypeInfo>& userTys, llvm::Module* mod, llvm::LLVMContext& ctx, bool is_main = false);
    std::vector<CTError> compile(StatementsNode* root, std::unordered_map<std::string, FunctionSignature> visibleFunctionSignatures,
                                 std::unordered_map<std::string, FuncDefNode*> visibleFunctionDefs,
                                 std::unordered_map<std::string, std::pair<int, int>> visibleJaggedArrays,
                                 std::unordered_map<std::string, std::string> visibleArrayTypeStrings,
                                 std::unordered_map<std::string, int> visibleLists, std::unordered_map<std::string, int> visibleArrayLengths,
                                 std::unordered_map<std::string, std::pair<int, int>> visibleMaps,
                                 std::unordered_map<std::string, std::string> visibleVarTypes,
                                 std::unordered_map<std::string, llvm::AllocaInst*> visibleRuntimeArraySizes,
                                 std::unordered_map<std::string, llvm::FunctionType*> visibleLambdaTypes,
                                 std::map<std::string, std::map<std::string, llvm::Function*>> visibleSpecializedFunctions,
                                 std::unordered_map<std::string, llvm::GlobalVariable*> visibleGlobals);
    bool is_main;

    void cg_error(const Position& pos, const std::string& msg);
    std::vector<CTError> errors;
    llvm::BasicBlock* currentBreakBB = nullptr;
    llvm::BasicBlock* currentContinueBB = nullptr;
    std::unordered_map<std::string, std::vector<size_t>> autoMethodIndices;

    bool isUnionType(llvm::Type* ty, std::string* outName = nullptr) {
        auto* st = llvm::dyn_cast<llvm::StructType>(ty);
        if (!st) return false;

        std::string name = st->getName().str();
        auto it = unionTypes.find(name);
        if (it == unionTypes.end()) return false;

        if (outName) *outName = name;
        return true;
    }
    bool isEnumType(llvm::Type* ty, std::string* outName = nullptr) {
        auto* st = llvm::dyn_cast<llvm::StructType>(ty);
        if (!st) return false;

        std::string name = st->getName().str();
        auto it = enumTypes.find(name);
        if (it == enumTypes.end()) return false;

        if (outName) *outName = name;
        return true;
    }
    std::string resolveType(const std::string& typeName);
    std::unordered_map<std::string, UserTypeInfo>& userTypes;
    struct EnumMemberValue {
        int tag;
        std::string type;
        std::string value;
    };
    llvm::Value* createEnumData(const std::string& type, const std::string& value) {
        if (type == "string") {
            std::string str = value.substr(1, value.length() - 2);
            return builder->CreateGlobalString(str);
        } else if (type == "int") {
            int i = std::stoi(value);
            llvm::AllocaInst* temp = createEntryAlloca("enum_int", builder->getInt32Ty());
            builder->CreateStore(builder->getInt32(i), temp);
            return builder->CreateBitCast(temp, llvm::PointerType::get(context, 0));
        } else if (type == "float") {
            float f = std::stof(value);
            llvm::AllocaInst* temp = createEntryAlloca("enum_float", builder->getFloatTy());
            builder->CreateStore(llvm::ConstantFP::get(builder->getFloatTy(), f), temp);
            return builder->CreateBitCast(temp, llvm::PointerType::get(context, 0));
        } else if (type == "double") {
            double d = std::stod(value);
            llvm::AllocaInst* temp = createEntryAlloca("enum_double", builder->getDoubleTy());
            builder->CreateStore(llvm::ConstantFP::get(builder->getDoubleTy(), d), temp);
            return builder->CreateBitCast(temp, llvm::PointerType::get(context, 0));
        } else if (type == "bool") {
            bool b = (value == "true");
            llvm::AllocaInst* temp = createEntryAlloca("enum_bool", builder->getInt1Ty());
            builder->CreateStore(builder->getInt1(b), temp);
            return builder->CreateBitCast(temp, llvm::PointerType::get(context, 0));
        } else if (type == "char") {
            std::string charStr = value.substr(1, value.length() - 2);

            char c;
            if (charStr.length() == 1) {
                c = charStr[0];
            } else if (charStr[0] == '\\') {
                switch (charStr[1]) {
                case 'n': c = '\n'; break;
                case 't': c = '\t'; break;
                case 'r': c = '\r'; break;
                case '\\': c = '\\'; break;
                case '\'': c = '\''; break;
                default: c = charStr[1]; break;
                }
            } else {
                c = charStr[0];
            }

            llvm::AllocaInst* temp = createEntryAlloca("enum_char", builder->getInt8Ty());
            builder->CreateStore(builder->getInt8(c), temp);
            return builder->CreateBitCast(temp, llvm::PointerType::get(context, 0));
        }

        return nullptr;
    }
    std::unordered_map<std::string, EnumMemberValue> enumMemberInfo;
    std::unordered_map<std::string, llvm::StructType*> enumTypes;
    std::unordered_map<std::string, std::string> typeAliases;
    std::unordered_map<std::string, llvm::StructType*> structTypes;
    std::unordered_map<std::string, llvm::StructType*> unionTypes;
    std::unordered_map<std::string, llvm::StructType*> classTypes;
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<llvm::Function*>>> classMethods;
    llvm::Value* currentThis = nullptr;
    std::string currentClassName = "";
    llvm::Value* copySpreadToArray(llvm::Value* collVal, AnyNode& collExpr, llvm::Value* destArray, llvm::Value* startIndex, llvm::Type* elemTy,
                                   int elemTypeCode);
    llvm::Value* createRuntimeSizedArray(std::vector<AnyNode>& elements, llvm::Value* totalSize);
    void expandSpreadIntoVector(llvm::Value* collVal, AnyNode& collExpr, std::vector<llvm::Value*>& elements);
    void expandSpreadIntoList(llvm::Value* collVal, AnyNode& collExpr, llvm::Value* listPtr, llvm::Function* pushFn, int elemTypeCode);
    llvm::Value* emitSpreadFunctionCall(llvm::Value* calleeVal, llvm::FunctionType* fnTy, CallNode& call);
    std::unordered_map<std::string, llvm::GlobalVariable*> globals;
    std::unordered_map<std::string, FunctionSignature> functionSignatures;
    std::unordered_map<std::string, FuncDefNode*> functionDefs;
    std::vector<std::unordered_map<std::string, std::pair<int, int>>> jaggedArraysStack;
    std::vector<std::unordered_map<std::string, std::string>> arrayTypeStringsStack;
    std::vector<std::unordered_map<std::string, int>> listsStack;
    std::vector<std::unordered_map<std::string, int>> arrayLengthsStack;
    std::vector<std::unordered_map<std::string, std::pair<int, int>>> mapsStack;
    std::vector<std::unordered_map<std::string, std::string>> varTypesStack;
    std::unordered_map<std::string, llvm::AllocaInst*> runtimeArraySizes;
    std::unordered_map<std::string, llvm::FunctionType*> lambdaTypes;
    int findUnionVariantTag(const std::string& unionName, AnyNode& valueNode, llvm::Value* val);
    llvm::Value* storeAndGetPointer(llvm::Value* val);
    std::map<std::string, std::map<std::string, llvm::Function*>> specializedFunctions;
    template <typename MapType> bool foundInStack(const std::vector<MapType>& stack, const std::string& key) {
        if (stack.empty()) return false;
        for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
            if (it->find(key) != it->end()) { return true; }
        }
        return false;
    }
    unsigned getPtrSize() {
        const llvm::DataLayout& DL = builder->GetInsertBlock()->getModule()->getDataLayout();
        return DL.getPointerSizeInBits();
    }
#define hasVarType(name) foundInStack(varTypesStack, name)
#define hasArrayType(name) foundInStack(arrayTypeStringsStack, name)
#define hasList(name) foundInStack(listsStack, name)
#define hasArrayLength(name) foundInStack(arrayLengthsStack, name)
#define hasMap(name) foundInStack(mapsStack, name)
#define hasJaggedArray(name) foundInStack(jaggedArraysStack, name)
#define lists (listsStack.back())
#define arrayLengths (arrayLengthsStack.back())
#define maps (mapsStack.back())
#define jaggedArrays (jaggedArraysStack.back())
#define varTypes (varTypesStack.back())
#define arrayTypeStrings (arrayTypeStringsStack.back())
#define findList(name) findInStack(listsStack, name)
#define findArrayLength(name) findInStack(arrayLengthsStack, name)
#define findMap(name) findInStack(mapsStack, name)
#define findVarType(name) findInStack(varTypesStack, name)
#define findJaggedArray(name) findInStack(jaggedArraysStack, name)
#define findArrayType(name) findInStack(arrayTypeStringsStack, name)
    void enterScope() {
        jaggedArraysStack.push_back({});
        arrayTypeStringsStack.push_back({});
        listsStack.push_back({});
        arrayLengthsStack.push_back({});
        mapsStack.push_back({});
        varTypesStack.push_back({});
    }

    void exitScope() {
        jaggedArraysStack.pop_back();
        arrayTypeStringsStack.pop_back();
        listsStack.pop_back();
        arrayLengthsStack.pop_back();
        mapsStack.pop_back();
        varTypesStack.pop_back();
    }
    llvm::Value* getCollectionLength(llvm::Value* collVal, AnyNode& collExpr);
    llvm::Value* expandSpreadIntoArrays(llvm::Value* collVal, AnyNode& collExpr, llvm::AllocaInst* argsArray, llvm::AllocaInst* typesArray,
                                        llvm::Value* startIndex);
    template <typename MapType> auto findInStack(std::vector<MapType>& stack, const std::string& key) {
        if (stack.empty()) {
            cg_error(Position("", "", 0, 0, 0), "Stack is empty");
            return stack.back().end();
        }
        for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
            auto found = it->find(key);
            if (found != it->end()) { return found; }
        }
        return stack.back().end();
    }
    std::string makeTypeSignature(const std::vector<std::string>& types) {
        std::string sig;
        for (auto& t : types) {
            if (!sig.empty()) sig += "_";
            sig += t;
        }
        return sig;
    }
    bool funcHasAutoParams(FuncDefNode* funcDef) {

        if (!funcDef) return false;

        for (auto& param : funcDef->params) {
            if (param.type.value == "auto") { return true; }
        }
        for (auto& ret_type : funcDef->return_types) {
            if (ret_type.value == "auto") { return true; }
        }
        return false;
    }
    std::string getExpressionType(AnyNode& node, bool strip = true) {
        if (auto arrLit = std::get_if<ArrayLiteralNode*>(&node)) {
            if (!(*arrLit)->elements.empty()) {
                std::string elemType = getExpressionType((*arrLit)->elements[0]);
                return elemType + "[]";
            }
            return "int[]";
        } else if (auto unaryOp = std::get_if<UnaryOpNode*>(&node)) {
            std::string type = getExpressionType((*unaryOp)->node, strip);
            if ((*unaryOp)->op_tok.type == TokenType::MUL) {
                if (type.ends_with("*")) { type.pop_back(); }
            }
            return type;
        } else if (auto binOp = std::get_if<BinOpNode*>(&node)) {
            std::string leftType = getExpressionType((*binOp)->left_node);
            std::string rightType = getExpressionType((*binOp)->right_node);
            if (leftType == rightType) return leftType;
            if (leftType == "double" || rightType == "double") return "double";
            if (leftType == "float" || rightType == "float") return "float";
            return leftType;
        } else if (auto listDecl = std::get_if<ListDeclNode*>(&node)) {
            return "list<" + (*listDecl)->type_tok.value + ">";
        } else if (auto mapDecl = std::get_if<MapDeclNode*>(&node)) {
            return "map<" + (*mapDecl)->key_type.value + "," + (*mapDecl)->value_type.value + ">";
        } else if (auto strNode = std::get_if<StringNode>(&node)) {
            return "string";
        } else if (auto numNode = std::get_if<NumberNode>(&node)) {
            switch (numNode->tok.type) {
            case TokenType::INT: return "int";
            case TokenType::FLOAT: return "float";
            case TokenType::DOUBLE: return "double";
            case TokenType::ADDR_T: return "addr_t";
            default: break;
            }
        } else if (auto boolNode = std::get_if<BoolNode>(&node)) {
            return "bool";
        } else if (auto charNode = std::get_if<CharNode>(&node)) {
            return "char";
        } else if (auto qboolNode = std::get_if<QBoolNode>(&node)) {
            return "qbool";
        } else if (auto varAcc = std::get_if<VarAccessNode*>(&node)) {
            std::string varName = (*varAcc)->var_name_tok.value;
            if (!resolveVarType(varName).empty()) {
                std::string t = resolveVarType(varName);
                if (t.ends_with("&") && strip) t.pop_back();
                return t;
            }
            if (hasList(varName)) {
                auto it = findList(varName);
                int code = it->second;
                std::string elemType;
                if (code == 0)
                    elemType = "int";
                else if (code == 1)
                    elemType = "float";
                else if (code == 2)
                    elemType = "double";
                else if (code == 3)
                    elemType = "char";
                else if (code == 4)
                    elemType = "bool";
                else if (code == 5)
                    elemType = "qbool";
                else if (code == 6)
                    elemType = "string";
                else
                    elemType = "auto";
                return "list<" + elemType + ">";
            }
            if (hasArrayType(varName)) { return findArrayType(varName)->second + "[]"; }
            if (hasMap(varName)) {
                auto it = findMap(varName);
                auto codeToType = [](int code) -> std::string {
                    if (code == 0) return "int";
                    if (code == 1) return "float";
                    if (code == 2) return "double";
                    if (code == 3) return "char";
                    if (code == 4) return "bool";
                    if (code == 5) return "qbool";
                    if (code == 6) return "string";
                    return "auto";
                };
                std::string keyType = codeToType(it->second.first);
                std::string valType = codeToType(it->second.second);
                return "map<" + keyType + "," + valType + ">";
            }
            if (auto* var = getVarAddress(varName)) { return getTypeName(var->getType()); }
        } else if (auto arrAcc = std::get_if<ArrayAccessNode*>(&node)) {
            std::string baseType = getExpressionType((*arrAcc)->base);
            if (baseType.ends_with("*")) {
                return baseType.substr(0, baseType.size() - 1);
            } else {
                if (auto varAcc = std::get_if<VarAccessNode*>(&(*arrAcc)->base)) {
                    std::string name = (*varAcc)->var_name_tok.value;
                    if (hasList(name)) {
                        auto it = findList(name);
                        int code = it->second;
                        if (code == 0) return "int";
                        if (code == 1) return "float";
                        if (code == 2) return "double";
                        if (code == 3) return "char";
                        if (code == 4) return "bool";
                        if (code == 5) return "qbool";
                        if (code == 6) return "string";
                    }
                    if (hasArrayType(name)) { return arrayTypeStrings[name]; }
                    if (hasMap(name)) {
                        auto it = findMap(name);
                        auto codeToType = [](int code) -> std::string {
                            if (code == 0) return "int";
                            if (code == 1) return "float";
                            if (code == 2) return "double";
                            if (code == 3) return "char";
                            if (code == 4) return "bool";
                            if (code == 5) return "qbool";
                            if (code == 6) return "string";
                            return "auto";
                        };
                        std::string keyType = codeToType(it->second.first);
                        std::string valType = codeToType(it->second.second);
                        return "map<" + keyType + "," + valType + ">";
                    }
                }
            }
            return "unknown";
        } else if (auto nullp = std::get_if<NullptrNode>(&node)) {
            return "@nullptr";
        } else if (auto propAcc = std::get_if<PropertyAccessNode*>(&node)) {
            std::string currentType = getExpressionType(*((*propAcc)->base));
            if (currentType.ends_with("*") || currentType.ends_with("&")) { currentType.pop_back(); }
            std::string fieldName = (*propAcc)->property_name.value;
            while (!currentType.empty() && userTypes.contains(currentType)) {
                auto& info = userTypes[currentType];
                for (const auto& f : info.fields) {
                    if (f.name == fieldName) { return f.type; }
                }
                for (const auto& f : info.classFields) {
                    if (f.name == fieldName) return f.type;
                }
                currentType = info.baseClassName;
            }
            return "unknown";
        }
        return "unknown";
    }
    llvm::Value* emitPropertyAddress(PropertyAccessNode& prop) {
        std::string propName = prop.property_name.value;
        llvm::Value* baseAddr = emitLValue(*prop.base);
        if (!baseAddr) {
            llvm::Value* rval = emitExpr(*prop.base);
            baseAddr = createEntryAlloca("temp_lval_base", rval->getType());
            builder->CreateStore(rval, baseAddr);
        }
        std::string typeName = getExpressionType(*prop.base);
        if (classTypes.count(typeName)) {
            int fieldIdx = getFlattenedFieldIndex(typeName, propName);
            if (fieldIdx == -1) {
                cg_error(prop.property_name.pos, "Field not found in class " + typeName + ": " + propName);
                return nullptr;
            }
            auto [fieldOwnerClass, fieldAccess] = getFieldOwner(typeName, propName);
            if (!canAccessField(currentClassName, fieldOwnerClass, fieldAccess)) {
                cg_error(prop.property_name.pos, "Cannot access " + fieldAccess + " field: " + propName);
                return nullptr;
            }
            return builder->CreateStructGEP(classTypes[typeName], baseAddr, fieldIdx, propName + "_ptr");
        }
        if (structTypes.count(typeName)) {
            auto& info = userTypes[typeName];
            int fieldIdx = -1;
            for (size_t i = 0; i < info.fields.size(); i++) {
                if (info.fields[i].name == propName) {
                    fieldIdx = (int)i;
                    break;
                }
            }
            if (fieldIdx == -1) {
                cg_error(prop.property_name.pos, "Field not found in struct " + typeName + ": " + propName);
                return nullptr;
            }
            return builder->CreateStructGEP(structTypes[typeName], baseAddr, fieldIdx, propName + "_ptr");
        }
        if (unionTypes.count(typeName)) {
            auto& unionInfo = userTypes[typeName];
            llvm::StructType* unionTy = unionTypes[typeName];
            for (auto& member : unionInfo.members) {
                std::string variantName = resolveTypeName(member.type);
                int fieldIdx = getFlattenedFieldIndex(variantName, propName);
                if (fieldIdx == -1 && userTypes.count(variantName)) {
                    auto& sInfo = userTypes[variantName];
                    for (size_t i = 0; i < sInfo.fields.size(); i++) {
                        if (sInfo.fields[i].name == propName) {
                            fieldIdx = i;
                            break;
                        }
                    }
                }
                if (fieldIdx != -1) {
                    llvm::Value* dataFieldPtr = builder->CreateStructGEP(unionTy, baseAddr, 1);
                    llvm::Value* dataPtr = builder->CreateLoad(llvm::PointerType::get(context, 0), dataFieldPtr);
                    llvm::Type* varTy = nullptr;
                    if (classTypes.count(variantName))
                        varTy = classTypes[variantName];
                    else if (structTypes.count(variantName))
                        varTy = structTypes[variantName];
                    if (!varTy) continue;
                    return builder->CreateStructGEP(varTy, dataPtr, fieldIdx, propName + "_ptr");
                }
            }
        }
        cg_error(prop.property_name.pos, "Cannot resolve address for property '" + propName + "' on type '" + typeName + "'");
        return nullptr;
    }
    llvm::StructType* getOrCreateStructType(std::vector<llvm::Type*> fields, const std::string& name) {
        if (auto* existing = llvm::StructType::getTypeByName(context, name)) { return existing; }
        auto* newTy = llvm::StructType::create(context, fields, name);
        return newTy;
    }
    llvm::StructType* getOrCreateStructType(const std::string& name) {
        if (auto* existing = llvm::StructType::getTypeByName(context, name)) { return existing; }
        auto* newTy = llvm::StructType::create(context, name);
        return newTy;
    }
    llvm::Value* emitLValue(AnyNode& node) {
        if (auto var = std::get_if<VarAccessNode*>(&node)) {
            std::string name = (*var)->var_name_tok.value;
            llvm::Value* addr = getVarAddress(name);
            return addr;
        } else if (auto unary = std::get_if<UnaryOpNode*>(&node)) {
            if ((*unary)->op_tok.type == TokenType::MUL) { return emitExpr((*unary)->node); }
        } else if (auto prop = std::get_if<PropertyAccessNode*>(&node)) {
            return emitPropertyAddress(**prop);
        } else if (auto call = std::get_if<CallNode*>(&node)) {
            std::string retType = getExpressionType(node, false);
            if (retType.ends_with("&")) { return emitExpr(node); }
        } else if (auto method = std::get_if<MethodCallNode*>(&node)) {
            std::string retType = getExpressionType(node, false);
            if (retType.ends_with("&")) { return emitExpr(node); }
        }
        return nullptr;
    }
    std::string getElementType(std::string fullType) {
        size_t start = fullType.find("<");
        size_t end = fullType.rfind(">");
        if (start != std::string::npos && end != std::string::npos) { return fullType.substr(start + 1, end - start - 1); }
        return "";
    }
    std::pair<std::string, std::string> splitMapTypes(const std::string& t) {
        size_t start = t.find("<");
        size_t end = t.rfind(">");
        std::string inner = t.substr(start + 1, end - start - 1);

        int depth = 0;
        for (size_t i = 0; i < inner.size(); i++) {
            if (inner[i] == '<') depth++;
            if (inner[i] == '>') depth--;
            if (inner[i] == ',' && depth == 0) { return {inner.substr(0, i), inner.substr(i + 1)}; }
        }
        return {inner, ""};
    }
    std::string getTypeName(llvm::Type* ty) {
        if (ty->isIntegerTy(32)) return "int";
        if (ty->isIntegerTy(16)) return "short";
        if (ty->isIntegerTy(64)) return "long";
        if (ty->isFloatTy()) return "float";
        if (ty->isDoubleTy()) return "double";
        if (ty->isPointerTy()) { return "ptr"; }
        if (auto structTy = llvm::dyn_cast<llvm::StructType>(ty)) { return structTy->getName().str(); }

        return "unknown";
    }
    llvm::Value* emitPrimitiveConversion(llvm::Value* arg, const std::string& target) {
        if (!arg) return nullptr;

        llvm::Type* ty = arg->getType();
        std::string fnName;
        llvm::Type* retTy = nullptr;

        if (target == "int") {
            retTy = builder->getInt32Ty();
            if (ty->isPointerTy())
                fnName = "qc_to_int_from_string";
            else if (ty->isFloatTy())
                fnName = "qc_to_int_from_float";
            else if (ty->isDoubleTy())
                fnName = "qc_to_int_from_double";
            else if (ty->isIntegerTy(1))
                fnName = "qc_to_int_from_bool";
            else if (ty->isIntegerTy(8))
                fnName = "qc_to_int_from_char";
            else if (ty->isIntegerTy(32))
                return arg;
        } else if (target == "float") {
            retTy = builder->getFloatTy();
            if (ty->isPointerTy())
                fnName = "qc_to_float_from_string";
            else if (ty->isIntegerTy(32))
                fnName = "qc_to_float_from_int";
            else if (ty->isDoubleTy())
                fnName = "qc_to_float_from_double";
            else if (ty->isIntegerTy(1))
                fnName = "qc_to_float_from_bool";
            else if (ty->isFloatTy())
                return arg;
        } else if (target == "double") {
            retTy = builder->getDoubleTy();
            if (ty->isPointerTy())
                fnName = "qc_to_double_from_string";
            else if (ty->isIntegerTy(32))
                fnName = "qc_to_double_from_int";
            else if (ty->isFloatTy())
                fnName = "qc_to_double_from_float";
            else if (ty->isIntegerTy(1))
                fnName = "qc_to_double_from_bool";
            else if (ty->isDoubleTy())
                return arg;
        } else if (target == "bool") {
            retTy = builder->getInt1Ty();
            if (ty->isIntegerTy(32))
                fnName = "qc_to_bool_from_int";
            else if (ty->isFloatTy())
                fnName = "qc_to_bool_from_float";
            else if (ty->isDoubleTy())
                fnName = "qc_to_bool_from_double";
            else if (ty->isIntegerTy(1))
                return arg;
        } else if (target == "char") {
            retTy = builder->getInt8Ty();
            if (ty->isPointerTy())
                fnName = "qc_to_char_from_string";
            else if (ty->isIntegerTy(32))
                fnName = "qc_to_char_from_int";
            else if (ty->isIntegerTy(8))
                return arg;
        }

        if (fnName.empty() || !retTy) {
            cg_error(Position(), "Cannot convert to " + target);
            return nullptr;
        }

        llvm::Function* fn = module->getFunction(fnName);
        if (!fn) {
            llvm::FunctionType* fty = llvm::FunctionType::get(retTy, {ty}, false);
            fn = llvm::Function::Create(fty, llvm::Function::ExternalLinkage, fnName, module);
        }

        return builder->CreateCall(fn, {arg}, "to_" + target);
    }
    std::string getFieldType(const std::string& className, const std::string& fieldName) {
        auto it = userTypes.find(className);
        if (it == userTypes.end()) return "";
        auto& info = it->second;
        for (auto& f : info.classFields) {
            if (f.name == fieldName) return f.type;
        }
        if (!info.baseClassName.empty()) { return getFieldType(info.baseClassName, fieldName); }

        return "";
    }
    llvm::Value* emitBuiltinConversion(llvm::Value* rawArg, const std::string& target) {
        if (!rawArg) return nullptr;

        std::string unionName;
        if (isUnionType(rawArg->getType(), &unionName)) {
            llvm::Value* tag = builder->CreateExtractValue(rawArg, 0, "conv_tag");
            llvm::Value* payload = builder->CreateExtractValue(rawArg, 1, "conv_payload");

            auto& members = userTypes[unionName].members;
            llvm::Type* resultTy = nullptr;

            if (target == "int")
                resultTy = builder->getInt32Ty();
            else if (target == "float")
                resultTy = builder->getFloatTy();
            else if (target == "double")
                resultTy = builder->getDoubleTy();
            else if (target == "bool")
                resultTy = builder->getInt1Ty();
            else if (target == "char")
                resultTy = builder->getInt8Ty();
            else {
                cg_error(Position(), "Unknown conversion target: " + target);
                return nullptr;
            }

            llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "conv_union_end", currentFunction);
            llvm::BasicBlock* failBB = llvm::BasicBlock::Create(context, "conv_union_fail", currentFunction);
            llvm::SwitchInst* sw = builder->CreateSwitch(tag, failBB, members.size());

            std::vector<std::pair<llvm::BasicBlock*, llvm::Value*>> incoming;

            for (size_t i = 0; i < members.size(); i++) {
                llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "conv_union_case_" + std::to_string(i), currentFunction);
                sw->addCase(builder->getInt32(i), caseBB);
                builder->SetInsertPoint(caseBB);

                std::string typeStr = members[i].type;
                size_t colonPos = typeStr.find(':');
                if (colonPos != std::string::npos) { typeStr = typeStr.substr(0, colonPos); }

                llvm::Type* memberTy = llvmTypeFor(typeStr);
                llvm::Value* typedPtr = builder->CreateBitCast(payload, llvm::PointerType::get(context, 0));
                llvm::Value* loaded = builder->CreateLoad(memberTy, typedPtr, "conv_loaded");

                llvm::Value* converted = emitPrimitiveConversion(loaded, target);
                if (!converted) return nullptr;

                incoming.push_back({builder->GetInsertBlock(), converted});
                builder->CreateBr(endBB);
            }

            builder->SetInsertPoint(failBB);
            builder->CreateUnreachable();

            builder->SetInsertPoint(endBB);
            llvm::PHINode* phi = builder->CreatePHI(resultTy, incoming.size(), "conv_union_phi");
            for (auto& [bb, val] : incoming) { phi->addIncoming(val, bb); }
            return phi;
        }

        std::string enumName;
        if (isEnumType(rawArg->getType(), &enumName)) {
            llvm::Value* tag = builder->CreateExtractValue(rawArg, 0, "conv_enum_tag");
            llvm::Value* payload = builder->CreateExtractValue(rawArg, 1, "conv_enum_payload");

            auto& entries = userTypes[enumName].enumEntries;
            llvm::Type* resultTy = nullptr;

            if (target == "int")
                resultTy = builder->getInt32Ty();
            else if (target == "float")
                resultTy = builder->getFloatTy();
            else if (target == "double")
                resultTy = builder->getDoubleTy();
            else if (target == "bool")
                resultTy = builder->getInt1Ty();
            else if (target == "char")
                resultTy = builder->getInt8Ty();
            else {
                cg_error(Position(), "Unknown conversion target: " + target);
                return nullptr;
            }

            llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "conv_enum_end", currentFunction);
            llvm::BasicBlock* failBB = llvm::BasicBlock::Create(context, "conv_enum_fail", currentFunction);
            llvm::SwitchInst* sw = builder->CreateSwitch(tag, failBB, entries.size());

            std::vector<std::pair<llvm::BasicBlock*, llvm::Value*>> incoming;

            for (size_t i = 0; i < entries.size(); i++) {
                llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "conv_enum_case_" + std::to_string(i), currentFunction);
                sw->addCase(builder->getInt32(i), caseBB);
                builder->SetInsertPoint(caseBB);

                std::string typeStr = entries[i].typeAtom;
                size_t colonPos = typeStr.find(':');
                if (colonPos != std::string::npos) { typeStr = typeStr.substr(0, colonPos); }

                llvm::Type* memberTy = llvmTypeFor(typeStr);
                llvm::Value* typedPtr = builder->CreateBitCast(payload, llvm::PointerType::get(context, 0));
                llvm::Value* loaded = builder->CreateLoad(memberTy, typedPtr, "conv_enum_loaded");

                llvm::Value* converted = emitPrimitiveConversion(loaded, target);
                if (!converted) return nullptr;

                incoming.push_back({builder->GetInsertBlock(), converted});
                builder->CreateBr(endBB);
            }

            builder->SetInsertPoint(failBB);
            builder->CreateUnreachable();

            builder->SetInsertPoint(endBB);
            llvm::PHINode* phi = builder->CreatePHI(resultTy, incoming.size(), "conv_enum_phi");
            for (auto& [bb, val] : incoming) { phi->addIncoming(val, bb); }
            return phi;
        }

        return emitPrimitiveConversion(rawArg, target);
    }
    llvm::Value* adaptArgumentForParam(llvm::Value* v, AnyNode& argNode, llvm::Type* paramTy, size_t argIndex) {
        if (!v) return nullptr;

        llvm::Type* srcTy = v->getType();

        for (auto& [unionName, unionTy] : unionTypes) {
            if (srcTy == unionTy && !isUnionType(paramTy)) {
                llvm::Value* dataPtr = builder->CreateExtractValue(v, 1, "union_data");
                if (paramTy->isPointerTy()) {
                    v = builder->CreateBitCast(dataPtr, paramTy);
                } else {
                    llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                    v = builder->CreateLoad(paramTy, typedPtr);
                }
                srcTy = paramTy;
                break;
            }

            if (!isUnionType(srcTy) && paramTy == unionTy) {
                int tag = findUnionVariantTag(unionName, argNode, v);
                if (tag == -1) {
                    cg_error(Position(), "Argument doesn't match union variant for parameter " + std::to_string(argIndex));
                    return nullptr;
                }

                llvm::Value* unionVal = llvm::UndefValue::get(unionTy);
                unionVal = builder->CreateInsertValue(unionVal, builder->getInt32(tag), 0);

                llvm::Value* dataPtr = storeAndGetPointer(v);
                unionVal = builder->CreateInsertValue(unionVal, dataPtr, 1);

                v = unionVal;
                srcTy = paramTy;
                break;
            }
        }

        for (auto& [enumName, enumTy] : enumTypes) {
            if (srcTy == enumTy && !isEnumType(paramTy)) {
                llvm::Value* dataPtr = builder->CreateExtractValue(v, 1, "enum_data");
                if (paramTy->isPointerTy()) {
                    v = builder->CreateBitCast(dataPtr, paramTy);
                } else {
                    llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                    v = builder->CreateLoad(paramTy, typedPtr);
                }
                srcTy = paramTy;
                break;
            }

            if (!isEnumType(srcTy) && paramTy == enumTy) {
                int tag = findEnumVariantTag(enumName, argNode, v);
                if (tag == -1) {
                    cg_error(Position(), "Argument doesn't match enum variant for parameter " + std::to_string(argIndex));
                    return nullptr;
                }

                llvm::Value* enumVal = llvm::UndefValue::get(enumTy);
                enumVal = builder->CreateInsertValue(enumVal, builder->getInt32(tag), 0);

                llvm::Value* dataPtr = storeAndGetPointer(v);
                enumVal = builder->CreateInsertValue(enumVal, dataPtr, 1);

                v = enumVal;
                srcTy = paramTy;
                break;
            }
        }

        return v;
    }
    std::vector<llvm::Value*> emitAdaptedArgs(const std::list<AnyNode>& argNodes, llvm::FunctionType* fnTy,
                                              const std::vector<std::string>& paramTypeStrings) {
        std::vector<llvm::Value*> args;
        size_t i = 0;
        for (auto it = argNodes.begin(); it != argNodes.end(); ++it, ++i) {
            AnyNode& argNode = const_cast<AnyNode&>(*it);
            llvm::Value* v = nullptr;
            if (i < paramTypeStrings.size() && paramTypeStrings[i].ends_with("&")) {
                if (auto* varAccess = std::get_if<VarAccessNode*>(&argNode)) {
                    v = getVarAddress((*varAccess)->var_name_tok.value);
                } else {
                    cg_error(Position(), "L-value required for reference parameter");
                    return {};
                }
            } else {
                v = emitExpr(argNode);
            }
            if (!v) return {};
            if (i < fnTy->getNumParams()) {
                llvm::Type* paramTy = fnTy->getParamType(i);
                v = adaptArgumentForParam(v, argNode, paramTy, i);
                if (!v) return {};
            } else {
            }

            args.push_back(v);
        }
        return args;
    }
    std::pair<llvm::Function*, std::string> findMethodInHierarchy(const std::string& className, const std::string& methodName) {
        std::string resolvedClassName = className;
        if (className.find("::") == std::string::npos && !getCurrentNamespace().empty()) {
            std::string qualifiedName = getCurrentNamespace() + "::" + className;
            if (classMethods.find(qualifiedName) != classMethods.end()) { resolvedClassName = qualifiedName; }
        }

        std::string currentClass = resolvedClassName;

        while (!currentClass.empty()) {
            auto classIt = classMethods.find(currentClass);
            if (classIt != classMethods.end()) {
                auto methodIt = classIt->second.find(methodName);
                if (methodIt != classIt->second.end()) {
                    if (!methodIt->second.empty()) { return {methodIt->second[0], currentClass}; }
                }
            }

            auto typeIt = userTypes.find(currentClass);
            if (typeIt != userTypes.end()) {
                std::string baseClass = typeIt->second.baseClassName;
                if (!baseClass.empty() && baseClass.find("::") == std::string::npos) {
                    size_t lastColon = currentClass.rfind("::");
                    if (lastColon != std::string::npos) {
                        std::string ns = currentClass.substr(0, lastColon);
                        std::string qualifiedBase = ns + "::" + baseClass;
                        if (userTypes.find(qualifiedBase) != userTypes.end()) { baseClass = qualifiedBase; }
                    }
                }
                currentClass = baseClass;
            } else {
                break;
            }
        }

        return {nullptr, ""};
    }
    int getFlattenedFieldIndex(const std::string& className, const std::string& fieldName) {
        int index = 0;

        std::function<bool(const std::string&)> searchFields = [&](const std::string& currentClass) -> bool {
            auto& classInfo = userTypes[currentClass];

            if (!classInfo.baseClassName.empty()) {
                std::string baseClass = classInfo.baseClassName;
                if (baseClass.find("::") == std::string::npos) {
                    size_t pos = currentClass.rfind("::");
                    if (pos != std::string::npos) {
                        std::string ns = currentClass.substr(0, pos);
                        std::string qualified = ns + "::" + baseClass;
                        if (userTypes.find(qualified) != userTypes.end()) { baseClass = qualified; }
                    }
                }

                if (searchFields(baseClass)) { return true; }
            }

            for (auto& field : classInfo.classFields) {
                if (field.name == fieldName) { return true; }
                index++;
            }

            return false;
        };
        std::string resolvedClass = className;
        if (className.find("::") == std::string::npos && !getCurrentNamespace().empty()) {
            std::string qualified = getCurrentNamespace() + "::" + className;
            if (userTypes.find(qualified) != userTypes.end()) { resolvedClass = qualified; }
        }

        if (searchFields(resolvedClass)) { return index; }

        return -1;
    }
    bool canAccessMethod(const std::string& callerClass, const std::string& methodClass, const std::string& methodName) {
        auto& classInfo = userTypes[methodClass];
        for (auto& method : classInfo.classMethods) {
            if (method.name_tok.value == methodName) {
                std::string access = method.access;

                if (access == "public") return true;
                if (access == "private") return callerClass == methodClass;
                if (access == "protected") {
                    if (callerClass == methodClass) return true;
                    std::string current = callerClass;
                    while (!current.empty()) {
                        if (current == methodClass) return true;
                        current = userTypes[current].baseClassName;
                    }
                    return false;
                }
            }
        }

        return true;
    }
    std::pair<std::string, std::string> getFieldOwner(const std::string& className, const std::string& fieldName) {
        std::string currentClass = className;

        while (!currentClass.empty()) {
            auto& classInfo = userTypes[currentClass];

            for (auto& field : classInfo.classFields) {
                if (field.name == fieldName) { return {currentClass, field.access}; }
            }
            currentClass = classInfo.baseClassName;
        }

        return {"", "public"};
    }
    bool canAccessField(const std::string& callerClass, const std::string& fieldOwnerClass, const std::string& access) {
        if (access == "public") return true;

        if (access == "private") { return callerClass == fieldOwnerClass; }

        if (access == "protected") {
            if (callerClass == fieldOwnerClass) return true;
            std::string current = callerClass;
            while (!current.empty()) {
                if (current == fieldOwnerClass) return true;
                current = userTypes[current].baseClassName;
            }
            return false;
        }

        return true;
    }
    std::vector<std::string> namespaceStack;
    std::string getCurrentNamespace() {
        if (namespaceStack.empty()) return "";

        std::string result = namespaceStack[0];
        for (size_t i = 1; i < namespaceStack.size(); i++) { result += "::" + namespaceStack[i]; }
        return result;
    }
    std::vector<std::string> getAccessibleNamespaces() {
        std::vector<std::string> accessible;
        accessible.push_back("");
        std::string current = "";
        for (auto& ns : namespaceStack) {
            if (!current.empty()) current += "::";
            current += ns;
            accessible.push_back(current);
        }

        return accessible;
    }
    llvm::Value* tryHandleSpecialized(const std::string& className, const std::string& methodName, MethodCallNode* node, llvm::Value* thisPtr) {
        if (autoMethodIndices.find(className) == autoMethodIndices.end()) return nullptr;
        for (size_t methodIdx : autoMethodIndices[className]) {
            auto& autoMethod = userTypes[className].classMethods[methodIdx];
            if (autoMethod.name_tok.value == methodName && autoMethod.params.size() == node->args.size()) {
                std::vector<std::string> argTypes;
                for (auto& argNode : node->args) argTypes.push_back(getExpressionType(argNode));
                bool paramsMatch = true;
                for (size_t i = 0; i < autoMethod.params.size(); ++i) {
                    if (autoMethod.params[i].type.value != "auto") {
                        std::string declared = autoMethod.params[i].type.value;
                        std::string argT = argTypes[i];
                        if (declared.ends_with("&")) declared.pop_back();
                        if (argT.ends_with("&")) argT.pop_back();
                        if (argT != declared) {
                            paramsMatch = false;
                            break;
                        }
                    }
                }
                if (!paramsMatch) continue;
                std::string specName = className + "_" + methodName;
                for (auto& ty : argTypes) specName += "_" + ty;
                llvm::Function* specFn = module->getFunction(specName);
                if (!specFn) specFn = generateSpecializedMethod(className, methodIdx, argTypes, specName);
                auto args = prepareArgs(&autoMethod, node->args);
                std::vector<llvm::Value*> allArgs = {thisPtr};
                allArgs.insert(allArgs.end(), args.begin(), args.end());
                for (auto* a : allArgs) {
                    if (!a) return (cg_error(node->method_name.pos, "Arg emission failed"), nullptr);
                }

                return builder->CreateCall(specFn, allArgs, methodName + "_result");
            }
        }
        return nullptr;
    }
    std::vector<llvm::Value*> reconcileArgs(llvm::Function* func, llvm::Value* thisPtr, const std::vector<llvm::Value*>& args) {
        std::vector<llvm::Value*> reconciled = {thisPtr};
        auto* funcTy = func->getFunctionType();
        for (size_t i = 0; i < args.size(); i++) {
            llvm::Type* expected = funcTy->getParamType(i + 1);
            llvm::Value* actual = args[i];
            if (actual->getType()->isPointerTy() && expected->isStructTy()) {
                actual = builder->CreateLoad(expected, actual);
                reconciled.push_back(actual);
            } else if (actual->getType() == expected) {
                reconciled.push_back(actual);
            } else if (!expected->isPointerTy() && actual->getType()->isPointerTy()) {
                reconciled.push_back(builder->CreateLoad(expected, actual));
            } else {
                reconciled.push_back(builder->CreateBitCast(actual, expected));
            }
        }
        return reconciled;
    }
    std::vector<llvm::Value*> prepareArgs(ClassMethodInfo* info, std::vector<AnyNode>& argNodes) {
        std::vector<llvm::Value*> args;
        for (size_t i = 0; i < argNodes.size(); i++) {
            bool isRef = info && i < info->params.size() && info->params[i].type.value.ends_with("&");
            if (isRef) {
                args.push_back(emitLValue(argNodes[i]));
            } else {
                args.push_back(emitExpr(argNodes[i]));
            }
        }
        return args;
    }
    llvm::Value* emitMethodCall(llvm::Function* method, llvm::Value* thisPtr, const std::vector<llvm::Value*>& args, const std::string& name) {
        std::vector<llvm::Value*> reconciled = {thisPtr};
        auto* funcTy = method->getFunctionType();
        for (size_t i = 0; i < args.size(); i++) {
            if (i + 1 >= funcTy->getNumParams()) {
                reconciled.push_back(args[i]);
                continue;
            }
            llvm::Type* expected = funcTy->getParamType(i + 1);
            llvm::Value* actual = args[i];
            if (actual->getType()->isPointerTy() && expected->isStructTy()) {
                actual = builder->CreateLoad(expected, actual);
                reconciled.push_back(actual);
            } else if (actual->getType() == expected) {
                reconciled.push_back(actual);
            } else if (!expected->isPointerTy() && actual->getType()->isPointerTy()) {
                reconciled.push_back(builder->CreateLoad(expected, actual));
            } else {
                reconciled.push_back(builder->CreateBitCast(actual, expected));
            }
        }
        return builder->CreateCall(method, reconciled, name + "_result");
    }
    llvm::Function* findMethodOverload(const std::string& className, const std::string& methodName, const std::vector<llvm::Value*>& args) {
        std::string resolvedClassName = className;
        if (className.find("::") == std::string::npos && !getCurrentNamespace().empty()) {
            std::string qualifiedName = getCurrentNamespace() + "::" + className;
            if (classMethods.find(qualifiedName) != classMethods.end()) { resolvedClassName = qualifiedName; }
        }

        std::string currentClass = resolvedClassName;

        while (!currentClass.empty()) {
            auto classIt = classMethods.find(currentClass);
            if (classIt != classMethods.end()) {
                auto methodIt = classIt->second.find(methodName);
                if (methodIt != classIt->second.end()) {
                    llvm::Function* bestMatch = nullptr;
                    int bestScore = 999;
                    for (auto* fn : methodIt->second) {
                        std::string lastargtype = "";
                        for (const auto& method : userTypes.find(currentClass)->second.classMethods) {
                            if (method.name_tok.value == methodName && method.params.size() == (fn->arg_size() - 1)) {
                                if (!method.params.empty()) { lastargtype = method.params.back().type.value; }
                                break;
                            }
                        }
                        int currentScore = 0;
                        bool matches = true;
                        if (lastargtype == "...") {
                            currentScore++;
                            for (size_t i = 0; i < fn->arg_size() - 2; i++) {
                                llvm::Type* expected = fn->getFunctionType()->getParamType(i + 1);
                                llvm::Type* actual = args[i]->getType();
                                if (expected != actual) {
                                    if (expected->isPointerTy() || actual->isPointerTy()) {
                                        currentScore += 1;
                                    } else {
                                        matches = false;
                                        break;
                                    }
                                }
                            }
                            if (matches && currentScore < bestScore) {
                                bestMatch = fn;
                                bestScore = currentScore;
                                if (bestScore == 0) break;
                            }
                            continue;
                        }
                        if (fn->arg_size() - 1 != args.size()) continue;
                        for (size_t i = 0; i < args.size(); i++) {

                            llvm::Type* expected = fn->getFunctionType()->getParamType(i + 1);
                            llvm::Type* actual = args[i]->getType();

                            if (expected != actual) {
                                if (expected->isPointerTy() || actual->isPointerTy()) {
                                    currentScore += 1;
                                } else {
                                    matches = false;
                                    break;
                                }
                            }
                        }

                        if (matches && currentScore < bestScore) {
                            bestMatch = fn;
                            bestScore = currentScore;
                            if (bestScore == 0) break;
                        }
                    }
                    return bestMatch;
                }
            }
            auto typeIt = userTypes.find(currentClass);
            if (typeIt != userTypes.end()) {
                currentClass = typeIt->second.baseClassName;
                if (!currentClass.empty() && currentClass.find("::") == std::string::npos) {
                    size_t lastColon = resolvedClassName.rfind("::");
                    if (lastColon != std::string::npos) {
                        std::string ns = resolvedClassName.substr(0, lastColon);
                        std::string qualifiedBase = ns + "::" + currentClass;
                        if (userTypes.find(qualifiedBase) != userTypes.end()) { currentClass = qualifiedBase; }
                    }
                }
            } else {
                break;
            }
        }

        return nullptr;
    }
    llvm::Function* generateSpecializedMethod(const std::string& className, size_t methodIdx, const std::vector<std::string>& concreteTypes,
                                              const std::string& specializedName) {
        llvm::Function* savedFunction = currentFunction;
        llvm::BasicBlock* savedBlock = builder->GetInsertBlock();
        auto savedLocals = locals;
        auto savedGlobals = globals;
        auto savedThis = currentThis;
        auto savedClassName = currentClassName;
        auto savedNamespaceStack = namespaceStack;
        namespaceStack.clear();
        size_t nsSep = specializedName.rfind("::");
        if (nsSep != std::string::npos) { namespaceStack = {specializedName.substr(0, nsSep)}; }
        enterScope();
        auto& method = userTypes[className].classMethods[methodIdx];
        std::vector<llvm::Type*> paramTypes;
        paramTypes.push_back(llvm::PointerType::get(context, 0));

        for (size_t i = 0; i < method.params.size(); i++) {
            std::string paramType = (method.params[i].type.value == "auto") ? concreteTypes[i] : method.params[i].type.value;

            paramTypes.push_back(llvmTypeFor(paramType));

            if (paramType.starts_with("list<") && paramType.ends_with(">")) {
                std::string elemType = paramType.substr(5, paramType.size() - 6);
                lists[method.params[i].name.value] = getTypeCode(elemType);
            } else if (paramType.ends_with("[]")) {
                arrayTypeStrings[method.params[i].name.value] = paramType.substr(0, paramType.size() - 2);
            } else {
                varTypes[method.params[i].name.value] = paramType;
            }
        }
        llvm::Type* retTy = builder->getVoidTy();

        if (!method.return_types.empty() && method.return_types[0].value == "auto") {
            std::function<std::string(AnyNode&)> inferTypeFromAST = [&](AnyNode& node) -> std::string {
                if (auto retNode = std::get_if<ReturnNode*>(&node)) {
                    if (auto arrAccess = std::get_if<ArrayAccessNode*>(&(*retNode)->value)) {
                        if (auto varAccess = std::get_if<VarAccessNode*>(&(*arrAccess)->base)) {
                            std::string varName = (*varAccess)->var_name_tok.value;
                            for (size_t i = 0; i < method.params.size(); i++) {
                                if (method.params[i].name.value == varName) {
                                    std::string paramType = (method.params[i].type.value == "auto") ? concreteTypes[i] : method.params[i].type.value;

                                    if (paramType.ends_with("[]")) { return paramType.substr(0, paramType.size() - 2); }
                                }
                            }
                        }
                    }
                    if (auto varAccess = std::get_if<VarAccessNode*>(&(*retNode)->value)) {
                        std::string varName = (*varAccess)->var_name_tok.value;
                        for (size_t i = 0; i < method.params.size(); i++) {
                            if (method.params[i].name.value == varName) {
                                return (method.params[i].type.value == "auto") ? concreteTypes[i] : method.params[i].type.value;
                            }
                        }
                    }
                    if (auto unaryOp = std::get_if<UnaryOpNode*>(&(*retNode)->value)) {
                        if (auto varAccess = std::get_if<VarAccessNode*>(&(*unaryOp)->node)) {
                            std::string varName = (*varAccess)->var_name_tok.value;
                            for (size_t i = 0; i < method.params.size(); i++) {
                                if (method.params[i].name.value == varName) {
                                    return (method.params[i].type.value == "auto") ? concreteTypes[i] : method.params[i].type.value;
                                }
                            }
                        }
                    }
                    if (auto binOp = std::get_if<BinOpNode*>(&(*retNode)->value)) {
                        std::string leftType = "unknown";
                        std::string rightType = "unknown";

                        if (auto leftVar = std::get_if<VarAccessNode*>(&(*binOp)->left_node)) {
                            std::string varName = (*leftVar)->var_name_tok.value;
                            for (size_t i = 0; i < method.params.size(); i++) {
                                if (method.params[i].name.value == varName) {
                                    leftType = (method.params[i].type.value == "auto") ? concreteTypes[i] : method.params[i].type.value;
                                    break;
                                }
                            }
                        }

                        if (auto rightVar = std::get_if<VarAccessNode*>(&(*binOp)->right_node)) {
                            std::string varName = (*rightVar)->var_name_tok.value;
                            for (size_t i = 0; i < method.params.size(); i++) {
                                if (method.params[i].name.value == varName) {
                                    rightType = (method.params[i].type.value == "auto") ? concreteTypes[i] : method.params[i].type.value;
                                    break;
                                }
                            }
                        }

                        if (leftType == rightType && leftType != "unknown") { return leftType; }
                        if (leftType == "double" || rightType == "double") return "double";
                        if (leftType == "float" || rightType == "float") return "float";
                        if (leftType != "unknown") return leftType;
                        if (rightType != "unknown") return rightType;
                    }

                    return getExpressionType((*retNode)->value);
                }
                if (auto ifNode = std::get_if<IfNode*>(&node)) {
                    for (auto& stmt : (*ifNode)->then_branch->statements) {
                        std::string ty = inferTypeFromAST(stmt);
                        if (ty != "unknown") return ty;
                    }
                    if ((*ifNode)->else_branch) {
                        for (auto& stmt : (*ifNode)->else_branch->statements) {
                            std::string ty = inferTypeFromAST(stmt);
                            if (ty != "unknown") return ty;
                        }
                    }
                }

                return "unknown";
            };

            std::string inferredTypeStr = "unknown";
            if (method.body) {
                for (auto& stmt : method.body->statements) {
                    inferredTypeStr = inferTypeFromAST(stmt);
                    if (inferredTypeStr != "unknown") break;
                }
            }

            retTy = llvmTypeFor(inferredTypeStr);
        } else if (!method.return_types.empty()) {
            retTy = llvmTypeFor(method.return_types[0].value);
        }
        llvm::FunctionType* fnTy = llvm::FunctionType::get(retTy, paramTypes, false);
        llvm::Function* fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, specializedName, module);
        currentFunction = fn;
        currentClassName = className;
        llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", fn);
        builder->SetInsertPoint(entry);
        auto argIt = fn->arg_begin();
        currentThis = &*argIt;
        ++argIt;
        for (size_t i = 0; i < method.params.size(); i++) {
            std::string paramName = method.params[i].name.value;
            std::string paramType = (method.params[i].type.value == "auto") ? concreteTypes[i] : method.params[i].type.value;

            llvm::Type* paramTy = llvmTypeFor(paramType);
            llvm::AllocaInst* alloc = createEntryAlloca(paramName, paramTy);
            builder->CreateStore(&*argIt, alloc);
            locals[paramName] = alloc;

            if (paramType.ends_with("[]")) {
                std::string elemType = paramType.substr(0, paramType.size() - 2);
                arrayTypeStrings[paramName] = elemType;
            } else if (paramType.starts_with("list<") && paramType.ends_with(">")) {
                std::string elemType = paramType.substr(5, paramType.size() - 6);
                int typeCode = getTypeCode(elemType);
                lists[paramName] = typeCode;
            }

            argIt->setName(paramName);
            ++argIt;
        }
        if (method.body) {
            for (auto& stmt : method.body->statements) { emitStmt(stmt); }
        }
        if (!builder->GetInsertBlock()->getTerminator()) {
            if (retTy->isVoidTy()) {
                builder->CreateRetVoid();
            } else {
                builder->CreateRet(llvm::Constant::getNullValue(retTy));
            }
        }

        currentFunction = savedFunction;
        locals = savedLocals;
        globals = savedGlobals;
        currentThis = savedThis;
        currentClassName = savedClassName;
        namespaceStack = savedNamespaceStack;
        exitScope();
        if (savedBlock) { builder->SetInsertPoint(savedBlock); }

        return fn;
    }
    llvm::Function* generateSpecializedFunction(FuncDefNode* funcDef, const std::vector<std::string>& concreteTypes,
                                                const std::string& specializedName) {
        llvm::Function* savedFunction = currentFunction;
        llvm::BasicBlock* savedBlock = builder->GetInsertBlock();
        auto savedLocals = locals;
        auto savedGlobals = globals;
        auto savedNamespaceStack = namespaceStack;
        namespaceStack.clear();
        size_t nsSep = specializedName.rfind("::");
        if (nsSep != std::string::npos) { namespaceStack = {specializedName.substr(0, nsSep)}; }
        enterScope();

        std::vector<llvm::Type*> paramTypes;
        size_t paramIdx = 0;
        for (auto it = funcDef->params.begin(); it != funcDef->params.end(); ++it, ++paramIdx) {
            std::string paramType = it->type.value;
            if (paramType == "auto") paramType = concreteTypes[paramIdx];

            paramTypes.push_back(llvmTypeFor(paramType));

            if (paramType.starts_with("list<") && paramType.ends_with(">")) {
                std::string elemType = paramType.substr(5, paramType.size() - 6);
                lists[it->name.value] = getTypeCode(elemType);
            } else if (paramType.ends_with("[]")) {
                arrayTypeStrings[it->name.value] = paramType.substr(0, paramType.size() - 2);
            } else {
                varTypes[it->name.value] = paramType;
            }
        }

        llvm::Type* retTy = builder->getVoidTy();

        if (!funcDef->return_types.empty() && funcDef->return_types[0].value == "auto") {
            std::function<std::string(AnyNode&)> inferTypeFromAST = [&](AnyNode& node) -> std::string {
                if (auto retNode = std::get_if<ReturnNode*>(&node)) {
                    if (auto arrAccess = std::get_if<ArrayAccessNode*>(&(*retNode)->value)) {
                        if (auto varAccess = std::get_if<VarAccessNode*>(&(*arrAccess)->base)) {
                            std::string varName = (*varAccess)->var_name_tok.value;
                            auto paramIt = funcDef->params.begin();
                            for (size_t i = 0; i < funcDef->params.size(); i++, ++paramIt) {
                                if (paramIt->name.value == varName) {
                                    std::string paramType = (paramIt->type.value == "auto") ? concreteTypes[i] : paramIt->type.value;
                                    if (paramType.ends_with("[]")) { return paramType.substr(0, paramType.size() - 2); }
                                    if (paramType.starts_with("list<") && paramType.ends_with(">")) {
                                        return paramType.substr(5, paramType.size() - 6);
                                    }
                                }
                            }
                        }
                    }
                    if (auto varAccess = std::get_if<VarAccessNode*>(&(*retNode)->value)) {
                        std::string varName = (*varAccess)->var_name_tok.value;
                        auto paramIt = funcDef->params.begin();
                        for (size_t i = 0; i < funcDef->params.size(); i++, ++paramIt) {
                            if (paramIt->name.value == varName) {
                                std::string paramType = (paramIt->type.value == "auto") ? concreteTypes[i] : paramIt->type.value;
                                return paramType;
                            }
                        }
                    }
                    if (auto unaryOp = std::get_if<UnaryOpNode*>(&(*retNode)->value)) {
                        if (auto varAccess = std::get_if<VarAccessNode*>(&(*unaryOp)->node)) {
                            std::string varName = (*varAccess)->var_name_tok.value;
                            auto paramIt = funcDef->params.begin();
                            for (size_t i = 0; i < funcDef->params.size(); i++, ++paramIt) {
                                if (paramIt->name.value == varName) {
                                    std::string paramType = (paramIt->type.value == "auto") ? concreteTypes[i] : paramIt->type.value;
                                    return paramType;
                                }
                            }
                        }
                    }
                    if (auto binOp = std::get_if<BinOpNode*>(&(*retNode)->value)) {
                        std::string leftType = "unknown";
                        std::string rightType = "unknown";
                        if (auto leftVar = std::get_if<VarAccessNode*>(&(*binOp)->left_node)) {
                            std::string varName = (*leftVar)->var_name_tok.value;
                            auto paramIt = funcDef->params.begin();
                            for (size_t i = 0; i < funcDef->params.size(); i++, ++paramIt) {
                                if (paramIt->name.value == varName) {
                                    leftType = (paramIt->type.value == "auto") ? concreteTypes[i] : paramIt->type.value;
                                    break;
                                }
                            }
                        }
                        if (auto rightVar = std::get_if<VarAccessNode*>(&(*binOp)->right_node)) {
                            std::string varName = (*rightVar)->var_name_tok.value;
                            auto paramIt = funcDef->params.begin();
                            for (size_t i = 0; i < funcDef->params.size(); i++, ++paramIt) {
                                if (paramIt->name.value == varName) {
                                    rightType = (paramIt->type.value == "auto") ? concreteTypes[i] : paramIt->type.value;
                                    break;
                                }
                            }
                        }
                        if (leftType == rightType && leftType != "unknown") { return leftType; }
                        if (leftType == "double" || rightType == "double") return "double";
                        if (leftType == "float" || rightType == "float") return "float";
                        if (leftType != "unknown") return leftType;
                        if (rightType != "unknown") return rightType;
                    }
                    return getExpressionType((*retNode)->value);
                }

                if (auto multiRet = std::get_if<MultiReturnNode*>(&node)) {
                    std::vector<std::string> types;
                    for (auto& val : (*multiRet)->values) {
                        if (auto arrAccess = std::get_if<ArrayAccessNode*>(&val)) {
                            if (auto varAccess = std::get_if<VarAccessNode*>(&(*arrAccess)->base)) {
                                std::string varName = (*varAccess)->var_name_tok.value;

                                auto paramIt = funcDef->params.begin();
                                for (size_t i = 0; i < funcDef->params.size(); i++, ++paramIt) {
                                    if (paramIt->name.value == varName) {
                                        std::string paramType = (paramIt->type.value == "auto") ? concreteTypes[i] : paramIt->type.value;

                                        if (paramType.ends_with("[]")) {
                                            types.push_back(paramType.substr(0, paramType.size() - 2));
                                            goto next_val;
                                        }
                                    }
                                }
                            }
                        }
                        types.push_back(getExpressionType(val));
                    next_val:;
                    }

                    std::string result;
                    for (auto& t : types) {
                        if (!result.empty()) result += ",";
                        result += t;
                    }
                    return result;
                }

                if (auto ifNode = std::get_if<IfNode*>(&node)) {
                    for (auto& stmt : (*ifNode)->then_branch->statements) {
                        std::string ty = inferTypeFromAST(stmt);
                        if (ty != "unknown") return ty;
                    }
                    for (auto& [cond, body] : (*ifNode)->elif_branches) {
                        for (auto& stmt : body->statements) {
                            std::string ty = inferTypeFromAST(stmt);
                            if (ty != "unknown") return ty;
                        }
                    }
                    if ((*ifNode)->else_branch) {
                        for (auto& stmt : (*ifNode)->else_branch->statements) {
                            std::string ty = inferTypeFromAST(stmt);
                            if (ty != "unknown") return ty;
                        }
                    }
                }

                if (auto qifNode = std::get_if<QIfNode*>(&node)) {
                    for (auto& stmt : (*qifNode)->then_branch->statements) {
                        std::string ty = inferTypeFromAST(stmt);
                        if (ty != "unknown") return ty;
                    }
                }

                if (auto whileNode = std::get_if<WhileNode*>(&node)) {
                    for (auto& stmt : (*whileNode)->body->statements) {
                        std::string ty = inferTypeFromAST(stmt);
                        if (ty != "unknown") return ty;
                    }
                }

                if (auto forNode = std::get_if<ForNode*>(&node)) {
                    for (auto& stmt : (*forNode)->body->statements) {
                        std::string ty = inferTypeFromAST(stmt);
                        if (ty != "unknown") return ty;
                    }
                }

                if (auto switchNode = std::get_if<SwitchNode*>(&node)) {
                    for (auto& section : (*switchNode)->sections) {
                        if (section.body) {
                            for (auto& stmt : section.body->statements) {
                                std::string ty = inferTypeFromAST(stmt);
                                if (ty != "unknown") return ty;
                            }
                        }
                    }
                }

                if (auto stmtsNode = std::get_if<StatementsNode*>(&node)) {
                    for (auto& stmt : (*stmtsNode)->statements) {
                        std::string ty = inferTypeFromAST(stmt);
                        if (ty != "unknown") return ty;
                    }
                }

                return "unknown";
            };

            std::string inferredTypeStr = "unknown";
            for (auto& stmt : funcDef->body->statements) {
                inferredTypeStr = inferTypeFromAST(stmt);
                if (inferredTypeStr != "unknown") break;
            }

            if (inferredTypeStr.find(',') != std::string::npos) {
                std::vector<llvm::Type*> types;
                size_t pos = 0;
                std::string remaining = inferredTypeStr;
                while ((pos = remaining.find(',')) != std::string::npos) {
                    types.push_back(llvmTypeFor(remaining.substr(0, pos)));
                    remaining.erase(0, pos + 1);
                }
                types.push_back(llvmTypeFor(remaining));
                retTy = llvm::StructType::get(context, types);
            } else {
                retTy = llvmTypeFor(inferredTypeStr);
            }
        } else if (!funcDef->return_types.empty()) {
            if (funcDef->return_types.size() > 1) {
                std::vector<llvm::Type*> retTypes;
                for (auto& rt : funcDef->return_types) { retTypes.push_back(llvmTypeFor(rt.value)); }
                retTy = llvm::StructType::get(context, retTypes);
            } else {
                retTy = llvmTypeFor(funcDef->return_types[0].value);
            }
        }
        llvm::FunctionType* fnTy = llvm::FunctionType::get(retTy, paramTypes, false);
        llvm::Function* fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, specializedName, module);

        currentFunction = fn;
        llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", fn);
        builder->SetInsertPoint(entry);
        auto argIt = fn->arg_begin();
        paramIdx = 0;
        for (auto it = funcDef->params.begin(); it != funcDef->params.end(); ++it, ++paramIdx) {
            std::string paramName = it->name.value;
            std::string paramType = (it->type.value == "auto") ? concreteTypes[paramIdx] : it->type.value;

            llvm::Value* alloca = createEntryAlloca(paramName, llvmTypeFor(paramType));
            builder->CreateStore(&*argIt, alloca);
            locals[paramName] = llvm::cast<llvm::AllocaInst>(alloca);

            if (paramType.ends_with("[]")) {
                std::string elemType = paramType.substr(0, paramType.size() - 2);
                arrayTypeStrings[paramName] = elemType;
            } else if (paramType.starts_with("list<") && paramType.ends_with(">")) {
                std::string elemType = paramType.substr(5, paramType.size() - 6);
                int typeCode = getTypeCode(elemType);
                lists[paramName] = typeCode;
            }

            argIt->setName(paramName);
            ++argIt;
        }
        for (auto& stmt : funcDef->body->statements) { emitStmt(stmt); }

        if (!builder->GetInsertBlock()->getTerminator()) {
            if (retTy->isVoidTy()) {
                builder->CreateRetVoid();
            } else {
                builder->CreateRet(llvm::Constant::getNullValue(retTy));
            }
        }

        exitScope();
        namespaceStack = savedNamespaceStack;
        currentFunction = savedFunction;
        locals = savedLocals;
        globals = savedGlobals;
        if (savedBlock) { builder->SetInsertPoint(savedBlock); }

        return fn;
    }
    llvm::Value* packVariadicArgs(const std::vector<llvm::Value*>& var_vals) {
        llvm::Value* args_cnt = builder->getInt32(var_vals.size());
        llvm::Value* items_array = builder->CreateAlloca(builder->getPtrTy(), args_cnt, "varargs_array");
        for (size_t i = 0; i < var_vals.size(); ++i) {
            llvm::Value* index = builder->getInt32(i);
            llvm::Value* element_ptr = builder->CreateGEP(builder->getPtrTy(), items_array, index);
            llvm::Value* valueToStore = var_vals[i];
            llvm::Type* valTy = valueToStore->getType();
            if (valTy->isIntegerTy()) {
                valueToStore = builder->CreateIntToPtr(valueToStore, builder->getPtrTy(), "vararg_int_to_ptr");
            } else if (valTy->isFloatingPointTy()) {
                llvm::Value* int64Bits = nullptr;
                if (valTy->isFloatTy()) {
                    llvm::Value* int32Bits = builder->CreateBitCast(valueToStore, builder->getInt32Ty(), "float_to_i32");
                    int64Bits = builder->CreateZExt(int32Bits, builder->getIntNTy(getPtrSize()), "i32_to_i64");
                } else {
                    int64Bits = builder->CreateBitCast(valueToStore, builder->getIntNTy(getPtrSize()), "double_to_i64");
                }
                valueToStore = builder->CreateIntToPtr(int64Bits, builder->getPtrTy(), "fp_bits_to_ptr");
            }
            builder->CreateStore(valueToStore, element_ptr);
        }
        llvm::StructType* VariadicStructTy = llvm::StructType::get(context, {builder->getPtrTy(), builder->getInt32Ty(), builder->getInt32Ty()});
        llvm::Value* variadic_struct = builder->CreateAlloca(VariadicStructTy, nullptr, "variadic_struct");
        builder->CreateStore(items_array, builder->CreateStructGEP(VariadicStructTy, variadic_struct, 0));
        builder->CreateStore(args_cnt, builder->CreateStructGEP(VariadicStructTy, variadic_struct, 1));
        builder->CreateStore(builder->getInt32(0), builder->CreateStructGEP(VariadicStructTy, variadic_struct, 2));
        return variadic_struct;
    }
    std::string resolveTypeName(const std::string& name) {
        if (name == "int" || name == "float" || name == "double" || name == "char" || name == "bool" || name == "qbool" || name == "string" ||
            name == "void" || name == "auto" || name == "short int" || name == "long int" || name == "long double") {
            return name;
        }
        if (name.ends_with("[]") || name.starts_with("list<") || name.starts_with("map<")) { return name; }
        auto aliasIt = typeAliases.find(name);
        if (aliasIt != typeAliases.end()) { return resolveTypeName(aliasIt->second); }
        if (name.find("::") != std::string::npos) {
            if (classTypes.find(name) != classTypes.end()) return name;
            if (structTypes.find(name) != structTypes.end()) return name;
            if (enumTypes.find(name) != enumTypes.end()) return name;
            if (unionTypes.find(name) != unionTypes.end()) return name;
            if (typeAliases.find(name) != typeAliases.end()) return name;
        }
        std::string current = getCurrentNamespace();

        while (true) {
            std::string fullName = current.empty() ? name : current + "::" + name;
            if (classTypes.find(fullName) != classTypes.end()) return fullName;
            if (structTypes.find(fullName) != structTypes.end()) return fullName;
            if (enumTypes.find(fullName) != enumTypes.end()) return fullName;
            if (unionTypes.find(fullName) != unionTypes.end()) return fullName;
            if (hasList(fullName)) return fullName;
            if (hasArrayType(fullName)) return fullName;
            if (hasMap(fullName)) return fullName;

            if (current.empty()) break;

            size_t pos = current.rfind("::");
            current = (pos == std::string::npos) ? "" : current.substr(0, pos);
        }
        return name;
    }
    llvm::Type* getPointeeType(const std::string& name) {
        std::string typeStr = resolveVarType(name);
        if (typeStr.empty()) {
            llvm::Value* ptr = resolveVariable(name);
            if (auto* alloca = llvm::dyn_cast<llvm::AllocaInst>(ptr)) { return alloca->getAllocatedType(); }
            if (auto* gv = llvm::dyn_cast<llvm::GlobalVariable>(ptr)) { return gv->getValueType(); }
            return nullptr;
        }
        if (typeStr.ends_with("&")) { typeStr.pop_back(); }

        return llvmTypeFor(typeStr);
    }
    llvm::Value* resolveGlobal(const std::string& name) {
        if (name.find("::") != std::string::npos) {
            auto git = globals.find(name);
            if (git != globals.end()) return git->second;
            return nullptr;
        }
        std::string current = getCurrentNamespace();
        while (true) {
            std::string fullName = current.empty() ? name : current + "::" + name;
            auto git = globals.find(fullName);
            if (git != globals.end()) return git->second;

            if (current.empty()) break;
            size_t pos = current.rfind("::");
            current = (pos == std::string::npos) ? "" : current.substr(0, pos);
        }
        auto git = globals.find(name);
        if (git != globals.end()) return git->second;
        return nullptr;
    }
    llvm::FunctionType* resolveLambdaType(const std::string& name) {
        if (name.find("::") != std::string::npos) {
            auto it = lambdaTypes.find(name);
            if (it != lambdaTypes.end()) return it->second;
            return nullptr;
        }
        std::string current = getCurrentNamespace();
        while (true) {
            std::string fullName = current.empty() ? name : current + "::" + name;
            auto it = lambdaTypes.find(fullName);
            if (it != lambdaTypes.end()) return it->second;

            if (current.empty()) break;
            size_t pos = current.rfind("::");
            current = (pos == std::string::npos) ? "" : current.substr(0, pos);
        }
        auto it = lambdaTypes.find(name);
        if (it != lambdaTypes.end()) return it->second;
        return nullptr;
    }
    llvm::Value* resolveVariable(const std::string& name) {
        if (name.find("::") != std::string::npos) {
            if (locals.count(name)) return locals[name];
            if (globals.count(name)) return globals[name];
            return nullptr;
        }
        std::string current = getCurrentNamespace();
        while (true) {
            std::string fullName = current.empty() ? name : current + "::" + name;
            auto it = locals.find(fullName);
            if (it != locals.end()) { return it->second; }
            auto git = globals.find(fullName);
            if (git != globals.end()) { return git->second; }
            if (current.empty()) break;
            size_t pos = current.rfind("::");
            current = (pos == std::string::npos) ? "" : current.substr(0, pos);
        }
        if (locals.count(name)) return locals[name];
        if (globals.count(name)) return globals[name];
        return nullptr;
    }
    std::string resolveVarType(const std::string& name) {
        if (name.find("::") != std::string::npos) {
            if (hasVarType(name)) return findVarType(name)->second;
            return "";
        }
        std::string current = getCurrentNamespace();
        while (true) {
            std::string fullName = current.empty() ? name : current + "::" + name;
            if (hasVarType(fullName)) return findVarType(fullName)->second;
            if (current.empty()) break;
            size_t pos = current.rfind("::");
            current = (pos == std::string::npos) ? "" : current.substr(0, pos);
        }
        if (hasVarType(name)) return findVarType(name)->second;
        return "";
    }

    llvm::Value* getVarAddress(const std::string& name) {
        llvm::Value* addr = resolveVariable(name);
        if (resolveVarType(name).ends_with("&")) { return builder->CreateLoad(builder->getPtrTy(), addr); }
        return addr;
    }
    std::string resolveMetadataName(const std::string& name) {
        if (name.find("::") != std::string::npos) return name;

        std::string current = getCurrentNamespace();
        while (true) {
            std::string fullName = current.empty() ? name : current + "::" + name;
            if (hasList(fullName) || hasArrayType(fullName) || hasJaggedArray(fullName)) { return fullName; }

            if (current.empty()) break;
            size_t pos = current.rfind("::");
            current = (pos == std::string::npos) ? "" : current.substr(0, pos);
        }
        return name;
    }
    llvm::Function* resolveFunction(const std::string& name) {
        if (name.find("::") != std::string::npos) { return module->getFunction(name); }
        std::string current = getCurrentNamespace();
        while (true) {
            std::string fullName = current.empty() ? name : current + "::" + name;

            llvm::Function* fn = module->getFunction(fullName);
            if (fn) return fn;

            if (current.empty()) break;

            size_t pos = current.rfind("::");
            current = (pos == std::string::npos) ? "" : current.substr(0, pos);
        }

        return nullptr;
    }

    llvm::Value* toTruthiness(llvm::Value* v, const Position& pos) {
        llvm::Type* ty = v->getType();

        if (ty->isIntegerTy(1)) { return v; }

        if (ty->isIntegerTy(2)) {
            llvm::Value* zero = builder->getIntN(2, 0);
            return builder->CreateICmpNE(v, zero, "qbool_truthy");
        }

        if (ty->isIntegerTy()) {
            llvm::Value* zero = llvm::ConstantInt::get(ty, 0);
            return builder->CreateICmpNE(v, zero, "int_truthy");
        }

        if (ty->isFloatingPointTy()) {
            llvm::Value* zero = llvm::ConstantFP::get(ty, 0.0);
            return builder->CreateFCmpONE(v, zero, "float_truthy");
        }

        if (ty->isPointerTy()) {
            llvm::Value* nullPtr = llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(ty));
            return builder->CreateICmpNE(v, nullPtr, "ptr_truthy");
        }
        if (auto structTy = llvm::dyn_cast<llvm::StructType>(ty)) {
            std::string className = structTy->getName().str();

            auto evalMethod = findMethodInHierarchy(className, "eval");
            if (evalMethod.first) {
                std::vector<llvm::Value*> args;

                llvm::AllocaInst* temp = createEntryAlloca("temp_eval", ty);
                builder->CreateStore(v, temp);
                args.push_back(temp);

                return builder->CreateCall(evalMethod.first, args);
            }
        }
        return builder->getInt1(1);
    }
    std::string getOperatorMethodName(TokenType op) {
        switch (op) {
        case TokenType::PLUS: return "operator+";
        case TokenType::MINUS: return "operator-";
        case TokenType::MUL: return "operator*";
        case TokenType::DIV: return "operator/";
        case TokenType::EQ_TO: return "operator==";
        case TokenType::NOT_EQ: return "operator!=";
        case TokenType::OR: return "operator||";
        case TokenType::AND: return "operator&&";
        case TokenType::NOT: return "operator!";
        case TokenType::MORE: return "operator>";
        case TokenType::LESS: return "operator<";
        case TokenType::MORE_EQ: return "operator>=";
        case TokenType::LESS_EQ: return "operator<=";
        case TokenType::POWER: return "operator#^";
        case TokenType::MOD: return "operator%";
        case TokenType::QNOT: return "operator!!";
        case TokenType::QAND: return "operator&&&";
        case TokenType::QOR: return "operator|||";
        case TokenType::QXOR: return "operator^^";
        case TokenType::COLLAPSE_OR: return "operator|&|";
        case TokenType::COLLAPSE_AND: return "operator&|&";
        case TokenType::XOR: return "operator^";
        default: return "";
        }
    }
    std::string getUnaryOperatorMethodName(TokenType op) {
        switch (op) {
        case TokenType::QNOT: return "operator!!";
        case TokenType::NOT: return "operator!";
        default: return "";
        }
    }
    struct UnionMatchInfo {
        int tagIndex = -1;
        std::string memberTypeStr;
    };

    std::optional<UnionMatchInfo> matchValueToUnionVariant(const std::string& unionName, AnyNode& valueNode, llvm::Value* val) {
        auto typeIt = userTypes.find(unionName);
        if (typeIt == userTypes.end()) return std::nullopt;

        auto& members = typeIt->second.members;

        int tag = findUnionVariantTag(unionName, valueNode, val);

        if (tag < 0 || (size_t)tag >= members.size()) { return std::nullopt; }
        UnionMatchInfo info;
        info.tagIndex = tag;

        const std::string& spec = members[tag].type;
        if (spec.find(':') == std::string::npos) {
            info.memberTypeStr = spec;
        } else {
            info.memberTypeStr.clear();
        }

        return info;
    }

  private:
    llvm::Type* getTypeFromCode(int code) {
        switch (code) {
        case 0: return builder->getInt32Ty();
        case 1: return builder->getFloatTy();
        case 2: return builder->getDoubleTy();
        case 3: return builder->getInt8Ty();
        case 4: return builder->getInt1Ty();
        case 5: return builder->getIntNTy(2);
        case 6: return llvm::PointerType::get(context, 0);
        default: return builder->getInt32Ty();
        }
    }
    int getTypeCode(const std::string& type) {
        if (type == "int") return 0;
        if (type == "float") return 1;
        if (type == "double") return 2;
        if (type == "char") return 3;
        if (type == "bool") return 4;
        if (type == "qbool") return 5;
        if (type == "string") return 6;
        return -1;
    }
    int getTypeCodeFromLLVM(llvm::Type* ty) {
        if (ty->isFloatTy()) return 1;    // float
        if (ty->isDoubleTy()) return 2;   // double
        if (ty->isIntegerTy(8)) return 3; // char
        if (ty->isIntegerTy(1)) return 4; // bool
        if (ty->isIntegerTy(2)) return 5; // qbool
        if (ty->isPointerTy()) return 6;  // string (or any pointer)
        if (ty->isIntegerTy()) return 0;  // int
        return -1;
    }
    llvm::Value* createJaggedArray(AnyNode& literalNode, int elemTypeCode, int depth);
    std::pair<bool, int> checkJagged(AnyNode& node);
    llvm::Value* boolToQBool(llvm::Value* boolVal);
    void addRuntimeToModule();
    llvm::Function* emitFuncDef(const FuncDefNode& fn);
    llvm::FunctionType* llvmFuncTypeForHelper(const std::vector<Token>& returnTypes, const std::vector<ParamTypeInfo>& params);
    llvm::FunctionType* llvmFuncTypeFor(const std::vector<Token>& retTypes, const std::list<Parameter>& params);
    llvm::FunctionType* llvmFuncTypeFor(const std::vector<Token>& returnTypes, const std::vector<Parameter>& params);
    llvm::Type* llvmTypeFor(const std::string& qcType);
    std::string lambdaName();
    std::string mangleName(const FuncDefNode& fn);
    std::unordered_map<std::string, llvm::AllocaInst*> locals;
    std::unordered_map<std::string, llvm::Function*> functions;
    llvm::Function* currentFunction = nullptr;
    llvm::AllocaInst* createEntryAlloca(const std::string& name, llvm::Type* ty);
    llvm::Value* emitExpr(AnyNode& node);
    llvm::Value* extractUnionToBestGuess(llvm::Value* unionVal) {
        std::string unionName;
        if (!isUnionType(unionVal->getType(), &unionName)) { return unionVal; }

        auto utIt = userTypes.find(unionName);
        if (utIt == userTypes.end()) { return nullptr; }

        auto& info = utIt->second;
        auto& members = info.members;
        if (members.empty()) return nullptr;
        std::string targetTypeStr;
        for (auto& m : members) {
            const std::string& t = m.type;
            if (t.empty()) continue;
            if (t.starts_with("\"") || t.starts_with("'") || std::isdigit(t[0]) || t == "true" || t == "false" || t == "qtrue" || t == "qfalse" ||
                t == "none" || t == "both") {
                continue;
            }
            targetTypeStr = t;
            break;
        }

        if (targetTypeStr.empty()) { targetTypeStr = "int"; }

        llvm::Type* targetTy = llvmTypeFor(targetTypeStr);
        llvm::Value* dataPtr = builder->CreateExtractValue(unionVal, 1, "union_data");
        llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
        return builder->CreateLoad(targetTy, typedPtr, "union_unwrapped");
    }
    llvm::Value* normalizeValue(llvm::Value* v, AnyNode& expr) {
        llvm::Type* ty = v->getType();

        std::string unionName, enumName;
        bool isUnion = isUnionType(ty, &unionName);
        bool isEnum = isEnumType(ty, &enumName);

        if (!isUnion && !isEnum) { return v; }

        std::string typeName = isUnion ? unionName : enumName;
        auto utIt = userTypes.find(typeName);
        if (utIt == userTypes.end()) return v;

        llvm::Value* tag = builder->CreateExtractValue(v, 0, "tag");
        llvm::Value* payload = builder->CreateExtractValue(v, 1, "payload");

        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "norm_end", currentFunction);

        llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
        llvm::AllocaInst* tmp = createEntryAlloca("norm_tmp", voidPtrTy);

        size_t memberCount = isUnion ? utIt->second.members.size() : utIt->second.enumEntries.size();

        llvm::SwitchInst* sw = builder->CreateSwitch(tag, endBB, memberCount);

        for (size_t i = 0; i < memberCount; ++i) {
            llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "norm_case_" + std::to_string(i), currentFunction);
            sw->addCase(builder->getInt32(i), caseBB);
            builder->SetInsertPoint(caseBB);

            std::string typeStr;
            if (isUnion) {
                typeStr = utIt->second.members[i].type;
                size_t colonPos = typeStr.find(':');
                if (colonPos != std::string::npos) { typeStr = typeStr.substr(0, colonPos); }
            } else {
                typeStr = utIt->second.enumEntries[i].typeAtom;
                size_t colonPos = typeStr.find(':');
                if (colonPos != std::string::npos) { typeStr = typeStr.substr(0, colonPos); }
            }

            llvm::Type* memberTy = llvmTypeFor(typeStr);

            llvm::Value* typedPtr = builder->CreateBitCast(payload, llvm::PointerType::get(context, 0));
            llvm::Value* loaded = builder->CreateLoad(memberTy, typedPtr, "member");
            llvm::AllocaInst* memberAlloc = createEntryAlloca("member_tmp", memberTy);
            builder->CreateStore(loaded, memberAlloc);
            llvm::Value* asVoidPtr = builder->CreateBitCast(memberAlloc, voidPtrTy);
            builder->CreateStore(asVoidPtr, tmp);
            builder->CreateBr(endBB);
        }

        builder->SetInsertPoint(endBB);

        return builder->CreateLoad(voidPtrTy, tmp, "normalized");
    }
    struct EnumMatchInfo {
        int tagIndex;
        std::string memberTypeStr;
        std::string memberValue;
    };
    int findEnumVariantTag(const std::string& enumName, AnyNode& valueNode, llvm::Value* val) {
        auto match = matchValueToEnumMember(enumName, valueNode, val);
        if (match) { return match->tagIndex; }
        return -1;
    }
    std::optional<EnumMatchInfo> matchValueToEnumMember(const std::string& enumName, AnyNode& valueNode, llvm::Value* val) {
        auto typeIt = userTypes.find(enumName);
        if (typeIt == userTypes.end() || typeIt->second.kind != UserTypeKind::Enum) { return std::nullopt; }

        auto& entries = typeIt->second.enumEntries;

        for (size_t i = 0; i < entries.size(); i++) {
            auto& entry = entries[i];

            size_t colonPos = entry.typeAtom.find(':');
            if (colonPos == std::string::npos) continue;

            std::string type = entry.typeAtom.substr(0, colonPos);
            std::string value = entry.typeAtom.substr(colonPos + 1);

            bool matches = false;

            if (type == "int" || type == "float" || type == "double" || type == "addr_t") {
                if (auto numNode = std::get_if<NumberNode>(&valueNode)) {
                    if (numNode->tok.value == value) { matches = true; }
                }
            } else if (type == "string") {
                if (auto strNode = std::get_if<StringNode>(&valueNode)) {
                    std::string strValue = value.substr(1, value.length() - 2);
                    if (strNode->tok.value == strValue) { matches = true; }
                }
            } else if (type == "char") {
                if (auto charNode = std::get_if<CharNode>(&valueNode)) {
                    char c = value[1];
                    if (charNode->tok.value[0] == c) { matches = true; }
                }
            } else if (type == "bool") {
                if (auto boolNode = std::get_if<BoolNode>(&valueNode)) {
                    if (boolNode->tok.value == value) { matches = true; }
                }
            }

            if (matches) { return EnumMatchInfo{(int)i, type, value}; }
        }

        return std::nullopt;
    }
    void emitStmt(AnyNode& node);
};
#endif
//////////////////////////////////////////////////////////////////////////////////////////////
// RUN //////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
Mer run(std::string file, std::string text, RunConfig config);

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
    Token make_raw_string();
};
} // namespace tkz
std::string trim(const std::string& str);
std::string resolve_path(const std::string& current_file, const std::string& include_path);
struct PreprocessResult {
    std::string clean_source;
    std::vector<std::string> dependency_paths;
    std::unordered_map<std::string, std::vector<std::string>> included_namespaces;
    std::unordered_set<std::string> accessible_namespaces;
};

PreprocessResult preprocess_includes(const std::string& source, const std::string& current_file);
#endif
