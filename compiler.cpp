//////////////////////////////////////////////////////////////////////////////////////////////
// TOKENS
// ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
#include "compiler.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <ranges>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>
#ifdef ENABLE_LLVM
#include <llvm/Analysis/CGSCCPassManager.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/IntrinsicInst.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Mangler.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Linker/Linker.h>
#include <llvm/MC/TargetRegistry.h>
#ifndef __EMSCRIPTEN__
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#endif
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/TargetParser/Host.h>
#endif
#if defined(_WIN32) || defined(_WIN64)
#include <print>
#endif
bool no_main = false;
static bool random_seeded = false;

bool isCharInSet(char c, const std::string& charSet) {
    return charSet.find(c) != std::string::npos;
}
std::string strip_brace(const std::string& s) {
    std::string r = s;
    while (r.size() >= 2 && r.substr(r.size() - 2) == "[]") r = r.substr(0, r.size() - 2);
    return r;
}

std::string strip(const std::string& s) {
    std::string r = s;
    size_t pos;
    while ((pos = r.find("list<")) != std::string::npos && r.back() == '>') r = r.substr(pos + 5, r.size() - (pos + 6));
    while (r.size() >= 2 && r.substr(r.size() - 2) == "[]") r = r.substr(0, r.size() - 2);
    while ((pos = r.find("list<")) != std::string::npos && r.back() == '>') r = r.substr(pos + 5, r.size() - (pos + 6));
    return r;
}
bool loose;
std::string entrypointName = "main";
extern "C" const char _binary_runtime_ll_start[];
extern "C" const size_t _binary_runtime_ll_size;
namespace tkz {
//////////////////////////////////////////////////////////////////////////////////////////////
// POSITION
// /////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
Position::Position() {
}
std::string Position::arrow_string() const {
    if (Filetxt.empty() || index < 0 || index > (int)Filetxt.size()) { return "\n"; }

    int start = index;
    while (start > 0 && Filetxt[start - 1] != '\n') start--;

    int end = index;
    while (end < (int)Filetxt.size() && Filetxt[end] != '\n') end++;

    if (start < 0) start = 0;
    if (end < start) end = start;

    std::string line = Filetxt.substr(start, end - start);

    std::string result = "\n";
    result += line + "\n";

    int col = std::max(0, column);
    int len = std::max(1, length);

    result += std::string(col, ' ');
    result += std::string(len, '^');
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
    this->index++;
    this->column++;
    if (current_char == '\n') {
        this->line++;
        this->column = 0;
    }
}
std::string get_token_name(TokenType tok) {
    switch (tok) {
    case TokenType::INT: return "int";
    case TokenType::STRING: return "string";
    case TokenType::ADDR_T: return "addr_t";
    case TokenType::FLOAT: return "float";
    case TokenType::DOUBLE: return "double";
    case TokenType::CHAR: return "char";
    case TokenType::BOOL: return "bool";
    case TokenType::QBOOL: return "qbool";
    case TokenType::VOID: return "void";
    case TokenType::ENUM: return "enum";
    case TokenType::CLASS: return "class";
    case TokenType::STRUCT: return "struct";
    case TokenType::MAP: return "map";
    case TokenType::LIST: return "list";
    case TokenType::ARRAY: return "array";
    case TokenType::FUNC: return "func";
    case TokenType::DEF: return "def";

    case TokenType::IF: return "if";
    case TokenType::ELSE: return "else";
    case TokenType::SWITCH: return "switch";
    case TokenType::CASE: return "case";
    case TokenType::DEFAULT: return "default";
    case TokenType::BREAK: return "break";

    case TokenType::IDENTIFIER: return "identifier";
    case TokenType::KEYWORD: return "keyword";
    case TokenType::FSTRING: return "fstring";

    case TokenType::PLUS: return "+";
    case TokenType::MINUS: return "-";
    case TokenType::MUL: return "*";
    case TokenType::DIV: return "/";
    case TokenType::MOD: return "%";
    case TokenType::POWER: return "#^";

    case TokenType::PLUS_EQ: return "+=";
    case TokenType::MINUS_EQ: return "-=";
    case TokenType::MUL_EQ: return "*=";
    case TokenType::DIV_EQ: return "/=";
    case TokenType::MOD_EQ: return "%=";

    case TokenType::INCREMENT: return "++";
    case TokenType::DECREMENT: return "--";

    case TokenType::EQ: return "=";
    case TokenType::EQ_TO: return "==";
    case TokenType::NOT_EQ: return "!=";
    case TokenType::MORE: return ">";
    case TokenType::LESS: return "<";
    case TokenType::MORE_EQ: return ">=";
    case TokenType::LESS_EQ: return "<=";

    case TokenType::AND: return "&&&";
    case TokenType::OR: return "||";
    case TokenType::XOR: return "^";
    case TokenType::NOT: return "!";

    case TokenType::QAND: return "&&&";
    case TokenType::QOR: return "|||";
    case TokenType::QXOR: return "^^";
    case TokenType::QNOT: return "!!";
    case TokenType::QEQEQ: return "===";
    case TokenType::QNEQ: return "!==";
    case TokenType::COLLAPSE_AND: return "&|&";
    case TokenType::COLLAPSE_OR: return "|&|";

    case TokenType::LPAREN: return "(";
    case TokenType::RPAREN: return ")";
    case TokenType::LBRACE: return "{";
    case TokenType::RBRACE: return "}";
    case TokenType::LBRACKET: return "[";
    case TokenType::RBRACKET: return "]";
    case TokenType::COMMA: return ",";
    case TokenType::DOT: return ".";
    case TokenType::COLON: return ":";
    case TokenType::SEMICOLON: return ";";
    case TokenType::ARROW: return "->";
    case TokenType::AMPERSAND: return "&";
    case TokenType::STAR: return "*";
    case TokenType::SCOPE: return "::";
    case TokenType::LSHIFT: return "<<";
    case TokenType::RSHIFT: return ">>";
    case TokenType::R_ROT: return ">>>";
    case TokenType::L_ROT: return "<<<";
    case TokenType::BITWISE_XOR: return "$";
    case TokenType::BITWISE_NOT: return "~";
    case TokenType::LOGICAL_RSHIFT: return ":>";
    case TokenType::AT: return "@";
    case TokenType::PIPE: return "|";
    case TokenType::SIZEOF: return "sizeof";
    case TokenType::EOFT: return "<eof>";
    case TokenType::VARADIC: return "...";
    }

    return "<unknown token>";
}
Position Position::copy() {
    return Position(this->Filename, this->Filetxt, this->index, this->line, this->column);
}
Token::Token() {
}
Token::Token(TokenType t, std::string val, Position p) : type(t), value(val), pos(p) {
    this->pos.length = val.size();
}
std::string Token::print() const {
    if (this->value.empty()) {
        return std::format("{}", get_token_name(this->type));
    } else {
        return std::format("{}:{}", get_token_name(this->type), this->value);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ERRORS
// ///////////////////////////////////////////////////////////////////////////////////
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
    result += "Compile or Runtime Error: " + this->details + "\n";
    result += "File " + this->pos.Filename + ", line " + std::to_string(this->pos.line + 1) + ", col " + std::to_string(this->pos.column + 1) +
              "\n\n";
    result += this->pos.arrow_string();
    return result;
}
std::string MissingSemicolonError::as_string() {
    std::string result;
    result += "QC-MS99: Missing Semicolon on ";
    result += "File " + this->pos.Filename + ", line " + std::to_string(this->pos.line + 1) + ", col " + std::to_string(this->pos.column + 1) +
              "\n\n";
    result += this->pos.arrow_string();
    return result;
}
std::string InvalidSyntaxError::as_string() {
    std::string result;
    result += "Invalid Syntax: " + this->details + "\n";
    result += "File " + this->pos.Filename + ", line " + std::to_string(this->pos.line + 1) + ", col " + std::to_string(this->pos.column + 1) +
              "\n\n";
    result += this->pos.arrow_string();
    return result;
}
std::string IllegalCharError::as_string() {
    std::string result;
    result += "Illegal Charecter: " + this->details + "\n";
    result += "File " + this->pos.Filename + ", line " + std::to_string(this->pos.line + 1) + ", col " + std::to_string(this->pos.column + 1) +
              "\n\n";
    result += this->pos.arrow_string();
    return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// NODES
// ////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
AnyNode clone_node(const AnyNode& node) {
    return std::visit(
        [](auto arg) -> AnyNode {
            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, NumberNode>) {
                return NumberNode(arg.tok);
            } else if constexpr (std::is_same_v<T, StringNode>) {
                return StringNode(arg.tok);
            } else if constexpr (std::is_same_v<T, CharNode>) {
                return CharNode(arg.tok);
            } else if constexpr (std::is_same_v<T, BoolNode>) {
                return BoolNode(arg.tok);
            } else if constexpr (std::is_same_v<T, QBoolNode>) {
                return QBoolNode(arg.tok);
            } else if constexpr (std::is_same_v<T, QInNode>) {
                return QInNode();
            } else if constexpr (std::is_same_v<T, NullptrNode>) {
                return NullptrNode(arg.pos);
            } else if constexpr (std::is_same_v<T, RefVarDeclNode>) {
                return RefVarDeclNode(arg.type_tok, arg.var_name_tok, arg.target_tok, arg.pos);
            } else if constexpr (std::is_same_v<T, VarAccessNode*>) {
                return new VarAccessNode(arg->var_name_tok);
            } else if constexpr (std::is_same_v<T, UnaryOpNode*>) {
                return new UnaryOpNode(arg->op_tok, clone_node(arg->node), arg->is_postfix);
            } else if constexpr (std::is_same_v<T, PropertyAccessNode*>) {
                return new PropertyAccessNode(clone_node(*(arg->base)), arg->base_name_tok, arg->property_name);
            } else if constexpr (std::is_same_v<T, ArrayAccessNode*>) {
                std::vector<AnyNode> cloned_indices;
                for (auto& idx : arg->indices) { cloned_indices.push_back(clone_node(idx)); }
                return new ArrayAccessNode(clone_node(arg->base), cloned_indices);
            } else {
                throw std::runtime_error("Cannot clone complex node type");
            }
        },
        node);
}
std::string printAny(const AnyNode& node) {
    return std::visit(
        [](auto arg) -> std::string {
            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, NumberNode>) {
                return arg.print();
            } else if constexpr (std::is_same_v<T, StringNode>) {
                return arg.print();
            } else if constexpr (std::is_same_v<T, CharNode>) {
                return arg.print();
            } else if constexpr (std::is_same_v<T, BoolNode>) {
                return arg.print();
            } else if constexpr (std::is_same_v<T, QBoolNode>) {
                return arg.print();
            } else if constexpr (std::is_same_v<T, RefVarDeclNode>) {
                return arg.print();
            } else if constexpr (std::is_same_v<T, NullptrNode>) {
                return arg.print();
            } else if constexpr (std::is_same_v<T, BinOpNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, UnaryOpNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, StatementsNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, VarAccessNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, VarAssignNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, AssignExprNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, IfNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, TryCatchNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::monostate>) {
                return "";
            } else if constexpr (std::is_same_v<T, WhileNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, ForNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, ContinueNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, BreakNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, SwitchNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, FuncDefNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, CallNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, ReturnNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, ArrayDeclNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, ArrayLiteralNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, ArrayAccessNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, ListDeclNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, MethodCallNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, PropertyAccessNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, SpreadNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, ForeachNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, QIfNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, QSwitchNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, QInNode>) {
                return arg.print();
            } else if constexpr (std::is_same_v<T, MapDeclNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, ArrayAssignNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, RandomCallNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, SeedCallNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, FieldAssignNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, MapLiteralNode*>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, NamespaceNode*>) {
                std::string ret = arg->print() + "\n";
                for (auto& stmt : arg->body) { ret += printAny(stmt); }
                return ret;
            } else {
                return "<unknown>";
            }
        },
        node);
}
std::string VarAssignNode::print() const {
    return "(" + this->type_tok.print() + " " + this->var_name_tok.print() + " " + printAny(this->value_node) + ")";
}
std::string VarAccessNode::print() const {
    return "(" + this->var_name_tok.print() + ")";
}
NumberNode::NumberNode(Token tok) {
    this->tok = tok;
}
std::string CharNode::print() const {
    return this->tok.print();
}
std::string NumberNode::print() const {
    return this->tok.print();
}
std::string BinOpNode::print() const {
    return "(" + printAny(left_node) + " " + op_tok.print() + " " + printAny(right_node) + ")";
}
std::string UnaryOpNode::print() const {
    return std::string{"("} + this->op_tok.print() + ", " + printAny(this->node) + ")";
}
std::string StatementsNode::print() const {
    std::string res = "[";
    for (size_t i = 0; i < statements.size(); i++) {
        res += printAny(statements[i]);
        if (i < statements.size() - 1) { res += ", "; }
    }
    res += "]";
    return res;
}
std::string StringNode::print() const {
    return "(" + this->tok.print() + ")";
}
StringNode::StringNode(Token tok) {
    this->tok = tok;
}
BoolNode::BoolNode(Token tok) {
    this->tok = tok;
}
std::string BoolNode::print() const {
    return "(" + this->tok.print() + ")";
}
QBoolNode::QBoolNode(Token tok) {
    this->tok = tok;
}
std::string QBoolNode::print() const {
    return "(" + this->tok.print() + ")";
}
std::string IfNode::print() const {
    std::string res = "(if ";
    if (init.has_value()) { res += "init=" + printAny(init.value()) + "; "; }
    res += printAny(this->condition) + " " + this->then_branch->print();
    for (auto& p : this->elif_branches) { res += " elif " + printAny(p.first) + " " + p.second->print(); }
    if (this->else_branch) { res += " else " + this->else_branch->print(); }
    res += ")";
    return res;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// PARSE RESULT
// /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
AnyNode ParseResult::reg_node(AnyNode res) {
    return res;
}
AnyNode ParseResult::reg(Prs res_variant) {
    if (std::holds_alternative<Error*>(res_variant)) {
        this->error = std::get<Error*>(res_variant);
        return std::monostate{};
    }
    return std::visit(
        [this](auto arg) -> AnyNode {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::monostate> || std::is_same_v<T, Error*> || std::is_same_v<T, ParseResult>) {
                return AnyNode{std::monostate{}};
            } else if constexpr (std::is_same_v<T, UnaryOpNode>) {
                return AnyNode{new UnaryOpNode(arg)};
            } else if constexpr (std::is_constructible_v<AnyNode, T>) {
                return arg;
            } else {
                return AnyNode{std::monostate{}};
            }
        },
        res_variant);
}

Prs ParseResult::success(AnyNode node) {
    this->node = node;
    return std::visit(
        [](auto arg) -> Prs {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::monostate>) {
                return Prs{std::monostate{}};
            } else if constexpr (std::is_same_v<T, NumberNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, StringNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, CharNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, BoolNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, RefVarDeclNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, NullptrNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, BinOpNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, UnaryOpNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, VarAccessNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, VarAssignNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, AssignExprNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, StatementsNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, IfNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, TryCatchNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, BreakNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, SwitchNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, WhileNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ForNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ContinueNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, FuncDefNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, CallNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ReturnNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, MultiVarDeclNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, MultiReturnNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, MultiReturnNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ArrayDeclNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ArrayLiteralNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ArrayAccessNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ListDeclNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, MethodCallNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, PropertyAccessNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, SpreadNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ForeachNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, QBoolNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, QIfNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, QSwitchNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, QInNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, MapDeclNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ArrayAssignNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, RandomCallNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, SeedCallNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, FieldAssignNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, MapLiteralNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, NamespaceNode*>) {
                return Prs{arg};
            } else {
                return Prs{std::monostate{}};
            }
        },
        this->node);
}

Prs ParseResult::to_prs() {
    if (this->error) { return Prs{this->error}; }
    return std::visit(
        [](auto arg) -> Prs {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::monostate>) {
                return Prs{std::monostate{}};
            } else if constexpr (std::is_same_v<T, NumberNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, StringNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, CharNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, BoolNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, RefVarDeclNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, BinOpNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, UnaryOpNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, VarAccessNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, VarAssignNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, AssignExprNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, StatementsNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, IfNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, TryCatchNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, BreakNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, SwitchNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, WhileNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ForNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ContinueNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, FuncDefNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, CallNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ReturnNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, MultiVarDeclNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, MultiReturnNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, MultiReturnNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ArrayDeclNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ArrayLiteralNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ArrayAccessNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ListDeclNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, MethodCallNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, PropertyAccessNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, SpreadNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ForeachNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, QBoolNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, QIfNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, QInNode>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, MapDeclNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, ArrayAssignNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, RandomCallNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, SeedCallNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, FieldAssignNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, MapLiteralNode*>) {
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, NamespaceNode*>) {
                return Prs{arg};
            } else {
                return Prs{std::monostate{}};
            }
        },
        this->node);
}
void ParseResult::failure(Error* error) {
    this->error = error;
}
TokenType stringToTokenType(const std::string& str) {
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);

    static const std::unordered_map<std::string, TokenType> stringToEnum = {{"INT", TokenType::INT},
                                                                            {"STRING", TokenType::STRING},
                                                                            {"FLOAT", TokenType::FLOAT},
                                                                            {"DOUBLE", TokenType::DOUBLE},
                                                                            {"CHAR", TokenType::CHAR},
                                                                            {"MAP", TokenType::MAP},
                                                                            {"LIST", TokenType::LIST},
                                                                            {"ARRAY", TokenType::ARRAY},
                                                                            {"VOID", TokenType::VOID},
                                                                            {"ENUM", TokenType::ENUM},
                                                                            {"CLASS", TokenType::CLASS},
                                                                            {"STRUCT", TokenType::STRUCT},
                                                                            {"BOOL", TokenType::BOOL},
                                                                            {"QBOOL", TokenType::QBOOL},
                                                                            {"PLUS", TokenType::PLUS},
                                                                            {"R_ROT", TokenType::R_ROT},
                                                                            {"L_ROT", TokenType::L_ROT},
                                                                            {"AMPERSAND", TokenType::AMPERSAND},
                                                                            {"PIPE", TokenType::PIPE},
                                                                            {"RSHIFT", TokenType::RSHIFT},
                                                                            {"LSHIFT", TokenType::LSHIFT},
                                                                            {"BITWISE_XOR", TokenType::BITWISE_XOR},
                                                                            {"BITWISE_NOT", TokenType::BITWISE_NOT},
                                                                            {"LOGICAL_RSHIFT", TokenType::LOGICAL_RSHIFT},
                                                                            {"MINUS", TokenType::MINUS},
                                                                            {"MUL", TokenType::MUL},
                                                                            {"DIV", TokenType::DIV},
                                                                            {"SIZEOF", TokenType::SIZEOF},
                                                                            {"POWER", TokenType::POWER},
                                                                            {"LPAREN", TokenType::LPAREN},
                                                                            {"RPAREN", TokenType::RPAREN},
                                                                            {"SEMICOLON", TokenType::SEMICOLON},
                                                                            {"DEF", TokenType::DEF},
                                                                            {"INCREMENT", TokenType::INCREMENT},
                                                                            {"DECREMENT", TokenType::DECREMENT},
                                                                            {"IDENTIFIER", TokenType::IDENTIFIER},
                                                                            {"ADDR_T", TokenType::ADDR_T},
                                                                            {"KEYWORD", TokenType::KEYWORD},
                                                                            {"EQ", TokenType::EQ},
                                                                            {"EOFT", TokenType::EOFT},
                                                                            {"ARROW", TokenType::ARROW}};

    auto it = stringToEnum.find(upperStr);
    if (it != stringToEnum.end()) return it->second;
    throw std::invalid_argument("Unknown TokenType string: " + str);
}
//////////////////////////////////////////////////////////////////////////////////////////////
// PARSER
// ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
AnyNode Parser::default_value_for_type(const Token& type_tok, const Position& pos) {
    std::string type = type_tok.value;

    if (type == "short int") return AnyNode{NumberNode(Token(TokenType::INT, "0", pos))};
    if (type == "int") return AnyNode{NumberNode(Token(TokenType::INT, "0", pos))};
    if (type == "long int") return AnyNode{NumberNode(Token(TokenType::INT, "0", pos))};

    if (type == "float") return AnyNode{NumberNode(Token(TokenType::FLOAT, "0.0f", pos))};
    if (type == "double") return AnyNode{NumberNode(Token(TokenType::DOUBLE, "0.0", pos))};
    if (type == "long double") return AnyNode{NumberNode(Token(TokenType::DOUBLE, "0.0", pos))};
    if (type == "addr_t") return AnyNode{NumberNode(Token(TokenType::ADDR_T, "0", pos))};

    if (type == "string") return AnyNode{StringNode(Token(TokenType::STRING, "", pos))};
    if (type == "char") return AnyNode{CharNode(Token(TokenType::CHAR, "\0", pos))};
    if (type == "bool") return AnyNode{BoolNode(Token(TokenType::BOOL, "false", pos))};
    if (type == "qbool") return AnyNode{QBoolNode(Token(TokenType::QBOOL, "none", pos))};
    return AnyNode{std::monostate{}};
}
Parser::Parser(std::vector<Token> tokens, std::unordered_map<std::string, UserTypeInfo> user_types) {
    this->user_types = user_types;
    this->tokens = tokens;
    if (this->tokens.size() > index) { this->current_tok = this->tokens[index]; }
}
Token Parser::advance() {
    Position last_pos = this->current_tok.pos;

    if (index + 1 < tokens.size()) {
        ++index;
        this->current_tok = tokens[index];
    } else {
        this->current_tok = Token(TokenType::EOFT, "", last_pos);
        index = tokens.size();
    }
    return this->current_tok;
}
std::string Parser::qualify_name(const std::string& name) {
    if (namespaceStack.empty()) return name;
    std::string q;
    for (auto& ns : namespaceStack) {
        if (!q.empty()) q += "::";
        q += ns;
    }
    q += "::";
    q += name;
    return q;
}
// EDIT FOR NEW STUFF VVVVVVVVVVVVVVVVVVVV
Prs Parser::qif_expr() {
    ParseResult res;
    this->advance();

    if (this->current_tok.type != TokenType::LPAREN) {
        res.failure(new InvalidSyntaxError("QC-S001: Expected '(' after 'qif'", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    AnyNode condition = res.reg(this->logical_or());
    if (res.error) { return res.to_prs(); }

    if (this->current_tok.type != TokenType::RPAREN) {
        res.failure(new InvalidSyntaxError("QC-S002: Expected ')' after qif condition", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    if (this->current_tok.type != TokenType::LBRACE) {
        res.failure(new InvalidSyntaxError("QC-S003: Expected '{' after qif condition", this->current_tok.pos));
        return res.to_prs();
    }

    this->advance();

    std::vector<AnyNode> then_stmts;
    while (this->current_tok.type != TokenType::RBRACE && this->current_tok.type != TokenType::EOFT) {
        auto stmt = res.reg(this->statement());
        if (res.error) { return res.to_prs(); }
        then_stmts.push_back(stmt);
    }

    if (this->current_tok.type != TokenType::RBRACE) {
        res.failure(new InvalidSyntaxError("QC-S004: Expected '}'", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    auto then_branch = new StatementsNode(then_stmts, true);
    if (res.error) { return res.to_prs(); }

    std::vector<std::pair<AnyNode, StatementsNode*>> qelif_branches;

    while (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "qelif") {
        this->advance();
        if (this->current_tok.type != TokenType::LPAREN) {
            res.failure(new InvalidSyntaxError("QC-S005: Expected '(' after 'qelif'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        AnyNode qelif_cond = res.reg(this->logical_or());
        if (res.error) return res.to_prs();

        if (this->current_tok.type != TokenType::RPAREN) {
            res.failure(new InvalidSyntaxError("QC-S006: Expected ')' after qelif condition", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        if (this->current_tok.type != TokenType::LBRACE) {
            res.failure(new InvalidSyntaxError("QC-S007: Expected '{' after qelif condition", this->current_tok.pos));
            return res.to_prs();
        }

        this->advance();

        std::vector<AnyNode> qelif_stmts;
        while (this->current_tok.type != TokenType::RBRACE && this->current_tok.type != TokenType::EOFT) {
            auto stmt = res.reg(this->statement());
            if (res.error) return res.to_prs();
            qelif_stmts.push_back(stmt);
        }

        if (this->current_tok.type != TokenType::RBRACE) {
            res.failure(new InvalidSyntaxError("QC-S004: Expected '}'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        auto qelif_body = new StatementsNode(qelif_stmts, true);
        if (res.error) return res.to_prs();

        qelif_branches.emplace_back(qelif_cond, qelif_body);
    }

    StatementsNode* qelse_branch = nullptr;
    if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "qelse") {
        this->advance();
        if (this->current_tok.type != TokenType::LBRACE) {
            res.failure(new InvalidSyntaxError("QC-S008: Expected '{' after 'qelse'", this->current_tok.pos));
            return res.to_prs();
        }

        this->advance();

        std::vector<AnyNode> qelse_stmts;
        while (this->current_tok.type != TokenType::RBRACE && this->current_tok.type != TokenType::EOFT) {
            auto stmt = res.reg(this->statement());
            if (res.error) return res.to_prs();
            qelse_stmts.push_back(stmt);
        }

        if (this->current_tok.type != TokenType::RBRACE) {
            res.failure(new InvalidSyntaxError("QC-S004: Expected '}'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        qelse_branch = new StatementsNode(qelse_stmts, true);
        if (res.error) return res.to_prs();
    }
    return res.success(new QIfNode(std::nullopt, condition, then_branch, qelif_branches, qelse_branch));
}
Prs Parser::if_expr() {
    auto has_semicolon_before_closing_paren = [this]() -> bool {
        size_t idx = index;
        int depth = 0;
        for (size_t i = idx; i < this->tokens.size(); ++i) {
            const Token& t = this->tokens[i];
            if (t.type == TokenType::LPAREN) {
                ++depth;
            } else if (t.type == TokenType::RPAREN) {
                if (depth == 0) { return false; }
                --depth;
            } else if (t.type == TokenType::SEMICOLON && depth == 0) {
                return true;
            }
        }
        return false;
    };
    ParseResult res;
    if (!(this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "if")) {
        res.failure(new InvalidSyntaxError("QC-S009: Expected 'if'", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    if (this->current_tok.type != TokenType::LPAREN) {
        res.failure(new InvalidSyntaxError("QC-S010: Expected '(' after 'if'", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    std::optional<AnyNode> init_node = std::nullopt;

    if (has_semicolon_before_closing_paren()) {
        if (this->current_tok.type == TokenType::KEYWORD &&
            (this->current_tok.value == "const" || this->current_tok.value == "int" || this->current_tok.value == "float" ||
             this->current_tok.value == "double" || this->current_tok.value == "bool" || this->current_tok.value == "string" ||
             this->current_tok.value == "char")) {

            bool is_const = false;
            Token tok = this->current_tok;
            if (tok.value == "const") {
                is_const = true;
                this->advance();
                tok = this->current_tok;
                if (tok.type != TokenType::KEYWORD) {
                    res.failure(new InvalidSyntaxError("QC-S011: Expected type after 'const' in if-init", this->current_tok.pos));
                    return res.to_prs();
                }
            }
            Token type_tok = tok;
            this->advance();
            if (this->current_tok.type == TokenType::AMPERSAND) {
                this->advance();
                type_tok.value += "&";
            }

            while (this->current_tok.type == TokenType::MUL) {
                this->advance();
                type_tok.value += "*";
            }
            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(new InvalidSyntaxError("QC-S012: Expected identifier in if-init", this->current_tok.pos));
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
                    res.failure(new InvalidSyntaxError("QC-S013: const variables must be initialized in "
                                                       "if-init",
                                                       var_name.pos));
                    return res.to_prs();
                }
                value = default_value_for_type(type_tok, var_name.pos);
            }

            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(new InvalidSyntaxError("QC-S014: Expected ';' after if-init declaration", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            init_node = AnyNode{new VarAssignNode(is_const, type_tok, var_name, value)};
        } else {
            AnyNode expr_init = res.reg(this->assignment_expr());
            if (res.error) return res.to_prs();

            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(new InvalidSyntaxError("QC-S015: Expected ';' after if-init expression", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            init_node = expr_init;
        }
    }

    AnyNode condition = res.reg(this->logical_or());
    if (res.error) return res.to_prs();

    if (this->current_tok.type != TokenType::RPAREN) {
        res.failure(new InvalidSyntaxError("QC-S016: Expected ')' after condition", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    StatementsNode* then_branch;
    if (!parse_block_into(then_branch, res)) return res.to_prs();

    std::vector<std::pair<AnyNode, StatementsNode*>> elifs;
    StatementsNode* else_branch = nullptr;

    while (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "else") {
        this->advance();
        if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "if") {
            this->advance();
            if (this->current_tok.type != TokenType::LPAREN) {
                res.failure(new InvalidSyntaxError("QC-S017: Expected '(' after 'else if'", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            AnyNode elif_cond = res.reg(this->logical_or());
            if (res.error) return res.to_prs();
            if (this->current_tok.type != TokenType::RPAREN) {
                res.failure(new InvalidSyntaxError("QC-S018: Expected ')' after 'else if' condition", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            StatementsNode* elif_block;
            if (!parse_block_into(elif_block, res)) return res.to_prs();
            elifs.emplace_back(elif_cond, elif_block);
            continue;
        } else {
            if (!parse_block_into(else_branch, res)) return res.to_prs();
            break;
        }
    }

    auto ifnode = new IfNode(init_node, condition, then_branch, elifs, else_branch);
    return res.success(ifnode);
}
Prs Parser::try_catch_expr() {
    ParseResult res;
    if (!(this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "try")) {
        res.failure(new InvalidSyntaxError("QC-S030: Expected 'try'", this->current_tok.pos));
        return res.to_prs();
    }
    Token try_tok = this->current_tok;
    this->advance();
    StatementsNode* try_body;
    if (!parse_block_into(try_body, res)) return res.to_prs();
    if (!(this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "catch")) {
        res.failure(new InvalidSyntaxError("QC-S031: Expected 'catch' after try block", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();
    if (this->current_tok.type != TokenType::LPAREN) {
        res.failure(new InvalidSyntaxError("QC-S032: Expected '(' after 'catch'", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();
    if (this->current_tok.type != TokenType::KEYWORD && this->current_tok.type != TokenType::IDENTIFIER) {
        res.failure(new InvalidSyntaxError("QC-S033: Expected type in catch declaration", this->current_tok.pos));
        return res.to_prs();
    }
    Token type_tok = this->current_tok;
    this->advance();
    if (this->current_tok.type == TokenType::AMPERSAND) {
        this->advance();
        type_tok.value += "&";
    }

    while (this->current_tok.type == TokenType::MUL) {
        this->advance();
        type_tok.value += "*";
    }
    std::string catch_type = type_tok.value;
    if (this->current_tok.type != TokenType::IDENTIFIER) {
        res.failure(new InvalidSyntaxError("QC-S034: Expected variable name in catch declaration", this->current_tok.pos));
        return res.to_prs();
    }
    Token var_tok = this->current_tok;
    std::string catch_var = var_tok.value;
    this->advance();
    if (this->current_tok.type != TokenType::RPAREN) {
        res.failure(new InvalidSyntaxError("QC-S035: Expected ')' after catch variable", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();
    StatementsNode* catch_body;
    if (!parse_block_into(catch_body, res)) return res.to_prs();
    auto try_catch_node = new TryCatchNode(try_body, catch_var, catch_type, catch_body, try_tok, try_tok.pos);

    return res.success(try_catch_node);
}
Prs Parser::switch_stmt() {
    ParseResult res;
    if (!(current_tok.type == TokenType::KEYWORD && current_tok.value == "switch")) {
        res.failure(new InvalidSyntaxError("QC-S019: Expected 'switch'", current_tok.pos));
        return res.to_prs();
    }
    advance();

    if (current_tok.type != TokenType::LPAREN) {
        res.failure(new InvalidSyntaxError("QC-S020: Expected '(' after 'switch'", current_tok.pos));
        return res.to_prs();
    }
    advance();

    AnyNode value = res.reg(this->logical_or());
    if (res.error) return res.to_prs();

    if (current_tok.type != TokenType::RPAREN) {
        res.failure(new InvalidSyntaxError("QC-S021: Expected ')' after switch expression", current_tok.pos));
        return res.to_prs();
    }
    advance();

    if (current_tok.type != TokenType::LBRACE) {
        res.failure(new InvalidSyntaxError("QC-S022: Expected '{' after switch(...)", current_tok.pos));
        return res.to_prs();
    }
    advance();

    std::vector<SwitchNode::Section> sections;

    while (this->current_tok.type != TokenType::RBRACE && this->current_tok.type != TokenType::EOFT) {
        SwitchNode::Section section;
        bool saw_label = false;
        while (this->current_tok.type == TokenType::KEYWORD && (this->current_tok.value == "case" || this->current_tok.value == "default")) {

            saw_label = true;

            if (current_tok.value == "default") {
                this->advance();
                if (current_tok.type != TokenType::COLON && current_tok.type != TokenType::SEMICOLON) {}
                section.is_default = true;
                this->advance();
                break;
            } else {
                advance();
                AnyNode case_expr = res.reg(this->logical_or());
                if (res.error) return res.to_prs();

                if (current_tok.type != TokenType::COLON) {
                    res.failure(new InvalidSyntaxError("QC-S023: Expected ':' after case label", current_tok.pos));
                    return res.to_prs();
                }
                advance();

                section.cases.push_back(CaseLabel{case_expr});
            }
        }

        if (!saw_label) {
            res.failure(new InvalidSyntaxError("QC-S024: Expected 'case' or 'default' inside switch", current_tok.pos));
            return res.to_prs();
        }
        std::vector<AnyNode> stmts;
        while (current_tok.type != TokenType::RBRACE &&
               !(current_tok.type == TokenType::KEYWORD && (current_tok.value == "case" || current_tok.value == "default"))) {

            Prs st = this->statement();
            if (std::holds_alternative<Error*>(st)) {
                res.failure(std::get<Error*>(st));
                return res.to_prs();
            }
            AnyNode any_stmt = std::visit(
                [](auto arg) -> AnyNode {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_constructible_v<AnyNode, T>) { return AnyNode(arg); }
                    return std::monostate{};
                },
                st);
            stmts.push_back(any_stmt);
        }

        section.body = new StatementsNode(stmts, true);
        sections.push_back(section);
    }

    if (current_tok.type != TokenType::RBRACE) {
        res.failure(new InvalidSyntaxError("QC-S025: Expected '}' after switch body", current_tok.pos));
        return res.to_prs();
    }
    advance();

    auto sw = new SwitchNode();
    sw->value = value;
    sw->sections = sections;
    return res.success(sw);
}
Prs Parser::qswitch_stmt() {
    ParseResult res;
    this->advance();

    if (this->current_tok.type != TokenType::LPAREN) {
        res.failure(new InvalidSyntaxError("QC-S026: Expected '(' after 'qswitch'", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    AnyNode value = res.reg(this->logical_or());
    if (res.error) return res.to_prs();

    if (this->current_tok.type != TokenType::RPAREN) {
        res.failure(new InvalidSyntaxError("QC-S027: Expected ')' after qswitch value", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    if (this->current_tok.type != TokenType::LBRACE) {
        res.failure(new InvalidSyntaxError("QC-S028: Expected '{' after qswitch", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    StatementsNode* case_t = nullptr;
    StatementsNode* case_f = nullptr;
    StatementsNode* case_n = nullptr;
    StatementsNode* case_b = nullptr;

    while (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "case") {
        this->advance();

        if (this->current_tok.type != TokenType::IDENTIFIER) {
            res.failure(new InvalidSyntaxError("QC-S029: Expected case label (t, f, n, or b)", this->current_tok.pos));
            return res.to_prs();
        }

        std::string case_label = this->current_tok.value;
        this->advance();

        if (this->current_tok.type != TokenType::COLON) {
            res.failure(new InvalidSyntaxError("QC-S023: Expected ':' after case label", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        std::vector<AnyNode> case_stmts;
        while (this->current_tok.type != TokenType::KEYWORD || (this->current_tok.value != "case" && this->current_tok.value != "break")) {

            if (this->current_tok.type == TokenType::RBRACE) break;
            if (this->current_tok.type == TokenType::EOFT) break;

            auto stmt = res.reg(this->statement());
            if (res.error) return res.to_prs();
            case_stmts.push_back(stmt);
        }

        if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "break") {
            this->advance();
            if (this->current_tok.type == TokenType::SEMICOLON) { this->advance(); }
        }

        auto case_body = new StatementsNode(case_stmts, true);

        if (case_label == "t") {
            case_t = case_body;
        } else if (case_label == "f") {
            case_f = case_body;
        } else if (case_label == "n") {
            case_n = case_body;
        } else if (case_label == "b") {
            case_b = case_body;
        } else {
            res.failure(new InvalidSyntaxError("QC-S030: Invalid case label (must be t, f, n, or b)", this->current_tok.pos));
            return res.to_prs();
        }
    }

    if (this->current_tok.type != TokenType::RBRACE) {
        res.failure(new InvalidSyntaxError("QC-S031: Expected '}' after qswitch", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    return res.success(new QSwitchNode(value, case_t, case_f, case_n, case_b));
}
Prs Parser::while_stmt() {
    ParseResult res;
    if (!(current_tok.type == TokenType::KEYWORD && current_tok.value == "while")) {
        res.failure(new InvalidSyntaxError("QC-S032: Expected 'while'", current_tok.pos));
        return res.to_prs();
    }
    advance();

    if (current_tok.type != TokenType::LPAREN) {
        res.failure(new InvalidSyntaxError("QC-S033: Expected '(' after 'while'", current_tok.pos));
        return res.to_prs();
    }
    advance();

    AnyNode cond = res.reg(this->logical_or());
    if (res.error) return res.to_prs();

    if (current_tok.type != TokenType::RPAREN) {
        res.failure(new InvalidSyntaxError("QC-S034: Expected ')' after while condition", current_tok.pos));
        return res.to_prs();
    }
    advance();

    StatementsNode* body;
    if (!this->parse_block_into(body, res)) return res.to_prs();

    auto wn = new WhileNode(cond, body);
    return res.success(wn);
}
Prs Parser::for_stmt() {
    ParseResult res;
    Token type_tok;
    if (!(this->current_tok.type == TokenType::KEYWORD && current_tok.value == "for")) {
        res.failure(new InvalidSyntaxError("QC-S035: Expected 'for'", current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    if (this->current_tok.type != TokenType::LPAREN) {
        res.failure(new InvalidSyntaxError("QC-S036: Expected '(' after 'for'", current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    std::optional<AnyNode> init;
    std::optional<AnyNode> update;
    AnyNode condition;

    if (this->current_tok.type != TokenType::SEMICOLON) {
        if (this->current_tok.type == TokenType::KEYWORD &&
            (this->current_tok.value == "const" || this->current_tok.value == "int" || this->current_tok.value == "float" ||
             this->current_tok.value == "double" || this->current_tok.value == "bool" || this->current_tok.value == "qbool" ||
             this->current_tok.value == "string" || this->current_tok.value == "char")) {

            bool is_const = false;
            Token tok = current_tok;

            if (tok.value == "const") {
                is_const = true;
                advance();
                tok = current_tok;
                if (tok.type != TokenType::KEYWORD) {
                    res.failure(new InvalidSyntaxError("QC-S011:  Expected type after 'const' in for-init", current_tok.pos));
                    return res.to_prs();
                }
            }

            type_tok = tok;
            advance();
            if (this->current_tok.type == TokenType::AMPERSAND) {
                this->advance();
                type_tok.value += "&";
            }

            while (this->current_tok.type == TokenType::MUL) {
                this->advance();
                type_tok.value += "*";
            }
            if (current_tok.type != TokenType::IDENTIFIER) {
                res.failure(new InvalidSyntaxError("QC-S038: Expected identifier in for-init", current_tok.pos));
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
                    res.failure(new InvalidSyntaxError("QC-S039: const variables must be initialized in "
                                                       "for-init",
                                                       var_name.pos));
                    return res.to_prs();
                }
                value = default_value_for_type(type_tok, var_name.pos);
            }

            init = AnyNode{new VarAssignNode(is_const, type_tok, var_name, value)};
        } else {
            AnyNode expr_init = res.reg(this->assignment_expr());
            if (res.error) return res.to_prs();
            init = expr_init;
        }
    }

    if (current_tok.type != TokenType::SEMICOLON) {
        res.failure(new InvalidSyntaxError("QC-S040: Expected ';' after for-init", current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    if (current_tok.type == TokenType::SEMICOLON) {
        condition = AnyNode{BoolNode(Token(TokenType::BOOL, "true", current_tok.pos))};
    } else {
        condition = res.reg(this->logical_or());
        if (res.error) return res.to_prs();
    }

    if (current_tok.type != TokenType::SEMICOLON) {
        res.failure(new InvalidSyntaxError("QC-S041: Expected ';' after for condition", current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    if (current_tok.type != TokenType::RPAREN) {
        AnyNode upd_expr = res.reg(this->assignment_expr());
        if (res.error) return res.to_prs();
        update = upd_expr;
    }

    if (current_tok.type != TokenType::RPAREN) {
        res.failure(new InvalidSyntaxError("QC-S042: Expected ')' after for header", current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    auto parse_block = [&](StatementsNode*& out_block) -> bool {
        if (this->current_tok.type == TokenType::LBRACE) {
            this->advance();
            std::vector<AnyNode> stmts;
            while (this->current_tok.type != TokenType::RBRACE && this->current_tok.type != TokenType::EOFT) {
                Prs st = this->statement();
                if (std::holds_alternative<Error*>(st)) {
                    res.failure(std::get<Error*>(st));
                    return false;
                }
                AnyNode any_stmt = std::visit(
                    [](auto arg) -> AnyNode {
                        using T = std::decay_t<decltype(arg)>;
                        if constexpr (std::is_constructible_v<AnyNode, T>) { return AnyNode(arg); }
                        return std::monostate{};
                    },
                    st);
                stmts.push_back(any_stmt);
            }
            if (this->current_tok.type != TokenType::RBRACE) {
                res.failure(new InvalidSyntaxError("QC-S043: Expected '}' after for body", this->current_tok.pos));
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
            AnyNode any_stmt = std::visit(
                [](auto arg) -> AnyNode {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_constructible_v<AnyNode, T>) { return AnyNode(arg); }
                    return std::monostate{};
                },
                st);
            std::vector<AnyNode> stmts;
            stmts.push_back(any_stmt);
            out_block = new StatementsNode(stmts, true);
            return true;
        }
    };

    StatementsNode* body;
    if (!parse_block(body)) return res.to_prs();

    auto fn = new ForNode(init, condition, update, body);
    return res.success(fn);
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

        auto parse_arg = [&]() -> AnyNode {
            if (this->current_tok.type == TokenType::AT) {
                this->advance();
                AnyNode expr = res.reg(this->logical_or());
                if (res.error) return AnyNode{};
                return new SpreadNode(expr);
            } else {
                return res.reg(this->logical_or());
            }
        };

        AnyNode arg = parse_arg();
        if (res.error) return res.to_prs();
        args.push_back(arg);

        while (this->current_tok.type == TokenType::COMMA) {
            this->advance();
            arg = parse_arg();
            if (res.error) return res.to_prs();
            args.push_back(arg);
        }
    }

    if (this->current_tok.type != TokenType::RPAREN) {
        res.failure(new InvalidSyntaxError("QC-S044: Expected ')' after function arguments", this->current_tok.pos));
        return res.to_prs();
    }

    this->advance();

    return res.success(new CallNode(node_to_call, args));
}
Prs Parser::qout_expr() {
    ParseResult res;
    AnyNode left = res.reg(this->logical_or());
    if (res.error) return res.to_prs();

    return res.success(left);
}
Prs Parser::array_literal() {
    ParseResult res;
    Position start_pos = this->current_tok.pos;

    this->advance();

    std::vector<AnyNode> elements;

    if (this->current_tok.type != TokenType::RBRACKET) {
        if (this->current_tok.type == TokenType::AT) {
            this->advance();
            AnyNode spread_expr = res.reg(this->logical_or());
            if (res.error) return res.to_prs();

            elements.push_back(new SpreadNode(spread_expr));
        } else {
            AnyNode elem = res.reg(this->logical_or());
            if (res.error) return res.to_prs();
            elements.push_back(elem);
        }

        while (this->current_tok.type == TokenType::COMMA) {
            this->advance();

            if (this->current_tok.type == TokenType::AT) {
                this->advance();
                AnyNode spread_expr = res.reg(this->logical_or());
                if (res.error) return res.to_prs();

                elements.push_back(new SpreadNode(spread_expr));
            } else {
                AnyNode elem = res.reg(this->logical_or());
                if (res.error) return res.to_prs();
                elements.push_back(elem);
            }
        }
    }

    if (this->current_tok.type != TokenType::RBRACKET) {
        res.failure(new InvalidSyntaxError("QC-S045: Expected ']' in array literal", this->current_tok.pos));
        return res.to_prs();
    }

    this->advance();

    return res.success(new ArrayLiteralNode(elements, start_pos));
}
Prs Parser::atom() {
    ParseResult res;
    Token tok = this->current_tok;
    if (tok.type == TokenType::LBRACE) {
        ParseResult res2;
        Position start_pos = this->current_tok.pos;
        this->advance();

        if (this->current_tok.type == TokenType::RBRACE) {
            this->advance();
            std::vector<std::pair<AnyNode, AnyNode>> pairs;
            return res2.success(new MapLiteralNode(pairs, start_pos));
        }

        auto first_key_expr = res2.reg(this->logical_or());
        if (res2.error) return res2.to_prs();

        if (this->current_tok.type == TokenType::COLON) {
            this->advance();

            AnyNode first_val_expr = res2.reg(this->logical_or());
            if (res2.error) return res2.to_prs();

            std::vector<std::pair<AnyNode, AnyNode>> pairs;
            pairs.emplace_back(first_key_expr, first_val_expr);

            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();

                AnyNode key_expr = res2.reg(this->logical_or());
                if (res2.error) return res2.to_prs();

                if (this->current_tok.type != TokenType::COLON) {
                    res2.failure(new InvalidSyntaxError("QC-S046: Expected ':' in map literal", this->current_tok.pos));
                    return res2.to_prs();
                }
                this->advance();

                AnyNode val_expr = res2.reg(this->logical_or());
                if (res2.error) return res2.to_prs();

                pairs.emplace_back(key_expr, val_expr);
            }

            if (this->current_tok.type != TokenType::RBRACE) {
                res2.failure(new InvalidSyntaxError("QC-S047: Expected '}' at end of map literal", this->current_tok.pos));
                return res2.to_prs();
            }
            this->advance();

            return res2.success(new MapLiteralNode(pairs, start_pos));
        } else {
            std::vector<AnyNode> elements;
            elements.push_back(first_key_expr);

            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                AnyNode e2 = res2.reg(this->logical_or());
                if (res2.error) return res2.to_prs();
                elements.push_back(e2);
            }

            if (this->current_tok.type != TokenType::RBRACE) {
                res2.failure(new InvalidSyntaxError("QC-S048: Expected '}' in initializer list", this->current_tok.pos));
                return res2.to_prs();
            }
            this->advance();

            return res2.success(new ArrayLiteralNode(elements, start_pos));
        }
    }
    if (tok.type == TokenType::LBRACKET) return this->array_literal();
    if (current_tok.value == "qin") {
        this->advance();

        return this->qin_expr();
    }

    if (tok.type == TokenType::INT || tok.type == TokenType::FLOAT || tok.type == TokenType::DOUBLE || tok.type == TokenType::ADDR_T) {
        this->advance();
        return res.success(NumberNode(tok));
    } else if (tok.type == TokenType::STRING) {
        this->advance();
        return res.success(StringNode(tok));
    } else if (tok.type == TokenType::CHAR) {
        this->advance();
        return res.success(CharNode(tok));
    } else if (tok.type == TokenType::BOOL) {
        this->advance();
        return res.success(BoolNode(tok));
    } else if (tok.type == TokenType::QBOOL) {
        this->advance();
        return res.success(QBoolNode(tok));
    } else if (tok.type == TokenType::AT) {
        Token op = tok;
        this->advance();

        AnyNode value = res.reg(this->atom());
        if (res.error) return res.to_prs();

        return res.success(new SpreadNode(value));
    } else if (tok.type == TokenType::KEYWORD && tok.value == "nullptr") {
        this->advance();
        return res.success(NullptrNode(tok.pos));
    } else if (tok.type == TokenType::IDENTIFIER) {
        std::string name = tok.value;
        Position pos = tok.pos;

        this->advance();

        while (this->current_tok.type == TokenType::SCOPE) {
            this->advance();

            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(new InvalidSyntaxError("QC-N001: Expected identifier or namespace name after '::'", this->current_tok.pos));
                return res.to_prs();
            }

            name += "::" + this->current_tok.value;
            pos = this->current_tok.pos;
            this->advance();
        }

        Token ident(TokenType::IDENTIFIER, name, pos);

        AnyNode base = new VarAccessNode(ident);

        if (this->current_tok.type == TokenType::LPAREN) {
            base = res.reg(this->call(base));
            if (res.error) return res.to_prs();
        }

        if (this->current_tok.type == TokenType::LBRACKET) {
            std::vector<AnyNode> indices;

            while (this->current_tok.type == TokenType::LBRACKET) {
                this->advance();
                AnyNode index = res.reg(this->logical_or());
                if (res.error) return res.to_prs();

                if (this->current_tok.type != TokenType::RBRACKET) {
                    res.failure(new InvalidSyntaxError("QC-S049: Expected ']'", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();

                indices.push_back(index);
            }

            base = new ArrayAccessNode(base, indices);
        }

        while (this->current_tok.type == TokenType::DOT || this->current_tok.type == TokenType::ARROW) {

            if (this->current_tok.type == TokenType::ARROW) {
                this->advance();

                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(new InvalidSyntaxError("Expected property or method name after '->'", this->current_tok.pos));
                    return res.to_prs();
                }

                Token property_name = this->current_tok;
                this->advance();
                Token base_name_tok;
                if (auto var = std::get_if<VarAccessNode*>(&base)) {
                    base_name_tok = (*var)->var_name_tok;
                } else {
                    base_name_tok = Token(TokenType::IDENTIFIER, "", property_name.pos);
                }

                auto deref = new UnaryOpNode(Token(TokenType::MUL, "*", property_name.pos), base);

                if (this->current_tok.type == TokenType::LPAREN) {
                    this->advance();

                    std::vector<AnyNode> args;
                    if (this->current_tok.type != TokenType::RPAREN) {
                        while (true) {
                            if (this->current_tok.type == TokenType::AT) {
                                this->advance();
                                AnyNode expr = res.reg(this->logical_or());
                                if (res.error) return res.to_prs();
                                args.push_back(new SpreadNode(expr));
                            } else {
                                AnyNode arg = res.reg(this->logical_or());
                                if (res.error) return res.to_prs();
                                args.push_back(arg);
                            }
                            if (this->current_tok.type != TokenType::COMMA) break;
                            this->advance();
                        }
                    }

                    if (this->current_tok.type != TokenType::RPAREN) {
                        res.failure(new InvalidSyntaxError("Expected ')' after method arguments", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();

                    base = new MethodCallNode(deref, property_name, args);
                } else {
                    base = new PropertyAccessNode(deref, base_name_tok, property_name);
                }
            } else if (this->current_tok.type == TokenType::DOT) {
                this->advance();

                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(new InvalidSyntaxError("Expected property or method name after '.'", this->current_tok.pos));
                    return res.to_prs();
                }

                Token property_name = this->current_tok;
                this->advance();

                if (this->current_tok.type == TokenType::LPAREN) {
                    this->advance();
                    std::vector<AnyNode> args;

                    if (this->current_tok.type != TokenType::RPAREN) {
                        while (true) {
                            if (this->current_tok.type == TokenType::AT) {
                                this->advance();
                                AnyNode expr = res.reg(this->logical_or());
                                if (res.error) return res.to_prs();
                                args.push_back(new SpreadNode(expr));
                            } else {
                                AnyNode arg = res.reg(this->logical_or());
                                if (res.error) return res.to_prs();
                                args.push_back(arg);
                            }
                            if (this->current_tok.type != TokenType::COMMA) break;
                            this->advance();
                        }
                    }

                    if (this->current_tok.type != TokenType::RPAREN) {
                        res.failure(new InvalidSyntaxError("QC-S044: Expected ')' after function arguments", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();

                    base = new MethodCallNode(base, property_name, args);
                } else {
                    base = new PropertyAccessNode(base, ident, property_name);
                }

                while (this->current_tok.type == TokenType::LBRACKET) {
                    std::vector<AnyNode> indices;
                    while (this->current_tok.type == TokenType::LBRACKET) {
                        this->advance();
                        AnyNode index = res.reg(this->logical_or());
                        if (res.error) return res.to_prs();
                        if (this->current_tok.type != TokenType::RBRACKET) {
                            res.failure(new InvalidSyntaxError("QC-S049: Expected ']'", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                        indices.push_back(index);
                    }
                    base = new ArrayAccessNode(base, indices);
                }
            }
        }
        if (this->current_tok.type == TokenType::INCREMENT || this->current_tok.type == TokenType::DECREMENT) {
            Token op = this->current_tok;
            this->advance();
            AnyNode value_node = new UnaryOpNode(op, base);
            return res.success(value_node);
        }
        while (true) {
            if (this->current_tok.type == TokenType::LPAREN) {
                base = res.reg(this->call(base));
            } else if (this->current_tok.type == TokenType::LBRACKET) {
                std::vector<AnyNode> indices;
                while (this->current_tok.type == TokenType::LBRACKET) {
                    this->advance();
                    AnyNode index = res.reg(this->logical_or());
                    if (res.error) return res.to_prs();
                    if (this->current_tok.type != TokenType::RBRACKET) {
                        res.failure(new InvalidSyntaxError("QC-S049: Expected ']'", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                    indices.push_back(index);
                }
                base = new ArrayAccessNode(base, indices);
            } else if (this->current_tok.type == TokenType::DOT || this->current_tok.type == TokenType::ARROW) {
                if (this->current_tok.type == TokenType::ARROW) {
                    this->advance();

                    if (this->current_tok.type != TokenType::IDENTIFIER) {
                        res.failure(new InvalidSyntaxError("Expected property or method name after '->'", this->current_tok.pos));
                        return res.to_prs();
                    }

                    Token property_name = this->current_tok;
                    this->advance();
                    Token base_name_tok;
                    if (auto var = std::get_if<VarAccessNode*>(&base)) {
                        base_name_tok = (*var)->var_name_tok;
                    } else {
                        base_name_tok = Token(TokenType::IDENTIFIER, "", property_name.pos);
                    }

                    auto deref = new UnaryOpNode(Token(TokenType::MUL, "*", property_name.pos), base);

                    if (this->current_tok.type == TokenType::LPAREN) {
                        this->advance();

                        std::vector<AnyNode> args;
                        if (this->current_tok.type != TokenType::RPAREN) {
                            while (true) {
                                if (this->current_tok.type == TokenType::AT) {
                                    this->advance();
                                    AnyNode expr = res.reg(this->logical_or());
                                    if (res.error) return res.to_prs();
                                    args.push_back(new SpreadNode(expr));
                                } else {
                                    AnyNode arg = res.reg(this->logical_or());
                                    if (res.error) return res.to_prs();
                                    args.push_back(arg);
                                }
                                if (this->current_tok.type != TokenType::COMMA) break;
                                this->advance();
                            }
                        }

                        if (this->current_tok.type != TokenType::RPAREN) {
                            res.failure(new InvalidSyntaxError("Expected ')' after method arguments", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();

                        base = new MethodCallNode(deref, property_name, args);
                    } else {
                        base = new PropertyAccessNode(deref, base_name_tok, property_name);
                    }
                } else if (this->current_tok.type == TokenType::DOT) {
                    this->advance();

                    if (this->current_tok.type != TokenType::IDENTIFIER) {
                        res.failure(new InvalidSyntaxError("Expected property or method name after '.'", this->current_tok.pos));
                        return res.to_prs();
                    }

                    Token property_name = this->current_tok;
                    this->advance();

                    if (this->current_tok.type == TokenType::LPAREN) {
                        this->advance();
                        std::vector<AnyNode> args;

                        if (this->current_tok.type != TokenType::RPAREN) {
                            while (true) {
                                if (this->current_tok.type == TokenType::AT) {
                                    this->advance();
                                    AnyNode expr = res.reg(this->logical_or());
                                    if (res.error) return res.to_prs();
                                    args.push_back(new SpreadNode(expr));
                                } else {
                                    AnyNode arg = res.reg(this->logical_or());
                                    if (res.error) return res.to_prs();
                                    args.push_back(arg);
                                }
                                if (this->current_tok.type != TokenType::COMMA) break;
                                this->advance();
                            }
                        }

                        if (this->current_tok.type != TokenType::RPAREN) {
                            res.failure(new InvalidSyntaxError("QC-S044: Expected ')' after function arguments", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();

                        base = new MethodCallNode(base, property_name, args);
                    } else {
                        base = new PropertyAccessNode(base, ident, property_name);
                    }

                    while (this->current_tok.type == TokenType::LBRACKET) {
                        std::vector<AnyNode> indices;
                        while (this->current_tok.type == TokenType::LBRACKET) {
                            this->advance();
                            AnyNode index = res.reg(this->logical_or());
                            if (res.error) return res.to_prs();
                            if (this->current_tok.type != TokenType::RBRACKET) {
                                res.failure(new InvalidSyntaxError("QC-S049: Expected ']'", this->current_tok.pos));
                                return res.to_prs();
                            }
                            this->advance();
                            indices.push_back(index);
                        }
                        base = new ArrayAccessNode(base, indices);
                    }
                }
            } else if (this->current_tok.type == TokenType::INCREMENT || this->current_tok.type == TokenType::DECREMENT) {
                Token op = this->current_tok;
                this->advance();
                AnyNode value_node = new UnaryOpNode(op, base);
                return res.success(value_node);
            } else {
                break;
            }
            if (res.error) return res.to_prs();
        }
        return res.success(base);
    } else if (tok.type == TokenType::LPAREN) {
        this->advance();
        AnyNode any_expr = res.reg(this->logical_or());
        if (res.error) return res.to_prs();

        if (this->current_tok.type == TokenType::RPAREN) {
            this->advance();
            AnyNode base = any_expr;

            while (this->current_tok.type == TokenType::DOT) {
                this->advance();

                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(new InvalidSyntaxError("Expected property or method name after '.'", this->current_tok.pos));
                    return res.to_prs();
                }

                Token property_name = this->current_tok;
                this->advance();
                Token base_name_tok;
                if (auto unary = std::get_if<UnaryOpNode*>(&base)) {
                    if ((*unary)->op_tok.type == TokenType::MUL) {
                        if (auto var = std::get_if<VarAccessNode*>(&(*unary)->node)) {
                            base_name_tok = (*var)->var_name_tok;
                        } else {
                            base_name_tok = Token(TokenType::IDENTIFIER, "", property_name.pos);
                        }
                    } else {
                        base_name_tok = Token(TokenType::IDENTIFIER, "", property_name.pos);
                    }
                } else if (auto var = std::get_if<VarAccessNode*>(&base)) {
                    base_name_tok = (*var)->var_name_tok;
                } else {
                    base_name_tok = Token(TokenType::IDENTIFIER, "", property_name.pos);
                }

                if (this->current_tok.type == TokenType::LPAREN) {
                    this->advance();
                    std::vector<AnyNode> args;
                    if (this->current_tok.type != TokenType::RPAREN) {
                        while (true) {
                            if (this->current_tok.type == TokenType::AT) {
                                this->advance();
                                AnyNode expr = res.reg(this->logical_or());
                                if (res.error) return res.to_prs();
                                args.push_back(new SpreadNode(expr));
                            } else {
                                AnyNode arg = res.reg(this->logical_or());
                                if (res.error) return res.to_prs();
                                args.push_back(arg);
                            }
                            if (this->current_tok.type != TokenType::COMMA) break;
                            this->advance();
                        }
                    }

                    if (this->current_tok.type != TokenType::RPAREN) {
                        res.failure(new InvalidSyntaxError("Expected ')' after method arguments", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();

                    base = new MethodCallNode(base, property_name, args);
                } else {
                    base = new PropertyAccessNode(base, base_name_tok, property_name);
                }
            }

            return res.success(base);
        } else {
            res.failure(new InvalidSyntaxError("QC-S050: Expected ')'", this->current_tok.pos));
            return res.to_prs();
        }
    } else if (tok.type == TokenType::FSTRING) {
        this->advance();

        std::vector<std::string> parts;
        std::vector<std::string> exprs;
        std::string current = "";
        bool in_expr = false;

        for (char c : tok.value) {
            if (c == '\x01') {
                if (in_expr)
                    exprs.push_back(current);
                else
                    parts.push_back(current);
                current = "";
                in_expr = !in_expr;
            } else {
                current += c;
            }
        }

        if (!current.empty()) {
            if (in_expr)
                exprs.push_back(current);
            else
                parts.push_back(current);
        }

        if (parts.empty()) parts.push_back("");

        AnyNode result = StringNode(Token(TokenType::STRING, parts[0], tok.pos));

        for (size_t i = 0; i < exprs.size(); ++i) {
            Lexer expr_lexer(exprs[i], "<fstring>");
            auto expr_tokens = expr_lexer.make_tokens();
            Parser expr_parser(expr_tokens.Tkns);
            AnyNode expr_node = res.reg(expr_parser.logical_or());
            if (res.error) return res.to_prs();

            result = new BinOpNode(result, Token(TokenType::PLUS, "+", tok.pos), expr_node, true);

            if (i + 1 < parts.size()) {
                result = new BinOpNode(result, Token(TokenType::PLUS, "+", tok.pos), StringNode(Token(TokenType::STRING, parts[i + 1], tok.pos)),
                                       true);
            }
        }

        return res.success(result);
    }

    if (tok.type == TokenType::KEYWORD && tok.value == "fn") {
        this->advance();

        if (this->current_tok.type != TokenType::LPAREN) {
            res.failure(new InvalidSyntaxError("QC-S051: Expected '(' after 'fn'", this->current_tok.pos));
            return res.to_prs();
        }

        auto saved_index = this->index;

        int paren_depth = 1;
        this->advance();

        while (paren_depth > 0 && this->current_tok.type != TokenType::EOFT) {
            if (this->current_tok.type == TokenType::LPAREN) paren_depth++;
            if (this->current_tok.type == TokenType::RPAREN) paren_depth--;
            this->advance();
        }

        std::vector<Token> return_types;

        if (this->current_tok.type == TokenType::ARROW) {
            this->advance();

            if (this->current_tok.type != TokenType::KEYWORD && !find_type(this->current_tok.value)) {
                res.failure(new InvalidSyntaxError("QC-S052: Expected return type after '->'", this->current_tok.pos));
                return res.to_prs();
            }

            return_types.push_back(this->current_tok);
            this->advance();

            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();

                if (this->current_tok.type != TokenType::KEYWORD) {
                    res.failure(new InvalidSyntaxError("QC-S053: Expected return type after ','", this->current_tok.pos));
                    return res.to_prs();
                }

                return_types.push_back(this->current_tok);
                this->advance();
            }
        }
        this->index = saved_index;
        this->current_tok = this->tokens[this->index];

        auto fn_pr = this->func_def_multi(return_types, std::nullopt);

        if (std::holds_alternative<Error*>(fn_pr)) return fn_pr;

        AnyNode fn_node;
        if (std::holds_alternative<FuncDefNode*>(fn_pr))
            fn_node = std::get<FuncDefNode*>(fn_pr);
        else
            fn_node = std::get<FuncDefNode*>(fn_pr);

        if (this->current_tok.type == TokenType::LPAREN) return this->call(fn_node);

        return res.success(fn_node);
    }
    return res.success(std::monostate{});
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
        left = new BinOpNode(left, op_tok, right);
    }

    return res.success(left);
}
Prs Parser::factor() {
    ParseResult res;
    Token tok = this->current_tok;

    if (tok.type == TokenType::PLUS || tok.type == TokenType::MINUS || tok.type == TokenType::BITWISE_NOT || tok.type == TokenType::NOT ||
        tok.type == TokenType::QNOT || tok.type == TokenType::AMPERSAND || tok.type == TokenType::MUL) {

        this->advance();
        AnyNode factor_node = res.reg(this->factor());
        if (res.error) return res.to_prs();
        return res.success(new UnaryOpNode(tok, factor_node));
    }
    if (current_tok.type == TokenType::INCREMENT || current_tok.type == TokenType::DECREMENT) {

        Token op = current_tok;
        advance();

        AnyNode operand = res.reg(this->factor());
        if (res.error) return res.to_prs();

        return res.success(new UnaryOpNode(op, operand, false));
    }
    if (current_tok.type == TokenType::SIZEOF) {

        Token op = current_tok;
        advance();

        AnyNode operand = res.reg(this->factor());
        if (res.error) return res.to_prs();

        return res.success(new UnaryOpNode(op, operand, false));
    }

    return this->power();
}
Prs Parser::term() {
    return this->bin_op([this]() { return this->factor(); }, {TokenType::DIV, TokenType::MUL, TokenType::MOD});
}
Prs Parser::bitwise() {
    return this->bin_op([this]() { return this->term(); },
                        {TokenType::RSHIFT, TokenType::LSHIFT, TokenType::R_ROT, TokenType::L_ROT, TokenType::LOGICAL_RSHIFT});
}
Prs Parser::logical_and() {
    ParseResult res;
    AnyNode left = res.reg(this->comparison());
    if (res.error) return res.to_prs();

    while (this->current_tok.type == TokenType::AND || this->current_tok.type == TokenType::AMPERSAND) {
        Token op_tok = this->current_tok;
        this->advance();
        AnyNode right = res.reg(this->comparison());
        if (res.error) return res.to_prs();

        left = new BinOpNode(left, op_tok, right);
    }

    return res.success(left);
}

Prs Parser::logical_or() {
    ParseResult res;
    AnyNode left = res.reg(this->logical_and());
    if (res.error) return res.to_prs();

    while (this->current_tok.type == TokenType::OR || this->current_tok.type == TokenType::XOR || this->current_tok.type == TokenType::PIPE ||
           this->current_tok.type == TokenType::BITWISE_XOR) {
        Token op_tok = this->current_tok;
        this->advance();
        AnyNode right = res.reg(this->logical_and());
        if (res.error) return res.to_prs();

        left = new BinOpNode(left, op_tok, right);
    }

    return res.success(left);
}
Prs Parser::qin_expr() {
    ParseResult res;

    AnyNode left = QInNode{};

    while (current_tok.type == TokenType::RSHIFT) {
        Token op_tok = current_tok;
        advance();

        AnyNode right = res.reg(this->bitwise());
        if (!std::holds_alternative<VarAccessNode*>(right)) {
            res.failure(new InvalidSyntaxError("QC-S055: Right-hand side of >> must be a variable", op_tok.pos));
            return res.to_prs();
        }

        left = new BinOpNode(left, op_tok, right);
    }

    return res.success(left);
}
Prs Parser::comparison() {
    ParseResult res;
    AnyNode left = res.reg(this->expr());
    if (res.error) return res.to_prs();

    while (this->current_tok.type == TokenType::EQ_TO || this->current_tok.type == TokenType::NOT_EQ || this->current_tok.type == TokenType::LESS ||
           this->current_tok.type == TokenType::LESS_EQ || this->current_tok.type == TokenType::MORE ||
           this->current_tok.type == TokenType::MORE_EQ || this->current_tok.type == TokenType::QEQEQ || this->current_tok.type == TokenType::QNEQ ||
           this->current_tok.type == TokenType::QAND || this->current_tok.type == TokenType::QOR || this->current_tok.type == TokenType::QXOR ||
           this->current_tok.type == TokenType::COLLAPSE_AND || this->current_tok.type == TokenType::COLLAPSE_OR) {

        Token op_tok = this->current_tok;
        this->advance();
        AnyNode right = res.reg(this->expr());
        if (res.error) return res.to_prs();

        left = new BinOpNode(left, op_tok, right);
    }

    return res.success(left);
}
Prs Parser::expr() {
    ParseResult res;
    AnyNode left = res.reg(this->bitwise());
    if (res.error) return res.to_prs();

    while (current_tok.type != TokenType::SEMICOLON && (current_tok.type == TokenType::PLUS || current_tok.type == TokenType::MINUS)) {
        Token op_tok = current_tok;
        advance();

        AnyNode right = res.reg(this->bitwise());
        if (res.error) return res.to_prs();

        left = new BinOpNode(left, op_tok, right);
    }

    return res.success(left);
}
Prs Parser::bin_op(std::function<Prs()> func, std::initializer_list<TokenType> ops) {
    ParseResult res;
    AnyNode left = res.reg(func());
    if (res.error) return res.to_prs();

    while (std::find(ops.begin(), ops.end(), this->current_tok.type) != ops.end()) {
        Token op_tok = this->current_tok;
        this->advance();

        AnyNode right = res.reg(func());
        if (res.error) return res.to_prs();

        left = new BinOpNode(left, op_tok, right);
    }

    return res.success(left);
}
Prs Parser::return_stmt() {
    ParseResult res;
    Position start_pos = this->current_tok.pos;

    this->advance();

    if (this->current_tok.type == TokenType::SEMICOLON) {
        this->advance();
        return res.success(new ReturnNode(std::monostate{}, start_pos));
    }

    std::vector<AnyNode> values;
    values.push_back(res.reg(this->logical_or()));
    if (res.error) { return res.to_prs(); }

    while (this->current_tok.type == TokenType::COMMA) {
        this->advance();
        values.push_back(res.reg(this->logical_or()));
        if (res.error) return res.to_prs();
    }

    if (this->current_tok.type != TokenType::SEMICOLON) {
        res.failure(new MissingSemicolonError(this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();

    if (values.size() == 1) { return res.success(new ReturnNode(values[0], start_pos)); }

    return res.success(new MultiReturnNode(values, start_pos));
}
Prs Parser::assignment_expr() {
    ParseResult res;

    AnyNode left = res.reg(this->logical_or());

    if (res.error) return res.to_prs();

    if (this->current_tok.type == TokenType::EQ || this->current_tok.type == TokenType::PLUS_EQ || this->current_tok.type == TokenType::MINUS_EQ ||
        this->current_tok.type == TokenType::MUL_EQ || this->current_tok.type == TokenType::DIV_EQ || this->current_tok.type == TokenType::MOD_EQ) {

        bool is_var = std::holds_alternative<VarAccessNode*>(left);
        bool is_array_access = std::holds_alternative<ArrayAccessNode*>(left);
        bool is_prop = std::holds_alternative<PropertyAccessNode*>(left);
        bool is_deref = std::holds_alternative<UnaryOpNode*>(left) && std::get<UnaryOpNode*>(left)->op_tok.type == TokenType::MUL;
        if (!is_var && !is_array_access && !is_prop && !is_deref) {
            res.failure(new InvalidSyntaxError("QC-S056: Left side of assignment must be a variable, struct "
                                               "field, "
                                               "array/map access, or *pointer",
                                               this->current_tok.pos));
            return res.to_prs();
        }
        Token op_tok = this->current_tok;
        this->advance();

        AnyNode right;
        if (op_tok.type == TokenType::EQ) {
            size_t next_i = index + 1;
            if (this->current_tok.type == TokenType::IDENTIFIER && next_i < tokens.size() && tokens[next_i].type == TokenType::EQ) {
                right = res.reg(this->assignment_expr());
            } else {
                right = res.reg(this->logical_or());
            }
        } else {
            right = res.reg(this->logical_or());
        }

        if (res.error) return res.to_prs();
        if (is_prop) {
            auto& prop = std::get<PropertyAccessNode*>(left);
            Token field = prop->property_name;

            TokenType binop_type;
            switch (op_tok.type) {
            case TokenType::EQ: binop_type = TokenType::EQ; break;
            case TokenType::PLUS_EQ: binop_type = TokenType::PLUS; break;
            case TokenType::MINUS_EQ: binop_type = TokenType::MINUS; break;
            case TokenType::MUL_EQ: binop_type = TokenType::MUL; break;
            case TokenType::DIV_EQ: binop_type = TokenType::DIV; break;
            case TokenType::MOD_EQ: binop_type = TokenType::MOD; break;
            default: res.failure(new InvalidSyntaxError("QC-S057: Unsupported op for struct fields", op_tok.pos)); return res.to_prs();
            }
            AnyNode lhsBase = clone_node(*(prop->base));

            if (binop_type == TokenType::EQ) { return res.success(new FieldAssignNode(lhsBase, field, right)); }
            AnyNode rhsBase = clone_node(*(prop->base));

            auto readProp = new PropertyAccessNode(rhsBase, prop->base_name_tok, field);
            AnyNode readPropNode = readProp;
            Token bin_tok(binop_type, get_token_name(binop_type), op_tok.pos);
            AnyNode binExpr = AnyNode{new BinOpNode(readPropNode, bin_tok, right)};
            return res.success(new FieldAssignNode(lhsBase, field, binExpr));
        }
        if (is_array_access) {
            if (op_tok.type != TokenType::EQ) {
                res.failure(new InvalidSyntaxError("QC-S058: Compound assignment (+=, -=, etc.) not supported "
                                                   "for "
                                                   "array/map access",
                                                   op_tok.pos));
                return res.to_prs();
            }

            return res.success(new ArrayAssignNode(left, right));
        }

        return res.success(new AssignExprNode(left, op_tok, right));
    }

    return res.success(left);
}
static bool is_statement_node(const Prs& st) {
    return std::visit(
        [](auto arg) -> bool {
            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, Error*>) { return true; }

            if constexpr (std::is_same_v<T, ParseResult> || std::is_same_v<T, std::monostate>) { return false; }

            return true;
        },
        st);
}
AnyNode to_any_node(Prs prs) {
    return std::visit(
        [](auto arg) -> AnyNode {
            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, Error*>) {
                return std::monostate{};
            } else if constexpr (std::is_same_v<T, ParseResult>) {
                return arg.node;
            } else if constexpr (std::is_same_v<T, BinOpNode*> || std::is_same_v<T, UnaryOpNode*> || std::is_same_v<T, VarAccessNode*> ||
                                 std::is_same_v<T, VarAssignNode*> || std::is_same_v<T, AssignExprNode*> || std::is_same_v<T, IfNode*> ||
                                 std::is_same_v<T, StatementsNode*> || std::is_same_v<T, SwitchNode*> || std::is_same_v<T, BreakNode*> ||
                                 std::is_same_v<T, WhileNode*> || std::is_same_v<T, ForNode*> || std::is_same_v<T, ContinueNode*> ||
                                 std::is_same_v<T, CallNode*> || std::is_same_v<T, FuncDefNode*> || std::is_same_v<T, ReturnNode*> ||
                                 std::is_same_v<T, MultiReturnNode*> || std::is_same_v<T, MultiVarDeclNode*> || std::is_same_v<T, ArrayDeclNode*> ||
                                 std::is_same_v<T, ArrayLiteralNode*> || std::is_same_v<T, ArrayAccessNode*> || std::is_same_v<T, QIfNode*> ||
                                 std::is_same_v<T, QSwitchNode*> || std::is_same_v<T, FieldAssignNode*> || std::is_same_v<T, MapLiteralNode*> ||
                                 std::is_same_v<T, NamespaceNode*> || std::is_same_v<T, TryCatchNode*>) {
                return arg;
            } else {
                return arg;
            }
        },
        prs);
}
Parameter Parser::parse_parameter(bool type_only = false) {
    Parameter p;
    if (this->current_tok.value == "fn" && this->current_tok.type == TokenType::KEYWORD) {
        p.type = this->current_tok;
        this->advance();

        if (this->current_tok.type != TokenType::LPAREN) { throw new InvalidSyntaxError("Expected '(' after 'fn'", this->current_tok.pos); }
        this->advance();

        Parameter::FunctionSignature sig;
        if (this->current_tok.type != TokenType::RPAREN) {
            while (true) {
                sig.params.push_back(this->parse_parameter());
                if (this->current_tok.type == TokenType::COMMA) {
                    this->advance();
                } else {
                    break;
                }
            }
        }

        if (this->current_tok.type != TokenType::RPAREN) { throw new InvalidSyntaxError("Expected ')'", this->current_tok.pos); }
        this->advance();
        if (this->current_tok.type == TokenType::ARROW) {
            this->advance();
            if (this->current_tok.type == TokenType::LPAREN) {
                this->advance();
                while (true) {
                    sig.return_types.push_back(this->parse_parameter(true).type);
                    if (this->current_tok.type != TokenType::COMMA) break;
                    this->advance();
                }
                if (this->current_tok.type != TokenType::RPAREN) { throw new InvalidSyntaxError("Expected ')'", this->current_tok.pos); }
                this->advance();
            } else {
                auto temp_p = this->parse_parameter(true);
                sig.return_types.push_back(temp_p.type);
            }
        }
        p.signature = sig;
    } else {
        p.type = this->current_tok;
        this->advance();
        if (!(p.type.type == TokenType::VARADIC)) {
            while (this->current_tok.type == TokenType::SCOPE) {
                this->advance();
                p.type.value += "::" + this->current_tok.value;
                this->advance();
            }

            if ((p.type.value == "list" || p.type.value == "map") && this->current_tok.type == TokenType::LESS) {
                this->advance();
                p.type.value += "<" + this->parse_parameter().type.value;
                if (this->current_tok.type == TokenType::COMMA) {
                    this->advance();
                    p.type.value += ", " + this->parse_parameter().type.value;
                }
                if (this->current_tok.type != TokenType::MORE) {
                    throw new InvalidSyntaxError("Expected '>' after a list/map type", this->current_tok.pos);
                }
                this->advance();
                p.type.value += ">";
            }

            if (this->current_tok.type == TokenType::AMPERSAND) {
                this->advance();
                p.type.value += "&";
            }
            while (this->current_tok.type == TokenType::MUL) {
                this->advance();
                p.type.value += "*";
            }
            while (this->current_tok.type == TokenType::LBRACKET) {
                this->advance();
                if (this->current_tok.type != TokenType::RBRACKET) { throw new InvalidSyntaxError("Expected ']' after '['", this->current_tok.pos); }
                this->advance();
                p.type.value += "[]";
            }
        } else {
            p.name = Token(TokenType::IDENTIFIER, "<varadic>", Position());
        }
    }
    if (!type_only) {
        if (this->current_tok.type == TokenType::IDENTIFIER) {
            p.name = this->current_tok;
            this->advance();
        }
        if (this->current_tok.type == TokenType::EQ) {
            this->advance();
            Prs val = this->logical_or();
            p.default_value = to_any_node(val);
        }
    }
    return p;
}
Prs Parser::func_def_multi(std::vector<Token> return_types, std::optional<Token> func_name) {
    ParseResult res;
    this->advance();
    std::vector<Parameter> params;
    if (this->current_tok.type != TokenType::RPAREN) {
        while (true) {
            params.push_back(this->parse_parameter());
            if (params.back().type.type == TokenType::VARADIC) { break; }
            if (this->current_tok.type == TokenType::COMMA) {
                this->advance();
            } else {
                break;
            }
        }
    }
    if (this->current_tok.type != TokenType::RPAREN) {
        res.failure(new InvalidSyntaxError("QC-S064: Expected ')' after parameters", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();
    if (this->current_tok.type == TokenType::ARROW) {
        this->advance();
        while (this->current_tok.type == TokenType::SCOPE) {
            this->advance();
            this->advance();
        }
        if (this->current_tok.type == TokenType::KEYWORD || this->user_types.count(this->current_tok.value) > 0) {
            this->parse_parameter(true);
            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                this->parse_parameter(true);
                if (this->current_tok.type == TokenType::KEYWORD || this->user_types.count(this->current_tok.value) > 0) {
                    this->advance();
                    this->parse_parameter(true);
                }
            }
        }
    }
    if (this->current_tok.type != TokenType::LBRACE) {
        if (this->in_foreign) {
            this->advance();
            std::list<Parameter> params_list((params.begin()), (params.end()));
            std::vector<AnyNode> body;
            body.emplace_back(std::monostate{});
            return res.success(
                new FuncDefNode(return_types, func_name, params_list, new StatementsNode(body), currentNamespace, this->in_extern, this->in_foreign));
        }
        res.failure(new InvalidSyntaxError("QC-S003: Expected '{' to start function body", this->current_tok.pos));
        return res.to_prs();
    }
    this->advance();
    if (this->in_foreign) {
        res.failure(new InvalidSyntaxError("QC-S003: Expected no function body for a foreign function.", this->current_tok.pos));
        return res.to_prs();
    }
    std::vector<AnyNode> body_stmts;
    while (true) {
        if (this->current_tok.type == TokenType::RBRACE) break;

        if (this->current_tok.type == TokenType::EOFT) {
            res.failure(new InvalidSyntaxError("Unexpected end of file in function body", this->current_tok.pos));
            return res.to_prs();
        }
        Prs st = this->statement();

        if (std::holds_alternative<Error*>(st)) {
            res.failure(std::get<Error*>(st));
            return res.to_prs();
        }

        if (!is_statement_node(st)) { continue; }

        AnyNode node = to_any_node(st);

        if (std::holds_alternative<std::monostate>(node)) { continue; }

        body_stmts.push_back(node);
    }

    if (this->current_tok.type != TokenType::RBRACE) {
        res.failure(new InvalidSyntaxError("Expected '}' to end function body", this->current_tok.pos));
        return res.to_prs();
    }
    auto body = new StatementsNode(body_stmts, true);
    this->advance();
    std::list<Parameter> params_list((params.begin()), (params.end()));

    return res.success(new FuncDefNode(return_types, func_name, params_list, body, currentNamespace, this->in_extern, this->in_foreign));
}
Prs Parser::statement() {
    ParseResult res;
    Token tok = this->current_tok;
    if (tok.type == TokenType::KEYWORD && tok.value == "extern") {
        this->advance();
        if (this->current_tok.type == TokenType::COLON) {
            this->advance();
            tok = this->current_tok;
            this->in_extern = true;
        } else {
            res.failure(new InvalidSyntaxError("Expected ':' after 'extern'", this->current_tok.pos));
            return res.to_prs();
        }
    }
    if (tok.type == TokenType::COLON && peek().value == "extern") {
        this->advance();
        this->advance();
        tok = this->current_tok;
        this->in_extern = false;
        return res.success(std::monostate{});
    }
    if (tok.type == TokenType::KEYWORD && tok.value == "foreign") {
        this->advance();
        if (this->current_tok.type == TokenType::COLON) {
            this->advance();
            tok = this->current_tok;
            this->in_foreign = true;
        } else {
            res.failure(new InvalidSyntaxError("Expected ':' after 'foreign'", this->current_tok.pos));
            return res.to_prs();
        }
    }
    if (tok.type == TokenType::COLON && peek().value == "foreign") {
        this->advance();
        this->advance();
        tok = this->current_tok;
        this->in_foreign = false;
        return res.success(std::monostate{});
    }
    if (tok.type == TokenType::KEYWORD && tok.value == "fn") {
        this->advance();

        if (this->current_tok.type != TokenType::LPAREN) {
            res.failure(new InvalidSyntaxError("Expected '(' after 'fn'", this->current_tok.pos));
            return res.to_prs();
        }

        auto saved_index = this->index;

        int paren_depth = 1;
        this->advance();

        while (paren_depth > 0 && this->current_tok.type != TokenType::EOFT) {
            if (this->current_tok.type == TokenType::LPAREN) paren_depth++;
            if (this->current_tok.type == TokenType::RPAREN) paren_depth--;
            this->advance();
        }

        std::vector<Token> return_types;

        if (this->current_tok.type == TokenType::ARROW) {
            this->advance();

            if (this->current_tok.type != TokenType::KEYWORD && user_types.count(this->current_tok.value) <= 0) {
                res.failure(new InvalidSyntaxError("Expected return type after '->'", this->current_tok.pos));
                return res.to_prs();
            }

            return_types.push_back(this->current_tok);
            this->advance();

            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();

                if (this->current_tok.type != TokenType::KEYWORD) {
                    res.failure(new InvalidSyntaxError("Expected return type after ','", this->current_tok.pos));
                    return res.to_prs();
                }

                return_types.push_back(this->current_tok);
                this->advance();
            }
        } else {
            return_types.push_back(Token(TokenType::KEYWORD, "auto", tok.pos));
        }

        this->index = saved_index;
        this->current_tok = this->tokens[this->index];

        auto fn_pr = this->func_def_multi(return_types, std::nullopt);

        if (std::holds_alternative<Error*>(fn_pr)) return fn_pr;

        AnyNode fn_node;
        if (std::holds_alternative<FuncDefNode*>(fn_pr))
            fn_node = std::get<FuncDefNode*>(fn_pr);
        else
            fn_node = std::get<FuncDefNode*>(fn_pr);

        if (this->current_tok.type == TokenType::LPAREN) return this->call(fn_node);
        if (this->current_tok.type == TokenType::SEMICOLON) this->advance();
        return res.success(fn_node);
    }
    if (tok.type == TokenType::KEYWORD && tok.value == "if") { return this->if_expr(); }
    if (tok.type == TokenType::KEYWORD && tok.value == "try") { return this->try_catch_expr(); }
    if (tok.type == TokenType::KEYWORD && tok.value == "qif") { return this->qif_expr(); }
    if (tok.type == TokenType::KEYWORD && tok.value == "switch") { return this->switch_stmt(); }
    if (tok.type == TokenType::KEYWORD && tok.value == "qswitch") { return this->qswitch_stmt(); }
    if (tok.type == TokenType::KEYWORD && tok.value == "while") { return this->while_stmt(); }
    if (tok.type == TokenType::KEYWORD && tok.value == "for") { return this->for_stmt(); }
    if (tok.type == TokenType::KEYWORD && tok.value == "foreach") {
        this->advance();

        if (this->current_tok.type != TokenType::LPAREN) {
            res.failure(new InvalidSyntaxError("Expected '(' after 'foreach'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        if (this->current_tok.type != TokenType::KEYWORD) {
            res.failure(new InvalidSyntaxError("Expected type in foreach", this->current_tok.pos));
            return res.to_prs();
        }
        Token elem_type = this->current_tok;
        this->advance();
        if (current_tok.type == TokenType::AMPERSAND) {
            this->advance();
            elem_type.value += "&";
        }
        while (this->current_tok.type == TokenType::MUL) {
            this->advance();
            elem_type.value += "*";
        }
        if (this->current_tok.type != TokenType::IDENTIFIER) {
            res.failure(new InvalidSyntaxError("Expected variable name in foreach", this->current_tok.pos));
            return res.to_prs();
        }
        Token elem_name = this->current_tok;
        this->advance();

        if (this->current_tok.type != TokenType::KEYWORD || this->current_tok.value != "in") {
            res.failure(new InvalidSyntaxError("Expected 'in' in foreach", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        AnyNode collection = res.reg(this->logical_or());
        if (res.error) { return res.to_prs(); }
        if (this->current_tok.type != TokenType::RPAREN) {
            res.failure(new InvalidSyntaxError("QC-S016: Expected ')' after foreach", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        if (this->current_tok.type != TokenType::LBRACE) {
            res.failure(new InvalidSyntaxError("QC-S003: Expected '{' to start foreach body", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        std::vector<AnyNode> stmts;
        while (this->current_tok.type != TokenType::RBRACE && this->current_tok.type != TokenType::EOFT) {
            Prs st = this->statement();
            if (std::holds_alternative<Error*>(st)) {
                res.failure(std::get<Error*>(st));
                return res.to_prs();
            }
            AnyNode any_stmt = this->prs_to_anynode(st);
            stmts.push_back(any_stmt);
        }

        if (this->current_tok.type != TokenType::RBRACE) {
            res.failure(new InvalidSyntaxError("Expected '}' to end foreach body", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        auto body_block = new StatementsNode(stmts, true);

        return res.success(new ForeachNode(elem_type, elem_name, collection, body_block));
    }
    if (tok.type == TokenType::KEYWORD && tok.value == "continue") {
        this->advance();
        if (current_tok.type != TokenType::SEMICOLON) {
            res.failure(new MissingSemicolonError(current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        return res.success(new ContinueNode(tok));
    }
    if (tok.type == TokenType::KEYWORD && tok.value == "return") { return this->return_stmt(); }
    if (tok.type == TokenType::KEYWORD && tok.value == "break") {
        this->advance();
        if (current_tok.type != TokenType::SEMICOLON) {
            res.failure(new MissingSemicolonError(current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        return res.success(new BreakNode(tok));
    }
    bool is_abstract_class = false;
    bool is_final_class = false;
    if (tok.type == TokenType::KEYWORD && tok.value == "abstract") {
        this->advance();
        if (this->current_tok.type != TokenType::KEYWORD || this->current_tok.value != "class") {
            res.failure(new InvalidSyntaxError("Expected 'class' after 'abstract'", this->current_tok.pos));
            return res.to_prs();
        }
        is_abstract_class = true;
        tok = this->current_tok;
    }
    if (tok.type == TokenType::KEYWORD && tok.value == "final") {
        this->advance();
        if (this->current_tok.type != TokenType::KEYWORD || this->current_tok.value != "class") {
            res.failure(new InvalidSyntaxError("Expected 'class' after 'final'", this->current_tok.pos));
            return res.to_prs();
        }
        is_final_class = true;
        tok = this->current_tok;
    }
    if (tok.type == TokenType::KEYWORD && tok.value == "class") {
        this->advance();

        if (this->current_tok.type != TokenType::IDENTIFIER) {
            res.failure(new InvalidSyntaxError("Expected class name", this->current_tok.pos));
            return res.to_prs();
        }
        Token class_name = this->current_tok;
        this->advance();
        std::string baseName = "";
        if (this->current_tok.type == TokenType::COLON) {
            advance();
            if (current_tok.type != TokenType::IDENTIFIER) {
                res.failure(new InvalidSyntaxError("Expected base name after ':'", this->current_tok.pos));
                return res.to_prs();
            }
            baseName = current_tok.value;
            advance();
        }
        if (!baseName.empty()) {
            auto* base_ptr = find_type(baseName);
            if (base_ptr && base_ptr->kind == UserTypeKind::Class && base_ptr->is_final_class) {
                auto& baseInfo = *base_ptr;
                res.failure(new InvalidSyntaxError("Cannot inherit from final class '" + baseName + "'", class_name.pos));
                return res.to_prs();
            }
        }
        if (this->current_tok.type != TokenType::LBRACE) {
            res.failure(new InvalidSyntaxError("QC-S003: Expected '{' after class name", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        UserTypeInfo dummy;
        UserTypeInfo info;
        dummy.baseClassName = baseName;
        dummy.is_final_class = is_final_class;
        dummy.kind = UserTypeKind::Class;
        info.baseClassName = baseName;
        info.is_final_class = is_final_class;
        info.kind = UserTypeKind::Class;
        dummy.is_abstract_class = is_abstract_class;
        info.is_abstract_class = is_abstract_class;
        if (user_types.contains(class_name.value)) {
            res.failure(new InvalidSyntaxError("QC-UT01: Redefinition of type '" + class_name.value + "'", class_name.pos));
            return res.to_prs();
        }
        dummy.namespace_path = currentNamespace;
        info.namespace_path = currentNamespace;
        std::string full_key = currentNamespace.empty() ? class_name.value : currentNamespace + "::" + class_name.value;
        user_types[full_key] = dummy;

        while (this->current_tok.type != TokenType::RBRACE && this->current_tok.type != TokenType::EOFT) {

            std::string access = "public";
            bool is_final_method = false;

            if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "final") {
                is_final_method = true;
                this->advance();
            }
            if (this->current_tok.type == TokenType::KEYWORD &&
                (this->current_tok.value == "public" || this->current_tok.value == "private" || this->current_tok.value == "protected")) {
                access = this->current_tok.value;
                this->advance();
            }
            if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "final") {
                is_final_method = true;
                this->advance();
            }

            if (this->current_tok.type == TokenType::IDENTIFIER && this->current_tok.value == class_name.value) {

                if (is_abstract_class) {
                    res.failure(new InvalidSyntaxError("Cannot make constructor on abstract class '" + class_name.value + "'", class_name.pos));
                    return res.to_prs();
                }

                Token next_tok;
                if (index + 1 < tokens.size()) {
                    next_tok = tokens[index + 1];
                } else {
                    next_tok = Token(TokenType::EOFT, "", this->current_tok.pos);
                }

                if (next_tok.type == TokenType::LPAREN) {
                    Token ctor_name = this->current_tok;
                    this->advance();
                    if (this->current_tok.type != TokenType::LPAREN) {
                        res.failure(new InvalidSyntaxError("Expected '(' after constructor name", this->current_tok.pos));
                        return res.to_prs();
                    }

                    auto ctor_pr = this->func_def_multi({}, std::nullopt);
                    if (std::holds_alternative<Error*>(ctor_pr)) return ctor_pr;

                    auto fn = std::get<FuncDefNode*>(ctor_pr);
                    ClassMethodInfo mi;
                    mi.name_tok = ctor_name;
                    mi.params.clear();
                    mi.params.reserve(fn->params.size());
                    for (auto it = fn->params.begin(); it != fn->params.end(); ++it) { mi.params.push_back(*it); }
                    mi.return_types = {};
                    mi.body = fn->body;
                    mi.is_constructor = true;
                    mi.access = access;

                    info.classMethods.push_back(mi);
                    continue;
                }
            }
            if (this->current_tok.type != TokenType::KEYWORD && this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(new InvalidSyntaxError("Expected type or constructor in class body", this->current_tok.pos));
                return res.to_prs();
            }

            std::vector<Token> type_list;

            auto parse_one_type_into = [&](Token& out_tok) -> bool {
                std::string field_type;
                bool is_user_type = false;

                if (this->current_tok.type == TokenType::IDENTIFIER) {
                    is_user_type = true;
                    field_type = this->current_tok.value;
                    this->advance();
                    while (this->current_tok.type == TokenType::SCOPE) {
                        this->advance();
                        if (this->current_tok.type != TokenType::IDENTIFIER) {
                            res.failure(new InvalidSyntaxError("QC-N001: Expected identifier after '::'", this->current_tok.pos));
                            return false;
                        }
                        field_type += "::" + this->current_tok.value;
                        this->advance();
                    }
                    if (this->current_tok.type == TokenType::AMPERSAND) {
                        this->advance();
                        field_type += "&";
                    }
                    while (this->current_tok.type == TokenType::MUL) {
                        this->advance();
                        field_type += "*";
                    }
                } else if (this->current_tok.type == TokenType::KEYWORD) {
                    Token base_type = this->current_tok;
                    this->advance();
                    if (current_tok.type == TokenType::AMPERSAND) {
                        this->advance();
                        base_type.value += "&";
                    }
                    while (this->current_tok.type == TokenType::MUL) {
                        this->advance();
                        base_type.value += "*";
                    }
                    field_type = base_type.value;
                    if (base_type.value == "list" && this->current_tok.type == TokenType::LESS) {
                        this->advance();

                        if (this->current_tok.type != TokenType::KEYWORD && this->current_tok.type != TokenType::IDENTIFIER) {
                            res.failure(new InvalidSyntaxError("Expected element type in list<T>", this->current_tok.pos));
                            return false;
                        }
                        std::string elem_type = this->current_tok.value;
                        this->advance();

                        if (this->current_tok.type != TokenType::MORE) {
                            res.failure(new InvalidSyntaxError("Expected '>' after list element type", this->current_tok.pos));
                            return false;
                        }
                        this->advance();

                        field_type = "list<" + elem_type + ">";
                    } else if (this->current_tok.type == TokenType::LBRACKET) {
                        this->advance();
                        if (this->current_tok.type != TokenType::RBRACKET) {
                            res.failure(new InvalidSyntaxError("QC-S061: Expected ']' after '[' in list type", this->current_tok.pos));
                            return false;
                        }
                        this->advance();
                        field_type = "list<" + base_type.value + ">";
                    } else if (base_type.value == "map") {
                        if (this->current_tok.type != TokenType::LESS) {
                            res.failure(new InvalidSyntaxError("QC-S066: Expected '<' after map for key type", this->current_tok.pos));
                            return false;
                        }
                        this->advance();

                        if (this->current_tok.type != TokenType::KEYWORD && this->current_tok.type != TokenType::IDENTIFIER) {
                            res.failure(new InvalidSyntaxError("QC-S067: Expected key type in map", this->current_tok.pos));
                            return false;
                        }
                        std::string key_type = this->current_tok.value;
                        this->advance();

                        if (this->current_tok.type != TokenType::COMMA) {
                            res.failure(new InvalidSyntaxError("QC-S068: Expected ',' between key and value "
                                                               "type in map",
                                                               this->current_tok.pos));
                            return false;
                        }
                        this->advance();

                        if (this->current_tok.type != TokenType::KEYWORD && this->current_tok.type != TokenType::IDENTIFIER) {
                            res.failure(new InvalidSyntaxError("QC-S069: Expected value type in map", this->current_tok.pos));
                            return false;
                        }
                        std::string value_type = this->current_tok.value;
                        this->advance();

                        if (this->current_tok.type != TokenType::MORE) {
                            res.failure(new InvalidSyntaxError("QC-S070: Expected '>' after map value type", this->current_tok.pos));
                            return false;
                        }
                        this->advance();

                        field_type = "map<" + key_type + ", " + value_type + ">";
                    }
                } else {
                    res.failure(new InvalidSyntaxError("QC-S071: Expected type in class body", this->current_tok.pos));
                    return false;
                }

                out_tok = Token(TokenType::KEYWORD, field_type, this->current_tok.pos);
                return true;
            };
            {
                Token t;
                if (!parse_one_type_into(t)) return res.to_prs();
                type_list.push_back(t);
            }
            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                Token t;
                if (!parse_one_type_into(t)) return res.to_prs();
                type_list.push_back(t);
            }
            Token name_tok;
            if (this->current_tok.type == TokenType::IDENTIFIER && this->current_tok.value != "operator") {
                name_tok = this->current_tok;
                this->advance();
            } else if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "operator") {
                this->advance();
                Token op_tok = this->current_tok;

                switch (op_tok.type) {
                case TokenType::PLUS:
                case TokenType::MINUS:
                case TokenType::MUL:
                case TokenType::DIV:
                case TokenType::EQ_TO:
                case TokenType::NOT_EQ:
                case TokenType::EQ:
                case TokenType::NOT:
                case TokenType::AND:
                case TokenType::OR:
                case TokenType::MORE:
                case TokenType::LESS:
                case TokenType::MORE_EQ:
                case TokenType::LESS_EQ:
                case TokenType::POWER:
                case TokenType::MOD:
                case TokenType::XOR:
                case TokenType::QNOT:
                case TokenType::QAND:
                case TokenType::QOR:
                case TokenType::QXOR:
                case TokenType::COLLAPSE_OR:
                case TokenType::COLLAPSE_AND: break;
                default: res.failure(new InvalidSyntaxError("Unsupported operator in operator method", op_tok.pos)); return res.to_prs();
                }
                std::string op_name;
                switch (op_tok.type) {
                case TokenType::PLUS: op_name = "operator+"; break;
                case TokenType::MINUS: op_name = "operator-"; break;
                case TokenType::MUL: op_name = "operator*"; break;
                case TokenType::DIV: op_name = "operator/"; break;
                case TokenType::EQ_TO: op_name = "operator=="; break;
                case TokenType::NOT_EQ: op_name = "operator!="; break;
                case TokenType::EQ: op_name = "operator="; break;
                case TokenType::NOT: op_name = "operator!"; break;
                case TokenType::AND: op_name = "operator&&"; break;
                case TokenType::OR: op_name = "operator||"; break;
                case TokenType::MORE: op_name = "operator>"; break;
                case TokenType::LESS: op_name = "operator<"; break;
                case TokenType::MORE_EQ: op_name = "operator>="; break;
                case TokenType::LESS_EQ: op_name = "operator<="; break;
                case TokenType::POWER: op_name = "operator#^"; break;
                case TokenType::MOD: op_name = "operator%"; break;
                case TokenType::XOR: op_name = "operator^"; break;
                case TokenType::QNOT: op_name = "operator!!"; break;
                case TokenType::QAND: op_name = "operator&&&"; break;
                case TokenType::QOR: op_name = "operator|||"; break;
                case TokenType::QXOR: op_name = "operator^^"; break;
                case TokenType::COLLAPSE_OR: op_name = "operator|&|"; break;
                case TokenType::COLLAPSE_AND: op_name = "operator&|&"; break;
                default: break;
                }

                name_tok = Token(TokenType::IDENTIFIER, op_name, op_tok.pos);
                this->advance();
            } else {
                res.failure(new InvalidSyntaxError("Expected method or field name after type(s)", this->current_tok.pos));
                return res.to_prs();
            }
            if (this->current_tok.type == TokenType::LPAREN) {
                ClassMethodInfo mi;
                mi.name_tok = name_tok;
                if (!info.baseClassName.empty()) {
                    auto* base_ptr = find_type(baseName);
                    if (base_ptr && base_ptr->kind == UserTypeKind::Class && base_ptr->is_final_class) {
                        auto& baseInfo = *base_ptr;
                        for (auto& bm : baseInfo.classMethods) {
                            if (bm.name_tok.value == mi.name_tok.value && bm.is_final) {
                                res.failure(new InvalidSyntaxError("Cannot override final method '" + mi.name_tok.value + "' from base class '" +
                                                                       info.baseClassName + "'",
                                                                   mi.name_tok.pos));
                                return res.to_prs();
                            }
                        }
                    }
                }

                auto m_pr = this->func_def_multi(type_list, std::make_optional(name_tok));
                if (std::holds_alternative<Error*>(m_pr)) return m_pr;

                auto fn = std::get<FuncDefNode*>(m_pr);

                mi.params.clear();
                mi.params.reserve(fn->params.size());
                for (auto it = fn->params.begin(); it != fn->params.end(); ++it) { mi.params.push_back(*it); }
                mi.return_types = fn->return_types;
                mi.body = fn->body;
                mi.is_constructor = false;
                mi.is_final = is_final_method;
                mi.access = access;

                info.classMethods.push_back(mi);
                continue;
            }
            if (type_list.size() != 1) {
                res.failure(new InvalidSyntaxError("Class fields cannot have multiple types", name_tok.pos));
                return res.to_prs();
            }
            std::string field_type = type_list[0].value;
            int array_dims = 0;
            while (this->current_tok.type == TokenType::LBRACKET) {
                this->advance();
                if (this->current_tok.type == TokenType::KEYWORD) { this->advance(); }
                if (this->current_tok.type != TokenType::RBRACKET) {
                    res.failure(new InvalidSyntaxError("QC-S061: Expected ']' after '[' in array", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                array_dims++;
            }
            for (int i = 0; i < array_dims; ++i) field_type += "[]";

            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(new InvalidSyntaxError("Expected ';' after field declaration", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            ClassField cf;
            cf.name = name_tok.value;
            cf.type = field_type;
            cf.access = access;
            info.classFields.push_back(cf);
        }

        if (this->current_tok.type != TokenType::RBRACE) {
            res.failure(new InvalidSyntaxError("Expected '}' at end of class", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        full_key = currentNamespace.empty() ? class_name.value : currentNamespace + "::" + class_name.value;
        user_types[full_key] = info;
        return res.success(std::monostate{});
    }

    if (tok.type == TokenType::KEYWORD && tok.value == "namespace") {
        ParseResult res;
        this->advance();

        if (current_tok.type != TokenType::IDENTIFIER) {
            res.failure(new InvalidSyntaxError("Expected namespace name", current_tok.pos));
            return res.to_prs();
        }

        Token nsName = current_tok;
        this->advance();

        if (current_tok.type != TokenType::LBRACE) {
            res.failure(new InvalidSyntaxError("QC-N004: Expected '{' after namespace name", current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        namespaceStack.push_back(nsName.value);

        if (currentNamespace.empty()) {
            currentNamespace = nsName.value;
        } else {
            currentNamespace += "::" + nsName.value;
        }

        std::vector<AnyNode> body;

        while (current_tok.type != TokenType::RBRACE && current_tok.type != TokenType::EOFT) {

            Prs st = statement();
            if (std::holds_alternative<Error*>(st)) {
                namespaceStack.pop_back();
                if (namespaceStack.empty()) {
                    currentNamespace = "";
                } else {
                    currentNamespace = "";
                    for (size_t i = 0; i < namespaceStack.size(); ++i) {
                        if (i > 0) currentNamespace += "::";
                        currentNamespace += namespaceStack[i];
                    }
                }
                return res.to_prs();
            }

            body.push_back(prs_to_anynode(st));
        }

        if (current_tok.type != TokenType::RBRACE) {
            res.failure(new InvalidSyntaxError("QC-N005: Expected '}' at end of namespace", current_tok.pos));
            return res.to_prs();
        }

        this->advance();

        namespaceStack.pop_back();

        if (namespaceStack.empty()) {
            currentNamespace = "";
        } else {
            currentNamespace = "";
            for (size_t i = 0; i < namespaceStack.size(); ++i) {
                if (i > 0) currentNamespace += "::";
                currentNamespace += namespaceStack[i];
            }
        }

        return res.success(new NamespaceNode(nsName.value, body));
    }
    if (tok.type == TokenType::KEYWORD && tok.value == "struct") {
        this->advance();

        if (this->current_tok.type != TokenType::IDENTIFIER) {
            res.failure(new InvalidSyntaxError("QC-S065: Expected struct name", this->current_tok.pos));
            return res.to_prs();
        }
        Token struct_name = this->current_tok;
        this->advance();

        if (this->current_tok.type != TokenType::LBRACE) {
            res.failure(new InvalidSyntaxError("QC-S003: Expected '{' after struct name", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        std::vector<StructField> fields;

        while (this->current_tok.type != TokenType::RBRACE && this->current_tok.type != TokenType::EOFT) {

            std::string field_type;
            bool is_user_type = false;
            if (this->current_tok.type == TokenType::IDENTIFIER) {
                is_user_type = true;
                field_type = this->current_tok.value;
                this->advance();
                while (this->current_tok.type == TokenType::SCOPE) {
                    this->advance();

                    if (this->current_tok.type != TokenType::IDENTIFIER) {
                        res.failure(new InvalidSyntaxError("QC-N001: Expected identifier after '::'", this->current_tok.pos));
                        return res.to_prs();
                    }

                    field_type += "::" + this->current_tok.value;
                    this->advance();
                }
                if (this->current_tok.type == TokenType::AMPERSAND) {
                    this->advance();
                    field_type += "&";
                }
                while (this->current_tok.type == TokenType::MUL) {
                    this->advance();
                    field_type += "*";
                }
            } else if (this->current_tok.type == TokenType::KEYWORD) {
                Token base_type = this->current_tok;
                this->advance();
                if (current_tok.type == TokenType::AMPERSAND) {
                    this->advance();
                    base_type.value += "&";
                }
                while (current_tok.type == TokenType::MUL) {
                    this->advance();
                    base_type.value += "*";
                }
                field_type = base_type.value;
                if (this->current_tok.type == TokenType::LBRACKET) {
                    this->advance();
                    if (this->current_tok.type != TokenType::RBRACKET) {
                        res.failure(new InvalidSyntaxError("QC-S061: Expected ']' after '[' in list type", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                    field_type = "list<" + base_type.value + ">";
                } else if (base_type.value == "map") {
                    if (this->current_tok.type != TokenType::LESS) {
                        res.failure(new InvalidSyntaxError("QC-S066: Expected '<' after map for key type", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();

                    if (this->current_tok.type != TokenType::KEYWORD && this->current_tok.type != TokenType::IDENTIFIER) {
                        res.failure(new InvalidSyntaxError("QC-S067: Expected key type in map", this->current_tok.pos));
                        return res.to_prs();
                    }
                    std::string key_type = this->current_tok.value;
                    this->advance();

                    if (this->current_tok.type != TokenType::COMMA) {
                        res.failure(new InvalidSyntaxError("QC-S068: Expected ',' between key and value type "
                                                           "in map",
                                                           this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();

                    if (this->current_tok.type != TokenType::KEYWORD && this->current_tok.type != TokenType::IDENTIFIER) {
                        res.failure(new InvalidSyntaxError("QC-S069: Expected value type in map", this->current_tok.pos));
                        return res.to_prs();
                    }
                    std::string value_type = this->current_tok.value;
                    this->advance();

                    if (this->current_tok.type != TokenType::MORE) {
                        res.failure(new InvalidSyntaxError("QC-S070: Expected '>' after map value type", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();

                    field_type = "map<" + key_type + ", " + value_type + ">";
                }
            } else {
                res.failure(new InvalidSyntaxError("QC-S071: Expected field type in struct", this->current_tok.pos));
                return res.to_prs();
            }

            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(new InvalidSyntaxError("QC-S072: Expected field name in struct", this->current_tok.pos));
                return res.to_prs();
            }
            Token field_name = this->current_tok;
            this->advance();

            int array_dims = 0;
            while (this->current_tok.type == TokenType::LBRACKET) {
                this->advance();
                if (this->current_tok.type == TokenType::INT) { this->advance(); }
                if (this->current_tok.type != TokenType::RBRACKET) {
                    res.failure(new InvalidSyntaxError("QC-S061: Expected ']' after '[' in array", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                array_dims++;
            }

            for (int i = 0; i < array_dims; ++i) field_type += "[]";

            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(new MissingSemicolonError(this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            fields.push_back({field_name.value, field_type});
        }
        if (this->current_tok.type != TokenType::RBRACE) {
            res.failure(new InvalidSyntaxError("QC-S073: Expected '}' at end of struct", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        if (this->current_tok.type == TokenType::SEMICOLON) { this->advance(); }
        if (user_types.contains(struct_name.value)) {
            res.failure(new InvalidSyntaxError("QC-UT01: Redefinition of struct '" + struct_name.value + "'", struct_name.pos));
            return res.to_prs();
        }
        UserTypeInfo info;
        info.kind = UserTypeKind::Struct;
        info.fields = fields;
        info.namespace_path = currentNamespace;
        std::string full_key = currentNamespace.empty() ? struct_name.value : currentNamespace + "::" + struct_name.value;
        user_types[full_key] = info;
        return res.success(std::monostate{});
    }
    if (tok.type == TokenType::KEYWORD && tok.value == "type") {
        this->advance();

        if (this->current_tok.type != TokenType::IDENTIFIER) {
            res.failure(new InvalidSyntaxError("QC-S074: Expected type name after 'type'", this->current_tok.pos));
            return res.to_prs();
        }
        Token type_name = this->current_tok;
        this->advance();

        if (this->current_tok.type != TokenType::EQ) {
            res.failure(new InvalidSyntaxError("QC-S075: Expected '=' after type name '" + type_name.value + "'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        auto parse_type_atom = [&](Token first_tok) -> UnionMember {
            std::string type_str;
            switch (first_tok.type) {
            case TokenType::STRING: return UnionMember{"string:\"" + first_tok.value + "\""};
            case TokenType::INT: return UnionMember{"int:" + first_tok.value};
            case TokenType::FLOAT: return UnionMember{"float:" + first_tok.value};
            case TokenType::DOUBLE: return UnionMember{"double:" + first_tok.value};
            case TokenType::ADDR_T: return UnionMember{"addr_t:" + first_tok.value};
            case TokenType::CHAR: return UnionMember{"char:" + first_tok.value};
            case TokenType::BOOL: return UnionMember{"bool:" + first_tok.value};
            case TokenType::QBOOL: return UnionMember{"qbool:" + first_tok.value};
            default: break;
            }
            type_str = first_tok.value;
            int array_dims = 0;
            while (this->current_tok.type == TokenType::LBRACKET) {
                this->advance();
                if (this->current_tok.type == TokenType::INT) { this->advance(); }
                if (this->current_tok.type != TokenType::RBRACKET) {
                    res.failure(new InvalidSyntaxError("QC-S061: Expected ']' after '[' in array", this->current_tok.pos));
                    return UnionMember{""};
                }
                this->advance();
                array_dims++;
            }
            for (int i = 0; i < array_dims; ++i) { type_str += "[]"; }

            return UnionMember{type_str};
        };

        auto is_type_or_literal_token = [&](TokenType tt) {
            return tt == TokenType::STRING || tt == TokenType::IDENTIFIER || tt == TokenType::KEYWORD || tt == TokenType::INT ||
                   tt == TokenType::FLOAT || tt == TokenType::DOUBLE || tt == TokenType::ADDR_T || tt == TokenType::BOOL || tt == TokenType::QBOOL ||
                   tt == TokenType::CHAR;
        };

        if (!is_type_or_literal_token(this->current_tok.type)) {
            res.failure(new InvalidSyntaxError("QC-S076: Expected type or literal in type alias", this->current_tok.pos));
            return res.to_prs();
        }

        std::vector<UnionMember> members;
        {
            Token first_tok = this->current_tok;
            this->advance();
            members.push_back(parse_type_atom(first_tok));
        }
        while (this->current_tok.type == TokenType::PIPE) {
            this->advance();

            if (!is_type_or_literal_token(this->current_tok.type)) {
                res.failure(new InvalidSyntaxError("QC-S077: Expected type or literal after '|' in type alias", this->current_tok.pos));
                return res.to_prs();
            }

            Token t = this->current_tok;
            this->advance();
            members.push_back(parse_type_atom(t));
        }

        if (this->current_tok.type != TokenType::SEMICOLON) {
            res.failure(new MissingSemicolonError(this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        if (user_types.contains(type_name.value)) {
            res.failure(new InvalidSyntaxError("QC-UT01: Redefinition of type '" + type_name.value + "'", type_name.pos));
            return res.to_prs();
        }

        UserTypeInfo info;
        if (members.size() == 1) {
            info.kind = UserTypeKind::Alias;
            info.aliasTarget = members[0].type;
        } else {
            info.kind = UserTypeKind::Union;
            info.members = members;
        }
        info.namespace_path = currentNamespace;
        std::string full_key = currentNamespace.empty() ? type_name.value : currentNamespace + "::" + type_name.value;
        user_types[full_key] = info;
        return res.success(std::monostate{});
    }
    if (tok.type == TokenType::KEYWORD && tok.value == "enum") {
        this->advance();

        if (this->current_tok.type != TokenType::IDENTIFIER) {
            res.failure(new InvalidSyntaxError("QC-S080: Expected enum name", this->current_tok.pos));
            return res.to_prs();
        }
        Token enum_name = this->current_tok;
        this->advance();

        if (this->current_tok.type != TokenType::LBRACE) {
            res.failure(new InvalidSyntaxError("QC-S003: Expected '{' after enum name", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        std::vector<UnionMember> members;
        std::vector<EnumEntry> entries;

        auto parse_type_atom = [&](Token tok) -> std::string {
            switch (tok.type) {
            case TokenType::STRING: return "string:\"" + tok.value + "\"";
            case TokenType::INT: return "int:" + tok.value;
            case TokenType::FLOAT: return "float:" + tok.value;
            case TokenType::DOUBLE: return "double:" + tok.value;
            case TokenType::ADDR_T: return "addr_t:" + tok.value;
            case TokenType::CHAR: return "char:" + tok.value;
            case TokenType::BOOL: return "bool:" + tok.value;
            case TokenType::QBOOL: return "qbool:" + tok.value;
            default: return tok.value;
            }
        };

        while (this->current_tok.type != TokenType::RBRACE && this->current_tok.type != TokenType::EOFT) {

            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(new InvalidSyntaxError("QC-S081: Expected enum member name", this->current_tok.pos));
                return res.to_prs();
            }
            Token member_name = this->current_tok;
            this->advance();

            if (this->current_tok.type != TokenType::EQ) {
                res.failure(
                    new InvalidSyntaxError("QC-S082: Expected '=' after enum member name '" + member_name.value + "'", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            Token value_tok = this->current_tok;
            this->advance();

            std::string typeAtom = parse_type_atom(value_tok);
            members.push_back(UnionMember{typeAtom});
            entries.push_back(EnumEntry{member_name.value, typeAtom});

            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(new InvalidSyntaxError("QC-S083: Expected ';' after enum member", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
        }

        if (this->current_tok.type != TokenType::RBRACE) {
            res.failure(new InvalidSyntaxError("QC-S084: Expected '}' at end of enum", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        if (user_types.contains(enum_name.value)) {
            res.failure(new InvalidSyntaxError("QC-UT01: Redefinition of type '" + enum_name.value + "'", enum_name.pos));
            return res.to_prs();
        }

        UserTypeInfo info;
        info.kind = UserTypeKind::Enum;
        info.members = members;
        info.enumEntries = entries;
        info.namespace_path = currentNamespace;
        std::string full_key = currentNamespace.empty() ? enum_name.value : currentNamespace + "::" + enum_name.value;
        user_types[full_key] = info;

        return res.success(std::monostate{});
    }
    if (tok.type == TokenType::KEYWORD) {
        bool is_const = false;

        if (tok.value == "const") {
            is_const = true;
            this->advance();
            tok = this->current_tok;

            if (tok.type != TokenType::KEYWORD) {
                res.failure(new InvalidSyntaxError("QC-S011: Expected type after 'const'", this->current_tok.pos));
                return res.to_prs();
            }
        }

        Token name_tok;
        Token type_tok = tok;
        this->advance();
        bool is_reference = false;
        if (this->current_tok.type == TokenType::AMPERSAND) {
            this->advance();
            is_reference = true;
            type_tok.value += "&";
        }

        while (this->current_tok.type == TokenType::MUL) {
            this->advance();
            type_tok.value += "*";
        }
        if (type_tok.value == "short" || type_tok.value == "long") {
            std::string modifier = type_tok.value;

            if (this->current_tok.type != TokenType::KEYWORD) {
                res.failure(new InvalidSyntaxError("QC-S059: Expected type after " + modifier, this->current_tok.pos));
                return res.to_prs();
            }

            Token base_type = this->current_tok;
            this->advance();
            if (current_tok.type == TokenType::AMPERSAND) {
                this->advance();
                base_type.value += "&";
            }
            while (current_tok.type == TokenType::MUL) {
                this->advance();
                base_type.value += "*";
            }
            type_tok.value = modifier + " " + base_type.value;
            type_tok.pos = base_type.pos;
        }

        if (type_tok.value == "map" && this->current_tok.type == TokenType::LESS) {
            this->advance();

            if (this->current_tok.type != TokenType::KEYWORD) {
                res.failure(new InvalidSyntaxError("QC-S067: Expected key type in map<K, V>", this->current_tok.pos));
                return res.to_prs();
            }
            Token key_type = this->current_tok;
            this->advance();
            if (current_tok.type == TokenType::AMPERSAND) {
                this->advance();
                key_type.value += "&";
            }
            while (current_tok.type == TokenType::MUL) {
                this->advance();
                key_type.value += "*";
            }

            if (this->current_tok.type != TokenType::COMMA) {
                res.failure(new InvalidSyntaxError("QC-S068: Expected ',' in map<K, V>", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            if (this->current_tok.type != TokenType::KEYWORD) {
                res.failure(new InvalidSyntaxError("QC-S069: Expected value type in map<K, V>", this->current_tok.pos));
                return res.to_prs();
            }
            Token value_type = this->current_tok;
            this->advance();
            if (current_tok.type == TokenType::AMPERSAND) {
                this->advance();
                value_type.value += "&";
            }
            while (current_tok.type == TokenType::MUL) {
                this->advance();
                value_type.value += "*";
            }

            if (this->current_tok.type != TokenType::MORE) {
                res.failure(new InvalidSyntaxError("QC-S070: Expected '>' in map<K, V>", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            type_tok = Token(TokenType::KEYWORD, "map<" + key_type.value + ", " + value_type.value + ">", type_tok.pos);
            if (this->current_tok.type == TokenType::IDENTIFIER) {
                Token var_name = this->current_tok;

                if (this->peek().type == TokenType::EQ || this->peek().type == TokenType::SEMICOLON) {
                    this->advance();
                    std::vector<std::pair<AnyNode, AnyNode>> init_pairs;

                    if (this->current_tok.type == TokenType::EQ) {
                        this->advance();

                        if (this->current_tok.type != TokenType::LBRACE) {
                            res.failure(new InvalidSyntaxError("QC-S003: Expected '{' for map initialization", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();

                        if (this->current_tok.type != TokenType::RBRACE) {
                            AnyNode key = res.reg(this->logical_or());
                            if (res.error) return res.to_prs();

                            if (this->current_tok.type != TokenType::COLON) {
                                res.failure(new InvalidSyntaxError("Expected ':' after key", this->current_tok.pos));
                                return res.to_prs();
                            }
                            this->advance();

                            AnyNode value = res.reg(this->logical_or());
                            if (res.error) return res.to_prs();

                            init_pairs.emplace_back(key, value);

                            while (this->current_tok.type == TokenType::COMMA) {
                                this->advance();

                                if (this->current_tok.type == TokenType::RBRACE) break;

                                AnyNode key = res.reg(this->logical_or());
                                if (res.error) return res.to_prs();

                                if (this->current_tok.type != TokenType::COLON) {
                                    res.failure(new InvalidSyntaxError("Expected ':' after key", this->current_tok.pos));
                                    return res.to_prs();
                                }
                                this->advance();

                                AnyNode value = res.reg(this->logical_or());
                                if (res.error) return res.to_prs();

                                init_pairs.emplace_back(key, value);
                            }
                        }

                        if (this->current_tok.type != TokenType::RBRACE) {
                            res.failure(new InvalidSyntaxError("Expected '}' after map initialization", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                    }

                    if (this->current_tok.type != TokenType::SEMICOLON) {
                        res.failure(new MissingSemicolonError(this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();

                    return res.success(new MapDeclNode(is_const, key_type, value_type, var_name, init_pairs));
                }
            }
        }
        bool is_list = false;
        if (type_tok.value == "list" && this->current_tok.type == TokenType::LESS) {
            this->advance();

            if (this->current_tok.type != TokenType::KEYWORD &&
                !(this->current_tok.type == TokenType::IDENTIFIER && user_types.find(this->current_tok.value) != user_types.end())) {
                res.failure(new InvalidSyntaxError("QC-S060: Expected element type in list<T>", this->current_tok.pos));
                return res.to_prs();
            }

            Token elem_type = this->current_tok;
            this->advance();
            if (current_tok.type == TokenType::AMPERSAND) {
                this->advance();
                elem_type.value += "&";
            }
            while (current_tok.type == TokenType::MUL) {
                this->advance();
                elem_type.value += "*";
            }
            if (this->current_tok.type != TokenType::MORE) {
                res.failure(new InvalidSyntaxError("QC-S061: Expected '>' in list<T>", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            type_tok = Token(TokenType::KEYWORD, "list<" + elem_type.value + ">", type_tok.pos);
            is_list = true;
        }

        while (this->current_tok.type == TokenType::LBRACKET) {
            this->advance();
            if (this->current_tok.type != TokenType::RBRACKET) {
                res.failure(new InvalidSyntaxError("QC-S049: Expected ']'", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            type_tok.value += "[]";
        }

        if (type_tok.value.find("[][]") != std::string::npos) {
            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(new InvalidSyntaxError("Multi-dimensional types can only be used in function "
                                                   "returns",
                                                   this->current_tok.pos));
                return res.to_prs();
            }

            Token func_name = this->current_tok;
            this->advance();

            if (this->current_tok.type == TokenType::LPAREN) {
                std::vector<Token> return_types = {type_tok};
                return this->func_def_multi(return_types, func_name);
            }

            res.failure(new InvalidSyntaxError("Expected '(' after function name", this->current_tok.pos));
            return res.to_prs();
        }

        std::vector<Token> return_types = {type_tok};
        if (this->current_tok.type == TokenType::COMMA) {
            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();

                if (this->current_tok.type != TokenType::KEYWORD && !find_type(this->current_tok.value)) {
                    res.failure(new InvalidSyntaxError("Expected type", this->current_tok.pos));
                    return res.to_prs();
                }

                return_types.push_back(this->current_tok);
                this->advance();
            }

            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(new InvalidSyntaxError("QC-S085: Expected identifier", this->current_tok.pos));
                return res.to_prs();
            }

            name_tok = this->current_tok;
            this->advance();
            int dimensions = 0;
            std::vector<std::optional<int>> sizes;

            while (this->current_tok.type == TokenType::LBRACKET) {
                this->advance();
                dimensions++;

                std::optional<int> size;
                if (this->current_tok.type == TokenType::INT) {
                    size = std::stoi(this->current_tok.value);
                    this->advance();
                }

                if (this->current_tok.type != TokenType::RBRACKET) {
                    res.failure(new InvalidSyntaxError("Expected closing bracket ']'", this->current_tok.pos));
                    return res.to_prs();
                }

                this->advance();
                sizes.push_back(size);
            }

            if (this->current_tok.type == TokenType::LPAREN) {
                auto func_def = res.reg(this->func_def_multi(return_types, name_tok));
                if (res.error) return res.to_prs();
                return res.success(func_def);
            }

            res.failure(new InvalidSyntaxError("Invalid syntax: use 'int x, string y = ...' for "
                                               "multi-variable "
                                               "declarations",
                                               name_tok.pos));
            return res.to_prs();
        }

        if (this->current_tok.type != TokenType::IDENTIFIER) {
            res.failure(new InvalidSyntaxError("QC-S085: Expected identifier", this->current_tok.pos));
            return res.to_prs();
        }
        name_tok = this->current_tok;
        this->advance();
        std::vector<std::optional<int>> array_sizes;
        int dimensions = 0;

        while (this->current_tok.type == TokenType::LBRACKET) {
            this->advance();
            dimensions++;

            if (this->current_tok.type == TokenType::INT) {
                array_sizes.push_back(std::stoi(this->current_tok.value));
                this->advance();
            } else {
                array_sizes.push_back(std::nullopt);
            }

            if (this->current_tok.type != TokenType::RBRACKET) {
                res.failure(new InvalidSyntaxError("QC-S049: Expected ']'", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
        }

        bool is_array = (dimensions > 0);
        if (this->current_tok.type == TokenType::LPAREN) {
            auto func_def = res.reg(this->func_def_multi(return_types, name_tok));
            if (res.error) return res.to_prs();
            return res.success(func_def);
        }
        std::vector<Token> var_names = {name_tok};

        if (this->current_tok.type == TokenType::COMMA) {
            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();

                if (this->current_tok.value == "list" && this->index + 1 < this->tokens.size() &&
                    this->tokens[this->index + 1].type == TokenType::LESS) {
                    Token list_tok = this->current_tok;
                    this->advance();
                    this->advance();

                    if (this->current_tok.type != TokenType::KEYWORD) {
                        res.failure(new InvalidSyntaxError("Expected element type in list<T>", this->current_tok.pos));
                        return res.to_prs();
                    }

                    Token elem_type = this->current_tok;
                    this->advance();

                    if (this->current_tok.type != TokenType::MORE) {
                        res.failure(new InvalidSyntaxError("Expected '>' in list<T>", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();

                    Token type = Token(TokenType::KEYWORD, "list<" + elem_type.value + ">", list_tok.pos);
                    return_types.push_back(type);
                } else if (this->current_tok.type != TokenType::KEYWORD) {
                    res.failure(new InvalidSyntaxError("Expected type", this->current_tok.pos));
                    return res.to_prs();
                } else {
                    Token type = this->current_tok;
                    this->advance();

                    while (this->current_tok.type == TokenType::LBRACKET) {
                        this->advance();
                        if (this->current_tok.type == TokenType::INT) { this->advance(); }
                        if (this->current_tok.type != TokenType::RBRACKET) {
                            res.failure(new InvalidSyntaxError("Expected ']'", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                        type.value += "[]";
                    }

                    return_types.push_back(type);
                }

                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(new InvalidSyntaxError("QC-S085: Expected identifier", this->current_tok.pos));
                    return res.to_prs();
                }
                var_names.push_back(this->current_tok);
                this->advance();
            }

            if (this->current_tok.type != TokenType::EQ) {
                res.failure(new InvalidSyntaxError("Expected '=' in multi-variable declaration", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            AnyNode value = res.reg(this->qout_expr());
            if (res.error) return res.to_prs();

            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(new MissingSemicolonError(this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            if (return_types.size() != var_names.size()) {
                res.failure(new InvalidSyntaxError("Number of types must match number of variables", var_names[0].pos));
                return res.to_prs();
            }

            return res.success(new MultiVarDeclNode(is_const, return_types, var_names, value));
        }

        if (is_list) {
            AnyNode value;
            if (this->current_tok.type == TokenType::EQ) {
                this->advance();
                value = res.reg(this->qout_expr());
                if (res.error) return res.to_prs();
            } else {
                if (is_const) {
                    res.failure(new InvalidSyntaxError("QC-T007: const variables and references must be "
                                                       "initialized",
                                                       name_tok.pos));
                    return res.to_prs();
                }
                value = new ArrayLiteralNode(std::vector<AnyNode>{}, name_tok.pos);
            }

            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(new MissingSemicolonError(this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            return res.success(new ListDeclNode(is_const, type_tok, name_tok, value));
        }

        if (is_array) {
            AnyNode value;
            if (this->current_tok.type == TokenType::EQ) {
                this->advance();
                value = res.reg(this->qout_expr());
                if (res.error) return res.to_prs();
            } else {
                if (is_const) {
                    res.failure(new InvalidSyntaxError("QC-T007: const variables must be initialized", name_tok.pos));
                    return res.to_prs();
                }
                value = default_value_for_type(type_tok, name_tok.pos);
            }

            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(new MissingSemicolonError(this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            return res.success(new ArrayDeclNode(is_const, type_tok, name_tok, value, dimensions, array_sizes));
        }
        AnyNode value;
        if (this->current_tok.type == TokenType::EQ) {
            this->advance();
            if (is_reference) {
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(new InvalidSyntaxError("QC-R001: Cannot assign an expression to a reference.", var_names[0].pos));
                    return res.to_prs();
                }

                Token target = this->current_tok;
                this->advance();
                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(new MissingSemicolonError(this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                auto ref_node = RefVarDeclNode(type_tok, var_names[0], target, type_tok.pos);
                return res.success(ref_node);
            }
            value = res.reg(this->qout_expr());
            if (res.error) return res.to_prs();
        } else {
            if (is_const || is_reference) {
                res.failure(new InvalidSyntaxError("const variables and references must be initialized", var_names[0].pos));
                return res.to_prs();
            }
            value = default_value_for_type(type_tok, var_names[0].pos);
        }

        if (this->current_tok.type != TokenType::SEMICOLON) {
            res.failure(new MissingSemicolonError(this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        return res.success(new VarAssignNode(is_const, return_types[0], var_names[0], value));
    }
    if (tok.type == TokenType::IDENTIFIER) {
        size_t saved_index = this->index;
        Token saved_tok = this->current_tok;
        auto maybe_qualified = this->try_parse_qualified_name();
        if (maybe_qualified.has_value()) {
            std::string qualified_name = *maybe_qualified;
            std::string type_name = qualified_name;
            bool is_type = false;
            auto* type_ptr = find_type(qualified_name);
            if (type_ptr) { is_type = true; }
            if (is_type) {

                Token next_tok;
                if (this->index + 1 < tokens.size()) {
                    next_tok = tokens[this->index + 1];
                } else {
                    next_tok = Token(TokenType::EOFT, "", this->current_tok.pos);
                }

                if (next_tok.type == TokenType::LPAREN) {
                    AnyNode expr = res.reg(this->qout_expr());
                    if (res.error) return res.to_prs();

                    if (this->current_tok.type != TokenType::SEMICOLON) {
                        res.failure(new MissingSemicolonError(this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                    return res.success(expr);
                }

                Token first_type = this->consume_qualified_name();
                std::vector<std::optional<int>> array_sizes;
                int dimensions = 0;
                while (this->current_tok.type == TokenType::LBRACKET) {
                    this->advance();
                    dimensions++;
                    if (this->current_tok.type == TokenType::INT) {
                        array_sizes.push_back(std::stoi(this->current_tok.value));
                        this->advance();
                    } else {
                        array_sizes.push_back(std::nullopt);
                    }
                    if (this->current_tok.type != TokenType::RBRACKET) {
                        res.failure(new InvalidSyntaxError("QC-S049: Expected ']'", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                }
                bool is_array = (dimensions > 0);
                if (this->current_tok.type == TokenType::AMPERSAND) {
                    this->advance();
                    first_type.value += "&";
                }
                while (this->current_tok.type == TokenType::MUL) {
                    this->advance();
                    first_type.value += "*";
                }
                std::vector<Token> return_types;
                return_types.push_back(first_type);
                if (this->current_tok.type == TokenType::COMMA) {
                    size_t peek_idx = this->index + 1;
                    bool is_multi_return = false;

                    if (peek_idx < tokens.size()) {
                        Token peek = tokens[peek_idx];
                        if (peek.type == TokenType::KEYWORD) {
                            is_multi_return = true;
                        } else if (peek.type == TokenType::IDENTIFIER) {
                            size_t saved = this->index;
                            Token saved_tok = this->current_tok;

                            this->advance();
                            auto peek_qual = this->try_parse_qualified_name();

                            if (peek_qual.has_value()) {
                                std::string base_name = *peek_qual;
                                size_t last_colon = peek_qual->rfind("::");
                                if (last_colon != std::string::npos) { base_name = peek_qual->substr(last_colon + 2); }
                                is_multi_return = (find_type(base_name) != nullptr || is_known_type(*peek_qual));
                            }

                            this->index = saved;
                            this->current_tok = saved_tok;
                        }
                    }

                    if (is_multi_return) {
                        while (this->current_tok.type == TokenType::COMMA) {
                            this->advance();

                            if (this->current_tok.type == TokenType::IDENTIFIER) {
                                auto next_qual = this->try_parse_qualified_name();
                                if (next_qual.has_value()) {
                                    std::string base_name = *next_qual;
                                    size_t last_colon = next_qual->rfind("::");
                                    if (last_colon != std::string::npos) { base_name = next_qual->substr(last_colon + 2); }

                                    if (is_known_type(*next_qual) || is_known_qualified_type(*next_qual) || find_type(base_name) != nullptr) {
                                        Token t = this->consume_qualified_name();
                                        if (this->current_tok.type == TokenType::AMPERSAND) {
                                            this->advance();
                                            t.value += "&";
                                        }
                                        while (this->current_tok.type == TokenType::MUL) {
                                            this->advance();
                                            t.value += "*";
                                        }

                                        return_types.push_back(t);
                                    } else {
                                        res.failure(new InvalidSyntaxError("Expected return type after ','", this->current_tok.pos));
                                        return res.to_prs();
                                    }
                                } else {
                                    res.failure(new InvalidSyntaxError("Expected return type after ','", this->current_tok.pos));
                                    return res.to_prs();
                                }
                            } else if (this->current_tok.type == TokenType::KEYWORD) {
                                Token t = this->current_tok;
                                this->advance();
                                if (this->current_tok.type == TokenType::AMPERSAND) {
                                    this->advance();
                                    t.value += "&";
                                }
                                while (this->current_tok.type == TokenType::MUL) {
                                    this->advance();
                                    t.value += "*";
                                }

                                return_types.push_back(t);
                            } else {
                                res.failure(new InvalidSyntaxError("Expected return type after ','", this->current_tok.pos));
                                return res.to_prs();
                            }
                        }
                    }
                }

                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(new InvalidSyntaxError("QC-S085: Expected name after types", this->current_tok.pos));
                    return res.to_prs();
                }

                Token name_tok = this->current_tok;
                this->advance();
                if (this->current_tok.type == TokenType::COMMA) {
                    std::vector<Token> var_names;
                    std::vector<Token> var_types;

                    var_names.push_back(name_tok);
                    var_types.push_back(first_type);

                    while (this->current_tok.type == TokenType::COMMA) {
                        this->advance();
                        Token next_type;

                        if (this->current_tok.type == TokenType::KEYWORD) {
                            next_type = this->current_tok;
                            this->advance();
                        } else if (this->current_tok.type == TokenType::IDENTIFIER) {
                            auto qual_name = this->try_parse_qualified_name();
                            if (qual_name.has_value()) {
                                std::string ns_part = "";
                                std::string base_name = *qual_name;
                                size_t last_colon = qual_name->rfind("::");
                                if (last_colon != std::string::npos) {
                                    ns_part = qual_name->substr(0, last_colon);
                                    base_name = qual_name->substr(last_colon + 2);
                                }
                                if (find_type(base_name) != nullptr || is_known_type(*qual_name)) {
                                    next_type = this->consume_qualified_name();
                                } else {
                                    res.failure(new InvalidSyntaxError("Expected type after ','", this->current_tok.pos));
                                    return res.to_prs();
                                }
                            } else {
                                res.failure(new InvalidSyntaxError("Expected type after ','", this->current_tok.pos));
                                return res.to_prs();
                            }
                        }
                        if (this->current_tok.type == TokenType::AMPERSAND) {
                            this->advance();
                            next_type.value += "&";
                        }
                        while (this->current_tok.type == TokenType::MUL) {
                            this->advance();
                            next_type.value += "*";
                        }

                        var_types.push_back(next_type);

                        if (this->current_tok.type != TokenType::IDENTIFIER) {
                            res.failure(new InvalidSyntaxError("Expected variable name", this->current_tok.pos));
                            return res.to_prs();
                        }

                        var_names.push_back(this->current_tok);
                        this->advance();
                    }

                    // Now expect = and the value
                    if (this->current_tok.type != TokenType::EQ) {
                        res.failure(new InvalidSyntaxError("Expected '=' in multi-var declaration", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();

                    AnyNode value = res.reg(this->qout_expr());
                    if (res.error) return res.to_prs();

                    if (this->current_tok.type != TokenType::SEMICOLON) {
                        res.failure(new MissingSemicolonError(this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();

                    return res.success(new MultiVarDeclNode(false, var_types, var_names, value));
                }
                if (this->current_tok.type == TokenType::LPAREN) {
                    auto func_def = res.reg(this->func_def_multi(return_types, name_tok));
                    if (res.error) return res.to_prs();
                    return res.success(func_def);
                }

                if (return_types.size() > 1) {
                    res.failure(new InvalidSyntaxError("Invalid syntax: multiple types before variable name; "
                                                       "did you mean to define a function?",
                                                       name_tok.pos));
                    return res.to_prs();
                }
                if (is_array) {
                    AnyNode value;
                    if (this->current_tok.type == TokenType::EQ) {
                        this->advance();
                        value = res.reg(this->qout_expr());
                        if (res.error) return res.to_prs();
                    } else {
                        value = default_value_for_type(first_type, name_tok.pos);
                    }
                    if (this->current_tok.type != TokenType::SEMICOLON) {
                        res.failure(new MissingSemicolonError(this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();

                    return res.success(new ArrayDeclNode(false, first_type, name_tok, value, dimensions, array_sizes));
                }
                AnyNode value;
                if (this->current_tok.type == TokenType::EQ) {
                    this->advance();
                    value = res.reg(this->qout_expr());
                    if (res.error) return res.to_prs();
                } else {
                    value = default_value_for_type(first_type, name_tok.pos);
                }

                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(new MissingSemicolonError(this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();

                return res.success(new VarAssignNode(false, first_type, name_tok, value));
            }
        }
        size_t next_i = index + 1;
        if (next_i < tokens.size() &&
            (tokens[next_i].type == TokenType::EQ || tokens[next_i].type == TokenType::PLUS_EQ || tokens[next_i].type == TokenType::MINUS_EQ ||
             tokens[next_i].type == TokenType::MUL_EQ || tokens[next_i].type == TokenType::DIV_EQ || tokens[next_i].type == TokenType::MOD_EQ)) {

            AnyNode assign_node = res.reg(this->assignment_expr());
            if (res.error) return res.to_prs();

            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(new MissingSemicolonError(this->current_tok.pos));
                return res.to_prs();
            }

            this->advance();
            return res.success(assign_node);
        }
    }

    // Expression statement: 2 + 3;
    AnyNode node = res.reg(this->assignment_expr());
    if (res.error) return res.to_prs();

    if (this->current_tok.type == TokenType::SEMICOLON) {
        this->advance();
        return res.success(node);
    }

    res.failure(new MissingSemicolonError(this->current_tok.pos));
    return res.to_prs();
}

Aer Parser::parse() {
    std::vector<AnyNode> stmts;
    bool has_main = false;
    FuncDefNode* main_func_ptr = nullptr;

    while (this->current_tok.type != TokenType::EOFT) {
        Prs result = this->statement();

        if (std::holds_alternative<Error*>(result)) { return Aer{nullptr, std::get<Error*>(result)}; }

        AnyNode stmt = std::visit(
            [&has_main, &main_func_ptr](auto arg) -> AnyNode {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, FuncDefNode*>) {
                    if (arg->name_tok.has_value() && arg->name_tok->value == entrypointName) {
                        if (arg->return_types.empty() || arg->return_types[0].value != "int") {
                            std::string actual = arg->return_types.empty() ? "void" : arg->return_types[0].value;
                            throw InvalidSyntaxError("the entrypoint must return int, not " + actual,
                                                     arg->return_types.empty() ? Position() : arg->return_types[0].pos);
                        }
                        if (!arg->params.empty() && arg->params.front().type.value != "string[]") {
                            throw InvalidSyntaxError("the entrypoint must have no parameters or "
                                                     "take a array of "
                                                     "strings.",
                                                     arg->return_types.empty() ? Position() : arg->return_types[0].pos);
                        }
                        has_main = true;
                        main_func_ptr = arg;
                    }
                }

                if constexpr (std::is_constructible_v<AnyNode, T>) { return AnyNode(arg); }
                return std::monostate{};
            },
            result);

        stmts.push_back(stmt);
    }

    if (!has_main && !no_main) {
        return Aer{nullptr, new Error("Missing the entrypoint function", "Program must have an 'int entrypointname()' function", Position())};
    }
    for (auto& [name, ut] : user_types) {
        if (ut.kind == UserTypeKind::Class && !ut.baseClassName.empty()) {
            std::string baseKey = ut.baseClassName;
            if (baseKey.find("::") == std::string::npos) {
                bool found = false;
                for (auto& [key, info] : user_types) {
                    if (key.find(baseKey) != std::string::npos && info.kind == UserTypeKind::Class) {
                        baseKey = key;
                        found = true;
                        break;
                    }
                }
                if (!found) { throw InvalidSyntaxError("Base class '" + ut.baseClassName + "' not found", Position()); }
            }

            auto it = user_types.find(baseKey);
            if (it == user_types.end() || it->second.kind != UserTypeKind::Class) {
                throw InvalidSyntaxError("class inherits from non-class or non-existent object", Position());
            }
        }
    }
    return Aer{new StatementsNode(stmts, true), nullptr, this->user_types};
}
//////////////////////////////////////////////////////////////////
// COMPILER /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#ifdef ENABLE_LLVM
llvm::Type* LLVMCompiler::llvmTypeFor(const std::string& qcType) {
    std::string type = resolveType(qcType);
    type = resolveTypeName(type);
    type = resolveType(type);
    type = resolveTypeName(type);
    if (type == "...") { return builder->getPtrTy(); }
    if (type.ends_with("[]")) { return llvm::PointerType::get(context, 0); }
    if (type.ends_with("&") || type.ends_with("*")) { return builder->getPtrTy(); }
    if (type.starts_with("list<") && type.ends_with(">")) { return llvm::PointerType::get(context, 0); }
    if (type.starts_with("map<") && type.ends_with(">")) { return llvm::PointerType::get(context, 0); }
    if (type == "int") return builder->getInt32Ty();
    if (type == "short int") return builder->getInt16Ty();
    if (type == "long int") return builder->getInt64Ty();
    if (type == "float") return builder->getFloatTy();
    if (type == "double") return builder->getDoubleTy();
    if (type == "long double") return builder->getDoubleTy();
    if (type == "addr_t") return builder->getIntNTy(getPtrSize());
    if (type == "char") return builder->getInt8Ty();
    if (type == "bool") return builder->getInt1Ty();
    if (type == "qbool") return builder->getIntNTy(2);
    if (type == "string") return llvm::PointerType::get(context, 0);
    if (type == "@nullptr") return builder->getPtrTy();
    if (classTypes.find(type) != classTypes.end()) { return classTypes[type]; }
    if (structTypes.find(type) != structTypes.end()) { return structTypes[type]; }
    if (enumTypes.find(type) != enumTypes.end()) { return enumTypes[type]; }
    if (unionTypes.find(type) != unionTypes.end()) { return unionTypes[type]; }
    if (type == "function" || type == "fn" || type.starts_with(("fn "))) { return builder->getPtrTy(); }
    return builder->getInt32Ty();
}
std::string LLVMCompiler::resolveType(const std::string& typeName) {
    auto it = typeAliases.find(typeName);
    if (it != typeAliases.end()) { return resolveType(it->second); }
    return typeName;
}
void LLVMCompiler::createUserTypes() {
    auto getFullName = [](const std::string& name, const UserTypeInfo& info) {
        if (info.namespace_path.empty()) { return name; }
        return info.namespace_path + "::" + name;
    };
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind == UserTypeKind::Enum) {
            size_t lastColon = mapKey.rfind("::");
            std::string actualName = (lastColon == std::string::npos) ? mapKey : mapKey.substr(lastColon + 2);

            std::vector<llvm::Type*> fields = {builder->getInt32Ty(), llvm::PointerType::get(context, 0)};
            llvm::StructType* enumTy = getOrCreateStructType(fields, mapKey);
            enumTypes[mapKey] = enumTy;
            for (size_t i = 0; i < info.enumEntries.size(); i++) {
                auto& entry = info.enumEntries[i];
                std::string fullName = mapKey + "." + entry.memberName;

                size_t colonPos = entry.typeAtom.find(':');
                std::string type = entry.typeAtom.substr(0, colonPos);
                std::string value = entry.typeAtom.substr(colonPos + 1);

                enumMemberInfo[fullName] = {(int)i, type, value};
            }
        }
    }
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind == UserTypeKind::Struct) {
            llvm::StructType* structTy = getOrCreateStructType(mapKey);
            structTypes[mapKey] = structTy;
        }
    }
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind == UserTypeKind::Class) {
            llvm::StructType* classTy = getOrCreateStructType(mapKey);
            classTypes[mapKey] = classTy;
        }
    }
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind == UserTypeKind::Class) {
            if (!info.baseClassName.empty()) {
                auto base_it = userTypes.find(info.baseClassName);
                if (base_it != userTypes.end() && base_it->second.is_final_class) {
                    cg_error(Position(), "Cannot inherit from final class '" + info.baseClassName + "'");
                    continue;
                }
            }
            std::vector<llvm::Type*> fieldTypes;

            std::function<void(const std::string&)> collectFields = [&](const std::string& className) {
                auto it = userTypes.find(className);
                if (it == userTypes.end()) { throw std::runtime_error("Class not found: " + className); }
                auto& classInfo = it->second;

                if (!classInfo.baseClassName.empty()) {
                    std::string baseFullName = classInfo.baseClassName;
                    if (baseFullName.find("::") == std::string::npos) {
                        for (auto& [key, info] : userTypes) {
                            if (key.find(baseFullName) != std::string::npos && info.kind == UserTypeKind::Class) {
                                baseFullName = key;
                                break;
                            }
                        }
                    }

                    collectFields(baseFullName);
                }

                for (auto& field : classInfo.classFields) { fieldTypes.push_back(llvmTypeFor(field.type)); }
            };

            collectFields(mapKey);

            if (fieldTypes.empty()) { fieldTypes.push_back(builder->getInt8Ty()); }

            classTypes[mapKey]->setBody(fieldTypes);
        }
    }
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind != UserTypeKind::Class) continue;
        if (!info.baseClassName.empty()) {
            auto base_it = userTypes.find(info.baseClassName);
            if (base_it != userTypes.end()) {
                auto& baseInfo = base_it->second;
                for (auto& method : info.classMethods) {
                    for (auto& baseMethod : baseInfo.classMethods) {
                        if (baseMethod.name_tok.value == method.name_tok.value && baseMethod.is_final) {
                            cg_error(method.name_tok.pos,
                                     "Cannot override final method '" + baseMethod.name_tok.value + "' from base class '" + info.baseClassName + "'");
                        }
                    }
                }
            }
        }
        llvm::StructType* classTy = classTypes[mapKey];

        for (auto& method : info.classMethods) {
            if (method.is_constructor && info.is_abstract_class) {
                cg_error(method.name_tok.pos, "Cannot make a constructor on a abstract class.");
                continue;
            }
            std::string methodName = mapKey + "_" + method.name_tok.value;
            std::vector<llvm::Type*> paramTypes;
            paramTypes.push_back(llvm::PointerType::get(context, 0));
            llvm::FunctionType* baseFuncTy = llvmFuncTypeFor(method.return_types, method.params);
            for (auto* paramTy : baseFuncTy->params()) { paramTypes.push_back(paramTy); }
            llvm::FunctionType* fnTy = llvm::FunctionType::get(baseFuncTy->getReturnType(), paramTypes, false);
            llvm::Function* fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, methodName, module);

            classMethods[mapKey][method.name_tok.value].push_back(fn);
        }
    }
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind == UserTypeKind::Struct) {
            std::vector<llvm::Type*> fieldTypes;

            for (auto& field : info.fields) {
                llvm::Type* ty = llvmTypeFor(field.type);
                fieldTypes.push_back(ty);
            }

            structTypes[mapKey]->setBody(fieldTypes);
        }
    }
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind == UserTypeKind::Union) {
            std::vector<llvm::Type*> fields = {builder->getInt32Ty(), llvm::PointerType::get(context, 0)};
            llvm::StructType* unionTy = getOrCreateStructType(fields, mapKey);
            unionTypes[mapKey] = unionTy;
        }
    }
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind == UserTypeKind::Alias) { typeAliases[mapKey] = info.aliasTarget; }
    }

    generateStructReprFunctions();
}
ParamTypeInfo toTypeInfo(const Parameter& p) {
    ParamTypeInfo out;

    out.type = p.type;
    out.name = p.name;
    if (p.signature.has_value()) {
        ParamTypeInfo::FunctionSignature sig;

        sig.return_types = p.signature->return_types;

        sig.params.reserve(p.signature->params.size());
        for (const auto& sub : p.signature->params) { sig.params.push_back(toTypeInfo(sub)); }

        out.signature = sig;
    }

    return out;
}
llvm::FunctionType* LLVMCompiler::llvmFuncTypeForHelper(const std::vector<Token>& returnTypes, const std::vector<ParamTypeInfo>& params) {
    std::vector<llvm::Type*> paramTypes;
    bool is_c_varargs = false;
    for (auto& p : params) {
        if (p.signature.has_value()) {
            paramTypes.push_back(llvm::PointerType::getUnqual(context));
        } else {
            if (p.type.type == TokenType::VARADIC) {
                if (p.name.value == "<varadic>") {
                    is_c_varargs = true;
                } else {
                    paramTypes.push_back(llvmTypeFor(p.type.value));
                }
                break;
            } else {
                paramTypes.push_back(llvmTypeFor(p.type.value));
            }
        }
    }
    if (returnTypes.empty()) { return llvm::FunctionType::get(builder->getVoidTy(), paramTypes, is_c_varargs); }

    if (returnTypes.size() == 1) {
        llvm::Type* retTy = llvmTypeFor(returnTypes[0].value);

        if (retTy->isArrayTy()) { retTy = llvm::PointerType::get(context, 0); }

        return llvm::FunctionType::get(retTy, paramTypes, is_c_varargs);
    }

    std::vector<llvm::Type*> retTypes;
    for (auto& rt : returnTypes) {
        llvm::Type* ty = llvmTypeFor(rt.value);
        if (ty->isArrayTy()) { ty = llvm::PointerType::get(context, 0); }

        retTypes.push_back(ty);
    }
    llvm::StructType* structTy = llvm::StructType::get(context, retTypes);
    return llvm::FunctionType::get(structTy, paramTypes, is_c_varargs);
}
llvm::FunctionType* LLVMCompiler::llvmFuncTypeFor(const std::vector<Token>& returnTypes, const std::list<Parameter>& params) {
    std::vector<ParamTypeInfo> converted;

    for (const auto& p : params) { converted.push_back(toTypeInfo(p)); }

    return llvmFuncTypeForHelper(returnTypes, converted);
}
llvm::FunctionType* LLVMCompiler::llvmFuncTypeFor(const std::vector<Token>& returnTypes, const std::vector<Parameter>& params) {
    std::vector<ParamTypeInfo> converted;

    for (const auto& p : params) { converted.push_back(toTypeInfo(p)); }

    return llvmFuncTypeForHelper(returnTypes, converted);
}
void LLVMCompiler::cg_error(const Position& pos, const std::string& msg) {
    errors.emplace_back(msg, pos);
}
llvm::Value* LLVMCompiler::createJaggedArray(AnyNode& literalNode, int elemTypeCode, int depth) {
    auto arrLit = std::get_if<ArrayLiteralNode*>(&literalNode);
    if (!arrLit) return nullptr;
    if (depth == 0) {
        int rowSize = (*arrLit)->elements.size();

        llvm::Function* createRowFn = module->getFunction("qc_create_leaf_row");
        if (!createRowFn) {
            llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
            llvm::FunctionType* fnTy = llvm::FunctionType::get(voidPtrTy, {builder->getInt32Ty(), builder->getInt32Ty()}, false);
            createRowFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_create_leaf_row", module);
        }

        llvm::Value* row = builder->CreateCall(createRowFn, {builder->getInt32(rowSize), builder->getInt32(elemTypeCode)}, "leaf_row");

        llvm::Function* setLeafFn = module->getFunction("qc_set_leaf_element");
        if (!setLeafFn) {
            llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
            llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getVoidTy(),
                                                               {voidPtrTy, builder->getInt32Ty(), voidPtrTy, builder->getInt32Ty()}, false);
            setLeafFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_set_leaf_element", module);
        }

        for (size_t j = 0; j < (*arrLit)->elements.size(); j++) {
            llvm::Value* elemVal = emitExpr((*arrLit)->elements[j]);
            if (!elemVal) continue;

            llvm::AllocaInst* tempAlloc = createEntryAlloca("temp_elem", elemVal->getType());
            builder->CreateStore(elemVal, tempAlloc);

            llvm::Value* elemPtr = builder->CreateBitCast(tempAlloc, llvm::PointerType::get(context, 0));

            builder->CreateCall(setLeafFn, {row, builder->getInt32(j), elemPtr, builder->getInt32(elemTypeCode)});
        }

        return row;
    }
    llvm::Function* createFn = module->getFunction("qc_create_jagged_array");
    if (!createFn) {
        llvm::Type* jaggedPtrTy = llvm::PointerType::get(context, 0);
        llvm::FunctionType* fnTy = llvm::FunctionType::get(jaggedPtrTy, {builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt32Ty()}, false);
        createFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_create_jagged_array", module);
    }

    int count = (*arrLit)->elements.size();
    llvm::Value* jaggedArr = builder->CreateCall(createFn, {builder->getInt32(count), builder->getInt32(elemTypeCode), builder->getInt32(depth)},
                                                 "jagged_arr");

    llvm::Function* setFn = module->getFunction("qc_set_jagged_element");
    if (!setFn) {
        llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
        llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getVoidTy(), {voidPtrTy, builder->getInt32Ty(), voidPtrTy, builder->getInt32Ty()},
                                                           false);
        setFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_set_jagged_element", module);
    }

    for (size_t i = 0; i < (*arrLit)->elements.size(); i++) {
        if (auto subLit = std::get_if<ArrayLiteralNode*>(&(*arrLit)->elements[i])) {
            llvm::Value* subArr = createJaggedArray((*arrLit)->elements[i], elemTypeCode, depth - 1);
            int subSize = (*subLit)->elements.size();

            builder->CreateCall(setFn, {jaggedArr, builder->getInt32(i), subArr, builder->getInt32(subSize)});
        }
    }

    return jaggedArr;
}
LLVMCompiler::LLVMCompiler(std::unordered_map<std::string, UserTypeInfo>& userTys, llvm::Module* mod, llvm::LLVMContext& ctx, bool is_main)
    : userTypes(userTys), context(ctx) {
    module = (mod == nullptr ? new llvm::Module("qc_module", context) : mod);
    builder = new llvm::IRBuilder<>(context);
    jaggedArraysStack.push_back({});
    arrayTypeStringsStack.push_back({});
    listsStack.push_back({});
    arrayLengthsStack.push_back({});
    mapsStack.push_back({});
    this->is_main = is_main;
}

llvm::Value* LLVMCompiler::boolToQBool(llvm::Value* boolVal) {
    llvm::Value* ext = builder->CreateZExt(boolVal, builder->getInt8Ty());
    llvm::Value* tripled = builder->CreateMul(ext, builder->getInt8(3));
    return builder->CreateTrunc(tripled, builder->getIntNTy(2));
}
llvm::Value* LLVMCompiler::emitExpr(AnyNode& node) {
    if (auto num = std::get_if<NumberNode>(&node)) {
        const std::string& text = num->tok.value;

        switch (num->tok.type) {
        case TokenType::INT: {
            long long v = std::stoll(text);
            if (v >= std::numeric_limits<int32_t>::min() && v <= std::numeric_limits<int32_t>::max()) {
                return builder->getInt32(static_cast<int32_t>(v));
            }
            return builder->getInt64(static_cast<int64_t>(v));
        }
        case TokenType::ADDR_T: {
            unsigned long long v = std::stoull(text);
            return llvm::ConstantInt::get(builder->getContext(), llvm::APInt(getPtrSize(), v));
        }
        case TokenType::FLOAT: {
            std::string t = text;
            if (!t.empty() && (std::tolower(t.back()) == 'f')) t.pop_back();
            float v = std::stof(t);
            return llvm::ConstantFP::get(builder->getFloatTy(), v);
        }
        case TokenType::DOUBLE: {
            long double v = std::stold(text);
            return llvm::ConstantFP::get(builder->getDoubleTy(), static_cast<double>(v));
        }
        default: int v = std::stoi(text); return builder->getInt32(v);
        }
    } else if (auto chr = std::get_if<CharNode>(&node)) {
        char c = chr->tok.value.empty() ? '\0' : chr->tok.value[0];
        return builder->getInt8((uint8_t)c);
    } else if (auto boolNode = std::get_if<BoolNode>(&node)) {
        bool value = (boolNode->tok.value == "true");
        return builder->getInt1(value ? 1 : 0);
    } else if (auto qbool = std::get_if<QBoolNode>(&node)) {
        uint8_t value;
        if (qbool->tok.value == "none") {
            value = 0b00;
        } else if (qbool->tok.value == "qfalse") {
            value = 0b01;
        } else if (qbool->tok.value == "qtrue") {
            value = 0b10;
        } else if (qbool->tok.value == "both") {
            value = 0b11;
        } else {
            cg_error(qbool->tok.pos, "Invalid qbool value: " + qbool->tok.value);
            return nullptr;
        }
        return llvm::ConstantInt::get(builder->getIntNTy(2), value);
    } else if (auto str = std::get_if<StringNode>(&node)) {
        llvm::Constant* strConstant = llvm::ConstantDataArray::getString(context, str->tok.value, true);
        llvm::GlobalVariable* globalStr = new llvm::GlobalVariable(*module, strConstant->getType(), true, llvm::GlobalValue::PrivateLinkage,
                                                                   strConstant, ".str");
        std::vector<llvm::Constant*> indices = {llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0),
                                                llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0)};
        return llvm::ConstantExpr::getInBoundsGetElementPtr(strConstant->getType(), globalStr, indices);
    } else if (auto bin = std::get_if<BinOpNode*>(&node)) {
        TokenType op = (*bin)->op_tok.type;
        if (op == TokenType::RSHIFT) {
            llvm::Value* leftResult = nullptr;
            if (startsWithQIn((*bin)->left_node)) {
                if (auto leftBin = std::get_if<BinOpNode*>(&(*bin)->left_node)) {
                    if ((*leftBin)->op_tok.type == TokenType::RSHIFT) {
                        while (true) {}
                        leftResult = emitExpr((*bin)->left_node);
                    }
                }
                llvm::Function* qinFn = module->getFunction("qc_qin");
                if (!qinFn) {
                    auto* fnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {}, false);
                    qinFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_qin", module);
                }

                llvm::Value* input = builder->CreateCall(qinFn, {}, "qin_input");

                if (auto varAccess = std::get_if<VarAccessNode*>(&(*bin)->right_node)) {
                    std::string varName = (*varAccess)->var_name_tok.value;
                    llvm::Value* alloc = getVarAddress(varName);
                    if (!alloc) {
                        cg_error(Position(), "qin: variable not declared: " + varName);
                        return nullptr;
                    }

                    llvm::Type* varTy = getPointeeType(varName);
                    llvm::Value* converted = input;

                    if (varTy->isIntegerTy(32)) {
                        llvm::Function* fn = module->getFunction("qc_to_int_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getInt32Ty(), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_int_from_string", module);
                        }
                        converted = builder->CreateCall(fn, {input});
                    } else if (varTy->isIntegerTy(16)) {
                        llvm::Function* fn = module->getFunction("qc_to_short_int_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getInt16Ty(), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_short_int_from_string", module);
                        }
                        converted = builder->CreateCall(fn, {input});
                    } else if (varTy->isIntegerTy(64)) {
                        llvm::Function* fn = module->getFunction("qc_to_long_int_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getInt64Ty(), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_long_int_from_string", module);
                        }
                        converted = builder->CreateCall(fn, {input});
                    } else if (varTy->isFloatTy()) {
                        llvm::Function* fn = module->getFunction("qc_to_float_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getFloatTy(), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_float_from_string", module);
                        }
                        converted = builder->CreateCall(fn, {input});
                    } else if (varTy->isDoubleTy()) {
                        llvm::Function* fn = module->getFunction("qc_to_double_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getDoubleTy(), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_double_from_string", module);
                        }
                        converted = builder->CreateCall(fn, {input});
                    } else if (varTy->isIntegerTy(8)) {
                        llvm::Function* fn = module->getFunction("qc_to_char_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getInt8Ty(), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_char_from_string", module);
                        }
                        converted = builder->CreateCall(fn, {input});
                    } else if (varTy->isIntegerTy(1)) {
                        llvm::Function* fn = module->getFunction("qc_to_bool_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getInt1Ty(), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_bool_from_string", module);
                        }
                        converted = builder->CreateCall(fn, {input});
                    } else if (varTy->isIntegerTy(2)) {
                        llvm::Function* fn = module->getFunction("qc_to_qbool_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getIntNTy(2), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_qbool_from_string", module);
                        }
                        converted = builder->CreateCall(fn, {input});
                    }

                    builder->CreateStore(converted, alloc);

                    return builder->getInt32(0);
                }

                cg_error(Position(), "qin: right side must be a variable");
                return nullptr;
            }
        }
        llvm::Value* L = emitExpr((*bin)->left_node);
        llvm::Value* R = emitExpr((*bin)->right_node);
        if (!L || !R) return nullptr;
        llvm::Type* lty = L->getType();
        llvm::Type* rty = R->getType();
        if (lty->isPointerTy()) {
            if (auto varAccess = std::get_if<VarAccessNode*>(&(*bin)->left_node)) {
                std::string varName = (*varAccess)->var_name_tok.value;
                llvm::Value* alloc = getVarAddress(varName);
                if (alloc) {
                    llvm::Type* allocTy = getPointeeType(varName);

                    if (auto structTy = llvm::dyn_cast<llvm::StructType>(allocTy)) {
                        if (structTy->hasName()) {
                            std::string className = structTy->getName().str();

                            if (classTypes.find(className) != classTypes.end()) {
                                std::string opMethodName = getOperatorMethodName((*bin)->op_tok.type);

                                if (!opMethodName.empty()) {
                                    std::vector<llvm::Value*> args = {R};
                                    llvm::Function* opMethod = findMethodOverload(className, opMethodName, args);

                                    if (opMethod) {
                                        std::vector<llvm::Value*> allArgs = {L, R};
                                        return builder->CreateCall(opMethod, allArgs, "op_result");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        bool isEq = (*bin)->op_tok.type == TokenType::EQ_TO;
        bool isNe = (*bin)->op_tok.type == TokenType::NOT_EQ;

        if (isEq || isNe) {
            llvm::Type* lTy = L->getType();
            llvm::Type* rTy = R->getType();

            std::string lUnionName, rUnionName;
            bool lIsUnion = isUnionType(lTy, &lUnionName);
            bool rIsUnion = isUnionType(rTy, &rUnionName);
            std::string lEnumName, rEnumName;
            bool lIsEnum = isEnumType(lTy, &lEnumName);
            bool rIsEnum = isEnumType(rTy, &rEnumName);
            if (lIsUnion && !rIsUnion) {
                auto match = matchValueToUnionVariant(lUnionName, (*bin)->right_node, R);

                if (!match) {
                    llvm::Value* res = builder->getFalse();
                    if (isNe) res = builder->CreateNot(res);
                    return res;
                }

                auto info = *match;
                llvm::Value* tag = builder->CreateExtractValue(L, 0, "union_tag");
                llvm::Value* dataPtr = builder->CreateExtractValue(L, 1, "union_data");

                llvm::Value* tagMatch = builder->CreateICmpEQ(tag, builder->getInt32(info.tagIndex), "union_tag_match");
                llvm::BasicBlock* matchBB = llvm::BasicBlock::Create(context, "tag_matches", currentFunction);
                llvm::BasicBlock* mismatchBB = llvm::BasicBlock::Create(context, "tag_mismatch", currentFunction);
                llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "cmp_end", currentFunction);

                builder->CreateCondBr(tagMatch, matchBB, mismatchBB);

                builder->SetInsertPoint(matchBB);
                llvm::Value* payloadMatch = nullptr;

                if (!info.memberTypeStr.empty()) {
                    llvm::Type* memberTy = llvmTypeFor(info.memberTypeStr);

                    if (memberTy->isPointerTy()) {
                        llvm::Value* payload = builder->CreateBitCast(dataPtr, memberTy);

                        llvm::Function* strcmp_fn = module->getFunction("qc_string_eq");
                        if (!strcmp_fn) {
                            auto* i8Ptr = llvm::PointerType::get(context, 0);
                            auto* fnTy = llvm::FunctionType::get(builder->getInt1Ty(), {i8Ptr, i8Ptr}, false);
                            strcmp_fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_string_eq", module);
                        }
                        payloadMatch = builder->CreateCall(strcmp_fn, {payload, R}, "payload_str_eq");
                    } else {
                        llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                        llvm::Value* payload = builder->CreateLoad(memberTy, typedPtr, "union_payload");

                        if (memberTy->isIntegerTy()) {
                            payloadMatch = builder->CreateICmpEQ(payload, R, "union_int_eq");
                        } else if (memberTy->isFloatingPointTy()) {
                            payloadMatch = builder->CreateFCmpOEQ(payload, R, "union_fp_eq");
                        }
                    }
                }

                llvm::Value* fullMatch = payloadMatch ? payloadMatch : builder->getTrue();
                if (fullMatch->getType() != builder->getInt1Ty()) { fullMatch = builder->CreateTrunc(fullMatch, builder->getInt1Ty()); }
                builder->CreateBr(endBB);

                builder->SetInsertPoint(mismatchBB);
                builder->CreateBr(endBB);

                builder->SetInsertPoint(endBB);
                llvm::PHINode* phi = builder->CreatePHI(builder->getInt1Ty(), 2, "cmp_result");
                phi->addIncoming(fullMatch, matchBB);
                phi->addIncoming(builder->getFalse(), mismatchBB);

                llvm::Value* result = phi;
                if (isNe) { result = builder->CreateNot(result); }
                return result;
            }
            if (!lIsUnion && rIsUnion) {
                auto match = matchValueToUnionVariant(rUnionName, (*bin)->left_node, L);
                if (!match) {
                    llvm::Value* res = builder->getFalse();
                    if (isNe) res = builder->CreateNot(res);
                    return res;
                }

                auto info = *match;
                llvm::Value* tag = builder->CreateExtractValue(R, 0, "union_tag");
                llvm::Value* dataPtr = builder->CreateExtractValue(R, 1, "union_data");

                llvm::Value* tagMatch = builder->CreateICmpEQ(tag, builder->getInt32(info.tagIndex), "union_tag_match");

                llvm::BasicBlock* matchBB = llvm::BasicBlock::Create(context, "tag_matches", currentFunction);
                llvm::BasicBlock* mismatchBB = llvm::BasicBlock::Create(context, "tag_mismatch", currentFunction);
                llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "cmp_end", currentFunction);

                builder->CreateCondBr(tagMatch, matchBB, mismatchBB);

                builder->SetInsertPoint(matchBB);
                llvm::Value* payloadMatch = nullptr;

                if (!info.memberTypeStr.empty()) {
                    llvm::Type* memberTy = llvmTypeFor(info.memberTypeStr);

                    if (memberTy->isPointerTy()) {
                        llvm::Value* payload = builder->CreateBitCast(dataPtr, memberTy);

                        llvm::Function* strcmp_fn = module->getFunction("qc_string_eq");
                        if (!strcmp_fn) {
                            auto* i8Ptr = llvm::PointerType::get(context, 0);
                            auto* fnTy = llvm::FunctionType::get(builder->getInt1Ty(), {i8Ptr, i8Ptr}, false);
                            strcmp_fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_string_eq", module);
                        }
                        payloadMatch = builder->CreateCall(strcmp_fn, {L, payload}, "payload_str_eq");
                    } else {
                        llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                        llvm::Value* payload = builder->CreateLoad(memberTy, typedPtr, "union_payload");

                        if (memberTy->isIntegerTy()) {
                            payloadMatch = builder->CreateICmpEQ(L, payload, "union_int_eq");
                        } else if (memberTy->isFloatingPointTy()) {
                            payloadMatch = builder->CreateFCmpOEQ(L, payload, "union_fp_eq");
                        }
                    }
                }

                llvm::Value* fullMatch = payloadMatch ? payloadMatch : builder->getTrue();
                if (fullMatch->getType() != builder->getInt1Ty()) { fullMatch = builder->CreateTrunc(fullMatch, builder->getInt1Ty()); }
                builder->CreateBr(endBB);

                builder->SetInsertPoint(mismatchBB);
                builder->CreateBr(endBB);

                builder->SetInsertPoint(endBB);
                llvm::PHINode* phi = builder->CreatePHI(builder->getInt1Ty(), 2, "cmp_result");
                phi->addIncoming(fullMatch, matchBB);
                phi->addIncoming(builder->getFalse(), mismatchBB);

                llvm::Value* result = phi;
                if (isNe) { result = builder->CreateNot(result); }
                return result;
            }
            if (lIsUnion && rIsUnion) {
                llvm::Value* lhsTag = builder->CreateExtractValue(L, 0, "lhs_tag");
                llvm::Value* rhsTag = builder->CreateExtractValue(R, 0, "rhs_tag");
                llvm::Value* tagsEqual = builder->CreateICmpEQ(lhsTag, rhsTag, "tags_equal");

                llvm::BasicBlock* tagMatchBB = llvm::BasicBlock::Create(context, "tags_match", currentFunction);
                llvm::BasicBlock* tagMismatchBB = llvm::BasicBlock::Create(context, "tags_mismatch", currentFunction);
                llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "union_cmp_end", currentFunction);

                builder->CreateCondBr(tagsEqual, tagMatchBB, tagMismatchBB);
                builder->SetInsertPoint(tagMatchBB);

                llvm::Value* lhsPayload = builder->CreateExtractValue(L, 1, "lhs_payload");
                llvm::Value* rhsPayload = builder->CreateExtractValue(R, 1, "rhs_payload");

                auto& members = userTypes[lUnionName].members;
                llvm::BasicBlock* payloadEndBB = llvm::BasicBlock::Create(context, "payload_cmp_end", currentFunction);
                llvm::BasicBlock* defaultBB = llvm::BasicBlock::Create(context, "cmp_default", currentFunction);
                llvm::SwitchInst* sw = builder->CreateSwitch(lhsTag, defaultBB, members.size());
                std::vector<std::pair<llvm::BasicBlock*, llvm::Value*>> caseResults;

                for (size_t i = 0; i < members.size(); i++) {
                    llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "cmp_case_" + std::to_string(i), currentFunction);
                    sw->addCase(builder->getInt32(i), caseBB);
                    builder->SetInsertPoint(caseBB);

                    std::string typeStr = members[i].type;
                    size_t colonPos = typeStr.find(':');
                    if (colonPos != std::string::npos) { typeStr = typeStr.substr(0, colonPos); }

                    llvm::Type* memberTy = llvmTypeFor(typeStr);

                    llvm::Value *lhsVal, *rhsVal;

                    if (memberTy->isPointerTy()) {
                        lhsVal = builder->CreateBitCast(lhsPayload, memberTy);
                        rhsVal = builder->CreateBitCast(rhsPayload, memberTy);
                    } else {
                        llvm::Value* lhsTyped = builder->CreateBitCast(lhsPayload, llvm::PointerType::get(context, 0));
                        llvm::Value* rhsTyped = builder->CreateBitCast(rhsPayload, llvm::PointerType::get(context, 0));
                        lhsVal = builder->CreateLoad(memberTy, lhsTyped);
                        rhsVal = builder->CreateLoad(memberTy, rhsTyped);
                    }
                    llvm::Value* cmp;
                    if (memberTy->isIntegerTy()) {
                        cmp = builder->CreateICmpEQ(lhsVal, rhsVal);
                    } else if (memberTy->isFloatingPointTy()) {
                        cmp = builder->CreateFCmpOEQ(lhsVal, rhsVal);
                    } else if (memberTy->isPointerTy()) {
                        llvm::Function* strcmp_fn = module->getFunction("qc_string_eq");
                        cmp = builder->CreateCall(strcmp_fn, {lhsVal, rhsVal});
                        cmp = builder->CreateTrunc(cmp, builder->getInt1Ty());
                    } else {
                        cmp = builder->getTrue();
                    }

                    caseResults.push_back({caseBB, cmp});
                    builder->CreateBr(payloadEndBB);
                }
                builder->SetInsertPoint(defaultBB);
                builder->CreateBr(payloadEndBB);
                builder->SetInsertPoint(payloadEndBB);
                llvm::PHINode* payloadPhi = builder->CreatePHI(builder->getInt1Ty(), caseResults.size());
                for (auto& [bb, val] : caseResults) { payloadPhi->addIncoming(val, bb); }
                payloadPhi->addIncoming(builder->getFalse(), defaultBB);
                builder->CreateBr(endBB);

                builder->SetInsertPoint(tagMismatchBB);
                builder->CreateBr(endBB);

                builder->SetInsertPoint(endBB);
                llvm::PHINode* finalPhi = builder->CreatePHI(builder->getInt1Ty(), 2);
                finalPhi->addIncoming(payloadPhi, payloadEndBB);
                finalPhi->addIncoming(builder->getFalse(), tagMismatchBB);

                llvm::Value* result = finalPhi;
                if (isNe) { result = builder->CreateNot(result); }
                return result;
            } else if (lIsEnum && !rIsEnum && !rIsUnion) {
                auto match = matchValueToEnumMember(lEnumName, (*bin)->right_node, R);
                if (!match) {
                    llvm::Value* res = builder->getFalse();
                    if (isNe) res = builder->CreateNot(res);
                    return res;
                }

                auto info = *match;
                llvm::Value* tag = builder->CreateExtractValue(L, 0, "union_tag");
                llvm::Value* dataPtr = builder->CreateExtractValue(L, 1, "union_data");

                llvm::Value* tagMatch = builder->CreateICmpEQ(tag, builder->getInt32(info.tagIndex), "union_tag_match");
                llvm::BasicBlock* matchBB = llvm::BasicBlock::Create(context, "tag_matches", currentFunction);
                llvm::BasicBlock* mismatchBB = llvm::BasicBlock::Create(context, "tag_mismatch", currentFunction);
                llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "cmp_end", currentFunction);

                builder->CreateCondBr(tagMatch, matchBB, mismatchBB);

                builder->SetInsertPoint(matchBB);
                llvm::Value* payloadMatch = nullptr;

                if (!info.memberTypeStr.empty()) {
                    llvm::Type* memberTy = llvmTypeFor(info.memberTypeStr);

                    if (memberTy->isPointerTy()) {
                        llvm::Value* payload = builder->CreateBitCast(dataPtr, memberTy);

                        llvm::Function* strcmp_fn = module->getFunction("qc_string_eq");
                        if (!strcmp_fn) {
                            auto* i8Ptr = llvm::PointerType::get(context, 0);
                            auto* fnTy = llvm::FunctionType::get(builder->getInt1Ty(), {i8Ptr, i8Ptr}, false);
                            strcmp_fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_string_eq", module);
                        }
                        payloadMatch = builder->CreateCall(strcmp_fn, {payload, R}, "payload_str_eq");
                    } else {
                        llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                        llvm::Value* payload = builder->CreateLoad(memberTy, typedPtr, "union_payload");

                        if (memberTy->isIntegerTy()) {
                            payloadMatch = builder->CreateICmpEQ(payload, R, "union_int_eq");
                        } else if (memberTy->isFloatingPointTy()) {
                            payloadMatch = builder->CreateFCmpOEQ(payload, R, "union_fp_eq");
                        }
                    }
                }

                llvm::Value* fullMatch = payloadMatch ? payloadMatch : builder->getTrue();
                if (fullMatch->getType() != builder->getInt1Ty()) { fullMatch = builder->CreateTrunc(fullMatch, builder->getInt1Ty()); }
                builder->CreateBr(endBB);

                builder->SetInsertPoint(mismatchBB);
                builder->CreateBr(endBB);

                builder->SetInsertPoint(endBB);
                llvm::PHINode* phi = builder->CreatePHI(builder->getInt1Ty(), 2, "cmp_result");
                phi->addIncoming(fullMatch, matchBB);
                phi->addIncoming(builder->getFalse(), mismatchBB);

                llvm::Value* result = phi;
                if (isNe) { result = builder->CreateNot(result); }
                return result;
            }

            else if (!lIsUnion && !lIsEnum && rIsEnum) {
                auto match = matchValueToEnumMember(rEnumName, (*bin)->left_node, L);
                if (!match) {
                    llvm::Value* res = builder->getFalse();
                    if (isNe) res = builder->CreateNot(res);
                    return res;
                }

                auto info = *match;
                llvm::Value* tag = builder->CreateExtractValue(R, 0, "union_tag");
                llvm::Value* dataPtr = builder->CreateExtractValue(R, 1, "union_data");

                llvm::Value* tagMatch = builder->CreateICmpEQ(tag, builder->getInt32(info.tagIndex), "union_tag_match");

                llvm::BasicBlock* matchBB = llvm::BasicBlock::Create(context, "tag_matches", currentFunction);
                llvm::BasicBlock* mismatchBB = llvm::BasicBlock::Create(context, "tag_mismatch", currentFunction);
                llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "cmp_end", currentFunction);

                builder->CreateCondBr(tagMatch, matchBB, mismatchBB);

                builder->SetInsertPoint(matchBB);
                llvm::Value* payloadMatch = nullptr;

                if (!info.memberTypeStr.empty()) {
                    llvm::Type* memberTy = llvmTypeFor(info.memberTypeStr);

                    if (memberTy->isPointerTy()) {
                        llvm::Value* payload = builder->CreateBitCast(dataPtr, memberTy);

                        llvm::Function* strcmp_fn = module->getFunction("qc_string_eq");
                        if (!strcmp_fn) {
                            auto* i8Ptr = llvm::PointerType::get(context, 0);
                            auto* fnTy = llvm::FunctionType::get(builder->getInt1Ty(), {i8Ptr, i8Ptr}, false);
                            strcmp_fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_string_eq", module);
                        }
                        payloadMatch = builder->CreateCall(strcmp_fn, {L, payload}, "payload_str_eq");
                    } else {
                        llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                        llvm::Value* payload = builder->CreateLoad(memberTy, typedPtr, "union_payload");

                        if (memberTy->isIntegerTy()) {
                            payloadMatch = builder->CreateICmpEQ(L, payload, "union_int_eq");
                        } else if (memberTy->isFloatingPointTy()) {
                            payloadMatch = builder->CreateFCmpOEQ(L, payload, "union_fp_eq");
                        }
                    }
                }

                llvm::Value* fullMatch = payloadMatch ? payloadMatch : builder->getTrue();
                if (fullMatch->getType() != builder->getInt1Ty()) { fullMatch = builder->CreateTrunc(fullMatch, builder->getInt1Ty()); }
                builder->CreateBr(endBB);

                builder->SetInsertPoint(mismatchBB);
                builder->CreateBr(endBB);

                builder->SetInsertPoint(endBB);
                llvm::PHINode* phi = builder->CreatePHI(builder->getInt1Ty(), 2, "cmp_result");
                phi->addIncoming(fullMatch, matchBB);
                phi->addIncoming(builder->getFalse(), mismatchBB);

                llvm::Value* result = phi;
                if (isNe) { result = builder->CreateNot(result); }
                return result;
            } else if (lIsEnum && rIsEnum) {
                llvm::Value* lhsTag = builder->CreateExtractValue(L, 0, "lhs_tag");
                llvm::Value* rhsTag = builder->CreateExtractValue(R, 0, "rhs_tag");
                llvm::Value* tagsEqual = builder->CreateICmpEQ(lhsTag, rhsTag, "tags_equal");

                llvm::BasicBlock* tagMatchBB = llvm::BasicBlock::Create(context, "tags_match", currentFunction);
                llvm::BasicBlock* tagMismatchBB = llvm::BasicBlock::Create(context, "tags_mismatch", currentFunction);
                llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "union_cmp_end", currentFunction);

                builder->CreateCondBr(tagsEqual, tagMatchBB, tagMismatchBB);
                builder->SetInsertPoint(tagMatchBB);

                llvm::Value* lhsPayload = builder->CreateExtractValue(L, 1, "lhs_payload");
                llvm::Value* rhsPayload = builder->CreateExtractValue(R, 1, "rhs_payload");

                auto& entries = userTypes[lEnumName].enumEntries;
                llvm::BasicBlock* payloadEndBB = llvm::BasicBlock::Create(context, "payload_cmp_end", currentFunction);
                llvm::BasicBlock* defaultBB = llvm::BasicBlock::Create(context, "cmp_default", currentFunction);
                llvm::SwitchInst* sw = builder->CreateSwitch(lhsTag, defaultBB, entries.size());
                std::vector<std::pair<llvm::BasicBlock*, llvm::Value*>> caseResults;

                for (size_t i = 0; i < entries.size(); i++) {
                    llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "cmp_case_" + std::to_string(i), currentFunction);
                    sw->addCase(builder->getInt32(i), caseBB);
                    builder->SetInsertPoint(caseBB);

                    std::string typeStr = entries[i].typeAtom;
                    size_t colonPos = typeStr.find(':');
                    if (colonPos != std::string::npos) { typeStr = typeStr.substr(0, colonPos); }

                    llvm::Type* memberTy = llvmTypeFor(typeStr);

                    llvm::Value *lhsVal, *rhsVal;

                    if (memberTy->isPointerTy()) {
                        lhsVal = builder->CreateBitCast(lhsPayload, memberTy);
                        rhsVal = builder->CreateBitCast(rhsPayload, memberTy);
                    } else {
                        llvm::Value* lhsTyped = builder->CreateBitCast(lhsPayload, llvm::PointerType::get(context, 0));
                        llvm::Value* rhsTyped = builder->CreateBitCast(rhsPayload, llvm::PointerType::get(context, 0));
                        lhsVal = builder->CreateLoad(memberTy, lhsTyped);
                        rhsVal = builder->CreateLoad(memberTy, rhsTyped);
                    }
                    llvm::Value* cmp;
                    if (memberTy->isIntegerTy()) {
                        cmp = builder->CreateICmpEQ(lhsVal, rhsVal);
                    } else if (memberTy->isFloatingPointTy()) {
                        cmp = builder->CreateFCmpOEQ(lhsVal, rhsVal);
                    } else if (memberTy->isPointerTy()) {
                        llvm::Function* strcmp_fn = module->getFunction("qc_string_eq");
                        cmp = builder->CreateCall(strcmp_fn, {lhsVal, rhsVal});
                        cmp = builder->CreateTrunc(cmp, builder->getInt1Ty());
                    } else {
                        cmp = builder->getTrue();
                    }

                    caseResults.push_back({caseBB, cmp});
                    builder->CreateBr(payloadEndBB);
                }
                builder->SetInsertPoint(defaultBB);
                builder->CreateBr(payloadEndBB);
                builder->SetInsertPoint(payloadEndBB);
                llvm::PHINode* payloadPhi = builder->CreatePHI(builder->getInt1Ty(), caseResults.size());
                for (auto& [bb, val] : caseResults) { payloadPhi->addIncoming(val, bb); }
                payloadPhi->addIncoming(builder->getFalse(), defaultBB);
                builder->CreateBr(endBB);

                builder->SetInsertPoint(tagMismatchBB);
                builder->CreateBr(endBB);

                builder->SetInsertPoint(endBB);
                llvm::PHINode* finalPhi = builder->CreatePHI(builder->getInt1Ty(), 2);
                finalPhi->addIncoming(payloadPhi, payloadEndBB);
                finalPhi->addIncoming(builder->getFalse(), tagMismatchBB);

                llvm::Value* result = finalPhi;
                if (isNe) { result = builder->CreateNot(result); }
                return result;
            }
        }
        if ((*bin)->is_f) {
            std::function<llvm::Value*(llvm::Value*, const Position&)> toString = [&](llvm::Value* v, const Position& pos) -> llvm::Value* {
                llvm::Type* ty = v->getType();
                if (ty->isIntegerTy(32)) {
                    auto* fn = module->getFunction("qc_to_string_int");
                    if (!fn) {
                        auto* i8Ptr = llvm::PointerType::get(context, 0);
                        auto* fnTy = llvm::FunctionType::get(i8Ptr, {builder->getInt32Ty()}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_string_int", module);
                    }
                    return builder->CreateCall(fn, {v}, "fstr_i32");
                }
                if (ty->isIntegerTy(16)) {
                    auto* fn = module->getFunction("qc_to_string_short_int");
                    if (!fn) {
                        auto* i8Ptr = llvm::PointerType::get(context, 0);
                        auto* fnTy = llvm::FunctionType::get(i8Ptr, {builder->getInt16Ty()}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_string_short_int", module);
                    }
                    return builder->CreateCall(fn, {v}, "fstr_i16");
                }
                if (ty->isIntegerTy(64)) {
                    auto* fn = module->getFunction("qc_to_string_long_int");
                    if (!fn) {
                        auto* i8Ptr = llvm::PointerType::get(context, 0);
                        auto* fnTy = llvm::FunctionType::get(i8Ptr, {builder->getInt64Ty()}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_string_long_int", module);
                    }
                    return builder->CreateCall(fn, {v}, "fstr_i64");
                }
                if (ty->isDoubleTy()) {
                    auto* fn = module->getFunction("qc_to_string_double");
                    if (!fn) {
                        auto* i8Ptr = llvm::PointerType::get(context, 0);
                        auto* fnTy = llvm::FunctionType::get(i8Ptr, {builder->getDoubleTy()}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_string_double", module);
                    }
                    return builder->CreateCall(fn, {v}, "fstr_f64");
                }
                if (ty->isFloatTy()) {
                    auto* fn = module->getFunction("qc_to_string_float");
                    if (!fn) {
                        auto* i8Ptr = llvm::PointerType::get(context, 0);
                        auto* fnTy = llvm::FunctionType::get(i8Ptr, {builder->getDoubleTy()}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_string_float", module);
                    }
                    return builder->CreateCall(fn, {v}, "fstr_f32");
                }
                if (ty->isIntegerTy(1)) {
                    auto* fn = module->getFunction("qc_to_string_bool");
                    if (!fn) {
                        auto* i8Ptr = llvm::PointerType::get(context, 0);
                        auto* fnTy = llvm::FunctionType::get(i8Ptr, {builder->getInt1Ty()}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_string_bool", module);
                    }
                    return builder->CreateCall(fn, {v}, "fstr_bool");
                }
                if (ty->isIntegerTy(8)) {
                    auto* fn = module->getFunction("qc_to_string_char");
                    if (!fn) {
                        auto* i8Ptr = llvm::PointerType::get(context, 0);
                        auto* fnTy = llvm::FunctionType::get(i8Ptr, {builder->getInt32Ty()}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_string_char", module);
                    }
                    return builder->CreateCall(fn, {v}, "fstr_i8");
                }
                if (ty->isPointerTy()) { return v; }
                if (ty->isIntegerTy(2)) {
                    auto* fn = module->getFunction("qc_to_string_qbool");
                    if (!fn) {
                        auto* i8Ptr = llvm::PointerType::get(context, 0);
                        auto* fnTy = llvm::FunctionType::get(i8Ptr, {builder->getIntNTy(2)}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_string_qbool", module);
                    }
                    return builder->CreateCall(fn, {v}, "fstr_qbool");
                }

                if (ty->isArrayTy()) {
                    std::vector<uint64_t> dimensions;
                    llvm::Type* checkTy = ty;
                    while (checkTy->isArrayTy()) {
                        dimensions.push_back(checkTy->getArrayNumElements());
                        checkTy = checkTy->getArrayElementType();
                    }
                    int elemTypeCode = -1;
                    if (checkTy->isIntegerTy(32))
                        elemTypeCode = 0;
                    else if (checkTy->isIntegerTy(64))
                        elemTypeCode = 0;
                    else if (checkTy->isIntegerTy(16))
                        elemTypeCode = 0;
                    else if (checkTy->isFloatTy())
                        elemTypeCode = 1;
                    else if (checkTy->isDoubleTy())
                        elemTypeCode = 2;
                    else if (checkTy->isIntegerTy(8))
                        elemTypeCode = 3;
                    else if (checkTy->isIntegerTy(1))
                        elemTypeCode = 4;
                    else if (checkTy->isIntegerTy(2))
                        elemTypeCode = 5;
                    else if (checkTy->isPointerTy())
                        elemTypeCode = 6;

                    llvm::ArrayType* dimsArrTy = llvm::ArrayType::get(builder->getInt32Ty(), dimensions.size());
                    llvm::AllocaInst* dimsAlloc = createEntryAlloca("fstr_dims", dimsArrTy);

                    for (size_t i = 0; i < dimensions.size(); i++) {
                        std::vector<llvm::Value*> indices = {builder->getInt32(0), builder->getInt32(i)};
                        llvm::Value* dimPtr = builder->CreateInBoundsGEP(dimsArrTy, dimsAlloc, indices);
                        builder->CreateStore(builder->getInt32(dimensions[i]), dimPtr);
                    }
                    llvm::Value* arrPtr = builder->CreateBitCast(v, llvm::PointerType::get(context, 0));

                    std::vector<llvm::Value*> dimsIndices = {builder->getInt32(0), builder->getInt32(0)};
                    llvm::Value* dimsPtr = builder->CreateInBoundsGEP(dimsArrTy, dimsAlloc, dimsIndices);

                    auto* fn = module->getFunction("qc_array_to_string_recursive");
                    if (!fn) {
                        auto* voidPtrTy = llvm::PointerType::get(context, 0);
                        auto* intPtrTy = llvm::PointerType::get(context, 0);
                        auto* fnTy = llvm::FunctionType::get(voidPtrTy, {voidPtrTy, builder->getInt32Ty(), builder->getInt32Ty(), intPtrTy}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_array_to_string_recursive", module);
                    }

                    return builder->CreateCall(fn, {arrPtr, builder->getInt32(elemTypeCode), builder->getInt32(dimensions.size()), dimsPtr},
                                               "fstr_array");
                }
                if (auto structTy = llvm::dyn_cast<llvm::StructType>(ty)) {
                    if (structTy->hasName()) {
                        std::string className = structTy->getName().str();

                        if (classTypes.find(className) != classTypes.end()) {
                            auto [reprMethod, ownerClass] = findMethodInHierarchy(className, "repr");

                            if (reprMethod) {
                                std::vector<llvm::Value*> args;

                                llvm::AllocaInst* temp = createEntryAlloca("temp_repr", ty);
                                builder->CreateStore(v, temp);
                                args.push_back(temp);

                                return builder->CreateCall(reprMethod, args, "repr_result");
                            }
                        }
                    }
                }

                for (auto& [enumName, enumTy] : enumTypes) {
                    if (ty == enumTy) {
                        llvm::Value* dataPtr = builder->CreateExtractValue(v, 1, "enum_data");
                        return builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                    }
                }

                for (auto& [unionName, unionTy] : unionTypes) {
                    if (ty == unionTy) {
                        auto& members = userTypes[unionName].members;
                        llvm::Value* tag = builder->CreateExtractValue(v, 0, "union_tag");
                        llvm::Value* payload = builder->CreateExtractValue(v, 1, "union_payload");

                        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "fstr_union_end", currentFunction);
                        llvm::AllocaInst* resultAlloc = createEntryAlloca("fstr_union_result", llvm::PointerType::get(context, 0));

                        llvm::SwitchInst* sw = builder->CreateSwitch(tag, endBB, members.size());

                        for (size_t i = 0; i < members.size(); i++) {
                            llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "fstr_union_case_" + std::to_string(i), currentFunction);
                            sw->addCase(builder->getInt32(i), caseBB);
                            builder->SetInsertPoint(caseBB);

                            std::string ts = members[i].type;
                            size_t c = ts.find(':');
                            if (c != std::string::npos) ts = ts.substr(0, c);
                            llvm::Type* memberTy = llvmTypeFor(ts);

                            llvm::Value* memberVal;
                            if (memberTy->isPointerTy()) {
                                memberVal = builder->CreateBitCast(payload, memberTy);
                            } else {
                                llvm::Value* typedPtr = builder->CreateBitCast(payload, llvm::PointerType::get(context, 0));
                                memberVal = builder->CreateLoad(memberTy, typedPtr, "union_member");
                            }
                            AnyNode fakeNode = std::monostate{};
                            llvm::Value* strVal = toString(memberVal, pos);
                            if (!strVal) strVal = builder->CreateGlobalString("?");
                            builder->CreateStore(strVal, resultAlloc);
                            builder->CreateBr(endBB);
                        }

                        builder->SetInsertPoint(endBB);
                        return builder->CreateLoad(llvm::PointerType::get(context, 0), resultAlloc, "fstr_union_result");
                    }
                }
                if (ty->isPointerTy()) { return v; }

                cg_error(pos, "f-string: unsupported type in compiled mode");
                return nullptr;
            };

            llvm::Value* lStr = toString(L, (*bin)->op_tok.pos);
            llvm::Value* rStr = toString(R, (*bin)->op_tok.pos);
            if (!lStr || !rStr) return nullptr;

            llvm::Function* concatFn = module->getFunction("qc_string_concat");
            if (!concatFn) {
                auto* i8Ptr = llvm::PointerType::get(context, 0);
                std::vector<llvm::Type*> argTypes = {i8Ptr, i8Ptr};
                auto* fnTy = llvm::FunctionType::get(i8Ptr, argTypes, false);
                concatFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_string_concat", module);
            }

            return builder->CreateCall(concatFn, {lStr, rStr}, "fstr_concat");
        }
        std::string lUnion, rUnion;
        bool lIsUnion = isUnionType(L->getType(), &lUnion);
        bool rIsUnion = isUnionType(R->getType(), &rUnion);
        if (lIsUnion && rIsUnion) {
            auto& members = userTypes[lUnion].members;
            llvm::Value* lTag = builder->CreateExtractValue(L, 0, "ltag");
            llvm::Value* lPayload = builder->CreateExtractValue(L, 1, "lpayload");
            llvm::Value* rPayload = builder->CreateExtractValue(R, 1, "rpayload");

            llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "union_op_end", currentFunction);
            bool isComparison = op == TokenType::LESS || op == TokenType::MORE || op == TokenType::LESS_EQ || op == TokenType::MORE_EQ;
            llvm::AllocaInst* resultAlloc = createEntryAlloca("union_op_result", isComparison ? builder->getInt1Ty() : builder->getDoubleTy());

            llvm::SwitchInst* sw = builder->CreateSwitch(lTag, endBB, members.size());

            for (size_t i = 0; i < members.size(); i++) {
                llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "union_op_case_" + std::to_string(i), currentFunction);
                sw->addCase(builder->getInt32(i), caseBB);
                builder->SetInsertPoint(caseBB);

                std::string ts = members[i].type;
                size_t c = ts.find(':');
                if (c != std::string::npos) ts = ts.substr(0, c);
                llvm::Type* memberTy = llvmTypeFor(ts);

                llvm::Value* lTypedPtr = builder->CreateBitCast(lPayload, llvm::PointerType::get(context, 0));
                llvm::Value* rTypedPtr = builder->CreateBitCast(rPayload, llvm::PointerType::get(context, 0));
                llvm::Value* lhsVal = builder->CreateLoad(memberTy, lTypedPtr, "lmember");
                llvm::Value* rhsVal = builder->CreateLoad(memberTy, rTypedPtr, "rmember");

                bool isFP = memberTy->isFloatingPointTy();
                llvm::Value* res = nullptr;
                switch (op) {
                case TokenType::LESS: res = isFP ? builder->CreateFCmpOLT(lhsVal, rhsVal) : builder->CreateICmpSLT(lhsVal, rhsVal); break;
                case TokenType::MORE: res = isFP ? builder->CreateFCmpOGT(lhsVal, rhsVal) : builder->CreateICmpSGT(lhsVal, rhsVal); break;
                case TokenType::LESS_EQ: res = isFP ? builder->CreateFCmpOLE(lhsVal, rhsVal) : builder->CreateICmpSLE(lhsVal, rhsVal); break;
                case TokenType::MORE_EQ: res = isFP ? builder->CreateFCmpOGE(lhsVal, rhsVal) : builder->CreateICmpSGE(lhsVal, rhsVal); break;
                case TokenType::PLUS: res = isFP ? builder->CreateFAdd(lhsVal, rhsVal) : builder->CreateAdd(lhsVal, rhsVal); break;
                case TokenType::MINUS: res = isFP ? builder->CreateFSub(lhsVal, rhsVal) : builder->CreateSub(lhsVal, rhsVal); break;
                case TokenType::MUL: res = isFP ? builder->CreateFMul(lhsVal, rhsVal) : builder->CreateMul(lhsVal, rhsVal); break;
                case TokenType::DIV: res = isFP ? builder->CreateFDiv(lhsVal, rhsVal) : builder->CreateSDiv(lhsVal, rhsVal); break;
                case TokenType::AMPERSAND: res = builder->CreateAnd(lhsVal, rhsVal); break;
                case TokenType::PIPE: res = builder->CreateOr(lhsVal, rhsVal); break;
                case TokenType::BITWISE_XOR: res = builder->CreateXor(lhsVal, rhsVal); break;
                case TokenType::LSHIFT: res = builder->CreateShl(lhsVal, rhsVal); break;
                case TokenType::RSHIFT: res = builder->CreateAShr(lhsVal, rhsVal); break;
                case TokenType::LOGICAL_RSHIFT: res = builder->CreateLShr(lhsVal, rhsVal); break;
                case TokenType::L_ROT:
                case TokenType::R_ROT: {
                    llvm::Intrinsic::ID id = (op == TokenType::L_ROT) ? llvm::Intrinsic::fshl : llvm::Intrinsic::fshr;
                    llvm::Function* rotFunc = llvm::Intrinsic::getOrInsertDeclaration(module, id, {lhsVal->getType()});
                    res = builder->CreateCall(rotFunc, {lhsVal, lhsVal, rhsVal});
                    break;
                }
                default: res = lhsVal; break;
                }

                llvm::Type* allocTy = resultAlloc->getAllocatedType();
                if (res->getType() != allocTy) {
                    if (allocTy->isDoubleTy() && res->getType()->isIntegerTy())
                        res = builder->CreateSIToFP(res, allocTy);
                    else if (allocTy->isDoubleTy() && res->getType()->isFloatTy())
                        res = builder->CreateFPExt(res, allocTy);
                }
                builder->CreateStore(res, resultAlloc);
                builder->CreateBr(endBB);
            }

            builder->SetInsertPoint(endBB);
            return builder->CreateLoad(resultAlloc->getAllocatedType(), resultAlloc, "union_op_result");
        }
        if (lIsUnion || rIsUnion) {
            std::string unionName = lIsUnion ? lUnion : rUnion;
            auto& members = userTypes[unionName].members;
            llvm::Value* unionVal = lIsUnion ? L : R;
            llvm::Value* otherVal = lIsUnion ? R : L;

            llvm::Value* tag = builder->CreateExtractValue(unionVal, 0, "tag");
            llvm::Value* payload = builder->CreateExtractValue(unionVal, 1, "payload");

            llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "union_op_end", currentFunction);
            bool isComparison = op == TokenType::LESS || op == TokenType::MORE || op == TokenType::LESS_EQ || op == TokenType::MORE_EQ;
            llvm::Type* resultTy = isComparison ? builder->getInt1Ty() : builder->getDoubleTy();
            llvm::AllocaInst* resultAlloc = createEntryAlloca("union_op_result", resultTy);

            llvm::SwitchInst* sw = builder->CreateSwitch(tag, endBB, members.size());
            std::vector<llvm::BasicBlock*> caseBBs;

            for (size_t i = 0; i < members.size(); i++) {
                llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "union_op_case_" + std::to_string(i), currentFunction);
                sw->addCase(builder->getInt32(i), caseBB);
                builder->SetInsertPoint(caseBB);

                std::string ts = members[i].type;
                size_t c = ts.find(':');
                if (c != std::string::npos) ts = ts.substr(0, c);
                llvm::Type* memberTy = llvmTypeFor(ts);

                llvm::Value* typedPtr = builder->CreateBitCast(payload, llvm::PointerType::get(context, 0));
                llvm::Value* memberVal = builder->CreateLoad(memberTy, typedPtr, "member");

                llvm::Value* lhsVal = lIsUnion ? memberVal : otherVal;
                llvm::Value* rhsVal = lIsUnion ? otherVal : memberVal;

                llvm::Type* lTy = lhsVal->getType();
                llvm::Type* rTy = rhsVal->getType();
                if (lTy != rTy) {
                    if (lTy->isDoubleTy() || rTy->isDoubleTy()) {
                        if (!lTy->isDoubleTy())
                            lhsVal = lTy->isFloatTy() ? builder->CreateFPExt(lhsVal, builder->getDoubleTy())
                                                      : builder->CreateSIToFP(lhsVal, builder->getDoubleTy());
                        if (!rTy->isDoubleTy())
                            rhsVal = rTy->isFloatTy() ? builder->CreateFPExt(rhsVal, builder->getDoubleTy())
                                                      : builder->CreateSIToFP(rhsVal, builder->getDoubleTy());
                    } else if (lTy->isFloatTy() || rTy->isFloatTy()) {
                        if (!lTy->isFloatTy()) lhsVal = builder->CreateSIToFP(lhsVal, builder->getFloatTy());
                        if (!rTy->isFloatTy()) rhsVal = builder->CreateSIToFP(rhsVal, builder->getFloatTy());
                    } else if (lTy->isIntegerTy() && rTy->isIntegerTy()) {
                        unsigned lBits = lTy->getIntegerBitWidth();
                        unsigned rBits = rTy->getIntegerBitWidth();
                        if (lBits < rBits)
                            lhsVal = builder->CreateSExt(lhsVal, rTy);
                        else
                            rhsVal = builder->CreateSExt(rhsVal, lTy);
                    } else if (lTy->isIntegerTy() && rTy->isFloatingPointTy()) {
                        lhsVal = builder->CreateSIToFP(lhsVal, rTy);
                    } else if (lTy->isFloatingPointTy() && rTy->isIntegerTy()) {
                        rhsVal = builder->CreateSIToFP(rhsVal, lTy);
                    }
                }

                bool isFP = lhsVal->getType()->isFloatingPointTy();
                llvm::Value* res = nullptr;
                switch (op) {
                case TokenType::LESS: res = isFP ? builder->CreateFCmpOLT(lhsVal, rhsVal) : builder->CreateICmpSLT(lhsVal, rhsVal); break;
                case TokenType::MORE: res = isFP ? builder->CreateFCmpOGT(lhsVal, rhsVal) : builder->CreateICmpSGT(lhsVal, rhsVal); break;
                case TokenType::LESS_EQ: res = isFP ? builder->CreateFCmpOLE(lhsVal, rhsVal) : builder->CreateICmpSLE(lhsVal, rhsVal); break;
                case TokenType::MORE_EQ: res = isFP ? builder->CreateFCmpOGE(lhsVal, rhsVal) : builder->CreateICmpSGE(lhsVal, rhsVal); break;
                case TokenType::PLUS: res = isFP ? builder->CreateFAdd(lhsVal, rhsVal) : builder->CreateAdd(lhsVal, rhsVal); break;
                case TokenType::MINUS: res = isFP ? builder->CreateFSub(lhsVal, rhsVal) : builder->CreateSub(lhsVal, rhsVal); break;
                case TokenType::MUL: res = isFP ? builder->CreateFMul(lhsVal, rhsVal) : builder->CreateMul(lhsVal, rhsVal); break;
                case TokenType::DIV: res = isFP ? builder->CreateFDiv(lhsVal, rhsVal) : builder->CreateSDiv(lhsVal, rhsVal); break;
                case TokenType::AMPERSAND:
                case TokenType::PIPE:
                case TokenType::BITWISE_XOR:
                case TokenType::LSHIFT:
                case TokenType::RSHIFT:
                case TokenType::LOGICAL_RSHIFT:
                    if (isFP) {
                        cg_error((*bin)->op_tok.pos, "Bitwise operations not allowed on "
                                                     "floating-point union members");
                        return nullptr;
                    }
                    if (op == TokenType::AMPERSAND)
                        res = builder->CreateAnd(lhsVal, rhsVal);
                    else if (op == TokenType::PIPE)
                        res = builder->CreateOr(lhsVal, rhsVal);
                    else if (op == TokenType::BITWISE_XOR)
                        res = builder->CreateXor(lhsVal, rhsVal);
                    else if (op == TokenType::LSHIFT)
                        res = builder->CreateShl(lhsVal, rhsVal);
                    else if (op == TokenType::RSHIFT)
                        res = builder->CreateAShr(lhsVal, rhsVal);
                    else
                        res = builder->CreateLShr(lhsVal, rhsVal);
                    break;
                case TokenType::L_ROT:
                case TokenType::R_ROT: {
                    if (isFP) {
                        cg_error((*bin)->op_tok.pos, "Rotation not allowed on floating-point union "
                                                     "members");
                        return nullptr;
                    }
                    llvm::Intrinsic::ID id = (op == TokenType::L_ROT) ? llvm::Intrinsic::fshl : llvm::Intrinsic::fshr;
                    llvm::Function* rotFunc = llvm::Intrinsic::getOrInsertDeclaration(module, id, {lhsVal->getType()});
                    res = builder->CreateCall(rotFunc, {lhsVal, lhsVal, rhsVal});
                    break;
                }
                default: res = memberVal; break;
                }
                llvm::Type* allocTy = resultAlloc->getAllocatedType();
                if (res->getType() != allocTy) {
                    if (allocTy->isDoubleTy() && res->getType()->isIntegerTy())
                        res = builder->CreateSIToFP(res, allocTy);
                    else if (allocTy->isDoubleTy() && res->getType()->isFloatTy())
                        res = builder->CreateFPExt(res, allocTy);
                }
                builder->CreateStore(res, resultAlloc);
                builder->CreateBr(endBB);
                caseBBs.push_back(caseBB);
            }

            builder->SetInsertPoint(endBB);
            return builder->CreateLoad(resultAlloc->getAllocatedType(), resultAlloc, "union_op_result");
        }

        L = normalizeValue(L, (*bin)->left_node);
        R = normalizeValue(R, (*bin)->right_node);
        lty = L->getType();
        rty = R->getType();
        if (auto lStructTy = llvm::dyn_cast<llvm::StructType>(lty)) {
            if (lStructTy->hasName()) {
                std::string className = lStructTy->getName().str();

                if (classTypes.find(className) != classTypes.end()) {
                    std::string opMethodName = getOperatorMethodName((*bin)->op_tok.type);

                    if (!opMethodName.empty()) {
                        std::vector<llvm::Value*> args = {R};
                        llvm::Function* opMethod = findMethodOverload(className, opMethodName, args);

                        if (opMethod) {
                            llvm::AllocaInst* temp = createEntryAlloca("temp_op_lhs", lty);
                            builder->CreateStore(L, temp);

                            std::vector<llvm::Value*> allArgs = {temp, R};
                            return builder->CreateCall(opMethod, allArgs, "op_result");
                        }
                    }
                }
            }
        }
        if ((lty == builder->getInt8Ty() || rty == builder->getInt8Ty()) && (op == TokenType::PLUS || op == TokenType::MINUS)) {
            if (lty == builder->getInt8Ty() && rty != builder->getInt8Ty()) {
                L = builder->CreateSExt(L, rty, "char_promote");
                lty = rty;
            } else if (rty == builder->getInt8Ty() && lty != builder->getInt8Ty()) {
                R = builder->CreateSExt(R, lty, "char_promote");
                rty = lty;
            }
        }
        if (lty != rty) {
            if (lty->isFloatTy() && rty->isDoubleTy()) {
                L = builder->CreateFPExt(L, rty, "promote_to_double");
                lty = rty;
            } else if (rty->isFloatTy() && lty->isDoubleTy()) {
                R = builder->CreateFPExt(R, lty, "promote_to_double");
                rty = lty;
            } else if (lty->isIntegerTy() && rty->isIntegerTy()) {
                unsigned lBits = lty->getIntegerBitWidth();
                unsigned rBits = rty->getIntegerBitWidth();
                if (lBits == 1 || rBits == 1 || lBits == 2 || rBits == 2 || lBits == 8 || rBits == 8) {
                    if (lBits != rBits) {}
                } else {
                    if (lBits < rBits) {
                        L = builder->CreateSExt(L, rty, "promote_int");
                        lty = rty;
                    } else if (rBits < lBits) {
                        R = builder->CreateSExt(R, lty, "promote_int");
                        rty = lty;
                    }
                }
            } else if (lty->isIntegerTy() && rty->isFloatingPointTy()) {
                L = builder->CreateSIToFP(L, rty, "int_to_float");
                lty = rty;
            } else if (rty->isIntegerTy() && lty->isFloatingPointTy()) {
                R = builder->CreateSIToFP(R, lty, "int_to_float");
                rty = lty;
            }
        }
        bool isFloatTy = lty->isFloatingPointTy();
        switch ((*bin)->op_tok.type) {
        case TokenType::PLUS:
            if (lty == builder->getInt8Ty() || rty == builder->getInt8Ty()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform this operation on char types");
                return nullptr;
            }
            if (lty->isPointerTy() || rty->isPointerTy()) {
                std::string lType = getExpressionType((*bin)->left_node);
                std::string rType = getExpressionType((*bin)->right_node);

                if (lType.ends_with("*") || lType == "@nullptr") {
                    if (lType == "void*") {
                        cg_error((*bin)->op_tok.pos, "Pointer arithmetic cannot be preformed on "
                                                     "void pointers");
                        return nullptr;
                    }
                    if (rType != "int") {
                        cg_error((*bin)->op_tok.pos, "Pointer arithmetic may only be preformed on "
                                                     "ptr lhs and "
                                                     "int rhs, got " +
                                                         lType + " and " + rType);
                        return nullptr;
                    }
                    lType.pop_back();
                    return builder->CreateGEP(llvmTypeFor(lType), L, R, "ptr_arith_plus");
                } else {
                    if (lType != rType) {
                        cg_error((*bin)->op_tok.pos, "You can only add string with string, got " + lType + " and " + rType);
                        return nullptr;
                    }
                    llvm::Function* concatFn = module->getFunction("qc_string_concat");
                    if (!concatFn) {
                        llvm::Type* i8PtrTy = llvm::PointerType::get(context, 0);
                        std::vector<llvm::Type*> argTypes = {i8PtrTy, i8PtrTy};
                        llvm::FunctionType* fnTy = llvm::FunctionType::get(i8PtrTy, argTypes, false);
                        concatFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_string_concat", module);
                    }
                    return builder->CreateCall(concatFn, {L, R}, "str_concat");
                }
                cg_error((*bin)->op_tok.pos, "Cannot perform arithmetic on types " + lType + " + " + " rType");
                return nullptr;
            }
            if (lty == builder->getInt1Ty() || rty == builder->getInt1Ty()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform arithmetic on bool types");
                return nullptr;
            }

            if (lty == builder->getIntNTy(2) || rty == builder->getIntNTy(2)) {
                cg_error((*bin)->op_tok.pos, "Cannot perform arithmetic on qbool types");
                return nullptr;
            }
            return isFloatTy ? builder->CreateFAdd(L, R, "fadd") : builder->CreateAdd(L, R, "add");
        case TokenType::MINUS:
            if (lty == builder->getInt8Ty() || rty == builder->getInt8Ty()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform this operation on char types");
                return nullptr;
            }
            if (lty->isPointerTy() || rty->isPointerTy()) {
                std::string lType = getExpressionType((*bin)->left_node);
                std::string rType = getExpressionType((*bin)->right_node);

                if ((lType.ends_with("*") || lType == "@nullptr") && (rType.ends_with("*") || rType == "@nullptr")) {
                    if (lType == "void*") {
                        cg_error((*bin)->op_tok.pos, "Pointer arithmetic cannot be preformed on "
                                                     "void pointers");
                        return nullptr;
                    }
                    if (rType == "void*") {
                        cg_error((*bin)->op_tok.pos, "Pointer arithmetic cannot be preformed on "
                                                     "void pointers");
                        return nullptr;
                    }
                    if (lType != rType) {
                        cg_error((*bin)->op_tok.pos, "Pointer arithmetic may only be preformed on "
                                                     "the same lhs "
                                                     "and rhs type, got " +
                                                         lType + " and " + rType);
                        return nullptr;
                    }
                    std::string baseType = (lType == "@nullptr") ? rType : lType;
                    if (baseType == "@nullptr") { return builder->getInt32(0); }
                    baseType.pop_back();
                    llvm::Value* diff = builder->CreatePtrDiff(llvmTypeFor(baseType), L, R, "ptr_diff");
                    return builder->CreateTrunc(diff, builder->getInt32Ty());
                } else if (lType.ends_with("*") && rType == "int") {
                    std::string baseType = lType;
                    baseType.pop_back();
                    llvm::Value* negR = builder->CreateNeg(R, "neg_offset");
                    return builder->CreateGEP(llvmTypeFor(baseType), L, {negR}, "ptr_arith_minus");
                }

                cg_error((*bin)->op_tok.pos, "Invalid pointer subtraction: " + lType + " - " + rType);
                return nullptr;
            }
            if (lty == builder->getInt1Ty() || rty == builder->getInt1Ty()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform arithmetic on bool types");
                return nullptr;
            }

            if (lty == builder->getIntNTy(2) || rty == builder->getIntNTy(2)) {
                cg_error((*bin)->op_tok.pos, "Cannot perform arithmetic on qbool types");
                return nullptr;
            }
            return isFloatTy ? builder->CreateFSub(L, R, "fsub") : builder->CreateSub(L, R, "sub");
        case TokenType::MUL:
            if (lty == builder->getInt8Ty() || rty == builder->getInt8Ty()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform this operation on char types");
                return nullptr;
            }
            if (lty->isPointerTy() || rty->isPointerTy()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform this operation on string types");
                return nullptr;
            }
            if (lty == builder->getInt1Ty() || rty == builder->getInt1Ty()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform arithmetic on bool types");
                return nullptr;
            }

            if (lty == builder->getIntNTy(2) || rty == builder->getIntNTy(2)) {
                cg_error((*bin)->op_tok.pos, "Cannot perform arithmetic on qbool types");
                return nullptr;
            }
            return isFloatTy ? builder->CreateFMul(L, R, "fmul") : builder->CreateMul(L, R, "mul");
        case TokenType::DIV:
            if (lty == builder->getInt8Ty() || rty == builder->getInt8Ty()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform this operation on char types");
                return nullptr;
            }
            if (lty->isPointerTy() || rty->isPointerTy()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform this operation on string types");
                return nullptr;
            }
            if (lty == builder->getInt1Ty() || rty == builder->getInt1Ty()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform arithmetic on bool types");
                return nullptr;
            }

            if (lty == builder->getIntNTy(2) || rty == builder->getIntNTy(2)) {
                cg_error((*bin)->op_tok.pos, "Cannot perform arithmetic on qbool types");
                return nullptr;
            }
            return isFloatTy ? builder->CreateFDiv(L, R, "fdiv") : builder->CreateSDiv(L, R, "sdiv");
        case TokenType::MOD:
            if (lty == builder->getInt8Ty() || rty == builder->getInt8Ty()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform this operation on char types");
                return nullptr;
            }
            if (lty->isPointerTy() || rty->isPointerTy()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform this operation on string types");
                return nullptr;
            }
            if (lty == builder->getInt1Ty() || rty == builder->getInt1Ty()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform arithmetic on bool types");
                return nullptr;
            }

            if (lty == builder->getIntNTy(2) || rty == builder->getIntNTy(2)) {
                cg_error((*bin)->op_tok.pos, "Cannot perform arithmetic on qbool types");
                return nullptr;
            }
            return isFloatTy ? builder->CreateFRem(L, R, "frem") : builder->CreateSRem(L, R, "srem");
        case TokenType::AMPERSAND:
        case TokenType::PIPE:
        case TokenType::BITWISE_XOR:
            if (isFloatTy) {
                cg_error((*bin)->op_tok.pos, "Cannot perform bitwise operations on float/double types");
                return nullptr;
            }
            if (lty->isPointerTy() || rty->isPointerTy()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform bitwise operations on string types");
                return nullptr;
            }
            if ((*bin)->op_tok.type == TokenType::AMPERSAND) return builder->CreateAnd(L, R, "andtmp");
            if ((*bin)->op_tok.type == TokenType::PIPE) return builder->CreateOr(L, R, "ortmp");
            return builder->CreateXor(L, R, "xortmp");
        case TokenType::RSHIFT:
        case TokenType::LSHIFT:
        case TokenType::LOGICAL_RSHIFT:
            if (isFloatTy) {
                cg_error((*bin)->op_tok.pos, "Cannot perform shifts on float/double types");
                return nullptr;
            }
            if ((*bin)->op_tok.type == TokenType::LSHIFT) return builder->CreateShl(L, R, "shltmp");
            if ((*bin)->op_tok.type == TokenType::RSHIFT) return builder->CreateAShr(L, R, "ashrtmp");
            return builder->CreateLShr(L, R, "lshrtmp");
        case TokenType::L_ROT:
        case TokenType::R_ROT:
            if (isFloatTy) {
                cg_error((*bin)->op_tok.pos, "Cannot perform rotations on float/double types");
                return nullptr;
            }
            {
                llvm::Intrinsic::ID id = ((*bin)->op_tok.type == TokenType::L_ROT) ? llvm::Intrinsic::fshl : llvm::Intrinsic::fshr;
                llvm::Function* rotFunc = llvm::Intrinsic::getOrInsertDeclaration(module, id, {lty});
                return builder->CreateCall(rotFunc, {L, L, R}, "rottmp");
            }
        case TokenType::POWER: {
            if (lty == builder->getInt8Ty() || rty == builder->getInt8Ty()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform this operation on char types");
                return nullptr;
            }
            if (lty->isPointerTy() || rty->isPointerTy()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform this operation on string types");
                return nullptr;
            }
            if (lty == builder->getInt1Ty() || rty == builder->getInt1Ty()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform arithmetic on bool types");
                return nullptr;
            }

            if (lty == builder->getIntNTy(2) || rty == builder->getIntNTy(2)) {
                cg_error((*bin)->op_tok.pos, "Cannot perform arithmetic on qbool types");
                return nullptr;
            }
            llvm::Type* ty = L->getType();

            if (ty->isIntegerTy()) {
                llvm::Function* qc_powi = module->getFunction("qc_powi_i32");
                if (!qc_powi) {
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getInt32Ty(), {builder->getInt32Ty(), builder->getInt32Ty()}, false);
                    qc_powi = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_powi_i32", module);
                }
                return builder->CreateCall(qc_powi, {L, R}, "powi");
            } else if (ty->isFloatTy() || ty->isDoubleTy()) {
                llvm::Function* powFn = llvm::Intrinsic::getOrInsertDeclaration(module, llvm::Intrinsic::pow, {ty});
                return builder->CreateCall(powFn, {L, R}, "pow");
            } else {
                cg_error((*bin)->op_tok.pos, "POWER not supported for this type");
                return nullptr;
            }
        }
        case TokenType::EQ_TO:
        case TokenType::NOT_EQ: {
            if (lty->isIntegerTy() && rty->isIntegerTy()) {
                unsigned lBits = lty->getIntegerBitWidth();
                unsigned rBits = rty->getIntegerBitWidth();
                if (lBits == 1 || rBits == 1 || lBits == 2 || rBits == 2) {
                    if (lBits == rBits) {
                        return (op == TokenType::EQ_TO) ? builder->CreateICmpEQ(L, R, "icmpeq") : builder->CreateICmpNE(L, R, "icmpne");
                    } else {
                        return builder->getInt1(op == TokenType::NOT_EQ ? 1 : 0);
                    }
                }
                if (lBits < rBits) {
                    L = builder->CreateSExt(L, rty, "promote");
                } else if (rBits < lBits) {
                    R = builder->CreateSExt(R, lty, "promote");
                }

                return (op == TokenType::EQ_TO) ? builder->CreateICmpEQ(L, R, "icmpeq") : builder->CreateICmpNE(L, R, "icmpne");
            }
            if ((lty->isFloatingPointTy() && rty->isFloatingPointTy())) {
                return (op == TokenType::EQ_TO) ? builder->CreateFCmpOEQ(L, R, "fcmpeq") : builder->CreateFCmpONE(L, R, "fcmpne");
            }
            if (lty->isPointerTy() && rty->isPointerTy()) {
                std::string lType = getExpressionType((*bin)->left_node);
                std::string rType = getExpressionType((*bin)->right_node);

                if (lType.ends_with("*") || rType.ends_with("*") || lType == "@nullptr" || rType == "@nullptr") {
                    if (op == TokenType::EQ_TO) {
                        return builder->CreateICmpEQ(L, R, "ptr_eq");
                    } else {
                        return builder->CreateICmpNE(L, R, "ptr_ne");
                    }
                } else {
                    llvm::Function* strcmp_fn = module->getFunction("qc_string_eq");
                    llvm::Value* result = builder->CreateCall(strcmp_fn, {L, R});
                    if (op == TokenType::NOT_EQ) { result = builder->CreateNot(result); }
                    return result;
                }
            }
            if (op == TokenType::EQ_TO) {
                return builder->getInt1(0);
            } else {
                return builder->getInt1(1);
            }
        }
        case TokenType::QEQEQ:
        case TokenType::QNEQ: {
            llvm::Value* boolResult = nullptr;

            if (lty->isIntegerTy() && rty->isIntegerTy()) {
                unsigned lBits = lty->getIntegerBitWidth();
                unsigned rBits = rty->getIntegerBitWidth();

                if (lBits == 1 || rBits == 1 || lBits == 2 || rBits == 2) {
                    if (lBits == rBits) {
                        boolResult = (op == TokenType::QEQEQ) ? builder->CreateICmpEQ(L, R, "qicmpeq") : builder->CreateICmpNE(L, R, "qicmpne");
                    } else {
                        return builder->getIntN(2, 0);
                    }
                } else {
                    if (lBits < rBits) {
                        L = builder->CreateSExt(L, rty, "promote");
                    } else if (rBits < lBits) {
                        R = builder->CreateSExt(R, lty, "promote");
                    }

                    boolResult = (op == TokenType::QEQEQ) ? builder->CreateICmpEQ(L, R, "qicmpeq") : builder->CreateICmpNE(L, R, "qicmpne");
                }
            } else if (lty->isFloatingPointTy() && rty->isFloatingPointTy()) {
                boolResult = (op == TokenType::QEQEQ) ? builder->CreateFCmpOEQ(L, R, "qfcmpeq") : builder->CreateFCmpONE(L, R, "qfcmpne");
            } else if (lty->isPointerTy() && rty->isPointerTy()) {
                llvm::Function* strcmp_fn = module->getFunction("qc_string_eq");
                llvm::Value* cmp = builder->CreateCall(strcmp_fn, {L, R});

                if (op == TokenType::QNEQ) { cmp = builder->CreateNot(cmp); }

                boolResult = builder->CreateTrunc(cmp, builder->getInt1Ty());
            } else {
                return builder->getIntN(2, 0);
            }
            llvm::Value* ext = builder->CreateZExt(boolResult, builder->getInt8Ty());
            llvm::Value* tripled = builder->CreateMul(ext, builder->getInt8(3));
            return builder->CreateTrunc(tripled, builder->getIntNTy(2));
        }
        case TokenType::LESS:
        case TokenType::MORE:
        case TokenType::LESS_EQ:
        case TokenType::MORE_EQ: {
            if (lty == builder->getInt8Ty() || rty == builder->getInt8Ty()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform this operation on char types");
                return nullptr;
            }
            if (lty->isPointerTy() || rty->isPointerTy()) {
                cg_error((*bin)->op_tok.pos, "Cannot perform this operation on string types");
                return nullptr;
            }
            if (lty->isIntegerTy() && rty->isIntegerTy()) {
                unsigned lBits = lty->getIntegerBitWidth();
                unsigned rBits = rty->getIntegerBitWidth();
                if (lBits == 1 || lBits == 2 || rBits == 1 || rBits == 2) {
                    cg_error((*bin)->op_tok.pos, "Cannot use comparison operators on bool/qbool");
                    return nullptr;
                }
                bool isFloatTy = false;
            } else if (lty->isFloatingPointTy() && rty->isFloatingPointTy()) {
                bool isFloatTy = true;
            } else {
                cg_error((*bin)->op_tok.pos, "Cannot compare non-numeric types with <, >, <=, >=");
                return nullptr;
            }
            switch (op) {
            case TokenType::LESS: return isFloatTy ? builder->CreateFCmpOLT(L, R, "fcmplt") : builder->CreateICmpSLT(L, R, "icmplt");
            case TokenType::MORE: return isFloatTy ? builder->CreateFCmpOGT(L, R, "fcmpgt") : builder->CreateICmpSGT(L, R, "icmpgt");
            case TokenType::LESS_EQ: return isFloatTy ? builder->CreateFCmpOLE(L, R, "fcmple") : builder->CreateICmpSLE(L, R, "icmple");
            case TokenType::MORE_EQ: return isFloatTy ? builder->CreateFCmpOGE(L, R, "fcmpge") : builder->CreateICmpSGE(L, R, "icmpge");
            default: break;
            }
        }
        case TokenType::AND:
            L = toTruthiness(L, Position("", "", 0, 0, 0));
            R = toTruthiness(R, Position("", "", 0, 0, 0));
            return builder->CreateAnd(L, R, "and");
        case TokenType::OR:
            L = toTruthiness(L, Position("", "", 0, 0, 0));
            R = toTruthiness(R, Position("", "", 0, 0, 0));
            return builder->CreateOr(L, R, "or");
        case TokenType::XOR:
            L = toTruthiness(L, Position("", "", 0, 0, 0));
            R = toTruthiness(R, Position("", "", 0, 0, 0));
            return builder->CreateXor(L, R, "xor");
        case TokenType::QAND:
            if (lty == builder->getIntNTy(2) && rty == builder->getIntNTy(2)) {
                llvm::Function* fn = module->getFunction("qc_qand");
                if (!fn) {
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getInt8Ty(), {builder->getInt8Ty(), builder->getInt8Ty()}, false);
                    fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_qand", module);
                }
                llvm::Value* L8 = builder->CreateZExt(L, builder->getInt8Ty());
                llvm::Value* R8 = builder->CreateZExt(R, builder->getInt8Ty());
                llvm::Value* result8 = builder->CreateCall(fn, {L8, R8});
                return builder->CreateTrunc(result8, builder->getIntNTy(2));
            }
            cg_error((*bin)->op_tok.pos, "&&& requires qbool operands");
            return nullptr;
        case TokenType::QOR:
            if (lty == builder->getIntNTy(2) && rty == builder->getIntNTy(2)) {
                llvm::Function* fn = module->getFunction("qc_qor");
                if (!fn) {
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getInt8Ty(), {builder->getInt8Ty(), builder->getInt8Ty()}, false);
                    fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_qor", module);
                }
                llvm::Value* L8 = builder->CreateZExt(L, builder->getInt8Ty());
                llvm::Value* R8 = builder->CreateZExt(R, builder->getInt8Ty());
                llvm::Value* result8 = builder->CreateCall(fn, {L8, R8});
                return builder->CreateTrunc(result8, builder->getIntNTy(2));
            }
            cg_error((*bin)->op_tok.pos, "||| requires qbool operands");
            return nullptr;

        case TokenType::QXOR:
            if (lty == builder->getIntNTy(2) && rty == builder->getIntNTy(2)) {
                llvm::Function* fn = module->getFunction("qc_qxor");
                if (!fn) {
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getInt8Ty(), {builder->getInt8Ty(), builder->getInt8Ty()}, false);
                    fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_qxor", module);
                }
                llvm::Value* L8 = builder->CreateZExt(L, builder->getInt8Ty());
                llvm::Value* R8 = builder->CreateZExt(R, builder->getInt8Ty());
                llvm::Value* result8 = builder->CreateCall(fn, {L8, R8});
                return builder->CreateTrunc(result8, builder->getIntNTy(2));
            }
            cg_error((*bin)->op_tok.pos, "^^ requires qbool operands");
            return nullptr;
        case TokenType::COLLAPSE_AND:
            if (lty == builder->getIntNTy(2) && rty == builder->getIntNTy(2)) {
                llvm::Function* fn = module->getFunction("qc_qand_collapse");
                if (!fn) {
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getInt1Ty(), {builder->getInt8Ty(), builder->getInt8Ty()}, false);
                    fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_qand_collapse", module);
                }
                llvm::Value* L8 = builder->CreateZExt(L, builder->getInt8Ty());
                llvm::Value* R8 = builder->CreateZExt(R, builder->getInt8Ty());
                llvm::Value* result8 = builder->CreateCall(fn, {L8, R8});
                return builder->CreateCall(fn, {L8, R8});
            }
            cg_error((*bin)->op_tok.pos, "&|& requires qbool operands");
            return nullptr;
        case TokenType::COLLAPSE_OR:
            if (lty == builder->getIntNTy(2) && rty == builder->getIntNTy(2)) {
                llvm::Function* fn = module->getFunction("qc_qor_collapse");
                if (!fn) {
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getInt1Ty(), {builder->getInt8Ty(), builder->getInt8Ty()}, false);
                    fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_qor_collapse", module);
                }
                llvm::Value* L8 = builder->CreateZExt(L, builder->getInt8Ty());
                llvm::Value* R8 = builder->CreateZExt(R, builder->getInt8Ty());
                llvm::Value* result8 = builder->CreateCall(fn, {L8, R8});
                return builder->CreateCall(fn, {L8, R8});
            }
            cg_error((*bin)->op_tok.pos, "|&| requires qbool operands");
            return nullptr;
        default: break;
        }
    } else if (auto va = std::get_if<VarAssignNode*>(&node)) {
        std::string name = (*va)->var_name_tok.value;
        std::string qcType = (*va)->type_tok.value;
        if (qcType.starts_with("list<") && qcType.ends_with(">")) {
            std::string elemType = qcType.substr(5, qcType.size() - 6);
            int elemTypeCode = getTypeCode(elemType);

            if (elemTypeCode != -1) {
                llvm::Function* createFn = module->getFunction("qc_create_list");
                if (!createFn) {
                    llvm::Type* ptrTy = llvm::PointerType::get(context, 0);
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(ptrTy, {builder->getInt32Ty()}, false);
                    createFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_create_list", module);
                }

                llvm::Value* listPtr = builder->CreateCall(createFn, {builder->getInt32(elemTypeCode)}, "list_ptr");

                llvm::Type* ptrTy = llvm::PointerType::get(context, 0);
                llvm::AllocaInst* alloc = createEntryAlloca(name, ptrTy);
                builder->CreateStore(listPtr, alloc);

                locals[name] = alloc;
                lists[name] = elemTypeCode;

                return nullptr;
            }
        }
        if (qcType == "auto") {
            llvm::Value* rhs = emitExpr((*va)->value_node);
            if (!rhs) {
                cg_error((*va)->var_name_tok.pos, "Cannot infer type from invalid expression");
                return nullptr;
            }

            llvm::Type* inferredTy = rhs->getType();
            llvm::AllocaInst* alloc = createEntryAlloca(name, inferredTy);
            builder->CreateStore(rhs, alloc);
            std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[fullName] = alloc;
            if (inferredTy->isArrayTy()) {
                llvm::Type* elemTy = inferredTy;
                while (elemTy->isArrayTy()) { elemTy = elemTy->getArrayElementType(); }
                if (elemTy->isIntegerTy(32))
                    arrayTypeStrings[name] = "int";
                else if (elemTy->isIntegerTy(16))
                    arrayTypeStrings[name] = "short int";
                else if (elemTy->isIntegerTy(64))
                    arrayTypeStrings[name] = "long int";
                else if (elemTy->isFloatTy())
                    arrayTypeStrings[name] = "float";
                else if (elemTy->isDoubleTy())
                    arrayTypeStrings[name] = "double";
                else if (elemTy->isIntegerTy(8))
                    arrayTypeStrings[name] = "char";
                else if (elemTy->isIntegerTy(1))
                    arrayTypeStrings[name] = "bool";
                else if (elemTy->isIntegerTy(2))
                    arrayTypeStrings[name] = "qbool";
                else if (elemTy->isPointerTy())
                    arrayTypeStrings[name] = "string";
            } else {
                varTypes[fullName] = qcType;
            }

            return nullptr;
        }
        if (qcType == "auto[]" || qcType.starts_with("auto[")) {
            llvm::Value* rhs = emitExpr((*va)->value_node);
            if (!rhs) {
                cg_error((*va)->var_name_tok.pos, "Cannot infer array type");
                return nullptr;
            }

            llvm::Type* rhsTy = rhs->getType();

            if (!rhsTy->isArrayTy()) {
                cg_error((*va)->var_name_tok.pos, "auto[] requires array literal");
                return nullptr;
            }

            llvm::AllocaInst* alloc = createEntryAlloca(name, rhsTy);
            builder->CreateStore(rhs, alloc);
            name = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[name] = alloc;
            llvm::Type* elemTy = rhsTy->getArrayElementType();
            if (elemTy->isIntegerTy(32))
                arrayTypeStrings[name] = "int";
            else if (elemTy->isIntegerTy(16))
                arrayTypeStrings[name] = "short int";
            else if (elemTy->isIntegerTy(64))
                arrayTypeStrings[name] = "long int";
            else if (elemTy->isFloatTy())
                arrayTypeStrings[name] = "float";
            else if (elemTy->isDoubleTy())
                arrayTypeStrings[name] = "double";
            else if (elemTy->isIntegerTy(8))
                arrayTypeStrings[name] = "char";
            else if (elemTy->isIntegerTy(1))
                arrayTypeStrings[name] = "bool";
            else if (elemTy->isIntegerTy(2))
                arrayTypeStrings[name] = "qbool";
            else if (elemTy->isPointerTy())
                arrayTypeStrings[name] = "string";

            arrayLengths[name] = rhsTy->getArrayNumElements();

            return nullptr;
        }

        if (qcType == "list<auto>") {
            llvm::Value* rhs = emitExpr((*va)->value_node);
            if (!rhs) {
                cg_error((*va)->var_name_tok.pos, "Cannot infer list type");
                return nullptr;
            }

            llvm::Type* rhsTy = rhs->getType();

            if (!rhsTy->isArrayTy()) {
                cg_error((*va)->var_name_tok.pos, "list<auto> requires array literal");
                return nullptr;
            }

            llvm::AllocaInst* alloc = createEntryAlloca(name, rhsTy);
            builder->CreateStore(rhs, alloc);
            name = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[name] = alloc;
            llvm::Type* elemTy = rhsTy->getArrayElementType();
            int elemTypeCode = -1;
            if (elemTy->isIntegerTy(32) || elemTy->isIntegerTy(16) || elemTy->isIntegerTy(64))
                elemTypeCode = 0;
            else if (elemTy->isFloatTy())
                elemTypeCode = 1;
            else if (elemTy->isDoubleTy())
                elemTypeCode = 2;
            else if (elemTy->isIntegerTy(8))
                elemTypeCode = 3;
            else if (elemTy->isIntegerTy(1))
                elemTypeCode = 4;
            else if (elemTy->isIntegerTy(2))
                elemTypeCode = 5;
            else if (elemTy->isPointerTy())
                elemTypeCode = 6;

            lists[name] = elemTypeCode;

            return nullptr;
        }
        qcType = resolveTypeName(qcType);
        auto userTypeIt = userTypes.find(qcType);
        if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Struct) {
            if (auto arrLit = std::get_if<ArrayLiteralNode*>(&(*va)->value_node)) {
                llvm::StructType* structTy = structTypes[qcType];
                llvm::Value* structVal = llvm::UndefValue::get(structTy);
                auto& structInfo = userTypeIt->second;
                for (size_t i = 0; i < (*arrLit)->elements.size(); i++) {
                    std::string fieldType = structInfo.fields[i].type;
                    auto fieldTypeIt = userTypes.find(fieldType);
                    llvm::Value* val;

                    if (fieldTypeIt != userTypes.end() && fieldTypeIt->second.kind == UserTypeKind::Struct) {
                        if (auto nestedArrLit = std::get_if<ArrayLiteralNode*>(&(*arrLit)->elements[i])) {
                            llvm::StructType* nestedStructTy = structTypes[fieldType];
                            llvm::Value* nestedStruct = llvm::UndefValue::get(nestedStructTy);
                            for (size_t j = 0; j < (*nestedArrLit)->elements.size(); j++) {
                                llvm::Value* fieldVal = emitExpr((*nestedArrLit)->elements[j]);
                                if (!fieldVal) return nullptr;
                                nestedStruct = builder->CreateInsertValue(nestedStruct, fieldVal, j);
                            }

                            val = nestedStruct;
                        } else {
                            val = emitExpr((*arrLit)->elements[i]);
                            if (!val) return nullptr;
                        }
                    } else {
                        val = emitExpr((*arrLit)->elements[i]);
                        if (!val) return nullptr;
                    }
                    structVal = builder->CreateInsertValue(structVal, val, i);
                }
                llvm::AllocaInst* structAlloc = createEntryAlloca(name, structTy);
                builder->CreateStore(structVal, structAlloc);

                std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
                locals[fullName] = structAlloc;
                varTypes[fullName] = qcType;
                return nullptr;
            }
        }
        if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Class) {
            llvm::StructType* classTy = classTypes[qcType];
            llvm::AllocaInst* instance = createEntryAlloca(name, classTy);

            if (auto call = std::get_if<CallNode*>(&(*va)->value_node)) {
                if (auto varAccess = std::get_if<VarAccessNode*>(&(*call)->node_to_call)) {
                    std::string calledName = (*varAccess)->var_name_tok.value;

                    if (calledName == qcType) {
                        std::string ctorMethodName = "";
                        for (auto& method : userTypeIt->second.classMethods) {
                            if (method.is_constructor) {
                                ctorMethodName = method.name_tok.value;
                                break;
                            }
                        }

                        if (!ctorMethodName.empty()) {
                            std::vector<llvm::Value*> args;
                            for (auto& argNode : (*call)->arg_nodes) {
                                llvm::Value* arg = emitExpr(argNode);
                                if (!arg) return nullptr;
                                args.push_back(arg);
                            }
                            llvm::Function* ctor = findMethodOverload(qcType, ctorMethodName, args);

                            if (ctor) {
                                std::vector<llvm::Value*> allArgs = {instance};
                                allArgs.insert(allArgs.end(), args.begin(), args.end());
                                builder->CreateCall(ctor, allArgs);
                            }
                        } else {
                            auto [initMethod, ownerClass] = findMethodInHierarchy(qcType, "init");

                            if (initMethod) {
                                std::vector<llvm::Value*> args = {instance};
                                builder->CreateCall(initMethod, args);
                            }
                        }
                    }
                }
            } else {
                auto [initMethod, ownerClass] = findMethodInHierarchy(qcType, "init");

                if (initMethod) {
                    std::vector<llvm::Value*> args;
                    args.push_back(instance);
                    builder->CreateCall(initMethod, args);
                } else {
                    llvm::Value* rhs = emitExpr((*va)->value_node);
                    if (rhs) { builder->CreateStore(rhs, instance); }
                }
            }

            std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[fullName] = instance;
            varTypes[fullName] = qcType;
            return nullptr;
        }
        if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Union) {
            llvm::StructType* unionTy = unionTypes[qcType];
            llvm::AllocaInst* unionAlloc = createEntryAlloca(name, unionTy);
            llvm::Value* rhs = emitExpr((*va)->value_node);
            if (!rhs) return nullptr;
            if (rhs->getType() == unionTy) {
                builder->CreateStore(rhs, unionAlloc);
                std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
                locals[fullName] = unionAlloc;
                return nullptr;
            }
            int tag = findUnionVariantTag(qcType, (*va)->value_node, rhs);

            if (tag == -1) {
                cg_error((*va)->var_name_tok.pos, "Value does not match any variant of union " + qcType);
                return nullptr;
            }
            auto& member = userTypes[qcType].members[tag];
            bool isLiteral = member.type.find(':') != std::string::npos;
            llvm::Type* rhsTy = rhs->getType();
            std::string baseType = isLiteral ? member.type.substr(0, member.type.find(':')) : member.type;

            llvm::Type* memberTy = llvmTypeFor(baseType);

            if (!rhsTy->isPointerTy() && rhsTy != memberTy) {
                cg_error((*va)->var_name_tok.pos, "Union literal variant type mismatch");
                return nullptr;
            }
            llvm::Value* unionVal = llvm::UndefValue::get(unionTy);
            unionVal = builder->CreateInsertValue(unionVal, builder->getInt32(tag), 0);

            llvm::Value* dataPtr = storeAndGetPointer(rhs);
            unionVal = builder->CreateInsertValue(unionVal, dataPtr, 1);

            builder->CreateStore(unionVal, unionAlloc);
            std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[fullName] = unionAlloc;
            varTypes[fullName] = qcType;
            return nullptr;
        }
        if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Enum) {
            llvm::StructType* enumTy = enumTypes[qcType];
            llvm::AllocaInst* enumAlloc = createEntryAlloca(name, enumTy);

            llvm::Value* rhs = emitExpr((*va)->value_node);
            if (!rhs) return nullptr;
            builder->CreateStore(rhs, enumAlloc);
            std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[fullName] = enumAlloc;
            varTypes[fullName] = qcType;
            return nullptr;
        }
        if (qcType.find("[]") != std::string::npos) {
            std::string baseType = qcType;
            while (baseType.ends_with("[]")) { baseType = baseType.substr(0, baseType.length() - 2); }
            arrayTypeStrings[name] = baseType;
        }
        llvm::AllocaInst* alloc = nullptr;
        if ((*va)->type_tok.value == "function" || (*va)->type_tok.value == "auto" && std::holds_alternative<FuncDefNode*>((*va)->value_node)) {
            auto fnPtr = std::get<FuncDefNode*>((*va)->value_node);
            llvm::Function* f = emitFuncDef(*fnPtr);
            name = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            lambdaTypes[name] = f->getFunctionType();
            llvm::Type* funcPtrTy = llvm::PointerType::get(context, 0);
            alloc = createEntryAlloca(name, funcPtrTy);

            locals[name] = alloc;

            builder->CreateStore(f, alloc);
            return nullptr;
        }
        llvm::Value* existingAlloc = getVarAddress(name);
        std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
        if (!existingAlloc) {
            llvm::Type* ty = llvmTypeFor(qcType);
            if (!ty) {
                cg_error((*va)->var_name_tok.pos, "Unknown type: " + qcType);
                return nullptr;
            }
            alloc = createEntryAlloca(fullName, ty);
            locals[fullName] = alloc;
            varTypes[fullName] = qcType;
        } else {
            if (auto* existingLocal = llvm::dyn_cast<llvm::AllocaInst>(existingAlloc)) {
                llvm::Type* existingTy = existingLocal->getAllocatedType();
                llvm::Type* newTy = llvmTypeFor(qcType);

                if (existingTy != newTy) {
                    static int shadowId = 0;
                    std::string uniqueName = fullName + ".shadow." + std::to_string(shadowId++);
                    alloc = createEntryAlloca(uniqueName, newTy);
                    locals[fullName] = alloc;
                    varTypes[fullName] = qcType;
                } else {
                    alloc = existingLocal;
                }
            } else if (auto* gv = llvm::dyn_cast<llvm::GlobalVariable>(existingAlloc)) {
                llvm::Value* rhs = emitExpr((*va)->value_node);
                if (rhs) {
                    if (auto* constantRHS = llvm::dyn_cast<llvm::Constant>(rhs)) {
                        gv->setInitializer(constantRHS);
                    } else {
                        builder->CreateStore(rhs, gv);
                    }
                }
                return nullptr;
            }
        }
        llvm::Type* destTy = getPointeeType(fullName);
        llvm::Value* rhs = emitExpr((*va)->value_node);
        if (!rhs) {
            cg_error((*va)->var_name_tok.pos, "Failed to compile initializer for '" + name + "'");
            return nullptr;
        }

        llvm::Type* srcTy = rhs->getType();
        for (auto& [unionName, unionTy] : unionTypes) {
            if (srcTy == unionTy && !isUnionType(destTy)) {
                llvm::Value* dataPtr = builder->CreateExtractValue(rhs, 1, "union_data");

                if (destTy->isPointerTy()) {
                    rhs = builder->CreateBitCast(dataPtr, destTy);
                } else {
                    llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                    rhs = builder->CreateLoad(destTy, typedPtr);
                }

                srcTy = destTy;
                break;
            }
        }
        for (auto& [enumName, enumTy] : enumTypes) {
            if (srcTy == enumTy) {
                llvm::Value* dataPtr = builder->CreateExtractValue(rhs, 1, "enum_data");

                if (destTy->isPointerTy()) {
                    rhs = builder->CreateBitCast(dataPtr, destTy);
                } else {
                    llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                    rhs = builder->CreateLoad(destTy, typedPtr);
                }

                srcTy = destTy;
                break;
            }
        }
        if (srcTy != destTy) {
            if (srcTy->isFloatTy() && destTy->isDoubleTy()) {
                rhs = builder->CreateFPExt(rhs, destTy, "f2d");
            } else if (srcTy->isDoubleTy() && destTy->isFloatTy()) {
                cg_error((*va)->var_name_tok.pos, "Cannot assign double to float in compiled mode");
                return nullptr;
            } else if (srcTy->isIntegerTy() && destTy->isIntegerTy()) {
                unsigned srcBits = srcTy->getIntegerBitWidth();
                unsigned destBits = destTy->getIntegerBitWidth();
                if (srcBits > destBits) {
                    rhs = builder->CreateTrunc(rhs, destTy, "trunc");
                } else if (srcBits < destBits) {
                    rhs = builder->CreateSExt(rhs, destTy, "sext");
                }
            } else if (srcTy->isIntegerTy() && destTy->isFloatingPointTy()) {
                rhs = builder->CreateSIToFP(rhs, destTy, "i2f");
            } else {
                cg_error((*va)->var_name_tok.pos, "Type mismatch in assignment in compiled mode");
                return nullptr;
            }
        }

        builder->CreateStore(rhs, alloc);
        return nullptr;
    } else if (auto acc = std::get_if<VarAccessNode*>(&node)) {
        std::string name = (*acc)->var_name_tok.value;
        if (name == "this") {
            if (currentThis) {
                return currentThis;
            } else {
                cg_error((*acc)->var_name_tok.pos, "'this' used outside class method");
                return nullptr;
            }
        }
        llvm::Value* alloc = getVarAddress(name);
        if (alloc) {
            llvm::Type* ty = getPointeeType(name);
            if (ty == nullptr) {
                cg_error((*acc)->var_name_tok.pos, "Could not resolve var type");
                return nullptr;
            }
            return builder->CreateLoad(ty, alloc, name);
        }

        llvm::Function* fn = resolveFunction(name);
        if (fn) { return fn; }

        cg_error((*acc)->var_name_tok.pos, "Use of undeclared variable '" + name + "' in compiled mode");
        return nullptr;
    } else if (auto asn = std::get_if<AssignExprNode*>(&node)) {
        if (auto propAccess = std::get_if<PropertyAccessNode*>(&(*asn)->target)) {
            std::string fieldName = (*propAccess)->property_name.value;

            if (auto varAccess = std::get_if<VarAccessNode*>(&*(*propAccess)->base)) {
                std::string varName = (*varAccess)->var_name_tok.value;
                if (varName == "this" && currentThis && !currentClassName.empty()) {
                    auto& classInfo = userTypes[currentClassName];
                    llvm::StructType* classTy = classTypes[currentClassName];

                    int fieldIdx = 0;
                    if (!classInfo.baseClassName.empty()) fieldIdx++;

                    for (size_t i = 0; i < classInfo.classFields.size(); i++) {
                        if (classInfo.classFields[i].name == fieldName) {
                            llvm::Type* fieldTy = llvmTypeFor(classInfo.classFields[i].type);
                            llvm::Value* fieldPtr = builder->CreateStructGEP(classTy, currentThis, fieldIdx + i);

                            llvm::Value* rhsVal = emitExpr((*asn)->value);
                            if (!rhsVal) return nullptr;

                            TokenType op = (*asn)->op_tok.type;

                            if (op != TokenType::EQ) {
                                llvm::Value* oldVal = builder->CreateLoad(fieldTy, fieldPtr);
                                bool isFloat = fieldTy->isFloatingPointTy();

                                switch (op) {
                                case TokenType::PLUS_EQ:
                                    rhsVal = isFloat ? builder->CreateFAdd(oldVal, rhsVal) : builder->CreateAdd(oldVal, rhsVal);
                                    break;
                                case TokenType::MINUS_EQ:
                                    rhsVal = isFloat ? builder->CreateFSub(oldVal, rhsVal) : builder->CreateSub(oldVal, rhsVal);
                                    break;
                                case TokenType::MUL_EQ:
                                    rhsVal = isFloat ? builder->CreateFMul(oldVal, rhsVal) : builder->CreateMul(oldVal, rhsVal);
                                    break;
                                case TokenType::DIV_EQ:
                                    rhsVal = isFloat ? builder->CreateFDiv(oldVal, rhsVal) : builder->CreateSDiv(oldVal, rhsVal);
                                    break;
                                case TokenType::MOD_EQ:
                                    rhsVal = isFloat ? builder->CreateFRem(oldVal, rhsVal) : builder->CreateSRem(oldVal, rhsVal);
                                    break;
                                default: break;
                                }
                            }

                            builder->CreateStore(rhsVal, fieldPtr);
                            return rhsVal;
                        }
                    }

                    cg_error(Position(), "Field not found: " + fieldName);
                    return nullptr;
                }
                llvm::Value* locAlloc = getVarAddress(varName);
                if (!locAlloc) {
                    cg_error(Position(), "Unknown variable: " + varName);
                    return nullptr;
                }

                llvm::Type* allocTy = getPointeeType(varName);

                auto structTy = llvm::dyn_cast<llvm::StructType>(allocTy);
                if (!structTy) {
                    cg_error(Position(), "Not a struct");
                    return nullptr;
                }

                std::string structName = structTy->getName().str();
                auto userTypeIt = userTypes.find(structName);
                int fieldIdx = -1;
                for (size_t i = 0; i < userTypeIt->second.fields.size(); i++) {
                    if (userTypeIt->second.fields[i].name == fieldName) {
                        fieldIdx = i;
                        break;
                    }
                }

                llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, locAlloc, fieldIdx);
                llvm::Type* fieldTy = structTy->getElementType(fieldIdx);

                llvm::Value* rhsVal = emitExpr((*asn)->value);
                TokenType op = (*asn)->op_tok.type;

                if (op != TokenType::EQ) {
                    llvm::Value* oldVal = builder->CreateLoad(fieldTy, fieldPtr);
                    bool isFloat = fieldTy->isFloatingPointTy();

                    switch (op) {
                    case TokenType::PLUS_EQ: rhsVal = isFloat ? builder->CreateFAdd(oldVal, rhsVal) : builder->CreateAdd(oldVal, rhsVal); break;
                    case TokenType::MINUS_EQ: rhsVal = isFloat ? builder->CreateFSub(oldVal, rhsVal) : builder->CreateSub(oldVal, rhsVal); break;
                    case TokenType::MUL_EQ: rhsVal = isFloat ? builder->CreateFMul(oldVal, rhsVal) : builder->CreateMul(oldVal, rhsVal); break;
                    case TokenType::DIV_EQ: rhsVal = isFloat ? builder->CreateFDiv(oldVal, rhsVal) : builder->CreateSDiv(oldVal, rhsVal); break;
                    case TokenType::MOD_EQ: rhsVal = isFloat ? builder->CreateFRem(oldVal, rhsVal) : builder->CreateSRem(oldVal, rhsVal); break;
                    default: break;
                    }
                }

                builder->CreateStore(rhsVal, fieldPtr);
                return rhsVal;
            }
        }
        llvm::Value* alloc = emitLValue((*asn)->target);
        if (!alloc) {
            cg_error((*asn)->op_tok.pos, "Left side of assignment must be an L-value "
                                         "(variable, property, or dereference)");
            return nullptr;
        }
        std::string lhsTypeStr = getExpressionType((*asn)->target, false);

        bool isReference = lhsTypeStr.ends_with("&");
        if (isReference) lhsTypeStr.pop_back();
        llvm::Type* destTy = llvmTypeFor(lhsTypeStr);
        if (!destTy) {
            cg_error((*asn)->op_tok.pos, "Could not resolve type for assignment");
            return nullptr;
        }
        for (auto& [unionName, unionTy] : unionTypes) {
            if (destTy == unionTy) {
                llvm::Value* rhs = emitExpr((*asn)->value);
                if (!rhs) return nullptr;
                if (rhs->getType() == unionTy) {
                    builder->CreateStore(rhs, alloc);
                    return rhs;
                }
                int tag = findUnionVariantTag(unionName, (*asn)->value, rhs);

                if (tag == -1) {
                    cg_error((*asn)->op_tok.pos, "Value does not match any variant of union " + unionName);
                    return nullptr;
                }
                auto& member = userTypes[unionName].members[tag];
                bool isLiteral = member.type.find(':') != std::string::npos;

                std::string baseType = isLiteral ? member.type.substr(0, member.type.find(':')) : member.type;

                llvm::Type* rhsTy = rhs->getType();
                llvm::Type* memberTy = llvmTypeFor(baseType);

                if (rhsTy->getTypeID() != memberTy->getTypeID()) {
                    cg_error((*asn)->op_tok.pos, "Union variant payload type mismatch");
                    return nullptr;
                }
                llvm::Value* unionVal = llvm::UndefValue::get(unionTy);
                unionVal = builder->CreateInsertValue(unionVal, builder->getInt32(tag), 0);
                llvm::Value* dataPtr = storeAndGetPointer(rhs);
                unionVal = builder->CreateInsertValue(unionVal, dataPtr, 1);

                builder->CreateStore(unionVal, alloc);
                return unionVal;
            }
        }
        for (auto& [enumName, enumTy] : enumTypes) {
            if (destTy == enumTy) {
                llvm::Value* rhs = emitExpr((*asn)->value);
                if (!rhs) return nullptr;

                builder->CreateStore(rhs, alloc);
                return rhs;
            }
        }
        llvm::Value* oldVal = builder->CreateLoad(destTy, alloc, "assign_lhs_val");
        llvm::Value* rhsVal = emitExpr((*asn)->value);
        std::string rhsType = getExpressionType((*asn)->value);
        if (!rhsVal) {
            cg_error((*asn)->op_tok.pos, "Failed to compile right-hand side of assignment");
            return nullptr;
        }
        llvm::Type* srcTy = rhsVal->getType();
        for (auto& [unionName, unionTy] : unionTypes) {
            if (srcTy == unionTy) {
                llvm::Value* dataPtr = builder->CreateExtractValue(rhsVal, 1);

                if (destTy->isPointerTy()) {
                    rhsVal = builder->CreateBitCast(dataPtr, destTy);
                } else {
                    llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                    rhsVal = builder->CreateLoad(destTy, typedPtr);
                }
                destTy = srcTy;
                break;
            }
        }

        if ((*asn)->op_tok.type != TokenType::EQ) {
            if (srcTy != destTy) {
                if (srcTy->isFloatTy() && destTy->isDoubleTy()) {
                    rhsVal = builder->CreateFPExt(rhsVal, destTy, "f2d");
                    srcTy = destTy;
                } else if (srcTy->isDoubleTy() && destTy->isFloatTy()) {
                    rhsVal = builder->CreateFPTrunc(rhsVal, destTy, "d2f");
                    srcTy = destTy;
                } else if (srcTy->isIntegerTy() && destTy->isIntegerTy()) {
                    unsigned srcBits = srcTy->getIntegerBitWidth();
                    unsigned destBits = destTy->getIntegerBitWidth();
                    if ((srcBits == 1 || srcBits == 2) && (destBits != srcBits)) {
                        cg_error((*asn)->op_tok.pos, "Cannot convert bool/qbool to other integer types");
                        return nullptr;
                    }

                    if (srcBits < destBits) {
                        rhsVal = builder->CreateSExt(rhsVal, destTy, "sext");
                        srcTy = destTy;
                    } else if (srcBits > destBits) {
                        rhsVal = builder->CreateTrunc(rhsVal, destTy, "trunc");
                        srcTy = destTy;
                    }
                } else if (srcTy->isIntegerTy() && destTy->isFloatingPointTy()) {
                    rhsVal = builder->CreateSIToFP(rhsVal, destTy, "i2f");
                    srcTy = destTy;
                } else if (srcTy->isFloatingPointTy() && destTy->isIntegerTy()) {
                    rhsVal = builder->CreateFPToSI(rhsVal, destTy, "f2i");
                    srcTy = destTy;
                } else if (srcTy->isPointerTy() && !destTy->isPointerTy()) {
                    if (lhsTypeStr.ends_with("&")) {
                        rhsVal = builder->CreateLoad(destTy, rhsVal, "ref_peel");
                        srcTy = rhsVal->getType();
                    } else {
                        cg_error((*asn)->op_tok.pos, "Type mismatch in assignment");
                        return nullptr;
                    }
                } else if (srcTy->isPointerTy() && destTy->isPointerTy()) {
                    if (lhsTypeStr == "void*" || rhsType.ends_with("*") || lhsTypeStr == "@nullptr" || rhsType == "@nullptr") {
                    } else if (lhsTypeStr == rhsType) {
                    } else {
                        cg_error((*asn)->op_tok.pos, "Type mismatch in assignment");
                        return nullptr;
                    }
                }
            }
        } else {
            if (srcTy != destTy) {
                if (srcTy->isFloatTy() && destTy->isDoubleTy()) {
                    rhsVal = builder->CreateFPExt(rhsVal, destTy, "f2d");
                } else if (srcTy->isIntegerTy() && destTy->isIntegerTy()) {
                    unsigned srcBits = srcTy->getIntegerBitWidth();
                    unsigned destBits = destTy->getIntegerBitWidth();
                    if ((srcBits == 1 || srcBits == 2) && (destBits != srcBits)) {
                        cg_error((*asn)->op_tok.pos, "Cannot convert bool/qbool to other integer types");
                        return nullptr;
                    }

                    if (srcBits < destBits) {
                        rhsVal = builder->CreateSExt(rhsVal, destTy, "sext");
                        srcTy = destTy;
                    } else if (srcBits > destBits) {
                        rhsVal = builder->CreateTrunc(rhsVal, destTy, "trunc");
                        srcTy = destTy;
                    }
                } else if (srcTy->isIntegerTy() && destTy->isFloatTy()) {
                    rhsVal = builder->CreateSIToFP(rhsVal, destTy, "i2f");
                } else if (srcTy->isIntegerTy() && destTy->isDoubleTy()) {
                    rhsVal = builder->CreateSIToFP(rhsVal, destTy, "i2d");
                } else if (srcTy->isDoubleTy() && destTy->isFloatTy()) {
                    cg_error((*asn)->op_tok.pos, "Cannot narrow double to float (loses precision)");
                    return nullptr;
                } else if (srcTy->isFloatingPointTy() && destTy->isIntegerTy()) {
                    cg_error((*asn)->op_tok.pos, "Cannot convert floating point to integer (loses "
                                                 "precision)");
                    return nullptr;
                } else if (srcTy->isPointerTy() && !destTy->isPointerTy()) {
                    if (lhsTypeStr.ends_with("&")) {
                        rhsVal = builder->CreateLoad(destTy, rhsVal, "ref_peel");
                        srcTy = rhsVal->getType();
                    }
                } else if (srcTy->isPointerTy() && destTy->isPointerTy()) {
                    if (lhsTypeStr == "void*" || rhsType.ends_with("*") || lhsTypeStr == "@nullptr" || rhsType == "@nullptr") {
                    } else if (lhsTypeStr == rhsType) {
                    } else {
                        cg_error((*asn)->op_tok.pos, "Type mismatch in assignment");
                        return nullptr;
                    }
                } else {
                    cg_error((*asn)->op_tok.pos, "Type mismatch in assignment");
                    return nullptr;
                }
            }
        }
        llvm::Value* newVal = nullptr;
        bool isFloatTy = destTy->isFloatingPointTy();

        switch ((*asn)->op_tok.type) {
        case TokenType::EQ: newVal = rhsVal; break;
        case TokenType::PLUS_EQ: newVal = isFloatTy ? builder->CreateFAdd(oldVal, rhsVal, "fadd") : builder->CreateAdd(oldVal, rhsVal, "add"); break;
        case TokenType::MINUS_EQ: newVal = isFloatTy ? builder->CreateFSub(oldVal, rhsVal, "fsub") : builder->CreateSub(oldVal, rhsVal, "sub"); break;
        case TokenType::MUL_EQ: newVal = isFloatTy ? builder->CreateFMul(oldVal, rhsVal, "fmul") : builder->CreateMul(oldVal, rhsVal, "mul"); break;
        case TokenType::DIV_EQ: newVal = isFloatTy ? builder->CreateFDiv(oldVal, rhsVal, "fdiv") : builder->CreateSDiv(oldVal, rhsVal, "sdiv"); break;
        case TokenType::MOD_EQ: newVal = isFloatTy ? builder->CreateFRem(oldVal, rhsVal, "frem") : builder->CreateSRem(oldVal, rhsVal, "srem"); break;
        default: cg_error((*asn)->op_tok.pos, "Unsupported assignment operator."); return nullptr;
        }
        if ((*asn)->op_tok.type == TokenType::EQ) {
            if (auto structTy = llvm::dyn_cast<llvm::StructType>(destTy)) {
                if (structTy->hasName()) {
                    std::string className = structTy->getName().str();

                    if (classTypes.find(className) != classTypes.end()) {
                        std::vector<llvm::Value*> args = {rhsVal};
                        llvm::Function* opMethod = findMethodOverload(className, "operator=", args);

                        if (opMethod) {
                            llvm::Type* expectedRhsTy = opMethod->getFunctionType()->getParamType(1);
                            if (expectedRhsTy->isStructTy() && rhsVal->getType()->isPointerTy()) {
                                rhsVal = builder->CreateLoad(expectedRhsTy, rhsVal, "op_rhs_load");
                            }
                            std::vector<llvm::Value*> allArgs = {alloc, rhsVal};
                            llvm::Value* callResult = builder->CreateCall(opMethod, allArgs, "op_assign_tmp");
                            return callResult;
                        }
                    }
                }
            }
        }
        builder->CreateStore(newVal, alloc);
        return newVal;
    } else if (auto unary = std::get_if<UnaryOpNode*>(&node)) {
        TokenType op = (*unary)->op_tok.type;

        llvm::Value* operand = emitExpr((*unary)->node);
        if (!operand) return nullptr;
        llvm::Type* operandTy = operand->getType();
        for (auto& [unionName, unionTy] : unionTypes) {
            if (operandTy == unionTy) {
                llvm::Type* targetTy = nullptr;

                if (op == TokenType::MINUS) {
                    targetTy = builder->getInt32Ty();
                } else if (op == TokenType::NOT) {
                    targetTy = builder->getInt1Ty();
                } else if (op == TokenType::QNOT) {
                    targetTy = builder->getIntNTy(2);
                } else if (op == TokenType::MUL) {
                    targetTy = builder->getPtrTy();
                }
                if (targetTy) {
                    llvm::Value* dataPtr = builder->CreateExtractValue(operand, 1);
                    llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                    operand = builder->CreateLoad(targetTy, typedPtr);
                    operandTy = targetTy;
                }
                break;
            }
        }
        for (auto& [enumName, enumTy] : enumTypes) {
            if (operandTy == enumTy) {
                llvm::Type* targetTy = nullptr;

                if (op == TokenType::MINUS) {
                    targetTy = builder->getInt32Ty();
                } else if (op == TokenType::NOT) {
                    targetTy = builder->getInt1Ty();
                } else if (op == TokenType::QNOT) {
                    targetTy = builder->getIntNTy(2);
                } else if (op == TokenType::MUL) {
                    targetTy = builder->getPtrTy();
                }
                if (targetTy) {
                    llvm::Value* dataPtr = builder->CreateExtractValue(operand, 1);
                    llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                    operand = builder->CreateLoad(targetTy, typedPtr);
                    operandTy = targetTy;
                }
                break;
            }
        }
        if (auto structTy = llvm::dyn_cast<llvm::StructType>(operandTy)) {
            if (structTy->hasName()) {
                std::string className = structTy->getName().str();

                if (classTypes.find(className) != classTypes.end()) {
                    std::string opMethodName = getUnaryOperatorMethodName((*unary)->op_tok.type);

                    if (!opMethodName.empty()) {
                        std::vector<llvm::Value*> args = {};
                        llvm::Function* opMethod = findMethodOverload(className, opMethodName, args);

                        if (opMethod) {
                            llvm::AllocaInst* temp = createEntryAlloca("temp_unary_this", operandTy);
                            builder->CreateStore(operand, temp);

                            std::vector<llvm::Value*> allArgs = {temp};
                            return builder->CreateCall(opMethod, allArgs, "unary_op_result");
                        }
                    }
                }
            }
        }
        if ((*unary)->op_tok.type == TokenType::NOT) {
            if (operand->getType() == builder->getInt1Ty()) {
                return builder->CreateNot(operand, "not");
            } else {
                cg_error((*unary)->op_tok.pos, "! requires bool operand");
                return nullptr;
            }
        }
        if ((*unary)->op_tok.type == TokenType::BITWISE_NOT) {
            llvm::Type* ty = operand->getType();
            if (ty->isFloatingPointTy() || ty->isPointerTy()) {
                cg_error((*unary)->op_tok.pos, "Cannot perform bitwise NOT on non-integer type");
                return nullptr;
            }
            llvm::Value* allOnes = llvm::ConstantInt::get(ty, -1, true);
            return builder->CreateXor(operand, allOnes, "nottmp");
        }
        if ((*unary)->op_tok.type == TokenType::QNOT) {
            if (operand->getType() == builder->getIntNTy(2)) {
                llvm::Function* fn = module->getFunction("qc_qnot");
                if (!fn) {
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getInt8Ty(), {builder->getInt8Ty()}, false);
                    fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_qnot", module);
                }
                llvm::Value* op8 = builder->CreateZExt(operand, builder->getInt8Ty());
                llvm::Value* result8 = builder->CreateCall(fn, {op8});
                return builder->CreateTrunc(result8, builder->getIntNTy(2));
            }
            cg_error((*unary)->op_tok.pos, "!! requires qbool operand");
            return nullptr;
        }
        if ((*unary)->op_tok.type == TokenType::MINUS) {
            if (operandTy->isIntegerTy()) {
                return builder->CreateNeg(operand, "neg");
            } else if (operandTy->isFloatingPointTy()) {
                return builder->CreateFNeg(operand, "fneg");
            } else {
                cg_error((*unary)->op_tok.pos, "- requires numeric operand");
                return nullptr;
            }
        }
        if ((*unary)->op_tok.type == TokenType::INCREMENT || (*unary)->op_tok.type == TokenType::DECREMENT) {
            llvm::Value* lhsVal = emitExpr((*unary)->node);
            llvm::Value* lhs = emitLValue((*unary)->node);
            if (!lhsVal->getType()->isIntegerTy()) {
                cg_error((*unary)->op_tok.pos, "++/-- only valid on int-like");
                return nullptr;
            }

            llvm::Value* oldVal = builder->CreateLoad(lhsVal->getType(), lhs, "inc_deref");
            llvm::Value* one = llvm::ConstantInt::get(lhsVal->getType(), 1);
            llvm::Value* newVal;
            if ((*unary)->op_tok.type == TokenType::INCREMENT) {
                newVal = builder->CreateAdd(oldVal, one, "inc");
            } else {
                newVal = builder->CreateSub(oldVal, one, "dec");
            }

            builder->CreateStore(newVal, lhs);
            bool isPostfix = (*unary)->is_postfix;
            return isPostfix ? oldVal : newVal;
        }
        if ((*unary)->op_tok.type == TokenType::AMPERSAND) {
            auto* varPtr = *(std::get_if<VarAccessNode*>(&(*unary)->node));
            if (!varPtr) {
                cg_error((*unary)->op_tok.pos, "& only supported on variables");
                return nullptr;
            }
            std::string name = varPtr->var_name_tok.value;
            if (!(resolveVariable(name))) {
                cg_error((*unary)->op_tok.pos, "cannot & something that doesn't exist.");
                return nullptr;
            }
            return resolveVariable(name);
        }
        if ((*unary)->op_tok.type == TokenType::MUL) {
            llvm::Value* val = emitExpr((*unary)->node);
            std::string type = getExpressionType((*unary)->node);
            if (!type.ends_with("*")) {
                cg_error((*unary)->op_tok.pos, "you can only dereference pointer types, found: " + type);
                return nullptr;
            }
            if (type == "void*") {
                cg_error((*unary)->op_tok.pos, "you canot dereference void*");
                return nullptr;
            }
            std::string baseType = type.substr(0, type.size() - 1);
            return builder->CreateLoad(llvmTypeFor(baseType), val, "deref");
        }
        if ((*unary)->op_tok.type == TokenType::SIZEOF) {
            const llvm::DataLayout& dl = module->getDataLayout();
            uint64_t size;
            if (StringNode* val = std::get_if<StringNode>(&(*unary)->node)) {
                size = dl.getTypeAllocSize(llvmTypeFor(val->tok.value));
            } else {
                size = dl.getTypeAllocSize(emitExpr((*unary)->node)->getType());
            }
            unsigned ptrBitWidth = dl.getPointerSizeInBits();
            llvm::IntegerType* addrType = llvm::IntegerType::get(context, ptrBitWidth);
            return llvm::ConstantInt::get(addrType, size);
        }
    } else if (auto fnPtr = std::get_if<FuncDefNode*>(&node)) {
        llvm::Function* f = emitFuncDef(*(*fnPtr));
        return f;
    } else if (auto mapLit = std::get_if<MapLiteralNode*>(&node)) {
        if ((*mapLit)->pairs.empty()) {
            cg_error((*mapLit)->pos, "Cannot infer type of empty map literal");
            return nullptr;
        }
        llvm::Value* firstKey = emitExpr((*mapLit)->pairs[0].first);
        llvm::Value* firstVal = emitExpr((*mapLit)->pairs[0].second);
        if (!firstKey || !firstVal) return nullptr;

        int keyTypeCode = getTypeCodeFromLLVM(firstKey->getType());
        int valueTypeCode = getTypeCodeFromLLVM(firstVal->getType());

        llvm::Function* createFn = module->getFunction("qc_create_map");
        if (!createFn) {
            llvm::Type* ptrTy = llvm::PointerType::get(context, 0);
            llvm::FunctionType* fnTy = llvm::FunctionType::get(ptrTy, {builder->getInt32Ty(), builder->getInt32Ty()}, false);
            createFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_create_map", module);
        }

        llvm::Value* mapPtr = builder->CreateCall(createFn, {builder->getInt32(keyTypeCode), builder->getInt32(valueTypeCode)}, "map_lit_ptr");

        llvm::Function* setFn = module->getFunction("qc_map_set");
        if (!setFn) {
            llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
            llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getVoidTy(), {voidPtrTy, voidPtrTy, voidPtrTy}, false);
            setFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_map_set", module);
        }

        for (auto& pair : (*mapLit)->pairs) {
            llvm::Value* keyVal = emitExpr(pair.first);
            llvm::Value* valueVal = emitExpr(pair.second);
            if (!keyVal || !valueVal) continue;

            llvm::AllocaInst* keyAlloc = createEntryAlloca("lit_key", keyVal->getType());
            llvm::AllocaInst* valAlloc = createEntryAlloca("lit_val", valueVal->getType());
            builder->CreateStore(keyVal, keyAlloc);
            builder->CreateStore(valueVal, valAlloc);

            llvm::Value* keyPtr = builder->CreateBitCast(keyAlloc, llvm::PointerType::get(context, 0));
            llvm::Value* valPtr = builder->CreateBitCast(valAlloc, llvm::PointerType::get(context, 0));

            builder->CreateCall(setFn, {mapPtr, keyPtr, valPtr});
        }

        return mapPtr;
    } else if (auto arrLit = std::get_if<ArrayLiteralNode*>(&node)) {
        if ((*arrLit)->elements.empty()) {
            if (!currentFunction) {
                cg_error(Position(), "Empty array literals only supported in functions");
                return nullptr;
            }

            llvm::Type* retTy = currentFunction->getReturnType();
            if (retTy->isPointerTy()) {
                llvm::Type* elemType = builder->getInt32Ty();
                llvm::Function* mallocFn = module->getFunction("malloc");
                if (!mallocFn) {
                    llvm::FunctionType* mallocTy = llvm::FunctionType::get(builder->getPtrTy(), {builder->getInt64Ty()}, false);
                    mallocFn = llvm::Function::Create(mallocTy, llvm::Function::InternalLinkage, "malloc", module);
                }
                llvm::Value* size = builder->getInt64(0);
                llvm::Value* ptr = builder->CreateCall(mallocFn, {size}, "empty_arr");
                return builder->CreateBitCast(ptr, retTy, "empty_arr_cast");
            }

            cg_error(Position(), "Cannot determine element type for empty array");
            return nullptr;
        }

        bool hasRuntimeSpread = false;
        llvm::Value* totalSize = builder->getInt32(0);

        for (auto& elem : (*arrLit)->elements) {
            if (auto spread = std::get_if<SpreadNode*>(&elem)) {
                llvm::Value* collVal = emitExpr((*spread)->expr);
                llvm::Value* spreadLen = getCollectionLength(collVal, (*spread)->expr);

                if (!llvm::isa<llvm::ConstantInt>(spreadLen)) { hasRuntimeSpread = true; }
                totalSize = builder->CreateAdd(totalSize, spreadLen);
            } else {
                totalSize = builder->CreateAdd(totalSize, builder->getInt32(1));
            }
        }

        if (hasRuntimeSpread) { return createRuntimeSizedArray((*arrLit)->elements, totalSize); }
        std::vector<llvm::Value*> allElements;
        for (auto& elem : (*arrLit)->elements) {
            if (auto spread = std::get_if<SpreadNode*>(&elem)) {
                llvm::Value* collVal = emitExpr((*spread)->expr);
                expandSpreadIntoVector(collVal, (*spread)->expr, allElements);
            } else {
                llvm::Value* v = emitExpr(elem);
                if (v) allElements.push_back(v);
            }
        }

        if (allElements.empty()) return nullptr;

        llvm::Value* firstElem = allElements[0];
        llvm::Type* elemTy = firstElem->getType();
        size_t arraySize = allElements.size();

        std::vector<llvm::Constant*> constElems;
        bool allConst = true;
        for (auto* v : allElements) {
            if (auto* constVal = llvm::dyn_cast<llvm::Constant>(v)) {
                constElems.push_back(constVal);
            } else {
                allConst = false;
                break;
            }
        }

        if (allConst) {
            llvm::ArrayType* arrTy = llvm::ArrayType::get(elemTy, arraySize);
            return llvm::ConstantArray::get(arrTy, constElems);
        }

        llvm::ArrayType* arrTy = llvm::ArrayType::get(elemTy, arraySize);
        llvm::AllocaInst* alloc = createEntryAlloca("arr_lit", arrTy);

        for (size_t i = 0; i < allElements.size(); i++) {
            std::vector<llvm::Value*> indices = {builder->getInt32(0), builder->getInt32(i)};
            llvm::Value* elemPtr = builder->CreateInBoundsGEP(arrTy, alloc, indices, "arr_elem_ptr");
            builder->CreateStore(allElements[i], elemPtr);
        }

        std::vector<llvm::Value*> indices = {builder->getInt32(0), builder->getInt32(0)};
        return builder->CreateInBoundsGEP(arrTy, alloc, indices, "arr_ptr");
    } else if (auto callPtr = std::get_if<CallNode*>(&node)) {
        CallNode& call = *(*callPtr);
        if (auto* varAccess = std::get_if<VarAccessNode*>(&call.node_to_call)) {
            std::string funcName = (*varAccess)->var_name_tok.value;
            std::string resolvedName = funcName;
            llvm::Function* resolved = resolveFunction(funcName);
            if (resolved) {
                resolvedName = resolved->getName().str();
            } else {
                std::string ns = getCurrentNamespace();
                while (!ns.empty()) {
                    std::string candidate = ns + "::" + funcName;
                    if (functionDefs.count(candidate)) {
                        resolvedName = candidate;
                        break;
                    }
                    size_t pos = ns.rfind("::");
                    ns = (pos == std::string::npos) ? "" : ns.substr(0, pos);
                }
            }
            funcName = resolvedName;
            auto funcDefIt = functionDefs.find(funcName);
            if (funcDefIt != functionDefs.end()) {
                FuncDefNode* funcDef = funcDefIt->second;
                if (funcHasAutoParams(funcDef)) {
                    std::vector<llvm::Value*> argValues;
                    std::vector<std::string> argTypes;
                    auto paramIt = funcDef->params.begin();
                    bool hasSpread = false;
                    for (auto& argNode : call.arg_nodes) {
                        if (std::holds_alternative<SpreadNode*>(argNode)) { hasSpread = true; }
                        std::string ptype = (paramIt != funcDef->params.end()) ? paramIt->type.value : "...";
                        llvm::Value* argVal;
                        if (ptype.ends_with("&")) {
                            auto* va = std::get_if<VarAccessNode*>(&argNode);
                            if (!va) {
                                cg_error(Position(), "L-value required for ref param");
                                return nullptr;
                            }
                            argVal = getVarAddress((*va)->var_name_tok.value);
                            argTypes.push_back(ptype);
                        } else {
                            argVal = emitExpr(argNode);
                            argTypes.push_back(getExpressionType(argNode));
                        }
                        argValues.push_back(argVal);
                        if (paramIt != funcDef->params.end()) ++paramIt;
                    }
                    if (hasSpread) {
                        cg_error(Position(), "Spread is no longer allowed in function calls.");
                        return nullptr;
                    }
                    std::string sig = makeTypeSignature(argTypes);
                    std::string specializedName = funcName + "_" + sig;
                    if (specializedFunctions[funcName].count(sig) == 0) {
                        llvm::Function* specializedFn = generateSpecializedFunction(funcDef, argTypes, specializedName);
                        if (!specializedFn) return nullptr;
                        specializedFunctions[funcName][sig] = specializedFn;
                    }
                    llvm::Function* fn = specializedFunctions[funcName][sig];
                    if (funcDef->params.size() > 0 && funcDef->params.back().type.value == "...") {
                        size_t fixedCount = funcDef->params.size() - 1;
                        std::vector<llvm::Value*> varVals(argValues.begin() + fixedCount, argValues.end());
                        argValues.resize(fixedCount);
                        argValues.push_back(packVariadicArgs(varVals));
                    }
                    return builder->CreateCall(fn, argValues);
                }
            }
            resolvedName = resolveTypeName(funcName);
            auto classIt = userTypes.find(resolvedName);
            if (classIt != userTypes.end() && classIt->second.kind == UserTypeKind::Class) {
                llvm::StructType* classTy = classTypes[resolvedName];
                llvm::AllocaInst* temp = createEntryAlloca("temp_" + resolvedName, classTy);
                std::string ctorName = "";
                ClassMethodInfo* ctorInfo = nullptr;
                for (auto& method : classIt->second.classMethods) {
                    if (method.is_constructor) {
                        ctorName = method.name_tok.value;
                        ctorInfo = &method;
                        break;
                    }
                }
                if (!ctorName.empty()) {
                    std::vector<llvm::Value*> ctorArgs;
                    for (auto& argNode : call.arg_nodes) {
                        llvm::Value* arg = emitExpr(argNode);
                        if (!arg) return nullptr;
                        ctorArgs.push_back(arg);
                    }
                    llvm::Function* ctor = findMethodOverload(resolvedName, ctorName, ctorArgs);
                    if (!ctor) {
                        cg_error((*varAccess)->var_name_tok.pos, "No matching constructor for " + resolvedName);
                        return nullptr;
                    }
                    bool isCtorVariadic = (ctorInfo->params.size() > 0 && ctorInfo->params.back().type.value == "...");
                    if (isCtorVariadic) {
                        size_t fixedCount = ctorInfo->params.size();
                        std::vector<llvm::Value*> varVals(ctorArgs.begin() + fixedCount, ctorArgs.end());
                        ctorArgs.resize(fixedCount);
                        ctorArgs.push_back(packVariadicArgs(varVals));
                    }

                    std::vector<llvm::Value*> allArgs = {temp};
                    allArgs.insert(allArgs.end(), ctorArgs.begin(), ctorArgs.end());
                    builder->CreateCall(ctor, allArgs);
                } else {
                    builder->CreateStore(llvm::Constant::getNullValue(classTy), temp);
                }
                return builder->CreateLoad(classTy, temp, resolvedName + "_inst");
            }
            static const std::unordered_map<std::string, std::string> builtins = {{"time", "qc_time"},
                                                                                  {"seed", "qc_seed"},
                                                                                  {"random", "qc_random_float"},
                                                                                  {"len", "qc_len"},
                                                                                  {"to_lower", "qc_to_lower"},
                                                                                  {"to_upper", "qc_to_upper"},
                                                                                  {"substring", "qc_substring"},
                                                                                  {"contains", "qc_contains"},
                                                                                  {"startswith", "qc_startswith"},
                                                                                  {"endswith", "qc_endswith"},
                                                                                  {"trim", "qc_trim"},
                                                                                  {"replace", "qc_replace"},
                                                                                  {"to_int", "qc_to_int_from_string"},
                                                                                  {"to_float", "qc_to_float_from_string"},
                                                                                  {"to_double", "qc_to_double_from_string"},
                                                                                  {"to_char", "qc_to_char_from_string"},
                                                                                  {"to_bool", "qc_to_bool_from_int"},
                                                                                  {"to_string", "qc_to_string_int"},
                                                                                  {"qout", ""},
                                                                                  {"typeof", ""},
                                                                                  {"fopen", "qc_fopen"},
                                                                                  {"fclose", "qc_fclose"},
                                                                                  {"fread", "qc_fread"},
                                                                                  {"fwrite", "qc_fwrite"},
                                                                                  {"malloc", "qc_malloc"},
                                                                                  {"calloc", "qc_calloc"},
                                                                                  {"free", "qc_free"},
                                                                                  {"realloc", "qc_realloc"},
                                                                                  {"mapped_ptr", ""},
                                                                                  {"ternary", ""},
                                                                                  {"to_address", ""},
                                                                                  {"inline", ""},
                                                                                  {"flush", "qc_flush"},
                                                                                  {"next", ""},
                                                                                  {"is_empty", ""}};
            auto it = builtins.find(funcName);

            if (it != builtins.end()) {
                std::string runtimeName = it->second;

                if (funcName == "typeof" && !call.arg_nodes.empty()) {
                    AnyNode& argNode = call.arg_nodes.front();
                    llvm::Value* arg = emitExpr(argNode);
                    if (!arg) return nullptr;
                    llvm::Type* argTy = arg->getType();
                    for (auto& [unionName, unionTy] : unionTypes) {
                        if (argTy == unionTy) {
                            llvm::Value* tag = builder->CreateExtractValue(arg, 0, "typeof_tag");
                            auto typeIt = userTypes.find(unionName);
                            if (typeIt != userTypes.end()) {
                                auto& members = typeIt->second.members;
                                llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "typeof_end", currentFunction);
                                llvm::AllocaInst* resultAlloc = createEntryAlloca("typeof_result", llvm::PointerType::get(context, 0));
                                llvm::SwitchInst* switchInst = builder->CreateSwitch(tag, endBB, members.size());
                                for (size_t i = 0; i < members.size(); i++) {
                                    llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "typeof_case_" + std::to_string(i), currentFunction);
                                    builder->SetInsertPoint(caseBB);
                                    std::string baseType = members[i].type;
                                    size_t colonPos = baseType.find(':');
                                    if (colonPos != std::string::npos) baseType = baseType.substr(0, colonPos);
                                    llvm::Value* variantName = builder->CreateGlobalString(baseType);
                                    builder->CreateStore(variantName, resultAlloc);
                                    builder->CreateBr(endBB);
                                    switchInst->addCase(builder->getInt32(i), caseBB);
                                }
                                builder->SetInsertPoint(endBB);
                                return builder->CreateLoad(llvm::PointerType::get(context, 0), resultAlloc, "typeof_result");
                            }
                        }
                    }
                    for (auto& [enumName, enumTy] : enumTypes) {
                        if (argTy == enumTy) {
                            llvm::Value* tag = builder->CreateExtractValue(arg, 0);
                            auto& entries = userTypes[enumName].enumEntries;
                            llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "typeof_end", currentFunction);
                            llvm::AllocaInst* resultAlloc = createEntryAlloca("typeof_result", llvm::PointerType::get(context, 0));
                            llvm::SwitchInst* switchInst = builder->CreateSwitch(tag, endBB, entries.size());
                            for (size_t i = 0; i < entries.size(); i++) {
                                llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "case", currentFunction);
                                builder->SetInsertPoint(caseBB);
                                size_t colonPos = entries[i].typeAtom.find(':');
                                std::string type = entries[i].typeAtom.substr(0, colonPos);
                                llvm::Value* typeStr = builder->CreateGlobalString(type);
                                builder->CreateStore(typeStr, resultAlloc);
                                builder->CreateBr(endBB);
                                switchInst->addCase(builder->getInt32(i), caseBB);
                            }
                            builder->SetInsertPoint(endBB);
                            return builder->CreateLoad(llvm::PointerType::get(context, 0), resultAlloc);
                        }
                    }
                    if (auto varAccess = std::get_if<VarAccessNode*>(&argNode)) {
                        std::string varName = (*varAccess)->var_name_tok.value;
                        if (resolveVarType(varName) != "") { return builder->CreateGlobalString(resolveVarType(varName)); }
                        if (hasArrayType(varName)) { return builder->CreateGlobalString(arrayTypeStrings[varName] + "[]"); }
                        if (hasList(varName)) {
                            if (lists.find(varName) != lists.end()) {
                                int elemTypeCode = lists[varName];
                                std::string elemType;
                                if (elemTypeCode == 0)
                                    elemType = "int";
                                else if (elemTypeCode == 1)
                                    elemType = "float";
                                else if (elemTypeCode == 2)
                                    elemType = "double";
                                else if (elemTypeCode == 3)
                                    elemType = "char";
                                else if (elemTypeCode == 4)
                                    elemType = "bool";
                                else if (elemTypeCode == 5)
                                    elemType = "qbool";
                                else if (elemTypeCode == 6)
                                    elemType = "string";
                                else
                                    elemType = "auto";
                                return builder->CreateGlobalString("list<" + elemType + ">");
                            }
                        }
                    }
                    std::string typeName = "unknown";
                    if (argTy->isIntegerTy(32))
                        typeName = "int";
                    else if (argTy->isIntegerTy(64))
                        typeName = "uintptr_t";
                    if (argTy->isIntegerTy(16))
                        typeName = "short int";
                    else if (argTy->isFloatTy())
                        typeName = "float";
                    else if (argTy->isDoubleTy())
                        typeName = "double";
                    else if (argTy->isIntegerTy(8))
                        typeName = "char";
                    else if (argTy->isIntegerTy(1))
                        typeName = "bool";
                    else if (argTy->isIntegerTy(2))
                        typeName = "qbool";
                    else if (argTy->isPointerTy())
                        typeName = "pointer";
                    if (auto structTy = llvm::dyn_cast<llvm::StructType>(argTy)) typeName = structTy->getName().str();
                    return builder->CreateGlobalString(typeName);
                }
                if (funcName == "fopen") {
                    std::vector<llvm::Value*> args;
                    for (auto& argNode : call.arg_nodes) {
                        llvm::Value* arg = emitExpr(argNode);
                        if (!arg) return nullptr;
                        args.push_back(arg);
                    }
                    llvm::Function* fn = module->getFunction("qc_fopen");
                    if (!fn) {
                        auto* fnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0),
                                                             {llvm::PointerType::get(context, 0), llvm::PointerType::get(context, 0)}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_fopen", module);
                    }
                    return builder->CreateCall(fn, args, "fopen_result");
                }
                if (funcName == "fclose") {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    llvm::Function* fn = module->getFunction("qc_fclose");
                    if (!fn) {
                        auto* fnTy = llvm::FunctionType::get(builder->getVoidTy(), {llvm::PointerType::get(context, 0)}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_fclose", module);
                    }
                    builder->CreateCall(fn, {arg});
                    return nullptr;
                }
                if (funcName == "fread") {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    llvm::Function* fn = module->getFunction("qc_fread");
                    if (!fn) {
                        auto* fnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {llvm::PointerType::get(context, 0)}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_fread", module);
                    }
                    return builder->CreateCall(fn, {arg}, "fread_result");
                }
                if (funcName == "fwrite") {
                    std::vector<llvm::Value*> args;
                    for (auto& argNode : call.arg_nodes) {
                        llvm::Value* arg = emitExpr(argNode);
                        if (!arg) return nullptr;
                        args.push_back(arg);
                    }
                    llvm::Function* fn = module->getFunction("qc_fwrite");
                    if (!fn) {
                        auto* fnTy = llvm::FunctionType::get(builder->getVoidTy(),
                                                             {llvm::PointerType::get(context, 0), llvm::PointerType::get(context, 0)}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_fwrite", module);
                    }
                    builder->CreateCall(fn, args);
                    return nullptr;
                }
                if (funcName == "random" && !call.arg_nodes.empty()) {
                    if (call.arg_nodes.size() == 1)
                        runtimeName = "qc_random_int";
                    else if (call.arg_nodes.size() == 2)
                        runtimeName = "qc_random_range";
                } else if (funcName == "qout") { // Ṱ̵̺̙̙͔̯̣͓̼̈́͜h̶̳͖̝̰͍̮͆̅̊e̶̡̧̮͍̘̘͍̮͎͎̺̗̦͕̾͗͐̽͑̔̅́̑̌̕ ̶̥̮̪͙̎͛̐͑̔̉́̂̂̐́̽̔̔͂̃d̴̛̪̦̞́́̎͊̌̈̍̓̓̔̑͑̒͘͝e̶͎̤̠̞̞͖̊ṽ̴̡͖̫̩̣̳̖̞̯̪͇̰̆͑͐͐̀̿͐̍̑̕͘̕͝͝ͅͅͅí̵̜̬͍̖̒͑̎͗l̸̛͍̰̜̞̩̜̘͈̯̬̇̀̋̈͐̔̿̓̅͌̉̅͂̌͘͜͝ ̷̡̣̰͙̰̪͈̪̣̺̺̤̦̰͌̊̀̀̑͑̅̈́ş̶̛̳̟̫͇̠͉͍̺̣̲̬̻̰͍̙̋̂͗̕͠ͅę̸̹̹̈́͒̐̃̋̓͐̓͆̉̀̊̀̏̿͘é̷͖͎̹̉́̈́͠͠͝s̸̡̢̢̩͍̹̼͈͕̘̖͋̋̃̓͗͆͌̕͠ͅͅͅ ̴̛̮͉̣̈́̒͋͐̿̾̐̽̚ḩ̶̨̧̺͉̹̩̙̫͇̰̫̯̬͐́̑͜i̶̠͖̠̟̻̭̫̙̳̪͆̄̿̈́̾̊̈́̒͑͊̆̋̃̎̿̂͗ş̴̥̤̜̦̗͍̟̈́̽̑̏ ̶̡̛̫̥̝̰̣̟͇͔̤̱̯͉̱̩̋̈̈́͐̓̑̋̎͝͝ͅö̷̡̝̣́̎̎͝ẘ̶̢̡̨̡̭̞̯̘̦̟̳̮̫͎̑͂̇̀͆̋̐̃̒́̏̓͒̅͜͝͝n̵̳͎̣̬̪̝̩͒͊̓̾̓̄̃̂͗̉͆̒̋̚͜͜͝ ̴͔̫̂̏ͅͅį̷̡̤̼͈̗̦̣̘̮̠̣͎̬̰̍͗ṉ̸̨̯̱̦͕͐̉̀͌͑̀͐̽̕͜
                                                 // ̷̛̜̈́̐̇̑͛̕ṯ̸̟̰̩̩̼̀͆̏̀̔̈́͛̍͑͑͠͝h̶̺̺͙͙̤̘̦̬̝̱̟͕̟̟͕̯͛̌͋̓́̔̊͘͘ͅè̷̢̡̝̗͙̘͍̠̝͑̃̋͜͝͝ ̶̬̐̂̏̆̀͝͠s̴̨̮̺͙͙̪̹͖͓̆̌̔͆̿̌̏̇̎͜͝h̴̛̝̜̥̺͇̗̪̄̀͆̆̅͋͂̅͘ͅḁ̸̖͐̅̑͗̃̂͌̃͝d̶̢͇͉͈̹̯͌̓͂̈̒́͐̈́͑̏̀͊͋͐͠o̴̧̧̥͎͓̒̀̍̀͒͠w̵̢̰̰̭̟̼̋̓͋̈́̅ ̸̢̖̘͓̯̦͎̼̗̠̤̙̿̄̍̎̎͑͐ȏ̷̹̫̲͎͖͉̩̺̫̖͊̐̄̀͌̃̀́̌͑͒̈́̐̀͘f̴̧̣͔͇̹͙͙̦͎̿̋͊͊̀̽͗͒ ̷͕̥͕̣͎̫̿͊͊̅͆͂͘͜ǫ̴̢̱͍͍͍̰͓͚̟͚̹͗̔̎͜͠͠ţ̷̨̺̯̥͕̳̮̳̜̙̫̫̺͐̀͊̽̀̇̽̋̚̚͠ͅh̷̼̦̦̝̺̒͌͐͐̀̈́̕̕͠ͅḙ̷̢̨̜͕͖͈̜͖̥̈́̐́̀̓́̽̀̈͂̅́̍̚͜͝r̷͙̎͐̅̍̐̈́͌͊͌̇́ŝ̵̥̱̞͔̩̉͋̌͂̉͑̇̆̓͆̃̚͝.̸̡̣̘̗̖̦͙͕̯̗̩́̔͜͠
                    if (call.arg_nodes.empty()) {
                        cg_error((*varAccess)->var_name_tok.pos, "qout requires arguments: " + funcName);
                        return nullptr;
                    }
                    std::vector<AnyNode> goodArgs((call.arg_nodes.begin()), (call.arg_nodes.end()));
                    int current_arg = 0;
                    std::string fmtString = "";
                    llvm::Value* argVal = emitExpr(goodArgs[0]);
                    llvm::ConstantDataSequential* constArray = nullptr;
                    if (auto* CE = llvm::dyn_cast<llvm::ConstantExpr>(argVal)) {
                        if (CE->getOpcode() == llvm::Instruction::GetElementPtr) { argVal = CE->getOperand(0); }
                    }
                    if (auto* GV = llvm::dyn_cast<llvm::GlobalVariable>(argVal)) {
                        if (GV->hasInitializer()) { constArray = llvm::dyn_cast<llvm::ConstantDataSequential>(GV->getInitializer()); }
                    } else {
                        constArray = llvm::dyn_cast<llvm::ConstantDataSequential>(argVal);
                    }
                    if (constArray && constArray->isString()) {
                        fmtString = constArray->getAsString().str();
                    } else {
                        cg_error((*varAccess)->var_name_tok.pos, "qout requires the first argument to be a "
                                                                 "string: " +
                                                                     funcName);
                        return nullptr;
                    }
                    std::string to_print = "";
                    char c;
                    llvm::Function* printString = module->getFunction("qc_print_string");
                    if (!printString) {
                        llvm::FunctionType* prStrFnTy = llvm::FunctionType::get(builder->getVoidTy(), {llvm::PointerType::get(context, 0)}, false);
                        printString = llvm::Function::Create(prStrFnTy, llvm::Function::ExternalLinkage, "qc_print_string", module);
                    }
                    llvm::Function* fmtStr = module->getFunction("qc_fmt_string");
                    if (!fmtStr) {
                        llvm::FunctionType* prStrFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0), {llvm::PointerType::get(context, 0), builder->getInt32Ty(), builder->getInt1Ty()},
                            false);
                        fmtStr = llvm::Function::Create(prStrFnTy, llvm::Function::ExternalLinkage, "qc_fmt_string", module);
                    }
                    llvm::Function* fmtInt = module->getFunction("qc_fmt_int");
                    if (!fmtInt) {
                        llvm::FunctionType* fmtIntFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0),
                            {builder->getInt64Ty(), builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt1Ty()}, false);
                        fmtInt = llvm::Function::Create(fmtIntFnTy, llvm::Function::ExternalLinkage, "qc_fmt_int", module);
                    }
                    llvm::Function* fmtUInt = module->getFunction("qc_fmt_unsigned_int");
                    if (!fmtUInt) {
                        llvm::FunctionType* fmtUIntFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0),
                            {builder->getInt64Ty(), builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt1Ty()}, false);
                        fmtUInt = llvm::Function::Create(fmtUIntFnTy, llvm::Function::ExternalLinkage, "qc_fmt_unsigned_int", module);
                    }
                    llvm::Function* fmtFloat = module->getFunction("qc_fmt_float");
                    if (!fmtFloat) {
                        llvm::FunctionType* fmtFloatFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0),
                            {builder->getDoubleTy(), builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt1Ty()}, false);
                        fmtFloat = llvm::Function::Create(fmtFloatFnTy, llvm::Function::ExternalLinkage, "qc_fmt_float", module);
                    }
                    llvm::Function* fmtDouble = module->getFunction("qc_fmt_double");
                    if (!fmtDouble) {
                        llvm::FunctionType* fmtDoubleFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0),
                            {builder->getDoubleTy(), builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt1Ty()}, false);
                        fmtDouble = llvm::Function::Create(fmtDoubleFnTy, llvm::Function::ExternalLinkage, "qc_fmt_double", module);
                    }
                    llvm::Function* fmtChar = module->getFunction("qc_fmt_char");
                    if (!fmtChar) {
                        llvm::FunctionType* fmtCharFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0), {builder->getInt8Ty(), builder->getInt32Ty(), builder->getInt1Ty()}, false);
                        fmtChar = llvm::Function::Create(fmtCharFnTy, llvm::Function::ExternalLinkage, "qc_fmt_char", module);
                    }
                    llvm::Function* fmtQBool = module->getFunction("qc_fmt_qbool");
                    if (!fmtQBool) {
                        llvm::FunctionType* fmtQBoolFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0), {builder->getInt1Ty(), builder->getInt32Ty(), builder->getInt1Ty()}, false);
                        fmtQBool = llvm::Function::Create(fmtQBoolFnTy, llvm::Function::ExternalLinkage, "qc_fmt_qbool", module);
                    }
                    llvm::Function* fmtBool = module->getFunction("qc_fmt_bool");
                    if (!fmtBool) {
                        llvm::FunctionType* fmtBoolFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0), {builder->getInt8Ty(), builder->getInt32Ty(), builder->getInt1Ty()}, false);
                        fmtBool = llvm::Function::Create(fmtBoolFnTy, llvm::Function::ExternalLinkage, "qc_fmt_bool", module);
                    }
                    llvm::Function* fmtPtr = module->getFunction("qc_fmt_ptr");
                    if (!fmtPtr) {
                        llvm::FunctionType* fmtPtrFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0), {llvm::PointerType::get(context, 0), builder->getInt32Ty(), builder->getInt1Ty()},
                            false);
                        fmtPtr = llvm::Function::Create(fmtPtrFnTy, llvm::Function::ExternalLinkage, "qc_fmt_ptr", module);
                    }
                    llvm::Function* fmtOctal = module->getFunction("qc_fmt_octal");
                    if (!fmtOctal) {
                        llvm::FunctionType* fmtOctalFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0), {builder->getInt64Ty(), builder->getInt32Ty(), builder->getInt1Ty()}, false);
                        fmtOctal = llvm::Function::Create(fmtOctalFnTy, llvm::Function::ExternalLinkage, "qc_fmt_octal", module);
                    }
                    llvm::Function* fmtHex = module->getFunction("qc_fmt_hex");
                    if (!fmtHex) {
                        llvm::FunctionType* fmtHexFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0), {builder->getInt64Ty(), builder->getInt32Ty(), builder->getInt1Ty()}, false);
                        fmtHex = llvm::Function::Create(fmtHexFnTy, llvm::Function::ExternalLinkage, "qc_fmt_hex", module);
                    }
                    llvm::Function* fmtScientific = module->getFunction("qc_fmt_scientific");
                    if (!fmtScientific) {
                        llvm::FunctionType* fmtScientificFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0),
                            {builder->getDoubleTy(), builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt1Ty()}, false);
                        fmtScientific = llvm::Function::Create(fmtScientificFnTy, llvm::Function::ExternalLinkage, "qc_fmt_scientific", module);
                    }
                    for (size_t i = 0; i < fmtString.length(); i++) {
                        c = fmtString[i];
                        if (c != '%') {
                            to_print += c;
                            continue;
                        }
                        i++;
                        if (i > fmtString.length() - 1) {
                            cg_error((*varAccess)->var_name_tok.pos, "unexpected end of fmt string: " + funcName);
                            return nullptr;
                        }
                        c = fmtString[i];
                        bool zero_pad = false;
                        int width = -1;
                        int precision = -1;
                        if (c == '%') {
                            to_print += '%';
                            continue;
                        }
                        if (c == '0') {
                            zero_pad = true;
                            i++;
                            if (i >= fmtString.size()) {
                                cg_error((*varAccess)->var_name_tok.pos, "invalid formater: " + funcName);
                                break;
                            }
                            c = fmtString[i];
                        }
                        if (std::isdigit(static_cast<unsigned char>(c))) {
                            std::string num;
                            while (i < fmtString.size() && std::isdigit(static_cast<unsigned char>(fmtString[i]))) {
                                num += fmtString[i];
                                i++;
                            }
                            c = fmtString[i];
                            width = std::stoi(num);
                        }
                        if (c == '.') {
                            i++;
                            if (i >= fmtString.size()) {
                                cg_error((*varAccess)->var_name_tok.pos, "invalid formater: " + funcName);
                                break;
                            }
                            c = fmtString[i];
                            if (std::isdigit(static_cast<unsigned char>(c))) {
                                std::string num;
                                while (i < fmtString.size() && std::isdigit(static_cast<unsigned char>(fmtString[i]))) {
                                    num += fmtString[i];
                                    i++;
                                }
                                c = fmtString[i];
                                precision = std::stoi(num);
                            } else {
                                cg_error((*varAccess)->var_name_tok.pos, "invalid formater: " + funcName);
                                break;
                            }
                        }
                        switch (c) {
                        case 'i': {
                            current_arg++;
                            if (goodArgs.size() - 1 < current_arg) {
                                cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                break;
                            }
                            llvm::Value* itgVal = emitExpr(goodArgs[current_arg]);
                            llvm::Value* bigIntSigned = nullptr;
                            if (!itgVal || !itgVal->getType()->isIntegerTy()) {
                                cg_error((*varAccess)->var_name_tok.pos, "%i formater takes an integer");
                                return nullptr;
                            }
                            llvm::Type* i64Ty = builder->getInt64Ty();
                            unsigned bitWidth = itgVal->getType()->getIntegerBitWidth();

                            if (bitWidth < 64) {
                                bigIntSigned = builder->CreateSExt(itgVal, i64Ty);
                            } else if (bitWidth > 64) {
                                bigIntSigned = builder->CreateTrunc(itgVal, i64Ty);
                            } else {
                                bigIntSigned = itgVal;
                            }
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            builder->CreateCall(printString,
                                                {builder->CreateCall(fmtInt, {bigIntSigned, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                              llvm::ConstantInt::get(builder->getInt32Ty(), precision),
                                                                              llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                            break;
                        }
                        case 'u': {
                            current_arg++;
                            if (goodArgs.size() - 1 < current_arg) {
                                cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                break;
                            }
                            llvm::Value* itgVal = emitExpr(goodArgs[current_arg]);
                            llvm::Value* bigIntSigned = nullptr;
                            if (!itgVal || !itgVal->getType()->isIntegerTy()) {
                                cg_error((*varAccess)->var_name_tok.pos, "%u formater takes an int-like (int, "
                                                                         "long int, short "
                                                                         "int, addr_t)");
                                return nullptr;
                            }
                            llvm::Type* i64Ty = builder->getInt64Ty();
                            unsigned bitWidth = itgVal->getType()->getIntegerBitWidth();

                            if (bitWidth < 64) {
                                bigIntSigned = builder->CreateSExt(itgVal, i64Ty);
                            } else if (bitWidth > 64) {
                                bigIntSigned = builder->CreateTrunc(itgVal, i64Ty);
                            } else {
                                bigIntSigned = itgVal;
                            }
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            builder->CreateCall(printString,
                                                {builder->CreateCall(fmtUInt, {bigIntSigned, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                               llvm::ConstantInt::get(builder->getInt32Ty(), precision),
                                                                               llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                            break;
                        }
                        case 's': {
                            current_arg++;
                            if (goodArgs.size() - 1 < current_arg) {
                                cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                return nullptr;
                            }
                            llvm::Value* stVal = emitExpr(goodArgs[current_arg]);
                            if (!stVal) {
                                cg_error((*varAccess)->var_name_tok.pos, "Failed to resolve argument for "
                                                                         "formatter in " +
                                                                             funcName);
                                return nullptr;
                            }
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            if (i >= fmtString.size()) {
                            } else if (fmtString[i + 1] == 't') {
                                i++;
                                llvm::Type* ty = stVal->getType();
                                if (auto structTy = llvm::dyn_cast<llvm::StructType>(stVal->getType())) {
                                    if (structTy->hasName()) {
                                        std::string className = structTy->getName().str();

                                        if (classTypes.find(className) != classTypes.end()) {
                                            cg_error((*varAccess)->var_name_tok.pos, "st formater takes a struct "
                                                                                     "instance: " +
                                                                                         funcName);
                                            break;
                                        } else if (structTypes.find(className) != structTypes.end()) {
                                            llvm::Function* nestedReprFn = module->getFunction(className + "_repr");
                                            if (nestedReprFn) {
                                                builder->CreateCall(printString, {builder->CreateCall(nestedReprFn, {stVal})});
                                            } else {
                                                builder->CreateCall(printString, {builder->CreateGlobalString("(unknown "
                                                                                                              "struct)")});
                                            }
                                        } else {
                                            cg_error((*varAccess)->var_name_tok.pos, "st formater takes a struct "
                                                                                     "instance: " +
                                                                                         funcName);
                                            break;
                                        }
                                    }
                                } else {
                                    cg_error((*varAccess)->var_name_tok.pos, "st formater takes a struct "
                                                                             "instance: " +
                                                                                 funcName);
                                    return nullptr;
                                }
                            } else {
                                if (!stVal->getType()->isPointerTy()) {
                                    cg_error((*varAccess)->var_name_tok.pos, "s formater takes a string: " + funcName);
                                    return nullptr;
                                }
                                builder->CreateCall(printString,
                                                    {builder->CreateCall(fmtStr, {stVal, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                  llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                            }
                            break;
                        }
                        case 'f': {
                            current_arg++;
                            if (goodArgs.size() - 1 < current_arg) {
                                cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                break;
                            }
                            llvm::Value* floatVal = emitExpr(goodArgs[current_arg]);
                            if (!floatVal || !floatVal->getType()->isFloatTy()) {
                                cg_error((*varAccess)->var_name_tok.pos, "f formater takes a float: " + funcName);
                                return nullptr;
                            }
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            builder->CreateCall(printString,
                                                {builder->CreateCall(fmtFloat, {builder->CreateFPExt(floatVal, builder->getDoubleTy()),
                                                                                llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                llvm::ConstantInt::get(builder->getInt32Ty(), precision),
                                                                                llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                            break;
                        }
                        case 'd': {
                            current_arg++;
                            if (goodArgs.size() - 1 < current_arg) {
                                cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                break;
                            }
                            llvm::Value* doubVal = emitExpr(goodArgs[current_arg]);
                            if (!doubVal || !doubVal->getType()->isDoubleTy()) {
                                cg_error((*varAccess)->var_name_tok.pos, "d formater takes a double: " + funcName);
                                return nullptr;
                            }
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            builder->CreateCall(printString,
                                                {builder->CreateCall(fmtDouble, {doubVal, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                 llvm::ConstantInt::get(builder->getInt32Ty(), precision),
                                                                                 llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                            break;
                        }
                        case 'c': {
                            current_arg++;
                            if (goodArgs.size() - 1 < current_arg) {
                                cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                break;
                            }
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            llvm::Value* cVal = emitExpr(goodArgs[current_arg]);
                            if (i >= fmtString.size()) {
                            } else if (fmtString[i + 1] == 's') {
                                i++;
                                llvm::Type* ty = cVal->getType();
                                if (auto structTy = llvm::dyn_cast<llvm::StructType>(cVal->getType())) {
                                    if (structTy->hasName()) {
                                        std::string className = structTy->getName().str();

                                        if (classTypes.find(className) != classTypes.end()) {
                                            auto [reprMethod, ownerClass] = findMethodInHierarchy(className, "repr");

                                            if (reprMethod) {
                                                std::vector<llvm::Value*> args;
                                                llvm::AllocaInst* temp = createEntryAlloca("temp_repr", ty);
                                                builder->CreateStore(cVal, temp);
                                                args.push_back(temp);

                                                builder->CreateCall(printString, {builder->CreateCall(reprMethod, args)});
                                            } else {
                                                to_print += "(reprless class)";
                                            }
                                        }
                                    }
                                } else {
                                    cg_error((*varAccess)->var_name_tok.pos, "cs formater takes a class instance: " + funcName);
                                    return nullptr;
                                }
                            } else {
                                if (!cVal->getType()->isIntegerTy(8)) {
                                    cg_error((*varAccess)->var_name_tok.pos, "c formater takes a char: " + funcName);
                                    return nullptr;
                                }
                                builder->CreateCall(printString,
                                                    {builder->CreateCall(fmtChar, {cVal, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                   llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                break;
                            }
                            break;
                        }
                        case 'b': {
                            current_arg++;
                            if (goodArgs.size() - 1 < current_arg) {
                                cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                break;
                            }
                            llvm::Value* boolVal = emitExpr(goodArgs[current_arg]);
                            if (!boolVal || !boolVal->getType()->isIntegerTy(1)) {
                                cg_error((*varAccess)->var_name_tok.pos, "b formater takes a bool: " + funcName);
                                return nullptr;
                            }
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            builder->CreateCall(printString,
                                                {builder->CreateCall(fmtBool, {boolVal, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                               llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                            break;
                        }
                        case 'q': {
                            current_arg++;
                            if (goodArgs.size() - 1 < current_arg) {
                                cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                break;
                            }
                            llvm::Value* qboolVal = emitExpr(goodArgs[current_arg]);
                            if (!qboolVal || !qboolVal->getType()->isIntegerTy(2)) {
                                cg_error((*varAccess)->var_name_tok.pos, "q formater takes a qbool: " + funcName);
                                return nullptr;
                            }
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            builder->CreateCall(printString,
                                                {builder->CreateCall(fmtQBool, {qboolVal, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                            break;
                        }
                        case 'x': {
                            current_arg++;
                            if (goodArgs.size() - 1 < current_arg) {
                                cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                break;
                            }
                            llvm::Value* itgVal = emitExpr(goodArgs[current_arg]);
                            llvm::Value* bigIntUnsigned;
                            if (!itgVal || !itgVal->getType()->isIntegerTy()) {
                                cg_error((*varAccess)->var_name_tok.pos, "x formater takes a int: " + funcName);
                                return nullptr;
                            }
                            llvm::Type* i64Ty = builder->getInt64Ty();
                            unsigned bitWidth = itgVal->getType()->getIntegerBitWidth();

                            if (bitWidth < 64) {
                                bigIntUnsigned = builder->CreateZExt(itgVal, i64Ty);
                            } else if (bitWidth > 64) {
                                bigIntUnsigned = builder->CreateTrunc(itgVal, i64Ty);
                            } else {
                                bigIntUnsigned = itgVal;
                            }
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            builder->CreateCall(printString,
                                                {builder->CreateCall(fmtHex, {bigIntUnsigned, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                              llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                            break;
                        }
                        case 'o': {
                            current_arg++;
                            if (goodArgs.size() - 1 < current_arg) {
                                cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                break;
                            }
                            llvm::Value* itgVal = emitExpr(goodArgs[current_arg]);
                            if (!itgVal || !itgVal->getType()->isIntegerTy()) {
                                cg_error((*varAccess)->var_name_tok.pos, "o formater takes a int: " + funcName);
                                return nullptr;
                            }
                            llvm::Type* i64Ty = builder->getInt64Ty();
                            llvm::Value* bigIntUnsigned;
                            unsigned bitWidth = itgVal->getType()->getIntegerBitWidth();

                            if (bitWidth < 64) {
                                bigIntUnsigned = builder->CreateZExt(itgVal, i64Ty);
                            } else if (bitWidth > 64) {
                                bigIntUnsigned = builder->CreateTrunc(itgVal, i64Ty);
                            } else {
                                bigIntUnsigned = itgVal;
                            }
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            builder->CreateCall(printString,
                                                {builder->CreateCall(fmtOctal, {bigIntUnsigned, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                            break;
                        }
                        case 'p': {
                            current_arg++;
                            if (goodArgs.size() - 1 < current_arg) {
                                cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                return nullptr;
                            }
                            llvm::Value* ptVal = emitExpr(goodArgs[current_arg]);
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            if (!ptVal || !ptVal->getType()->isPointerTy()) {
                                cg_error((*varAccess)->var_name_tok.pos, "p formater takes a pointer: " + funcName);
                                break;
                            }
                            builder->CreateCall(printString,
                                                {builder->CreateCall(fmtPtr, {ptVal, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                              llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                            break;
                        }
                        case 'e': {
                            current_arg++;
                            if (goodArgs.size() - 1 < current_arg) {
                                cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                return nullptr;
                            }
                            llvm::Value* decimalVal = emitExpr(goodArgs[current_arg]);
                            if (!decimalVal || !decimalVal->getType()->isFloatTy() && !decimalVal->getType()->isDoubleTy() &&
                                                   !decimalVal->getType()->isIntegerTy()) {
                                cg_error((*varAccess)->var_name_tok.pos, "e formater takes a number: " + funcName);
                            }
                            if (decimalVal->getType()->isIntegerTy()) {
                                decimalVal = builder->CreateSIToFP(decimalVal, builder->getDoubleTy());
                            } else if (decimalVal->getType()->isFloatTy()) {
                                decimalVal = builder->CreateFPExt(decimalVal, builder->getDoubleTy());
                            } else if (decimalVal->getType()->isDoubleTy()) {
                                decimalVal = decimalVal;
                            }
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            builder->CreateCall(printString,
                                                {builder->CreateCall(fmtScientific, {builder->CreateFPExt(decimalVal, builder->getDoubleTy()),
                                                                                     llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                     llvm::ConstantInt::get(builder->getInt32Ty(), precision),
                                                                                     llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                            break;
                        }
                        case 'a': {
                            current_arg++;
                            if (goodArgs.size() - 1 < current_arg) {
                                cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                return nullptr;
                            }

                            llvm::Value* val = emitExpr(goodArgs[current_arg]);
                            if (!val) {
                                cg_error((*varAccess)->var_name_tok.pos,
                                         "failed to evaluate argument " + std::to_string(current_arg) + ": " + funcName);
                                return nullptr;
                            }
                            llvm::Type* aTy = val->getType();
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            if (aTy->isIntegerTy(32) || aTy->isIntegerTy(64) || aTy->isIntegerTy(16)) {
                                builder->CreateCall(printString,
                                                    {builder->CreateCall(fmtInt, {builder->CreateZExt(val, builder->getInt64Ty()),
                                                                                  llvm::ConstantInt::get(builder->getInt64Ty(), width),
                                                                                  llvm::ConstantInt::get(builder->getInt32Ty(), precision),
                                                                                  llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                break;
                            }
                            if (auto structTy = llvm::dyn_cast<llvm::StructType>(aTy)) {
                                if (structTy->hasName()) {
                                    std::string className = structTy->getName().str();
                                    if (structTypes.find(className) != structTypes.end()) {
                                        llvm::Function* nestedReprFn = module->getFunction(className + "_repr");
                                        if (nestedReprFn) {
                                            builder->CreateCall(printString, {builder->CreateCall(nestedReprFn, {val})});
                                        } else {
                                            builder->CreateCall(printString, {builder->CreateGlobalString("(unknown struct)")});
                                        }
                                    }
                                }
                                break;
                            }
                            auto* varNode = *std::get_if<VarAccessNode*>(&goodArgs[current_arg]);
                            if ((aTy->isPointerTy() && std::get_if<StringNode>(&goodArgs[current_arg])) ||
                                (varNode && hasVarType(varNode->var_name_tok.value) &&
                                 findVarType(varNode->var_name_tok.value)->second == std::string("string"))) {
                                builder->CreateCall(printString,
                                                    {builder->CreateCall(fmtStr, {val, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                  llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                break;
                            }
                            if (aTy->isFloatTy()) {
                                builder->CreateCall(printString,
                                                    {builder->CreateCall(fmtFloat, {builder->CreateFPExt(val, builder->getDoubleTy()),
                                                                                    llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                    llvm::ConstantInt::get(builder->getInt32Ty(), precision),
                                                                                    llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                break;
                            }
                            if (aTy->isDoubleTy()) {
                                builder->CreateCall(printString,
                                                    {builder->CreateCall(fmtDouble, {val, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                     llvm::ConstantInt::get(builder->getInt32Ty(), precision),
                                                                                     llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                break;
                            }
                            if (auto structTy = llvm::dyn_cast<llvm::StructType>(aTy)) {
                                if (structTy->hasName()) {
                                    std::string className = structTy->getName().str();
                                    if (classTypes.find(className) != classTypes.end()) {
                                        auto [reprMethod, ownerClass] = findMethodInHierarchy(className, "repr");
                                        if (reprMethod) {
                                            std::vector<llvm::Value*> args;
                                            llvm::AllocaInst* temp = createEntryAlloca("temp_repr", aTy);
                                            builder->CreateStore(val, temp);
                                            args.push_back(temp);
                                            builder->CreateCall(printString, {builder->CreateCall(reprMethod, args)});
                                        } else {
                                            to_print += "(reprless class)";
                                        }
                                    }
                                }
                                if (aTy->isIntegerTy(8)) {
                                    builder->CreateCall(printString,
                                                        {builder->CreateCall(fmtChar, {val, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                       llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                    break;
                                }
                                break;
                            }
                            if (aTy->isIntegerTy(1)) {
                                builder->CreateCall(printString,
                                                    {builder->CreateCall(fmtBool, {val, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                   llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                break;
                            }
                            if (aTy->isIntegerTy(2)) {
                                builder->CreateCall(printString,
                                                    {builder->CreateCall(fmtQBool, {val, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                    llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                break;
                            }
                            if (aTy->isPointerTy()) {
                                builder->CreateCall(printString,
                                                    {builder->CreateCall(fmtPtr, {val, llvm::ConstantInt::get(builder->getInt32Ty(), width),
                                                                                  llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                break;
                            }
                            break;
                        }
                        default: cg_error((*varAccess)->var_name_tok.pos, "invalid formater: " + funcName); break;
                        }
                    }
                    llvm::Value* strVal = builder->CreateGlobalString(to_print);
                    builder->CreateCall(printString, {strVal});
                    to_print = "";
                    return nullptr;
                }
                if (funcName == "to_string" && !call.arg_nodes.empty()) {
                    AnyNode& argNode = call.arg_nodes.front();
                    llvm::Value* arg = emitExpr(argNode);
                    if (!arg) return nullptr;
                    return convertToString(arg, argNode);
                }

                if (funcName == "to_int" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "int");
                }

                if (funcName == "to_float" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "float");
                }

                if (funcName == "to_double" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "double");
                }

                if (funcName == "to_bool" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "bool");
                }

                if (funcName == "to_char" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "char");
                }
                if (funcName == "mapped_ptr" && !call.arg_nodes.empty()) {
                    llvm::Value* val = emitExpr(call.arg_nodes.front());
                    if (!(val->getType()->isIntegerTy())) {
                        cg_error((*varAccess)->var_name_tok.pos, "arg 1 must be a integer: " + funcName);
                        return nullptr;
                    }
                    if (!(val->getType()->isIntegerTy(getPtrSize()))) {
                        cg_error((*varAccess)->var_name_tok.pos,
                                 "arg 1 must be a integer the size of a pointer (" + std::to_string(getPtrSize()) + ") (addr_t or " +
                                     (getPtrSize() == 32 ? "int" : "long long") + "), got a " + std::to_string(val->getType()->getIntegerBitWidth()) +
                                     " bit integer (" +
                                     ((val->getType()->getIntegerBitWidth() == 32)
                                          ? "int"
                                          : ((val->getType()->getIntegerBitWidth() == 64) ? "long int" : "short int")) +
                                     ": " + funcName);
                        return nullptr;
                    }
                    return builder->CreateIntToPtr(val, builder->getPtrTy());
                }
                if (funcName == "to_address" && !call.arg_nodes.empty()) {
                    llvm::Value* val = emitExpr(call.arg_nodes.front());
                    if (!(val->getType()->isPointerTy())) {
                        cg_error((*varAccess)->var_name_tok.pos, "arg 1 must be a pointer: " + funcName);
                        return nullptr;
                    }
                    return builder->CreatePtrToInt(val, builder->getIntNTy(getPtrSize()), "addr");
                }
                if (funcName == "ternary" && !call.arg_nodes.empty()) {
                    if (call.arg_nodes.size() != 3) {
                        cg_error((*varAccess)->var_name_tok.pos, "must have exactly 3 args: " + funcName);
                        return nullptr;
                    }
                    auto it = std::next(call.arg_nodes.begin(), 1);
                    llvm::Value* is_tr = emitExpr(*it);
                    llvm::Value* is_fl = emitExpr(call.arg_nodes.back());
                    if (is_tr->getType() != is_fl->getType()) {
                        cg_error((*varAccess)->var_name_tok.pos, "arg 2 and 3 must be the same type: " + funcName);
                        return nullptr;
                    }
                    llvm::Value* val = emitExpr(call.arg_nodes.front());
                    if (val->getType()->isIntegerTy(1)) { return builder->CreateSelect(val, is_tr, is_fl, "select_val"); }
                    cg_error((*varAccess)->var_name_tok.pos, "arg 1 must be a boolean: " + funcName);
                    return nullptr;
                }
                if (funcName == "inline" && !call.arg_nodes.empty()) {
                    StringNode* data = std::get_if<StringNode>(&call.arg_nodes.front());
                    if (data == nullptr) {
                        cg_error((*varAccess)->var_name_tok.pos, "arg 1 must be a compile-time string: " + funcName);
                        return nullptr;
                    }
                    int outputs = 0;
                    int inputs = 0;
                    std::string asm_text = data->tok.value;
                    std::vector<AsmOp> output_ops;
                    std::vector<AsmOp> input_ops;
                    std::vector<std::string> clobbers;
                    /*
                    struct AsmOp {
          bool isOutput;
          int index;
          char kind;
          };  */
                    bool isATT = false;
                    std::string finalized = "";
                    for (int i = 0; i < asm_text.length(); i++) {
                        char c = asm_text[i];
                        if (i == 0 && c == ';') {
                            if (!(i + 2 >= asm_text.size())) { isATT = asm_text[i + 1] == 'A' && asm_text[i + 2] == 'T' && asm_text[i + 3] == 'T'; }
                        }
                        if (c != '$') {
                            finalized += c;
                            continue;
                        } else {
                            if (asm_text.length() <= i + 1) {
                                cg_error((*varAccess)->var_name_tok.pos, "invalid operand placeholder: " + funcName);
                                return nullptr;
                            }
                            finalized += c;
                            i++;
                            AsmOp op;
                            op.isOutput = false;
                            try {
                                if (i >= asm_text.size() || !std::isdigit(asm_text[i])) {
                                    cg_error((*varAccess)->var_name_tok.pos, "expected number after $: " + funcName);
                                    return nullptr;
                                }
                                int index = 0;
                                while (i < asm_text.size() && std::isdigit(asm_text[i])) {
                                    finalized += asm_text[i];
                                    index = index * 10 + (asm_text[i] - '0');
                                    i++;
                                }
                                op.index = index;
                            } catch (...) {
                                cg_error((*varAccess)->var_name_tok.pos, "invalid operand index: " + funcName);
                                return nullptr;
                            }
                            if (asm_text.length() <= i + 1) {
                                cg_error((*varAccess)->var_name_tok.pos, "invalid operand placeholder: " + funcName);
                                return nullptr;
                            }
                            if (i < asm_text.size() && asm_text[i] == '=') {
                                op.isOutput = true;
                                i++;
                            }
                            if (i >= asm_text.size()) {
                                cg_error((*varAccess)->var_name_tok.pos, "expected operand kind after asm "
                                                                         "operand index: " +
                                                                             funcName);
                                return nullptr;
                            }
                            char kind = asm_text[i];
                            if (kind != 'r' && kind != 'm' && kind != 'i' && kind != 'g') {
                                cg_error((*varAccess)->var_name_tok.pos, "invalid asm operand kind: " + funcName);
                                return nullptr;
                            }
                            op.kind = kind;
                            if (op.isOutput) {
                                outputs++;
                                output_ops.push_back(op);
                            } else {
                                inputs++;
                                input_ops.push_back(op);
                            }
                        }
                    }
                    StringNode* clobber_string_node = std::get_if<StringNode>(&call.arg_nodes.back());
                    if (clobber_string_node == nullptr) {
                        cg_error((*varAccess)->var_name_tok.pos, "final arg must be a compile-time string: " + funcName);
                        return nullptr;
                    }
                    std::string clobber_string = clobber_string_node->tok.value;
                    std::string current_clobber = "";
                    for (char c : clobber_string) {
                        if (c == '~') {
                            if (!current_clobber.empty()) { clobbers.push_back(current_clobber); }
                            current_clobber = "~";
                        } else {
                            current_clobber += c;
                        }
                    }
                    if (!(current_clobber.empty())) { clobbers.push_back(current_clobber); }
                    std::unordered_set<int> output_indices;
                    std::unordered_set<int> input_indices;
                    for (const auto& op : output_ops) output_indices.insert(op.index);
                    for (const auto& op : input_ops) input_indices.insert(op.index);

                    for (int idx : input_indices) {
                        if (output_indices.contains(idx)) {
                            cg_error((*varAccess)->var_name_tok.pos, "asm operand " + std::to_string(idx) + " used as both input and output");
                            return nullptr;
                        }
                    }

                    int output_count = (int)output_indices.size();
                    for (int i = 0; i < output_count; i++) {
                        if (!output_indices.contains(i)) {
                            cg_error((*varAccess)->var_name_tok.pos, "output operands must be contiguous "
                                                                     "starting at index 0");
                            return nullptr;
                        }
                    }

                    for (int idx : input_indices) {
                        if (idx < output_count) {
                            cg_error((*varAccess)->var_name_tok.pos, "input operands must come after all outputs");
                            return nullptr;
                        }
                    }
                    std::map<int, AsmOp> unique_outputs;
                    std::map<int, AsmOp> unique_inputs;
                    for (const auto& op : output_ops) {
                        if (!unique_outputs.contains(op.index)) { unique_outputs[op.index] = op; }
                    }
                    for (const auto& op : input_ops) {
                        if (!unique_inputs.contains(op.index)) { unique_inputs[op.index] = op; }
                    }
                    std::vector<llvm::Type*> input_types;
                    std::vector<llvm::Value*> input_values;

                    std::vector<llvm::Type*> output_types;
                    std::vector<llvm::Value*> output_targets;
                    for (auto& [idx, op] : unique_inputs) {
                        int arg_pos = idx + 1;
                        if (arg_pos >= call.arg_nodes.size() - 1) {
                            cg_error((*varAccess)->var_name_tok.pos, "asm input index out of range");
                            return nullptr;
                        }
                        auto it = std::next(call.arg_nodes.begin(), arg_pos);
                        auto& arg_node = *it;
                        llvm::Value* val = emitExpr(arg_node);
                        if (val == nullptr) { return nullptr; }
                        input_values.push_back(val);
                        input_types.push_back(val->getType());
                    }
                    for (auto& [idx, op] : unique_outputs) {
                        int arg_pos = idx + 1;
                        if (arg_pos >= call.arg_nodes.size() - 1) {
                            cg_error((*varAccess)->var_name_tok.pos, "asm output index out of range");
                            return nullptr;
                        }
                        auto it = std::next(call.arg_nodes.begin(), arg_pos);
                        auto& arg_node = *it;
                        auto* out_var = safe_get<VarAccessNode>(arg_node);
                        if (out_var == nullptr) {
                            cg_error((*varAccess)->var_name_tok.pos, "asm outputs must be variables");
                            return nullptr;
                        }

                        llvm::Value* out_ptr = resolveVariable(out_var->var_name_tok.value);
                        if (out_ptr == nullptr) {
                            cg_error((*varAccess)->var_name_tok.pos, "unknown output variable: " + out_var->var_name_tok.value);
                            return nullptr;
                        }
                        llvm::Type* out_ty = llvmTypeFor(resolveVarType(out_var->var_name_tok.value));
                        output_targets.push_back(out_ptr);
                        output_types.push_back(out_ty);
                    }
                    llvm::Type* ret_ty = nullptr;
                    if (output_types.empty()) {
                        ret_ty = builder->getVoidTy();
                    } else if (output_types.size() == 1) {
                        ret_ty = output_types[0];
                    } else {
                        ret_ty = llvm::StructType::get(context, output_types);
                    }
                    llvm::FunctionType* fn_ty = llvm::FunctionType::get(ret_ty, input_types, false);
                    std::string constraints = "";
                    bool first = true;
                    for (auto& [idx, op] : unique_outputs) {
                        if (!first) constraints += ",";
                        constraints += "=";
                        constraints += op.kind;
                        first = false;
                    }
                    for (auto& [idx, op] : unique_inputs) {
                        if (!first) constraints += ",";
                        constraints += op.kind;
                        first = false;
                    }
                    for (const auto& clobber : clobbers) {
                        if (!first) constraints += ",";
                        constraints += clobber;
                        first = false;
                    }
                    llvm::InlineAsm* asm_fn;
                    if (isATT) {
                        asm_fn = llvm::InlineAsm::get(fn_ty, finalized, constraints, true);
                    } else {
                        asm_fn = llvm::InlineAsm::get(fn_ty, finalized, constraints, true, false, llvm::InlineAsm::AD_Intel);
                    }

                    llvm::Value* result = builder->CreateCall(fn_ty, asm_fn, input_values);
                    if (output_targets.empty()) {
                        return result;
                    } else if (output_targets.size() == 1) {
                        builder->CreateStore(result, output_targets[0]);
                        return result;
                    } else {
                        for (unsigned i = 0; i < output_targets.size(); i++) {
                            llvm::Value* field = builder->CreateExtractValue(result, {i});
                            builder->CreateStore(field, output_targets[i]);
                        }
                        return result;
                    }
                }
                if (funcName == "next" && !call.arg_nodes.empty()) {
                    if (auto acc = std::get_if<VarAccessNode*>(&call.arg_nodes.front())) {
                        std::string var_name = (*acc)->var_name_tok.value;
                        if (resolveVarType(var_name) != "...") {
                            cg_error((*varAccess)->var_name_tok.pos, "Argument one must be a variadic argument: " + funcName);
                            return nullptr;
                        }
                        StringNode* expectedType = std::get_if<StringNode>(&call.arg_nodes.back());
                        if (!expectedType) {
                            cg_error((*varAccess)->var_name_tok.pos, "Argument two must be a string storing the type: " + funcName);
                            return nullptr;
                        }
                        llvm::Value* ConvertedValue = nullptr;
                        llvm::Function* nextElem = module->getFunction("qc_variadic_next");
                        if (!nextElem) {
                            llvm::FunctionType* nextElemFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0),
                                                                                       {llvm::PointerType::get(context, 0)}, false);
                            nextElem = llvm::Function::Create(nextElemFnTy, llvm::Function::InternalLinkage, "qc_variadic_next", module);
                        }
                        llvm::Value* VariableAddr = resolveVariable(var_name);
                        llvm::Value* RawSlot = builder->CreateCall(nextElem, builder->CreateLoad(builder->getPtrTy(), VariableAddr, "variad"),
                                                                   "variadc_arg");

                        llvm::Type* TargetType = llvmTypeFor(expectedType->tok.value);
                        if (TargetType->isIntegerTy()) {
                            ConvertedValue = builder->CreatePtrToInt(RawSlot, TargetType, "vararg_int");
                        } else if (TargetType->isPointerTy()) {
                            ConvertedValue = builder->CreateBitCast(RawSlot, TargetType, "vararg_ptr");
                        } else if (TargetType->isFloatingPointTy()) {
                            llvm::Type* Int64Ty = builder->getInt64Ty();
                            llvm::Value* RawInt = builder->CreatePtrToInt(RawSlot, Int64Ty, "vararg_fp_bits");

                            if (TargetType->isFloatTy()) {
                                llvm::Value* Int32Trunc = builder->CreateTrunc(RawInt, builder->getInt32Ty());
                                ConvertedValue = builder->CreateBitCast(Int32Trunc, TargetType, "vararg_float");
                            } else {
                                ConvertedValue = builder->CreateBitCast(RawInt, TargetType, "vararg_double");
                            }
                        } else if (TargetType->isStructTy()) {
                            ConvertedValue = builder->CreateLoad(TargetType, RawSlot, "vararg_struct");
                        }
                        return ConvertedValue;
                    } else {
                        cg_error((*varAccess)->var_name_tok.pos, "Argument one must be a direct variadic argument: " + funcName);
                    }
                    return nullptr;
                }
                if (funcName == "is_empty" && !call.arg_nodes.empty()) {
                    if (auto acc = std::get_if<VarAccessNode*>(&call.arg_nodes.back())) {
                        std::string var_name = (*acc)->var_name_tok.value;
                        if (resolveVarType(var_name) != "...") {
                            cg_error((*acc)->var_name_tok.pos, "Argument must be a variadic argument: " + funcName);
                            return nullptr;
                        }
                        llvm::Function* isEmpty = module->getFunction("qc_variadic_is_empty");
                        if (!isEmpty) {
                            llvm::FunctionType* isEmptyFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0),
                                                                                      {llvm::PointerType::get(context, 0)}, false);
                            isEmpty = llvm::Function::Create(isEmptyFnTy, llvm::Function::InternalLinkage, "qc_variadic_is_empty", module);
                        }
                        llvm::Value* VariableAddr = resolveVariable(var_name);
                        return builder->CreateCall(isEmpty, builder->CreateLoad(builder->getPtrTy(), VariableAddr, "variad"), "variadc_is_empty");
                    } else {
                        cg_error((*acc)->var_name_tok.pos, "Argument must be a direct variadic argument: " + funcName);
                    }
                    return nullptr;
                }
                llvm::Function* fn = module->getFunction(runtimeName);
                if (!fn) {
                    cg_error((*varAccess)->var_name_tok.pos, "Built-in function not found in runtime: " + runtimeName);
                    return nullptr;
                }
                llvm::FunctionType* builtinFnTy = fn->getFunctionType();
                std::vector<std::string> emptyMetadata;
                std::vector<llvm::Value*> args = emitAdaptedArgs(call.arg_nodes, builtinFnTy, emptyMetadata);
                if (call.arg_nodes.size() != args.size()) return nullptr;
                llvm::Type* retTy = fn->getReturnType();
                return builder->CreateCall(fn, args, retTy->isVoidTy() ? "" : "builtin_call");
            }
        }
        llvm::Value* calleeVal = nullptr;
        llvm::FunctionType* fnTy = nullptr;
        std::string funcName = "";
        if (auto* varAccess = std::get_if<VarAccessNode*>(&call.node_to_call)) {
            std::string name = (*varAccess)->var_name_tok.value;
            llvm::Value* varAddr = getVarAddress(name);
            if (varAddr) {
                if (auto lmbt = resolveLambdaType(name)) {
                    fnTy = lmbt;
                    calleeVal = emitExpr(call.node_to_call);
                }
            } else {
                llvm::Function* resolved = resolveFunction(name);
                if (resolved) {
                    calleeVal = resolved;
                    fnTy = resolved->getFunctionType();
                }
            }
            if (!calleeVal) {
                cg_error((*varAccess)->var_name_tok.pos, "Undeclared function or variable: " + name);
                return nullptr;
            }
            funcName = name;
        }
        if (!fnTy) {
            cg_error(Position(), "Could not determine function type");
            return nullptr;
        }
        bool hasSpread = false;
        for (auto& argNode : call.arg_nodes) {
            if (std::holds_alternative<SpreadNode*>(argNode)) {
                hasSpread = true;
                break;
            }
        }

        if (hasSpread) {
            cg_error(Position(), "Spread is no longer allowed in function calls.");
            return nullptr;
        }

        std::vector<std::string> paramTypeStrings;
        std::string lastVarName = "";
        auto defIt = functionDefs.find(funcName);
        if (defIt != functionDefs.end()) {
            for (auto& p : defIt->second->params) {
                paramTypeStrings.push_back(p.type.value);
                lastVarName = p.name.value;
            }
        }
        std::vector<llvm::Value*> args = emitAdaptedArgs(call.arg_nodes, fnTy, paramTypeStrings);
        if (call.arg_nodes.size() < args.size()) {
            cg_error(Position(), "Too few args to function.");
            return nullptr;
        }
        if (!paramTypeStrings.empty() && paramTypeStrings.back() == "...") {
            if (lastVarName == "<varadic>") {

            } else {
                size_t num_fixed_args = paramTypeStrings.size() - 1;
                std::vector<llvm::Value*> var_vals(args.begin() + num_fixed_args, args.end());
                args.resize(num_fixed_args);
                llvm::Value* args_cnt = builder->getInt32(var_vals.size());
                llvm::Value* items_array = builder->CreateAlloca(builder->getPtrTy(), args_cnt, "varadics_array");
                for (size_t i = 0; i < var_vals.size(); ++i) {
                    llvm::Value* index = builder->getInt32(i);
                    llvm::Value* element_ptr = builder->CreateGEP(builder->getPtrTy(), items_array, index);
                    llvm::Value* ValueToStore = var_vals[i];
                    llvm::Type* valTy = ValueToStore->getType();
                    if (valTy->isIntegerTy()) {
                        ValueToStore = builder->CreateIntToPtr(ValueToStore, builder->getPtrTy(), "vararg_int_to_ptr");
                    } else if (valTy->isFloatingPointTy()) {
                        llvm::Value* Int64Bits = nullptr;
                        if (valTy->isFloatTy()) {
                            llvm::Value* Int32Bits = builder->CreateBitCast(ValueToStore, builder->getInt32Ty(), "float_to_i32");
                            Int64Bits = builder->CreateZExt(Int32Bits, builder->getInt64Ty(), "i32_to_i64");
                        } else {
                            Int64Bits = builder->CreateBitCast(ValueToStore, builder->getInt64Ty(), "double_to_i64");
                        }
                        ValueToStore = builder->CreateIntToPtr(Int64Bits, builder->getPtrTy(), "fp_bits_to_ptr");
                    }
                    builder->CreateStore(ValueToStore, element_ptr);
                }
                llvm::StructType* VaradicStructTy = llvm::StructType::get(context,
                                                                          {builder->getPtrTy(), builder->getInt32Ty(), builder->getInt32Ty()});
                llvm::Value* variadic_struct = builder->CreateAlloca(VaradicStructTy, nullptr, "variadic_struct");
                llvm::Value* Field0Ptr = builder->CreateStructGEP(VaradicStructTy, variadic_struct, 0);
                builder->CreateStore(items_array, Field0Ptr);
                llvm::Value* Field1Ptr = builder->CreateStructGEP(VaradicStructTy, variadic_struct, 1);
                builder->CreateStore(args_cnt, Field1Ptr);
                llvm::Value* Field2Ptr = builder->CreateStructGEP(VaradicStructTy, variadic_struct, 2);
                builder->CreateStore(builder->getInt32(0), Field2Ptr);
                args.push_back(variadic_struct);
            }
        }
        if (defIt != functionDefs.end()) {
            auto& fnDef = defIt->second;
            size_t paramIdx = 0;

            for (auto& param : fnDef->params) {
                if (paramIdx >= args.size()) {
                    if (param.default_value.has_value()) {
                        AnyNode& defaultRef = const_cast<AnyNode&>(param.default_value.value());
                        llvm::Value* defVal = emitExpr(defaultRef);
                        if (!defVal) {
                            cg_error(Position(), "Failed to evaluate default parameter");
                            return nullptr;
                        }
                        args.push_back(defVal);
                    } else {
                        cg_error(Position(), "Missing required argument at position " + std::to_string(paramIdx));
                        return nullptr;
                    }
                }
                paramIdx++;
            }
        }
        llvm::Type* retTy = fnTy->getReturnType();
        auto* callInst = builder->CreateCall(fnTy, calleeVal, args, retTy->isVoidTy() ? "" : "calltmp");

        return retTy->isVoidTy() ? nullptr : callInst;
    } else if (auto arrAcc = safe_get<ArrayAccessNode>(node)) {
        std::string ptrTy = getExpressionType(arrAcc->base);
        if (ptrTy.ends_with("*") || ptrTy == "@nullptr") {
            if (ptrTy == "@nullptr") {
                cg_error(Position(), "Attempted to dereference nullptr");
                return nullptr;
            }
            if (ptrTy == "void*") {
                cg_error((*bin)->op_tok.pos, "Pointer arithmetic cannot be preformed on void pointers");
                return nullptr;
            }
            std::string valueTy = getExpressionType(arrAcc->indices[0]);
            if (valueTy != "int") {
                cg_error(Position(), "Attempted to index a pointer with a non-integer value.");
                return nullptr;
            }
            llvm::Value* value = emitExpr(arrAcc->indices[0]);
            ptrTy.pop_back();
            llvm::Value* addr = builder->CreateGEP(llvmTypeFor(ptrTy), emitExpr(arrAcc->base), value, "ptr_arr_addr");
            return builder->CreateLoad(llvmTypeFor(ptrTy), addr, "ptr_arr_val");
        }
        if (auto varAcc = safe_get<VarAccessNode>(arrAcc->base)) {
            std::string name = varAcc->var_name_tok.value;
            if (hasJaggedArray(name)) {
                auto jagIt = findJaggedArray(name);
                llvm::Value* alloc = getVarAddress(name);
                if (!alloc) {
                    cg_error(Position(), "Unknown jagged array: " + name);
                    return nullptr;
                }

                llvm::Value* jaggedPtr = builder->CreateLoad(llvm::PointerType::get(context, 0), alloc, "jagged_ptr");
                llvm::ArrayType* indicesArrTy = llvm::ArrayType::get(builder->getInt32Ty(), arrAcc->indices.size());
                llvm::AllocaInst* indicesAlloc = createEntryAlloca("indices_arr", indicesArrTy);

                for (size_t i = 0; i < arrAcc->indices.size(); i++) {
                    llvm::Value* indexVal = emitExpr(arrAcc->indices[i]);
                    if (!indexVal) return nullptr;

                    std::vector<llvm::Value*> indices = {builder->getInt32(0), builder->getInt32(i)};
                    llvm::Value* idxPtr = builder->CreateInBoundsGEP(indicesArrTy, indicesAlloc, indices);
                    builder->CreateStore(indexVal, idxPtr);
                }
                llvm::Function* getFn = module->getFunction("qc_jagged_array_get");
                if (!getFn) {
                    llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                    llvm::Type* intPtrTy = llvm::PointerType::get(context, 0);
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(voidPtrTy, {voidPtrTy, intPtrTy, builder->getInt32Ty()}, false);
                    getFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_jagged_array_get", module);
                }

                std::vector<llvm::Value*> idxIndices = {builder->getInt32(0), builder->getInt32(0)};
                llvm::Value* indicesPtr = builder->CreateInBoundsGEP(indicesArrTy, indicesAlloc, idxIndices);

                llvm::Value* elemPtr = builder->CreateCall(getFn, {jaggedPtr, indicesPtr, builder->getInt32(arrAcc->indices.size())},
                                                           "jagged_elem_ptr");
                int elemTypeCode = jagIt->second.first;
                llvm::Type* elemTy = nullptr;
                switch (elemTypeCode) {
                case 0: elemTy = builder->getInt32Ty(); break;
                case 1: elemTy = builder->getFloatTy(); break;
                case 2: elemTy = builder->getDoubleTy(); break;
                case 3: elemTy = builder->getInt8Ty(); break;
                case 4: elemTy = builder->getInt1Ty(); break;
                case 5: elemTy = builder->getIntNTy(2); break;
                case 6: elemTy = llvm::PointerType::get(context, 0); break;
                }
                llvm::Value* typedPtr = builder->CreateBitCast(elemPtr, llvm::PointerType::get(context, 0));
                return builder->CreateLoad(elemTy, typedPtr, "jagged_elem");
            }
            if (hasList(name)) {
                auto listIt = findList(name);
                llvm::Value* alloc = getVarAddress(name);
                if (!alloc) {
                    cg_error(Position(), "Unknown list: " + name);
                    return nullptr;
                }

                llvm::Value* listPtr = builder->CreateLoad(llvm::PointerType::get(context, 0), alloc, "list_ptr");

                llvm::Function* getFn = module->getFunction("qc_list_get");
                if (!getFn) {
                    llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(voidPtrTy, {voidPtrTy, builder->getInt32Ty()}, false);
                    getFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_list_get", module);
                }

                llvm::Value* indexVal = emitExpr(arrAcc->indices[0]);
                if (!indexVal) return nullptr;

                llvm::Value* elemPtr = builder->CreateCall(getFn, {listPtr, indexVal}, "list_elem_ptr");
                llvm::Value* nestedPtr = elemPtr;
                if (arrAcc->indices.size() > 1) {
                    for (size_t i = 1; i < arrAcc->indices.size(); i++) {
                        llvm::Value* idx = emitExpr(arrAcc->indices[i]);
                        if (!idx) return nullptr;
                        int elemTypeCode = listIt->second;
                        llvm::Type* elemTy = nullptr;
                        switch (elemTypeCode) {
                        case 0: elemTy = builder->getInt32Ty(); break;
                        case 1: elemTy = builder->getFloatTy(); break;
                        case 2: elemTy = builder->getDoubleTy(); break;
                        case 3: elemTy = builder->getInt8Ty(); break;
                        case 4: elemTy = builder->getInt1Ty(); break;
                        case 5: elemTy = builder->getIntNTy(2); break;
                        case 6: elemTy = llvm::PointerType::get(context, 0); break;
                        }

                        nestedPtr = builder->CreateGEP(elemTy, nestedPtr, idx, "nested_elem_ptr");
                    }

                    int elemTypeCode = listIt->second;
                    llvm::Type* elemTy = nullptr;
                    switch (elemTypeCode) {
                    case 0: elemTy = builder->getInt32Ty(); break;
                    case 1: elemTy = builder->getFloatTy(); break;
                    case 2: elemTy = builder->getDoubleTy(); break;
                    case 3: elemTy = builder->getInt8Ty(); break;
                    case 4: elemTy = builder->getInt1Ty(); break;
                    case 5: elemTy = builder->getIntNTy(2); break;
                    case 6: elemTy = llvm::PointerType::get(context, 0); break;
                    }

                    return builder->CreateLoad(elemTy, nestedPtr, "list_nested_elem");
                }

                int elemTypeCode = listIt->second;
                llvm::Type* elemTy = nullptr;
                switch (elemTypeCode) {
                case 0: elemTy = builder->getInt32Ty(); break;
                case 1: elemTy = builder->getFloatTy(); break;
                case 2: elemTy = builder->getDoubleTy(); break;
                case 3: elemTy = builder->getInt8Ty(); break;
                case 4: elemTy = builder->getInt1Ty(); break;
                case 5: elemTy = builder->getIntNTy(2); break;
                case 6: elemTy = llvm::PointerType::get(context, 0); break;
                }

                llvm::Value* typedPtr = builder->CreateBitCast(elemPtr, llvm::PointerType::get(context, 0));
                return builder->CreateLoad(elemTy, typedPtr, "list_elem");
            }
            if (hasMap(name)) {
                auto mapIt = findMap(name);
                llvm::Value* alloc = getVarAddress(name);
                if (!alloc) {
                    cg_error(Position(), "Unknown map: " + name);
                    return nullptr;
                }

                llvm::Value* mapPtr = builder->CreateLoad(llvm::PointerType::get(context, 0), alloc, "map_ptr");

                llvm::Value* keyVal = emitExpr(arrAcc->indices[0]);
                if (!keyVal) return nullptr;

                llvm::Value* keyPtr;
                if (keyVal->getType()->isPointerTy()) {
                    keyPtr = keyVal;
                } else {
                    llvm::AllocaInst* keyAlloc = createEntryAlloca("map_key", keyVal->getType());
                    builder->CreateStore(keyVal, keyAlloc);
                    keyPtr = builder->CreateBitCast(keyAlloc, llvm::PointerType::get(context, 0));
                }
                llvm::Function* getFn = module->getFunction("qc_map_get");
                if (!getFn) {
                    llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(voidPtrTy, {voidPtrTy, voidPtrTy}, false);
                    getFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_map_get", module);
                }

                llvm::Value* valPtr = builder->CreateCall(getFn, {mapPtr, keyPtr}, "map_val_ptr");

                int valueTypeCode = mapIt->second.second;

                if (valueTypeCode == 6) {
                    return valPtr;
                } else {
                    llvm::Type* valueTy = getTypeFromCode(valueTypeCode);
                    llvm::Value* typedPtr = builder->CreateBitCast(valPtr, llvm::PointerType::get(context, 0));
                    return builder->CreateLoad(valueTy, typedPtr, "map_val");
                }
            }
            llvm::Value* alloc = getVarAddress(name);
            if (!alloc) {
                cg_error(Position(), "Unknown array: " + name);
                return nullptr;
            }

            llvm::Value* arrAlloc = alloc;
            llvm::Type* arrTy = getPointeeType(name);

            if (arrTy->isPointerTy()) {
                llvm::Value* ptr = builder->CreateLoad(arrTy, arrAlloc, "arr_ptr");
                llvm::Value* indexVal = emitExpr(arrAcc->indices[0]);
                if (!indexVal) return nullptr;
                std::string baseType = arrayTypeStrings[name];
                llvm::Type* elemTy = llvmTypeFor(baseType);

                llvm::Value* elemPtr = builder->CreateGEP(elemTy, ptr, indexVal, "arr_elem_ptr");

                return builder->CreateLoad(elemTy, elemPtr, "arr_elem");
            } else if (arrTy->isArrayTy()) {
                std::vector<llvm::Value*> indices = {builder->getInt32(0)};

                for (size_t i = 0; i < arrAcc->indices.size(); i++) {
                    llvm::Value* indexVal = emitExpr(arrAcc->indices[i]);
                    if (!indexVal) return nullptr;
                    indices.push_back(indexVal);
                }

                llvm::Value* elemPtr = builder->CreateInBoundsGEP(arrTy, arrAlloc, indices, "arr_elem_ptr");
                llvm::Type* elemTy = arrTy;
                for (size_t i = 0; i < arrAcc->indices.size(); i++) {
                    if (elemTy->isArrayTy()) { elemTy = elemTy->getArrayElementType(); }
                }

                return builder->CreateLoad(elemTy, elemPtr, "arr_elem");
            }
        }

        cg_error(Position(), "Complex array access not yet supported");
        return nullptr;
    } else if (auto propAccess = std::get_if<PropertyAccessNode*>(&node)) {
        std::string propName = (*propAccess)->property_name.value;

        std::string baseName = "";
        bool isEnum = false;
        if (auto varAccess = std::get_if<VarAccessNode*>(&*(*propAccess)->base)) {
            baseName = (*varAccess)->var_name_tok.value;
            if ((*varAccess)->var_name_tok.value == "this" && currentThis && !currentClassName.empty()) {
                int fieldIdx = getFlattenedFieldIndex(currentClassName, propName);

                if (fieldIdx == -1) {
                    cg_error(Position(), "Unknown property: " + propName);
                    return nullptr;
                }

                auto [fieldOwnerClass, fieldAccess] = getFieldOwner(currentClassName, propName);
                if (!canAccessField(currentClassName, fieldOwnerClass, fieldAccess)) {
                    cg_error(Position(), "Cannot access " + fieldAccess + " field");
                    return nullptr;
                }

                llvm::StructType* classTy = classTypes[currentClassName];
                llvm::Type* fieldTy = classTy->getElementType(fieldIdx);
                llvm::Value* fieldPtr = builder->CreateStructGEP(classTy, currentThis, fieldIdx);
                return builder->CreateLoad(fieldTy, fieldPtr, propName);
            }
            std::string resolved = resolveTypeName(baseName);
            auto enumIt = enumTypes.find(resolved);
            if (enumIt != enumTypes.end()) {
                isEnum = true;
                std::string fullName = resolved + "." + propName;
                auto memberIt = enumMemberInfo.find(fullName);

                if (memberIt != enumMemberInfo.end()) {
                    int tag = memberIt->second.tag;
                    std::string type = memberIt->second.type;
                    std::string value = memberIt->second.value;

                    llvm::StructType* enumTy = enumTypes[baseName];
                    llvm::Value* enumVal = llvm::UndefValue::get(enumTy);

                    enumVal = builder->CreateInsertValue(enumVal, builder->getInt32(tag), 0);

                    llvm::Value* dataPtr = createEnumData(type, value);
                    enumVal = builder->CreateInsertValue(enumVal, dataPtr, 1);

                    return enumVal;
                } else {
                    cg_error(Position(), "Enum " + baseName + " has no member " + propName);
                    return nullptr;
                }
            }
        }

        if (isEnum) {
            cg_error(Position(), "Enum member not found");
            return nullptr;
        }
        if (propName == "length") {
            if (hasArrayLength(baseName)) {
                auto lenIt = findArrayLength(baseName);
                return builder->getInt32(lenIt->second);
            }
            auto runtimeIt = runtimeArraySizes.find(baseName);
            if (runtimeIt != runtimeArraySizes.end()) { return builder->CreateLoad(builder->getInt32Ty(), runtimeIt->second, "runtime_len"); }
            auto it = locals.find(baseName);
            if (it != locals.end()) {
                llvm::Type* allocTy = getPointeeType(baseName);
                if (allocTy && allocTy->isArrayTy()) { return builder->getInt32(allocTy->getArrayNumElements()); }
            }
            llvm::Value* baseVal = emitExpr(*(*propAccess)->base);
            if (!baseVal) return nullptr;

            llvm::Function* lenFn = module->getFunction("qc_list_length");
            if (!lenFn) {
                llvm::FunctionType* ty = llvm::FunctionType::get(builder->getInt32Ty(), {llvm::PointerType::get(context, 0)}, false);
                lenFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_list_length", module);
            }

            return builder->CreateCall(lenFn, {baseVal}, "list_len");
        }
        if (propName == "size") {
            llvm::Value* baseVal = emitExpr(*(*propAccess)->base);
            if (!baseVal) return nullptr;

            llvm::Function* sizeFn = module->getFunction("qc_map_size");
            if (!sizeFn) {
                llvm::FunctionType* ty = llvm::FunctionType::get(builder->getInt32Ty(), {llvm::PointerType::get(context, 0)}, false);
                sizeFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_map_size", module);
            }

            return builder->CreateCall(sizeFn, {baseVal}, "map_size");
        }
        llvm::Value* baseVal = emitExpr(*(*propAccess)->base);
        if (!baseVal) return nullptr;

        llvm::Type* baseTy = baseVal->getType();
        if (baseTy->isPointerTy()) {
            if (auto varAccess = std::get_if<VarAccessNode*>(&*(*propAccess)->base)) {
                std::string varName = (*varAccess)->var_name_tok.value;
                llvm::Value* locAlloc = getVarAddress(varName);
                if (locAlloc) {
                    llvm::Type* allocTy = getPointeeType(varName);

                    if (auto structTy = llvm::dyn_cast<llvm::StructType>(allocTy)) {
                        std::string structName = structTy->getName().str();

                        auto userTypeIt = userTypes.find(structName);
                        if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Struct) {
                            int fieldIdx = -1;
                            for (size_t i = 0; i < userTypeIt->second.fields.size(); i++) {
                                if (userTypeIt->second.fields[i].name == propName) {
                                    fieldIdx = i;
                                    break;
                                }
                            }

                            if (fieldIdx == -1) {
                                cg_error(Position(), "Struct " + structName + " has no field " + propName);
                                return nullptr;
                            }

                            llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, locAlloc, fieldIdx, propName + "_ptr");
                            llvm::Type* fieldTy = structTy->getElementType(fieldIdx);
                            return builder->CreateLoad(fieldTy, fieldPtr, propName);
                        }
                    }
                }
            }
        }
        if (auto structTy = llvm::dyn_cast<llvm::StructType>(baseTy)) {
            std::string structName = structTy->getName().str();

            auto userTypeIt = userTypes.find(structName);
            if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Struct) {
                int fieldIdx = -1;
                for (size_t i = 0; i < userTypeIt->second.fields.size(); i++) {
                    if (userTypeIt->second.fields[i].name == propName) {
                        fieldIdx = i;
                        break;
                    }
                }

                if (fieldIdx == -1) {
                    cg_error(Position(), "Struct " + structName + " has no field " + propName);
                    return nullptr;
                }
                llvm::Value* result = builder->CreateExtractValue(baseVal, fieldIdx, propName);
                return result;
            }
        }
        for (auto& [className, classTy] : classTypes) {
            if (baseTy == classTy) {
                int fieldIdx = getFlattenedFieldIndex(className, propName);

                if (fieldIdx == -1) {
                    cg_error(Position(), "Field not found: " + propName);
                    return nullptr;
                }
                auto [fieldOwnerClass, fieldAccess] = getFieldOwner(className, propName);
                if (!canAccessField(currentClassName, fieldOwnerClass, fieldAccess)) {
                    cg_error(Position(), "Cannot access " + fieldAccess + " field");
                    return nullptr;
                }

                llvm::Type* fieldTy = classTy->getElementType(fieldIdx);
                for (auto& [unionName, unionTy] : unionTypes) {
                    if (fieldTy == unionTy) {
                        llvm::AllocaInst* temp = createEntryAlloca("temp_obj", baseTy);
                        builder->CreateStore(baseVal, temp);
                        llvm::Value* fieldPtr = builder->CreateStructGEP(classTy, temp, fieldIdx);
                        return builder->CreateLoad(unionTy, fieldPtr, "union_field");
                    }
                }
                llvm::Value* ptr;
                if (baseTy->isPointerTy()) {
                    ptr = baseVal;
                } else {
                    llvm::AllocaInst* temp = createEntryAlloca("temp_obj", baseTy);
                    builder->CreateStore(baseVal, temp);
                    ptr = temp;
                }

                llvm::Value* fieldPtr = builder->CreateStructGEP(classTy, ptr, fieldIdx);
                return builder->CreateLoad(fieldTy, fieldPtr, propName);
            }
        }
        for (auto& [unionName, unionTy] : unionTypes) {
            if (baseTy == unionTy) {
                auto& unionInfo = userTypes[unionName];

                for (auto& member : unionInfo.members) {
                    std::string resolvedVariant = resolveTypeName(member.type);
                    if (classTypes.find(resolvedVariant) != classTypes.end()) {
                        int fieldIdx = getFlattenedFieldIndex(resolvedVariant, propName);
                        if (fieldIdx != -1) {
                            llvm::Value* varAlloc = nullptr;
                            if (auto varAcc = *std::get_if<VarAccessNode*>(&*(*propAccess)->base)) {
                                varAlloc = getVarAddress(varAcc->var_name_tok.value);
                            }
                            if (!varAlloc) return nullptr;

                            llvm::Value* dataFieldPtr = builder->CreateStructGEP(unionTy, varAlloc, 1, "union_data_ptr");
                            llvm::Value* dataPtr = builder->CreateLoad(llvm::PointerType::get(context, 0), dataFieldPtr, "union_data");

                            llvm::StructType* classTy = classTypes[resolvedVariant];
                            llvm::Value* castedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));

                            llvm::Type* fieldTy = classTy->getElementType(fieldIdx);
                            llvm::Value* fieldPtr = builder->CreateStructGEP(classTy, castedPtr, fieldIdx);
                            return builder->CreateLoad(fieldTy, fieldPtr, propName);
                        }
                    }
                    if (structTypes.find(resolvedVariant) != structTypes.end()) {
                        auto& structInfo = userTypes[resolvedVariant];
                        int fieldIdx = -1;
                        for (size_t i = 0; i < structInfo.fields.size(); i++) {
                            if (structInfo.fields[i].name == propName) {
                                fieldIdx = i;
                                break;
                            }
                        }
                        if (fieldIdx != -1) {
                            llvm::Value* varAlloc = nullptr;
                            if (auto varAcc = safe_get<VarAccessNode>(*(*propAccess)->base)) { varAlloc = getVarAddress(varAcc->var_name_tok.value); }
                            if (!varAlloc) return nullptr;

                            llvm::Value* dataFieldPtr = builder->CreateStructGEP(unionTy, varAlloc, 1, "union_data_ptr");
                            llvm::Value* dataPtr = builder->CreateLoad(llvm::PointerType::get(context, 0), dataFieldPtr, "union_data");

                            llvm::StructType* structTy = structTypes[resolvedVariant];
                            llvm::Value* castedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));

                            llvm::Type* fieldTy = structTy->getElementType(fieldIdx);
                            llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, castedPtr, fieldIdx);
                            return builder->CreateLoad(fieldTy, fieldPtr, propName);
                        }
                    }
                }

                cg_error((*propAccess)->property_name.pos, "No variant of union '" + unionName + "' has field '" + propName + "'");
                return nullptr;
            }
        }
        cg_error((*propAccess)->property_name.pos, "Unknown property: " + propName);
        return nullptr;
    } else if (auto methodCall = std::get_if<MethodCallNode*>(&node)) {
        auto* call = methodCall;
        std::string methodName = (*call)->method_name.value;
        llvm::Value* thisPtr = nullptr;
        std::string targetClass = "";
        if (auto varAccess = std::get_if<VarAccessNode*>(&(*call)->base)) {
            std::string varName = (*varAccess)->var_name_tok.value;
            if (varName == "this") {
                thisPtr = currentThis;
                targetClass = currentClassName;
            } else {
                thisPtr = getVarAddress(varName);
                llvm::Type* pTy = getPointeeType(varName);
                if (pTy) {
                    auto* st = llvm::dyn_cast<llvm::StructType>(pTy);
                    std::string typeName = st ? st->getName().str() : "";
                    auto unionIt = unionTypes.find(typeName);
                    if (unionIt != unionTypes.end()) {
                        llvm::Function* F = builder->GetInsertBlock()->getParent();
                        llvm::BasicBlock* defaultBB = llvm::BasicBlock::Create(context, "union.bad", F);
                        llvm::BasicBlock* joinBB = llvm::BasicBlock::Create(context, "union.join", F);
                        llvm::Value* tagPtr = builder->CreateStructGEP(unionIt->second, thisPtr, 0);
                        llvm::Value* tagVal = builder->CreateLoad(builder->getInt32Ty(), tagPtr);
                        llvm::SwitchInst* sw = builder->CreateSwitch(tagVal, defaultBB);
                        llvm::Value* unionPtr = thisPtr;
                        builder->SetInsertPoint(defaultBB);
                        builder->CreateUnreachable();
                        builder->SetInsertPoint(joinBB);
                        llvm::Value* result = nullptr;
                        int idx = 0;
                        for (auto& m : userTypes[typeName].members) {
                            std::string ty = resolveTypeName(m.type);
                            if (!classTypes.count(ty)) {
                                idx++;
                                continue;
                            }
                            llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "union.case", F);
                            sw->addCase(builder->getInt32(idx), caseBB);
                            builder->SetInsertPoint(caseBB);
                            llvm::Value* payloadPtr = builder->CreateStructGEP(unionIt->second, unionPtr, 1);
                            llvm::Value* payload = builder->CreateLoad(builder->getPtrTy(), payloadPtr);
                            ClassMethodInfo* info = nullptr;
                            for (auto& m2 : userTypes[ty].classMethods) {
                                if (m2.name_tok.value == methodName && m2.params.size() == (*call)->args.size()) {
                                    info = &m2;
                                    break;
                                }
                            }
                            if (!info) {
                                cg_error((*call)->method_name.pos, "No overload found");
                                return nullptr;
                            }
                            auto args = prepareArgs(info, (*call)->args);
                            llvm::Function* resolvedMethod = findMethodOverload(ty, methodName, args);
                            if (!resolvedMethod) {
                                cg_error((*call)->method_name.pos, "No overload found");
                                return nullptr;
                            }
                            llvm::Value* callResult = emitMethodCall(resolvedMethod, payload, args, methodName);
                            result = callResult;
                            builder->CreateBr(joinBB);
                            idx++;
                        }
                        builder->SetInsertPoint(joinBB);
                        return result;
                    } else if (st) {
                        targetClass = typeName;
                    }
                }
            }
        } else if (auto propAcc = safe_get<PropertyAccessNode>((*call)->base)) {
            llvm::Value* baseAddr = emitExpr(*(propAcc->base));
            std::string ownerClass = getExpressionType(*(propAcc->base));
            llvm::Type* baseTy = baseAddr->getType();
            if (auto* st = llvm::dyn_cast<llvm::StructType>(baseTy)) {
                std::string unionName = st->getName().str();
                auto unionIt = unionTypes.find(unionName);
                if (unionIt != unionTypes.end()) {
                    llvm::Function* F = builder->GetInsertBlock()->getParent();
                    llvm::BasicBlock* defaultBB = llvm::BasicBlock::Create(context, "union.bad", F);
                    llvm::BasicBlock* joinBB = llvm::BasicBlock::Create(context, "union.join", F);
                    llvm::Value* tagPtr = builder->CreateStructGEP(unionIt->second, baseAddr, 0);
                    llvm::Value* tagVal = builder->CreateLoad(builder->getInt32Ty(), tagPtr);
                    llvm::SwitchInst* sw = builder->CreateSwitch(tagVal, defaultBB);
                    llvm::Value* unionPtr = baseAddr;
                    builder->SetInsertPoint(defaultBB);
                    builder->CreateUnreachable();
                    builder->SetInsertPoint(joinBB);
                    llvm::Value* result = nullptr;
                    int idx = 0;
                    for (auto& m : userTypes[unionName].members) {
                        std::string ty = resolveTypeName(m.type);
                        if (!classTypes.count(ty)) {
                            idx++;
                            continue;
                        }
                        llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "union.case", F);
                        sw->addCase(builder->getInt32(idx), caseBB);
                        builder->SetInsertPoint(caseBB);
                        llvm::Value* payloadPtr = builder->CreateStructGEP(unionIt->second, unionPtr, 1);
                        llvm::Value* payload = builder->CreateLoad(builder->getPtrTy(), payloadPtr);
                        ClassMethodInfo* info = nullptr;
                        for (auto& m2 : userTypes[ty].classMethods) {
                            if (m2.name_tok.value == methodName && m2.params.size() == (*call)->args.size()) {
                                info = &m2;
                                break;
                            }
                        }
                        if (!info) {
                            cg_error((*call)->method_name.pos, "No overload found");
                            return nullptr;
                        }
                        auto args = prepareArgs(info, (*call)->args);
                        llvm::Function* resolvedMethod = findMethodOverload(ty, methodName, args);
                        if (!resolvedMethod) {
                            cg_error((*call)->method_name.pos, "No overload found");
                            return nullptr;
                        }
                        llvm::Value* callResult = emitMethodCall(resolvedMethod, payload, args, methodName);
                        result = callResult;
                        builder->CreateBr(joinBB);
                        idx++;
                    }
                    builder->SetInsertPoint(joinBB);
                    return result;
                } else if (st) {
                    targetClass = unionName;
                }
            }
            llvm::StructType* structType = llvm::StructType::getTypeByName(context, ownerClass);
            unsigned fieldIndex = 0;
            bool found = false;
            const auto& fields = userTypes[ownerClass].classFields;
            for (size_t i = 0; i < fields.size(); ++i) {
                if (fields[i].name == propAcc->property_name.value) {
                    fieldIndex = (unsigned)i;
                    found = true;
                    break;
                }
            }
            if (!found) { return (cg_error((*call)->method_name.pos, "Field not found"), nullptr); }
            llvm::Value* fieldAddr = builder->CreateStructGEP(structType, baseAddr, fieldIndex);
            thisPtr = builder->CreateLoad(builder->getPtrTy(), fieldAddr, "ptr_ld");
            AnyNode temp = AnyNode(propAcc);
            targetClass = getExpressionType(temp);
        } else {
            llvm::Value* baseVal = emitExpr((*call)->base);
            llvm::Type* baseTy = baseVal->getType();
            if (auto* st = llvm::dyn_cast<llvm::StructType>(baseTy)) {
                std::string unionName = st->getName().str();
                auto unionIt = unionTypes.find(unionName);
                if (unionIt != unionTypes.end()) {
                    llvm::Function* F = builder->GetInsertBlock()->getParent();
                    llvm::BasicBlock* defaultBB = llvm::BasicBlock::Create(context, "union.bad", F);
                    llvm::BasicBlock* joinBB = llvm::BasicBlock::Create(context, "union.join", F);
                    llvm::Value* tagPtr = builder->CreateStructGEP(unionIt->second, baseVal, 0);
                    llvm::Value* tagVal = builder->CreateLoad(builder->getInt32Ty(), tagPtr);
                    llvm::SwitchInst* sw = builder->CreateSwitch(tagVal, defaultBB);
                    builder->SetInsertPoint(defaultBB);
                    builder->CreateUnreachable();
                    builder->SetInsertPoint(joinBB);
                    llvm::Value* result = nullptr;
                    int idx = 0;
                    for (auto& m : userTypes[unionName].members) {
                        std::string ty = resolveTypeName(m.type);
                        if (!classTypes.count(ty)) {
                            idx++;
                            continue;
                        }
                        llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "union.case", F);
                        sw->addCase(builder->getInt32(idx), caseBB);
                        builder->SetInsertPoint(caseBB);
                        llvm::Value* payloadPtr = builder->CreateStructGEP(unionIt->second, baseVal, 1);
                        llvm::Value* payload = builder->CreateLoad(builder->getPtrTy(), payloadPtr);
                        ClassMethodInfo* info = nullptr;
                        for (auto& m2 : userTypes[ty].classMethods) {
                            if (m2.name_tok.value == methodName && m2.params.size() == (*call)->args.size()) {
                                info = &m2;
                                break;
                            }
                        }
                        if (!info) {
                            cg_error((*call)->method_name.pos, "No overload found");
                            return nullptr;
                        }
                        auto args = prepareArgs(info, (*call)->args);
                        llvm::Function* resolvedMethod = findMethodOverload(ty, methodName, args);
                        if (!resolvedMethod) {
                            cg_error((*call)->method_name.pos, "No overload found");
                            return nullptr;
                        }
                        llvm::Value* callResult = emitMethodCall(resolvedMethod, payload, args, methodName);
                        result = callResult;
                        builder->CreateBr(joinBB);
                        idx++;
                    }
                    builder->SetInsertPoint(joinBB);
                    return result;
                }
            }
            if (auto* sTy = llvm::dyn_cast<llvm::StructType>(baseVal->getType())) {
                targetClass = sTy->getName().str();
                thisPtr = createEntryAlloca("temp_this", sTy);
                builder->CreateStore(baseVal, thisPtr);
            }
        }
        if (targetClass == "" || targetClass.starts_with("list") || targetClass.starts_with("map")) {
            llvm::Value* baseVal = thisPtr;
            if (methodName == "push") {
                if ((*methodCall)->args.empty()) {
                    cg_error((*methodCall)->method_name.pos, "push() requires 1 argument");
                    return nullptr;
                }

                llvm::Value* argVal = emitExpr((*methodCall)->args[0]);
                if (!argVal) return nullptr;

                int typeCode = -1;
                llvm::Type* argTy = argVal->getType();

                if (argTy->isIntegerTy(32) || argTy->isIntegerTy(64) || argTy->isIntegerTy(16))
                    typeCode = 0;
                else if (argTy->isFloatTy())
                    typeCode = 1;
                else if (argTy->isDoubleTy())
                    typeCode = 2;
                else if (argTy->isIntegerTy(8))
                    typeCode = 3;
                else if (argTy->isIntegerTy(1))
                    typeCode = 4;
                else if (argTy->isIntegerTy(2))
                    typeCode = 5;
                else
                    typeCode = 6;

                llvm::Function* pushFn = module->getFunction("qc_list_push");
                if (!pushFn) {
                    llvm::FunctionType* ty = llvm::FunctionType::get(
                        builder->getVoidTy(), {llvm::PointerType::get(context, 0), llvm::PointerType::get(context, 0), builder->getInt32Ty()}, false);
                    pushFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_list_push", module);
                }
                llvm::AllocaInst* argAlloc = createEntryAlloca("push_arg", argVal->getType());
                builder->CreateStore(argVal, argAlloc);
                llvm::Value* argPtr = builder->CreateBitCast(argAlloc, builder->getPtrTy());
                llvm::Value* actualListPtr = baseVal;
                if (llvm::isa<llvm::AllocaInst>(baseVal)) { actualListPtr = builder->CreateLoad(builder->getPtrTy(), baseVal, "loaded_list_ptr"); }
                builder->CreateCall(pushFn, {actualListPtr, argPtr, builder->getInt32(typeCode)});
                return nullptr;
            }

            if (methodName == "pop") {
                llvm::Function* popFn = module->getFunction("qc_list_pop");
                if (!popFn) {
                    llvm::FunctionType* ty = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {llvm::PointerType::get(context, 0)}, false);
                    popFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_list_pop", module);
                }
                return builder->CreateCall(popFn, {baseVal}, "list_pop");
            }

            if (methodName == "set") {
                if ((*methodCall)->args.size() != 2) {
                    cg_error((*methodCall)->method_name.pos, "set() requires 2 arguments");
                    return nullptr;
                }
                llvm::Value* keyVal = emitExpr((*methodCall)->args[0]);
                llvm::Value* valueVal = emitExpr((*methodCall)->args[1]);
                if (!keyVal || !valueVal) return nullptr;

                llvm::Value* keyPtr = nullptr;
                if (keyVal->getType()->isPointerTy()) {
                    keyPtr = keyVal;
                } else {
                    llvm::AllocaInst* keyAlloc = createEntryAlloca("set_key", keyVal->getType());
                    builder->CreateStore(keyVal, keyAlloc);
                    keyPtr = builder->CreateBitCast(keyAlloc, llvm::PointerType::get(context, 0));
                }
                llvm::Value* valPtr = nullptr;
                if (valueVal->getType()->isPointerTy()) {
                    valPtr = valueVal;
                } else {
                    llvm::AllocaInst* valAlloc = createEntryAlloca("set_val", valueVal->getType());
                    builder->CreateStore(valueVal, valAlloc);
                    valPtr = builder->CreateBitCast(valAlloc, llvm::PointerType::get(context, 0));
                }
                llvm::Function* setFn = module->getFunction("qc_map_set");
                if (!setFn) {
                    llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getVoidTy(), {voidPtrTy, voidPtrTy, voidPtrTy}, false);
                    setFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_map_set", module);
                }
                builder->CreateCall(setFn, {baseVal, keyPtr, valPtr});
                return llvm::ConstantInt::get(builder->getInt32Ty(), 0);
            }
            if (methodName == "has") {
                if ((*methodCall)->args.size() != 1) {
                    cg_error((*methodCall)->method_name.pos, "has() requires 1 argument");
                    return nullptr;
                }

                llvm::Value* keyVal = emitExpr((*methodCall)->args[0]);
                if (!keyVal) return nullptr;

                llvm::Value* keyPtr;
                if (keyVal->getType()->isPointerTy()) {
                    keyPtr = keyVal;
                } else {
                    llvm::AllocaInst* keyAlloc = createEntryAlloca("has_key", keyVal->getType());
                    builder->CreateStore(keyVal, keyAlloc);
                    keyPtr = builder->CreateBitCast(keyAlloc, llvm::PointerType::get(context, 0));
                }

                llvm::Function* hasFn = module->getFunction("qc_map_has");
                if (!hasFn) {
                    llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getInt1Ty(), {voidPtrTy, voidPtrTy}, false);
                    hasFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_map_has", module);
                }

                return builder->CreateCall(hasFn, {baseVal, keyPtr}, "map_has");
            }

            if (methodName == "remove") {
                if ((*methodCall)->args.size() != 1) {
                    cg_error((*methodCall)->method_name.pos, "remove() requires 1 argument");
                    return nullptr;
                }

                llvm::Value* keyVal = emitExpr((*methodCall)->args[0]);
                if (!keyVal) return nullptr;

                llvm::Value* keyPtr;
                if (keyVal->getType()->isPointerTy()) {
                    keyPtr = keyVal;
                } else {
                    llvm::AllocaInst* keyAlloc = createEntryAlloca("remove_key", keyVal->getType());
                    builder->CreateStore(keyVal, keyAlloc);
                    keyPtr = builder->CreateBitCast(keyAlloc, llvm::PointerType::get(context, 0));
                }

                llvm::Function* removeFn = module->getFunction("qc_map_remove");
                if (!removeFn) {
                    llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getVoidTy(), {voidPtrTy, voidPtrTy}, false);
                    removeFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_map_remove", module);
                }

                builder->CreateCall(removeFn, {baseVal, keyPtr});
                return llvm::ConstantInt::get(builder->getInt32Ty(), 0);
            }
            if (methodName == "keys") {
                llvm::Function* keysFn = module->getFunction("qc_map_keys");
                if (!keysFn) {
                    llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(voidPtrTy, {voidPtrTy}, false);
                    keysFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_map_keys", module);
                }

                return builder->CreateCall(keysFn, {baseVal}, "map_keys");
            }
        }
        if (targetClass.empty()) return (cg_error((*call)->method_name.pos, "Cannot resolve target"), nullptr);
        if (llvm::Value* specializedCall = tryHandleSpecialized(targetClass, methodName, *call, thisPtr)) { return specializedCall; }
        ClassMethodInfo* info = nullptr;
        std::string searchClass = targetClass;
        while (!searchClass.empty() && !info) {
            for (auto& m : userTypes[searchClass].classMethods) {
                bool isVar = !m.params.empty() && m.params.back().type.value == "...";
                if (m.name_tok.value == methodName) {
                    if (isVar && (*call)->args.size() >= m.params.size() - 1) {
                        info = &m;
                        break;
                    } else if (m.params.size() == (*call)->args.size()) {
                        info = &m;
                        break;
                    }
                }
            }
            searchClass = userTypes[searchClass].baseClassName;
        }

        auto args = prepareArgs(info, (*call)->args);
        llvm::StructType* VariadicStructTy = llvm::StructType::get(context, {builder->getPtrTy(), builder->getInt32Ty(), builder->getInt32Ty()});
        bool isVariadic = (info && !info->params.empty() && info->params.back().type.value == "...");
        if (isVariadic) {
            size_t numFixedParams = info->params.size() - 1;
            std::vector<llvm::Value*> varVals;
            if (args.size() > numFixedParams) {
                varVals.assign(args.begin() + numFixedParams, args.end());
                args.resize(numFixedParams);
            }
            llvm::Value* args_cnt = builder->getInt32(varVals.size());
            llvm::Value* items_array = builder->CreateAlloca(builder->getPtrTy(), args_cnt, "var_array");
            for (size_t i = 0; i < varVals.size(); ++i) {
                llvm::Value* element_ptr = builder->CreateGEP(builder->getPtrTy(), items_array, builder->getInt32(i));
                llvm::Value* val = varVals[i];
                if (val->getType()->isStructTy()) {
                    llvm::Value* tempAlloc = builder->CreateAlloca(val->getType(), nullptr, "var_struct_tmp");
                    builder->CreateStore(val, tempAlloc);
                    val = tempAlloc;
                } else if (val->getType()->isIntegerTy()) {
                    val = builder->CreateIntToPtr(val, builder->getPtrTy());
                } else if (val->getType()->isFloatingPointTy()) {
                    llvm::Value* asInt = builder->CreateBitCast(val, builder->getInt64Ty());
                    val = builder->CreateIntToPtr(asInt, builder->getPtrTy());
                }
                builder->CreateStore(val, element_ptr);
            }
            llvm::Value* varStructAlloc = builder->CreateAlloca(VariadicStructTy, nullptr, "var_struct_alloc");
            llvm::Value* ptrField = builder->CreateStructGEP(VariadicStructTy, varStructAlloc, 0);
            builder->CreateStore(items_array, ptrField);
            llvm::Value* lenField = builder->CreateStructGEP(VariadicStructTy, varStructAlloc, 1);
            builder->CreateStore(args_cnt, lenField);
            llvm::Value* capField = builder->CreateStructGEP(VariadicStructTy, varStructAlloc, 2);
            builder->CreateStore(builder->getInt32(0), capField);
            args.push_back(varStructAlloc);
        }
        llvm::Function* method = findMethodOverload(targetClass, methodName, args);
        if (!method) return (cg_error((*call)->method_name.pos, "No overload found"), nullptr);
        return emitMethodCall(method, thisPtr, args, methodName);
    } else if (auto spread = std::get_if<SpreadNode*>(&node)) {
        cg_error(Position(), "Spread operator can only be used in array/list "
                             "literals or function calls");
        return nullptr;
    } else if (auto fieldAssign = std::get_if<FieldAssignNode*>(&node)) {
        std::string fieldName = (*fieldAssign)->field_name.value;
        std::string targetTypeStr = "";
        if (auto varAccess = std::get_if<VarAccessNode*>(&(*fieldAssign)->base)) {
            if ((*varAccess)->var_name_tok.value == "this" && !currentClassName.empty()) {
                targetTypeStr = getFieldType(currentClassName, fieldName);
            }
        }
        llvm::Value* valueVal = nullptr;
        if (auto arrLit = std::get_if<ArrayLiteralNode*>(&(*fieldAssign)->value)) {
            if ((*arrLit)->elements.empty() && targetTypeStr.find("list<") == 0) {
                std::string inner = getElementType(targetTypeStr);
                int typeCode = getTypeCode(inner);
                llvm::Function* createListFn = module->getFunction("qc_create_list");
                if (!createListFn) {
                    llvm::FunctionType* ft = llvm::FunctionType::get(builder->getPtrTy(), {builder->getInt32Ty()}, false);
                    createListFn = llvm::Function::Create(ft, llvm::Function::InternalLinkage, "qc_create_list", module);
                }
                valueVal = builder->CreateCall(createListFn, {builder->getInt32(typeCode)});
            }
        }
        if (!valueVal) { valueVal = emitExpr((*fieldAssign)->value); }
        if (!valueVal) return nullptr;
        if (auto varAccess = std::get_if<VarAccessNode*>(&(*fieldAssign)->base)) {
            if ((*varAccess)->var_name_tok.value == "this" && currentThis && !currentClassName.empty()) {
                int fieldIdx = getFlattenedFieldIndex(currentClassName, fieldName);

                if (fieldIdx == -1) {
                    cg_error(Position(), "Field not found: " + fieldName);
                    return nullptr;
                }

                auto [fieldOwnerClass, fieldAccess] = getFieldOwner(currentClassName, fieldName);
                if (!canAccessField(currentClassName, fieldOwnerClass, fieldAccess)) {
                    cg_error(Position(), "Cannot access " + fieldAccess + " field");
                    return nullptr;
                }

                llvm::StructType* classTy = classTypes[currentClassName];
                llvm::Value* fieldPtr = builder->CreateStructGEP(classTy, currentThis, fieldIdx);
                builder->CreateStore(valueVal, fieldPtr);
                return builder->getInt32(0);
            }
        }
        PropertyAccessNode tempProp((*fieldAssign)->base, Token(), (*fieldAssign)->field_name);
        llvm::Value* fieldPtr = emitPropertyAddress(tempProp);
        AnyNode tempVariant = new PropertyAccessNode(tempProp);
        std::string fieldTypeStr = getExpressionType(tempVariant, true);
        if (auto propPtr = std::get_if<PropertyAccessNode*>(&tempVariant)) { (*fieldAssign)->base = *(*propPtr)->base; }
        if (!fieldPtr) return nullptr;
        llvm::Type* destTy = llvmTypeFor(fieldTypeStr);
        llvm::Value* rhsVal = emitExpr((*fieldAssign)->value);
        if (!rhsVal) return nullptr;
        builder->CreateStore(rhsVal, fieldPtr);
        return rhsVal;
    } else if (auto ref = std::get_if<RefVarDeclNode>(&node)) {
        /*Token type_tok;
        Token var_name_tok;
        Token target_tok;
        Position pos;*/
        std::string fullName = (getCurrentNamespace().empty() ? "" : getCurrentNamespace() + "::") + ref->var_name_tok.value;
        varTypes[fullName] = ref->type_tok.value + "&";
        if (resolveGlobal(ref->target_tok.value) != nullptr) {
            cg_error(ref->target_tok.pos, ref->target_tok.value + " is a global. You cannot create references to globals "
                                                                  "because it is wasted memory and unnecessary indirection; "
                                                                  "globals already have global lifetime.");
            return nullptr;
        } else if (getVarAddress(ref->target_tok.value) != nullptr) {
            llvm::Value* destPtr = getVarAddress(ref->target_tok.value);
            std::string varT = resolveVarType(ref->target_tok.value);
            if (varT.ends_with("&")) {
                cg_error(ref->target_tok.pos, ref->target_tok.value + " is a reference, and you cannot "
                                                                      "create references-to-references");
            }
            llvm::AllocaInst* refStore = builder->CreateAlloca(builder->getPtrTy(), nullptr, fullName);
            builder->CreateStore(destPtr, refStore);
            locals[fullName] = refStore;
        } else {
            cg_error(ref->target_tok.pos, ref->target_tok.value + " is not defined when creating reference " + ref->var_name_tok.value);
            return nullptr;
        }
        return nullptr;
    } else if (auto ref = std::get_if<NullptrNode>(&node)) {
        return llvm::ConstantPointerNull::get(llvm::PointerType::get(context, 0));
    }
    return nullptr;
}
llvm::Value* LLVMCompiler::storeAndGetPointer(llvm::Value* val) {
    llvm::Type* ty = val->getType();

    if (ty->isPointerTy()) { return builder->CreateBitCast(val, llvm::PointerType::get(context, 0)); }

    llvm::Function* mallocFn = module->getFunction("malloc");
    if (!mallocFn) {
        llvm::FunctionType* mallocTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {builder->getInt64Ty()}, false);
        mallocFn = llvm::Function::Create(mallocTy, llvm::Function::InternalLinkage, "malloc", module);
    }

    const llvm::DataLayout& DL = module->getDataLayout();
    uint64_t size = DL.getTypeAllocSize(ty);

    llvm::Value* heapPtr = builder->CreateCall(mallocFn, {builder->getInt64(size)}, "union_heap");
    llvm::Value* typedPtr = builder->CreateBitCast(heapPtr, llvm::PointerType::get(context, 0));
    builder->CreateStore(val, typedPtr);

    return heapPtr;
}
int LLVMCompiler::findUnionVariantTag(const std::string& unionName, AnyNode& valueNode, llvm::Value* val) {
    auto typeIt = userTypes.find(unionName);
    if (typeIt == userTypes.end()) return -1;

    auto& members = typeIt->second.members;

    for (size_t i = 0; i < members.size(); i++) {
        auto& member = members[i];

        const std::string& m = member.type;
        size_t colonPos = m.find(':');

        if (colonPos != std::string::npos) {
            std::string kind = m.substr(0, colonPos);
            std::string valueStr = m.substr(colonPos + 1);

            if (kind == "int") {
                if (auto numNode = std::get_if<NumberNode>(&valueNode)) {
                    if (numNode->tok.value == valueStr) { return i; }
                }
            } else if (kind == "string") {
                if (auto strNode = std::get_if<StringNode>(&valueNode)) {
                    std::string lit = "\"" + strNode->tok.value + "\"";
                    if (lit == valueStr) { return i; }
                }
            } else if (kind == "char") {
                if (auto charNode = std::get_if<CharNode>(&valueNode)) {
                    std::string lit = "'" + charNode->tok.value + "'";
                    if (lit == valueStr) { return i; }
                }
            } else if (kind == "bool") {
                if (auto boolNode = std::get_if<BoolNode>(&valueNode)) {
                    if (boolNode->tok.value == valueStr) { return i; }
                }
            } else if (kind == "qbool") {
                if (auto qBoolNode = std::get_if<QBoolNode>(&valueNode)) {
                    if (qBoolNode->tok.value == valueStr) { return i; }
                }
            }
        } else {
            llvm::Type* valTy = val->getType();
            llvm::Type* memberTy = llvmTypeFor(m);

            if (valTy == memberTy) { return i; }
        }
    }

    return -1;
}
llvm::Value* LLVMCompiler::callStringConcat(llvm::Value* a, llvm::Value* b) {
    llvm::Function* concatFn = module->getFunction("qc_string_concat");
    if (!concatFn) {
        llvm::FunctionType* ty = llvm::FunctionType::get(llvm::PointerType::get(context, 0),
                                                         {llvm::PointerType::get(context, 0), llvm::PointerType::get(context, 0)}, false);
        concatFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_string_concat", module);
    }
    return builder->CreateCall(concatFn, {a, b});
}
void LLVMCompiler::generateStructReprFunctions() {
    llvm::BasicBlock* savedBB = builder->GetInsertBlock();

    for (auto& [name, info] : userTypes) {
        if (info.kind != UserTypeKind::Struct) continue;

        llvm::StructType* structTy = structTypes[name];
        llvm::FunctionType* reprFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {structTy}, false);

        llvm::Function* reprFn = llvm::Function::Create(reprFnTy, llvm::Function::InternalLinkage, name + "_repr", module);
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

            if (field.type == "int") {
                llvm::Function* toStrFn = module->getFunction("qc_to_string_int");
                fieldStr = builder->CreateCall(toStrFn, {fieldVal});
            } else if (field.type == "float") {
                llvm::Function* toStrFn = module->getFunction("qc_to_string_float");
                fieldStr = builder->CreateCall(toStrFn, {fieldVal});
            } else if (field.type == "double") {
                llvm::Function* toStrFn = module->getFunction("qc_to_string_double");
                fieldStr = builder->CreateCall(toStrFn, {fieldVal});
            } else if (field.type == "bool") {
                llvm::Function* toStrFn = module->getFunction("qc_to_string_bool");
                fieldStr = builder->CreateCall(toStrFn, {fieldVal});
            } else if (field.type == "char") {
                llvm::Function* toStrFn = module->getFunction("qc_to_string_char");
                fieldStr = builder->CreateCall(toStrFn, {fieldVal});
            } else if (field.type == "string") {
                fieldStr = fieldVal;
            } else if (structTypes.find(field.type) != structTypes.end()) {
                llvm::Function* nestedReprFn = module->getFunction(field.type + "_repr");
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
    }
    if (savedBB) { builder->SetInsertPoint(savedBB); }
}
llvm::Value* LLVMCompiler::convertToString(llvm::Value* val, AnyNode& expr) {
    llvm::Type* ty = val->getType();

    if (ty->isPointerTy()) {
        if (auto varAccess = std::get_if<VarAccessNode*>(&expr)) {
            std::string varName = (*varAccess)->var_name_tok.value;
            if (varName == "this") {
                if (currentThis) {
                    return currentThis;
                } else {
                    cg_error((*varAccess)->var_name_tok.pos, "'this' used outside of class method");
                    return nullptr;
                }
            }
            if (hasList(varName)) {
                llvm::Function* fn = module->getFunction("qc_list_to_string");
                if (!fn) {
                    llvm::FunctionType* ty = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {llvm::PointerType::get(context, 0)}, false);
                    fn = llvm::Function::Create(ty, llvm::Function::InternalLinkage, "qc_list_to_string", module);
                }
                return builder->CreateCall(fn, {val}, "list_str");
            }
            if (hasMap(varName)) {
                llvm::Function* fn = module->getFunction("qc_map_to_string");
                if (!fn) {
                    llvm::FunctionType* ty = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {llvm::PointerType::get(context, 0)}, false);
                    fn = llvm::Function::Create(ty, llvm::Function::InternalLinkage, "qc_map_to_string", module);
                }
                return builder->CreateCall(fn, {val}, "map_str");
            }
            if (hasJaggedArray(varName)) {
                llvm::Function* fn = module->getFunction("qc_jagged_to_string");
                if (!fn) {
                    llvm::FunctionType* ty = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {llvm::PointerType::get(context, 0)}, false);
                    fn = llvm::Function::Create(ty, llvm::Function::InternalLinkage, "qc_jagged_to_string", module);
                }
                return builder->CreateCall(fn, {val}, "jagged_str");
            }
        }
        return val;
    }
    std::string fnName;
    if (ty->isIntegerTy(32))
        fnName = "qc_to_string_int";
    else if (ty->isFloatTy())
        fnName = "qc_to_string_float";
    else if (ty->isDoubleTy())
        fnName = "qc_to_string_double";
    else if (ty->isIntegerTy(1))
        fnName = "qc_to_string_bool";
    else if (ty->isIntegerTy(2))
        fnName = "qc_to_string_qbool";
    else if (ty->isIntegerTy(8))
        fnName = "qc_to_string_char";
    else {
        cg_error(Position(), "Cannot convert type to string");
        return nullptr;
    }

    llvm::Function* fn = module->getFunction(fnName);
    if (!fn) {
        llvm::FunctionType* fty = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {val->getType()}, false);
        fn = llvm::Function::Create(fty, llvm::Function::ExternalLinkage, fnName, module);
    }

    return builder->CreateCall(fn, {val}, "to_str");
}
void LLVMCompiler::expandSpreadIntoVector(llvm::Value* collVal, AnyNode& collExpr, std::vector<llvm::Value*>& elements) {
    llvm::Value* lengthVal = getCollectionLength(collVal, collExpr);
    if (!lengthVal) return;

    if (auto* constLen = llvm::dyn_cast<llvm::ConstantInt>(lengthVal)) {
        int length = constLen->getSExtValue();

        bool isList = false;
        int elemTypeCode = 0;

        if (auto varAccess = std::get_if<VarAccessNode*>(&collExpr)) {
            std::string collName = (*varAccess)->var_name_tok.value;
            if (hasList(collName)) {
                auto listIt = findList(collName);
                isList = true;
                elemTypeCode = listIt->second;
            } else {
                if (hasArrayType(collName)) {
                    auto typeIt = findArrayType(collName);
                    elemTypeCode = getTypeCode(typeIt->second);
                }
            }
        }

        for (int i = 0; i < length; i++) {
            llvm::Value* elemVal;

            if (isList) {
                llvm::Function* getFn = module->getFunction("qc_list_get");
                if (!getFn) {
                    llvm::FunctionType* ty = llvm::FunctionType::get(llvm::PointerType::get(context, 0),
                                                                     {llvm::PointerType::get(context, 0), builder->getInt32Ty()}, false);
                    getFn = llvm::Function::Create(ty, llvm::Function::InternalLinkage, "qc_list_get", module);
                }
                llvm::Value* elemPtr = builder->CreateCall(getFn, {collVal, builder->getInt32(i)});

                llvm::Type* elemTy = getTypeFromCode(elemTypeCode);
                llvm::Value* typedPtr = builder->CreateBitCast(elemPtr, llvm::PointerType::get(context, 0));
                elemVal = builder->CreateLoad(elemTy, typedPtr);
            } else {
                llvm::Type* elemTy = getTypeFromCode(elemTypeCode);
                llvm::Value* gepPtr = builder->CreateGEP(elemTy, collVal, builder->getInt32(i));
                elemVal = builder->CreateLoad(elemTy, gepPtr);
            }

            elements.push_back(elemVal);
        }
    } else {
        cg_error(Position(), "Cannot spread runtime-sized collection into array literal");
    }
}
void LLVMCompiler::expandSpreadIntoList(llvm::Value* collVal, AnyNode& collExpr, llvm::Value* listPtr, llvm::Function* pushFn, int elemTypeCode) {
    llvm::Value* lengthVal = getCollectionLength(collVal, collExpr);
    if (!lengthVal) return;

    bool isList = false;
    llvm::Value* actualCollVal = collVal;

    if (auto varAccess = std::get_if<VarAccessNode*>(&collExpr)) {
        std::string collName = (*varAccess)->var_name_tok.value;
        if (hasList(collName)) {
            isList = true;
        } else {
            auto locAlloc = getVarAddress(collName);
            if (locAlloc) {
                llvm::Type* allocTy = getPointeeType(collName);
                if (allocTy->isPointerTy()) {
                    actualCollVal = builder->CreateLoad(allocTy, locAlloc, "arr_ptr");
                } else if (allocTy->isArrayTy()) {
                    std::vector<llvm::Value*> indices = {builder->getInt32(0), builder->getInt32(0)};
                    actualCollVal = builder->CreateInBoundsGEP(allocTy, locAlloc, indices, "arr_ptr");
                }
            }
        }
    }

    llvm::BasicBlock* loopBB = llvm::BasicBlock::Create(context, "spread_push_loop", currentFunction);
    llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(context, "spread_push_body", currentFunction);
    llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "spread_push_end", currentFunction);

    llvm::AllocaInst* iAlloc = createEntryAlloca("spread_push_i", builder->getInt32Ty());
    builder->CreateStore(builder->getInt32(0), iAlloc);
    builder->CreateBr(loopBB);

    builder->SetInsertPoint(loopBB);
    llvm::Value* iVal = builder->CreateLoad(builder->getInt32Ty(), iAlloc);
    llvm::Value* cond = builder->CreateICmpSLT(iVal, lengthVal);
    builder->CreateCondBr(cond, bodyBB, endBB);

    builder->SetInsertPoint(bodyBB);

    llvm::Value* elemPtr;
    if (isList) {
        llvm::Function* getFn = module->getFunction("qc_list_get");
        if (!getFn) {
            llvm::FunctionType* ty = llvm::FunctionType::get(llvm::PointerType::get(context, 0),
                                                             {llvm::PointerType::get(context, 0), builder->getInt32Ty()}, false);
            getFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_list_get", module);
        }
        elemPtr = builder->CreateCall(getFn, {collVal, iVal});
    } else {
        llvm::Type* elemTy = getTypeFromCode(elemTypeCode);
        llvm::Value* gepPtr = builder->CreateGEP(elemTy, actualCollVal, iVal);
        elemPtr = builder->CreateBitCast(gepPtr, llvm::PointerType::get(context, 0));
    }

    builder->CreateCall(pushFn, {listPtr, elemPtr, builder->getInt32(elemTypeCode)});

    llvm::Value* nextI = builder->CreateAdd(iVal, builder->getInt32(1));
    builder->CreateStore(nextI, iAlloc);
    builder->CreateBr(loopBB);
    builder->SetInsertPoint(endBB);
}
llvm::Value* LLVMCompiler::expandSpreadIntoArrays(llvm::Value* collVal, AnyNode& collExpr, llvm::AllocaInst* argsArray, llvm::AllocaInst* typesArray,
                                                  llvm::Value* startIndex) {
    llvm::Value* lengthVal = getCollectionLength(collVal, collExpr);
    if (!lengthVal) return startIndex;

    bool isList = false;
    int elemTypeCode = 0;

    if (auto varAccess = std::get_if<VarAccessNode*>(&collExpr)) {
        std::string collName = (*varAccess)->var_name_tok.value;
        if (hasList(collName)) {
            isList = true;
            auto listIt = findList(collName);
            elemTypeCode = listIt->second;
        } else {
            if (hasArrayType(collName)) {
                auto typeIt = findArrayType(collName);
                elemTypeCode = getTypeCode(typeIt->second);
            }
        }
    }

    llvm::BasicBlock* loopBB = llvm::BasicBlock::Create(context, "expand_loop", currentFunction);
    llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(context, "expand_body", currentFunction);
    llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "expand_end", currentFunction);

    llvm::AllocaInst* iAlloc = createEntryAlloca("expand_i", builder->getInt32Ty());
    llvm::AllocaInst* currentIdxAlloc = createEntryAlloca("expand_idx", builder->getInt32Ty());

    builder->CreateStore(builder->getInt32(0), iAlloc);
    builder->CreateStore(startIndex, currentIdxAlloc);
    builder->CreateBr(loopBB);

    builder->SetInsertPoint(loopBB);
    llvm::Value* iVal = builder->CreateLoad(builder->getInt32Ty(), iAlloc);
    llvm::Value* cond = builder->CreateICmpSLT(iVal, lengthVal);
    builder->CreateCondBr(cond, bodyBB, endBB);

    builder->SetInsertPoint(bodyBB);
    llvm::Value* currentIdx = builder->CreateLoad(builder->getInt32Ty(), currentIdxAlloc);

    llvm::Value* elemPtr;

    if (isList) {
        llvm::Function* getFn = module->getFunction("qc_list_get");
        if (!getFn) {
            llvm::FunctionType* ty = llvm::FunctionType::get(llvm::PointerType::get(context, 0),
                                                             {llvm::PointerType::get(context, 0), builder->getInt32Ty()}, false);
            getFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_list_get", module);
        }
        elemPtr = builder->CreateCall(getFn, {collVal, iVal}, "list_elem");
    } else {
        llvm::Type* elemTy = getTypeFromCode(elemTypeCode);
        llvm::Value* arrayPtr = collVal;
        if (auto varAccess = std::get_if<VarAccessNode*>(&collExpr)) {
            std::string collName = (*varAccess)->var_name_tok.value;
            llvm::Value* locAlloc = getVarAddress(collName);
            if (locAlloc) {
                llvm::Type* allocTy = getPointeeType(collName);
                if (allocTy->isPointerTy()) { arrayPtr = builder->CreateLoad(allocTy, locAlloc, "arr_ptr"); }
            }
        }

        llvm::Value* gepPtr = builder->CreateGEP(elemTy, arrayPtr, iVal, "arr_elem_ptr");
        elemPtr = builder->CreateBitCast(gepPtr, llvm::PointerType::get(context, 0));
    }

    llvm::Value* argSlot = builder->CreateGEP(llvm::PointerType::get(context, 0), argsArray, currentIdx);
    builder->CreateStore(elemPtr, argSlot);

    llvm::Value* typeSlot = builder->CreateGEP(builder->getInt32Ty(), typesArray, currentIdx);
    builder->CreateStore(builder->getInt32(elemTypeCode), typeSlot);

    llvm::Value* nextI = builder->CreateAdd(iVal, builder->getInt32(1));
    builder->CreateStore(nextI, iAlloc);
    llvm::Value* nextIdx = builder->CreateAdd(currentIdx, builder->getInt32(1));
    builder->CreateStore(nextIdx, currentIdxAlloc);
    builder->CreateBr(loopBB);

    builder->SetInsertPoint(endBB);
    llvm::Value* finalIdx = builder->CreateLoad(builder->getInt32Ty(), currentIdxAlloc);
    return finalIdx;
}
llvm::Value* LLVMCompiler::getCollectionLength(llvm::Value* collVal, AnyNode& collExpr) {
    if (auto varAccess = std::get_if<VarAccessNode*>(&collExpr)) {
        std::string collName = (*varAccess)->var_name_tok.value;
        if (hasList(collName)) {
            auto listIt = findList(collName);
            llvm::Function* lenFn = module->getFunction("qc_list_length");
            if (!lenFn) {
                llvm::FunctionType* ty = llvm::FunctionType::get(builder->getInt32Ty(), {llvm::PointerType::get(context, 0)}, false);
                lenFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_list_length", module);
            }
            return builder->CreateCall(lenFn, {collVal}, "list_len");
        }
        if (hasArrayLength(collName)) {
            auto arrLenIt = findArrayLength(collName);
            return builder->getInt32(arrLenIt->second);
        }
        llvm::Value* locAlloc = getVarAddress(collName);
        if (locAlloc) {
            llvm::Type* allocTy = getPointeeType(collName);

            if (allocTy && allocTy->isArrayTy()) { return builder->getInt32(allocTy->getArrayNumElements()); }
            if (allocTy && allocTy->isPointerTy()) {
                llvm::Function* lenFn = module->getFunction("qc_list_length");
                if (!lenFn) {
                    llvm::FunctionType* ty = llvm::FunctionType::get(builder->getInt32Ty(), {llvm::PointerType::get(context, 0)}, false);
                    lenFn = llvm::Function::Create(ty, llvm::Function::InternalLinkage, "qc_list_length", module);
                }
                return builder->CreateCall(lenFn, {collVal}, "list_len");
            }
        }
    }

    if (auto arrLit = std::get_if<ArrayLiteralNode*>(&collExpr)) { return builder->getInt32((*arrLit)->elements.size()); }
    cg_error(Position(), "Cannot determine collection length for spread");
    return nullptr;
}
llvm::Value* LLVMCompiler::copySpreadToArray(llvm::Value* collVal, AnyNode& collExpr, llvm::Value* destArray, llvm::Value* startIndex,
                                             llvm::Type* elemTy, int elemTypeCode) {
    llvm::Value* lengthVal = getCollectionLength(collVal, collExpr);
    if (!lengthVal) return startIndex;
    bool isList = false;
    bool isJagged = false;
    if (auto varAccess = std::get_if<VarAccessNode*>(&collExpr)) {
        std::string rawName = (*varAccess)->var_name_tok.value;
        std::string resolvedName = resolveMetadataName(rawName);
        if (hasList(resolvedName)) {
            isList = true;
        } else if (hasJaggedArray(resolvedName)) {
            isJagged = true;
        }
    }

    llvm::BasicBlock* loopBB = llvm::BasicBlock::Create(context, "copy_loop", currentFunction);
    llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(context, "copy_body", currentFunction);
    llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "copy_end", currentFunction);

    llvm::AllocaInst* iAlloc = createEntryAlloca("copy_i", builder->getInt32Ty());
    llvm::AllocaInst* destIdxAlloc = createEntryAlloca("copy_dest_idx", builder->getInt32Ty());
    builder->CreateStore(builder->getInt32(0), iAlloc);
    builder->CreateStore(startIndex, destIdxAlloc);
    builder->CreateBr(loopBB);
    builder->SetInsertPoint(loopBB);
    llvm::Value* iVal = builder->CreateLoad(builder->getInt32Ty(), iAlloc);
    llvm::Value* cond = builder->CreateICmpSLT(iVal, lengthVal);
    builder->CreateCondBr(cond, bodyBB, endBB);
    builder->SetInsertPoint(bodyBB);
    llvm::Value* destIdx = builder->CreateLoad(builder->getInt32Ty(), destIdxAlloc);
    llvm::Value* elemVal;
    if (isList) {
        llvm::Function* getFn = module->getFunction("qc_list_get");
        if (!getFn) {
            llvm::FunctionType* ty = llvm::FunctionType::get(llvm::PointerType::get(context, 0),
                                                             {llvm::PointerType::get(context, 0), builder->getInt32Ty()}, false);
            getFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_list_get", module);
        }
        llvm::Value* elemPtr = builder->CreateCall(getFn, {collVal, iVal});
        if (elemTypeCode == 6) {
            elemVal = elemPtr;
        } else {
            llvm::Value* typedPtr = builder->CreateBitCast(elemPtr, llvm::PointerType::get(context, 0));
            elemVal = builder->CreateLoad(elemTy, typedPtr);
        }
    } else {
        llvm::Value* srcPtr = builder->CreateGEP(elemTy, collVal, iVal);
        elemVal = builder->CreateLoad(elemTy, srcPtr);
    }
    llvm::Value* destPtr = builder->CreateGEP(elemTy, destArray, destIdx);
    builder->CreateStore(elemVal, destPtr);

    llvm::Value* nextI = builder->CreateAdd(iVal, builder->getInt32(1));
    builder->CreateStore(nextI, iAlloc);

    llvm::Value* nextDestIdx = builder->CreateAdd(destIdx, builder->getInt32(1));
    builder->CreateStore(nextDestIdx, destIdxAlloc);

    builder->CreateBr(loopBB);
    builder->SetInsertPoint(endBB);
    llvm::Value* finalDestIdx = builder->CreateLoad(builder->getInt32Ty(), destIdxAlloc);
    return finalDestIdx;
}
llvm::Value* LLVMCompiler::createRuntimeSizedArray(std::vector<AnyNode>& elements, llvm::Value* totalSize) {
    llvm::Type* elemTy = nullptr;
    int elemTypeCode = 0;
    for (auto& elem : elements) {
        if (auto spread = std::get_if<SpreadNode*>(&elem)) {
            if (auto varAccess = std::get_if<VarAccessNode*>(&(*spread)->expr)) {
                std::string collName = resolveTypeName((*varAccess)->var_name_tok.value);
                if (hasList(collName)) {
                    auto listIt = findList(collName);

                    if (listIt != listsStack.back().end()) {
                        elemTypeCode = listIt->second;
                        elemTy = getTypeFromCode(elemTypeCode);
                        break;
                    }
                }
                if (hasArrayType(collName)) {
                    auto typeIt = findArrayType(collName);
                    elemTypeCode = getTypeCode(typeIt->second);
                    elemTy = getTypeFromCode(elemTypeCode);
                    break;
                }
            }
        } else {
            llvm::Value* v = emitExpr(elem);
            if (v) {
                elemTy = v->getType();
                elemTypeCode = getTypeCodeFromLLVM(elemTy);
                break;
            }
        }
    }

    if (!elemTy) {
        cg_error(Position(), "Cannot determine element type for runtime array");
        return nullptr;
    }
    llvm::Function* mallocFn = module->getFunction("malloc");
    if (!mallocFn) {
        llvm::FunctionType* mallocTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {builder->getInt64Ty()}, false);
        mallocFn = llvm::Function::Create(mallocTy, llvm::Function::InternalLinkage, "malloc", module);
    }

    const llvm::DataLayout& DL = module->getDataLayout();
    uint64_t elemSize = DL.getTypeAllocSize(elemTy);
    llvm::Value* totalSizeExt = builder->CreateZExt(totalSize, builder->getInt64Ty());
    llvm::Value* sizeBytes = builder->CreateMul(totalSizeExt, builder->getInt64(elemSize));

    llvm::Value* mallocCall = builder->CreateCall(mallocFn, {sizeBytes}, "runtime_arr");
    llvm::Value* arrPtr = builder->CreateBitCast(mallocCall, llvm::PointerType::get(context, 0));

    llvm::Value* currentIndex = builder->getInt32(0);

    for (auto& elem : elements) {
        if (auto spread = std::get_if<SpreadNode*>(&elem)) {
            llvm::Value* collVal = emitExpr((*spread)->expr);
            currentIndex = copySpreadToArray(collVal, (*spread)->expr, arrPtr, currentIndex, elemTy, elemTypeCode);
        } else {
            llvm::Value* elemVal = emitExpr(elem);
            if (!elemVal) continue;

            llvm::Value* elemPtr = builder->CreateGEP(elemTy, arrPtr, currentIndex);
            builder->CreateStore(elemVal, elemPtr);

            currentIndex = builder->CreateAdd(currentIndex, builder->getInt32(1));
        }
    }
    return arrPtr;
}
llvm::AllocaInst* LLVMCompiler::createEntryAlloca(const std::string& name, llvm::Type* ty) {
    if (!currentFunction) {
        llvm::Constant* initVal = llvm::Constant::getNullValue(ty);

        llvm::GlobalVariable* gv = new llvm::GlobalVariable(*module, ty, false, llvm::GlobalValue::InternalLinkage, initVal, name);
        return reinterpret_cast<llvm::AllocaInst*>(gv);
    }
    llvm::IRBuilder<> tmp(&currentFunction->getEntryBlock(), currentFunction->getEntryBlock().begin());
    return tmp.CreateAlloca(ty, nullptr, name);
}
llvm::Function* LLVMCompiler::emitFuncDef(const FuncDefNode& fn) {
    std::string name;
    if (fn.name_tok) {
        name = fn.name_tok->value;
        if (!namespaceStack.empty()) { name = getCurrentNamespace() + "::" + name; }
    } else {
        name = lambdaName();
    }
    llvm::FunctionType* fTy = llvmFuncTypeFor(fn.return_types, fn.params);
    auto* existing = module->getFunction(name);
    if (existing) return existing;
    functionSignatures[name] = {fTy, {}};
    llvm::GlobalValue::LinkageTypes linkage = fn.is_extern || fn.is_foreign ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;

    auto* func = llvm::Function::Create(fTy, linkage, name, module);

    if (fn.is_foreign) return func;
    enterScope();
    auto savedLambdaTypes = lambdaTypes;
    llvm::BasicBlock* savedInsertBlock = builder->GetInsertBlock();
    auto* entryBB = llvm::BasicBlock::Create(context, "entry", func);
    builder->SetInsertPoint(entryBB);

    auto* oldFunction = currentFunction;
    auto oldLocals = locals;

    currentFunction = func;
    unsigned idx = 0;
    for (auto& arg : func->args()) {
        auto& param = *std::next(fn.params.begin(), idx);
        arg.setName(param.name.value);

        auto* alloca = createEntryAlloca(arg.getName().str(), arg.getType());
        builder->CreateStore(&arg, alloca);
        locals[param.name.value] = alloca;
        if (param.signature.has_value()) {
            varTypes[param.name.value] = "fn";
            lambdaTypes[param.name.value] = llvmFuncTypeFor(param.signature->return_types, param.signature->params);
        } else {
            std::string t = param.type.value;
            if (t.find("list<") == 0) {
                std::string inner = getElementType(t);
                int code = getTypeCode(inner);
                lists[param.name.value] = code;
                varTypes[param.name.value] = param.type.value;
            } else if (t.find("map<") == 0) {
                auto [key, val] = splitMapTypes(t);
                maps[param.name.value] = std::make_pair(getTypeCode(key), getTypeCode(val));
                varTypes[param.name.value] = param.type.value;
            } else if (t.find("[]") != std::string::npos) {
                int dims = 0;
                size_t pos = t.find("[]");
                while (pos != std::string::npos) {
                    dims++;
                    pos = t.find("[]", pos + 2);
                }
                if (dims > 1) {
                    std::string base = t.substr(0, t.find("[]"));
                    int baseTypeCode = getTypeCode(base);
                    jaggedArrays[param.name.value] = {baseTypeCode, dims};
                    arrayTypeStrings[param.name.value] = base;
                    varTypes[param.name.value] = param.type.value;
                } else {
                    std::string base = t.substr(0, t.find("[]"));
                    arrayTypeStrings[param.name.value] = base;
                    varTypes[param.name.value] = param.type.value;
                }
            } else {
                varTypes[param.name.value] = t;
            }
        }
        idx++;
    }

    for (auto& stmt : fn.body->statements) { emitStmt(stmt); }

    if (!builder->GetInsertBlock()->getTerminator()) {
        if (fn.is_multi_return()) {
            llvm::Type* retTy = fTy->getReturnType();
            builder->CreateRet(llvm::UndefValue::get(retTy));
        } else {
            llvm::Type* retTy = fTy->getReturnType();
            if (retTy->isVoidTy()) {
                builder->CreateRetVoid();
            } else if (retTy->isIntegerTy()) {
                builder->CreateRet(llvm::ConstantInt::get(retTy, 0));
            } else if (retTy->isFloatingPointTy()) {
                builder->CreateRet(llvm::ConstantFP::get(retTy, 0.0));
            } else {
                builder->CreateRet(llvm::UndefValue::get(retTy));
            }
        }
    }

    if (savedInsertBlock) { builder->SetInsertPoint(savedInsertBlock); }

    currentFunction = oldFunction;
    locals = oldLocals;
    functions[name] = func;
    lambdaTypes = savedLambdaTypes;
    exitScope();
    return func;
}
std::string LLVMCompiler::mangleName(const FuncDefNode& fn) {
    std::string base = fn.name_tok ? fn.name_tok->value : "lambda";
    if (!fn.namespace_path.empty()) { base = fn.namespace_path + "::" + base; }
    return base;
}
std::string LLVMCompiler::lambdaName() {
    static int counter = 0;
    return "__lambda_" + std::to_string(counter++);
}
void LLVMCompiler::emitStmt(AnyNode& node) {
    if (std::holds_alternative<VarAssignNode*>(node) || std::holds_alternative<AssignExprNode*>(node) || std::holds_alternative<BinOpNode*>(node) ||
        std::holds_alternative<NumberNode>(node) || std::holds_alternative<VarAccessNode*>(node) || std::holds_alternative<BoolNode>(node) ||
        std::holds_alternative<CharNode>(node) || std::holds_alternative<StringNode>(node) || std::holds_alternative<QBoolNode>(node) ||
        std::holds_alternative<UnaryOpNode*>(node) || std::holds_alternative<CallNode*>(node) || std::holds_alternative<FuncDefNode*>(node) ||
        std::holds_alternative<ArrayAccessNode*>(node) || std::holds_alternative<PropertyAccessNode*>(node) ||
        std::holds_alternative<MethodCallNode*>(node) || std::holds_alternative<SpreadNode*>(node) ||
        std::holds_alternative<FieldAssignNode*>(node) || std::holds_alternative<RefVarDeclNode>(node)) {
        emitExpr(node);
    } else if (auto mret = safe_get<MultiReturnNode>(node)) {
        llvm::Type* retTy = currentFunction->getReturnType();

        if (!retTy->isStructTy()) {
            cg_error(mret->pos, "Multi-return in non-multi-return function");
            return;
        }

        llvm::Value* agg = llvm::UndefValue::get(retTy);
        llvm::StructType* retStructTy = llvm::cast<llvm::StructType>(retTy);
        for (size_t i = 0; i < mret->values.size(); ++i) {
            llvm::Value* val = nullptr;
            if (auto varAccess = std::get_if<VarAccessNode*>(&mret->values[i])) {
                std::string name = (*varAccess)->var_name_tok.value;
                llvm::Value* alloc = getVarAddress(name);
                if (alloc) {
                    llvm::Type* allocatedTy = getPointeeType(name);
                    if (allocatedTy->isArrayTy()) { val = builder->CreateBitCast(alloc, llvm::PointerType::get(context, 0), "array_ret_ptr"); }
                }
            }
            if (auto call = std::get_if<CallNode*>(&mret->values[i])) {
                if (auto varAccess = std::get_if<VarAccessNode*>(&(*call)->node_to_call)) {
                    std::string funcName = (*varAccess)->var_name_tok.value;

                    if (classTypes.find(funcName) != classTypes.end()) {
                        llvm::StructType* classTy = classTypes[funcName];

                        std::vector<llvm::Value*> ctorArgs;
                        for (auto& argNode : (*call)->arg_nodes) {
                            llvm::Value* arg = emitExpr(argNode);
                            if (!arg) return;
                            ctorArgs.push_back(arg);
                        }

                        llvm::Function* ctor = findMethodOverload(funcName, funcName, ctorArgs);

                        if (ctor) {
                            llvm::AllocaInst* retVal = createEntryAlloca("mret_val_" + std::to_string(i), classTy);

                            std::vector<llvm::Value*> allArgs = {retVal};
                            allArgs.insert(allArgs.end(), ctorArgs.begin(), ctorArgs.end());
                            builder->CreateCall(ctor, allArgs);

                            val = builder->CreateLoad(classTy, retVal);
                        }
                    }
                }
            }
            if (auto arrayLit = std::get_if<ArrayLiteralNode*>(&mret->values[i])) {
                val = emitExpr(mret->values[i]);
                if (!val) return;

                llvm::Type* srcTy = val->getType();
                llvm::Type* destTy = retStructTy->getElementType(i);
                if (destTy->isPointerTy() && srcTy->isArrayTy()) {
                    llvm::ArrayType* arrayType = llvm::cast<llvm::ArrayType>(srcTy);
                    llvm::Type* i64Ty = builder->getInt64Ty();
                    llvm::Value* size = llvm::ConstantInt::get(i64Ty, module->getDataLayout().getTypeAllocSize(arrayType));

                    llvm::Function* mallocFn = module->getFunction("malloc");
                    if (!mallocFn) {
                        llvm::FunctionType* mallocTy = llvm::FunctionType::get(builder->getPtrTy(), {i64Ty}, false);
                        mallocFn = llvm::Function::Create(mallocTy, llvm::Function::InternalLinkage, "malloc", module);
                    }

                    llvm::Value* heapPtr = builder->CreateCall(mallocFn, {size});
                    llvm::Value* typedPtr = builder->CreateBitCast(heapPtr, llvm::PointerType::get(context, 0));

                    builder->CreateStore(val, typedPtr);

                    val = builder->CreateBitCast(typedPtr, destTy);
                }
            }
            if (!val) { val = emitExpr(mret->values[i]); }
            if (!val) return;
            llvm::Type* srcTy = val->getType();
            llvm::Type* destTy = retStructTy->getElementType(i);
            for (auto& [unionName, unionTy] : unionTypes) {
                if (srcTy == unionTy && !isUnionType(destTy)) {
                    llvm::Value* dataPtr = builder->CreateExtractValue(val, 1, "union_data");
                    if (destTy->isPointerTy()) {
                        val = builder->CreateBitCast(dataPtr, destTy);
                    } else {
                        llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                        val = builder->CreateLoad(destTy, typedPtr);
                    }
                    srcTy = destTy;
                    break;
                }
                if (!isUnionType(srcTy) && destTy == unionTy) {
                    int tag = findUnionVariantTag(unionName, mret->values[i], val);
                    if (tag == -1) {
                        cg_error(mret->pos, "Return value doesn't match union variant");
                        return;
                    }

                    llvm::Value* unionVal = llvm::UndefValue::get(unionTy);
                    unionVal = builder->CreateInsertValue(unionVal, builder->getInt32(tag), 0);
                    llvm::Value* dataPtr = storeAndGetPointer(val);
                    val = builder->CreateInsertValue(unionVal, dataPtr, 1);

                    srcTy = destTy;
                    break;
                }
            }
            for (auto& [enumName, enumTy] : enumTypes) {
                if (srcTy == enumTy && !isEnumType(destTy)) {
                    llvm::Value* dataPtr = builder->CreateExtractValue(val, 1, "enum_data");
                    if (destTy->isPointerTy()) {
                        val = builder->CreateBitCast(dataPtr, destTy);
                    } else {
                        llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                        val = builder->CreateLoad(destTy, typedPtr);
                    }
                    srcTy = destTy;
                    break;
                }
                if (!isEnumType(srcTy) && destTy == enumTy) {
                    int tag = findEnumVariantTag(enumName, mret->values[i], val);
                    if (tag == -1) {
                        cg_error(mret->pos, "Return value doesn't match enum variant");
                        return;
                    }

                    llvm::Value* enumVal = llvm::UndefValue::get(enumTy);
                    enumVal = builder->CreateInsertValue(enumVal, builder->getInt32(tag), 0);
                    llvm::Value* dataPtr = storeAndGetPointer(val);
                    enumVal = builder->CreateInsertValue(enumVal, dataPtr, 1);

                    val = enumVal;
                    srcTy = destTy;
                    break;
                }
            }
            agg = builder->CreateInsertValue(agg, val, i);
        }

        builder->CreateRet(agg);
        return;
    } else if (auto ret = std::get_if<ReturnNode*>(&node)) {
        if (auto varAccess = std::get_if<VarAccessNode*>(&(*ret)->value)) {
            std::string name = (*varAccess)->var_name_tok.value;
            llvm::Value* alloc = getVarAddress(name);
            if (alloc) {
                llvm::Type* allocatedTy = getPointeeType(name);
                if (allocatedTy && allocatedTy->isArrayTy()) {
                    llvm::Value* arrayPtr = builder->CreateBitCast(alloc, llvm::PointerType::get(context, 0), "array_ret_ptr");
                    builder->CreateRet(arrayPtr);
                    return;
                }
            }
        }
        if (auto call = std::get_if<CallNode*>(&(*ret)->value)) {
            if (auto varAccess = std::get_if<VarAccessNode*>(&(*call)->node_to_call)) {
                std::string funcName = (*varAccess)->var_name_tok.value;

                if (classTypes.find(funcName) != classTypes.end()) {
                    llvm::StructType* classTy = classTypes[funcName];
                    std::vector<llvm::Value*> ctorArgs;
                    for (auto& argNode : (*call)->arg_nodes) {
                        llvm::Value* arg = emitExpr(argNode);
                        if (!arg) return;
                        ctorArgs.push_back(arg);
                    }

                    std::string ctorName = funcName;
                    llvm::Function* ctor = findMethodOverload(funcName, ctorName, ctorArgs);

                    if (ctor) {
                        llvm::AllocaInst* retVal = createEntryAlloca("ret_val", classTy);

                        std::vector<llvm::Value*> allArgs = {retVal};
                        allArgs.insert(allArgs.end(), ctorArgs.begin(), ctorArgs.end());
                        builder->CreateCall(ctor, allArgs);

                        llvm::Value* result = llvm::UndefValue::get(classTy);
                        for (unsigned i = 0; i < classTy->getNumElements(); i++) {
                            std::vector<llvm::Value*> indices = {builder->getInt32(0), builder->getInt32(i)};
                            llvm::Value* fieldPtr = builder->CreateInBoundsGEP(classTy, retVal, indices);
                            llvm::Type* fieldTy = classTy->getElementType(i);
                            llvm::Value* fieldVal = builder->CreateLoad(fieldTy, fieldPtr);

                            result = builder->CreateInsertValue(result, fieldVal, i);
                        }

                        builder->CreateRet(result);
                        return;
                    }
                }
            }
        }
        llvm::Value* v = emitExpr((*ret)->value);
        if (!v) {
            if (currentFunction->getReturnType()->isVoidTy()) {
                builder->CreateRetVoid();
            } else {
                cg_error((*ret)->pos, "Return without value in non-void function");
            }
            return;
        }
        llvm::Type* srcTy = v->getType();
        llvm::Type* destTy = currentFunction->getReturnType();
        if (auto arrayLit = std::get_if<ArrayLiteralNode*>(&(*ret)->value)) {
            if (destTy->isPointerTy() && srcTy->isArrayTy()) {
                llvm::ArrayType* arrayType = llvm::cast<llvm::ArrayType>(srcTy);
                llvm::Type* i64Ty = builder->getInt64Ty();
                llvm::Value* size = llvm::ConstantInt::get(i64Ty, module->getDataLayout().getTypeAllocSize(arrayType));
                llvm::Function* mallocFn = module->getFunction("malloc");
                if (!mallocFn) {
                    llvm::FunctionType* mallocTy = llvm::FunctionType::get(builder->getPtrTy(), {i64Ty}, false);
                    mallocFn = llvm::Function::Create(mallocTy, llvm::Function::InternalLinkage, "malloc", module);
                }

                llvm::Value* heapPtr = builder->CreateCall(mallocFn, {size});
                llvm::Value* typedPtr = builder->CreateBitCast(heapPtr, llvm::PointerType::get(context, 0));
                builder->CreateStore(v, typedPtr);
                llvm::Value* retPtr = builder->CreateBitCast(typedPtr, destTy);

                builder->CreateRet(retPtr);
                return;
            }
        }
        for (auto& [unionName, unionTy] : unionTypes) {
            if (srcTy == unionTy && !isUnionType(destTy)) {
                llvm::Value* dataPtr = builder->CreateExtractValue(v, 1, "union_data");
                if (destTy->isPointerTy()) {
                    v = builder->CreateBitCast(dataPtr, destTy);
                } else {
                    llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                    v = builder->CreateLoad(destTy, typedPtr);
                }
                srcTy = destTy;
                break;
            }
            if (!isUnionType(srcTy) && destTy == unionTy) {
                int tag = findUnionVariantTag(unionName, (*ret)->value, v);
                if (tag == -1) {
                    cg_error((*ret)->pos, "Return value doesn't match union variant");
                    return;
                }

                llvm::Value* unionVal = llvm::UndefValue::get(unionTy);
                unionVal = builder->CreateInsertValue(unionVal, builder->getInt32(tag), 0);
                llvm::Value* dataPtr = storeAndGetPointer(v);
                unionVal = builder->CreateInsertValue(unionVal, dataPtr, 1);

                builder->CreateRet(unionVal);
                return;
            }
        }
        for (auto& [enumName, enumTy] : enumTypes) {
            if (srcTy == enumTy && !isEnumType(destTy)) {
                llvm::Value* dataPtr = builder->CreateExtractValue(v, 1, "enum_data");
                if (destTy->isPointerTy()) {
                    v = builder->CreateBitCast(dataPtr, destTy);
                } else {
                    llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                    v = builder->CreateLoad(destTy, typedPtr);
                }
                srcTy = destTy;
                break;
            }
            if (!isEnumType(srcTy) && destTy == enumTy) {
                int tag = findEnumVariantTag(enumName, (*ret)->value, v);
                if (tag == -1) {
                    cg_error((*ret)->pos, "Return value doesn't match enum variant");
                    return;
                }

                llvm::Value* enumVal = llvm::UndefValue::get(enumTy);
                enumVal = builder->CreateInsertValue(enumVal, builder->getInt32(tag), 0);
                llvm::Value* dataPtr = storeAndGetPointer(v);
                enumVal = builder->CreateInsertValue(enumVal, dataPtr, 1);

                builder->CreateRet(enumVal);
                return;
            }
        }

        builder->CreateRet(v);
        return;
    } else if (auto mv = safe_get<MultiVarDeclNode>(node)) {
        llvm::Value* callVal = emitExpr(mv->value);
        if (!callVal) {
            cg_error(mv->var_names[0].pos, "Failed to compile multi-var initializer");
            return;
        }

        llvm::Type* retTy = callVal->getType();
        if (!retTy->isStructTy() || retTy->getStructNumElements() != mv->var_names.size()) {
            cg_error(mv->var_names[0].pos, "Multi-return arity/type mismatch");
            return;
        }

        for (size_t i = 0; i < mv->var_names.size(); ++i) {
            llvm::Value* field = builder->CreateExtractValue(callVal, i);
            std::string name = mv->var_names[i].value;
            std::string typeStr = mv->type_toks[i].value;
            if (typeStr.find("[]") != std::string::npos) {
                std::string baseType = typeStr;
                while (baseType.ends_with("[]")) { baseType = baseType.substr(0, baseType.length() - 2); }
                arrayTypeStrings[name] = baseType;
            }
            llvm::Type* srcTy = field->getType();
            llvm::Type* destTy = llvmTypeFor(typeStr);
            for (auto& [unionName, unionTy] : unionTypes) {
                if (srcTy == unionTy && !isUnionType(destTy)) {
                    llvm::Value* dataPtr = builder->CreateExtractValue(field, 1, "union_data");
                    if (destTy->isPointerTy()) {
                        field = builder->CreateBitCast(dataPtr, destTy);
                    } else {
                        llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                        field = builder->CreateLoad(destTy, typedPtr);
                    }
                    srcTy = destTy;
                    break;
                }
            }
            for (auto& [enumName, enumTy] : enumTypes) {
                if (srcTy == enumTy && !isEnumType(destTy)) {
                    llvm::Value* dataPtr = builder->CreateExtractValue(field, 1, "enum_data");
                    if (destTy->isPointerTy()) {
                        field = builder->CreateBitCast(dataPtr, destTy);
                    } else {
                        llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                        field = builder->CreateLoad(destTy, typedPtr);
                    }
                    srcTy = destTy;
                    break;
                }
            }
            llvm::AllocaInst* alloc = createEntryAlloca(name, destTy);
            builder->CreateStore(field, alloc);
            std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[fullName] = alloc;
        }

        return;
    } else if (auto if_node = safe_get<IfNode>(node)) {
        enterScope();
        if (if_node->init.has_value()) { emitStmt(if_node->init.value()); }
        llvm::Value* cond = emitExpr(if_node->condition);
        if (!cond) return;
        for (auto& [enumName, enumTy] : enumTypes) {
            if (cond->getType() == enumTy) {
                llvm::Value* dataPtr = builder->CreateExtractValue(cond, 1);

                llvm::Type* targetTy = builder->getInt1Ty();

                llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                cond = builder->CreateLoad(targetTy, typedPtr);
                break;
            }
        }
        cond = normalizeValue(cond, if_node->condition);
        cond = toTruthiness(cond, Position("", "", 0, 0, 0));
        if (!cond) return;
        llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(context, "then", currentFunction);
        llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(context, "ifcont", currentFunction);
        std::vector<std::pair<llvm::BasicBlock*, llvm::BasicBlock*>> elifBlocks;
        for (size_t i = 0; i < if_node->elif_branches.size(); i++) {
            llvm::BasicBlock* elifCondBB = llvm::BasicBlock::Create(context, "elif.cond", currentFunction);
            llvm::BasicBlock* elifBodyBB = llvm::BasicBlock::Create(context, "elif.body", currentFunction);
            elifBlocks.push_back({elifCondBB, elifBodyBB});
        }

        llvm::BasicBlock* elseBB = nullptr;
        if (if_node->else_branch) { elseBB = llvm::BasicBlock::Create(context, "else", currentFunction); }
        llvm::BasicBlock* nextBB = elifBlocks.empty() ? (elseBB ? elseBB : mergeBB) : elifBlocks[0].first;
        builder->CreateCondBr(cond, thenBB, nextBB);
        builder->SetInsertPoint(thenBB);
        for (auto& stmt : if_node->then_branch->statements) { emitStmt(stmt); }
        if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(mergeBB); }
        for (size_t i = 0; i < elifBlocks.size(); i++) {
            builder->SetInsertPoint(elifBlocks[i].first);
            llvm::Value* elifCond = emitExpr(if_node->elif_branches[i].first);

            llvm::BasicBlock* nextElifBB = (i + 1 < elifBlocks.size()) ? elifBlocks[i + 1].first : (elseBB ? elseBB : mergeBB);
            builder->CreateCondBr(elifCond, elifBlocks[i].second, nextElifBB);

            builder->SetInsertPoint(elifBlocks[i].second);
            for (auto& stmt : if_node->elif_branches[i].second->statements) { emitStmt(stmt); }
            if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(mergeBB); }
        }
        if (elseBB) {
            builder->SetInsertPoint(elseBB);
            for (auto& stmt : if_node->else_branch->statements) { emitStmt(stmt); }
            if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(mergeBB); }
        }
        exitScope();
        builder->SetInsertPoint(mergeBB);
    } else if (auto while_node = safe_get<WhileNode>(node)) {
        enterScope();
        llvm::BasicBlock* condBB = llvm::BasicBlock::Create(context, "while.cond", currentFunction);
        llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(context, "while.body", currentFunction);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "while.end", currentFunction);
        llvm::BasicBlock* oldBreakBB = currentBreakBB;
        llvm::BasicBlock* oldContinueBB = currentContinueBB;
        currentBreakBB = endBB;
        currentContinueBB = condBB;
        builder->CreateBr(condBB);
        builder->SetInsertPoint(condBB);
        llvm::Value* cond = emitExpr(while_node->condition);
        if (!cond) return;
        for (auto& [enumName, enumTy] : enumTypes) {
            if (cond->getType() == enumTy) {
                llvm::Value* dataPtr = builder->CreateExtractValue(cond, 1);
                llvm::Type* targetTy = builder->getInt1Ty();

                llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                cond = builder->CreateLoad(targetTy, typedPtr);
                break;
            }
        }
        cond = normalizeValue(cond, while_node->condition);
        cond = toTruthiness(cond, Position("", "", 0, 0, 0));
        if (!cond) return;
        builder->CreateCondBr(cond, bodyBB, endBB);
        builder->SetInsertPoint(bodyBB);
        for (auto& stmt : while_node->body->statements) { emitStmt(stmt); }
        if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(condBB); }
        currentBreakBB = oldBreakBB;
        currentContinueBB = oldContinueBB;
        exitScope();
        builder->SetInsertPoint(endBB);
    } else if (std::holds_alternative<BreakNode*>(node)) {
        if (currentBreakBB) {
            builder->CreateBr(currentBreakBB);
        } else {
            cg_error(Position(), "break outside of loop/switch");
        }
    } else if (std::holds_alternative<ContinueNode*>(node)) {
        if (currentContinueBB) {
            builder->CreateBr(currentContinueBB);
        } else {
            cg_error(Position(), "continue outside of loop");
        }
    } else if (auto for_node = safe_get<ForNode>(node)) {
        enterScope();
        if (for_node->init.has_value()) { emitStmt(for_node->init.value()); }
        llvm::BasicBlock* condBB = llvm::BasicBlock::Create(context, "for.cond", currentFunction);
        llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(context, "for.body", currentFunction);
        llvm::BasicBlock* incBB = llvm::BasicBlock::Create(context, "for.inc", currentFunction);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "for.end", currentFunction);
        llvm::BasicBlock* oldBreakBB = currentBreakBB;
        llvm::BasicBlock* oldContinueBB = currentContinueBB;
        currentBreakBB = endBB;
        currentContinueBB = incBB;
        builder->CreateBr(condBB);
        builder->SetInsertPoint(condBB);
        llvm::Value* cond = emitExpr(for_node->condition);
        if (!cond) return;
        for (auto& [enumName, enumTy] : enumTypes) {
            if (cond->getType() == enumTy) {
                llvm::Value* dataPtr = builder->CreateExtractValue(cond, 1);
                llvm::Type* targetTy = builder->getInt1Ty();

                llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                cond = builder->CreateLoad(targetTy, typedPtr);
                break;
            }
        }
        cond = normalizeValue(cond, for_node->condition);
        cond = toTruthiness(cond, Position("", "", 0, 0, 0));
        if (!cond) return;
        builder->CreateCondBr(cond, bodyBB, endBB);
        builder->SetInsertPoint(bodyBB);
        for (auto& stmt : for_node->body->statements) { emitStmt(stmt); }
        if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(incBB); }
        builder->SetInsertPoint(incBB);
        if (for_node->update.has_value()) { emitStmt(for_node->update.value()); }
        builder->CreateBr(condBB);
        currentBreakBB = oldBreakBB;
        currentContinueBB = oldContinueBB;
        exitScope();
        builder->SetInsertPoint(endBB);
    } else if (auto switch_node = safe_get<SwitchNode>(node)) {
        enterScope();
        llvm::Value* switchVal = emitExpr(switch_node->value);
        if (!switchVal) return;

        llvm::Type* switchTy = switchVal->getType();

        bool canUseSwitch = switchTy->isIntegerTy();

        for (auto& [enumName, enumTy] : enumTypes) {
            if (switchTy == enumTy) {
                canUseSwitch = false;
                break;
            }
        }

        for (auto& [unionName, unionTy] : unionTypes) {
            if (switchTy == unionTy) {
                canUseSwitch = false;
                break;
            }
        }

        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "switch.end", currentFunction);
        std::vector<llvm::BasicBlock*> sectionBlocks;
        llvm::BasicBlock* defaultBB = nullptr;

        for (auto& section : switch_node->sections) {
            llvm::BasicBlock* bb = llvm::BasicBlock::Create(context, "switch.case", currentFunction);
            sectionBlocks.push_back(bb);
            if (section.is_default) { defaultBB = bb; }
        }

        if (!defaultBB) { defaultBB = endBB; }

        if (canUseSwitch) {
            llvm::SwitchInst* switchInst = builder->CreateSwitch(switchVal, defaultBB, switch_node->sections.size());

            for (size_t i = 0; i < switch_node->sections.size(); i++) {
                auto& section = switch_node->sections[i];
                if (section.is_default) continue;

                for (auto& caseLabel : section.cases) {
                    llvm::Value* caseVal = emitExpr(caseLabel.expr);
                    if (auto constInt = llvm::dyn_cast<llvm::ConstantInt>(caseVal)) { switchInst->addCase(constInt, sectionBlocks[i]); }
                }
            }
        } else {
            llvm::BasicBlock* currentCheckBB = builder->GetInsertBlock();

            for (size_t i = 0; i < switch_node->sections.size(); i++) {
                auto& section = switch_node->sections[i];

                if (section.is_default) { continue; }
                llvm::BasicBlock* nextCheckBB = (i + 1 < switch_node->sections.size())
                                                    ? llvm::BasicBlock::Create(context, "switch.check", currentFunction)
                                                    : defaultBB;

                builder->SetInsertPoint(currentCheckBB);

                llvm::Value* matches = nullptr;
                for (auto& caseLabel : section.cases) {
                    llvm::Value* caseVal = emitExpr(caseLabel.expr);

                    llvm::Value* cmp = nullptr;

                    if (switchTy->isPointerTy() && caseVal->getType()->isPointerTy()) {
                        llvm::Function* strcmp_fn = module->getFunction("qc_string_eq");
                        cmp = builder->CreateCall(strcmp_fn, {switchVal, caseVal});
                    } else if (switchTy->isIntegerTy()) {
                        cmp = builder->CreateICmpEQ(switchVal, caseVal);
                    } else if (switchTy->isFloatingPointTy()) {
                        cmp = builder->CreateFCmpOEQ(switchVal, caseVal);
                    } else {
                        llvm::Value* switchTag = builder->CreateExtractValue(switchVal, 0);
                        llvm::Value* caseTag = builder->CreateExtractValue(caseVal, 0);
                        llvm::Value* tagMatch = builder->CreateICmpEQ(switchTag, caseTag);

                        llvm::Value* switchData = builder->CreateExtractValue(switchVal, 1);
                        llvm::Value* caseData = builder->CreateExtractValue(caseVal, 1);
                        llvm::Value* dataMatch = builder->CreateICmpEQ(switchData, caseData);

                        cmp = builder->CreateAnd(tagMatch, dataMatch);
                    }
                    if (matches) {
                        matches = builder->CreateOr(matches, cmp);
                    } else {
                        matches = cmp;
                    }
                }

                builder->CreateCondBr(matches, sectionBlocks[i], nextCheckBB);
                currentCheckBB = nextCheckBB;
            }
        }

        llvm::BasicBlock* oldBreakBB = currentBreakBB;
        currentBreakBB = endBB;

        for (size_t i = 0; i < switch_node->sections.size(); i++) {
            builder->SetInsertPoint(sectionBlocks[i]);

            for (auto& stmt : switch_node->sections[i].body->statements) { emitStmt(stmt); }

            if (!builder->GetInsertBlock()->getTerminator()) {
                if (i + 1 < sectionBlocks.size()) {
                    builder->CreateBr(sectionBlocks[i + 1]);
                } else {
                    builder->CreateBr(endBB);
                }
            }
        }

        currentBreakBB = oldBreakBB;
        exitScope();
        builder->SetInsertPoint(endBB);
    } else if (auto qif_node = safe_get<QIfNode>(node)) {
        enterScope();
        if (qif_node->init.has_value()) { emitStmt(qif_node->init.value()); }
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "qif.end", currentFunction);

        llvm::Value* qifCond = emitExpr(qif_node->condition);
        for (auto& [enumName, enumTy] : enumTypes) {
            if (qifCond->getType() == enumTy) {
                llvm::Value* dataPtr = builder->CreateExtractValue(qifCond, 1);
                llvm::Type* targetTy = builder->getIntNTy(2);

                llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                qifCond = builder->CreateLoad(targetTy, typedPtr);
                break;
            }
        }
        qifCond = normalizeValue(qifCond, qif_node->condition);
        llvm::Value* qifBit1 = builder->CreateAnd(qifCond, builder->getIntN(2, 0b10));
        llvm::Value* qif_is_true = builder->CreateICmpNE(qifBit1, builder->getIntN(2, 0));

        llvm::BasicBlock* qifBodyBB = llvm::BasicBlock::Create(context, "qif.body", currentFunction);
        llvm::BasicBlock* nextBB = (qif_node->qelif_branches.empty() && !qif_node->qelse_branch)
                                       ? endBB
                                       : llvm::BasicBlock::Create(context, "qelif.check", currentFunction);

        builder->CreateCondBr(qif_is_true, qifBodyBB, nextBB);

        builder->SetInsertPoint(qifBodyBB);
        for (auto& stmt : qif_node->then_branch->statements) { emitStmt(stmt); }
        if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(endBB); }

        for (size_t i = 0; i < qif_node->qelif_branches.size(); i++) {
            builder->SetInsertPoint(nextBB);

            llvm::Value* elifCond = emitExpr(qif_node->qelif_branches[i].first);
            llvm::Value* elifBit1 = builder->CreateAnd(elifCond, builder->getIntN(2, 0b10));
            llvm::Value* elif_is_true = builder->CreateICmpNE(elifBit1, builder->getIntN(2, 0));

            llvm::BasicBlock* elifBodyBB = llvm::BasicBlock::Create(context, "qelif.body", currentFunction);
            llvm::BasicBlock* nextElifBB = (i + 1 < qif_node->qelif_branches.size() || qif_node->qelse_branch)
                                               ? llvm::BasicBlock::Create(context, "qelif.check", currentFunction)
                                               : endBB;

            builder->CreateCondBr(elif_is_true, elifBodyBB, nextElifBB);

            builder->SetInsertPoint(elifBodyBB);
            for (auto& stmt : qif_node->qelif_branches[i].second->statements) { emitStmt(stmt); }
            if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(endBB); }

            nextBB = nextElifBB;
        }

        if (qif_node->qelse_branch) {
            builder->SetInsertPoint(nextBB);
            llvm::Value* qifBit0 = builder->CreateAnd(qifCond, builder->getIntN(2, 0b01));
            llvm::Value* all_false = builder->CreateICmpNE(qifBit0, builder->getIntN(2, 0));
            for (auto& qelif : qif_node->qelif_branches) {
                llvm::Value* elifCond = emitExpr(qelif.first);
                llvm::Value* elifBit0 = builder->CreateAnd(elifCond, builder->getIntN(2, 0b01));
                llvm::Value* elif_false = builder->CreateICmpNE(elifBit0, builder->getIntN(2, 0));
                all_false = builder->CreateAnd(all_false, elif_false);
            }

            llvm::BasicBlock* qelseBodyBB = llvm::BasicBlock::Create(context, "qelse.body", currentFunction);
            builder->CreateCondBr(all_false, qelseBodyBB, endBB);

            builder->SetInsertPoint(qelseBodyBB);
            for (auto& stmt : qif_node->qelse_branch->statements) { emitStmt(stmt); }
            if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(endBB); }
        }
        exitScope();
        builder->SetInsertPoint(endBB);
    } else if (auto qsw = safe_get<QSwitchNode>(node)) {
        enterScope();
        llvm::Value* qb_val = emitExpr(qsw->value);
        if (!qb_val) {
            cg_error(Position("", "", 0, 0, 0), "Failed to compile qswitch value");
            return;
        }
        for (auto& [enumName, enumTy] : enumTypes) {
            if (qb_val->getType() == enumTy) {
                llvm::Value* dataPtr = builder->CreateExtractValue(qb_val, 1);
                llvm::Type* targetTy = builder->getIntNTy(2);

                llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                qb_val = builder->CreateLoad(targetTy, typedPtr);
                break;
            }
        }
        qb_val = normalizeValue(qb_val, qsw->value);
        if (qb_val->getType() != builder->getIntNTy(2)) {
            cg_error(Position("", "", 0, 0, 0), "qswitch requires qbool type");
            return;
        }
        llvm::BasicBlock* check_true = llvm::BasicBlock::Create(context, "qsw.check_true", currentFunction);
        llvm::BasicBlock* check_false = llvm::BasicBlock::Create(context, "qsw.check_false", currentFunction);
        llvm::BasicBlock* case_t_block = nullptr;
        llvm::BasicBlock* case_f_block = nullptr;
        llvm::BasicBlock* case_n_block = nullptr;
        llvm::BasicBlock* case_b_block = nullptr;
        llvm::BasicBlock* qswitch_end = llvm::BasicBlock::Create(context, "qswitch.end", currentFunction);
        if (qsw->case_t) { case_t_block = llvm::BasicBlock::Create(context, "qsw.case_t", currentFunction); }
        if (qsw->case_f) { case_f_block = llvm::BasicBlock::Create(context, "qsw.case_f", currentFunction); }
        if (qsw->case_n) { case_n_block = llvm::BasicBlock::Create(context, "qsw.case_n", currentFunction); }
        if (qsw->case_b) { case_b_block = llvm::BasicBlock::Create(context, "qsw.case_b", currentFunction); }
        builder->CreateBr(check_true);
        builder->SetInsertPoint(check_true);
        llvm::Value* has_true = builder->CreateAnd(qb_val, builder->getIntN(2, 2), "has_true");
        llvm::Value* is_true = builder->CreateICmpNE(has_true, builder->getIntN(2, 0), "is_true");
        builder->CreateCondBr(is_true, check_false, check_false);
        builder->SetInsertPoint(check_false);
        llvm::Value* has_false = builder->CreateAnd(qb_val, builder->getIntN(2, 1), "has_false");
        llvm::Value* is_false = builder->CreateICmpNE(has_false, builder->getIntN(2, 0), "is_false");
        llvm::Value* is_both = builder->CreateAnd(is_true, is_false, "is_both");
        llvm::Value* not_false = builder->CreateNot(is_false, "not_false");
        llvm::Value* is_qtrue_only = builder->CreateAnd(is_true, not_false, "is_qtrue_only");
        llvm::Value* not_true = builder->CreateNot(is_true, "not_true");
        llvm::Value* is_qfalse_only = builder->CreateAnd(not_true, is_false, "is_qfalse_only");
        llvm::Value* is_none = builder->CreateAnd(not_true, not_false, "is_none");
        llvm::BasicBlock* check_qtrue = llvm::BasicBlock::Create(context, "qsw.check_qtrue", currentFunction);
        llvm::BasicBlock* check_qfalse = llvm::BasicBlock::Create(context, "qsw.check_qfalse", currentFunction);
        llvm::BasicBlock* check_none_final = llvm::BasicBlock::Create(context, "qsw.check_none_final", currentFunction);
        builder->CreateCondBr(is_both, case_b_block ? case_b_block : qswitch_end, check_qtrue);
        builder->SetInsertPoint(check_qtrue);
        builder->CreateCondBr(is_qtrue_only, case_t_block ? case_t_block : qswitch_end, check_qfalse);
        builder->SetInsertPoint(check_qfalse);
        builder->CreateCondBr(is_qfalse_only, case_f_block ? case_f_block : qswitch_end, check_none_final);
        builder->SetInsertPoint(check_none_final);
        builder->CreateCondBr(is_none, case_n_block ? case_n_block : qswitch_end, qswitch_end);
        if (case_t_block && qsw->case_t) {
            builder->SetInsertPoint(case_t_block);
            for (auto& stmt : qsw->case_t->statements) { emitStmt(stmt); }
            if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(qswitch_end); }
        }

        if (case_f_block && qsw->case_f) {
            builder->SetInsertPoint(case_f_block);
            for (auto& stmt : qsw->case_f->statements) { emitStmt(stmt); }
            if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(qswitch_end); }
        }

        if (case_n_block && qsw->case_n) {
            builder->SetInsertPoint(case_n_block);
            for (auto& stmt : qsw->case_n->statements) { emitStmt(stmt); }
            if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(qswitch_end); }
        }
        if (case_b_block && qsw->case_b) {
            builder->SetInsertPoint(case_b_block);
            for (auto& stmt : qsw->case_b->statements) { emitStmt(stmt); }
            if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(qswitch_end); }
        }
        exitScope();
        builder->SetInsertPoint(qswitch_end);
    } else if (auto arrDecl = safe_get<ArrayDeclNode>(node)) {
        std::string name = arrDecl->var_name_tok.value;
        std::string elemType = arrDecl->type_tok.value;
        arrayTypeStrings[name] = elemType;
        llvm::Type* elemTy = llvmTypeFor(elemType);
        if (!std::holds_alternative<ArrayLiteralNode*>(arrDecl->value) && !std::holds_alternative<std::monostate>(arrDecl->value)) {

            llvm::Value* arrPtr = emitExpr(arrDecl->value);
            if (!arrPtr) return;

            llvm::AllocaInst* alloc = createEntryAlloca(name, arrPtr->getType());
            builder->CreateStore(arrPtr, alloc);
            locals[name] = alloc;

            return;
        }
        if (auto arrLit = std::get_if<ArrayLiteralNode*>(&arrDecl->value)) {
            bool hasSpread = false;
            for (auto& elem : (*arrLit)->elements) {
                if (std::holds_alternative<SpreadNode*>(elem)) {
                    hasSpread = true;
                    break;
                }
            }

            if (hasSpread) {
                llvm::Value* arrPtr = emitExpr(arrDecl->value);
                if (!arrPtr) return;
                llvm::Value* totalSize = builder->getInt32(0);
                if (auto arrLit = std::get_if<ArrayLiteralNode*>(&arrDecl->value)) {
                    for (auto& elem : (*arrLit)->elements) {
                        if (auto spread = std::get_if<SpreadNode*>(&elem)) {
                            llvm::Value* collVal = emitExpr((*spread)->expr);
                            llvm::Value* spreadLen = getCollectionLength(collVal, (*spread)->expr);
                            totalSize = builder->CreateAdd(totalSize, spreadLen);
                        } else {
                            totalSize = builder->CreateAdd(totalSize, builder->getInt32(1));
                        }
                    }
                }

                if (!arrDecl->sizes.empty() && arrDecl->sizes[0].has_value()) {
                    int userSize = *arrDecl->sizes[0];
                    arrayLengths[name] = userSize;
                } else if (auto* constSize = llvm::dyn_cast<llvm::ConstantInt>(totalSize)) {
                    arrayLengths[name] = constSize->getSExtValue();
                } else {
                    llvm::AllocaInst* sizeAlloc = createEntryAlloca(name + "_size", builder->getInt32Ty());
                    builder->CreateStore(totalSize, sizeAlloc);
                    runtimeArraySizes[name] = sizeAlloc;
                }
                llvm::AllocaInst* alloc = createEntryAlloca(name, arrPtr->getType());
                builder->CreateStore(arrPtr, alloc);
                std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
                locals[fullName] = alloc;
                arrayTypeStrings[fullName] = elemType;
                return;
            }
            auto [isJagged, depth] = checkJagged(arrDecl->value);
            size_t arraySize = (*arrLit)->elements.size();
            arrayLengths[name] = arraySize;
            if (isJagged) {
                int elemTypeCode = -1;
                if (elemType == "int")
                    elemTypeCode = 0;
                else if (elemType == "float")
                    elemTypeCode = 1;
                else if (elemType == "double")
                    elemTypeCode = 2;
                else if (elemType == "char")
                    elemTypeCode = 3;
                else if (elemType == "bool")
                    elemTypeCode = 4;
                else if (elemType == "qbool")
                    elemTypeCode = 5;
                else if (elemType == "string")
                    elemTypeCode = 6;

                llvm::Value* jaggedArr = createJaggedArray(arrDecl->value, elemTypeCode, depth - 1);
                llvm::Type* ptrTy = llvm::PointerType::get(context, 0);
                llvm::AllocaInst* alloc = createEntryAlloca(name, ptrTy);
                builder->CreateStore(jaggedArr, alloc);
                std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
                locals[fullName] = alloc;
                jaggedArrays[fullName] = {elemTypeCode, depth};
                return;
            }

            std::vector<uint64_t> actualSizes;

            std::function<void(AnyNode&, int)> inferDims;
            inferDims = [&](AnyNode& node, int depth) {
                if (auto lit = std::get_if<ArrayLiteralNode*>(&node)) {
                    if (actualSizes.size() <= depth) { actualSizes.push_back((*lit)->elements.size()); }
                    if (!(*lit)->elements.empty()) { inferDims((*lit)->elements[0], depth + 1); }
                }
            };

            inferDims(arrDecl->value, 0);
            llvm::Type* arrTy = elemTy;
            for (int i = actualSizes.size() - 1; i >= 0; i--) { arrTy = llvm::ArrayType::get(arrTy, actualSizes[i]); }

            bool useHeap = (currentFunction != nullptr);

            llvm::AllocaInst* alloc;
            if (useHeap) {
                llvm::Function* mallocFn = module->getFunction("malloc");
                if (!mallocFn) {
                    llvm::FunctionType* mallocTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {builder->getInt64Ty()}, false);
                    mallocFn = llvm::Function::Create(mallocTy, llvm::Function::InternalLinkage, "malloc", module);
                }

                const llvm::DataLayout& DL = module->getDataLayout();
                uint64_t sizeBytes = DL.getTypeAllocSize(arrTy);

                llvm::Value* mallocCall = builder->CreateCall(mallocFn, {builder->getInt64(sizeBytes)}, "heap_arr");
                llvm::Value* arrPtr = builder->CreateBitCast(mallocCall, llvm::PointerType::get(context, 0), "arr_cast");

                alloc = createEntryAlloca(name, llvm::PointerType::get(context, 0));
                builder->CreateStore(arrPtr, alloc);
                arrayTypeStrings[name] = elemType;
            } else {
                alloc = createEntryAlloca(name, arrTy);
            }
            std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[fullName] = alloc;
            std::function<void(llvm::Value*, llvm::Type*, AnyNode&, std::vector<uint64_t>&)> initArray;
            initArray = [&](llvm::Value* ptr, llvm::Type* ty, AnyNode& node, std::vector<uint64_t>& indices) {
                if (auto lit = std::get_if<ArrayLiteralNode*>(&node)) {
                    for (size_t i = 0; i < (*lit)->elements.size(); i++) {
                        indices.push_back(i);

                        if (std::holds_alternative<ArrayLiteralNode*>((*lit)->elements[i])) {
                            initArray(ptr, ty, (*lit)->elements[i], indices);
                        } else {
                            llvm::Value* elemVal = emitExpr((*lit)->elements[i]);
                            if (!elemVal) return;

                            std::vector<llvm::Value*> llvmIndices = useHeap ? std::vector<llvm::Value*>{builder->getInt32(0)}
                                                                            : std::vector<llvm::Value*>{builder->getInt32(0)};

                            for (auto idx : indices) { llvmIndices.push_back(builder->getInt32(idx)); }

                            llvm::Value* basePtr = useHeap ? builder->CreateLoad(llvm::PointerType::get(context, 0), alloc, "heap_ptr")
                                                           : static_cast<llvm::Value*>(alloc);

                            llvm::Value* elemPtr = builder->CreateInBoundsGEP(arrTy, basePtr, llvmIndices);
                            builder->CreateStore(elemVal, elemPtr);
                        }

                        indices.pop_back();
                    }
                }
            };

            std::vector<uint64_t> indices;
            initArray(alloc, arrTy, arrDecl->value, indices);
        }
        if (!arrDecl->sizes.empty() && arrDecl->sizes[0].has_value()) {
            int arraySize = *arrDecl->sizes[0];
            if (std::holds_alternative<std::monostate>(arrDecl->value)) {
                llvm::ArrayType* arrTy = llvm::ArrayType::get(elemTy, arraySize);
                llvm::AllocaInst* alloc = createEntryAlloca(name, arrTy);
                llvm::Value* zeroInit = llvm::ConstantAggregateZero::get(arrTy);
                builder->CreateStore(zeroInit, alloc);
                locals[name] = alloc;
                arrayTypeStrings[name] = elemType;
                arrayLengths[name] = arraySize;

                return;
            }
        }
        return;
    } else if (auto arrAssign = safe_get<ArrayAssignNode>(node)) {
        if (auto arrAcc = safe_get<ArrayAccessNode>(arrAssign->array_access)) {
            std::string ptrTy = getExpressionType(arrAcc->base);
            if (ptrTy.ends_with("*") || ptrTy == "@nullptr") {
                if (ptrTy == "@nullptr") {
                    cg_error(Position(), "Attempted to dereference nullptr");
                    return;
                }
                if (ptrTy == "void*") {
                    cg_error(Position(), "You cannot dereference or indice void*");
                    return;
                }
                std::string valueTy = getExpressionType(arrAcc->indices[0]);
                if (valueTy != "int") {
                    cg_error(Position(), "Attempted to index a pointer with a "
                                         "non-integer value.");
                    return;
                }
                llvm::Value* value = emitExpr(arrAcc->indices[0]);
                ptrTy.pop_back();
                llvm::Value* addr = builder->CreateGEP(llvmTypeFor(ptrTy), emitExpr(arrAcc->base), value, "ptr_arr_asi");
                llvm::Value* valToStore = emitExpr(arrAssign->value);
                builder->CreateStore(valToStore, addr);
            }
            if (auto varAcc = safe_get<VarAccessNode>(arrAcc->base)) {
                std::string name = varAcc->var_name_tok.value;
                if (hasJaggedArray(name)) {
                    auto jagIt = findJaggedArray(name);
                    auto it = locals.find(name);
                    if (it == locals.end()) {
                        cg_error(Position(), "Unknown jagged array: " + name);
                        return;
                    }

                    llvm::Value* jaggedPtr = builder->CreateLoad(llvm::PointerType::get(context, 0), it->second, "jagged_ptr");
                    llvm::ArrayType* indicesArrTy = llvm::ArrayType::get(builder->getInt32Ty(), arrAcc->indices.size());
                    llvm::AllocaInst* indicesAlloc = createEntryAlloca("indices_arr", indicesArrTy);

                    for (size_t i = 0; i < arrAcc->indices.size(); i++) {
                        llvm::Value* indexVal = emitExpr(arrAcc->indices[i]);
                        if (!indexVal) return;

                        std::vector<llvm::Value*> indices = {builder->getInt32(0), builder->getInt32(i)};
                        llvm::Value* idxPtr = builder->CreateInBoundsGEP(indicesArrTy, indicesAlloc, indices);
                        builder->CreateStore(indexVal, idxPtr);
                    }

                    llvm::Function* getFn = module->getFunction("qc_jagged_array_get");
                    if (!getFn) {
                        llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                        llvm::Type* intPtrTy = llvm::PointerType::get(context, 0);
                        llvm::FunctionType* fnTy = llvm::FunctionType::get(voidPtrTy, {voidPtrTy, intPtrTy, builder->getInt32Ty()}, false);
                        getFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_jagged_array_get", module);
                    }

                    std::vector<llvm::Value*> idxIndices = {builder->getInt32(0), builder->getInt32(0)};
                    llvm::Value* indicesPtr = builder->CreateInBoundsGEP(indicesArrTy, indicesAlloc, idxIndices);

                    llvm::Value* elemPtr = builder->CreateCall(getFn, {jaggedPtr, indicesPtr, builder->getInt32(arrAcc->indices.size())},
                                                               "jagged_elem_ptr");

                    llvm::Value* valueVal = emitExpr(arrAssign->value);
                    if (!valueVal) return;

                    int elemTypeCode = jagIt->second.first;
                    llvm::Type* elemTy = nullptr;
                    switch (elemTypeCode) {
                    case 0: elemTy = builder->getInt32Ty(); break;
                    case 1: elemTy = builder->getFloatTy(); break;
                    case 2: elemTy = builder->getDoubleTy(); break;
                    case 3: elemTy = builder->getInt8Ty(); break;
                    case 4: elemTy = builder->getInt1Ty(); break;
                    case 5: elemTy = builder->getIntNTy(2); break;
                    case 6: elemTy = llvm::PointerType::get(context, 0); break;
                    }

                    llvm::Value* typedPtr = builder->CreateBitCast(elemPtr, llvm::PointerType::get(context, 0));
                    builder->CreateStore(valueVal, typedPtr);

                    return;
                }
                if (hasMap(name)) {
                    auto mapIt = findMap(name);
                    auto it = locals.find(name);
                    if (it == locals.end()) {
                        cg_error(Position(), "Unknown map: " + name);
                        return;
                    }

                    llvm::Value* mapPtr = builder->CreateLoad(llvm::PointerType::get(context, 0), it->second, "map_ptr");

                    llvm::Value* keyVal = emitExpr(arrAcc->indices[0]);
                    llvm::Value* valueVal = emitExpr(arrAssign->value);
                    if (!keyVal || !valueVal) return;

                    llvm::Value* keyPtr;
                    if (keyVal->getType()->isPointerTy()) {
                        keyPtr = keyVal;
                    } else {
                        llvm::AllocaInst* keyAlloc = createEntryAlloca("map_key", keyVal->getType());
                        builder->CreateStore(keyVal, keyAlloc);
                        keyPtr = builder->CreateBitCast(keyAlloc, llvm::PointerType::get(context, 0));
                    }

                    llvm::Value* valPtr;
                    if (valueVal->getType()->isPointerTy()) {
                        valPtr = valueVal;
                    } else {
                        llvm::AllocaInst* valAlloc = createEntryAlloca("map_val", valueVal->getType());
                        builder->CreateStore(valueVal, valAlloc);
                        valPtr = builder->CreateBitCast(valAlloc, llvm::PointerType::get(context, 0));
                    }
                    llvm::Function* setFn = module->getFunction("qc_map_set");
                    if (!setFn) {
                        llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                        llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getVoidTy(), {voidPtrTy, voidPtrTy, voidPtrTy}, false);
                        setFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_map_set", module);
                    }

                    builder->CreateCall(setFn, {mapPtr, keyPtr, valPtr});
                    return;
                }
                if (hasList(name)) {
                    auto listIt = findList(name);
                    llvm::Value* alloc = getVarAddress(name);
                    if (!alloc) {
                        cg_error(Position(), "Unknown list: " + name);
                        return;
                    }

                    llvm::Value* listPtr = builder->CreateLoad(llvm::PointerType::get(context, 0), alloc, "list_ptr");

                    llvm::Value* indexVal = emitExpr(arrAcc->indices[0]);
                    if (!indexVal) return;

                    llvm::Value* valueVal = emitExpr(arrAssign->value);
                    if (!valueVal) return;

                    llvm::AllocaInst* valAlloc = createEntryAlloca("list_set_val", valueVal->getType());
                    builder->CreateStore(valueVal, valAlloc);
                    llvm::Value* valPtr = builder->CreateBitCast(valAlloc, llvm::PointerType::get(context, 0));

                    llvm::Function* setFn = module->getFunction("qc_list_set");
                    if (!setFn) {
                        llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                        llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getVoidTy(), {voidPtrTy, builder->getInt32Ty(), voidPtrTy},
                                                                           false);
                        setFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_list_set", module);
                    }

                    builder->CreateCall(setFn, {listPtr, indexVal, valPtr});
                    return;
                }
                llvm::Value* alloc = getVarAddress(name);
                if (!alloc) {
                    cg_error(Position(), "Unknown array: " + name);
                    return;
                }

                llvm::Value* arrAlloc = alloc;
                llvm::Type* arrTy = getPointeeType(name);

                llvm::Value* indexVal = emitExpr(arrAcc->indices[0]);
                if (!indexVal) return;

                llvm::Value* valueVal = emitExpr(arrAssign->value);
                if (!valueVal) return;
                if (arrTy->isPointerTy()) {
                    llvm::Value* ptr = builder->CreateLoad(arrTy, arrAlloc, "arr_ptr");
                    llvm::Type* elemTy = valueVal->getType();

                    llvm::Value* elemPtr = builder->CreateGEP(elemTy, ptr, indexVal, "arr_elem_ptr");

                    builder->CreateStore(valueVal, elemPtr);
                } else if (arrTy->isArrayTy()) {
                    std::vector<llvm::Value*> indices = {builder->getInt32(0), indexVal};
                    llvm::Value* elemPtr = builder->CreateInBoundsGEP(arrTy, arrAlloc, indices, "arr_elem_ptr");

                    builder->CreateStore(valueVal, elemPtr);
                }
            }
        }

        return;
    } else if (auto listDecl = safe_get<ListDeclNode>(node)) {
        std::string name = listDecl->var_name_tok.value;
        std::string typeStr = listDecl->type_tok.value;
        size_t start = typeStr.find('<');
        size_t end = typeStr.find('>');
        std::string elemType = typeStr.substr(start + 1, end - start - 1);

        int elemTypeCode = -1;
        if (elemType == "int" || elemType == "short int" || elemType == "addr_t" || elemType == "long int")
            elemTypeCode = 0;
        else if (elemType == "float")
            elemTypeCode = 1;
        else if (elemType == "double")
            elemTypeCode = 2;
        else if (elemType == "char")
            elemTypeCode = 3;
        else if (elemType == "bool")
            elemTypeCode = 4;
        else if (elemType == "qbool")
            elemTypeCode = 5;
        else
            elemTypeCode = 6;
        llvm::Function* createFn = module->getFunction("qc_create_list");
        if (!createFn) {
            llvm::Type* ptrTy = llvm::PointerType::get(context, 0);
            llvm::FunctionType* fnTy = llvm::FunctionType::get(ptrTy, {builder->getInt32Ty()}, false);
            createFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_create_list", module);
        }

        llvm::Value* listPtr = builder->CreateCall(createFn, {builder->getInt32(elemTypeCode)}, "list_ptr");
        if (auto callNode = std::get_if<CallNode*>(&listDecl->value)) {
            listPtr = emitExpr(listDecl->value);
            if (!listPtr) return;
        } else if (auto arrLit = std::get_if<ArrayLiteralNode*>(&listDecl->value)) {
            llvm::Function* pushFn = module->getFunction("qc_list_push");
            if (!pushFn) {
                llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getVoidTy(), {voidPtrTy, voidPtrTy}, false);
                pushFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_list_push", module);
            }

            for (auto& elem : (*arrLit)->elements) {
                if (auto spread = std::get_if<SpreadNode*>(&elem)) {
                    llvm::Value* collVal = emitExpr((*spread)->expr);
                    expandSpreadIntoList(collVal, (*spread)->expr, listPtr, pushFn, elemTypeCode);
                } else {
                    llvm::Value* elemVal = emitExpr(elem);
                    if (!elemVal) continue;

                    llvm::AllocaInst* tempAlloc = createEntryAlloca("temp_elem", elemVal->getType());
                    builder->CreateStore(elemVal, tempAlloc);

                    llvm::Value* elemPtr = builder->CreateBitCast(tempAlloc, llvm::PointerType::get(context, 0));

                    builder->CreateCall(pushFn, {listPtr, elemPtr, builder->getInt32(elemTypeCode)});
                }
            }
        } else if (auto methodCall = std::get_if<MethodCallNode*>(&listDecl->value)) {
            listPtr = emitExpr(listDecl->value);
            if (!listPtr) return;
        } else {
            listPtr = emitExpr(listDecl->value);
            if (!listPtr) return;
        }
        llvm::Type* ptrTy = llvm::PointerType::get(context, 0);
        llvm::AllocaInst* alloc = createEntryAlloca(name, ptrTy);
        builder->CreateStore(listPtr, alloc);
        std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
        locals[fullName] = alloc;
        lists[fullName] = elemTypeCode;
        return;
    }

    else if (auto foreach = safe_get<ForeachNode>(node)) {
        std::string elemName = foreach->elem_name.value;
        std::string iterName = "__foreach_i_" + elemName;

        llvm::Value* collVal = emitExpr(foreach->collection);
        if (!collVal) return;

        llvm::Value* lengthVal = nullptr;
        bool isArray = false;
        llvm::Value* arrayAlloc = nullptr;
        llvm::Type* arrayElemTy = nullptr;
        std::string collName = "";
        if (auto varAccess = std::get_if<VarAccessNode*>(&foreach->collection)) {
            collName = (*varAccess)->var_name_tok.value;

            llvm::Value* alloc = getVarAddress(collName);
            if (alloc) {
                llvm::Type* allocTy = getPointeeType(collName);

                if (allocTy->isArrayTy()) {
                    isArray = true;
                    arrayAlloc = alloc;
                    lengthVal = builder->getInt32(allocTy->getArrayNumElements());
                } else if (allocTy->isPointerTy()) {
                    if (hasArrayLength(collName)) {
                        auto lenIt = findArrayLength(collName);
                        isArray = true;
                        arrayAlloc = alloc;
                        lengthVal = builder->getInt32(lenIt->second);

                        if (hasArrayType(collName)) {
                            auto typeIt = findArrayType(collName);
                            arrayElemTy = llvmTypeFor(typeIt->second);
                        } else {
                        }
                    } else if (runtimeArraySizes.find(collName) != runtimeArraySizes.end()) {
                        isArray = true;
                        arrayAlloc = alloc;
                        llvm::AllocaInst* sizeAlloc = runtimeArraySizes[collName];
                        lengthVal = builder->CreateLoad(builder->getInt32Ty(), sizeAlloc, "runtime_len");
                        if (hasArrayType(collName)) {
                            auto typeIt = findArrayType(collName);
                            arrayElemTy = llvmTypeFor(typeIt->second);
                        }
                    } else {
                    }
                }
            }
        }
        if (!lengthVal) {
            llvm::Function* lenFn = module->getFunction("qc_list_length");
            if (!lenFn) {
                llvm::FunctionType* ty = llvm::FunctionType::get(builder->getInt32Ty(), {llvm::PointerType::get(context, 0)}, false);
                lenFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_list_length", module);
            }
            lengthVal = builder->CreateCall(lenFn, {collVal}, "coll_len");
        }
        enterScope();
        llvm::Type* elemTy = llvmTypeFor(foreach->elem_type.value);
        llvm::AllocaInst* iterAlloc = createEntryAlloca(iterName, builder->getInt32Ty());
        llvm::AllocaInst* elemAlloc = createEntryAlloca(elemName, elemTy);
        locals[iterName] = iterAlloc;
        locals[elemName] = elemAlloc;
        varTypes[elemName] = foreach->elem_type.value;
        varTypes[iterName] = "int";
        builder->CreateStore(builder->getInt32(0), iterAlloc);

        llvm::BasicBlock* condBB = llvm::BasicBlock::Create(context, "foreach.cond", currentFunction);
        llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(context, "foreach.body", currentFunction);
        llvm::BasicBlock* incBB = llvm::BasicBlock::Create(context, "foreach.inc", currentFunction);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "foreach.end", currentFunction);

        builder->CreateBr(condBB);

        builder->SetInsertPoint(condBB);
        llvm::Value* iVal = builder->CreateLoad(builder->getInt32Ty(), iterAlloc, iterName);
        llvm::Value* cmpVal = builder->CreateICmpSLT(iVal, lengthVal, "foreach_cmp");
        builder->CreateCondBr(cmpVal, bodyBB, endBB);

        builder->SetInsertPoint(bodyBB);

        llvm::Value* elemVal = nullptr;

        if (isArray && arrayAlloc) {
            llvm::Type* allocTy = getPointeeType(collName);

            if (allocTy->isArrayTy()) {
                std::vector<llvm::Value*> indices = {builder->getInt32(0), iVal};
                llvm::Value* elemPtr = builder->CreateInBoundsGEP(allocTy, arrayAlloc, indices, "elem_ptr");
                elemVal = builder->CreateLoad(elemTy, elemPtr, "elem");
            } else if (allocTy->isPointerTy() && arrayElemTy) {
                llvm::Value* heapPtr = builder->CreateLoad(allocTy, arrayAlloc, "heap_ptr");
                llvm::Value* elemPtr = builder->CreateGEP(arrayElemTy, heapPtr, iVal, "heap_elem_ptr");

                elemVal = builder->CreateLoad(elemTy, elemPtr, "elem");
            }
        } else {
            llvm::Function* getFn = module->getFunction("qc_list_get");
            if (!getFn) {
                llvm::FunctionType* ty = llvm::FunctionType::get(llvm::PointerType::get(context, 0),
                                                                 {llvm::PointerType::get(context, 0), builder->getInt32Ty()}, false);
                getFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_list_get", module);
            }
            llvm::Value* elemPtr = builder->CreateCall(getFn, {collVal, iVal}, "elem_ptr");
            if (foreach->elem_type.value == "string") {
                elemVal = elemPtr;
            } else {
                llvm::Value* typedPtr = builder->CreateBitCast(elemPtr, llvm::PointerType::get(context, 0));
                elemVal = builder->CreateLoad(elemTy, typedPtr, "elem");
            }
        }

        builder->CreateStore(elemVal, elemAlloc);

        emitStmt(foreach->body);

        builder->CreateBr(incBB);

        builder->SetInsertPoint(incBB);
        llvm::Value* iVal2 = builder->CreateLoad(builder->getInt32Ty(), iterAlloc, iterName);
        llvm::Value* incVal = builder->CreateAdd(iVal2, builder->getInt32(1), "i_inc");
        builder->CreateStore(incVal, iterAlloc);
        builder->CreateBr(condBB);
        exitScope();
        builder->SetInsertPoint(endBB);

        locals.erase(iterName);
        locals.erase(elemName);

        return;
    } else if (auto stmts = safe_get<StatementsNode>(node)) {
        for (auto& stmt : stmts->statements) { emitStmt(stmt); }
        return;
    }

    else if (auto mapDecl = safe_get<MapDeclNode>(node)) {
        std::string name = mapDecl->var_name.value;
        std::string keyType = mapDecl->key_type.value;
        std::string valueType = mapDecl->value_type.value;

        int keyTypeCode = getTypeCode(keyType);
        int valueTypeCode = getTypeCode(valueType);
        llvm::Function* createFn = module->getFunction("qc_create_map");
        if (!createFn) {
            llvm::Type* ptrTy = llvm::PointerType::get(context, 0);
            llvm::FunctionType* fnTy = llvm::FunctionType::get(ptrTy, {builder->getInt32Ty(), builder->getInt32Ty()}, false);
            createFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_create_map", module);
        }

        llvm::Value* mapPtr = builder->CreateCall(createFn, {builder->getInt32(keyTypeCode), builder->getInt32(valueTypeCode)}, "map_ptr");

        if (!mapDecl->init_pairs.empty()) {
            llvm::Function* setFn = module->getFunction("qc_map_set");
            if (!setFn) {
                llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                llvm::FunctionType* fnTy = llvm::FunctionType::get(builder->getVoidTy(), {voidPtrTy, voidPtrTy, voidPtrTy}, false);
                setFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_map_set", module);
            }

            for (auto& pair : mapDecl->init_pairs) {
                llvm::Value* keyVal = emitExpr(pair.first);
                llvm::Value* valueVal = emitExpr(pair.second);
                if (!keyVal || !valueVal) continue;

                llvm::Value* keyPtr;
                llvm::Value* valPtr;

                if (keyVal->getType()->isPointerTy()) {
                    keyPtr = keyVal;
                } else {
                    llvm::AllocaInst* keyAlloc = createEntryAlloca("temp_key", keyVal->getType());
                    builder->CreateStore(keyVal, keyAlloc);
                    keyPtr = builder->CreateBitCast(keyAlloc, llvm::PointerType::get(context, 0));
                }

                if (valueVal->getType()->isPointerTy()) {
                    valPtr = valueVal;
                } else {
                    llvm::AllocaInst* valAlloc = createEntryAlloca("temp_val", valueVal->getType());
                    builder->CreateStore(valueVal, valAlloc);
                    valPtr = builder->CreateBitCast(valAlloc, llvm::PointerType::get(context, 0));
                }

                builder->CreateCall(setFn, {mapPtr, keyPtr, valPtr});
            }
        }

        llvm::Type* ptrTy = llvm::PointerType::get(context, 0);
        llvm::AllocaInst* alloc = createEntryAlloca(name, ptrTy);
        builder->CreateStore(mapPtr, alloc);
        std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
        locals[fullName] = alloc;
        maps[fullName] = {keyTypeCode, valueTypeCode};

        return;
    } else if (auto ns = safe_get<NamespaceNode>(node)) {
        namespaceStack.push_back(ns->name);
        for (auto& decl : ns->body) { emitStmt(decl); }
        namespaceStack.pop_back();

        return;
    }
}
std::pair<bool, int> LLVMCompiler::checkJagged(AnyNode& node) {
    if (auto lit = std::get_if<ArrayLiteralNode*>(&node)) {
        if ((*lit)->elements.empty()) return {false, 0};

        auto [firstJagged, firstDepth] = checkJagged((*lit)->elements[0]);
        size_t firstSize = 0;
        if (auto firstLit = safe_get<ArrayLiteralNode>((*lit)->elements[0])) { firstSize = firstLit->elements.size(); }

        bool isJagged = firstJagged;
        int maxDepth = firstDepth;

        for (auto& elem : (*lit)->elements) {
            auto [elemJagged, elemDepth] = checkJagged(elem);
            maxDepth = std::max(maxDepth, elemDepth);
            isJagged = isJagged || elemJagged;

            if (auto elemLit = safe_get<ArrayLiteralNode>(elem)) {
                if (elemLit->elements.size() != firstSize) { isJagged = true; }
            }
        }

        return {isJagged, maxDepth + 1};
    }
    return {false, 0};
}
std::vector<CTError> LLVMCompiler::compile(
    StatementsNode* root, std::unordered_map<std::string, FunctionSignature> visibleFunctionSignatures,
    std::unordered_map<std::string, FuncDefNode*> visibleFunctionDefs, std::unordered_map<std::string, std::pair<int, int>> visibleJaggedArrays,
    std::unordered_map<std::string, std::string> visibleArrayTypeStrings, std::unordered_map<std::string, int> visibleLists,
    std::unordered_map<std::string, int> visibleArrayLengths, std::unordered_map<std::string, std::pair<int, int>> visibleMaps,
    std::unordered_map<std::string, std::string> visibleVarTypes, std::unordered_map<std::string, llvm::AllocaInst*> visibleRuntimeArraySizes,
    std::unordered_map<std::string, llvm::FunctionType*> visibleLambdaTypes,
    std::map<std::string, std::map<std::string, llvm::Function*>> visibleSpecializedFunctions,
    std::unordered_map<std::string, llvm::GlobalVariable*> visibleGlobals) {
    this->functionSignatures = visibleFunctionSignatures;
    this->functionDefs = visibleFunctionDefs;
    this->globals = visibleGlobals;
    this->varTypesStack = {visibleVarTypes};
    this->jaggedArraysStack = {visibleJaggedArrays};
    this->arrayTypeStringsStack = {visibleArrayTypeStrings};
    this->listsStack = {visibleLists};
    this->arrayLengthsStack = {visibleArrayLengths};
    this->mapsStack = {visibleMaps};
    this->runtimeArraySizes = visibleRuntimeArraySizes;
    this->lambdaTypes = visibleLambdaTypes;
    createUserTypes();
    std::function<void(NamespaceNode&)> createGlobals = [&](NamespaceNode& ns) {
        namespaceStack.push_back(ns.name);
        for (auto& decl : ns.body) {
            if (auto va = std::get_if<VarAssignNode*>(&decl)) {
                std::string fullName = getCurrentNamespace().empty() ? (*va)->var_name_tok.value
                                                                     : getCurrentNamespace() + "::" + (*va)->var_name_tok.value;
                llvm::Type* ty = llvmTypeFor((*va)->type_tok.value);
                auto* gv = module->getGlobalVariable(fullName);
                if (!gv) {
                    gv = new llvm::GlobalVariable(*module, ty, false, llvm::GlobalValue::ExternalLinkage, llvm::Constant::getNullValue(ty), fullName);
                }
                globals[fullName] = gv;
                varTypes[fullName] = (*va)->type_tok.value;
            } else if (auto nested = std::get_if<NamespaceNode*>(&decl)) {
                createGlobals(**nested);
            }
        }
        namespaceStack.pop_back();
    };
    for (auto& stmt : root->statements) {
        if (auto ns = std::get_if<NamespaceNode*>(&stmt)) {
            createGlobals(**ns);
        } else if (auto va = std::get_if<VarAssignNode*>(&stmt)) {
            std::string name = (*va)->var_name_tok.value;
            llvm::Type* ty = llvmTypeFor((*va)->type_tok.value);
            auto* gv = module->getGlobalVariable(name);
            if (!gv) {
                gv = new llvm::GlobalVariable(*module, ty, false, llvm::GlobalValue::ExternalLinkage, llvm::Constant::getNullValue(ty), name);
            }
            globals[name] = gv;
            varTypes[name] = (*va)->type_tok.value;
        }
    }
    std::function<void(NamespaceNode&)> scanAutoFunctions = [&](NamespaceNode& ns) {
        namespaceStack.push_back(ns.name);

        for (auto& decl : ns.body) {
            if (auto fn = safe_get<FuncDefNode>(decl)) {
                if (fn->name_tok.has_value()) {
                    std::string funcName = fn->name_tok.value().value;
                    std::string fullName = getCurrentNamespace() + "::" + funcName;
                    functionDefs[fullName] = fn;
                }
            } else if (auto nested = std::get_if<NamespaceNode*>(&decl)) {
                scanAutoFunctions(**nested);
            }
        }

        namespaceStack.pop_back();
    };

    for (auto& stmt : root->statements) {
        if (auto ns = std::get_if<NamespaceNode*>(&stmt)) {
            scanAutoFunctions(**ns);
        } else if (std::holds_alternative<FuncDefNode*>(stmt)) {
            auto fnPtr = std::get<FuncDefNode*>(stmt);
            if (!fnPtr->name_tok.has_value()) continue;
            std::string funcName = fnPtr->name_tok.value().value;
            if (funcName == entrypointName && !this->is_main) { continue; }
            functionDefs[funcName] = fnPtr;
        }
    }
    for (auto& [className, info] : userTypes) {
        if (info.kind != UserTypeKind::Class) continue;

        for (size_t methodIdx = 0; methodIdx < info.classMethods.size(); methodIdx++) {
            auto& method = info.classMethods[methodIdx];
            bool hasAutoParam = false;
            for (auto& param : method.params) {
                if (param.type.value == "auto") {
                    hasAutoParam = true;
                    break;
                }
            }

            bool hasAutoReturn = !method.return_types.empty() && method.return_types[0].value == "auto";

            if (hasAutoParam || hasAutoReturn) { autoMethodIndices[className].push_back(methodIdx); }
        }
    }
    std::function<void(NamespaceNode&)> compileNamespaceFunctions = [&](NamespaceNode& ns) {
        namespaceStack.push_back(ns.name);

        for (auto& decl : ns.body) {
            if (auto fn = safe_get<FuncDefNode>(decl)) {
                if (fn->name_tok.has_value()) {
                    if (fn->name_tok.value().value == entrypointName && !this->is_main) { continue; }

                    if (!funcHasAutoParams(fn)) { emitFuncDef(*fn); }
                }
            } else if (auto va = std::get_if<VarAssignNode*>(&decl)) {
                emitExpr(decl);
            } else if (auto nested = std::get_if<NamespaceNode*>(&decl)) {
                compileNamespaceFunctions(**nested);
            }
        }

        namespaceStack.pop_back();
    };

    for (auto& stmt : root->statements) {
        if (auto ns = std::get_if<NamespaceNode*>(&stmt)) {
            compileNamespaceFunctions(**ns);
        } else if (auto va = std::get_if<VarAssignNode*>(&stmt)) {
            emitExpr(stmt);
        } else if (std::holds_alternative<FuncDefNode*>(stmt)) {
            auto fnPtr = std::get<FuncDefNode*>(stmt);
            if (!fnPtr->name_tok.has_value()) continue;
            if (fnPtr->name_tok.value().value == entrypointName && !this->is_main) { continue; }
            if (!funcHasAutoParams(fnPtr)) { emitFuncDef(*fnPtr); }
        }
    }
    for (auto& [className, info] : userTypes) {
        if (info.kind != UserTypeKind::Class) continue;
        if (!info.namespace_path.empty()) { namespaceStack.push_back(info.namespace_path); }

        for (size_t methodIdx = 0; methodIdx < info.classMethods.size(); methodIdx++) {
            auto& method = info.classMethods[methodIdx];
            if (std::find(autoMethodIndices[className].begin(), autoMethodIndices[className].end(), methodIdx) !=
                autoMethodIndices[className].end()) {
                continue;
            }

            llvm::Function* fn = nullptr;
            auto& overloads = classMethods[className][method.name_tok.value];

            for (auto* overload : overloads) {
                if (overload->arg_size() - 1 == method.params.size()) {
                    bool matches = true;
                    for (size_t i = 0; i < method.params.size(); i++) {
                        auto& param = method.params[i];
                        llvm::Type* expectedType;
                        if (param.signature.has_value()) {
                            expectedType = llvm::PointerType::get(context, 0);
                        } else {
                            std::string resolvedType = resolveTypeName(param.type.value);
                            expectedType = llvmTypeFor(resolvedType);
                        }

                        llvm::Type* actualType = overload->getFunctionType()->getParamType(i + 1);
                        if (expectedType != actualType && param.type.value == "...") {
                            matches = false;
                            break;
                        }
                    }
                    if (matches) {
                        fn = overload;
                        break;
                    }
                }
            }

            if (!fn || !fn->empty()) continue;

            llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", fn);
            builder->SetInsertPoint(entry);

            auto oldThis = currentThis;
            auto oldClassName = currentClassName;
            auto oldFunction = currentFunction;
            auto oldLocals = locals;
            enterScope();
            currentThis = fn->getArg(0);
            varTypes["this"] = className;
            currentClassName = className;
            currentFunction = fn;

            for (size_t i = 0; i < method.params.size(); i++) {
                auto& param = method.params[i];
                llvm::Type* paramTy;
                std::string typeDescriptor;

                if (param.signature.has_value()) {
                    paramTy = llvm::PointerType::get(context, 0);
                    typeDescriptor = "fn";
                } else {
                    typeDescriptor = resolveTypeName(param.type.value);
                    paramTy = llvmTypeFor(typeDescriptor);
                }
                llvm::AllocaInst* alloc = createEntryAlloca(param.name.value, paramTy);
                builder->CreateStore(fn->getArg(i + 1), alloc);
                locals[param.name.value] = alloc;
                varTypes[param.name.value] = typeDescriptor;
            }
            size_t bodyStartIdx = 0;
            if (method.is_constructor && !info.baseClassName.empty()) {
                if (method.body && !method.body->statements.empty()) {
                    auto& firstStmt = method.body->statements[0];
                    if (auto call = std::get_if<CallNode*>(&firstStmt)) {
                        if (auto varAccess = std::get_if<VarAccessNode*>(&(*call)->node_to_call)) {
                            std::string callName = (*varAccess)->var_name_tok.value;
                            if (callName == info.baseClassName) {
                                std::vector<llvm::Value*> parentArgs;
                                for (auto& argNode : (*call)->arg_nodes) {
                                    llvm::Value* arg = emitExpr(argNode);
                                    if (!arg) continue;
                                    parentArgs.push_back(arg);
                                }
                                llvm::Function* parentCtor = findMethodOverload(info.baseClassName, info.baseClassName, parentArgs);
                                if (parentCtor) {
                                    std::vector<llvm::Value*> allArgs = {currentThis};
                                    allArgs.insert(allArgs.end(), parentArgs.begin(), parentArgs.end());
                                    builder->CreateCall(parentCtor, allArgs);
                                    bodyStartIdx = 1;
                                } else {
                                    cg_error(Position(), "Parent class '" + info.baseClassName + "' has no matching constructor");
                                }
                            }
                        }
                    }
                }
            }

            if (method.body) {
                for (size_t i = bodyStartIdx; i < method.body->statements.size(); i++) { emitStmt(method.body->statements[i]); }
            }

            if (!builder->GetInsertBlock()->getTerminator()) {
                if (fn->getReturnType()->isVoidTy()) {
                    builder->CreateRetVoid();
                } else {
                    builder->CreateRet(llvm::Constant::getNullValue(fn->getReturnType()));
                }
            }

            currentThis = oldThis;
            currentClassName = oldClassName;
            currentFunction = oldFunction;
            locals = oldLocals;
            exitScope();
        }

        if (!info.namespace_path.empty()) { namespaceStack.pop_back(); }
    }
    currentFunction = nullptr;
    if (this->is_main) {
        if (!no_main) {
            llvm::Function* userEntry = module->getFunction(entrypointName);
            if (userEntry) {
                userEntry->setName("__user_entry");

                llvm::FunctionType* mainTy = llvm::FunctionType::get(builder->getInt32Ty(), {}, false);
                llvm::Function* realMain = llvm::Function::Create(mainTy, llvm::Function::ExternalLinkage, "main", module);
                llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", realMain);
                builder->SetInsertPoint(entry);
                currentFunction = realMain;
                llvm::Value* result = builder->CreateCall(userEntry, {}, "entry_result");
                builder->CreateRet(result);
            } else {
                cg_error(Position(), "Entrypoint function '" + entrypointName + "' not defined");
            }
        }
    }
    if (!errors.empty()) return errors;
    return errors;
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////
// RUN
// //////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
std::string collapse_inline_brackets(const std::string& s) {
    std::string out;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '[') {
            size_t k = out.size();
            char prev = 0;
            while (k > 0) {
                char c = out[k - 1];
                if (!std::isspace((unsigned char)c)) {
                    prev = c;
                    break;
                }
                --k;
            }

            size_t j = i + 1;
            while (j < s.size() && std::isspace((unsigned char)s[j])) j++;

            bool prev_is_value_starter = (prev == '=' || prev == '(' || prev == ',' || prev == '{' || prev == '[');

            if (j < s.size() && s[j] == ']' && prev_is_value_starter) {
                out += "[]";
                i = j;
                continue;
            }
        }

        out += s[i];
    }
    return out;
}
std::string bst_diagram(const std::string& input) {
    std::string s = collapse_inline_brackets(input);

    struct Node {
        std::string val;
        std::vector<Node> children;
    };

    std::function<Node(const std::string&, size_t&)> parse_node;
    parse_node = [&](const std::string& str, size_t& pos) -> Node {
        Node n;
        std::string token;
        while (pos < str.size()) {
            char c = str[pos++];
            if (c == '(' || c == '[' || c == '{') {
                Node child = parse_node(str, pos);
                n.children.push_back(child);
            } else if (c == ')' || c == ']' || c == '}') {
                break;
            } else if (c == ',') {
                if (!token.empty()) {
                    n.children.push_back(Node{token});
                    token.clear();
                }
            } else {
                token += c;
            }
        }
        if (!token.empty()) n.val = token;
        return n;
    };

    size_t idx = 0;
    Node root = parse_node(s, idx);

    struct ASCIINode {
        std::vector<std::string> lines;
        int width = 0;
        int height = 0;
        int middle = 0;
    };

    std::function<ASCIINode(const Node&)> build;
    build = [&](const Node& n) -> ASCIINode {
        ASCIINode res;
        res.lines.push_back(n.val);
        res.width = n.val.size();
        res.height = 1;
        res.middle = res.width / 2;

        if (n.children.empty()) return res;

        std::vector<ASCIINode> child_nodes;
        int total_width = 0;
        for (const auto& c : n.children) {
            ASCIINode cn = build(c);
            child_nodes.push_back(cn);
            total_width += cn.width;
        }
        total_width += (int)(n.children.size() - 1) * 2;

        res.width = std::max(res.width, total_width);
        res.height = 1;
        std::string connector(res.width, ' ');
        int x = 0;
        for (size_t i = 0; i < child_nodes.size(); i++) {
            int cmid = x + child_nodes[i].middle;
            if (cmid < res.middle)
                connector[cmid] = '/';
            else if (cmid > res.middle)
                connector[cmid] = '\\';
            x += child_nodes[i].width + 2;
        }

        res.lines.push_back(connector);
        res.height++;

        int max_child_height = 0;
        for (auto& c : child_nodes) max_child_height = std::max(max_child_height, (int)c.lines.size());

        for (int i = 0; i < max_child_height; i++) {
            std::string line(res.width, ' ');
            int pos = 0;
            for (size_t j = 0; j < child_nodes.size(); j++) {
                ASCIINode& c = child_nodes[j];
                std::string part = (i < (int)c.lines.size()) ? c.lines[i] : std::string(c.width, ' ');
                for (int k = 0; k < (int)part.size(); k++) line[pos + k] = part[k];
                pos += c.width + 2;
            }
            res.lines.push_back(line);
            res.height++;
        }

        return res;
    };

    ASCIINode diagram = build(root);
    std::ostringstream out;
    for (auto& l : diagram.lines) out << l << "\n";
    return out.str();
}

std::string indent_ast(const std::string& input) {
    std::string s = collapse_inline_brackets(input);

    std::string out;
    int indent = 0;
    bool new_line = true;

    auto add_indent = [&]() {
        for (int i = 0; i < indent; ++i) out += "    ";
    };

    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];

        if (new_line) {
            add_indent();
            new_line = false;
        }
        if (s[i] == '[' && i + 1 < s.size() && s[i + 1] == ']') {
            out += "[]";
            i++;
            continue;
        } else if (c == '{' || c == '[') {
            out += c;
            out += '\n';
            indent++;
            new_line = true;
        } else if (c == '}' || c == ']') {
            out += '\n';
            indent = std::max(0, indent - 1);
            new_line = true;
            add_indent();
            out += c;
        } else if (c == ',') {
            out += c;
            out += '\n';
            new_line = true;
        } else {
            out += c;
        }
    }

    out += '\n';
    return out;
}
std::string asciiTreeAST(const std::string& input) {
    std::string s = collapse_inline_brackets(input);

    std::string out;
    std::vector<bool> lastChildStack;
    int indent = 0;
    bool new_line = true;

    for (size_t i = 0; i < s.size(); ++i) {
        if (new_line) {
            while (i < s.size() && std::isspace((unsigned char)s[i])) i++;
            if (i >= s.size()) break;

            for (int j = 0; j < indent; ++j) out += lastChildStack[j] ? "    " : "│   ";

            out += (lastChildStack.empty() || !lastChildStack.back()) ? "├─ " : "└─ ";

            new_line = false;
        }

        if (s[i] == '[' && i + 1 < s.size() && s[i + 1] == ']') {
            out += "[]";
            i++;
            continue;
        }

        char c = s[i];

        if (c == '{' || c == '[') {
            out += '\n';
            indent++;
            lastChildStack.push_back(false);
            new_line = true;
        } else if (c == '}' || c == ']') {
            out += '\n';
            indent = std::max(0, indent - 1);
            if (!lastChildStack.empty()) lastChildStack.pop_back();
            new_line = true;
        } else if (c == ',') {
            out += '\n';
            new_line = true;
        } else {
            out += c;
        }
    }

    out += '\n';
    return out;
}
std::string removeExtension(const std::string& filename) {
    size_t lastDot = filename.find_last_of('.');
    if (lastDot == std::string::npos) { return filename; }
    return filename.substr(0, lastDot);
}
int emitObjectFile(llvm::Module& M, const std::string& outputPath, bool debug) {
#ifdef __EMSCRIPTEN__
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmPrinters();
    llvm::InitializeAllAsmParsers();
    llvm::Triple triple("wasm32-unknown-unknown");
    M.setTargetTriple(triple);
    std::string err;
    const llvm::Target* target = llvm::TargetRegistry::lookupTarget(triple, err);
    if (!target) {
        llvm::errs() << "Target error: " << err << "\n";
        return 1;
    }
    llvm::TargetOptions opt;
    if (debug) opt.DebuggerTuning = llvm::DebuggerKind::GDB;
    auto RM = llvm::Reloc::PIC_;
    llvm::TargetMachine* TM = target->createTargetMachine(triple, "generic", "", opt, RM);
    M.setDataLayout(TM->createDataLayout());
    std::error_code EC;
    llvm::raw_fd_ostream dest(outputPath, EC, llvm::sys::fs::OF_None);
    if (EC) {
        llvm::errs() << "Could not open file: " << EC.message() << "\n";
        return 1;
    }
    llvm::legacy::PassManager PM;
    if (TM->addPassesToEmitFile(PM, dest, nullptr, llvm::CodeGenFileType::WasmObjectFile)) {
        llvm::errs() << "TargetMachine cannot emit file\n";
        return 1;
    }
    PM.run(M);
    delete TM;
    return 0;
#else
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmPrinters();
    llvm::InitializeAllAsmParsers();
    llvm::Triple triple(llvm::sys::getDefaultTargetTriple());
    M.setTargetTriple(triple);
    std::string err;
    const llvm::Target* target = llvm::TargetRegistry::lookupTarget(triple, err);
    if (!target) {
        llvm::errs() << "Target error: " << err << "\n";
        return 1;
    }
    llvm::TargetOptions opt;
    if (debug) opt.DebuggerTuning = llvm::DebuggerKind::GDB;
    auto RM = llvm::Reloc::PIC_;
    llvm::TargetMachine* TM = target->createTargetMachine(triple, "generic", "", opt, RM);
    M.setDataLayout(TM->createDataLayout());
    std::error_code EC;
    llvm::raw_fd_ostream dest(outputPath, EC, llvm::sys::fs::OF_None);
    if (EC) {
        llvm::errs() << "Could not open file: " << EC.message() << "\n";
        return 1;
    }
    llvm::legacy::PassManager PM;
    if (TM->addPassesToEmitFile(PM, dest, nullptr, llvm::CodeGenFileType::ObjectFile)) {
        llvm::errs() << "TargetMachine cannot emit file\n";
        return 1;
    }
    PM.run(M);
    delete TM;
    return 0;
#endif
}
Mer run(std::string file, std::string text, RunConfig config = {}) {
    // Check for inline directives
    if (text.find("// @no-context") != std::string::npos) { config.use_context = false; }

    if (text.find("// @looser-types") != std::string::npos) { config.looser_types = true; }

    if (text.find("// @print-ast") != std::string::npos) { config.print_ast = true; }

    if (text.find("// @print-tokens") != std::string::npos) { config.print_tokens = true; }

    if (text.find("// @show-time") != std::string::npos) { config.show_time = true; }

    if (text.find("// @quiet") != std::string::npos) { config.quiet_mode = true; }
    if (text.find("// @raw-ast") != std::string::npos) {
        config.raw = true;
        config.print_ast = true;
    }
    if (text.find("// @bst-ast") != std::string::npos) {
        config.bst = true;
        config.print_ast = true;
    }
    loose = config.looser_types;
    std::unordered_map<std::string, std::string> cleaned_files;
    std::unordered_set<std::string> visited;
    std::vector<std::string> queue = {file};
    std::unordered_map<std::string, std::string> raw_file_contents;
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> file_included_namespaces;
    raw_file_contents[file] = text;
    std::unordered_map<std::string, std::unordered_set<std::string>> fileAccessibleNamespaces;
    auto start = std::chrono::high_resolution_clock::now();
    try {
        while (!queue.empty()) {
            std::string current_file = queue.back();
            queue.pop_back();
            if (visited.count(current_file)) { continue; }
            visited.insert(current_file);
            std::string current_text;
            if (raw_file_contents.count(current_file)) {
                current_text = raw_file_contents[current_file];
            } else {
                std::ifstream infile(current_file);
                if (!infile.is_open()) {
                    return Mer{
                        Aer{nullptr, nullptr},
                        Ler{std::vector<Token>{}, new InvalidSyntaxError("QC-IX01: Include Error: Could not open " + current_file, Position())}, ""};
                }
                std::stringstream buffer;
                buffer << infile.rdbuf();
                current_text = buffer.str();
            }
            bool saved_no_main = no_main;
            auto outputofdeps = preprocess_includes(current_text, current_file);
            if (!(current_file == file)) { no_main = saved_no_main; }
            cleaned_files[current_file] = outputofdeps.clean_source;
            fileAccessibleNamespaces[current_file] = outputofdeps.accessible_namespaces;
            file_included_namespaces[current_file] = outputofdeps.included_namespaces;
            for (const std::string& dep_path : outputofdeps.dependency_paths) {
                if (!visited.count(dep_path)) { queue.push_back(dep_path); }
            }
        }
    } catch (std::runtime_error& e) {
        return Mer{Aer{nullptr, nullptr},
                   Ler{std::vector<Token>{}, new InvalidSyntaxError(std::string("QC-IX01: Include Error: ") + e.what(), Position())}, ""};
    }
    std::unordered_map<std::string, Aer> file_asts;
    std::unordered_map<std::string, std::unordered_map<std::string, UserTypeInfo>> type_registry;
    Ler resp;
    std::function<void(const std::string&)> process_file = [&](const std::string& path) {
        if (file_asts.count(path)) return;
        auto& deps = file_included_namespaces[path];
        for (auto const& [dep_path, ns_list] : deps) { process_file(dep_path); }
        std::unordered_map<std::string, UserTypeInfo> visible_types;
        for (auto const& [dep_path, ns_list] : deps) {
            auto& dep_types = type_registry[dep_path];
            for (const std::string& ns : ns_list) {
                for (auto& [type_name, info] : dep_types) {
                    if (type_name.rfind(ns + "::", 0) == 0) { visible_types[type_name] = info; }
                }
            }
        }
        Lexer lexer(cleaned_files[path], path);
        Ler file_resp = lexer.make_tokens();
        Parser parser(file_resp.Tkns, visible_types);
        bool saved_no_main = no_main;
        no_main = ((path == file) ? no_main : true);
        Aer ast = parser.parse();
        no_main = saved_no_main;
        type_registry[path] = ast.user_types;
        file_asts[path] = ast;
        if (path == file) { resp = file_resp; }
    };
    try {
        process_file(file);
    } catch (InvalidSyntaxError& e) {
        std::cout << '\n' << e.as_string() << '\n';
        return Mer{Aer{nullptr, nullptr}, resp, ""};
    }
    Aer ast = file_asts[file];
    if (config.print_tokens) {
        std::cout << "=== TOKENS ===" << std::endl;
        for (const auto& tok : resp.Tkns) { std::cout << "Type: " << get_token_name(tok.type) << " | Value: '" << tok.value << "'" << std::endl; }
        std::cout << "==============" << std::endl << std::endl;
    }
    if (ast.error) { return Mer{ast, resp, ""}; }
    if (config.print_ast) {
        std::cout << "=== AST ===" << std::endl;
        for (const auto& [filepath, astd] : file_asts) {
            std::cout << "--- File: " << filepath << " ---" << std::endl;
            if (!astd.statements) {
                std::cout << "  (Empty AST)" << std::endl;
                continue;
            }
            for (const auto& stmt : astd.statements->statements) {
                if (config.raw) {
                    std::cout << indent_ast(printAny(stmt));
                } else if (config.bst) {
                    std::cout << bst_diagram(printAny(stmt));
                } else {
                    std::cout << asciiTreeAST(printAny(stmt));
                }
            }
        }
        std::cout << "===========" << std::endl << std::endl;
    }
    try {
        // compiler
#ifdef ENABLE_LLVM
        if (config.compile_mode) {
            llvm::LLVMContext context;
            auto master_module = new llvm::Module("master_module", context);
            llvm::StringRef irString(_binary_runtime_ll_start, _binary_runtime_ll_size);
            llvm::SMDiagnostic err;
            llvm::MemoryBufferRef bufRef(irString, "runtime.ll");
            auto modulePtr = llvm::parseIR(bufRef, err, context);
            if (!modulePtr) { throw "Failed to load runtime.ll"; }
            if (llvm::Linker::linkModules(*master_module, std::move(modulePtr))) { throw "Failed to link runtime module"; }
            std::unordered_map<std::string, std::unordered_map<std::string, FunctionSignature>> db_sigs;
            std::unordered_map<std::string, std::unordered_map<std::string, FuncDefNode*>> db_fDefs;
            std::unordered_map<std::string, std::unordered_map<std::string, std::pair<int, int>>> db_jagged;
            std::unordered_map<std::string, std::unordered_map<std::string, std::string>> db_typeStrings;
            std::unordered_map<std::string, std::unordered_map<std::string, int>> db_lists;
            std::unordered_map<std::string, std::unordered_map<std::string, int>> db_lengths;
            std::unordered_map<std::string, std::unordered_map<std::string, std::pair<int, int>>> db_maps;
            std::unordered_map<std::string, std::unordered_map<std::string, std::string>> db_vars;
            std::unordered_map<std::string, std::unordered_map<std::string, llvm::AllocaInst*>> db_allocas;
            std::unordered_map<std::string, std::unordered_map<std::string, llvm::FunctionType*>> db_lambdas;
            std::unordered_map<std::string, std::unordered_map<std::string, llvm::GlobalVariable*>> db_globals;
            std::unordered_map<std::string, std::map<std::string, std::map<std::string, llvm::Function*>>> db_specialized;
            std::vector<std::string> sorted_files;
            std::unordered_set<std::string> sort_visited;
            std::function<void(const std::string&)> sort_visit = [&](const std::string& p) {
                if (sort_visited.count(p)) return;
                for (auto const& [dep_p, ns_list] : file_included_namespaces[p]) { sort_visit(dep_p); }
                sort_visited.insert(p);
                sorted_files.push_back(p);
            };
            sort_visit(file);
            std::vector<Diagnostic> diagnostics;
            for (auto& filepath : sorted_files) {
                std::unordered_map<std::string, FunctionSignature> visSigs;
                std::unordered_map<std::string, FuncDefNode*> visFDefs;
                std::unordered_map<std::string, std::pair<int, int>> visJagged;
                std::unordered_map<std::string, std::string> visTypeStr;
                std::unordered_map<std::string, int> visLists;
                std::unordered_map<std::string, int> visLen;
                std::unordered_map<std::string, std::pair<int, int>> visMaps;
                std::unordered_map<std::string, std::string> visVars;
                std::unordered_map<std::string, llvm::AllocaInst*> visAlloc;
                std::unordered_map<std::string, llvm::GlobalVariable*> visGlobals;
                std::unordered_map<std::string, llvm::FunctionType*> visLamb;
                std::map<std::string, std::map<std::string, llvm::Function*>> visSpec;
                for (auto const& [dep_p, ns_list] : file_included_namespaces[filepath]) {
                    if (db_sigs.find(dep_p) == db_sigs.end()) continue;
                    for (const std::string& ns : ns_list) {
                        if (ns.empty()) continue;
                        auto pre = ns + "::";
                        auto& d_sigs = db_sigs.at(dep_p);
                        auto& d_fDefs = db_fDefs.at(dep_p);
                        auto& d_jagged = db_jagged.at(dep_p);
                        auto& d_typeStr = db_typeStrings.at(dep_p);
                        auto& d_lists = db_lists.at(dep_p);
                        auto& d_len = db_lengths.at(dep_p);
                        auto& d_maps = db_maps.at(dep_p);
                        auto& d_vars = db_vars.at(dep_p);
                        auto& d_allocs = db_allocas.at(dep_p);
                        auto& d_lambs = db_lambdas.at(dep_p);
                        auto& d_spec = db_specialized.at(dep_p);
                        auto& d_globals = db_globals.at(dep_p);
                        for (auto const& [k, v] : d_sigs)
                            if (k.rfind(pre, 0) == 0) visSigs[k] = v;
                        for (auto const& [k, v] : d_fDefs)
                            if (k.rfind(pre, 0) == 0) visFDefs[k] = v;
                        for (auto const& [k, v] : d_jagged)
                            if (k.rfind(pre, 0) == 0) visJagged[k] = v;
                        for (auto const& [k, v] : d_typeStr)
                            if (k.rfind(pre, 0) == 0) visTypeStr[k] = v;
                        for (auto const& [k, v] : d_lists)
                            if (k.rfind(pre, 0) == 0) visLists[k] = v;
                        for (auto const& [k, v] : d_len)
                            if (k.rfind(pre, 0) == 0) visLen[k] = v;
                        for (auto const& [k, v] : d_maps)
                            if (k.rfind(pre, 0) == 0) visMaps[k] = v;
                        for (auto const& [k, v] : d_vars)
                            if (k.rfind(pre, 0) == 0) visVars[k] = v;
                        for (auto const& [k, v] : d_allocs)
                            if (k.rfind(pre, 0) == 0) visAlloc[k] = v;
                        for (auto const& [k, v] : d_lambs)
                            if (k.rfind(pre, 0) == 0) visLamb[k] = v;
                        for (auto const& [k, v] : d_globals)
                            if (k.rfind(pre, 0) == 0) visGlobals[k] = v;
                        if (d_spec.count(ns)) { visSpec[ns] = d_spec.at(ns); }
                    }
                }
                LLVMCompiler comp(file_asts[filepath].user_types, master_module, context, filepath == file);
                std::vector<CTError> errs = comp.compile(file_asts[filepath].statements, visSigs, visFDefs, visJagged, visTypeStr, visLists, visLen,
                                                         visMaps, visVars, visAlloc, visLamb, visSpec, visGlobals);
                if (!errs.empty()) {
                    for (auto& err : errs) diagnostics.push_back({new RTError(err.details, err.pos), "Error"});
                    break;
                }
                db_sigs[filepath] = comp.functionSignatures;
                db_fDefs[filepath] = comp.functionDefs;
                db_jagged[filepath] = comp.jaggedArraysStack[0];
                db_typeStrings[filepath] = comp.arrayTypeStringsStack[0];
                db_lists[filepath] = comp.listsStack[0];
                db_lengths[filepath] = comp.arrayLengthsStack[0];
                db_maps[filepath] = comp.mapsStack[0];
                db_vars[filepath] = comp.varTypesStack[0];
                db_allocas[filepath] = comp.runtimeArraySizes;
                db_lambdas[filepath] = comp.lambdaTypes;
                db_specialized[filepath] = comp.specializedFunctions;
                db_globals[filepath] = comp.globals;
            }
            std::string base_name = config.output_file.empty() ? "out" : removeExtension(config.output_file);
            size_t last_slash = base_name.find_last_of("/\\");
            std::string dir = (last_slash == std::string::npos) ? "" : base_name.substr(0, last_slash + 1);
            std::string stem = (last_slash == std::string::npos) ? base_name : base_name.substr(last_slash + 1);

            std::string ll_file = config.compile_only ? base_name + ".ll" : dir + "temp_" + stem + ".ll";
            std::string obj_file = config.object_only ? base_name + ".o" : dir + "temp_" + stem + ".o";
            auto end = std::chrono::high_resolution_clock::now();
            bool error_found = false;
            if (!diagnostics.empty()) { error_found = true; }
            std::string message = "Program exited with code: 0";
            if (error_found) { message = "Program exited with code: 1"; }

            if (!diagnostics.empty()) { return Mer{ast, resp, message, diagnostics}; }
            std::error_code EC;
            llvm::raw_fd_ostream out(ll_file, EC, llvm::sys::fs::OF_Text);
            if (EC) {
                llvm::errs() << "Failed to open output: " << EC.message() << "\n";
                message = "Program exited with code: 1";
                return Mer{ast, resp, message, diagnostics};
            }
            for (llvm::Function& F : master_module->functions()) {
                if (F.getName().starts_with("qc_")) { F.setLinkage(llvm::GlobalValue::InternalLinkage); }
            }
#ifndef __EMSCRIPTEN__
            if (config.optimize) {
                llvm::PassBuilder PB;
                llvm::LoopAnalysisManager LAM;
                llvm::FunctionAnalysisManager FAM;
                llvm::CGSCCAnalysisManager CGAM;
                llvm::ModuleAnalysisManager MAM;
                PB.registerModuleAnalyses(MAM);
                PB.registerCGSCCAnalyses(CGAM);
                PB.registerFunctionAnalyses(FAM);
                PB.registerLoopAnalyses(LAM);
                PB.crossRegisterProxies(LAM, FAM, CGAM, MAM);
                llvm::ModulePassManager MPM;
                auto optimization_level = llvm::OptimizationLevel::O2;
                switch (config.opt_level[1]) {
                case '0': optimization_level = llvm::OptimizationLevel::O0; break;
                case '1': optimization_level = llvm::OptimizationLevel::O1; break;
                case '2': optimization_level = llvm::OptimizationLevel::O2; break;
                case '3': optimization_level = llvm::OptimizationLevel::O3; break;
                case 'z': optimization_level = llvm::OptimizationLevel::Oz; break;
                default: optimization_level = llvm::OptimizationLevel::O2; break;
                }
                MPM = PB.buildPerModuleDefaultPipeline(optimization_level);
                MPM.run(*master_module, MAM);
            }
#endif
            master_module->print(out, nullptr);
            if (config.compile_only) {
                message += ". Compiled to " + ll_file;
                return Mer{ast, resp, message, diagnostics};
            }
            int llc_result = emitObjectFile(*master_module, obj_file, config.debug);
            if (llc_result != 0) {
                diagnostics.push_back({new RTError("Failed to compile IR to object file", Position("", "", 0, 0, 0)), "Error"});
                return Mer{ast, resp, message, diagnostics};
            }
            if (config.object_only) {
                std::remove(ll_file.c_str());
                message += ". Compiled to " + obj_file;
                return Mer{ast, resp, message, diagnostics};
            }
            std::string final_exe = config.output_file.empty() ? "a.out" : config.output_file;
            std::string link_cmd = "gcc " + obj_file + " -o " + final_exe + " -lm";
            if (config.debug) link_cmd += " -g";
            int link_result = system(link_cmd.c_str());
            if (link_result != 0) {
                diagnostics.push_back({new RTError("Failed to link object file", Position("", "", 0, 0, 0)), "Error"});
                return Mer{ast, resp, message, diagnostics};
            }
            std::remove(ll_file.c_str());
            std::remove(obj_file.c_str());

            message += ". Built executable: " + final_exe;
            if (config.quiet_mode) message = "";
            return Mer{ast, resp, message, diagnostics};
        }
#endif
    } catch (const char* err) { std::cout << err << '\n'; } catch (...) {
        std::cout << "unknown error" << '\n';
    }
    return Mer{ast, resp, "", std::vector<Diagnostic>{}};
}

//////////////////////////////////////////////////////////////////////////////////////////////
// LEXER
// ////////////////////////////////////////////////////////////////////////////////////
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
    if (this->pos.index < this->text.length()) {
        this->current_char = this->text[this->pos.index];
    } else {
        this->current_char = '\0';
    }
}
Token Lexer::make_number() {
    Position start_pos = this->pos.copy();
    std::string num = "";
    int dot_count = 0;
    bool is_float = false;
    bool is_octal = false;
    bool is_binary = false;
    bool is_hex = false;
    if (this->current_char == '0') {
        switch (this->text[this->pos.index + 1]) {
        case 'x':
        case 'X':
            is_hex = true;
            this->advance();
            this->advance();
            break;
        case 'o':
        case 'O':
            is_octal = true;
            this->advance();
            this->advance();
            break;
        case 'b':
        case 'B':
            is_binary = true;
            this->advance();
            this->advance();
            break;
        }
    }
    if (is_hex) {
        while (this->current_char != '\0' && isCharInSet(this->current_char, DIGITS + "abcdefABCDEF")) {
            num += this->current_char;
            this->advance();
        }
        unsigned long long val = std::stoull(num, nullptr, 16);
        return Token(TokenType::ADDR_T, std::to_string(val), start_pos);
    } else if (is_octal) {
        while (this->current_char != '\0' && std::isdigit(this->current_char) && this->current_char - '0' < 8) {
            num += this->current_char;
            this->advance();
        }
        unsigned long long val = std::stoull(num, nullptr, 8);
        return Token(TokenType::ADDR_T, std::to_string(val), start_pos);
    } else if (is_binary) {
        while (this->current_char != '\0' && std::isdigit(this->current_char) && this->current_char - '0' < 2) {
            num += this->current_char;
            this->advance();
        }
        unsigned long long val = std::stoull(num, nullptr, 2);
        return Token(TokenType::ADDR_T, std::to_string(val), start_pos);
    } else {
        while (this->current_char != '\0' && isCharInSet(this->current_char, DIGITS + ".f")) {
            if (this->current_char == '.') {
                if (dot_count == 1 || is_hex || is_binary || is_octal) {
                    this->advance();
                    break;
                }
                dot_count++;
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
    }
    if (dot_count == 1) {
        if (is_float) { return Token(TokenType::FLOAT, num, start_pos); }
        return Token(TokenType::DOUBLE, num, start_pos);
    }
    return Token(TokenType::INT, num, start_pos);
}
Token Lexer::make_identifier() {
    std::string id = "";
    Position start_pos = this->pos.copy();
    while (this->current_char != '\0' && (isalnum(this->current_char) || this->current_char == '_')) {
        id += this->current_char;
        this->advance();
    }
    if (id == "int" || id == "float" || id == "double" || id == "bool" || id == "case" || id == "string" || id == "qbool" || id == "void" ||
        id == "char" || id == "break" || id == "if" || id == "else" || id == "while" || id == "for" || id == "switch" || id == "return" ||
        id == "qif" || id == "qelse" || id == "qelif" || id == "qswitch" || id == "const" || id == "default" || id == "class" || id == "struct" ||
        id == "enum" || id == "long" || id == "short" || id == "fn" || id == "continue" || id == "auto" || id == "list" || id == "foreach" ||
        id == "do" || id == "in" || id == "map" || id == "type" || id == "foreign" || id == "public" || id == "protected" || id == "private" ||
        id == "extern" || id == "function" || id == "namespace" || id == "keyword" || id == "operator" || id == "abstract" || id == "final" ||
        id == "try" || id == "catch" || id == "nullptr" || id == "addr_t") {
        return Token(TokenType::KEYWORD, id, start_pos);
    }
    if (id == "true" || id == "false") { return Token(TokenType::BOOL, id, start_pos); }
    if (id == "qtrue" || id == "qfalse" || id == "both" || id == "none") { return Token(TokenType::QBOOL, id, start_pos); }
    if (id == "sizeof") { return Token(TokenType::SIZEOF, id, start_pos); }
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
        throw IllegalCharError("QC-IC01: Expected \"", this->pos);
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
        case 'n': val = "\n"; break;
        case 't': val = "\t"; break;
        case 'r': val = "\r"; break;
        case '\'': val = "\'"; break;
        case '\\': val = "\\"; break;
        default: val = std::string(1, this->current_char); break;
        }
        this->advance();
    } else {
        val = std::string(1, this->current_char);
        this->advance();
    }
    if (this->current_char != '\'') { throw IllegalCharError("QC-IC01: Expected closing single quote", this->pos); }
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
                if (this->current_char == '{')
                    brace_depth++;
                else if (this->current_char == '}')
                    brace_depth--;

                if (brace_depth > 0) expr += this->current_char;

                this->advance();
            }

            if (brace_depth != 0) throw IllegalCharError("QC-IC02: Unclosed brace in f-string", this->pos);

            exprs.push_back(expr);
        } else {
            current += this->current_char;
            this->advance();
        }
    }

    parts.push_back(current);

    if (this->current_char != '"') throw IllegalCharError("QC-IC02: Unterminated f-string", this->pos);
    this->advance();
    std::string encoded = "";
    for (size_t i = 0; i < parts.size(); i++) {
        encoded += parts[i];
        if (i < exprs.size()) encoded += "\x01" + exprs[i] + "\x01";
    }
    return Token(TokenType::FSTRING, encoded, start_pos);
}
Token Lexer::make_raw_string() {
    Position start_pos = this->pos.copy();
    std::string start_delim = "\"";
    this->advance();
    while (this->current_char != '\0' && this->current_char != '(' && this->current_char != '\\' && this->current_char != ' ') {
        start_delim += this->current_char;
        this->advance();
    }
    start_delim += '(';
    this->advance();
    std::string end_marker = start_delim;
    std::reverse(end_marker.begin(), end_marker.end());
    for (char& c : end_marker) {
        if (c == '(')
            c = ')';
        else if (c == ')')
            c = '(';
        else if (c == '[')
            c = ']';
        else if (c == ']')
            c = '[';
        else if (c == '{')
            c = '}';
        else if (c == '}')
            c = '{';
        else if (c == '<')
            c = '>';
        else if (c == '>')
            c = '<';
    }
    std::string value = "";
    while (this->current_char != '\0') {
        value += this->current_char;
        this->advance();
        if (value.ends_with(end_marker)) {
            value = value.substr(0, value.length() - end_marker.length());
            break;
        }
    }
    return Token(TokenType::STRING, value, start_pos);
}
Ler Lexer::make_tokens() {
    std::vector<Token> tokens;
    tokens.reserve(256);
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
            continue;
        } else if (this->current_char == 'R' && this->text[this->pos.index + 1] == '"') {
            this->advance();
            tokens.push_back(this->make_raw_string());
            continue;
        } else if (isCharInSet(this->current_char, LETTERS + "_")) {
            tokens.push_back(this->make_identifier());
        } else if (this->current_char == '"') {
            tokens.push_back(this->make_string());
            continue;
        } else if (this->current_char == '\'') {
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
                    tokens.push_back(Token(TokenType::PLUS, "+", start_pos));
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
                } else if (current_char == '>') {
                    this->advance();
                    tokens.push_back(Token(TokenType::ARROW, "->", start_pos));
                } else {
                    tokens.push_back(Token(TokenType::MINUS, "-", start_pos));
                }
                break;
            case '*':
                this->advance();
                if (current_char == '=') {
                    this->advance();
                    tokens.push_back(Token(TokenType::MUL_EQ, "*=", start_pos));
                } else {
                    tokens.push_back(Token(TokenType::MUL, "*", start_pos));
                    break;
                }
                break;
            case '/':
                this->advance();
                if (this->current_char == '/') {
                    while (this->current_char != '\0' && this->current_char != '\n') { this->advance(); }
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
                    tokens.push_back(Token(TokenType::DIV, "/", start_pos));
                }
                break;
            case '=':
                this->advance();
                if (current_char == '=') {
                    this->advance();
                    if (current_char == '=') {
                        this->advance();
                        tokens.push_back(Token(TokenType::QEQEQ, "===", start_pos));
                    } else {
                        tokens.push_back(Token(TokenType::EQ_TO, "==", start_pos));
                    }
                } else {
                    tokens.push_back(Token(TokenType::EQ, "=", start_pos));
                    break;
                }
                break;
            case '!':
                this->advance();
                if (current_char == '=') {
                    this->advance();
                    if (current_char == '=') {
                        this->advance();
                        tokens.push_back(Token(TokenType::QNEQ, "!==", start_pos));
                    } else {
                        tokens.push_back(Token(TokenType::NOT_EQ, "!=", start_pos));
                    }
                } else if (current_char == '!') {
                    this->advance();
                    tokens.push_back(Token(TokenType::QNOT, "!!", start_pos));
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
                } else if (this->current_char == '>') {
                    this->advance();
                    if (this->current_char == '>') {
                        this->advance();
                        tokens.push_back(Token(TokenType::R_ROT, ">>>", start_pos));
                    } else {
                        tokens.push_back(Token(TokenType::RSHIFT, ">>", start_pos));
                    }
                } else {
                    tokens.push_back(Token(TokenType::MORE, ">", start_pos));
                    break;
                }
                break;
            case '<':
                this->advance();
                if (current_char == '<') {
                    this->advance();
                    if (current_char == '<') {
                        this->advance();
                        tokens.push_back(Token(TokenType::L_ROT, "<<<", start_pos));
                    } else {
                        tokens.push_back(Token(TokenType::LSHIFT, "<<", start_pos));
                    }
                } else if (current_char == '=') {
                    this->advance();
                    tokens.push_back(Token(TokenType::LESS_EQ, "<=", start_pos));
                } else {
                    tokens.push_back(Token(TokenType::LESS, "<", start_pos));
                    break;
                }
                break;
            case '(':
                tokens.push_back(Token(TokenType::LPAREN, "(", start_pos));
                this->advance();
                break;
            case ')':
                tokens.push_back(Token(TokenType::RPAREN, ")", start_pos));
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
            case '[':
                tokens.push_back(Token(TokenType::LBRACKET, "[", start_pos));
                this->advance();
                break;
            case ']':
                tokens.push_back(Token(TokenType::RBRACKET, "]", start_pos));
                this->advance();
                break;
            case '%':
                this->advance();
                if (current_char == '=') {
                    this->advance();
                    tokens.push_back(Token(TokenType::MOD_EQ, "%=", start_pos));
                } else {
                    tokens.push_back(Token(TokenType::MOD, "%", start_pos));
                    break;
                }
                break;
            case '&':
                this->advance();
                if (current_char == '&') {
                    this->advance();
                    if (current_char == '&') {
                        this->advance();
                        tokens.push_back(Token(TokenType::QAND, "&&&", start_pos));
                    } else {
                        tokens.push_back(Token(TokenType::AND, "&&", start_pos));
                    }
                } else if (this->current_char == '|') {
                    this->advance();
                    if (this->current_char == '&') {
                        this->advance();
                        tokens.push_back(Token(TokenType::COLLAPSE_AND, "&|&", start_pos));
                    }
                } else {
                    tokens.push_back(Token(TokenType::AMPERSAND, "&", start_pos));
                    break;
                }
                break;
            case '|':
                this->advance();
                if (current_char == '|') {
                    this->advance();
                    if (current_char == '|') {
                        this->advance();
                        tokens.push_back(Token(TokenType::QOR, "|||", start_pos));
                    } else {
                        tokens.push_back(Token(TokenType::OR, "||", start_pos));
                    }
                } else if (this->current_char == '&') {
                    this->advance();
                    if (this->current_char == '|') {
                        this->advance();
                        tokens.push_back(Token(TokenType::COLLAPSE_OR, "|&|", start_pos));
                    }
                } else {
                    tokens.push_back(Token(TokenType::PIPE, "|", start_pos));
                    break;
                }
                break;
            case '@':
                this->advance();
                tokens.push_back(Token(TokenType::AT, "@", start_pos));
                break;
            case '^':
                this->advance();
                if (current_char == '^') {
                    this->advance();
                    tokens.push_back(Token(TokenType::QXOR, "^^", start_pos));
                } else {
                    tokens.push_back(Token(TokenType::XOR, "^", start_pos));
                }
                break;
            case '#':
                this->advance();
                if (current_char == '^') {
                    this->advance();
                    tokens.push_back(Token(TokenType::POWER, "#^", start_pos));
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
                } else if (current_char == '>') {
                    this->advance();
                    tokens.push_back(Token(TokenType::LOGICAL_RSHIFT, ":>", start_pos));
                    break;
                } else {
                    tokens.push_back(Token(TokenType::COLON, ":", start_pos));
                }
                break;
            case ';':
                tokens.push_back(Token(TokenType::SEMICOLON, ";", start_pos));
                this->advance();
                break;
            case '.':
                this->advance();
                if (this->current_char == '.') {
                    this->advance();
                    if (this->current_char == '.') {
                        this->advance();
                        tokens.push_back(Token(TokenType::VARADIC, "...", start_pos));
                        break;
                    }
                }
                tokens.push_back(Token(TokenType::DOT, ".", start_pos));
                break;
            case '$':
                tokens.push_back(Token(TokenType::BITWISE_XOR, "$", start_pos));
                this->advance();
                break;
            case '~':
                tokens.push_back(Token(TokenType::BITWISE_NOT, "~", start_pos));
                this->advance();
                break;
            default:
                std::string unknown = std::string(1, this->current_char);
                return Ler{std::vector<Token>(), new IllegalCharError("QC-IC03:" + unknown, this->pos)};
            }
        }
    }
    tokens.push_back(Token(TokenType::EOFT, "<eof>", this->pos));
    return Ler{tokens, NULL};
}

} // namespace tkz
///////////////////////////////////////////////////////////////////////////////////////////
// PREPROCCESERS /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}
std::string resolve_path(const std::string& current_file, const std::string& include_path) {
    std::filesystem::path current(current_file);
    std::filesystem::path include(include_path);
    if (include.is_absolute()) { return include.string(); }
    std::filesystem::path resolved = current.parent_path() / include;
    return std::filesystem::weakly_canonical(resolved).string();
}
PreprocessResult preprocess_includes(const std::string& source, const std::string& current_file) {
    PreprocessResult res;
    res.accessible_namespaces.clear();
    res.accessible_namespaces.insert("Exported");
    res.accessible_namespaces.insert("");
    std::vector<std::string> dependencies;
    std::unordered_map<std::string, std::vector<std::string>> from_where;
    size_t ep_pos = source.find("#entrypoint");
    size_t nomain_pos = source.find("#nomain");
    if (ep_pos != std::string::npos) {
        bool in_string = false;
        for (size_t check = 0; check < ep_pos; check++) {
            if (source[check] == '"' && (check == 0 || source[check - 1] != '\\')) { in_string = !in_string; }
        }
        if (!in_string) {
            size_t line_end = source.find('\n', ep_pos);
            if (line_end == std::string::npos) line_end = source.size();
            std::string directive = source.substr(ep_pos + 12, line_end - ep_pos - 12);
            entrypointName = trim(directive);
        }
    }
    if (nomain_pos != std::string::npos) {
        bool in_string = false;
        for (size_t check = 0; check < nomain_pos; check++) {
            if (source[check] == '"' && (check == 0 || source[check - 1] != '\\')) { in_string = !in_string; }
        }
        if (!in_string) { no_main = true; }
    }
    size_t pos = 0;
    while ((pos = source.find("#include", pos)) != std::string::npos) {
        bool in_string = false;
        for (size_t check = 0; check < pos; check++) {
            if (source[check] == '"' && (check == 0 || source[check - 1] != '\\')) { in_string = !in_string; }
        }
        if (in_string) {
            pos++;
            continue;
        }
        size_t start = source.find('<', pos);
        size_t end = source.find('>', start);
        std::string directive = source.substr(start + 1, end - start - 1);
        std::vector<std::string> ns_names = {};
        size_t last_comma = directive.find_last_of(',');
        std::string path;
        if (last_comma == std::string::npos) {
            throw std::runtime_error("You cannot include just a path");
        } else {
            path = trim(directive.substr(last_comma + 1));
            std::string namespaces_part = directive.substr(0, last_comma);
            size_t segment_start = 0;
            size_t comma = namespaces_part.find(',', segment_start);
            while (comma != std::string::npos) {
                ns_names.push_back(trim(namespaces_part.substr(segment_start, comma - segment_start)));
                segment_start = comma + 1;
                comma = namespaces_part.find(',', segment_start);
            }
            ns_names.push_back(trim(namespaces_part.substr(segment_start)));
        }
        if (!path.empty() && path.front() == '"') { path = path.substr(1); }
        if (!path.empty() && path.back() == '"') { path = path.substr(0, path.size() - 1); }
        std::string full_path;
        if (path == "std") {
            const char* home = std::getenv("QC_STDLIB");
            if (!home) { throw std::runtime_error("QC_STDLIB environment variable not set"); }
            full_path = std::string(home);
        } else {
            full_path = resolve_path(current_file, path);
        }
        if (!from_where.contains(full_path)) { from_where[full_path] = std::vector<std::string>(); }
        for (std::string ns_name : ns_names) { from_where[full_path].push_back(ns_name); }
        dependencies.push_back(full_path);
        pos = end + 1;
    }
    std::string result = "";
    size_t last_pos = 0;
    pos = 0;
    while ((pos = source.find("#include", pos)) != std::string::npos) {
        bool in_string = false;
        for (size_t check = 0; check < pos; check++) {
            if (source[check] == '"' && (check == 0 || source[check - 1] != '\\')) { in_string = !in_string; }
        }
        if (in_string) {
            pos++;
            continue;
        }
        result += source.substr(last_pos, pos - last_pos);
        size_t end = source.find('>', pos);
        last_pos = end + 1;
        if (last_pos < source.size() && source[last_pos] == '\n') { last_pos++; }
        pos = last_pos;
    }
    result += source.substr(last_pos);
    pos = 0;
    while ((pos = result.find("#entrypoint", pos)) != std::string::npos) {
        bool in_str = false;
        for (size_t check = 0; check < pos; check++) {
            if (result[check] == '"' && (check == 0 || result[check - 1] != '\\')) { in_str = !in_str; }
        }
        if (!in_str) {
            size_t line_end = result.find('\n', pos);
            if (line_end == std::string::npos) line_end = result.size();
            result.erase(pos, line_end - pos + 1);
        } else {
            pos++;
        }
    }
    pos = 0;
    while ((pos = result.find("#nomain", pos)) != std::string::npos) {
        bool in_str = false;
        for (size_t check = 0; check < pos; check++) {
            if (result[check] == '"' && (check == 0 || result[check - 1] != '\\')) { in_str = !in_str; }
        }
        if (!in_str) {
            size_t line_end = result.find('\n', pos);
            if (line_end == std::string::npos) line_end = result.size();
            result.erase(pos, line_end - pos + 1);
        } else {
            pos++;
        }
    }
    res.clean_source = result;
    res.dependency_paths = dependencies;
    res.included_namespaces = from_where;
    return res;
}
