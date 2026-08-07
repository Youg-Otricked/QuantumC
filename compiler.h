#ifndef TOKEN_H
#define TOKEN_H
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <optional>
#include <ranges>
#include <set>
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
extern bool isHeader;
extern uint64_t invokeCounter;
bool isCharInSet(char, const std::string&);
inline int levenshteinDistance(const std::string& a, const std::string& b) { // hehe fancy word
    std::vector<int> prev(b.size() + 1);
    std::vector<int> curr(b.size() + 1);
    for (size_t j = 0; j <= b.size(); j++) prev[j] = static_cast<int>(j);
    for (size_t i = 1; i <= a.size(); i++) {
        curr[0] = static_cast<int>(i);
        for (size_t j = 1; j <= b.size(); j++) {
            int cost = a[i - 1] == b[j - 1] ? 0 : 1;
            curr[j] = std::min({curr[j - 1] + 1, prev[j] + 1, prev[j - 1] + cost});
        }
        std::swap(prev, curr);
    }
    return prev[b.size()];
}
std::string trim(const std::string& str);
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
    size_t index;
    size_t line;
    size_t column;
    size_t length = 1;
    Position();
    std::string arrow_string(size_t context = 2) const;
    Position(std::string, std::string, size_t, size_t, size_t);
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
class MethodCallNode;
class PropertyAccessNode;
class SpreadNode;
class NamespaceNode;
class ForeachNode;
class QBoolNode;
class QIfNode;
class QSwitchNode;
class ArrayAssignNode;
class FieldAssignNode;
class MapLiteralNode;
class TryCatchNode;
class RefVarDeclNode;
class NullptrNode;
class TypeValueNode;
class DeferNode;
using AnyNode = std::variant<std::monostate, NumberNode, StringNode, CharNode, BoolNode, QInNode, QBoolNode, RefVarDeclNode, NullptrNode, BinOpNode*,
                             UnaryOpNode*, VarAccessNode*, VarAssignNode*, AssignExprNode*, IfNode*, QIfNode*, StatementsNode*, SwitchNode*,
                             QSwitchNode*, BreakNode*, WhileNode*, ForNode*, ContinueNode*, CallNode*, FuncDefNode*, ReturnNode*, MultiReturnNode*,
                             MultiVarDeclNode*, ArrayDeclNode*, ArrayLiteralNode*, ArrayAccessNode*, MethodCallNode*, PropertyAccessNode*,
                             SpreadNode*, ForeachNode*, ArrayAssignNode*, FieldAssignNode*, MapLiteralNode*, NamespaceNode*, TryCatchNode*,
                             TypeValueNode, DeferNode*>;

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
    LONG_DOUBLE,
    LONG_INT,
    SHORT_INT,
    STRING,
    FLOAT,
    BYTE,
    NIBBLE,
    ADDR_T,
    DOUBLE,
    CHAR,
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
    LSH_EQ,
    RSH_EQ,
    SEMICOLON,
    DEF,
    INCREMENT,
    DECREMENT,
    IDENTIFIER,
    KEYWORD,
    PLUS_EQ,
    MINUS_EQ,
    SIZEOF,
    THROW,
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
    BIT_X_EQ,
    R_ROT,
    L_ROT,
    RROT_EQ,
    LROT_EQ,
    LOGICAL_RSHIFT,
    LRSH_EQ,
    BIT_A_EQ,
    BIT_O_EQ,
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
    IllegalCharError(std::string details, Position pos) : Error("illegal character", details, pos) {}
};

class InvalidSyntaxError : public Error {
  public:
    InvalidSyntaxError(std::string details, Position pos) : Error("invalid syntax: ", details, pos) {}
};

class MissingSemicolonError : public Error {
  public:
    MissingSemicolonError(Position pos) : Error("QC-MS99", "expected semicolon", pos) {}
};
class Note {
  public:
    Position pos;
    std::string message;
    Note(const Position& pos, const std::string& message) : pos(pos), message(message) {}
    std::string as_string() const {
        std::string result;
        result += "note: ";
        result += message;
        result += "\n";
        result += "   --> ";
        result += pos.Filename;
        result += ":";
        result += std::to_string(pos.line + 1);
        result += ":";
        result += std::to_string(pos.column + 1);
        result += "\n";
        result += pos.arrow_string(0);
        return result;
    }
};
class CTError : public Error {
  public:
    CTError(std::string d, Position pos, bool is_warning = false, std::string code = "", std::vector<Note> notes = {}) : Error(code, d, pos) {
        this->is_warning = is_warning;
        this->notes = notes;
    }
    bool is_warning = false;
    std::vector<Note> notes;
    std::string as_string() override {
        std::string result;
        result += (is_warning ? "warning " : "error ");
        result += this->error_name;
        if (!this->details.empty()) { result += ": " + this->details; }
        result += "\n";
        result += " --> ";
        result += this->pos.Filename;
        result += ":";
        result += std::to_string(this->pos.line + 1);
        result += ":";
        result += std::to_string(this->pos.column + 1);
        result += "\n";
        result += this->pos.arrow_string();
        for (const auto& note : notes) {
            result += "\n\033[0m\033[36m  ";
            result += note.as_string();
            result += "\033[0m";
        }
        return result;
    }
};
struct Ler {
    std::vector<Token> Tkns;
    Error* error;
};
struct GenericType {
    std::string name;
    bool isVariadic = false;
    bool isNonType = false;
    std::string nonTypeKind;
    std::string constraint;
    std::string defaultValue;
    bool negated = false;
    std::vector<std::string> subconstraints;
};

class Parameter;

//////////////////////////////////////////////////////////////////////////////////////////////
// VALUE NODES //////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
std::string printAny(const AnyNode& node);
Position get_pos(AnyNode node);
class QInNode {
  public:
    QInNode() {}

    std::string print() const { return "std::qin"; }
};
class CharNode {
  public:
    Token tok;
    CharNode(Token t) : tok(t) {}
    Position getPos() { return this->tok.pos; }
    std::string print() const;
};

class NumberNode {
  public:
    Token tok;
    NumberNode(Token tok);
    Position getPos() { return this->tok.pos; }
    std::string print() const;
};

class StringNode {
  public:
    Token tok;
    StringNode(Token tok);
    Position getPos() { return this->tok.pos; }
    std::string print() const;
};

class BoolNode {
  public:
    Token tok;
    BoolNode(Token tok);
    Position getPos() { return this->tok.pos; }
    std::string print() const;
};
class QBoolNode {
  public:
    Token tok;
    QBoolNode(Token tok);
    Position getPos() { return this->tok.pos; }
    std::string print() const;
};
class NullptrNode {
  public:
    Position pos;
    NullptrNode(Position p) : pos(p) {}
    Position getPos() { return this->pos; }
    std::string print() const { return "nullptr"; }
};
class TypeValueNode {
  public:
    Token tok;
    TypeValueNode(Token tok);
    Position getPos() { return this->tok.pos; }
    std::string print() const;
};
class RefVarDeclNode {
  public:
    Token type_tok;
    Token var_name_tok;
    Token target_tok;
    Position pos;
    Position getPos() { return this->pos; }
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
    bool is_scoped = false;
    Position getPos() { return statements.empty() ? Position("", "", 0, 0, 0) : get_pos(statements[0]); }
    StatementsNode(std::vector<AnyNode> stmts, bool is_block = false, bool is_scoped = false) : statements(stmts), is_block(is_block), is_scoped(is_scoped) {}
    std::string print() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////
// OTHER NODES //////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
class Parameter {
  public:
    Token type;
    Token name;
    std::optional<AnyNode> default_value;
    class FunctionSignature {
      public:
        std::vector<Token> return_types;
        std::vector<Parameter> params;
        std::string print() const {
            std::string res = "fn(";
            for (size_t i = 0; i < params.size(); i++) {
                res += params[i].toString();
                if (i + 1 != params.size()) res += ", ";
            }
            res += ") -> ";
            if (return_types.empty())
                res += "void";
            else
                for (size_t i = 0; i < return_types.size(); i++) {
                    res += return_types[i].value;
                    if (i + 1 != return_types.size()) res += ", ";
                }
            return res;
        }
    };
    std::string toString() const {
        std::string res = isVolatile ? "volatile " : "";
        return res + (signature.has_value() ? signature.value().print() : type.value + " " + name.value) +
               (default_value.has_value() ? (" = " + printAny(default_value.value())) : "");
    }
    std::optional<FunctionSignature> signature;
    bool isVolatile = false;
};
struct ParamTypeInfo {
    Token type;
    struct FunctionSignature {
        std::vector<Token> return_types;
        std::vector<ParamTypeInfo> params;
    };
    Token name;
    std::optional<FunctionSignature> signature;
    bool isVolatile = false;
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
    bool isStatic;
    AnyNode defaultValue;
};

class ClassMethodInfo {
  public:
    Token name_tok;
    std::vector<Parameter> params;
    std::vector<Token> return_types;
    StatementsNode* body;
    bool is_constructor = false;
    std::string access;
    bool is_final = false;
    bool is_volatile = false;
    bool is_static = false;
    std::vector<GenericType> generics;
    std::string print() {
        std::string res = is_volatile ? "volatile " : "";
        if (is_final) res += " final ";
        res += access + " " + name_tok.value + "(";
        for (int i = 0; i < return_types.size(); i++) {
            res += return_types[i].value;
            if (i + 1 < return_types.size()) { res += ", "; }
        }
        for (int i = 0; i < params.size(); i++) {
            res += params[i].toString();
            if (i + 1 < return_types.size()) res += ", ";
        }
        return res;
    }
};
class ConceptInfo {
  public:
    class FunctionSignature {
      public:
        Token name;
        std::vector<Token> return_types;
        std::vector<Parameter> params;
        std::vector<GenericType> generics;
        std::string print() const {
            std::string res = this->name.value;
            for (size_t i = 0; i < params.size(); i++) {
                res += params[i].toString();
                if (i + 1 != params.size()) res += ", ";
            }
            res += ") -> ";
            if (return_types.empty())
                res += "void";
            else
                for (size_t i = 0; i < return_types.size(); i++) {
                    res += return_types[i].value;
                    if (i + 1 != return_types.size()) res += ", ";
                }
            return res;
        }
    };
    struct Block {
        std::vector<FunctionSignature> signatures;
        std::vector<Block> subblocks;
        std::vector<Token> requiredConcepts;
        Token constraint;
    };
    struct DefaultBlock {
        std::vector<std::pair<Token, ClassMethodInfo>> definitions;
    };
    std::vector<std::pair<Block, std::optional<DefaultBlock>>> blocks;
};
enum class UserTypeKind { Struct, Alias, Union, Enum, Class, Concept };

struct UnionMember {
    std::string type;
};
class ProvedConcepts {
  public:
    Token conceptName;
    std::vector<ClassMethodInfo> additionalProof;
};
struct UserTypeInfo {
    Position pos;
    UserTypeKind kind;
    std::vector<ProvedConcepts> provedConcepts;
    std::vector<StructField> fields;
    std::string aliasTarget;
    ConceptInfo conceptInfo;
    std::vector<UnionMember> members;
    std::vector<EnumEntry> enumEntries;
    std::vector<ClassField> classFields;
    std::vector<ClassMethodInfo> classMethods;
    std::vector<std::string> friendClasses;
    std::vector<std::string> friendlyClasses;
    std::string baseClassName = "";
    std::string namespace_path;
    bool is_abstract_class = false;
    bool is_final_class = false;
    std::vector<GenericType> generics;
    std::string baseFile = "";
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

class BinOpNode {
  public:
    bool is_f;
    AnyNode left_node;
    Token op_tok;
    AnyNode right_node;
    Position getPos() { return op_tok.pos; }
    BinOpNode(AnyNode left, Token op, AnyNode right, bool is_f = false) : left_node(left), op_tok(op), right_node(right) { this->is_f = is_f; }
    std::string print() const;
};

class UnaryOpNode {
  public:
    Token op_tok;
    AnyNode node;
    bool is_postfix;
    Position getPos() { return op_tok.pos; }
    UnaryOpNode(Token op, AnyNode n, bool postfix = false) : op_tok(op), node(n), is_postfix(postfix) {}
    std::string print() const;
};

class AssignExprNode {
  public:
    AnyNode target;
    AnyNode value;
    Token op_tok;
    AssignExprNode(AnyNode t, Token op, AnyNode v) : target(t), op_tok(op), value(v) {}
    Position getPos() { return op_tok.pos; }
    std::string print() { return "(" + printAny(target) + " = " + printAny(value) + ")"; }
};

class VarAssignNode {
  public:
    bool is_const;
    Token type_tok;
    Token var_name_tok;
    AnyNode value_node;
    Position getPos() { return var_name_tok.pos; }
    VarAssignNode(bool is_const, Token type, Token name, AnyNode value, bool is_foreign = false)
        : is_const(is_const), is_foreign(is_foreign), type_tok(type), var_name_tok(name), value_node(value) {}
    bool is_foreign;
    std::string print() const;
};

class VarAccessNode {
  public:
    Token var_name_tok;
    Position getPos() { return var_name_tok.pos; }
    VarAccessNode(Token name) : var_name_tok(name) {}

    std::string print() const;
};
class DeferNode {
  public:
    StatementsNode* block;
    Position getPos() { return get_pos(block); }
    DeferNode(StatementsNode* block)
        : block(block) {}
    std::string print() const;
};

class IfNode {
  public:
    std::optional<AnyNode> init;
    AnyNode condition;
    StatementsNode* then_branch;
    std::vector<std::pair<AnyNode, StatementsNode*>> elif_branches;
    StatementsNode* else_branch;
    Position getPos() { return get_pos(condition); }
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
    Position getPos() { return get_pos(condition); }
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
    Position getPos() { return get_pos(value); }
    std::string print() { return printAny(value); }
};
class QSwitchNode {
  public:
    AnyNode value;
    StatementsNode* case_t;
    StatementsNode* case_f;
    StatementsNode* case_n;
    StatementsNode* case_b;
    Position getPos() { return get_pos(value); }
    QSwitchNode(AnyNode val, StatementsNode* t, StatementsNode* f, StatementsNode* n, StatementsNode* b)
        : value(val), case_t(t), case_f(f), case_n(n), case_b(b) {}

    std::string print() const { return "qswitch (...)"; }
};

class BreakNode {
  public:
    Token tok;
    BreakNode(Token t) : tok(t) {}
    std::string print() { return "(break)"; }
    Position getPos() { return tok.pos; }
};

class WhileNode {
  public:
    AnyNode condition;
    StatementsNode* body;

    Position getPos() { return get_pos(condition); }
    WhileNode(AnyNode cond, StatementsNode* b) : condition(cond), body(b) {}

    std::string print() { return "(while " + printAny(condition) + " " + body->print() + ")"; }
};
class TryCatchNode {
  public:
    StatementsNode* try_body;
    struct CatchBody {
        std::string var_name;
        std::string var_type;
        StatementsNode* body;
    };
    std::vector<CatchBody> catch_bodys;
    Token tok;
    Position pos;
    Position getPos() { return tok.pos; }
    TryCatchNode(StatementsNode* try_b, std::vector<CatchBody> catch_b, Token t, Position p)
        : try_body(try_b), catch_bodys(catch_b), tok(t), pos(p) {}
    std::string print() { return "try {\n\t" + try_body->print() + "\n} catch (...) {    ...\n}"; }
};
class ForNode {
  public:
    std::optional<AnyNode> init;
    AnyNode condition;
    std::optional<AnyNode> update;
    StatementsNode* body;

