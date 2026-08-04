//////////////////////////////////////////////////////////////////////////////////////////////
// TOKENS
// ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
#define QC_EXCEPTION_CLASS 0x5143455843455054ULL
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
#include <llvm/Support/ModRef.h>
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
uint64_t invokeCounter = 0;
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
std::set<std::string> inProgressGenerics;
std::string strip(const std::string& s) {
    std::string r = s;
    size_t pos;
    while (r.size() >= 2 && r.substr(r.size() - 2) == "[]") r = r.substr(0, r.size() - 2);
    return r;
}
bool loose;
std::vector<std::string> to_link;
std::vector<std::string> to_link_dir;
std::unordered_map<std::string, std::string> aliases;
std::unordered_map<std::string, std::string> dir_aliases;
std::string entrypointName = "main";
extern "C" const char _binary_runtime_ll_start[];
extern "C" const size_t _binary_runtime_ll_size;
bool isHeader = false;
namespace tkz {
//////////////////////////////////////////////////////////////////////////////////////////////
// POSITION
// /////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
Position::Position() {
}
std::string Position::arrow_string(size_t context) const {
    if (Filetxt.empty() || index < 0 || index > Filetxt.size()) { return "\n"; }
    std::vector<std::string> lines;
    std::stringstream ss(Filetxt);
    std::string temp;
    while (std::getline(ss, temp)) { lines.push_back(temp); }
    size_t current = std::min<size_t>(line, lines.size() - 1);
    size_t first = (current >= context) ? current - context : 0;
    size_t last = std::min(current + context, lines.size() - 1);
    std::string result;
    size_t width = std::to_string(last + 1).size();
    for (size_t i = first; i <= last; i++) {
        std::string num = std::to_string(i + 1);
        result += "  ";
        result += std::string(width - num.size(), ' ');
        result += num;
        result += " | ";
        result += lines[i];
        result += "\n";
        if (i == current) {
            result += "  ";
            result += std::string(width, ' ');
            result += " | ";
            size_t col = column < 0 ? 0 : static_cast<size_t>(column);
            size_t len = length < 1 ? 1 : static_cast<size_t>(length);
            result += std::string(col, ' ');
            result += std::string(len, '^');
            result += "\n";
        }
    }
    return result;
}
Position::Position(std::string Filename, std::string Filetxt, size_t index, size_t line, size_t column) {
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
    case TokenType::BYTE: return "byte";
    case TokenType::NIBBLE: return "nibble";
    case TokenType::LONG_INT: return "long int";
    case TokenType::SHORT_INT: return "short int";
    case TokenType::LONG_DOUBLE: return "long double";
    case TokenType::FLOAT: return "float";
    case TokenType::DOUBLE: return "double";
    case TokenType::CHAR: return "char";
    case TokenType::BOOL: return "bool";
    case TokenType::QBOOL: return "qbool";
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
    case TokenType::RSHIFT: return "|>";
    case TokenType::R_ROT: return "|>>";
    case TokenType::L_ROT: return "<<<";
    case TokenType::BITWISE_XOR: return "$";
    case TokenType::BITWISE_NOT: return "~";
    case TokenType::LOGICAL_RSHIFT: return ":>";
    case TokenType::AT: return "@";
    case TokenType::PIPE: return "|";
    case TokenType::SIZEOF: return "sizeof";
    case TokenType::THROW: return "throw";
    case TokenType::EOFT: return "<eof>";
    case TokenType::VARADIC: return "...";
    case TokenType::RROT_EQ: return "|>>=";
    case TokenType::LROT_EQ: return "<<<=";
    case TokenType::LSH_EQ: return "<<=";
    case TokenType::RSH_EQ: return "|>=";
    case TokenType::LRSH_EQ: return ":>=";
    case TokenType::BIT_X_EQ: return "$=";
    case TokenType::BIT_A_EQ: return "&=";
    case TokenType::BIT_O_EQ: return "|=";
    default: return "<unknown token>";
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
    this->pos = pos;
}
std::string Error::as_string() {
    std::string result;
    result += "error";
    if (!this->error_name.empty()) { result += " " + this->error_name; }
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
            } else if constexpr (std::is_same_v<T, TypeValueNode>) {
                return TypeValueNode(arg.tok);
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
Position get_pos(AnyNode node) {
    return std::visit(
        [](auto& n) -> Position {
            if constexpr (requires { n.getPos(); }) {
                return n.getPos();
            } else if constexpr (requires { n->getPos(); }) {
                return n->getPos();
            } else {
                return Position("", "", 0, 0, 0);
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
            } else if constexpr (std::is_same_v<T, RefVarDeclNode>) {
                return arg.print();
            } else if constexpr (std::is_same_v<T, TypeValueNode>) {
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
            } else if constexpr (std::is_same_v<T, ArrayAssignNode*>) {
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
std::string TypeValueNode::print() const {
    return "(" + this->tok.print() + ")";
}
TypeValueNode::TypeValueNode(Token tok) {
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
            } else if constexpr (std::is_same_v<T, TypeValueNode>) {
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
            } else if constexpr (std::is_same_v<T, ArrayAssignNode*>) {
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
            } else if constexpr (std::is_same_v<T, ArrayAssignNode*>) {
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
                                                                            {"BOOL", TokenType::BOOL},
                                                                            {"QBOOL", TokenType::QBOOL},
                                                                            {"PLUS", TokenType::PLUS},
                                                                            {"R_ROT", TokenType::R_ROT},
                                                                            {"L_ROT", TokenType::L_ROT},
                                                                            {"RROT_EQ", TokenType::RROT_EQ},
                                                                            {"LROT_EQ", TokenType::LROT_EQ},
                                                                            {"RSH_EQ", TokenType::RSH_EQ},
                                                                            {"LSH_EQ", TokenType::LSH_EQ},
                                                                            {"LRSH_EQ", TokenType::LRSH_EQ},
                                                                            {"BIT_X_EQ", TokenType::BIT_X_EQ},
                                                                            {"BIT_A_EQ", TokenType::BIT_A_EQ},
                                                                            {"BIT_O_EQ", TokenType::BIT_O_EQ},
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
                                                                            {"THROW", TokenType::THROW},
                                                                            {"POWER", TokenType::POWER},
                                                                            {"LPAREN", TokenType::LPAREN},
                                                                            {"RPAREN", TokenType::RPAREN},
                                                                            {"SEMICOLON", TokenType::SEMICOLON},
                                                                            {"DEF", TokenType::DEF},
                                                                            {"INCREMENT", TokenType::INCREMENT},
                                                                            {"DECREMENT", TokenType::DECREMENT},
                                                                            {"IDENTIFIER", TokenType::IDENTIFIER},
                                                                            {"ADDR_T", TokenType::ADDR_T},
                                                                            {"BYTE", TokenType::BYTE},
                                                                            {"NIBBLE", TokenType::NIBBLE},
                                                                            {"LONG_DOUBLE", TokenType::LONG_DOUBLE},
                                                                            {"SHORT_INT", TokenType::SHORT_INT},
                                                                            {"LONG_INT", TokenType::LONG_INT},
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

    if (type == "short int") return AnyNode{NumberNode(Token(TokenType::SHORT_INT, "0", pos))};
    if (type == "int") return AnyNode{NumberNode(Token(TokenType::INT, "0", pos))};
    if (type == "long int") return AnyNode{NumberNode(Token(TokenType::LONG_INT, "0", pos))};

    if (type == "float") return AnyNode{NumberNode(Token(TokenType::FLOAT, "0.0f", pos))};
    if (type == "double") return AnyNode{NumberNode(Token(TokenType::DOUBLE, "0.0", pos))};
    if (type == "long double") return AnyNode{NumberNode(Token(TokenType::LONG_DOUBLE, "0.0", pos))};
    if (type == "addr_t") return AnyNode{NumberNode(Token(TokenType::ADDR_T, "0", pos))};
    if (type == "byte") return AnyNode{NumberNode(Token(TokenType::BYTE, "0", pos))};
    if (type == "nibble") return AnyNode{NumberNode(Token(TokenType::NIBBLE, "0", pos))};

    if (type == "string") return AnyNode{StringNode(Token(TokenType::STRING, "", pos))};
    if (type == "char") return AnyNode{CharNode(Token(TokenType::CHAR, std::string(1, '\0'), pos))};
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
        if (is_known_type(this->current_tok.value)) {
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

            init_node = AnyNode{new VarAssignNode(is_const, type_tok, var_name, value, this->in_foreign)};
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
    std::vector<TryCatchNode::CatchBody> catch_bodys;
    while (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "catch") {
        this->advance();
        if (this->current_tok.type != TokenType::LPAREN) {
            res.failure(new InvalidSyntaxError("QC-S032: Expected '(' after 'catch'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        if (this->current_tok.type != TokenType::KEYWORD && this->current_tok.type != TokenType::IDENTIFIER && this->current_tok.value != "...") {
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
        if (this->current_tok.type != TokenType::IDENTIFIER && catch_type != "...") {
            res.failure(new InvalidSyntaxError("QC-S034: Expected variable name in catch declaration", this->current_tok.pos));
            return res.to_prs();
        }
        std::string catch_var = "";
        if (catch_type != "...") {
            Token var_tok = this->current_tok;
            catch_var = var_tok.value;
            this->advance();
        }
        if (this->current_tok.type != TokenType::RPAREN) {
            res.failure(new InvalidSyntaxError("QC-S035: Expected ')' after catch variable", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        StatementsNode* catch_body;
        if (!parse_block_into(catch_body, res)) return res.to_prs();
        catch_bodys.push_back({catch_var, catch_type, catch_body});
    }
    if (catch_bodys.size() == 0) {
        res.failure(new InvalidSyntaxError("QC-S031: Expected 'catch' after try block", this->current_tok.pos));
        return res.to_prs();
    }
    auto try_catch_node = new TryCatchNode(try_body, catch_bodys, try_tok, try_tok.pos);
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
             this->current_tok.value == "string" || this->current_tok.value == "char" || this->current_tok.value == "addr_t" ||
             this->current_tok.value == "byte" || this->current_tok.value == "nibble")) {

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

            init = AnyNode{new VarAssignNode(is_const, type_tok, var_name, value, this->in_foreign)};
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
    std::string type = "";
    AnyNode length = std::monostate{};
    if (this->current_tok.type != TokenType::RBRACKET) {
        if (this->current_tok.type == TokenType::KEYWORD || is_known_type(this->current_tok.value)) {
            type = parseTypeString();
            if (this->current_tok.type != TokenType::COMMA) {
                res.failure(new InvalidSyntaxError("QC-S045: Expected ',' after element type in empty array literal.", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            length = res.reg(this->atom());
            if (res.error) return res.to_prs();
        } else {
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
    }

    if (this->current_tok.type != TokenType::RBRACKET) {
        res.failure(new InvalidSyntaxError("QC-S045: Expected ']' in array literal", this->current_tok.pos));
        return res.to_prs();
    }

    this->advance();
    ArrayLiteralNode* result = new ArrayLiteralNode(elements, start_pos);
    result->type = type;
    result->length = length;
    return res.success(result);
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

    if (tok.type == TokenType::INT || tok.type == TokenType::FLOAT || tok.type == TokenType::DOUBLE || tok.type == TokenType::ADDR_T ||
        tok.type == TokenType::BYTE || tok.type == TokenType::LONG_INT || tok.type == TokenType::SHORT_INT || tok.type == TokenType::LONG_DOUBLE ||
        tok.type == TokenType::NIBBLE) {
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
        bool generic_failed = false;
        while (true) {
            if (this->current_tok.type == TokenType::SCOPE) {
                this->advance();
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(new InvalidSyntaxError("QC-N001: Expected identifier or namespace name after '::'", this->current_tok.pos));
                    return res.to_prs();
                }
                name += "::" + this->current_tok.value;
                pos = this->current_tok.pos;
                this->advance();
            }
            if (this->current_tok.type == TokenType::LESS) {
                size_t oldId = this->index;
                std::string oldName = name;
                this->advance();
                name += "<";
                int depth = 1;
                if (this->current_tok.type == TokenType::MORE) {
                    name = oldName;
                    this->index = oldId;
                    this->current_tok = this->tokens[this->index];
                    depth = 0;
                    generic_failed = true;
                }
                bool next_comma = false;
                bool just_incremented = true;
                while (depth > 0) {
                    if (next_comma) {
                        if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::LESS &&
                            this->current_tok.type != TokenType::MORE) {
                            this->index = oldId;
                            name = oldName;
                            generic_failed = true;
                            this->current_tok = this->tokens[this->index];
                            break;
                        }
                    } else {
                        if (this->current_tok.type == TokenType::COMMA) {
                            this->index = oldId;
                            generic_failed = true;
                            name = oldName;
                            this->current_tok = this->tokens[this->index];
                            break;
                        }
                    }
                    if (!(std::unordered_set<TokenType>(
                              {TokenType::COMMA, TokenType::KEYWORD, TokenType::IDENTIFIER, TokenType::STRING, TokenType::INT, TokenType::DOUBLE,
                               TokenType::FLOAT, TokenType::CHAR, TokenType::ADDR_T, TokenType::BOOL, TokenType::QBOOL, TokenType::LONG_INT,
                               TokenType::SHORT_INT, TokenType::LONG_DOUBLE, TokenType::LESS, TokenType::MORE, TokenType::BYTE, TokenType::NIBBLE})
                              .contains(this->current_tok.type))) {
                        this->index = oldId;
                        name = oldName;
                        generic_failed = true;
                        this->current_tok = this->tokens[this->index];
                        break;
                    }
                    if (this->current_tok.type == TokenType::EOFT) {
                        res.failure(new InvalidSyntaxError("Unterminated generic argument list", pos));
                        return res.to_prs();
                    }
                    if (this->current_tok.type == TokenType::LESS) {
                        if (just_incremented) {
                            this->index = oldId;
                            name = oldName;
                            generic_failed = true;
                            this->current_tok = this->tokens[this->index];
                            break;
                        }
                        just_incremented = true;
                        depth++;
                        if (depth > 128) {
                            res.failure(new InvalidSyntaxError(
                                "Generic nesting exceeds maximum depth of 128.\n\nNote: While expanding:\n    " + name.substr(0, 120) + "..." +
                                    "\n\nNote: We opened the box and there was another box. And another. Please stop. The "
                                    "compiler is not a Matryoshka doll. It has feelings too.",
                                pos));
                            return res.to_prs();
                        }
                    } else if (this->current_tok.type == TokenType::MORE) {
                        depth--;
                        if (depth == 0) {
                            this->advance();
                            break;
                        }
                    } else {
                        just_incremented = false;
                    }
                    if (this->current_tok.type != TokenType::MORE) next_comma = !next_comma;
                    name += this->current_tok.value;
                    this->advance();
                }
                if (this->index != oldId && name != oldName) name += ">";
            }
            if (generic_failed || this->current_tok.type != TokenType::SCOPE && this->current_tok.type != TokenType::LESS) { break; }
        }
        if (this->current_tok.type == TokenType::LESS) {
            size_t oldId = this->index;
            std::string oldName = name;
            this->advance();
            name += "<";
            int depth = 1;
            if (this->current_tok.type == TokenType::MORE) {
                name = oldName;
                this->index = oldId;
                this->current_tok = this->tokens[this->index];
                depth = 0;
            }
            bool next_comma = false;
            bool just_incremented = true;
            while (depth > 0) {
                if (next_comma) {
                    if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::LESS &&
                        this->current_tok.type != TokenType::MORE) {
                        this->index = oldId;
                        name = oldName;
                        this->current_tok = this->tokens[this->index];
                        break;
                    }
                } else {
                    if (this->current_tok.type == TokenType::COMMA) {
                        this->index = oldId;
                        name = oldName;
                        this->current_tok = this->tokens[this->index];
                        break;
                    }
                }
                if (!(std::unordered_set<TokenType>({TokenType::COMMA, TokenType::KEYWORD, TokenType::IDENTIFIER, TokenType::STRING, TokenType::INT,
                                                     TokenType::DOUBLE, TokenType::FLOAT, TokenType::CHAR, TokenType::ADDR_T, TokenType::BOOL,
                                                     TokenType::QBOOL, TokenType::LONG_INT, TokenType::SHORT_INT, TokenType::LONG_DOUBLE,
                                                     TokenType::LESS, TokenType::MORE, TokenType::BYTE, TokenType::NIBBLE})
                          .contains(this->current_tok.type))) {
                    this->index = oldId;
                    name = oldName;
                    this->current_tok = this->tokens[this->index];
                    break;
                }
                if (this->current_tok.type == TokenType::EOFT) {
                    res.failure(new InvalidSyntaxError("Unterminated generic argument list", pos));
                    return res.to_prs();
                }
                if (this->current_tok.type == TokenType::LESS) {
                    if (just_incremented) {
                        this->index = oldId;
                        name = oldName;
                        this->current_tok = this->tokens[this->index];
                        break;
                    }
                    just_incremented = true;
                    depth++;
                    if (depth > 128) {
                        res.failure(new InvalidSyntaxError("Generic nesting exceeds maximum depth of 128.\n\nNote: While expanding:\n    " +
                                                               name.substr(0, 120) + "..." +
                                                               "\n\nNote: We opened the box and there was another box. And another. Please stop. The "
                                                               "compiler is not a Matryoshka doll. It has feelings too.",
                                                           pos));
                        return res.to_prs();
                    }
                } else if (this->current_tok.type == TokenType::MORE) {
                    depth--;
                    if (depth == 0) {
                        this->advance();
                        break;
                    }
                } else {
                    just_incremented = false;
                }
                if (this->current_tok.type != TokenType::MORE) next_comma = !next_comma;
                name += this->current_tok.value;
                this->advance();
            }
            if (this->index != oldId && name != oldName) name += ">";
        }
        if (this->current_tok.type == TokenType::LBRACE) {
            Position start_pos = this->current_tok.pos;
            this->advance();
            if (this->current_tok.type == TokenType::RBRACE) {
                this->advance();
                std::vector<std::pair<AnyNode, AnyNode>> pairs;
                return res.success(new MapLiteralNode(pairs, start_pos, name));
            }
            auto first_key_expr = res.reg(this->logical_or());
            if (res.error) return res.to_prs();
            if (this->current_tok.type == TokenType::COLON) {
                this->advance();
                AnyNode first_val_expr = res.reg(this->logical_or());
                if (res.error) return res.to_prs();
                std::vector<std::pair<AnyNode, AnyNode>> pairs;
                pairs.emplace_back(first_key_expr, first_val_expr);
                while (this->current_tok.type == TokenType::COMMA) {
                    this->advance();
                    AnyNode key_expr = res.reg(this->logical_or());
                    if (res.error) return res.to_prs();

                    if (this->current_tok.type != TokenType::COLON) {
                        res.failure(new InvalidSyntaxError("QC-S046: Expected ':' in map literal", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                    AnyNode val_expr = res.reg(this->logical_or());
                    if (res.error) return res.to_prs();
                    pairs.emplace_back(key_expr, val_expr);
                }
                if (this->current_tok.type != TokenType::RBRACE) {
                    res.failure(new InvalidSyntaxError("QC-S047: Expected '}' at end of map literal", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                return res.success(new MapLiteralNode(pairs, start_pos, name));
            } else {
                std::vector<AnyNode> elements;
                elements.push_back(first_key_expr);
                while (this->current_tok.type == TokenType::COMMA) {
                    this->advance();
                    AnyNode e2 = res.reg(this->logical_or());
                    if (res.error) return res.to_prs();
                    elements.push_back(e2);
                }

                if (this->current_tok.type != TokenType::RBRACE) {
                    res.failure(new InvalidSyntaxError("QC-S048: Expected '}' in initializer list", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();

                return res.success(new ArrayLiteralNode(elements, start_pos, name));
            }
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
                if (this->current_tok.type == TokenType::LESS) {
                    size_t oldId = this->index;
                    std::string oldName = property_name.value;
                    this->advance();
                    property_name.value += "<";
                    int depth = 1;
                    if (this->current_tok.type == TokenType::MORE) {
                        property_name.value = oldName;
                        this->index = oldId;
                        this->current_tok = this->tokens[this->index];
                        depth = 0;
                    }
                    bool next_comma = false;
                    bool just_incremented = true;
                    while (depth > 0) {
                        if (next_comma) {
                            if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::LESS &&
                                this->current_tok.type != TokenType::MORE) {
                                this->index = oldId;
                                property_name.value = oldName;
                                this->current_tok = this->tokens[this->index];
                                break;
                            }
                        } else {
                            if (this->current_tok.type == TokenType::COMMA) {
                                this->index = oldId;
                                property_name.value = oldName;
                                this->current_tok = this->tokens[this->index];
                                break;
                            }
                        }
                        if (!(std::unordered_set<TokenType>({TokenType::COMMA, TokenType::KEYWORD, TokenType::IDENTIFIER, TokenType::STRING,
                                                             TokenType::INT, TokenType::DOUBLE, TokenType::FLOAT, TokenType::CHAR, TokenType::ADDR_T,
                                                             TokenType::BOOL, TokenType::QBOOL, TokenType::LONG_INT, TokenType::SHORT_INT,
                                                             TokenType::LONG_DOUBLE, TokenType::LESS, TokenType::MORE, TokenType::BYTE,
                                                             TokenType::NIBBLE})
                                  .contains(this->current_tok.type))) {
                            this->index = oldId;
                            property_name.value = oldName;
                            this->current_tok = this->tokens[this->index];
                            break;
                        }
                        if (this->current_tok.type == TokenType::EOFT) {
                            res.failure(new InvalidSyntaxError("Unterminated generic argument list", this->current_tok.pos));
                            return res.to_prs();
                        }
                        if (this->current_tok.type == TokenType::LESS) {
                            if (just_incremented) {
                                this->index = oldId;
                                property_name.value = oldName;
                                this->current_tok = this->tokens[this->index];
                                break;
                            }
                            just_incremented = true;
                            depth++;
                            if (depth > 128) {
                                res.failure(
                                    new InvalidSyntaxError("Generic nesting exceeds maximum depth of 128.\n\nNote: While expanding:\n    " +
                                                               property_name.value.substr(0, 120) + "..." +
                                                               "\n\nNote: We opened the box and there was another box. And another. Please stop. The "
                                                               "compiler is not a Matryoshka doll. It has feelings too.",
                                                           this->current_tok.pos));
                                return res.to_prs();
                            }
                        } else if (this->current_tok.type == TokenType::MORE) {
                            depth--;
                            if (depth == 0) {
                                this->advance();
                                break;
                            }
                        } else {
                            just_incremented = false;
                        }
                        if (this->current_tok.type != TokenType::MORE) next_comma = !next_comma;
                        property_name.value += this->current_tok.value;
                        this->advance();
                    }
                    if (this->index != oldId && property_name.value != oldName) property_name.value += ">";
                }
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
                if (this->current_tok.type == TokenType::LESS) {
                    size_t oldId = this->index;
                    std::string oldName = property_name.value;
                    this->advance();
                    property_name.value += "<";
                    int depth = 1;
                    if (this->current_tok.type == TokenType::MORE) {
                        property_name.value = oldName;
                        this->index = oldId;
                        this->current_tok = this->tokens[this->index];
                        depth = 0;
                    }
                    bool next_comma = false;
                    bool just_incremented = true;
                    while (depth > 0) {
                        if (next_comma) {
                            if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::LESS &&
                                this->current_tok.type != TokenType::MORE) {
                                this->index = oldId;
                                property_name.value = oldName;
                                this->current_tok = this->tokens[this->index];
                                break;
                            }
                        } else {
                            if (this->current_tok.type == TokenType::COMMA) {
                                this->index = oldId;
                                property_name.value = oldName;
                                this->current_tok = this->tokens[this->index];
                                break;
                            }
                        }
                        if (!(std::unordered_set<TokenType>({TokenType::COMMA, TokenType::KEYWORD, TokenType::IDENTIFIER, TokenType::STRING,
                                                             TokenType::INT, TokenType::DOUBLE, TokenType::FLOAT, TokenType::CHAR, TokenType::ADDR_T,
                                                             TokenType::BOOL, TokenType::QBOOL, TokenType::LONG_INT, TokenType::SHORT_INT,
                                                             TokenType::LONG_DOUBLE, TokenType::LESS, TokenType::MORE, TokenType::BYTE,
                                                             TokenType::NIBBLE})
                                  .contains(this->current_tok.type))) {
                            this->index = oldId;
                            property_name.value = oldName;
                            this->current_tok = this->tokens[this->index];
                            break;
                        }
                        if (this->current_tok.type == TokenType::EOFT) {
                            res.failure(new InvalidSyntaxError("Unterminated generic argument list", this->current_tok.pos));
                            return res.to_prs();
                        }
                        if (this->current_tok.type == TokenType::LESS) {
                            if (just_incremented) {
                                this->index = oldId;
                                property_name.value = oldName;
                                this->current_tok = this->tokens[this->index];
                                break;
                            }
                            just_incremented = true;
                            depth++;
                            if (depth > 128) {
                                res.failure(
                                    new InvalidSyntaxError("Generic nesting exceeds maximum depth of 128.\n\nNote: While expanding:\n    " +
                                                               property_name.value.substr(0, 120) + "..." +
                                                               "\n\nNote: We opened the box and there was another box. And another. Please stop. The "
                                                               "compiler is not a Matryoshka doll. It has feelings too.",
                                                           this->current_tok.pos));
                                return res.to_prs();
                            }
                        } else if (this->current_tok.type == TokenType::MORE) {
                            depth--;
                            if (depth == 0) {
                                this->advance();
                                break;
                            }
                        } else {
                            just_incremented = false;
                        }
                        if (this->current_tok.type != TokenType::MORE) next_comma = !next_comma;
                        property_name.value += this->current_tok.value;
                        this->advance();
                    }
                    if (this->index != oldId && property_name.value != oldName) property_name.value += ">";
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
            AnyNode value_node = new UnaryOpNode(op, base, true);
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
                    if (this->current_tok.type == TokenType::LESS) {
                        size_t oldId = this->index;
                        std::string oldName = property_name.value;
                        this->advance();
                        property_name.value += "<";
                        int depth = 1;
                        if (this->current_tok.type == TokenType::MORE) {
                            property_name.value = oldName;
                            this->index = oldId;
                            this->current_tok = this->tokens[this->index];
                            depth = 0;
                        }
                        bool next_comma = false;
                        bool just_incremented = true;
                        while (depth > 0) {
                            if (next_comma) {
                                if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::LESS &&
                                    this->current_tok.type != TokenType::MORE) {
                                    this->index = oldId;
                                    property_name.value = oldName;
                                    this->current_tok = this->tokens[this->index];
                                    break;
                                }
                            } else {
                                if (this->current_tok.type == TokenType::COMMA) {
                                    this->index = oldId;
                                    property_name.value = oldName;
                                    this->current_tok = this->tokens[this->index];
                                    break;
                                }
                            }
                            if (!(std::unordered_set<TokenType>({TokenType::COMMA, TokenType::KEYWORD, TokenType::IDENTIFIER, TokenType::STRING,
                                                                 TokenType::INT, TokenType::DOUBLE, TokenType::FLOAT, TokenType::CHAR,
                                                                 TokenType::ADDR_T, TokenType::BOOL, TokenType::QBOOL, TokenType::LONG_INT,
                                                                 TokenType::SHORT_INT, TokenType::LONG_DOUBLE, TokenType::LESS, TokenType::MORE,
                                                                 TokenType::BYTE, TokenType::NIBBLE})
                                      .contains(this->current_tok.type))) {
                                this->index = oldId;
                                property_name.value = oldName;
                                this->current_tok = this->tokens[this->index];
                                break;
                            }
                            if (this->current_tok.type == TokenType::EOFT) {
                                res.failure(new InvalidSyntaxError("Unterminated generic argument list", this->current_tok.pos));
                                return res.to_prs();
                            }
                            if (this->current_tok.type == TokenType::LESS) {
                                if (just_incremented) {
                                    this->index = oldId;
                                    property_name.value = oldName;
                                    this->current_tok = this->tokens[this->index];
                                    break;
                                }
                                just_incremented = true;
                                depth++;
                                if (depth > 128) {
                                    res.failure(new InvalidSyntaxError(
                                        "Generic nesting exceeds maximum depth of 128.\n\nNote: While expanding:\n    " +
                                            property_name.value.substr(0, 120) + "..." +
                                            "\n\nNote: We opened the box and there was another box. And another. Please stop. The "
                                            "compiler is not a Matryoshka doll. It has feelings too.",
                                        this->current_tok.pos));
                                    return res.to_prs();
                                }
                            } else if (this->current_tok.type == TokenType::MORE) {
                                depth--;
                                if (depth == 0) {
                                    this->advance();
                                    break;
                                }
                            } else {
                                just_incremented = false;
                            }
                            if (this->current_tok.type != TokenType::MORE) next_comma = !next_comma;
                            property_name.value += this->current_tok.value;
                            this->advance();
                        }
                        if (this->index != oldId && property_name.value != oldName) property_name.value += ">";
                    }
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
                    if (this->current_tok.type == TokenType::LESS) {
                        size_t oldId = this->index;
                        std::string oldName = property_name.value;
                        this->advance();
                        property_name.value += "<";
                        int depth = 1;
                        if (this->current_tok.type == TokenType::MORE) {
                            property_name.value = oldName;
                            this->index = oldId;
                            this->current_tok = this->tokens[this->index];
                            depth = 0;
                        }
                        bool next_comma = false;
                        bool just_incremented = true;
                        while (depth > 0) {
                            if (next_comma) {
                                if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::LESS &&
                                    this->current_tok.type != TokenType::MORE) {
                                    this->index = oldId;
                                    property_name.value = oldName;
                                    this->current_tok = this->tokens[this->index];
                                    break;
                                }
                            } else {
                                if (this->current_tok.type == TokenType::COMMA) {
                                    this->index = oldId;
                                    property_name.value = oldName;
                                    this->current_tok = this->tokens[this->index];
                                    break;
                                }
                            }
                            if (!(std::unordered_set<TokenType>({TokenType::COMMA, TokenType::KEYWORD, TokenType::IDENTIFIER, TokenType::STRING,
                                                                 TokenType::INT, TokenType::DOUBLE, TokenType::FLOAT, TokenType::CHAR,
                                                                 TokenType::ADDR_T, TokenType::BOOL, TokenType::QBOOL, TokenType::LONG_INT,
                                                                 TokenType::SHORT_INT, TokenType::LONG_DOUBLE, TokenType::LESS, TokenType::MORE,
                                                                 TokenType::BYTE, TokenType::NIBBLE})
                                      .contains(this->current_tok.type))) {
                                this->index = oldId;
                                property_name.value = oldName;
                                this->current_tok = this->tokens[this->index];
                                break;
                            }
                            if (this->current_tok.type == TokenType::EOFT) {
                                res.failure(new InvalidSyntaxError("Unterminated generic argument list", this->current_tok.pos));
                                return res.to_prs();
                            }
                            if (this->current_tok.type == TokenType::LESS) {
                                if (just_incremented) {
                                    this->index = oldId;
                                    property_name.value = oldName;
                                    this->current_tok = this->tokens[this->index];
                                    break;
                                }
                                just_incremented = true;
                                depth++;
                                if (depth > 128) {
                                    res.failure(new InvalidSyntaxError(
                                        "Generic nesting exceeds maximum depth of 128.\n\nNote: While expanding:\n    " +
                                            property_name.value.substr(0, 120) + "..." +
                                            "\n\nNote: We opened the box and there was another box. And another. Please stop. The "
                                            "compiler is not a Matryoshka doll. It has feelings too.",
                                        this->current_tok.pos));
                                    return res.to_prs();
                                }
                            } else if (this->current_tok.type == TokenType::MORE) {
                                depth--;
                                if (depth == 0) {
                                    this->advance();
                                    break;
                                }
                            } else {
                                just_incremented = false;
                            }
                            if (this->current_tok.type != TokenType::MORE) next_comma = !next_comma;
                            property_name.value += this->current_tok.value;
                            this->advance();
                        }
                        if (this->index != oldId && property_name.value != oldName) property_name.value += ">";
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
                AnyNode value_node = new UnaryOpNode(op, base, true);
                return res.success(value_node);
            } else {
                break;
            }
            if (res.error) return res.to_prs();
        }
        if (is_known_type(name)) { return res.success(TypeValueNode(Token(TokenType::KEYWORD, name, tok.pos))); }
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
                if (this->current_tok.type == TokenType::LESS) {
                    size_t oldId = this->index;
                    std::string oldName = property_name.value;
                    this->advance();
                    property_name.value += "<";
                    int depth = 1;
                    if (this->current_tok.type == TokenType::MORE) {
                        property_name.value = oldName;
                        this->index = oldId;
                        this->current_tok = this->tokens[this->index];
                        depth = 0;
                    }
                    bool next_comma = false;
                    bool just_incremented = true;
                    while (depth > 0) {
                        if (next_comma) {
                            if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::LESS &&
                                this->current_tok.type != TokenType::MORE) {
                                this->index = oldId;
                                property_name.value = oldName;
                                this->current_tok = this->tokens[this->index];
                                break;
                            }
                        } else {
                            if (this->current_tok.type == TokenType::COMMA) {
                                this->index = oldId;
                                property_name.value = oldName;
                                this->current_tok = this->tokens[this->index];
                                break;
                            }
                        }
                        if (!(std::unordered_set<TokenType>({TokenType::COMMA, TokenType::KEYWORD, TokenType::IDENTIFIER, TokenType::STRING,
                                                             TokenType::INT, TokenType::DOUBLE, TokenType::FLOAT, TokenType::CHAR, TokenType::ADDR_T,
                                                             TokenType::BOOL, TokenType::QBOOL, TokenType::LONG_INT, TokenType::SHORT_INT,
                                                             TokenType::LONG_DOUBLE, TokenType::LESS, TokenType::MORE, TokenType::BYTE,
                                                             TokenType::NIBBLE})
                                  .contains(this->current_tok.type))) {
                            this->index = oldId;
                            property_name.value = oldName;
                            this->current_tok = this->tokens[this->index];
                            break;
                        }
                        if (this->current_tok.type == TokenType::EOFT) {
                            res.failure(new InvalidSyntaxError("Unterminated generic argument list", this->current_tok.pos));
                            return res.to_prs();
                        }
                        if (this->current_tok.type == TokenType::LESS) {
                            if (just_incremented) {
                                this->index = oldId;
                                property_name.value = oldName;
                                this->current_tok = this->tokens[this->index];
                                break;
                            }
                            just_incremented = true;
                            depth++;
                            if (depth > 128) {
                                res.failure(
                                    new InvalidSyntaxError("Generic nesting exceeds maximum depth of 128.\n\nNote: While expanding:\n    " +
                                                               property_name.value.substr(0, 120) + "..." +
                                                               "\n\nNote: We opened the box and there was another box. And another. Please stop. The "
                                                               "compiler is not a Matryoshka doll. It has feelings too.",
                                                           this->current_tok.pos));
                                return res.to_prs();
                            }
                        } else if (this->current_tok.type == TokenType::MORE) {
                            depth--;
                            if (depth == 0) {
                                this->advance();
                                break;
                            }
                        } else {
                            just_incremented = false;
                        }
                        if (this->current_tok.type != TokenType::MORE) next_comma = !next_comma;
                        property_name.value += this->current_tok.value;
                        this->advance();
                    }
                    if (this->index != oldId && property_name.value != oldName) property_name.value += ">";
                }
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
    } else if (tok.type == TokenType::KEYWORD && tok.value == "fn") {
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
            return_types.push_back(Token(TokenType::KEYWORD, parseTypeString(), this->current_tok.pos));
            this->advance();

            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                return_types.push_back(Token(TokenType::KEYWORD, parseTypeString(), this->current_tok.pos));
                this->advance();
            }
        }
        this->index = saved_index;
        this->current_tok = this->tokens[this->index];

        auto fn_pr = this->func_def_multi(return_types, std::nullopt, {}, false);

        if (std::holds_alternative<Error*>(fn_pr)) return fn_pr;

        AnyNode fn_node;
        if (std::holds_alternative<FuncDefNode*>(fn_pr))
            fn_node = std::get<FuncDefNode*>(fn_pr);
        else
            fn_node = std::get<FuncDefNode*>(fn_pr);

        if (this->current_tok.type == TokenType::LPAREN) return this->call(fn_node);

        return res.success(fn_node);
    } else if (tok.type == TokenType::KEYWORD) {
        return res.success(TypeValueNode(Token(TokenType::KEYWORD, this->parseTypeString(), tok.pos)));
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
    if (this->current_tok.type == TokenType::INCREMENT || this->current_tok.type == TokenType::DECREMENT ||
        this->current_tok.type == TokenType::SIZEOF || this->current_tok.type == TokenType::THROW) {
        Token op = this->current_tok;
        this->advance();
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
        this->current_tok.type == TokenType::MUL_EQ || this->current_tok.type == TokenType::DIV_EQ || this->current_tok.type == TokenType::MOD_EQ ||
        this->current_tok.type == TokenType::RSH_EQ || this->current_tok.type == TokenType::LSH_EQ || this->current_tok.type == TokenType::LRSH_EQ ||
        this->current_tok.type == TokenType::RROT_EQ || this->current_tok.type == TokenType::LROT_EQ ||
        this->current_tok.type == TokenType::BIT_X_EQ || this->current_tok.type == TokenType::BIT_O_EQ ||
        this->current_tok.type == TokenType::BIT_A_EQ) {
        bool is_var = std::holds_alternative<VarAccessNode*>(left);
        bool is_array_access = std::holds_alternative<ArrayAccessNode*>(left);
        bool is_prop = std::holds_alternative<PropertyAccessNode*>(left);
        bool is_deref = std::holds_alternative<UnaryOpNode*>(left) && std::get<UnaryOpNode*>(left)->op_tok.type == TokenType::MUL;
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
            case TokenType::RSH_EQ: binop_type = TokenType::RSHIFT; break;
            case TokenType::LSH_EQ: binop_type = TokenType::LSHIFT; break;
            case TokenType::LRSH_EQ: binop_type = TokenType::LOGICAL_RSHIFT; break;
            case TokenType::RROT_EQ: binop_type = TokenType::R_ROT; break;
            case TokenType::LROT_EQ: binop_type = TokenType::L_ROT; break;
            case TokenType::BIT_X_EQ: binop_type = TokenType::BITWISE_XOR; break;
            case TokenType::BIT_O_EQ: binop_type = TokenType::PIPE; break;
            case TokenType::BIT_A_EQ: binop_type = TokenType::AMPERSAND; break;
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
                                                   "array access",
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
        if (!(p.type.type == TokenType::VARADIC)) {
            p.type.value = "";
            while (this->current_tok.type == TokenType::KEYWORD) {
                if (std::unordered_set<std::string>({"out", "inout", "volatile"}).contains(this->current_tok.value)) {
                    if (this->current_tok.value == "volatile") {
                        p.isVolatile = true;
                    } else {
                        p.type.value += this->current_tok.value + " ";
                    }
                    this->advance();
                } else {
                    break;
                }
            }
            p.type.value += parseTypeString();
            if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "restrict") {
                p.type.value += "restrict";
                this->advance();
            }
        } else {
            this->advance();
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
Prs Parser::func_def_multi(std::vector<Token> return_types, std::optional<Token> func_name, std::vector<GenericType> generics, bool keep,
                           bool is_volatile) {
    ParseResult res;
    std::vector<GenericType> old_generics = this->current_generics;
    if (keep) {
        this->current_generics.insert(this->current_generics.end(), generics.begin(), generics.end());
    } else {
        this->current_generics = generics;
    }
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
        while (true) {
            if (this->current_tok.type == TokenType::SCOPE) {
                this->advance();
                if (this->current_tok.type == TokenType::IDENTIFIER || this->current_tok.type == TokenType::KEYWORD) { this->advance(); }
            } else if (this->current_tok.type == TokenType::LESS) {
                int depth = 1;
                this->advance();
                while (depth > 0 && this->current_tok.type != TokenType::EOFT) {
                    if (this->current_tok.type == TokenType::LESS)
                        depth++;
                    else if (this->current_tok.type == TokenType::MORE)
                        depth--;
                    this->advance();
                }
            } else {
                break;
            }
        }
        if (this->current_tok.type == TokenType::KEYWORD || is_known_type(this->current_tok.value) > 0) {
            this->parse_parameter(true);
            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                this->parse_parameter(true);
                if (this->current_tok.type == TokenType::KEYWORD || is_known_type(this->current_tok.value) > 0) {
                    this->advance();
                    this->parse_parameter(true);
                }
            }
        }
    }
    if (this->current_tok.type != TokenType::LBRACE) {
        if (this->current_tok.type == TokenType::SEMICOLON) {
            this->advance();
            std::list<Parameter> params_list((params.begin()), (params.end()));
            std::vector<AnyNode> body;
            body.emplace_back(std::monostate{});
            return res.success(new FuncDefNode(return_types, func_name, params_list, new StatementsNode(body), currentNamespace, this->in_extern,
                                               this->in_foreign, generics, is_volatile, true));
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
    this->current_generics = old_generics;
    return res.success(
        new FuncDefNode(return_types, func_name, params_list, body, currentNamespace, this->in_extern, this->in_foreign, generics, is_volatile));
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

            if (this->current_tok.type != TokenType::KEYWORD && this->current_tok.type != TokenType::IDENTIFIER &&
                std::none_of(this->current_generics.begin(), this->current_generics.end(),
                             [this](GenericType t) { return t.name == this->current_tok.value; })) {
                res.failure(new InvalidSyntaxError("Expected return type after '->'", this->current_tok.pos));
                return res.to_prs();
            }
            Token saved_tok = this->current_tok;
            std::string type_str = parseTypeString();
            saved_tok.value = type_str;
            return_types.push_back(saved_tok);
            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                if (this->current_tok.type != TokenType::KEYWORD && this->current_tok.type != TokenType::IDENTIFIER &&
                    std::none_of(this->current_generics.begin(), this->current_generics.end(),
                                 [this](GenericType t) { return t.name == this->current_tok.value; })) {
                    res.failure(new InvalidSyntaxError("Expected return type after ','", this->current_tok.pos));
                    return res.to_prs();
                }
                Token saved_tok = this->current_tok;
                std::string type_str = parseTypeString();
                saved_tok.value = type_str;
                return_types.push_back(saved_tok);
            }
        } else {
            return_types.push_back(Token(TokenType::KEYWORD, "void", tok.pos));
        }

        this->index = saved_index;
        this->current_tok = this->tokens[this->index];

        auto fn_pr = this->func_def_multi(return_types, std::nullopt, {}, false);

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
        elem_type.value = parseTypeString();
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
        std::vector<GenericType> generics;
        if (this->current_tok.type == TokenType::LESS) {
            this->advance();
            while (true) {
                GenericType curr;
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    if (this->current_tok.type == TokenType::KEYWORD &&
                        std::unordered_set<std::string>({"int", "double", "float", "addr_t", "byte", "nibble", "string", "char", "bool", "qbool"})
                            .contains(this->current_tok.value)) {
                        curr.isNonType = true;
                        curr.nonTypeKind = this->current_tok.value;
                    } else if (this->current_tok.value == "long" || this->current_tok.value == "short") {
                        std::string prev = this->current_tok.value;
                        this->advance();
                        if (this->current_tok.value != "int" && this->current_tok.value != "double") {
                            res.failure(new InvalidSyntaxError("Expected 'int' or 'double' after '" + prev + "'", this->current_tok.pos));
                            return res.to_prs();
                        }
                        curr.isNonType = true;
                        curr.nonTypeKind = prev + " " + this->current_tok.value;
                    } else {
                        res.failure(
                            new InvalidSyntaxError("Expected generic typename to be a identifier ([_a-zA-Z][0-9a-zA-Z_]*)", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                }
                curr.name = this->current_tok.value;
                this->advance();
                if (this->current_tok.type == TokenType::LPAREN && !curr.isNonType) {
                    this->advance();
                    if (this->current_tok.type != TokenType::COLON) {
                        if (this->current_tok.type == TokenType::IDENTIFIER &&
                            (this->current_tok.value == "usertype" || this->current_tok.value == "primitive" ||
                             this->current_tok.value == "callable" || this->current_tok.value == "numeric" || this->current_tok.value == "pointer")) {
                            curr.constraint = this->current_tok.value;
                        } else {
                            res.failure(new InvalidSyntaxError("Expected : or usertype:, primitive:, or callable: before generic constraint list",
                                                               this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                    } else {
                        curr.constraint = "";
                    }
                    this->advance();
                    if (this->current_tok.type == TokenType::NOT) {
                        curr.negated = true;
                        this->advance();
                    }
                    while (this->current_tok.type == TokenType::IDENTIFIER || this->current_tok.type == TokenType::KEYWORD) {
                        curr.subconstraints.push_back(this->current_tok.value);
                        this->advance();
                        if (this->current_tok.type == TokenType::PIPE) { this->advance(); }
                    }
                    if (this->current_tok.type != TokenType::RPAREN) {
                        res.failure(new InvalidSyntaxError("Expected ) after generic type constraint list.", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                }
                if (this->current_tok.type == TokenType::EQ) {
                    this->advance();
                    curr.defaultValue = this->current_tok.value;
                    this->advance();
                }
                if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::MORE) {
                    res.failure(new InvalidSyntaxError("Expected > or , after generic type.", this->current_tok.pos));
                    return res.to_prs();
                }
                generics.push_back(curr);
                if (this->current_tok.type == TokenType::MORE) {
                    this->advance();
                    break;
                }
                this->advance();
            }
        }
        auto saved_generics = this->current_generics;
        this->current_generics.insert(this->current_generics.end(), generics.begin(), generics.end());
        std::string baseName = "";
        if (this->current_tok.type == TokenType::COLON) {
            this->advance();
            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(new InvalidSyntaxError("Expected base class name after ':'", this->current_tok.pos));
                return res.to_prs();
            }
            baseName = this->current_tok.value;
            this->advance();
            if (this->current_tok.type == TokenType::LESS) {
                baseName += "<";
                this->advance();
                int angleDepth = 1;
                while (angleDepth > 0) {
                    if (this->current_tok.type == TokenType::LESS) {
                        angleDepth++;
                        baseName += "<";
                        this->advance();
                    } else if (this->current_tok.type == TokenType::MORE) {
                        angleDepth--;
                        baseName += ">";
                        if (angleDepth == 0) {
                            this->advance();
                            break;
                        }
                        this->advance();
                    } else if (this->current_tok.type == TokenType::COMMA) {
                        baseName += ",";
                        this->advance();
                    } else if (this->current_tok.type == TokenType::IDENTIFIER || this->current_tok.type == TokenType::KEYWORD) {
                        baseName += parseTypeString();
                    } else {
                        res.failure(new InvalidSyntaxError("Unexpected token inside base class generic argument list", this->current_tok.pos));
                        return res.to_prs();
                    }
                }
            }
        }
        if (!baseName.empty()) {
            auto* base_ptr = find_type(base_type_name(baseName));
            if (base_ptr && base_ptr->kind == UserTypeKind::Class && base_ptr->is_final_class) {
                res.failure(new InvalidSyntaxError("Cannot inherit from final class '" + base_type_name(baseName) + "'", class_name.pos));
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
        ClassField vp;
        vp.name = "__vptr";
        vp.type = (currentNamespace.empty() ? class_name.value : currentNamespace + "::" + class_name.value) + "*";
        vp.access = "public";
        info.classFields.push_back(vp);
        dummy.baseClassName = baseName;
        dummy.is_final_class = is_final_class;
        dummy.kind = UserTypeKind::Class;
        info.baseClassName = baseName;
        info.is_final_class = is_final_class;
        info.kind = UserTypeKind::Class;
        info.baseFile = this->current_tok.pos.Filename;
        dummy.is_abstract_class = is_abstract_class;
        info.is_abstract_class = is_abstract_class;
        std::string full_key = currentNamespace.empty() ? class_name.value : currentNamespace + "::" + class_name.value;
        if (user_types.contains(base_type_name(full_key))) {
            res.failure(new InvalidSyntaxError("QC-UT01: Redefinition of type '" + class_name.value + "'", class_name.pos));
            return res.to_prs();
        }
        dummy.generics = generics;
        info.generics = generics;
        dummy.namespace_path = currentNamespace;
        info.namespace_path = currentNamespace;
        user_types[base_type_name(full_key)] = dummy;

        while (this->current_tok.type != TokenType::RBRACE && this->current_tok.type != TokenType::EOFT) {

            std::string access = "public";
            bool is_final_method = false;
            bool is_volatile_method = false;
            bool is_static = false;
            if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "final") {
                is_final_method = true;
                this->advance();
            }
            if (this->current_tok.type == TokenType::KEYWORD &&
                (this->current_tok.value == "public" || this->current_tok.value == "private" || this->current_tok.value == "protected")) {
                access = this->current_tok.value;
                this->advance();
            }
            if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "static") {
                is_static = true;
                this->advance();
            }
            if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "final") {
                is_final_method = true;
                this->advance();
            }
            if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "volatile") {
                is_volatile_method = true;
                this->advance();
            }
            if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "friend") {
                this->advance();
                info.friendClasses.push_back(parseTypeString());
                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(new InvalidSyntaxError("expected ; after friend class name", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                continue;
            }
            if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "friendly") {
                this->advance();
                info.friendlyClasses.push_back(parseTypeString());
                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(new InvalidSyntaxError("expected ; after friendly class name", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                continue;
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
                std::vector<GenericType> genericsM;
                Token ctor_name = this->current_tok;
                size_t oldPos = this->index;
                if (next_tok.type == TokenType::LESS) {
                    ctor_name = this->current_tok;
                    this->advance();
                    this->advance();
                    while (true) {
                        GenericType curr;
                        if (this->current_tok.type != TokenType::IDENTIFIER) {
                            if (this->current_tok.type == TokenType::KEYWORD &&
                                std::unordered_set<std::string>(
                                    {"int", "double", "float", "byte", "nibble", "addr_t", "string", "char", "bool", "qbool"})
                                    .contains(this->current_tok.value)) {
                                curr.isNonType = true;
                                curr.nonTypeKind = this->current_tok.value;
                            } else if (this->current_tok.value == "long" || this->current_tok.value == "short") {
                                std::string prev = this->current_tok.value;
                                this->advance();
                                if (this->current_tok.value != "int" && this->current_tok.value != "double") {
                                    res.failure(new InvalidSyntaxError("Expected 'int' or 'double' after '" + prev + "'", this->current_tok.pos));
                                    return res.to_prs();
                                }
                                curr.isNonType = true;
                                curr.nonTypeKind = prev + " " + this->current_tok.value;
                            } else {
                                res.failure(new InvalidSyntaxError("Expected generic typename to be a identifier ([_a-zA-Z][0-9a-zA-Z_]*)",
                                                                   this->current_tok.pos));
                                return res.to_prs();
                            }
                            this->advance();
                        }
                        curr.name = this->current_tok.value;
                        this->advance();
                        if (this->current_tok.type == TokenType::LPAREN && !curr.isNonType) {
                            this->advance();
                            if (this->current_tok.type != TokenType::COLON) {
                                if (this->current_tok.type == TokenType::IDENTIFIER &&
                                    (this->current_tok.value == "usertype" || this->current_tok.value == "primitive" ||
                                     this->current_tok.value == "callable" || this->current_tok.value == "numeric" ||
                                     this->current_tok.value == "pointer")) {
                                    curr.constraint = this->current_tok.value;
                                } else {
                                    res.failure(new InvalidSyntaxError(
                                        "Expected : or usertype:, primitive:, or callable: before generic constraint list", this->current_tok.pos));
                                    return res.to_prs();
                                }
                                this->advance();
                            } else {
                                curr.constraint = "";
                            }
                            this->advance();
                            if (this->current_tok.type == TokenType::NOT) {
                                curr.negated = true;
                                this->advance();
                            }
                            while (this->current_tok.type == TokenType::IDENTIFIER || this->current_tok.type == TokenType::KEYWORD) {
                                curr.subconstraints.push_back(this->current_tok.value);
                                this->advance();
                                if (this->current_tok.type == TokenType::PIPE) { this->advance(); }
                            }
                            if (this->current_tok.type != TokenType::RPAREN) {
                                res.failure(new InvalidSyntaxError("Expected ) after generic type constraint list.", this->current_tok.pos));
                                return res.to_prs();
                            }
                            this->advance();
                        }
                        if (this->current_tok.type == TokenType::EQ) {
                            this->advance();
                            curr.defaultValue = this->current_tok.value;
                            this->advance();
                        }
                        if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::MORE) {
                            res.failure(new InvalidSyntaxError("Expected > or , after generic type.", this->current_tok.pos));
                            return res.to_prs();
                        }
                        genericsM.push_back(curr);
                        if (this->current_tok.type == TokenType::MORE) {
                            this->advance();
                            break;
                        }
                        this->advance();
                    }
                }
                next_tok = peek();
                if (next_tok.type == TokenType::LPAREN) {
                    this->advance();
                    if (this->current_tok.type != TokenType::LPAREN) {
                        res.failure(new InvalidSyntaxError("Expected '(' after constructor name", this->current_tok.pos));
                        return res.to_prs();
                    }

                    auto ctor_pr = this->func_def_multi({}, std::nullopt, genericsM, true);
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
                    mi.is_volatile = is_volatile_method;
                    mi.generics = genericsM;
                    info.classMethods.push_back(mi);
                    continue;
                } else {
                    this->index = oldPos;
                    this->current_tok = peek(0);
                }
            }
            if (this->current_tok.type != TokenType::KEYWORD && this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(new InvalidSyntaxError("Expected type or constructor in class body", this->current_tok.pos));
                return res.to_prs();
            }

            std::vector<Token> type_list;

            auto parse_one_type_into = [&](Token& out_tok) -> bool {
                std::string field_type = parseTypeString();
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
                Token long_ops[2] = {};
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
                case TokenType::INCREMENT:
                case TokenType::DECREMENT:
                case TokenType::BITWISE_NOT:
                case TokenType::RSHIFT:
                case TokenType::LOGICAL_RSHIFT:
                case TokenType::R_ROT:
                case TokenType::LSHIFT:
                case TokenType::L_ROT:
                case TokenType::BITWISE_XOR:
                case TokenType::PIPE:
                case TokenType::AMPERSAND:
                case TokenType::COLLAPSE_OR:
                case TokenType::PLUS_EQ:
                case TokenType::MINUS_EQ:
                case TokenType::MUL_EQ:
                case TokenType::DIV_EQ:
                case TokenType::MOD_EQ:
                case TokenType::BIT_X_EQ:
                case TokenType::BIT_A_EQ:
                case TokenType::BIT_O_EQ:
                case TokenType::LSH_EQ:
                case TokenType::RSH_EQ:
                case TokenType::LRSH_EQ:
                case TokenType::RROT_EQ:
                case TokenType::LROT_EQ:
                case TokenType::COLLAPSE_AND: break;
                case TokenType::LPAREN:
                    this->advance();
                    if (this->current_tok.type != TokenType::RPAREN) {
                        res.failure(new InvalidSyntaxError("expected closing paren in operator()", op_tok.pos));
                        return res.to_prs();
                    }
                    break;
                case TokenType::LBRACKET:
                    this->advance();
                    if (this->current_tok.type == TokenType::RBRACKET) {
                        long_ops[0] = this->current_tok;
                        if (this->peek().type == TokenType::EQ) {
                            this->advance();
                            long_ops[1] = this->current_tok;
                            break;
                        }
                        long_ops[1] = Token(TokenType::EOFT, "N/A", op_tok.pos);
                        break;
                    } else {
                        res.failure(new InvalidSyntaxError("Unsupported operator in operator method", op_tok.pos));
                        return res.to_prs();
                    }
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
                case TokenType::PLUS_EQ: op_name = "operator+="; break;
                case TokenType::MINUS_EQ: op_name = "operator-="; break;
                case TokenType::MUL_EQ: op_name = "operator*="; break;
                case TokenType::DIV_EQ: op_name = "operator/="; break;
                case TokenType::MOD_EQ: op_name = "operator%="; break;
                case TokenType::BIT_X_EQ: op_name = "operator$="; break;
                case TokenType::BIT_A_EQ: op_name = "operator&="; break;
                case TokenType::BIT_O_EQ: op_name = "operator|="; break;
                case TokenType::LSH_EQ: op_name = "operator<<="; break;
                case TokenType::RSH_EQ: op_name = "operator|>="; break;
                case TokenType::LRSH_EQ: op_name = "operator:>="; break;
                case TokenType::RROT_EQ: op_name = "operator|>>="; break;
                case TokenType::LROT_EQ: op_name = "operator<<<="; break;
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
                case TokenType::LBRACKET: op_name = ((long_ops[1].type == TokenType::EQ) ? "operator[]=" : "operator[]"); break;
                case TokenType::LPAREN: op_name = "operator()"; break;
                case TokenType::INCREMENT: op_name = "operator++"; break;
                case TokenType::DECREMENT: op_name = "operator--"; break;
                case TokenType::BITWISE_NOT: op_name = "operator~"; break;
                case TokenType::RSHIFT: op_name = "operator|>"; break;
                case TokenType::LOGICAL_RSHIFT: op_name = "operator:>"; break;
                case TokenType::R_ROT: op_name = "operator|>>"; break;
                case TokenType::LSHIFT: op_name = "operator<<"; break;
                case TokenType::L_ROT: op_name = "operator<<<"; break;
                case TokenType::BITWISE_XOR: op_name = "operator$"; break;
                case TokenType::PIPE: op_name = "operator|"; break;
                case TokenType::AMPERSAND: op_name = "operator&"; break;
                default: break;
                }
                name_tok = Token(TokenType::IDENTIFIER, op_name, op_tok.pos);
                this->advance();
            } else if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "roperator") {
                this->advance();
                Token op_tok = this->current_tok;
                Token long_ops[2] = {};
                switch (op_tok.type) {
                case TokenType::MINUS:
                case TokenType::DIV:
                case TokenType::POWER:
                case TokenType::MOD:
                case TokenType::RSHIFT:
                case TokenType::LOGICAL_RSHIFT:
                case TokenType::R_ROT:
                case TokenType::LSHIFT:
                case TokenType::L_ROT: break;
                default: res.failure(new InvalidSyntaxError("Unsupported operator in roperator method", op_tok.pos)); return res.to_prs();
                }
                std::string op_name;
                switch (op_tok.type) {
                case TokenType::MINUS: op_name = "operator-"; break;
                case TokenType::DIV: op_name = "operator/"; break;
                case TokenType::POWER: op_name = "operator#^"; break;
                case TokenType::MOD: op_name = "operator%"; break;
                case TokenType::RSHIFT: op_name = "operator|>"; break;
                case TokenType::LOGICAL_RSHIFT: op_name = "operator:>"; break;
                case TokenType::R_ROT: op_name = "operator|>>"; break;
                case TokenType::LSHIFT: op_name = "operator<<"; break;
                case TokenType::L_ROT: op_name = "operator<<<"; break;
                default: break;
                }
                name_tok = Token(TokenType::IDENTIFIER, op_name, op_tok.pos);
                this->advance();
            } else {
                res.failure(new InvalidSyntaxError("Expected method or field name after type(s)", this->current_tok.pos));
                return res.to_prs();
            }
            std::vector<GenericType> genericsM;
            if (this->current_tok.type == TokenType::LESS) {
                this->advance();
                while (true) {
                    GenericType curr;
                    if (this->current_tok.type != TokenType::IDENTIFIER) {
                        if (this->current_tok.type == TokenType::KEYWORD &&
                            std::unordered_set<std::string>({"int", "double", "float", "byte", "nibble", "addr_t", "string", "char", "bool", "qbool"})
                                .contains(this->current_tok.value)) {
                            curr.isNonType = true;
                            curr.nonTypeKind = this->current_tok.value;
                        } else if (this->current_tok.value == "long" || this->current_tok.value == "short") {
                            std::string prev = this->current_tok.value;
                            this->advance();
                            if (this->current_tok.value != "int" && this->current_tok.value != "double") {
                                res.failure(new InvalidSyntaxError("Expected 'int' or 'double' after '" + prev + "'", this->current_tok.pos));
                                return res.to_prs();
                            }
                            curr.isNonType = true;
                            curr.nonTypeKind = prev + " " + this->current_tok.value;
                        } else {
                            res.failure(new InvalidSyntaxError("Expected generic typename to be a identifier ([_a-zA-Z][0-9a-zA-Z_]*)",
                                                               this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                    }
                    curr.name = this->current_tok.value;
                    this->advance();
                    if (this->current_tok.type == TokenType::LPAREN && !curr.isNonType) {
                        this->advance();
                        if (this->current_tok.type != TokenType::COLON) {
                            if (this->current_tok.type == TokenType::IDENTIFIER &&
                                (this->current_tok.value == "usertype" || this->current_tok.value == "primitive" ||
                                 this->current_tok.value == "callable" || this->current_tok.value == "numeric" ||
                                 this->current_tok.value == "pointer")) {
                                curr.constraint = this->current_tok.value;
                            } else {
                                res.failure(new InvalidSyntaxError("Expected : or usertype:, primitive:, or callable: before generic constraint list",
                                                                   this->current_tok.pos));
                                return res.to_prs();
                            }
                            this->advance();
                        } else {
                            curr.constraint = "";
                        }
                        this->advance();
                        if (this->current_tok.type == TokenType::NOT) {
                            curr.negated = true;
                            this->advance();
                        }
                        while (this->current_tok.type == TokenType::IDENTIFIER || this->current_tok.type == TokenType::KEYWORD) {
                            curr.subconstraints.push_back(this->current_tok.value);
                            this->advance();
                            if (this->current_tok.type == TokenType::PIPE) { this->advance(); }
                        }
                        if (this->current_tok.type != TokenType::RPAREN) {
                            res.failure(new InvalidSyntaxError("Expected ) after generic type constraint list.", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                    }
                    if (this->current_tok.type == TokenType::EQ) {
                        this->advance();
                        curr.defaultValue = this->current_tok.value;
                        this->advance();
                    }
                    if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::MORE) {
                        res.failure(new InvalidSyntaxError("Expected > or , after generic type.", this->current_tok.pos));
                        return res.to_prs();
                    }
                    genericsM.push_back(curr);
                    if (this->current_tok.type == TokenType::MORE) {
                        this->advance();
                        break;
                    }
                    this->advance();
                }
            }
            if (this->current_tok.type == TokenType::LPAREN) {
                ClassMethodInfo mi;
                mi.name_tok = name_tok;
                if (!info.baseClassName.empty()) {
                    auto* base_ptr = find_type(base_type_name(baseName));
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

                auto m_pr = this->func_def_multi(type_list, std::make_optional(name_tok), genericsM, true);
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
                mi.is_volatile = is_volatile_method;
                mi.generics = genericsM;
                mi.is_static = is_static;
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
                field_type += "[";
                if (this->current_tok.type != TokenType::RBRACKET) {
                    field_type += this->current_tok.value;
                    this->advance();
                }
                if (this->current_tok.type != TokenType::RBRACKET) {
                    res.failure(new InvalidSyntaxError("QC-S061: Expected ']' after '[' in array", this->current_tok.pos));
                    return res.to_prs();
                }
                field_type += "]";
                this->advance();
            }
            AnyNode default_value = std::monostate{};
            if (this->current_tok.type == TokenType::EQ) {
                this->advance();
                default_value = res.reg(this->logical_or());
                if (res.error) return res.to_prs();
            }
            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(new InvalidSyntaxError("Expected ';' after field declaration", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            ClassField cf;
            cf.name = name_tok.value;
            cf.type = field_type;
            cf.access = access;
            cf.isStatic = is_static;
            cf.defaultValue = default_value;
            info.classFields.push_back(cf);
        }

        if (this->current_tok.type != TokenType::RBRACE) {
            res.failure(new InvalidSyntaxError("Expected '}' at end of class", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        full_key = currentNamespace.empty() ? class_name.value : currentNamespace + "::" + class_name.value;
        user_types[base_type_name(full_key)] = info;
        this->current_generics = saved_generics;
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

        return res.success(new NamespaceNode(nsName.value, body, nsName.pos));
    }
    if (tok.type == TokenType::KEYWORD && tok.value == "struct") {
        this->advance();

        if (this->current_tok.type != TokenType::IDENTIFIER) {
            res.failure(new InvalidSyntaxError("QC-S065: Expected struct name", this->current_tok.pos));
            return res.to_prs();
        }
        Token struct_name = this->current_tok;
        this->advance();
        std::vector<GenericType> generics;
        if (this->current_tok.type == TokenType::LESS) {
            this->advance();
            while (true) {
                GenericType curr;
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    if (this->current_tok.type == TokenType::KEYWORD &&
                        std::unordered_set<std::string>({"int", "double", "float", "byte", "nibble", "addr_t", "string", "char", "bool", "qbool"})
                            .contains(this->current_tok.value)) {
                        curr.isNonType = true;
                        curr.nonTypeKind = this->current_tok.value;
                    } else if (this->current_tok.value == "long" || this->current_tok.value == "short") {
                        std::string prev = this->current_tok.value;
                        this->advance();
                        if (this->current_tok.value != "int" && this->current_tok.value != "double") {
                            res.failure(new InvalidSyntaxError("Expected 'int' or 'double' after '" + prev + "'", this->current_tok.pos));
                            return res.to_prs();
                        }
                        curr.isNonType = true;
                        curr.nonTypeKind = prev + " " + this->current_tok.value;
                    } else {
                        res.failure(
                            new InvalidSyntaxError("Expected generic typename to be a identifier ([_a-zA-Z][0-9a-zA-Z_]*)", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                }
                curr.name = this->current_tok.value;
                this->advance();
                if (this->current_tok.type == TokenType::LPAREN && !curr.isNonType) {
                    this->advance();
                    if (this->current_tok.type != TokenType::COLON) {
                        if (this->current_tok.type == TokenType::IDENTIFIER &&
                            (this->current_tok.value == "usertype" || this->current_tok.value == "primitive" ||
                             this->current_tok.value == "callable" || this->current_tok.value == "numeric" || this->current_tok.value == "pointer")) {
                            curr.constraint = this->current_tok.value;
                        } else {
                            res.failure(new InvalidSyntaxError("Expected : or usertype:, primitive:, or callable: before generic constraint list",
                                                               this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                    } else {
                        curr.constraint = "";
                    }
                    this->advance();
                    if (this->current_tok.type == TokenType::NOT) {
                        curr.negated = true;
                        this->advance();
                    }
                    while (this->current_tok.type == TokenType::IDENTIFIER || this->current_tok.type == TokenType::KEYWORD) {
                        curr.subconstraints.push_back(this->current_tok.value);
                        this->advance();
                        if (this->current_tok.type == TokenType::PIPE) { this->advance(); }
                    }
                    if (this->current_tok.type != TokenType::RPAREN) {
                        res.failure(new InvalidSyntaxError("Expected ) after generic type constraint list.", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                }
                if (this->current_tok.type == TokenType::EQ) {
                    this->advance();
                    curr.defaultValue = this->current_tok.value;
                    this->advance();
                }
                if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::MORE) {
                    res.failure(new InvalidSyntaxError("Expected > or , after generic type.", this->current_tok.pos));
                    return res.to_prs();
                }
                generics.push_back(curr);
                if (this->current_tok.type == TokenType::MORE) {
                    this->advance();
                    break;
                }
                this->advance();
            }
        }
        auto saved_generics = this->current_generics;
        this->current_generics.insert(this->current_generics.end(), generics.begin(), generics.end());
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
                field_type = parseTypeString();
            } else if (this->current_tok.type == TokenType::KEYWORD) {
                field_type = parseTypeString();
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
        std::string full_key = currentNamespace.empty() ? struct_name.value : currentNamespace + "::" + struct_name.value;
        if (this->current_tok.type == TokenType::SEMICOLON) { this->advance(); }
        if (user_types.contains(base_type_name(full_key))) {
            res.failure(new InvalidSyntaxError("QC-UT01: Redefinition of struct '" + struct_name.value + "'", struct_name.pos));
            return res.to_prs();
        }
        UserTypeInfo info;
        info.baseFile = this->current_tok.pos.Filename;
        info.kind = UserTypeKind::Struct;
        info.fields = fields;
        info.generics = generics;
        info.namespace_path = currentNamespace;
        user_types[base_type_name(full_key)] = info;
        this->current_generics = std::move(saved_generics);
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
        std::vector<GenericType> generics;
        if (this->current_tok.type == TokenType::LESS) {
            this->advance();
            while (true) {
                GenericType curr;
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    if (this->current_tok.type == TokenType::KEYWORD &&
                        std::unordered_set<std::string>({"int", "double", "float", "byte", "nibble", "addr_t", "string", "char", "bool", "qbool"})
                            .contains(this->current_tok.value)) {
                        curr.isNonType = true;
                        curr.nonTypeKind = this->current_tok.value;
                    } else if (this->current_tok.value == "long" || this->current_tok.value == "short") {
                        std::string prev = this->current_tok.value;
                        this->advance();
                        if (this->current_tok.value != "int" && this->current_tok.value != "double") {
                            res.failure(new InvalidSyntaxError("Expected 'int' or 'double' after '" + prev + "'", this->current_tok.pos));
                            return res.to_prs();
                        }
                        curr.isNonType = true;
                        curr.nonTypeKind = prev + " " + this->current_tok.value;
                    } else {
                        res.failure(
                            new InvalidSyntaxError("Expected generic typename to be a identifier ([_a-zA-Z][0-9a-zA-Z_]*)", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                }
                curr.name = this->current_tok.value;
                this->advance();
                if (this->current_tok.type == TokenType::LPAREN && !curr.isNonType) {
                    this->advance();
                    if (this->current_tok.type != TokenType::COLON) {
                        if (this->current_tok.type == TokenType::IDENTIFIER &&
                            (this->current_tok.value == "usertype" || this->current_tok.value == "primitive" ||
                             this->current_tok.value == "callable" || this->current_tok.value == "numeric" || this->current_tok.value == "pointer")) {
                            curr.constraint = this->current_tok.value;
                        } else {
                            res.failure(new InvalidSyntaxError("Expected : or usertype:, primitive:, or callable: before generic constraint list",
                                                               this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                    } else {
                        curr.constraint = "";
                    }
                    this->advance();
                    if (this->current_tok.type == TokenType::NOT) {
                        curr.negated = true;
                        this->advance();
                    }
                    while (this->current_tok.type == TokenType::IDENTIFIER || this->current_tok.type == TokenType::KEYWORD) {
                        curr.subconstraints.push_back(this->current_tok.value);
                        this->advance();
                        if (this->current_tok.type == TokenType::PIPE) { this->advance(); }
                    }
                    if (this->current_tok.type != TokenType::RPAREN) {
                        res.failure(new InvalidSyntaxError("Expected ) after generic type constraint list.", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                }
                if (this->current_tok.type == TokenType::EQ) {
                    this->advance();
                    curr.defaultValue = this->current_tok.value;
                    this->advance();
                }
                if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::MORE) {
                    res.failure(new InvalidSyntaxError("Expected > or , after generic type.", this->current_tok.pos));
                    return res.to_prs();
                }
                generics.push_back(curr);
                if (this->current_tok.type == TokenType::MORE) {
                    this->advance();
                    break;
                }
                this->advance();
            }
        }
        auto saved_generics = this->current_generics;
        this->current_generics.insert(this->current_generics.end(), generics.begin(), generics.end());
        if (this->current_tok.type != TokenType::EQ) {
            res.failure(new InvalidSyntaxError("QC-S075: Expected '=' after type name '" + type_name.value + "'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        auto parse_type_atom = [&](Token first_tok) -> UnionMember {
            std::string type_str;
            switch (first_tok.type) {
            case TokenType::STRING: this->advance(); return UnionMember{"string:\"" + first_tok.value + "\""};
            case TokenType::INT: this->advance(); return UnionMember{"int:" + first_tok.value};
            case TokenType::FLOAT: this->advance(); return UnionMember{"float:" + first_tok.value};
            case TokenType::DOUBLE: this->advance(); return UnionMember{"double:" + first_tok.value};
            case TokenType::LONG_INT: this->advance(); return UnionMember{"long_int:" + first_tok.value};
            case TokenType::SHORT_INT: this->advance(); return UnionMember{"short_int:" + first_tok.value};
            case TokenType::LONG_DOUBLE: this->advance(); return UnionMember{"long_double:" + first_tok.value};
            case TokenType::ADDR_T: this->advance(); return UnionMember{"addr_t:" + first_tok.value};
            case TokenType::CHAR: this->advance(); return UnionMember{"char:" + first_tok.value};
            case TokenType::BYTE: this->advance(); return UnionMember{"byte:" + first_tok.value};
            case TokenType::NIBBLE: this->advance(); return UnionMember{"nibble:" + first_tok.value};
            case TokenType::BOOL: this->advance(); return UnionMember{"bool:" + first_tok.value};
            case TokenType::QBOOL: this->advance(); return UnionMember{"qbool:" + first_tok.value};
            default: break;
            }
            type_str = parseTypeString();
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
                   tt == TokenType::NIBBLE || tt == TokenType::FLOAT || tt == TokenType::DOUBLE || tt == TokenType::ADDR_T || tt == TokenType::BOOL ||
                   tt == TokenType::QBOOL || tt == TokenType::CHAR || tt == TokenType::LONG_INT || tt == TokenType::SHORT_INT ||
                   tt == TokenType::LONG_DOUBLE || tt == TokenType::BYTE;
        };

        if (!is_type_or_literal_token(this->current_tok.type)) {
            res.failure(new InvalidSyntaxError("QC-S076: Expected type or literal in type alias", this->current_tok.pos));
            return res.to_prs();
        }

        std::vector<UnionMember> members;
        {
            Token first_tok = this->current_tok;
            members.push_back(parse_type_atom(first_tok));
        }
        while (this->current_tok.type == TokenType::PIPE) {
            this->advance();

            if (!is_type_or_literal_token(this->current_tok.type)) {
                res.failure(new InvalidSyntaxError("QC-S077: Expected type or literal after '|' in type alias", this->current_tok.pos));
                return res.to_prs();
            }

            Token t = this->current_tok;
            members.push_back(parse_type_atom(t));
        }
        if (this->current_tok.type != TokenType::SEMICOLON) {
            res.failure(new MissingSemicolonError(this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        std::string full_key = currentNamespace.empty() ? type_name.value : currentNamespace + "::" + type_name.value;
        if (user_types.contains(base_type_name(full_key))) {
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
        info.baseFile = this->current_tok.pos.Filename;
        info.generics = generics;
        info.namespace_path = currentNamespace;
        user_types[base_type_name(full_key)] = info;
        this->current_generics = std::move(saved_generics);
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
            case TokenType::LONG_INT: return "long_int:" + tok.value;
            case TokenType::SHORT_INT: return "short_int:" + tok.value;
            case TokenType::LONG_DOUBLE: return "long_double:" + tok.value;
            case TokenType::ADDR_T: return "addr_t:" + tok.value;
            case TokenType::BYTE: return "byte:" + tok.value;
            case TokenType::NIBBLE: return "nibble:" + tok.value;
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
        std::string full_key = currentNamespace.empty() ? enum_name.value : currentNamespace + "::" + enum_name.value;
        if (user_types.contains(base_type_name(full_key))) {
            res.failure(new InvalidSyntaxError("QC-UT01: Redefinition of type '" + enum_name.value + "'", enum_name.pos));
            return res.to_prs();
        }
        UserTypeInfo info;
        info.kind = UserTypeKind::Enum;
        info.baseFile = this->current_tok.pos.Filename;
        info.members = members;
        info.enumEntries = entries;
        info.namespace_path = currentNamespace;
        user_types[base_type_name(full_key)] = info;
        return res.success(std::monostate{});
    }
    if (tok.type == TokenType::KEYWORD || tok.type == TokenType::IDENTIFIER && tok.value != "this") {
        if (tok.type == TokenType::IDENTIFIER) {
            Token saved_tok = this->current_tok;
            size_t saved_index = this->index;
            auto maybe_qualified = this->try_parse_qualified_name();
            bool is_type = false;
            if (maybe_qualified.has_value()) {
                std::string base = *maybe_qualified;
                size_t lc = base.rfind("::");
                if (lc != std::string::npos) base = base.substr(lc + 2);
                is_type = (find_type(base) != nullptr || find_type(*maybe_qualified) != nullptr || is_known_type(base) ||
                           is_known_type(*maybe_qualified));
            }
            if (!is_type) {
                if (!maybe_qualified.has_value()) this->parseTypeString();
                while (this->current_tok.type == TokenType::COMMA) {
                    this->advance();
                    this->parseTypeString();
                }
                bool looks_like_generic_func = (this->current_tok.type == TokenType::IDENTIFIER && peek(1).type == TokenType::LESS);
                if (!looks_like_generic_func) {
                    this->index = saved_index;
                    this->current_tok = saved_tok;
                    size_t next_i = index + 1;
                    if (next_i < tokens.size() && (tokens[next_i].type == TokenType::EQ || tokens[next_i].type == TokenType::PLUS_EQ ||
                                                   tokens[next_i].type == TokenType::MINUS_EQ || tokens[next_i].type == TokenType::MUL_EQ ||
                                                   tokens[next_i].type == TokenType::DIV_EQ || tokens[next_i].type == TokenType::MOD_EQ ||
                                                   tokens[next_i].type == TokenType::RSH_EQ || tokens[next_i].type == TokenType::LSH_EQ ||
                                                   tokens[next_i].type == TokenType::LRSH_EQ || tokens[next_i].type == TokenType::RROT_EQ ||
                                                   tokens[next_i].type == TokenType::LROT_EQ || tokens[next_i].type == TokenType::BIT_X_EQ ||
                                                   tokens[next_i].type == TokenType::BIT_O_EQ || tokens[next_i].type == TokenType::BIT_A_EQ)) {
                        AnyNode assign_node = res.reg(this->assignment_expr());
                        if (res.error) return res.to_prs();

                        if (this->current_tok.type != TokenType::SEMICOLON) {
                            res.failure(new MissingSemicolonError(this->current_tok.pos));
                            return res.to_prs();
                        }

                        this->advance();
                        return res.success(assign_node);
                    }
                    AnyNode node = res.reg(this->assignment_expr());
                    if (res.error) return res.to_prs();
                    if (this->current_tok.type == TokenType::SEMICOLON) {
                        this->advance();
                        return res.success(node);
                    }
                    res.failure(new MissingSemicolonError(this->current_tok.pos));
                    return res.to_prs();
                }
            }
            this->index = saved_index;
            this->current_tok = saved_tok;
        }
        bool is_const = false;
        if (tok.value == "const") {
            is_const = true;
            this->advance();
        }
        bool is_volatile = false;
        if (tok.value == "volatile") {
            is_volatile = true;
            this->advance();
        }
        if (this->current_tok.value == "volatile") {
            is_volatile = true;
            this->advance();
        }
        if (this->current_tok.value == "const") {
            is_const = true;
            this->advance();
        }
        Position type_pos = this->current_tok.pos;
        std::string type_str = parseTypeString();
        if (type_str.empty()) return res.to_prs();
        Token type_tok(TokenType::KEYWORD, type_str, type_pos);
        bool is_reference = type_str.ends_with("&");
        bool is_array = type_str.find("[]") != std::string::npos;
        if (type_str.find("[][]") != std::string::npos) {
            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(new InvalidSyntaxError("Multi-dimensional types can only be used in function returns", this->current_tok.pos));
                return res.to_prs();
            }
            Token func_name = this->current_tok;
            this->advance();
            std::vector<GenericType> genericsM;
            if (this->current_tok.type == TokenType::LESS) {
                this->advance();
                while (true) {
                    GenericType curr;
                    if (this->current_tok.type != TokenType::IDENTIFIER) {
                        if (this->current_tok.type == TokenType::KEYWORD &&
                            std::unordered_set<std::string>({"int", "double", "float", "byte", "nibble", "addr_t", "string", "char", "bool", "qbool"})
                                .contains(this->current_tok.value)) {
                            curr.isNonType = true;
                            curr.nonTypeKind = this->current_tok.value;
                        } else if (this->current_tok.value == "long" || this->current_tok.value == "short") {
                            std::string prev = this->current_tok.value;
                            this->advance();
                            if (this->current_tok.value != "int" && this->current_tok.value != "double") {
                                res.failure(new InvalidSyntaxError("Expected 'int' or 'double' after '" + prev + "'", this->current_tok.pos));
                                return res.to_prs();
                            }
                            curr.isNonType = true;
                            curr.nonTypeKind = prev + " " + this->current_tok.value;
                        } else {
                            res.failure(new InvalidSyntaxError("Expected generic typename to be a identifier ([_a-zA-Z][0-9a-zA-Z_]*)",
                                                               this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                    }
                    curr.name = this->current_tok.value;
                    this->advance();
                    if (this->current_tok.type == TokenType::LPAREN && !curr.isNonType) {
                        this->advance();
                        if (this->current_tok.type != TokenType::COLON) {
                            if (this->current_tok.type == TokenType::IDENTIFIER &&
                                (this->current_tok.value == "usertype" || this->current_tok.value == "primitive" ||
                                 this->current_tok.value == "callable" || this->current_tok.value == "numeric" ||
                                 this->current_tok.value == "pointer")) {
                                curr.constraint = this->current_tok.value;
                            } else {
                                res.failure(new InvalidSyntaxError("Expected : or usertype:, primitive:, or callable: before generic constraint list",
                                                                   this->current_tok.pos));
                                return res.to_prs();
                            }
                            this->advance();
                        } else {
                            curr.constraint = "";
                        }
                        this->advance();
                        if (this->current_tok.type == TokenType::NOT) {
                            curr.negated = true;
                            this->advance();
                        }
                        while (this->current_tok.type == TokenType::IDENTIFIER || this->current_tok.type == TokenType::KEYWORD) {
                            curr.subconstraints.push_back(this->current_tok.value);
                            this->advance();
                            if (this->current_tok.type == TokenType::PIPE) { this->advance(); }
                        }
                        if (this->current_tok.type != TokenType::RPAREN) {
                            res.failure(new InvalidSyntaxError("Expected ) after generic type constraint list.", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                    }
                    if (this->current_tok.type == TokenType::EQ) {
                        this->advance();
                        curr.defaultValue = this->current_tok.value;
                        this->advance();
                    }
                    if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::MORE) {
                        res.failure(new InvalidSyntaxError("Expected > or , after generic type.", this->current_tok.pos));
                        return res.to_prs();
                    }
                    genericsM.push_back(curr);
                    if (this->current_tok.type == TokenType::MORE) {
                        this->advance();
                        break;
                    }
                    this->advance();
                }
            }
            if (this->current_tok.type == TokenType::LPAREN) return this->func_def_multi({type_tok}, func_name, genericsM, false, is_volatile);
            res.failure(new InvalidSyntaxError("Expected '(' after function name", this->current_tok.pos));
            return res.to_prs();
        }
        std::vector<Token> return_types = {type_tok};
        if (this->current_tok.type == TokenType::COMMA) {
            size_t peek_idx = this->index + 1;
            bool is_multi_return = false;
            if (peek_idx < tokens.size()) {
                Token peek = tokens[peek_idx];
                if (peek.type == TokenType::KEYWORD) {
                    is_multi_return = true;
                } else if (peek.type == TokenType::IDENTIFIER) {
                    size_t saved = this->index;
                    Token saved_cur = this->current_tok;
                    this->advance();
                    auto peek_qual = this->try_parse_qualified_name();
                    if (peek_qual.has_value()) {
                        std::string base = *peek_qual;
                        size_t lc = base.rfind("::");
                        if (lc != std::string::npos) base = base.substr(lc + 2);
                        is_multi_return = (find_type(base) != nullptr || is_known_type(*peek_qual));
                    }
                    this->index = saved;
                    this->current_tok = saved_cur;
                }
            }
            if (is_multi_return) {
                while (this->current_tok.type == TokenType::COMMA) {
                    this->advance();
                    Position next_pos = this->current_tok.pos;
                    std::string next_str = parseTypeString();
                    if (next_str.empty()) return res.to_prs();
                    return_types.push_back(Token(TokenType::KEYWORD, next_str, next_pos));
                }
            }
        }
        if (this->current_tok.type != TokenType::IDENTIFIER) {
            res.failure(new InvalidSyntaxError("QC-S085: Expected identifier", this->current_tok.pos));
            return res.to_prs();
        }
        Token name_tok = this->current_tok;
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
        if (dimensions > 0) is_array = true;
        std::vector<GenericType> genericsM;
        if (this->current_tok.type == TokenType::LESS) {
            this->advance();
            while (true) {
                GenericType curr;
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    if (this->current_tok.type == TokenType::KEYWORD &&
                        std::unordered_set<std::string>({"int", "double", "float", "byte", "nibble", "addr_t", "string", "char", "bool", "qbool"})
                            .contains(this->current_tok.value)) {
                        curr.isNonType = true;
                        curr.nonTypeKind = this->current_tok.value;
                    } else if (this->current_tok.value == "long" || this->current_tok.value == "short") {
                        std::string prev = this->current_tok.value;
                        this->advance();
                        if (this->current_tok.value != "int" && this->current_tok.value != "double") {
                            res.failure(new InvalidSyntaxError("Expected 'int' or 'double' after '" + prev + "'", this->current_tok.pos));
                            return res.to_prs();
                        }
                        curr.isNonType = true;
                        curr.nonTypeKind = prev + " " + this->current_tok.value;
                    } else {
                        res.failure(
                            new InvalidSyntaxError("Expected generic typename to be a identifier ([_a-zA-Z][0-9a-zA-Z_]*)", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                }
                curr.name = this->current_tok.value;
                this->advance();
                if (this->current_tok.type == TokenType::LPAREN && !curr.isNonType) {
                    this->advance();
                    if (this->current_tok.type != TokenType::COLON) {
                        if (this->current_tok.type == TokenType::IDENTIFIER &&
                            (this->current_tok.value == "usertype" || this->current_tok.value == "primitive" ||
                             this->current_tok.value == "callable" || this->current_tok.value == "numeric" || this->current_tok.value == "pointer")) {
                            curr.constraint = this->current_tok.value;
                        } else {
                            res.failure(new InvalidSyntaxError("Expected : or usertype:, primitive:, or callable: before generic constraint list",
                                                               this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                    } else {
                        curr.constraint = "";
                    }
                    this->advance();
                    if (this->current_tok.type == TokenType::NOT) {
                        curr.negated = true;
                        this->advance();
                    }
                    while (this->current_tok.type == TokenType::IDENTIFIER || this->current_tok.type == TokenType::KEYWORD) {
                        curr.subconstraints.push_back(this->current_tok.value);
                        this->advance();
                        if (this->current_tok.type == TokenType::PIPE) { this->advance(); }
                    }
                    if (this->current_tok.type != TokenType::RPAREN) {
                        res.failure(new InvalidSyntaxError("Expected ) after generic type constraint list.", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                }
                if (this->current_tok.type == TokenType::EQ) {
                    this->advance();
                    curr.defaultValue = this->current_tok.value;
                    this->advance();
                }
                if (this->current_tok.type != TokenType::COMMA && this->current_tok.type != TokenType::MORE) {
                    res.failure(new InvalidSyntaxError("Expected > or , after generic type.", this->current_tok.pos));
                    return res.to_prs();
                }
                genericsM.push_back(curr);
                if (this->current_tok.type == TokenType::MORE) {
                    this->advance();
                    break;
                }
                this->advance();
            }
        }

        if (this->current_tok.type == TokenType::LPAREN) {
            auto func_def = res.reg(this->func_def_multi(return_types, name_tok, genericsM, false, is_volatile));
            if (res.error) return res.to_prs();
            return res.success(func_def);
        }
        if (is_volatile) { type_tok.value = "volatile " + type_tok.value; }
        if (this->current_tok.type == TokenType::COMMA) {
            std::vector<Token> var_names = {name_tok};
            std::vector<Token> var_types = {type_tok};
            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                Position next_pos = this->current_tok.pos;
                std::string next_str = parseTypeString();
                if (next_str.empty()) return res.to_prs();
                var_types.push_back(Token(TokenType::KEYWORD, next_str, next_pos));
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(new InvalidSyntaxError("QC-S085: Expected identifier", this->current_tok.pos));
                    return res.to_prs();
                }
                var_names.push_back(this->current_tok);
                this->advance();
            }
            if (this->current_tok.type != TokenType::EQ) {
                res.failure(new InvalidSyntaxError("Expected '=' in multi-variable declaration", name_tok.pos));
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
            if (var_types.size() != var_names.size()) {
                res.failure(new InvalidSyntaxError("Number of types must match number of variables", var_names[0].pos));
                return res.to_prs();
            }
            return res.success(new MultiVarDeclNode(is_const, var_types, var_names, value));
        }
        if (return_types.size() > 1) {
            std::vector<Token> var_names = {name_tok};
            std::vector<Token> var_types = {type_tok};
            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                Position next_pos = this->current_tok.pos;
                std::string next_str = parseTypeString();
                if (next_str.empty()) return res.to_prs();
                var_types.push_back(Token(TokenType::KEYWORD, next_str, next_pos));
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(new InvalidSyntaxError("QC-S085: Expected identifier", this->current_tok.pos));
                    return res.to_prs();
                }
                var_names.push_back(this->current_tok);
                this->advance();
            }
            if (this->current_tok.type != TokenType::EQ) {
                res.failure(new InvalidSyntaxError("Expected '=' in multi-variable declaration", name_tok.pos));
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
            if (var_types.size() != var_names.size()) {
                res.failure(new InvalidSyntaxError("Number of types must match number of variables", var_names[0].pos));
                return res.to_prs();
            }
            return res.success(new MultiVarDeclNode(is_const, var_types, var_names, value));
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
                    res.failure(new InvalidSyntaxError("QC-R001: Cannot assign an expression to a reference.", name_tok.pos));
                    return res.to_prs();
                }
                Token target = this->current_tok;
                this->advance();
                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(new MissingSemicolonError(this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                return res.success(RefVarDeclNode(type_tok, name_tok, target, type_tok.pos));
            }
            value = res.reg(this->qout_expr());
            if (res.error) return res.to_prs();
        } else {
            if (is_const || is_reference) {
                res.failure(new InvalidSyntaxError("QC-T007: const variables and references must be initialized", name_tok.pos));
                return res.to_prs();
            }
            value = default_value_for_type(type_tok, name_tok.pos);
        }
        if (this->current_tok.type != TokenType::SEMICOLON) {
            res.failure(new MissingSemicolonError(this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        return res.success(new VarAssignNode(is_const, type_tok, name_tok, value, this->in_foreign));
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
enum class MainType { NA, RT_ARRAY, C_STYLE };
MainType main_type = MainType::NA;
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
                            throw InvalidSyntaxError("the entrypoint must return int, not " + actual, get_pos(arg));
                        }
                        if (!arg->params.empty() && (arg->params.front().type.value != "string[]" &&
                                                     ((((arg->params.size())) == 2 &&
                                                       (arg->params.front().type.value != "int" || arg->params.back().type.value != "char**"))))) {
                            throw InvalidSyntaxError(
                                "the entrypoint must have no parameters, take a integer argc and a char** argv, or take a array of strings.",
                                get_pos(arg));
                        }
                        if (!arg->params.empty()) {
                            if (arg->params.front().type.value == "string[]") {
                                main_type = MainType::RT_ARRAY;
                            } else {
                                main_type = MainType::C_STYLE;
                            }
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
        return Aer{nullptr,
                   new Error("Missing the entrypoint function", "Program must have an 'int entrypointname()' function", Position("", "", 0, 0, 0))};
    }
    for (auto& [name, ut] : user_types) {
        if (ut.kind == UserTypeKind::Class && !ut.baseClassName.empty()) {
            std::string baseKey = ut.baseClassName;
            if (baseKey.find("::") == std::string::npos) {
                bool found = false;
                for (auto& [key, info] : user_types) {
                    if (key.find(base_type_name(baseKey)) != std::string::npos && info.kind == UserTypeKind::Class) {
                        baseKey = key;
                        found = true;
                        break;
                    }
                }
                if (!found) { throw InvalidSyntaxError("Base class '" + ut.baseClassName + "' not found", Position()); }
            }

            auto it = user_types.find(base_type_name(baseKey));
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
llvm::Type* LLVMCompiler::llvmTypeFor(std::string qcType) {
    if (currentGenericTypes.find(qcType) != currentGenericTypes.end()) { return currentGenericTypes[qcType]; }
    if (!currentGenericTypeStrings.empty()) {
        std::string substituted = substituteGenerics(qcType);
        if (substituted != qcType) qcType = substituted;
    }
    std::string type = resolveTypeName(qcType, false);
    type = resolveTypeName(type, false);
    if (type == "...") { return builder->getPtrTy(); }
    if (type.ends_with("[]")) { return llvm::PointerType::get(context, 0); }
    if (type.ends_with("]")) {
        size_t open = type.rfind('[');
        if (open == std::string::npos) {
            cg_error(Position(), "malformed array type");
            return nullptr;
        }
        std::string sizeStr = type.substr(open + 1, type.size() - open - 2);
        size_t count;
        try {
            count = parseInteger(sizeStr);
        } catch (...) {
            cg_error(Position(), "invalid array size: " + sizeStr);
            return nullptr;
        }
        std::string elementType = type.substr(0, open);
        llvm::Type* elemTy = llvmTypeFor(elementType);
        return llvm::ArrayType::get(elemTy, count);
    }
    if (type.ends_with("&") || type.ends_with("*")) { return builder->getPtrTy(); }
    if (type == "int") return builder->getInt32Ty();
    if (type == "short int") return builder->getInt16Ty();
    if (type == "long int") return builder->getIntNTy(getPtrSize());
    if (type == "float") return builder->getFloatTy();
    if (type == "double") return builder->getDoubleTy();
    if (type == "long double") return builder->getDoubleTy();
    if (type == "nibble") return builder->getIntNTy(4);
    if (type == "addr_t") return builder->getIntNTy(getPtrSize());
    if (type == "char" || type == "byte") return builder->getInt8Ty();
    if (type == "bool") return builder->getInt1Ty();
    if (type == "qbool") return builder->getIntNTy(2);
    if (type == "string") return llvm::PointerType::get(context, 0);
    if (type == "@nullptr") return builder->getPtrTy();
    if (classTypes.find(type) != classTypes.end() || genericClasses.find(baseTypeName(type)) != genericClasses.end()) {
        return genericiseOrFindClass(resolveTypeName(qcType, false));
    }
    if (structTypes.find(type) != structTypes.end() || genericStructs.find(baseTypeName(type)) != genericStructs.end()) {
        return genericiseOrFindStruct(type);
    }
    if (enumTypes.find(type) != enumTypes.end()) { return enumTypes[type]; }
    if (unionTypes.find(type) != unionTypes.end() || genericUnions.find(baseTypeName(type)) != genericUnions.end()) {
        genericiseOrFindUnion(type);
        return unionTypes[type];
    }
    if (type == "function" || type == "fn" || type.starts_with("fn (") || type.starts_with("fn(")) { return builder->getPtrTy(); }
    if (type == "void") return builder->getVoidTy();
    return nullptr;
}
llvm::StructType* LLVMCompiler::generateGenericClass(std::string className, UserTypeInfo classInfo, std::vector<std::string> genericParams) {
    std::string mangled_class_name = className + "<";
    for (int j = 0; j < classInfo.generics.size(); j++) {
        std::string val;
        if (genericParams.size() <= j) {
            val = classInfo.generics[j].defaultValue;
        } else {
            val = genericParams[j];
        }
        mangled_class_name += val;
        if (j != classInfo.generics.size() - 1) { mangled_class_name += ","; }
    }
    mangled_class_name += ">";
    if (inProgressGenerics.count(mangled_class_name)) return nullptr;
    if (classTypes.find(mangled_class_name) != classTypes.end()) { return genericiseOrFindClass(mangled_class_name); }
    llvm::StructType* classTy = getOrCreateStructType(mangled_class_name);
    classTypes[mangled_class_name] = classTy;
    inProgressGenerics.insert(mangled_class_name);
    llvm::BasicBlock* savedBlock = builder->GetInsertBlock();
    llvm::BasicBlock::iterator savedPoint = builder->GetInsertPoint();
    auto oldGenericTypes = this->currentGenericTypes;
    auto oldGenericTypeStrings = currentGenericTypeStrings;
    auto oldNonTypeGenerics = currentNonTypeGenericValues;
    for (int i = 0; i < classInfo.generics.size(); i++) {
        GenericType generic = classInfo.generics[i];
        if (genericParams.size() <= i) {
            if (generic.defaultValue.empty()) {
                cg_error(Position(), "too few generic params for class " + className);
                return nullptr;
            }
        }
        std::string value;
        if ((!generic.defaultValue.empty()) && genericParams.size() <= i) {
            value = generic.defaultValue;
        } else {
            value = genericParams[i];
        }
        if (!generic.isNonType && !generic.isVariadic) {
            if (generic.constraint == "pointer") {
                if (!(value.ends_with("*"))) {
                    cg_error(Position(), "pointer generic constrain " + generic.name + " expectes pointer type, got " + value);
                    return nullptr;
                }
            } else if (generic.constraint == "numeric") {
                if (!(std::unordered_set<std::string>({"int", "double", "float", "byte", "nibble", "addr_t", "long double", "short int", "long int"})
                          .contains(value))) {
                    cg_error(Position(), "numeric generic constrain " + generic.name + " expectes numeric type, got " + value);
                    return nullptr;
                }
            } else if (generic.constraint == "primitive" || generic.constraint == "usertype") {
                static const std::unordered_set<std::string> native_types = {
                    "int", "double", "float", "addr_t", "long double", "short int", "long int", "char", "bool", "byte", "nibble", "qbool", "string"};
                auto clean_view = value | std::views::filter([](char c) { return c != '*' && c != '&' && c != '[' && c != ']'; });
                if (native_types.contains(std::string(clean_view.begin(), clean_view.end()))) {
                    if (generic.constraint == "usertype") {
                        cg_error(Position(), "usertype generic constrain " + generic.name + " expectes usertype type, got " + value);
                        return nullptr;
                    }
                } else {
                    if (generic.constraint == "primitive") {
                        cg_error(Position(), "primitive generic constrain " + generic.name + " expectes primitive type, got " + value);
                        return nullptr;
                    }
                }
            }
            if (!generic.subconstraints.empty()) {
                if (generic.negated) {
                    for (std::string subconstraint : generic.subconstraints) {
                        if (value == subconstraint) {
                            cg_error(Position(), "generic constrain !" + value + " in generic " + generic.name + " does not except type " + value);
                            return nullptr;
                        }
                    }
                } else {
                    bool is_valid = false;
                    for (std::string subconstraint : generic.subconstraints) {
                        if (value == subconstraint) { is_valid = true; }
                    }
                    if (!is_valid) {
                        cg_error(Position(), "generic constrait " + generic.name + " does not except type " + value);
                        return nullptr;
                    }
                }
            }
            currentGenericTypes[generic.name] = llvmTypeFor(value);
            currentGenericTypeStrings[generic.name] = value;
        } else if (generic.isNonType) {
            GenericType generic = classInfo.generics[i];
            if (genericParams.size() <= i) {
                if (generic.defaultValue.empty()) {
                    cg_error(Position(), "too few generic params for class " + className);
                    return nullptr;
                }
            }
            std::string gname = generic.name;
            generic.name = genericParams[i];
            currentNonTypeGenericValues[gname] = generic;
        }
    }
    auto oldNamespaceStack = namespaceStack;
    namespaceStack.clear();
    if (!classInfo.namespace_path.empty()) {
        size_t start = 0;
        size_t pos;
        while ((pos = classInfo.namespace_path.find("::", start)) != std::string::npos) {
            namespaceStack.push_back(classInfo.namespace_path.substr(start, pos - start));
            start = pos + 2;
        }
        namespaceStack.push_back(classInfo.namespace_path.substr(start));
    }
    std::vector<llvm::Type*> fieldTypes;
    std::function<void(const std::string&, std::unordered_map<std::string, std::string>)> collectFields =
        [&](const std::string& classame, std::unordered_map<std::string, std::string> genericSubs) {
            auto it = userTypes.find(this->baseTypeName(classame));
            if (it == userTypes.end()) { throw std::string("Class not found: ") + classame; }
            auto& classIfo = it->second;
            if (!classIfo.baseClassName.empty()) {
                std::string baseFullName = classIfo.baseClassName;
                for (auto& [gname, gval] : genericSubs) {
                    size_t pos;
                    while ((pos = baseFullName.find(gname)) != std::string::npos) baseFullName.replace(pos, gname.size(), gval);
                }
                std::unordered_map<std::string, std::string> baseSubs;
                std::string baseRaw = this->baseTypeName(baseFullName);
                auto baseIt = userTypes.find(baseRaw);
                if (baseIt != userTypes.end()) {
                    auto& baseInfo = baseIt->second;
                    genericiseOrFindClass(baseFullName);
                    auto baseArgs = genericParamsFromName(baseFullName);
                    for (size_t i = 0; i < baseInfo.generics.size() && i < baseArgs.size(); i++) {
                        baseSubs[baseInfo.generics[i].name] = baseArgs[i];
                    }
                }
                collectFields(baseFullName, baseSubs);
            }
            for (auto& field : classIfo.classFields) {
                std::string resolvedType = field.type;
                if (field.name == "__vptr") {
                    resolvedType = mangled_class_name + "*";
                } else {
                    for (auto& [gname, gval] : genericSubs) {
                        size_t pos;
                        while ((pos = resolvedType.find(gname)) != std::string::npos) resolvedType.replace(pos, gname.size(), gval);
                    }
                }
                if (field.isStatic) {
                    llvm::Type* fieldTy = llvmTypeFor(resolvedType);
                    std::string mangledName = mangled_class_name + "::" + field.name;
                    if (!module->getNamedGlobal(mangledName)) {
                        llvm::Constant* initVal = !std::holds_alternative<std::monostate>(field.defaultValue)
                                                      ? llvm::dyn_cast<llvm::Constant>(emitExpr(field.defaultValue))
                                                      : llvm::Constant::getNullValue(fieldTy);

                        if (!initVal) { initVal = llvm::Constant::getNullValue(fieldTy); }
                        globals[mangledName] = new llvm::GlobalVariable(*module, fieldTy, false, llvm::GlobalValue::ExternalLinkage, initVal,
                                                                        mangledName);
                        varTypes[mangledName] = resolvedType;
                        volatileVars[mangledName] = false;
                    }
                } else {
                    fieldTypes.push_back(llvmTypeFor(resolvedType));
                }
            }
        };
    std::unordered_map<std::string, std::string> rootSubs;
    for (size_t i = 0; i < classInfo.generics.size() && i < genericParams.size(); i++) { rootSubs[classInfo.generics[i].name] = genericParams[i]; }
    collectFields(mangled_class_name, rootSubs);
    classTypes[mangled_class_name]->setBody(fieldTypes);
    if (!classInfo.baseClassName.empty()) {
        auto base_it = userTypes.find(resolveTypeName(classInfo.baseClassName));
        if (base_it != userTypes.end()) {
            auto& baseInfo = base_it->second;
            for (auto& method : classInfo.classMethods) {
                for (auto& baseMethod : baseInfo.classMethods) {
                    if (baseMethod.name_tok.value == method.name_tok.value && baseMethod.is_final) {
                        cg_error(method.name_tok.pos, "cannot override final method '" + baseMethod.name_tok.value + "' from base class '" +
                                                          classInfo.baseClassName + "'");
                    }
                }
            }
        }
    }
    std::vector<llvm::Constant*> vtableFuncs;
    std::vector<std::string> slotOrder;
    std::unordered_map<std::string, int> nameCounts;
    for (auto& method : classInfo.classMethods) { nameCounts[method.name_tok.value]++; }
    for (size_t methodIdx = 0; methodIdx < classInfo.classMethods.size(); methodIdx++) {
        auto& method = classInfo.classMethods[methodIdx];
        if (method.is_static) continue;
        if (method.is_constructor && classInfo.is_abstract_class) {
            cg_error(method.name_tok.pos, "cannot make a constructor on a abstract class.");
            continue;
        }
        if (std::find(genericMethodIndices[baseTypeName(className)].begin(), genericMethodIndices[baseTypeName(className)].end(), methodIdx) !=
            genericMethodIndices[baseTypeName(className)].end()) {
            continue;
        }
        std::string methodName = mangled_class_name + "_" + method.name_tok.value;
        if (nameCounts[method.name_tok.value] > 1) {
            for (auto& param : method.params) { methodName += "_" + (param.signature.has_value() ? std::string("fn") : param.type.value); }
        }
        std::vector<llvm::Type*> paramTypes;
        paramTypes.push_back(llvm::PointerType::get(context, 0));
        llvm::FunctionType* baseFuncTy = llvmFuncTypeFor(method.return_types, method.params);
        for (auto* paramTy : baseFuncTy->params()) { paramTypes.push_back(paramTy); }
        llvm::FunctionType* fnTy = llvm::FunctionType::get(baseFuncTy->getReturnType(), paramTypes, false);
        llvm::Function* fn = module->getFunction(methodName);
        if (!fn) { fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, methodName, module); }
        llvm::SmallVector<llvm::Metadata*, 4> retTypes;
        for (auto& ret : method.return_types) { retTypes.push_back(llvm::MDString::get(context, ret.value)); }
        fn->setMetadata("qc.return_types", llvm::MDNode::get(context, retTypes));
        if (method.is_volatile) {
            fn->addFnAttr(llvm::Attribute::NoInline);
            fn->addFnAttr(llvm::Attribute::OptimizeNone);
            fn->addFnAttr("noipa");
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
        classMethods[mangled_class_name][method.name_tok.value].push_back(fn);
        vtableFuncs.push_back(fn);
        slotOrder.push_back(methodName);
    }
    for (size_t i = 0; i < slotOrder.size(); i++) { vtableSlotIndex[mangled_class_name][slotOrder[i]] = i; }
    auto* arrTy = llvm::ArrayType::get(llvm::PointerType::get(context, 0), vtableFuncs.size());
    auto* vtableInit = llvm::ConstantArray::get(arrTy, vtableFuncs);
    auto* vtable = getOrCreateVtable(mangled_class_name + "_vtable", arrTy, isHeader || classInfo.baseFile.ends_with(".hqc") ? nullptr : vtableInit);
    vtables[mangled_class_name] = vtable;
    for (size_t methodIdx = 0; methodIdx < classInfo.classMethods.size(); methodIdx++) {
        auto& method = classInfo.classMethods[methodIdx];
        if (!method.is_static) continue;
        std::string mangledName = mangled_class_name + "::" + method.name_tok.value;
        if (nameCounts[method.name_tok.value] > 1) {
            for (auto& param : method.params) { mangledName += "_" + (param.signature.has_value() ? std::string("fn") : param.type.value); }
        }
        llvm::FunctionType* fnTy = llvmFuncTypeFor(method.return_types, method.params);
        llvm::Function* fn = module->getFunction(mangledName);
        if (!fn) { fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, mangledName, module); }
        llvm::SmallVector<llvm::Metadata*, 4> retTypes;
        for (auto& ret : method.return_types) { retTypes.push_back(llvm::MDString::get(context, ret.value)); }
        if (method.is_volatile) {
            fn->addFnAttr(llvm::Attribute::NoInline);
            fn->addFnAttr(llvm::Attribute::OptimizeNone);
            fn->addFnAttr("noipa");
        }
        fn->setMetadata("qc.return_types", llvm::MDNode::get(context, retTypes));
        for (size_t i = 0; i < method.params.size(); i++) {
            if (method.params[i].type.value.starts_with("out ")) {
                fn->addParamAttr(i, llvm::Attribute::WriteOnly);
                fn->addParamAttr(i, llvm::Attribute::getWithCaptureInfo(context, llvm::CaptureInfo::none()));
            } else if (method.params[i].type.value.starts_with("inout ")) {
                fn->addParamAttr(i, llvm::Attribute::getWithCaptureInfo(context, llvm::CaptureInfo::none()));
            }
            if (method.params[i].type.value.ends_with("restrict")) { fn->addParamAttr(i, llvm::Attribute::NoAlias); }
        }
        functionDefs[mangledName] = funcDefFromClassMethod(method, mangled_class_name);
    }
    for (size_t methodIdx = 0; methodIdx < classInfo.classMethods.size(); methodIdx++) {
        auto& method = classInfo.classMethods[methodIdx];
        if (method.is_static) continue;
        if (std::find(genericMethodIndices[baseTypeName(className)].begin(), genericMethodIndices[baseTypeName(className)].end(), methodIdx) !=
            genericMethodIndices[baseTypeName(className)].end()) {
            continue;
        }
        llvm::Function* fn = nullptr;
        auto& overloads = classMethods[mangled_class_name][method.name_tok.value];
        for (auto* overload : overloads) {
            if (overload->arg_size() - 1 == method.params.size()) {
                bool matches = true;
                for (size_t i = 0; i < method.params.size(); i++) {
                    auto& param = method.params[i];
                    llvm::Type* expectedType;
                    if (param.signature.has_value()) {
                        expectedType = llvm::PointerType::get(context, 0);
                    } else {
                        std::string resolvedType = resolveTypeName(param.type.value, false);
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
        if (isHeader || classInfo.baseFile.ends_with(".hqc")) continue;
        if (!fn || !fn->empty()) continue;

        llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", fn);
        builder->SetInsertPoint(entry);

        auto oldThis = currentThis;
        auto oldClassName = currentClassName;
        auto oldFunction = currentFunction;
        enterScope();
        currentThis = fn->getArg(0);
        volatileVars["this"] = false;
        varTypes["this"] = mangled_class_name;
        currentClassName = mangled_class_name;
        currentFunction = fn;

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
        size_t bodyStartIdx = 0;
        if (method.is_constructor && !classInfo.baseClassName.empty()) {
            if (method.body && !method.body->statements.empty()) {
                auto& firstStmt = method.body->statements[0];
                if (auto call = std::get_if<CallNode*>(&firstStmt)) {
                    if (auto varAccess = std::get_if<VarAccessNode*>(&(*call)->node_to_call)) {
                        std::string callName = (*varAccess)->var_name_tok.value;
                        if (callName == classInfo.baseClassName) {
                            std::vector<llvm::Value*> parentArgs;
                            for (auto& argNode : (*call)->arg_nodes) {
                                llvm::Value* arg = emitExpr(argNode);
                                if (!arg) continue;
                                parentArgs.push_back(arg);
                            }
                            llvm::Function* parentCtor = findMethodOverload(classInfo.baseClassName, classInfo.baseClassName, parentArgs);
                            if (parentCtor) {
                                std::vector<llvm::Value*> allArgs = {currentThis};
                                allArgs.insert(allArgs.end(), parentArgs.begin(), parentArgs.end());
                                if (insideTry()) {
                                    auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++),
                                                                           currentFunction);
                                    builder->CreateInvoke(parentCtor, contBB, currentLandingPad(), allArgs);
                                    builder->SetInsertPoint(contBB);
                                } else {
                                    builder->CreateCall(parentCtor, allArgs);
                                }
                                bodyStartIdx = 1;
                            } else {
                                Position pos = get_pos(*call);
                                cg_error(pos, "parent class `" + classInfo.baseClassName + "` has no matching constructor");
                                addConstructorNotes(classInfo.baseClassName, parentArgs, pos);
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
        exitScope();
    }
    namespaceStack = oldNamespaceStack;
    this->currentGenericTypes = oldGenericTypes;
    this->currentGenericTypeStrings = oldGenericTypeStrings;
    currentNonTypeGenericValues = oldNonTypeGenerics;
    if (savedBlock) { builder->SetInsertPoint(savedBlock, savedPoint); }
    inProgressGenerics.erase(mangled_class_name);
    return classTy;
}
llvm::StructType* LLVMCompiler::generateGenericStruct(std::string structName, UserTypeInfo structInfo, std::vector<std::string> genericParams) {
    std::string mangled_struct_name = structName + "<";
    for (int j = 0; j < structInfo.generics.size(); j++) {
        std::string val;
        if (genericParams.size() <= j) {
            val = structInfo.generics[j].defaultValue;
        } else {
            val = genericParams[j];
        }
        mangled_struct_name += val;
        if (j != structInfo.generics.size() - 1) { mangled_struct_name += ","; }
    }
    mangled_struct_name += ">";
    if (inProgressGenerics.count(mangled_struct_name)) return nullptr;
    if (structTypes.find(mangled_struct_name) != structTypes.end()) { return genericiseOrFindStruct(mangled_struct_name); }
    llvm::StructType* structTy = getOrCreateStructType(mangled_struct_name);
    structTypes[mangled_struct_name] = structTy;
    inProgressGenerics.insert(mangled_struct_name);
    auto oldGenericTypes = this->currentGenericTypes;
    auto oldGenericTypeStrings = currentGenericTypeStrings;
    auto oldNonTypeGenerics = currentNonTypeGenericValues;
    for (int i = 0; i < structInfo.generics.size(); i++) {
        GenericType generic = structInfo.generics[i];
        if (genericParams.size() <= i) {
            if (generic.defaultValue.empty()) {
                cg_error(Position(), "too few generic params for struct " + structName);
                return nullptr;
            }
        }
        std::string value;
        if ((!generic.defaultValue.empty()) && genericParams.size() <= i) {
            value = generic.defaultValue;
        } else {
            value = genericParams[i];
        }
        if (!generic.isNonType && !generic.isVariadic) {
            if (generic.constraint == "pointer") {
                if (!(value.ends_with("*"))) {
                    cg_error(Position(), "pointer generic constrain " + generic.name + " expectes pointer type, got " + value);
                    return nullptr;
                }
            } else if (generic.constraint == "numeric") {
                if (!(std::unordered_set<std::string>({"int", "double", "float", "byte", "nibble", "addr_t", "long double", "short int", "long int"})
                          .contains(value))) {
                    cg_error(Position(), "numeric generic constrain " + generic.name + " expectes numeric type, got " + value);
                    return nullptr;
                }
            } else if (generic.constraint == "primitive" || generic.constraint == "usertype") {
                static const std::unordered_set<std::string> native_types = {
                    "int", "double", "float", "byte", "nibble", "addr_t", "long double", "short int", "long int", "char", "bool", "qbool", "string"};
                auto clean_view = value | std::views::filter([](char c) { return c != '*' && c != '&' && c != '[' && c != ']'; });
                if (native_types.contains(std::string(clean_view.begin(), clean_view.end()))) {
                    if (generic.constraint == "usertype") {
                        cg_error(Position(), "usertype generic constrain " + generic.name + " expectes usertype type, got " + value);
                        return nullptr;
                    }
                } else {
                    if (generic.constraint == "primitive") {
                        cg_error(Position(), "primitive generic constrain " + generic.name + " expectes primitive type, got " + value);
                        return nullptr;
                    }
                }
            }
            if (!generic.subconstraints.empty()) {
                if (generic.negated) {
                    for (std::string subconstraint : generic.subconstraints) {
                        if (value == subconstraint) {
                            cg_error(Position(), "generic constrain !" + value + " in generic " + generic.name + " does not except type " + value);
                            return nullptr;
                        }
                    }
                } else {
                    bool is_valid = false;
                    for (std::string subconstraint : generic.subconstraints) {
                        if (value == subconstraint) { is_valid = true; }
                    }
                    if (!is_valid) {
                        cg_error(Position(), "generic constrait " + generic.name + " does not except type " + value);
                        return nullptr;
                    }
                }
            }
            currentGenericTypes[generic.name] = llvmTypeFor(value);
            currentGenericTypeStrings[generic.name] = value;
        } else if (generic.isNonType) {
            GenericType generic = structInfo.generics[i];
            if (genericParams.size() <= i) {
                if (generic.defaultValue.empty()) {
                    cg_error(Position(), "too few generic params for struct " + structName);
                    return nullptr;
                }
            }
            std::string gname = generic.name;
            generic.name = genericParams[i];
            currentNonTypeGenericValues[gname] = generic;
        }
    }
    auto oldNamespaceStack = namespaceStack;
    namespaceStack.clear();
    if (!structInfo.namespace_path.empty()) {
        size_t start = 0;
        size_t pos;
        while ((pos = structInfo.namespace_path.find("::", start)) != std::string::npos) {
            namespaceStack.push_back(structInfo.namespace_path.substr(start, pos - start));
            start = pos + 2;
        }
        namespaceStack.push_back(structInfo.namespace_path.substr(start));
    }
    std::vector<llvm::Type*> fieldTypes;
    for (auto& field : structInfo.fields) {
        llvm::Type* ty = llvmTypeFor(field.type);
        fieldTypes.push_back(ty);
    }
    structTypes[mangled_struct_name]->setBody(fieldTypes);
    namespaceStack = oldNamespaceStack;
    inProgressGenerics.erase(mangled_struct_name);
    if (this->config.use_runtime) { generateStructReprFunction(mangled_struct_name, structInfo); }
    this->currentGenericTypes = oldGenericTypes;
    this->currentGenericTypeStrings = oldGenericTypeStrings;
    currentNonTypeGenericValues = oldNonTypeGenerics;
    return structTy;
}
UserTypeInfo LLVMCompiler::generateGenericUnion(std::string unionName, UserTypeInfo unionInfo, std::vector<std::string> genericParams) {
    std::string mangled_union_name = unionName + "<";
    for (int j = 0; j < unionInfo.generics.size(); j++) {
        std::string val;
        if (genericParams.size() <= j) {
            val = unionInfo.generics[j].defaultValue;
        } else {
            val = genericParams[j];
        }
        mangled_union_name += val;
        if (j != unionInfo.generics.size() - 1) { mangled_union_name += ","; }
    }
    mangled_union_name += ">";
    if (inProgressGenerics.count(mangled_union_name)) return {};
    if (unionTypes.find(mangled_union_name) != unionTypes.end()) { return genericiseOrFindUnion(mangled_union_name); }
    std::vector<llvm::Type*> fields = {builder->getInt32Ty(), llvm::PointerType::get(context, 0)};
    llvm::StructType* unionTy = getOrCreateStructType(fields, mangled_union_name);
    unionTypes[mangled_union_name] = unionTy;
    inProgressGenerics.insert(mangled_union_name);
    auto oldGenericTypes = this->currentGenericTypes;
    auto oldGenericTypeStrings = currentGenericTypeStrings;
    auto oldNonTypeGenerics = currentNonTypeGenericValues;
    for (int i = 0; i < unionInfo.generics.size(); i++) {
        GenericType generic = unionInfo.generics[i];
        if (genericParams.size() <= i) {
            if (generic.defaultValue.empty()) {
                cg_error(Position(), "too few generic params for struct " + unionName);
                return {};
            }
        }
        std::string value;
        if ((!generic.defaultValue.empty()) && genericParams.size() <= i) {
            value = generic.defaultValue;
        } else {
            value = genericParams[i];
        }
        if (!generic.isNonType && !generic.isVariadic) {
            if (generic.constraint == "pointer") {
                if (!(value.ends_with("*"))) {
                    cg_error(Position(), "pointer generic constrain " + generic.name + " expectes pointer type, got " + value);
                    return {};
                }
            } else if (generic.constraint == "numeric") {
                if (!(std::unordered_set<std::string>({"int", "double", "float", "byte", "nibble", "addr_t", "long double", "short int", "long int"})
                          .contains(value))) {
                    cg_error(Position(), "numeric generic constrain " + generic.name + " expectes numeric type, got " + value);
                    return {};
                }
            } else if (generic.constraint == "primitive" || generic.constraint == "usertype") {
                static const std::unordered_set<std::string> native_types = {
                    "int", "double", "float", "byte", "nibble", "addr_t", "long double", "short int", "long int", "char", "bool", "qbool", "string"};
                auto clean_view = value | std::views::filter([](char c) { return c != '*' && c != '&' && c != '[' && c != ']'; });
                if (native_types.contains(std::string(clean_view.begin(), clean_view.end()))) {
                    if (generic.constraint == "usertype") {
                        cg_error(Position(), "usertype generic constrain " + generic.name + " expectes usertype type, got " + value);
                        return {};
                    }
                } else {
                    if (generic.constraint == "primitive") {
                        cg_error(Position(), "primitive generic constrain " + generic.name + " expectes primitive type, got " + value);
                        return {};
                    }
                }
            }
            if (!generic.subconstraints.empty()) {
                if (generic.negated) {
                    for (std::string subconstraint : generic.subconstraints) {
                        if (value == subconstraint) {
                            cg_error(Position(), "generic constrain !" + value + " in generic " + generic.name + " does not except type " + value);
                            return {};
                        }
                    }
                } else {
                    bool is_valid = false;
                    for (std::string subconstraint : generic.subconstraints) {
                        if (value == subconstraint) { is_valid = true; }
                    }
                    if (!is_valid) {
                        cg_error(Position(), "generic constrait " + generic.name + " does not except type " + value);
                        return {};
                    }
                }
            }
            currentGenericTypes[generic.name] = llvmTypeFor(value);
            currentGenericTypeStrings[generic.name] = value;
        } else if (generic.isNonType) {
            GenericType generic = unionInfo.generics[i];
            if (genericParams.size() <= i) {
                if (generic.defaultValue.empty()) {
                    cg_error(Position(), "too few generic params for struct " + unionName);
                    return {};
                }
            }
            std::string gname = generic.name;
            generic.name = genericParams[i];
            currentNonTypeGenericValues[gname] = generic;
        }
    }
    auto oldNamespaceStack = namespaceStack;
    namespaceStack.clear();
    if (!unionInfo.namespace_path.empty()) {
        size_t start = 0;
        size_t pos;
        while ((pos = unionInfo.namespace_path.find("::", start)) != std::string::npos) {
            namespaceStack.push_back(unionInfo.namespace_path.substr(start, pos - start));
            start = pos + 2;
        }
        namespaceStack.push_back(unionInfo.namespace_path.substr(start));
    }
    UserTypeInfo genericisedInfo;
    genericisedInfo.kind = UserTypeKind::Union;
    for (UnionMember member : unionInfo.members) {
        if (currentNonTypeGenericValues.count(member.type)) {
            member.type = std::find_if(unionInfo.generics.begin(), unionInfo.generics.end(), [&](const auto& p) { return p.name == member.type; })
                              ->nonTypeKind +
                          ":" + currentNonTypeGenericValues[member.type].name;
        }
        genericisedInfo.members.push_back({substituteGenerics(resolveTypeName(substituteGenerics(member.type)))});
    }
    substitutedUnions[mangled_union_name] = genericisedInfo;
    namespaceStack = oldNamespaceStack;
    inProgressGenerics.erase(mangled_union_name);
    this->currentGenericTypes = oldGenericTypes;
    this->currentGenericTypeStrings = oldGenericTypeStrings;
    currentNonTypeGenericValues = oldNonTypeGenerics;
    return genericisedInfo;
}
std::string LLVMCompiler::generateGenericAlias(std::string aliasName, UserTypeInfo aliasInfo, std::vector<std::string> genericParams) {
    std::string mangled_alias_name = aliasName + "<";
    for (int j = 0; j < aliasInfo.generics.size(); j++) {
        std::string val;
        if (genericParams.size() <= j) {
            val = aliasInfo.generics[j].defaultValue;
        } else {
            val = genericParams[j];
        }
        mangled_alias_name += val;
        if (j != aliasInfo.generics.size() - 1) { mangled_alias_name += ","; }
    }
    mangled_alias_name += ">";
    if (inProgressGenerics.count(mangled_alias_name)) return "";
    if (typeAliases.count(mangled_alias_name)) return typeAliases[mangled_alias_name];
    inProgressGenerics.insert(mangled_alias_name);
    auto oldGenericTypes = this->currentGenericTypes;
    auto oldGenericTypeStrings = currentGenericTypeStrings;
    auto oldNonTypeGenerics = currentNonTypeGenericValues;
    for (int i = 0; i < aliasInfo.generics.size(); i++) {
        GenericType generic = aliasInfo.generics[i];
        if (genericParams.size() <= i) {
            if (generic.defaultValue.empty()) {
                cg_error(Position(), "too few generic params for alias " + aliasName);
                return "";
            }
        }
        std::string value;
        if ((!generic.defaultValue.empty()) && genericParams.size() <= i) {
            value = generic.defaultValue;
        } else {
            value = genericParams[i];
        }
        if (!generic.isNonType && !generic.isVariadic) {
            if (generic.constraint == "pointer") {
                if (!(value.ends_with("*"))) {
                    cg_error(Position(), "pointer generic constrain " + generic.name + " expectes pointer type, got " + value);
                    return "";
                }
            } else if (generic.constraint == "numeric") {
                if (!(std::unordered_set<std::string>({"int", "double", "float", "byte", "nibble", "addr_t", "long double", "short int", "long int"})
                          .contains(value))) {
                    cg_error(Position(), "numeric generic constrain " + generic.name + " expectes numeric type, got " + value);
                    return "";
                }
            } else if (generic.constraint == "primitive" || generic.constraint == "usertype") {
                static const std::unordered_set<std::string> native_types = {
                    "int", "double", "float", "byte", "nibble", "addr_t", "long double", "short int", "long int", "char", "bool", "qbool", "string"};
                auto clean_view = value | std::views::filter([](char c) { return c != '*' && c != '&' && c != '[' && c != ']'; });
                if (native_types.contains(std::string(clean_view.begin(), clean_view.end()))) {
                    if (generic.constraint == "usertype") {
                        cg_error(Position(), "usertype generic constrain " + generic.name + " expectes usertype type, got " + value);
                        return "";
                    }
                } else {
                    if (generic.constraint == "primitive") {
                        cg_error(Position(), "primitive generic constrain " + generic.name + " expectes primitive type, got " + value);
                        return "";
                    }
                }
            }
            if (!generic.subconstraints.empty()) {
                if (generic.negated) {
                    for (std::string subconstraint : generic.subconstraints) {
                        if (value == subconstraint) {
                            cg_error(Position(), "generic constrain !" + value + " in generic " + generic.name + " does not except type " + value);
                            return "";
                        }
                    }
                } else {
                    bool is_valid = false;
                    for (std::string subconstraint : generic.subconstraints) {
                        if (value == subconstraint) { is_valid = true; }
                    }
                    if (!is_valid) {
                        cg_error(Position(), "generic constrait " + generic.name + " does not except type " + value);
                        return "";
                    }
                }
            }
            currentGenericTypes[generic.name] = llvmTypeFor(value);
            currentGenericTypeStrings[generic.name] = value;
        } else if (generic.isNonType) {
            GenericType generic = aliasInfo.generics[i];
            if (genericParams.size() <= i) {
                if (generic.defaultValue.empty()) {
                    cg_error(Position(), "too few generic params for alias " + aliasName);
                    return "";
                }
            }
            std::string gname = generic.name;
            generic.name = genericParams[i];
            currentNonTypeGenericValues[gname] = generic;
        }
    }
    std::string substituted = substituteGenerics(aliasInfo.aliasTarget);
    typeAliases[mangled_alias_name] = substituted;
    inProgressGenerics.erase(mangled_alias_name);
    this->currentGenericTypes = oldGenericTypes;
    this->currentGenericTypeStrings = oldGenericTypeStrings;
    currentNonTypeGenericValues = oldNonTypeGenerics;
    return substituted;
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
            if (!info.generics.empty()) {
                genericStructs[mapKey] = true;
                continue;
            }
            genericStructs[mapKey] = false;
            llvm::StructType* structTy = getOrCreateStructType(mapKey);
            structTypes[mapKey] = structTy;
        }
    }
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind == UserTypeKind::Class) {
            if (!info.generics.empty()) {
                genericClasses[mapKey] = true;
                continue;
            }
            genericClasses[mapKey] = false;
            llvm::StructType* classTy = getOrCreateStructType(mapKey);
            classTypes[mapKey] = classTy;
        }
    }
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind == UserTypeKind::Class) {
            if (!info.generics.empty()) continue;
            if (!info.baseClassName.empty()) {
                auto base_it = userTypes.find(baseTypeName(info.baseClassName));
                if (base_it != userTypes.end() && base_it->second.is_final_class) {
                    cg_error(Position(), "cannot inherit from final class '" + info.baseClassName + "'");
                    continue;
                }
            }
            auto oldNamespaceStack = namespaceStack;
            namespaceStack.clear();
            if (!info.namespace_path.empty()) {
                size_t start = 0;
                size_t pos;
                while ((pos = info.namespace_path.find("::", start)) != std::string::npos) {
                    namespaceStack.push_back(info.namespace_path.substr(start, pos - start));
                    start = pos + 2;
                }
                namespaceStack.push_back(info.namespace_path.substr(start));
            }

            std::vector<llvm::Type*> fieldTypes;

            std::function<void(const std::string&, std::unordered_map<std::string, std::string>)> collectFields =
                [&](const std::string& cname, std::unordered_map<std::string, std::string> genericSubs) {
                    auto it = userTypes.find(baseTypeName(cname));
                    if (it == userTypes.end()) { throw std::string("Class not found: ") + cname; }
                    auto& classIfo = it->second;
                    if (!classIfo.baseClassName.empty()) {
                        std::string baseFullName = classIfo.baseClassName;
                        for (auto& [gname, gval] : genericSubs) {
                            size_t pos;
                            while ((pos = baseFullName.find(gname)) != std::string::npos) baseFullName.replace(pos, gname.size(), gval);
                        }
                        std::unordered_map<std::string, std::string> baseSubs;
                        auto baseIt = userTypes.find(baseTypeName(baseFullName));
                        if (baseIt != userTypes.end()) {
                            genericiseOrFindClass(baseFullName);
                            auto baseArgs = genericParamsFromName(baseFullName);
                            for (size_t i = 0; i < baseIt->second.generics.size() && i < baseArgs.size(); i++) {
                                baseSubs[baseIt->second.generics[i].name] = baseArgs[i];
                            }
                        }
                        collectFields(baseFullName, baseSubs);
                    }
                    for (auto& field : classIfo.classFields) {
                        std::string resolvedType = field.type;
                        if (field.name == "__vptr") {
                            resolvedType = cname + "*";
                        } else {
                            for (auto& [gname, gval] : genericSubs) {
                                size_t pos;
                                while ((pos = resolvedType.find(gname)) != std::string::npos) resolvedType.replace(pos, gname.size(), gval);
                            }
                        }
                        if (field.isStatic) {
                            llvm::Type* fieldTy = llvmTypeFor(resolvedType);
                            std::string mangledName = cname + "::" + field.name;
                            if (!module->getNamedGlobal(mangledName)) {
                                llvm::Constant* initVal = !std::holds_alternative<std::monostate>(field.defaultValue)
                                                              ? llvm::dyn_cast<llvm::Constant>(emitExpr(field.defaultValue))
                                                              : llvm::Constant::getNullValue(fieldTy);

                                if (!initVal) { initVal = llvm::Constant::getNullValue(fieldTy); }

                                globals[mangledName] = new llvm::GlobalVariable(*module, fieldTy, false, llvm::GlobalValue::ExternalLinkage, initVal,
                                                                                mangledName);
                                varTypes[mangledName] = resolvedType;
                                volatileVars[mangledName] = false;
                            }
                        } else {
                            if (!std::holds_alternative<std::monostate>(field.defaultValue)) {
                                cg_warn(get_pos(field.defaultValue), "default values do not exist on non-static members");
                            }
                            fieldTypes.push_back(llvmTypeFor(resolvedType));
                        }
                    }
                };
            collectFields(mapKey, {});
            if (fieldTypes.empty()) { fieldTypes.push_back(builder->getInt8Ty()); }

            classTypes[mapKey]->setBody(fieldTypes);
            namespaceStack = oldNamespaceStack;
        }
    }
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind == UserTypeKind::Union) {
            if (!info.generics.empty()) {
                genericUnions[mapKey] = true;
                continue;
            }
            genericUnions[mapKey] = false;
            std::vector<llvm::Type*> fields = {builder->getInt32Ty(), llvm::PointerType::get(context, 0)};
            llvm::StructType* unionTy = getOrCreateStructType(fields, mapKey);
            unionTypes[mapKey] = unionTy;
        }
    }
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind == UserTypeKind::Alias) {
            if (!info.generics.empty()) {
                genericAliases[mapKey] = true;
                continue;
            }
            genericAliases[mapKey] = false;
            typeAliases[mapKey] = info.aliasTarget;
        }
    }
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind != UserTypeKind::Class) continue;
        if (!info.generics.empty()) continue;
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
        auto oldNamespaceStack = namespaceStack;
        namespaceStack.clear();
        if (!info.namespace_path.empty()) {
            size_t start = 0;
            size_t pos;
            while ((pos = info.namespace_path.find("::", start)) != std::string::npos) {
                namespaceStack.push_back(info.namespace_path.substr(start, pos - start));
                start = pos + 2;
            }
            namespaceStack.push_back(info.namespace_path.substr(start));
        }
        llvm::StructType* classTy = genericiseOrFindClass(mapKey);
        std::vector<llvm::Constant*> vtableFuncs;
        std::vector<std::string> slotOrder;
        std::unordered_map<std::string, int> nameCounts;
        for (auto& method : info.classMethods) { nameCounts[method.name_tok.value]++; }
        for (auto& [mapKey, info] : userTypes) {
            if (info.kind != UserTypeKind::Class || !info.generics.empty()) continue;
            for (size_t methodIdx = 0; methodIdx < info.classMethods.size(); methodIdx++) {
                auto& method = info.classMethods[methodIdx];
                if (!method.is_static) continue;
                std::string mangledName = mapKey + "::" + method.name_tok.value;
                if (nameCounts[method.name_tok.value] > 1) {
                    for (auto& param : method.params) { mangledName += "_" + (param.signature.has_value() ? std::string("fn") : param.type.value); }
                }
                llvm::FunctionType* fnTy = llvmFuncTypeFor(method.return_types, method.params);
                llvm::Function* fn = module->getFunction(mangledName);
                if (!fn) { fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, mangledName, module); }
                llvm::SmallVector<llvm::Metadata*, 4> retTypes;
                for (auto& ret : method.return_types) { retTypes.push_back(llvm::MDString::get(context, ret.value)); }
                if (method.is_volatile) {
                    fn->addFnAttr(llvm::Attribute::NoInline);
                    fn->addFnAttr(llvm::Attribute::OptimizeNone);
                    fn->addFnAttr("noipa");
                }
                fn->setMetadata("qc.return_types", llvm::MDNode::get(context, retTypes));
                for (size_t i = 0; i < method.params.size(); i++) {
                    if (method.params[i].type.value.starts_with("out ")) {
                        fn->addParamAttr(i, llvm::Attribute::WriteOnly);
                        fn->addParamAttr(i, llvm::Attribute::getWithCaptureInfo(context, llvm::CaptureInfo::none()));
                    } else if (method.params[i].type.value.starts_with("inout ")) {
                        fn->addParamAttr(i, llvm::Attribute::getWithCaptureInfo(context, llvm::CaptureInfo::none()));
                    }
                    if (method.params[i].type.value.ends_with("restrict")) { fn->addParamAttr(i, llvm::Attribute::NoAlias); }
                }
                functionDefs[mangledName] = funcDefFromClassMethod(method, mapKey);
            }
        }
        for (size_t methodIdx = 0; methodIdx < info.classMethods.size(); methodIdx++) {
            auto& method = info.classMethods[methodIdx];
            if (method.is_static) continue;
            if (method.is_constructor && info.is_abstract_class) {
                cg_error(method.name_tok.pos, "cannot make a constructor on a abstract class.");
                continue;
            }
            if (std::find(genericMethodIndices[mapKey].begin(), genericMethodIndices[mapKey].end(), methodIdx) !=
                genericMethodIndices[mapKey].end()) {
                continue;
            }
            std::string methodName = mapKey + "_" + method.name_tok.value;
            if (nameCounts[method.name_tok.value] > 1) {
                for (auto& param : method.params) { methodName += "_" + (param.signature.has_value() ? std::string("fn") : param.type.value); }
            }
            std::vector<llvm::Type*> paramTypes;
            paramTypes.push_back(llvm::PointerType::get(context, 0));
            llvm::FunctionType* baseFuncTy = llvmFuncTypeFor(method.return_types, method.params);
            for (auto* paramTy : baseFuncTy->params()) { paramTypes.push_back(paramTy); }
            llvm::FunctionType* fnTy = llvm::FunctionType::get(baseFuncTy->getReturnType(), paramTypes, false);
            llvm::Function* fn = module->getFunction(methodName);
            if (!fn) { fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, methodName, module); }
            llvm::SmallVector<llvm::Metadata*, 4> retTypes;
            for (auto& ret : method.return_types) { retTypes.push_back(llvm::MDString::get(context, ret.value)); }
            if (method.is_volatile) {
                fn->addFnAttr(llvm::Attribute::NoInline);
                fn->addFnAttr(llvm::Attribute::OptimizeNone);
                fn->addFnAttr("noipa");
            }
            fn->setMetadata("qc.return_types", llvm::MDNode::get(context, retTypes));
            for (int i = 1; i < fnTy->getNumParams(); i++) {
                if (method.params[i - 1].type.value.starts_with("out ")) {
                    fn->addParamAttr(i, llvm::Attribute::WriteOnly);
                    fn->addParamAttr(i, llvm::Attribute::getWithCaptureInfo(context, llvm::CaptureInfo::none()));
                } else if (method.params[i - 1].type.value.starts_with("inout ")) {
                    fn->addParamAttr(i, llvm::Attribute::getWithCaptureInfo(context, llvm::CaptureInfo::none()));
                }
                if (method.params[i - 1].type.value.ends_with("restrict")) { fn->addParamAttr(i, llvm::Attribute::NoAlias); }
            }
            classMethods[mapKey][method.name_tok.value].push_back(fn);
            if (isHeader || info.baseFile.ends_with(".hqc")) { continue; }
            vtableFuncs.push_back(fn);
            slotOrder.push_back(methodName);
        }
        for (size_t i = 0; i < slotOrder.size(); i++) { vtableSlotIndex[mapKey][slotOrder[i]] = i; }
        auto* arrTy = llvm::ArrayType::get(llvm::PointerType::get(context, 0), vtableFuncs.size());
        auto* vtableInit = llvm::ConstantArray::get(arrTy, vtableFuncs);
        auto* vtable = getOrCreateVtable(mapKey + "_vtable", arrTy, isHeader || info.baseFile.ends_with(".hqc") ? nullptr : vtableInit);
        vtables[mapKey] = vtable;
        namespaceStack = oldNamespaceStack;
    }
    for (auto& [mapKey, info] : userTypes) {
        if (info.kind == UserTypeKind::Struct) {
            if (!info.generics.empty()) continue;
            std::vector<llvm::Type*> fieldTypes;
            auto oldNamespaceStack = namespaceStack;
            namespaceStack.clear();
            if (!info.namespace_path.empty()) {
                size_t start = 0;
                size_t pos;
                while ((pos = info.namespace_path.find("::", start)) != std::string::npos) {
                    namespaceStack.push_back(info.namespace_path.substr(start, pos - start));
                    start = pos + 2;
                }
                namespaceStack.push_back(info.namespace_path.substr(start));
            }
            for (auto& field : info.fields) {
                llvm::Type* ty = llvmTypeFor(field.type);
                fieldTypes.push_back(ty);
            }

            structTypes[mapKey]->setBody(fieldTypes);
            namespaceStack = oldNamespaceStack;
        }
    }
    if (this->config.use_runtime) { generateStructReprFunctions(); }
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
                std::string toType = p.type.value;
                while (toType.starts_with("out ") || toType.starts_with("inout ")) { toType.erase(0, toType.find(' ') + 1); }
                if (toType.ends_with("restrict")) { toType = toType.substr(0, toType.length() - 8); }
                paramTypes.push_back(llvmTypeFor(toType));
            }
        }
    }
    if (returnTypes.empty()) {
        llvm::FunctionType* funcTy = llvm::FunctionType::get(builder->getVoidTy(), paramTypes, is_c_varargs);
        return funcTy;
    }

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
void LLVMCompiler::cg_error(const Position& pos, const std::string& msg, std::string code) {
    errors.emplace_back(msg, pos, false, code);
}
void LLVMCompiler::cg_warn(const Position& pos, const std::string& msg, std::string code) {
    errors.emplace_back(msg, pos, true, code);
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
    pointerSizeBits = module->getDataLayout().getPointerSizeInBits();
    jaggedArraysStack.push_back({});
    arrayTypeStringsStack.push_back({});
    arrayLengthsStack.push_back({});
    this->is_main = is_main;
}

llvm::Value* LLVMCompiler::boolToQBool(llvm::Value* boolVal) {
    llvm::Value* ext = builder->CreateZExt(boolVal, builder->getInt8Ty());
    llvm::Value* tripled = builder->CreateMul(ext, builder->getInt8(3));
    return builder->CreateTrunc(tripled, builder->getIntNTy(2));
}
llvm::Value* LLVMCompiler::emitMethodCall(llvm::Function* method, llvm::Value* thisPtr, const std::vector<llvm::Value*>& args,
                                          const std::string& name) {
    auto callArgs = reconcileArgs(method, thisPtr, args);
    bool returnsVoid = method->getReturnType()->isVoidTy();
    if (insideTry()) {
        auto* contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
        auto* invoke = builder->CreateInvoke(method, contBB, currentLandingPad(), callArgs);
        if (!returnsVoid) { invoke->setName(name + "_result"); }
        builder->SetInsertPoint(contBB);
        return returnsVoid ? nullptr : invoke;
    }
    auto* call = builder->CreateCall(method, callArgs);
    if (!returnsVoid) { call->setName(name + "_result"); }
    return returnsVoid ? nullptr : call;
}
llvm::Value* LLVMCompiler::emitExpr(AnyNode node) {
    if (auto num = std::get_if<NumberNode>(&node)) {
        const std::string& text = num->tok.value;

        switch (num->tok.type) {
        case TokenType::INT: {
            intptr_t v = std::stoll(text);
            return builder->getInt32(static_cast<int32_t>(v));
        }
        case TokenType::LONG_INT: {
            intptr_t v = std::stoll(text);
            return getPtrSize() == 32 ? builder->getInt32(static_cast<int32_t>(v)) : builder->getInt64(static_cast<int64_t>(v));
        }
        case TokenType::SHORT_INT: {
            intptr_t v = std::stoi(text);
            return builder->getInt16(static_cast<int16_t>(v));
        }
        case TokenType::ADDR_T: {
            llvm::APInt value(getPtrSize(), text, 10);
            return llvm::ConstantInt::get(builder->getContext(), value);
        }
        case TokenType::BYTE: {
            llvm::APInt value(8, text, 10);
            return llvm::ConstantInt::get(builder->getContext(), value);
        }
        case TokenType::NIBBLE: {
            llvm::APInt value(4, text, 10);
            return llvm::ConstantInt::get(builder->getContext(), value);
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
            cg_error(qbool->tok.pos, "invalid qbool value '" + qbool->tok.value + "'");
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
    } else if (auto tv = std::get_if<TypeValueNode>(&node)) {
        llvm::Constant* strConstant = llvm::ConstantDataArray::getString(context, tv->tok.value, true);
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
                        Position pos = get_pos(*varAccess);
                        cg_error(pos, "qin: variable not declared: " + varName);
                        auto suggestions = getVisibleVariables();
                        std::vector<std::pair<int, std::string>> matches;
                        if (varName.size() >= 3) {
                            for (auto& name : suggestions) {
                                int distance = levenshteinDistance(varName, name);
                                if (distance <= 2) { matches.push_back({distance, name}); }
                            }
                        }
                        std::sort(matches.begin(), matches.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
                        if (!matches.empty()) {
                            std::string note = "did you mean ";
                            size_t count = std::min<size_t>(3, matches.size());
                            for (size_t i = 0; i < count; i++) {
                                if (i != 0) note += ", ";
                                note += "`" + matches[i].second + "`";
                            }
                            note += "?";
                            cg_note(pos, note);
                        }
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
                            auto* fnTy = llvm::FunctionType::get(builder->getIntNTy(getPtrSize()), {llvm::PointerType::get(context, 0)}, false);
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
                    } else if (varTy->isIntegerTy(4)) {
                        llvm::Function* fn = module->getFunction("qc_to_nibble_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getIntNTy(4), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_nibble_from_string", module);
                        }
                        converted = builder->CreateCall(fn, {input});
                    }

                    builder->CreateStore(converted, alloc);

                    return builder->getInt32(0);
                }

                cg_error(get_pos((*bin)->right_node), "qin: right side must be a variable");
                return nullptr;
            }
        }
        llvm::Value* L = emitExpr((*bin)->left_node);
        if (!L) return nullptr;
        if (op == TokenType::AND || op == TokenType::OR) {
            L = toTruthiness(L, get_pos((*bin)->left_node));
            if (L) {
                llvm::BasicBlock* lhsBB = builder->GetInsertBlock();
                llvm::BasicBlock* rhsBB = llvm::BasicBlock::Create(context, op == TokenType::AND ? "and.rhs" : "or.rhs", currentFunction);
                llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, op == TokenType::AND ? "and.end" : "or.end", currentFunction);
                if (op == TokenType::AND) {
                    builder->CreateCondBr(L, rhsBB, endBB);
                } else {
                    builder->CreateCondBr(L, endBB, rhsBB);
                }
                builder->SetInsertPoint(rhsBB);
                llvm::Value* R = emitExpr((*bin)->right_node);
                if (R) {
                    R = toTruthiness(R, Position("", "", 0, 0, 0));
                    if (R) {
                        llvm::BasicBlock* rhsEndBB = builder->GetInsertBlock();
                        builder->CreateBr(endBB);
                        builder->SetInsertPoint(endBB);
                        llvm::PHINode* result = builder->CreatePHI(builder->getInt1Ty(), 2, op == TokenType::AND ? "and" : "or");
                        if (op == TokenType::AND) {
                            result->addIncoming(builder->getFalse(), lhsBB);
                            result->addIncoming(R, rhsEndBB);
                        } else {
                            result->addIncoming(builder->getTrue(), lhsBB);
                            result->addIncoming(R, rhsEndBB);
                        }
                        return result;
                    }
                }
            }
        }
        llvm::Value* R = emitExpr((*bin)->right_node);
        if (!R) return nullptr;
        llvm::Type* lty = L->getType();
        llvm::Type* rty = R->getType();
        if (L->getType()->isPointerTy()) {
            llvm::Type* allocTy = llvmTypeFor(getExpressionType((*bin)->left_node));
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
                                if (insideTry()) {
                                    auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++),
                                                                           currentFunction);
                                    auto invk = builder->CreateInvoke(opMethod, contBB, currentLandingPad(), allArgs);
                                    builder->SetInsertPoint(contBB);
                                    return invk;
                                }
                                return builder->CreateCall(opMethod, allArgs, "op_result");
                            }
                        }
                    }
                }
            }
        }
        if (R->getType()->isPointerTy()) {
            llvm::Type* allocTy = llvmTypeFor(getExpressionType((*bin)->right_node));
            if (auto structTy = llvm::dyn_cast<llvm::StructType>(allocTy)) {
                if (structTy->hasName()) {
                    std::string className = structTy->getName().str();
                    if (classTypes.find(className) != classTypes.end()) {
                        std::string opMethodName = getRoperatorMethodName((*bin)->op_tok.type);
                        if (!opMethodName.empty()) {
                            std::vector<llvm::Value*> args = {L};
                            llvm::Function* opMethod = findMethodOverload(className, opMethodName, args);
                            if (opMethod) {
                                std::vector<llvm::Value*> allArgs = {R, L};
                                if (insideTry()) {
                                    auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++),
                                                                           currentFunction);
                                    auto invk = builder->CreateInvoke(opMethod, contBB, currentLandingPad(), allArgs);
                                    builder->SetInsertPoint(contBB);
                                    return invk;
                                }
                                return builder->CreateCall(opMethod, allArgs, "op_result");
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

                auto& members = userTypes.at(baseTypeName(lUnionName)).members;
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

                auto& entries = userTypes.at(baseTypeName(lEnumName)).enumEntries;
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
            std::function<llvm::Value*(llvm::Value*, AnyNode&, const Position&)> toString = [&](llvm::Value* v, AnyNode& node,
                                                                                                const Position& pos) -> llvm::Value* {
                v = derefIfReference(v, node);
                if (!v) return nullptr;
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
                        auto* fnTy = llvm::FunctionType::get(i8Ptr, {builder->getIntNTy(getPtrSize())}, false);
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
                if (ty->isIntegerTy(4)) {
                    auto* fn = module->getFunction("qc_to_string_nibble");
                    if (!fn) {
                        auto* i4Ptr = llvm::PointerType::get(context, 0);
                        auto* fnTy = llvm::FunctionType::get(i4Ptr, {builder->getIntNTy(4)}, false);
                        fn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_to_string_nibble", module);
                    }
                    return builder->CreateCall(fn, {v}, "fstr_nibble");
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
                if (auto structTy = llvm::dyn_cast<llvm::StructType>(ty)) {
                    if (structTy->hasName()) {
                        std::string className = structTy->getName().str();

                        if (classTypes.find(className) != classTypes.end()) {
                            auto [reprMethod, ownerClass] = findMethodInHierarchy(className, "_repr");

                            if (reprMethod) {
                                std::vector<llvm::Value*> args;

                                llvm::AllocaInst* temp = createEntryAlloca("temp_repr", ty);
                                builder->CreateStore(v, temp);
                                args.push_back(temp);
                                if (insideTry()) {
                                    auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++),
                                                                           currentFunction);
                                    llvm::InvokeInst* invk = builder->CreateInvoke(reprMethod, contBB, currentLandingPad(), args);
                                    builder->SetInsertPoint(contBB);
                                    return invk;
                                }
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
                std::string unionName;
                if (isUnionType(ty, &unionName)) {
                    auto members = genericiseOrFindUnion(unionName).members;
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
                        llvm::Value* strVal = toString(memberVal, fakeNode, pos);
                        if (!strVal) strVal = builder->CreateGlobalString("?");
                        builder->CreateStore(strVal, resultAlloc);
                        builder->CreateBr(endBB);
                    }

                    builder->SetInsertPoint(endBB);
                    return builder->CreateLoad(llvm::PointerType::get(context, 0), resultAlloc, "fstr_union_result");
                }
                if (ty->isPointerTy()) { return v; }

                cg_error(pos, "f-string: unsupported type in compiled mode");
                return nullptr;
            };
            llvm::Value* lStr = toString(L, (*bin)->left_node, (*bin)->op_tok.pos);
            llvm::Value* rStr = toString(R, (*bin)->right_node, (*bin)->op_tok.pos);
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
            auto& members = userTypes.at(baseTypeName(lUnion)).members;
            llvm::Value* lTag = builder->CreateExtractValue(L, 0, "ltag");
            llvm::Value* rTag = builder->CreateExtractValue(R, 0, "rtag");
            llvm::Value* lPayload = builder->CreateExtractValue(L, 1, "lpayload");
            llvm::Value* rPayload = builder->CreateExtractValue(R, 1, "rpayload");
            const bool isBooleanResult = op == TokenType::EQ_TO || op == TokenType::NOT_EQ || op == TokenType::LESS || op == TokenType::MORE ||
                                         op == TokenType::LESS_EQ || op == TokenType::MORE_EQ || op == TokenType::AND || op == TokenType::OR ||
                                         op == TokenType::XOR;
            llvm::Type* resultTy = isBooleanResult ? builder->getInt1Ty() : builder->getDoubleTy();
            llvm::AllocaInst* resultAlloc = createEntryAlloca("union_op_result", resultTy);
            llvm::BasicBlock* dispatchBB = llvm::BasicBlock::Create(context, "union_op_dispatch", currentFunction);
            llvm::BasicBlock* badTagBB = llvm::BasicBlock::Create(context, "union_op_bad_tag", currentFunction);
            llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "union_op_end", currentFunction);
            llvm::Value* sameTag = builder->CreateICmpEQ(lTag, rTag, "union_same_tag");
            builder->CreateCondBr(sameTag, dispatchBB, badTagBB);
            builder->SetInsertPoint(badTagBB);
            builder->CreateStore(isBooleanResult ? static_cast<llvm::Value*>(builder->getFalse())
                                                 : static_cast<llvm::Value*>(llvm::ConstantFP::get(builder->getDoubleTy(), 0.0)),
                                 resultAlloc);
            builder->CreateBr(endBB);
            builder->SetInsertPoint(dispatchBB);
            llvm::SwitchInst* sw = builder->CreateSwitch(lTag, badTagBB, members.size());
            for (size_t i = 0; i < members.size(); ++i) {
                llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "union_op_case_" + std::to_string(i), currentFunction);
                sw->addCase(builder->getInt32(i), caseBB);
                builder->SetInsertPoint(caseBB);
                std::string ts = members[i].type;
                size_t colon = ts.find(':');
                if (colon != std::string::npos) ts = ts.substr(0, colon);
                llvm::Type* memberTy = llvmTypeFor(ts);
                if (memberTy->isPointerTy() || memberTy->isArrayTy()) {
                    cg_error((*bin)->op_tok.pos, "pointer arithmetic is not allowed on unions");
                    return nullptr;
                }
                llvm::Value* lhsVal = builder->CreateLoad(memberTy, lPayload, "lmember");
                llvm::Value* rhsVal = builder->CreateLoad(memberTy, rPayload, "rmember");
                llvm::Value* res = nullptr;
                if (auto* classTy = llvm::dyn_cast<llvm::StructType>(memberTy); classTy && classTy->hasName()) {
                    std::string className = classTy->getName().str();
                    std::string methodName = getOperatorMethodName(op);
                    if (classTypes.contains(className) && !methodName.empty()) {
                        llvm::Function* method = findMethodOverload(className, methodName, {rhsVal});
                        if (method) {
                            llvm::AllocaInst* self = createEntryAlloca("union_op_self", memberTy);
                            builder->CreateStore(lhsVal, self);
                            std::vector<llvm::Value*> args = {self, rhsVal};
                            if (insideTry()) {
                                auto* contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
                                res = builder->CreateInvoke(method, contBB, currentLandingPad(), args);
                                builder->SetInsertPoint(contBB);
                            } else {
                                res = builder->CreateCall(method, args, "op_result");
                            }
                        }
                    }
                }
                if (!res && ts == "char" && (op == TokenType::PLUS || op == TokenType::MINUS)) {
                    llvm::Value* pl = builder->CreateSExtOrTrunc(lhsVal, builder->getInt32Ty(), "char_lhs");
                    llvm::Value* pr = builder->CreateSExtOrTrunc(rhsVal, builder->getInt32Ty(), "char_rhs");

                    res = op == TokenType::PLUS ? builder->CreateAdd(pl, pr, "char_add") : builder->CreateSub(pl, pr, "char_sub");
                }
                if (!res) {
                    const bool isFP = memberTy->isFloatingPointTy();
                    switch (op) {
                    case TokenType::AND:
                    case TokenType::OR:
                    case TokenType::XOR:
                        lhsVal = toTruthiness(lhsVal, get_pos((*bin)->left_node));
                        rhsVal = toTruthiness(rhsVal, get_pos((*bin)->right_node));
                        if (op == TokenType::AND)
                            res = builder->CreateAnd(lhsVal, rhsVal, "and");
                        else if (op == TokenType::OR)
                            res = builder->CreateOr(lhsVal, rhsVal, "or");
                        else
                            res = builder->CreateXor(lhsVal, rhsVal, "xor");
                        break;
                    case TokenType::EQ_TO: res = isFP ? builder->CreateFCmpOEQ(lhsVal, rhsVal) : builder->CreateICmpEQ(lhsVal, rhsVal); break;
                    case TokenType::NOT_EQ: res = isFP ? builder->CreateFCmpONE(lhsVal, rhsVal) : builder->CreateICmpNE(lhsVal, rhsVal); break;
                    case TokenType::LESS: res = isFP ? builder->CreateFCmpOLT(lhsVal, rhsVal) : builder->CreateICmpSLT(lhsVal, rhsVal); break;
                    case TokenType::MORE: res = isFP ? builder->CreateFCmpOGT(lhsVal, rhsVal) : builder->CreateICmpSGT(lhsVal, rhsVal); break;
                    case TokenType::LESS_EQ: res = isFP ? builder->CreateFCmpOLE(lhsVal, rhsVal) : builder->CreateICmpSLE(lhsVal, rhsVal); break;
                    case TokenType::MORE_EQ: res = isFP ? builder->CreateFCmpOGE(lhsVal, rhsVal) : builder->CreateICmpSGE(lhsVal, rhsVal); break;
                    case TokenType::PLUS: res = isFP ? builder->CreateFAdd(lhsVal, rhsVal) : builder->CreateAdd(lhsVal, rhsVal); break;
                    case TokenType::MINUS: res = isFP ? builder->CreateFSub(lhsVal, rhsVal) : builder->CreateSub(lhsVal, rhsVal); break;
                    case TokenType::MUL: res = isFP ? builder->CreateFMul(lhsVal, rhsVal) : builder->CreateMul(lhsVal, rhsVal); break;
                    case TokenType::DIV: res = isFP ? builder->CreateFDiv(lhsVal, rhsVal) : builder->CreateSDiv(lhsVal, rhsVal); break;
                    case TokenType::MOD: res = isFP ? builder->CreateFRem(lhsVal, rhsVal) : builder->CreateSRem(lhsVal, rhsVal); break;
                    case TokenType::AMPERSAND:
                    case TokenType::PIPE:
                    case TokenType::BITWISE_XOR:
                        if (isFP) {
                            cg_error((*bin)->op_tok.pos, "bitwise operation is not allowed "
                                                         "on floating-point union members");
                            return nullptr;
                        }

                        if (op == TokenType::AMPERSAND)
                            res = builder->CreateAnd(lhsVal, rhsVal);
                        else if (op == TokenType::PIPE)
                            res = builder->CreateOr(lhsVal, rhsVal);
                        else
                            res = builder->CreateXor(lhsVal, rhsVal);
                        break;
                    case TokenType::LSHIFT:
                    case TokenType::RSHIFT:
                    case TokenType::LOGICAL_RSHIFT:
                        if (isFP) {
                            cg_error((*bin)->op_tok.pos, "shift operation is not allowed on "
                                                         "floating-point union members");
                            return nullptr;
                        }
                        if (op == TokenType::LSHIFT)
                            res = builder->CreateShl(lhsVal, rhsVal);
                        else if (op == TokenType::RSHIFT)
                            res = builder->CreateAShr(lhsVal, rhsVal);
                        else
                            res = builder->CreateLShr(lhsVal, rhsVal);
                        break;
                    case TokenType::L_ROT:
                    case TokenType::R_ROT: {
                        if (isFP) {
                            cg_error((*bin)->op_tok.pos, "rotation is not allowed on "
                                                         "floating-point union members");
                            return nullptr;
                        }
                        llvm::Intrinsic::ID id = op == TokenType::L_ROT ? llvm::Intrinsic::fshl : llvm::Intrinsic::fshr;
                        llvm::Function* rotation = llvm::Intrinsic::getOrInsertDeclaration(module, id, {memberTy});
                        res = builder->CreateCall(rotation, {lhsVal, lhsVal, rhsVal}, "union_rotate");
                        break;
                    }
                    default: cg_error((*bin)->op_tok.pos, "unsupported operator for union member " + ts); return nullptr;
                    }
                }
                if (res->getType() != resultTy) {
                    if (resultTy->isDoubleTy()) {
                        if (res->getType()->isIntegerTy()) {
                            res = builder->CreateSIToFP(res, resultTy, "union_to_double");
                        } else if (res->getType()->isFloatTy()) {
                            res = builder->CreateFPExt(res, resultTy, "union_to_double");
                        } else {
                            cg_error((*bin)->op_tok.pos, "union operator must return a numeric "
                                                         "value");
                            return nullptr;
                        }
                    } else {
                        cg_error((*bin)->op_tok.pos, "union boolean operator must return bool");
                        return nullptr;
                    }
                }
                builder->CreateStore(res, resultAlloc);
                builder->CreateBr(endBB);
            }
            builder->SetInsertPoint(endBB);
            return builder->CreateLoad(resultTy, resultAlloc, "union_op_result");
        }
        if (lIsUnion || rIsUnion) {
            std::string unionName = lIsUnion ? lUnion : rUnion;
            auto& members = userTypes.at(baseTypeName(unionName)).members;
            llvm::Value* unionVal = lIsUnion ? L : R;
            llvm::Value* otherVal = lIsUnion ? R : L;

            llvm::Value* tag = builder->CreateExtractValue(unionVal, 0, "tag");
            llvm::Value* payload = builder->CreateExtractValue(unionVal, 1, "payload");

            llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "union_op_end", currentFunction);
            bool isComparison = op == TokenType::EQ_TO || op == TokenType::NOT_EQ || op == TokenType::LESS || op == TokenType::MORE ||
                                op == TokenType::LESS_EQ || op == TokenType::MORE_EQ || op == TokenType::AND || op == TokenType::OR ||
                                op == TokenType::XOR;
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
                bool lhsChar = lIsUnion ? ts == "char" : getExpressionType((*bin)->left_node) == "char";
                bool rhsChar = rIsUnion ? ts == "char" : getExpressionType((*bin)->right_node) == "char";
                llvm::Value* typedPtr = builder->CreateBitCast(payload, llvm::PointerType::get(context, 0));
                llvm::Value* memberVal = builder->CreateLoad(memberTy, typedPtr, "member");

                llvm::Value* lhsVal = lIsUnion ? memberVal : otherVal;
                llvm::Value* rhsVal = lIsUnion ? otherVal : memberVal;
                llvm::StructType* classTy = llvm::dyn_cast<llvm::StructType>(lhsVal->getType());
                llvm::Value* res = nullptr;

                if (classTy && classTy->hasName()) {
                    std::string className = classTy->getName().str();
                    std::string methodName = getOperatorMethodName(op);

                    if (classTypes.contains(className) && !methodName.empty()) {
                        std::vector<llvm::Value*> args = {rhsVal};
                        llvm::Function* method = findMethodOverload(className, methodName, args);
                        if (method) {
                            llvm::AllocaInst* self = createEntryAlloca("union_op_self", lhsVal->getType());
                            builder->CreateStore(lhsVal, self);

                            std::vector<llvm::Value*> callArgs = {self, rhsVal};
                            if (insideTry()) {
                                auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
                                res = builder->CreateInvoke(method, contBB, currentLandingPad(), callArgs);
                                builder->SetInsertPoint(contBB);
                            }
                            res = builder->CreateCall(method, callArgs, "op_result");
                        }
                    }
                } else {
                    classTy = llvm::dyn_cast<llvm::StructType>(rhsVal->getType());
                    if (classTy && classTy->hasName()) {
                        std::string className = classTy->getName().str();
                        std::string methodName = getRoperatorMethodName(op);

                        if (classTypes.contains(className) && !methodName.empty()) {
                            std::vector<llvm::Value*> args = {rhsVal};
                            llvm::Function* method = findMethodOverload(className, methodName, args);
                            if (method) {
                                llvm::AllocaInst* self = createEntryAlloca("union_op_self", rhsVal->getType());
                                builder->CreateStore(rhsVal, self);
                                std::vector<llvm::Value*> callArgs = {self, lhsVal};
                                if (insideTry()) {
                                    auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++),
                                                                           currentFunction);
                                    res = builder->CreateInvoke(method, contBB, currentLandingPad(), callArgs);
                                    builder->SetInsertPoint(contBB);
                                }
                                res = builder->CreateCall(method, callArgs, "op_result");
                            }
                        }
                    }
                }
                llvm::Type* lTy = lhsVal->getType();
                llvm::Type* rTy = rhsVal->getType();
                if ((op == TokenType::PLUS || op == TokenType::MINUS) && (lhsChar || rhsChar)) {
                    if (!lhsVal->getType()->isIntegerTy() || !rhsVal->getType()->isIntegerTy()) {
                        cg_error((*bin)->op_tok.pos, "char arithmetic requires integer operands");
                        return nullptr;
                    }
                    unsigned width = std::max(32u, std::max(lhsVal->getType()->getIntegerBitWidth(), rhsVal->getType()->getIntegerBitWidth()));
                    llvm::Type* promotedTy = builder->getIntNTy(width);
                    lhsVal = builder->CreateSExtOrTrunc(lhsVal, promotedTy);
                    rhsVal = builder->CreateSExtOrTrunc(rhsVal, promotedTy);
                    res = op == TokenType::PLUS ? builder->CreateAdd(lhsVal, rhsVal) : builder->CreateSub(lhsVal, rhsVal);
                }
                bool lhsPtr = lhsVal->getType()->isPointerTy();
                bool rhsPtr = rhsVal->getType()->isPointerTy();
                if (lhsPtr || rhsPtr) {
                    cg_error(get_pos(*bin), "Pointer arithmetic is not allow on unions. Consider extracting the value first.");
                    return nullptr;
                }
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
                if (res == nullptr) {
                    switch (op) {
                    case TokenType::AND:
                    case TokenType::OR:
                    case TokenType::XOR:
                        lhsVal = toTruthiness(lhsVal, get_pos((*bin)->left_node));
                        rhsVal = toTruthiness(rhsVal, get_pos((*bin)->right_node));
                        if (op == TokenType::AND)
                            res = builder->CreateAnd(lhsVal, rhsVal);
                        else if (op == TokenType::OR)
                            res = builder->CreateOr(lhsVal, rhsVal);
                        else
                            res = builder->CreateXor(lhsVal, rhsVal);
                        break;
                    case TokenType::NOT_EQ: res = isFP ? builder->CreateFCmpONE(lhsVal, rhsVal) : builder->CreateICmpNE(lhsVal, rhsVal); break;
                    case TokenType::EQ: res = isFP ? builder->CreateFCmpOEQ(lhsVal, rhsVal) : builder->CreateICmpEQ(lhsVal, rhsVal); break;
                    case TokenType::MOD: res = isFP ? builder->CreateFRem(lhsVal, rhsVal) : builder->CreateSRem(lhsVal, rhsVal); break;
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
                            cg_error((*bin)->op_tok.pos, "bitwise operations not allowed on "
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
                            cg_error((*bin)->op_tok.pos, "rotation not allowed on floating-point union "
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
                }
                bool isCharArithmetic = (lhsChar || rhsChar) && (op == TokenType::PLUS || op == TokenType::MINUS);
                if (isCharArithmetic) {
                    if (!lhsVal->getType()->isIntegerTy() || !rhsVal->getType()->isIntegerTy()) {
                        cg_error((*bin)->op_tok.pos, "char arithmetic requires integer operands");
                        return nullptr;
                    }
                    bool mixedChar = lhsChar != rhsChar;
                    llvm::Type* promotedTy = builder->getInt32Ty();
                    llvm::Value* promotedL = builder->CreateSExtOrTrunc(lhsVal, promotedTy, "char_lhs");
                    llvm::Value* promotedR = builder->CreateSExtOrTrunc(rhsVal, promotedTy, "char_rhs");
                    switch (op) {
                    case TokenType::PLUS: res = builder->CreateAdd(promotedL, promotedR, "char_add"); break;
                    case TokenType::MINUS: res = builder->CreateSub(promotedL, promotedR, "char_sub"); break;
                    default: break;
                    }
                    if (mixedChar) { res = builder->CreateTrunc(res, builder->getInt8Ty(), "truncate_to_char"); }
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
        std::string lTyStr = getExpressionType((*bin)->left_node);
        std::string rTyStr = getExpressionType((*bin)->right_node);
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
                            if (insideTry()) {
                                auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
                                llvm::InvokeInst* invk = builder->CreateInvoke(opMethod, contBB, currentLandingPad(), allArgs);
                                builder->SetInsertPoint(contBB);
                                return invk;
                            }
                            return builder->CreateCall(opMethod, allArgs, "op_result");
                        }
                    }
                }
            }
        }
        if (auto rStructTy = llvm::dyn_cast<llvm::StructType>(rty)) {
            if (rStructTy->hasName()) {
                std::string className = rStructTy->getName().str();
                if (classTypes.find(className) != classTypes.end()) {
                    std::string opMethodName = getOperatorMethodName((*bin)->op_tok.type);
                    if (!opMethodName.empty()) {
                        std::vector<llvm::Value*> args = {L};
                        llvm::Function* opMethod = findMethodOverload(className, opMethodName, args);
                        if (opMethod) {
                            llvm::AllocaInst* temp = createEntryAlloca("temp_op_rhs", rty);
                            builder->CreateStore(R, temp);
                            std::vector<llvm::Value*> allArgs = {temp, L};
                            if (insideTry()) {
                                auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
                                llvm::InvokeInst* invk = builder->CreateInvoke(opMethod, contBB, currentLandingPad(), allArgs);
                                builder->SetInsertPoint(contBB);
                                return invk;
                            }
                            return builder->CreateCall(opMethod, allArgs, "op_result");
                        }
                    }
                }
            }
        }
        bool isCharOperation = false;
        if ((lTyStr == "char" || rTyStr == "char") && (lty->isIntegerTy() && rty->isIntegerTy()) &&
            (op == TokenType::PLUS || op == TokenType::MINUS)) {
            bool lIsChar = lTyStr == "char";
            bool rIsChar = rTyStr == "char";
            if (lIsChar && rIsChar) {
                L = builder->CreateSExt(L, builder->getInt32Ty(), "char_promote");
                R = builder->CreateSExt(R, builder->getInt32Ty(), "char_promote");
                lty = builder->getInt32Ty();
                rty = builder->getInt32Ty();
            } else if (lIsChar) {
                L = builder->CreateSExtOrTrunc(L, rty, "char_set");
                lty = rty;
                isCharOperation = true;
            } else if (rIsChar) {
                R = builder->CreateSExtOrTrunc(R, lty, "char_set");
                rty = lty;
                isCharOperation = true;
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
            if (lty->isPointerTy() || rty->isPointerTy() || lty->isArrayTy()) {
                std::string lType = getExpressionType((*bin)->left_node);
                std::string rType = getExpressionType((*bin)->right_node);

                if ((lType == "string" || lType == "char*") && (rType == "string" || rType == "char*")) {
                    llvm::Function* concatFn = module->getFunction("qc_string_concat");
                    if (!concatFn) {
                        llvm::Type* i8PtrTy = llvm::PointerType::get(context, 0);
                        std::vector<llvm::Type*> argTypes = {i8PtrTy, i8PtrTy};
                        llvm::FunctionType* fnTy = llvm::FunctionType::get(i8PtrTy, argTypes, false);
                        concatFn = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_string_concat", module);
                    }
                    return builder->CreateCall(concatFn, {L, R}, "str_concat");
                } else if (lType.ends_with("*") || lType == "@nullptr" || lType == "string" && rType != "string" || lType.ends_with("]")) {
                    if (lType == "void*") {
                        cg_error((*bin)->op_tok.pos, "pointer arithmetic cannot be preformed on "
                                                     "void pointers");
                        return nullptr;
                    }
                    if (lType.ends_with("]")) {
                        L = decayArrayToPointer(L);
                        size_t start_pos = lType.rfind("[");
                        if (start_pos != std::string::npos) { lType.replace(start_pos, lType.size() - start_pos, "*"); }
                    }
                    if (!llvmTypeFor(rType)->isIntegerTy()) {
                        cg_error((*bin)->op_tok.pos, "pointer arithmetic may only be preformed on "
                                                     "ptr lhs and "
                                                     "int rhs, got " +
                                                         lType + " and " + rType);
                        return nullptr;
                    }
                    if (lType == "string")
                        lType = "char";
                    else
                        lType.pop_back();
                    return builder->CreateGEP(llvmTypeFor(lType), L, R, "ptr_arith_plus");
                }
                cg_error((*bin)->op_tok.pos, "cannot perform arithmetic on types " + lType + " + " + rType);
                return nullptr;
            }
            if (lty == builder->getInt1Ty() || rty == builder->getInt1Ty()) {
                cg_error((*bin)->op_tok.pos, "cannot perform arithmetic on bool types");
                return nullptr;
            }

            if (lty == builder->getIntNTy(2) || rty == builder->getIntNTy(2)) {
                cg_error((*bin)->op_tok.pos, "cannot perform arithmetic on qbool types");
                return nullptr;
            }
            return isFloatTy         ? builder->CreateFAdd(L, R, "fadd")
                   : isCharOperation ? builder->CreateTrunc(builder->CreateAdd(L, R, "add"), builder->getInt8Ty(), "trunc_char")
                                     : builder->CreateAdd(L, R, "add");
        case TokenType::MINUS:
            if (lty->isPointerTy() || rty->isPointerTy() || lty->isArrayTy() || rty->isArrayTy()) {
                std::string lType = getExpressionType((*bin)->left_node);
                std::string rType = getExpressionType((*bin)->right_node);

                if ((lType.ends_with("]") || lType.ends_with("*") || lType == "@nullptr") &&
                    (rType.ends_with("]") || rType.ends_with("*") || rType == "@nullptr")) {
                    if (lType == "void*") {
                        cg_error((*bin)->op_tok.pos, "pointer arithmetic cannot be preformed on "
                                                     "void pointers");
                        return nullptr;
                    }
                    if (rType == "void*") {
                        cg_error((*bin)->op_tok.pos, "pointer arithmetic cannot be preformed on "
                                                     "void pointers");
                        return nullptr;
                    }
                    if (remove_last_ptr(lType) != remove_last_ptr(rType)) {
                        cg_error((*bin)->op_tok.pos, "pointer arithmetic may only be preformed on "
                                                     "the same lhs "
                                                     "and rhs type, got " +
                                                         lType + " and " + rType);
                        return nullptr;
                    }
                    std::string baseType = (lType == "@nullptr") ? rType : lType;
                    if (baseType == "@nullptr") { return builder->getInt32(0); }
                    if (baseType.ends_with("]")) {
                        auto pos = baseType.rfind("[");
                        if (pos != std::string::npos) baseType.erase(pos);
                        baseType += "*";
                    }
                    baseType.pop_back();
                    llvm::Value* diff = builder->CreatePtrDiff(llvmTypeFor(baseType), L, R, "ptr_diff");
                    return builder->CreateTrunc(diff, builder->getInt32Ty());
                } else if (lType.ends_with("*") && rType == "int") {
                    std::string baseType = lType;
                    baseType.pop_back();
                    llvm::Value* negR = builder->CreateNeg(R, "neg_offset");
                    return builder->CreateGEP(llvmTypeFor(baseType), L, {negR}, "ptr_arith_minus");
                }

                cg_error((*bin)->op_tok.pos, "invalid pointer subtraction: " + lType + " - " + rType);
                return nullptr;
            }
            if (lty == builder->getInt1Ty() || rty == builder->getInt1Ty()) {
                cg_error((*bin)->op_tok.pos, "cannot perform arithmetic on bool types");
                return nullptr;
            }

            if (lty == builder->getIntNTy(2) || rty == builder->getIntNTy(2)) {
                cg_error((*bin)->op_tok.pos, "cannot perform arithmetic on qbool types");
                return nullptr;
            }
            return isFloatTy         ? builder->CreateFSub(L, R, "fsub")
                   : isCharOperation ? builder->CreateTrunc(builder->CreateSub(L, R, "sub"), builder->getInt8Ty(), "trunc_char")
                                     : builder->CreateSub(L, R, "sub");
        case TokenType::MUL:
            if (lTyStr == "char" || rTyStr == "char") {
                cg_error((*bin)->op_tok.pos, "cannot perform this operation on char types");
                return nullptr;
            }
            if (lty->isPointerTy() || rty->isPointerTy()) {
                cg_error((*bin)->op_tok.pos, "cannot perform this operation on string types");
                return nullptr;
            }
            if (lty == builder->getInt1Ty() || rty == builder->getInt1Ty()) {
                cg_error((*bin)->op_tok.pos, "cannot perform arithmetic on bool types");
                return nullptr;
            }

            if (lty == builder->getIntNTy(2) || rty == builder->getIntNTy(2)) {
                cg_error((*bin)->op_tok.pos, "cannot perform arithmetic on qbool types");
                return nullptr;
            }
            return isFloatTy ? builder->CreateFMul(L, R, "fmul") : builder->CreateMul(L, R, "mul");
        case TokenType::DIV:
            if (lTyStr == "char" || rTyStr == "char") {
                cg_error((*bin)->op_tok.pos, "cannot perform this operation on char types");
                return nullptr;
            }
            if (lty->isPointerTy() || rty->isPointerTy()) {
                cg_error((*bin)->op_tok.pos, "cannot perform this operation on string types");
                return nullptr;
            }
            if (lty == builder->getInt1Ty() || rty == builder->getInt1Ty()) {
                cg_error((*bin)->op_tok.pos, "cannot perform arithmetic on bool types");
                return nullptr;
            }

            if (lty == builder->getIntNTy(2) || rty == builder->getIntNTy(2)) {
                cg_error((*bin)->op_tok.pos, "cannot perform arithmetic on qbool types");
                return nullptr;
            }
            return isFloatTy ? builder->CreateFDiv(L, R, "fdiv") : builder->CreateSDiv(L, R, "sdiv");
        case TokenType::MOD:
            if (lTyStr == "char" || rTyStr == "char") {
                cg_error((*bin)->op_tok.pos, "cannot perform this operation on char types");
                return nullptr;
            }
            if (lty->isPointerTy() || rty->isPointerTy()) {
                cg_error((*bin)->op_tok.pos, "cannot perform this operation on string types");
                return nullptr;
            }
            if (lty == builder->getInt1Ty() || rty == builder->getInt1Ty()) {
                cg_error((*bin)->op_tok.pos, "cannot perform arithmetic on bool types");
                return nullptr;
            }

            if (lty == builder->getIntNTy(2) || rty == builder->getIntNTy(2)) {
                cg_error((*bin)->op_tok.pos, "cannot perform arithmetic on qbool types");
                return nullptr;
            }
            return isFloatTy ? builder->CreateFRem(L, R, "frem") : builder->CreateSRem(L, R, "srem");
        case TokenType::AMPERSAND:
        case TokenType::PIPE:
        case TokenType::BITWISE_XOR:
            if (isFloatTy) {
                cg_error((*bin)->op_tok.pos, "cannot perform bitwise operations on float/double types");
                return nullptr;
            }
            if (lty->isPointerTy() || rty->isPointerTy()) {
                cg_error((*bin)->op_tok.pos, "cannot perform bitwise operations on string types");
                return nullptr;
            }
            if ((*bin)->op_tok.type == TokenType::AMPERSAND) return builder->CreateAnd(L, R, "andtmp");
            if ((*bin)->op_tok.type == TokenType::PIPE) return builder->CreateOr(L, R, "ortmp");
            return builder->CreateXor(L, R, "xortmp");
        case TokenType::RSHIFT:
        case TokenType::LSHIFT:
        case TokenType::LOGICAL_RSHIFT:
            if (isFloatTy) {
                cg_error((*bin)->op_tok.pos, "cannot perform shifts on float/double types");
                return nullptr;
            }
            if ((*bin)->op_tok.type == TokenType::LSHIFT) return builder->CreateShl(L, R, "shltmp");
            if ((*bin)->op_tok.type == TokenType::RSHIFT) return builder->CreateAShr(L, R, "ashrtmp");
            return builder->CreateLShr(L, R, "lshrtmp");
        case TokenType::L_ROT:
        case TokenType::R_ROT:
            if (isFloatTy) {
                cg_error((*bin)->op_tok.pos, "cannot perform rotations on float/double types");
                return nullptr;
            }
            {
                llvm::Intrinsic::ID id = ((*bin)->op_tok.type == TokenType::L_ROT) ? llvm::Intrinsic::fshl : llvm::Intrinsic::fshr;
                llvm::Function* rotFunc = llvm::Intrinsic::getOrInsertDeclaration(module, id, {lty});
                return builder->CreateCall(rotFunc, {L, L, R}, "rottmp");
            }
        case TokenType::POWER: {
            if (lTyStr == "char" || rTyStr == "char") {
                cg_error((*bin)->op_tok.pos, "cannot perform this operation on char types");
                return nullptr;
            }
            if (lty->isPointerTy() || rty->isPointerTy()) {
                cg_error((*bin)->op_tok.pos, "cannot perform this operation on string types");
                return nullptr;
            }
            if (lty == builder->getInt1Ty() || rty == builder->getInt1Ty()) {
                cg_error((*bin)->op_tok.pos, "cannot perform arithmetic on bool types");
                return nullptr;
            }

            if (lty == builder->getIntNTy(2) || rty == builder->getIntNTy(2)) {
                cg_error((*bin)->op_tok.pos, "cannot perform arithmetic on qbool types");
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
                cg_error((*bin)->op_tok.pos, "pOWER not supported for this type");
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
            auto isStringLike = [](const std::string& type) { return type == "string" || type == "char*"; };
            if (lty->isPointerTy() && rty->isPointerTy()) {
                std::string lType = getExpressionType((*bin)->left_node);
                std::string rType = getExpressionType((*bin)->right_node);
                if (isStringLike(lType) && isStringLike(rType)) {
                    llvm::Function* stringEq = module->getFunction("qc_string_eq");
                    if (!stringEq) {
                        auto* ptrTy = llvm::PointerType::get(context, 0);
                        auto* fnTy = llvm::FunctionType::get(builder->getInt1Ty(), {ptrTy, ptrTy}, false);
                        stringEq = llvm::Function::Create(fnTy, llvm::Function::InternalLinkage, "qc_string_eq", module);
                    }
                    llvm::Value* equal = builder->CreateCall(stringEq, {L, R}, "str_eq");
                    return op == TokenType::NOT_EQ ? builder->CreateNot(equal, "str_ne") : equal;
                }
                return op == TokenType::EQ_TO ? builder->CreateICmpEQ(L, R, "ptr_eq") : builder->CreateICmpNE(L, R, "ptr_ne");
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
            bool isFloatTy = false;
            if (lty->isPointerTy() || rty->isPointerTy()) {
                cg_error((*bin)->op_tok.pos, "cannot perform this operation on string types");
                return nullptr;
            }
            if (lty->isIntegerTy() && rty->isIntegerTy()) {
                unsigned lBits = lty->getIntegerBitWidth();
                unsigned rBits = rty->getIntegerBitWidth();
                if (lBits == 1 || lBits == 2 || rBits == 1 || rBits == 2) {
                    cg_error((*bin)->op_tok.pos, "cannot use comparison operators on bool/qbool");
                    return nullptr;
                }
                if (lBits < rBits) {
                    L = builder->CreateSExt(L, R->getType());
                    lty = L->getType();
                } else if (rBits < lBits) {
                    R = builder->CreateSExt(R, L->getType());
                    rty = R->getType();
                }
            } else if (lty->isFloatingPointTy() && rty->isFloatingPointTy()) {
                isFloatTy = true;
                if (lty->isFloatTy() && rty->isDoubleTy()) {
                    L = builder->CreateFPExt(L, rty);
                    lty = rty;
                } else if (lty->isDoubleTy() && rty->isFloatTy()) {
                    R = builder->CreateFPExt(R, lty);
                    rty = lty;
                }
            } else {
                cg_error((*bin)->op_tok.pos, "cannot compare non-numeric types with <, >, <=, >=");
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
            L = toTruthiness(L, get_pos((*bin)->left_node));
            R = toTruthiness(R, get_pos((*bin)->right_node));
            return builder->CreateAnd(L, R, "and");
        case TokenType::OR:
            L = toTruthiness(L, get_pos((*bin)->left_node));
            R = toTruthiness(R, get_pos((*bin)->right_node));
            return builder->CreateOr(L, R, "or");
        case TokenType::XOR:
            L = toTruthiness(L, get_pos((*bin)->left_node));
            R = toTruthiness(R, get_pos((*bin)->right_node));
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
                return builder->CreateCall(fn, {L8, R8});
            }
            cg_error((*bin)->op_tok.pos, "|&| requires qbool operands");
            return nullptr;
        default: break;
        }
    } else if (auto va = std::get_if<VarAssignNode*>(&node)) {
        std::string name = (*va)->var_name_tok.value;
        std::string qcType = (*va)->type_tok.value;
        bool isVolatile = false;
        if (qcType.starts_with("volatile ")) {
            isVolatile = true;
            qcType = qcType.substr(9, qcType.length() - 9);
        }
        if (qcType == "auto") {
            llvm::Value* rhs = emitExpr((*va)->value_node);
            if (!rhs) {
                cg_error((*va)->var_name_tok.pos, "cannot infer type from invalid expression");
                return nullptr;
            }

            llvm::Type* inferredTy = rhs->getType();
            llvm::AllocaInst* alloc = createEntryAlloca(name, inferredTy);
            builder->CreateStore(rhs, alloc, isVolatile);
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
                else if (elemTy->isIntegerTy(4))
                    arrayTypeStrings[name] = "nibble";
                else if (elemTy->isIntegerTy(2))
                    arrayTypeStrings[name] = "qbool";
                else if (elemTy->isPointerTy())
                    arrayTypeStrings[name] = "string";
            } else {
                varTypes[fullName] = qcType;
                volatileVars[fullName] = isVolatile;
            }

            return nullptr;
        }
        if (qcType == "auto[]" || qcType.starts_with("auto[")) {
            llvm::Value* rhs = emitExpr((*va)->value_node);
            if (!rhs) {
                cg_error((*va)->var_name_tok.pos, "cannot infer array type");
                return nullptr;
            }

            llvm::Type* rhsTy = rhs->getType();

            if (!rhsTy->isArrayTy()) {
                cg_error((*va)->var_name_tok.pos, "auto[] requires array literal");
                return nullptr;
            }

            llvm::AllocaInst* alloc = createEntryAlloca(name, rhsTy);
            builder->CreateStore(rhs, alloc, isVolatile);
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
            else if (elemTy->isIntegerTy(4))
                arrayTypeStrings[name] = "nibble";
            else if (elemTy->isIntegerTy(1))
                arrayTypeStrings[name] = "bool";
            else if (elemTy->isIntegerTy(2))
                arrayTypeStrings[name] = "qbool";
            else if (elemTy->isPointerTy())
                arrayTypeStrings[name] = "string";

            arrayLengths[name] = rhsTy->getArrayNumElements();
            volatileVars[name] = isVolatile;
            return nullptr;
        }

        std::string saved_qc_type = qcType;
        qcType = resolveTypeName(qcType);
        if ((*va)->is_foreign) {
            llvm::GlobalVariable* global = module->getGlobalVariable(name);
            if (!global) {
                global = new llvm::GlobalVariable(*module, llvmTypeFor(qcType), false, llvm::GlobalValue::ExternalLinkage, nullptr, name);
                globals[name] = global;
                varTypes[name] = qcType;
                volatileVars[name] = isVolatile;
            }
            return nullptr;
        }
        if (genericClasses.count(qcType) && genericClasses[qcType]) {
            std::string savedest_qc_type = saved_qc_type;
            std::string inner = saved_qc_type.substr(saved_qc_type.find('<') + 1, saved_qc_type.size() - saved_qc_type.find('<') - 2);
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
            auto userTypeIt = userTypes.find(qcType);
            llvm::StructType* classTy = generateGenericClass(qcType, userTypeIt->second, genericParams);
            if (classTy == nullptr) {
                cg_error((*va)->var_name_tok.pos, "failed to generate generic subset for class " + qcType);
                return nullptr;
            }
            llvm::AllocaInst* instance = createEntryAlloca(name, classTy);
            if (auto call = std::get_if<CallNode*>(&(*va)->value_node)) {
                bool handled = false;
                if (auto varAccess = std::get_if<VarAccessNode*>(&(*call)->node_to_call)) {
                    std::string calledName = (*varAccess)->var_name_tok.value;
                    if (calledName == buildMangledName(qcType, genericParams)) {
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
                            std::string mangledName = buildMangledName(qcType, genericParams);
                            llvm::Function* ctor = findMethodOverload(mangledName, ctorMethodName, args);
                            if (ctor) {
                                std::vector<llvm::Value*> allArgs = {instance};
                                allArgs.insert(allArgs.end(), args.begin(), args.end());
                                if (insideTry()) {
                                    auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++),
                                                                           currentFunction);
                                    llvm::InvokeInst* invk = builder->CreateInvoke(ctor, contBB, currentLandingPad(), allArgs);
                                    builder->SetInsertPoint(contBB);
                                } else {
                                    builder->CreateCall(ctor, allArgs);
                                }
                                std::string mangledName = buildMangledName(qcType, genericParams);
                                auto vtableIt = vtables.find(mangledName);
                                if (vtableIt != vtables.end()) {
                                    llvm::Value* vptrField = builder->CreateStructGEP(classTy, instance, 0, "vptr_field");
                                    builder->CreateStore(vtableIt->second, vptrField);
                                }
                                handled = true;
                            }
                        }
                    }
                }
                if (!handled) {
                    llvm::Value* rhs = emitExpr((*va)->value_node);
                    if (!rhs) return nullptr;
                    if (rhs->getType() != classTy) {
                        cg_error((*va)->var_name_tok.pos, "cannot initialize " + qcType + " from class of different type.");
                        return nullptr;
                    }
                    builder->CreateStore(rhs, instance, isVolatile);
                }
            } else if (auto arrLit = std::get_if<ArrayLiteralNode*>(&(*va)->value_node)) {
                llvm::Value* rhsVal = emitExpr(*arrLit);
                llvm::Value* len = builder->getInt32((*arrLit)->elements.size());
                rhsVal = decayArrayToPointer(rhsVal);
                if (rhsVal == nullptr) { return nullptr; }
                llvm::Function* opMethod = findMethodOverload(buildMangledName(qcType, genericParams), "operator[]=", {rhsVal, len});
                std::string mangledName = buildMangledName(qcType, genericParams);
                if (opMethod) {
                    emitMethodCall(opMethod, instance, {rhsVal, len}, "operator[]=");
                    std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
                    locals[fullName] = instance;
                    varTypes[fullName] = mangledName;
                    volatileVars[fullName] = isVolatile;
                } else {
                    cg_error((*va)->var_name_tok.pos, "no valid operator[]= method found on class " + qcType);
                    return nullptr;
                }
                auto vtableIt = vtables.find(mangledName);
                if (vtableIt != vtables.end()) {
                    llvm::Value* vptrField = builder->CreateStructGEP(classTy, instance, 0, "vptr_field");
                    builder->CreateStore(vtableIt->second, vptrField);
                }
                return nullptr;
            }
            std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[fullName] = instance;
            volatileVars[fullName] = isVolatile;
            varTypes[fullName] = buildMangledName(qcType, genericParams);
            return nullptr; // do this for every single type.
        }
        auto userTypeIt = userTypes.find(qcType);
        if (genericStructs.count(qcType) && genericStructs[qcType]) {
            std::string savedest_qc_type = saved_qc_type;
            std::string inner = saved_qc_type.substr(saved_qc_type.find('<') + 1, saved_qc_type.size() - saved_qc_type.find('<') - 2);
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
            auto userTypeIt = userTypes.find(qcType);
            llvm::StructType* structTy = generateGenericStruct(qcType, userTypeIt->second, genericParams);
            if (structTy == nullptr) {
                cg_error((*va)->var_name_tok.pos, "failed to generate generic subset for struct " + qcType);
                return nullptr;
            }
            if (auto arrLit = std::get_if<ArrayLiteralNode*>(&(*va)->value_node)) {
                llvm::StructType* structTy = genericiseOrFindStruct(buildMangledName(qcType, genericParams));
                if (!(*arrLit)->type.empty()) {
                    if (buildMangledName(qcType, genericParams) != fixMangling(resolveTypeName((*arrLit)->type, true))) {
                        cg_error(get_pos(*va), "cannot initialize struct with literal of different struct type");
                        cg_note(get_pos(*arrLit), "got type " + fixMangling(resolveTypeName((*arrLit)->type, true)) + ", expected " +
                                                      buildMangledName(qcType, genericParams));
                        return nullptr;
                    }
                }
                llvm::Value* structVal = llvm::ConstantAggregateZero::get(structTy);
                auto& structInfo = userTypeIt->second;
                for (size_t i = 0; i < (*arrLit)->elements.size(); i++) {
                    std::string fieldType = structInfo.fields[i].type;
                    auto fieldTypeIt = userTypes.find(fieldType);
                    llvm::Value* val;
                    if (fieldTypeIt != userTypes.end() && fieldTypeIt->second.kind == UserTypeKind::Struct) {
                        if (auto nestedArrLit = std::get_if<ArrayLiteralNode*>(&(*arrLit)->elements[i])) {
                            llvm::StructType* nestedStructTy = genericiseOrFindStruct(fieldType);
                            llvm::Value* nestedStruct = llvm::ConstantAggregateZero::get(nestedStructTy);
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
                builder->CreateStore(structVal, structAlloc, isVolatile);
                std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
                locals[fullName] = structAlloc;
                varTypes[fullName] = buildMangledName(qcType, genericParams);
                volatileVars[fullName] = isVolatile;
                return nullptr;
            } else if (auto mapLit = std::get_if<MapLiteralNode*>(&(*va)->value_node)) {
                llvm::StructType* structTy = genericiseOrFindStruct(buildMangledName(qcType, genericParams));
                if (!(*mapLit)->struct_type.empty()) {
                    if (buildMangledName(qcType, genericParams) != fixMangling(resolveTypeName((*mapLit)->struct_type, true))) {
                        cg_error(get_pos(*va), "cannot initialize struct with literal of different struct type");
                        cg_note(get_pos(*mapLit), "got type " + fixMangling(resolveTypeName((*mapLit)->struct_type, true)) + ", expected " +
                                                      buildMangledName(qcType, genericParams));
                        return nullptr;
                    }
                }
                llvm::Value* structVal = llvm::ConstantAggregateZero::get(structTy);
                auto& structInfo = userTypeIt->second;
                for (auto& [keyNode, valueNode] : (*mapLit)->pairs) {
                    std::string fieldName;
                    if (auto key = std::get_if<VarAccessNode*>(&keyNode)) {
                        fieldName = (*key)->var_name_tok.value;
                    } else if (auto key = std::get_if<StringNode>(&keyNode)) {
                        fieldName = key->tok.value;
                    } else {
                        cg_error((*mapLit)->pos, "struct field name must be an identifier");
                        return nullptr;
                    }
                    int fieldIndex = -1;
                    for (size_t i = 0; i < structInfo.fields.size(); i++) {
                        if (structInfo.fields[i].name == fieldName) {
                            fieldIndex = i;
                            break;
                        }
                    }
                    if (fieldIndex == -1) {
                        cg_error((*mapLit)->pos, "unknown field '" + fieldName + "' in struct " + qcType);
                        return nullptr;
                    }
                    llvm::Value* fieldValue = emitExpr(valueNode);
                    if (!fieldValue) return nullptr;
                    structVal = builder->CreateInsertValue(structVal, fieldValue, fieldIndex);
                }
                llvm::AllocaInst* structAlloc = createEntryAlloca(name, structTy);
                builder->CreateStore(structVal, structAlloc, isVolatile);
                std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
                locals[fullName] = structAlloc;
                varTypes[fullName] = buildMangledName(qcType, genericParams);
                volatileVars[fullName] = isVolatile;
                return nullptr;
            }
            return nullptr;
        }
        if (genericUnions.count(qcType) && genericUnions[qcType]) {
            UserTypeInfo info = genericiseOrFindUnion(saved_qc_type);
            llvm::StructType* unionTy = unionTypes[resolveTypeName(saved_qc_type, false)];
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
                cg_error((*va)->var_name_tok.pos, "value does not match any variant of union " + qcType);
                return nullptr;
            }
            auto& member = info.members[tag];
            bool isLiteral = member.type.find(':') != std::string::npos;
            llvm::Type* rhsTy = rhs->getType();
            std::string baseType = isLiteral ? member.type.substr(0, member.type.find(':')) : member.type;
            llvm::Type* memberTy = llvmTypeFor(baseType);
            if (!rhsTy->isPointerTy() && rhsTy != memberTy) {
                cg_error((*va)->var_name_tok.pos, "union literal variant type mismatch");
                return nullptr;
            }
            llvm::Value* unionVal = llvm::ConstantAggregateZero::get(unionTy);
            unionVal = builder->CreateInsertValue(unionVal, builder->getInt32(tag), 0);
            llvm::Value* dataPtr = storeAndGetPointer(rhs);
            unionVal = builder->CreateInsertValue(unionVal, dataPtr, 1);
            builder->CreateStore(unionVal, unionAlloc, isVolatile);
            std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[fullName] = unionAlloc;
            varTypes[fullName] = fixMangling(saved_qc_type);
            volatileVars[fullName] = isVolatile;
            return nullptr;
        }
        if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Struct) {
            if (auto arrLit = std::get_if<ArrayLiteralNode*>(&(*va)->value_node)) {
                llvm::StructType* structTy = genericiseOrFindStruct(qcType);
                if (!(*arrLit)->type.empty()) {
                    if (qcType != fixMangling(resolveTypeName((*arrLit)->type, true))) {
                        cg_error(get_pos(*va), "cannot initialize struct with literal of different struct type");
                        cg_note(get_pos(*arrLit), "got type " + fixMangling(resolveTypeName((*arrLit)->type, true)) + ", expected " + qcType);
                        return nullptr;
                    }
                }
                llvm::Value* structVal = llvm::Constant::getNullValue(structTy);
                auto& structInfo = userTypeIt->second;
                for (size_t i = 0; i < (*arrLit)->elements.size(); i++) {
                    std::string fieldType = structInfo.fields[i].type;
                    auto fieldTypeIt = userTypes.find(fieldType);
                    llvm::Value* val;

                    if (fieldTypeIt != userTypes.end() && fieldTypeIt->second.kind == UserTypeKind::Struct) {
                        if (auto nestedArrLit = std::get_if<ArrayLiteralNode*>(&(*arrLit)->elements[i])) {
                            llvm::StructType* nestedStructTy = genericiseOrFindStruct(fieldType);
                            llvm::Value* nestedStruct = llvm::Constant::getNullValue(nestedStructTy);
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
                llvm::Value* structAlloc = getVarAddress(name);
                if (auto* gv = llvm::dyn_cast_or_null<llvm::GlobalVariable>(structAlloc)) {
                    auto* constant = llvm::dyn_cast<llvm::Constant>(structVal);
                    if (!constant) {
                        cg_error((*va)->var_name_tok.pos, "global struct initializer must be constant");
                        return nullptr;
                    }
                    gv->setInitializer(constant);
                    return nullptr;
                } else {
                    if (!structAlloc) structAlloc = createEntryAlloca(name, structTy);

                    builder->CreateStore(structVal, structAlloc, isVolatile);
                }
                std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
                locals[fullName] = llvm::cast<llvm::AllocaInst>(structAlloc);
                varTypes[fullName] = qcType;
                volatileVars[fullName] = isVolatile;
                return nullptr;
            } else if (auto mapLit = std::get_if<MapLiteralNode*>(&(*va)->value_node)) {
                llvm::StructType* structTy = genericiseOrFindStruct(qcType);
                if (!(*mapLit)->struct_type.empty()) {
                    if (qcType != fixMangling(resolveTypeName((*mapLit)->struct_type, true))) {
                        cg_error(get_pos(*va), "cannot initialize struct with literal of different struct type");
                        cg_note(get_pos(*mapLit), "got type " + fixMangling(resolveTypeName((*mapLit)->struct_type, true)) + ", expected " + qcType);
                        return nullptr;
                    }
                }
                llvm::Value* structVal = llvm::ConstantAggregateZero::get(structTy);

                auto& structInfo = userTypeIt->second;

                for (auto& [keyNode, valueNode] : (*mapLit)->pairs) {
                    std::string fieldName;

                    if (auto key = std::get_if<VarAccessNode*>(&keyNode)) {
                        fieldName = (*key)->var_name_tok.value;
                    } else if (auto key = std::get_if<StringNode>(&keyNode)) {
                        fieldName = key->tok.value;
                    } else {
                        cg_error((*mapLit)->pos, "struct field name must be an identifier");
                        return nullptr;
                    }

                    int fieldIndex = -1;

                    for (size_t i = 0; i < structInfo.fields.size(); i++) {
                        if (structInfo.fields[i].name == fieldName) {
                            fieldIndex = i;
                            break;
                        }
                    }

                    if (fieldIndex == -1) {
                        cg_error((*mapLit)->pos, "unknown field '" + fieldName + "' in struct " + qcType);
                        return nullptr;
                    }

                    llvm::Value* fieldValue = emitExpr(valueNode);

                    if (!fieldValue) return nullptr;

                    structVal = builder->CreateInsertValue(structVal, fieldValue, fieldIndex);
                }

                llvm::Value* structAlloc = getVarAddress(name);
                if (auto* gv = llvm::dyn_cast_or_null<llvm::GlobalVariable>(structAlloc)) {
                    auto* constant = llvm::dyn_cast<llvm::Constant>(structVal);
                    if (!constant) {
                        cg_error((*va)->var_name_tok.pos, "global struct initializer must be constant");
                        return nullptr;
                    }
                    gv->setInitializer(constant);
                    return nullptr;
                } else {
                    if (!structAlloc) structAlloc = createEntryAlloca(name, structTy);

                    builder->CreateStore(structVal, structAlloc, isVolatile);
                }
                std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;

                locals[fullName] = llvm::cast<llvm::AllocaInst>(structAlloc);
                varTypes[fullName] = qcType;
                volatileVars[fullName] = isVolatile;
                return nullptr;
            }
        }
        if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Class) {
            llvm::StructType* classTy = genericiseOrFindClass(qcType);
            llvm::AllocaInst* instance = createEntryAlloca(name, classTy);
            if (auto call = std::get_if<CallNode*>(&(*va)->value_node)) {
                bool handled = false;
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
                                if (insideTry()) {
                                    auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++),
                                                                           currentFunction);
                                    llvm::InvokeInst* invk = builder->CreateInvoke(ctor, contBB, currentLandingPad(), allArgs);
                                    builder->SetInsertPoint(contBB);
                                    return invk;
                                } else {
                                    builder->CreateCall(ctor, allArgs);
                                }
                                auto vtableIt = vtables.find(qcType);
                                if (vtableIt != vtables.end()) {
                                    llvm::Value* vptrField = builder->CreateStructGEP(classTy, instance, 0, "vptr_field");
                                    builder->CreateStore(vtableIt->second, vptrField);
                                }
                                handled = true;
                            }
                        }
                    }
                }
                if (!handled) {
                    llvm::Value* rhs = emitExpr((*va)->value_node);
                    if (!rhs) return nullptr;
                    if (rhs->getType() != classTy) {
                        cg_error((*va)->var_name_tok.pos, "cannot initialize " + qcType + " from class of different type.");
                        return nullptr;
                    }
                    builder->CreateStore(rhs, instance, isVolatile);
                }
            } else if (auto arrLit = std::get_if<ArrayLiteralNode*>(&(*va)->value_node)) {
                llvm::Value* rhsVal = emitExpr(*arrLit);
                llvm::Value* len = builder->getInt32((*arrLit)->elements.size());
                rhsVal = decayArrayToPointer(rhsVal);
                if (rhsVal == nullptr) { return nullptr; }
                llvm::Function* opMethod = findMethodOverload(qcType, "operator[]=", {rhsVal, len});
                if (opMethod) {
                    emitMethodCall(opMethod, instance, {rhsVal, len}, "operator[]=");
                    std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
                    locals[fullName] = instance;
                    varTypes[fullName] = qcType;
                    volatileVars[fullName] = isVolatile;
                } else {
                    cg_error((*va)->var_name_tok.pos, "no valid operator[]= method found on class " + qcType);
                    return nullptr;
                }
                auto vtableIt = vtables.find(qcType);
                if (vtableIt != vtables.end()) {
                    llvm::Value* vptrField = builder->CreateStructGEP(classTy, instance, 0, "vptr_field");
                    builder->CreateStore(vtableIt->second, vptrField);
                }
                return nullptr;
            } else {
                llvm::Value* rhs = emitExpr((*va)->value_node);
                if (!rhs) return nullptr;
                if (rhs->getType() != classTy) {
                    cg_error((*va)->var_name_tok.pos, "cannot initialize " + qcType + " from class of different type.");
                    return nullptr;
                }
                builder->CreateStore(rhs, instance, isVolatile);
            }
            std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[fullName] = instance;
            varTypes[fullName] = qcType;
            volatileVars[fullName] = isVolatile;
            return nullptr;
        }
        if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Union) {
            llvm::StructType* unionTy = unionTypes[qcType];
            llvm::Value* unionAlloc = getVarAddress(name);
            if (!unionAlloc) unionAlloc = createEntryAlloca(name, unionTy);
            llvm::Value* rhs = emitExpr((*va)->value_node);
            if (!rhs) return nullptr;
            auto storeUnion = [&](llvm::Value* value) {
                if (auto* gv = llvm::dyn_cast<llvm::GlobalVariable>(unionAlloc)) {
                    auto* constant = llvm::dyn_cast<llvm::Constant>(value);
                    if (!constant) {
                        cg_error((*va)->var_name_tok.pos, "global union initializer must be constant");
                        return false;
                    }
                    gv->setInitializer(constant);
                    return false;
                } else {
                    builder->CreateStore(value, unionAlloc, isVolatile);
                }
                return true;
            };
            if (rhs->getType() == unionTy) {
                if (!storeUnion(rhs)) return nullptr;
                std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
                locals[fullName] = llvm::cast<llvm::AllocaInst>(unionAlloc);
                volatileVars[fullName] = isVolatile;
                return nullptr;
            }
            int tag = findUnionVariantTag(qcType, (*va)->value_node, rhs);
            if (tag == -1) {
                cg_error((*va)->var_name_tok.pos, "value does not match any variant of union " + qcType);
                return nullptr;
            }
            auto& member = userTypes.at(baseTypeName(qcType)).members[tag];
            bool isLiteral = member.type.find(':') != std::string::npos;
            llvm::Type* rhsTy = rhs->getType();
            std::string baseType = isLiteral ? member.type.substr(0, member.type.find(':')) : member.type;
            llvm::Type* memberTy = llvmTypeFor(baseType);
            if (!rhsTy->isPointerTy() && rhsTy != memberTy) {
                cg_error((*va)->var_name_tok.pos, "union literal variant type mismatch");
                return nullptr;
            }
            llvm::Value* unionVal = llvm::ConstantAggregateZero::get(unionTy);
            unionVal = builder->CreateInsertValue(unionVal, builder->getInt32(tag), 0);
            llvm::Value* dataPtr = storeAndGetPointer(rhs);
            unionVal = builder->CreateInsertValue(unionVal, dataPtr, 1);
            if (!storeUnion(unionVal)) return nullptr;
            std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[fullName] = llvm::cast<llvm::AllocaInst>(unionAlloc);
            varTypes[fullName] = qcType;
            volatileVars[fullName] = isVolatile;
            return nullptr;
        }
        if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Enum) {
            llvm::StructType* enumTy = enumTypes[qcType];
            llvm::Value* enumAlloc = getVarAddress(name);
            if (!enumAlloc) enumAlloc = createEntryAlloca(name, enumTy);
            llvm::Value* rhs = emitExpr((*va)->value_node);
            if (!rhs) return nullptr;
            if (auto* gv = llvm::dyn_cast<llvm::GlobalVariable>(enumAlloc)) {
                auto* constant = llvm::dyn_cast<llvm::Constant>(rhs);
                if (!constant) {
                    cg_error((*va)->var_name_tok.pos, "global enum initializer must be constant");
                    return nullptr;
                }
                gv->setInitializer(constant);
                return nullptr;
            } else {
                builder->CreateStore(rhs, enumAlloc, isVolatile);
            }
            std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[fullName] = llvm::cast<llvm::AllocaInst>(enumAlloc);
            varTypes[fullName] = qcType;
            volatileVars[fullName] = isVolatile;
            return nullptr;
        }
        if (qcType.find("[]") != std::string::npos) {
            std::string baseType = qcType;
            while (baseType.ends_with("[]")) { baseType = baseType.substr(0, baseType.length() - 2); }
            arrayTypeStrings[name] = baseType;
        }
        llvm::AllocaInst* alloc = nullptr;
        if ((*va)->type_tok.value == "function" || (*va)->type_tok.value.starts_with("fn(") || (*va)->type_tok.value.starts_with("fn (") ||
            (*va)->type_tok.value == "auto" && std::holds_alternative<FuncDefNode*>((*va)->value_node)) {
            auto fnPtr = std::get<FuncDefNode*>((*va)->value_node);
            llvm::Function* f = emitFuncDef(*fnPtr);
            name = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            lambdaTypes[name] = f->getFunctionType();
            llvm::Type* funcPtrTy = llvm::PointerType::get(context, 0);
            alloc = createEntryAlloca(name, funcPtrTy);

            locals[name] = alloc;
            volatileVars[name] = isVolatile;
            builder->CreateStore(f, alloc, isVolatile);
            return nullptr;
        }
        llvm::Value* existingAlloc = getVarAddress(name);
        std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
        if (!existingAlloc) {
            llvm::Type* ty = llvmTypeFor(qcType);
            if (!ty) {
                cg_error((*va)->var_name_tok.pos, "unknown type: " + qcType);
                return nullptr;
            }
            alloc = createEntryAlloca(fullName, ty);
            locals[fullName] = alloc;
            varTypes[fullName] = qcType;
            volatileVars[fullName] = isVolatile;
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
                    volatileVars[fullName] = isVolatile;
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
            cg_error((*va)->var_name_tok.pos, "failed to compile initializer for '" + name + "'");
            return nullptr;
        }

        llvm::Type* srcTy = rhs->getType();
        if (isUnionType(srcTy) && !isUnionType(destTy)) {
            llvm::Value* dataPtr = builder->CreateExtractValue(rhs, 1, "union_data");

            if (destTy->isPointerTy()) {
                rhs = builder->CreateBitCast(dataPtr, destTy);
            } else {
                llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                rhs = builder->CreateLoad(destTy, typedPtr);
            }

            srcTy = destTy;
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
            } else if (srcTy->isArrayTy() && destTy->isPointerTy()) {
                auto* arr_alloca = builder->CreateAlloca(srcTy);
                builder->CreateStore(rhs, arr_alloca);
                rhs = builder->CreateGEP(srcTy, arr_alloca, {builder->getInt32(0), builder->getInt32(0)});
            } else if (srcTy->isArrayTy() && destTy->isArrayTy()) {
                auto* srcArrTy = llvm::cast<llvm::ArrayType>(srcTy);
                auto* destArrTy = llvm::cast<llvm::ArrayType>(destTy);
                if (srcArrTy->getElementType() != destArrTy->getElementType()) {
                    cg_error((*va)->var_name_tok.pos, "array element type mismatch in assignment");
                    return nullptr;
                }
                uint64_t srcLen = srcArrTy->getNumElements();
                uint64_t destLen = destArrTy->getNumElements();
                if (srcLen > destLen) {
                    cg_error((*va)->var_name_tok.pos, "source array is larger than destination array");
                    return nullptr;
                }
                if (!rhs->getType()->isPointerTy()) {
                    auto* tmp = createEntryAlloca("src_array_tmp", srcArrTy);
                    builder->CreateStore(rhs, tmp);
                    rhs = tmp;
                }
                llvm::AllocaInst* newArr = createEntryAlloca("array_copy", destArrTy);
                uint64_t bytes = srcLen * srcArrTy->getElementType()->getPrimitiveSizeInBits() / 8;
                builder->CreateMemCpy(newArr, llvm::MaybeAlign(), rhs, llvm::MaybeAlign(), bytes);
                if (destLen > srcLen) {
                    llvm::Value* zeroStart = builder->CreateGEP(destArrTy, newArr, {builder->getInt32(0), builder->getInt32(srcLen)});
                    uint64_t zeroBytes = (destLen - srcLen) * srcArrTy->getElementType()->getPrimitiveSizeInBits() / 8;
                    builder->CreateMemSet(zeroStart, builder->getInt8(0), zeroBytes, llvm::MaybeAlign());
                }
                rhs = newArr;
            } else if (srcTy->isDoubleTy() && destTy->isFloatTy()) {
                cg_error((*va)->var_name_tok.pos, "cannot assign double to float in compiled mode");
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
                cg_error((*va)->var_name_tok.pos, "type mismatch in assignment in compiled mode");
                return nullptr;
            }
        }
        if (llvm::isa<llvm::ConstantAggregateZero>(rhs) && srcTy->isArrayTy()) {
            uint64_t bytes = module->getDataLayout().getTypeAllocSize(srcTy);
            builder->CreateMemSet(alloc, builder->getInt8(0), bytes, llvm::MaybeAlign(), isVolatile);
        } else {
            builder->CreateStore(rhs, alloc, isVolatile);
        }
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
        if (currentNonTypeGenericValues.find(name) != currentNonTypeGenericValues.end()) {
            auto& entry = currentNonTypeGenericValues[name];
            llvm::Type* ty = llvmTypeFor(entry.nonTypeKind);
            if (ty->isIntegerTy()) {
                return llvm::ConstantInt::get(ty, std::stoull(entry.name), true);
            } else if (ty->isFloatingPointTy()) {
                return llvm::ConstantFP::get(ty, std::stod(entry.name));
            } else if (entry.nonTypeKind == "string") {
                return builder->CreateGlobalString(entry.name);
            }
        }
        llvm::Value* alloc = getVarAddress(name);
        if (alloc) {
            llvm::Type* ty = getPointeeType(name);
            if (ty == nullptr) {
                cg_error((*acc)->var_name_tok.pos, "could not resolve var type");
                return nullptr;
            }
            return builder->CreateLoad(ty, alloc, resolveVolatileVar(name), name);
        }

        llvm::Function* fn = resolveFunction(name);
        if (fn) { return fn; }

        cg_error((*acc)->var_name_tok.pos, "use of undeclared variable '" + name + "'");
        auto suggestions = getVisibleVariables();
        std::vector<std::pair<int, std::string>> matches;
        if (name.size() >= 3) {
            for (auto& vname : suggestions) {
                int distance = levenshteinDistance(name, vname);
                if (distance <= 2) { matches.push_back({distance, vname}); }
            }
        }
        std::sort(matches.begin(), matches.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
        if (!matches.empty()) {
            std::string note = "did you mean ";
            size_t count = std::min<size_t>(3, matches.size());
            for (size_t i = 0; i < count; i++) {
                if (i != 0) note += ", ";
                note += "`" + matches[i].second + "`";
            }
            note += "?";
            cg_note((*acc)->var_name_tok.pos, note);
        }
        return nullptr;
    } else if (auto asn = std::get_if<AssignExprNode*>(&node)) {
        if (auto propAccess = std::get_if<PropertyAccessNode*>(&(*asn)->target)) {
            std::string fieldName = (*propAccess)->property_name.value;

            if (auto varAccess = std::get_if<VarAccessNode*>(&*(*propAccess)->base)) {
                std::string varName = (*varAccess)->var_name_tok.value;
                if (varName == "this" && currentThis && !currentClassName.empty()) {
                    llvm::StructType* classTy = genericiseOrFindClass(currentClassName);
                    int fieldIdx = getFlattenedFieldIndex(baseTypeName(currentClassName), fieldName);
                    if (fieldIdx == -1) {
                        cg_error((*propAccess)->property_name.pos, "field not found: " + fieldName);
                        return nullptr;
                    }
                    std::string resolvedFieldType;
                    std::function<bool(const std::string&)> findFieldType = [&](const std::string& cname) -> bool {
                        auto& ci = userTypes.at(baseTypeName(baseTypeName(cname)));
                        if (!ci.baseClassName.empty() && findFieldType(ci.baseClassName)) return true;
                        for (auto& field : ci.classFields) {
                            if (field.name == fieldName) {
                                resolvedFieldType = field.type;
                                return true;
                            }
                        }
                        return false;
                    };
                    findFieldType(baseTypeName(currentClassName));
                    llvm::Type* fieldTy = llvmTypeFor(resolvedFieldType);
                    llvm::Value* fieldPtr = builder->CreateStructGEP(classTy, currentThis, fieldIdx);
                    llvm::Value* rhsVal = emitExpr((*asn)->value);
                    if (!rhsVal) return nullptr;
                    TokenType op = (*asn)->op_tok.type;
                    if (op != TokenType::EQ) {
                        llvm::Value* oldVal = builder->CreateLoad(fieldTy, fieldPtr);
                        bool isFloat = fieldTy->isFloatingPointTy();
                        if (op == TokenType::PLUS_EQ && (resolvedFieldType == "char*" || resolvedFieldType == "string") &&
                            std::unordered_set<std::string>({"string", "char*"}).contains(getExpressionType((*asn)->value))) {
                            llvm::Value* concatedString = callStringConcat(oldVal, rhsVal);
                            builder->CreateStore(concatedString, fieldPtr);
                            return concatedString;
                        }
                        if (oldVal->getType()->isPointerTy() && (op == TokenType::MINUS_EQ || op == TokenType::PLUS_EQ)) {
                            if (!rhsVal->getType()->isIntegerTy()) {
                                cg_error((*asn)->op_tok.pos, "pointer offset must be integer");
                                return nullptr;
                            }
                            llvm::Value* offset = rhsVal;
                            if (op == TokenType::MINUS_EQ) { offset = builder->CreateNeg(offset, "neg_offset"); }
                            std::string baseType = resolvedFieldType;
                            baseType.pop_back();
                            llvm::Type* elementTy = resolvedFieldType == "string" ? builder->getInt8Ty() : llvmTypeFor(baseType);
                            llvm::Value* newPtr = builder->CreateGEP(elementTy, oldVal, offset, "ptr_add");
                            builder->CreateStore(newPtr, fieldPtr);
                            return newPtr;
                        }
                        switch (op) {
                        case TokenType::PLUS_EQ: rhsVal = isFloat ? builder->CreateFAdd(oldVal, rhsVal) : builder->CreateAdd(oldVal, rhsVal); break;

                        case TokenType::MINUS_EQ: rhsVal = isFloat ? builder->CreateFSub(oldVal, rhsVal) : builder->CreateSub(oldVal, rhsVal); break;

                        case TokenType::MUL_EQ: rhsVal = isFloat ? builder->CreateFMul(oldVal, rhsVal) : builder->CreateMul(oldVal, rhsVal); break;

                        case TokenType::DIV_EQ: rhsVal = isFloat ? builder->CreateFDiv(oldVal, rhsVal) : builder->CreateSDiv(oldVal, rhsVal); break;

                        case TokenType::MOD_EQ: rhsVal = isFloat ? builder->CreateFRem(oldVal, rhsVal) : builder->CreateSRem(oldVal, rhsVal); break;

                        case TokenType::RSH_EQ: rhsVal = builder->CreateAShr(oldVal, rhsVal); break;

                        case TokenType::LSH_EQ: rhsVal = builder->CreateShl(oldVal, rhsVal); break;

                        case TokenType::LRSH_EQ: rhsVal = builder->CreateLShr(oldVal, rhsVal); break;

                        case TokenType::BIT_A_EQ: rhsVal = builder->CreateAnd(oldVal, rhsVal); break;

                        case TokenType::BIT_O_EQ: rhsVal = builder->CreateOr(oldVal, rhsVal); break;

                        case TokenType::BIT_X_EQ: rhsVal = builder->CreateXor(oldVal, rhsVal); break;

                        case TokenType::LROT_EQ:
                            rhsVal = builder->CreateIntrinsic(llvm::Intrinsic::fshl, {oldVal->getType()}, {oldVal, oldVal, rhsVal});
                            break;

                        case TokenType::RROT_EQ:
                            rhsVal = builder->CreateIntrinsic(llvm::Intrinsic::fshr, {oldVal->getType()}, {oldVal, oldVal, rhsVal});
                            break;

                        default: break;
                        }
                    }

                    builder->CreateStore(rhsVal, fieldPtr);
                    return rhsVal;
                }
                llvm::Value* locAlloc = getVarAddress(varName);
                if (!locAlloc) {
                    cg_error(get_pos(*varAccess), "unknown variable: " + varName);
                    return nullptr;
                }

                llvm::Type* allocTy = getPointeeType(varName);

                auto structTy = llvm::dyn_cast<llvm::StructType>(allocTy);
                if (!structTy) {
                    cg_error(get_pos(*varAccess), "not a struct");
                    return nullptr;
                }

                std::string structName = structTy->getName().str();
                int fieldIdx = getFlattenedFieldIndex(structName, fieldName);

                llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, locAlloc, fieldIdx);
                llvm::Type* fieldTy = structTy->getElementType(fieldIdx);

                llvm::Value* rhsVal = emitExpr((*asn)->value);
                TokenType op = (*asn)->op_tok.type;
                std::string resolvedFieldType;
                std::function<bool(const std::string&)> findFieldType = [&](const std::string& cname) -> bool {
                    auto& ci = userTypes.at(baseTypeName(baseTypeName(cname)));
                    if (!ci.baseClassName.empty() && findFieldType(ci.baseClassName)) return true;
                    for (auto& field : ci.fields) {
                        if (field.name == fieldName) {
                            resolvedFieldType = field.type;
                            return true;
                        }
                    }
                    return false;
                };
                findFieldType(baseTypeName(structName));
                if (op != TokenType::EQ) {
                    llvm::Value* oldVal = builder->CreateLoad(fieldTy, fieldPtr);
                    bool isFloat = fieldTy->isFloatingPointTy();
                    if (op == TokenType::PLUS_EQ && (resolvedFieldType == "char*" || resolvedFieldType == "string") &&
                        std::unordered_set<std::string>({"string", "char*"}).contains(getExpressionType((*asn)->value))) {
                        llvm::Value* concatedString = callStringConcat(oldVal, rhsVal);
                        builder->CreateStore(concatedString, fieldPtr);
                        return concatedString;
                    }
                    if (oldVal->getType()->isPointerTy() && (op == TokenType::MINUS_EQ || op == TokenType::PLUS_EQ)) {
                        if (!rhsVal->getType()->isIntegerTy()) {
                            cg_error(get_pos((*asn)->value), "pointer offset must be an integer");
                            return nullptr;
                        }
                        llvm::Value* offset = rhsVal;
                        if (op == TokenType::MINUS_EQ) { offset = builder->CreateNeg(offset, "neg_offset"); }
                        std::string baseType = resolvedFieldType;
                        baseType.pop_back();
                        llvm::Type* elementTy = resolvedFieldType == "string" ? builder->getInt8Ty() : llvmTypeFor(baseType);
                        llvm::Value* newPtr = builder->CreateGEP(elementTy, oldVal, offset, "ptr_add");
                        builder->CreateStore(newPtr, fieldPtr);
                        return newPtr;
                    }
                    switch (op) {
                    case TokenType::PLUS_EQ: rhsVal = isFloat ? builder->CreateFAdd(oldVal, rhsVal) : builder->CreateAdd(oldVal, rhsVal); break;

                    case TokenType::MINUS_EQ: rhsVal = isFloat ? builder->CreateFSub(oldVal, rhsVal) : builder->CreateSub(oldVal, rhsVal); break;

                    case TokenType::MUL_EQ: rhsVal = isFloat ? builder->CreateFMul(oldVal, rhsVal) : builder->CreateMul(oldVal, rhsVal); break;

                    case TokenType::DIV_EQ: rhsVal = isFloat ? builder->CreateFDiv(oldVal, rhsVal) : builder->CreateSDiv(oldVal, rhsVal); break;

                    case TokenType::MOD_EQ: rhsVal = isFloat ? builder->CreateFRem(oldVal, rhsVal) : builder->CreateSRem(oldVal, rhsVal); break;

                    case TokenType::RSH_EQ: rhsVal = builder->CreateAShr(oldVal, rhsVal); break;

                    case TokenType::LSH_EQ: rhsVal = builder->CreateShl(oldVal, rhsVal); break;

                    case TokenType::LRSH_EQ: rhsVal = builder->CreateLShr(oldVal, rhsVal); break;

                    case TokenType::BIT_A_EQ: rhsVal = builder->CreateAnd(oldVal, rhsVal); break;

                    case TokenType::BIT_O_EQ: rhsVal = builder->CreateOr(oldVal, rhsVal); break;

                    case TokenType::BIT_X_EQ: rhsVal = builder->CreateXor(oldVal, rhsVal); break;

                    case TokenType::LROT_EQ:
                        rhsVal = builder->CreateIntrinsic(llvm::Intrinsic::fshl, {oldVal->getType()}, {oldVal, oldVal, rhsVal});
                        break;

                    case TokenType::RROT_EQ:
                        rhsVal = builder->CreateIntrinsic(llvm::Intrinsic::fshr, {oldVal->getType()}, {oldVal, oldVal, rhsVal});
                        break;

                    default: break;
                    }
                }

                builder->CreateStore(rhsVal, fieldPtr);
                return rhsVal;
            }
        }
        llvm::Value* alloc = emitLValue((*asn)->target);
        if (!alloc) {
            cg_error((*asn)->op_tok.pos, "left side of assignment must be an L-value "
                                         "(variable, property, or dereference)");
            return nullptr;
        }
        std::string name = "";
        if (auto acc = std::get_if<VarAccessNode*>(&((*asn)->target))) { name = (*acc)->var_name_tok.value; }
        std::string lhsTypeStr = getExpressionType((*asn)->target);
        llvm::Type* destTy = llvmTypeFor(lhsTypeStr);
        if (!destTy) {
            cg_error(get_pos((*asn)->target), "could not resolve type " + lhsTypeStr + " for assignment");
            return nullptr;
        }
        for (auto& [unionName, unionTy] : unionTypes) {
            if (destTy == unionTy) {
                llvm::Value* rhs = emitExpr((*asn)->value);
                if (!rhs) return nullptr;
                if (rhs->getType() == unionTy) {
                    builder->CreateStore(rhs, alloc, resolveVolatileVar(name));
                    return rhs;
                }
                int tag = findUnionVariantTag(unionName, (*asn)->value, rhs);

                if (tag == -1) { continue; }
                auto member = genericiseOrFindUnion(unionName).members[tag];
                bool isLiteral = member.type.find(':') != std::string::npos;

                std::string baseType = isLiteral ? member.type.substr(0, member.type.find(':')) : member.type;

                llvm::Type* rhsTy = rhs->getType();
                llvm::Type* memberTy = llvmTypeFor(baseType);

                if (rhsTy->getTypeID() != memberTy->getTypeID()) {
                    cg_error((*asn)->op_tok.pos, "union variant payload type mismatch");
                    return nullptr;
                }
                llvm::Value* unionVal = llvm::ConstantAggregateZero::get(unionTy);
                unionVal = builder->CreateInsertValue(unionVal, builder->getInt32(tag), 0);
                llvm::Value* dataPtr = storeAndGetPointer(rhs);
                unionVal = builder->CreateInsertValue(unionVal, dataPtr, 1);

                builder->CreateStore(unionVal, alloc, resolveVolatileVar(name));
                return unionVal;
            }
        }
        for (auto& [enumName, enumTy] : enumTypes) {
            if (destTy == enumTy) {
                llvm::Value* rhs = emitExpr((*asn)->value);
                if (!rhs) return nullptr;

                builder->CreateStore(rhs, alloc, resolveVolatileVar(name));
                return rhs;
            }
        }
        llvm::Value* oldVal = builder->CreateLoad(destTy, alloc, resolveVolatileVar(name), "assign_lhs_val");
        llvm::Value* rhsVal = nullptr;
        if (destTy->isPointerTy() && classTypes.count(getExpressionType((*asn)->value))) {
            rhsVal = emitLValue((*asn)->value);
        } else {
            rhsVal = emitExpr((*asn)->value);
        }
        std::string rhsType = getExpressionType((*asn)->value);
        if (!rhsVal) {
            cg_error(get_pos((*asn)->value), "failed to compile right-hand side of assignment");
            return nullptr;
        }
        llvm::Type* srcTy = rhsVal->getType();
        for (auto& [unionName, unionTy] : unionTypes) {
            if (fixMangling(rhsType) == unionName) {
                llvm::Value* dataPtr = builder->CreateExtractValue(rhsVal, 1);

                if (destTy->isPointerTy()) {
                    rhsVal = builder->CreateBitCast(dataPtr, destTy);
                } else {
                    llvm::Value* typedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));
                    rhsVal = builder->CreateLoad(destTy, typedPtr, resolveVolatileVar(name));
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
                } else if (auto structTy = llvm::dyn_cast<llvm::StructType>(destTy)) {
                    if (structTy->hasName()) {
                        std::string destClassName = structTy->getName().str();
                        std::string srcClassName = getExpressionType((*asn)->value);
                        if (classTypes.count(destClassName) && classTypes.count(srcClassName)) {
                            auto& srcInfo = userTypes.at(baseTypeName(srcClassName));
                            if (srcInfo.baseClassName == destClassName) {
                            } else {
                                cg_error((*asn)->op_tok.pos, "type mismatch in assignment");
                                return nullptr;
                            }
                        } else {
                            cg_error((*asn)->op_tok.pos, "type mismatch in assignment");
                            return nullptr;
                        }
                    } else {
                        cg_error((*asn)->op_tok.pos, "type mismatch in assignment");
                        return nullptr;
                    }
                } else if (srcTy->isDoubleTy() && destTy->isFloatTy()) {
                    rhsVal = builder->CreateFPTrunc(rhsVal, destTy, "d2f");
                    srcTy = destTy;
                } else if (srcTy->isIntegerTy() && destTy->isIntegerTy()) {
                    unsigned srcBits = srcTy->getIntegerBitWidth();
                    unsigned destBits = destTy->getIntegerBitWidth();
                    if ((srcBits == 1 || srcBits == 2) && (destBits != srcBits)) {
                        cg_error((*asn)->op_tok.pos, "cannot convert bool/qbool to other integer types");
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
                        cg_error((*asn)->op_tok.pos, "type mismatch in assignment");
                        return nullptr;
                    }
                } else if (srcTy->isPointerTy() && destTy->isPointerTy()) {
                    if (lhsTypeStr == "void*" || rhsType.ends_with("*") || lhsTypeStr == "@nullptr" || rhsType == "@nullptr") {
                    } else if (lhsTypeStr == rhsType) {
                    } else {
                        cg_error((*asn)->op_tok.pos, "type mismatch in assignment");
                        return nullptr;
                    }
                } else if (srcTy->isIntegerTy() && destTy->isPointerTy()) {
                    if ((*asn)->op_tok.type == TokenType::PLUS_EQ || (*asn)->op_tok.type == TokenType::MINUS_EQ) {
                        llvm::Value* offset = rhsVal;
                        if ((*asn)->op_tok.type == TokenType::MINUS_EQ) { offset = builder->CreateNeg(offset, "neg_offset"); }
                        std::string ptrType = getExpressionType((*asn)->target);
                        llvm::Type* elementTy;
                        if (ptrType == "string") {
                            elementTy = builder->getInt8Ty();
                        } else {
                            std::string baseType = ptrType;
                            baseType.pop_back();
                            elementTy = llvmTypeFor(baseType);
                        }
                        llvm::Value* newPtr = builder->CreateGEP(elementTy, oldVal, offset, "ptr_add");
                        builder->CreateStore(newPtr, alloc, resolveVolatileVar(name));
                        return newPtr;
                    }
                    cg_error((*asn)->op_tok.pos, "type mismatch in assignment");
                    return nullptr;
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
                        cg_error((*asn)->op_tok.pos, "cannot convert bool/qbool to other integer types");
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
                    cg_error((*asn)->op_tok.pos, "cannot narrow double to float (loses precision)");
                    return nullptr;
                } else if (srcTy->isFloatingPointTy() && destTy->isIntegerTy()) {
                    cg_error((*asn)->op_tok.pos, "cannot convert floating point to integer (loses "
                                                 "precision)");
                    return nullptr;
                } else if (srcTy->isPointerTy() && !destTy->isPointerTy()) {
                    if (lhsTypeStr.ends_with("&")) {
                        rhsVal = builder->CreateLoad(destTy, rhsVal, "ref_peel");
                        srcTy = rhsVal->getType();
                    }
                } else if (llvm::StructType* sTy = llvm::dyn_cast<llvm::StructType>(destTy);
                           sTy != nullptr && sTy->hasName() && classTypes.find(sTy->getName().str()) != classTypes.end()) {

                } else if (srcTy->isPointerTy() && destTy->isPointerTy()) {
                    if (lhsTypeStr == "void*" || rhsType.ends_with("*") || lhsTypeStr == "@nullptr" || rhsType == "@nullptr") {
                    } else if (lhsTypeStr == rhsType) {
                    } else {
                        cg_error((*asn)->op_tok.pos, "type mismatch in assignment");
                        return nullptr;
                    }
                } else {
                    cg_error((*asn)->op_tok.pos, "type mismatch in assignment");
                    return nullptr;
                }
            }
        }
        llvm::Value* newVal = nullptr;
        bool isFloatTy = destTy->isFloatingPointTy();
        if ((*asn)->op_tok.type == TokenType::PLUS_EQ && (lhsTypeStr == "char*" || lhsTypeStr == "string") &&
            std::unordered_set<std::string>({"string", "char*"}).contains(rhsType)) {
            llvm::Value* concatedString = callStringConcat(oldVal, rhsVal);
            builder->CreateStore(concatedString, alloc, resolveVolatileVar(name));
            return concatedString;
        }
        if ((*asn)->op_tok.type == TokenType::EQ) {
            if (auto structTy = llvm::dyn_cast<llvm::StructType>(destTy)) {
                if (structTy->hasName()) {
                    std::string className = structTy->getName().str();
                    if (genericiseOrFindClass(className)) {
                        if (auto* arrLit = std::get_if<ArrayLiteralNode*>(&(*asn)->value)) {
                            std::string lhsType = getExpressionType((*asn)->target, false);
                            if (userTypes.count(baseTypeName(lhsType))) {
                                llvm::Value* len = builder->getInt32((*arrLit)->elements.size());
                                rhsVal = decayArrayToPointer(rhsVal);
                                if (rhsVal == nullptr) { return nullptr; }
                                llvm::Function* opMethod = findMethodOverload(className, "operator[]=", {rhsVal, len});
                                if (opMethod) {
                                    llvm::Value* lhsAlloc = emitLValue((*asn)->target);
                                    return emitMethodCall(opMethod, lhsAlloc, {rhsVal, len}, "operator[]=");
                                }
                                cg_error((*asn)->op_tok.pos, "class " + className + " has no valid matching operator[]=");
                                return nullptr;
                            }
                        }
                        std::vector<llvm::Value*> args = {rhsVal};
                        llvm::Function* opMethod = findMethodOverload(className, "operator=", args);
                        if (opMethod) {
                            llvm::Type* expectedRhsTy = opMethod->getFunctionType()->getParamType(1);
                            if (expectedRhsTy->isStructTy() && rhsVal->getType()->isPointerTy()) {
                                rhsVal = builder->CreateLoad(expectedRhsTy, rhsVal, "op_rhs_load");
                            }
                            std::vector<llvm::Value*> allArgs = {alloc, rhsVal};
                            if (insideTry()) {
                                auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
                                llvm::InvokeInst* invk = builder->CreateInvoke(opMethod, contBB, currentLandingPad(), allArgs);
                                builder->SetInsertPoint(contBB);
                                return invk;
                            }
                            llvm::Value* callResult = builder->CreateCall(opMethod, allArgs, "op_assign_tmp");
                            return callResult;
                        }
                    }
                    std::string destClassName = structTy->getName().str();
                    std::string srcClassName = getExpressionType((*asn)->value);
                    if (classTypes.count(destClassName) && classTypes.count(srcClassName)) {
                        auto& srcInfo = userTypes.at(baseTypeName(srcClassName));
                        if (srcInfo.baseClassName == destClassName) {
                            builder->CreateStore(newVal, alloc);
                            auto vtableIt = vtables.find(srcClassName);
                            if (vtableIt != vtables.end()) {
                                llvm::Value* vptrField = builder->CreateStructGEP(structTy, alloc, 0, "vptr_fix");
                                builder->CreateStore(vtableIt->second, vptrField);
                            }
                            return newVal;
                        }
                    }
                }
            }
        } else {
            if (auto structTy = llvm::dyn_cast<llvm::StructType>(destTy)) {
                if (structTy->hasName()) {
                    std::string className = structTy->getName().str();
                    if (genericiseOrFindClass(className)) {
                        std::vector<llvm::Value*> args = {rhsVal};
                        llvm::Function* opMethod = findMethodOverload(className, getCombinationalOperatorMethodName((*asn)->op_tok.type), args);
                        if (opMethod) {
                            llvm::Type* expectedRhsTy = opMethod->getFunctionType()->getParamType(1);
                            if (expectedRhsTy->isStructTy() && rhsVal->getType()->isPointerTy()) {
                                rhsVal = builder->CreateLoad(expectedRhsTy, rhsVal, "op_rhs_load");
                            }
                            std::vector<llvm::Value*> allArgs = {alloc, rhsVal};
                            if (insideTry()) {
                                auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
                                llvm::InvokeInst* invk = builder->CreateInvoke(opMethod, contBB, currentLandingPad(), allArgs);
                                builder->SetInsertPoint(contBB);
                                return invk;
                            }
                            llvm::Value* callResult = builder->CreateCall(opMethod, allArgs, "op_assign_tmp");
                            return callResult;
                        }
                    }
                    cg_error(get_pos(*asn), "no valid overload to " + getCombinationalOperatorMethodName((*asn)->op_tok.type) + " found");
                    struct Candidate {
                        int score;
                        ClassMethodInfo* method;
                    };
                    std::vector<Candidate> candidates;
                    for (auto& method : userTypes.at(baseTypeName(baseTypeName(className))).classMethods) {
                        if (method.is_constructor || (method.name_tok.value != getCombinationalOperatorMethodName((*asn)->op_tok.type))) continue;
                        int score = 0;
                        size_t argCount = 1;
                        size_t paramCount = 1;
                        if (srcTy == destTy) {
                            score += 3;
                        } else if ((srcTy->isIntegerTy() || srcTy->isFloatTy() || srcTy->isDoubleTy()) &&
                                   (destTy->isIntegerTy() || destTy->isFloatTy() || destTy->isDoubleTy())) {
                            score += 1;
                        } else if (srcTy->isPointerTy() && destTy->isPointerTy()) {
                            score += 1;
                        } else {
                            score -= 3;
                        }
                        candidates.push_back({score, &method});
                    }
                    if (candidates.empty()) {
                        std::vector<std::pair<int, std::string>> suggestions;
                        for (auto& method : userTypes[baseTypeName(className)].classMethods) {
                            int distance = levenshteinDistance(getCombinationalOperatorMethodName((*asn)->op_tok.type), method.name_tok.value);
                            if (distance <= 2) { suggestions.push_back({distance, method.name_tok.value}); }
                        }
                        std::sort(suggestions.begin(), suggestions.end());
                        if (!suggestions.empty()) {
                            std::string note = "similar methods:";
                            for (auto& [distance, name] : suggestions) { note += "\n  - `" + name + "`"; }
                            cg_note(get_pos(*acc), note);
                        }
                        return nullptr;
                    }
                    std::sort(candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b) { return a.score > b.score; });
                    if (candidates[0].score > 0) { cg_note(get_pos(*acc), "closest matching overload: " + candidates[0].method->print()); }
                    if (candidates.size() <= 5) {
                        std::string note = "available overloads:";
                        for (auto& candidate : candidates) { note += "\n  - " + candidate.method->print(); }
                        cg_note(get_pos(*acc), note);
                    } else {
                        std::string note = "other overloads:";
                        size_t shown = 0;
                        for (auto& candidate : candidates) {
                            if (shown >= 3) break;
                            note += "\n  - " + candidate.method->print();
                            shown++;
                        }
                        cg_note(get_pos(*acc), note);
                    }
                }
            }
        }
        switch ((*asn)->op_tok.type) {
        case TokenType::EQ: newVal = rhsVal; break;
        case TokenType::PLUS_EQ: newVal = isFloatTy ? builder->CreateFAdd(oldVal, rhsVal, "fadd") : builder->CreateAdd(oldVal, rhsVal, "add"); break;
        case TokenType::MINUS_EQ: newVal = isFloatTy ? builder->CreateFSub(oldVal, rhsVal, "fsub") : builder->CreateSub(oldVal, rhsVal, "sub"); break;
        case TokenType::MUL_EQ: newVal = isFloatTy ? builder->CreateFMul(oldVal, rhsVal, "fmul") : builder->CreateMul(oldVal, rhsVal, "mul"); break;
        case TokenType::DIV_EQ: newVal = isFloatTy ? builder->CreateFDiv(oldVal, rhsVal, "fdiv") : builder->CreateSDiv(oldVal, rhsVal, "sdiv"); break;
        case TokenType::MOD_EQ: newVal = isFloatTy ? builder->CreateFRem(oldVal, rhsVal, "frem") : builder->CreateSRem(oldVal, rhsVal, "srem"); break;
        case TokenType::RSH_EQ: newVal = builder->CreateAShr(oldVal, rhsVal, "ashr"); break;
        case TokenType::LSH_EQ: newVal = builder->CreateShl(oldVal, rhsVal, "shl"); break;
        case TokenType::LRSH_EQ: newVal = builder->CreateLShr(oldVal, rhsVal, "lshr"); break;
        case TokenType::BIT_A_EQ: newVal = builder->CreateAnd(oldVal, rhsVal, "and"); break;
        case TokenType::BIT_O_EQ: newVal = builder->CreateOr(oldVal, rhsVal, "or"); break;
        case TokenType::BIT_X_EQ: newVal = builder->CreateXor(oldVal, rhsVal, "xor"); break;
        case TokenType::LROT_EQ: newVal = builder->CreateIntrinsic(llvm::Intrinsic::fshl, {oldVal->getType()}, {oldVal, oldVal, rhsVal}); break;
        case TokenType::RROT_EQ: newVal = builder->CreateIntrinsic(llvm::Intrinsic::fshr, {oldVal->getType()}, {oldVal, oldVal, rhsVal}); break;
        default: cg_error((*asn)->op_tok.pos, "unsupported assignment operator."); return nullptr;
        }
        builder->CreateStore(newVal, alloc, resolveVolatileVar(name));
        return newVal;
    } else if (auto unary = std::get_if<UnaryOpNode*>(&node)) {
        TokenType op = (*unary)->op_tok.type;

        llvm::Value* operand = emitExpr((*unary)->node);
        if (!operand) return nullptr;
        llvm::Type* operandTy = operand->getType();
        for (auto& [unionName, unionTy] : unionTypes) {
            if (fixMangling(getExpressionType((*unary)->node)) == unionName) {
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
                            if (insideTry()) {
                                auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
                                llvm::InvokeInst* invk = builder->CreateInvoke(opMethod, contBB, currentLandingPad(), allArgs);
                                builder->SetInsertPoint(contBB);
                                return invk;
                            }
                            return builder->CreateCall(opMethod, allArgs, "unary_op_result");
                        }
                    }
                }
            }
        }
        if ((*unary)->op_tok.type == TokenType::NOT) {
            if (operand->getType() == builder->getInt1Ty()) {
                return builder->CreateNot(operand, "not");
            } else if (operand->getType()->isPointerTy()) {
                llvm::Value* NullPtr = llvm::ConstantPointerNull::get(llvm::cast<llvm::PointerType>(operand->getType()));
                return builder->CreateICmpEQ(operand, NullPtr, "isnull");
            } else {
                cg_error((*unary)->op_tok.pos, "! requires bool operand");
                return nullptr;
            }
        }
        if ((*unary)->op_tok.type == TokenType::BITWISE_NOT) {
            llvm::Type* ty = operand->getType();
            if (ty->isFloatingPointTy() || ty->isPointerTy()) {
                cg_error((*unary)->op_tok.pos, "cannot perform bitwise NOT on non-integer type");
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
            bool isPostfix = (*unary)->is_postfix;
            llvm::Value* lhsVal = operand;
            llvm::Value* lhs = emitLValue((*unary)->node);
            llvm::Type* type = lhsVal->getType();
            std::string ptrTy = getExpressionType((*unary)->node);
            std::string name = std::get_if<VarAccessNode*>(&(*unary)->node) ? (*(std::get_if<VarAccessNode*>(&(*unary)->node)))->var_name_tok.value
                                                                            : "";
            llvm::Value* oldVal = builder->CreateLoad(lhsVal->getType(), lhs, resolveVolatileVar(name), "inc_deref");
            if (lhsVal->getType()->isPointerTy()) {
                if (ptrTy == "string") {
                    ptrTy = "char";
                } else {
                    ptrTy.pop_back();
                }
                llvm::Value* newVal;
                llvm::Value* one = llvm::ConstantInt::get(builder->getIntNTy(getPtrSize()), 1);
                if ((*unary)->op_tok.type == TokenType::INCREMENT) {
                    newVal = builder->CreateGEP(llvmTypeFor(ptrTy), oldVal, one, "ptr_inc");
                } else {
                    llvm::Value* negOne = llvm::ConstantInt::get(builder->getIntNTy(getPtrSize()), -1, true);
                    newVal = builder->CreateGEP(llvmTypeFor(ptrTy), oldVal, negOne, "ptr_dec");
                }
                builder->CreateStore(newVal, lhs, resolveVolatileVar(name));
                return isPostfix ? oldVal : newVal;
            }
            if (!lhsVal->getType()->isIntegerTy()) {
                cg_error((*unary)->op_tok.pos, "++/-- only valid on int-like");
                return nullptr;
            }
            llvm::Value* one = llvm::ConstantInt::get(lhsVal->getType(), 1);
            llvm::Value* newVal;
            if ((*unary)->op_tok.type == TokenType::INCREMENT) {
                newVal = builder->CreateAdd(oldVal, one, "inc");
            } else {
                newVal = builder->CreateSub(oldVal, one, "dec");
            }

            builder->CreateStore(newVal, lhs, resolveVolatileVar(name));
            return isPostfix ? oldVal : newVal;
        }
        if ((*unary)->op_tok.type == TokenType::AMPERSAND) { return emitLValue((*unary)->node); }
        if ((*unary)->op_tok.type == TokenType::MUL) {
            std::string name = std::get_if<VarAccessNode*>(&(*unary)->node) ? (*(std::get_if<VarAccessNode*>(&(*unary)->node)))->var_name_tok.value
                                                                            : "";
            llvm::Value* val = operand;
            std::string type = getExpressionType((*unary)->node);
            if (!type.ends_with("*") && !type.ends_with("[]") && type != "string") {
                cg_error((*unary)->op_tok.pos, "you can only dereference pointer types, found: " + type);
                return nullptr;
            }
            if (type == "void*") {
                cg_error((*unary)->op_tok.pos, "you canot dereference void*");
                return nullptr;
            }
            if (type.ends_with("]")) type.pop_back();
            std::string baseType = type == "string" ? "char" : type.substr(0, type.size() - 1);
            if (classTypes.count(baseType)) { return val; }
            return builder->CreateLoad(llvmTypeFor(baseType), val, resolveVolatileVar(name), "deref");
        }
        if ((*unary)->op_tok.type == TokenType::SIZEOF) {
            const llvm::DataLayout& dl = module->getDataLayout();
            uint64_t size;
            if (StringNode* val = std::get_if<StringNode>(&(*unary)->node)) {
                llvm::Type* ty = llvmTypeFor(val->tok.value);
                if (ty) {
                    size = dl.getTypeAllocSize(ty);
                } else {
                    size = dl.getTypeAllocSize(operand->getType());
                }
            } else if (TypeValueNode* t = std::get_if<TypeValueNode>(&(*unary)->node)) {
                llvm::Type* ty = llvmTypeFor(t->tok.value);
                if (ty) {
                    size = dl.getTypeAllocSize(ty);
                } else {
                    cg_error(t->getPos(), "unknown type `" + t->tok.value + "`");
                    return nullptr;
                }
            } else {
                size = dl.getTypeAllocSize(operand->getType());
            }
            unsigned ptrBitWidth = dl.getPointerSizeInBits();
            llvm::IntegerType* addrType = llvm::IntegerType::get(context, ptrBitWidth);
            return llvm::ConstantInt::get(addrType, size);
        }
        if ((*unary)->op_tok.type == TokenType::THROW) {
            llvm::Value* type = getStringConstant(getExpressionType((*unary)->node));
            llvm::Value* value = emitExpr((*unary)->node);
            llvm::Value* storage = builder->CreateAlloca(value->getType());
            builder->CreateStore(value, storage);
            value = storage;
            llvm::Function* createFn = module->getFunction("__qc_create_exception");
            llvm::Value* exception = builder->CreateCall(createFn, {type, value}, "exception");
            llvm::Function* throwFn = module->getFunction("__qc_throw");
            builder->CreateCall(throwFn, {exception});
            builder->CreateUnreachable();
            return nullptr;
        }
    } else if (auto fnPtr = std::get_if<FuncDefNode*>(&node)) {
        llvm::Function* f = emitFuncDef(*(*fnPtr));
        return f;
    } else if (auto mapLit = std::get_if<MapLiteralNode*>(&node)) {
        if ((*mapLit)->struct_type.empty()) {
            cg_error(get_pos(*mapLit), "struct literals must have a struct type");
            return nullptr;
        }
        llvm::StructType* structTy = genericiseOrFindStruct((*mapLit)->struct_type);
        if (!structTy) {
            cg_error(get_pos(*mapLit), "unknown struct type '" + (*mapLit)->struct_type + "'");
            std::vector<std::pair<int, std::string>> matches;
            if ((*mapLit)->struct_type.size() >= 3) {
                for (auto& [vname, strct] : userTypes) {
                    if (strct.kind != UserTypeKind::Struct) continue;
                    int distance = levenshteinDistance((*mapLit)->struct_type, vname);
                    if (distance <= 2) { matches.push_back({distance, vname}); }
                }
            }
            std::sort(matches.begin(), matches.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
            if (!matches.empty()) {
                std::string note = "did you mean ";
                size_t count = std::min<size_t>(3, matches.size());
                for (size_t i = 0; i < count; i++) {
                    if (i != 0) note += ", ";
                    note += "`" + buildMangledName(baseTypeName(matches[i].second), genericParamsFromName((*mapLit)->struct_type), true) + "`";
                }
                note += "?";
                cg_note(get_pos(*mapLit), note);
            }
            return nullptr;
        }
        llvm::Value* structVal = llvm::ConstantAggregateZero::get(structTy);
        auto structInfo = userTypes.find(baseTypeName((*mapLit)->struct_type))->second;
        for (auto& [keyNode, valueNode] : (*mapLit)->pairs) {
            std::string fieldName;
            if (auto key = std::get_if<VarAccessNode*>(&keyNode)) {
                fieldName = (*key)->var_name_tok.value;
            } else if (auto key = std::get_if<StringNode>(&keyNode)) {
                fieldName = key->tok.value;
            } else {
                cg_error((*mapLit)->pos, "struct field name must be an identifier");
                return nullptr;
            }
            int fieldIndex = -1;
            for (size_t i = 0; i < structInfo.fields.size(); i++) {
                if (structInfo.fields[i].name == fieldName) {
                    fieldIndex = i;
                    break;
                }
            }
            if (fieldIndex == -1) {
                cg_error((*mapLit)->pos, "unknown field '" + fieldName + "' in struct " + (*mapLit)->struct_type);
                return nullptr;
            }
            llvm::Value* fieldValue = emitExpr(valueNode);
            if (!fieldValue) return nullptr;
            structVal = builder->CreateInsertValue(structVal, fieldValue, fieldIndex);
        }
        return structVal;
    } else if (auto arrLit = std::get_if<ArrayLiteralNode*>(&node)) {
        if (!(*arrLit)->type.empty() && std::holds_alternative<std::monostate>((*arrLit)->length)) {
            llvm::StructType* structTy = genericiseOrFindStruct((*arrLit)->type);
            if (!structTy) {
                cg_error(get_pos(*arrLit), "unknown struct type '" + (*arrLit)->type + "'");
                std::vector<std::pair<int, std::string>> matches;
                if ((*arrLit)->type.size() >= 3) {
                    for (auto& [vname, strct] : userTypes) {
                        if (strct.kind != UserTypeKind::Struct) continue;
                        int distance = levenshteinDistance((*arrLit)->type, vname);
                        if (distance <= 2) { matches.push_back({distance, vname}); }
                    }
                }
                std::sort(matches.begin(), matches.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
                if (!matches.empty()) {
                    std::string note = "did you mean ";
                    size_t count = std::min<size_t>(3, matches.size());
                    for (size_t i = 0; i < count; i++) {
                        if (i != 0) note += ", ";
                        note += "`" + buildMangledName(baseTypeName(matches[i].second), genericParamsFromName((*arrLit)->type), true) + "`";
                    }
                    note += "?";
                    cg_note(get_pos(*arrLit), note);
                }
                return nullptr;
            }
            llvm::Value* structVal = llvm::ConstantAggregateZero::get(structTy);
            auto structInfo = userTypes.find(baseTypeName((*arrLit)->type))->second;
            for (size_t i = 0; i < (*arrLit)->elements.size(); i++) {
                std::string fieldType = structInfo.fields[i].type;
                auto fieldTypeIt = userTypes.find(fieldType);
                llvm::Value* val;
                if (fieldTypeIt != userTypes.end() && fieldTypeIt->second.kind == UserTypeKind::Struct) {
                    if (auto nestedArrLit = std::get_if<ArrayLiteralNode*>(&(*arrLit)->elements[i])) {
                        llvm::StructType* nestedStructTy = genericiseOrFindStruct(fieldType);
                        llvm::Value* nestedStruct = llvm::ConstantAggregateZero::get(nestedStructTy);
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
            return structVal;
        }
        if ((*arrLit)->elements.empty()) {
            llvm::Type* elemType = llvmTypeFor((*arrLit)->type);
            if (elemType == nullptr) {
                cg_error(get_pos(*arrLit), "empty array literals without an element type are not allowed");
                cg_note(get_pos(*arrLit),
                        "for a empty literal of integers, you can do `[int, 0]`, or for a array of 10 ints, you can do `[int, 10]`");
                return nullptr;
            }
            llvm::Value* length = emitExpr((*arrLit)->length);
            llvm::ConstantInt* ci = llvm::dyn_cast<llvm::ConstantInt>(length);
            if (ci == nullptr) {
                cg_error(get_pos(*arrLit), "empty array literal length must be a constant compile time int");
                return nullptr;
            }
            llvm::ArrayType* arrTy = llvm::ArrayType::get(elemType, ci->getZExtValue());
            return llvm::ConstantAggregateZero::get(arrTy);
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
            if (llvm::Value* v = resolveVariable(baseTypeName(funcName))) {
                if (std::string className = resolveVarType(baseTypeName(funcName)); !className.empty()) {
                    if (classTypes.find(className) != classTypes.end()) {
                        if (funcName.find("<") != std::string::npos)
                            if (llvm::Value* val = tryHandleSpecialized(
                                    className, buildMangledName("operator()", genericParamsFromName(funcName)),
                                    methodCallFromCall(*callPtr, buildMangledName("operator()", genericParamsFromName(funcName))), v))
                                return val;
                        if (auto methodIt = std::find_if(
                                userTypes[baseTypeName(className)].classMethods.begin(), userTypes[baseTypeName(className)].classMethods.end(),
                                [&](const ClassMethodInfo& method) { return method.name_tok.value == "operator()" && method.generics.empty(); });
                            methodIt != userTypes[baseTypeName(className)].classMethods.end()) {
                            size_t methodIdx = std::distance(userTypes[baseTypeName(className)].classMethods.begin(), methodIt);
                            auto& info = userTypes[baseTypeName(className)].classMethods[methodIdx];
                            MethodCallNode* n = methodCallFromCall(*callPtr, "operator()");
                            auto args = prepareArgs(&info, n->args);
                            delete n;
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
                            llvm::Function* opMethod = findMethodOverload(className, "operator()", args);
                            if (!opMethod) {
                                cg_error(get_pos(*callPtr), "no matching operator() overload for class " + className);
                                return nullptr;
                            }
                            return emitMethodCall(opMethod, v, args, "operator()");
                        }
                        cg_error(get_pos(*callPtr), "no matching operator( ) for class " + className);
                        return nullptr;
                    }
                }
            }
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
            auto funcDefIt = functionDefs.find(baseTypeName(funcName));
            if (funcDefIt != functionDefs.end()) {
                FuncDefNode* funcDef = funcDefIt->second;
                if (!funcDef->generics.empty()) {
                    std::vector<llvm::Value*> argValues;
                    auto paramIt = funcDef->params.begin();
                    bool hasSpread = false;
                    for (auto& argNode : call.arg_nodes) {
                        if (std::holds_alternative<SpreadNode*>(argNode)) { hasSpread = true; }
                        std::string ptype = (paramIt != funcDef->params.end()) ? paramIt->type.value : "...";
                        llvm::Value* argVal;
                        if (ptype.ends_with("&")) {
                            argVal = emitLValue(argNode);
                        } else {
                            argVal = emitExpr(argNode);
                        }
                        argValues.push_back(argVal);
                        if (paramIt != funcDef->params.end()) ++paramIt;
                    }
                    if (hasSpread) {
                        cg_error(get_pos(&call), "spread is no longer allowed in function calls.");
                        return nullptr;
                    }
                    funcName = fixMangling(funcName);
                    if (specializedFunctions.find(funcName) == specializedFunctions.end()) {
                        llvm::Function* specializedFn = generateSpecializedFunction(funcDef, funcName);
                        if (!specializedFn) return nullptr;
                        specializedFunctions[funcName] = specializedFn;
                    }
                    llvm::Function* fn = specializedFunctions[funcName];
                    if (funcDef->params.size() > 0 && funcDef->params.back().type.value == "...") {
                        size_t fixedCount = funcDef->params.size() - 1;
                        std::vector<llvm::Value*> varVals(argValues.begin() + fixedCount, argValues.end());
                        argValues.resize(fixedCount);
                        argValues.push_back(packVariadicArgs(varVals));
                    }
                    if (insideTry()) {
                        auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
                        llvm::InvokeInst* invoke = builder->CreateInvoke(fn, contBB, currentLandingPad(), argValues);
                        builder->SetInsertPoint(contBB);
                        return invoke;
                    } else {
                        return builder->CreateCall(fn, argValues);
                    }
                }
            }
            std::string saved_name = funcName;
            resolvedName = resolveTypeName(funcName, false);
            if (!currentGenericTypeStrings.empty()) {
                std::string substituted = substituteGenerics(resolvedName);
                if (substituted != resolvedName) resolvedName = substituted;
            }
            saved_name = resolvedName;
            auto classIt = userTypes.find(baseTypeName(resolvedName));

            if (classIt != userTypes.end() && classIt->second.kind == UserTypeKind::Class) {
                llvm::StructType* classTy = genericiseOrFindClass(resolvedName);
                if (classTy == nullptr) {
                    if (saved_name.find('<') != std::string::npos) {
                        size_t lt = saved_name.find('<');
                        std::string inner = saved_name.substr(lt + 1, saved_name.size() - lt - 2);
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
                        std::string fullName = buildMangledName(resolvedName, genericParams);
                        classTy = generateGenericClass(resolvedName, classIt->second, genericParams);
                        resolvedName = fullName;
                        if (classTy == nullptr) {
                            cg_error(get_pos(*varAccess), "failed to generate generic subset for class " + resolvedName);
                            return nullptr;
                        }
                    } else {
                        cg_error(get_pos(*callPtr), "class '" + resolvedName + "' has no generated type");
                        return nullptr;
                    }
                }
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
                        cg_error((*varAccess)->var_name_tok.pos, "no matching constructor for " + resolvedName);
                        addConstructorNotes(resolvedName, ctorArgs, get_pos(*varAccess));
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
                    if (insideTry()) {
                        auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
                        builder->CreateInvoke(ctor, contBB, currentLandingPad(), allArgs);
                        builder->SetInsertPoint(contBB);
                    } else {
                        builder->CreateCall(ctor, allArgs);
                    }
                    auto vtableIt = vtables.find(resolvedName);
                    if (vtableIt != vtables.end()) {
                        llvm::Value* vptrField = builder->CreateStructGEP(classTy, temp, 0, "vptr_field");
                        builder->CreateStore(vtableIt->second, vptrField);
                    }
                } else {
                    builder->CreateStore(llvm::Constant::getNullValue(classTy), temp);
                    auto vtableIt = vtables.find(resolvedName);
                    if (vtableIt != vtables.end()) {
                        llvm::Value* vptrField = builder->CreateStructGEP(classTy, temp, 0, "vptr_field");
                        builder->CreateStore(vtableIt->second, vptrField);
                    }
                }
                return builder->CreateLoad(classTy, temp, resolvedName + "_inst");
            }
            static const std::unordered_map<std::string, std::string> builtins = {{"`time", "qc_time"},
                                                                                  {"`seed", "qc_seed"},
                                                                                  {"`random", "qc_random_int"},
                                                                                  {"`len", "qc_len"},
                                                                                  {"`to_lower", "qc_to_lower"},
                                                                                  {"`to_upper", "qc_to_upper"},
                                                                                  {"`substring", "qc_substring"},
                                                                                  {"`contains", "qc_contains"},
                                                                                  {"`startswith", "qc_startswith"},
                                                                                  {"`endswith", "qc_endswith"},
                                                                                  {"`trim", "qc_trim"},
                                                                                  {"`replace", "qc_replace"},
                                                                                  {"`to_int", "qc_to_int_from_string"},
                                                                                  {"`to_float", "qc_to_float_from_string"},
                                                                                  {"`to_double", "qc_to_double_from_string"},
                                                                                  {"`to_char", "qc_to_char_from_string"},
                                                                                  {"`to_bool", "qc_to_bool_from_string"},
                                                                                  {"`to_string", "qc_to_string_int"},
                                                                                  {"`to_byte", "qc_to_byte_from_string"},
                                                                                  {"`to_nibble", "qc_to_nibble_from_string"},
                                                                                  {"`to_addr_t", "qc_to_addr_t_from_string"},
                                                                                  {"`to_qbool", "qc_to_qbool_from_string"},
                                                                                  {"`to_long_int", "qc_to_long_int_from_string"},
                                                                                  {"`to_short_int", "qc_to_short_int_from_string"},
                                                                                  {"`qout", ""},
                                                                                  {"`typeof", ""},
                                                                                  {"`open", "qc_open"},
                                                                                  {"`close", "qc_close"},
                                                                                  {"`read", "qc_read"},
                                                                                  {"`write", "qc_write"},
                                                                                  {"`malloc", "qc_malloc"},
                                                                                  {"`calloc", "qc_calloc"},
                                                                                  {"`free", "qc_free"},
                                                                                  {"`realloc", "qc_realloc"},
                                                                                  {"`mapped_ptr", ""},
                                                                                  {"`ternary", ""},
                                                                                  {"`to_address", ""},
                                                                                  {"`inline", ""},
                                                                                  {"`flush", "qc_flush"},
                                                                                  {"`next", ""},
                                                                                  {"`is_empty", ""}};
            auto it = builtins.find(funcName);

            if (it != builtins.end()) {
                std::string runtimeName = it->second;

                if (funcName == "`typeof" && !call.arg_nodes.empty()) {
                    AnyNode& argNode = call.arg_nodes.front();
                    llvm::Value* arg = emitExpr(argNode);
                    if (!arg) return nullptr;
                    llvm::Type* argTy = arg->getType();
                    for (auto& [unionName, unionTy] : unionTypes) {
                        if (argTy == unionTy) {
                            llvm::Value* tag = builder->CreateExtractValue(arg, 0, "typeof_tag");
                            auto type = genericiseOrFindUnion(unionName);
                            auto& members = type.members;
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
                    for (auto& [enumName, enumTy] : enumTypes) {
                        if (argTy == enumTy) {
                            llvm::Value* tag = builder->CreateExtractValue(arg, 0);
                            auto& entries = userTypes.at(baseTypeName(enumName)).enumEntries;
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
                    }
                    std::string typeName = "unknown";
                    if (argTy->isIntegerTy(32))
                        typeName = "int";
                    else if (argTy->isIntegerTy(4))
                        typeName = "nibble";
                    else if (argTy->isIntegerTy(64))
                        typeName = "addr_t";
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
                if (funcName == "`random" && !call.arg_nodes.empty()) {
                    if (call.arg_nodes.size() == 1)
                        runtimeName = "qc_random_int";
                    else if (call.arg_nodes.size() == 2)
                        runtimeName = "qc_random_range";
                } else if (funcName == "`qout") { // Ṱ̵̺̙̙͔̯̣͓̼̈́͜h̶̳͖̝̰͍̮͆̅̊e̶̡̧̮͍̘̘͍̮͎͎̺̗̦͕̾͗͐̽͑̔̅́̑̌̕ ̶̥̮̪͙̎͛̐͑̔̉́̂̂̐́̽̔̔͂̃d̴̛̪̦̞́́̎͊̌̈̍̓̓̔̑͑̒͘͝e̶͎̤̠̞̞͖̊ṽ̴̡͖̫̩̣̳̖̞̯̪͇̰̆͑͐͐̀̿͐̍̑̕͘̕͝͝ͅͅͅí̵̜̬͍̖̒͑̎͗l̸̛͍̰̜̞̩̜̘͈̯̬̇̀̋̈͐̔̿̓̅͌̉̅͂̌͘͜͝ ̷̡̣̰͙̰̪͈̪̣̺̺̤̦̰͌̊̀̀̑͑̅̈́ş̶̛̳̟̫͇̠͉͍̺̣̲̬̻̰͍̙̋̂͗̕͠ͅę̸̹̹̈́͒̐̃̋̓͐̓͆̉̀̊̀̏̿͘é̷͖͎̹̉́̈́͠͠͝s̸̡̢̢̩͍̹̼͈͕̘̖͋̋̃̓͗͆͌̕͠ͅͅͅ ̴̛̮͉̣̈́̒͋͐̿̾̐̽̚ḩ̶̨̧̺͉̹̩̙̫͇̰̫̯̬͐́̑͜i̶̠͖̠̟̻̭̫̙̳̪͆̄̿̈́̾̊̈́̒͑͊̆̋̃̎̿̂͗ş̴̥̤̜̦̗͍̟̈́̽̑̏ ̶̡̛̫̥̝̰̣̟͇͔̤̱̯͉̱̩̋̈̈́͐̓̑̋̎͝͝ͅö̷̡̝̣́̎̎͝ẘ̶̢̡̨̡̭̞̯̘̦̟̳̮̫͎̑͂̇̀͆̋̐̃̒́̏̓͒̅͜͝͝n̵̳͎̣̬̪̝̩͒͊̓̾̓̄̃̂͗̉͆̒̋̚͜͜͝ ̴͔̫̂̏ͅͅį̷̡̤̼͈̗̦̣̘̮̠̣͎̬̰̍͗ṉ̸̨̯̱̦͕͐̉̀͌͑̀͐̽̕͜
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
                            {builder->getIntNTy(getPtrSize()), builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt1Ty()}, false);
                        fmtInt = llvm::Function::Create(fmtIntFnTy, llvm::Function::ExternalLinkage, "qc_fmt_int", module);
                    }
                    llvm::Function* fmtUInt = module->getFunction("qc_fmt_unsigned_int");
                    if (!fmtUInt) {
                        llvm::FunctionType* fmtUIntFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0),
                            {builder->getIntNTy(getPtrSize()), builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt1Ty()}, false);
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
                            llvm::PointerType::get(context, 0), {builder->getIntNTy(getPtrSize()), builder->getInt32Ty(), builder->getInt1Ty()},
                            false);
                        fmtOctal = llvm::Function::Create(fmtOctalFnTy, llvm::Function::ExternalLinkage, "qc_fmt_octal", module);
                    }
                    llvm::Function* fmtHex = module->getFunction("qc_fmt_hex");
                    if (!fmtHex) {
                        llvm::FunctionType* fmtHexFnTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0), {builder->getIntNTy(getPtrSize()), builder->getInt32Ty(), builder->getInt1Ty()},
                            false);
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
                            llvm::Value* itgVal = derefIfReference(emitExpr(goodArgs[current_arg]), goodArgs[current_arg]);
                            llvm::Value* bigIntSigned = nullptr;
                            if (!itgVal || !itgVal->getType()->isIntegerTy()) {
                                cg_error((*varAccess)->var_name_tok.pos, "%i formater takes an integer");
                                return nullptr;
                            }
                            llvm::Type* i64Ty = builder->getIntNTy(getPtrSize());
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
                            llvm::Value* itgVal = derefIfReference(emitExpr(goodArgs[current_arg]), goodArgs[current_arg]);
                            llvm::Value* bigIntSigned = nullptr;
                            if (!itgVal || !itgVal->getType()->isIntegerTy()) {
                                cg_error((*varAccess)->var_name_tok.pos, "%u formater takes an int-like (int, "
                                                                         "long int, short "
                                                                         "int, addr_t, nibble, byte)");
                                return nullptr;
                            }
                            llvm::Type* i64Ty = builder->getIntNTy(getPtrSize());
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
                            llvm::Value* stVal = derefIfReference(emitExpr(goodArgs[current_arg]), goodArgs[current_arg]);
                            if (!stVal) {
                                cg_error((*varAccess)->var_name_tok.pos, "failed to resolve argument for "
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
                            llvm::Value* floatVal = derefIfReference(emitExpr(goodArgs[current_arg]), goodArgs[current_arg]);
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
                            llvm::Value* doubVal = derefIfReference(emitExpr(goodArgs[current_arg]), goodArgs[current_arg]);
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
                            llvm::Value* cVal = derefIfReference(emitExpr(goodArgs[current_arg]), goodArgs[current_arg]);
                            if (i >= fmtString.size()) {
                            } else if (fmtString[i + 1] == 's') {
                                i++;
                                llvm::Type* ty = cVal->getType();
                                if (auto structTy = llvm::dyn_cast<llvm::StructType>(cVal->getType())) {
                                    if (structTy->hasName()) {
                                        std::string className = structTy->getName().str();

                                        if (classTypes.find(className) != classTypes.end()) {
                                            auto [reprMethod, ownerClass] = findMethodInHierarchy(className, "_repr");

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
                            llvm::Value* boolVal = derefIfReference(emitExpr(goodArgs[current_arg]), goodArgs[current_arg]);
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
                            llvm::Value* qboolVal = derefIfReference(emitExpr(goodArgs[current_arg]), goodArgs[current_arg]);
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
                            llvm::Value* itgVal = derefIfReference(emitExpr(goodArgs[current_arg]), goodArgs[current_arg]);
                            llvm::Value* bigIntUnsigned;
                            if (!itgVal || !itgVal->getType()->isIntegerTy()) {
                                cg_error((*varAccess)->var_name_tok.pos, "x formater takes a int: " + funcName);
                                return nullptr;
                            }
                            llvm::Type* i64Ty = builder->getIntNTy(getPtrSize());
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
                            llvm::Value* itgVal = derefIfReference(emitExpr(goodArgs[current_arg]), goodArgs[current_arg]);
                            if (!itgVal || !itgVal->getType()->isIntegerTy()) {
                                cg_error((*varAccess)->var_name_tok.pos, "o formater takes a int: " + funcName);
                                return nullptr;
                            }
                            llvm::Type* i64Ty = builder->getIntNTy(getPtrSize());
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
                            llvm::Value* decimalVal = derefIfReference(emitExpr(goodArgs[current_arg]), goodArgs[current_arg]);
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

                            llvm::Value* val = derefIfReference(emitExpr(goodArgs[current_arg]), goodArgs[current_arg]);

                            if (!val) {
                                cg_error((*varAccess)->var_name_tok.pos,
                                         "failed to evaluate argument " + std::to_string(current_arg) + ": " + funcName);
                                return nullptr;
                            }
                            llvm::Type* aTy = val->getType();
                            llvm::Value* strVal = builder->CreateGlobalString(to_print);
                            builder->CreateCall(printString, {strVal});
                            to_print = "";
                            if (aTy->isIntegerTy(32) || aTy->isIntegerTy(64) || aTy->isIntegerTy(16) || aTy->isIntegerTy(4)) {
                                builder->CreateCall(printString,
                                                    {builder->CreateCall(fmtInt, {builder->CreateZExt(val, builder->getIntNTy(getPtrSize())),
                                                                                  llvm::ConstantInt::get(builder->getIntNTy(getPtrSize()), width),
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
                            std::string sourceType = getExpressionType(goodArgs[current_arg]);
                            if (sourceType == "string" || sourceType == "char*") {
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
                                        auto [reprMethod, ownerClass] = findMethodInHierarchy(className, "_repr");
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
                if (funcName == "`to_string" && !call.arg_nodes.empty()) {
                    AnyNode& argNode = call.arg_nodes.front();
                    llvm::Value* arg = emitExpr(argNode);
                    if (!arg) return nullptr;
                    return convertToString(arg, argNode);
                }
                if (funcName == "`to_long_int" && !call.arg_nodes.empty()) {
                    AnyNode& argNode = call.arg_nodes.front();
                    llvm::Value* arg = emitExpr(argNode);
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "long int");
                }
                if (funcName == "`to_short_int" && !call.arg_nodes.empty()) {
                    AnyNode& argNode = call.arg_nodes.front();
                    llvm::Value* arg = emitExpr(argNode);
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "short int");
                }
                if (funcName == "`to_qbool" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "qbool");
                }
                if (funcName == "`to_int" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "int");
                }

                if (funcName == "`to_float" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "float");
                }

                if (funcName == "`to_double" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "double");
                }

                if (funcName == "`to_bool" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "bool");
                }

                if (funcName == "`to_char" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "char");
                }
                if (funcName == "`to_addr_t" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "addr_t");
                }
                if (funcName == "`to_byte" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "byte");
                }
                if (funcName == "`to_nibble" && !call.arg_nodes.empty()) {
                    llvm::Value* arg = emitExpr(call.arg_nodes.front());
                    if (!arg) return nullptr;
                    return emitBuiltinConversion(arg, "nibble");
                }
                if (funcName == "`mapped_ptr" && !call.arg_nodes.empty()) {
                    llvm::Value* val = emitExpr(call.arg_nodes.front());
                    if (!(val->getType()->isIntegerTy())) {
                        cg_error((*varAccess)->var_name_tok.pos, "arg 1 must be a integer: " + funcName);
                        return nullptr;
                    }
                    if (!(val->getType()->isIntegerTy(getPtrSize()))) {
                        cg_error((*varAccess)->var_name_tok.pos,
                                 "arg 1 must be a integer the size of a pointer (" + std::to_string(getPtrSize()) + ") (addr_t or " +
                                     (getPtrSize() == 32 ? "int" : "long int") + ", got a " + std::to_string(val->getType()->getIntegerBitWidth()) +
                                     " bit integer (" +
                                     ((val->getType()->getIntegerBitWidth() == 32)
                                          ? "int"
                                          : ((val->getType()->getIntegerBitWidth() == 64) ? "long int" : "short int")) +
                                     ": " + funcName);
                        return nullptr;
                    }
                    return builder->CreateIntToPtr(val, builder->getPtrTy());
                }
                if (funcName == "`to_address" && !call.arg_nodes.empty()) {
                    llvm::Value* val = emitExpr(call.arg_nodes.front());
                    if (!(val->getType()->isPointerTy())) {
                        cg_error((*varAccess)->var_name_tok.pos, "arg 1 must be a pointer: " + funcName);
                        return nullptr;
                    }
                    return builder->CreatePtrToInt(val, builder->getIntNTy(getPtrSize()), "addr");
                }
                if (funcName == "`ternary" && !call.arg_nodes.empty()) {
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
                    llvm::Value* val = toTruthiness(emitExpr(call.arg_nodes.front()), get_pos(call.arg_nodes.front()));
                    if (val->getType()->isIntegerTy(1)) { return builder->CreateSelect(val, is_tr, is_fl, "select_val"); }
                    cg_error((*varAccess)->var_name_tok.pos, "arg 1 must be a boolean: " + funcName);
                    return nullptr;
                }
                if (funcName == "`inline" && !call.arg_nodes.empty()) {
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
                            op.isRW = false;
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
                            } else if (i < asm_text.size() && asm_text[i] == '+') {
                                op.isRW = true;
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
                            if (op.isOutput || op.isRW) {
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
                    size_t i = 0;
                    while (i < clobber_string.size()) {
                        if (clobber_string[i] != '~') {
                            i++;
                            continue;
                        }
                        i++;
                        while (i < clobber_string.size() && isspace(clobber_string[i])) i++;
                        if (i >= clobber_string.size() || clobber_string[i] != '{') {
                            cg_error((*varAccess)->var_name_tok.pos, "invalid clobber syntax: expected '{'");
                            return nullptr;
                        }
                        i++;
                        while (i < clobber_string.size()) {
                            while (i < clobber_string.size() && isspace(clobber_string[i])) { i++; }
                            std::string reg;
                            while (i < clobber_string.size() && clobber_string[i] != ',' && clobber_string[i] != '}') {
                                if (!isspace(clobber_string[i])) reg += clobber_string[i];
                                i++;
                            }
                            if (!reg.empty()) {
                                if (reg == "rsp" || reg == "esp" || reg == "rbp" || reg == "ebp") {
                                    cg_error((*varAccess)->var_name_tok.pos, reg + " is the stack pointer. You cannot clobber the stack pointer "
                                                                                   "because the compiler relies on it to track local variables "
                                                                                   "and function returns; modifying it guarantees a runtime crash.");
                                    return nullptr;
                                }
                                clobbers.push_back("~{" + reg + "}");
                            }
                            while (i < clobber_string.size() && isspace(clobber_string[i])) { i++; }
                            if (i < clobber_string.size() && clobber_string[i] == ',') {
                                i++;
                                continue;
                            }
                            if (i < clobber_string.size() && clobber_string[i] == '}') {
                                i++;
                                break;
                            }
                            cg_error((*varAccess)->var_name_tok.pos, "invalid clobber syntax: expected ',' or '}'");
                            return nullptr;
                        }
                    }
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
                    std::vector<llvm::Value*> output_ptrs;
                    std::vector<llvm::Type*> output_types;
                    for (auto& [idx, op] : unique_inputs) {
                        int arg_pos = idx + 1;
                        if (arg_pos >= call.arg_nodes.size() - 1) {
                            cg_error((*varAccess)->var_name_tok.pos, "asm input index out of range");
                            return nullptr;
                        }
                        auto it = std::next(call.arg_nodes.begin(), arg_pos);
                        llvm::Value* val = emitExpr(*it);
                        if (!val) return nullptr;
                        input_values.push_back(val);
                        input_types.push_back(val->getType());
                    }
                    std::vector<std::pair<unsigned, llvm::Type*>> memory_element_types;
                    for (auto& [idx, op] : unique_outputs) {
                        int arg_pos = idx + 1;
                        auto it = std::next(call.arg_nodes.begin(), arg_pos);
                        llvm::Value* out_ptr = emitLValue(*it);
                        if (!out_ptr) return nullptr;
                        if (op.kind == 'm') {
                            input_values.push_back(out_ptr);
                            input_types.push_back(out_ptr->getType());
                            memory_element_types.push_back({(unsigned)input_values.size() - 1, llvmTypeFor(getExpressionType(*it))});
                        }
                        if (op.kind == 'r') {
                            auto type = getExpressionType(*it);
                            output_types.push_back(llvmTypeFor(type));
                            output_ptrs.push_back(out_ptr);
                        }
                    }
                    llvm::Type* return_ty = builder->getVoidTy();
                    if (output_types.size() == 1) {
                        return_ty = output_types[0];
                    } else if (output_types.size() > 1) {
                        return_ty = llvm::StructType::get(context, output_types);
                    }
                    llvm::FunctionType* fn_ty = llvm::FunctionType::get(return_ty, input_types, false);
                    std::string constraints;
                    bool first = true;
                    for (auto& [idx, op] : unique_outputs) {
                        if (!first) constraints += ",";
                        if (op.kind == 'm') {
                            constraints += (op.isRW ? "+*m" : "=*m");
                        } else {
                            constraints += (op.isRW ? "+" : "=");
                            constraints += op.kind;
                        }
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
                    llvm::CallInst* asm_call = builder->CreateCall(fn_ty, asm_fn, input_values);
                    for (auto& [idx, ty] : memory_element_types) {
                        llvm::Attribute attr = llvm::Attribute::get(context, llvm::Attribute::ElementType, ty);
                        asm_call->addParamAttr(idx, attr);
                    }
                    llvm::Value* asm_result = asm_call;
                    if (output_types.empty()) { return nullptr; }
                    if (output_types.size() == 1) {
                        builder->CreateStore(asm_result, output_ptrs[0]);
                        return asm_result;
                    }
                    for (unsigned i = 0; i < output_types.size(); ++i) {
                        llvm::Value* value = builder->CreateExtractValue(asm_result, {i}, "asm_output");
                        builder->CreateStore(value, output_ptrs[i]);
                    }
                    return asm_result;
                }
                if (funcName == "`next" && !call.arg_nodes.empty()) {
                    if (auto acc = std::get_if<VarAccessNode*>(&call.arg_nodes.front())) {
                        std::string var_name = (*acc)->var_name_tok.value;
                        if (resolveVarType(var_name) != "...") {
                            cg_error((*varAccess)->var_name_tok.pos, "argument one must be a variadic argument: " + funcName);
                            return nullptr;
                        }
                        StringNode* expectedType = std::get_if<StringNode>(&call.arg_nodes.back());
                        TypeValueNode* otherExpType = std::get_if<TypeValueNode>(&call.arg_nodes.back());
                        if (!expectedType && !otherExpType) {
                            cg_error((*varAccess)->var_name_tok.pos,
                                     "argument two must be a string storing the type or the type. (" + funcName + ")");
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
                        llvm::Type* TargetType = llvmTypeFor(expectedType ? expectedType->tok.value : otherExpType->tok.value);
                        if (!TargetType) {
                            cg_error((*varAccess)->var_name_tok.pos, "argument two must be a valid type");
                            return nullptr;
                        }
                        if (TargetType->isIntegerTy()) {
                            ConvertedValue = builder->CreatePtrToInt(RawSlot, TargetType, "vararg_int");
                        } else if (TargetType->isPointerTy()) {
                            ConvertedValue = builder->CreateBitCast(RawSlot, TargetType, "vararg_ptr");
                        } else if (TargetType->isFloatingPointTy()) {
                            llvm::Type* Int64Ty = builder->getIntNTy(getPtrSize());
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
                        cg_error((*varAccess)->var_name_tok.pos, "argument one must be a direct variadic argument: " + funcName);
                    }
                    return nullptr;
                }
                if (funcName == "`is_empty" && !call.arg_nodes.empty()) {
                    if (auto acc = std::get_if<VarAccessNode*>(&call.arg_nodes.back())) {
                        std::string var_name = (*acc)->var_name_tok.value;
                        if (resolveVarType(var_name) != "...") {
                            cg_error((*acc)->var_name_tok.pos, "argument must be a variadic argument: " + funcName);
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
                        cg_error(get_pos(call.arg_nodes.back()), "argument must be a direct variadic argument: " + funcName);
                    }
                    return nullptr;
                }
                llvm::Function* fn = module->getFunction(runtimeName);
                if (!fn) {
                    cg_error((*varAccess)->var_name_tok.pos, "built-in function not found in runtime: " + runtimeName);
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
        if (llvm::Value* v = emitExpr(call.node_to_call)) {
            if (std::string className = getExpressionType(call.node_to_call); !className.empty()) {
                if (classTypes.find(className) != classTypes.end()) {
                    if (auto methodIt = std::find_if(
                            userTypes[baseTypeName(className)].classMethods.begin(), userTypes[baseTypeName(className)].classMethods.end(),
                            [&](const ClassMethodInfo& method) { return method.name_tok.value == "operator()" && method.generics.empty(); });
                        methodIt != userTypes[baseTypeName(className)].classMethods.end()) {
                        size_t methodIdx = std::distance(userTypes[baseTypeName(className)].classMethods.begin(), methodIt);
                        auto& info = userTypes[baseTypeName(className)].classMethods[methodIdx];
                        MethodCallNode* n = methodCallFromCall(*callPtr, "operator()");
                        auto args = prepareArgs(&info, n->args);
                        delete n;
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
                        llvm::Function* opMethod = findMethodOverload(className, "operator()", args);
                        if (!opMethod) {
                            cg_error(get_pos(*callPtr), "no matching operator() overload for class " + className);
                            return nullptr;
                        }
                        return emitMethodCall(opMethod, v, args, "operator()");
                    }
                    cg_error(get_pos(*callPtr), "no matching operator( ) for class " + className);
                    return nullptr;
                }
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
                cg_error((*varAccess)->var_name_tok.pos, "undeclared function or variable: " + name);
                return nullptr;
            }
            funcName = name;
        }
        if (!fnTy) {
            cg_error(get_pos(&call), "could not determine function type");
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
            cg_error(get_pos(&call), "spread is no longer allowed in function calls.");
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
            cg_error(get_pos(&call),
                     "too few arguments to function: got " + std::to_string(call.arg_nodes.size()) + ", expected " + std::to_string(args.size()));

            cg_note(get_pos(&call), "missing " + std::to_string(args.size() - call.arg_nodes.size()) + " argument" +
                                        (args.size() - call.arg_nodes.size() == 1 ? "" : "s"));

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
                            Int64Bits = builder->CreateZExt(Int32Bits, builder->getIntNTy(getPtrSize()), "i32_to_i64");
                        } else {
                            Int64Bits = builder->CreateBitCast(ValueToStore, builder->getIntNTy(getPtrSize()), "double_to_i64");
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
                            cg_error(get_pos(&call), "failed to evaluate default parameter");
                            return nullptr;
                        }
                        args.push_back(defVal);
                    } else {
                        cg_error(get_pos(&call), "missing required argument at position " + std::to_string(paramIdx));
                        return nullptr;
                    }
                }
                paramIdx++;
            }
        }
        llvm::Type* retTy = fnTy->getReturnType();
        if (insideTry()) {
            auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
            auto* invokeInst = builder->CreateInvoke(fnTy, calleeVal, contBB, currentLandingPad(), args, retTy->isVoidTy() ? "" : "calltmp");
            builder->SetInsertPoint(contBB);
            return retTy->isVoidTy() ? nullptr : invokeInst;
        }
        auto* callInst = builder->CreateCall(fnTy, calleeVal, args, retTy->isVoidTy() ? "" : "calltmp");
        return retTy->isVoidTy() ? nullptr : callInst;
    } else if (auto arrAcc = safe_get<ArrayAccessNode>(node)) {
        std::string ptrTy = getExpressionType(arrAcc->base);
        if (ptrTy.ends_with("*") || ptrTy == "@nullptr" || ptrTy == "string") {
            if (ptrTy == "@nullptr") {
                cg_error(get_pos(arrAcc), "attempted to dereference nullptr");
                return nullptr;
            }
            if (ptrTy == "void*") {
                cg_error(get_pos(arrAcc), "pointer arithmetic cannot be preformed on void pointers");
                return nullptr;
            }
            llvm::Value* value = emitExpr(arrAcc->indices[0]);
            if (!value->getType()->isIntegerTy()) {
                cg_error(get_pos(arrAcc->indices[0]), "attempted to index a pointer with a non-integer value.");
                return nullptr;
            }
            if (ptrTy == "string") {
                ptrTy = "char";
            } else {
                ptrTy.pop_back();
            }
            llvm::Value* addr = builder->CreateGEP(llvmTypeFor(ptrTy), emitExpr(arrAcc->base), value, "ptr_arr_addr");
            return builder->CreateLoad(llvmTypeFor(ptrTy), addr, "ptr_arr_val");
        }
        if (genericiseOrFindClass(ptrTy)) {
            llvm::Value* obj = emitLValue(arrAcc->base);
            llvm::Value* idx = emitExpr(arrAcc->indices[0]);
            llvm::Value* ref = emitVirtualOrDirectCall(ptrTy, "operator[]", obj, {idx});
            if (!ref) {
                cg_error(get_pos(arrAcc), ptrTy + " does not have operator[]");
                return nullptr;
            }
            return ref;
        }
        if (auto varAcc = safe_get<VarAccessNode>(arrAcc->base)) {
            std::string name = varAcc->var_name_tok.value;
            if (hasJaggedArray(name)) {
                auto jagIt = findJaggedArray(name);
                llvm::Value* alloc = getVarAddress(name);
                if (!alloc) {
                    cg_error(get_pos(varAcc), "unknown jagged array: " + name);
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
                    builder->CreateStore(indexVal, idxPtr, resolveVolatileVar(name));
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
                return builder->CreateLoad(elemTy, typedPtr, resolveVolatileVar(name), "jagged_elem");
            }
            llvm::Value* alloc = getVarAddress(name);
            if (!alloc) {
                cg_error(get_pos(varAcc), "unknown array: " + name);
                return nullptr;
            }

            llvm::Value* arrAlloc = alloc;
            llvm::Type* arrTy = getPointeeType(name);

            if (arrTy->isPointerTy()) {
                llvm::Value* ptr = builder->CreateLoad(arrTy, arrAlloc, resolveVolatileVar(name), "arr_ptr");
                llvm::Value* indexVal = emitExpr(arrAcc->indices[0]);
                if (!indexVal) return nullptr;
                auto it = findArrayType(name);
                if (it == arrayTypeStrings.end()) {
                    cg_error(get_pos(varAcc), "failed to find array access type");
                    return nullptr;
                }
                std::string baseType = it->second;
                llvm::Type* elemTy = llvmTypeFor(baseType);
                llvm::Value* elemPtr = builder->CreateGEP(elemTy, ptr, indexVal, "arr_elem_ptr");
                return builder->CreateLoad(elemTy, elemPtr, resolveVolatileVar(name), "arr_elem");
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
                return builder->CreateLoad(elemTy, elemPtr, resolveVolatileVar(name), "arr_elem");
            }
        }
        llvm::Value* base;
        llvm::Value* val = emitExpr(arrAcc->base);
        llvm::Type* elemTy;
        if (val->getType()->isArrayTy()) {
            base = emitLValue(arrAcc->base);
            elemTy = llvm::cast<llvm::ArrayType>(val->getType())->getElementType();
            if (!elemTy) {
                cg_error(get_pos(arrAcc), "cannot determine element type for array access");
                return nullptr;
            }
            llvm::Value* idx = emitExpr(arrAcc->indices[arrAcc->indices.size() - 1]);
            llvm::Value* elemPtr = builder->CreateInBoundsGEP(val->getType(), base, {builder->getInt32(0), idx}, "arr_elem_ptr");
            return builder->CreateLoad(elemTy, elemPtr, "arr_elem");
        } else {
            base = val;
            elemTy = llvmTypeFor(ptrTy.ends_with("*") ? ptrTy.substr(0, ptrTy.size() - 1) : ptrTy.substr(0, ptrTy.size() - 2));
            if (!elemTy) {
                cg_error(get_pos(arrAcc), "cannot determine element type for array access");
                return nullptr;
            }
            llvm::Value* idx = emitExpr(arrAcc->indices[arrAcc->indices.size() - 1]);
            llvm::Value* elemPtr = builder->CreateGEP(elemTy, base, idx, "arr_elem_ptr");
            return builder->CreateLoad(elemTy, elemPtr, "arr_elem");
        }
    } else if (auto propAccess = std::get_if<PropertyAccessNode*>(&node)) {
        std::string propName = (*propAccess)->property_name.value;

        std::string baseName = "";
        bool isEnum = false;
        if (auto varAccess = std::get_if<VarAccessNode*>(&*(*propAccess)->base)) {
            baseName = (*varAccess)->var_name_tok.value;
            if ((*varAccess)->var_name_tok.value == "this" && currentThis && !currentClassName.empty()) {
                int fieldIdx = getFlattenedFieldIndex(baseTypeName(currentClassName), propName);

                if (fieldIdx == -1) {
                    cg_error(get_pos(*varAccess), "unknown property: " + propName);
                    if (propName.length() > 3) {
                        std::vector<std::pair<int, std::string>> suggestions;
                        for (auto& field : userTypes[baseTypeName(currentClassName)].classFields) {
                            int distance = levenshteinDistance(propName, field.name);
                            if (distance <= 2) { suggestions.push_back({distance, field.name}); }
                        }
                        std::sort(suggestions.begin(), suggestions.end());
                        if (!suggestions.empty()) {
                            std::string note = "similar fields:";
                            for (auto& [distance, name] : suggestions) { note += "\n  - `" + name + "`"; }
                            cg_note(get_pos(*varAccess), note);
                        }
                    }
                    return nullptr;
                }

                auto [fieldOwnerClass, fieldAccess] = getFieldOwner(baseTypeName(currentClassName), propName);
                if (!canAccessField(baseTypeName(currentClassName), fieldOwnerClass, fieldAccess)) {
                    cg_error(get_pos(*varAccess), "cannot access " + fieldAccess + " field " + propName + " on " + baseTypeName(currentClassName));
                    return nullptr;
                }

                llvm::StructType* classTy = genericiseOrFindClass(currentClassName);
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

                    llvm::StructType* enumTy = enumTypes[resolved];
                    llvm::Value* enumVal = llvm::ConstantAggregateZero::get(enumTy);

                    enumVal = builder->CreateInsertValue(enumVal, builder->getInt32(tag), 0);

                    llvm::Value* dataPtr = createEnumData(type, value);
                    enumVal = builder->CreateInsertValue(enumVal, dataPtr, 1);

                    return enumVal;
                } else {
                    cg_error(get_pos(*varAccess), "enum " + baseName + " has no member " + propName);
                    std::vector<std::pair<int, std::string>> suggestions;
                    for (auto& entry : userTypes[resolved].enumEntries) {
                        int distance = levenshteinDistance(propName, entry.memberName);
                        if (distance <= 2) { suggestions.push_back({distance, entry.memberName}); }
                    }
                    std::sort(suggestions.begin(), suggestions.end());
                    if (!suggestions.empty()) {
                        std::string note = "similar entrys:";
                        for (auto& [distance, name] : suggestions) { note += "\n  - `" + name + "`"; }
                        cg_note(get_pos(*varAccess), note);
                    }
                    return nullptr;
                }
            }
        }

        if (isEnum) {
            cg_error(get_pos(*propAccess), "enum member not found");
            return nullptr;
        }
        if (propName == "length") {
            if (hasArrayLength(baseName)) {
                auto lenIt = findArrayLength(baseName);
                return builder->getInt32(lenIt->second);
            }
            auto runtimeIt = runtimeArraySizes.find(baseName);
            if (runtimeIt != runtimeArraySizes.end()) { return builder->CreateLoad(builder->getInt32Ty(), runtimeIt->second, "runtime_len"); }
            if (hasLocal(baseName)) {
                llvm::Type* allocTy = getPointeeType(baseName);
                if (allocTy && allocTy->isArrayTy()) { return builder->getInt32(allocTy->getArrayNumElements()); }
            }
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
                        auto userTypeIt = userTypes.find(baseTypeName(structName));
                        if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Struct) {
                            int fieldIdx = -1;
                            for (size_t i = 0; i < userTypeIt->second.fields.size(); i++) {
                                if (userTypeIt->second.fields[i].name == propName) {
                                    fieldIdx = i;
                                    break;
                                }
                            }

                            if (fieldIdx == -1) {
                                cg_error(get_pos(*varAccess), "struct " + structName + " has no field " + propName);
                                if (propName.length() > 3) {
                                    std::vector<std::pair<int, std::string>> suggestions;
                                    for (auto& field : userTypes[baseTypeName(structName)].fields) {
                                        int distance = levenshteinDistance(propName, field.name);
                                        if (distance <= 2) { suggestions.push_back({distance, field.name}); }
                                    }
                                    std::sort(suggestions.begin(), suggestions.end());
                                    if (!suggestions.empty()) {
                                        std::string note = "similar fields:";
                                        for (auto& [distance, name] : suggestions) { note += "\n  - `" + name + "`"; }
                                        cg_note(get_pos(*varAccess), note);
                                    }
                                }
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

            auto userTypeIt = userTypes.find(baseTypeName(structName));
            if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Struct) {
                int fieldIdx = -1;
                for (size_t i = 0; i < userTypeIt->second.fields.size(); i++) {
                    if (userTypeIt->second.fields[i].name == propName) {
                        fieldIdx = i;
                        break;
                    }
                }

                if (fieldIdx == -1) {
                    cg_error(get_pos(*propAccess), "struct " + structName + " has no field " + propName);
                    if (propName.length() > 3) {
                        std::vector<std::pair<int, std::string>> suggestions;
                        for (auto& field : userTypes[baseTypeName(structName)].fields) {
                            int distance = levenshteinDistance(propName, field.name);
                            if (distance <= 2) { suggestions.push_back({distance, field.name}); }
                        }
                        std::sort(suggestions.begin(), suggestions.end());
                        if (!suggestions.empty()) {
                            std::string note = "similar fields:";
                            for (auto& [distance, name] : suggestions) { note += "\n  - `" + name + "`"; }
                            cg_note(get_pos(*propAccess), note);
                        }
                    }

                    return nullptr;
                }
                llvm::Value* result = builder->CreateExtractValue(baseVal, fieldIdx, propName);
                return result;
            }
        }
        for (auto& [className, classTy] : classTypes) {
            if (baseTy == classTy) {
                int fieldIdx = getFlattenedFieldIndex(baseTypeName(className), propName);

                if (fieldIdx == -1) {
                    cg_error(get_pos(*propAccess), "field " + propName + " not found in class " + baseTypeName(className));
                    if (propName.length() > 3) {
                        std::vector<std::pair<int, std::string>> suggestions;
                        for (auto& field : userTypes[baseTypeName(className)].classFields) {
                            int distance = levenshteinDistance(propName, field.name);
                            if (distance <= 2) { suggestions.push_back({distance, field.name}); }
                        }
                        std::sort(suggestions.begin(), suggestions.end());
                        if (!suggestions.empty()) {
                            std::string note = "similar fields:";
                            for (auto& [distance, name] : suggestions) { note += "\n  - `" + name + "`"; }
                            cg_note(get_pos(*propAccess), note);
                        }
                    }
                    return nullptr;
                }
                auto [fieldOwnerClass, fieldAccess] = getFieldOwner(baseTypeName(className), propName);
                if (!canAccessField(currentClassName, fieldOwnerClass, fieldAccess)) {
                    cg_error(get_pos(*propAccess), "cannot access " + fieldAccess + " field " + propName);
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
                auto unionInfo = genericiseOrFindUnion(unionName);

                for (auto& member : unionInfo.members) {
                    std::string resolvedBaseType = resolveTypeName(member.type, false);
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
                            std::string inner = resolvedBaseType.substr(resolvedBaseType.find('<') + 1,
                                                                        resolvedBaseType.size() - resolvedBaseType.find('<') - 2);
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

                            llvm::StructType* classTy;
                            if (genericClasses[resolvedVariant]) {
                                classTy = generateGenericClass(resolvedVariant, userTypes.find(resolvedVariant)->second, genericParams);
                                if (classTy == nullptr) {
                                    cg_error(get_pos(*propAccess), "failed to create specialized version of class " + resolvedVariant);
                                    return nullptr;
                                }
                            } else {
                                classTy = genericiseOrFindClass(resolvedBaseType);
                            }
                            llvm::Value* castedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));

                            llvm::Type* fieldTy = classTy->getElementType(fieldIdx);
                            llvm::Value* fieldPtr = builder->CreateStructGEP(classTy, castedPtr, fieldIdx);
                            return builder->CreateLoad(fieldTy, fieldPtr, propName);
                        }
                    }
                    if (structTypes.find(resolvedVariant) != structTypes.end()) {
                        auto& structInfo = userTypes.at(baseTypeName(resolvedVariant));
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

                            llvm::StructType* structTy = genericiseOrFindStruct(resolvedVariant);
                            llvm::Value* castedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0));

                            llvm::Type* fieldTy = structTy->getElementType(fieldIdx);
                            llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, castedPtr, fieldIdx);
                            return builder->CreateLoad(fieldTy, fieldPtr, propName);
                        }
                    }
                }
            }
        }
        cg_error((*propAccess)->property_name.pos, "unknown property: " + propName);
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
                        for (auto m : genericiseOrFindUnion(typeName).members) {
                            std::string ty = resolveTypeName(m.type, false);
                            if (!classTypes.count(ty) && !genericClasses[ty]) {
                                idx++;
                                continue;
                            }
                            llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "union.case", F);
                            sw->addCase(builder->getInt32(idx), caseBB);
                            builder->SetInsertPoint(caseBB);
                            llvm::Value* payloadPtr = builder->CreateStructGEP(unionIt->second, unionPtr, 1);
                            llvm::Value* payload = builder->CreateLoad(builder->getPtrTy(), payloadPtr);
                            ClassMethodInfo* info = nullptr;
                            for (auto& m2 : userTypes.at(baseTypeName(baseTypeName(ty))).classMethods) {
                                if (m2.name_tok.value == methodName && m2.params.size() == (*call)->args.size()) {
                                    info = &m2;
                                    break;
                                }
                            }
                            if (!info) {
                                cg_error((*call)->method_name.pos, "no overload found");
                                struct Candidate {
                                    int score;
                                    ClassMethodInfo* method;
                                };
                                std::vector<Candidate> candidates;
                                for (auto& method : userTypes.at(baseTypeName(baseTypeName(ty))).classMethods) {
                                    if (method.is_constructor || (method.name_tok.value != methodName)) continue;
                                    int score = 0;
                                    size_t argCount = (*call)->args.size();
                                    size_t paramCount = method.params.size();
                                    score -= std::abs((int)argCount - (int)paramCount) * 5;
                                    size_t count = std::min(argCount, paramCount);
                                    for (size_t i = 0; i < count; i++) {
                                        llvm::Type* argTy = emitExpr((*call)->args[i])->getType();
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
                                if (candidates.empty()) {
                                    if (methodName.length() < 3) return nullptr;
                                    std::vector<std::pair<int, std::string>> suggestions;
                                    for (auto& method : userTypes[baseTypeName(ty)].classMethods) {
                                        int distance = levenshteinDistance(methodName, method.name_tok.value);
                                        if (distance <= 2) { suggestions.push_back({distance, method.name_tok.value}); }
                                    }
                                    std::sort(suggestions.begin(), suggestions.end());
                                    if (!suggestions.empty()) {
                                        std::string note = "similar methods:";
                                        for (auto& [distance, name] : suggestions) { note += "\n  - `" + name + "`"; }
                                        cg_note(get_pos(*varAccess), note);
                                    }
                                    return nullptr;
                                }
                                std::sort(candidates.begin(), candidates.end(),
                                          [](const Candidate& a, const Candidate& b) { return a.score > b.score; });
                                if (candidates[0].score > 0) {
                                    cg_note(get_pos(*varAccess), "closest matching overload: " + candidates[0].method->print());
                                }
                                if (candidates.size() <= 5) {
                                    std::string note = "available overloads:";
                                    for (auto& candidate : candidates) { note += "\n  - " + candidate.method->print(); }
                                    cg_note(get_pos(*varAccess), note);
                                } else {
                                    std::string note = "other overloads:";
                                    size_t shown = 0;
                                    for (auto& candidate : candidates) {
                                        if (shown >= 3) break;
                                        note += "\n  - " + candidate.method->print();
                                        shown++;
                                    }
                                    cg_note(get_pos(*varAccess), note);
                                }
                                return nullptr;
                            }
                            auto args = prepareArgs(info, (*call)->args);
                            llvm::Value* callResult = emitVirtualOrDirectCall(ty, methodName, payload, args);
                            result = callResult;
                            builder->CreateBr(joinBB);
                            idx++;
                        }
                        builder->SetInsertPoint(joinBB);
                        return result;
                    } else if (st) {
                        std::string typeStr = resolveVarType(varName);
                        if (typeStr.ends_with("*")) {
                            thisPtr = builder->CreateLoad(builder->getPtrTy(), getVarAddress(varName), "loaded_ptr");
                        } else {
                            thisPtr = getVarAddress(varName);
                        }
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
                    for (auto& m : genericiseOrFindUnion(unionName).members) {
                        std::string ty = resolveTypeName(m.type, false);
                        if (!classTypes.count(ty) && !genericClasses[ty]) {
                            idx++;
                            continue;
                        }
                        llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "union.case", F);
                        sw->addCase(builder->getInt32(idx), caseBB);
                        builder->SetInsertPoint(caseBB);
                        llvm::Value* payloadPtr = builder->CreateStructGEP(unionIt->second, unionPtr, 1);
                        llvm::Value* payload = builder->CreateLoad(builder->getPtrTy(), payloadPtr);
                        ClassMethodInfo* info = nullptr;
                        for (auto& m2 : userTypes.at(baseTypeName(baseTypeName(ty))).classMethods) {
                            if (m2.name_tok.value == methodName && m2.params.size() == (*call)->args.size()) {
                                info = &m2;
                                break;
                            }
                        }
                        if (!info) {
                            cg_error((*call)->method_name.pos, "no overload found");
                            struct Candidate {
                                int score;
                                ClassMethodInfo* method;
                            };
                            std::vector<Candidate> candidates;
                            for (auto& method : userTypes.at(baseTypeName(baseTypeName(ty))).classMethods) {
                                if (method.is_constructor || (method.name_tok.value != methodName)) continue;
                                int score = 0;
                                size_t argCount = (*call)->args.size();
                                size_t paramCount = method.params.size();
                                score -= std::abs((int)argCount - (int)paramCount) * 5;
                                size_t count = std::min(argCount, paramCount);
                                for (size_t i = 0; i < count; i++) {
                                    llvm::Type* argTy = emitExpr((*call)->args[i])->getType();
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
                            if (candidates.empty()) {
                                if (methodName.length() < 3) return nullptr;
                                std::vector<std::pair<int, std::string>> suggestions;
                                for (auto& method : userTypes[baseTypeName(ty)].classMethods) {
                                    int distance = levenshteinDistance(methodName, method.name_tok.value);
                                    if (distance <= 2) { suggestions.push_back({distance, method.name_tok.value}); }
                                }
                                std::sort(suggestions.begin(), suggestions.end());
                                if (!suggestions.empty()) {
                                    std::string note = "similar methods:";
                                    for (auto& [distance, name] : suggestions) { note += "\n  - `" + name + "`"; }
                                    cg_note((*call)->method_name.pos, note);
                                }
                                return nullptr;
                            }
                            std::sort(candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b) { return a.score > b.score; });
                            if (candidates[0].score > 0) {
                                cg_note((*call)->method_name.pos, "closest matching overload: " + candidates[0].method->print());
                            }
                            if (candidates.size() <= 5) {
                                std::string note = "available overloads:";
                                for (auto& candidate : candidates) { note += "\n  - " + candidate.method->print(); }
                                cg_note((*call)->method_name.pos, note);
                            } else {
                                std::string note = "other overloads:";
                                size_t shown = 0;
                                for (auto& candidate : candidates) {
                                    if (shown >= 3) break;
                                    note += "\n  - " + candidate.method->print();
                                    shown++;
                                }
                                cg_note((*call)->method_name.pos, note);
                            }
                            return nullptr;
                        }
                        auto args = prepareArgs(info, (*call)->args);
                        llvm::Value* callResult = emitVirtualOrDirectCall(ty, methodName, payload, args);
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
            llvm::StructType* structType;
            if (genericClasses[baseTypeName(ownerClass)]) {
                structType = generateGenericClass(baseTypeName(ownerClass), userTypes.find(baseTypeName(ownerClass))->second,
                                                  genericParamsFromName(ownerClass));
                if (structType == nullptr) {
                    cg_error(get_pos(*call), "failed to create specialized version of class " + baseTypeName(ownerClass));
                    return nullptr;
                }
            } else {
                structType = llvm::StructType::getTypeByName(context, baseTypeName(ownerClass));
            }
            unsigned fieldIndex = 0;
            bool found = false;
            const auto& fields = userTypes.at(baseTypeName(baseTypeName(ownerClass))).classFields;
            for (size_t i = 0; i < fields.size(); ++i) {
                if (fields[i].name == propAcc->property_name.value) {
                    fieldIndex = (unsigned)i;
                    found = true;
                    break;
                }
            }
            if (!found) { return (cg_error((*call)->method_name.pos, "field not found"), nullptr); }
            llvm::Value* fieldAddr = builder->CreateStructGEP(structType, baseAddr, fieldIndex);
            thisPtr = fieldAddr;
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
                    for (auto& m : genericiseOrFindUnion(unionName).members) {
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
                        for (auto& m2 : userTypes.at(baseTypeName(baseTypeName(ty))).classMethods) {
                            if (m2.name_tok.value == methodName && m2.params.size() == (*call)->args.size()) {
                                info = &m2;
                                break;
                            }
                        }
                        if (!info) {
                            cg_error((*call)->method_name.pos, "no overload found");
                            struct Candidate {
                                int score;
                                ClassMethodInfo* method;
                            };
                            std::vector<Candidate> candidates;
                            for (auto& method : userTypes.at(baseTypeName(baseTypeName(ty))).classMethods) {
                                if (method.is_constructor || (method.name_tok.value != methodName)) continue;
                                int score = 0;
                                size_t argCount = (*call)->args.size();
                                size_t paramCount = method.params.size();
                                score -= std::abs((int)argCount - (int)paramCount) * 5;
                                size_t count = std::min(argCount, paramCount);
                                for (size_t i = 0; i < count; i++) {
                                    llvm::Type* argTy = emitExpr((*call)->args[i])->getType();
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
                            if (candidates.empty()) {
                                if (methodName.length() < 3) return nullptr;
                                std::vector<std::pair<int, std::string>> suggestions;
                                for (auto& method : userTypes[baseTypeName(ty)].classMethods) {
                                    int distance = levenshteinDistance(methodName, method.name_tok.value);
                                    if (distance <= 2) { suggestions.push_back({distance, method.name_tok.value}); }
                                }
                                std::sort(suggestions.begin(), suggestions.end());
                                if (!suggestions.empty()) {
                                    std::string note = "similar methods:";
                                    for (auto& [distance, name] : suggestions) { note += "\n  - `" + name + "`"; }
                                    cg_note((*call)->method_name.pos, note);
                                }
                                return nullptr;
                            }
                            std::sort(candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b) { return a.score > b.score; });
                            if (candidates[0].score > 0) {
                                cg_note((*call)->method_name.pos, "closest matching overload: " + candidates[0].method->print());
                            }
                            if (candidates.size() <= 5) {
                                std::string note = "available overloads:";
                                for (auto& candidate : candidates) { note += "\n  - " + candidate.method->print(); }
                                cg_note((*call)->method_name.pos, note);
                            } else {
                                std::string note = "other overloads:";
                                size_t shown = 0;
                                for (auto& candidate : candidates) {
                                    if (shown >= 3) break;
                                    note += "\n  - " + candidate.method->print();
                                    shown++;
                                }
                                cg_note((*call)->method_name.pos, note);
                            }
                            return nullptr;
                        }
                        auto args = prepareArgs(info, (*call)->args);
                        llvm::Value* callResult = emitVirtualOrDirectCall(ty, methodName, payload, args);
                        result = callResult;
                        builder->CreateBr(joinBB);
                        idx++;
                    }
                    builder->SetInsertPoint(joinBB);
                    return result;
                }
            }
            std::string exprTy = getExpressionType((*call)->base, false);
            if (exprTy.ends_with("*")) {
                targetClass = exprTy.substr(0, exprTy.size() - 1);
                thisPtr = baseVal;
            } else if (auto* sTy = llvm::dyn_cast<llvm::StructType>(baseVal->getType())) {
                targetClass = sTy->getName().str();
                thisPtr = createEntryAlloca("temp_this", sTy);
                builder->CreateStore(baseVal, thisPtr);
            }
        }
        if (targetClass.empty()) return (cg_error((*call)->method_name.pos, "cannot resolve target"), nullptr);
        if (llvm::Value* specializedCall = tryHandleSpecialized(targetClass, methodName, *call, thisPtr)) { return specializedCall; }
        ClassMethodInfo* info = nullptr;
        std::string searchClass = baseTypeName(targetClass);
        while (!searchClass.empty() && !info) {
            for (auto& m : userTypes.at(baseTypeName(searchClass)).classMethods) {
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
            searchClass = userTypes.at(baseTypeName(searchClass)).baseClassName;
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
                    llvm::Value* asInt = builder->CreateBitCast(val, builder->getIntNTy(getPtrSize()));
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
        std::string dispatchClass = targetClass;
        targetClass = resolveVirtualTargetClass(targetClass, methodName, (*call)->args.size());
        llvm::Function* method = findMethodOverload(targetClass, methodName, args);
        if (!method) return (cg_error((*call)->method_name.pos, "no overload found"), nullptr);
        auto vtableIt = vtables.find(targetClass);
        auto slotIt = vtableSlotIndex.find(targetClass);
        if (vtableIt != vtables.end() && slotIt != vtableSlotIndex.end()) {
            std::string mangledName = targetClass + "_" + methodName;
            if (info && classMethods[targetClass][methodName].size() > 1) {
                for (auto& param : info->params) { mangledName += "_" + (param.signature.has_value() ? std::string("fn") : param.type.value); }
            }
            auto indexIt = slotIt->second.find(mangledName);
            if (indexIt != slotIt->second.end()) {
                int slotIndex = indexIt->second;
                llvm::StructType* classTy = genericiseOrFindClass(targetClass);
                llvm::Value* vptrField = builder->CreateStructGEP(classTy, thisPtr, 0, "vptr_field");
                llvm::Value* vptr = builder->CreateLoad(builder->getPtrTy(), vptrField, "vptr");
                llvm::Value* fnPtrAddr = builder->CreateGEP(builder->getPtrTy(), vptr, builder->getInt32(slotIndex), "vtable_slot");
                llvm::Value* fnPtr = builder->CreateLoad(builder->getPtrTy(), fnPtrAddr, "fn_ptr");
                std::vector<llvm::Value*> allArgs = {thisPtr};
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

        return emitMethodCall(method, thisPtr, args, methodName);
    } else if (auto spread = std::get_if<SpreadNode*>(&node)) {
        cg_error(get_pos(*spread), "spread operator can only be used in array "
                                   "literals");
        return nullptr;
    } else if (auto fieldAssign = std::get_if<FieldAssignNode*>(&node)) {
        std::string fieldName = (*fieldAssign)->field_name.value;
        std::string targetTypeStr = "";
        if (auto varAccess = std::get_if<VarAccessNode*>(&(*fieldAssign)->base)) {
            if ((*varAccess)->var_name_tok.value == "this" && !currentClassName.empty()) {
                targetTypeStr = getFieldType(baseTypeName(currentClassName), fieldName);
            }
        }
        llvm::Value* valueVal = nullptr;
        if (!valueVal) { valueVal = emitExpr((*fieldAssign)->value); }
        if (!valueVal) return nullptr;
        if (auto varAccess = std::get_if<VarAccessNode*>(&(*fieldAssign)->base)) {
            if ((*varAccess)->var_name_tok.value == "this" && currentThis && !currentClassName.empty()) {
                int fieldIdx = getFlattenedFieldIndex(baseTypeName(currentClassName), fieldName);
                if (fieldIdx == -1) {
                    cg_error(get_pos(*varAccess), "field not found: " + fieldName);
                    return nullptr;
                }

                auto [fieldOwnerClass, fieldAccess] = getFieldOwner(currentClassName, fieldName);
                if (!canAccessField(currentClassName, fieldOwnerClass, fieldAccess)) {
                    cg_error(get_pos(*varAccess), "cannot access " + fieldAccess + " field");
                    return nullptr;
                }
                llvm::StructType* classTy = genericiseOrFindClass(currentClassName);
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
        varTypes[fullName] = ref->type_tok.value.substr(9, ref->type_tok.value.length() - 9) + "&";
        volatileVars[fullName] = ref->type_tok.value.starts_with("volatile ");
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

    llvm::Function* mallocFn = module->getFunction("qc_malloc");
    if (!mallocFn) {
        llvm::FunctionType* mallocTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {builder->getIntNTy(getPtrSize())}, false);
        mallocFn = llvm::Function::Create(mallocTy, llvm::Function::InternalLinkage, "qc_malloc", module);
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
        if (!info.generics.empty()) continue;
        llvm::StructType* structTy = structTypes[name];
        llvm::FunctionType* reprFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {structTy}, false);
        llvm::Function* reprFn = module->getFunction(name + "_repr");
        if (!reprFn) reprFn = llvm::Function::Create(reprFnTy, llvm::Function::ExternalLinkage, name + "_repr", module);
        if (isHeader || info.baseFile.ends_with(".hqc")) continue;
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
        }
        return val;
    }
    std::string fnName;
    if (ty->isIntegerTy(32))
        fnName = "qc_to_string_int";
    else if (ty->isIntegerTy(64))
        fnName = "qc_to_string_long_int";
    else if (ty->isIntegerTy(16))
        fnName = "qc_to_string_short_int";
    else if (ty->isFloatTy())
        fnName = "qc_to_string_float";
    else if (ty->isDoubleTy())
        fnName = "qc_to_string_double";
    else if (ty->isIntegerTy(1))
        fnName = "qc_to_string_bool";
    else if (ty->isIntegerTy(2))
        fnName = "qc_to_string_qbool";
    else if (ty->isIntegerTy(4))
        fnName = "qc_to_string_nibble";
    else if (ty->isIntegerTy(8))
        fnName = "qc_to_string_char";
    else {
        cg_error(Position(), "cannot convert type to string");
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
        int elemTypeCode = 0;

        if (auto varAccess = std::get_if<VarAccessNode*>(&collExpr)) {
            std::string collName = (*varAccess)->var_name_tok.value;
            if (hasArrayType(collName)) {
                auto typeIt = findArrayType(collName);
                elemTypeCode = getTypeCode(typeIt->second);
            }
        }

        for (int i = 0; i < length; i++) {
            llvm::Value* elemVal;
            llvm::Type* elemTy = getTypeFromCode(elemTypeCode);
            llvm::Value* gepPtr = builder->CreateGEP(elemTy, collVal, builder->getInt32(i));
            elemVal = builder->CreateLoad(elemTy, gepPtr);
            elements.push_back(elemVal);
        }
    } else {
        cg_error(get_pos(collExpr), "cannot spread runtime-sized collection into array literal");
    }
}
llvm::Value* LLVMCompiler::expandSpreadIntoArrays(llvm::Value* collVal, AnyNode& collExpr, llvm::AllocaInst* argsArray, llvm::AllocaInst* typesArray,
                                                  llvm::Value* startIndex) {
    llvm::Value* lengthVal = getCollectionLength(collVal, collExpr);
    if (!lengthVal) return startIndex;

    int elemTypeCode = 0;

    if (auto varAccess = std::get_if<VarAccessNode*>(&collExpr)) {
        std::string collName = (*varAccess)->var_name_tok.value;
        if (hasArrayType(collName)) {
            auto typeIt = findArrayType(collName);
            elemTypeCode = getTypeCode(typeIt->second);
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
        llvm::Value* locAlloc = getVarAddress(collName);
        if (locAlloc) {
            llvm::Type* allocTy = getPointeeType(collName);

            if (allocTy && allocTy->isArrayTy()) { return builder->getInt32(allocTy->getArrayNumElements()); }
        }
    }

    if (auto arrLit = std::get_if<ArrayLiteralNode*>(&collExpr)) { return builder->getInt32((*arrLit)->elements.size()); }
    cg_error(get_pos(collExpr), "cannot determine collection length for spread");
    return nullptr;
}
llvm::Value* LLVMCompiler::copySpreadToArray(llvm::Value* collVal, AnyNode& collExpr, llvm::Value* destArray, llvm::Value* startIndex,
                                             llvm::Type* elemTy, int elemTypeCode) {
    llvm::Value* lengthVal = getCollectionLength(collVal, collExpr);
    if (!lengthVal) return startIndex;
    bool isJagged = false;
    if (auto varAccess = std::get_if<VarAccessNode*>(&collExpr)) {
        std::string rawName = (*varAccess)->var_name_tok.value;
        std::string resolvedName = resolveMetadataName(rawName);
        if (hasJaggedArray(resolvedName)) { isJagged = true; }
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
    llvm::Value* srcPtr = builder->CreateGEP(elemTy, collVal, iVal);
    elemVal = builder->CreateLoad(elemTy, srcPtr);
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
        cg_error(Position(), "cannot determine element type for runtime array");
        return nullptr;
    }
    llvm::Function* mallocFn = module->getFunction("qc_malloc");
    if (!mallocFn) {
        llvm::FunctionType* mallocTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {builder->getIntNTy(getPtrSize())}, false);
        mallocFn = llvm::Function::Create(mallocTy, llvm::Function::InternalLinkage, "qc_malloc", module);
    }

    const llvm::DataLayout& DL = module->getDataLayout();
    uint64_t elemSize = DL.getTypeAllocSize(elemTy);
    llvm::Value* totalSizeExt = builder->CreateZExt(totalSize, builder->getIntNTy(getPtrSize()));
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

        llvm::GlobalVariable* gv = new llvm::GlobalVariable(*module, ty, false, llvm::GlobalValue::ExternalLinkage, initVal, name);
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
    llvm::GlobalValue::LinkageTypes linkage = llvm::Function::ExternalLinkage;
    auto* func = module->getFunction(name);
    functionSignatures[name] = {fTy, {}};
    if (func) {
        if (func->getFunctionType() != fTy) { cg_warn(fn.getPos(), "conflicting declaration for function " + name); }
        if (fn.is_foreign || fn.is_header) return func;
        if (!func->empty()) { cg_warn(fn.getPos(), "redefinition of function " + name); }
        func->setLinkage(linkage);
    } else {
        func = llvm::Function::Create(fTy, linkage, name, module);
    }
    llvm::SmallVector<llvm::Metadata*, 4> retTypes;
    for (auto& ret : fn.return_types) { retTypes.push_back(llvm::MDString::get(context, ret.value)); }
    func->setMetadata("qc.return_types", llvm::MDNode::get(context, retTypes));
    if (fn.is_volatile) {
        func->addFnAttr(llvm::Attribute::NoInline);
        func->addFnAttr(llvm::Attribute::OptimizeNone);
        func->addFnAttr("noipa");
    }
    for (int i = 0; i < fTy->getNumParams(); i++) {
        auto it = fn.params.begin();
        std::advance(it, i);
        if (it->type.value.starts_with("out ")) {
            func->addParamAttr(i, llvm::Attribute::WriteOnly);
            func->addParamAttr(i, llvm::Attribute::getWithCaptureInfo(context, llvm::CaptureInfo::none()));
        } else if (it->type.value.starts_with("inout ")) {
            func->addParamAttr(i, llvm::Attribute::getWithCaptureInfo(context, llvm::CaptureInfo::none()));
        }
        if (it->type.value.ends_with("restrict")) { func->addParamAttr(i, llvm::Attribute::NoAlias); }
    }
    if (fn.is_foreign || fn.is_header) return func;
    enterScope();
    auto savedLambdaTypes = lambdaTypes;
    llvm::BasicBlock* savedInsertBlock = builder->GetInsertBlock();
    auto* entryBB = llvm::BasicBlock::Create(context, "entry", func);
    builder->SetInsertPoint(entryBB);
    auto* oldFunction = currentFunction;
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
            if (t.find("[]") != std::string::npos) {
                int dims = 0;
                size_t pos = t.find("[]");
                while (pos != std::string::npos) {
                    dims++;
                    pos = t.find("[]", pos + 2);
                }
                if (dims > 0 && name != entrypointName) {
                    cg_warn(Position(), "Using type " + t + " as parameter to function, which will degrade to " + ([](std::string str) {
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

    for (auto& stmt : fn.body->statements) { emitStmt(stmt); }

    if (!builder->GetInsertBlock()->getTerminator()) {
        if (fn.is_multi_return()) {
            llvm::Type* retTy = fTy->getReturnType();
            builder->CreateRet(llvm::ConstantAggregateZero::get(retTy));
        } else {
            llvm::Type* retTy = fTy->getReturnType();
            if (retTy->isVoidTy()) {
                builder->CreateRetVoid();
            } else if (retTy->isIntegerTy()) {
                builder->CreateRet(llvm::ConstantInt::get(retTy, 0));
            } else if (retTy->isFloatingPointTy()) {
                builder->CreateRet(llvm::ConstantFP::get(retTy, 0.0));
            } else {
                builder->CreateRet(llvm::ConstantAggregateZero::get(retTy));
            }
        }
    }

    if (savedInsertBlock) { builder->SetInsertPoint(savedInsertBlock); }

    currentFunction = oldFunction;
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
void LLVMCompiler::emitStmt(AnyNode node) {
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
            cg_error(mret->pos, "multi-return in non-multi-return function");
            return;
        }

        llvm::Value* agg = llvm::ConstantAggregateZero::get(retTy);
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
                        llvm::StructType* classTy = genericiseOrFindClass(funcName);

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
                            if (insideTry()) {
                                auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
                                llvm::InvokeInst* invoke = builder->CreateInvoke(ctor, contBB, currentLandingPad(), allArgs);
                                builder->SetInsertPoint(contBB);
                            } else {
                                builder->CreateCall(ctor, allArgs);
                            }
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
                    llvm::Type* iTy = builder->getIntNTy(getPtrSize());
                    llvm::Value* size = llvm::ConstantInt::get(iTy, module->getDataLayout().getTypeAllocSize(arrayType));

                    llvm::Function* mallocFn = module->getFunction("qc_malloc");
                    if (!mallocFn) {
                        llvm::FunctionType* mallocTy = llvm::FunctionType::get(builder->getPtrTy(), {iTy}, false);
                        mallocFn = llvm::Function::Create(mallocTy, llvm::Function::InternalLinkage, "qc_malloc", module);
                    }

                    llvm::Value* heapPtr = builder->CreateCall(mallocFn, {size});
                    llvm::Value* typedPtr = builder->CreateBitCast(heapPtr, llvm::PointerType::get(context, 0));

                    builder->CreateStore(val, typedPtr);

                    val = builder->CreateBitCast(typedPtr, destTy);
                }
            }
            if (this->returnsRef(i)) { val = this->emitLValue(mret->values[i]); }
            if (!val) { val = emitExpr(mret->values[i]); }
            if (!val) return;
            llvm::Type* srcTy = val->getType();
            llvm::Type* destTy = retStructTy->getElementType(i);
            if (isUnionType(srcTy) && !isUnionType(destTy)) {
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
            if (!isUnionType(srcTy)) {
                std::string unionName;
                if (isUnionType(destTy, &unionName)) {
                    int tag = findUnionVariantTag(unionName, mret->values[i], val);
                    if (tag == -1) {
                        cg_error(mret->pos, "return value doesn't match union variant");
                        return;
                    }

                    llvm::Value* unionVal = llvm::ConstantAggregateZero::get(destTy);
                    unionVal = builder->CreateInsertValue(unionVal, builder->getInt32(tag), 0);
                    llvm::Value* dataPtr = storeAndGetPointer(val);
                    val = builder->CreateInsertValue(unionVal, dataPtr, 1);

                    srcTy = destTy;
                    break;
                }
            }
            for (auto& [enumName, enumTy] : enumTypes) {
                if (isEnumType(srcTy) && !isEnumType(destTy)) {
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
                if (!isEnumType(srcTy) && isEnumType(destTy)) {
                    int tag = findEnumVariantTag(enumName, mret->values[i], val);
                    if (tag == -1) {
                        cg_error(mret->pos, "return value doesn't match enum variant");
                        return;
                    }

                    llvm::Value* enumVal = llvm::ConstantAggregateZero::get(enumTy);
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
                    llvm::StructType* classTy = genericiseOrFindClass(funcName);
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
                        if (insideTry()) {
                            auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++), currentFunction);
                            llvm::InvokeInst* invoke = builder->CreateInvoke(ctor, contBB, currentLandingPad(), allArgs);
                            builder->SetInsertPoint(contBB);
                        } else {
                            builder->CreateCall(ctor, allArgs);
                        }
                        llvm::Value* result = llvm::ConstantAggregateZero::get(classTy);
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
        llvm::Value* v = nullptr;
        llvm::Type* destTy = currentFunction->getReturnType();
        if (this->returnsRef()) { v = this->emitLValue((*ret)->value); }
        if (!v) { v = emitExpr((*ret)->value); }

        if (!v) {
            if (currentFunction->getReturnType()->isVoidTy()) {
                builder->CreateRetVoid();
            } else {
                cg_error((*ret)->pos, "return without value in non-void function");
            }
            return;
        }
        llvm::Type* srcTy = v->getType();
        destTy = currentFunction->getReturnType();
        if (auto arrayLit = std::get_if<ArrayLiteralNode*>(&(*ret)->value)) {
            if (destTy->isPointerTy() && srcTy->isArrayTy()) {
                llvm::ArrayType* arrayType = llvm::cast<llvm::ArrayType>(srcTy);
                llvm::Type* iTy = builder->getIntNTy(getPtrSize());
                llvm::Value* size = llvm::ConstantInt::get(iTy, module->getDataLayout().getTypeAllocSize(arrayType));
                llvm::Function* mallocFn = module->getFunction("qc_malloc");
                if (!mallocFn) {
                    llvm::FunctionType* mallocTy = llvm::FunctionType::get(builder->getPtrTy(), {iTy}, false);
                    mallocFn = llvm::Function::Create(mallocTy, llvm::Function::InternalLinkage, "qc_malloc", module);
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
                    cg_error((*ret)->pos, "return value doesn't match union variant");
                    return;
                }

                llvm::Value* unionVal = llvm::ConstantAggregateZero::get(unionTy);
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
                    cg_error((*ret)->pos, "return value doesn't match enum variant");
                    return;
                }

                llvm::Value* enumVal = llvm::ConstantAggregateZero::get(enumTy);
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
            cg_error(mv->var_names[0].pos, "failed to compile multi-var initializer");
            return;
        }

        llvm::Type* retTy = callVal->getType();
        if (!retTy->isStructTy() || retTy->getStructNumElements() != mv->var_names.size()) {
            cg_error(mv->var_names[0].pos, "multi-return arity/type mismatch");
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
        cond = toTruthiness(cond, get_pos(if_node->condition));
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
        enterScope();
        for (auto& stmt : if_node->then_branch->statements) { emitStmt(stmt); }
        exitScope();
        if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(mergeBB); }
        for (size_t i = 0; i < elifBlocks.size(); i++) {
            builder->SetInsertPoint(elifBlocks[i].first);
            llvm::Value* elifCond = emitExpr(if_node->elif_branches[i].first);

            llvm::BasicBlock* nextElifBB = (i + 1 < elifBlocks.size()) ? elifBlocks[i + 1].first : (elseBB ? elseBB : mergeBB);
            builder->CreateCondBr(elifCond, elifBlocks[i].second, nextElifBB);

            builder->SetInsertPoint(elifBlocks[i].second);
            enterScope();
            for (auto& stmt : if_node->elif_branches[i].second->statements) { emitStmt(stmt); }
            exitScope();
            if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(mergeBB); }
        }
        if (elseBB) {
            builder->SetInsertPoint(elseBB);
            enterScope();
            for (auto& stmt : if_node->else_branch->statements) { emitStmt(stmt); }
            exitScope();
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
        cond = toTruthiness(cond, get_pos(while_node->condition));
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
            cg_error(get_pos(node), "break outside of loop/switch");
        }
    } else if (std::holds_alternative<ContinueNode*>(node)) {
        if (currentContinueBB) {
            builder->CreateBr(currentContinueBB);
        } else {
            cg_error(get_pos(node), "continue outside of loop");
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
        cond = toTruthiness(cond, get_pos(for_node->condition));
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
            cg_error(get_pos(qsw), "failed to compile qswitch value");
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
            cg_error(get_pos(qsw), "qswitch requires qbool type");
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
        bool isVolatile = false;
        if (elemType.starts_with("volatile ")) {
            isVolatile = true;
            elemType.erase(0, 9);
        }
        llvm::Type* elemTy = llvmTypeFor(elemType);
        if (!elemTy) {
            cg_error(arrDecl->type_tok.pos, "unknown array element type: " + elemType);
            return;
        }
        arrayTypeStrings[name] = elemType;
        if (!std::holds_alternative<ArrayLiteralNode*>(arrDecl->value) && !std::holds_alternative<std::monostate>(arrDecl->value)) {

            llvm::Value* arrPtr = emitExpr(arrDecl->value);
            if (!arrPtr) return;

            llvm::AllocaInst* alloc = createEntryAlloca(name, arrPtr->getType());
            builder->CreateStore(arrPtr, alloc, isVolatile);
            locals[name] = alloc;
            volatileVars[name] = isVolatile;
            return;
        }
        if (auto arrLit = std::get_if<ArrayLiteralNode*>(&arrDecl->value)) {
            if ((*arrLit)->elements.empty()) {
                llvm::Value* lengthValue = emitExpr((*arrLit)->length);
                auto* lengthConstant = llvm::dyn_cast<llvm::ConstantInt>(lengthValue);
                if (!lengthConstant) {
                    cg_error(get_pos(*arrLit), "array length must be constant");
                    return;
                }
                uint64_t length = lengthConstant->getZExtValue();
                auto* arrTy = llvm::ArrayType::get(elemTy, length);
                auto* alloc = createEntryAlloca(name, arrTy);
                uint64_t bytes = module->getDataLayout().getTypeAllocSize(arrTy).getFixedValue();
                builder->CreateMemSet(alloc, builder->getInt8(0), builder->getInt64(bytes), llvm::MaybeAlign(1), isVolatile);
                locals[name] = alloc;
                arrayTypeStrings[name] = elemType;
                arrayLengths[name] = length;
                volatileVars[name] = isVolatile;
                return;
            }
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
                builder->CreateStore(arrPtr, alloc, isVolatile);
                std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
                locals[fullName] = alloc;
                arrayTypeStrings[fullName] = elemType;
                volatileVars[fullName] = isVolatile;
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
                builder->CreateStore(jaggedArr, alloc, isVolatile);
                std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
                locals[fullName] = alloc;
                volatileVars[fullName] = isVolatile;
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
                llvm::Function* mallocFn = module->getFunction("qc_malloc");
                if (!mallocFn) {
                    llvm::FunctionType* mallocTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), {builder->getIntNTy(getPtrSize())},
                                                                           false);
                    mallocFn = llvm::Function::Create(mallocTy, llvm::Function::InternalLinkage, "qc_malloc", module);
                }

                const llvm::DataLayout& DL = module->getDataLayout();
                uint64_t sizeBytes = DL.getTypeAllocSize(arrTy);

                llvm::Value* mallocCall = builder->CreateCall(mallocFn, {builder->getInt64(sizeBytes)}, "heap_arr");
                llvm::Value* arrPtr = builder->CreateBitCast(mallocCall, llvm::PointerType::get(context, 0), "arr_cast");

                alloc = createEntryAlloca(name, llvm::PointerType::get(context, 0));
                builder->CreateStore(arrPtr, alloc, isVolatile);
                arrayTypeStrings[name] = elemType;
            } else {
                alloc = createEntryAlloca(name, arrTy);
            }
            std::string fullName = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
            locals[fullName] = alloc;
            volatileVars[fullName] = isVolatile;
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
                const llvm::DataLayout& dl = module->getDataLayout();
                uint64_t sizeBytes = dl.getTypeAllocSize(arrTy).getFixedValue();
                builder->CreateMemSet(alloc, builder->getInt8(0), builder->getInt64(sizeBytes), llvm::MaybeAlign(1), isVolatile);
                locals[name] = alloc;
                arrayTypeStrings[name] = elemType;
                arrayLengths[name] = arraySize;
                volatileVars[name] = isVolatile;
                return;
            }
        }
        return;
    } else if (auto arrAssign = safe_get<ArrayAssignNode>(node)) {
        if (auto arrAcc = safe_get<ArrayAccessNode>(arrAssign->array_access)) {
            std::string ptrTy = getExpressionType(arrAcc->base);
            if (ptrTy.ends_with("*") || ptrTy == "@nullptr") {
                if (ptrTy == "@nullptr") {
                    cg_error(get_pos(arrAcc), "attempted to dereference nullptr");
                    return;
                }
                if (ptrTy == "void*") {
                    cg_error(get_pos(arrAcc), "you cannot dereference or indice void*");
                    return;
                }
                std::string valueTy = getExpressionType(arrAcc->indices[0]);
                if (valueTy != "int") {
                    cg_error(get_pos(arrAcc->indices[0]), "attempted to index a pointer with a "
                                                          "non-integer value.");
                    return;
                }
                llvm::Value* value = emitExpr(arrAcc->indices[0]);
                ptrTy.pop_back();
                llvm::Value* addr = builder->CreateGEP(llvmTypeFor(ptrTy), emitExpr(arrAcc->base), value, "ptr_arr_asi");
                llvm::Value* valToStore = emitExpr(arrAssign->value);
                builder->CreateStore(valToStore, addr);
            }
            if (genericiseOrFindClass(ptrTy)) {
                llvm::Value* obj = emitLValue(arrAcc->base);
                llvm::Value* idx = emitExpr(arrAcc->indices[0]);
                llvm::Value* ref = emitVirtualOrDirectCall(ptrTy, "operator[]", obj, {idx});
                if (!ref) {
                    cg_error(get_pos(arrAcc->base), ptrTy + " does not have operator[]");
                    return;
                }
                llvm::Value* val = emitExpr(arrAssign->value);
                builder->CreateStore(val, ref);
                return;
            }
            if (auto varAcc = safe_get<VarAccessNode>(arrAcc->base)) {
                std::string name = varAcc->var_name_tok.value;
                if (hasJaggedArray(name)) {
                    auto jagIt = findJaggedArray(name);
                    if (!hasLocal(name)) {
                        cg_error(get_pos(varAcc), "unknown jagged array: " + name);
                        return;
                    }
                    auto it = findLocal(name);
                    llvm::Value* jaggedPtr = builder->CreateLoad(llvm::PointerType::get(context, 0), it->second, "jagged_ptr");
                    llvm::ArrayType* indicesArrTy = llvm::ArrayType::get(builder->getInt32Ty(), arrAcc->indices.size());
                    llvm::AllocaInst* indicesAlloc = createEntryAlloca("indices_arr", indicesArrTy);

                    for (size_t i = 0; i < arrAcc->indices.size(); i++) {
                        llvm::Value* indexVal = emitExpr(arrAcc->indices[i]);
                        if (!indexVal) return;

                        std::vector<llvm::Value*> indices = {builder->getInt32(0), builder->getInt32(i)};
                        llvm::Value* idxPtr = builder->CreateInBoundsGEP(indicesArrTy, indicesAlloc, indices);
                        builder->CreateStore(indexVal, idxPtr, hasVolatileVar(name) ? findVolatileVar(name)->second : false);
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
                    builder->CreateStore(valueVal, typedPtr, hasVolatileVar(name) ? findVolatileVar(name)->second : false);

                    return;
                }
                llvm::Value* alloc = getVarAddress(name);
                if (!alloc) {
                    cg_error(get_pos(arrAcc->base), "unknown array: " + name);
                    return;
                }

                llvm::Value* arrAlloc = alloc;
                llvm::Type* arrTy = getPointeeType(name);

                llvm::Value* indexVal = emitExpr(arrAcc->indices[0]);
                if (!indexVal) return;

                llvm::Value* valueVal = emitExpr(arrAssign->value);
                if (!valueVal) return;
                if (arrTy->isPointerTy()) {
                    llvm::Value* ptr = builder->CreateLoad(arrTy, arrAlloc, hasVolatileVar(name) ? findVolatileVar(name)->second : false, "arr_ptr");
                    llvm::Type* elemTy = valueVal->getType();

                    llvm::Value* elemPtr = builder->CreateGEP(elemTy, ptr, indexVal, "arr_elem_ptr");

                    builder->CreateStore(valueVal, elemPtr, hasVolatileVar(name) ? findVolatileVar(name)->second : false);
                } else if (arrTy->isArrayTy()) {
                    std::vector<llvm::Value*> indices = {builder->getInt32(0), indexVal};
                    llvm::Value* elemPtr = builder->CreateInBoundsGEP(arrTy, arrAlloc, indices, "arr_elem_ptr");

                    builder->CreateStore(valueVal, elemPtr, hasVolatileVar(name) ? findVolatileVar(name)->second : false);
                }
            }
        }

        return;
    } else if (auto foreach = safe_get<ForeachNode>(node)) {
        std::string elemName = foreach->elem_name.value;
        std::string iterName = "__foreach_i_" + elemName;
        llvm::Value* lengthVal = nullptr;
        bool isArray = false;
        llvm::Value* arrayAlloc = nullptr;
        llvm::Type* arrayElemTy = nullptr;
        std::string collName = "";
        std::string collTypeName = "";
        llvm::Function* beginOverload = nullptr;
        llvm::Value* collVal;
        if (auto varAccess = std::get_if<VarAccessNode*>(&foreach->collection)) {
            collName = (*varAccess)->var_name_tok.value;
            collTypeName = resolveVarType(collName);
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
            beginOverload = findMethodOverload(collTypeName, "_begin", {});
            bool isIterator = !isArray && !collTypeName.empty() && beginOverload != nullptr;
            collVal = isIterator ? emitLValue(foreach->collection) : emitExpr(foreach->collection);
        } else {
            collVal = userTypes.find(baseTypeName(getExpressionType(foreach->collection))) == userTypes.end() ? emitExpr(foreach->collection)
                                                                                                              : emitLValue(foreach->collection);
            if (userTypes.find(baseTypeName(getExpressionType(foreach->collection))) != userTypes.end()) {
                if (userTypes[baseTypeName(getExpressionType(foreach->collection))].kind == UserTypeKind::Class) {
                    collTypeName = getExpressionType(foreach->collection);
                    isArray = false;
                }
            } else {
                if (collVal->getType()->isArrayTy()) {
                    collTypeName = getExpressionType(foreach->collection);
                    isArray = true;
                }
            }
        }
        beginOverload = findMethodOverload(collTypeName, "_begin", {});
        bool isIterator = !isArray && !collTypeName.empty() && beginOverload != nullptr;
        llvm::AllocaInst* iterObjAlloc = nullptr;
        std::string iterTypeName = "";
        llvm::Type* iterLLVMTy = nullptr;
        llvm::Value* iterLoaded = nullptr;
        if (!collVal) return;
        if (isIterator) {
            auto baseInfo = userTypes.find(baseTypeName(collTypeName));
            auto info = baseInfo->second;
            auto oldNamespaceStack = namespaceStack;
            namespaceStack.clear();

            if (!info.namespace_path.empty()) {
                size_t start = 0;
                size_t pos;

                while ((pos = info.namespace_path.find("::", start)) != std::string::npos) {
                    namespaceStack.push_back(info.namespace_path.substr(start, pos - start));
                    start = pos + 2;
                }

                namespaceStack.push_back(info.namespace_path.substr(start));
            }
            iterTypeName = resolveTypeName(getMethodReturnTypeName(collTypeName, "_begin"), false);
            auto concreteParams = genericParamsFromName(collTypeName);
            for (size_t i = 0; i < baseInfo->second.generics.size() && i < concreteParams.size(); i++) {
                std::string gname = baseInfo->second.generics[i].name;
                std::string gval = concreteParams[i];
                size_t pos;
                while ((pos = iterTypeName.find(gname)) != std::string::npos) iterTypeName.replace(pos, gname.size(), gval);
            }
            iterLLVMTy = llvmTypeFor(iterTypeName);
            iterObjAlloc = createEntryAlloca("__iter_" + elemName, iterLLVMTy);
            llvm::Value* iterObj = emitMethodCall(beginOverload, collVal, {}, "_begin");
            builder->CreateStore(iterObj, iterObjAlloc);
            namespaceStack = oldNamespaceStack;
        }
        enterScope();
        llvm::BasicBlock* savedBreakBB = currentBreakBB;
        llvm::BasicBlock* savedContinueBB = currentContinueBB;
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
        llvm::BasicBlock* incBB = nullptr;
        if (isArray) incBB = llvm::BasicBlock::Create(context, "foreach.inc", currentFunction);
        llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "foreach.end", currentFunction);
        if (isIterator)
            currentContinueBB = condBB;
        else
            currentContinueBB = incBB;
        if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(condBB); }
        builder->SetInsertPoint(condBB);
        if (isArray) {
            llvm::Value* iVal = builder->CreateLoad(builder->getInt32Ty(), iterAlloc, iterName);
            llvm::Value* cmpVal = builder->CreateICmpSLT(iVal, lengthVal, "foreach_cmp");
            builder->CreateCondBr(cmpVal, bodyBB, endBB);
        } else if (isIterator) {
            llvm::Function* atEndFn = findMethodOverload(iterTypeName, "_atEnd", {});
            llvm::Value* atEnd = emitMethodCall(atEndFn, iterObjAlloc, {}, "_atEnd");
            builder->CreateCondBr(atEnd, endBB, bodyBB);
        }

        builder->SetInsertPoint(bodyBB);
        currentBreakBB = endBB;
        llvm::Value* elemVal = nullptr;
        if (isArray && arrayAlloc) {
            llvm::Value* iVal = builder->CreateLoad(builder->getInt32Ty(), iterAlloc, iterName);
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
            builder->CreateStore(elemVal, elemAlloc);
            emitStmt(foreach->body);
            if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(incBB); }
            builder->SetInsertPoint(incBB);
            llvm::Value* iVal2 = builder->CreateLoad(builder->getInt32Ty(), iterAlloc, iterName);
            llvm::Value* incVal = builder->CreateAdd(iVal2, builder->getInt32(1), "i_inc");
            builder->CreateStore(incVal, iterAlloc);
            builder->CreateBr(condBB);
        } else if (isIterator) {
            iterLoaded = builder->CreateLoad(iterLLVMTy, iterObjAlloc);
            llvm::Function* nextFn = findMethodOverload(iterTypeName, "_next", {});
            llvm::Value* cur = emitMethodCall(nextFn, iterObjAlloc, {}, "_next");
            builder->CreateStore(cur, elemAlloc);
            emitStmt(foreach->body);
            if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(condBB); }
        }
        builder->SetInsertPoint(endBB);
        exitScope();
        locals.erase(iterName);
        locals.erase(elemName);
        currentBreakBB = savedBreakBB;
        currentContinueBB = savedContinueBB;
        return;
    } else if (auto stmts = safe_get<StatementsNode>(node)) {
        for (auto& stmt : stmts->statements) { emitStmt(stmt); }
        return;
    } else if (auto ns = safe_get<NamespaceNode>(node)) {
        namespaceStack.push_back(ns->name);
        for (auto& decl : ns->body) { emitStmt(decl); }
        namespaceStack.pop_back();

        return;
    } else if (auto trycatch = safe_get<TryCatchNode>(node)) {
        enterScope();
        auto* tryBB = llvm::BasicBlock::Create(context, "try.start", currentFunction);
        auto* landingPadBB = llvm::BasicBlock::Create(context, "catch.landing", currentFunction);
        auto* endBB = llvm::BasicBlock::Create(context, "try.end", currentFunction);
        std::vector<llvm::BasicBlock*> catchBlocks;
        catchBlocks.reserve(trycatch->catch_bodys.size());
        EHScope thisScope{
            .landingPad = landingPadBB,
            .continuation = endBB,
            .handlers = {},
        };
        for (size_t i = 0; i < trycatch->catch_bodys.size(); ++i) {
            auto* catchBB = llvm::BasicBlock::Create(context, "catch." + std::to_string(i), currentFunction);
            catchBlocks.push_back(catchBB);
            thisScope.handlers.push_back({
                .body = trycatch->catch_bodys[i],
                .block = catchBB,
            });
        }
        ehScopes.push_back(std::move(thisScope));
        builder->CreateBr(tryBB);
        builder->SetInsertPoint(tryBB);
        emitStmt(trycatch->try_body);
        if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(endBB); }
        builder->SetInsertPoint(landingPadBB);
        auto* exceptionType = llvm::StructType::get(context, {builder->getPtrTy(), builder->getInt32Ty()});
        std::vector<EHHandler> visibleHandlers;
        for (auto scopeIt = ehScopes.rbegin(); scopeIt != ehScopes.rend(); ++scopeIt) {
            for (const auto& handler : scopeIt->handlers) { visibleHandlers.push_back(handler); }
        }
        auto* lp = builder->CreateLandingPad(exceptionType, visibleHandlers.size(), "qc.exception");
        for (const auto& handler : visibleHandlers) {
            const auto& c = handler.body;
            llvm::Constant* typeInfo = c.var_type == "..." ? llvm::ConstantPointerNull::get(builder->getPtrTy()) : getStringConstant(c.var_type);
            lp->addClause(typeInfo);
        }
        if (!currentFunction->hasPersonalityFn()) { currentFunction->setPersonalityFn(module->getFunction("__qc_personality")); }
        auto* exception = builder->CreateExtractValue(lp, 0, "exception");
        auto* selector = builder->CreateExtractValue(lp, 1, "selector");
        auto* noMatchBB = llvm::BasicBlock::Create(context, "catch.no_match", currentFunction);
        auto* sw = builder->CreateSwitch(selector, noMatchBB, visibleHandlers.size());
        for (size_t i = 0; i < visibleHandlers.size(); ++i) {
            sw->addCase(llvm::ConstantInt::get(builder->getInt32Ty(), i + 1), visibleHandlers[i].block);
        }
        EHScope savedScope = std::move(ehScopes.back());
        ehScopes.pop_back();
        for (size_t i = 0; i < savedScope.handlers.size(); ++i) {
            const auto& c = savedScope.handlers[i].body;
            auto* catchBB = savedScope.handlers[i].block;
            builder->SetInsertPoint(catchBB);
            if (!c.var_name.empty()) {
                std::string name = getCurrentNamespace().empty() ? c.var_name : getCurrentNamespace() + c.var_name;
                auto* payloadPtr = builder->CreateStructGEP(exceptionType, exception, 1, "exception.value.ptr");
                auto* payload = builder->CreateLoad(builder->getPtrTy(), payloadPtr, "exception.value");
                auto* catchLLVMType = llvmTypeFor(c.var_type);
                auto* catchValue = builder->CreateLoad(catchLLVMType, payload, "caught.value");
                auto* alloc = createEntryAlloca(name, catchLLVMType);
                builder->CreateStore(catchValue, alloc);
                locals[name] = alloc;
            }
            emitStmt(c.body);
            if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(endBB); }
        }
        builder->SetInsertPoint(noMatchBB);
        builder->CreateResume(lp);
        exitScope();
        builder->SetInsertPoint(endBB);
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
    std::unordered_map<std::string, std::string> visibleArrayTypeStrings, std::unordered_map<std::string, int> visibleArrayLengths,
    std::unordered_map<std::string, std::string> visibleVarTypes, std::unordered_map<std::string, llvm::AllocaInst*> visibleRuntimeArraySizes,
    std::unordered_map<std::string, llvm::FunctionType*> visibleLambdaTypes, std::map<std::string, llvm::Function*> visibleSpecializedFunctions,
    std::unordered_map<std::string, llvm::GlobalVariable*> visibleGlobals) {
    this->volatileVarsStack = {{}};
    this->functionSignatures = visibleFunctionSignatures;
    this->functionDefs = visibleFunctionDefs;
    this->globals = visibleGlobals;
    this->varTypesStack = {visibleVarTypes};
    this->jaggedArraysStack = {visibleJaggedArrays};
    this->arrayTypeStringsStack = {visibleArrayTypeStrings};
    this->arrayLengthsStack = {visibleArrayLengths};
    this->runtimeArraySizes = visibleRuntimeArraySizes;
    this->lambdaTypes = visibleLambdaTypes;
    this->localsStack = {{}};
    for (auto& [className, info] : userTypes) {
        if (info.kind != UserTypeKind::Class) continue;
        for (size_t methodIdx = 0; methodIdx < info.classMethods.size(); methodIdx++) {
            auto& method = info.classMethods[methodIdx];
            if (!method.generics.empty() && !method.is_static) { genericMethodIndices[className].push_back(methodIdx); }
        }
    }
    createUserTypes();
    auto createGlobal = [&](VarAssignNode* va) {
        const bool foreign = va->is_foreign;
        std::string name = foreign || getCurrentNamespace().empty() ? va->var_name_tok.value : getCurrentNamespace() + "::" + va->var_name_tok.value;
        llvm::Type* ty = llvmTypeFor(va->type_tok.value);
        llvm::GlobalVariable* gv = module->getGlobalVariable(name);
        if (!gv) {
            llvm::Constant* initializer = foreign ? nullptr : llvm::Constant::getNullValue(ty);
            gv = new llvm::GlobalVariable(*module, ty, false, llvm::GlobalValue::ExternalLinkage, initializer, name);
        }
        globals[name] = gv;
        varTypes[name] = va->type_tok.value;
    };
    std::function<void(NamespaceNode&)> createGlobals = [&](NamespaceNode& ns) {
        namespaceStack.push_back(ns.name);
        for (auto& decl : ns.body) {
            if (auto va = std::get_if<VarAssignNode*>(&decl)) {
                createGlobal(*va);
            } else if (auto nested = std::get_if<NamespaceNode*>(&decl)) {
                createGlobals(**nested);
            }
        }
        namespaceStack.pop_back();
    };
    if (root)
        for (auto& stmt : root->statements) {
            if (auto ns = std::get_if<NamespaceNode*>(&stmt)) {
                createGlobals(**ns);
            } else if (auto va = std::get_if<VarAssignNode*>(&stmt)) {
                createGlobal(*va);
            }
        }
    std::function<void(NamespaceNode&)> scanGenericFunctions = [&](NamespaceNode& ns) {
        namespaceStack.push_back(ns.name);

        for (auto& decl : ns.body) {
            if (auto fn = safe_get<FuncDefNode>(decl)) {
                if (fn->name_tok.has_value()) {
                    std::string funcName = fn->name_tok.value().value;
                    std::string fullName = getCurrentNamespace() + "::" + funcName;
                    functionDefs[fullName] = fn;
                }
            } else if (auto nested = std::get_if<NamespaceNode*>(&decl)) {
                scanGenericFunctions(**nested);
            }
        }

        namespaceStack.pop_back();
    };

    if (root)
        for (auto& stmt : root->statements) {
            if (auto ns = std::get_if<NamespaceNode*>(&stmt)) {
                scanGenericFunctions(**ns);
            } else if (std::holds_alternative<FuncDefNode*>(stmt)) {
                auto fnPtr = std::get<FuncDefNode*>(stmt);
                if (!fnPtr->name_tok.has_value()) continue;
                std::string funcName = fnPtr->name_tok.value().value;
                if (funcName == entrypointName && !this->is_main) { continue; }
                functionDefs[funcName] = fnPtr;
            }
        }
    std::function<void(NamespaceNode&)> compileNamespaceFunctions = [&](NamespaceNode& ns) {
        namespaceStack.push_back(ns.name);

        for (auto& decl : ns.body) {
            if (auto fn = safe_get<FuncDefNode>(decl)) {
                if (fn->name_tok.has_value()) {
                    if (fn->name_tok.value().value == entrypointName && !this->is_main) { continue; }

                    if (fn->generics.empty()) { emitFuncDef(*fn); }
                }
            } else if (auto va = std::get_if<VarAssignNode*>(&decl)) {
                emitExpr(decl);
            } else if (auto nested = std::get_if<NamespaceNode*>(&decl)) {
                compileNamespaceFunctions(**nested);
            }
        }

        namespaceStack.pop_back();
    };

    if (root)
        for (auto& stmt : root->statements) {
            if (auto ns = std::get_if<NamespaceNode*>(&stmt)) {
                compileNamespaceFunctions(**ns);
            } else if (auto va = std::get_if<VarAssignNode*>(&stmt)) {
                emitExpr(stmt);
            } else if (std::holds_alternative<FuncDefNode*>(stmt)) {
                auto fnPtr = std::get<FuncDefNode*>(stmt);
                if (!fnPtr->name_tok.has_value()) continue;
                if (fnPtr->name_tok.value().value == entrypointName && !this->is_main) { continue; }
                if (fnPtr->generics.empty()) { emitFuncDef(*fnPtr); }
            }
        }
    for (auto& [className, info] : userTypes) {
        if (info.kind != UserTypeKind::Class || !info.generics.empty()) continue;
        for (auto& method : info.classMethods) {
            if (!method.is_static || !method.generics.empty()) continue;
            std::string mangledName = className + "::" + method.name_tok.value;
            if (functionDefs.count(mangledName)) { emitFuncDef(*functionDefs[mangledName]); }
        }
    }
    for (auto& [className, info] : userTypes) {
        if (info.kind != UserTypeKind::Class || !info.generics.empty()) continue;

        auto oldNamespaceStack = namespaceStack;
        namespaceStack.clear();

        if (!info.namespace_path.empty()) {
            size_t start = 0;
            size_t pos;

            while ((pos = info.namespace_path.find("::", start)) != std::string::npos) {
                namespaceStack.push_back(info.namespace_path.substr(start, pos - start));
                start = pos + 2;
            }

            namespaceStack.push_back(info.namespace_path.substr(start));
        }
        for (size_t methodIdx = 0; methodIdx < info.classMethods.size(); methodIdx++) {
            auto& method = info.classMethods[methodIdx];
            if (std::find(genericMethodIndices[className].begin(), genericMethodIndices[className].end(), methodIdx) !=
                genericMethodIndices[className].end()) {
                continue;
            }
            if (!method.generics.empty()) continue;
            llvm::Function* fn = nullptr;
            auto& overloads = classMethods[className][method.name_tok.value];
            bool isStatic = method.is_static;
            size_t expectedParamOffset = isStatic ? 0 : 1;
            for (auto* overload : overloads) {
                if (overload->arg_size() - expectedParamOffset == method.params.size()) {
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
                        llvm::Type* actualType = overload->getFunctionType()->getParamType(i + expectedParamOffset);
                        if (expectedType != actualType && param.type.value != "...") {
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
            if (isHeader || info.baseFile.ends_with(".hqc")) continue;
            llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", fn);
            builder->SetInsertPoint(entry);
            auto oldThis = currentThis;
            auto oldClassName = currentClassName;
            auto oldFunction = currentFunction;
            enterScope();
            if (!isStatic) {
                currentThis = fn->getArg(0);
                varTypes["this"] = className;
            } else {
                currentThis = nullptr;
            }
            currentClassName = className;
            currentFunction = fn;
            for (size_t i = 0; i < method.params.size(); i++) {
                auto& param = method.params[i];
                llvm::Type* paramTy;
                std::string typeDescriptor;
                if (param.signature.has_value()) {
                    paramTy = llvm::PointerType::get(context, 0);
                    typeDescriptor = "fn";
                    lambdaTypes[param.name.value] = llvmFuncTypeFor(param.signature->return_types, param.signature->params);
                } else {
                    typeDescriptor = resolveTypeName(param.type.value);
                    paramTy = llvmTypeFor(typeDescriptor);
                }
                llvm::AllocaInst* alloc = createEntryAlloca(param.name.value, paramTy);
                llvm::Value* argVal = fn->getArg(i + expectedParamOffset);
                builder->CreateStore(argVal, alloc);
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
                                    if (insideTry()) {
                                        auto contBB = llvm::BasicBlock::Create(context, "invoke.cont." + std::to_string(invokeCounter++),
                                                                               currentFunction);
                                        llvm::InvokeInst* invoke = builder->CreateInvoke(parentCtor, contBB, currentLandingPad(), allArgs);
                                        builder->SetInsertPoint(contBB);
                                    } else {
                                        builder->CreateCall(parentCtor, allArgs);
                                    }
                                    bodyStartIdx = 1;
                                } else {
                                    cg_error(get_pos(*call), "parent class '" + info.baseClassName + "' has no matching constructor");
                                    addConstructorNotes(info.baseClassName, parentArgs, get_pos(*call));
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
            exitScope();
        }
        namespaceStack = oldNamespaceStack;
    }
    currentFunction = nullptr;
    if (this->is_main) {
        if (!no_main) {
            llvm::Function* userEntry = module->getFunction(entrypointName);
            if (userEntry) {
                userEntry->setName("__user_entry");
                llvm::FunctionType* mainTy = llvm::FunctionType::get(builder->getInt32Ty(), {}, false);
                if (main_type != MainType::NA) {
                    mainTy = llvm::FunctionType::get(builder->getInt32Ty(), {builder->getInt32Ty(), builder->getPtrTy()}, false);
                }
                llvm::Function* realMain = llvm::Function::Create(mainTy, llvm::Function::ExternalLinkage, "main", module);
                llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", realMain);
                builder->SetInsertPoint(entry);
                currentFunction = realMain;
                std::vector<llvm::Value*> user_entry_args;
                for (llvm::Argument& arg : realMain->args()) { user_entry_args.push_back(&arg); }
                if (main_type == MainType::RT_ARRAY) {
                    llvm::Value* argc = realMain->getArg(0);
                    llvm::AllocaInst* argcSlot = builder->CreateAlloca(builder->getInt32Ty(), nullptr, "argc.addr");
                    builder->CreateStore(argc, argcSlot);
                    user_entry_args = {realMain->getArg(1)};
                    arrayTypeStrings[functionDefs[entrypointName]->params.back().name.value] = "string";
                    runtimeArraySizes[functionDefs[entrypointName]->params.back().name.value] = argcSlot;
                }
                llvm::Value* result = builder->CreateCall(userEntry, user_entry_args, "entry_result");
                builder->CreateRet(result);
            } else {
                cg_error(Position("", "", 0, 0, 0), "entrypoint function '" + entrypointName + "' not defined");
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
int emitObjectFile(llvm::Module& M, const std::string& outputPath, bool debug, std::string tgt = "") {
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
    if (TM->addPassesToEmitFile(PM, dest, nullptr, llvm::CodeGenFileType::ObjectFile)) {
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
    llvm::Triple triple(tgt.empty() ? llvm::sys::getDefaultTargetTriple() : tgt);
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
    aliases = config.aliases;
    dir_aliases = config.dir_aliases;
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
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> file_namespace_deps;
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
            file_namespace_deps[current_file] = outputofdeps.namespace_depends;
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
            std::unordered_set<std::string> widened_ns(ns_list.begin(), ns_list.end());
            std::vector<std::string> worklist(ns_list.begin(), ns_list.end());
            while (!worklist.empty()) {
                std::string ns = worklist.back();
                worklist.pop_back();
                if (file_namespace_deps.count(dep_path) && file_namespace_deps[dep_path].count(ns)) {
                    for (const std::string& needed_ns : file_namespace_deps[dep_path][ns]) {
                        if (widened_ns.insert(needed_ns).second) { worklist.push_back(needed_ns); }
                    }
                }
            }
            for (const std::string& ns : widened_ns) {
                for (auto& [type_name, info] : dep_types) {
                    if (type_name.rfind(ns + "::", 0) == 0) { visible_types[type_name] = info; }
                }
            }
        }
        Ler file_resp;
        try {
            Lexer lexer(cleaned_files[path], path);
            file_resp = lexer.make_tokens();
            if (config.dump_tokens && file == path && file_resp.error != nullptr) {
                std::cout << "\n##DUMP##" << '\n'
                          << "ERROR: " << file_resp.error->pos.line << " " << file_resp.error->pos.column << " " << file_resp.error->pos.length << " "
                          << file_resp.error->details << '\n'
                          << "########" << '\n';
                return;
            }
        } catch (IllegalCharError e) {
            if (config.dump_tokens) {
                std::cout << "\n##DUMP##" << '\n'
                          << e.pos.line << " " << e.pos.column << " " << e.pos.length << " " << e.details << '\n'
                          << "########" << '\n';
                return;
            } else {
                throw e;
            }
        }
        if (config.dump_tokens && file == path) {
            std::cout << "\n##DUMP##" << '\n';
            for (const auto& tok : file_resp.Tkns) {
                std::cout << tok.pos.line << " " << tok.pos.column << " " << tok.pos.length << " " << get_token_name(tok.type) << '\n';
            }
            std::cout << "########" << '\n';
            return;
        }
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
        if (config.dump_tokens) { return Mer{Aer{nullptr, nullptr}, Ler{std::vector<Token>(), nullptr}, ""}; }
    } catch (InvalidSyntaxError& e) {
        std::cout << '\n' << e.as_string() << '\n';
        return Mer{Aer{nullptr, nullptr}, resp, ""};
    }
    Aer ast = file_asts[file];
    if (config.print_tokens) {
        std::cout << "=== TOKENS ===" << '\n';
        for (const auto& tok : resp.Tkns) { std::cout << "Type: " << get_token_name(tok.type) << " | Value: '" << tok.value << "'" << '\n'; }
        std::cout << "==============" << '\n' << '\n';
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
#ifdef __EMSCRIPTEN__
            llvm::InitializeAllTargets();
            llvm::InitializeAllTargetMCs();

            llvm::Triple triple("wasm32-unknown-unknown");
            master_module->setTargetTriple(triple);

            std::string target_err;
            const llvm::Target* target = llvm::TargetRegistry::lookupTarget(triple, target_err);
            if (target) {
                llvm::TargetOptions opt;
                auto RM = llvm::Reloc::PIC_;
                llvm::TargetMachine* TM = target->createTargetMachine(triple, "generic", "", opt, RM);
                master_module->setDataLayout(TM->createDataLayout());
                delete TM;
            }
#else
            llvm::InitializeAllTargets();
            llvm::InitializeAllTargetMCs();

            llvm::Triple triple(config.target.empty() ? llvm::sys::getDefaultTargetTriple() : config.target);
            master_module->setTargetTriple(triple);

            std::string target_err;
            const llvm::Target* target = llvm::TargetRegistry::lookupTarget(triple, target_err);
            if (target) {
                llvm::TargetOptions opt;
                auto RM = llvm::Reloc::PIC_;
                llvm::TargetMachine* TM = target->createTargetMachine(triple, "generic", "", opt, RM);
                master_module->setDataLayout(TM->createDataLayout());
                delete TM;
            }
#endif
            if (config.use_runtime) {
                llvm::StringRef irString(_binary_runtime_ll_start, _binary_runtime_ll_size);
                llvm::SMDiagnostic err;
                llvm::MemoryBufferRef bufRef(irString, "runtime.ll");
                auto modulePtr = llvm::parseIR(bufRef, err, context);
                if (!modulePtr) {
                    err.print("runtime.ll", llvm::errs());
                    throw "Failed to load runtime.ll";
                }
                if (llvm::Linker::linkModules(*master_module, std::move(modulePtr))) { throw "Failed to link runtime module"; }
            }
            std::unordered_map<std::string, std::unordered_map<std::string, FunctionSignature>> db_sigs;
            std::unordered_map<std::string, std::unordered_map<std::string, FuncDefNode*>> db_fDefs;
            std::unordered_map<std::string, std::unordered_map<std::string, std::pair<int, int>>> db_jagged;
            std::unordered_map<std::string, std::unordered_map<std::string, std::string>> db_typeStrings;
            std::unordered_map<std::string, std::unordered_map<std::string, int>> db_lengths;
            std::unordered_map<std::string, std::unordered_map<std::string, std::string>> db_vars;
            std::unordered_map<std::string, std::unordered_map<std::string, llvm::AllocaInst*>> db_allocas;
            std::unordered_map<std::string, std::unordered_map<std::string, llvm::FunctionType*>> db_lambdas;
            std::unordered_map<std::string, std::unordered_map<std::string, llvm::GlobalVariable*>> db_globals;
            std::unordered_map<std::string, std::map<std::string, llvm::Function*>> db_specialized;
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
                std::unordered_map<std::string, int> visLen;
                std::unordered_map<std::string, std::string> visVars;
                std::unordered_map<std::string, llvm::AllocaInst*> visAlloc;
                std::unordered_map<std::string, llvm::GlobalVariable*> visGlobals;
                std::unordered_map<std::string, llvm::FunctionType*> visLamb;
                std::map<std::string, llvm::Function*> visSpec;
                for (auto const& [dep_p, ns_list] : file_included_namespaces[filepath]) {
                    if (db_sigs.find(dep_p) == db_sigs.end()) continue;
                    for (const std::string& ns : ns_list) {
                        if (ns.empty()) continue;
                        auto pre = ns + "::";
                        auto& d_sigs = db_sigs.at(dep_p);
                        auto& d_fDefs = db_fDefs.at(dep_p);
                        auto& d_jagged = db_jagged.at(dep_p);
                        auto& d_typeStr = db_typeStrings.at(dep_p);
                        auto& d_len = db_lengths.at(dep_p);
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
                        for (auto const& [k, v] : d_len)
                            if (k.rfind(pre, 0) == 0) visLen[k] = v;
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
                isHeader = std::filesystem::path(filepath).extension() == ".hqc";
                LLVMCompiler comp(file_asts[filepath].user_types, master_module, context, filepath == file);
                comp.config = config;
                std::vector<CTError> errs = comp.compile(file_asts[filepath].statements, visSigs, visFDefs, visJagged, visTypeStr, visLen, visVars,
                                                         visAlloc, visLamb, visSpec, visGlobals);
                if (!errs.empty()) {
                    for (auto& err : errs)
                        diagnostics.push_back(
                            {new CTError(err.details, err.pos, err.is_warning, err.error_name, err.notes), err.is_warning ? "Warning" : "Error"});
                    break;
                }
                db_sigs[filepath] = comp.functionSignatures;
                db_fDefs[filepath] = comp.functionDefs;
                db_jagged[filepath] = comp.jaggedArraysStack[0];
                db_typeStrings[filepath] = comp.arrayTypeStringsStack[0];
                db_lengths[filepath] = comp.arrayLengthsStack[0];
                db_vars[filepath] = comp.varTypesStack[0];
                db_allocas[filepath] = comp.runtimeArraySizes;
                db_lambdas[filepath] = comp.lambdaTypes;
                db_specialized[filepath] = comp.specializedFunctions;
                db_globals[filepath] = comp.globals;
            }
            for (Diagnostic& diagnostic : diagnostics) {
                if (diagnostic.level != "Warning") { return Mer{ast, resp, "Program exited with code: 1", diagnostics}; }
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
            if (config.use_runtime) {
                for (llvm::Function& F : master_module->functions()) {
                    if (F.getName().starts_with("qc_") || F.getName().starts_with("__qc_") || F.getName().starts_with("_qc_")) {
                        F.setLinkage(llvm::GlobalValue::InternalLinkage);
                    }
                }
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
            int llc_result = emitObjectFile(*master_module, obj_file, config.debug, config.target);
            if (llc_result != 0) {
                diagnostics.push_back({new CTError("Failed to compile IR to object file", Position("", "", 0, 0, 0))});
                return Mer{ast, resp, message, diagnostics};
            }
            if (config.object_only) {
                std::remove(ll_file.c_str());
                message += ". Compiled to " + obj_file;
                return Mer{ast, resp, message, diagnostics};
            }
            std::string final_exe = config.output_file.empty() ? "a.out" : config.output_file;
            std::string link_cmd = "gcc " + obj_file + " -o " + final_exe;
            for (const auto& path : to_link_dir) { link_cmd += " -L\"" + path + "\""; }
            for (const auto& lib : to_link) {
                if (lib.ends_with(".a") || lib.ends_with(".so") || lib.ends_with(".dylib")) {
                    link_cmd += " \"" + lib + "\"";
                } else {
                    link_cmd += " -l" + lib;
                }
            }
            for (const auto& path : config.library_search_paths) { link_cmd += " -L\"" + path + "\""; }
            for (const auto& lib : config.libraries) {
                if (lib.ends_with(".a") || lib.ends_with(".so") || lib.ends_with(".dylib")) {
                    link_cmd += " \"" + lib + "\"";
                } else {
                    link_cmd += " -l" + lib;
                }
            }
            for (const std::string& arg : config.link_with) { link_cmd += " " + arg; }
            link_cmd += " -lm";
            if (config.debug) link_cmd += " -g";
            if (!config.quiet_mode) std::cout << "Linking with command " + link_cmd << '\n';
            int link_result = system(link_cmd.c_str());
            if (link_result != 0) {
                diagnostics.push_back({new CTError("Failed to link object file", Position("", "", 0, 0, 0))});
                return Mer{ast, resp, message, diagnostics};
            }
            std::remove(ll_file.c_str());
            std::remove(obj_file.c_str());

            message += ". Built executable: " + final_exe;
            if (config.quiet_mode) message = "";
            return Mer{ast, resp, message, diagnostics};
        }
#endif
    } catch (const char* err) { std::cout << err << '\n'; } catch (const std::exception& e) {
        std::cout << "std::exception: " << e.what() << '\n';
    } catch (...) { std::cout << "unknown error\n"; }
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
    bool is_long = false;
    bool is_short = false;
    bool is_hex = false;
    bool is_addrt = false;
    bool is_byte = false;
    bool is_nibble = false;
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
        while (this->current_char != '\0' && isCharInSet(this->current_char, DIGITS + "abcdefABCDEF'")) {
            if (this->current_char == '\'') { this->advance(); }
            num += this->current_char;
            this->advance();
        }
        size_t val = std::stoull(num, nullptr, 16);
        if (this->current_char == 'l') {
            this->advance();
            return Token(TokenType::LONG_INT, std::to_string(val), start_pos);
        } else if (this->current_char == 'i') {
            this->advance();
            return Token(TokenType::INT, std::to_string(val), start_pos);
        } else if (this->current_char == 's') {
            this->advance();
            return Token(TokenType::SHORT_INT, std::to_string(val), start_pos);
        } else if (this->current_char == 'b') {
            this->advance();
            return Token(TokenType::BYTE, std::to_string(val), start_pos);
        } else if (this->current_char == 'n') {
            this->advance();
            return Token(TokenType::NIBBLE, std::to_string(val), start_pos);
        }
        return Token(TokenType::ADDR_T, std::to_string(val), start_pos);
    } else if (is_octal) {
        while (this->current_char != '\0' && ((std::isdigit(this->current_char) && this->current_char - '0' < 8) || this->current_char == '\'')) {
            if (this->current_char == '\'') { this->advance(); }
            num += this->current_char;
            this->advance();
        }
        size_t val = std::stoull(num, nullptr, 8);
        if (this->current_char == 'l') {
            this->advance();
            return Token(TokenType::LONG_INT, std::to_string(val), start_pos);
        } else if (this->current_char == 'i') {
            this->advance();
            return Token(TokenType::INT, std::to_string(val), start_pos);
        } else if (this->current_char == 's') {
            this->advance();
            return Token(TokenType::SHORT_INT, std::to_string(val), start_pos);
        } else if (this->current_char == 'b') {
            this->advance();
            return Token(TokenType::BYTE, std::to_string(val), start_pos);
        } else if (this->current_char == 'n') {
            this->advance();
            return Token(TokenType::NIBBLE, std::to_string(val), start_pos);
        }
        return Token(TokenType::ADDR_T, std::to_string(val), start_pos);
    } else if (is_binary) {
        while (this->current_char != '\0' && ((std::isdigit(this->current_char) && this->current_char - '0' < 2) || this->current_char == '\'')) {
            if (this->current_char == '\'') { this->advance(); }
            num += this->current_char;
            this->advance();
        }
        size_t val = std::stoull(num, nullptr, 2);
        if (this->current_char == 'l') {
            this->advance();
            return Token(TokenType::LONG_INT, std::to_string(val), start_pos);
        } else if (this->current_char == 'i') {
            this->advance();
            return Token(TokenType::INT, std::to_string(val), start_pos);
        } else if (this->current_char == 's') {
            this->advance();
            return Token(TokenType::SHORT_INT, std::to_string(val), start_pos);
        } else if (this->current_char == 'b') {
            this->advance();
            return Token(TokenType::BYTE, std::to_string(val), start_pos);
        } else if (this->current_char == 'n') {
            this->advance();
            return Token(TokenType::NIBBLE, std::to_string(val), start_pos);
        }
        return Token(TokenType::ADDR_T, std::to_string(val), start_pos);
    } else {
        while (this->current_char != '\0' && isCharInSet(this->current_char, DIGITS + ".flsabn'")) {
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
            } else if (this->current_char == 'l') {
                is_long = true;
                this->advance();
                break;
            } else if (this->current_char == 's') {
                is_short = true;
                this->advance();
                break;
            } else if (this->current_char == 'a') {
                is_addrt = true;
                this->advance();
                break;
            } else if (this->current_char == 'b') {
                this->advance();
                is_byte = true;
                break;
            } else if (this->current_char == 'n') {
                this->advance();
                is_nibble = true;
                break;
            } else if (this->current_char == '\'') {
                if (num.empty() || !std::isdigit(static_cast<unsigned char>(this->text[this->pos.index + 1]))) {
                    throw new InvalidSyntaxError("QC-IC03: ' delimiter must appear between digits", start_pos);
                }
                this->advance();
            } else {
                num += this->current_char;
                this->advance();
            }
        }
    }
    if (dot_count == 1) {
        if (is_float) { return Token(TokenType::FLOAT, num, start_pos); }
        if (is_long) return Token(TokenType::LONG_DOUBLE, num, start_pos);
        return Token(TokenType::DOUBLE, num, start_pos);
    }
    if (is_byte) return Token(TokenType::BYTE, num, start_pos);
    if (is_nibble) return Token(TokenType::NIBBLE, num, start_pos);
    if (is_addrt) return Token(TokenType::ADDR_T, num, start_pos);
    if (is_long) return Token(TokenType::LONG_INT, num, start_pos);
    if (is_short) return Token(TokenType::SHORT_INT, num, start_pos);
    return Token(TokenType::INT, num, start_pos);
}
Token Lexer::make_identifier() {
    std::string id = "";
    Position start_pos = this->pos.copy();
    while (this->current_char != '\0' && (isalnum(this->current_char) || this->current_char == '_' || this->current_char == '`')) {
        id += this->current_char;
        this->advance();
    }
    if (id == "int" || id == "float" || id == "double" || id == "bool" || id == "case" || id == "string" || id == "qbool" || id == "void" ||
        id == "char" || id == "break" || id == "if" || id == "else" || id == "while" || id == "for" || id == "switch" || id == "return" ||
        id == "qif" || id == "qelse" || id == "qelif" || id == "qswitch" || id == "const" || id == "default" || id == "class" || id == "struct" ||
        id == "enum" || id == "long" || id == "short" || id == "fn" || id == "continue" || id == "auto" || id == "foreach" || id == "do" ||
        id == "in" || id == "type" || id == "foreign" || id == "public" || id == "protected" || id == "private" || id == "extern" ||
        id == "function" || id == "namespace" || id == "roperator" || id == "operator" || id == "abstract" || id == "final" || id == "try" ||
        id == "catch" || id == "nullptr" || id == "addr_t" || id == "out" || id == "inout" || id == "volatile" || id == "restrict" || id == "byte" ||
        id == "nibble" || id == "friend" || id == "friendly" || id == "static") {
        return Token(TokenType::KEYWORD, id, start_pos);
    }
    if (id == "true" || id == "false") { return Token(TokenType::BOOL, id, start_pos); }
    if (id == "qtrue" || id == "qfalse" || id == "both" || id == "none") { return Token(TokenType::QBOOL, id, start_pos); }
    if (id == "sizeof") { return Token(TokenType::SIZEOF, id, start_pos); }
    if (id == "throw") { return Token(TokenType::THROW, id, start_pos); }
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
            case 'a': str += '\a'; break;
            case 'b': str += '\b'; break;
            case 't': str += '\t'; break;
            case 'n': str += '\n'; break;
            case 'v': str += '\v'; break;
            case 'f': str += '\f'; break;
            case 'r': str += '\r'; break;
            case 'e': str += '\x1B'; break;
            case '\\': str += '\\'; break;
            case '"': str += '"'; break;
            case 'x': {
                escape_character = false;
                this->advance();
                if (!std::isxdigit(static_cast<unsigned char>(this->current_char))) {
                    throw IllegalCharError("QC-IC02: Expected hex digit after \\x", this->pos);
                }
                std::string hex = "";
                while (std::isxdigit(this->current_char) && hex.size() < 2) {
                    hex += this->current_char;
                    this->advance();
                }
                if (hex.size() != 2) { throw IllegalCharError("QC-IC02: Expected two hex digits after \\x", this->pos); }

                str += static_cast<char>(std::stoi(hex, nullptr, 16));
                continue;
            }
            default:
                if (this->current_char >= '0' && this->current_char <= '7') {
                    escape_character = false;
                    std::string octal;
                    for (int i = 0; i < 3 && this->current_char >= '0' && this->current_char <= '7'; ++i) {
                        octal += this->current_char;
                        this->advance();
                    }
                    str += static_cast<char>(std::stoi(octal, nullptr, 8));
                    continue;
                }
                str += this->current_char;
                break;
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
    bool already_advanced = false;
    std::string val = "";
    if (this->current_char == '\\') {
        this->advance();
        switch (this->current_char) {
        case 'e': val = std::string(1, '\x1B'); break;
        case 'a': val = std::string(1, '\a'); break;
        case 'b': val = std::string(1, '\b'); break;
        case 't': val = std::string(1, '\t'); break;
        case 'n': val = std::string(1, '\n'); break;
        case 'v': val = std::string(1, '\v'); break;
        case 'f': val = std::string(1, '\f'); break;
        case 'r': val = std::string(1, '\r'); break;
        case '\\': val = std::string(1, '\\'); break;
        case '\'': val = std::string(1, '\''); break;
        case '"': val = std::string(1, '"'); break;
        case 'x': {
            this->advance();
            std::string hex;

            for (int i = 0; i < 2; ++i) {
                if (!std::isxdigit(static_cast<unsigned char>(this->current_char))) {
                    throw IllegalCharError("QC-IC01: Invalid hex escape", this->pos);
                }

                hex += this->current_char;
                this->advance();
            }

            val = std::string(1, static_cast<char>(std::stoi(hex, nullptr, 16)));
            already_advanced = true;
            break;
        }
        default:
            if (this->current_char >= '0' && this->current_char <= '7') {
                std::string octal;
                for (int i = 0; i < 3 && this->current_char >= '0' && this->current_char <= '7'; ++i) {
                    octal += this->current_char;
                    this->advance();
                }
                already_advanced = true;
                val = std::string(1, static_cast<char>(std::stoi(octal, nullptr, 8)));
            } else {
                val = std::string(1, this->current_char);
                break;
            }
        }
        if (!already_advanced) this->advance();
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
            case 'e': current += '\x1B'; break;
            case 'a': current += '\a'; break;
            case 'b': current += '\b'; break;
            case 't': current += '\t'; break;
            case 'n': current += '\n'; break;
            case 'v': current += '\v'; break;
            case 'f': current += '\f'; break;
            case 'r': current += '\r'; break;
            case '\\': current += '\\'; break;
            case '"': current += '"'; break;
            case 'x': {
                escape = false;
                this->advance();
                if (!std::isxdigit(this->current_char)) { throw IllegalCharError("QC-IC02: Expected hex digit after \\x", this->pos); }
                std::string hex = "";
                while (std::isxdigit(this->current_char) && hex.size() < 2) {
                    hex += this->current_char;
                    this->advance();
                }
                if (hex.size() != 2) { throw IllegalCharError("QC-IC02: Expected two hex digits after \\x", this->pos); }
                current += static_cast<char>(std::stoi(hex, nullptr, 16));
                continue;
            }
            default:
                escape = false;
                if (this->current_char >= '0' && this->current_char <= '7') {
                    std::string octal;
                    for (int i = 0; i < 3 && this->current_char >= '0' && this->current_char <= '7'; ++i) {
                        octal += this->current_char;
                        this->advance();
                    }
                    current += static_cast<char>(std::stoi(octal, nullptr, 8));
                    continue;
                }
                current += this->current_char;
                break;
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
        } else if (isCharInSet(this->current_char, LETTERS + "_`")) {
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
                        if (this->current_char == '=') {
                            this->advance();
                            tokens.push_back(Token(TokenType::LROT_EQ, "<<<=", start_pos));
                            break;
                        }
                        tokens.push_back(Token(TokenType::L_ROT, "<<<", start_pos));
                    } else {
                        if (this->current_char == '=') {
                            this->advance();
                            tokens.push_back(Token(TokenType::LSH_EQ, "<<=", start_pos));
                            break;
                        }
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
                    if (this->current_char == '=') {
                        this->advance();
                        tokens.push_back(Token(TokenType::BIT_A_EQ, "&=", start_pos));
                        break;
                    }
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
                } else if (this->current_char == '>') {
                    this->advance();
                    if (this->current_char == '>') {
                        this->advance();
                        if (this->current_char == '=') {
                            this->advance();
                            tokens.push_back(Token(TokenType::RROT_EQ, "|>>=", start_pos));
                            break;
                        }
                        tokens.push_back(Token(TokenType::R_ROT, "|>>", start_pos));
                    } else {
                        if (this->current_char == '=') {
                            this->advance();
                            tokens.push_back(Token(TokenType::RSH_EQ, "|>=", start_pos));
                            break;
                        }
                        tokens.push_back(Token(TokenType::RSHIFT, "|>", start_pos));
                    }
                } else {
                    if (this->current_char == '=') {
                        this->advance();
                        tokens.push_back(Token(TokenType::BIT_O_EQ, "|=", start_pos));
                        break;
                    }
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
                    if (this->current_char == '=') {
                        this->advance();
                        tokens.push_back(Token(TokenType::LRSH_EQ, ":>=", start_pos));
                        break;
                    }
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
                this->advance();
                if (this->current_char == '=') {
                    this->advance();
                    tokens.push_back(Token(TokenType::BIT_X_EQ, "$=", start_pos));
                    break;
                }
                tokens.push_back(Token(TokenType::BITWISE_XOR, "$", start_pos));
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
    std::unordered_map<std::string, std::vector<std::string>> namespace_depends;
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
    while ((pos = source.find("#link", pos)) != std::string::npos) {
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
        std::vector<std::string> file_paths = {};
        size_t item_start = 0;
        pos = end + 1;
        while (item_start <= directive.size()) {
            size_t comma = directive.find(',', item_start);
            std::string path = trim(directive.substr(item_start, comma == std::string::npos ? std::string::npos : comma - item_start));
            if (!path.empty()) {
                if (path.front() == '"') path.erase(0, 1);
                if (!path.empty() && path.back() == '"') path.pop_back();
                std::string full_path;
                size_t slash = path.find('/');
                std::string alias = path.substr(0, slash);
                bool looks_like_path = path.find('/') != std::string::npos || path.find('\\') != std::string::npos || path.starts_with(".") ||
                                       std::filesystem::path(path).has_extension();
                if (aliases.contains(path)) {
                    full_path = resolve_path(current_file, aliases[path]);
                } else if (dir_aliases.contains(alias)) {
                    std::string rest = slash == std::string::npos ? "" : path.substr(slash + 1);
                    full_path = resolve_path(current_file, (std::filesystem::path(dir_aliases[alias]) / rest).string());
                } else if (looks_like_path) {
                    full_path = resolve_path(current_file, path);
                } else {
                    full_path = path;
                }
                to_link.push_back(full_path);
            }

            if (comma == std::string::npos) break;
            item_start = comma + 1;
        }
    }
    pos = 0;
    while ((pos = source.find("#searchdir", pos)) != std::string::npos) {
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
        std::vector<std::string> file_paths = {};
        size_t item_start = 0;
        pos = end + 1;
        while (item_start <= directive.size()) {
            size_t comma = directive.find(',', item_start);
            std::string path = trim(directive.substr(item_start, comma == std::string::npos ? std::string::npos : comma - item_start));
            if (!path.empty()) {
                if (path.front() == '"') path.erase(0, 1);
                if (!path.empty() && path.back() == '"') path.pop_back();
                std::string full_path;
                size_t slash = path.find('/');
                std::string alias = path.substr(0, slash);
                if (aliases.contains(path)) {
                    full_path = resolve_path(current_file, aliases[path]);
                } else if (dir_aliases.contains(alias)) {
                    std::string rest = slash == std::string::npos ? "" : path.substr(slash + 1);

                    full_path = resolve_path(current_file, (std::filesystem::path(dir_aliases[alias]) / rest).string());
                } else {
                    full_path = resolve_path(current_file, path);
                }
                to_link_dir.push_back(full_path);
            }

            if (comma == std::string::npos) break;
            item_start = comma + 1;
        }
    }
    pos = 0;
    while ((pos = source.find("#depends", pos)) != std::string::npos) {
        bool in_string = false;
        for (size_t check = 0; check < pos; check++) {
            if (source[check] == '"' && (check == 0 || source[check - 1] != '\\')) { in_string = !in_string; }
        }
        if (in_string) {
            pos++;
            continue;
        }
        size_t start = source.find('(', pos);
        size_t end = source.find(')', start);
        if (start == std::string::npos || end == std::string::npos) {
            throw std::runtime_error("malformed #depends directive: expected #depends(<namespace>: <deps...>)");
        }
        std::string directive = source.substr(start + 1, end - start - 1);

        size_t colon = directive.find(':');
        if (colon == std::string::npos) { throw std::runtime_error("malformed #depends directive: missing ':' separator"); }
        std::string owner_ns = trim(directive.substr(0, colon));
        std::string rest = directive.substr(colon + 1);
        size_t segment_start = 0;
        size_t comma = rest.find(',', segment_start);
        while (comma != std::string::npos) {
            namespace_depends[owner_ns].push_back(trim(rest.substr(segment_start, comma - segment_start)));
            segment_start = comma + 1;
            comma = rest.find(',', segment_start);
        }
        namespace_depends[owner_ns].push_back(trim(rest.substr(segment_start)));

        pos = end + 1;
    }
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
        auto slash = path.find('/');
        std::string alias = path.substr(0, slash);
        if (path == "std") {
            const char* home = std::getenv("QC_STDLIB");
            if (!home) { throw std::runtime_error("QC_STDLIB environment variable not set"); }
            full_path = std::string(home);
        } else if (aliases.count(path)) {
            full_path = resolve_path(current_file, aliases[path]);
        } else if (dir_aliases.count(alias)) {
            std::string rest = slash == std::string::npos ? "" : path.substr(slash);
            full_path = resolve_path(current_file, (std::filesystem::path(dir_aliases[alias]) / rest.substr(1)).string());
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
    while ((pos = result.find("#link", pos)) != std::string::npos) {
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
    while ((pos = result.find("#searchdir", pos)) != std::string::npos) {
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
    while ((pos = result.find("#depends", pos)) != std::string::npos) {
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
    res.namespace_depends = namespace_depends;
    return res;
}