    Position getPos() { return get_pos(condition); }
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
    Position getPos() { return tok.pos; }
    std::string print() { return "(continue)"; }
};

class FuncDefNode {
  public:
    std::vector<Token> return_types;
    std::optional<Token> name_tok;
    std::list<Parameter> params;
    StatementsNode* body;
    std::vector<GenericType> generics;
    std::string namespace_path;
    Position pos;
    bool is_extern = false;
    bool is_foreign = false;
    bool is_volatile = false;
    bool is_header = true;
    FuncDefNode(std::vector<Token> ret_types, std::optional<Token> name, std::list<Parameter> parameters, StatementsNode* func_body,
                std::string ns = "", bool is_ex = false, bool is_f = false, std::vector<GenericType> generics = {}, bool is_volatile = false,
                bool is_header = false)
        : return_types(ret_types), name_tok(name), params(parameters), body(func_body), namespace_path(ns) {
        this->is_extern = is_ex;
        this->is_foreign = is_f;
        this->generics = generics;
        this->is_volatile = is_volatile;
        this->is_header = is_header;
    }
    Position getPos() const {
        if (name_tok.has_value()) return name_tok.value().pos;

        if (return_types.empty()) return get_pos(body);

        return return_types[0].pos;
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
    Position getPos() { return get_pos(node_to_call); }
    std::string print() { return printAny(node_to_call) + "(args)"; }
};
class MultiReturnNode {
  public:
    std::vector<AnyNode> values;
    Position pos;
    Position getPos() { return pos; }
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
    Position getPos() { return var_names[0].pos; };
    MultiVarDeclNode(bool is_const, std::vector<Token> type_toks, std::vector<Token> var_names, AnyNode value)
        : is_const(is_const), type_toks(type_toks), var_names(var_names), value(value) {}
};
class ArrayDeclNode {
  public:
    bool is_const;
    Token type_tok;
    Token var_name_tok;
    AnyNode value;
    Position getPos() { return var_name_tok.pos; }
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

class ArrayLiteralNode {
  public:
    std::vector<AnyNode> elements;
    std::string type;
    Position pos;
    AnyNode length;
    Position getPos() { return pos; }
    ArrayLiteralNode(std::vector<AnyNode> elems, Position p, std::string struct_ty = "") : elements(elems), pos(p), type(struct_ty) {}

    std::string print() {
        std::string result = "[";
        for (size_t i = 0; i < elements.size(); i++) {
            result += printAny(elements[i]);
            if (i < elements.size() - 1) result += ", ";
        }
        if (elements.empty()) result += this->type;
        return result + "]";
    }
};
class MapLiteralNode {
  public:
    std::vector<std::pair<AnyNode, AnyNode>> pairs;
    Position pos;
    std::string struct_type;
    Position getPos() { return pos; }
    MapLiteralNode(std::vector<std::pair<AnyNode, AnyNode>> p, Position pos, std::string struct_ty = "")
        : pairs(p), pos(pos), struct_type(struct_ty) {}

    std::string print() const { return this->struct_type + "{}"; }
};
class ArrayAccessNode {
  public:
    AnyNode base;
    std::vector<AnyNode> indices;
    Position getPos() { return get_pos(base); }
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
    Position getPos() { return method_name.pos; }
    MethodCallNode(AnyNode base_node, Token method, std::vector<AnyNode> arguments) : base(base_node), method_name(method), args(arguments) {}

    std::string print() { return printAny(base) + "." + method_name.value + "(...)"; }
};
class ReturnNode {
  public:
    AnyNode value;
    Position pos;
    Position getPos() { return pos; }
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
    Position getPos() { return property_name.pos; }
    std::string print() { return printAny(*base) + "." + property_name.value; }
};
class SpreadNode {
  public:
    AnyNode expr;
    Position getPos() { return get_pos(expr); }
    SpreadNode(AnyNode expression) : expr(expression) {}

    std::string print() { return "@" + printAny(expr); }
};
class ForeachNode {
  public:
    Token elem_type;
    Token elem_name;
    AnyNode collection;
    AnyNode body;
    Position getPos() { return elem_name.pos; }
    ForeachNode(Token type, Token name, AnyNode coll, AnyNode body_stmt) : elem_type(type), elem_name(name), collection(coll), body(body_stmt) {}

    std::string print() { return "foreach (" + elem_type.value + " " + elem_name.value + " in ...)"; }
};
class FieldAssignNode {
  public:
    AnyNode base;
    Token field_name;
    AnyNode value;
    Position getPos() { return field_name.pos; }
    FieldAssignNode(AnyNode b, Token f, AnyNode v) : base(b), field_name(f), value(v) {}
    std::string print() const { return printAny(base) + "." + field_name.value + " = " + printAny(value); }
};
class ArrayAssignNode {
  public:
    AnyNode array_access;
    AnyNode value;
    Position getPos() { return get_pos(array_access); }
    ArrayAssignNode(AnyNode access, AnyNode val) : array_access(access), value(val) {}

    std::string print() const { return "array_assign"; }
};
class NamespaceNode {
  public:
    std::string name;
    Position pos;
    std::vector<AnyNode> body;
    Position getPos() { return pos; }
    NamespaceNode(std::string name, std::vector<AnyNode> body, Position pos) : name(name), body(body) { this->pos = pos; }
    std::string print() { return "namespace " + name; }
};
//////////////////////////////////////////////////////////////////////////////////////////////
// PARSE RESULT /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
class ParseResult;
using Prs = std::variant<std::monostate, ParseResult, NumberNode, StringNode, CharNode, BoolNode, BinOpNode*, Error*, UnaryOpNode*, VarAccessNode*,
                         VarAssignNode*, AssignExprNode*, StatementsNode*, IfNode*, BreakNode*, SwitchNode*, WhileNode*, ForNode*, ContinueNode*,
                         CallNode*, FuncDefNode*, ReturnNode*, MultiReturnNode*, MultiVarDeclNode*, ArrayDeclNode*, ArrayLiteralNode*,
                         ArrayAccessNode*, MethodCallNode*, PropertyAccessNode*, SpreadNode*, ForeachNode*, QBoolNode, QInNode, QIfNode*,
                         QSwitchNode*, ArrayAssignNode*, FieldAssignNode*, MapLiteralNode*, NamespaceNode*, TryCatchNode*, RefVarDeclNode,
                         NullptrNode, TypeValueNode, DeferNode*>;

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
    std::vector<GenericType> current_generics;
    std::string base_type_name(std::string full_type) {
        size_t open_bracket = full_type.find('<');
        if (open_bracket == std::string::npos) { return full_type; }
        std::string base = full_type.substr(0, open_bracket);
        size_t last_valid_char = base.find_last_not_of(" \t\r\n");
        if (last_valid_char != std::string::npos) { return base.substr(0, last_valid_char + 1); }
        return base;
    }

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
    bool is_known_type(std::string name) {
        std::string base = base_type_name(name);
        if (base.ends_with("&")) { base.pop_back(); }
        while (base.ends_with("*")) base.pop_back();
        while (base.ends_with("[]")) {
            base.pop_back();
            base.pop_back();
        }
        for (GenericType ty : current_generics) {
            if (ty.name == base) { return true; }
        }
        if (user_types.count(base_type_name(base))) return true;
        std::string ns;
        for (int i = (int)namespaceStack.size() - 1; i >= 0; --i) {
            ns = ns.empty() ? namespaceStack[i] : namespaceStack[i] + "::" + ns;
            std::string candidate = ns + "::" + base;
            if (user_types.count(base_type_name(candidate))) return true;
        }
        return false;
    }
    std::string get_known_type(std::string name) {
        std::string base = base_type_name(name);
        if (base.ends_with("&")) { base.pop_back(); }
        while (base.ends_with("*")) base.pop_back();
        while (base.ends_with("[]")) {
            name.pop_back();
            base.pop_back();
        }
        if (user_types.count(base)) return base;
        for (GenericType ty : current_generics) {
            if (ty.name == base) { return base; }
        }
        std::string ns;
        for (int i = (int)namespaceStack.size() - 1; i >= 0; --i) {
            ns = ns.empty() ? namespaceStack[i] : namespaceStack[i] + "::" + ns;
            std::string candidate = ns + "::" + base;
            if (user_types.count(candidate)) return candidate;
        }
        return base;
    }
    Token peek(int offset = 1) {
        size_t peek_idx = this->index + offset;
        if (peek_idx < this->tokens.size()) { return this->tokens[peek_idx]; }
        return this->current_tok;
    }
    std::optional<std::string> try_parse_qualified_name() {
        if (current_tok.type != TokenType::IDENTIFIER) return std::nullopt;
        return parseTypeString();
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
    UserTypeInfo* find_type(std::string name) {
        if (is_known_type(base_type_name(name))) {
            for (GenericType ty : current_generics) {
                if (ty.name == base_type_name(get_known_type(name))) { return nullptr; }
            }
            return &user_types[base_type_name(get_known_type(name))];
        }
        name = base_type_name(name);
        if (name.find("::") != std::string::npos) {
            if (user_types.count(base_type_name(name))) { return &user_types[base_type_name(name)]; }
            return nullptr;
        }
        if (!currentNamespace.empty()) {
            std::string key = currentNamespace + "::" + name;
            if (user_types.count(base_type_name(key))) { return &user_types[base_type_name(key)]; }
        }
        for (int i = namespaceStack.size() - 1; i >= 0; --i) {
            std::string ns;
            for (int j = 0; j <= i; ++j) {
                if (j > 0) ns += "::";
                ns += namespaceStack[j];
            }
            std::string key = ns + "::" + name;
            if (user_types.count(base_type_name(key))) { return &user_types[base_type_name(key)]; }
        }
        if (user_types.count(base_type_name(name))) { return &user_types[base_type_name(name)]; }

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
    Prs defer_expr();
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
    Prs func_def_multi(std::vector<Token> return_type, std::optional<Token> func_name, std::vector<GenericType> generics, bool keep = false,
                       bool is_volatile = false);
    Parameter parse_parameter(bool type_only);
    bool in_extern = false;
    bool in_foreign = false;
    std::string parseTypeString() {
        std::string type = "";
        if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "volatile") {
            type += "volatile ";
            this->advance();
        }
        if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "fn") {
            type += "fn";
            this->advance();
            if (this->current_tok.type != TokenType::LPAREN) {
                throw InvalidSyntaxError("`fn` is not a standalone type and must also have its () and return type", this->current_tok.pos);
            }
            this->advance();
            type += "(";
            type += parseTypeString();
            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                type += ", " + parseTypeString();
            }
            if (this->current_tok.type != TokenType::RPAREN) {
                throw InvalidSyntaxError("`fn` is not a standalone type and must also have its () and return type", this->current_tok.pos);
            }
            this->advance();
            type += ")";
            if (this->current_tok.type != TokenType::ARROW) {
                throw InvalidSyntaxError("`fn` must have a `->` before the return type.", this->current_tok.pos);
            }
            type += " -> ";
            this->advance();
            type += parseTypeString();
            return type;
        }
        if (this->current_tok.type == TokenType::KEYWORD && (this->current_tok.value == "short" || this->current_tok.value == "long")) {
            type += this->current_tok.value + " ";
            this->advance();
        }
        if (this->current_tok.type == TokenType::KEYWORD || this->current_tok.type == TokenType::IDENTIFIER) {
            type += this->current_tok.value;
            this->advance();
        } else {
            return "";
        }
        while (this->current_tok.type == TokenType::SCOPE) {
            this->advance();
            type += "::" + this->current_tok.value;
            this->advance();
        }
        if (this->current_tok.type == TokenType::LESS) {
            this->advance();
            type += "<";
            int depth = 1;
            while (depth > 0) {
                if (this->current_tok.type == TokenType::EOFT) break;
                if (this->current_tok.type == TokenType::LESS) {
                    depth++;
                } else if (this->current_tok.type == TokenType::MORE) {
                    depth--;
                    if (depth == 0) {
                        this->advance();
                        break;
                    }
                }
                type += this->current_tok.value;
                this->advance();
            }
            type += ">";
        }
        while (this->current_tok.type == TokenType::LBRACKET) {
            this->advance();
            if (this->current_tok.type == TokenType::INT) {
                type += "[" + this->current_tok.value + "]";
                this->advance();
            } else {
                type += "[]";
            }
            this->advance();
        }
        while (this->current_tok.type == TokenType::MUL) {
            type += "*";
            this->advance();
        }
        if (this->current_tok.type == TokenType::AMPERSAND) {
            type += "&";
            this->advance();
        }

        return type;
    }
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
    bool use_runtime = true;
    bool dump_tokens = false;
    std::string target = "";
    std::unordered_map<std::string, std::string> aliases = {};
    std::unordered_map<std::string, std::string> dir_aliases = {};
    std::vector<std::string> library_search_paths = {"."};
    std::vector<std::string> libraries = {};
    std::vector<std::string> link_with = {};
};
//////////////////////////////////////////////////////////////////////////////////////////////
// COMPILER /////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_LLVM
struct AsmOp {
    bool isRW;
    bool isOutput;
    int index;
    char kind;
};
struct FunctionSignature {
    llvm::FunctionType* type;
    std::vector<llvm::Value*> defaultValues;
};
struct ExceptionHandlerInfo {
    llvm::Function* function;
    llvm::BasicBlock* landingPad;
    std::string catchType;
};
class LLVMCompiler {
  public:
    RunConfig config;
    llvm::LLVMContext& context;
    llvm::Module* module;
    llvm::IRBuilder<>* builder;
    bool startsWithQIn(const AnyNode& node) {
        if (auto bin = std::get_if<BinOpNode*>(&node)) { return startsWithQIn((*bin)->left_node); }
        if (auto qin = std::get_if<QInNode>(&node)) { return true; }
        return false;
    }
    std::string baseTypeName(const std::string& mangled) {
        size_t angle = mangled.find('<');
        if (angle == std::string::npos) return mangled;
        int depth = 0;
        size_t end = angle;
        for (size_t i = angle; i < mangled.size(); i++) {
            if (mangled[i] == '<')
                depth++;
            else if (mangled[i] == '>') {
                depth--;
                if (depth == 0) {
                    end = i + 1;
                    break;
                }
            }
        }
        return mangled.substr(0, angle) + mangled.substr(end);
    }
    llvm::Constant* getStringConstant(const std::string& str) {
        llvm::Constant* stringConstant = llvm::ConstantDataArray::getString(context, str, true);
        llvm::GlobalVariable* globalString = new llvm::GlobalVariable(*module, stringConstant->getType(), true, llvm::GlobalValue::PrivateLinkage,
                                                                      stringConstant, ".qc.str");
        llvm::Constant* zero = llvm::ConstantInt::get(builder->getInt32Ty(), 0);
        llvm::SmallVector<llvm::Constant*, 2> indices = {zero, zero};
        return llvm::ConstantExpr::getInBoundsGetElementPtr(stringConstant->getType(), globalString, indices);
    }
    void generateStructReprFunctions();
    llvm::Value* callStringConcat(llvm::Value* a, llvm::Value* b);
    void createUserTypes();
    llvm::Value* convertToString(llvm::Value* val, AnyNode& expr, Position pos);
    LLVMCompiler(std::unordered_map<std::string, UserTypeInfo>& userTys, llvm::Module* mod, llvm::LLVMContext& ctx, bool is_main = false);
    std::vector<CTError> compile(
        StatementsNode* root, std::unordered_map<std::string, FunctionSignature> visibleFunctionSignatures,
        std::unordered_map<std::string, FuncDefNode*> visibleFunctionDefs, std::unordered_map<std::string, std::pair<int, int>> visibleJaggedArrays,
        std::unordered_map<std::string, std::string> visibleArrayTypeStrings, std::unordered_map<std::string, int> visibleArrayLengths,
        std::unordered_map<std::string, std::string> visibleVarTypes, std::unordered_map<std::string, llvm::AllocaInst*> visibleRuntimeArraySizes,
        std::unordered_map<std::string, llvm::FunctionType*> visibleLambdaTypes, std::map<std::string, llvm::Function*> visibleSpecializedFunctions,
        std::unordered_map<std::string, llvm::GlobalVariable*> visibleGlobals);
    bool is_main;
    void cg_warn(const Position& pos, const std::string& msg, std::string code = "");
    void cg_error(const Position& pos, const std::string& msg, std::string code = "");
    void cg_note(const Position& pos, const std::string& msg) {
        if (errors.empty()) return;
        errors.back().notes.emplace_back(pos, msg);
    }
    std::vector<CTError> errors;
    llvm::BasicBlock* currentBreakBB = nullptr;
    llvm::BasicBlock* currentContinueBB = nullptr;
    std::unordered_map<std::string, std::vector<size_t>> genericMethodIndices;

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
    std::unordered_map<std::string, UserTypeInfo>& userTypes;
    struct EnumMemberValue {
        int tag;
        std::string type;
        std::string value;
    };
    std::string getMethodReturnTypeName(const std::string& typeName, const std::string& methodName) {
        auto it = userTypes.find(baseTypeName(typeName));
        if (it == userTypes.end()) return "";

        for (auto& method : it->second.classMethods) {
            if (method.name_tok.value == methodName) {
                if (!method.return_types.empty()) { return method.return_types[0].value; }
            }
        }
        return "";
    }
    llvm::Value* createEnumData(const std::string& type, const std::string& value) {
        if (type == "string") {
            std::string str = value.substr(1, value.length() - 2);
            return builder->CreateGlobalString(str);
        } else if (type == "int") {
            int i = std::stoi(value);
            llvm::AllocaInst* temp = createEntryAlloca("enum_int", builder->getInt32Ty());
            builder->CreateStore(builder->getInt32(i), temp);
            return builder->CreateBitCast(temp, llvm::PointerType::get(context, 0));
        } else if (type == "long int") {
            long long i = std::stoll(value);
            llvm::AllocaInst* temp = createEntryAlloca("enum_long_int", builder->getIntNTy(getPtrSize()));
            builder->CreateStore(llvm::ConstantInt::get(builder->getIntNTy(getPtrSize()), i, true), temp);
            return builder->CreateBitCast(temp, llvm::PointerType::get(context, 0));
        } else if (type == "short int") {
            long long i = std::stoll(value);
            llvm::AllocaInst* temp = createEntryAlloca("enum_short_int", builder->getInt16Ty());
            builder->CreateStore(builder->getInt16(i), temp);
            return builder->CreateBitCast(temp, llvm::PointerType::get(context, 0));
        } else if (type == "addr_t") {
            long long i = std::stoll(value);
            llvm::AllocaInst* temp = createEntryAlloca("enum_addr_t", builder->getIntNTy(getPtrSize()));
            builder->CreateStore(llvm::ConstantInt::get(builder->getIntNTy(getPtrSize()), i, false), temp);
            return builder->CreateBitCast(temp, llvm::PointerType::get(context, 0));
        } else if (type == "byte") {
            long long i = std::stoll(value);
            llvm::AllocaInst* temp = createEntryAlloca("enum_byte", builder->getInt8Ty());
            builder->CreateStore(builder->getInt8(i), temp);
            return builder->CreateBitCast(temp, llvm::PointerType::get(context, 0));
        } else if (type == "nibble") {
            long long i = std::stoll(value);
            llvm::AllocaInst* temp = createEntryAlloca("enum_nibble", builder->getIntNTy(4));
            builder->CreateStore(llvm::ConstantInt::get(builder->getIntNTy(4), i, false), temp);
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
    std::unordered_map<std::string, llvm::GlobalVariable*> vtables;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> vtableSlotIndex;
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<llvm::Function*>>> classMethods;
    std::unordered_map<std::string, bool> genericClasses;
    std::unordered_map<std::string, bool> genericStructs;
    std::unordered_map<std::string, bool> genericAliases;
    std::unordered_map<std::string, bool> genericUnions;
    std::unordered_map<std::string, bool> genericConcepts;
    std::unordered_map<std::string, ConceptInfo> concepts;
    std::unordered_map<std::string, UserTypeInfo> substitutedUnions;
    std::unordered_map<std::string, llvm::Type*> currentGenericTypes;
    std::unordered_map<std::string, std::string> currentGenericTypeStrings;
    std::unordered_map<std::string, GenericType> currentNonTypeGenericValues;
    std::vector<ExceptionHandlerInfo> handlers;
    llvm::Value* currentThis = nullptr;
    std::string currentClassName = "";
    struct EHHandler {
        TryCatchNode::CatchBody body;
        llvm::BasicBlock* block;
    };

    struct EHScope {
        llvm::BasicBlock* landingPad;
        llvm::BasicBlock* continuation;
        std::vector<EHHandler> handlers;
        size_t deferDepth;
    };
    std::vector<EHScope> ehScopes;

    std::vector<std::vector<StatementsNode*>> defersStack = {{}};
#define defers defersStack.back()
    bool insideTry() { return !ehScopes.empty(); }
    llvm::BasicBlock* currentLandingPad() { return ehScopes.back().landingPad; }
    llvm::Value* copySpreadToArray(llvm::Value* collVal, AnyNode& collExpr, llvm::Value* destArray, llvm::Value* startIndex, llvm::Type* elemTy,
                                   int elemTypeCode);
    std::string substituteGenerics(const std::string& typeStr) {
        size_t anglePos = typeStr.find('<');
        size_t suffix_start = anglePos;
        if (anglePos == std::string::npos) {
            size_t modifierPos = typeStr.find_first_of("*&[");
            std::string base = modifierPos == std::string::npos ? typeStr : typeStr.substr(0, modifierPos);
            std::string suffix = modifierPos == std::string::npos ? "" : typeStr.substr(modifierPos);
            base.erase(0, base.find_first_not_of(" "));
            base.erase(base.find_last_not_of(" ") + 1);
            auto typeIt = currentGenericTypeStrings.find(base);
            if (typeIt != currentGenericTypeStrings.end()) { base = typeIt->second; }
            auto nonTypeIt = currentNonTypeGenericValues.find(base);
            if (nonTypeIt != currentNonTypeGenericValues.end()) { base = nonTypeIt->second.name; }
            for (size_t i = 0; i < suffix.size();) {
                if (suffix[i] == '[') {
                    size_t end = suffix.find(']', i);
                    if (end == std::string::npos) { break; }
                    std::string size = suffix.substr(i + 1, end - i - 1);
                    std::string newSize = substituteGenerics(size);
                    suffix.replace(i + 1, end - i - 1, newSize);
                    i += newSize.size() + 2;
                } else {
                    i++;
                }
            }
            return base + suffix;
        }
        std::string baseName = typeStr.substr(0, anglePos);
        std::string inner = typeStr.substr(anglePos + 1, typeStr.rfind('>') - anglePos - 1);
        std::string suffix = typeStr.substr(typeStr.rfind('>') + 1); // catches trailing * & etc
        std::vector<std::string> args;
        int depth = 0;
        std::string current;
        for (char c : inner) {
            if (c == '<')
                depth++;
            else if (c == '>')
                depth--;
            else if (c == ',' && depth == 0) {
                args.push_back(current);
                current.clear();
                continue;
            }
            current += c;
        }
        if (!current.empty()) args.push_back(current);
        for (auto& arg : args) arg = substituteGenerics(arg);
        std::string result = baseName + "<";
        for (size_t i = 0; i < args.size(); i++) {
            if (i != 0) result += ",";
            result += args[i];
        }
        return result + ">" + suffix;
    }
    unsigned pointerSizeBits;
    llvm::Value* createRuntimeSizedArray(std::vector<AnyNode>& elements, llvm::Value* totalSize);
    void expandSpreadIntoVector(llvm::Value* collVal, AnyNode& collExpr, std::vector<llvm::Value*>& elements);
    llvm::Value* emitSpreadFunctionCall(llvm::Value* calleeVal, llvm::FunctionType* fnTy, CallNode& call);
    bool fulfillsGenericConstraints(std::vector<GenericType> generics, std::vector<std::string> genericParams, Position pos = Position());
    ConceptInfo generateGenericConcept(std::string conceptName, UserTypeInfo conceptInfo, std::vector<std::string> genericParams);
    llvm::StructType* generateGenericClass(std::string className, UserTypeInfo classInfo, std::vector<std::string> genericParams);
    llvm::StructType* generateGenericStruct(std::string structName, UserTypeInfo structInfo, std::vector<std::string> genericParams);
    UserTypeInfo generateGenericUnion(std::string unionName, UserTypeInfo unionInfo, std::vector<std::string> genericParams);
    std::string generateGenericAlias(std::string aliasName, UserTypeInfo aliasInfo, std::vector<std::string> genericParams);
    std::unordered_map<std::string, llvm::GlobalVariable*> globals;
    std::unordered_map<std::string, FunctionSignature> functionSignatures;
    std::unordered_map<std::string, FuncDefNode*> functionDefs;
    std::vector<std::unordered_map<std::string, std::pair<int, int>>> jaggedArraysStack;
    std::vector<std::unordered_map<std::string, std::string>> arrayTypeStringsStack;
    std::vector<std::unordered_map<std::string, int>> arrayLengthsStack;
    std::vector<std::unordered_map<std::string, std::string>> varTypesStack;
    std::vector<std::unordered_map<std::string, llvm::AllocaInst*>> localsStack;
    std::vector<std::unordered_map<std::string, bool>> volatileVarsStack;
    std::unordered_map<std::string, llvm::AllocaInst*> runtimeArraySizes;
    std::unordered_map<std::string, llvm::FunctionType*> lambdaTypes;
    int findUnionVariantTag(const std::string& unionName, AnyNode& valueNode, llvm::Value* val);
    llvm::Value* storeAndGetPointer(llvm::Value* val);
    std::map<std::string, llvm::Function*> specializedFunctions;
    template <typename MapType> bool foundInStack(const std::vector<MapType>& stack, const std::string& key) {
        if (stack.empty()) return false;
        for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
            if (it->find(key) != it->end()) { return true; }
        }
        return false;
    }
    unsigned getPtrSize() { return pointerSizeBits; }
#define hasVarType(name) foundInStack(varTypesStack, name)
#define hasLocal(name) foundInStack(localsStack, name)
#define hasArrayType(name) foundInStack(arrayTypeStringsStack, name)
#define hasArrayLength(name) foundInStack(arrayLengthsStack, name)
#define hasJaggedArray(name) foundInStack(jaggedArraysStack, name)
#define hasVolatileVar(name) foundInStack(volatileVarsStack, name)
#define volatileVars (volatileVarsStack.back())
#define arrayLengths (arrayLengthsStack.back())
#define locals (localsStack.back())
#define jaggedArrays (jaggedArraysStack.back())
#define varTypes (varTypesStack.back())
#define arrayTypeStrings (arrayTypeStringsStack.back())
#define findLocal(name) findInStack(localsStack, name)
#define findVolatileVar(name) findInStack(volatileVarsStack, name)
#define findArrayLength(name) findInStack(arrayLengthsStack, name)
#define findVarType(name) findInStack(varTypesStack, name)
#define findJaggedArray(name) findInStack(jaggedArraysStack, name)
#define findArrayType(name) findInStack(arrayTypeStringsStack, name)
    void enterScope() {
        defersStack.push_back({});
        localsStack.push_back({});
        jaggedArraysStack.push_back({});
        arrayTypeStringsStack.push_back({});
        arrayLengthsStack.push_back({});
        varTypesStack.push_back({});
        volatileVarsStack.push_back({});
    }

    void exitScope() {
        auto *currentBlock = builder->GetInsertBlock();
        if (currentBlock && !currentBlock->getTerminator()) {
            emitDefersDownTo(defersStack.size());
        }
        defersStack.pop_back();
        localsStack.pop_back();
        volatileVarsStack.pop_back();
        jaggedArraysStack.pop_back();
        arrayTypeStringsStack.pop_back();
        arrayLengthsStack.pop_back();
        varTypesStack.pop_back();
    }
    size_t targetDeferDepth = 0;
    std::vector<size_t> loopStack;
    void emitDefersDownTo(size_t targetDepth) {
        if (defersStack.empty()) return;
        int first = std::max(0, (int)targetDepth - 1);
        for (int i = (int)defersStack.size() - 1; i >= first; --i) {
            auto defersToRun = defersStack[i]; 
            for (auto it = defersToRun.rbegin(); it != defersToRun.rend(); ++it) {
                enterScope();
                emitStmt(*it);
                exitScope();
            }
        }
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
    std::string getExpressionType(AnyNode& node, bool strip = true) {
        if (auto mapLit = std::get_if<MapLiteralNode*>(&node)) {
            if (!(*mapLit)->struct_type.empty()) { return (*mapLit)->struct_type; }
        } else if (auto arrLit = std::get_if<ArrayLiteralNode*>(&node)) {
            if (!(*arrLit)->type.empty()) { return (*arrLit)->type; }
            if (!(*arrLit)->elements.empty()) {
                std::string elemType = getExpressionType((*arrLit)->elements[0]);
                return elemType + "[]";
            }
            return "int[]";
        } else if (auto unaryOp = std::get_if<UnaryOpNode*>(&node)) {
            std::string type = getExpressionType((*unaryOp)->node, strip);
            if ((*unaryOp)->op_tok.type == TokenType::MUL) {
                if (type.ends_with("*") && strip) { type.pop_back(); }
            }
            if ((*unaryOp)->op_tok.type == TokenType::AMPERSAND) { return type + "*"; }
            if ((*unaryOp)->op_tok.type == TokenType::SIZEOF) { return "addr_t"; }
            return type;
        } else if (auto binOp = std::get_if<BinOpNode*>(&node)) {
            std::string leftType = getExpressionType((*binOp)->left_node);
            std::string rightType = getExpressionType((*binOp)->right_node);
            if (leftType == "char" && rightType == "char") return "int";
            if (leftType == rightType) return leftType;
            if (leftType == "double" || rightType == "double") return "double";
            if (leftType == "float" || rightType == "float") return "float";
            return leftType;
        } else if (auto strNode = std::get_if<StringNode>(&node)) {
            return "string";
        } else if (auto numNode = std::get_if<NumberNode>(&node)) {
            switch (numNode->tok.type) {
            case TokenType::INT: return "int";
            case TokenType::FLOAT: return "float";
            case TokenType::DOUBLE: return "double";
            case TokenType::LONG_DOUBLE: return "long double";
            case TokenType::LONG_INT: return "long int";
            case TokenType::SHORT_INT: return "short int";
            case TokenType::ADDR_T: return "addr_t";
            case TokenType::BYTE: return "byte";
            case TokenType::NIBBLE: return "nibble";
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
            if (!this->resolveVarType(varName).empty()) {
                std::string t = this->resolveVarType(varName);
                if (t.ends_with("&") && strip) t.pop_back();
                return substituteGenerics(t);
            }
            if (hasArrayType(varName)) { return substituteGenerics(findArrayType(varName)->second) + "[]"; }
        } else if (auto arrAcc = std::get_if<ArrayAccessNode*>(&node)) {
            std::string baseType = getExpressionType((*arrAcc)->base);
            if (baseType.ends_with(']')) {
                const size_t open = baseType.rfind('[');
                if (open != std::string::npos) { return baseType.substr(0, open); }
            }
            if (baseType.ends_with("*")) {
                return baseType.substr(0, baseType.size() - 1);
            } else if (baseType == "string") {
                return "char";
            } else {
                if (auto varAcc = std::get_if<VarAccessNode*>(&(*arrAcc)->base)) {
                    std::string name = (*varAcc)->var_name_tok.value;
                    if (auto arrayType = resolveArrayType(name)) { return *arrayType; }
                }
            }
            std::string className = baseTypeName(baseType);
            while (!className.empty() && userTypes.contains(className)) {
                auto& info = userTypes[className];
                auto originalGenericMap = currentGenericTypeStrings;
                std::string ret;
                for (auto& m : info.classMethods) {
                    if (m.name_tok.value == "operator[]" && !m.return_types.empty()) {
                        ret = m.return_types[0].value;
                        std::vector<std::string> actualArgs = genericParamsFromName(baseType);
                        auto& formalParams = userTypes[className].generics;
                        for (size_t i = 0; i < formalParams.size() && i < actualArgs.size(); ++i) {
                            currentGenericTypeStrings[formalParams[i].name] = actualArgs[i];
                        }
                        if (ret.ends_with("&") && strip) ret.pop_back();
                        ret = substituteGenerics(ret);
                        currentGenericTypeStrings = std::move(originalGenericMap);
                        return ret;
                    }
                }
                std::string parentTypeStr = info.baseClassName;
                if (parentTypeStr.empty()) break;
                std::vector<std::string> parentActualArgs = genericParamsFromName(parentTypeStr);
                std::string nextClassName = baseTypeName(parentTypeStr);
                std::unordered_map<std::string, std::string> nextGenericMap;
                if (userTypes.contains(nextClassName)) {
                    auto& parentFormalParams = userTypes[nextClassName].generics;
                    for (size_t i = 0; i < parentFormalParams.size() && i < parentActualArgs.size(); ++i) {
                        nextGenericMap[parentFormalParams[i].name] = substituteGenerics(parentActualArgs[i]);
                    }
                }
                className = nextClassName;
                currentGenericTypeStrings = std::move(nextGenericMap);
            }
            return "unknown";
        } else if (auto nullp = std::get_if<NullptrNode>(&node)) {
            return "@nullptr";
        } else if (auto propAcc = std::get_if<PropertyAccessNode*>(&node)) {
            std::string currentType = getExpressionType(*((*propAcc)->base));
            if (currentType.ends_with("*") || currentType.ends_with("&")) { currentType.pop_back(); }
            std::string fieldName = (*propAcc)->property_name.value;
            while (!currentType.empty() && userTypes.contains(baseTypeName(currentType))) {
                auto& info = userTypes[baseTypeName(currentType)];
                for (const auto& f : info.fields) {
                    if (f.name == fieldName) { return substituteGenerics(f.type); }
                }
                for (const auto& f : info.classFields) {
                    if (f.name == fieldName) return substituteGenerics(f.type);
                }
                currentType = info.baseClassName;
            }
            return "unknown";
        } else if (auto callNode = std::get_if<CallNode*>(&node)) {
            if (auto varAcc = std::get_if<VarAccessNode*>(&(*callNode)->node_to_call)) {
                std::string funcName = (*varAcc)->var_name_tok.value;
                if (funcName == "`is_empty" || funcName == "`to_bool") return "bool";
                if (funcName == "`inline" || funcName == "`qout") return "void";
                if (funcName == "`time") return "addr_t";
                if (funcName == "`seed") return "void";
                if (funcName == "`random") {
                    if ((*callNode)->arg_nodes.size() > 1) { return "double"; }
                    return "int";
                }
                if (funcName == "`len") return "addr_t";
                if (funcName == "`to_lower" || funcName == "`to_upper" || funcName == "`substring" || funcName == "`trim" || funcName == "`replace" ||
                    funcName == "`read" || funcName == "`to_string")
                    return "string";
                if (funcName == "`contains" || funcName == "`startswith" || funcName == "`endswith") return "bool";
                if (funcName == "`to_int") return "int";
                if (funcName == "`to_float") return "float";
                if (funcName == "`to_double") return "double";
                if (funcName == "`to_char") return "char";
                if (funcName == "`to_addr_t" || funcName == "`to_address") return "addr_t";
                if (funcName == "`to_qbool") return "qbool";
                if (funcName == "`to_long_int") return "long int";
                if (funcName == "`to_short_int") return "short int";
                if (funcName == "`to_byte") return "byte";
                if (funcName == "`to_nibble") return "nibble";
                if (funcName == "`open") return "int";
                if (funcName == "`close" || funcName == "`write" || funcName == "`free" || funcName == "`flush") return "void";
                if (funcName == "`malloc" || funcName == "`calloc" || funcName == "`realloc" || funcName == "`mapped_ptr") return "void*";

                if (funcName == "`typeof") { return "string"; }
                if (funcName == "`ternary") {
                    if ((*callNode)->arg_nodes.size() < 3) {
                        cg_error((*varAcc)->var_name_tok.pos, "too few arguments to `ternary");
                        cg_note((*varAcc)->var_name_tok.pos, "`ternary expects 3 arguments: condition, true_value, false_value");
                        cg_note((*varAcc)->var_name_tok.pos, "got " + std::to_string((*callNode)->arg_nodes.size()) + " arguments");
                        return "unknown";
                    }
                    return getExpressionType(*std::next((*callNode)->arg_nodes.begin()));
                }
                if (funcName == "`next") {
                    if ((*callNode)->arg_nodes.size() < 2) {
                        cg_error((*varAcc)->var_name_tok.pos, "too few arguments to `next");
                        cg_note((*varAcc)->var_name_tok.pos, "`next expects 2 arguments");
                        cg_note((*varAcc)->var_name_tok.pos, "got " + std::to_string((*callNode)->arg_nodes.size()) + " arguments");
                        return "unknown";
                    }
                    auto node = *std::next((*callNode)->arg_nodes.begin());
                    if (auto str = std::get_if<StringNode>(&node)) {
                        return resolveTypeName(substituteGenerics(str->tok.value), false);
                    } else {
                        cg_error((*varAcc)->var_name_tok.pos, "arg 2 to `next is a comptime string");
                        cg_note((*varAcc)->var_name_tok.pos, "expected comptime string, got " + getExpressionType(node));
                        return "unknown";
                    }
                }
                if (classTypes.contains(resolveTypeName(funcName, false))) { return resolveTypeName(funcName, false); }
                if (functionDefs.contains(funcName)) {
                    auto* def = functionDefs[funcName];
                    if (!def->return_types.empty()) {
                        std::string ret = def->return_types[0].value;
                        if (ret.ends_with("&") && strip) ret.pop_back();
                        return substituteGenerics(ret);
                    }
                }
            }
            return "unknown";
        } else if (auto methCall = std::get_if<MethodCallNode*>(&node)) {
            std::string baseType = getExpressionType((*methCall)->base);
            if (baseType.ends_with("*") || baseType.ends_with("&")) baseType.pop_back();
            auto originalGenericMap = currentGenericTypeStrings;
            std::vector<std::string> actualArgs = genericParamsFromName(baseType);
            std::string className = baseTypeName(baseType);
            std::string methodName = (*methCall)->method_name.value;
            if (userTypes.contains(className)) {
                auto& formalParams = userTypes[className].generics;
                for (size_t i = 0; i < formalParams.size() && i < actualArgs.size(); ++i) {
                    currentGenericTypeStrings[formalParams[i].name] = actualArgs[i];
                }
            }
            std::string foundReturnType = "unknown";
            while (!className.empty() && userTypes.contains(className)) {
                auto& info = userTypes[className];
                bool methodFound = false;
                for (auto& m : info.classMethods) {
                    if (m.name_tok.value == methodName && !m.return_types.empty()) {
                        std::string ret = m.return_types[0].value;
                        if (ret.ends_with("&") && strip) ret.pop_back();
                        foundReturnType = substituteGenerics(ret);
                        methodFound = true;
                        break;
                    }
                }
                if (methodFound) break;
                std::string parentTypeStr = info.baseClassName;
                if (parentTypeStr.empty()) break;
                std::vector<std::string> parentActualArgs = genericParamsFromName(parentTypeStr);
                std::string nextClassName = baseTypeName(parentTypeStr);
                std::unordered_map<std::string, std::string> nextGenericMap;
                if (userTypes.contains(nextClassName)) {
                    auto& parentFormalParams = userTypes[nextClassName].generics;
                    for (size_t i = 0; i < parentFormalParams.size() && i < parentActualArgs.size(); ++i) {
                        nextGenericMap[parentFormalParams[i].name] = substituteGenerics(parentActualArgs[i]);
                    }
                }
                className = nextClassName;
                currentGenericTypeStrings = std::move(nextGenericMap);
            }
            currentGenericTypeStrings = std::move(originalGenericMap);

            return foundReturnType;
        }
        return "unknown";
    }
    bool returnsRef(unsigned index = 0) {
        auto* md = currentFunction->getMetadata("qc.return_types");
        if (!md || index >= md->getNumOperands()) return false;

        auto* s = llvm::dyn_cast<llvm::MDString>(md->getOperand(index));
        return s && s->getString().ends_with("&");
    }
    /*
    class TypedValue {
        llvm::Value* val;
        std::string qcType; // "int&", "int*", "string", etc.
        TypedValue(llvm::Value* val) {
            this->val = val;
        }
        TypedValue(std::string qcType, llvm::Value* val) {
            this->qcType = qcType;
            this->val = val;
        }
        operator llvm::Value*() const { return this->val; }
    };
    */
    llvm::Value* derefIfReference(llvm::Value* val, AnyNode& argNode) {
        if (!val || !val->getType()->isPointerTy()) return val;
        std::string qcType = substituteGenerics(getExpressionType(argNode, false));
        if (!qcType.ends_with("&")) return val;
        if (qcType.ends_with("&")) qcType.pop_back();
        llvm::Type* pointeeTy = llvmTypeFor(qcType);
        if (!pointeeTy || pointeeTy->isVoidTy()) return val;
        return builder->CreateLoad(pointeeTy, val, "deref_ref");
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
        if (classTypes.count(typeName) || genericClasses.count(baseTypeName(typeName))) {
            llvm::StructType* classTy = genericiseOrFindClass(typeName);
            int fieldIdx = getFlattenedFieldIndex(baseTypeName(typeName), propName);
            if (fieldIdx == -1) {
                cg_error(prop.property_name.pos, "field " + propName + " not found in class " + typeName);
                if (propName.length() > 3) {
                    std::vector<std::pair<int, std::string>> suggestions;
                    for (auto& field : userTypes[baseTypeName(typeName)].classFields) {
                        int distance = levenshteinDistance(propName, field.name);
                        if (distance <= 2) { suggestions.push_back({distance, field.name}); }
                    }
                    std::sort(suggestions.begin(), suggestions.end());
                    if (!suggestions.empty()) {
                        std::string note = "similar fields:";
                        for (auto& [distance, name] : suggestions) { note += "\n  - `" + name + "`"; }
                        cg_note(prop.property_name.pos, note);
                    }
                }
                return nullptr;
            }
            auto [fieldOwnerClass, fieldAccess] = getFieldOwner(baseTypeName(typeName), propName);
            if (!canAccessField(currentClassName, fieldOwnerClass, fieldAccess)) {
                cg_error(prop.property_name.pos, "cannot access " + fieldAccess + " field " + propName);
                return nullptr;
            }
            return builder->CreateStructGEP(classTy, baseAddr, fieldIdx, propName + "_ptr");
        }
        if (structTypes.count(typeName) || genericStructs.count(baseTypeName(typeName))) {
            auto structTy = genericiseOrFindStruct(typeName);
            auto& info = userTypes[baseTypeName(typeName)];
            int fieldIdx = -1;
            for (size_t i = 0; i < info.fields.size(); i++) {
                if (info.fields[i].name == propName) {
                    fieldIdx = (int)i;
                    break;
                }
            }
            if (fieldIdx == -1) {
                cg_error(prop.property_name.pos, "field " + propName + " not found in struct " + typeName);
                if (propName.length() > 3) {
                    std::vector<std::pair<int, std::string>> suggestions;
                    for (auto& field : userTypes[baseTypeName(typeName)].fields) {
                        int distance = levenshteinDistance(propName, field.name);
                        if (distance <= 2) { suggestions.push_back({distance, field.name}); }
                    }
                    std::sort(suggestions.begin(), suggestions.end());
                    if (!suggestions.empty()) {
                        std::string note = "similar fields:";
                        for (auto& [distance, name] : suggestions) { note += "\n  - `" + name + "`"; }
                        cg_note(prop.property_name.pos, note);
                    }
                }

                return nullptr;
            }
            return builder->CreateStructGEP(structTy, baseAddr, fieldIdx, propName + "_ptr");
        }
        if (unionTypes.count(typeName) || genericUnions.count(baseTypeName(typeName))) {
            auto unionInfo = genericiseOrFindUnion(typeName);
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
                        varTy = genericiseOrFindClass(variantName);
                    else if (structTypes.count(variantName))
                        varTy = genericiseOrFindStruct(variantName);
                    if (!varTy) continue;
                    return builder->CreateStructGEP(varTy, dataPtr, fieldIdx, propName + "_ptr");
                }
            }
        }
        cg_error(prop.property_name.pos, "cannot resolve address for property '" + propName + "' on type '" + typeName + "'");
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
            if (name == "this") {
                if (currentThis) {
                    return currentThis;
                } else {
                    cg_error((*var)->var_name_tok.pos, "'this' used outside class method");
                    return nullptr;
                }
            }
            llvm::Value* addr = getVarAddress(name);
            return addr;
        } else if (auto unary = std::get_if<UnaryOpNode*>(&node)) {
            if ((*unary)->op_tok.type == TokenType::MUL) { return emitExpr((*unary)->node); }
            if ((*unary)->op_tok.type == TokenType::AMPERSAND) { return emitLValue((*unary)->node); }
        } else if (auto prop = std::get_if<PropertyAccessNode*>(&node)) {
            return emitPropertyAddress(**prop);
        } else if (auto call = std::get_if<CallNode*>(&node)) {
            std::string retType = getExpressionType(node, false);
            if (retType.ends_with("&") || retType.ends_with("*")) { return emitExpr(node); }
        } else if (auto method = std::get_if<MethodCallNode*>(&node)) {
            std::string retType = getExpressionType(node, false);
            if (retType.ends_with("&") || retType.ends_with("*")) { return emitExpr(node); }
        } else if (auto arrAcc = std::get_if<ArrayAccessNode*>(&node)) {
            std::string ptrTy = getExpressionType((*arrAcc)->base);
            if (ptrTy.ends_with("*")) {
                ptrTy.pop_back();
                llvm::Value* base = emitExpr((*arrAcc)->base);
                llvm::Value* idx = emitExpr((*arrAcc)->indices[0]);
                return builder->CreateGEP(llvmTypeFor(ptrTy), base, idx, "lval_ptr_arr_addr");
            }
            if (ptrTy.ends_with("[]")) {
                llvm::Value* slot = emitLValue((*arrAcc)->base);
                llvm::Value* index = emitExpr((*arrAcc)->indices[0]);
                if (!slot || !index) return nullptr;
                std::string elementName = ptrTy.substr(0, ptrTy.size() - 2);
                llvm::Type* elementTy = llvmTypeFor(elementName);
                if (!elementTy) {
                    cg_error(get_pos((*arrAcc)->base), "invalid array element type: " + elementName);
                    return nullptr;
                }
                llvm::Value* dataPtr = builder->CreateLoad(builder->getPtrTy(), slot, "array_data");
                return builder->CreateInBoundsGEP(elementTy, dataPtr, index, "lval_arr_addr");
            }
            if (ptrTy.ends_with("]")) {
                llvm::Value* base = emitLValue((*arrAcc)->base);
                llvm::Value* index = emitExpr((*arrAcc)->indices[0]);
                if (!base) { return nullptr; }
                llvm::Type* arrayTy = llvmTypeFor(ptrTy);
                if (!arrayTy->isArrayTy()) {
                    cg_error(get_pos((*arrAcc)->base), "invalid array type for indexing");
                    return nullptr;
                }
                return builder->CreateGEP(arrayTy, base, {builder->getInt32(0), index}, "lval_arr_addr");
            }
            if (genericiseOrFindClass(ptrTy)) {
                llvm::Value* obj = emitLValue((*arrAcc)->base);
                llvm::Value* idx = emitExpr((*arrAcc)->indices[0]);
                return emitVirtualOrDirectCall(ptrTy, "operator[]", obj, {idx});
            }
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
    llvm::Value* emitPrimitiveConversion(llvm::Value* arg, const std::string& target, Position pos = Position()) {
        if (!arg) return nullptr;

        llvm::Type* ty = arg->getType();
        std::string fnName;
        llvm::Type* retTy = nullptr;

        if (target == "int") {
            retTy = builder->getInt32Ty();
            if (ty->isPointerTy())
                fnName = "qc_to_int_from_string";
            else if (ty->isFloatTy() || ty->isDoubleTy())
                return builder->CreateFPToSI(arg, retTy);
            else if (ty->isIntegerTy(64))
                return builder->CreateTrunc(arg, retTy);
            else if (ty->isIntegerTy(32))
                return arg;
            else if (ty->isIntegerTy())
                return builder->CreateSExt(arg, retTy);
        } else if (target == "short int") {
            retTy = builder->getInt16Ty();
            if (ty->isPointerTy())
                fnName = "qc_to_short_int_from_string";
            else if (ty->isFloatTy() || ty->isDoubleTy())
                return builder->CreateFPToSI(arg, retTy);
            else if (ty->isIntegerTy(64) || ty->isIntegerTy(32))
                return builder->CreateTrunc(arg, retTy);
            else if (ty->isIntegerTy(16))
                return arg;
            else if (ty->isIntegerTy())
                return builder->CreateSExt(arg, retTy);
        } else if (target == "long int") {
            retTy = builder->getIntNTy(getPtrSize());
            if (ty->isPointerTy())
                fnName = "qc_to_int_from_string";
            else if (ty->isFloatTy() || ty->isDoubleTy())
                return builder->CreateFPToSI(arg, retTy);
            else if (ty == retTy)
                return arg;
            else if (ty->isIntegerTy())
                return builder->CreateSExt(arg, retTy);
        } else if (target == "float") {
            retTy = builder->getFloatTy();
            if (ty->isPointerTy())
                fnName = "qc_to_float_from_string";
            else if (ty->isIntegerTy())
                return builder->CreateSIToFP(arg, retTy);
            else if (ty->isDoubleTy())
                return builder->CreateFPTrunc(arg, retTy);
            else if (ty->isFloatTy())
                return arg;
        } else if (target == "double") {
            retTy = builder->getDoubleTy();
            if (ty->isPointerTy())
                fnName = "qc_to_double_from_string";
            else if (ty->isIntegerTy())
                return builder->CreateSIToFP(arg, retTy);
            else if (ty->isFloatTy())
                return builder->CreateFPExt(arg, retTy);
            else if (ty->isDoubleTy())
                return arg;
        } else if (target == "bool") {
            retTy = builder->getInt1Ty();
            if (ty->isIntegerTy(1))
                return arg;
            else if (ty->isIntegerTy())
                return builder->CreateICmpNE(arg, llvm::ConstantInt::get(ty, 0));
            else if (ty->isFloatTy() || ty->isDoubleTy())
                return builder->CreateFCmpONE(arg, llvm::ConstantFP::get(ty, 0.0));
            else if (ty->isPointerTy())
                fnName = "qc_to_bool_from_string";
        } else if (target == "char") {
            retTy = builder->getInt8Ty();
            if (ty->isPointerTy())
                fnName = "qc_to_char_from_string";
            else if (ty->isIntegerTy(32))
                return builder->CreateTrunc(arg, retTy);
            else if (ty->isIntegerTy(8))
                return arg;
        } else if (target == "addr_t") {
            retTy = builder->getIntNTy(getPtrSize());
            if (ty->isPointerTy())
                fnName = "qc_to_addr_t_from_string";
            else if (ty->isIntegerTy())
                return builder->CreateZExtOrTrunc(arg, retTy);
            else if (ty->isFloatTy() || ty->isDoubleTy())
                return builder->CreateFPToUI(arg, retTy);
        } else if (target == "byte") {
            retTy = builder->getInt8Ty();
            if (ty->isPointerTy())
                fnName = "qc_to_byte_from_string";
            else if (ty->isIntegerTy())
                return builder->CreateZExtOrTrunc(arg, retTy);
            else if (ty->isFloatTy() || ty->isDoubleTy())
                return builder->CreateFPToUI(arg, retTy);
        } else if (target == "nibble") {
            retTy = builder->getIntNTy(4);
            if (ty->isPointerTy())
                fnName = "qc_to_nibble_from_string";
            else if (ty->isIntegerTy())
                return builder->CreateZExtOrTrunc(arg, retTy);
            else if (ty->isFloatTy() || ty->isDoubleTy())
                return builder->CreateFPToUI(arg, retTy);
        }

        if (fnName.empty() || !retTy) {
            cg_error(pos, "Cannot convert to " + target);
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
    llvm::Value* emitBuiltinConversion(llvm::Value* rawArg, const std::string& target, Position pos = Position()) {
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
            else if (target == "addr_t" || target == "long int")
                resultTy = builder->getIntNTy(getPtrSize());
            else if (target == "short int")
                resultTy = builder->getInt16Ty();
            else if (target == "nibble")
                resultTy = builder->getIntNTy(4);
            else if (target == "byte")
                resultTy = builder->getInt8Ty();
            else if (target == "qbool")
                resultTy = builder->getIntNTy(2);
            else {
                cg_error(pos, "Unknown conversion target: " + target);
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

                llvm::Value* converted = emitPrimitiveConversion(loaded, target, pos);
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
            else if (target == "addr_t" || target == "long int")
                resultTy = builder->getIntNTy(getPtrSize());
            else if (target == "short int")
                resultTy = builder->getInt16Ty();
            else if (target == "nibble")
                resultTy = builder->getIntNTy(4);
            else if (target == "byte")
                resultTy = builder->getInt8Ty();
            else if (target == "qbool")
                resultTy = builder->getIntNTy(2);
            else {
                cg_error(pos, "Unknown conversion target: " + target);
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

                llvm::Value* converted = emitPrimitiveConversion(loaded, target, pos);
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

        return emitPrimitiveConversion(rawArg, target, pos);
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
                    cg_error(get_pos(argNode), "argument doesn't match union variant for " + unionName + " parameter " + std::to_string(argIndex));
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
                    cg_error(get_pos(argNode), "argument doesn't match enum variant for " + enumName + " parameter " + std::to_string(argIndex));
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
        if (v->getType()->isArrayTy() && paramTy->isPointerTy()) {
            v = decayArrayToPointer(v);
            if (!v) return nullptr;
        }
        if (srcTy->isIntegerTy() && paramTy->isIntegerTy()) {
            unsigned srcBits = srcTy->getIntegerBitWidth();
            unsigned dstBits = paramTy->getIntegerBitWidth();
            if (srcBits < dstBits) {
                v = builder->CreateSExt(v, paramTy, "arg_sext");
            } else if (srcBits > dstBits) {
                v = builder->CreateTrunc(v, paramTy, "arg_trunc");
            }
            return v;
        }
        if (srcTy->isFloatTy() && paramTy->isDoubleTy()) { return builder->CreateFPExt(v, paramTy, "arg_fpext"); }
        if (srcTy->isDoubleTy() && paramTy->isFloatTy()) { return builder->CreateFPTrunc(v, paramTy, "arg_fptrunc"); }
        if (srcTy->isIntegerTy() && paramTy->isFloatingPointTy()) { return builder->CreateSIToFP(v, paramTy, "arg_sitofp"); }
        if (srcTy->isFloatingPointTy() && paramTy->isIntegerTy()) { return builder->CreateFPToSI(v, paramTy, "arg_fptosi"); }
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
                v = emitLValue(argNode);
                if (!v) {
                    cg_error(get_pos(argNode), "L-value required for reference parameter");
                    return {};
                }
            } else {
                v = emitExpr(argNode);
            }
            if (!v) {
                cg_error(get_pos(argNode), "Failed to emit argument");
                return {};
            }
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

                if (searchFields(baseTypeName(baseClass))) { return true; }
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
            auto it = userTypes.find(baseTypeName(currentClass));
            if (it == userTypes.end()) { return {"", "public"}; }

            auto& classInfo = it->second;
            for (auto& field : classInfo.classFields) {
                if (field.name == fieldName) { return {currentClass, field.access}; }
            }
            currentClass = classInfo.baseClassName;
        }

        return {"", "public"};
    }
    bool canAccessField(const std::string& callerClass, const std::string& fieldOwnerClass, const std::string& access) {
        auto userTypeIt = userTypes.find(resolveTypeName(fieldOwnerClass));
        UserTypeInfo usertype;
        if (userTypeIt != userTypes.end()) { usertype = userTypeIt->second; }
        bool isFriend = usertype.kind == UserTypeKind::Class && std::ranges::any_of(usertype.friendClasses, [&](const std::string& friendName) {
                            return resolveTypeName(friendName, false) == resolveTypeName(callerClass, false);
                        });
        bool isFriendly = usertype.kind == UserTypeKind::Class && std::ranges::any_of(usertype.friendlyClasses, [&](const std::string& friendName) {
                              return resolveTypeName(friendName, false) == resolveTypeName(callerClass, false);
                          });
        if (access == "public") return true;
        if (access == "private") { return callerClass == fieldOwnerClass || isFriend; }
        if (access == "protected") {
            if (callerClass == fieldOwnerClass || isFriend || isFriendly) return true;
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
    MethodCallNode* methodCallFromCall(CallNode* call, std::string name) {
        return new MethodCallNode(call->node_to_call, Token(TokenType::IDENTIFIER, name, get_pos(call)),
                                  std::vector<AnyNode>(call->arg_nodes.begin(), call->arg_nodes.end()));
    }
    FuncDefNode* funcDefFromClassMethod(const ClassMethodInfo& method, const std::string& className, std::string delim = "::") {
        std::string mangledName = className + delim + method.name_tok.value;
        Token nameTok(TokenType::IDENTIFIER, mangledName, method.name_tok.pos);
        return new FuncDefNode(method.return_types, nameTok, std::list(method.params.begin(), method.params.end()), method.body, "", false, false,
                               method.generics, false);
    }
    std::unordered_map<std::string, std::unordered_map<std::string, llvm::Function*>> genericisedMethods;
    llvm::Value* tryHandleSpecialized(const std::string& className, const std::string& methodName, MethodCallNode* node, llvm::Value* thisPtr) {
        if (auto methodIt = std::find_if(
                userTypes[baseTypeName(className)].classMethods.begin(), userTypes[baseTypeName(className)].classMethods.end(),
                [&](ClassMethodInfo method) { return method.name_tok.value == baseTypeName(methodName) && !method.generics.empty(); });
            methodIt != userTypes[baseTypeName(className)].classMethods.end()) {
            auto genericParams = genericParamsFromName(className);
            auto oldGenericTypes = this->currentGenericTypes;
            auto oldGenericTypeStrings = currentGenericTypeStrings;
            auto oldNonTypeGenerics = currentNonTypeGenericValues;
            if (!genericParams.empty()) {
                auto classInfo = userTypes[baseTypeName(className)];
                if (!fulfillsGenericConstraints(classInfo.generics, genericParams, classInfo.pos)) {
                    this->currentGenericTypes = oldGenericTypes;
                    currentGenericTypeStrings = oldGenericTypeStrings;
                    currentNonTypeGenericValues = oldNonTypeGenerics;
                    return nullptr;
                }
            }
            size_t methodIdx = std::distance(userTypes[baseTypeName(className)].classMethods.begin(), methodIt);
            if (genericisedMethods[fixMangling(className)][fixMangling(methodName)] == nullptr) {
                genericisedMethods[fixMangling(className)][fixMangling(methodName)] = generateSpecializedMethod(fixMangling(className), methodIdx,
                                                                                                                fixMangling(methodName));
            }
            llvm::Function* fn = genericisedMethods[fixMangling(className)][fixMangling(methodName)];
            auto& info = userTypes[baseTypeName(className)].classMethods[methodIdx];
            auto args = prepareArgs(&info, node->args);
            bool isVariadic = !info.params.empty() && info.params.back().type.value == "...";
            if (isVariadic) {
                size_t numFixedParams = info.params.size() - 1;
                std::vector<llvm::Value*> varVals;
                if (args.size() > numFixedParams) {
                    varVals.assign(args.begin() + numFixedParams, args.end());
                    args.resize(numFixedParams);
                }
                args.push_back(packVariadicArgs(varVals));
            }
            this->currentGenericTypes = oldGenericTypes;
            currentGenericTypeStrings = oldGenericTypeStrings;
            currentNonTypeGenericValues = oldNonTypeGenerics;
            return emitMethodCall(fn, thisPtr, args, methodName);
        }
        return nullptr;
    }
    void addConstructorNotes(const std::string& className, const std::vector<llvm::Value*>& args, Position pos) {
        auto& methods = userTypes[baseTypeName(className)].classMethods;
        struct Candidate {
            int score;
            ClassMethodInfo* method;
        };
        std::vector<Candidate> candidates;
        for (auto& method : methods) {
            if (!method.is_constructor) continue;
            int score = 0;
            size_t argCount = args.size();
            size_t paramCount = method.params.size();
            score -= std::abs((int)argCount - (int)paramCount) * 5;
            size_t count = std::min(argCount, paramCount);
            for (size_t i = 0; i < count; i++) {
                llvm::Type* argTy = args[i]->getType();
                llvm::Type* paramTy = llvmTypeFor(method.params[i].type.value);
                if (argTy == paramTy) {
                    score += 3;
                } else if ((argTy->isIntegerTy() || argTy->isFloatTy() || argTy->isDoubleTy()) &&
                           (paramTy->isIntegerTy() || paramTy->isFloatTy() || paramTy->isDoubleTy())) {
                    score += 1;
                } else if (argTy->isPointerTy() && paramTy->isPointerTy()) {
                    score += 1;
                } else {
                    score -= 3;
                }
            }
            candidates.push_back({score, &method});
        }
        if (candidates.empty()) return;
        std::sort(candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b) { return a.score > b.score; });
        if (candidates[0].score > 0) { cg_note(pos, "closest matching constructor: " + candidates[0].method->print()); }
        if (candidates.size() <= 5) {
            std::string note = "available constructors:";
            for (auto& candidate : candidates) { note += "\n  - " + candidate.method->print(); }
            cg_note(pos, note);
        } else {
            std::string note = "other constructors:";
            size_t shown = 0;
            for (auto& candidate : candidates) {
                if (shown >= 3) break;
                note += "\n  - " + candidate.method->print();
                shown++;
            }
            cg_note(pos, note);
        }
    }
    std::string fixMangling(std::string type) { return buildMangledName(baseTypeName(type), genericParamsFromName(type), true); }
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
        for (size_t i = 0; i < argNodes.size(); ++i) {
            llvm::Type* paramTy = nullptr;
            bool isRef = false;
            if (info && i < info->params.size()) {
                const std::string& typeName = info->params[i].type.value;
                isRef = typeName.ends_with("&");
                paramTy = llvmTypeFor(typeName);
            }
            llvm::Value* value = nullptr;
            if (isRef) {
                value = emitLValue(argNodes[i]);
            } else if (paramTy && paramTy->isPointerTy()) {
                value = emitExpr(argNodes[i]);
            } else {
                value = emitExpr(argNodes[i]);
            }
            if (!value) {
                cg_error(get_pos(argNodes[i]), "failed to emit method argument");
                return {};
            }
            if (paramTy) {
                value = adaptArgumentForParam(value, argNodes[i], paramTy, i);
                if (!value) return {};
            }
            args.push_back(value);
        }

        return args;
    }
    llvm::Value* emitMethodCall(llvm::Function* method, llvm::Value* thisPtr, const std::vector<llvm::Value*>& args, const std::string& name);
    std::string resolveVirtualTargetClass(const std::string& declaredClass, const std::string& methodName, size_t argCount) {
        for (auto& m : userTypes[baseTypeName(declaredClass)].classMethods) {
            if (m.name_tok.value == methodName && m.params.size() == argCount) return declaredClass;
        }
        for (auto& [name, info] : userTypes) {
            if (info.baseClassName == baseTypeName(declaredClass)) {
                for (auto& m : info.classMethods) {
                    if (m.name_tok.value == methodName && m.params.size() == argCount) return name;
                }
            }
        }
        return declaredClass;
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
                        auto utIt = userTypes.find(baseTypeName(currentClass));
                        if (utIt == userTypes.end()) {
                            std::string baseName = currentClass.find('<') != std::string::npos ? currentClass.substr(0, currentClass.find('<'))
                                                                                               : currentClass;
                            utIt = userTypes.find(baseTypeName(baseName));
                        }
                        if (utIt == userTypes.end()) break;
                        for (const auto& method : utIt->second.classMethods) {
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

                        if (fn->arg_size() - 1 != args.size())
                            continue;
                        else {
                            for (size_t i = 0; i < args.size(); i++) {

                                llvm::Type* expected = fn->getFunctionType()->getParamType(i + 1);
                                llvm::Type* actual = args[i]->getType();

                                if (expected != actual) {
                                    if (expected->isPointerTy() || actual->isPointerTy() || expected->isArrayTy() && actual->isPointerTy() ||
                                        expected->isPointerTy() && actual->isArrayTy()) {
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
                    }
                    return bestMatch;
                }
            }
            auto typeIt = userTypes.find(baseTypeName(currentClass));
            if (typeIt == userTypes.end()) {
                std::string baseName = currentClass.find('<') != std::string::npos ? currentClass.substr(0, currentClass.find('<')) : currentClass;
                typeIt = userTypes.find(baseTypeName(baseName));
            }

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
    llvm::Value* decayArrayToPointer(llvm::Value* v) {
        if (!v) return nullptr;
        if (auto* load = llvm::dyn_cast<llvm::LoadInst>(v)) {
            if (auto* arrayTy = llvm::dyn_cast<llvm::ArrayType>(load->getType())) {
                llvm::Value* address = load->getPointerOperand();
                llvm::Value* result = builder->CreateInBoundsGEP(arrayTy, address, {builder->getInt32(0), builder->getInt32(0)}, "decayptr");
                if (load->use_empty()) load->eraseFromParent();

                return result;
            }
        }
        if (auto* global = llvm::dyn_cast<llvm::GlobalVariable>(v)) {
            auto* arrTy = llvm::dyn_cast<llvm::ArrayType>(global->getValueType());
            if (arrTy) { return builder->CreateInBoundsGEP(arrTy, global, {builder->getInt32(0), builder->getInt32(0)}, "decayptr"); }
        }
        if (auto* alloca = llvm::dyn_cast<llvm::AllocaInst>(v)) {
            if (auto* arrTy = llvm::dyn_cast<llvm::ArrayType>(alloca->getAllocatedType())) {
                return builder->CreateInBoundsGEP(arrTy, alloca, {builder->getInt32(0), builder->getInt32(0)}, "decayptr");
            }
        }
        if (auto* arrTy = llvm::dyn_cast<llvm::ArrayType>(v->getType())) {
            llvm::AllocaInst* tmp = builder->CreateAlloca(arrTy);
            llvm::Value* srcPtr = builder->CreateAlloca(arrTy);
            builder->CreateStore(v, srcPtr);
            builder->CreateMemCpy(tmp, llvm::MaybeAlign(), srcPtr, llvm::MaybeAlign(), module->getDataLayout().getTypeAllocSize(arrTy));
            return builder->CreateInBoundsGEP(arrTy, tmp, {builder->getInt32(0), builder->getInt32(0)});
        }
        if (v->getType()->isPointerTy()) return v;
        return nullptr;
    }
    llvm::Value* emitVirtualOrDirectCall(const std::string& ty, const std::string& methodName, llvm::Value* payload,
                                         const std::vector<llvm::Value*>& args) {
        llvm::Function* method = findMethodOverload(ty, methodName, args);
        if (!method) return nullptr;
        ClassMethodInfo* info = nullptr;
        std::string searchClass = baseTypeName(ty);
        while (!searchClass.empty() && !info) {
            for (auto& m : userTypes.at(baseTypeName(searchClass)).classMethods) {
                if (m.name_tok.value == methodName && m.params.size() == args.size()) {
                    info = &m;
                    break;
                }
            }
            searchClass = userTypes.at(baseTypeName(searchClass)).baseClassName;
        }
        auto vtableIt = vtables.find(ty);
        auto slotIt = vtableSlotIndex.find(ty);
        if (vtableIt != vtables.end() && slotIt != vtableSlotIndex.end()) {
            std::string mangledName = ty + "_" + methodName;
            if (info && classMethods[ty][methodName].size() > 1) {
                for (auto& param : info->params) { mangledName += "_" + (param.signature.has_value() ? std::string("fn") : param.type.value); }
            }
            auto indexIt = slotIt->second.find(mangledName);
            if (indexIt != slotIt->second.end()) {
                int slotIndex = indexIt->second;
                llvm::StructType* classTy = genericiseOrFindClass(ty);
                llvm::Value* vptrField = builder->CreateStructGEP(classTy, payload, 0, "vptr_field");
                llvm::Value* vptr = builder->CreateLoad(builder->getPtrTy(), vptrField, "vptr");
                llvm::Value* fnPtrAddr = builder->CreateGEP(builder->getPtrTy(), vptr, builder->getInt32(slotIndex), "vtable_slot");
                llvm::Value* fnPtr = builder->CreateLoad(builder->getPtrTy(), fnPtrAddr, "fn_ptr");
                std::vector<llvm::Value*> allArgs = {payload};
                allArgs.insert(allArgs.end(), args.begin(), args.end());
                if (insideTry()) {
                    auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
                    llvm::InvokeInst* invoke = builder->CreateInvoke(method->getFunctionType(), fnPtr, contBB, currentLandingPad(), allArgs);
                    builder->SetInsertPoint(contBB);
                    return invoke;
                }
                return builder->CreateCall(method->getFunctionType(), fnPtr, allArgs);
            }
        }
        return emitMethodCall(method, payload, args, methodName);
    }
    uint64_t parseInteger(std::string s) {
        int base = 10;
        if (s.starts_with("0x") || s.starts_with("0X")) {
            base = 16;
        } else if (s.starts_with("0b") || s.starts_with("0B")) {
            base = 2;
            s = s.substr(2);
        } else if (s.size() > 1 && s[0] == '0') {
            base = 8;
        }
        return std::stoull(s, nullptr, base);
    }
    llvm::Function* generateSpecializedMethod(const std::string& className, size_t methodIdx, const std::string& specializedName) {
        llvm::Function* savedFunction = currentFunction;
        llvm::BasicBlock* savedBlock = builder->GetInsertBlock();
        auto savedGlobals = globals;
        auto savedThis = currentThis;
        auto savedClassName = currentClassName;
        auto savedNamespaceStack = namespaceStack;
        auto oldGenericTypes = this->currentGenericTypes;
        auto oldGenericTypeStrings = currentGenericTypeStrings;
        auto oldNonTypeGenerics = currentNonTypeGenericValues;
        auto genericParams = genericParamsFromName(specializedName);
        auto& method = userTypes[baseTypeName(className)].classMethods[methodIdx];
        if (!fulfillsGenericConstraints(method.generics, genericParams, method.name_tok.pos)) {
            this->currentGenericTypes = oldGenericTypes;
            currentGenericTypeStrings = oldGenericTypeStrings;
            currentNonTypeGenericValues = oldNonTypeGenerics;
            return nullptr;
        }        
        namespaceStack.clear();
        size_t nsSep = specializedName.rfind("::");
        if (nsSep != std::string::npos) {
            namespaceStack = {specializedName.substr(0, nsSep)};
        } else if (!userTypes[baseTypeName(className)].namespace_path.empty()) {
            namespaceStack = {userTypes[baseTypeName(className)].namespace_path};
        }
        enterScope();
        std::vector<llvm::Type*> paramTypes;
        paramTypes.push_back(llvm::PointerType::get(context, 0));
        llvm::FunctionType* baseFuncTy = llvmFuncTypeFor(method.return_types, method.params);
        for (auto* paramTy : baseFuncTy->params()) { paramTypes.push_back(paramTy); }
        llvm::FunctionType* fnTy = llvm::FunctionType::get(baseFuncTy->getReturnType(), paramTypes, false);
        llvm::Function* fn = module->getFunction(specializedName);
        if (!fn) fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, specializedName, module);
        size_t paramIdx = 0;
        if (method.is_volatile) {
            fn->addFnAttr(llvm::Attribute::NoInline);
            fn->addFnAttr(llvm::Attribute::OptimizeNone);
            fn->addFnAttr("noipa");
        }
        for (size_t i = 0; i < method.params.size(); i++) {
            auto& param = method.params[i];
            llvm::Type* paramTy;
            std::string typeDescriptor;

            if (param.signature.has_value()) {
                paramTy = llvm::PointerType::get(context, 0);
                typeDescriptor = "fn";
            } else {
                typeDescriptor = resolveTypeName(param.type.value, false);
                paramTy = llvmTypeFor(typeDescriptor);
            }
            llvm::AllocaInst* alloc = createEntryAlloca(param.name.value, paramTy);
            builder->CreateStore(fn->getArg(i + 1), alloc);
            locals[param.name.value] = alloc;
            varTypes[param.name.value] = typeDescriptor;
            volatileVars[param.name.value] = param.isVolatile;
        }
        for (int i = 1; i < fnTy->getNumParams(); i++) {
            if (method.params[i - 1].type.value.starts_with("out ")) {
                fn->addParamAttr(i, llvm::Attribute::WriteOnly);
                fn->addParamAttr(i, llvm::Attribute::getWithCaptureInfo(context, llvm::CaptureInfo::none()));
            } else if (method.params[i - 1].type.value.starts_with("inout ")) {
                fn->addParamAttr(i, llvm::Attribute::getWithCaptureInfo(context, llvm::CaptureInfo::none()));
            }
            if (method.params[i - 1].type.value.ends_with("restrict")) { fn->addParamAttr(i, llvm::Attribute::NoAlias); }
        }
        if (isHeader) return nullptr;
        currentFunction = fn;
        currentClassName = className;
        llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", fn);
        builder->SetInsertPoint(entry);
        auto argIt = fn->arg_begin();
        currentThis = &*argIt;
        ++argIt;
        paramIdx = 0;
        for (auto& stmt : method.body->statements) { emitStmt(stmt); }
        if (!builder->GetInsertBlock()->getTerminator()) {
            if (baseFuncTy->getReturnType()->isVoidTy()) {
                builder->CreateRetVoid();
            } else {
                builder->CreateRet(llvm::Constant::getNullValue(baseFuncTy->getReturnType()));
            }
        }
        exitScope();
        namespaceStack = savedNamespaceStack;
        currentFunction = savedFunction;
        globals = savedGlobals;
        this->currentGenericTypes = oldGenericTypes;
        currentGenericTypeStrings = oldGenericTypeStrings;
        currentNonTypeGenericValues = oldNonTypeGenerics;
        if (savedBlock) { builder->SetInsertPoint(savedBlock); }
        return fn;
    }
    std::string strip_decorations(std::string old) {
        old = old.substr(0, old.find("&"));
        old = old.substr(0, old.find("*"));
        old = old.substr(0, old.find("["));
        return old;
    }
    std::string remove_last_ptr(std::string old) {
        if (old.ends_with("*")) {
            old.pop_back();
        } else if (old.ends_with("]")) {
            size_t pos = old.rfind("[");
            if (pos != std::string::npos) { old.erase(pos); }
        }
        return old;
    }
    llvm::Function* generateSpecializedFunction(FuncDefNode* funcDef, std::string specializedName) {
        llvm::Function* savedFunction = currentFunction;
        llvm::BasicBlock* savedBlock = builder->GetInsertBlock();
        auto savedGlobals = globals;
        auto savedNamespaceStack = namespaceStack;
        auto oldGenericTypes = this->currentGenericTypes;
        auto oldGenericTypeStrings = currentGenericTypeStrings;
        auto oldNonTypeGenerics = currentNonTypeGenericValues;
        auto genericParams = genericParamsFromName(specializedName);
        if (!fulfillsGenericConstraints(funcDef->generics, genericParams, get_pos(funcDef))) {
            this->currentGenericTypes = oldGenericTypes;
            currentGenericTypeStrings = oldGenericTypeStrings;
            currentNonTypeGenericValues = oldNonTypeGenerics;
            return nullptr;
        }    
        namespaceStack.clear();
        size_t nsSep = specializedName.rfind("::");
        if (nsSep != std::string::npos) { namespaceStack = {specializedName.substr(0, nsSep)}; }
        enterScope();
        llvm::FunctionType* fnTy = llvmFuncTypeFor(funcDef->return_types, funcDef->params);
        llvm::Function* fn = module->getFunction(specializedName);
        if (!fn) fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, specializedName, module);
        if (funcDef->is_volatile) {
            fn->addFnAttr("noipa");
            fn->addFnAttr(llvm::Attribute::NoInline);
            fn->addFnAttr(llvm::Attribute::OptimizeNone);
        }
        for (int i = 0; i < fnTy->getNumParams(); i++) {
            auto it = funcDef->params.begin();
            std::advance(it, i);
            if (it->type.value.starts_with("out ")) {
                fn->addParamAttr(i, llvm::Attribute::WriteOnly);
                fn->addParamAttr(i, llvm::Attribute::getWithCaptureInfo(context, llvm::CaptureInfo::none()));
            } else if (it->type.value.starts_with("inout ")) {
                fn->addParamAttr(i, llvm::Attribute::getWithCaptureInfo(context, llvm::CaptureInfo::none()));
            }
            if (it->type.value.ends_with("restrict")) { fn->addParamAttr(i, llvm::Attribute::NoAlias); }
        }
        if (isHeader) return nullptr;
        currentFunction = fn;
        llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", fn);
        builder->SetInsertPoint(entry);
        auto argIt = fn->arg_begin();
        unsigned idx = 0;
        for (auto& arg : fn->args()) {
            auto& param = *std::next(funcDef->params.begin(), idx);
            arg.setName(param.name.value);
            auto* alloca = createEntryAlloca(arg.getName().str(), arg.getType());
            builder->CreateStore(&arg, alloca);
            locals[param.name.value] = alloca;
            if (param.signature.has_value()) {
                varTypes[param.name.value] = "fn";
                lambdaTypes[param.name.value] = llvmFuncTypeFor(param.signature->return_types, param.signature->params);
            } else {
                std::string t = param.type.value;
                if (t.find("[]") != std::string::npos) {
                    int dims = 0;
                    size_t pos = t.find("[]");
                    while (pos != std::string::npos) {
                        dims++;
                        pos = t.find("[]", pos + 2);
                    }
                    if (dims > 0) {
                        cg_warn(get_pos(funcDef),
                                "Using type " + t + " as parameter to function, which will degrade to " + ([](std::string str) {
                                    size_t pos = 0;
                                    while ((pos = str.find("[]", pos)) != std::string::npos) {
                                        str.replace(pos, 2, "*");
                                        pos += 1;
                                    }
                                    return str;
                                }(t)) +
                                    ". Please consider changing the type of this parameter to that type instead, and if you need the length "
                                    "property (which won't exist on pointers), add an additional length parameter.");
                    }
                    if (dims > 1) {
                        std::string base = t.substr(0, t.find("[]"));
                        int baseTypeCode = getTypeCode(base);
                        if (alloca->getType()->isArrayTy()) { arrayLengths[param.name.value] = alloca->getType()->getArrayNumElements(); }
                        jaggedArrays[param.name.value] = {baseTypeCode, dims};
                        arrayTypeStrings[param.name.value] = base;
                        varTypes[param.name.value] = param.type.value;
                    } else {
                        std::string base = t.substr(0, t.find("[]"));
                        if (alloca->getType()->isArrayTy()) { arrayLengths[param.name.value] = alloca->getType()->getArrayNumElements(); }
                        arrayTypeStrings[param.name.value] = base;
                        varTypes[param.name.value] = param.type.value;
                    }
                } else {
                    varTypes[param.name.value] = t;
                }
            }
            volatileVars[param.name.value] = param.isVolatile;
            idx++;
        }

        for (auto& stmt : funcDef->body->statements) { emitStmt(stmt); }
        if (!builder->GetInsertBlock()->getTerminator()) {
            if (fnTy->getReturnType()->isVoidTy()) {
                builder->CreateRetVoid();
            } else {
                builder->CreateRet(llvm::Constant::getNullValue(fnTy->getReturnType()));
            }
        }
        exitScope();
        namespaceStack = savedNamespaceStack;
        currentFunction = savedFunction;
        globals = savedGlobals;
        this->currentGenericTypes = oldGenericTypes;
        currentGenericTypeStrings = oldGenericTypeStrings;
        currentNonTypeGenericValues = oldNonTypeGenerics;
        if (savedBlock) { builder->SetInsertPoint(savedBlock); }
        return fn;
    }
    llvm::GlobalVariable* getOrCreateVtable(const std::string& name, llvm::ArrayType* type, llvm::Constant* initializer) {
        if (auto* existing = module->getNamedGlobal(name)) { return existing; }
        return new llvm::GlobalVariable(*module, type, true, llvm::GlobalValue::ExternalLinkage, initializer, name);
    }
    llvm::Value* packVariadicArgs(const std::vector<llvm::Value*>& var_vals) {
        llvm::Value* args_cnt = builder->getInt32(var_vals.size());
        llvm::Value* items_array = builder->CreateAlloca(builder->getPtrTy(), args_cnt, "varargs_array");
        for (size_t i = 0; i < var_vals.size(); ++i) {
            llvm::Value* index = builder->getInt32(i);
            llvm::Value* element_ptr = builder->CreateGEP(builder->getPtrTy(), items_array, index);
            llvm::Value* valueToStore = var_vals[i];
            llvm::Type* valTy = valueToStore->getType();
            if (valTy->isStructTy()) {
                llvm::Value* tempAlloc = builder->CreateAlloca(valTy, nullptr, "vararg_struct_tmp");
                builder->CreateStore(valueToStore, tempAlloc);
                valueToStore = tempAlloc;
            } else if (valTy->isIntegerTy()) {
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
    std::vector<std::string> genericParamsFromName(std::string baseName) {
        size_t open = baseName.find('<');
        if (open == std::string::npos) { return {}; }
        size_t close = baseName.rfind('>');
        std::string inner = baseName.substr(open + 1, close - open - 1);
        std::vector<std::string> genericParams;
        std::string cur;
        int depth = 0;
        for (char c : inner) {
            if (c == '<')
                depth++;
            else if (c == '>')
                depth--;
            else if (c == ',' && depth == 0) {
                genericParams.push_back(trim(cur));
                cur.clear();
                continue;
            }
            cur += c;
        }
        if (!cur.empty()) genericParams.push_back(trim(cur));
        return genericParams;
    }
    std::string buildMangledName(const std::string& baseName, const std::vector<std::string>& params, bool noBrace = false) {
        if (params.empty() && noBrace) return baseName;
        std::string result = baseName + "<";
        for (size_t i = 0; i < params.size(); i++) {
            if (i != 0) result += ",";
            result += params[i];
        }
        return result + ">";
    }
    void generateStructReprFunction(std::string name, UserTypeInfo info) {
        llvm::BasicBlock* savedBB = builder->GetInsertBlock();
        if (info.kind != UserTypeKind::Struct) return;
        llvm::StructType* structTy = genericiseOrFindStruct(name);
        llvm::FunctionType* reprFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {structTy}, false);
        llvm::Function* reprFn = module->getFunction(name + "_repr");
        if (!reprFn) reprFn = llvm::Function::Create(reprFnTy, llvm::Function::ExternalLinkage, name + "_repr", module);
        if (isHeader) return;
        llvm::BasicBlock* entryBB = llvm::BasicBlock::Create(context, "entry", reprFn);
        builder->SetInsertPoint(entryBB);
        llvm::Value* structArg = reprFn->arg_begin();
        llvm::Value* result = builder->CreateGlobalString(name + "(");
        for (size_t i = 0; i < info.fields.size(); i++) {
            auto& field = info.fields[i];
            if (i > 0) {
                llvm::Value* comma = builder->CreateGlobalString(", ");
                result = callStringConcat(result, comma);
            }
            llvm::Value* fieldLabel = builder->CreateGlobalString(field.name + "=");
            result = callStringConcat(result, fieldLabel);
            llvm::Value* fieldVal = builder->CreateExtractValue(structArg, i);
            llvm::Value* fieldStr = nullptr;
            auto type = substituteGenerics(field.type);
            if (type == "int") {
                llvm::Function* toStrFn = module->getFunction("qc_to_string_int");
                fieldStr = builder->CreateCall(toStrFn, {fieldVal});
            } else if (type == "float") {
                llvm::Function* toStrFn = module->getFunction("qc_to_string_float");
                fieldStr = builder->CreateCall(toStrFn, {fieldVal});
            } else if (type == "double") {
                llvm::Function* toStrFn = module->getFunction("qc_to_string_double");
                fieldStr = builder->CreateCall(toStrFn, {fieldVal});
            } else if (type == "bool") {
                llvm::Function* toStrFn = module->getFunction("qc_to_string_bool");
                fieldStr = builder->CreateCall(toStrFn, {fieldVal});
            } else if (type == "char") {
                llvm::Function* toStrFn = module->getFunction("qc_to_string_char");
                fieldStr = builder->CreateCall(toStrFn, {fieldVal});
            } else if (type == "string") {
                fieldStr = fieldVal;
            } else if (structTypes.find(type) != structTypes.end()) {
                llvm::Function* nestedReprFn = module->getFunction(type + "_repr");
                if (nestedReprFn) {
                    fieldStr = builder->CreateCall(nestedReprFn, {fieldVal});
                } else {
                    fieldStr = builder->CreateGlobalString("?");
                }
            } else {
                fieldStr = builder->CreateGlobalString("?");
            }

            result = callStringConcat(result, fieldStr);
        }
        llvm::Value* closeParen = builder->CreateGlobalString(")");
        result = callStringConcat(result, closeParen);

        builder->CreateRet(result);
        if (savedBB) { builder->SetInsertPoint(savedBB); }
    }
    void proveConceptsForTypeInfo(std::string mapKey, UserTypeInfo info) {
        if (info.provedConcepts.empty()) return;
        for (auto& proof : info.provedConcepts) {
            std::string conceptName = proof.conceptName.value;
            auto [conceptInfo, exists] = genericiseOrFindConcept(resolveTypeName(conceptName, false));
            if (!exists) {
                cg_error(proof.conceptName.pos, "Unknown concept '" + conceptName + "'");
                continue;
            }
            std::unordered_set<std::string> additionalProofNames;
            for (auto& proofMethod : proof.additionalProof) {
                additionalProofNames.insert(proofMethod.name_tok.value);
            }
            auto alreadyDefd = [&](const std::string& methodName, const std::vector<Parameter>& sigParams) -> bool {
                std::string mangledName = mapKey + "_" + methodName;
                auto it = functionDefs.find(mangledName);
                if (it == functionDefs.end()) {
                    return false;
                }
                FuncDefNode* funcNode = it->second;
                if (!funcNode) return false;
                if (funcNode->params.size() != sigParams.size()) {
                    return false;
                }
                auto actualParamIt = funcNode->params.begin();
                for (size_t i = 0; i < sigParams.size(); ++i, ++actualParamIt) {
                    std::string expectedType = (sigParams[i].type.value == "Self") ? mapKey : sigParams[i].type.value;
                    std::string actualType = actualParamIt->type.value;
                    if (resolveTypeName(expectedType, false) != resolveTypeName(actualType, false)) {
                        return false;
                    }
                }
                return true;
            };
            auto matchesSignature = [&](const ConceptInfo::FunctionSignature& sig, const UserTypeInfo& targetType, const ProvedConcepts& proof) -> bool {
                std::string methodName = sig.name.value;
                auto matchesParams = [&](const std::vector<Parameter>& sigParams, const std::vector<Parameter>& targetParams) {
                    if (sigParams.size() != targetParams.size()) return false;
                    for (size_t i = 0; i < sigParams.size(); ++i) {
                        std::string sigParamTy = (sigParams[i].type.value == "Self") ? mapKey : sigParams[i].type.value;
                        std::string targetParamTy = targetParams[i].type.value;
                        if (resolveTypeName(sigParamTy, false) != resolveTypeName(targetParamTy, false)) return false;
                    }
                    return true;
                };
                for (auto& method : targetType.classMethods) {
                    if (method.name_tok.value == methodName && matchesParams(sig.params, method.params)) {
                        return true;
                    }
                }
                for (auto& proofMethod : proof.additionalProof) {
                    if (proofMethod.name_tok.value == methodName && matchesParams(sig.params, proofMethod.params)) {
                        return true;
                    }
                }
                if (alreadyDefd(methodName, sig.params)) {
                    return true;
                }
                return false;
            };
            std::function<bool(const std::pair<ConceptInfo::Block, std::optional<ConceptInfo::DefaultBlock>>&)> verifyBlock = 
            [&](const std::pair<ConceptInfo::Block, std::optional<ConceptInfo::DefaultBlock>>& block) -> bool {
                auto b = block.first;
                std::vector<std::pair<Position, std::optional<std::string>>> failedConstraints;
                std::vector<Position> passedConstraints;
                for (const Token& requiredConcept : b.requiredConcepts) {
                    if (!std::ranges::any_of(info.provedConcepts, [&](const ProvedConcepts& c) {
                            return resolveTypeName(requiredConcept.value, false) == resolveTypeName(c.conceptName.value, false);
                        })) {
                        failedConstraints.push_back({requiredConcept.pos, "missing required concept proof: " + requiredConcept.value});
                    } else {
                        passedConstraints.push_back(requiredConcept.pos);
                    }
                }
                for (const auto& sig : b.signatures) {
                    if (!matchesSignature(sig, info, proof)) {
                        failedConstraints.push_back({sig.name.pos, "missing matching method: " + sig.print()});
                    } else {
                        passedConstraints.push_back(sig.name.pos);
                    }
                }
                for (const auto& sub : b.subblocks) {
                    if (!verifyBlock(std::pair(sub, std::nullopt))) {
                        failedConstraints.push_back({sub.constraint.pos, "nested block constraint failed"});
                    } else {
                        passedConstraints.push_back(sub.constraint.pos);
                    }
                }
                bool failed = false;
                bool isAtLeast = false;
                int requiredCount = -1;
                if (b.constraint.value == "all_of") {
                    failed = !failedConstraints.empty();
                } else if (b.constraint.value.ends_with("_of")) {
                    std::string val = b.constraint.value;
                    if (val.starts_with("at_least ")) {
                        isAtLeast = true;
                        val = val.substr(std::string("at_least ").length());
                    }
                    size_t pos = val.find("_of");
                    if (pos != std::string::npos) {
                        std::string numStr = val.substr(0, pos);
                        if (!numStr.empty() && std::all_of(numStr.begin(), numStr.end(), ::isdigit)) {
                            requiredCount = std::stoi(numStr);
                        }
                    }
                    if (isAtLeast) failed = (int)passedConstraints.size() < requiredCount;
                    else failed = (int)passedConstraints.size() != requiredCount;
                }
                if (failed && !block.second.has_value()) {
                    if (requiredCount >= 0) {
                        cg_error(proof.conceptName.pos, "failed to prove concept " + conceptName + " for type " + mapKey);
                        cg_note(block.first.constraint.pos, "due to this constraint block");
                        cg_note(block.first.constraint.pos, (isAtLeast ? "less than " + std::to_string(requiredCount) + " constraints were fulfiled" :
                            "the amount of fulfiled constraints was not equal to " + std::to_string(requiredCount)) + "(amount of fulfilled constraints: " + std::to_string(passedConstraints.size() == 0 ? 0 : passedConstraints.size() - 1) + ")");
                        cg_note(proof.conceptName.pos, "failed constraints were:"); 
                        for (auto& [failedConstraintPos, additionalMessage] : failedConstraints) {
                            cg_note(failedConstraintPos, additionalMessage.has_value() ? ("    " + additionalMessage.value()) : "");
                        }
                        cg_note(proof.conceptName.pos, "passed constraints were:"); 
                        for (auto& passedConstraintPos : passedConstraints) {
                            cg_note(passedConstraintPos, "");
                        }

                    } else {
                        cg_error(proof.conceptName.pos, "failed to prove concept " + conceptName + " for type " + mapKey);
                        cg_note(block.first.constraint.pos, "due to this constraint block");
                        cg_note(proof.conceptName.pos, "failed constraints were:"); 
                        for (auto& [failedConstraintPos, additionalMessage] : failedConstraints) {
                            cg_note(failedConstraintPos, additionalMessage.has_value() ? ("    " + additionalMessage.value()) : "");
                        }
                    }
                }
                if (block.second.has_value()) return false;
                return true;
            };
            for (std::pair<ConceptInfo::Block, std::optional<ConceptInfo::DefaultBlock>>& block : conceptInfo.blocks) {
                bool blockPassed = verifyBlock(block);
                if (blockPassed || block.second.has_value()) {
                    if (info.kind == UserTypeKind::Class) {
                        for (auto& proofMethod : proof.additionalProof) {
                            info.classMethods.push_back(proofMethod);
                            size_t newIdx = info.classMethods.size() - 1;
                            if (!proofMethod.generics.empty()) {
                                if (!proofMethod.is_static) {
                                    genericMethodIndices[mapKey].push_back(newIdx);
                                }
                            } else {
                                std::string methodName = mapKey + "_" + proofMethod.name_tok.value;
                                std::vector<llvm::Type*> paramTypes;
                                paramTypes.push_back(llvm::PointerType::get(context, 0));
                                llvm::FunctionType* baseFuncTy = llvmFuncTypeFor(proofMethod.return_types, proofMethod.params);
                                for (auto* paramTy : baseFuncTy->params()) { 
                                    paramTypes.push_back(paramTy); 
                                }
                                llvm::FunctionType* fnTy = llvm::FunctionType::get(baseFuncTy->getReturnType(), paramTypes, false);
                                llvm::Function* fn = module->getFunction(methodName);
                                if (!fn) {
                                    fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, methodName, module);
                                }
                                classMethods[mapKey][proofMethod.name_tok.value].push_back(fn);
                                functionDefs[methodName] = funcDefFromClassMethod(proofMethod, mapKey, "_");
                            }
                        }
                    } else {
                        for (auto& proofMethod : proof.additionalProof) {
                            std::string methodName = mapKey + "_" + proofMethod.name_tok.value;
                            ClassMethodInfo concreteMethod = proofMethod;
                            for (auto& param : concreteMethod.params) {
                                if (param.type.value == "Self") {
                                    param.type.value = mapKey;
                                }
                            }
                            for (auto& ret : concreteMethod.return_types) {
                                if (ret.value == "Self") {
                                    ret.value = mapKey;
                                }
                            }
                            FuncDefNode *funcNode = funcDefFromClassMethod(concreteMethod, mapKey, "_");
                            functionDefs[methodName] = funcNode;
                            if (!concreteMethod.generics.empty()) {
                                continue;
                            }
                            emitFuncDef(*funcNode);                       
                        }
                    }
                }
                if (!blockPassed) {
                    if (block.second.has_value()) {
                        auto& defaultBlock = block.second.value();
                        std::string targetModifier = (info.kind == UserTypeKind::Class) ? "class" : "else";
                        for (auto& [modifierTok, defaultMethod] : defaultBlock.definitions) {
                            if (modifierTok.value == targetModifier) {
                                std::string methodName = defaultMethod.name_tok.value;
                                bool alreadyProvided = alreadyDefd(methodName, defaultMethod.params);
                                if (!alreadyProvided) {
                                    for (auto& proofMethod : proof.additionalProof) {
                                        if (proofMethod.name_tok.value == methodName) {
                                            alreadyProvided = true;
                                            break;
                                        }
                                    }
                                }
                                if (!alreadyProvided) {
                                    ClassMethodInfo concreteMethod = defaultMethod;
                                    for (auto& param : concreteMethod.params) {
                                        if (param.type.value == "Self") {
                                            param.type.value = mapKey;
                                        }
                                    }
                                    for (auto& ret : concreteMethod.return_types) {
                                        if (ret.value == "Self") {
                                            ret.value = mapKey;
                                        }
                                    }
                                    if (info.kind == UserTypeKind::Class) {
                                        info.classMethods.push_back(concreteMethod);
                                        size_t newIdx = info.classMethods.size() - 1;
                                        if (!concreteMethod.generics.empty()) {
                                            if (!concreteMethod.is_static) {
                                                genericMethodIndices[mapKey].push_back(newIdx);
                                            }
                                        } else {
                                            std::string mangledName = mapKey + "_" + concreteMethod.name_tok.value;
                                            std::vector<llvm::Type*> paramTypes;
                                            paramTypes.push_back(llvm::PointerType::get(context, 0));
                                            llvm::FunctionType* baseFuncTy = llvmFuncTypeFor(concreteMethod.return_types, concreteMethod.params);
                                            for (auto* paramTy : baseFuncTy->params()) {
                                                paramTypes.push_back(paramTy);
                                            }
                                            llvm::FunctionType* fnTy = llvm::FunctionType::get(baseFuncTy->getReturnType(), paramTypes, false);
                                            llvm::Function* fn = module->getFunction(mangledName);
                                            if (!fn) {
                                                fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, mangledName, module);
                                            }
                                            classMethods[mapKey][concreteMethod.name_tok.value].push_back(fn);
                                            functionDefs[mangledName] = funcDefFromClassMethod(concreteMethod, mapKey, "_");
                                        }
                                    } else {
                                        std::string mangledName = mapKey + "_" + concreteMethod.name_tok.value;
                                        FuncDefNode *funcNode = funcDefFromClassMethod(concreteMethod, mapKey, "_");
                                        functionDefs[mangledName] = funcNode;
                                        if (!concreteMethod.generics.empty()) {
                                            continue;
                                        }
                                        emitFuncDef(*funcNode);
                                    }                            
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::pair<ConceptInfo, bool> genericiseOrFindConcept(const std::string& baseName) {
        const auto base = baseTypeName(baseName);
        if (genericConcepts.contains(base) && genericConcepts.at(base)) {
            if (auto it = concepts.find(baseName); it != concepts.end()) { return std::make_pair(it->second, true); }
            auto userIt = userTypes.find(base);
            if (userIt == userTypes.end()) { return std::make_pair(ConceptInfo{}, false); }
            return std::make_pair(generateGenericConcept(base, userIt->second, genericParamsFromName(baseName)), true);
        }
        if (auto it = concepts.find(baseName); it != concepts.end()) { return std::make_pair(it->second, true); }
        return std::make_pair(ConceptInfo{}, false);
    }
    llvm::StructType* genericiseOrFindClass(const std::string& baseName) {
        const auto base = baseTypeName(baseName);
        if (genericClasses.contains(base) && genericClasses.at(base)) {
            if (auto it = classTypes.find(baseName); it != classTypes.end()) { return it->second; }
            auto userIt = userTypes.find(base);
            if (userIt == userTypes.end()) { return nullptr; }
            return generateGenericClass(base, userIt->second, genericParamsFromName(baseName));
        }
        if (auto it = classTypes.find(baseName); it != classTypes.end()) { return it->second; }
        return nullptr;
    }
    llvm::StructType* genericiseOrFindStruct(std::string baseName) {
        if (genericStructs.contains(baseTypeName(baseName)) && genericStructs[baseTypeName(baseName)]) {
            if (structTypes.count(baseName)) return structTypes[baseName];
            llvm::StructType* structTy = generateGenericStruct(baseTypeName(baseName), userTypes[baseTypeName(baseName)],
                                                               genericParamsFromName(baseName));
            if (structTy == nullptr) {
                cg_error(userTypes[baseTypeName(baseName)].pos, "Failed to create specialized version of struct " + baseTypeName(baseName));
                return nullptr;
            }
            return structTy;
        }
        return structTypes.contains(baseName) ? structTypes[baseName] : nullptr;
    }
    UserTypeInfo genericiseOrFindUnion(std::string baseName) {
        if (genericUnions.contains(baseTypeName(baseName)) && genericUnions[baseTypeName(baseName)]) {
            if (unionTypes.count(baseName)) return substitutedUnions[baseName];
            UserTypeInfo unionInfo = generateGenericUnion(baseTypeName(baseName), userTypes[baseTypeName(baseName)], genericParamsFromName(baseName));
            if (static_cast<int>(unionInfo.kind) == 0) {
                cg_error(userTypes[baseTypeName(baseName)].pos, "Failed to create specialized version of union " + baseTypeName(baseName));
                return {};
            }
            return unionInfo;
        }
        return userTypes.contains(baseTypeName(baseName)) ? userTypes[baseTypeName(baseName)] : UserTypeInfo{};
    }
    std::string genericiseOrFindAlias(std::string baseName) {
        if (genericAliases.count(baseTypeName(baseName)) && genericAliases[baseTypeName(baseName)]) {
            if (typeAliases.count(baseName)) return resolveTypeName(typeAliases[baseName]);
            std::string newAlias = generateGenericAlias(baseTypeName(baseName), userTypes[baseTypeName(baseName)], genericParamsFromName(baseName));
            if (newAlias == "") {
                cg_error(userTypes[baseTypeName(baseName)].pos, "Failed to create specialized version of union " + baseTypeName(baseName));
                return "";
            }
            return resolveTypeName(newAlias);
        }
        if (typeAliases.count(baseName)) return resolveTypeName(typeAliases[baseName]);
        return baseName;
    }
    std::string resolveTypeName(std::string name, bool strip = true) {
        if (name == "int" || name == "float" || name == "double" || name == "char" || name == "bool" || name == "qbool" || name == "string" ||
            name == "byte" || name == "void" || name == "auto" || name == "short int" || name == "long int" || name == "long double" ||
            name == "addr_t" || name == "nibble") {
            return name;
        }
        std::string suffix;
        while (!name.empty() && (name.ends_with("*") || name.ends_with("&") || name.ends_with("[]"))) {
            if (name.ends_with("[]")) {
                suffix = "[]" + suffix;
                name = name.substr(0, name.size() - 2);
            } else {
                suffix = std::string(1, name.back()) + suffix;
                name = name.substr(0, name.size() - 1);
            }
        }
        auto finish = [&](std::string s) { return s + suffix; };
        name = genericiseOrFindAlias(name);
        std::string savedName = name;
        std::vector<std::string> params;
        for (std::string param : genericParamsFromName(savedName)) { params.push_back(resolveTypeName(param, false)); }
        if (!params.empty()) savedName = buildMangledName(baseTypeName(name), params);
        name = baseTypeName(name);

        if (name.find("::") != std::string::npos) {
            if (classTypes.find(savedName) != classTypes.end()) return finish(strip ? name : savedName);
            if (genericClasses.find(name) != genericClasses.end()) return finish(strip ? name : savedName);
            if (genericStructs.find(name) != genericStructs.end()) return finish(strip ? name : savedName);
            if (genericUnions.find(name) != genericUnions.end()) return finish(strip ? name : savedName);
            if (structTypes.find(savedName) != structTypes.end()) return finish(strip ? name : savedName);
            if (enumTypes.find(savedName) != enumTypes.end()) return finish(strip ? name : savedName);
            if (unionTypes.find(savedName) != unionTypes.end()) return finish(strip ? name : savedName);
            if (typeAliases.find(savedName) != typeAliases.end()) return finish(strip ? name : savedName);
            if (concepts.find(savedName) != concepts.end()) return finish(strip ? name : savedName);
            if (genericConcepts.find(savedName) != genericConcepts.end()) return finish(strip ? name : savedName);
        }

        std::string current = getCurrentNamespace();

        while (true) {
            std::string fullName = current.empty() ? name : current + "::" + name;
            std::string fullSavedName = current.empty() ? savedName : current + "::" + savedName;
            std::string result = strip ? fullName : fullSavedName;
            if (concepts.count(fullSavedName)) return finish(result);
            if (genericConcepts.count(fullName)) return finish(result);
            if (typeAliases.count(fullSavedName)) return finish(result);
            if (classTypes.count(fullSavedName)) return finish(result);
            if (genericClasses.count(fullName)) return finish(result);
            if (genericStructs.count(fullName)) return finish(result);
            if (genericUnions.count(fullName)) return finish(result);
            if (structTypes.count(fullSavedName)) return finish(result);
            if (enumTypes.count(fullSavedName)) return finish(result);
            if (unionTypes.count(fullSavedName)) return finish(result);
            if (hasArrayType(fullSavedName)) return finish(result);
            if (current.empty()) break;
            size_t pos = current.rfind("::");
            current = (pos == std::string::npos) ? "" : current.substr(0, pos);
        }
        return finish(name);
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
            if (hasLocal(name)) return findLocal(name)->second;
            if (globals.count(name)) return globals[name];
        }
        std::string current = getCurrentNamespace();
        while (true) {
            std::string fullName = current.empty() ? name : current + "::" + name;
            if (hasLocal(fullName)) return findLocal(fullName)->second;
            auto git = globals.find(fullName);
            if (git != globals.end()) { return git->second; }
            if (current.empty()) break;
            size_t pos = current.rfind("::");
            current = (pos == std::string::npos) ? "" : current.substr(0, pos);
        }
        if (hasLocal(name)) return findLocal(name)->second;
        if (globals.count(name)) return globals[name];
        return nullptr;
    }

    std::vector<std::string> getVisibleVariables() {
        std::vector<std::string> vars;
        std::string current = getCurrentNamespace();
        while (true) {
            std::string prefix = current.empty() ? "" : current + "::";
            for (auto& [name, type] : varTypes) {
                if (!name.starts_with(prefix)) continue;
                std::string relative = name.substr(prefix.size());
                vars.push_back(relative);
            }
            if (current.empty()) break;
            size_t pos = current.rfind("::");
            current = (pos == std::string::npos) ? "" : current.substr(0, pos);
        }
        return vars;
    }
    std::string resolveVarType(const std::string& name) {
        if (name.find("::") != std::string::npos) {
            if (hasVarType(name)) return findVarType(name)->second;
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
    bool resolveVolatileVar(const std::string& name) {
        std::string current = getCurrentNamespace();
        while (true) {
            std::string fullName = current.empty() ? name : current + "::" + name;
            if (hasVolatileVar(fullName)) return findVolatileVar(fullName)->second;
            if (current.empty()) break;
            size_t pos = current.rfind("::");
            current = (pos == std::string::npos) ? "" : current.substr(0, pos);
        }
        if (hasVolatileVar(name)) return findVolatileVar(name)->second;
        return false;
    }
    std::optional<std::string> resolveArrayType(const std::string& name) {
        std::string current = getCurrentNamespace();
        while (true) {
            std::string fullName = current.empty() ? name : current + "::" + name;
            if (hasArrayType(fullName)) { return findArrayType(fullName)->second; }
            if (current.empty()) break;
            size_t pos = current.rfind("::");
            current = pos == std::string::npos ? "" : current.substr(0, pos);
        }
        if (hasArrayType(name)) { return findArrayType(name)->second; }
        return std::nullopt;
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

            auto evalMethod = findMethodInHierarchy(className, "_eval");
            if (evalMethod.first) {
                std::vector<llvm::Value*> args;

                llvm::AllocaInst* temp = createEntryAlloca("temp_eval", ty);
                builder->CreateStore(v, temp);
                args.push_back(temp);
                if (insideTry()) {
                    auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
                    llvm::InvokeInst* invoke = builder->CreateInvoke(evalMethod.first, contBB, currentLandingPad(), args);
                    builder->SetInsertPoint(contBB);
                    return invoke;
                }
                return builder->CreateCall(evalMethod.first, args);
            }
        }
        return builder->getInt1(1);
    }
    std::string getCombinationalOperatorMethodName(TokenType op) {
        switch (op) {
        case TokenType::PLUS_EQ: return "operator+=";
        case TokenType::MINUS_EQ: return "operator-=";
        case TokenType::MUL_EQ: return "operator*=";
        case TokenType::DIV_EQ: return "operator/=";
        case TokenType::MOD_EQ: return "operator%=";
        case TokenType::BIT_X_EQ: return "operator$=";
        case TokenType::BIT_A_EQ: return "operator&=";
        case TokenType::BIT_O_EQ: return "operator|=";
        case TokenType::LSH_EQ: return "operator<<=";
        case TokenType::RSH_EQ: return "operator|>=";
        case TokenType::LRSH_EQ: return "operator:>=";
        case TokenType::RROT_EQ: return "operator|>>=";
        case TokenType::LROT_EQ: return "operator<<<=";
        default: return "";
        }
    }
    std::string getRoperatorMethodName(TokenType op) {
        switch (op) {
        case TokenType::MINUS: return "roperator-";
        case TokenType::DIV: return "roperator/";
        case TokenType::MOD: return "roperator%";
        case TokenType::POWER: return "roperator#^";
        case TokenType::RSHIFT: return "roperator|>";
        case TokenType::LOGICAL_RSHIFT: return "roperator:>";
        case TokenType::R_ROT: return "roperator|>>";
        case TokenType::LSHIFT: return "roperator<<";
        case TokenType::L_ROT: return "roperator<<<";
        default: return "";
        }
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
        case TokenType::INCREMENT: return "operator++";
        case TokenType::DECREMENT: return "operator--";
        case TokenType::BITWISE_NOT: return "operator~";
        case TokenType::RSHIFT: return "operator|>";
        case TokenType::LOGICAL_RSHIFT: return "operator:>";
        case TokenType::R_ROT: return "operator|>>";
        case TokenType::LSHIFT: return "operator<<";
        case TokenType::L_ROT: return "operator<<<";
        case TokenType::BITWISE_XOR: return "operator$";
        case TokenType::PIPE: return "operator|";
        case TokenType::AMPERSAND: return "operator&";
        default: return "";
        }
    }
    std::string getUnaryOperatorMethodName(TokenType op) {
        switch (op) {
        case TokenType::QNOT: return "operator!!";
        case TokenType::NOT: return "operator!";
        case TokenType::MINUS: return "operator-";
        case TokenType::INCREMENT: return "operator++";
        case TokenType::DECREMENT: return "operator--";
        case TokenType::BITWISE_NOT: return "operator~";
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
    llvm::Type* llvmTypeFor(std::string qcType);
    std::string lambdaName();
    std::string mangleName(const FuncDefNode& fn);
    std::unordered_map<std::string, llvm::Function*> functions;
    llvm::Function* currentFunction = nullptr;
    llvm::AllocaInst* createEntryAlloca(const std::string& name, llvm::Type* ty);
    llvm::Value* emitExpr(AnyNode node);
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

            if (type == "int" || type == "float" || type == "double" || type == "addr_t" || type == "long int" || type == "short int" ||
                type == "long double" || type == "nibble" || type == "byte") {
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
    void emitStmt(AnyNode node);
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
std::string resolve_path(const std::string& current_file, const std::string& include_path);
struct PreprocessResult {
    std::string clean_source;
    std::vector<std::string> dependency_paths;
    std::unordered_map<std::string, std::vector<std::string>> namespace_depends;
    std::unordered_map<std::string, std::vector<std::string>> included_namespaces;
    std::unordered_set<std::string> accessible_namespaces;
};

PreprocessResult preprocess_includes(const std::string& source, const std::string& current_file);
#endif
