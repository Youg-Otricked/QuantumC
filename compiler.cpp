
//////////////////////////////////////////////////////////////////////////////////////////////
// TOKENS ///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
#include "compiler.h"
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
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <climits>  
#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include <ranges>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <set>
#include <algorithm>
#include <iomanip>
#ifdef ENABLE_LLVM
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/IR/IntrinsicInst.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/Mangler.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h> 
#include <llvm/Linker/Linker.h>            
#endif
#if defined(_WIN32) || defined(_WIN64)
    #include <print>
#endif
static bool random_seeded = false;
bool isCharInSet(char c, const std::string &charSet) {
    return charSet.find(c) != std::string::npos;
}
std::string strip_brace(const std::string& s) {
    std::string r = s;
    while(r.size()>=2 && r.substr(r.size()-2)=="[]") r=r.substr(0,r.size()-2);
    return r;
}

std::string strip(const std::string& s) {
    std::string r = s;
    size_t pos;
    while((pos=r.find("list<"))!=std::string::npos && r.back()=='>') r=r.substr(pos+5,r.size()-(pos+6));
    while(r.size()>=2 && r.substr(r.size()-2)=="[]") r=r.substr(0,r.size()-2);
    while((pos=r.find("list<"))!=std::string::npos && r.back()=='>') r=r.substr(pos+5,r.size()-(pos+6));
    return r;
}
bool loose;
std::string entrypointName = "main";
extern "C" const char _binary_runtime_ll_start[];
extern "C" const size_t _binary_runtime_ll_size;
namespace tkz {
//////////////////////////////////////////////////////////////////////////////////////////////
// POSITION /////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    Position::Position() {

    }
    std::string Position::arrow_string() const {
        if (Filetxt.empty() || index < 0 || index > (int)Filetxt.size()) {
            return "\n"; 
        }

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
        this->index ++;
        this->column ++;
        if (current_char == '\n') {
            this->line ++;
            this->column = 0;
        }
    }
    std::string get_token_name(TokenType tok) {
        switch (tok) {
            case TokenType::INT:        return "int";
            case TokenType::STRING:     return "string";
            case TokenType::FLOAT:      return "float";
            case TokenType::DOUBLE:     return "double";
            case TokenType::CHAR:       return "char";
            case TokenType::BOOL:       return "bool";
            case TokenType::QBOOL:      return "qbool";
            case TokenType::VOID:       return "void";
            case TokenType::ENUM:       return "enum";
            case TokenType::CLASS:      return "class";
            case TokenType::STRUCT:     return "struct";
            case TokenType::MAP:        return "map";
            case TokenType::LIST:       return "list";
            case TokenType::ARRAY:      return "array";
            case TokenType::FUNC:       return "func";
            case TokenType::DEF:        return "def";

            case TokenType::IF:         return "if";
            case TokenType::ELSE:       return "else";
            case TokenType::SWITCH:     return "switch";
            case TokenType::CASE:       return "case";
            case TokenType::DEFAULT:    return "default";
            case TokenType::BREAK:      return "break";

            case TokenType::IDENTIFIER: return "identifier";
            case TokenType::KEYWORD:    return "keyword";
            case TokenType::FSTRING:    return "fstring";

            case TokenType::PLUS:       return "+";
            case TokenType::MINUS:      return "-";
            case TokenType::MUL:        return "*";
            case TokenType::DIV:        return "/";
            case TokenType::MOD:        return "%";
            case TokenType::POWER:      return "^*";

            case TokenType::PLUS_EQ:    return "+=";
            case TokenType::MINUS_EQ:   return "-=";
            case TokenType::MUL_EQ:     return "*=";
            case TokenType::DIV_EQ:     return "/=";
            case TokenType::MOD_EQ:     return "%=";

            case TokenType::INCREMENT:  return "++";
            case TokenType::DECREMENT:  return "--";

            case TokenType::EQ:         return "=";
            case TokenType::EQ_TO:      return "==";
            case TokenType::NOT_EQ:     return "!=";
            case TokenType::MORE:       return ">";
            case TokenType::LESS:       return "<";
            case TokenType::MORE_EQ:    return ">=";
            case TokenType::LESS_EQ:    return "<=";

            case TokenType::AND:        return "&&&";
            case TokenType::OR:         return "||";
            case TokenType::XOR:        return "^";
            case TokenType::NOT:        return "!";

            case TokenType::QAND:        return "&&&";
            case TokenType::QOR:         return "|||";
            case TokenType::QXOR:        return "^^";
            case TokenType::QNOT:        return "!!";
            case TokenType::QEQEQ:       return "===";
            case TokenType::QNEQ:        return "!==";
            case TokenType::COLLAPSE_AND:return "&|&";
            case TokenType::COLLAPSE_OR: return "|&|";

            case TokenType::LPAREN:     return "(";
            case TokenType::RPAREN:     return ")";
            case TokenType::LBRACE:     return "{";
            case TokenType::RBRACE:     return "}";
            case TokenType::LBRACKET:   return "[";
            case TokenType::RBRACKET:   return "]";
            case TokenType::COMMA:      return ",";
            case TokenType::DOT:        return ".";
            case TokenType::COLON:      return ":";
            case TokenType::SEMICOLON:  return ";";
            case TokenType::ARROW:      return "->";
            case TokenType::AMPERSAND:  return "&";
            case TokenType::STAR:       return "*";
            case TokenType::SCOPE:      return "::";
            case TokenType::LSHIFT:     return "<<";
            case TokenType::RSHIFT:     return ">>";
            case TokenType::AT:         return "@";
            case TokenType::PIPE:       return "|";

            case TokenType::EOFT:       return "<eof>";
        }

        return "<unknown token>";
    }
    Position Position::copy() {
        return Position(this->Filename, this->Filetxt, this->index, this->line, this->column);
    }
    Position get_pos(const NumberVariant& v) {
        return std::visit([](auto const& x) -> Position {
            using T = std::decay_t<decltype(x)>;

            if constexpr (std::is_same_v<T, Number<int>> ||
                        std::is_same_v<T, Number<float>> ||
                        std::is_same_v<T, Number<double>> ||
                        std::is_same_v<T, Number<long long>> ||
                        std::is_same_v<T, Number<short>> ||
                        std::is_same_v<T, Number<long double>>) {
                return x.pos;
            } else if constexpr (std::is_same_v<T, StringValue> ||
                                std::is_same_v<T, CharValue>   ||
                                std::is_same_v<T, BoolValue>   ||
                                std::is_same_v<T, QBoolValue>  ||
                                std::is_same_v<T, VoidValue>   ||
                                std::is_same_v<T, FunctionValue> || 
                                std::is_same_v<T, PointerValue>) {
                return x.pos;
            } else if constexpr (std::is_same_v<T, std::shared_ptr<ArrayValue>>   ||
                                std::is_same_v<T, std::shared_ptr<ListValue>>    ||
                                std::is_same_v<T, std::shared_ptr<MapValue>>     ||
                                std::is_same_v<T, std::shared_ptr<StructValue>>  ||
                                std::is_same_v<T, std::shared_ptr<InstanceValue>>||
                                std::is_same_v<T, std::shared_ptr<MultiValue>>) {
                return x ? x->pos : Position();
            } else {
                return Position();
            }
        }, v);
    }
    Token::Token() {}
    Token::Token(TokenType t, std::string val, Position p)
    : type(t), value(val), pos(p)
    {
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
        result += "Compile or Runtime Error: " + this->details + "\n";
        result += "File " + this->pos.Filename +
                ", line " + std::to_string(this->pos.line + 1) +
                ", col " + std::to_string(this->pos.column + 1) + "\n\n";
        result += this->pos.arrow_string();
        return result;
    }
    std::string MissingSemicolonError::as_string() {
        std::string result;
        result += "QC-MS99: Missing Semicolon on ";
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
    AnyNode clone_node(const AnyNode& node) {
        return std::visit([](auto&& arg) -> AnyNode {
            using T = std::decay_t<decltype(arg)>;
            
            if constexpr (std::is_same_v<T, NumberNode>) {
                return NumberNode(arg.tok);
            }
            else if constexpr (std::is_same_v<T, StringNode>) {
                return StringNode(arg.tok);
            }
            else if constexpr (std::is_same_v<T, CharNode>) {
                return CharNode(arg.tok);
            }
            else if constexpr (std::is_same_v<T, BoolNode>) {
                return BoolNode(arg.tok);
            }
            else if constexpr (std::is_same_v<T, QBoolNode>) {
                return QBoolNode(arg.tok);
            }
            else if constexpr (std::is_same_v<T, QInNode>) {
                return QInNode();
            }
            else if constexpr (std::is_same_v<T, NullptrNode>) {
                return NullptrNode(arg.pos);
            }
            else if constexpr (std::is_same_v<T, RefVarDeclNode>) {
                return RefVarDeclNode(arg.type_tok, arg.var_name_tok, arg.target_tok, arg.pos);
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<VarAccessNode>>) {
                return std::make_unique<VarAccessNode>(arg->var_name_tok);
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<UnaryOpNode>>) {
                return std::make_unique<UnaryOpNode>(
                    arg->op_tok,
                    clone_node(arg->node),
                    arg->is_postfix
                );
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<PropertyAccessNode>>) {
                return std::make_shared<PropertyAccessNode>(
                    clone_node(*(arg->base)),
                    arg->base_name_tok,
                    arg->property_name
                );
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ArrayAccessNode>>) {
                std::vector<AnyNode> cloned_indices;
                for (auto& idx : arg->indices) {
                    cloned_indices.push_back(clone_node(idx));
                }
                return std::make_unique<ArrayAccessNode>(
                    clone_node(arg->base),
                    std::move(cloned_indices)
                );
            }
            else {
                throw std::runtime_error("Cannot clone complex node type");
            }
        }, node);
    }
    std::string printAny(const AnyNode& node) {
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
            else if constexpr (std::is_same_v<T, QBoolNode>) { 
                return arg.print();
            }
            else if constexpr (std::is_same_v<T, RefVarDeclNode>) { 
                return arg.print();
            }
            else if constexpr (std::is_same_v<T, NullptrNode>) { 
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
            else if constexpr (std::is_same_v<T, std::unique_ptr<TryCatchNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::monostate>) {
                return "";
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
            else if constexpr (std::is_same_v<T, std::unique_ptr<ReturnNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ArrayDeclNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ArrayLiteralNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<ArrayAccessNode>>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ListDeclNode>>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MethodCallNode>>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::shared_ptr<PropertyAccessNode>>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<SpreadNode>>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ForeachNode>>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<QIfNode>>) { 
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<QSwitchNode>>) {
                return arg->print();
            } else if constexpr (std::is_same_v<T, QInNode>) { 
                return arg.print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MapDeclNode>>) { 
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ArrayAssignNode>>) { 
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<RandomCallNode>>) { 
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<SeedCallNode>>) { 
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<FieldAssignNode>>) { 
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MapLiteralNode>>) { 
                return arg->print();
            } else if constexpr (std::is_same_v<T, std::unique_ptr<NamespaceNode>>) { 
                return arg->print();
            } else {
                return "<unknown>"; 
            }
        }, node);
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
            if (i < statements.size() - 1) {
                res += ", ";
            }
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
        NumberVariant value;
        ReturnException(NumberVariant v) : value(std::move(v)) {}
    };
//////////////////////////////////////////////////////////////////////////////////////////////
// PARSE RESULT /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    AnyNode ParseResult::reg_node(AnyNode res) {
        return res;
    }
    AnyNode ParseResult::reg(Prs res_variant) {
        if (std::holds_alternative<std::unique_ptr<Error>>(res_variant)) {
            this->error = std::move(std::get<std::unique_ptr<Error>>(res_variant));
            return std::monostate{};
        }
        return std::visit([this](auto&& arg) -> AnyNode {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::monostate> ||
                        std::is_same_v<T, std::unique_ptr<Error>> ||
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
            } else if constexpr (std::is_same_v<T, RefVarDeclNode>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, NullptrNode>) { 
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
            } else if constexpr (std::is_same_v<T, std::unique_ptr<TryCatchNode>>) {
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
            else if constexpr (std::is_same_v<T, std::unique_ptr<ReturnNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MultiVarDeclNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MultiReturnNode>>) {
                return Prs{std::move(arg)}; 
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MultiReturnNode>>) {
                return Prs{std::move(arg)}; 
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ArrayDeclNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ArrayLiteralNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ArrayAccessNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ListDeclNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MethodCallNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::shared_ptr<PropertyAccessNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<SpreadNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ForeachNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, QBoolNode>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<QIfNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<QSwitchNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, QInNode>) { 
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MapDeclNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ArrayAssignNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<RandomCallNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<SeedCallNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<FieldAssignNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MapLiteralNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<NamespaceNode>>) { 
                return Prs{std::move(arg)};
            } else {
                return Prs{std::monostate{}};
            }
        }, std::move(this->node));
    }
    
    Prs ParseResult::to_prs() {
        if (this->error) {
            return Prs{std::move(this->error)};
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
            } else if constexpr (std::is_same_v<T, RefVarDeclNode>) { 
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
            } else if constexpr (std::is_same_v<T, std::unique_ptr<TryCatchNode>>) {
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
            else if constexpr (std::is_same_v<T, std::unique_ptr<ReturnNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MultiVarDeclNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MultiReturnNode>>) { 
                return Prs{std::move(arg)}; 
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MultiReturnNode>>) {
                return Prs{std::move(arg)}; 
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ArrayDeclNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ArrayLiteralNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ArrayAccessNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ListDeclNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MethodCallNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::shared_ptr<PropertyAccessNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<SpreadNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ForeachNode>>) {
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, QBoolNode>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<QIfNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, QInNode>) { 
                return Prs{arg};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MapDeclNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<ArrayAssignNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<RandomCallNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<SeedCallNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<FieldAssignNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<MapLiteralNode>>) { 
                return Prs{std::move(arg)};
            } else if constexpr (std::is_same_v<T, std::unique_ptr<NamespaceNode>>) { 
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
        std::string upperStr = str;
        std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);

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

        auto it = stringToEnum.find(upperStr);
        if (it != stringToEnum.end()) return it->second;
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
    AnyNode Parser::default_value_for_type(const Token& type_tok, const Position& pos) {
        std::string type = type_tok.value;
        
        if (type == "short int")
            return AnyNode{NumberNode(Token(TokenType::INT, "0", pos))};
        if (type == "int")
            return AnyNode{NumberNode(Token(TokenType::INT, "0", pos))};
        if (type == "long int")
            return AnyNode{NumberNode(Token(TokenType::INT, "0", pos))};
        
        if (type == "float")
            return AnyNode{NumberNode(Token(TokenType::FLOAT, "0.0f", pos))};
        if (type == "double")
            return AnyNode{NumberNode(Token(TokenType::DOUBLE, "0.0", pos))};
        if (type == "long double")
            return AnyNode{NumberNode(Token(TokenType::DOUBLE, "0.0", pos))};
        
        if (type == "string")
            return AnyNode{StringNode(Token(TokenType::STRING, "", pos))};
        if (type == "char")
            return AnyNode{CharNode(Token(TokenType::CHAR, "\0", pos))};
        if (type == "bool")
            return AnyNode{BoolNode(Token(TokenType::BOOL, "false", pos))};
        if (type == "qbool")
            return AnyNode{QBoolNode(Token(TokenType::QBOOL, "none", pos))};
        if (type == "function") {
            return AnyNode{std::make_shared<FuncDefNode>(std::vector<Token>{}, std::nullopt, std::list<Parameter>{}, std::make_unique<StatementsNode>(std::vector<AnyNode>{}, true), currentNamespace)};
        }
        return AnyNode{std::monostate{}};
    }
    Parser::Parser(std::vector<Token> tokens) {
        this->tokens = tokens;
        this->current_tok = tokens[index];
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
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S001: Expected '(' after 'qif'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        
        AnyNode condition = res.reg(this->logical_or());
        if (res.error) {
            return res.to_prs();
        }
        

        if (this->current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S002: Expected ')' after qif condition", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        if (this->current_tok.type != TokenType::LBRACE) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S003: Expected '{' after qif condition", this->current_tok.pos));
            return res.to_prs();
        }

        this->advance();

        std::vector<AnyNode> then_stmts;
        while (this->current_tok.type != TokenType::RBRACE && 
            this->current_tok.type != TokenType::EOFT) {
            auto stmt = res.reg(this->statement());
            if (res.error) {
                return res.to_prs();
            }
            then_stmts.push_back(std::move(stmt));
        }


        if (this->current_tok.type != TokenType::RBRACE) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S004: Expected '}'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        auto then_branch = std::make_unique<StatementsNode>(std::move(then_stmts), true);
        if (res.error) {
            return res.to_prs();
        }
        
        std::vector<std::pair<AnyNode, std::unique_ptr<StatementsNode>>> qelif_branches;
        
        while (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "qelif") {
            this->advance();
            if (this->current_tok.type != TokenType::LPAREN) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S005: Expected '(' after 'qelif'", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            
            AnyNode qelif_cond = res.reg(this->logical_or());
            if (res.error) return res.to_prs();
            
            if (this->current_tok.type != TokenType::RPAREN) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S006: Expected ')' after qelif condition", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            
            if (this->current_tok.type != TokenType::LBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S007: Expected '{' after qelif condition", this->current_tok.pos));
                return res.to_prs();
            }
            
            this->advance(); 

            std::vector<AnyNode> qelif_stmts;
            while (this->current_tok.type != TokenType::RBRACE && 
                this->current_tok.type != TokenType::EOFT) {
                auto stmt = res.reg(this->statement());
                if (res.error) return res.to_prs();
                qelif_stmts.push_back(std::move(stmt));
            }

            if (this->current_tok.type != TokenType::RBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S004: Expected '}'", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            auto qelif_body = std::make_unique<StatementsNode>(std::move(qelif_stmts), true);
            if (res.error) return res.to_prs();
            
            qelif_branches.emplace_back(std::move(qelif_cond), std::move(qelif_body));
        }
        
        std::unique_ptr<StatementsNode> qelse_branch = nullptr;
        if (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "qelse") {
            this->advance();
            if (this->current_tok.type != TokenType::LBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S008: Expected '{' after 'qelse'", this->current_tok.pos));
                return res.to_prs();
            }
            
            this->advance(); 

            std::vector<AnyNode> qelse_stmts;
            while (this->current_tok.type != TokenType::RBRACE && 
                this->current_tok.type != TokenType::EOFT) {
                auto stmt = res.reg(this->statement());
                if (res.error) return res.to_prs();
                qelse_stmts.push_back(std::move(stmt));
            }

            if (this->current_tok.type != TokenType::RBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S004: Expected '}'", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            qelse_branch = std::make_unique<StatementsNode>(std::move(qelse_stmts), true);
            if (res.error) return res.to_prs();
        }
        return res.success(std::make_unique<QIfNode>(
            std::nullopt,
            std::move(condition),
            std::move(then_branch),
            std::move(qelif_branches),
            std::move(qelse_branch)));
    }
    Prs Parser::if_expr() {
        auto has_semicolon_before_closing_paren = [this]() -> bool {
            size_t idx = index;
            int depth = 0;
            for (size_t i = idx; i < this->tokens.size(); ++i) {
                const Token &t = this->tokens[i];
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
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S009: Expected 'if'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance(); 

        if (this->current_tok.type != TokenType::LPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S010: Expected '(' after 'if'", this->current_tok.pos));
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
                        res.failure(std::make_unique<InvalidSyntaxError>("QC-S011: Expected type after 'const' in if-init", this->current_tok.pos));
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
                    res.failure(std::make_unique<InvalidSyntaxError>("QC-S012: Expected identifier in if-init", this->current_tok.pos));
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
                        res.failure(std::make_unique<InvalidSyntaxError>("QC-S013: const variables must be initialized in if-init", var_name.pos));
                        return res.to_prs();
                    }
                    value = default_value_for_type(type_tok, var_name.pos);
                }

                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(std::make_unique<InvalidSyntaxError>("QC-S014: Expected ';' after if-init declaration", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance(); 

                init_node = AnyNode{std::make_unique<VarAssignNode>(is_const, type_tok, var_name, std::move(value))};
            } else {
                AnyNode expr_init = res.reg(this->assignment_expr());
                if (res.error) return res.to_prs();

                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(std::make_unique<InvalidSyntaxError>("QC-S015: Expected ';' after if-init expression", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance(); 
                init_node = std::move(expr_init);
            }
        }

        AnyNode condition = res.reg(this->logical_or());
        if (res.error) return res.to_prs();

        if (this->current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S016: Expected ')' after condition", this->current_tok.pos));
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
                    res.failure(std::make_unique<InvalidSyntaxError>("QC-S017: Expected '(' after 'else if'", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                AnyNode elif_cond = res.reg(this->logical_or());
                if (res.error) return res.to_prs();
                if (this->current_tok.type != TokenType::RPAREN) {
                    res.failure(std::make_unique<InvalidSyntaxError>("QC-S018: Expected ')' after 'else if' condition", this->current_tok.pos));
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
    Prs Parser::try_catch_expr() {
        ParseResult res;
        if (!(this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "try")) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S030: Expected 'try'", this->current_tok.pos));
            return res.to_prs();
        }
        Token try_tok = this->current_tok;
        this->advance();
        std::unique_ptr<StatementsNode> try_body;
        if (!parse_block_into(try_body, res)) return res.to_prs();
        if (!(this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "catch")) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S031: Expected 'catch' after try block", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        if (this->current_tok.type != TokenType::LPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S032: Expected '(' after 'catch'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        if (this->current_tok.type != TokenType::KEYWORD && this->current_tok.type != TokenType::IDENTIFIER) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S033: Expected type in catch declaration", this->current_tok.pos));
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
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S034: Expected variable name in catch declaration", this->current_tok.pos));
            return res.to_prs();
        }
        Token var_tok = this->current_tok;
        std::string catch_var = var_tok.value;
        this->advance();
        if (this->current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S035: Expected ')' after catch variable", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        std::unique_ptr<StatementsNode> catch_body;
        if (!parse_block_into(catch_body, res)) return res.to_prs();
        auto try_catch_node = std::make_unique<TryCatchNode>(
            std::move(try_body),
            catch_var,
            catch_type,
            std::move(catch_body),
            try_tok,
            try_tok.pos
        );
        
        return res.success(std::move(try_catch_node));
    }
    Prs Parser::switch_stmt() {
        ParseResult res;
        if (!(current_tok.type == TokenType::KEYWORD && current_tok.value == "switch")) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S019: Expected 'switch'", current_tok.pos));
            return res.to_prs();
        }
        advance();

        if (current_tok.type != TokenType::LPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S020: Expected '(' after 'switch'", current_tok.pos));
            return res.to_prs();
        }
        advance();

        AnyNode value = res.reg(this->logical_or());
        if (res.error) return res.to_prs();

        if (current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S021: Expected ')' after switch expression", current_tok.pos));
            return res.to_prs();
        }
        advance();

        if (current_tok.type != TokenType::LBRACE) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S022: Expected '{' after switch(...)", current_tok.pos));
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
                        res.failure(std::make_unique<InvalidSyntaxError>("QC-S023: Expected ':' after case label", current_tok.pos));
                        return res.to_prs();
                    }
                    advance();

                    section.cases.push_back(CaseLabel{std::move(case_expr)});
                }
            }

            if (!saw_label) {
                res.failure(std::make_unique<InvalidSyntaxError>("QC-S024: Expected 'case' or 'default' inside switch", current_tok.pos));
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
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S025: Expected '}' after switch body", current_tok.pos));
            return res.to_prs();
        }
        advance();

        auto sw = std::make_unique<SwitchNode>();
        sw->value = std::move(value);
        sw->sections = std::move(sections);
        return res.success(std::move(sw));
    }
    Prs Parser::qswitch_stmt() {
        ParseResult res;
        this->advance();
        
        if (this->current_tok.type != TokenType::LPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S026: Expected '(' after 'qswitch'", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        
        AnyNode value = res.reg(this->logical_or());
        if (res.error) return res.to_prs();
        
        if (this->current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S027: Expected ')' after qswitch value", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        
        if (this->current_tok.type != TokenType::LBRACE) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S028: Expected '{' after qswitch", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        
        std::unique_ptr<StatementsNode> case_t = nullptr;
        std::unique_ptr<StatementsNode> case_f = nullptr;
        std::unique_ptr<StatementsNode> case_n = nullptr;
        std::unique_ptr<StatementsNode> case_b = nullptr;
        
        while (this->current_tok.type == TokenType::KEYWORD && this->current_tok.value == "case") {
            this->advance();
            
            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S029: Expected case label (t, f, n, or b)", this->current_tok.pos));
                return res.to_prs();
            }
            
            std::string case_label = this->current_tok.value;
            this->advance();
            
            if (this->current_tok.type != TokenType::COLON) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S023: Expected ':' after case label", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            
            std::vector<AnyNode> case_stmts;
            while (this->current_tok.type != TokenType::KEYWORD ||
                (this->current_tok.value != "case" && 
                    this->current_tok.value != "break")) {
                
                if (this->current_tok.type == TokenType::RBRACE) break;
                if (this->current_tok.type == TokenType::EOFT) break;
                
                auto stmt = res.reg(this->statement());
                if (res.error) return res.to_prs();
                case_stmts.push_back(std::move(stmt));
            }
            
            if (this->current_tok.type == TokenType::KEYWORD && 
                this->current_tok.value == "break") {
                this->advance();
                if (this->current_tok.type == TokenType::SEMICOLON) {
                    this->advance();
                }
            }
            
            auto case_body = std::make_unique<StatementsNode>(std::move(case_stmts), true);
            
            if (case_label == "t") {
                case_t = std::move(case_body);
            } else if (case_label == "f") {
                case_f = std::move(case_body);
            } else if (case_label == "n") {
                case_n = std::move(case_body);
            } else if (case_label == "b") {
                case_b = std::move(case_body);
            } else {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S030: Invalid case label (must be t, f, n, or b)", this->current_tok.pos));
                return res.to_prs();
            }
        }
        
        if (this->current_tok.type != TokenType::RBRACE) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S031: Expected '}' after qswitch", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance();
        
        return res.success(std::make_unique<QSwitchNode>(
            std::move(value),
            std::move(case_t),
            std::move(case_f),
            std::move(case_n),
            std::move(case_b)));
    }
    Prs Parser::while_stmt() {
        ParseResult res;
        if (!(current_tok.type == TokenType::KEYWORD && current_tok.value == "while")) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S032: Expected 'while'", current_tok.pos));
            return res.to_prs();
        }
        advance();

        if (current_tok.type != TokenType::LPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S033: Expected '(' after 'while'", current_tok.pos));
            return res.to_prs();
        }
        advance();

        AnyNode cond = res.reg(this->logical_or());
        if (res.error) return res.to_prs();

        if (current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S034: Expected ')' after while condition", current_tok.pos));
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
        Token type_tok;
        if (!(this->current_tok.type == TokenType::KEYWORD && current_tok.value == "for")) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S035: Expected 'for'", current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        if (this->current_tok.type != TokenType::LPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S036: Expected '(' after 'for'", current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        std::optional<AnyNode> init;
        std::optional<AnyNode> update;
        AnyNode condition;

        if (this->current_tok.type != TokenType::SEMICOLON) {
            if (this->current_tok.type == TokenType::KEYWORD &&
                (this->current_tok.value == "const" ||
                this->current_tok.value == "int"   ||
                this->current_tok.value == "float" ||
                this->current_tok.value == "double"||
                this->current_tok.value == "bool"  ||
                this->current_tok.value == "string"||
                this->current_tok.value == "char")) {

                bool is_const = false;
                Token tok = current_tok;

                if (tok.value == "const") {
                    is_const = true;
                    advance();
                    tok = current_tok;
                    if (tok.type != TokenType::KEYWORD) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S011:  Expected type after 'const' in for-init", current_tok.pos));
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
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S038: Expected identifier in for-init", current_tok.pos));
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
                            "QC-S039: const variables must be initialized in for-init", var_name.pos));
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
                "QC-S040: Expected ';' after for-init", current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        if (current_tok.type == TokenType::SEMICOLON) {
            condition = AnyNode{ BoolNode(Token(TokenType::BOOL, "true", current_tok.pos)) };
        } else {
            condition = res.reg(this->logical_or());
            if (res.error) return res.to_prs();
        }

        if (current_tok.type != TokenType::SEMICOLON) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S041: Expected ';' after for condition", current_tok.pos));
            return res.to_prs();
        }
        this->advance();

        if (current_tok.type != TokenType::RPAREN) {
            AnyNode upd_expr = res.reg(this->assignment_expr());
            if (res.error) return res.to_prs();
            update = std::move(upd_expr);
        } 

        if (current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S042: Expected ')' after for header", current_tok.pos));
            return res.to_prs();
        }
        this->advance();

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
                        "QC-S043: Expected '}' after for body", this->current_tok.pos));
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
                out_block = std::make_unique<StatementsNode>(std::move(stmts), true);
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

            auto parse_arg = [&]() -> AnyNode {
                if (this->current_tok.type == TokenType::AT) {
                    this->advance();
                    AnyNode expr = res.reg(this->logical_or());
                    if (res.error) return AnyNode{};
                    return std::make_unique<SpreadNode>(std::move(expr));
                } else {
                    return res.reg(this->logical_or());
                }
            };

            AnyNode arg = parse_arg();
            if (res.error) return res.to_prs();
            args.push_back(std::move(arg));

            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                arg = parse_arg();
                if (res.error) return res.to_prs();
                args.push_back(std::move(arg));
            }
        }

        if (this->current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S044: Expected ')' after function arguments", this->current_tok.pos));
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
        
        return res.success(std::move(left));
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
                
                elements.push_back(std::make_unique<SpreadNode>(std::move(spread_expr)));
            } else {
                AnyNode elem = res.reg(this->logical_or());
                if (res.error) return res.to_prs();
                elements.push_back(std::move(elem));
            }
            
            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                
                if (this->current_tok.type == TokenType::AT) {
                    this->advance();
                    AnyNode spread_expr = res.reg(this->logical_or());
                    if (res.error) return res.to_prs();
                    
                    elements.push_back(std::make_unique<SpreadNode>(std::move(spread_expr)));
                } else {
                    AnyNode elem = res.reg(this->logical_or());
                    if (res.error) return res.to_prs();
                    elements.push_back(std::move(elem));
                }
            }
        }
        
        if (this->current_tok.type != TokenType::RBRACKET) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S045: Expected ']' in array literal", this->current_tok.pos));
            return res.to_prs();
        }
        
        this->advance(); 
        
        return res.success(std::make_unique<ArrayLiteralNode>(std::move(elements), start_pos));
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
                return res2.success(
                    std::make_unique<MapLiteralNode>(std::move(pairs), start_pos)
                );
            }

            auto first_key_expr = res2.reg(this->logical_or());
            if (res2.error) return res2.to_prs();

            if (this->current_tok.type == TokenType::COLON) {
                this->advance();

                AnyNode first_val_expr = res2.reg(this->logical_or());
                if (res2.error) return res2.to_prs();

                std::vector<std::pair<AnyNode, AnyNode>> pairs;
                pairs.emplace_back(std::move(first_key_expr), std::move(first_val_expr));

                while (this->current_tok.type == TokenType::COMMA) {
                    this->advance();

                    AnyNode key_expr = res2.reg(this->logical_or());
                    if (res2.error) return res2.to_prs();

                    if (this->current_tok.type != TokenType::COLON) {
                        res2.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S046: Expected ':' in map literal", this->current_tok.pos));
                        return res2.to_prs();
                    }
                    this->advance();

                    AnyNode val_expr = res2.reg(this->logical_or());
                    if (res2.error) return res2.to_prs();

                    pairs.emplace_back(std::move(key_expr), std::move(val_expr));
                }

                if (this->current_tok.type != TokenType::RBRACE) {
                    res2.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S047: Expected '}' at end of map literal", this->current_tok.pos));
                    return res2.to_prs();
                }
                this->advance();

                return res2.success(
                    std::make_unique<MapLiteralNode>(std::move(pairs), start_pos));
            } else {
                std::vector<AnyNode> elements;
                elements.push_back(std::move(first_key_expr));

                while (this->current_tok.type == TokenType::COMMA) {
                    this->advance();
                    AnyNode e2 = res2.reg(this->logical_or());
                    if (res2.error) return res2.to_prs();
                    elements.push_back(std::move(e2));
                }

                if (this->current_tok.type != TokenType::RBRACE) {
                    res2.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S048: Expected '}' in initializer list", this->current_tok.pos));
                    return res2.to_prs();
                }
                this->advance();

                return res2.success(
                    std::make_unique<ArrayLiteralNode>(std::move(elements), start_pos));
            }
        }
        if (tok.type == TokenType::LBRACKET)
            return this->array_literal();
        if (current_tok.value == "qin") {
            this->advance();
            
            return this->qin_expr(); 
        }
        
        if (tok.type == TokenType::INT || tok.type == TokenType::FLOAT || tok.type == TokenType::DOUBLE) {
            this->advance();
            return res.success(NumberNode(tok));
        }
        else if (tok.type == TokenType::STRING) {
            this->advance();
            return res.success(StringNode(tok));
        }
        else if (tok.type == TokenType::CHAR) {
            this->advance();
            return res.success(CharNode(tok));
        }
        else if (tok.type == TokenType::BOOL) {
            this->advance();
            return res.success(BoolNode(tok));
        }
        else if (tok.type == TokenType::QBOOL) {
            this->advance();
            return res.success(QBoolNode(tok));
        }
        else if (tok.type == TokenType::AT) {
            Token op = tok;
            this->advance();

            AnyNode value = res.reg(this->atom()); 
            if (res.error) return res.to_prs();

            return res.success(std::make_unique<SpreadNode>(std::move(value)));
        }
        else if (tok.type == TokenType::KEYWORD && tok.value == "nullptr") {
            this->advance();
            return res.success(NullptrNode(tok.pos));
        } else if (tok.type == TokenType::IDENTIFIER) {
            std::string name = tok.value;
            Position pos = tok.pos;

            this->advance();

            while (this->current_tok.type == TokenType::SCOPE) {
                this->advance();

                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-N001: Expected identifier or namespace name after '::'", this->current_tok.pos));
                    return res.to_prs();
                }

                name += "::" + this->current_tok.value;
                pos = this->current_tok.pos;
                this->advance();
            }

            Token ident(
                TokenType::IDENTIFIER,
                name,
                pos
            );

            AnyNode base = std::make_unique<VarAccessNode>(ident);

            if (this->current_tok.type == TokenType::LPAREN) {
                return this->call(std::move(base));
            }

            if (this->current_tok.type == TokenType::LBRACKET) {
                std::vector<AnyNode> indices;

                while (this->current_tok.type == TokenType::LBRACKET) {
                    this->advance();
                    AnyNode index = res.reg(this->logical_or());
                    if (res.error) return res.to_prs();

                    if (this->current_tok.type != TokenType::RBRACKET) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S049: Expected ']'", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();

                    indices.push_back(std::move(index));
                }

                base = std::make_unique<ArrayAccessNode>(std::move(base),
                                                        std::move(indices));
            }

            while (this->current_tok.type == TokenType::DOT || 
                this->current_tok.type == TokenType::ARROW) {
                
                if (this->current_tok.type == TokenType::ARROW) {
                    this->advance();
                    
                    if (this->current_tok.type != TokenType::IDENTIFIER) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Expected property or method name after '->'",
                            this->current_tok.pos));
                        return res.to_prs();
                    }
                    
                    Token property_name = this->current_tok;
                    this->advance();
                    Token base_name_tok;
                    if (auto var = std::get_if<std::unique_ptr<VarAccessNode>>(&base)) {
                        base_name_tok = (*var)->var_name_tok;
                    } else {
                        base_name_tok = Token(TokenType::IDENTIFIER, "", property_name.pos);
                    }
                    
                    auto deref = std::make_unique<UnaryOpNode>(
                        Token(TokenType::MUL, "*", property_name.pos),
                        std::move(base) 
                    );
                    
                    if (this->current_tok.type == TokenType::LPAREN) {
                        this->advance();
                        
                        std::vector<AnyNode> args;
                        if (this->current_tok.type != TokenType::RPAREN) {
                            while (true) {
                                if (this->current_tok.type == TokenType::AT) {
                                    this->advance();
                                    AnyNode expr = res.reg(this->logical_or());
                                    if (res.error) return res.to_prs();
                                    args.push_back(std::make_unique<SpreadNode>(std::move(expr)));
                                } else {
                                    AnyNode arg = res.reg(this->logical_or());
                                    if (res.error) return res.to_prs();
                                    args.push_back(std::move(arg));
                                }
                                if (this->current_tok.type != TokenType::COMMA) break;
                                this->advance();
                            }
                        }
                        
                        if (this->current_tok.type != TokenType::RPAREN) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "Expected ')' after method arguments",
                                this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                        
                        base = std::make_unique<MethodCallNode>(
                            std::move(deref), property_name, std::move(args));
                    }
                    else {
                        base = std::make_shared<PropertyAccessNode>(
                            std::move(deref), base_name_tok, property_name);
                    }
                }
                else if (this->current_tok.type == TokenType::DOT) {
                    this->advance();

                    if (this->current_tok.type != TokenType::IDENTIFIER) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Expected property or method name after '.'",
                            this->current_tok.pos));
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
                                    args.push_back(
                                        std::make_unique<SpreadNode>(std::move(expr)));
                                } else {
                                    AnyNode arg = res.reg(this->logical_or());
                                    if (res.error) return res.to_prs();
                                    args.push_back(std::move(arg));
                                }
                                if (this->current_tok.type != TokenType::COMMA) break;
                                this->advance();
                            }
                        }

                        if (this->current_tok.type != TokenType::RPAREN) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "QC-S044: Expected ')' after function arguments",
                                this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();

                        base = std::make_unique<MethodCallNode>(
                            std::move(base), property_name, std::move(args));
                    } else {
                        base = std::make_shared<PropertyAccessNode>(
                            std::move(base), ident, property_name);
                    }

                    while (this->current_tok.type == TokenType::LBRACKET) {
                        std::vector<AnyNode> indices;
                        while (this->current_tok.type == TokenType::LBRACKET) {
                            this->advance();
                            AnyNode index = res.reg(this->logical_or());
                            if (res.error) return res.to_prs();
                            if (this->current_tok.type != TokenType::RBRACKET) {
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "QC-S049: Expected ']'", this->current_tok.pos));
                                return res.to_prs();
                            }
                            this->advance();
                            indices.push_back(std::move(index));
                        }
                        base = std::make_unique<ArrayAccessNode>(std::move(base),
                                                                std::move(indices));
                    }
                }
            }
            if (this->current_tok.type == TokenType::INCREMENT ||
                this->current_tok.type == TokenType::DECREMENT) {
                Token op = this->current_tok;
                this->advance();
                AnyNode target = std::make_unique<VarAccessNode>(ident);
                AnyNode value_node = std::make_unique<UnaryOpNode>(
                    op,
                    std::make_unique<VarAccessNode>(ident)
                );

                return res.success(std::make_unique<AssignExprNode>(
                    std::move(target),
                    Token(TokenType::EQ, "=", op.pos),
                    std::move(value_node)
                ));
            }

            return res.success(std::move(base));
        }
        else if (tok.type == TokenType::LPAREN) {
            this->advance();
            AnyNode any_expr = res.reg(this->logical_or());
            if (res.error) return res.to_prs();

            if (this->current_tok.type == TokenType::RPAREN) {
                this->advance();
                AnyNode base = std::move(any_expr);
                
                while (this->current_tok.type == TokenType::DOT) {
                    this->advance();
                    
                    if (this->current_tok.type != TokenType::IDENTIFIER) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Expected property or method name after '.'",
                            this->current_tok.pos));
                        return res.to_prs();
                    }
                    
                    Token property_name = this->current_tok;
                    this->advance();
                    Token base_name_tok;
                    if (auto unary = std::get_if<std::unique_ptr<UnaryOpNode>>(&base)) {
                        if ((*unary)->op_tok.type == TokenType::MUL) {
                            if (auto var = std::get_if<std::unique_ptr<VarAccessNode>>(&(*unary)->node)) {
                                base_name_tok = (*var)->var_name_tok;
                            } else {
                                base_name_tok = Token(TokenType::IDENTIFIER, "", property_name.pos);
                            }
                        } else {
                            base_name_tok = Token(TokenType::IDENTIFIER, "", property_name.pos);
                        }
                    }
                    else if (auto var = std::get_if<std::unique_ptr<VarAccessNode>>(&base)) {
                        base_name_tok = (*var)->var_name_tok;
                    }
                    else {
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
                                    args.push_back(
                                        std::make_unique<SpreadNode>(std::move(expr)));
                                } else {
                                    AnyNode arg = res.reg(this->logical_or());
                                    if (res.error) return res.to_prs();
                                    args.push_back(std::move(arg));
                                }
                                if (this->current_tok.type != TokenType::COMMA) break;
                                this->advance();
                            }
                        }
                        
                        if (this->current_tok.type != TokenType::RPAREN) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "Expected ')' after method arguments",
                                this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                        
                        base = std::make_unique<MethodCallNode>(
                            std::move(base), property_name, std::move(args));
                    }
                    else {
                        base = std::make_shared<PropertyAccessNode>(
                            std::move(base), base_name_tok, property_name);
                    }
                }
                
                return res.success(std::move(base));
            } else {
                res.failure(std::make_unique<InvalidSyntaxError>("QC-S050: Expected ')'", this->current_tok.pos));
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

            for (size_t i = 0; i < exprs.size(); ++i) {
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

        if (tok.type == TokenType::KEYWORD && tok.value == "fn") {
            this->advance();
            
            if (this->current_tok.type != TokenType::LPAREN) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S051: Expected '(' after 'fn'", this->current_tok.pos));
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
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S052: Expected return type after '->'", this->current_tok.pos));
                    return res.to_prs();
                }
                
                return_types.push_back(this->current_tok);
                this->advance();
                
                while (this->current_tok.type == TokenType::COMMA) {
                    this->advance();
                    
                    if (this->current_tok.type != TokenType::KEYWORD) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S053: Expected return type after ','", this->current_tok.pos));
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

            if (std::holds_alternative<std::unique_ptr<Error>>(fn_pr))
                return fn_pr;

            AnyNode fn_node;
            if (std::holds_alternative<std::shared_ptr<FuncDefNode>>(fn_pr))
                fn_node = std::get<std::shared_ptr<FuncDefNode>>(std::move(fn_pr));
            else
                fn_node = std::get<std::shared_ptr<FuncDefNode>>(std::move(fn_pr));

            if (this->current_tok.type == TokenType::LPAREN)
                return this->call(std::move(fn_node));

            return res.success(std::move(fn_node));
        }

        res.failure(std::make_unique<InvalidSyntaxError>("QC-S054: Expected an atom", tok.pos));
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
            tok.type == TokenType::NOT || tok.type == TokenType::QNOT || tok.type == TokenType::AMPERSAND || tok.type == TokenType::MUL) {
            
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

        while (this->current_tok.type == TokenType::OR || this->current_tok.type == TokenType::XOR) {
            Token op_tok = this->current_tok;
            this->advance();
            AnyNode right = res.reg(this->logical_and());
            if (res.error) return res.to_prs();
            
            left = std::make_unique<BinOpNode>(std::move(left), op_tok, std::move(right));
        }

        return res.success(std::move(left));
    }
    Prs Parser::qin_expr() {
        ParseResult res;
        
        AnyNode left = QInNode{};
        
        while (current_tok.type == TokenType::RSHIFT) {
            Token op_tok = current_tok;
            advance();

            AnyNode right = res.reg(this->term());
            if (!std::holds_alternative<std::unique_ptr<VarAccessNode>>(right)) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S055: Right-hand side of >> must be a variable",
                    op_tok.pos
                ));
                return res.to_prs();
            }

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
            this->current_tok.type == TokenType::MORE_EQ ||
            this->current_tok.type == TokenType::QEQEQ ||
            this->current_tok.type == TokenType::QNEQ ||
            this->current_tok.type == TokenType::QAND ||
            this->current_tok.type == TokenType::QOR ||
            this->current_tok.type == TokenType::QXOR ||
            this->current_tok.type == TokenType::COLLAPSE_AND ||
            this->current_tok.type == TokenType::COLLAPSE_OR) {
            
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

        while (
            current_tok.type != TokenType::SEMICOLON &&
            (current_tok.type == TokenType::PLUS ||
            current_tok.type == TokenType::MINUS)
        ) {
            Token op_tok = current_tok;
            advance();

            AnyNode right = res.reg(this->term());
            if (res.error) return res.to_prs();

            left = std::make_unique<BinOpNode>(
                std::move(left),
                op_tok,
                std::move(right)
            );
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
            
            bool is_var = std::holds_alternative<std::unique_ptr<VarAccessNode>>(left);
            bool is_array_access = std::holds_alternative<std::unique_ptr<ArrayAccessNode>>(left);
            bool is_prop = std::holds_alternative<std::shared_ptr<PropertyAccessNode>>(left);
            bool is_deref = std::holds_alternative<std::unique_ptr<UnaryOpNode>>(left) && std::get<std::unique_ptr<UnaryOpNode>>(left)->op_tok.type == TokenType::MUL;
            if (!is_var && !is_array_access && !is_prop && !is_deref) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S056: Left side of assignment must be a variable, struct field, array/map access, or *pointer",
                    this->current_tok.pos
                ));
                return res.to_prs();
            }
            Token op_tok = this->current_tok;
            this->advance();
            
            AnyNode right;
            if (op_tok.type == TokenType::EQ) {
                size_t next_i = index + 1;
                if (this->current_tok.type == TokenType::IDENTIFIER &&
                    next_i < tokens.size() && tokens[next_i].type == TokenType::EQ) {
                    right = res.reg(this->assignment_expr());
                } else {
                    right = res.reg(this->expr());
                }
            } else {
                right = res.reg(this->expr());
            }
            
            if (res.error) return res.to_prs();
            if (is_prop) {
                auto& prop = std::get<std::shared_ptr<PropertyAccessNode>>(left);
                Token field = prop->property_name;

                TokenType binop_type;
                switch (op_tok.type) {
                    case TokenType::EQ:       binop_type = TokenType::EQ;   break;
                    case TokenType::PLUS_EQ:  binop_type = TokenType::PLUS; break;
                    case TokenType::MINUS_EQ: binop_type = TokenType::MINUS;break;
                    case TokenType::MUL_EQ:   binop_type = TokenType::MUL;  break;
                    case TokenType::DIV_EQ:   binop_type = TokenType::DIV;  break;
                    case TokenType::MOD_EQ:   binop_type = TokenType::MOD;  break;
                    default:
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S057: Unsupported op for struct fields", op_tok.pos));
                        return res.to_prs();
                }
                AnyNode lhsBase = clone_node(*(prop->base));

                if (binop_type == TokenType::EQ) {
                    return res.success(std::make_unique<FieldAssignNode>(
                        std::move(lhsBase),
                        field,
                        std::move(right)
                    ));
                }
                AnyNode rhsBase = clone_node(*(prop->base));
                
                auto readProp = std::make_shared<PropertyAccessNode>(
                    std::move(rhsBase),
                    prop->base_name_tok,
                    field
                );
                AnyNode readPropNode = AnyNode{ std::move(readProp) };
                Token bin_tok(binop_type, get_token_name(binop_type), op_tok.pos);
                AnyNode binExpr = AnyNode{
                    std::make_unique<BinOpNode>(
                        std::move(readPropNode),
                        bin_tok,
                        std::move(right)
                    )
                };
                return res.success(std::make_unique<FieldAssignNode>(
                    std::move(lhsBase),
                    field,
                    std::move(binExpr)
                ));
            }
            if (is_array_access) {
                if (op_tok.type != TokenType::EQ) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S058: Compound assignment (+=, -=, etc.) not supported for array/map access",
                        op_tok.pos
                    ));
                    return res.to_prs();
                }
                
                return res.success(std::make_unique<ArrayAssignNode>(
                    std::move(left),
                    std::move(right)
                ));
            }
            
            return res.success(std::make_unique<AssignExprNode>(
                std::move(left),
                op_tok,
                std::move(right)
            ));
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
            

            if constexpr (std::is_same_v<T, std::unique_ptr<Error>>) {
                return std::monostate{};
            } else if constexpr (std::is_same_v<T, ParseResult>) {
                return std::move(arg.node);
            } else if constexpr (
                std::is_same_v<T, std::unique_ptr<BinOpNode>> ||
                std::is_same_v<T, std::unique_ptr<UnaryOpNode>> ||
                std::is_same_v<T, std::unique_ptr<VarAccessNode>> ||
                std::is_same_v<T, std::unique_ptr<VarAssignNode>> ||
                std::is_same_v<T, std::unique_ptr<AssignExprNode>> ||
                std::is_same_v<T, std::unique_ptr<IfNode>> ||
                std::is_same_v<T, std::unique_ptr<StatementsNode>> ||
                std::is_same_v<T, std::unique_ptr<SwitchNode>> ||
                std::is_same_v<T, std::unique_ptr<BreakNode>> ||
                std::is_same_v<T, std::unique_ptr<WhileNode>> ||
                std::is_same_v<T, std::unique_ptr<ForNode>> ||
                std::is_same_v<T, std::unique_ptr<ContinueNode>> ||
                std::is_same_v<T, std::unique_ptr<CallNode>> ||
                std::is_same_v<T, std::shared_ptr<FuncDefNode>> ||
                std::is_same_v<T, std::unique_ptr<ReturnNode>> ||
                std::is_same_v<T, std::unique_ptr<MultiReturnNode>> ||
                std::is_same_v<T, std::unique_ptr<MultiVarDeclNode>> ||
                std::is_same_v<T, std::unique_ptr<ArrayDeclNode>> ||        
                std::is_same_v<T, std::unique_ptr<ArrayLiteralNode>> ||     
                std::is_same_v<T, std::unique_ptr<ArrayAccessNode>>  ||
                std::is_same_v<T, std::unique_ptr<QIfNode>> ||
                std::is_same_v<T, std::unique_ptr<QSwitchNode>> ||
                std::is_same_v<T, std::unique_ptr<FieldAssignNode>> ||
                std::is_same_v<T, std::unique_ptr<MapLiteralNode>> ||
                std::is_same_v<T, std::unique_ptr<NamespaceNode>> ||
                std::is_same_v<T, std::unique_ptr<TryCatchNode>>
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
            bool ran = false;
            while (this->current_tok.type == TokenType::SCOPE) {
                this->advance();
                param_type.value += "::" + this->current_tok.value;
                this->advance();
            }
            if (this->current_tok.type == TokenType::AMPERSAND) {
                this->advance();
                param_type.value += "&";
            }
            while (this->current_tok.type == TokenType::MUL) {
                this->advance();
                param_type.value += "*";
            }
            if (param_type.value == "short" || param_type.value == "long") {
                std::string modifier = param_type.value;

                if (this->current_tok.type != TokenType::KEYWORD) {
                    res.failure(std::make_unique<InvalidSyntaxError>("QC-S059: Expected type after 'short'/'long'", this->current_tok.pos));
                    return res.to_prs();
                }
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
                param_type.value = modifier + " " + base_type.value;
                param_type.pos = base_type.pos;
            }

            if (param_type.value == "list" && this->current_tok.type == TokenType::LESS) {
                this->advance();

                if (this->current_tok.type != TokenType::KEYWORD && !find_type(this->current_tok.value)) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S060: Expected element type in list<T>", this->current_tok.pos));
                    return res.to_prs();
                }
                Token elem_type = this->current_tok;
                this->advance();
                while (this->current_tok.type == TokenType::SCOPE) {
                    this->advance();
                    elem_type.value += "::" + this->current_tok.value;
                    this->advance();
                }
                if (current_tok.type == TokenType::AMPERSAND) {
                    this->advance();
                    elem_type.value += "&";
                }
                while (this->current_tok.type == TokenType::MUL) {
                    this->advance();
                    elem_type.value += "*";
                }
                if (this->current_tok.type != TokenType::MORE) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S061: Expected '>' in list<T>", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();

                param_type = Token(
                    TokenType::KEYWORD,
                    "list<" + elem_type.value + ">",
                    param_type.pos
                );
            }
            if (param_type.value == "map" && this->current_tok.type == TokenType::LESS) {
                this->advance();
                
                if (this->current_tok.type != TokenType::KEYWORD && !find_type(this->current_tok.value)) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S067: Expected key type in map<K, V>", this->current_tok.pos));
                    return res.to_prs();
                }
                Token key_type = this->current_tok;
                this->advance();
                
                if (this->current_tok.type != TokenType::COMMA) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S068: Expected ',' in map<K, V>", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                
                if (this->current_tok.type != TokenType::KEYWORD && !find_type(this->current_tok.value)) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S069: Expected value type in map<K, V>", this->current_tok.pos));
                    return res.to_prs();
                }
                Token value_type = this->current_tok;
                this->advance();
                
                if (this->current_tok.type != TokenType::MORE) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S070: Expected '>' in map<K, V>", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                
                param_type = Token(
                    TokenType::KEYWORD,
                    "map<" + key_type.value + ", " + value_type.value + ">",
                    param_type.pos
                );
            }
            while (this->current_tok.type == TokenType::LBRACKET) {
                this->advance();
                if (this->current_tok.type != TokenType::RBRACKET) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S062: Expected ']' after '[' in parameter", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                param_type.value += "[]"; 
            }
            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S063: Expected parameter name", this->current_tok.pos));
                return res.to_prs();
            }
            Token param_name = this->current_tok;
            this->advance();
            
            std::optional<AnyNode> default_val;
            if (this->current_tok.type == TokenType::EQ) {
                this->advance(); 
                default_val = res.reg(this->logical_or());
                if (res.error) return res.to_prs();
            }
            
            Parameter p;
            p.type = param_type;
            p.name = param_name;
            p.default_value = std::move(default_val);
            params.push_back(std::move(p));
            
            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                
                Token param_type = this->current_tok;
                this->advance();
                while (this->current_tok.type == TokenType::SCOPE) {
                    this->advance();
                    param_type.value += "::" + this->current_tok.value;
                    this->advance();
                }
                if (this->current_tok.type == TokenType::AMPERSAND) {
                    this->advance();
                    param_type.value += "&";
                }
                while (this->current_tok.type == TokenType::MUL) {
                    this->advance();
                    param_type.value += "*";
                }
                if (param_type.value == "short" || param_type.value == "long") {
                    std::string modifier = param_type.value;

                    if (this->current_tok.type != TokenType::KEYWORD) {
                        res.failure(std::make_unique<InvalidSyntaxError>("QC-S059: Expected type after 'short'/'long'", this->current_tok.pos));
                        return res.to_prs();
                    }
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
                    param_type.value = modifier + " " + base_type.value;
                    param_type.pos = base_type.pos;
                }
                if (param_type.value == "list" && this->current_tok.type == TokenType::LESS) {
                    this->advance(); 

                    if (this->current_tok.type != TokenType::KEYWORD && !find_type(this->current_tok.value)) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S060: Expected element type in list<T>", this->current_tok.pos));
                        return res.to_prs();
                    }
                    Token elem_type = this->current_tok;
                    this->advance();
                    while (this->current_tok.type == TokenType::SCOPE) {
                        this->advance();
                        elem_type.value += "::" + this->current_tok.value;
                        this->advance();
                    }
                    if (current_tok.type == TokenType::AMPERSAND) {
                        this->advance();
                        elem_type.value += "&";
                    }
                    while (this->current_tok.type == TokenType::MUL) {
                        this->advance();
                        elem_type.value += "*";
                    }
                    if (this->current_tok.type != TokenType::MORE) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S061: Expected '>' in list<T>", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance(); 

                    param_type = Token(
                        TokenType::KEYWORD,
                        "list<" + elem_type.value + ">",
                        param_type.pos
                    );
                }
                while (this->current_tok.type == TokenType::LBRACKET) {
                    this->advance();
                    if (this->current_tok.type != TokenType::RBRACKET) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S061: Expected ']' after '[' in parameter", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                    param_type.value += "[]"; 
                }
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S063: Expected parameter name", this->current_tok.pos));
                    return res.to_prs();
                }
                Token param_name = this->current_tok;
                this->advance();
                
                default_val = std::nullopt;
                if (this->current_tok.type == TokenType::EQ) {
                    this->advance();
                    default_val = res.reg(this->logical_or());
                    if (res.error) return res.to_prs();
                }
                
                Parameter p;
                p.type = param_type;
                p.name = param_name;
                p.default_value = std::move(default_val);
                params.push_back(std::move(p));
            }
        }
        
        if (this->current_tok.type != TokenType::RPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S064: Expected ')' after parameters", this->current_tok.pos));
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
                this->advance();
                
                while (this->current_tok.type == TokenType::COMMA) {
                    this->advance();
                    if (this->current_tok.type == TokenType::KEYWORD || this->user_types.count(this->current_tok.value) > 0) {
                        this->advance();
                    }
                }
            }
        }
        if (this->current_tok.type != TokenType::LBRACE) {
            res.failure(std::make_unique<InvalidSyntaxError>(
                "QC-S003: Expected '{' to start function body", this->current_tok.pos));
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
        
        auto body = std::make_unique<StatementsNode>(std::move(body_stmts), true);
        this->advance();
        return res.success(std::make_unique<FuncDefNode>(return_types, func_name, std::move(params), std::move(body), currentNamespace));
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
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected return type after '->'", this->current_tok.pos));
                    return res.to_prs();
                }
                
                return_types.push_back(this->current_tok);
                this->advance();
                
                while (this->current_tok.type == TokenType::COMMA) {
                    this->advance();
                    
                    if (this->current_tok.type != TokenType::KEYWORD) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Expected return type after ','", this->current_tok.pos));
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

            if (std::holds_alternative<std::unique_ptr<Error>>(fn_pr))
                return fn_pr;

            AnyNode fn_node;
            if (std::holds_alternative<std::shared_ptr<FuncDefNode>>(fn_pr))
                fn_node = std::get<std::shared_ptr<FuncDefNode>>(std::move(fn_pr));
            else
                fn_node = std::get<std::shared_ptr<FuncDefNode>>(std::move(fn_pr));

            if (this->current_tok.type == TokenType::LPAREN)
                return this->call(std::move(fn_node));

            return res.success(std::move(fn_node));
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "if") {
            return this->if_expr();
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "try") {
            return this->try_catch_expr();
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "qif") {
            return this->qif_expr();
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "switch") {
            return this->switch_stmt();
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "qswitch") {
            return this->qswitch_stmt();
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "while") {
            return this->while_stmt();
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "for") {
            return this->for_stmt();
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "foreach") {
            this->advance();
            
            if (this->current_tok.type != TokenType::LPAREN) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected '(' after 'foreach'", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            
            if (this->current_tok.type != TokenType::KEYWORD) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected type in foreach", this->current_tok.pos));
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
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected variable name in foreach", this->current_tok.pos));
                return res.to_prs();
            }
            Token elem_name = this->current_tok;
            this->advance();
            
            if (this->current_tok.type != TokenType::KEYWORD || this->current_tok.value != "in") {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected 'in' in foreach", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            
            AnyNode collection = res.reg(this->logical_or());
            if (res.error) {
                return res.to_prs();
            }
            if (this->current_tok.type != TokenType::RPAREN) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S016: Expected ')' after foreach", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            if (this->current_tok.type != TokenType::LBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S003: Expected '{' to start foreach body", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            std::vector<AnyNode> stmts;
            while (this->current_tok.type != TokenType::RBRACE &&
                this->current_tok.type != TokenType::EOFT) {
                Prs st = this->statement();
                if (std::holds_alternative<std::unique_ptr<Error>>(st)) {
                    res.failure(std::get<std::unique_ptr<Error>>(std::move(st)));
                    return res.to_prs();
                }
                AnyNode any_stmt = this->prs_to_anynode(std::move(st));
                stmts.push_back(std::move(any_stmt));
            }

            if (this->current_tok.type != TokenType::RBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected '}' to end foreach body", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            auto body_block = std::make_unique<StatementsNode>(std::move(stmts), true);

            return res.success(std::make_unique<ForeachNode>(
                elem_type, elem_name, std::move(collection), std::move(body_block)));
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
        bool is_abstract_class = false;
        bool is_final_class = false;
        if (tok.type == TokenType::KEYWORD && tok.value == "abstract") {
            this->advance();
            if (this->current_tok.type != TokenType::KEYWORD ||
                this->current_tok.value != "class") {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected 'class' after 'abstract'", this->current_tok.pos));
                return res.to_prs();
            }
            is_abstract_class = true;
            tok = this->current_tok;
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "final") {
            this->advance();
            if (this->current_tok.type != TokenType::KEYWORD ||
                this->current_tok.value != "class") {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected 'class' after 'final'", this->current_tok.pos));
                return res.to_prs();
            }
            is_final_class = true;
            tok = this->current_tok;
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "class") {
            this->advance();

            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected class name", this->current_tok.pos));
                return res.to_prs();
            }
            Token class_name = this->current_tok;
            this->advance();      
            std::string baseName = "";
            if (this->current_tok.type == TokenType::COLON) {
                advance();
                if (current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected base name after ':'", this->current_tok.pos));
                    return res.to_prs();
                }
                baseName = current_tok.value;
                advance();
            }
            if (!baseName.empty()) {
                auto* base_ptr = find_type(baseName);
                if (base_ptr &&
                    base_ptr->kind == UserTypeKind::Class &&
                    base_ptr->is_final_class) {
                    auto& baseInfo = *base_ptr;
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Cannot inherit from final class '" + baseName + "'",
                        class_name.pos));
                    return res.to_prs();
                }
            }    
            if (this->current_tok.type != TokenType::LBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S003: Expected '{' after class name", this->current_tok.pos));
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
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-UT01: Redefinition of type '" + class_name.value + "'",
                    class_name.pos));
                return res.to_prs();
            }
            dummy.namespace_path = currentNamespace;
            info.namespace_path = currentNamespace;
            std::string full_key = currentNamespace.empty() 
                ? class_name.value 
                : currentNamespace + "::" + class_name.value;
            user_types[full_key] = std::move(dummy);

            while (this->current_tok.type != TokenType::RBRACE &&
                this->current_tok.type != TokenType::EOFT) {

                std::string access = "public";
                bool is_final_method = false;

                if (this->current_tok.type == TokenType::KEYWORD &&
                    this->current_tok.value == "final") {
                    is_final_method = true;
                    this->advance();
                }
                if (this->current_tok.type == TokenType::KEYWORD &&
                (this->current_tok.value == "public" ||
                    this->current_tok.value == "private" ||
                    this->current_tok.value == "protected")) {
                    access = this->current_tok.value;
                    this->advance();
                }
                if (this->current_tok.type == TokenType::KEYWORD &&
                    this->current_tok.value == "final") {
                    is_final_method = true;
                    this->advance();
                }

                if (this->current_tok.type == TokenType::IDENTIFIER &&
                    this->current_tok.value == class_name.value) {

                    if (is_abstract_class) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Cannot make constructor on abstract class '" + class_name.value + "'",
                            class_name.pos));
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
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "Expected '(' after constructor name", this->current_tok.pos));
                            return res.to_prs();
                        }

                        auto ctor_pr = this->func_def_multi({}, std::nullopt);
                        if (std::holds_alternative<std::unique_ptr<Error>>(ctor_pr))
                            return ctor_pr;

                        auto fn = std::get<std::shared_ptr<FuncDefNode>>(std::move(ctor_pr));
                        ClassMethodInfo mi;
                        mi.name_tok = ctor_name;
                        mi.params.clear();
                        mi.params.reserve(fn->params.size());
                        for (auto it = fn->params.begin(); it != fn->params.end(); ++it) {
                            mi.params.push_back(std::move(*it));
                        }
                        mi.return_types = {};
                        mi.body = std::move(fn->body);
                        mi.is_constructor = true;
                        mi.access = access;

                        info.classMethods.push_back(std::move(mi));
                        continue;
                    }
                }
                if (this->current_tok.type != TokenType::KEYWORD &&
                    this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected type or constructor in class body", this->current_tok.pos));
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
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "QC-N001: Expected identifier after '::'", this->current_tok.pos));
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
                    }
                    else if (this->current_tok.type == TokenType::KEYWORD) {
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

                            if (this->current_tok.type != TokenType::KEYWORD &&
                                this->current_tok.type != TokenType::IDENTIFIER) {
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "Expected element type in list<T>", this->current_tok.pos));
                                return false;
                            }
                            std::string elem_type = this->current_tok.value;
                            this->advance();

                            if (this->current_tok.type != TokenType::MORE) {
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "Expected '>' after list element type", this->current_tok.pos));
                                return false;
                            }
                            this->advance();

                            field_type = "list<" + elem_type + ">";
                        }
                        else if (this->current_tok.type == TokenType::LBRACKET) {
                            this->advance();
                            if (this->current_tok.type != TokenType::RBRACKET) {
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "QC-S061: Expected ']' after '[' in list type", this->current_tok.pos));
                                return false;
                            }
                            this->advance();
                            field_type = "list<" + base_type.value + ">";
                        }
                        else if (base_type.value == "map") {
                            if (this->current_tok.type != TokenType::LESS) {
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "QC-S066: Expected '<' after map for key type", this->current_tok.pos));
                                return false;
                            }
                            this->advance();

                            if (this->current_tok.type != TokenType::KEYWORD &&
                                this->current_tok.type != TokenType::IDENTIFIER) {
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "QC-S067: Expected key type in map", this->current_tok.pos));
                                return false;
                            }
                            std::string key_type = this->current_tok.value;
                            this->advance();

                            if (this->current_tok.type != TokenType::COMMA) {
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "QC-S068: Expected ',' between key and value type in map", this->current_tok.pos));
                                return false;
                            }
                            this->advance();

                            if (this->current_tok.type != TokenType::KEYWORD &&
                                this->current_tok.type != TokenType::IDENTIFIER) {
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "QC-S069: Expected value type in map", this->current_tok.pos));
                                return false;
                            }
                            std::string value_type = this->current_tok.value;
                            this->advance();

                            if (this->current_tok.type != TokenType::MORE) {
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "QC-S070: Expected '>' after map value type", this->current_tok.pos));
                                return false;
                            }
                            this->advance();

                            field_type = "map<" + key_type + ", " + value_type + ">";
                        }
                    } else {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S071: Expected type in class body", this->current_tok.pos));
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
                if (this->current_tok.type == TokenType::IDENTIFIER &&
                    this->current_tok.value != "operator") {
                    name_tok = this->current_tok;
                    this->advance();
                }
                else if (this->current_tok.type == TokenType::KEYWORD &&
                        this->current_tok.value == "operator") {
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
                        case TokenType::COLLAPSE_AND:
                            break;
                        default:
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "Unsupported operator in operator method", op_tok.pos));
                            return res.to_prs();
                    }
                            std::string op_name;
                    switch (op_tok.type) {
                        case TokenType::PLUS:        op_name = "operator+";    break;
                        case TokenType::MINUS:       op_name = "operator-";    break;
                        case TokenType::MUL:         op_name = "operator*";    break;
                        case TokenType::DIV:         op_name = "operator/";    break;
                        case TokenType::EQ_TO:       op_name = "operator==";   break;
                        case TokenType::NOT_EQ:      op_name = "operator!=";   break;
                        case TokenType::EQ:          op_name = "operator=";    break;
                        case TokenType::NOT:         op_name = "operator!";    break;
                        case TokenType::AND:         op_name = "operator&&";   break;
                        case TokenType::OR:          op_name = "operator||";   break;
                        case TokenType::MORE:        op_name = "operator>";    break;
                        case TokenType::LESS:        op_name = "operator<";    break;
                        case TokenType::MORE_EQ:     op_name = "operator>=";   break;
                        case TokenType::LESS_EQ:     op_name = "operator<=";   break;
                        case TokenType::POWER:       op_name = "operator^*";   break;
                        case TokenType::MOD:         op_name = "operator%";    break;
                        case TokenType::XOR:         op_name = "operator^";    break;
                        case TokenType::QNOT:        op_name = "operator!!";   break;
                        case TokenType::QAND:        op_name = "operator&&&";  break;
                        case TokenType::QOR:         op_name = "operator|||";  break;
                        case TokenType::QXOR:        op_name = "operator^^";   break;
                        case TokenType::COLLAPSE_OR: op_name = "operator|&|";  break;
                        case TokenType::COLLAPSE_AND:op_name = "operator&|&";  break;
                    }

                    name_tok = Token(TokenType::IDENTIFIER, op_name, op_tok.pos);
                    this->advance();
                }
                else {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected method or field name after type(s)", this->current_tok.pos));
                    return res.to_prs();
                }
                if (this->current_tok.type == TokenType::LPAREN) {
                    ClassMethodInfo mi;
                    mi.name_tok = name_tok;
                    if (!info.baseClassName.empty()) {
                        auto* base_ptr = find_type(baseName);
                        if (base_ptr &&
                            base_ptr->kind == UserTypeKind::Class &&
                            base_ptr->is_final_class) {
                            auto& baseInfo = *base_ptr;
                            for (auto& bm : baseInfo.classMethods) {
                                if (bm.name_tok.value == mi.name_tok.value && bm.is_final) {
                                    res.failure(std::make_unique<InvalidSyntaxError>(
                                        "Cannot override final method '" + mi.name_tok.value +
                                        "' from base class '" + info.baseClassName + "'",
                                        mi.name_tok.pos));
                                    return res.to_prs();
                                }
                            }
                        }
                    }

                    auto m_pr = this->func_def_multi(type_list, std::make_optional(name_tok));
                    if (std::holds_alternative<std::unique_ptr<Error>>(m_pr))
                        return m_pr;

                    auto fn = std::get<std::shared_ptr<FuncDefNode>>(std::move(m_pr));

                    mi.params.clear();
                    mi.params.reserve(fn->params.size());
                    for (auto it = fn->params.begin(); it != fn->params.end(); ++it) {
                        mi.params.push_back(std::move(*it)); 
                    }
                    mi.return_types   = fn->return_types;
                    mi.body           = std::move(fn->body);
                    mi.is_constructor = false;
                    mi.is_final       = is_final_method;
                    mi.access         = access;

                    info.classMethods.push_back(std::move(mi));
                    continue;
                }
                if (type_list.size() != 1) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Class fields cannot have multiple types", name_tok.pos));
                    return res.to_prs();
                }
                std::string field_type = type_list[0].value;
                int array_dims = 0;
                while (this->current_tok.type == TokenType::LBRACKET) {
                    this->advance();
                    if (this->current_tok.type == TokenType::KEYWORD) {
                        this->advance();
                    }
                    if (this->current_tok.type != TokenType::RBRACKET) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S061: Expected ']' after '[' in array", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                    array_dims++;
                }
                for (int i = 0; i < array_dims; ++i) field_type += "[]";

                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected ';' after field declaration", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();

                ClassField cf;
                cf.name   = name_tok.value;
                cf.type   = field_type;
                cf.access = access;
                info.classFields.push_back(std::move(cf));
            }

            if (this->current_tok.type != TokenType::RBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected '}' at end of class", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
         full_key = currentNamespace.empty() 
                ? class_name.value 
                : currentNamespace + "::" + class_name.value;
            user_types[full_key] = std::move(info);
            return res.success(std::monostate{});
        }
        
        if (tok.type == TokenType::KEYWORD && tok.value == "namespace") {
            ParseResult res;
            this->advance();

            if (current_tok.type != TokenType::IDENTIFIER) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected namespace name", current_tok.pos));
                return res.to_prs();
            }

            Token nsName = current_tok;
            this->advance();

            if (current_tok.type != TokenType::LBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-N004: Expected '{' after namespace name", current_tok.pos));
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

            while (current_tok.type != TokenType::RBRACE &&
                current_tok.type != TokenType::EOFT) {

                Prs st = statement();
                if (std::holds_alternative<std::unique_ptr<Error>>(st)) {
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

                body.push_back(prs_to_anynode(std::move(st)));
            }

            if (current_tok.type != TokenType::RBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-N005: Expected '}' at end of namespace", current_tok.pos));
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

            return res.success(
                std::make_unique<NamespaceNode>(nsName.value, std::move(body))
            );
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "struct") {
            this->advance(); 

            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S065: Expected struct name", this->current_tok.pos));
                return res.to_prs();
            }
            Token struct_name = this->current_tok;
            this->advance();

            if (this->current_tok.type != TokenType::LBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S003: Expected '{' after struct name", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            std::vector<StructField> fields;

            while (this->current_tok.type != TokenType::RBRACE &&
                this->current_tok.type != TokenType::EOFT) {
                
                std::string field_type;
                bool is_user_type = false;
                if (this->current_tok.type == TokenType::IDENTIFIER) {
                    is_user_type = true;
                    field_type = this->current_tok.value;
                    this->advance();
                    while (this->current_tok.type == TokenType::SCOPE) {
                        this->advance();
                        
                        if (this->current_tok.type != TokenType::IDENTIFIER) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "QC-N001: Expected identifier after '::'", this->current_tok.pos));
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
                }
                else if (this->current_tok.type == TokenType::KEYWORD) {
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
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "QC-S061: Expected ']' after '[' in list type", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                        field_type = "list<" + base_type.value + ">";
                    }
                    else if (base_type.value == "map") {
                        if (this->current_tok.type != TokenType::LESS) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "QC-S066: Expected '<' after map for key type", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                        
                        if (this->current_tok.type != TokenType::KEYWORD && 
                            this->current_tok.type != TokenType::IDENTIFIER) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "QC-S067: Expected key type in map", this->current_tok.pos));
                            return res.to_prs();
                        }
                        std::string key_type = this->current_tok.value;
                        this->advance();

                        if (this->current_tok.type != TokenType::COMMA) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "QC-S068: Expected ',' between key and value type in map", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();

                        if (this->current_tok.type != TokenType::KEYWORD && 
                            this->current_tok.type != TokenType::IDENTIFIER) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "QC-S069: Expected value type in map", this->current_tok.pos));
                            return res.to_prs();
                        }
                        std::string value_type = this->current_tok.value;
                        this->advance();

                        if (this->current_tok.type != TokenType::MORE) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "QC-S070: Expected '>' after map value type", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();

                        field_type = "map<" + key_type + ", " + value_type + ">";
                    }
                } else {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S071: Expected field type in struct", this->current_tok.pos));
                    return res.to_prs();
                }

                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S072: Expected field name in struct", this->current_tok.pos));
                    return res.to_prs();
                }
                Token field_name = this->current_tok;
                this->advance();

                int array_dims = 0;
                while (this->current_tok.type == TokenType::LBRACKET) {
                    this->advance();
                    if (this->current_tok.type == TokenType::INT) {
                        this->advance();
                    }
                    if (this->current_tok.type != TokenType::RBRACKET) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S061: Expected ']' after '[' in array", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                    array_dims++;
                }

                for (int i = 0; i < array_dims; ++i) field_type += "[]";

                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();

                fields.push_back({ field_name.value, field_type });
            }
            if (this->current_tok.type != TokenType::RBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S073: Expected '}' at end of struct", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance(); 

            if (this->current_tok.type == TokenType::SEMICOLON) {
                this->advance();
            }
            if (user_types.contains(struct_name.value)) {
                res.failure(std::make_unique<InvalidSyntaxError>("QC-UT01: Redefinition of struct '" + struct_name.value + "'", struct_name.pos));
                return res.to_prs();
            }
            UserTypeInfo info;
            info.kind   = UserTypeKind::Struct;
            info.fields = std::move(fields);
            info.namespace_path = currentNamespace;
            std::string full_key = currentNamespace.empty() 
                ? struct_name.value 
                : currentNamespace + "::" + struct_name.value;
            user_types[full_key] = std::move(info);
            return res.success(std::monostate{});
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "type") {
            this->advance();

            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S074: Expected type name after 'type'", this->current_tok.pos));
                return res.to_prs();
            }
            Token type_name = this->current_tok;
            this->advance();

            if (this->current_tok.type != TokenType::EQ) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S075: Expected '=' after type name '" + type_name.value + "'",
                    this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            auto parse_type_atom = [&](Token first_tok) -> UnionMember {
                std::string type_str;
                switch (first_tok.type) {
                    case TokenType::STRING:  return UnionMember{ "string:\"" + first_tok.value + "\"" };
                    case TokenType::INT:     return UnionMember{ "int:"    + first_tok.value };
                    case TokenType::FLOAT:   return UnionMember{ "float:"  + first_tok.value };
                    case TokenType::DOUBLE:  return UnionMember{ "double:" + first_tok.value };
                    case TokenType::CHAR:    return UnionMember{ "char:"   + first_tok.value };
                    case TokenType::BOOL:    return UnionMember{ "bool:"   + first_tok.value };
                    case TokenType::QBOOL:   return UnionMember{ "qbool:"  + first_tok.value };
                    default:
                        break;
                }
                type_str = first_tok.value;
                int array_dims = 0;
                while (this->current_tok.type == TokenType::LBRACKET) {
                    this->advance();
                    if (this->current_tok.type == TokenType::INT) {
                        this->advance();
                    }
                    if (this->current_tok.type != TokenType::RBRACKET) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S061: Expected ']' after '[' in array", this->current_tok.pos));
                        return UnionMember{ "" };
                    }
                    this->advance();
                    array_dims++;
                }
                for (int i = 0; i < array_dims; ++i) {
                    type_str += "[]";
                }

                return UnionMember{ type_str };
            };

            auto is_type_or_literal_token = [&](TokenType tt) {
                return tt == TokenType::STRING  ||
                    tt == TokenType::IDENTIFIER ||
                    tt == TokenType::KEYWORD   ||
                    tt == TokenType::INT       ||
                    tt == TokenType::FLOAT     ||
                    tt == TokenType::DOUBLE    ||
                    tt == TokenType::BOOL      ||
                    tt == TokenType::QBOOL     ||
                    tt == TokenType::CHAR;
            };

            if (!is_type_or_literal_token(this->current_tok.type)) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S076: Expected type or literal in type alias",
                    this->current_tok.pos));
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
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S077: Expected type or literal after '|' in type alias",
                        this->current_tok.pos));
                    return res.to_prs();
                }

                Token t = this->current_tok;
                this->advance();
                members.push_back(parse_type_atom(t));
            }

            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            if (user_types.contains(type_name.value)) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-UT01: Redefinition of type '" + type_name.value + "'",
                    type_name.pos
                ));
                return res.to_prs();
            }

            UserTypeInfo info;
            if (members.size() == 1) {
                info.kind = UserTypeKind::Alias;
                info.aliasTarget = members[0].type;
            } else {
                info.kind = UserTypeKind::Union;
                info.members = std::move(members);
            }
            info.namespace_path = currentNamespace;
            std::string full_key = currentNamespace.empty() 
                ? type_name.value 
                : currentNamespace + "::" + type_name.value;
            user_types[full_key] = std::move(info);
            return res.success(std::monostate{});
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "enum") {
            this->advance();

            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S080: Expected enum name", this->current_tok.pos));
                return res.to_prs();
            }
            Token enum_name = this->current_tok;
            this->advance();

            if (this->current_tok.type != TokenType::LBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S003: Expected '{' after enum name", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            std::vector<UnionMember> members;
            std::vector<EnumEntry> entries;

            auto parse_type_atom = [&](Token tok) -> std::string {
                switch (tok.type) {
                    case TokenType::STRING:  return "string:\"" + tok.value + "\"";
                    case TokenType::INT:     return "int:" + tok.value;
                    case TokenType::FLOAT:   return "float:" + tok.value;
                    case TokenType::DOUBLE:  return "double:" + tok.value;
                    case TokenType::CHAR:    return "char:" + tok.value;
                    case TokenType::BOOL:    return "bool:" + tok.value;
                    case TokenType::QBOOL:   return "qbool:" + tok.value;
                    default:                 return tok.value;
                }
            };

            while (this->current_tok.type != TokenType::RBRACE &&
                this->current_tok.type != TokenType::EOFT) {

                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S081: Expected enum member name", this->current_tok.pos));
                    return res.to_prs();
                }
                Token member_name = this->current_tok;
                this->advance();

                if (this->current_tok.type != TokenType::EQ) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S082: Expected '=' after enum member name '" + member_name.value + "'",
                        this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();

                Token value_tok = this->current_tok;
                this->advance();

                std::string typeAtom = parse_type_atom(value_tok);
                members.push_back(UnionMember{ typeAtom });
                entries.push_back(EnumEntry{ member_name.value, typeAtom });

                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S083: Expected ';' after enum member", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
            }

            if (this->current_tok.type != TokenType::RBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-S084: Expected '}' at end of enum", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            if (user_types.contains(enum_name.value)) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "QC-UT01: Redefinition of type '" + enum_name.value + "'",
                    enum_name.pos));
                return res.to_prs();
            }

            UserTypeInfo info;
            info.kind = UserTypeKind::Enum;
            info.members = std::move(members);
            info.enumEntries = std::move(entries);
            info.namespace_path = currentNamespace;
            std::string full_key = currentNamespace.empty() 
                ? enum_name.value 
                : currentNamespace + "::" + enum_name.value;
            user_types[full_key] = std::move(info);

            return res.success(std::monostate{});
        }
        if (tok.type == TokenType::KEYWORD) {
            bool is_const = false;
            
            if (tok.value == "const") {
                is_const = true;
                this->advance();
                tok = this->current_tok;
                
                if (tok.type != TokenType::KEYWORD) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S011: Expected type after 'const'", this->current_tok.pos));
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
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S059: Expected type after " + modifier, this->current_tok.pos));
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
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S067: Expected key type in map<K, V>", this->current_tok.pos));
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
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S068: Expected ',' in map<K, V>", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                
                if (this->current_tok.type != TokenType::KEYWORD) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S069: Expected value type in map<K, V>", this->current_tok.pos));
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
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S070: Expected '>' in map<K, V>", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                
                type_tok = Token(
                    TokenType::KEYWORD,
                    "map<" + key_type.value + ", " + value_type.value + ">",
                    type_tok.pos
                );
                if (this->current_tok.type == TokenType::IDENTIFIER) {
                    Token var_name = this->current_tok;
                    
                    if (this->peek().type == TokenType::EQ || 
                        this->peek().type == TokenType::SEMICOLON) {
                        this->advance();
                        std::vector<std::pair<AnyNode, AnyNode>> init_pairs;
                        
                        if (this->current_tok.type == TokenType::EQ) {
                            this->advance();
                            
                            if (this->current_tok.type != TokenType::LBRACE) {
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "QC-S003: Expected '{' for map initialization", this->current_tok.pos));
                                return res.to_prs();
                            }
                            this->advance();
                            
                            if (this->current_tok.type != TokenType::RBRACE) {
                                AnyNode key = res.reg(this->logical_or());
                                if (res.error) return res.to_prs();
                                
                                if (this->current_tok.type != TokenType::COLON) {
                                    res.failure(std::make_unique<InvalidSyntaxError>(
                                        "Expected ':' after key", this->current_tok.pos));
                                    return res.to_prs();
                                }
                                this->advance();
                                
                                AnyNode value = res.reg(this->logical_or());
                                if (res.error) return res.to_prs();
                                
                                init_pairs.emplace_back(std::move(key), std::move(value));
                                
                                while (this->current_tok.type == TokenType::COMMA) {
                                    this->advance();
                                    
                                    if (this->current_tok.type == TokenType::RBRACE) break;
                                    
                                    AnyNode key = res.reg(this->logical_or());
                                    if (res.error) return res.to_prs();
                                    
                                    if (this->current_tok.type != TokenType::COLON) {
                                        res.failure(std::make_unique<InvalidSyntaxError>(
                                            "Expected ':' after key", this->current_tok.pos));
                                        return res.to_prs();
                                    }
                                    this->advance();
                                    
                                    AnyNode value = res.reg(this->logical_or());
                                    if (res.error) return res.to_prs();
                                    
                                    init_pairs.emplace_back(std::move(key), std::move(value));
                                }
                            }
                            
                            if (this->current_tok.type != TokenType::RBRACE) {
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "Expected '}' after map initialization", this->current_tok.pos));
                                return res.to_prs();
                            }
                            this->advance();
                        }
                        
                        if (this->current_tok.type != TokenType::SEMICOLON) {
                            res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                        
                        return res.success(std::make_unique<MapDeclNode>(
                            is_const, key_type, value_type, var_name, std::move(init_pairs)));
                    }
                }
                
            }
            bool is_list = false;
            if (type_tok.value == "list" && this->current_tok.type == TokenType::LESS) {
                this->advance();
                
                if (this->current_tok.type != TokenType::KEYWORD) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S060: Expected element type in list<T>", this->current_tok.pos));
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
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S061: Expected '>' in list<T>", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                
                type_tok = Token(
                    TokenType::KEYWORD,
                    "list<" + elem_type.value + ">",
                    type_tok.pos
                );
                is_list = true;
            }
            
            while (this->current_tok.type == TokenType::LBRACKET) {
                this->advance();
                if (this->current_tok.type != TokenType::RBRACKET) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S049: Expected ']'", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                type_tok.value += "[]";
            }

            if (type_tok.value.find("[][]") != std::string::npos) {
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Multi-dimensional types can only be used in function returns", this->current_tok.pos));
                    return res.to_prs();
                }
                
                Token func_name = this->current_tok;
                this->advance();
                
                if (this->current_tok.type == TokenType::LPAREN) {
                    std::vector<Token> return_types = {type_tok};
                    return this->func_def_multi(return_types, func_name);
                }
                
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected '(' after function name", this->current_tok.pos));
                return res.to_prs();
            }
            
            std::vector<Token> return_types = {type_tok};
            if (this->current_tok.type == TokenType::COMMA) {
                while (this->current_tok.type == TokenType::COMMA) {
                    this->advance();
                    
                    if (this->current_tok.type != TokenType::KEYWORD && !find_type(this->current_tok.value)) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Expected type", this->current_tok.pos));
                        return res.to_prs();
                    }
                    
                    return_types.push_back(this->current_tok);
                    this->advance();
                }
                
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S085: Expected identifier", this->current_tok.pos));
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
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Expected closing bracket ']'", this->current_tok.pos
                        ));
                        return res.to_prs();
                    }

                    this->advance();
                    sizes.push_back(size);
                }

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
                    "QC-S085: Expected identifier", this->current_tok.pos));
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
                    res.failure(std::make_unique<InvalidSyntaxError>("QC-S049: Expected ']'", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
            }

            bool is_array = (dimensions > 0);
            if (this->current_tok.type == TokenType::LPAREN) {
                auto func_def = res.reg(this->func_def_multi(return_types, name_tok));
                if (res.error) return res.to_prs();
                return res.success(std::move(func_def));
            }
            std::vector<Token> var_names = {name_tok};

            if (this->current_tok.type == TokenType::COMMA) {
                while (this->current_tok.type == TokenType::COMMA) {
                    this->advance();
                    
                    if (this->current_tok.value == "list" && this->index + 1 < this->tokens.size() && this->tokens[this->index + 1].type == TokenType::LESS) {
                        Token list_tok = this->current_tok;
                        this->advance(); 
                        this->advance();
                        
                        if (this->current_tok.type != TokenType::KEYWORD) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "Expected element type in list<T>", this->current_tok.pos));
                            return res.to_prs();
                        }
                        
                        Token elem_type = this->current_tok;
                        this->advance();
                        
                        if (this->current_tok.type != TokenType::MORE) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "Expected '>' in list<T>", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                        
                        Token type = Token(
                            TokenType::KEYWORD,
                            "list<" + elem_type.value + ">",
                            list_tok.pos
                        );
                        return_types.push_back(type);
                    }
                    else if (this->current_tok.type != TokenType::KEYWORD) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Expected type", this->current_tok.pos));
                        return res.to_prs();
                    } else {
                        Token type = this->current_tok;
                        this->advance();
                        
                        while (this->current_tok.type == TokenType::LBRACKET) {
                            this->advance();
                            if (this->current_tok.type == TokenType::INT) {
                                this->advance();
                            }
                            if (this->current_tok.type != TokenType::RBRACKET) {
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "Expected ']'", this->current_tok.pos));
                                return res.to_prs();
                            }
                            this->advance();
                            type.value += "[]";
                        }
                        
                        return_types.push_back(type);
                    }
                    
                    if (this->current_tok.type != TokenType::IDENTIFIER) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S085: Expected identifier", this->current_tok.pos));
                        return res.to_prs();
                    }
                    var_names.push_back(this->current_tok);
                    this->advance();
                }
                
                if (this->current_tok.type != TokenType::EQ) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected '=' in multi-variable declaration", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                
                AnyNode value = res.reg(this->qout_expr());
                if (res.error) return res.to_prs();
                
                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                
                if (return_types.size() != var_names.size()) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Number of types must match number of variables", var_names[0].pos));
                    return res.to_prs();
                }
                
                return res.success(std::make_unique<MultiVarDeclNode>(
                    is_const, return_types, var_names, std::move(value)));
            }

            if (is_list) {
                AnyNode value;
                if (this->current_tok.type == TokenType::EQ) {
                    this->advance();
                    value = res.reg(this->qout_expr());
                    if (res.error) return res.to_prs();
                } else {
                    if (is_const) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-T007: const variables and references must be initialized", name_tok.pos));
                        return res.to_prs();
                    }
                    value = std::make_unique<ArrayLiteralNode>(std::vector<AnyNode>{}, name_tok.pos);
                }
                
                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                
                return res.success(std::make_unique<ListDeclNode>(
                    is_const, type_tok, name_tok, std::move(value)));
            }

            if (is_array) {
                AnyNode value;
                if (this->current_tok.type == TokenType::EQ) {
                    this->advance();
                    value = res.reg(this->qout_expr());
                    if (res.error) return res.to_prs();
                } else {
                    if (is_const) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-T007: const variables must be initialized", name_tok.pos));
                        return res.to_prs();
                    }
                    value = default_value_for_type(type_tok, name_tok.pos);
                }
                
                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                
                return res.success(std::make_unique<ArrayDeclNode>(
                            is_const, type_tok, name_tok, std::move(value), 
                    dimensions, std::move(array_sizes)));
            }
            AnyNode value;
            if (this->current_tok.type == TokenType::EQ) {
                this->advance();
                if (is_reference) {
                    if (this->current_tok.type != TokenType::IDENTIFIER) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-R001: Cannot assign an expression to a reference.", var_names[0].pos));
                        return res.to_prs();
                    }
                    
                    Token target = this->current_tok;
                    this->advance();
                    if (this->current_tok.type != TokenType::SEMICOLON) {
                        res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                    auto ref_node = RefVarDeclNode(
                        type_tok, var_names[0], target, type_tok.pos
                    );
                    return res.success(std::move(ref_node));
                }
                value = res.reg(this->qout_expr());
                if (res.error) return res.to_prs();
            } else {
                if (is_const || is_reference) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "const variables and references must be initialized", var_names[0].pos));
                    return res.to_prs();
                }
                value = default_value_for_type(type_tok, var_names[0].pos);
            }

            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            return res.success(std::make_unique<VarAssignNode>(
                is_const, return_types[0], var_names[0], std::move(value)));
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
                if (type_ptr) {
                    is_type = true;
                }
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
                            res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                        return res.success(std::move(expr));
                    }
                    
                    Token first_type = this->consume_qualified_name();
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
                            }
                            else if (peek.type == TokenType::IDENTIFIER) {
                                size_t saved = this->index;
                                Token saved_tok = this->current_tok;
                                
                                this->advance();
                                auto peek_qual = this->try_parse_qualified_name();
                                
                                if (peek_qual.has_value()) {
                                    std::string base_name = *peek_qual;
                                    size_t last_colon = peek_qual->rfind("::");
                                    if (last_colon != std::string::npos) {
                                        base_name = peek_qual->substr(last_colon + 2);
                                    }
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
                                        if (last_colon != std::string::npos) {
                                            base_name = next_qual->substr(last_colon + 2);
                                        }
                                        
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
                                            res.failure(std::make_unique<InvalidSyntaxError>(
                                                "Expected return type after ','", this->current_tok.pos));
                                            return res.to_prs();
                                        }
                                    } else {
                                        res.failure(std::make_unique<InvalidSyntaxError>(
                                            "Expected return type after ','", this->current_tok.pos));
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
                                    res.failure(std::make_unique<InvalidSyntaxError>(
                                        "Expected return type after ','", this->current_tok.pos));
                                    return res.to_prs();
                                }
                            }
                        }
                    }

                    if (this->current_tok.type != TokenType::IDENTIFIER) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S085: Expected name after types", this->current_tok.pos));
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
                            } 
                            else if (this->current_tok.type == TokenType::IDENTIFIER) {
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
                                        res.failure(std::make_unique<InvalidSyntaxError>(
                                            "Expected type after ','", this->current_tok.pos));
                                        return res.to_prs();
                                    }
                                } else {
                                    res.failure(std::make_unique<InvalidSyntaxError>(
                                        "Expected type after ','", this->current_tok.pos));
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
                                res.failure(std::make_unique<InvalidSyntaxError>(
                                    "Expected variable name", this->current_tok.pos));
                                return res.to_prs();
                            }
                            
                            var_names.push_back(this->current_tok);
                            this->advance();
                        }
                        
                        // Now expect = and the value
                        if (this->current_tok.type != TokenType::EQ) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "Expected '=' in multi-var declaration", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                        
                        AnyNode value = res.reg(this->qout_expr());
                        if (res.error) return res.to_prs();
                        
                        if (this->current_tok.type != TokenType::SEMICOLON) {
                            res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                        
                        return res.success(std::make_unique<MultiVarDeclNode>(false, var_types, var_names, std::move(value)));
                    }
                    if (this->current_tok.type == TokenType::LPAREN) {
                        auto func_def = res.reg(this->func_def_multi(return_types, name_tok));
                        if (res.error) return res.to_prs();
                        return res.success(std::move(func_def));
                    }

                    if (return_types.size() > 1) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Invalid syntax: multiple types before variable name; "
                            "did you mean to define a function?", name_tok.pos));
                        return res.to_prs();
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
                        res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();

                    return res.success(std::make_unique<VarAssignNode>(
                        false, first_type, name_tok, std::move(value)));
                }
            }
            size_t next_i = index + 1;
            if (next_i < tokens.size() && 
                (tokens[next_i].type == TokenType::EQ ||
                tokens[next_i].type == TokenType::PLUS_EQ ||
                tokens[next_i].type == TokenType::MINUS_EQ ||
                tokens[next_i].type == TokenType::MUL_EQ ||
                tokens[next_i].type == TokenType::DIV_EQ ||
                tokens[next_i].type == TokenType::MOD_EQ)) {
                
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
                    if (arg->name_tok.has_value() && arg->name_tok->value == entrypointName) {
                        if (arg->return_types.empty() || arg->return_types[0].value != "int") {
                            std::string actual = arg->return_types.empty() ? "void" : arg->return_types[0].value;
                            throw InvalidSyntaxError("the entrypoint must return int, not " + actual, 
                                                    arg->return_types.empty() ? Position() : arg->return_types[0].pos);
                        }
                        if (!arg->params.empty()) {
                            throw InvalidSyntaxError("the entrypoint must have no parameters", 
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
                "Missing the entrypoint function", 
                "Program must have an 'int entrypointname()' function", 
                Position())};
        }
        for (auto& [name, ut] : user_types) {
            if (ut.kind == UserTypeKind::Class && !ut.baseClassName.empty()) {
                std::string baseKey = ut.baseClassName;
                if (baseKey.find("::") == std::string::npos) {
                    bool found = false;
                    for (auto& [key, info] : user_types) {
                        if (key.find(baseKey) != std::string::npos && 
                            info.kind == UserTypeKind::Class) {
                            baseKey = key;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        throw InvalidSyntaxError(
                            "Base class '" + ut.baseClassName + "' not found", 
                            Position()
                        );
                    }
                }
                
                auto it = user_types.find(baseKey);
                if (it == user_types.end() || it->second.kind != UserTypeKind::Class) {
                    throw InvalidSyntaxError(
                        "class inherits from non-class or non-existent object", 
                        Position()
                    ); 
                }
            }
        }
        return Aer{std::make_unique<StatementsNode>(std::move(stmts), true), nullptr, std::move(this->user_types)};
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
    std::string Number<T>::print() const {
        return std::to_string(this->value);
    }

    // Explicit instantiations
    template class Number<int>;
    template class Number<float>;
    template class Number<double>;

//////////////////////////////////////////////////////////////////
// INTERPRETER //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
    ClassMethodInfo* Interpreter::find_method_on_class(
        const std::string& className,
        const std::string& mname
    ) {
        auto it = context->user_types.find(className);
        if (it == context->user_types.end()) return nullptr;

        UserTypeInfo* cur = &it->second;
        while (cur) {
            for (auto& m : cur->classMethods) {
                if (!m.is_constructor && m.name_tok.value == mname) {
                    return &m;
                }
            }

            if (cur->baseClassName.empty()) break;
            auto bit = context->user_types.find(cur->baseClassName);
            if (bit == context->user_types.end() ||
                bit->second.kind != UserTypeKind::Class) {
                break;
            }
            cur = &bit->second;
        }
        return nullptr;
    }
    std::string PointerValue::print(Context* ctx) const {
        if (this->is_null) return "nullptr";
        if (!ctx || frame_index >= ctx->frames.size()) {
            return "&<dangling>";
        }
        auto& frame = ctx->frames[frame_index];
        auto it = frame.find(symbol_key);
        if (it == frame.end()) {
            return "&<dangling>";
        }

        const void* addr = static_cast<const void*>(&(it->second.value));
        std::ostringstream oss;
        oss << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(addr);
        return oss.str();
    }
    bool Interpreter::is_truthy(const NumberVariant& val) {
        return std::visit([this](auto&& v) -> bool {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, BoolValue>) {
                return v.value;
            } else if constexpr (std::is_same_v<T, QBoolValue>) {
                return v.tval;
            } else if constexpr (std::is_same_v<T, Number<int>> || 
                                std::is_same_v<T, Number<float>> || 
                                std::is_same_v<T, Number<double>> ||
                                std::is_same_v<T, Number<short>> || 
                                std::is_same_v<T, Number<long long>> || 
                                std::is_same_v<T, Number<long double>>) {
                return v.value != 0;
            } else if constexpr (std::is_same_v<T, StringValue>) {
                return !v.value.empty();
            } else if constexpr (std::is_same_v<T, MultiValue>) { 
                return true; 
            } else if constexpr (std::is_same_v<T, PointerValue>) {
                return !v.is_null;
            } else if constexpr (std::is_same_v<T, std::shared_ptr<InstanceValue>>) { 
                auto inst = v;
                const std::string& className = inst->class_name;

                ClassMethodInfo* method = find_method_on_class(className, "eval");
                if (!method) {
                    this->errors.push_back({RTError(
                        "QC-CLW1: Instance of '" + className +
                        "' used as condition but is missing eval(): defaulting true", Position()),
                        "Warning"});
                    return true;
                }
                NumberVariant result = call_instance_method(
                    inst,
                    method,
                    std::vector<NumberVariant>{},
                    Position()
                );
                if (auto b = std::get_if<BoolValue>(&result)) {
                    return b->value;
                }

                this->errors.push_back({RTError(
                    "eval() on class '" + className + "' must return bool",
                    get_pos(result)),
                    "Error"});
                return false;
            }
            return false;
        }, val);
    }
    bool value_matches_union_member(const std::string& member_type, const std::string& actual_type, const NumberVariant& val)
    {
        auto colon_pos = member_type.find(':');
        if (colon_pos != std::string::npos) {
            std::string lit_kind = member_type.substr(0, colon_pos);
            std::string lit_val  = member_type.substr(colon_pos + 1);
            if (member_type == "auto" || actual_type == "auto") return true;
            if (member_type == "list<auto>") {
                if (actual_type.find("list<") != std::string::npos || actual_type.find("[]") != std::string::npos) {
                    return true;
                }
            }
            else if (member_type.find("list<") == 0) {
                std::string inner = strip(member_type);
                if (strip(actual_type) == inner && actual_type != inner) {
                    return true;
                }
            }
            if (actual_type.find("list<") == 0) {
                std::string inner = strip(actual_type);
                
                if (strip(member_type) == inner && member_type != inner) {
                    return true;
                }
            }
            if (lit_kind == "string" && actual_type == "string") {
                if (auto sv = std::get_if<StringValue>(&val)) {
                    if (lit_val.size() >= 2 && lit_val.front() == '"' && lit_val.back() == '"') {
                        std::string inner = lit_val.substr(1, lit_val.size() - 2);
                        return sv->value == inner;
                    }
                }
                return false;
            }

            if (lit_kind == "int" && actual_type == "int") {
                if (auto iv = std::get_if<Number<int>>(&val)) {
                    int lit_int = std::stoi(lit_val);
                    return iv->value == lit_int;
                }
                return false;
            }

            if (lit_kind == "float" && actual_type == "float") {
                if (auto fv = std::get_if<Number<float>>(&val)) {
                    float lit_f = std::stof(lit_val);
                    return fv->value == lit_f;
                }
                return false;
            }

            if (lit_kind == "double" && actual_type == "double") {
                if (auto dv = std::get_if<Number<double>>(&val)) {
                    double lit_d = std::stod(lit_val);
                    return dv->value == lit_d;
                }
                return false;
            }

            if (lit_kind == "char" && actual_type == "char") {
                if (auto cv = std::get_if<CharValue>(&val)) {
                    if (lit_val.size() == 1) {
                        return cv->value == lit_val[0];
                    }
                    if (lit_val.size() >= 3 && lit_val.front() == '\'' && lit_val.back() == '\'') {
                        char c = lit_val[1];
                        return cv->value == c;
                    }
                }
                return false;
            }

            if (lit_kind == "bool" && actual_type == "bool") {
                if (auto bv = std::get_if<BoolValue>(&val)) {
                    bool lit_b = (lit_val == "true");
                    bool val_b = (bv->value);
                    return lit_b == val_b;
                }
                return false;
            }

            if (lit_kind == "qbool" && actual_type == "qbool") {
                if (auto qv = std::get_if<QBoolValue>(&val)) {
                    return qv->valname == lit_val;
                }
                return false;
            }
            if (lit_kind == "function" && actual_type == "function") {
                return true;
            }

            return false;
        }

        return actual_type == member_type;
    }
    void Context::set(const std::string& name, NumberVariant new_val, Position pos) {
        auto loc_opt = find_any_symbol(name);
        if (!loc_opt.has_value()) {
            throw RTError("QC-C001: Undefined variable: '" + name + "'", pos);
        }

        auto [fi, key] = *loc_opt;
        auto [t_fi, t_key] = follow_ref_chain(fi, key, pos);

        if (t_fi >= frames.size()) {
            throw RTError("Dangling reference: invalid frame index", pos);
        }

        auto& frame = frames[t_fi];
        auto sym_it = frame.find(t_key);
        if (sym_it == frame.end()) {
            throw RTError("Dangling reference: symbol '" + t_key + "' not found", pos);
        }

        Symbol& sym = sym_it->second;

        if (sym.is_const) {
            throw RTError("QC-T001: Cannot assign to const variable '" + name + "'", pos);
        }

        std::string expected = sym.declared_type;
        std::string actual   = get_type_name(new_val);
        std::string lookup_type = expected;
        auto ut_it = user_types.find(lookup_type);

        if (ut_it == user_types.end()) {
            size_t last_colon = lookup_type.rfind("::");
            if (last_colon == std::string::npos && !namespaceStack.empty()) {
                std::string qualified;
                for (auto& ns : namespaceStack) {
                    if (!qualified.empty()) qualified += "::";
                    qualified += ns;
                }
                lookup_type = qualified + "::" + expected;
                ut_it = user_types.find(lookup_type);
            }
        }

        if (ut_it == user_types.end()) {
            for (auto& [type_name, info] : user_types) {
                if (type_name == expected ||
                    type_name.find("::" + expected) != std::string::npos) {
                    ut_it = user_types.find(type_name);
                    break;
                }
            }
        }

        if (ut_it != user_types.end() &&
            ut_it->second.kind == UserTypeKind::Union) {

            auto& members = ut_it->second.members;
            bool ok = false;

            for (auto& m : members) {
                if (value_matches_union_member(m.type, actual, new_val)) {
                    ok = true;
                    break;
                }
            }

            if (!ok) {
                throw RTError(
                    "QC-T004: Type mismatch: value of type " + actual +
                    " is not assignable to union type '" + expected + "'",
                    pos
                );
            }

            sym.value = std::move(new_val);
            return;
        }

        if (expected == "list<auto>") {
            if (actual.find("list<") != std::string::npos ||
                actual.find("[]")     != std::string::npos) {
                actual = expected;
            }
        }
        if (expected.find("list<") == 0) {
            std::string inner = strip(expected);
            if (strip(actual) == inner && actual != inner) {
                actual = expected;
            }
        }
        if (actual.find("list<") == 0) {
            std::string inner = strip(actual);
            if (strip(expected) == inner && expected != inner) {
                actual = expected;
            }
        }

        auto normalize_type = [](const std::string& t) {
            std::string type = t;
            size_t pos = type.rfind("::");
            type = (pos != std::string::npos) ? type.substr(pos + 2) : type;
            if (type == "long int")     type = "int";
            if (type == "short int")    type = "int";
            if (type == "long double")  type = "double";
            return type;
        };
        if (expected.find("*") != std::string::npos && actual == "void*") {
            sym.value = std::move(new_val);
            return;
        }
        if (normalize_type(expected) != normalize_type(actual) && expected != actual) {
            throw RTError("QC-T003: Type mismatch: cannot assign " + actual + " to " + expected, pos);
        }

        sym.value = std::move(new_val);
    }
    NumberVariant def_value_for_type(const std::string& type_name) {
        if (type_name == "int")    return Number<int>(0);
        else if (type_name == "float")  return Number<float>(0.0f);
        else if (type_name == "double") return Number<double>(0.0);
        else if (type_name == "string") return StringValue("");
        else if (type_name == "char")   return CharValue("");
        else if (type_name == "bool")   return BoolValue("");
        else if (type_name == "qbool")  return QBoolValue("");
        else if (type_name == "short int")   return Number<short>(0);
        else if (type_name == "long int")    return Number<long long>(0);
        else if (type_name == "long double") return Number<long double>(0.0L);
        if (type_name.rfind("list<", 0) == 0 && type_name.back() == '>') {
        std::string elem_type = type_name.substr(5, type_name.size() - 6);
            auto list = std::make_shared<ListValue>(elem_type, std::vector<NumberVariant>{});
            return list;
        }
        if (type_name.rfind("map<", 0) == 0 && type_name.back() == '>') {
            std::string inner = type_name.substr(4, type_name.size() - 5);
            size_t comma = inner.find(',');
            std::string key_type = "auto";
            std::string val_type = "auto";
            if (comma != std::string::npos) {
                key_type = inner.substr(0, comma);
                val_type = inner.substr(comma + 1);
            }
            auto map = std::make_shared<MapValue>(key_type, val_type);
            return map;
        }
        if (type_name.size() >= 2 && type_name.find("[]") != std::string::npos) {
            std::string elem_type = type_name;
            while (elem_type.size() >= 2 &&
                elem_type.substr(elem_type.size() - 2) == "[]") {
                elem_type = elem_type.substr(0, elem_type.size() - 2);
            }
            auto arr = std::make_shared<ArrayValue>(elem_type, std::vector<NumberVariant>{});
            return arr;
        }

        return VoidValue();
    }
    std::string Interpreter::value_to_string(const NumberVariant& val) {
        return std::visit([this](auto const& v) -> std::string {
            using T = std::decay_t<decltype(v)>;

            if constexpr (std::is_same_v<T, std::monostate>) {
                return "";
            } 
            else if constexpr (std::is_same_v<T, QBoolValue>) {
                return v.print();
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<MultiValue>> ||
                            std::is_same_v<T, std::shared_ptr<ArrayValue>> ||
                            std::is_same_v<T, std::shared_ptr<ListValue>> ||
                            std::is_same_v<T, std::shared_ptr<MapValue>> ||
                            std::is_same_v<T, std::shared_ptr<StructValue>>) {
                return v->print();
            } 
            else if constexpr (std::is_same_v<T, std::shared_ptr<InstanceValue>>) {
                auto inst = v;
                const std::string& className = inst->class_name;

                ClassMethodInfo* method = find_method_on_class(className, "repr");
                if (!method) {
                    this->errors.push_back({RTError(
                        "QC-CLW2: Instance of '" + className +
                        "' printed, but missing repr function. Printing (reprless class)", Position()),
                        "Warning"});
                    return "(reprless class)";
                }
                NumberVariant result = call_instance_method(
                    inst,
                    method,
                    std::vector<NumberVariant>{},
                    Position()
                );
                if (auto s = std::get_if<StringValue>(&result)) {
                    return s->value;
                }

                this->errors.push_back({RTError(
                    "repr() on class '" + className + "' must return string",
                    get_pos(result)),
                    "Error"});
                return v->print();
            }
            else if constexpr (std::is_same_v<T, PointerValue>) {
                return v.print(this->context);
            }
            else {
                return v.print();
            }
        }, val);
    }
    std::string value_to_string(const NumberVariant& val) {
        return std::visit([](auto const& v) -> std::string {
            using T = std::decay_t<decltype(v)>;

            if constexpr (std::is_same_v<T, std::monostate>) {
                return "";
            } 
            else if constexpr (std::is_same_v<T, QBoolValue>) {
                return v.print();
            }
            else if constexpr (std::is_same_v<T, PointerValue>) {
                return "&" + v.pointee_type;
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<MultiValue>> ||
                            std::is_same_v<T, std::shared_ptr<ArrayValue>> ||
                            std::is_same_v<T, std::shared_ptr<ListValue>> ||
                            std::is_same_v<T, std::shared_ptr<MapValue>> ||
                            std::is_same_v<T, std::shared_ptr<StructValue>> ||
                            std::is_same_v<T, std::shared_ptr<InstanceValue>>) {
                return v->print();
            } 
            else {
                return v.print();
            }
        }, val);
    }
    std::string InstanceValue::print() const {
        std::string out = class_name + "{";
        bool first = true;
        for (auto& [k, v] : fields) {
            if (!first) out += ", ";
            out += k + ": " + value_to_string(v);
            first = false;
        }
        out += "}";
        return out;
    }
    std::string MapValue::print() const {
        std::string result = "{";
        bool first = true;
        for (auto& [key, val] : data) {
            if (!first) result += ", ";
            result += key + ": " + value_to_string(val);
            first = false;
        }
        result += "}";
        return result;
    }
    std::string StructValue::print() const {
        std::string out = type_name + "{";
        bool first = true;
        for (auto& [name, val] : fields) {
            if (!first) out += ", ";
            out += name + ": " + value_to_string(val);
            first = false;
        }
        out += "}";
        return out;
    }
    bool values_equal(const NumberVariant& a,
                    const NumberVariant& b,
                    const Position& pos)
    {
        auto get_elements = [](const NumberVariant& v) -> const std::vector<NumberVariant>* {
            if (auto list_ptr = std::get_if<std::shared_ptr<ListValue>>(&v)) {
                return &((*list_ptr)->elements);
            }
            if (auto arr_ptr = std::get_if<std::shared_ptr<ArrayValue>>(&v)) {
                return &((*arr_ptr)->elements);
            }
            return nullptr;
        };
        
        auto a_elements = get_elements(a);
        auto b_elements = get_elements(b);
        if (a_elements && b_elements) {
            if (a_elements->size() != b_elements->size()) {
                return false;
            }
            
            for (size_t i = 0; i < a_elements->size(); i++) {
                if (!values_equal((*a_elements)[i], (*b_elements)[i], pos)) {
                    return false;
                }
            }
            
            return true;
        }
        if (a_elements || b_elements) {
            return false;
        }
        if (a.index() != b.index()) {
            return false;
        }
        
        return std::visit([&](auto&& v) -> bool {
            using T = std::decay_t<decltype(v)>;

            if constexpr (std::is_same_v<T, StringValue>) {
                return v.value == std::get<StringValue>(b).value;
            } else if constexpr (std::is_same_v<T, CharValue>) {
                return v.value == std::get<CharValue>(b).value;
            } else if constexpr (std::is_same_v<T, BoolValue>) {
                return v.value == std::get<BoolValue>(b).value;
            } else if constexpr (std::is_same_v<T, QBoolValue>) {
                return v.valname == std::get<QBoolValue>(b).valname;
            } else if constexpr (
                std::is_same_v<T, Number<int>> ||
                std::is_same_v<T, Number<float>> ||
                std::is_same_v<T, Number<double>> ||
                std::is_same_v<T, Number<long long>> ||
                std::is_same_v<T, Number<long double>> ||
                std::is_same_v<T, Number<short>>
            ) {
                return static_cast<double>(v.value)
                    == static_cast<double>(std::get<T>(b).value);
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<ListValue>> ||
                            std::is_same_v<T, std::shared_ptr<ArrayValue>>) {
                return false;
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<MapValue>>) {
                auto map_a = v;
                auto map_b = std::get<std::shared_ptr<MapValue>>(b);
                
                if (map_a->data.size() != map_b->data.size()) {
                    return false;
                }
                
                for (const auto& [key, value] : map_a->data) {
                    if (map_b->data.find(key) == map_b->data.end()) {
                        return false;
                    }
                    if (!values_equal(value, map_b->data.at(key), pos)) {
                        return false;
                    }
                }
                
                return true;
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<StructValue>>) {
                auto struct_a = v;
                auto struct_b = std::get<std::shared_ptr<StructValue>>(b);
                
                if (struct_a->type_name != struct_b->type_name) {
                    return false;
                }
                
                if (struct_a->fields.size() != struct_b->fields.size()) {
                    return false;
                }
                
                for (const auto& [field_name, value] : struct_a->fields) {
                    auto it = struct_b->fields.find(field_name);
                    if (it == struct_b->fields.end()) {
                        return false;
                    }
                    if (!values_equal(value, it->second, pos)) {
                        return false;
                    }
                }
                
                return true;
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<InstanceValue>>) {
                auto inst_a = v;
                auto inst_b = std::get<std::shared_ptr<InstanceValue>>(b);
                
                if (inst_a->class_name != inst_b->class_name) {
                    return false;
                }
                
                if (inst_a->fields.size() != inst_b->fields.size()) {
                    return false;
                }
                
                for (const auto& [field_name, value] : inst_a->fields) {
                    auto it = inst_b->fields.find(field_name);
                    if (it == inst_b->fields.end()) {
                        return false;
                    }
                    if (!values_equal(value, it->second, pos)) {
                        return false;
                    }
                }
                
                return true;
            }
            else if constexpr (std::is_same_v<T, std::shared_ptr<MultiValue>>) {
                throw RTError("Cannot compare multi-values", pos);
            }
            else if constexpr (std::is_same_v<T, VoidValue>) {
                return true;
            }
            else if constexpr (std::is_same_v<T, FunctionValue>) {
                throw RTError("Cannot compare functions", pos);
            }
            else {
                throw RTError("Invalid comparison type", pos);
            }
        }, a);
    }
    NumberVariant Interpreter::operator()(NullptrNode& node) {
        PointerValue pv("void", 0, "", true);
        pv.pos = node.pos;
        return pv;
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<NamespaceNode>& node) {
        context->push_namespace(node->name);

        for (auto& stmt : node->body) {
            this->process(stmt);
        }

        context->pop_namespace();
        return VoidValue();
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<TryCatchNode>& node) {
        try {
            if (node->try_body) {
                AnyNode try_node = std::move(node->try_body);
                this->process(try_node);
            }
        }
        catch (const NumberVariant& thrown_value) {
            std::string thrown_type = context->get_type_name(thrown_value);
            
            bool type_matches = false;
            
            if (node->catch_var_type == "auto") {
                type_matches = true;
            }
            else if (thrown_type == node->catch_var_type) {
                type_matches = true;
            }
            else {
                if (node->catch_var_type == "list<auto>") {
                    if (thrown_type.find("list<") != std::string::npos || 
                        thrown_type.find("[]") != std::string::npos) {
                        type_matches = true;
                    }
                }
                else if (node->catch_var_type.find("list<") == 0) {
                    std::string inner = strip(node->catch_var_type);
                    if (strip(thrown_type) == inner && thrown_type != inner) {
                        type_matches = true;
                    }
                }
                else if (thrown_type.find("list<") == 0) {
                    std::string inner = strip(thrown_type);
                    if (strip(node->catch_var_type) == inner && node->catch_var_type != inner) {
                        type_matches = true;
                    }
                }
            }
            
            if (type_matches) {
                context->push_scope();
                context->define(
                    node->catch_var_name,
                    node->catch_var_type,
                    thrown_value,
                    false
                );
                
                if (node->catch_body) {
                    AnyNode catch_node = std::move(node->catch_body);
                    this->process(catch_node);
                }
                
                context->pop_scope();
            }
            else {
                throw;
            }
        }
        catch (const RTError& e) {
            if (node->catch_var_type == "string" || node->catch_var_type == "auto") {
                context->push_scope();
                context->define(
                    node->catch_var_name,
                    "string",
                    StringValue(e.details),
                    false
                );
                
                if (node->catch_body) {
                    AnyNode catch_node = std::move(node->catch_body);
                    this->process(catch_node);
                }
                
                context->pop_scope();
            }
            else {
                throw;
            }
        }
        
        return VoidValue();
    }
    NumberVariant Interpreter::process(AnyNode& node) {
        try {
            if (this->errors.size() > 50) {
                throw RTError("Too many errors! Execution stopped.", Position("", "", 0, 0, 0));
            }
            return std::visit([this](auto& n) -> NumberVariant {
                using T = std::decay_t<decltype(n)>;
                return (*this)(n);
            }, node);
        } catch (RTError& e) {
            throw e;
        }
        return VoidValue();
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<BreakNode>& node) {
        this->errors.push_back({RTError("QC-SW01: Unexpected 'break' outside loop or switch", node->tok.pos), "Warning"});
        return VoidValue();
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
            else if constexpr (std::is_same_v<T, std::unique_ptr<QIfNode>>) {
                return exec_stmt_in_loop_or_switch(*n);
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<QSwitchNode>>) {
                return exec_stmt_in_loop_or_switch(*n);
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<TryCatchNode>>) {
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
        return {};
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
    static std::pair<std::string, std::string> parse_map_type(const std::string& s) {
        auto inside = s.substr(4, s.size() - 5);
        auto comma = inside.find(',');
        if (comma == std::string::npos) return {"", ""};
        std::string key   = inside.substr(0, comma);
        std::string value = inside.substr(comma + 1);
        return {key, value};
    }
    NumberVariant Interpreter::convert_array_to_struct(
        const std::shared_ptr<ArrayValue>& arr,
        const std::string& struct_type,
        Context* context
    ) {
        const auto& info   = context->user_types[struct_type];
        const auto& fields = info.fields;

        if (arr->elements.size() != fields.size()) {
            this->errors.push_back({RTError("Nested struct initializer size mismatch for '" + struct_type + "'", Position("", "", 0, 0, 0)), "Error"});
        }

        auto sv = std::make_shared<StructValue>(struct_type);

        for (size_t i = 0; i < fields.size(); ++i) {
            NumberVariant elemVal = arr->elements[i];
            const auto& field = fields[i];

            if (context->user_types.contains(field.type)) {
                auto nestedArr = std::get_if<std::shared_ptr<ArrayValue>>(&elemVal);
                if (!nestedArr) {
                    this->errors.push_back({RTError(
                        "Expected struct initializer for nested struct '" + field.type + "'",
                        Position("", "", 0, 0, 0)
                    ), "Error"});
                }
                elemVal = convert_array_to_struct(*nestedArr, field.type, context);
            }
            else if ((field.type.size() >= 2 &&
                    field.type.substr(field.type.size() - 2) == "[]") ||
                    (field.type.size() > 5 &&
                    field.type.substr(0, 5) == "list<")) {

                auto arrVal = std::get_if<std::shared_ptr<ArrayValue>>(&elemVal);
                if (!arrVal) {
                    this->errors.push_back({RTError(
                        "Expected array initializer for list/array field '" + field.name + "'",
                        Position("", "", 0, 0, 0)
                    ), "Error"});
                }

                std::string elemType;
                if (field.type.rfind("list<", 0) == 0) {
                    elemType = field.type.substr(5, field.type.size() - 6);
                    elemVal = std::make_shared<ListValue>(elemType, (*arrVal)->elements);
                } else {
                    elemType = field.type.substr(0, field.type.size() - 2);
                }
            }
            else if (field.type.size() > 4 &&
                    field.type.substr(0, 4) == "map<") {

                auto mapVal = std::get_if<std::shared_ptr<MapValue>>(&elemVal);
                if (!mapVal) {
                    this->errors.push_back({RTError(
                        "QC-E001: Expected map initializer for field '" + field.name +
                        "' of type '" + field.type + "'",
                        Position("", "", 0, 0, 0)
                    ), "Error"});
                }

                auto inside = field.type.substr(4, field.type.size() - 5);
                auto comma = inside.find(',');
                std::string expectedKey   = inside.substr(0, comma);
                std::string expectedValue = inside.substr(comma + 1);

                const std::string& actualKey   = (*mapVal)->key_type;
                const std::string& actualValue = (*mapVal)->value_type;

                if (expectedKey != actualKey || expectedValue != actualValue) {
                    this->errors.push_back({RTError(
                        "QC-T010: Type mismatch for map field '" + field.name +
                        "': expected " + field.type +
                        ", got map<" + actualKey + "," + actualValue + ">",
                        Position("", "", 0, 0, 0)
                    ), "Error"});
                }
            }

            sv->fields[field.name] = elemVal;
        }

        return sv;
    }
    NumberVariant Interpreter::operator()(RefVarDeclNode& node) {
        std::string target_name = node.target_tok.value;
        NumberVariant target_value;
        try {
            target_value = context->get(target_name, Position("", "", 0, 0, 0));
        } catch (RTError& e) {
            errors.push_back({RTError(
                "Cannot create reference to undefined variable '" + target_name + "'",
                Position("", "", 0, 0, 0)
            ), "Error"});
            return VoidValue();
        }
        std::string target_type = context->get_type_name(target_value);
        std::string ref_type = node.type_tok.value;
        if (ref_type != target_type) {
            errors.push_back({RTError(
                "Reference type mismatch: cannot bind " + ref_type + "& to " + target_type,
                Position("", "", 0, 0, 0)
            ), "Error"});
            return VoidValue();
        }
        std::string ref_name = node.var_name_tok.value;
        context->define_reference(ref_name, target_name, ref_type + "&", node.var_name_tok.pos);
        return VoidValue();
    }
    ClassMethodInfo* Interpreter::find_method_with_args(
        const std::string& className,
        const std::string& mname,
        const std::vector<NumberVariant>& args
    ) {
        auto it = context->user_types.find(className);
        if (it == context->user_types.end()) return nullptr;

        UserTypeInfo* cur = &it->second;
        std::vector<ClassMethodInfo*> candidates;
        while (cur) {
            for (auto& m : cur->classMethods) {
                if (m.name_tok.value == mname || (m.is_constructor && mname == className)) {
                    candidates.push_back(&m);
                }
            }

            if (cur->baseClassName.empty()) break;
            auto bit = context->user_types.find(cur->baseClassName);
            if (bit == context->user_types.end()) break;
            cur = &bit->second;
        }

        if (candidates.empty()) return nullptr;
        ClassMethodInfo* best = nullptr;
        int best_score = -1;

        for (auto* m : candidates) {
            if (m->params.size() != args.size()) continue;

            int score = 0;
            bool valid = true;
            size_t i = 0;

            auto norm = [](std::string t) {
                if (!t.empty() && t.back() == '&') t.pop_back();
                size_t pos = t.rfind("::");
                if (pos != std::string::npos) t = t.substr(pos + 2);
                if (t == "long int" || t == "short int") t = "int";
                if (t == "long double") t = "double";
                return t;
            };

            for (auto it = m->params.begin(); it != m->params.end(); ++it, ++i) {
                std::string expected = it->type.value;
                std::string actual   = context->get_type_name(args[i]);

                std::string exp_n = norm(expected);
                std::string act_n = norm(actual);

                if (expected == "list<auto>") {
                    if (actual.find("list<") != std::string::npos || actual.find("[]") != std::string::npos) {
                        score += 50;
                    }
                }
                else if (expected.find("list<") == 0) {
                    std::string inner = strip(expected);
                    if (strip(actual) == inner && actual != inner) {
                        score += 100;
                    }
                }
                else if (actual.find("list<") == 0) {
                    std::string inner = strip(actual);
                    if (strip(expected) == inner && expected != inner) {
                        score += 100;
                    }
                }
                else if (exp_n == act_n) {
                    score += 100;
                } else if (expected == "auto") {
                    score += 50;
                } else {
                    valid = false;
                    break;
                }
            }

            if (valid && score > best_score) {
                best_score = score;
                best = m;
            }
        }
        if (best) {
            return best;
        }
        return nullptr;
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<VarAssignNode>& node) {
        if (!node) return std::move(Number<int>(0));
        NumberVariant value = this->process(node->value_node);
        

        std::string declaredType = node->type_tok.value;
        std::string actualType   = context->get_type_name(value);
        std::string lookup_type = declaredType;
        auto ut_it = context->user_types.find(lookup_type);
        if (ut_it == context->user_types.end() && !context->namespaceStack.empty()) {
            std::string qualified = "";
            for (auto& ns : context->namespaceStack) {
                if (!qualified.empty()) qualified += "::";
                qualified += ns;
            }
            lookup_type = qualified + "::" + declaredType;
            ut_it = context->user_types.find(lookup_type);
        }
        if (ut_it == context->user_types.end()) {
            for (auto& [name, info] : context->user_types) {
                if (name == declaredType || name.find("::" + declaredType) != std::string::npos) {
                    ut_it = context->user_types.find(name);
                    break;
                }
            }
        }
        if (ut_it != context->user_types.end()) {
            UserTypeInfo& ut = ut_it->second;

            if (ut.kind == UserTypeKind::Struct) {
                if (std::holds_alternative<VoidValue>(value)) {
                    auto sv = std::make_shared<StructValue>(declaredType);
                    sv->set_pos(node->var_name_tok.pos);
                    for (auto& field : ut.fields) {
                        sv->fields[field.name] = def_value_for_type(field.type);
                    }
                    
                    value = sv;
                }
                const auto& fields = ut.fields;

                if (auto svPtr = std::get_if<std::shared_ptr<StructValue>>(&value)) {
                    std::string value_type = (*svPtr)->type_name;
                    std::string declared_type = declaredType;
                    
                    std::string declared_simple = declared_type;
                    size_t pos = declared_simple.rfind("::");
                    if (pos != std::string::npos) {
                        declared_simple = declared_simple.substr(pos + 2);
                    }
                    if (value_type == declared_simple) {
                        actualType = declaredType;
                    } else if ((*svPtr)->type_name != declaredType) {
                        this->errors.push_back({RTError(
                            "Cannot assign struct of type '" + (*svPtr)->type_name +
                            "' to variable of type '" + declaredType + "'",
                            node->var_name_tok.pos
                        ), "Error"});
                    }
                    
                    auto newStruct = std::make_shared<StructValue>(**svPtr);
                    newStruct->set_pos(node->var_name_tok.pos);
                    value = newStruct;
                }
                else if (auto arrPtr = std::get_if<std::shared_ptr<ArrayValue>>(&value)) {

                    if (arrPtr->get()->elements.size() != fields.size()) {
                        this->errors.push_back({RTError(
                            "Initializer list has " + std::to_string(arrPtr->get()->elements.size()) +
                            " elements, but struct '" + declaredType + "' has " +
                            std::to_string(fields.size()) + " fields",
                            node->var_name_tok.pos
                        ), "Error"});
                    }

                    auto sv = std::make_shared<StructValue>(declaredType);
                    sv->set_pos(node->var_name_tok.pos);

                    for (size_t i = 0; i < fields.size(); ++i) {
                        const auto& field = fields[i];
                        NumberVariant elemVal = arrPtr->get()->elements[i];

                        auto nested_it = context->user_types.find(field.type);
                        if (nested_it != context->user_types.end() &&
                            nested_it->second.kind == UserTypeKind::Struct) {

                            auto nestedArr = std::get_if<std::shared_ptr<ArrayValue>>(&elemVal);
                            if (!nestedArr) {
                                this->errors.push_back({RTError(
                                    "Expected struct initializer for nested struct '" + field.type + "'",
                                    node->var_name_tok.pos
                                ), "Error"});
                            }
                            elemVal = Interpreter::convert_array_to_struct(*nestedArr, field.type, context);
                        }
                        else if (field.type.size() >= 2 &&
                                field.type.substr(field.type.size() - 2) == "[]") {

                            auto arrVal = std::get_if<std::shared_ptr<ArrayValue>>(&elemVal);
                            if (!arrVal) {
                                this->errors.push_back({RTError(
                                    "Expected array initializer for list field '" + field.name + "'",
                                    node->var_name_tok.pos
                                ), "Error"});
                            }
                            std::string elemType = field.type.substr(0, field.type.size() - 2);
                            auto listVal = std::make_shared<ListValue>(elemType, (*arrVal)->elements);
                            elemVal = listVal;
                        }
                        else if (field.type.size() > 4 &&
                                field.type.substr(0, 4) == "map<") {

                            auto mapVal = std::get_if<std::shared_ptr<MapValue>>(&elemVal);
                            if (!mapVal) {
                                this->errors.push_back({RTError(
                                    "QC-E001: Expected map initializer for field '" + field.name +
                                    "' of type '" + field.type + "'",
                                    node->var_name_tok.pos
                                ), "Error"});
                            }

                            auto [expectedKeyType, expectedValType] = parse_map_type(field.type);
                            const std::string& actualKeyType = (*mapVal)->key_type;
                            const std::string& actualValType = (*mapVal)->value_type;

                            if (expectedKeyType != actualKeyType || expectedValType != actualValType) {
                                this->errors.push_back({RTError(
                                    "QC-T010: Type mismatch for map field '" + field.name +
                                    "': expected " + field.type +
                                    ", got map<" + actualKeyType + "," + actualValType + ">",
                                    node->var_name_tok.pos
                                ), "Error"});
                            }
                        }

                        sv->fields[field.name] = elemVal;
                    }

                    value = sv;
                }
                else {
                    this->errors.push_back({RTError(
                        "Expected struct initializer '{ ... }' or struct value for type '" + declaredType + "'",
                        node->var_name_tok.pos
                    ), "Error"});
                }

                actualType = declaredType;
            }

            else if (ut.kind == UserTypeKind::Alias) {
                declaredType = ut.aliasTarget;
            }
            else if (ut.kind == UserTypeKind::Union) {
                auto& members = ut_it->second.members;
                std::string valType = context->get_type_name(value);
                bool ok = false;

                for (auto& m : members) {
                    if (value_matches_union_member(m.type, valType, value)) {
                        ok = true;
                        break;
                    }
                }
                if (actualType == "void") {
                    ok = true;
                    auto colon_pos = members[0].type.find(':');
                    if (colon_pos != std::string::npos) {
                        std::string lit_kind = members[0].type.substr(0, colon_pos);
                        value = def_value_for_type(lit_kind);
                    }
                    value = def_value_for_type(members[0].type);
                }
                if (!ok) {
                    this->errors.push_back({RTError(
                        "QC-T004: Type mismatch: value of type " + valType +
                        " is not assignable to union type '" + node->type_tok.value + "'",
                        Position()
                    ), "Error"});
                }

                actualType = node->type_tok.value;
            }
            else if (ut.kind == UserTypeKind::Class) {
                if (std::holds_alternative<VoidValue>(value)) {
                    auto fields = make_instance_fields(lookup_type);
                    auto inst = std::make_shared<InstanceValue>(lookup_type, std::move(fields));
                    std::vector<NumberVariant> no_args;
                    ClassMethodInfo* init_m =
                        this->find_method_with_args(lookup_type, "init", no_args);

                    if (init_m) {
                        context->push_scope();
                        context->define("this", lookup_type, inst, true);
                        this->call_instance_method(inst, init_m, no_args, node->var_name_tok.pos);
                        context->pop_scope();
                    }
                    value      = inst;
                    actualType = declaredType;
                }
            }
        }
        if (declaredType != "auto") {
            bool type_matches = false;
            
            if (declaredType == "short int" && actualType == "int") {
                if (auto int_val = std::get_if<Number<int>>(&value)) {
                    value = Number<short>(static_cast<short>(int_val->value));
                    actualType = "short int";
                }
            }

                        
            if (declaredType == "long int" && actualType == "int") {
                if (auto int_val = std::get_if<Number<int>>(&value)) {
                    value = Number<long long>(static_cast<long long>(int_val->value));
                    actualType = "long int";
                }
            }
            
            if (declaredType == "long double") {
                if (actualType == "double") {
                    if (auto dbl_val = std::get_if<Number<double>>(&value)) {
                        value = Number<long double>(static_cast<long double>(dbl_val->value));
                        actualType = "long double";
                    }
                }
                else if (actualType == "float") {
                    if (auto flt_val = std::get_if<Number<float>>(&value)) {
                        value = Number<long double>(static_cast<long double>(flt_val->value));
                        actualType = "long double";
                    }
                }
            }
            if (declaredType == actualType) {
                type_matches = true;
            }
            else if (declaredType.find("*") != std::string::npos) {
                if (actualType == "void*") {
                    type_matches = true;
                }
            }
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
            } else if (declaredType == "qbool" && actualType == "qbool") {
                type_matches = true;
            }
            if (declaredType == "list<auto>") {
                if (actualType.find("list<") != std::string::npos || actualType.find("[]") != std::string::npos) {
                    type_matches = true;
                }
            }
            else if (declaredType.find("list<") != std::string::npos) {
                std::string inner = strip(declaredType);
                if (strip(actualType) == inner && actualType != inner) {
                    type_matches = true;
                }
            }
            if (actualType.find("list<") != std::string::npos) {
                std::string inner = strip(actualType);
                
                if (strip(declaredType) == inner && declaredType != inner) {
                    type_matches = true;
                }
            }
            if (!type_matches) {
                this->errors.push_back({RTError(
                    "QC-T003: Type mismatch: expected " + declaredType + ", got " + actualType,
                    node->var_name_tok.pos
                ), "Error"});
            }
        }

        context->define(node->var_name_tok.value, 
                        declaredType == "auto" || declaredType == "list<auto>" ? actualType : declaredType, 
                        std::move(value), 
                        node->is_const);
        return std::move(value);
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<MapDeclNode>& node) {
        if (!node) return Number<int>(0);
        
        auto map_val = std::make_shared<MapValue>(
            node->key_type.value,
            node->value_type.value
        );
        
        // Initialize with pairs
        for (auto& [key_node, val_node] : node->init_pairs) {
            NumberVariant key = this->process(key_node);
            NumberVariant val = this->process(val_node);
            
            // Convert key to string
            std::string key_str = this->value_to_string(key);
            
            map_val->set(key_str, std::move(val));
        }
        
        std::string map_type = "map<" + node->key_type.value + ", " + node->value_type.value + ">";
        context->define(node->var_name.value, map_type, map_val, node->is_const);
        
        return VoidValue();
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
    ExecResult Interpreter::exec_stmt_in_loop_or_switch(QIfNode& ifn) {
        NumberVariant cond_val = this->process(ifn.condition); 
        
        bool should_run_true = false;
        bool should_run_false = false;
        
        if (auto qb = std::get_if<QBoolValue>(&cond_val)) {
            should_run_true = qb->tval;
            should_run_false = qb->fval;
        } else {
            bool truthy = is_truthy(cond_val);
            should_run_true = truthy;
            should_run_false = !truthy;
        }
        
        NumberVariant last = Number<int>(0);
        
        if (should_run_true) {
            for (auto& stmt : ifn.then_branch->statements) {  
                ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                last = std::move(r.value);
                
                if (r.did_break) return r;     
                if (r.did_continue) return r;  
            }
        }
        
        bool qelif_ran = false;
        for (auto& [qelif_cond, qelif_body] : ifn.qelif_branches) { 
            NumberVariant qelif_val = this->process(qelif_cond);
            
            bool qelif_true = false;
            bool qelif_false = false;
            
            if (auto qb = std::get_if<QBoolValue>(&qelif_val)) {
                qelif_true = qb->tval;
                qelif_false = qb->fval;
            } else {
                bool truthy = is_truthy(qelif_val);
                qelif_true = truthy;
                qelif_false = !truthy;
            }
            
            if (should_run_false && qelif_true) {
                for (auto& stmt : qelif_body->statements) {
                    ExecResult r = this->exec_stmt_in_loop_or_switch(stmt); 
                    last = std::move(r.value);
                    
                    if (r.did_break) return r;     
                    if (r.did_continue) return r;  
                }
                qelif_ran = true;
                break;
            }
        }
        
        if (should_run_false && !qelif_ran && ifn.qelse_branch) {
            for (auto& stmt : ifn.qelse_branch->statements) {
                ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);  
                last = std::move(r.value);
                
                if (r.did_break) return r;     
                if (r.did_continue) return r;  
            }
        }
        
        return ExecResult{std::move(last), false, false}; 
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
    ExecResult Interpreter::exec_stmt_in_loop_or_switch(QSwitchNode& qsw) {
        NumberVariant val = this->process(qsw.value);
        
        if (auto qb = std::get_if<QBoolValue>(&val)) {
            NumberVariant last = Number<int>(0);
            
            if (qb->tval && qsw.case_t) {
                for (auto& stmt : qsw.case_t->statements) {
                    ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                    last = std::move(r.value);
                    if (r.did_break) return ExecResult{std::move(last), true, false};
                    if (r.did_continue) return ExecResult{std::move(last), false, true};
                }
            }
            
            if (qb->fval && qsw.case_f) {
                for (auto& stmt : qsw.case_f->statements) {
                    ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                    last = std::move(r.value);
                    if (r.did_break) return ExecResult{std::move(last), true, false};
                    if (r.did_continue) return ExecResult{std::move(last), false, true};
                }
            }
            
            if (!qb->tval && !qb->fval && qsw.case_n) {
                for (auto& stmt : qsw.case_n->statements) {
                    ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                    last = std::move(r.value);
                    if (r.did_break) return ExecResult{std::move(last), true, false};
                    if (r.did_continue) return ExecResult{std::move(last), false, true};
                }
            }
            
            if (qb->tval && qb->fval && qsw.case_b) {
                for (auto& stmt : qsw.case_b->statements) {
                    ExecResult r = this->exec_stmt_in_loop_or_switch(stmt);
                    last = std::move(r.value);
                    if (r.did_break) return ExecResult{std::move(last), true, false};
                    if (r.did_continue) return ExecResult{std::move(last), false, true};
                }
            }
            
            return ExecResult{std::move(last), false, false};
        }
        
        this->errors.push_back({RTError("qswitch requires a qbool", get_pos(val)), "Severe"});
        return {};
    }
    ExecResult Interpreter::exec_stmt_in_loop_or_switch(TryCatchNode& tcn) {
        try {
            if (tcn.try_body) {
                ExecResult r = exec_stmt_in_loop_or_switch(*tcn.try_body);
                if (r.did_break || r.did_continue || r.did_return) {
                    return r;
                }
            }
        }
        catch (const NumberVariant& thrown_value) {
            std::string thrown_type = context->get_type_name(thrown_value);
            bool type_matches = false;
            
            if (tcn.catch_var_type == "auto") {
                type_matches = true;
            }
            else if (thrown_type == tcn.catch_var_type) {
                type_matches = true;
            }
            else {
                if (tcn.catch_var_type == "list<auto>") {
                    if (thrown_type.find("list<") != std::string::npos || 
                        thrown_type.find("[]") != std::string::npos) {
                        type_matches = true;
                    }
                }
                else if (tcn.catch_var_type.find("list<") == 0) {
                    std::string inner = strip(tcn.catch_var_type);
                    if (strip(thrown_type) == inner && thrown_type != inner) {
                        type_matches = true;
                    }
                }
                else if (thrown_type.find("list<") == 0) {
                    std::string inner = strip(thrown_type);
                    if (strip(tcn.catch_var_type) == inner && tcn.catch_var_type != inner) {
                        type_matches = true;
                    }
                }
            }
            
            if (type_matches) {
                context->push_scope();
                context->define(
                    tcn.catch_var_name,
                    tcn.catch_var_type,
                    thrown_value,
                    false
                );
                ExecResult r = {};
                if (tcn.catch_body) {
                    r = exec_stmt_in_loop_or_switch(*tcn.catch_body);
                }
                context->pop_scope();
                return r;
            }
            else {
                throw;
            }
        }
        catch (const RTError& e) {
            if (tcn.catch_var_type == "string" || tcn.catch_var_type == "auto") {
                context->push_scope();
                
                context->define(
                    tcn.catch_var_name,
                    "string",
                    StringValue(e.details),
                    false
                );
                
                ExecResult r = {};
                if (tcn.catch_body) {
                    r = exec_stmt_in_loop_or_switch(*tcn.catch_body);
                }
                
                context->pop_scope();
                
                return r;
            }
            else {
                throw;
            }
        }
        return {};
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<QSwitchNode>& node) {
        if (!node) return Number<int>(0);
        
        NumberVariant val = this->process(node->value);
        
        if (auto qb = std::get_if<QBoolValue>(&val)) {
            NumberVariant last = Number<int>(0);
            
            if (qb->tval && !qb->fval && node->case_t) {
                for (auto& stmt : node->case_t->statements) {
                    last = this->process(stmt);
                }
            }
            
            if (qb->fval && !qb->tval && node->case_f) {
                for (auto& stmt : node->case_f->statements) {
                    last = this->process(stmt);
                }
            }
            
            if (!qb->tval && !qb->fval && node->case_n) {
                for (auto& stmt : node->case_n->statements) {
                    last = this->process(stmt);
                }
            }
            
            if (qb->tval && qb->fval && node->case_b) {
                for (auto& stmt : node->case_b->statements) {
                    last = this->process(stmt);
                }
            }
            return last;
        } else {
            bool truthy = is_truthy(val);
            
            NumberVariant last = Number<int>(0);
            
            if (truthy && node->case_t) {
                for (auto& stmt : node->case_t->statements) {
                    last = this->process(stmt);
                }
            } else if (!truthy && node->case_f) {
                for (auto& stmt : node->case_f->statements) {
                    last = this->process(stmt);
                }
            }
            
            return last;
        }
        return VoidValue();
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<ContinueNode>& node) {
        this->errors.push_back({RTError("QC-SW02: Unexpected 'continue' outside loop", node ? node->tok.pos : Position()), "Warning"});
        return VoidValue();
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
    NumberVariant Interpreter::operator()(QInNode& node) {
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
    bool Interpreter::struct_has_field(
        const std::shared_ptr<StructValue>& sv,
        const std::string& field
    ) {
        auto it = sv->fields.find(field);
        if (it == sv->fields.end()) return false;
        if (std::holds_alternative<VoidValue>(it->second)) return false;

        return true;
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
                if (values_equal(switch_val, case_val, get_pos(case_val))) {
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
        
        if (!node) {
            return std::move(Number<int>(0));
        }

        
        if (std::holds_alternative<std::monostate>(node->value)) {
            throw ReturnException(VoidValue().set_pos(node->pos));
        }

        NumberVariant val = this->process(node->value);
        
        throw ReturnException(std::move(val));
    }
    
    std::unordered_map<std::string, NumberVariant> Interpreter::make_instance_fields(
        const std::string& className
    ) {
        std::unordered_map<std::string, NumberVariant> fields;

        auto it = context->user_types.find(className);
        if (it == context->user_types.end()) return fields;
        auto& info = it->second;
        if (!info.baseClassName.empty()) {
            auto baseFields = make_instance_fields(info.baseClassName);
            fields.insert(baseFields.begin(), baseFields.end());
        }
        for (auto& f : info.classFields) {
            fields[f.name] = def_value_for_type(f.type);
        }

        return fields;
    }
    size_t Interpreter::get_sizeof_type(const std::string& type) {
        std::string base_type = type;
        size_t ptr_count = 0;
        while (!base_type.empty() && base_type.back() == '*') {
            base_type.pop_back();
            ptr_count++;
        }
        if (!base_type.empty() && base_type.back() == '&') {
            base_type.pop_back();
        }
        base_type.erase(base_type.find_last_not_of(" \t") + 1);
        if (ptr_count > 0) {
            return 8;
        }
        if (base_type == "char") return 1;
        if (base_type == "bool") return 1;
        if (base_type == "qbool") return 1;
        if (base_type == "short" || base_type == "short int") return 2;
        if (base_type == "int") return 4;
        if (base_type == "long" || base_type == "long int") return 8;
        if (base_type == "float") return 4;
        if (base_type == "double") return 8;
        if (base_type == "long double") return 16;
        auto ut_it = context->user_types.find(base_type);
        if (ut_it != context->user_types.end()) {
            if (ut_it->second.kind == UserTypeKind::Struct) {
                size_t total = 0;
                for (auto& field : ut_it->second.fields) {
                    total += get_sizeof_type(field.type);
                }
                return total;
            }
            else if (ut_it->second.kind == UserTypeKind::Class) {
                size_t total = 0;
                for (auto& field : ut_it->second.classFields) {
                    total += get_sizeof_type(field.type);
                }
                return total;
            }
        }
        if (base_type.find("[]") != std::string::npos) return 8;
        if (base_type.find("list<") != std::string::npos) return 8;
        if (base_type.find("map<") != std::string::npos) return 8;
        return 0;
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<CallNode>& node) {
        if (!node) return Number<int>(0);
        NumberVariant target_val;  
        std::string func_name = "<anonymous>";
        std::vector<NumberVariant> final_args;
        std::vector<std::string>   final_lvalues;
        if (std::holds_alternative<std::unique_ptr<VarAccessNode>>(node->node_to_call)) {
            auto& varacc = std::get<std::unique_ptr<VarAccessNode>>(node->node_to_call);
            func_name = varacc->var_name_tok.value;
            if (func_name == "throw") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: throw() requires exactly 1 argument", get_pos(target_val)), "Error"});
                }
                
                NumberVariant value = this->process(node->arg_nodes.front());
                throw value;
            }
            if (func_name == "qout") {
                if (node->arg_nodes.size() < 1) {
                    this->errors.push_back({RTError("QC-B001: qout() requires at least 1 argument", get_pos(target_val)), "Error"});
                }
                std::vector<NumberVariant> args;
                for (auto& arg : node->arg_nodes) {
                    args.push_back(this->process(arg));
                }
                int current_arg = 0;
                std::string val = this->value_to_string(args[0]);
                std::string to_print;
                for (size_t i = 0; i < val.size(); i++) {
                    char c = val[i];
                    if (c != '%') {
                        to_print += c;
                        continue;
                    }
                    i++;
                    if (i >= val.size()) {
                        this->errors.push_back({RTError("QC-Q003: invalid formatter", get_pos(target_val)), "Error"});
                        break;
                    }
                    bool zero_pad = false;
                    int width = -1;
                    int precision = -1;
                    c = val[i];
                    if (c == '%') {
                        to_print += '%';
                        continue;
                    } else if (c == '0') {
                        zero_pad = true;
                        i++;
                        if (i >= val.size()) {
                            this->errors.push_back({RTError("QC-Q003: invalid formatter", get_pos(target_val)), "Error"});
                            break;
                        }
                        c = val[i];
                    }
                    if (std::isdigit(static_cast<unsigned char>(c))) {
                        std::string num;
                        while (i < val.size() && std::isdigit(static_cast<unsigned char>(val[i]))) {
                            num += val[i];
                            i++;
                        }
                        c = val[i];
                        width = std::stoi(num);
                    }
                    if (c == '.') {
                        i++;
                        if (i >= val.size()) {
                            this->errors.push_back({RTError("QC-Q003: invalid formatter", get_pos(target_val)), "Error"});
                            break;
                        }
                        c = val[i];
                        if (std::isdigit(static_cast<unsigned char>(c))) {
                            std::string num;
                            while (i < val.size() && std::isdigit(static_cast<unsigned char>(val[i]))) {
                                num += val[i];
                                i++;
                            }
                            c = val[i];
                            precision = std::stoi(num);
                        } else {
                            this->errors.push_back({RTError("QC-Q003: invalid formatter", get_pos(target_val)), "Error"});
                            break;
                        }
                    }
                    switch (c) {
                        case 'i':
                            current_arg++;
                            if (args.size() - 1 < current_arg) {
                                this->errors.push_back({RTError("QC-B001: too few arguments to qout().", get_pos(target_val)), "Error"});
                            } else if (auto is_intVal = std::get_if<Number<int>>(&args[current_arg])) {
                                std::stringstream ss;
                                if (zero_pad) ss << std::setfill('0');
                                if (width >= 0) ss << std::setw(width);
                                ss << is_intVal->value;
                                to_print += ss.str();
                            } else {
                                this->errors.push_back({RTError("QC-B002: qout(): i formater takes a int", get_pos(target_val)), "Error"});
                            } 
                            break;
                        case 's':
                            current_arg++;
                            if (current_arg >= args.size()) {
                                this->errors.push_back({
                                    RTError("QC-B001: too few arguments to qout().", get_pos(target_val)),
                                    "Error"
                                });
                            } else if (i + 1 < val.size()) {
                                if (val[i + 1] == 't') {
                                    i++;
                                    if (std::get_if<std::shared_ptr<StructValue>>(&args[current_arg])) {
                                        to_print += this->value_to_string(args[current_arg]);
                                    } else {
                                        this->errors.push_back({
                                            RTError("QC-B002: st formater requires a struct value.", get_pos(target_val)),
                                            "Error"
                                        });
                                    }
                                } else {
                                    if (std::get_if<StringValue>(&args[current_arg])) {
                                        to_print += this->value_to_string(args[current_arg]);
                                    } else {
                                        this->errors.push_back({RTError("QC-B002: qout(): s formater takes a string", get_pos(target_val)), "Error"});
                                    }
                                }
                            } else {
                                if (std::get_if<StringValue>(&args[current_arg])) {
                                    to_print += this->value_to_string(args[current_arg]);
                                } else {
                                    this->errors.push_back({RTError("QC-B002: qout(): s formater takes a string", get_pos(target_val)), "Error"});
                                }
                            }
                            break;
                        case 'f':
                            current_arg++;
                            if (args.size() - 1 < current_arg) {
                                this->errors.push_back({RTError("QC-B001: too few arguments to qout().", get_pos(target_val)), "Error"});
                            } else if (auto is_ftVal = std::get_if<Number<float>>(&args[current_arg])) {
                                std::stringstream ss;
                                if (zero_pad) ss << std::setfill('0');
                                if (width >= 0) ss << std::setw(width);
                                if (precision >= 0) ss << std::setprecision(precision);
                                ss << std::fixed << is_ftVal->value;
                                to_print += ss.str();
                            } else {
                                this->errors.push_back({RTError("QC-B002: qout(): f formater takes a float", get_pos(target_val)), "Error"});
                            } 
                            break;
                        case 'd':
                            current_arg++;
                            if (args.size() - 1 < current_arg) {
                                this->errors.push_back({RTError("QC-B001: too few arguments to qout().", get_pos(target_val)), "Error"});
                            } else if (auto is_dobVal = std::get_if<Number<double>>(&args[current_arg])) {
                                std::stringstream ss;
                                if (zero_pad) ss << std::setfill('0');
                                if (width >= 0) ss << std::setw(width);
                                if (precision >= 0) ss << std::setprecision(precision);
                                ss << is_dobVal->value;
                                to_print += ss.str();
                            } else {
                                this->errors.push_back({RTError("QC-B002: qout(): d formater takes a double", get_pos(target_val)), "Error"});
                            } 
                            break;
                        case 'c':
                            current_arg++;
                            if (args.size() - 1 < current_arg) this->errors.push_back({RTError("QC-B001: too few arguments to qout().", get_pos(target_val)), "Error"});
                            if (i >= val.size()) {
                            } else if (val[i + 1] == 's') {
                                i++;
                                if (std::get_if<std::shared_ptr<InstanceValue>>(&args[current_arg])) { 
                                    to_print += this->value_to_string(args[current_arg]);
                                } else {
                                    this->errors.push_back({RTError("QC-B002: qout(): cs formater takes a class instance", get_pos(target_val)), "Error"});
                                }
                            }
                            else if (std::get_if<CharValue>(&args[current_arg])) { 
                                to_print += this->value_to_string(args[current_arg]);
                            } else {
                                this->errors.push_back({RTError("QC-B002: qout(): c formater takes a char", get_pos(target_val)), "Error"});
                            }
                            break; 
                        case 'b':
                            current_arg++;
                            if (args.size() - 1 < current_arg) this->errors.push_back({RTError("QC-B001: too few arguments to qout().", get_pos(target_val)), "Error"});
                            else to_print += this->value_to_string(args[current_arg]);
                            break;
                        case 'q':
                            current_arg++;
                            if (args.size() - 1 < current_arg) this->errors.push_back({RTError("QC-B001: too few arguments to qout().", get_pos(target_val)), "Error"});
                            else to_print += this->value_to_string(args[current_arg]);
                            break;
                        case 'p':
                            current_arg++;
                            if (args.size() - 1 < current_arg) this->errors.push_back({RTError("QC-B001: too few arguments to qout().", get_pos(target_val)), "Error"});
                            else if (std::get_if<PointerValue>(&args[current_arg])) { to_print += this->value_to_string(args[current_arg]); }
                            else { this->errors.push_back({RTError("QC-B002: qout(): p formater takes a pointer", get_pos(target_val)), "Error"}); }
                            break;
                        case 'x':
                            current_arg++;
                            if (args.size() - 1 < current_arg) this->errors.push_back({RTError("QC-B001: too few arguments to qout().", get_pos(target_val)), "Error"});
                            if (auto is_intVal = std::get_if<Number<int>>(&args[current_arg])) {
                                std::stringstream ss;
                                if (zero_pad) ss << std::setfill('0');
                                if (width >= 0) ss << std::setw(width);
                                ss << std::showbase << std::hex << is_intVal->value;
                                to_print += ss.str();
                            } else {
                                this->errors.push_back({RTError("QC-B002: qout(): x formater takes a int", get_pos(target_val)), "Error"});
                            }   
                            break;  
                        case 'o':
                            current_arg++;
                            if (args.size() - 1 < current_arg) this->errors.push_back({RTError("QC-B001: too few arguments to qout().", get_pos(target_val)), "Error"});
                            if (auto is_intVal = std::get_if<Number<int>>(&args[current_arg])) {
                                std::stringstream ss;
                                if (zero_pad) ss << std::setfill('0');
                                if (width >= 0) ss << std::setw(width);
                                ss << std::showbase << std::oct << is_intVal->value;
                                to_print += ss.str();
                            } else {
                                this->errors.push_back({RTError("QC-B002: qout(): o formater takes a int", get_pos(target_val)), "Error"});
                            }   
                            break;
                        case 'e':
                            current_arg++;
                            if (args.size() - 1 < current_arg) this->errors.push_back({RTError("QC-B001: too few arguments to qout().", get_pos(target_val)), "Error"});
                            if (auto is_intVal = std::get_if<Number<int>>(&args[current_arg])) {
                                std::stringstream ss;
                                if (zero_pad) ss << std::setfill('0');
                                if (width >= 0) ss << std::setw(width);
                                if (precision >= 0) ss << std::setprecision(precision);
                                ss << std::scientific << is_intVal->value;
                                to_print += ss.str();
                            } else if (auto is_dobVal = std::get_if<Number<double>>(&args[current_arg])) {
                                std::stringstream ss;
                                if (zero_pad) ss << std::setfill('0');
                                if (width >= 0) ss << std::setw(width);
                                if (precision >= 0) ss << std::setprecision(precision);
                                ss << std::scientific << is_dobVal->value;
                                to_print += ss.str();
                            } else if (auto is_ftVal = std::get_if<Number<float>>(&args[current_arg])) {
                                std::stringstream ss;
                                if (zero_pad) ss << std::setfill('0');
                                if (width >= 0) ss << std::setw(width);
                                if (precision >= 0) ss << std::setprecision(precision);
                                ss << std::scientific << is_ftVal->value;
                                to_print += ss.str();
                            } else if (auto is_sVal = std::get_if<Number<short>>(&args[current_arg])) {
                                std::stringstream ss;
                                if (zero_pad) ss << std::setfill('0');
                                if (width >= 0) ss << std::setw(width);
                                if (precision >= 0) ss << std::setprecision(precision);
                                ss << std::scientific << is_sVal->value;
                                to_print += ss.str();
                            } else if (auto is_llVal = std::get_if<Number<long long>>(&args[current_arg])) {
                                std::stringstream ss;
                                if (zero_pad) ss << std::setfill('0');
                                if (width >= 0) ss << std::setw(width);
                                if (precision >= 0) ss << std::setprecision(precision);
                                ss << std::scientific << is_llVal->value;
                                to_print += ss.str();
                            } else if (auto is_ldVal = std::get_if<Number<long double>>(&args[current_arg])) {
                                std::stringstream ss;
                                if (zero_pad) ss << std::setfill('0');
                                if (width >= 0) ss << std::setw(width);
                                if (precision >= 0) ss << std::setprecision(precision);
                                ss << std::scientific << is_ldVal->value;
                                to_print += ss.str();
                            } else {
                                this->errors.push_back({RTError("QC-B002: qout(): e formatter takes a numeric type", get_pos(target_val)), "Error"});
                            }   
                            break; 
                        case 'a':
                            current_arg++;
                            if (args.size() - 1 < current_arg) this->errors.push_back({RTError("QC-B001: too few arguments to qout().", get_pos(target_val)), "Error"});
                            else to_print += this->value_to_string(args[current_arg]);
                            break;                
                        default:
                            this->errors.push_back({RTError("QC-Q003: invalid formatter", get_pos(target_val)), "Error"});
                    }
                }
                std::cout << to_print;
                return Number<int>(0);
            }
            if (func_name == "random") {
                std::vector<NumberVariant> args;
                for (auto& arg : node->arg_nodes) {
                    args.push_back(this->process(arg));
                }
                if (!random_seeded) {
                    srand(static_cast<unsigned int>(time(nullptr)));
                    random_seeded = true;
                }
                if (args.size() == 0) {
                    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                    return Number<float>(r);
                }
                else if (args.size() == 1) {
                    if (auto max_num = std::get_if<Number<int>>(&args[0])) {
                        int r = rand() % max_num->value;
                        return Number<int>(r);
                    }
                    this->errors.push_back({RTError("QC-B002: random(max) requires integer argument",  get_pos(args[0])), "Error"});
                }
                else if (args.size() == 2) {
                    if (auto min_num = std::get_if<Number<int>>(&args[0])) {
                        if (auto max_num = std::get_if<Number<int>>(&args[1])) {
                            int range = max_num->value - min_num->value;
                            int r = min_num->value + (rand() % range);
                            return Number<int>(r);
                        }
                    }
                    this->errors.push_back({RTError("QC-B002: random(min, max) requires integer arguments", get_pos(args[1])), "Error"});
                }
                
                this->errors.push_back({RTError("QC-B001: random() takes 0, 1, or 2 arguments", get_pos(args[2])), "Error"});
            }
            if (func_name == "time") {
                if (node->arg_nodes.size() != 0) {
                    this->errors.push_back({RTError("QC-B001: time() takes no arguments", Position()), "Error"});
                }
                
                return Number<int>(static_cast<int>(time(nullptr)));
            }
            if (func_name == "seed") {
                
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: seed() requires exactly 1 argument", Position()), "Error"});
                }
                
                NumberVariant seed_val = this->process(node->arg_nodes.front());
                
                if (auto seed_num = std::get_if<Number<int>>(&seed_val)) {
                    srand(seed_num->value);
                    random_seeded = true;
                    return VoidValue();
                }
                
                this->errors.push_back({RTError("QC-B002: seed() requires integer argument",  get_pos(seed_val)), "Error"});
            }
            if (func_name == "typeof") {
                
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: typeof() requires exactly 1 argument", Position()), "Error"});
                }
                
                NumberVariant value = this->process(node->arg_nodes.front());
                
                return StringValue(this->context->get_type_name(value));
            }
            if (func_name == "to_qbool") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: to_qbool() requires exactly 1 argument", Position()), "Error"});
                }

                NumberVariant cur_val = this->process(node->arg_nodes.front());

                if (auto bv = std::get_if<BoolValue>(&cur_val)) {
                    return QBoolValue("q" + value_to_string(*bv)).set_pos(bv->pos);
                } else if (auto qbv = std::get_if<QBoolValue>(&cur_val)) {
                    return *qbv;
                } else if (auto sv = std::get_if<StringValue>(&cur_val)) {
                    if (sv->value == "qtrue" || sv->value == "qfalse" ||
                        sv->value == "none"  || sv->value == "both") {
                        return QBoolValue(sv->value).set_pos(sv->pos);
                    }
                    this->errors.push_back({RTError(
                        "QC-B002: to_qbool() requires string argument to be qtrue qfalse both or none.",
                        sv->pos),
                        "Error"});
                } else {
                    this->errors.push_back({RTError(
                        "QC-B002: to_qbool() requires string or boolean argument",
                        get_pos(cur_val)),
                        "Error"});
                }
            }

            if (func_name == "to_bool") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: to_bool() requires exactly 1 argument", Position()), "Error"});
                }

                NumberVariant cur_val = this->process(node->arg_nodes.front());

                if (auto qbv = std::get_if<QBoolValue>(&cur_val)) {
                    return BoolValue(qbv->tval ? "true" : "false").set_pos(qbv->pos);
                } else if (auto bv = std::get_if<BoolValue>(&cur_val)) {
                    return *bv;
                } else if (auto sv = std::get_if<StringValue>(&cur_val)) {
                    if (sv->value == "true" || sv->value == "false") {
                        return BoolValue(sv->value).set_pos(sv->pos);
                    }
                    this->errors.push_back({RTError(
                        "QC-B002: to_bool() requires string argument to be true or false.",
                        sv->pos),
                        "Error"});
                } else {
                    this->errors.push_back({RTError(
                        "QC-B002: to_bool() requires string or quantum boolean argument",
                        get_pos(cur_val)),
                        "Error"});
                }
            }

            if (func_name == "to_int") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: to_int() requires exactly 1 argument", Position()), "Error"});
                }

                NumberVariant cur_val = this->process(node->arg_nodes.front());

                if (auto fv = std::get_if<Number<float>>(&cur_val)) {
                    return Number<int>(static_cast<int>(fv->value)).set_pos(fv->pos);
                } else if (auto dv = std::get_if<Number<double>>(&cur_val)) {
                    return Number<int>(static_cast<int>(dv->value)).set_pos(dv->pos);
                } else if (auto iv = std::get_if<Number<int>>(&cur_val)) {
                    return *iv;
                } else if (auto sv = std::get_if<StringValue>(&cur_val)) {
                    try {
                        return Number<int>(std::stoi(sv->value)).set_pos(sv->pos);
                    } catch (...) {
                        this->errors.push_back({RTError(
                            "QC-B002: could not convert value to int.",
                            sv->pos),
                            "Error"});
                    }
                } else if (auto qbv = std::get_if<QBoolValue>(&cur_val)) {
                    int val = 0;
                    if      (qbv->valname == "none")   val = 0;
                    else if (qbv->valname == "qfalse") val = 1;
                    else if (qbv->valname == "qtrue")  val = 2;
                    else if (qbv->valname == "both")   val = 3;
                    else throw RTError("QC-WHAT: What the heck is that", qbv->pos);

                    return Number<int>(val).set_pos(qbv->pos);
                } else if (auto bv = std::get_if<BoolValue>(&cur_val)) {
                    return Number<int>(bv->value ? 1 : 0).set_pos(bv->pos);
                } else {
                    this->errors.push_back({RTError(
                        "QC-B002: to_int() cannot take that argument type.",
                        get_pos(cur_val)),
                        "Error"});
                }
            }

            if (func_name == "to_float") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: to_float() requires exactly 1 argument", Position()), "Error"});
                }

                NumberVariant cur_val = this->process(node->arg_nodes.front());

                if (auto fv = std::get_if<Number<float>>(&cur_val)) {
                    return *fv;
                } else if (auto dv = std::get_if<Number<double>>(&cur_val)) {
                    return Number<float>(static_cast<float>(dv->value)).set_pos(dv->pos);
                } else if (auto iv = std::get_if<Number<int>>(&cur_val)) {
                    return Number<float>(static_cast<float>(iv->value)).set_pos(iv->pos);
                } else if (auto sv = std::get_if<StringValue>(&cur_val)) {
                    try {
                        return Number<float>(std::stof(sv->value)).set_pos(sv->pos);
                    } catch (...) {
                        this->errors.push_back({RTError(
                            "QC-B002: could not convert value to float.",
                            sv->pos),
                            "Error"});
                    }
                } else {
                    this->errors.push_back({RTError(
                        "QC-B002: to_float() cannot take that argument type.",
                        get_pos(cur_val)),
                        "Error"});
                }
            }

            if (func_name == "to_double") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: to_double() requires exactly 1 argument", Position()), "Error"});
                }

                NumberVariant cur_val = this->process(node->arg_nodes.front());

                if (auto fv = std::get_if<Number<float>>(&cur_val)) {
                    return Number<double>(static_cast<double>(fv->value)).set_pos(fv->pos);
                } else if (auto dv = std::get_if<Number<double>>(&cur_val)) {
                    return *dv;
                } else if (auto iv = std::get_if<Number<int>>(&cur_val)) {
                    return Number<double>(static_cast<double>(iv->value)).set_pos(iv->pos);
                } else if (auto sv = std::get_if<StringValue>(&cur_val)) {
                    try {
                        return Number<double>(std::stod(sv->value)).set_pos(sv->pos);
                    } catch (...) {
                        this->errors.push_back({RTError(
                            "QC-B002: could not convert value to double.",
                            sv->pos),
                            "Error"});
                    }
                } else {
                    this->errors.push_back({RTError(
                        "QC-B002: to_double() cannot take that argument type.",
                        get_pos(cur_val)),
                        "Error"});
                }
            }

            if (func_name == "to_char") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: to_char() requires exactly 1 argument", Position()), "Error"});
                }

                NumberVariant cur_val = this->process(node->arg_nodes.front());

                if (auto sv = std::get_if<StringValue>(&cur_val)) {
                    if (!sv->value.empty()) {
                        return CharValue(std::string(1, sv->value[0])).set_pos(sv->pos);
                    }
                    this->errors.push_back({RTError(
                        "QC-B002: to_char() cannot take empty string.",
                        sv->pos),
                        "Error"});
                } else if (auto cv = std::get_if<CharValue>(&cur_val)) {
                    return *cv;
                } else {
                    this->errors.push_back({RTError(
                        "QC-B002: to_char() cannot take that argument type.",
                        get_pos(cur_val)),
                        "Error"});
                }
            }
            if (func_name == "to_string") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: to_string() requires exactly 1 argument", Position()), "Error"});
                }

                NumberVariant cur_val = this->process(node->arg_nodes.front());

                if (auto fv = std::get_if<Number<float>>(&cur_val)) {
                    return StringValue(std::to_string(fv->value)).set_pos(fv->pos);
                } else if (auto dv = std::get_if<Number<double>>(&cur_val)) {
                    return StringValue(std::to_string(dv->value)).set_pos(dv->pos);
                } else if (auto iv = std::get_if<Number<int>>(&cur_val)) {
                    return StringValue(std::to_string(iv->value)).set_pos(iv->pos);
                } else if (auto sv = std::get_if<StringValue>(&cur_val)) {
                    return *sv;
                } else if (auto qbv = std::get_if<QBoolValue>(&cur_val)) {
                    return StringValue(qbv->valname).set_pos(qbv->pos);
                } else if (auto bv = std::get_if<BoolValue>(&cur_val)) {
                    return StringValue(bv->value ? "true" : "false").set_pos(bv->pos);
                } else {
                    this->errors.push_back({RTError(
                        "QC-B002: to_string() cannot take that argument type.",
                        get_pos(cur_val)),
                        "Error"});
                }
            }
            if (func_name == "split") {
                if (node->arg_nodes.size() != 2) {
                    this->errors.push_back({RTError("QC-B001: split() requires exactly 2 arguments", Position()), "Error"});
                }

                auto it = node->arg_nodes.begin();
                NumberVariant str_val = this->process(*it);

                std::advance(it, 1);
                NumberVariant delim_val = this->process(*it);

                if (!std::holds_alternative<StringValue>(str_val) || !std::holds_alternative<StringValue>(delim_val)) {
                    this->errors.push_back({RTError("QC-B002: split() requires string arguments", get_pos(str_val)), "Error"});
                }

                std::string s = std::get<StringValue>(str_val).value;
                std::string delim = std::get<StringValue>(delim_val).value;

                std::vector<NumberVariant> out;
                size_t start = 0;
                size_t pos = s.find(delim);

                while (pos != std::string::npos) {
                    out.push_back(StringValue(s.substr(start, pos - start)));
                    start = pos + delim.size();
                    pos = s.find(delim, start);
                }

                out.push_back(StringValue(s.substr(start)));

                return std::make_shared<ListValue>("string", out);
            }
            if (func_name == "len") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: len() requires exactly 1 argument", Position()), "Error"});
                }

                auto it = node->arg_nodes.begin();
                NumberVariant val = this->process(*it);

                if (auto sv = std::get_if<StringValue>(&val)) {
                    return Number<int>(static_cast<int>(sv->value.size())).set_pos(sv->pos);
                } else {
                    this->errors.push_back({RTError("QC-B002: len() requires string argument", get_pos(val)), "Error"});
                }
            }
            if (func_name == "to_lower") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: to_lower() requires exactly 1 argument", Position()), "Error"});
                }

                auto it = node->arg_nodes.begin();
                NumberVariant val = this->process(*it);

                if (auto sv = std::get_if<StringValue>(&val)) {
                    std::string out = sv->value;
                    std::transform(out.begin(), out.end(), out.begin(), ::tolower);
                    return StringValue(out).set_pos(sv->pos);
                } else {
                    this->errors.push_back({RTError("QC-B002: to_lower() requires string argument", get_pos(val)), "Error"});
                }
            }
            if (func_name == "to_upper") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: to_upper() requires exactly 1 argument", Position()), "Error"});
                }

                auto it = node->arg_nodes.begin();
                NumberVariant val = this->process(*it);

                if (auto sv = std::get_if<StringValue>(&val)) {
                    std::string out = sv->value;
                    std::transform(out.begin(), out.end(), out.begin(), ::toupper);
                    return StringValue(out).set_pos(sv->pos);
                } else {
                    this->errors.push_back({RTError("QC-B002: to_upper() requires string argument", get_pos(val)), "Error"});
                }
            }
            if (func_name == "fopen") {
                if (node->arg_nodes.size() != 2) {
                    this->errors.push_back({RTError("QC-B001: fopen() requires exactly 2 arguments (path, mode)", Position()), "Error"});
                    return VoidValue();
                }
                
                NumberVariant path_val = this->process(node->arg_nodes.front());
                NumberVariant mode_val = this->process(node->arg_nodes.back());
                
                auto path_str = std::get_if<StringValue>(&path_val);
                auto mode_str = std::get_if<StringValue>(&mode_val);
                
                if (!path_str || !mode_str) {
                    this->errors.push_back({RTError("QC-B002: fopen() requires string arguments", Position()), "Error"});
                    return VoidValue();
                }
                
                FILE* file = fopen(path_str->value.c_str(), mode_str->value.c_str());
                if (!file) {
                    this->errors.push_back({RTError("QC-B003: Failed to open file: " + path_str->value, Position()), "Error"});
                    return StringValue("");
                }
                
                std::ostringstream oss;
                oss << (void*)file;
                return StringValue(oss.str()).set_pos(path_str->pos);
            }

            if (func_name == "fclose") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: fclose() requires exactly 1 argument", Position()), "Error"});
                    return VoidValue();
                }
                
                NumberVariant file_val = this->process(node->arg_nodes.front());
                
                if (auto file_str = std::get_if<StringValue>(&file_val)) {
                    void* ptr;
                    std::istringstream iss(file_str->value);
                    iss >> ptr;
                    FILE* file = (FILE*)ptr;
                    if (file) fclose(file);
                    return VoidValue();
                }
                this->errors.push_back({RTError("QC-B002: fclose() requires file handle", Position()), "Error"});
                return VoidValue();
            }

            if (func_name == "fread") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: fread() requires exactly 1 argument", Position()), "Error"});
                    return StringValue("");
                }
                
                NumberVariant file_val = this->process(node->arg_nodes.front());
                
                if (auto file_str = std::get_if<StringValue>(&file_val)) {
                    void* ptr;
                    std::istringstream iss(file_str->value);
                    iss >> ptr;
                    FILE* file = (FILE*)ptr;
                    
                    if (!file) return StringValue("");
                    
                    char buffer[1024];
                    if (fgets(buffer, sizeof(buffer), file)) {
                        std::string line(buffer);
                        if (!line.empty() && line.back() == '\n') {
                            line.pop_back();
                        }
                        return StringValue(line);
                    }
                    return StringValue("");
                }
                
                this->errors.push_back({RTError("QC-B002: fread() requires file handle", Position()), "Error"});
                return StringValue("");
            }

            if (func_name == "fwrite") {
                if (node->arg_nodes.size() != 2) {
                    this->errors.push_back({RTError("QC-B001: fwrite() requires exactly 2 arguments (file, data)", Position()), "Error"});
                    return VoidValue();
                }
                
                NumberVariant file_val = this->process(node->arg_nodes.front());
                NumberVariant data_val = this->process(node->arg_nodes.back());
                
                if (auto file_str = std::get_if<StringValue>(&file_val)) {
                    void* ptr;
                    std::istringstream iss(file_str->value);
                    iss >> ptr;
                    FILE* file = (FILE*)ptr;
                    
                    if (!file) return VoidValue();
                    
                    std::string data = value_to_string(data_val);
                    fputs(data.c_str(), file);
                    fputc('\n', file);
                    return VoidValue();
                }
                
                this->errors.push_back({RTError("QC-B002: fwrite() requires file handle", Position()), "Error"});
                return VoidValue();
            }
            if (func_name == "substring") {
                if (node->arg_nodes.size() != 3) {
                    this->errors.push_back({RTError("QC-B001: substring() requires 3 arguments", Position()), "Error"});
                }

                auto it = node->arg_nodes.begin();
                NumberVariant str_val = this->process(*it);

                std::advance(it, 1);
                NumberVariant start_val = this->process(*it);

                std::advance(it, 1);
                NumberVariant len_val = this->process(*it);

                if (auto sv = std::get_if<StringValue>(&str_val)) {
                    if (auto start_n = std::get_if<Number<int>>(&start_val)) {
                        if (auto len_n = std::get_if<Number<int>>(&len_val)) {             
                            std::string s = sv->value;
                            int start = start_n->value;
                            int len   = len_n->value;
                            if (start < 0 || len < 0 || start > (int)s.size()) {
                                return StringValue("").set_pos(sv->pos);
                            }
                            if (start + len > (int)s.size()) {
                                len = s.size() - start;
                            }

                            std::string out = s.substr(start, len);
                            return StringValue(out).set_pos(sv->pos);
                        }
                    }
                    this->errors.push_back({RTError("QC-B002: substring() requires (string, int, int)", get_pos(str_val)), "Error"});
                } else {
                    this->errors.push_back({RTError("QC-B002: substring() requires string argument", get_pos(str_val)), "Error"});
                }
            }
            if (func_name == "join") {
                if (node->arg_nodes.size() != 2) {
                    this->errors.push_back({RTError("QC-B001: join() requires 2 arguments", Position()), "Error"});
                }

                auto it = node->arg_nodes.begin();
                NumberVariant list_val = this->process(*it);

                std::advance(it, 1);
                NumberVariant delim_val = this->process(*it);

                if (auto lv = std::get_if<std::shared_ptr<ListValue>>(&list_val)) {
                    if (auto sv = std::get_if<StringValue>(&delim_val)) {
                        std::string out;
                        for (size_t i = 0; i < (*lv)->elements.size(); i++) {
                            auto& el = (*lv)->elements[i];
                            if (auto s = std::get_if<StringValue>(&el)) {
                                out += s->value;
                                if (i != (*lv)->elements.size() - 1) out += sv->value;
                            } else {
                                this->errors.push_back({RTError("QC-B002: join() requires list of strings", get_pos(el)), "Error"});
                            }
                        }
                        return StringValue(out).set_pos(sv->pos);
                    }
                }

                this->errors.push_back({RTError("QC-B002: join() requires (list, string)", get_pos(list_val)), "Error"});
            }
            if (func_name == "contains") {
                if (node->arg_nodes.size() != 2) {
                    this->errors.push_back({RTError("QC-B001: contains() requires 2 arguments", Position()), "Error"});
                }

                auto it = node->arg_nodes.begin();
                NumberVariant str_val = this->process(*it);

                std::advance(it, 1);
                NumberVariant substr_val = this->process(*it);

                if (auto sv = std::get_if<StringValue>(&str_val)) {
                    if (auto ss = std::get_if<StringValue>(&substr_val)) {
                        bool res = (sv->value.find(ss->value) != std::string::npos);
                        return BoolValue(res ? "true" : "false").set_pos(sv->pos);
                    }
                }

                this->errors.push_back({RTError("QC-B002: contains() requires (string, string)", get_pos(str_val)), "Error"});
            }
            if (func_name == "startswith") {
                if (node->arg_nodes.size() != 2) {
                    this->errors.push_back({RTError("QC-B001: startswith() requires 2 arguments", Position()), "Error"});
                }

                auto it = node->arg_nodes.begin();
                NumberVariant str_val = this->process(*it);

                std::advance(it, 1);
                NumberVariant prefix_val = this->process(*it);

                if (auto sv = std::get_if<StringValue>(&str_val)) {
                    if (auto ss = std::get_if<StringValue>(&prefix_val)) {
                        bool res = (sv->value.rfind(ss->value, 0) == 0);
                        return BoolValue(res ? "true" : "false").set_pos(sv->pos);
                    }
                }

                this->errors.push_back({RTError("QC-B002: startswith() requires (string, string)", get_pos(str_val)), "Error"});
            }
            if (func_name == "endswith") {
                if (node->arg_nodes.size() != 2) {
                    this->errors.push_back({RTError("QC-B001: endswith() requires 2 arguments", Position()), "Error"});
                }

                auto it = node->arg_nodes.begin();
                NumberVariant str_val = this->process(*it);

                std::advance(it, 1);
                NumberVariant suffix_val = this->process(*it);

                if (auto sv = std::get_if<StringValue>(&str_val)) {
                    if (auto ss = std::get_if<StringValue>(&suffix_val)) {
                        bool res = (sv->value.size() >= ss->value.size() &&
                                    sv->value.compare(sv->value.size() - ss->value.size(), ss->value.size(), ss->value) == 0);
                        return BoolValue(res ? "true" : "false").set_pos(sv->pos);
                    }
                }

                this->errors.push_back({RTError("QC-B002: endswith() requires (string, string)", get_pos(str_val)), "Error"});
            }
            if (func_name == "trim") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: trim() requires exactly 1 argument", Position()), "Error"});
                }

                auto it = node->arg_nodes.begin();
                NumberVariant val = this->process(*it);

                if (auto sv = std::get_if<StringValue>(&val)) {
                    std::string s = sv->value;
                    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front()))) {
                        s.erase(s.begin());
                    }
                    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back()))) {
                        s.pop_back();
                    }

                    return StringValue(s).set_pos(sv->pos);
                }

                this->errors.push_back({RTError("QC-B002: trim() requires string argument", get_pos(val)), "Error"});
            }
            if (func_name == "replace") {
                if (node->arg_nodes.size() != 3) {
                    this->errors.push_back({RTError("QC-B001: replace() requires 3 arguments", Position()), "Error"});
                }

                auto it = node->arg_nodes.begin();
                NumberVariant str_val = this->process(*it);

                std::advance(it, 1);
                NumberVariant find_val = this->process(*it);

                std::advance(it, 1);
                NumberVariant replace_val = this->process(*it);

                if (auto sv = std::get_if<StringValue>(&str_val)) {
                    if (auto fs = std::get_if<StringValue>(&find_val)) {
                        if (auto rs = std::get_if<StringValue>(&replace_val)) {
                            std::string out = sv->value;
                            size_t pos = out.find(fs->value);

                            while (pos != std::string::npos) {
                                out.replace(pos, fs->value.size(), rs->value);
                                pos = out.find(fs->value, pos + rs->value.size());
                            }

                            return StringValue(out).set_pos(sv->pos);
                        }
                    }
                }

                this->errors.push_back({RTError("QC-B002: replace() requires (string, string, string)", get_pos(str_val)), "Error"});
            }
            if (func_name == "sizeof") {
                if (node->arg_nodes.size() != 1) {
                    throw RTError("QC-B001: sizeof expects exactly 1 argument", Position("", "", 0, 0, 0));
                }
                NumberVariant arg_val = this->process(node->arg_nodes.front());
                
                auto str_val = std::get_if<StringValue>(&arg_val);
                if (!str_val) {
                    throw RTError("QC-B002: sizeof expects a string argument (type name)", Position("", "", 0, 0, 0));
                }
                
                std::string type = str_val->value;
                size_t size = get_sizeof_type(type);
                
                if (size == 0) {
                    throw RTError("QC-B002: Unknown type: " + type, Position("", "", 0, 0, 0));
                }
                
                return Number<int>(size);
            }
            if (func_name == "malloc") {
                if (node->arg_nodes.size() != 1) {
                    throw RTError("QC-B001: malloc expects exactly 1 argument (type name string)", Position());
                }

                NumberVariant type_val = this->process(node->arg_nodes.front());
                auto sv = std::get_if<StringValue>(&type_val);
                if (!sv) {
                    throw RTError("QC-B002: malloc expects a string type name", get_pos(type_val));
                }

                std::string type_name = sv->value;
                size_t sz = this->get_sizeof_type(type_name);
                if (sz == 0) {
                    throw RTError("QC-B002: Unknown or unsupported type in malloc: " + type_name, get_pos(type_val));
                }

                NumberVariant def_val = def_value_for_type(type_name);
                size_t heap_id = context->heap_alloc(def_val);

                return PointerValue::heap_ptr(type_name, heap_id).set_pos(get_pos(type_val));
            }
            if (func_name == "free") {
                if (node->arg_nodes.size() != 1) {
                    throw RTError("QC-B001: free expects exactly 1 argument (pointer)", Position("", "", 0, 0, 0));
                }
                
                NumberVariant ptr_val = this->process(node->arg_nodes.front());
                
                auto ptr = std::get_if<PointerValue>(&ptr_val);
                if (!ptr) {
                    throw RTError("QC-B002: free expects a pointer argument", get_pos(ptr_val));
                }
                
                if (ptr->is_null) {
                    return VoidValue();
                }
                
                if (!ptr->is_heap) {
                    throw RTError("QC-M010: Cannot free stack-allocated memory", ptr->pos);
                }
                
                context->heap_free(ptr->heap_id);
                
                return VoidValue();
            }
            if (func_name == "calloc") {
                if (node->arg_nodes.size() != 2) {
                    throw RTError("QC-B001: calloc expects 2 arguments (count, type name)", Position());
                }

                auto it = node->arg_nodes.begin();
                NumberVariant count_val = this->process(*it);
                ++it;
                NumberVariant type_val = this->process(*it);

                int count = std::visit([&](auto&& arg) -> int {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, Number<int>>  ||
                                std::is_same_v<T, Number<long long>> ||
                                std::is_same_v<T, Number<short>>) {
                        return (int)arg.value;
                    }
                    throw RTError("QC-B002: calloc count must be an integer", get_pos(count_val));
                }, count_val);

                auto sv = std::get_if<StringValue>(&type_val);
                if (!sv) {
                    throw RTError("QC-B002: calloc type must be a string", get_pos(type_val));
                }
                std::string type_name = sv->value;

                if (count <= 0) {
                    throw RTError("QC-B002: calloc count must be positive", get_pos(count_val));
                }

                size_t sz = this->get_sizeof_type(type_name);
                if (sz == 0) {
                    throw RTError("QC-B002: Unknown or unsupported type in calloc: " + type_name, get_pos(type_val));
                }

                std::vector<NumberVariant> elems;
                elems.reserve(count);
                for (int i = 0; i < count; ++i) {
                    elems.push_back(def_value_for_type(type_name));
                }

                auto arr = std::make_shared<ArrayValue>(type_name, std::move(elems));
                size_t heap_id = context->heap_alloc(arr);

                return PointerValue::heap_ptr(type_name, heap_id).set_pos(get_pos(type_val));
            }
            if (func_name == "realloc") {
                if (node->arg_nodes.size() != 2) {
                    throw RTError("QC-B001: realloc expects 2 arguments (ptr, new_size)", Position());
                }

                auto it = node->arg_nodes.begin();
                NumberVariant ptr_val = this->process(*it);
                ++it;
                NumberVariant size_val = this->process(*it);

                auto ptr = std::get_if<PointerValue>(&ptr_val);
                if (!ptr) {
                    throw RTError("QC-B002: realloc expects a pointer as first argument", get_pos(ptr_val));
                }

                int new_size = std::visit([&](auto&& arg) -> int {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, Number<int>>  ||
                                std::is_same_v<T, Number<long long>> ||
                                std::is_same_v<T, Number<short>>) {
                        return (int)arg.value;
                    }
                    throw RTError("QC-B002: realloc size must be an integer", get_pos(size_val));
                }, size_val);

                if (new_size < 0) {
                    throw RTError("QC-B002: realloc size must be non-negative", get_pos(size_val));
                }

                if (ptr->is_null) {
                    if (new_size == 0) {
                        return PointerValue::heap_ptr("void", 0).set_pos(get_pos(ptr_val));
                    }
                    NumberVariant def_val = VoidValue();
                    size_t heap_id = context->heap_alloc(def_val);
                    return PointerValue::heap_ptr("void", heap_id).set_pos(get_pos(ptr_val));
                }

                if (!ptr->is_heap) {
                    throw RTError("QC-B002: Cannot realloc stack-allocated memory", ptr->pos);
                }

                if (!context->heap_valid(ptr->heap_id)) {
                    throw RTError("QC-B002: Cannot realloc freed memory", ptr->pos);
                }
                NumberVariant& block = context->heap_get(ptr->heap_id);
                if (std::holds_alternative<std::shared_ptr<ArrayValue>>(block)) {
                    throw RTError("QC-B002: realloc not allowed on array blocks (use calloc for arrays)", ptr->pos);
                }

                if (new_size == 0) {
                    context->heap_free(ptr->heap_id);
                    return PointerValue::heap_ptr(ptr->pointee_type, 0).set_pos(get_pos(ptr_val));
                }
                return *ptr;
            }
            auto ut_it = context->user_types.find(func_name);
            if (ut_it != context->user_types.end() &&
                ut_it->second.kind == UserTypeKind::Class) {

                UserTypeInfo& info = ut_it->second;
                bool inside_constructor = false;
                std::shared_ptr<InstanceValue> existing_inst = nullptr;
                if (info.is_abstract_class) {
                    errors.push_back({RTError("QC-B002: Cannot construct abstract class", Position()), "Error"});
                    return VoidValue();
                }
                try {
                    NumberVariant this_val = context->get("this", Position());
                    if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&this_val)) {
                        inside_constructor = true;
                        existing_inst = *inst_ptr;
                    }
                } catch (...) {
                }
                if (inside_constructor && existing_inst) {
                    std::string child_class = existing_inst->class_name;
                    auto child_ut = context->user_types.find(child_class);
                    
                    if (child_ut != context->user_types.end() && 
                        child_ut->second.baseClassName == func_name) {
                        ClassMethodInfo* ctor = nullptr;
                        for (auto& m : info.classMethods) {
                            if (m.is_constructor) {
                                ctor = &m;
                                break;
                            }
                        }

                        if (!ctor) {
                            return VoidValue();
                        }
                        final_args.clear();
                        final_lvalues.clear();

                        for (auto& arg : node->arg_nodes) {
                            if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&arg)) {
                                NumberVariant sv = this->process((*spread)->expr);
                                if (auto arr = std::get_if<std::shared_ptr<ArrayValue>>(&sv)) {
                                    for (auto& e : (*arr)->elements) {
                                        final_args.push_back(e);
                                        final_lvalues.push_back("");
                                    }
                                } else if (auto lst = std::get_if<std::shared_ptr<ListValue>>(&sv)) {
                                    for (auto& e : (*lst)->elements) {
                                        final_args.push_back(e);
                                        final_lvalues.push_back("");
                                    }
                                } else {
                                    this->errors.push_back({RTError("QC-I005: Spread target must be array or list", get_pos(sv)), "Error"});
                                }
                            } else {
                                if (auto varacc_ptr = std::get_if<std::unique_ptr<VarAccessNode>>(&arg)) {
                                    std::string var_name = (*varacc_ptr)->var_name_tok.value;
                                    NumberVariant v      = this->process(arg);
                                    final_args.push_back(v);
                                    final_lvalues.push_back(var_name);
                                } else {
                                    final_args.push_back(this->process(arg));
                                    final_lvalues.push_back("");
                                }
                            }
                        }
                        context->push_scope();

                        if (final_args.size() > ctor->params.size()) {
                            context->pop_scope();
                            this->errors.push_back({RTError("QC-C002: Too many arguments to parent constructor '" + func_name + "'", Position()), "Error"});
                            return VoidValue();
                        }

                        for (size_t i = 0; i < ctor->params.size(); ++i) {
                            auto it_param = ctor->params.begin();
                            std::advance(it_param, i);

                            NumberVariant value;
                            if (i < final_args.size()) {
                                value = final_args[i];
                            } else if (it_param->default_value.has_value()) {
                                value = this->process(it_param->default_value.value());
                            } else {
                                context->pop_scope();
                                this->errors.push_back({RTError("QC-C004: Missing argument to parent constructor '" + func_name + "'", get_pos(value)), "Error"});
                                return VoidValue();
                            }
                            context->define(it_param->name.value, it_param->type.value, value);
                        }

                        try {
                            for (auto& stmt : ctor->body->statements) {
                                this->process(stmt);
                            }
                        } catch (ReturnException&) {
                            
                        }
                        context->pop_scope();

                        return VoidValue();
                    }
                }
                auto fields = make_instance_fields(func_name);
                auto inst = std::make_shared<InstanceValue>(func_name, std::move(fields));
                ClassMethodInfo* ctor = nullptr;
                for (auto& m : info.classMethods) {
                    if (m.is_constructor) {
                        ctor = &m;
                        break;
                    }
                }
                ClassMethodInfo* init_m = this->find_method_on_class(func_name, "init");
                if (!ctor) {
                    if (init_m) {
                        this->call_instance_method(inst, init_m, {}, Position{});
                    }
                    return inst;
                }

                final_args.clear();
                final_lvalues.clear();

                for (auto& arg : node->arg_nodes) {
                    if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&arg)) {
                        NumberVariant sv = this->process((*spread)->expr);
                        if (auto arr = std::get_if<std::shared_ptr<ArrayValue>>(&sv)) {
                            for (auto& e : (*arr)->elements) {
                                final_args.push_back(e);
                                final_lvalues.push_back("");
                            }
                        } else if (auto lst = std::get_if<std::shared_ptr<ListValue>>(&sv)) {
                            for (auto& e : (*lst)->elements) {
                                final_args.push_back(e);
                                final_lvalues.push_back("");
                            }
                        } else {
                            this->errors.push_back({RTError("QC-I005: Spread target must be array or list", get_pos(sv)), "Error"});
                        }
                    } else {
                        if (auto varacc_ptr = std::get_if<std::unique_ptr<VarAccessNode>>(&arg)) {
                            std::string var_name = (*varacc_ptr)->var_name_tok.value;
                            NumberVariant v      = this->process(arg);
                            final_args.push_back(v);
                            final_lvalues.push_back(var_name);
                        } else {
                            final_args.push_back(this->process(arg));
                            final_lvalues.push_back("");
                        }
                    }
                }

                context->push_scope();
                context->define("this", func_name, inst, true);

                if (final_args.size() > ctor->params.size()) {
                    context->pop_scope();
                    this->errors.push_back({RTError("QC-C002: Too many arguments to constructor '" + func_name + "'", Position()), "Error"});
                    return inst;
                }

                for (size_t i = 0; i < ctor->params.size(); ++i) {
                    auto it_param = ctor->params.begin();
                    std::advance(it_param, i);

                    NumberVariant value;
                    if (i < final_args.size()) {
                        value = final_args[i];
                    } else if (it_param->default_value.has_value()) {
                        value = this->process(it_param->default_value.value());
                    } else {
                        context->pop_scope();
                        this->errors.push_back({RTError("QC-C004: Missing argument to constructor '" + func_name + "'", get_pos(value)), "Error"});
                        return inst;
                    }
                    context->define(it_param->name.value, it_param->type.value, value);
                }// need do this for methods

                try {
                    for (auto& stmt : ctor->body->statements) {
                        this->process(stmt);
                    }
                } catch (ReturnException&) {
                    
                }
                context->pop_scope();

                return inst;
            }
            std::string lookup_name = func_name;
            if (lookup_name.find("::") != std::string::npos) {
                auto func = context->functions.find(lookup_name);
                if (func != context->functions.end()) {
                    target_val = FunctionValue(func->second);
                } else {
                    throw RTError("Undefined function: '" + func_name + "'", Position());
                }
            } else {
                try { 
                    target_val = context->get(func_name, varacc->var_name_tok.pos); 
                } catch (RTError&) {
                    auto func = context->get_function(func_name);
                    if (!func) throw RTError("Undefined function: '" + func_name + "'", Position());
                    target_val = FunctionValue(func);
                }
            }
        } else {
            target_val = this->process(node->node_to_call);
        }
        
        if (!std::holds_alternative<FunctionValue>(target_val))
            this->errors.push_back({RTError("Can only call functions", Position()), "Error"});

        FunctionValue fval = std::get<FunctionValue>(target_val);
        if (!fval.func) this->errors.push_back({RTError("Invalid function value", Position()), "Error"});

        auto func = fval.func;
        final_args.clear();
        final_lvalues.clear();

        for (auto& arg : node->arg_nodes) {
            if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&arg)) {
                NumberVariant sv = this->process((*spread)->expr);
                if (auto arr = std::get_if<std::shared_ptr<ArrayValue>>(&sv)) {
                    for (auto& e : (*arr)->elements) {
                        final_args.push_back(e);
                        final_lvalues.push_back("");
                    }
                } else if (auto lst = std::get_if<std::shared_ptr<ListValue>>(&sv)) {
                    for (auto& e : (*lst)->elements) {
                        final_args.push_back(e);
                        final_lvalues.push_back("");
                    }
                } else {
                    this->errors.push_back({RTError("QC-I005: Spread target must be array or list", get_pos(sv)), "Error"});
                }
            } else {
                if (auto varacc_ptr = std::get_if<std::unique_ptr<VarAccessNode>>(&arg)) {
                    std::string var_name = (*varacc_ptr)->var_name_tok.value;
                    NumberVariant v      = this->process(arg);
                    final_args.push_back(v);
                    final_lvalues.push_back(var_name);
                } else {
                    final_args.push_back(this->process(arg));
                    final_lvalues.push_back("");
                }
            }
        }
        std::vector<std::string> saved_namespace_stack = context->namespaceStack;
        bool changed_namespace = false;
        std::string current_ns = "";
        for (size_t i = 0; i < context->namespaceStack.size(); i++) {
            if (i > 0) current_ns += "::";
            current_ns += context->namespaceStack[i];
        }

        if (!func->namespace_path.empty() && current_ns != func->namespace_path) {
            changed_namespace = true;
            context->namespaceStack.clear();
            std::string path = func->namespace_path;
            size_t pos = 0;
            while ((pos = path.find("::")) != std::string::npos) {
                context->namespaceStack.push_back(path.substr(0, pos));
                path.erase(0, pos + 2);
            }
            if (!path.empty()) {
                context->namespaceStack.push_back(path);
            }
        }

        context->push_scope();
        try {
            if (final_args.size() > func->params.size()) {
                context->pop_scope();
                if (changed_namespace) {
                    context->namespaceStack = saved_namespace_stack;
                }
                this->errors.push_back({RTError("QC-C001: Too many arguments", Position()), "Error"});
            }
            for (size_t i = 0; i < func->params.size(); i++) {
                auto it_param = func->params.begin();
                std::advance(it_param, i);

                NumberVariant value;
                if (i < final_args.size()) {
                    value = final_args[i];
                } else if (it_param->default_value.has_value()) {
                    value = this->process(it_param->default_value.value());
                } else {
                    this->errors.push_back({RTError("QC-C003: Missing argument", Position()), "Error"});
                    continue;
                }

                std::string expected_type = it_param->type.value;
                std::string actual_type   = context->get_type_name(value);
                bool is_ref_param = false;
                std::string base_expected = expected_type;
                if (!expected_type.empty() && expected_type.back() == '&') {
                    is_ref_param = true;
                    base_expected.pop_back();
                }

                std::string lvalue_name;
                if (i < final_lvalues.size()) {
                    lvalue_name = final_lvalues[i];
                }

                if (is_ref_param && !lvalue_name.empty()) {
                    auto norm = [](std::string t) {
                        size_t pos = t.rfind("::");
                        if (pos != std::string::npos) t = t.substr(pos + 2);
                        if (t == "long int" || t == "short int") t = "int";
                        if (t == "long double") t = "double";
                        return t;
                    };

                    if (norm(base_expected) != norm(actual_type)) {
                        this->errors.push_back({RTError(
                            "QC-R003: Cannot bind ref parameter '" + it_param->name.value +
                            "' of type " + base_expected + "& to '" + lvalue_name +
                            "' of type " + actual_type,
                            it_param->name.pos),
                            "Error"});
                        continue;
                    }

                    context->define_reference(it_param->name.value, lvalue_name, base_expected + "&", it_param->name.pos);
                    continue;
                }
                if (is_ref_param && lvalue_name.empty()) {
                    expected_type = base_expected;
                }
                if (expected_type == "auto") {
                    context->define(it_param->name.value, actual_type, value);
                } else {
                    
                    bool types_compatible = false;
                    
                    if (expected_type == actual_type) {
                        types_compatible = true;
                    } else {
                        std::string lookup_type = expected_type;
                        auto ut_it = context->user_types.find(lookup_type);
                        if (ut_it == context->user_types.end()) {
                            size_t last_colon = lookup_type.rfind("::");
                            if (last_colon == std::string::npos && !context->namespaceStack.empty()) {
                                std::string qualified;
                                for (auto& ns : context->namespaceStack) {
                                    if (!qualified.empty()) qualified += "::";
                                    qualified += ns;
                                }
                                lookup_type = qualified + "::" + expected_type;
                                ut_it = context->user_types.find(lookup_type);
                            }
                        }
                        if (ut_it == context->user_types.end()) {
                            for (auto& [type_name, info] : context->user_types) {
                                if (type_name == expected_type ||
                                    type_name.rfind("::" + expected_type) != std::string::npos) {
                                    ut_it = context->user_types.find(type_name);
                                    break;
                                }
                            }
                        }

                        if (ut_it != context->user_types.end() &&
                            ut_it->second.kind == UserTypeKind::Union) {

                            auto& members = ut_it->second.members;
                            std::string valType = context->get_type_name(value);
                            bool ok = false;

                            for (auto& m : members) {
                                if (value_matches_union_member(m.type, valType, value)) {
                                    ok = true;
                                    break;
                                }
                            }

                            if (!ok) {
                                this->errors.push_back({RTError(
                                    "QC-T004: Type mismatch: value of type " + valType +
                                    " is not assignable to union type '" + expected_type + "'",
                                    Position()
                                ), "Error"});
                            }

                            actual_type = expected_type;
                            types_compatible = true;
                        }
                        if (actual_type == "long int") actual_type = "int";
                        if (actual_type == "short int") actual_type = "int";
                        if (actual_type == "long double") actual_type = "double";
                        if (expected_type == "long int") expected_type = "int";
                        if (expected_type == "short int") expected_type = "int";
                        if (expected_type == "long double") expected_type = "double";
                    }
                    if (!types_compatible) {
                        if (expected_type == "list<auto>") {
                            if (actual_type.find("list<") != std::string::npos || actual_type.find("[]") != std::string::npos) {
                                types_compatible = true;
                                if (auto av = std::get_if<std::shared_ptr<ArrayValue>>(&value)) {
                                    value = std::make_shared<ListValue>(strip((*av)->element_type), (*av)->elements);
                                }
                            }
                        }
                        else if (expected_type.find("list<") == 0) {
                            std::string inner = strip(expected_type);
                            if (strip(actual_type) == inner && actual_type != inner) {
                                types_compatible = true;
                                if (auto av = std::get_if<std::shared_ptr<ArrayValue>>(&value)) {
                                    value = std::make_shared<ListValue>(strip((*av)->element_type), (*av)->elements);
                                }
                            }
                        }
                        else if (actual_type.find("list<") == 0) {
                            std::string inner = strip(actual_type);
                            
                            if (strip(expected_type) == inner && expected_type != inner) {
                                types_compatible = true;
                                if (auto lv = std::get_if<std::shared_ptr<ListValue>>(&value)) {
                                    value = std::make_shared<ArrayValue>(strip((*lv)->element_type), (*lv)->elements);
                                }
                            }
                        }
                        else {
                            types_compatible = (expected_type == actual_type);

                        }
                    }
                    
                    if (!types_compatible) {
                        context->pop_scope();
                        if (changed_namespace) {
                            context->namespaceStack = saved_namespace_stack;
                        }
                        this->errors.push_back({RTError(
                            "Argument type mismatch: expected " + expected_type + 
                            ", got " + actual_type, 
                            Position()
                        ), "Error"});
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
                if (changed_namespace) {
                    context->namespaceStack = saved_namespace_stack;
                }
                return std::make_shared<MultiValue>(std::move(defaults));
            } else if (func->return_types.size() == 1) {
                context->pop_scope();
                if (changed_namespace) {
                    context->namespaceStack = saved_namespace_stack;
                }
                return def_value_for_type(func->return_types[0].value);
            } else {
                context->pop_scope();
                if (changed_namespace) {
                    context->namespaceStack = saved_namespace_stack;
                }
                return VoidValue();
            }
            
        } catch (ReturnException& re) {
            context->pop_scope();
            if (changed_namespace) {
                context->namespaceStack = saved_namespace_stack;
            }
            
            if (!func->return_types.empty()) {
                std::string expected_type = func->return_types[0].value;
                
                auto ut_it = context->user_types.find(expected_type);
                if (ut_it != context->user_types.end() && 
                    ut_it->second.kind == UserTypeKind::Struct) {
                    if (auto arr_ptr = std::get_if<std::shared_ptr<ArrayValue>>(&re.value)) {
                        NumberVariant converted = convert_array_to_struct(
                            *arr_ptr, 
                            expected_type, 
                            context
                        );
                        return std::move(converted);
                    }
                }
            }
            
            return std::move(re.value);
        } catch (MultiReturnException& mre) {
            context->pop_scope();
            if (changed_namespace) {
                context->namespaceStack = saved_namespace_stack;
            }
            return std::make_shared<MultiValue>(std::move(mre.values));
            
        } catch (...) {
            context->pop_scope();
            if (changed_namespace) {
                context->namespaceStack = saved_namespace_stack;
            }
            throw;
        }
        if (changed_namespace) {
            context->namespaceStack = saved_namespace_stack;
        }
        return VoidValue();
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
        if (node.tok.type == TokenType::INT) {
            try {
                long long val = std::stoll(node.tok.value);
                
                if (val > INT_MAX || val < INT_MIN) {
                    return Number<long long>(val);
                }
                
                if (val >= SHRT_MIN && val <= SHRT_MAX) {
                    return Number<int>(static_cast<int>(val));
                }
                
                return Number<int>(static_cast<int>(val));
            } catch (...) {
                this->errors.push_back({RTError("Integer out of range", node.tok.pos), "Severe"});
            }
        }
        
        if (node.tok.type == TokenType::FLOAT) {
            return Number<float>(std::stof(node.tok.value));
        }
        
        if (node.tok.type == TokenType::DOUBLE) {
            return Number<double>(std::stod(node.tok.value));
        }
        
        return Number<int>(0);
    }

    NumberVariant Interpreter::operator()(std::unique_ptr<VarAccessNode>& node) {
        if (!node) {
            throw RTError("Interpreter got a null VarAccessNode", Position());
        }
        if (!context) {
            this->errors.push_back({RTError("Context not initialized", node->var_name_tok.pos), "Severe"});
        }
        
        std::string name = node->var_name_tok.value;
        
        
        if (name.find("::") != std::string::npos) {
            for (auto it = context->frames.rbegin(); it != context->frames.rend(); ++it) {
                auto sym_it = it->find(name);
                if (sym_it != it->end()) {
                    return sym_it->second.value;
                }
            }
            throw RTError("QC-C001: Undefined variable: '" + name + "'", node->var_name_tok.pos);
        }
        
        auto result = context->get(name, node->var_name_tok.pos);
        return result;
    }


    std::string Interpreter::run_statements(std::unique_ptr<StatementsNode>& node) {
        std::string output = "";
        
        for (auto& stmt : node->statements) {
            ExecResult r = exec_stmt_in_loop_or_switch(stmt);
            auto result = std::move(r.value);

            output += this->value_to_string(result) + "\n";
        }
        
        return output;
    }
    std::string MultiValue::print() const {
        std::string result = "(";
        for (size_t i = 0; i < values.size(); i++) {
            result += value_to_string(values[i]);
            if (i < values.size() - 1) result += ", ";
        }
        return result + ")";
    }

    std::string ArrayValue::print() const {
        std::string result = "[";
        for (size_t i = 0; i < elements.size(); i++) {
            result += value_to_string(elements[i]);
            if (i < elements.size() - 1) result += ", ";
        }
        return result + "]";
    }

    std::string ListValue::print() const {
        std::string result = "[";
        for (size_t i = 0; i < elements.size(); i++) {
            result += value_to_string(elements[i]);
            if (i < elements.size() - 1) result += ", ";
        }
        return result + "]";
    }
    NumberVariant Interpreter::call_instance_method(
        const std::shared_ptr<InstanceValue>& inst,
        ClassMethodInfo* method,
        std::vector<NumberVariant> args,
        const Position& pos
    ) {
        const std::string& className = inst->class_name;
        const std::string& mname = method->name_tok.value;
        if (method->access == "private" && !in_class_context(className)) {
            this->errors.push_back({RTError(
                "Method '" + mname + "' of class '" + className +
                "' is private and cannot be called here",
                pos),
                "Error"});
            return VoidValue();
        }
        if (method->access == "protected" && !in_class_or_derived_context(className)) {
            this->errors.push_back({RTError(
                "Method '" + mname + "' of class '" + className +
                "' is protected and cannot be called here",
                pos),
                "Error"});
            return VoidValue();
        }

        context->push_scope();
        context->define("this", className, inst, true);

        if (args.size() > method->params.size()) {
            context->pop_scope();
            this->errors.push_back({RTError(
                "QC-C002: Too many arguments to method '" + mname + "'",
                pos),
                "Error"});
            return VoidValue();
        }

        for (size_t i = 0; i < method->params.size(); ++i) {
            auto it_param = method->params.begin();
            std::advance(it_param, i);

            NumberVariant value;
            if (i < args.size()) {
                value = args[i];
            } else if (it_param->default_value.has_value()) {
                value = this->process(it_param->default_value.value());
            } else {
                context->pop_scope();
                this->errors.push_back({RTError(
                    "QC-C004: Missing argument " + it_param->name.value +
                    " for method '" + mname + "'",
                    pos),
                    "Error"});
                return VoidValue{};
            }

            std::string ptype = it_param->type.value;
            if (ptype.rfind("list<", 0) == 0 && ptype.back() == '>') {
                if (auto arr = std::get_if<std::shared_ptr<ArrayValue>>(&value)) {
                    std::string elem_type = ptype.substr(5, ptype.size() - 6);
                    auto list = std::make_shared<ListValue>(elem_type, (*arr)->elements);
                    value = list;
                }
            }
            else if (ptype.size() >= 2 && ptype.substr(ptype.size() - 2) == "[]") {
                if (auto lst = std::get_if<std::shared_ptr<ListValue>>(&value)) {
                    std::string elem_type = ptype.substr(0, ptype.size() - 2);
                    auto arr = std::make_shared<ArrayValue>(elem_type, (*lst)->elements);
                    value = arr;
                }
            }
            bool is_ref_param = false;
            if (!ptype.empty() && ptype.back() == '&') {
                is_ref_param = true;
                ptype.pop_back();
            }
            context->define(it_param->name.value, ptype, value);
        }

        try {
            NumberVariant last = Number<int>(0);
            for (auto& stmt : method->body->statements) {
                last = this->process(stmt);
            }

            if (!method->return_types.empty()) {
                if (method->return_types.size() == 1) {
                    context->pop_scope();
                    return def_value_for_type(method->return_types[0].value);
                } else {
                    std::vector<NumberVariant> defaults;
                    for (auto& rt : method->return_types)
                        defaults.push_back(def_value_for_type(rt.value));
                    context->pop_scope();
                    return std::make_shared<MultiValue>(std::move(defaults));
                }
            }

            context->pop_scope();
            return last;
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
    NumberVariant Interpreter::operator()(std::unique_ptr<BinOpNode>& node) {
        if (!node) return VoidValue();
        if (node->op_tok.type == TokenType::RSHIFT) {
            bool is_qin_start = std::holds_alternative<QInNode>(node->left_node);
            
            bool is_qin_chain = false;
            if (auto left_binop = std::get_if<std::unique_ptr<BinOpNode>>(&node->left_node)) {
                if ((*left_binop)->op_tok.type == TokenType::RSHIFT) {
                    is_qin_chain = true; 
                }
            }
            
            if (is_qin_start || is_qin_chain) {
                this->process(node->left_node);
                
                        
                if (auto var = std::get_if<std::unique_ptr<VarAccessNode>>(&node->right_node)) {
                    std::string var_name = (*var)->var_name_tok.value;
                    
                    
                    std::string input;
                    std::cin >> input;
                    
                    
                    auto v = this->context->get(var_name, node->op_tok.pos);
                    auto type = this->context->get_type_name(v);
                    NumberVariant val;
                    
                    if (type == "int" || type == "short int" || type == "long int") {
                        try {
                            if (type == "short int") {
                                val = Number<short>(static_cast<short>(std::stoi(input)));
                            }
                            else if (type == "long int") {
                                val = Number<long long>(std::stoll(input));
                            }
                            else {
                                val = Number<int>(std::stoi(input));
                            }
                        } catch (...) {
                            this->errors.push_back({RTError("Cannot parse integer", node->op_tok.pos), "Error"});
                        }
                    }
                    else if (type == "float") {
                        try {
                            val = Number<float>(std::stof(input));
                        } catch (...) {
                            this->errors.push_back({RTError("Cannot parse float", node->op_tok.pos), "Error"});
                        }
                    }
                    else if (type == "double" || type == "long double") {
                        try {
                            if (type == "long double") {
                                val = Number<long double>(std::stold(input));
                            }
                            else {
                                val = Number<double>(std::stod(input));
                            }
                        } catch (...) {
                            this->errors.push_back({RTError("Cannot parse double", node->op_tok.pos), "Error"});
                        }
                    }
                    else if (type == "string") {
                        val = StringValue(input);
                    }
                    else if (type == "char") {
                        val = CharValue(std::string(1, input[0]));
                    }
                    else if (type == "bool") {
                        val = BoolValue(input);
                    }
                    else if (type == "qbool") {
                        val = QBoolValue(input);
                    }
                    else {
                        this->errors.push_back({RTError("Cannot read input into type " + type, node->op_tok.pos), "Error"});
                    }
                    
                    context->set(var_name, val, node->op_tok.pos);
                    return VoidValue();
                }
                return VoidValue();
            }
            return VoidValue();
        }
        if (node->op_tok.type == TokenType::AND) {
            NumberVariant left = std::move(this->process(node->left_node));
            NumberVariant right = std::move(this->process(node->right_node));
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
                std::vector<NumberVariant> args = {right};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator&&", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }
            
            if (!is_truthy(left)) return BoolValue("false");
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                std::vector<NumberVariant> args = {left};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator&&", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }
            
            return BoolValue(is_truthy(right) ? "true" : "false");
        }

        if (node->op_tok.type == TokenType::OR) {
            NumberVariant left = std::move(this->process(node->left_node));
            NumberVariant right = std::move(this->process(node->right_node));
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
                std::vector<NumberVariant> args = {right};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator||", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }
            
            if (is_truthy(left)) return BoolValue("true");
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                std::vector<NumberVariant> args = {left};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator||", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }
            
            return BoolValue(is_truthy(right) ? "true" : "false");
        }

        if (node->op_tok.type == TokenType::XOR) {
            NumberVariant left = std::move(this->process(node->left_node));
            NumberVariant right = std::move(this->process(node->right_node));
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
                std::vector<NumberVariant> args = {right};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator^", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                std::vector<NumberVariant> args = {left};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator^", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }
            
            bool l = is_truthy(left);
            bool r = is_truthy(right);
            return BoolValue((l != r) ? "true" : "false");
        }

        if (node->op_tok.type == TokenType::QAND) { 
            NumberVariant left = this->process(node->left_node);
            NumberVariant right = this->process(node->right_node);
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
                std::vector<NumberVariant> args = {right};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator&&&", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                std::vector<NumberVariant> args = {left};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator&&&", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }

            auto l_qb = std::get_if<QBoolValue>(&left);
            auto r_qb = std::get_if<QBoolValue>(&right);

            if (l_qb && r_qb) {
                bool t = l_qb->tval && r_qb->tval;
                bool f = l_qb->fval || r_qb->fval;
                
                if (t && f) return QBoolValue("both");
                if (t) return QBoolValue("qtrue");
                if (f) return QBoolValue("qfalse");
                return QBoolValue("none");
            }
        }

        if (node->op_tok.type == TokenType::QOR) {
            NumberVariant left = this->process(node->left_node);
            NumberVariant right = this->process(node->right_node);

            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
                std::vector<NumberVariant> args = {right};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator|||", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }

            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                std::vector<NumberVariant> args = {left};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator|||", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }

            auto l_qb = std::get_if<QBoolValue>(&left);
            auto r_qb = std::get_if<QBoolValue>(&right);

            if (l_qb && r_qb) {
                bool t = l_qb->tval || r_qb->tval;
                bool f = l_qb->fval || r_qb->fval;
                
                if (t && f) return QBoolValue("both");
                if (t) return QBoolValue("qtrue");
                if (f) return QBoolValue("qfalse");
                return QBoolValue("none");
            }
        }

        if (node->op_tok.type == TokenType::QXOR) {
            NumberVariant left = this->process(node->left_node);
            NumberVariant right = this->process(node->right_node);

            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
                std::vector<NumberVariant> args = {right};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator^^", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }

            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                std::vector<NumberVariant> args = {left};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator^^", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }

            auto l_qb = std::get_if<QBoolValue>(&left);
            auto r_qb = std::get_if<QBoolValue>(&right);

            if (l_qb && r_qb) {
                bool t = !(l_qb->tval && r_qb->tval);
                bool f = l_qb->tval || r_qb->tval;
                
                if (t && f) return QBoolValue("both");
                if (!t) return QBoolValue("qfalse");
                return QBoolValue("none");
            }
        }

        if (node->op_tok.type == TokenType::QEQEQ) {
            NumberVariant l_qb = this->process(node->left_node);
            NumberVariant r_qb = this->process(node->right_node);

            try {
                if (values_equal(l_qb, r_qb, node->op_tok.pos)) {
                    return QBoolValue(std::string("both"));
                } else {
                    return QBoolValue(std::string("none"));
                }
            } catch (const RTError& e) {
                errors.push_back({e, "Error"});
                return QBoolValue(std::string("none"));
            }
        }

        if (node->op_tok.type == TokenType::QNEQ) {
            NumberVariant l_qb = this->process(node->left_node);
            NumberVariant r_qb = this->process(node->right_node);

            try {
                if (!values_equal(l_qb, r_qb, node->op_tok.pos)) {
                    return QBoolValue(std::string("both"));
                } else {
                    return QBoolValue(std::string("none"));
                }
            } catch (const RTError& e) {
                errors.push_back({e, "Error"});
                return QBoolValue(std::string("both"));
            }
        }

        if (node->op_tok.type == TokenType::COLLAPSE_AND) { 
            NumberVariant left = this->process(node->left_node);
            NumberVariant right = this->process(node->right_node);

            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
                std::vector<NumberVariant> args = {right};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator&|&", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }

            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                std::vector<NumberVariant> args = {left};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator&|&", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }

            auto l_qb = std::get_if<QBoolValue>(&left);
            auto r_qb = std::get_if<QBoolValue>(&right);

            if (l_qb && r_qb) {
                bool t = l_qb->tval && r_qb->tval;
                
                if (t) return BoolValue("true");
                return BoolValue("false");
            }
        }

        if (node->op_tok.type == TokenType::COLLAPSE_OR) {
            NumberVariant left = this->process(node->left_node);
            NumberVariant right = this->process(node->right_node);

            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
                std::vector<NumberVariant> args = {right};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator|&|", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }

            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                std::vector<NumberVariant> args = {left};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, "operator|&|", args);
                if (method) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }

            auto l_qb = std::get_if<QBoolValue>(&left);
            auto r_qb = std::get_if<QBoolValue>(&right);

            if (l_qb && r_qb) {
                bool t = l_qb->tval || r_qb->tval;
                
                if (t) return BoolValue("true");
                return BoolValue("false");
            }
        }
        NumberVariant left  = std::move(this->process(node->left_node));
        NumberVariant right = std::move(this->process(node->right_node));
        if (node->is_f) {
            if (auto ls = std::get_if<StringValue>(&left)) {
                if (auto inst = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                    std::string r_str = this->value_to_string(*inst); // use repr here
                    return StringValue(ls->value + r_str).set_pos(node->op_tok.pos);
                }
            } else if (auto rs = std::get_if<StringValue>(&right)) {
                if (auto inst = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
                    std::string l_str = this->value_to_string(*inst);
                    return StringValue(l_str + rs->value).set_pos(node->op_tok.pos);
                }
            }
        }
        if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
            std::string mname = op_method_name(node->op_tok.type);
            if (!mname.empty()) {
                std::vector<NumberVariant> args = {right};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, mname, args);
                if (method != nullptr) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }
            errors.push_back({RTError(
                "QC-C005: No matching '" + mname + "' operator found for class '" +
                (*inst_ptr)->class_name + "'",
                get_pos(left)
            ), "Error"});
            return VoidValue();
        }

        if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
            std::string mname = op_method_name(node->op_tok.type);
            if (!mname.empty()) {
                std::vector<NumberVariant> args = {left};
                ClassMethodInfo* method = find_method_with_args((*inst_ptr)->class_name, mname, args);
                if (method != nullptr) {
                    return call_instance_method(*inst_ptr, method, args, node->op_tok.pos);
                }
            }
            errors.push_back({RTError(
                "QC-C005: No matching '" + mname + "' operator found for class '" +
                (*inst_ptr)->class_name + "'",
                get_pos(left)
            ), "Error"});
            return VoidValue();
        }
        return std::visit([this, &node, right, left](const auto& L, const auto& R) -> NumberVariant {
            using T1 = std::decay_t<decltype(L)>;
            using T2 = std::decay_t<decltype(R)>;

            if (node->is_f) {
                std::string l_str = value_to_string(L);
                std::string r_str = value_to_string(R);
                return std::move(StringValue(l_str + r_str).set_pos(node->op_tok.pos));
            }
            
            if (node->op_tok.type == TokenType::EQ_TO) {
                try {
                    return BoolValue(values_equal(left, right, node->op_tok.pos) ? "true" : "false");
                } catch (RTError& e) {
                    return BoolValue("false");
                } 
            }
            if (node->op_tok.type == TokenType::NOT_EQ) {
                try {
                    return BoolValue(!values_equal(left, right, node->op_tok.pos) ? "true" : "false");
                } catch (RTError& e) {
                    return BoolValue("false");
                }
            }
            if constexpr (std::is_same_v<T1, StringValue> && std::is_same_v<T2, StringValue>) {
                if (node->op_tok.type == TokenType::PLUS) {
                    return std::move(StringValue(L.value + R.value).set_pos(node->op_tok.pos));
                }
                this->errors.push_back({RTError("QC-T005: Only '+' and logical expresions are supported for strings", node->op_tok.pos), "Error"});
            } else if constexpr (std::is_same_v<T1, StringValue> ^ std::is_same_v<T2, StringValue>) {
                this->errors.push_back({RTError("QC-T006: Cannot perform operations on string and number", node->op_tok.pos), "Error"});
            } else if constexpr (std::is_same_v<T1, CharValue> || std::is_same_v<T2, CharValue>) {
                this->errors.push_back({RTError("QC-T006: Cannot perform arithmetic on a Char", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::monostate> || std::is_same_v<T2, std::monostate>) {
                this->errors.push_back({RTError("QC-T006: Operation on uninitialized value", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, BoolValue> || std::is_same_v<T2, BoolValue>) { 
                this->errors.push_back({RTError("QC-T006: Cannot perform arithmetic operations on a Boolean", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, QBoolValue> || std::is_same_v<T2, QBoolValue>) { 
                this->errors.push_back({RTError("QC-T006: Cannot perform arithmetic operations on a Quantum Boolean", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, FunctionValue> || std::is_same_v<T2, FunctionValue>) { 
                this->errors.push_back({RTError("QC-T006: Cannot perform arithmetic operations on a Function", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, VoidValue> || std::is_same_v<T2, VoidValue>) { 
                this->errors.push_back({RTError("QC-T006: Cannot perform arithmetic operations on nothing", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<ArrayValue>> || std::is_same_v<T2, std::shared_ptr<ArrayValue>>) { 
                this->errors.push_back({RTError("QC-T006: Cannot perform arithmetic operations on arrays", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<ListValue>> || std::is_same_v<T2, std::shared_ptr<ListValue>>) { 
                this->errors.push_back({RTError("QC-T006: Cannot perform arithmetic operations on lists", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<MapValue>> || std::is_same_v<T2, std::shared_ptr<MapValue>>) { 
                this->errors.push_back({RTError("QC-T006: Cannot perform arithmetic operations on a map/dict", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<StructValue>> || std::is_same_v<T2, std::shared_ptr<StructValue>>) { 
                this->errors.push_back({RTError("QC-T006: Cannot perform arithmetic operations on a Struct", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<MultiValue>> || 
                            std::is_same_v<T2, std::shared_ptr<MultiValue>>) {
                this->errors.push_back({RTError("QC-T006: Cannot perform arithmetic on multi-return values", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<InstanceValue>> || 
                            std::is_same_v<T2, std::shared_ptr<InstanceValue>>) {
                this->errors.push_back({RTError("QC-T006: Cannot perform arithmetic on classes", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, PointerValue> || 
                            std::is_same_v<T2, PointerValue>) {
                this->errors.push_back({RTError("QC-T006: Cannot perform arithmetic on pointers", node->op_tok.pos), "Error"});
            }
            else{ 
                return std::move(handle_binop(L, R, node->op_tok.type, this->error));
            }
            return VoidValue();
        }, left, right);
        return VoidValue();
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
            this->errors.push_back({RTError("Expected multi-return value", node->var_names[0].pos), "Error"});
        }

        if (mv->values.size() != node->var_names.size()) {
            this->errors.push_back({RTError(
                "Expected " + std::to_string(node->var_names.size()) +
                " values, got " + std::to_string(mv->values.size()),
                node->var_names[0].pos
            ), "Error"});
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
    NumberVariant Interpreter::operator()(CharNode& node) {
        CharValue cv(node.tok.value);
        return std::move(cv.set_pos(node.tok.pos));
    }
    NumberVariant Interpreter::operator()(BoolNode& node) {
        return std::move(BoolValue(node.tok.value).set_pos(node.tok.pos));
    }
    NumberVariant Interpreter::operator()(QBoolNode& node) {
        auto qb = QBoolValue(node.tok.value);
        return std::move(qb.set_pos(node.tok.pos));
    }
    NumberVariant apply_numeric_binop(
        const NumberVariant& left,
        const NumberVariant& right,
        TokenType op,
        const Position& pos
    ) {
        return std::visit(
            [&](auto const& L, auto const& R) -> NumberVariant {
                using TL = std::decay_t<decltype(L)>;
                using TR = std::decay_t<decltype(R)>;
                if constexpr (
                    std::is_same_v<TL, Number<short>>      ||
                    std::is_same_v<TL, Number<int>>        ||
                    std::is_same_v<TL, Number<long long>>  ||
                    std::is_same_v<TL, Number<float>>      ||
                    std::is_same_v<TL, Number<double>>     ||
                    std::is_same_v<TL, Number<long double>>
                ) {
                    if constexpr (
                        std::is_same_v<TR, Number<short>>      ||
                        std::is_same_v<TR, Number<int>>        ||
                        std::is_same_v<TR, Number<long long>>  ||
                        std::is_same_v<TR, Number<float>>      ||
                        std::is_same_v<TR, Number<double>>     ||
                        std::is_same_v<TR, Number<long double>>
                    ) {
                        InterpEer dummyErr;
                        return handle_binop(L, R, op, dummyErr);
                    } else {
                        throw RTError("QC-T002: Right side of compound assignment must be numeric", pos);
                    }
                } else {
                    throw RTError("QC-T002: Left side of compound assignment must be numeric", pos);
                }
            },
            left,
            right
        );
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<AssignExprNode>& node) {
        if (!node) return Number<int>(0);

        TokenType op = node->op_tok.type;
        AnyNode& target = node->target;
        auto get_symbol_for_var = [this](const std::string& name, const Position& pos) -> Symbol& {
            auto loc_opt = context->find_any_symbol(name);
            if (!loc_opt) {
                throw RTError("QC-C001: Undefined variable: '" + name + "'", pos);
            }
            auto [fi, key] = *loc_opt;
            auto [t_fi, t_key] = context->follow_ref_chain(fi, key, pos);

            if (t_fi >= context->frames.size()) {
                throw RTError("Dangling reference: invalid frame index", pos);
            }
            auto& frame = context->frames[t_fi];
            auto sym_it = frame.find(t_key);
            if (sym_it == frame.end()) {
                throw RTError("Dangling reference: symbol '" + t_key + "' not found", pos);
            }
            return sym_it->second;
        };
        if (auto var = std::get_if<std::unique_ptr<VarAccessNode>>(&target)) {
            std::string name = (*var)->var_name_tok.value;
            Position pos = (*var)->var_name_tok.pos;
            NumberVariant current = context->get(name, pos);
            NumberVariant rhs;
            if (op == TokenType::EQ) {
                rhs = this->process(node->value);
            } else {
                NumberVariant rightVal = this->process(node->value);

                TokenType binop_type;
                if (op == TokenType::PLUS_EQ)  binop_type = TokenType::PLUS;
                else if (op == TokenType::MINUS_EQ) binop_type = TokenType::MINUS;
                else if (op == TokenType::MUL_EQ)   binop_type = TokenType::MUL;
                else if (op == TokenType::DIV_EQ)   binop_type = TokenType::DIV;
                else if (op == TokenType::MOD_EQ)   binop_type = TokenType::MOD;
                else throw RTError("Unsupported assignment operator", pos);
                rhs = apply_numeric_binop(current, rightVal, binop_type, pos);
            }
            context->set(name, std::move(rhs), pos);
            return context->get(name, pos);
        }
        if (auto un = std::get_if<std::unique_ptr<UnaryOpNode>>(&target)) {
            if ((*un)->op_tok.type == TokenType::MUL) {
                NumberVariant inner = this->process((*un)->node);
                auto pv = std::get_if<PointerValue>(&inner);
                if (!pv) {
                    throw RTError("Left-hand side '*...' is not a pointer", (*un)->op_tok.pos);
                }

                if (pv->is_null) {
                    throw RTError("Dereference of null pointer in assignment", pv->pos);
                }
                
                if (pv->is_heap) {
                    if (!context->heap_valid(pv->heap_id)) {
                        throw RTError("Assignment to freed memory", pv->pos);
                    }
                    
                    NumberVariant rhs;
                    if (op == TokenType::EQ) {
                        rhs = this->process(node->value);
                    } else {
                        NumberVariant current = context->heap_get(pv->heap_id);
                        NumberVariant rightVal = this->process(node->value);

                        TokenType binop_type;
                        if (op == TokenType::PLUS_EQ)      binop_type = TokenType::PLUS;
                        else if (op == TokenType::MINUS_EQ) binop_type = TokenType::MINUS;
                        else if (op == TokenType::MUL_EQ)   binop_type = TokenType::MUL;
                        else if (op == TokenType::DIV_EQ)   binop_type = TokenType::DIV;
                        else if (op == TokenType::MOD_EQ)   binop_type = TokenType::MOD;
                        else {
                            throw RTError("Unsupported assignment operator for heap pointer", (*un)->op_tok.pos);
                        }

                        rhs = apply_numeric_binop(current, rightVal, binop_type, get_pos(rightVal));
                    }
                    
                    context->heap_get(pv->heap_id) = std::move(rhs);
                    return context->heap_get(pv->heap_id);
                }
                
                if (pv->frame_index >= context->frames.size()) {
                    throw RTError("Dangling pointer (invalid frame)", pv->pos);
                }

                auto& frame = context->frames[pv->frame_index];
                auto it = frame.find(pv->symbol_key);
                if (it == frame.end()) {
                    throw RTError("Dangling pointer (symbol not found)", pv->pos);
                }

                Symbol& sym = it->second;
                if (sym.is_const) {
                    throw RTError(
                        "QC-T001: Cannot assign through const pointer target '" +
                        pv->symbol_key + "'",
                        pv->pos
                    );
                }
                
                NumberVariant current = sym.value;
                NumberVariant rhs;
                if (op == TokenType::EQ) {
                    rhs = this->process(node->value);
                } else {
                    NumberVariant rightVal = this->process(node->value);

                    TokenType binop_type;
                    if (op == TokenType::PLUS_EQ)      binop_type = TokenType::PLUS;
                    else if (op == TokenType::MINUS_EQ) binop_type = TokenType::MINUS;
                    else if (op == TokenType::MUL_EQ)   binop_type = TokenType::MUL;
                    else if (op == TokenType::DIV_EQ)   binop_type = TokenType::DIV;
                    else if (op == TokenType::MOD_EQ)   binop_type = TokenType::MOD;
                    else {
                        throw RTError("Unsupported assignment operator for *pointer", (*un)->op_tok.pos);
                    }

                    rhs = apply_numeric_binop(current, rightVal, binop_type, get_pos(rightVal));
                }
                
                std::string expected = sym.declared_type;
                std::string actual   = context->get_type_name(rhs);
                if (expected.find("*") != std::string::npos && actual == "void*") {
                    sym.value = std::move(rhs);
                    return sym.value;
                }

                auto normalize_type = [](const std::string& t) {
                    std::string type = t;
                    size_t pos = type.rfind("::");
                    type = (pos != std::string::npos) ? type.substr(pos + 2) : type;
                    if (type == "long int")    type = "int";
                    if (type == "short int")   type = "int";
                    if (type == "long double") type = "double";
                    return type;
                };

                if (normalize_type(expected) != normalize_type(actual) && expected != actual) {
                    throw RTError(
                        "QC-T003: Type mismatch: cannot assign " + actual +
                        " to " + expected,
                        pv->pos
                    );
                }

                sym.value = std::move(rhs);
                return sym.value;
            }
        }
        throw RTError("Invalid assignment target", get_pos(this->process(node->value)));
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<UnaryOpNode>& node) {
        if (!node) return Number<int>(0);
        if (node->op_tok.type == TokenType::QNOT) {
            
            NumberVariant val = std::move(this->process(node->node));
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&val)) {
                std::string mname = "operator!!";
                if (!mname.empty()) {
                    ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                    if (method) {
                        NumberVariant result = call_instance_method(
                            *inst_ptr,
                            method,
                            std::vector<NumberVariant>{},
                            node->op_tok.pos
                        );
                        return result;
                    }
                }
            }
            return std::visit([&](auto&& n) -> NumberVariant {
                using T = std::decay_t<decltype(n)>;
                if constexpr (std::is_same_v<T, std::shared_ptr<MultiValue>>) {
                    this->errors.push_back({RTError("Cannot use !! operator on multi-return values", node->op_tok.pos), "Error"});
                } else {
                    if constexpr (std::is_same_v<T, QBoolValue>) {
                        if (n.valname == "both") {
                            return QBoolValue("none");
                        }
                        if (n.valname == "none") {
                            return QBoolValue("both");
                        }
                        if (n.valname == "qtrue") {
                            return QBoolValue("qfalse");
                        }
                        if (n.valname == "qfalse") {
                            return QBoolValue("qtrue");
                        }
                    }
                    return std::move(QBoolValue(is_truthy(n) ? "qfalse" : "qtrue"));
                }
                return VoidValue();
            }, val);
        }
        if (node->op_tok.type == TokenType::NOT) {
            
            NumberVariant val = std::move(this->process(node->node));
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&val)) {
                std::string mname = "operator!";
                if (!mname.empty()) {
                    ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                    if (method) {
                        NumberVariant result = call_instance_method(
                            *inst_ptr,
                            method,
                            std::vector<NumberVariant>{},
                            node->op_tok.pos
                        );
                        return result;
                    }
                }
            }
            return std::visit([&](auto&& n) -> NumberVariant {
                using T = std::decay_t<decltype(n)>;
                if constexpr (std::is_same_v<T, std::shared_ptr<MultiValue>>) {
                    this->errors.push_back({RTError("Cannot use ! operator on multi-return values", node->op_tok.pos), "Error"});
                } else {
                    return std::move(BoolValue(is_truthy(n) ? "false" : "true"));
                }
                return VoidValue();
            }, val);
        }
        
        if (node->op_tok.type == TokenType::INCREMENT ||
            node->op_tok.type == TokenType::DECREMENT) {
            
            auto* var = std::get_if<std::unique_ptr<VarAccessNode>>(&node->node);
            if (!var) {
                this->errors.push_back({RTError("Increment/decrement must target a variable",
                            node->op_tok.pos), "Error"});
                return VoidValue();
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
                    !std::is_same_v<T, QBoolValue> &&
                    !std::is_same_v<T, FunctionValue> &&
                    !std::is_same_v<T, VoidValue> &&
                    !std::is_same_v<T, PointerValue> &&
                    !std::is_same_v<T, std::shared_ptr<MultiValue>> &&
                    !std::is_same_v<T, std::shared_ptr<ArrayValue>> &&
                    !std::is_same_v<T, std::shared_ptr<ListValue>>  &&
                    !std::is_same_v<T, std::shared_ptr<MapValue>> &&
                    !std::is_same_v<T, std::shared_ptr<StructValue>> &&
                    !std::is_same_v<T, std::shared_ptr<InstanceValue>>
                ) {
                    if (node->op_tok.type == TokenType::INCREMENT)
                        return std::move(n.added_to(Number<int>(1)));
                    else
                        return std::move(n.subbed_by(Number<int>(1)));
                }
                this->errors.push_back({RTError("Invalid operand for ++/--", pos), "Error"});
                return VoidValue();
            }, old_val));

            context->set(name, std::move(new_val), pos);
            return std::move(node->is_postfix ? old_val : new_val);
        }
        if (node->op_tok.type == TokenType::AMPERSAND) {
            auto* var_ptr = std::get_if<std::unique_ptr<VarAccessNode>>(&node->node);
            if (!var_ptr) {
                throw RTError(
                    "Address-of '&' must target a variable (for now)",
                    node->op_tok.pos);
                return VoidValue();
            }

            auto& var = *var_ptr;
            std::string name = var->var_name_tok.value;
            Position pos = var->var_name_tok.pos;
            auto loc_opt = context->find_any_symbol(name);
            if (!loc_opt) {
                throw RTError(
                    "Cannot take address of undefined variable '" + name + "'",
                    pos);
            }
            auto [fi, key] = *loc_opt;
            auto [t_fi, t_key] = context->follow_ref_chain(fi, key, pos);

            if (t_fi >= context->frames.size()) {
                throw RTError("Dangling symbol when taking address of '" + name + "'", pos);
            }

            auto& frame = context->frames[t_fi];
            auto it = frame.find(t_key);
            if (it == frame.end()) {
                throw RTError("Dangling symbol when taking address of '" + name + "'", pos);
            }
            std::string base_type = it->second.declared_type;
            auto ptr = PointerValue(base_type, t_fi, t_key);

            return ptr.set_pos(pos);
        }
        if (node->op_tok.type == TokenType::MUL) {
            NumberVariant value = this->process(node->node);

            if (auto pv = std::get_if<PointerValue>(&value)) {
                if (pv->is_null) {
                    throw RTError("Dereference of null pointer", pv->pos);
                }
                if (pv->is_heap) {
                    if (!context->heap_valid(pv->heap_id)) {
                        throw RTError("Dereference of freed memory", pv->pos);
                    }
                    return context->heap_get(pv->heap_id);
                }
                if (pv->frame_index >= context->frames.size()) {
                    throw RTError("Dangling pointer (invalid frame)", pv->pos);
                }

                auto& frame = context->frames[pv->frame_index];
                auto it = frame.find(pv->symbol_key);
                if (it == frame.end()) {
                    throw RTError("Dangling pointer (symbol not found)", pv->pos);
                }

                return it->second.value;
            }

            this->errors.push_back({RTError(
                "Unary '*' requires pointer value",
                node->op_tok.pos),
                "Error"});
            return VoidValue();
        }
        NumberVariant number = std::move(this->process(node->node));

        return std::move(std::visit([&node, this](const auto& n) -> NumberVariant {
            using T = std::decay_t<decltype(n)>;

            if constexpr (
                !std::is_same_v<T, StringValue> &&
                !std::is_same_v<T, CharValue> &&
                !std::is_same_v<T, BoolValue> &&
                !std::is_same_v<T, QBoolValue> &&
                !std::is_same_v<T, FunctionValue> &&
                !std::is_same_v<T, VoidValue> &&
                !std::is_same_v<T, PointerValue> &&
                !std::is_same_v<T, std::monostate> &&
                !std::is_same_v<T, std::shared_ptr<MultiValue>> &&
                !std::is_same_v<T, std::shared_ptr<ArrayValue>> &&
                !std::is_same_v<T, std::shared_ptr<ListValue>> &&
                !std::is_same_v<T, std::shared_ptr<MapValue>> &&
                !std::is_same_v<T, std::shared_ptr<StructValue>> &&
                !std::is_same_v<T, std::shared_ptr<InstanceValue>>

            ) {
                if (node->op_tok.type == TokenType::MINUS) {
                    return std::move(n.multed_by(Number<int>(-1)));
                }
                return std::move(n);
            } else {
                this->errors.push_back({RTError("Unary operator '" + get_token_name(node->op_tok.type) + "'not supported for this type",
                            node->op_tok.pos), "Error"});
            }
            return VoidValue();
        }, number));
    }


    NumberVariant Interpreter::operator()(StringNode& node) {
        return std::move(StringValue(node.tok.value).set_pos(node.tok.pos));
    }
    NumberVariant Interpreter::operator()(std::monostate) {
        return VoidValue();
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<MapLiteralNode>& node) {
        if (!node) return Number<int>(0);

        if (node->pairs.empty()) {
            auto mv = std::make_shared<MapValue>("string", "any");
            return mv;
        }

        NumberVariant firstKey = this->process(node->pairs[0].first);
        NumberVariant firstVal = this->process(node->pairs[0].second);

        std::string keyType = context->get_type_name(firstKey);
        std::string valType = context->get_type_name(firstVal);

        auto map_val = std::make_shared<MapValue>(keyType, valType);
        map_val->set(this->value_to_string(firstKey), std::move(firstVal));

        for (size_t i = 1; i < node->pairs.size(); ++i) {
            NumberVariant key = this->process(node->pairs[i].first);
            NumberVariant val = this->process(node->pairs[i].second);

            if (context->get_type_name(key) != keyType) {
                this->errors.push_back({RTError("Inconsistent key type in map literal", node->pos), "Error"});
            }
            if (context->get_type_name(val) != valType) {
                this->errors.push_back({RTError("Inconsistent value type in map literal", node->pos), "Error"});
            }

            map_val->set(this->value_to_string(key), std::move(val));
        }

        return map_val;
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
    NumberVariant Interpreter::operator()(std::unique_ptr<QIfNode>& node) {
        if (!node) return Number<int>(0);
        
        NumberVariant cond_val = this->process(node->condition);
        
        bool should_run_true = false;
        bool should_run_false = false;
        
        if (auto qb = std::get_if<QBoolValue>(&cond_val)) {
            should_run_true = qb->tval;
            should_run_false = qb->fval;
        } else {
            bool truthy = is_truthy(cond_val);
            should_run_true = truthy;
            should_run_false = !truthy;
        }
        
        NumberVariant last = Number<int>(0);
        
        if (should_run_true) {
            for (auto& stmt : node->then_branch->statements) {
                last = this->process(stmt);
            }
        }
        
        bool qelif_ran = false;
        for (auto& [qelif_cond, qelif_body] : node->qelif_branches) {
            NumberVariant qelif_val = this->process(qelif_cond);
            
            bool qelif_true = false;
            bool qelif_false = false;
            
            if (auto qb = std::get_if<QBoolValue>(&qelif_val)) {
                qelif_true = qb->tval;
                qelif_false = qb->fval;
            } else {
                bool truthy = is_truthy(qelif_val);
                qelif_true = truthy;
                qelif_false = !truthy;
            }
            
            if (should_run_false && qelif_true) {
                for (auto& stmt : qelif_body->statements) {
                    last = this->process(stmt);
                }
                qelif_ran = true;
                break; 
            }
        }
        
        if (should_run_false && !qelif_ran && node->qelse_branch) {
            for (auto& stmt : node->qelse_branch->statements) {
                last = this->process(stmt);
            }
        }
        
        return last;
    }
    
    NumberVariant Interpreter::operator()(std::unique_ptr<ArrayDeclNode>& node) {
        if (!node) return Number<int>(0);

        NumberVariant init_value = this->process(node->value); 

        if (!std::holds_alternative<std::shared_ptr<ArrayValue>>(init_value))
            this->errors.push_back({RTError("Array must be initialized with array literal", node->var_name_tok.pos), "Error"});

        auto array_val = std::get<std::shared_ptr<ArrayValue>>(init_value);

        for (size_t i = 0; i < node->sizes.size(); ++i) {
            if (node->sizes[i].has_value()) {
                if (i >= array_val->sizes().size())
                    this->errors.push_back({RTError("Declared array has more dimensions than initialized", node->var_name_tok.pos), "Error"});
                if (array_val->sizes()[i] != node->sizes[i].value())
                    this->errors.push_back({RTError(
                        "Array size mismatch on dimension " + std::to_string(i) +
                        ": declared " + std::to_string(node->sizes[i].value()) +
                        " but got " + std::to_string(array_val->sizes()[i]),
                        node->var_name_tok.pos
                    ), "Error"});
            }
        }

        std::string array_type = node->type_tok.value;
        for (size_t i = 0; i < array_val->sizes().size(); ++i)
            array_type += "[]";

        context->define(node->var_name_tok.value, array_type, init_value, node->is_const);
        return VoidValue();
    }

    NumberVariant Interpreter::operator()(std::unique_ptr<ListDeclNode>& node) {
        if (!node) return Number<int>(0);

        NumberVariant init_value = this->process(node->value);

        if (std::holds_alternative<std::shared_ptr<ArrayValue>>(init_value)) {
            auto array_val = std::get<std::shared_ptr<ArrayValue>>(init_value);

            auto list_val = std::make_shared<ListValue>(
                node->type_tok.value,
                std::move(array_val->elements)
            );

            std::string list_type = "list<" + strip(node->type_tok.value) + ">";
            context->define(node->var_name_tok.value, list_type, list_val, node->is_const);
            return VoidValue();
        }

        if (std::holds_alternative<std::shared_ptr<ListValue>>(init_value)) {
            auto list_val = std::get<std::shared_ptr<ListValue>>(init_value);
            std::string list_type = "list<" + strip(node->type_tok.value) + ">";
            list_val->element_type = strip(node->type_tok.value);
            context->define(node->var_name_tok.value, list_type, list_val, node->is_const);
            return VoidValue();
        }

        this->errors.push_back({RTError("List must be initialized with array literal or another list", node->var_name_tok.pos), "Error"});
        return VoidValue();
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<SpreadNode>& node) {
        if (!node) return Number<int>(0);
        this->errors.push_back({RTError(
            "SpreadNode evaluated outside of a valid context",
            Position()
        ), "Error"});
        return VoidValue();
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<ArrayLiteralNode>& node) {
        if (!node) return Number<int>(0);

        std::vector<NumberVariant> elements;
        std::string element_type;

        for (auto& elem : node->elements) {
            if (auto spread_ptr = std::get_if<std::unique_ptr<SpreadNode>>(&elem)) {
                NumberVariant spread_val = this->process((*spread_ptr)->expr);
                
                if (auto arr = std::get_if<std::shared_ptr<ArrayValue>>(&spread_val)) {
                    for (auto& arr_elem : (*arr)->elements) {
                        elements.push_back(arr_elem);
                    }
                } else if (auto list = std::get_if<std::shared_ptr<ListValue>>(&spread_val)) {
                    for (auto& list_elem : (*list)->elements) {
                        elements.push_back(list_elem);
                    }
                } else {
                    this->errors.push_back({RTError("Cannot spread non-array type", Position()), "Error"});
                }
            } else {
                elements.push_back(this->process(elem));
            }
        }

        if (element_type.empty()) element_type = "int";

        return std::make_shared<ArrayValue>(element_type, std::move(elements));
    }


    NumberVariant Interpreter::operator()(std::unique_ptr<ArrayAccessNode>& node) {
        if (!node) return Number<int>(0);

        NumberVariant base_value = this->process(node->base);
        if (auto map_ptr = std::get_if<std::shared_ptr<MapValue>>(&base_value)) {
            auto map = *map_ptr;
            
            if (node->indices.size() != 1) {
                this->errors.push_back({RTError("Map access requires exactly one key", Position()), "Error"});
            }
            
            NumberVariant key = this->process(node->indices[0]);
            std::string key_str = this->value_to_string(key);
            
            return map->get(key_str);
        }
        if (auto ptr = std::get_if<PointerValue>(&base_value)) {
            if (!ptr->is_heap) {
                this->errors.push_back({RTError("QC-I003: Cannot index non-heap pointer", ptr->pos), "Error"});
                return Number<int>(0);
            }
            if (node->indices.size() != 1) {
                this->errors.push_back({RTError("QC-I003: Pointer indexing supports exactly one index", Position()), "Error"});
                return Number<int>(0);
            }
            NumberVariant index_val = this->process(node->indices[0]);
            int index = std::visit([&](auto&& arg) -> int {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, Number<int>>)    return arg.value;
                if constexpr (std::is_same_v<T, Number<float>>)  return (int)arg.value;
                if constexpr (std::is_same_v<T, Number<double>>) return (int)arg.value;
                this->errors.push_back({RTError("Index must be a number", Position()), "Error"});
                return 0;
            }, index_val);

            NumberVariant& block = context->heap_get(ptr->heap_id);
            auto arr = std::get_if<std::shared_ptr<ArrayValue>>(&block);
            if (!arr) {
                this->errors.push_back({RTError("QC-I003: Pointer does not reference an array block", ptr->pos), "Error"});
                return Number<int>(0);
            }

            if (index < 0 || (size_t)index >= (*arr)->elements.size()) {
                throw RTError("QC-I001: Array index out of bounds: " + std::to_string(index), Position());
            }

            return (*arr)->elements[index];
        }
        bool is_array = std::holds_alternative<std::shared_ptr<ArrayValue>>(base_value);
        bool is_list  = std::holds_alternative<std::shared_ptr<ListValue>>(base_value);
        if (!is_array && !is_list) {
            
            this->errors.push_back({RTError("QC-I003: Cannot index non-array/list type", Position()), "Error"});
        }
        std::shared_ptr<ArrayValue> current_array;
        std::shared_ptr<ListValue>  current_list;

        if (is_array) current_array = std::get<std::shared_ptr<ArrayValue>>(base_value);
        if (is_list)  current_list  = std::get<std::shared_ptr<ListValue>>(base_value);

        for (size_t dim = 0; dim < node->indices.size(); ++dim) {
            NumberVariant index_val = this->process(node->indices[dim]);
            int index = std::visit([&](auto&& arg) -> int {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, Number<int>>)    return arg.value;
                if constexpr (std::is_same_v<T, Number<float>>)  return (int)arg.value;
                if constexpr (std::is_same_v<T, Number<double>>) return (int)arg.value;
                this->errors.push_back({RTError("Index must be a number", Position()), "Error"});
                return 0;
            }, index_val);

            if (current_array) {
                if (index < 0 || (size_t)index >= current_array->size())
                    throw RTError("QC-I001: Array index out of bounds: " + std::to_string(index), Position());
                NumberVariant next = current_array->elements[index];

                if (dim == node->indices.size() - 1)
                    return next;

                if (auto next_arr = std::get_if<std::shared_ptr<ArrayValue>>(&next)) {
                    current_array = *next_arr;
                    current_list.reset();
                } else if (auto next_list = std::get_if<std::shared_ptr<ListValue>>(&next)) {
                    current_list = *next_list;
                    current_array.reset();
                } else {
                    this->errors.push_back({RTError("QC-I003: Cannot index inside non-array/list", Position()), "Error"});
                }
            } else if (current_list) {
                if (index < 0 || (size_t)index >= current_list->elements.size())
                    throw RTError("QC-I002: List index out of bounds: " + std::to_string(index), Position());
                NumberVariant next = current_list->elements[index];

                if (dim == node->indices.size() - 1)
                    return next;

                if (auto next_arr = std::get_if<std::shared_ptr<ArrayValue>>(&next)) {
                    current_array = *next_arr;
                    current_list.reset();
                } else if (auto next_list = std::get_if<std::shared_ptr<ListValue>>(&next)) {
                    current_list = *next_list;
                    current_array.reset();
                } else {
                    this->errors.push_back({RTError("QC-I003: Cannot index inside non-array/list", Position()), "Error"});
                }
            } else {
                this->errors.push_back({RTError("Internal error: lost array/list during indexing", Position()), "Error"});
            }
        }

        return Number<int>(0);  
    }
    bool Interpreter::in_class_or_derived_context(const std::string& baseName) {
        NumberVariant this_val;
        try {
            this_val = context->get("this", Position());
        } catch (RTError&) {
            return false;
        }

        auto inst = std::get_if<std::shared_ptr<InstanceValue>>(&this_val);
        if (!inst) return false;

        std::string curName = (*inst)->class_name;
        if (curName == baseName) return true;

        auto it = context->user_types.find(curName);
        while (it != context->user_types.end() &&
            it->second.kind == UserTypeKind::Class &&
            !it->second.baseClassName.empty()) {

            if (it->second.baseClassName == baseName) return true;
            it = context->user_types.find(it->second.baseClassName);
        }
        return false;
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<MethodCallNode>& node) {
        if (!node) return Number<int>(0);
        
        NumberVariant obj = this->process(node->base);
        std::vector<NumberVariant> final_args;

        for (auto& arg : node->args) {

            if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&arg)) {
                NumberVariant spread_val = this->process((*spread)->expr);

                if (auto arr = std::get_if<std::shared_ptr<ArrayValue>>(&spread_val)) {
                    for (auto& elem : (*arr)->elements)
                        final_args.push_back(elem);
                }
                else if (auto list = std::get_if<std::shared_ptr<ListValue>>(&spread_val)) {
                    for (auto& elem : (*list)->elements)
                        final_args.push_back(elem);
                }
                else {
                    this->errors.push_back({RTError("QC-I005: Spread target must be array or list", Position()), "Error"});
                }
            }
            else {
                final_args.push_back(this->process(arg));
            }
        }
        if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&obj)) {
            auto inst = *inst_ptr;
            const std::string& className = inst->class_name;
            const std::string& mname = node->method_name.value;
            if (mname == "has") {
                if (node->args.size() != 1) {
                    this->errors.push_back({RTError(
                        "QC-BM01: class.has() expects 1 argument (field name)", node->method_name.pos),
                        "Error"});
                    return BoolValue("false");
                }

                NumberVariant arg = this->process(node->args[0]);
                if (!std::holds_alternative<StringValue>(arg)) {
                    this->errors.push_back({RTError(
                        "QC-BM02: class.has() argument must be a string", node->method_name.pos),
                        "Error"});
                    return BoolValue("false");
                }

                std::string field = std::get<StringValue>(arg).value;
                bool exists = inst->fields.count(field) > 0;
                return BoolValue(exists ? "true" : "false");
            }
            
            if (mname == "has_method") {
                if (node->args.size() != 1) {
                    this->errors.push_back({RTError(
                        "QC-BM01: class.has_method() expects 1 argument (method name)", node->method_name.pos),
                        "Error"});
                    return BoolValue("false");
                }

                NumberVariant arg = this->process(node->args[0]);
                if (!std::holds_alternative<StringValue>(arg)) {
                    this->errors.push_back({RTError(
                        "QC-BM02: class.has_method() argument must be a string", node->method_name.pos),
                        "Error"});
                    return BoolValue("false");
                }

                std::string method = std::get<StringValue>(arg).value;
                
                auto ut_it = context->user_types.find(inst->class_name);
                if (ut_it == context->user_types.end()) {
                    return BoolValue("false");
                }
                
                for (auto& m : ut_it->second.classMethods) {
                    if (m.name_tok.value == method) {
                        return BoolValue("true");
                    }
                }
                
                return BoolValue("false");
            }
            ClassMethodInfo* method = find_method_with_args(className, mname, final_args);
            if (!method) {
                this->errors.push_back({RTError(
                    "QC-M001: Class '" + className + "' has no method or no matching overload for'" + mname + "'",
                    node->method_name.pos),
                    "Error"});
                return VoidValue{};
            }
            return call_instance_method(inst, method, std::move(final_args), node->method_name.pos);
        }
        if (auto sv = std::get_if<std::shared_ptr<StructValue>>(&obj)) {
            if (node->method_name.value == "has") {
                if (node->args.size() != 1) {
                    this->errors.push_back({RTError(
                        "QC-BM01: struct.has() expects 1 argument (field name)", node->method_name.pos),
                        "Error"});
                    return BoolValue("false");
                }

                NumberVariant arg = this->process(node->args[0]);
                if (!std::holds_alternative<StringValue>(arg)) {
                    this->errors.push_back({RTError(
                        "QC-BM02: struct.has() argument must be a string", node->method_name.pos),
                        "Error"});
                    return BoolValue("false");
                }

                std::string field = std::get<StringValue>(arg).value;
                bool ok = struct_has_field(*sv, field);
                return BoolValue(ok ? "true" : "false");
            }
        }
        if (auto list_ptr = std::get_if<std::shared_ptr<ListValue>>(&obj)) {
            auto list = *list_ptr;
            
            if (node->method_name.value == "push") {
                if (node->args.size() != 1) {
                    this->errors.push_back({RTError("QC-BM01: push() requires exactly 1 argument", node->method_name.pos), "Error"});
                }
                NumberVariant val = final_args[0];
                std::string name = context->get_type_name(val);
                if (name.find(strip(list->element_type)) == std::string::npos && !loose) {
                    this->errors.push_back({RTError("QC-BM02: cannot push a " + name + " to a list of type " + list->element_type, node->method_name.pos), "Error"});
                } else if (name != strip(list->element_type) && name.find("list<") == std::string::npos && name.find("[]") == std::string::npos) {
                    this->errors.push_back({RTError("QC-BM02: (loose) cannot push a " + name + " to a list of type " + list->element_type, node->method_name.pos), "Error"});
                }
                list->push(std::move(val));
                return VoidValue();
            }
            
            if (node->method_name.value == "pop") {
                if (node->args.size() != 0) {
                    this->errors.push_back({RTError("QC-BM01: pop() takes no arguments", node->method_name.pos), "Error"});
                }
                return list->pop();
            }
            
            this->errors.push_back({RTError("QC-M001: Unknown method: " + node->method_name.value, node->method_name.pos), "Error"});
        }
        if (auto map_ptr = std::get_if<std::shared_ptr<MapValue>>(&obj)) {
            auto map = *map_ptr;
            
            if (node->method_name.value == "set") {
                if (node->args.size() != 2) {
                    this->errors.push_back({RTError("QC-BM01: set() requires 2 arguments (key, value)", node->method_name.pos), "Error"});
                }
                NumberVariant key = this->process(node->args[0]);
                NumberVariant val = this->process(node->args[1]);
                
                std::string key_str = this->value_to_string(key);
                map->set(key_str, std::move(val));
                return VoidValue();
            }
            
            if (node->method_name.value == "remove") {
                if (node->args.size() != 1) {
                    this->errors.push_back({RTError("QC-BM01: remove() requires 1 argument (key)", node->method_name.pos), "Error"});
                }
                NumberVariant key = this->process(node->args[0]);
                std::string key_str = this->value_to_string(key);
                
                map->remove(key_str);
                return VoidValue();
            }
            
            if (node->method_name.value == "has") {
                if (node->args.size() != 1) {
                    this->errors.push_back({RTError("QC-BM01: has() requires 1 argument (key)", node->method_name.pos), "Error"});
                }
                NumberVariant key = this->process(node->args[0]);
                std::string key_str = this->value_to_string(key);
                
                return BoolValue(map->has(key_str) ? "true" : "false");
            }
            
            if (node->method_name.value == "keys") {
                if (node->args.size() != 0) {
                    this->errors.push_back({RTError("QC-BM01: keys() takes no arguments", node->method_name.pos), "Error"});
                }
                
                auto keys = map->keys();
                std::vector<NumberVariant> key_variants;
                for (auto& key : keys) {
                    key_variants.push_back(StringValue(key));
                }
                
                return std::make_shared<ArrayValue>("string", std::move(key_variants));
            }
            
            this->errors.push_back({RTError("QC-BM04: Unknown map method: " + node->method_name.value, node->method_name.pos), "Error"});
        }
        this->errors.push_back({RTError("QC-BM05: Object does not support methods", node->method_name.pos), "Error"});
        return VoidValue();
    }
    NumberVariant make_value_from_type_atom(const std::string& atom) {
        if (atom.rfind("int:", 0) == 0) {
            return Number<int>(std::stoi(atom.substr(4)));
        }

        if (atom.rfind("float:", 0) == 0) {
            return Number<float>(std::stof(atom.substr(6)));
        }

        if (atom.rfind("double:", 0) == 0) {
            return Number<double>(std::stod(atom.substr(7)));
        }

        if (atom.rfind("char:", 0) == 0) {
            std::string s = atom.substr(5);
            char c = s.empty() ? '\0' : s[0];
            return CharValue(std::string(1, c));
        }

        if (atom.rfind("bool:", 0) == 0) {
            std::string s = atom.substr(5);
            bool b = (s == "true");
            return BoolValue(s);
        }

        if (atom.rfind("qbool:", 0) == 0) {
            std::string s = atom.substr(6);
            return QBoolValue(s);
        }

        if (atom.rfind("string:\"", 0) == 0) {
            std::string inner = atom.substr(8, atom.size() - 9);
            return StringValue(inner);
        }

        return VoidValue();
    }
    bool Interpreter::in_class_context(const std::string& class_name) {
        try {
            NumberVariant this_val = context->get("this", Position());
            if (auto inst = std::get_if<std::shared_ptr<InstanceValue>>(&this_val)) {
                return (*inst)->class_name == class_name;
            }
        } catch (RTError& z) {
            this->errors.push_back({z, "Error"});
        }
        return false;
    }
    bool Interpreter::field_exists_on_class(
        const std::string& className,
        const std::string& fieldName
    ) {
        auto it = context->user_types.find(className);
        if (it == context->user_types.end()) return false;

        UserTypeInfo* cur = &it->second;
        while (cur) {
            for (auto& f : cur->classFields) {
                if (f.name == fieldName) return true;
            }
            if (cur->baseClassName.empty()) break;
            auto bit = context->user_types.find(cur->baseClassName);
            if (bit == context->user_types.end() ||
                bit->second.kind != UserTypeKind::Class) break;
            cur = &bit->second;
        }
        return false;
    }
    NumberVariant Interpreter::operator()(std::shared_ptr<PropertyAccessNode>& node) {
        if (!node) return Number<int>(0);
        if (!node->base_name_tok.value.empty()) {
            if (auto varAcc = std::get_if<std::unique_ptr<VarAccessNode>>(&(*node->base))) {
                const std::string& baseName = (*varAcc)->var_name_tok.value;
                const std::string& memberName = node->property_name.value;

                auto ut_it = context->user_types.find(baseName);
                if (ut_it != context->user_types.end()) {
                    UserTypeInfo& ut = ut_it->second;
                    if (!ut.enumEntries.empty()) {
                        for (auto& e : ut.enumEntries) {
                            if (e.memberName == memberName) {
                                return make_value_from_type_atom(e.typeAtom);
                            }
                        }
                        this->errors.push_back({RTError(
                            "QC-F001: Enum '" + baseName + "' has no member '" + memberName + "'",
                            node->property_name.pos
                        ), "Error"});
                    }
                }
            }
        }
        NumberVariant obj = this->process(*(node->base));
        const std::string& name = node->property_name.value;
        
        while (true) {
            
            if (auto s = std::get_if<std::shared_ptr<StructValue>>(&obj)) {
                auto it = (*s)->fields.find(name);
                if (it == (*s)->fields.end()) {
                    this->errors.push_back({RTError("QC-F001: Unknown field '" + name + "' on struct '" + (*s)->type_name + "'",
                                node->property_name.pos), "Error"});
                }
                obj = it->second;
                break; 
            }

            if (auto arr = std::get_if<std::shared_ptr<ArrayValue>>(&obj)) {
                std::string struct_type = context->get_type_name(obj);
                auto it = context->user_types.find(struct_type);
                if (it != context->user_types.end() &&
                    it->second.kind == UserTypeKind::Struct) {

                    const auto& fields = it->second.fields;
                    size_t idx = SIZE_MAX;
                    for (size_t i = 0; i < fields.size(); ++i) {
                        if (fields[i].name == name) { idx = i; break; }
                    }
                    if (idx == SIZE_MAX) {
                        this->errors.push_back({RTError("QC-F001: Unknown field '" + name + "' on struct '" + struct_type + "'",
                                    node->property_name.pos), "Error"});
                    }
                    obj = (*arr)->elements[idx];
                    break;
                }

                if (name == "length") return Number<int>((*arr)->elements.size());
            }

            if (auto list = std::get_if<std::shared_ptr<ListValue>>(&obj)) {
                if (name == "length") return Number<int>((*list)->length());
            }

            if (auto map = std::get_if<std::shared_ptr<MapValue>>(&obj)) {
                if (name == "size") return Number<int>((*map)->size());
            }
            if (auto inst = std::get_if<std::shared_ptr<InstanceValue>>(&obj)) {
                const std::string& className = (*inst)->class_name;

                if (!field_exists_on_class(className, name)) {
                    this->errors.push_back({RTError(
                        "QC-F001: Unknown field '" + name + "' on class '" + className + "'",
                        node->property_name.pos),
                        "Error"});
                    return VoidValue{};
                }

                auto it = (*inst)->fields.find(name);
                if (it == (*inst)->fields.end()) {
                    this->errors.push_back({RTError(
                        "QC-X001: Internal error: field '" + name + "' missing on instance of '" + className + "'",
                        node->property_name.pos),
                        "Severe"});
                    return VoidValue{};
                }

                auto ut_it = context->user_types.find(className);
                if (ut_it != context->user_types.end() &&
                    ut_it->second.kind == UserTypeKind::Class) {

                    const auto& info = ut_it->second;
                    std::string access = "public";

                    for (auto& f : info.classFields) {
                        if (f.name == name) {
                            access = f.access;
                            break;
                        }
                    }

                    if (access == "private") {
                        if (!in_class_context(className)) {
                            this->errors.push_back({RTError(
                                "QC-A001: Field '" + name + "' of class '" + className +
                                "' is " + access + " and cannot be accessed here",
                                node->property_name.pos),
                                "Error"});
                            return VoidValue{};
                        }
                    }
                    if (access == "protected") {
                        if (!in_class_or_derived_context(className)) {
                            this->errors.push_back({RTError(
                                "QC-A001: Field '" + name + "' of class '" + className +
                                "' is " + access + " and cannot be accessed here",
                                node->property_name.pos),
                                "Error"});
                            return VoidValue{};
                        }
                    }
                }

                obj = it->second;
                break;
            }
            this->errors.push_back({RTError("QC-F002: Unknown property: " + name, node->property_name.pos), "Error"});
        }

        return obj;
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<ForeachNode>& node) {
        if (!node) return Number<int>(0);
        
        NumberVariant coll_val = this->process(node->collection);
        
        std::vector<NumberVariant>* elements = nullptr;
        
        if (auto arr = std::get_if<std::shared_ptr<ArrayValue>>(&coll_val)) {
            elements = &((*arr)->elements);
        } else if (auto list = std::get_if<std::shared_ptr<ListValue>>(&coll_val)) {
            elements = &((*list)->elements);
        } else {
            this->errors.push_back({RTError("foreach requires an array or list", node->elem_name.pos), "Error"});
        }
        
        NumberVariant last = Number<int>(0);
        for (auto& elem : *elements) {
            context->define(node->elem_name.value, node->elem_type.value, elem, false);
            ExecResult r = this->exec_stmt_in_loop_or_switch(node->body);
            last = std::move(r.value);

            if (r.did_break) {
                return std::move(last);      
            }
            if (r.did_continue) {
                goto foreach_update;   
            }
        foreach_update:
            continue;
        }
        
        return VoidValue();
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<ArrayAssignNode>& node) {
        if (!node) return Number<int>(0);
        
        auto& arr_access = std::get<std::unique_ptr<ArrayAccessNode>>(node->array_access);
        NumberVariant base = this->process(arr_access->base);
        NumberVariant val = this->process(node->value);
        
        if (auto map_ptr = std::get_if<std::shared_ptr<MapValue>>(&base)) {
            auto map = *map_ptr;
            
            if (arr_access->indices.size() != 1) {
                this->errors.push_back({RTError("Map access requires exactly one key", Position()), "Error"});
            }
            
            NumberVariant key = this->process(arr_access->indices[0]);
            std::string key_str = this->value_to_string(key);
            map->set(key_str, std::move(val));
            return val;
        }
        if (auto ptr = std::get_if<PointerValue>(&base)) {
            if (!ptr->is_heap) {
                this->errors.push_back({RTError("QC-B002: cannot assign through non-heap pointer", ptr->pos), "Error"});
                return VoidValue();
            }

            if (arr_access->indices.size() != 1) {
                this->errors.push_back({RTError("QC-B002: pointer indexing supports exactly one index", Position()), "Error"});
                return VoidValue();
            }

            NumberVariant idx_val = this->process(arr_access->indices[0]);
            int index = std::visit([&](auto&& arg) -> int {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, Number<int>>  ||
                            std::is_same_v<T, Number<long long>> ||
                            std::is_same_v<T, Number<short>>) {
                    return (int)arg.value;
                }
                this->errors.push_back({RTError("Array index must be an integer", Position()), "Error"});
                return 0;
            }, idx_val);

            NumberVariant& block = context->heap_get(ptr->heap_id);
            auto arr = std::get_if<std::shared_ptr<ArrayValue>>(&block);
            if (!arr) {
                this->errors.push_back({RTError("QC-B002: pointer does not reference an array block", ptr->pos), "Error"});
                return VoidValue();
            }

            if (index < 0 || (size_t)index >= (*arr)->elements.size()) {
                this->errors.push_back({RTError("QC-I001: Array index out of bounds", Position()), "Error"});
                return VoidValue();
            }

            (*arr)->elements[index] = std::move(val);
            return (*arr)->elements[index];
        }
        if (auto arr_ptr = std::get_if<std::shared_ptr<ArrayValue>>(&base)) {
            auto arr = *arr_ptr;
            
            int flat_index = 0;
            int multiplier = 1;
            
            for (int i = arr_access->indices.size() - 1; i >= 0; i--) {
                NumberVariant idx_val = this->process(arr_access->indices[i]);
                
                if (auto idx_num = std::get_if<Number<int>>(&idx_val)) {
                    int idx = idx_num->value;
                    flat_index += idx * multiplier;
                    
                    if (i > 0) {
                        multiplier *= 10;
                    }
                } else {
                    this->errors.push_back({RTError("Array index must be an integer", Position()), "Error"});
                }
            }
            
            if (flat_index < 0 || flat_index >= arr->elements.size()) {
                this->errors.push_back({RTError("QC-I001: Array index out of bounds", Position()), "Error"});
            }
            
            arr->elements[flat_index] = std::move(val);
            return val;
        }
        
        if (auto list_ptr = std::get_if<std::shared_ptr<ListValue>>(&base)) {
            auto list = *list_ptr;
            
            if (arr_access->indices.size() != 1) {
                this->errors.push_back({RTError("List access requires exactly one index", Position()), "Error"});
            }
            
            NumberVariant idx_val = this->process(arr_access->indices[0]);
            
            if (auto idx_num = std::get_if<Number<int>>(&idx_val)) {
                int idx = idx_num->value;
                
                if (idx < 0 || idx >= list->elements.size()) {
                    this->errors.push_back({RTError("QC-I002: List index out of bounds", Position()), "Error"});
                }
                
                list->elements[idx] = std::move(val);
                return val;
            } else {
                this->errors.push_back({RTError("List index must be an integer", Position()), "Error"});
            }
        }
        
        this->errors.push_back({RTError("Cannot assign to this type", Position()), "Error"});
        return VoidValue();
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<RandomCallNode>& node) {
        if (!node) return Number<int>(0);
        
        if (node->args.size() == 0) {
            float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            return Number<float>(r);
        }
        else if (node->args.size() == 1) {
            NumberVariant max_val = this->process(node->args[0]);
            
            if (auto max_num = std::get_if<Number<int>>(&max_val)) {
                int r = rand() % max_num->value;
                return Number<int>(r);
            }
            
            this->errors.push_back({RTError("random(max) requires integer argument", Position()), "Error"});
        }
        else if (node->args.size() == 2) {
            NumberVariant min_val = this->process(node->args[0]);
            NumberVariant max_val = this->process(node->args[1]);
            
            if (auto min_num = std::get_if<Number<int>>(&min_val)) {
                if (auto max_num = std::get_if<Number<int>>(&max_val)) {
                    int range = max_num->value - min_num->value;
                    int r = min_num->value + (rand() % range);
                    return Number<int>(r);
                }
            }
            
            this->errors.push_back({RTError("random(min, max) requires integer arguments", Position()), "Error"});
        }
        
        this->errors.push_back({RTError("random() takes 0, 1, or 2 arguments", Position()), "Error"});
        return VoidValue();
    }

    NumberVariant Interpreter::operator()(std::unique_ptr<SeedCallNode>& node) {
        if (!node) return Number<int>(0);
        
        NumberVariant seed_val = this->process(node->value);
        
        if (auto seed_num = std::get_if<Number<int>>(&seed_val)) {
            srand(seed_num->value);
            return VoidValue();
        }
        
        this->errors.push_back({RTError("seed() requires integer argument", Position()), "Error"});
        return VoidValue();
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<FieldAssignNode>& node) {
        if (!node) return VoidValue();

        NumberVariant base_val = this->process(node->base);
        const std::string& fieldName = node->field_name.value;
        if (auto inst = std::get_if<std::shared_ptr<InstanceValue>>(&base_val)) {
            const std::string& className = (*inst)->class_name;
            const std::string  fieldName = node->field_name.value;

            auto ut_it = context->user_types.find(className);
            if (ut_it == context->user_types.end() ||
                ut_it->second.kind != UserTypeKind::Class) {
                this->errors.push_back({RTError("Unknown class '" + className + "'",
                                                node->field_name.pos),
                                        "Severe"});
                return VoidValue{};
            }

            UserTypeInfo* cur = &ut_it->second;
            bool found = false;
            std::string access = "public";
            std::string targetFieldType = "";

            while (cur) {
                for (auto& f : cur->classFields) {
                    if (f.name == fieldName) {
                        found = true;
                        access = f.access;
                        targetFieldType = f.type;
                        break;
                    }
                }
                if (found) break;

                if (cur->baseClassName.empty()) break;
                auto bit = context->user_types.find(cur->baseClassName);
                if (bit == context->user_types.end() ||
                    bit->second.kind != UserTypeKind::Class)
                    break;
                cur = &bit->second;     
            }

            if (!found) {
                this->errors.push_back({RTError(
                    "Unknown field '" + fieldName + "' in class '" + className + "'",
                    node->field_name.pos),
                    "Error"});
                return VoidValue{};
            }

            if (access == "private") {
                if (!in_class_context(className)) {
                    this->errors.push_back({RTError(
                        "Field '" + fieldName + "' of class '" + className +
                        "' is " + access + " and cannot be assigned here",
                        node->field_name.pos),
                        "Error"});
                    return VoidValue{};
                }
            }
            if (access == "protected") {
                if (!in_class_or_derived_context(className)) {
                    this->errors.push_back({RTError(
                        "Field '" + fieldName + "' of class '" + className +
                        "' is " + access + " and cannot be assigned here",
                        node->field_name.pos),
                        "Error"});
                    return VoidValue{};
                }
            }
            NumberVariant rightVal;
            rightVal = this->process(node->value);

            (*inst)->fields[fieldName] = rightVal;
            return rightVal;
        }
        if (auto s = std::get_if<std::shared_ptr<StructValue>>(&base_val)) {
            const std::string& structName = (*s)->type_name;
            std::string targetFieldType = "";

            auto ut_it = context->user_types.find(structName);
            if (ut_it != context->user_types.end()) {
                for (auto& f : ut_it->second.fields) {
                    if (f.name == fieldName) {
                        targetFieldType = f.type;
                        break;
                    }
                }
            }
            NumberVariant rightVal;
            if (auto arrLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&node->value)) {
                if (targetFieldType.find("list<") == 0) {
                    std::vector<NumberVariant> evaluatedElements;
                    for (auto& elementNode : (*arrLit)->elements) {
                        evaluatedElements.push_back(this->process(elementNode));
                    }
                    std::string innerType = getElementType(targetFieldType); 
                    rightVal = std::make_shared<ListValue>(innerType, evaluatedElements);
                } else {
                    rightVal = this->process(node->value);
                }
            }

            (*s)->fields[fieldName] = rightVal;
            return rightVal;
        }
        this->errors.push_back({
            RTError("Expected struct or class instance on left side of '.'",
                    node->field_name.pos),
            "Error"
        });
        return VoidValue();
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
        if (type.ends_with("[]")) {
            std::string baseType = type.substr(0, type.length() - 2);
            llvm::Type* elemTy = llvmTypeFor(baseType);
            return llvm::PointerType::get(context, 0);
        }
        if (type.starts_with("list<") && type.ends_with(">")) {
            size_t start = 5;
            size_t end = qcType.length() - 1;
            std::string elemType = type.substr(start, end - start);
            return llvm::PointerType::get(context, 0);
        }
        if (type.starts_with("map<") && type.ends_with(">")) {
            return llvm::PointerType::get(context, 0);
        }
        if (type == "int")        return builder->getInt32Ty();
        if (type == "short int")  return builder->getInt16Ty();
        if (type == "long int")   return builder->getInt64Ty();
        if (type == "float")        return builder->getFloatTy();
        if (type == "double")  return builder->getDoubleTy();
        if (type == "long double")   return builder->getDoubleTy();
        if (type == "char")        return builder->getInt8Ty();
        if (type == "bool")        return builder->getInt1Ty();
        if (type == "qbool")       return builder->getIntNTy(2);
        if (type == "string")      return llvm::PointerType::get(context, 0);
    
        if (classTypes.find(type) != classTypes.end()) {
            return classTypes[type];
        }
        if (structTypes.find(type) != structTypes.end()) {
            return structTypes[type];
        }
        if (enumTypes.find(type) != enumTypes.end()) {
            return enumTypes[type];
        }
        if (unionTypes.find(type) != unionTypes.end()) {
            return unionTypes[type];
        }
        return builder->getInt32Ty();
    }
    std::string LLVMCompiler::resolveType(const std::string& typeName) {
        auto it = typeAliases.find(typeName);
        if (it != typeAliases.end()) {
            return resolveType(it->second);
        }
        return typeName;
    }
    void LLVMCompiler::createUserTypes() {
        auto getFullName = [](const std::string& name, const UserTypeInfo& info) {
            if (info.namespace_path.empty()) {
                return name;
            }
            return info.namespace_path + "::" + name;
        };
        for (auto& [mapKey, info] : userTypes) {
            if (info.kind == UserTypeKind::Enum) {
                size_t lastColon = mapKey.rfind("::");
                std::string actualName = (lastColon == std::string::npos) 
                    ? mapKey 
                    : mapKey.substr(lastColon + 2);
                
                std::vector<llvm::Type*> fields = {
                    builder->getInt32Ty(),
                    llvm::PointerType::get(context, 0)
                };
                
                llvm::StructType* enumTy = llvm::StructType::create(context, fields, mapKey);
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
                llvm::StructType* structTy = llvm::StructType::create(context, mapKey);
                structTypes[mapKey] = structTy;
            }
        }
        for (auto& [mapKey, info] : userTypes) {
            if (info.kind == UserTypeKind::Class) {
                llvm::StructType* classTy = llvm::StructType::create(context, mapKey);
                classTypes[mapKey] = classTy;
            }
        }
        for (auto& [mapKey, info] : userTypes) {
            if (info.kind == UserTypeKind::Class) {
                if (!info.baseClassName.empty()) {
                    auto base_it = userTypes.find(info.baseClassName);
                    if (base_it != userTypes.end() && base_it->second.is_final_class) {
                        cg_error(Position(), 
                            "Cannot inherit from final class '" + info.baseClassName + "'");
                        continue;
                    }
                }
                std::vector<llvm::Type*> fieldTypes;
                
                std::function<void(const std::string&)> collectFields = [&](const std::string& className) {
                    auto it = userTypes.find(className);
                    if (it == userTypes.end()) {
                        throw std::runtime_error("Class not found: " + className);
                    }
                    auto& classInfo = it->second;
                    
                    if (!classInfo.baseClassName.empty()) {
                        std::string baseFullName = classInfo.baseClassName;
                        if (baseFullName.find("::") == std::string::npos) {
                            for (auto& [key, info] : userTypes) {
                                if (key.find(baseFullName) != std::string::npos && 
                                    info.kind == UserTypeKind::Class) {
                                    baseFullName = key;
                                    break;
                                }
                            }
                        }
                        
                        collectFields(baseFullName);
                    }
                    
                    for (auto& field : classInfo.classFields) {
                        fieldTypes.push_back(llvmTypeFor(field.type));
                    }
                };
                
                collectFields(mapKey);
                
                if (fieldTypes.empty()) {
                    fieldTypes.push_back(builder->getInt8Ty());
                }
                
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
                            if (baseMethod.name_tok.value == method.name_tok.value && 
                                baseMethod.is_final) {
                                cg_error(method.name_tok.pos,
                                    "Cannot override final method '" + 
                                    baseMethod.name_tok.value + 
                                    "' from base class '" + info.baseClassName + "'");
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
                
                for (auto& param : method.params) {
                    paramTypes.push_back(llvmTypeFor(param.type.value));
                }
                
                llvm::Type* retTy = builder->getVoidTy();
                if (!method.return_types.empty()) {
                    if (method.return_types.size() == 1) {
                        retTy = llvmTypeFor(method.return_types[0].value);
                    } else {
                        std::vector<llvm::Type*> retTypes;
                        for (auto& rt : method.return_types) {
                            retTypes.push_back(llvmTypeFor(rt.value));
                        }
                        retTy = llvm::StructType::get(context, retTypes);
                    }
                }
                
                llvm::FunctionType* fnTy = llvm::FunctionType::get(retTy, paramTypes, false);
                llvm::Function* fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, methodName, module.get());
                
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
                std::vector<llvm::Type*> fields = {
                    builder->getInt32Ty(),
                    llvm::PointerType::get(context, 0)
                };
                
                llvm::StructType* unionTy = llvm::StructType::create(context, fields, mapKey);
                unionTypes[mapKey] = unionTy;
            }
        }
        for (auto& [mapKey, info] : userTypes) {
            if (info.kind == UserTypeKind::Alias) {
                typeAliases[mapKey] = info.aliasTarget;
            }
        }
        
        generateStructReprFunctions();
    }
    llvm::FunctionType* LLVMCompiler::llvmFuncTypeFor(
        const std::vector<Token>& returnTypes,
        const std::list<Parameter>& params
    ) {
        std::vector<llvm::Type*> paramTypes;
        for (auto& p : params) {
            llvm::Type* ty = llvmTypeFor(p.type.value);
            paramTypes.push_back(ty);
        }
        
        if (returnTypes.empty()) {
            return llvm::FunctionType::get(builder->getVoidTy(), paramTypes, false);
        }
        
        if (returnTypes.size() == 1) {
            llvm::Type* retTy = llvmTypeFor(returnTypes[0].value);
            
            if (retTy->isArrayTy()) {
                retTy = llvm::PointerType::get(context, 0);
            }
            
            return llvm::FunctionType::get(retTy, paramTypes, false);
        }
        
        std::vector<llvm::Type*> retTypes;
        for (auto& rt : returnTypes) {
            llvm::Type* ty = llvmTypeFor(rt.value);
            if (ty->isArrayTy()) {
                ty = llvm::PointerType::get(context, 0);
            }
            
            retTypes.push_back(ty);
        }
        llvm::StructType* structTy = llvm::StructType::get(context, retTypes);
        return llvm::FunctionType::get(structTy, paramTypes, false);
    }
    void LLVMCompiler::cg_error(const Position& pos, const std::string& msg) {
        errors.emplace_back(msg, pos);
    }
    llvm::Value* LLVMCompiler::createJaggedArray(
        AnyNode& literalNode, 
        int elemTypeCode,
        int depth
    ) {
        auto arrLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&literalNode);
        if (!arrLit) return nullptr;
        if (depth == 0) {
            int rowSize = (*arrLit)->elements.size();
            
            llvm::Function* createRowFn = module->getFunction("qc_create_leaf_row");
            if (!createRowFn) {
                llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                llvm::FunctionType* fnTy = llvm::FunctionType::get(
                    voidPtrTy,
                    {builder->getInt32Ty(), builder->getInt32Ty()},
                    false
                );
                createRowFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                    "qc_create_leaf_row", module.get());
            }
            
            llvm::Value* row = builder->CreateCall(createRowFn, {
                builder->getInt32(rowSize),
                builder->getInt32(elemTypeCode)
            }, "leaf_row");
            
            llvm::Function* setLeafFn = module->getFunction("qc_set_leaf_element");
            if (!setLeafFn) {
                llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                llvm::FunctionType* fnTy = llvm::FunctionType::get(
                    builder->getVoidTy(),
                    {voidPtrTy, builder->getInt32Ty(), voidPtrTy, builder->getInt32Ty()},
                    false
                );
                setLeafFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                "qc_set_leaf_element", module.get());
            }
            
            for (size_t j = 0; j < (*arrLit)->elements.size(); j++) {
                llvm::Value* elemVal = emitExpr((*arrLit)->elements[j]);
                if (!elemVal) continue;
                
                llvm::AllocaInst* tempAlloc = createEntryAlloca("temp_elem", elemVal->getType());
                builder->CreateStore(elemVal, tempAlloc);
                
                llvm::Value* elemPtr = builder->CreateBitCast(tempAlloc, 
                                                            llvm::PointerType::get(context, 0));
                
                builder->CreateCall(setLeafFn, {
                    row,
                    builder->getInt32(j),
                    elemPtr,
                    builder->getInt32(elemTypeCode)
                });
            }
            
            return row;
        }
        llvm::Function* createFn = module->getFunction("qc_create_jagged_array");
        if (!createFn) {
            llvm::Type* jaggedPtrTy = llvm::PointerType::get(context, 0);
            llvm::FunctionType* fnTy = llvm::FunctionType::get(
                jaggedPtrTy,
                {builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt32Ty()},
                false
            );
            createFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, 
                                            "qc_create_jagged_array", module.get());
        }
        
        int count = (*arrLit)->elements.size();
        llvm::Value* jaggedArr = builder->CreateCall(createFn, {
            builder->getInt32(count),
            builder->getInt32(elemTypeCode),
            builder->getInt32(depth)
        }, "jagged_arr");
        
        llvm::Function* setFn = module->getFunction("qc_set_jagged_element");
        if (!setFn) {
            llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
            llvm::FunctionType* fnTy = llvm::FunctionType::get(
                builder->getVoidTy(),
                {voidPtrTy, builder->getInt32Ty(), voidPtrTy, builder->getInt32Ty()},
                false
            );
            setFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                        "qc_set_jagged_element", module.get());
        }
        
        for (size_t i = 0; i < (*arrLit)->elements.size(); i++) {
            if (auto subLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&(*arrLit)->elements[i])) {
                llvm::Value* subArr = createJaggedArray((*arrLit)->elements[i], elemTypeCode, depth - 1);
                int subSize = (*subLit)->elements.size();
                
                builder->CreateCall(setFn, {
                    jaggedArr,
                    builder->getInt32(i),
                    subArr,
                    builder->getInt32(subSize)
                });
            }
        }
        
        return jaggedArr;
    }
    LLVMCompiler::LLVMCompiler(std::unordered_map<std::string, UserTypeInfo>& types) : userTypes(types) {
        module  = std::make_unique<llvm::Module>("qc_module", context);
        builder = std::make_unique<llvm::IRBuilder<>>(context);
        jaggedArraysStack.push_back({});
        arrayTypeStringsStack.push_back({});
        listsStack.push_back({});
        arrayLengthsStack.push_back({});
        mapsStack.push_back({});
        addRuntimeToModule();
    }
    void LLVMCompiler::addRuntimeToModule() {
        llvm::StringRef irString(_binary_runtime_ll_start, _binary_runtime_ll_size);
        llvm::SMDiagnostic err;
        llvm::MemoryBufferRef bufRef(irString, "runtime.ll");
        std::unique_ptr<llvm::Module> runtimeMod = llvm::parseIR(bufRef, err, context);
        if (!runtimeMod) {
            err.print("qc", llvm::errs());
            errors.emplace_back("Failed to load runtime.ll", Position());
            return;
        }
        if (llvm::Linker::linkModules(*module, std::move(runtimeMod))) {
            errors.emplace_back("Failed to link runtime module", Position());
        }
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
                int v = std::stoi(text);
                return builder->getInt32(v);
            }
            case TokenType::FLOAT: {
                std::string t = text;
                if (!t.empty() && (t.back() == 'f' || t.back() == 'F')) t.pop_back();
                float v = std::stof(t);
                return llvm::ConstantFP::get(builder->getFloatTy(), v);
            }
            case TokenType::DOUBLE: {
                double v = std::stod(text);
                llvm::Type* ty = builder->getDoubleTy();
                return llvm::ConstantFP::get(ty, v);
            }
            default:
                int v = std::stoi(text);
                return builder->getInt32(v);
            }
        }
        else if (auto chr = std::get_if<CharNode>(&node)) {
            char c = chr->tok.value.empty() ? '\0' : chr->tok.value[0];
            return builder->getInt8((uint8_t)c);
        }
        else if (auto boolNode = std::get_if<BoolNode>(&node)) {
            bool value = (boolNode->tok.value == "true");
            return builder->getInt1(value ? 1 : 0);
        }
        else if (auto qbool = std::get_if<QBoolNode>(&node)) {
            uint8_t value;
            if (qbool->tok.value == "none") {
                value = 0b00;
            }
            else if (qbool->tok.value == "qfalse") {
                value = 0b01;
            }
            else if (qbool->tok.value == "qtrue") {
                value = 0b10;
            }
            else if (qbool->tok.value == "both") {
                value = 0b11;
            }
            else {
                cg_error(qbool->tok.pos, "Invalid qbool value: " + qbool->tok.value);
                return nullptr;
            }
            return llvm::ConstantInt::get(builder->getIntNTy(2), value);
        }
        else if (auto str = std::get_if<StringNode>(&node)) {
            llvm::Constant* strConstant = llvm::ConstantDataArray::getString(
                context, 
                str->tok.value,
                true
            );
            
            llvm::GlobalVariable* globalStr = new llvm::GlobalVariable(
                *module,
                strConstant->getType(),
                true,
                llvm::GlobalValue::PrivateLinkage,
                strConstant,
                ".str"
            );
            std::vector<llvm::Value*> indices = {
                builder->getInt32(0),
                builder->getInt32(0)
            };
            return builder->CreateInBoundsGEP(
                strConstant->getType(),
                globalStr,
                indices,
                "str"
            );
        }
        else if (auto bin = std::get_if<std::unique_ptr<BinOpNode>>(&node)) {
            TokenType op = (*bin)->op_tok.type;
            if (op == TokenType::RSHIFT) {
                llvm::Value* leftResult = nullptr;
                
                if (auto leftBin = std::get_if<std::unique_ptr<BinOpNode>>(&(*bin)->left_node)) {
                    if ((*leftBin)->op_tok.type == TokenType::RSHIFT) {
                        leftResult = emitExpr((*bin)->left_node);
                    }
                }
                llvm::Function* qinFn = module->getFunction("qc_qin");
                if (!qinFn) {
                    auto* fnTy = llvm::FunctionType::get(
                        llvm::PointerType::get(context, 0),
                        {},
                        false
                    );
                    qinFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_qin", module.get());
                }
                
                llvm::Value* input = builder->CreateCall(qinFn, {}, "qin_input");
                
                if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&(*bin)->right_node)) {
                    std::string varName = (*varAccess)->var_name_tok.value;
                    llvm::Value* alloc = resolveVariable(varName);
                    if (!alloc) {
                        cg_error(Position(), "qin: variable not declared: " + varName);
                        return nullptr;
                    }
                    
                    llvm::Type* varTy = getPointeeType(alloc);
                    llvm::Value* converted = input;
                    
                    if (varTy->isIntegerTy(32)) {
                        llvm::Function* fn = module->getFunction("qc_to_int_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getInt32Ty(), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_to_int_from_string", module.get());
                        }
                        converted = builder->CreateCall(fn, {input});
                    } else if (varTy->isFloatTy()) {
                        llvm::Function* fn = module->getFunction("qc_to_float_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getFloatTy(), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_to_float_from_string", module.get());
                        }
                        converted = builder->CreateCall(fn, {input});
                    } else if (varTy->isDoubleTy()) {
                        llvm::Function* fn = module->getFunction("qc_to_double_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getDoubleTy(), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_to_double_from_string", module.get());
                        }
                        converted = builder->CreateCall(fn, {input});
                    } else if (varTy->isIntegerTy(8)) {
                        llvm::Function* fn = module->getFunction("qc_to_char_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getInt8Ty(), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_to_char_from_string", module.get());
                        }
                        converted = builder->CreateCall(fn, {input});
                    } else if (varTy->isIntegerTy(1)) {
                        llvm::Function* fn = module->getFunction("qc_to_bool_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getInt1Ty(), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_to_bool_from_string", module.get());
                        }
                        converted = builder->CreateCall(fn, {input});
                    } else if (varTy->isIntegerTy(2)) {
                        llvm::Function* fn = module->getFunction("qc_to_qbool_from_string");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getIntNTy(2), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_to_qbool_from_string", module.get());
                        }
                        converted = builder->CreateCall(fn, {input});
                    }
                    
                    builder->CreateStore(converted, alloc);
                    
                    return builder->getInt32(0);
                }
                
                cg_error(Position(), "qin: right side must be a variable");
                return nullptr;
            }
            llvm::Value* L = emitExpr((*bin)->left_node);
            llvm::Value* R = emitExpr((*bin)->right_node);
            if (!L || !R) return nullptr;
            llvm::Type* lty = L->getType();
            llvm::Type* rty = R->getType();
            if (lty->isPointerTy()) {
                if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&(*bin)->left_node)) {
                    std::string varName = (*varAccess)->var_name_tok.value;
                    llvm::Value* alloc = resolveVariable(varName);
                    if (alloc) {
                        llvm::Type* allocTy = getPointeeType(alloc);
                        
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

                    llvm::Value* tagMatch = builder->CreateICmpEQ(
                        tag, builder->getInt32(info.tagIndex), "union_tag_match"
                    );
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
                                strcmp_fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_string_eq", module.get());
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
                    if (fullMatch->getType() != builder->getInt1Ty()) {
                        fullMatch = builder->CreateTrunc(fullMatch, builder->getInt1Ty());
                    }
                    builder->CreateBr(endBB);

                    builder->SetInsertPoint(mismatchBB);
                    builder->CreateBr(endBB);

                    builder->SetInsertPoint(endBB);
                    llvm::PHINode* phi = builder->CreatePHI(builder->getInt1Ty(), 2, "cmp_result");
                    phi->addIncoming(fullMatch, matchBB);
                    phi->addIncoming(builder->getFalse(), mismatchBB);

                    llvm::Value* result = phi;
                    if (isNe) {
                        result = builder->CreateNot(result);
                    }
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

                    llvm::Value* tagMatch = builder->CreateICmpEQ(
                        tag, builder->getInt32(info.tagIndex), "union_tag_match"
                    );

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
                                strcmp_fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_string_eq", module.get());
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
                    if (fullMatch->getType() != builder->getInt1Ty()) {
                        fullMatch = builder->CreateTrunc(fullMatch, builder->getInt1Ty());
                    }
                    builder->CreateBr(endBB);

                    builder->SetInsertPoint(mismatchBB);
                    builder->CreateBr(endBB);

                    builder->SetInsertPoint(endBB);
                    llvm::PHINode* phi = builder->CreatePHI(builder->getInt1Ty(), 2, "cmp_result");
                    phi->addIncoming(fullMatch, matchBB);
                    phi->addIncoming(builder->getFalse(), mismatchBB);

                    llvm::Value* result = phi;
                    if (isNe) {
                        result = builder->CreateNot(result);
                    }
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
                        if (colonPos != std::string::npos) {
                            typeStr = typeStr.substr(0, colonPos);
                        }
                        
                        llvm::Type* memberTy = llvmTypeFor(typeStr);
                        
                        llvm::Value* lhsVal, *rhsVal;
                        
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
                    for (auto& [bb, val] : caseResults) {
                        payloadPhi->addIncoming(val, bb);
                    }
                    payloadPhi->addIncoming(builder->getFalse(), defaultBB);
                    builder->CreateBr(endBB);
                    
                    builder->SetInsertPoint(tagMismatchBB);
                    builder->CreateBr(endBB);
                    
                    builder->SetInsertPoint(endBB);
                    llvm::PHINode* finalPhi = builder->CreatePHI(builder->getInt1Ty(), 2);
                    finalPhi->addIncoming(payloadPhi, payloadEndBB);
                    finalPhi->addIncoming(builder->getFalse(), tagMismatchBB);
                    
                    llvm::Value* result = finalPhi;
                    if (isNe) {
                        result = builder->CreateNot(result);
                    }
                    return result;
                }
                else if (lIsEnum && !rIsEnum && !rIsUnion) {
                    auto match = matchValueToEnumMember(lEnumName, (*bin)->right_node, R);
                    if (!match) {
                        llvm::Value* res = builder->getFalse();
                        if (isNe) res = builder->CreateNot(res);
                        return res;
                    }

                    auto info = *match;
                    llvm::Value* tag = builder->CreateExtractValue(L, 0, "union_tag");
                    llvm::Value* dataPtr = builder->CreateExtractValue(L, 1, "union_data");

                    llvm::Value* tagMatch = builder->CreateICmpEQ(
                        tag, builder->getInt32(info.tagIndex), "union_tag_match"
                    );
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
                                strcmp_fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_string_eq", module.get());
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
                    if (fullMatch->getType() != builder->getInt1Ty()) {
                        fullMatch = builder->CreateTrunc(fullMatch, builder->getInt1Ty());
                    }
                    builder->CreateBr(endBB);

                    builder->SetInsertPoint(mismatchBB);
                    builder->CreateBr(endBB);

                    builder->SetInsertPoint(endBB);
                    llvm::PHINode* phi = builder->CreatePHI(builder->getInt1Ty(), 2, "cmp_result");
                    phi->addIncoming(fullMatch, matchBB);
                    phi->addIncoming(builder->getFalse(), mismatchBB);

                    llvm::Value* result = phi;
                    if (isNe) {
                        result = builder->CreateNot(result);
                    }
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

                    llvm::Value* tagMatch = builder->CreateICmpEQ(
                        tag, builder->getInt32(info.tagIndex), "union_tag_match"
                    );

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
                                strcmp_fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_string_eq", module.get());
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
                    if (fullMatch->getType() != builder->getInt1Ty()) {
                        fullMatch = builder->CreateTrunc(fullMatch, builder->getInt1Ty());
                    }
                    builder->CreateBr(endBB);

                    builder->SetInsertPoint(mismatchBB);
                    builder->CreateBr(endBB);

                    builder->SetInsertPoint(endBB);
                    llvm::PHINode* phi = builder->CreatePHI(builder->getInt1Ty(), 2, "cmp_result");
                    phi->addIncoming(fullMatch, matchBB);
                    phi->addIncoming(builder->getFalse(), mismatchBB);

                    llvm::Value* result = phi;
                    if (isNe) {
                        result = builder->CreateNot(result);
                    }
                    return result;
                }
                else if (lIsEnum && rIsEnum) {
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
                        if (colonPos != std::string::npos) {
                            typeStr = typeStr.substr(0, colonPos);
                        }
                        
                        llvm::Type* memberTy = llvmTypeFor(typeStr);
                        
                        llvm::Value* lhsVal, *rhsVal;
                        
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
                    for (auto& [bb, val] : caseResults) {
                        payloadPhi->addIncoming(val, bb);
                    }
                    payloadPhi->addIncoming(builder->getFalse(), defaultBB);
                    builder->CreateBr(endBB);
                    
                    builder->SetInsertPoint(tagMismatchBB);
                    builder->CreateBr(endBB);
                    
                    builder->SetInsertPoint(endBB);
                    llvm::PHINode* finalPhi = builder->CreatePHI(builder->getInt1Ty(), 2);
                    finalPhi->addIncoming(payloadPhi, payloadEndBB);
                    finalPhi->addIncoming(builder->getFalse(), tagMismatchBB);
                    
                    llvm::Value* result = finalPhi;
                    if (isNe) {
                        result = builder->CreateNot(result);
                    }
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
                            auto* fnTy  = llvm::FunctionType::get(i8Ptr, { builder->getInt32Ty() }, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                        "qc_to_string_int", module.get());
                        }
                        return builder->CreateCall(fn, { v }, "fstr_i32");
                    }
                    if (ty->isDoubleTy()) {
                        auto* fn = module->getFunction("qc_to_string_double");
                        if (!fn) {
                            auto* i8Ptr = llvm::PointerType::get(context, 0);
                            auto* fnTy  = llvm::FunctionType::get(i8Ptr, { builder->getDoubleTy() }, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                        "qc_to_string_double", module.get());
                        }
                        return builder->CreateCall(fn, { v }, "fstr_f64");
                    }
                    if (ty->isFloatTy()) {
                        auto* fn = module->getFunction("qc_to_string_float");
                        if (!fn) {
                            auto* i8Ptr = llvm::PointerType::get(context, 0);
                            auto* fnTy  = llvm::FunctionType::get(i8Ptr, { builder->getDoubleTy() }, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                        "qc_to_string_float", module.get());
                        }
                        return builder->CreateCall(fn, { v }, "fstr_f32");
                    }
                    if (ty->isIntegerTy(1)) {
                        auto* fn = module->getFunction("qc_to_string_bool");
                        if (!fn) {
                            auto* i8Ptr = llvm::PointerType::get(context, 0);
                            auto* fnTy  = llvm::FunctionType::get(i8Ptr, { builder->getInt1Ty() }, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                        "qc_to_string_bool", module.get());
                        }
                        return builder->CreateCall(fn, { v }, "fstr_bool");
                    }
                    if (ty->isIntegerTy(8)) {
                        auto* fn = module->getFunction("qc_to_string_char");
                        if (!fn) {
                            auto* i8Ptr = llvm::PointerType::get(context, 0);
                            auto* fnTy  = llvm::FunctionType::get(i8Ptr, { builder->getInt32Ty() }, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                        "qc_to_string_char", module.get());
                        }
                        return builder->CreateCall(fn, { v }, "fstr_i8");
                    }
                    if (ty->isPointerTy()) {
                        return v;
                    }
                    if (ty->isIntegerTy(2)) {
                        auto* fn = module->getFunction("qc_to_string_qbool");
                        if (!fn) {
                            auto* i8Ptr = llvm::PointerType::get(context, 0);
                            auto* fnTy = llvm::FunctionType::get(i8Ptr, { builder->getIntNTy(2) }, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                        "qc_to_string_qbool", module.get());
                        }
                        return builder->CreateCall(fn, { v }, "fstr_qbool");
                    }
                    
                    if (ty->isArrayTy()) {
                        std::vector<uint64_t> dimensions;
                        llvm::Type* checkTy = ty;
                        while (checkTy->isArrayTy()) {
                            dimensions.push_back(checkTy->getArrayNumElements());
                            checkTy = checkTy->getArrayElementType();
                        }
                        int elemTypeCode = -1;
                        if (checkTy->isIntegerTy(32)) elemTypeCode = 0;
                        else if (checkTy->isFloatTy()) elemTypeCode = 1;
                        else if (checkTy->isDoubleTy()) elemTypeCode = 2;
                        else if (checkTy->isIntegerTy(8)) elemTypeCode = 3;
                        else if (checkTy->isIntegerTy(1)) elemTypeCode = 4;
                        else if (checkTy->isIntegerTy(2)) elemTypeCode = 5;
                        else if (checkTy->isPointerTy()) elemTypeCode = 6;
                        
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
                            auto* fnTy = llvm::FunctionType::get(
                                voidPtrTy,
                                { voidPtrTy, builder->getInt32Ty(), builder->getInt32Ty(), intPtrTy },
                                false
                            );
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, 
                                                        "qc_array_to_string_recursive", module.get());
                        }
                        
                        return builder->CreateCall(fn, {
                            arrPtr,
                            builder->getInt32(elemTypeCode),
                            builder->getInt32(dimensions.size()),
                            dimsPtr
                        }, "fstr_array");
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
                            llvm::AllocaInst* resultAlloc = createEntryAlloca("fstr_union_result", 
                                llvm::PointerType::get(context, 0));
                            
                            llvm::SwitchInst* sw = builder->CreateSwitch(tag, endBB, members.size());
                            
                            for (size_t i = 0; i < members.size(); i++) {
                                llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "fstr_union_case_" + std::to_string(i), currentFunction);
                                sw->addCase(builder->getInt32(i), caseBB);
                                builder->SetInsertPoint(caseBB);
                                
                                std::string ts = members[i].type;
                                size_t c = ts.find(':'); if (c != std::string::npos) ts = ts.substr(0, c);
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
                                if (!strVal) strVal = builder->CreateGlobalStringPtr("?");
                                builder->CreateStore(strVal, resultAlloc);
                                builder->CreateBr(endBB);
                            }
                            
                            builder->SetInsertPoint(endBB);
                            return builder->CreateLoad(llvm::PointerType::get(context, 0), resultAlloc, "fstr_union_result");
                        }
                    }
                    if (ty->isPointerTy()) {
                        return v;
                    }

                    cg_error(pos, "f-string: unsupported type in compiled mode");
                    return nullptr;
                };

                llvm::Value* lStr = toString(L, (*bin)->op_tok.pos);
                llvm::Value* rStr = toString(R, (*bin)->op_tok.pos);
                if (!lStr || !rStr) return nullptr;

                llvm::Function* concatFn = module->getFunction("qc_string_concat");
                if (!concatFn) {
                    auto* i8Ptr = llvm::PointerType::get(context, 0);
                    std::vector<llvm::Type*> argTypes = { i8Ptr, i8Ptr };
                    auto* fnTy = llvm::FunctionType::get(i8Ptr, argTypes, false);
                    concatFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                    "qc_string_concat", module.get());
                }

                return builder->CreateCall(concatFn, { lStr, rStr }, "fstr_concat");
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
                bool isComparison = op == TokenType::LESS || op == TokenType::MORE || 
                                    op == TokenType::LESS_EQ || op == TokenType::MORE_EQ;
                llvm::AllocaInst* resultAlloc = createEntryAlloca("union_op_result", 
                    isComparison ? builder->getInt1Ty() : builder->getDoubleTy());
                
                llvm::SwitchInst* sw = builder->CreateSwitch(lTag, endBB, members.size());
                
                for (size_t i = 0; i < members.size(); i++) {
                    llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "union_op_case_" + std::to_string(i), currentFunction);
                    sw->addCase(builder->getInt32(i), caseBB);
                    builder->SetInsertPoint(caseBB);
                    
                    std::string ts = members[i].type;
                    size_t c = ts.find(':'); if (c != std::string::npos) ts = ts.substr(0, c);
                    llvm::Type* memberTy = llvmTypeFor(ts);
                    
                    llvm::Value* lTypedPtr = builder->CreateBitCast(lPayload, llvm::PointerType::get(context, 0));
                    llvm::Value* rTypedPtr = builder->CreateBitCast(rPayload, llvm::PointerType::get(context, 0));
                    llvm::Value* lhsVal = builder->CreateLoad(memberTy, lTypedPtr, "lmember");
                    llvm::Value* rhsVal = builder->CreateLoad(memberTy, rTypedPtr, "rmember");
                    
                    bool isFP = memberTy->isFloatingPointTy();
                    llvm::Value* res = nullptr;
                    switch (op) {
                        case TokenType::LESS:    res = isFP ? builder->CreateFCmpOLT(lhsVal, rhsVal) : builder->CreateICmpSLT(lhsVal, rhsVal); break;
                        case TokenType::MORE:    res = isFP ? builder->CreateFCmpOGT(lhsVal, rhsVal) : builder->CreateICmpSGT(lhsVal, rhsVal); break;
                        case TokenType::LESS_EQ: res = isFP ? builder->CreateFCmpOLE(lhsVal, rhsVal) : builder->CreateICmpSLE(lhsVal, rhsVal); break;
                        case TokenType::MORE_EQ: res = isFP ? builder->CreateFCmpOGE(lhsVal, rhsVal) : builder->CreateICmpSGE(lhsVal, rhsVal); break;
                        case TokenType::PLUS:    res = isFP ? builder->CreateFAdd(lhsVal, rhsVal) : builder->CreateAdd(lhsVal, rhsVal); break;
                        case TokenType::MINUS:   res = isFP ? builder->CreateFSub(lhsVal, rhsVal) : builder->CreateSub(lhsVal, rhsVal); break;
                        case TokenType::MUL:     res = isFP ? builder->CreateFMul(lhsVal, rhsVal) : builder->CreateMul(lhsVal, rhsVal); break;
                        case TokenType::DIV:     res = isFP ? builder->CreateFDiv(lhsVal, rhsVal) : builder->CreateSDiv(lhsVal, rhsVal); break;
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
                bool isComparison = op == TokenType::LESS || op == TokenType::MORE || 
                                    op == TokenType::LESS_EQ || op == TokenType::MORE_EQ;
                llvm::Type* resultTy = isComparison ? builder->getInt1Ty() : builder->getDoubleTy();
                llvm::AllocaInst* resultAlloc = createEntryAlloca("union_op_result", resultTy);
                
                llvm::SwitchInst* sw = builder->CreateSwitch(tag, endBB, members.size());
                std::vector<llvm::BasicBlock*> caseBBs;
                
                for (size_t i = 0; i < members.size(); i++) {
                    llvm::BasicBlock* caseBB = llvm::BasicBlock::Create(context, "union_op_case_" + std::to_string(i), currentFunction);
                    sw->addCase(builder->getInt32(i), caseBB);
                    builder->SetInsertPoint(caseBB);
                    
                    std::string ts = members[i].type;
                    size_t c = ts.find(':'); if (c != std::string::npos) ts = ts.substr(0, c);
                    llvm::Type* memberTy = llvmTypeFor(ts);
                    
                    llvm::Value* typedPtr = builder->CreateBitCast(payload, llvm::PointerType::get(context, 0));
                    llvm::Value* memberVal = builder->CreateLoad(memberTy, typedPtr, "member");
                    
                    llvm::Value* lhsVal = lIsUnion ? memberVal : otherVal;
                    llvm::Value* rhsVal = lIsUnion ? otherVal : memberVal;
                    
                    llvm::Type* lTy = lhsVal->getType();
                    llvm::Type* rTy = rhsVal->getType();
                    if (lTy != rTy) {
                        if (lTy->isDoubleTy() || rTy->isDoubleTy()) {
                            if (!lTy->isDoubleTy()) lhsVal = lTy->isFloatTy()
                                ? builder->CreateFPExt(lhsVal, builder->getDoubleTy())
                                : builder->CreateSIToFP(lhsVal, builder->getDoubleTy());
                            if (!rTy->isDoubleTy()) rhsVal = rTy->isFloatTy()
                                ? builder->CreateFPExt(rhsVal, builder->getDoubleTy())
                                : builder->CreateSIToFP(rhsVal, builder->getDoubleTy());
                        } else if (lTy->isFloatTy() || rTy->isFloatTy()) {
                            if (!lTy->isFloatTy()) lhsVal = builder->CreateSIToFP(lhsVal, builder->getFloatTy());
                            if (!rTy->isFloatTy()) rhsVal = builder->CreateSIToFP(rhsVal, builder->getFloatTy());
                        } else if (lTy->isIntegerTy() && rTy->isIntegerTy()) {
                            unsigned lBits = lTy->getIntegerBitWidth();
                            unsigned rBits = rTy->getIntegerBitWidth();
                            if (lBits < rBits) lhsVal = builder->CreateSExt(lhsVal, rTy);
                            else rhsVal = builder->CreateSExt(rhsVal, lTy);
                        } else if (lTy->isIntegerTy() && rTy->isFloatingPointTy()) {
                            lhsVal = builder->CreateSIToFP(lhsVal, rTy);
                        } else if (lTy->isFloatingPointTy() && rTy->isIntegerTy()) {
                            rhsVal = builder->CreateSIToFP(rhsVal, lTy);
                        }
                    }
                    
                    bool isFP = lhsVal->getType()->isFloatingPointTy();
                    llvm::Value* res = nullptr;
                    switch (op) {
                        case TokenType::LESS:    res = isFP ? builder->CreateFCmpOLT(lhsVal, rhsVal) : builder->CreateICmpSLT(lhsVal, rhsVal); break;
                        case TokenType::MORE:    res = isFP ? builder->CreateFCmpOGT(lhsVal, rhsVal) : builder->CreateICmpSGT(lhsVal, rhsVal); break;
                        case TokenType::LESS_EQ: res = isFP ? builder->CreateFCmpOLE(lhsVal, rhsVal) : builder->CreateICmpSLE(lhsVal, rhsVal); break;
                        case TokenType::MORE_EQ: res = isFP ? builder->CreateFCmpOGE(lhsVal, rhsVal) : builder->CreateICmpSGE(lhsVal, rhsVal); break;
                        case TokenType::PLUS:    res = isFP ? builder->CreateFAdd(lhsVal, rhsVal) : builder->CreateAdd(lhsVal, rhsVal); break;
                        case TokenType::MINUS:   res = isFP ? builder->CreateFSub(lhsVal, rhsVal) : builder->CreateSub(lhsVal, rhsVal); break;
                        case TokenType::MUL:     res = isFP ? builder->CreateFMul(lhsVal, rhsVal) : builder->CreateMul(lhsVal, rhsVal); break;
                        case TokenType::DIV:     res = isFP ? builder->CreateFDiv(lhsVal, rhsVal) : builder->CreateSDiv(lhsVal, rhsVal); break;
                        default: res = memberVal; break;
                    }
                    
                    // store result - cast to result alloc type if needed
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
            if (lty->isPointerTy() && rty->isPointerTy() && op == TokenType::PLUS) {
                llvm::Function* concatFn = module->getFunction("qc_string_concat");
                if (!concatFn) {
                    llvm::Type* i8PtrTy = llvm::PointerType::get(context, 0);
                    std::vector<llvm::Type*> argTypes = { i8PtrTy, i8PtrTy };
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(i8PtrTy, argTypes, false);
                    concatFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                    "qc_string_concat", module.get());
                }
                return builder->CreateCall(concatFn, { L, R }, "str_concat");
            }
            if ((lty == builder->getInt8Ty() || rty == builder->getInt8Ty()) &&
                (op == TokenType::PLUS || op == TokenType::MINUS)) {
                if (lty == builder->getInt8Ty() && rty != builder->getInt8Ty()) {
                    L = builder->CreateSExt(L, rty, "char_promote");
                    lty = rty;
                }
                else if (rty == builder->getInt8Ty() && lty != builder->getInt8Ty()) {
                    R = builder->CreateSExt(R, lty, "char_promote");
                    rty = lty;
                }
            }
            if (lty != rty) {
                if (lty->isFloatTy() && rty->isDoubleTy()) {
                    L = builder->CreateFPExt(L, rty, "promote_to_double");
                    lty = rty;
                }
                else if (rty->isFloatTy() && lty->isDoubleTy()) {
                    R = builder->CreateFPExt(R, lty, "promote_to_double");
                    rty = lty;
                }
                else if (lty->isIntegerTy() && rty->isIntegerTy()) {
                    unsigned lBits = lty->getIntegerBitWidth();
                    unsigned rBits = rty->getIntegerBitWidth();
                    if (lBits == 1 || rBits == 1 || lBits == 2 || rBits == 2 || lBits == 8 || rBits == 8) {
                        if (lBits != rBits) {
                        }
                    }
                    else {
                        if (lBits < rBits) {
                            L = builder->CreateSExt(L, rty, "promote_int");
                            lty = rty;
                        }
                        else if (rBits < lBits) {
                            R = builder->CreateSExt(R, lty, "promote_int");
                            rty = lty;
                        }
                    }
                }
                else if (lty->isIntegerTy() && rty->isFloatingPointTy()) {
                    L = builder->CreateSIToFP(L, rty, "int_to_float");
                    lty = rty;
                }
                else if (rty->isIntegerTy() && lty->isFloatingPointTy()) {
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
                    return isFloatTy
                        ? builder->CreateFAdd(L, R, "fadd")
                        : builder->CreateAdd (L, R, "add");
                case TokenType::MINUS:
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
                    return isFloatTy
                        ? builder->CreateFSub(L, R, "fsub")
                        : builder->CreateSub (L, R, "sub");
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
                    return isFloatTy
                        ? builder->CreateFMul(L, R, "fmul")
                        : builder->CreateMul (L, R, "mul");
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
                    return isFloatTy
                        ? builder->CreateFDiv(L, R, "fdiv")
                        : builder->CreateSDiv(L, R, "sdiv");
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
                    return isFloatTy
                        ? builder->CreateFRem(L, R, "frem")
                        : builder->CreateSRem(L, R, "srem");
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
                            llvm::FunctionType* fnTy = llvm::FunctionType::get(
                                builder->getInt32Ty(),
                                { builder->getInt32Ty(), builder->getInt32Ty() },
                                false
                            );
                            qc_powi = llvm::Function::Create(
                                fnTy,
                                llvm::Function::ExternalLinkage,
                                "qc_powi_i32",
                                module.get()
                            );
                        }
                        return builder->CreateCall(qc_powi, { L, R }, "powi");
                    }
                    else if (ty->isFloatTy() || ty->isDoubleTy()) {
                        llvm::Function* powFn = llvm::Intrinsic::getDeclaration(
                            module.get(),
                            llvm::Intrinsic::pow,
                            { ty }
                        );
                        return builder->CreateCall(powFn, { L, R }, "pow");
                    }
                    else {
                        cg_error((*bin)->op_tok.pos, "POWER not supported for this type");
                        return nullptr;
                    }
                }
                case TokenType::EQ_TO:
                case TokenType::NOT_EQ:  
                {
                    if (lty->isIntegerTy() && rty->isIntegerTy()) {
                        unsigned lBits = lty->getIntegerBitWidth();
                        unsigned rBits = rty->getIntegerBitWidth();
                        if (lBits == 1 || rBits == 1 || lBits == 2 || rBits == 2) {
                            if (lBits == rBits) {
                                return (op == TokenType::EQ_TO)
                                    ? builder->CreateICmpEQ(L, R, "icmpeq")
                                    : builder->CreateICmpNE(L, R, "icmpne");
                            } else {
                                return builder->getInt1(op == TokenType::NOT_EQ ? 1 : 0);
                            }
                        }
                        if (lBits < rBits) {
                            L = builder->CreateSExt(L, rty, "promote");
                        } else if (rBits < lBits) {
                            R = builder->CreateSExt(R, lty, "promote");
                        }
                        
                        return (op == TokenType::EQ_TO)
                            ? builder->CreateICmpEQ(L, R, "icmpeq")
                            : builder->CreateICmpNE(L, R, "icmpne");
                    }
                    if ((lty->isFloatingPointTy() && rty->isFloatingPointTy())) {
                        return (op == TokenType::EQ_TO)
                            ? builder->CreateFCmpOEQ(L, R, "fcmpeq")
                            : builder->CreateFCmpONE(L, R, "fcmpne");
                    }
                    if (lty->isPointerTy() && rty->isPointerTy()) {
                        llvm::Function* strcmp_fn = module->getFunction("qc_string_eq");
                        llvm::Value* result = builder->CreateCall(strcmp_fn, {L, R});
                        if (op == TokenType::NOT_EQ) {
                            result = builder->CreateNot(result);
                        }
                        return result;
                    }
                    
                     if (op == TokenType::EQ_TO) {
                        return builder->getInt1(0);
                    } else {
                        return builder->getInt1(1);
                    }
                }
                case TokenType::QEQEQ:
                case TokenType::QNEQ:
                {
                    llvm::Value* boolResult = nullptr;
                    
                    if (lty->isIntegerTy() && rty->isIntegerTy()) {
                        unsigned lBits = lty->getIntegerBitWidth();
                        unsigned rBits = rty->getIntegerBitWidth();
                        
                        if (lBits == 1 || rBits == 1 || lBits == 2 || rBits == 2) {
                            if (lBits == rBits) {
                                boolResult = (op == TokenType::QEQEQ)
                                    ? builder->CreateICmpEQ(L, R, "qicmpeq")
                                    : builder->CreateICmpNE(L, R, "qicmpne");
                            } else {
                                return builder->getIntN(2, 0);
                            }
                        } else {
                            if (lBits < rBits) {
                                L = builder->CreateSExt(L, rty, "promote");
                            } else if (rBits < lBits) {
                                R = builder->CreateSExt(R, lty, "promote");
                            }
                            
                            boolResult = (op == TokenType::QEQEQ)
                                ? builder->CreateICmpEQ(L, R, "qicmpeq")
                                : builder->CreateICmpNE(L, R, "qicmpne");
                        }
                    }
                    else if (lty->isFloatingPointTy() && rty->isFloatingPointTy()) {
                        boolResult = (op == TokenType::QEQEQ)
                            ? builder->CreateFCmpOEQ(L, R, "qfcmpeq")
                            : builder->CreateFCmpONE(L, R, "qfcmpne");
                    }
                    else if (lty->isPointerTy() && rty->isPointerTy()) {
                        llvm::Function* strcmp_fn = module->getFunction("qc_string_eq");
                        llvm::Value* cmp = builder->CreateCall(strcmp_fn, {L, R});
                        
                        if (op == TokenType::QNEQ) {
                            cmp = builder->CreateNot(cmp);
                        }
                        
                        boolResult = builder->CreateTrunc(cmp, builder->getInt1Ty());
                    }
                    else {
                        return builder->getIntN(2, 0);
                    }
                    llvm::Value* ext = builder->CreateZExt(boolResult, builder->getInt8Ty());
                    llvm::Value* tripled = builder->CreateMul(ext, builder->getInt8(3));
                    return builder->CreateTrunc(tripled, builder->getIntNTy(2));
                }
                case TokenType::LESS:
                case TokenType::MORE:
                case TokenType::LESS_EQ:
                case TokenType::MORE_EQ:
                {
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
                    }
                    else if (lty->isFloatingPointTy() && rty->isFloatingPointTy()) {
                        bool isFloatTy = true;
                    }
                    else {
                        cg_error((*bin)->op_tok.pos, "Cannot compare non-numeric types with <, >, <=, >=");
                        return nullptr;
                    }
                    switch (op) {
                        case TokenType::LESS:
                            return isFloatTy ? builder->CreateFCmpOLT(L, R, "fcmplt") : builder->CreateICmpSLT(L, R, "icmplt");
                        case TokenType::MORE:
                            return isFloatTy ? builder->CreateFCmpOGT(L, R, "fcmpgt") : builder->CreateICmpSGT(L, R, "icmpgt");
                        case TokenType::LESS_EQ:
                            return isFloatTy ? builder->CreateFCmpOLE(L, R, "fcmple") : builder->CreateICmpSLE(L, R, "icmple");
                        case TokenType::MORE_EQ:
                            return isFloatTy ? builder->CreateFCmpOGE(L, R, "fcmpge") : builder->CreateICmpSGE(L, R, "icmpge");
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
                            llvm::FunctionType* fnTy = llvm::FunctionType::get(
                                builder->getInt8Ty(),
                                {builder->getInt8Ty(), builder->getInt8Ty()},
                                false
                            );
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_qand", module.get());
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
                            llvm::FunctionType* fnTy = llvm::FunctionType::get(
                                builder->getInt8Ty(),
                                {builder->getInt8Ty(), builder->getInt8Ty()},
                                false
                            );
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_qor", module.get());
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
                            llvm::FunctionType* fnTy = llvm::FunctionType::get(
                                builder->getInt8Ty(),
                                {builder->getInt8Ty(), builder->getInt8Ty()},
                                false
                            );
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_qxor", module.get());
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
                            llvm::FunctionType* fnTy = llvm::FunctionType::get(
                                builder->getInt1Ty(),
                                {builder->getInt8Ty(), builder->getInt8Ty()},
                                false
                            );
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_qand_collapse", module.get());
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
                            llvm::FunctionType* fnTy = llvm::FunctionType::get(
                                builder->getInt1Ty(),
                                {builder->getInt8Ty(), builder->getInt8Ty()},
                                false
                            );
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_qor_collapse", module.get());
                        }
                        llvm::Value* L8 = builder->CreateZExt(L, builder->getInt8Ty());
                        llvm::Value* R8 = builder->CreateZExt(R, builder->getInt8Ty());
                        llvm::Value* result8 = builder->CreateCall(fn, {L8, R8});
                        return builder->CreateCall(fn, {L8, R8});
                    }
                    cg_error((*bin)->op_tok.pos, "|&| requires qbool operands");
                    return nullptr;
            }
        }
        else if (auto va = std::get_if<std::unique_ptr<VarAssignNode>>(&node)) {
            std::string name = (*va)->var_name_tok.value;
            std::string qcType = (*va)->type_tok.value;
            if (qcType.starts_with("list<") && qcType.ends_with(">")) {
                std::string elemType = qcType.substr(5, qcType.size() - 6);
                int elemTypeCode = getTypeCode(elemType);
                
                if (elemTypeCode != -1) {
                    llvm::Function* createFn = module->getFunction("qc_create_list");
                    if (!createFn) {
                        llvm::Type* ptrTy = llvm::PointerType::get(context, 0);
                        llvm::FunctionType* fnTy = llvm::FunctionType::get(
                            ptrTy,
                            {builder->getInt32Ty()},
                            false
                        );
                        createFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                        "qc_create_list", module.get());
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
                    while (elemTy->isArrayTy()) {
                        elemTy = elemTy->getArrayElementType();
                    }
                    if (elemTy->isIntegerTy(32)) arrayTypeStrings[name] = "int";
                    else if (elemTy->isFloatTy()) arrayTypeStrings[name] = "float";
                    else if (elemTy->isDoubleTy()) arrayTypeStrings[name] = "double";
                    else if (elemTy->isIntegerTy(8)) arrayTypeStrings[name] = "char";
                    else if (elemTy->isIntegerTy(1)) arrayTypeStrings[name] = "bool";
                    else if (elemTy->isIntegerTy(2)) arrayTypeStrings[name] = "qbool";
                    else if (elemTy->isPointerTy()) arrayTypeStrings[name] = "string";
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
                if (elemTy->isIntegerTy(32)) arrayTypeStrings[name] = "int";
                else if (elemTy->isFloatTy()) arrayTypeStrings[name] = "float";
                else if (elemTy->isDoubleTy()) arrayTypeStrings[name] = "double";
                else if (elemTy->isIntegerTy(8)) arrayTypeStrings[name] = "char";
                else if (elemTy->isIntegerTy(1)) arrayTypeStrings[name] = "bool";
                else if (elemTy->isIntegerTy(2)) arrayTypeStrings[name] = "qbool";
                else if (elemTy->isPointerTy()) arrayTypeStrings[name] = "string";
                
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
                if (elemTy->isIntegerTy(32)) elemTypeCode = 0;
                else if (elemTy->isFloatTy()) elemTypeCode = 1;
                else if (elemTy->isDoubleTy()) elemTypeCode = 2;
                else if (elemTy->isIntegerTy(8)) elemTypeCode = 3;
                else if (elemTy->isIntegerTy(1)) elemTypeCode = 4;
                else if (elemTy->isIntegerTy(2)) elemTypeCode = 5;
                else if (elemTy->isPointerTy()) elemTypeCode = 6;
                
                lists[name] = elemTypeCode;
                
                return nullptr;
            }
            qcType = resolveTypeName(qcType);
            auto userTypeIt = userTypes.find(qcType);
            if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Struct) {
                if (auto arrLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&(*va)->value_node)) {
                    llvm::StructType* structTy = structTypes[qcType];
                    llvm::Value* structVal = llvm::UndefValue::get(structTy);
                    auto& structInfo = userTypeIt->second;
                    for (size_t i = 0; i < (*arrLit)->elements.size(); i++) {
                        std::string fieldType = structInfo.fields[i].type;
                        auto fieldTypeIt = userTypes.find(fieldType);
                        llvm::Value* val;
                        
                        if (fieldTypeIt != userTypes.end() && fieldTypeIt->second.kind == UserTypeKind::Struct) {
                            if (auto nestedArrLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&(*arrLit)->elements[i])) {
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
                
                if (auto call = std::get_if<std::unique_ptr<CallNode>>(&(*va)->value_node)) {
                    if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&(*call)->node_to_call)) {
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
                        if (rhs) {
                            builder->CreateStore(rhs, instance);
                        }
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
                    cg_error((*va)->var_name_tok.pos, 
                            "Value does not match any variant of union " + qcType);
                    return nullptr;
                }
                auto& member = userTypes[qcType].members[tag];
                bool isLiteral = member.type.find(':') != std::string::npos;
                llvm::Type* rhsTy = rhs->getType();
                std::string baseType = isLiteral
                    ? member.type.substr(0, member.type.find(':'))
                    : member.type;

                llvm::Type* memberTy = llvmTypeFor(baseType);

                if (!rhsTy->isPointerTy() && rhsTy != memberTy) {
                    cg_error((*va)->var_name_tok.pos,
                        "Union literal variant type mismatch");
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
                while (baseType.ends_with("[]")) {
                    baseType = baseType.substr(0, baseType.length() - 2);
                }
                arrayTypeStrings[name] = baseType;
            }
            llvm::AllocaInst* alloc = nullptr;
            if ((*va)->type_tok.value == "function" || (*va)->type_tok.value == "auto" && std::holds_alternative<std::shared_ptr<FuncDefNode>>((*va)->value_node)) {
                auto fnPtr = std::get<std::shared_ptr<FuncDefNode>>((*va)->value_node);
                llvm::Function* f = emitFuncDef(*fnPtr);
                name = getCurrentNamespace().empty() ? name : getCurrentNamespace() + "::" + name;
                lambdaTypes[name] = f->getFunctionType();
                llvm::Type* funcPtrTy = llvm::PointerType::get(context, 0);
                alloc = createEntryAlloca(name, funcPtrTy);
                
                locals[name] = alloc;
                
                builder->CreateStore(f, alloc);
                return nullptr;
            }
            llvm::Value* existingAlloc = resolveVariable(name);
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
                        builder->CreateStore(rhs, gv);
                    }
                    return nullptr;
                }
            }
            llvm::Type* destTy = getPointeeType(alloc);
            llvm::Value* rhs = emitExpr((*va)->value_node);
            if (!rhs) {
                cg_error((*va)->var_name_tok.pos,
                        "Failed to compile initializer for '" + name + "'");
                return nullptr;
            }

            llvm::Type* srcTy = rhs->getType();
            for (auto& [unionName, unionTy] : unionTypes) {
                if (srcTy == unionTy && !isUnionType(destTy)) {
                    llvm::Value* dataPtr = builder->CreateExtractValue(rhs, 1, "union_data");

                    if (destTy->isPointerTy()) {
                        rhs = builder->CreateBitCast(dataPtr, destTy);
                    } else {
                        llvm::Value* typedPtr = builder->CreateBitCast(
                            dataPtr, 
                            llvm::PointerType::get(context, 0)
                        );
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
                        llvm::Value* typedPtr = builder->CreateBitCast(
                            dataPtr, 
                            llvm::PointerType::get(context, 0)
                        );
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
                    cg_error((*va)->var_name_tok.pos,
                            "Cannot assign double to float in compiled mode");
                    return nullptr;
                } else if (srcTy->isIntegerTy() && destTy->isIntegerTy()) {
                    unsigned srcBits  = srcTy->getIntegerBitWidth();
                    unsigned destBits = destTy->getIntegerBitWidth();
                    if (srcBits > destBits) {
                        rhs = builder->CreateTrunc(rhs, destTy, "trunc");
                    } else if (srcBits < destBits) {
                        rhs = builder->CreateSExt(rhs, destTy, "sext");
                    }
                } else if (srcTy->isIntegerTy() && destTy->isFloatingPointTy()) {
                    rhs = builder->CreateSIToFP(rhs, destTy, "i2f");
                } else {
                    cg_error((*va)->var_name_tok.pos,
                            "Type mismatch in assignment in compiled mode");
                    return nullptr;
                }
            }

            builder->CreateStore(rhs, alloc);
            return nullptr;
        }
        else if (auto acc = std::get_if<std::unique_ptr<VarAccessNode>>(&node)) {
            std::string name = (*acc)->var_name_tok.value;
            if (name == "this") {
                if (currentThis) {
                    return currentThis;
                } else {
                    cg_error((*acc)->var_name_tok.pos, "'this' used outside class method");
                    return nullptr;
                }
            }
            llvm::Value* alloc = resolveVariable(name);
            if (alloc) {
                llvm::Type* ty = getPointeeType(alloc);
                return builder->CreateLoad(ty, alloc, name);
            }
            
            llvm::Function* fn = resolveFunction(name);
            if (fn) {
                return fn;
            }

            cg_error((*acc)->var_name_tok.pos,
                    "Use of undeclared variable '" + name + "' in compiled mode");
            return nullptr;
        }
        else if (auto asn = std::get_if<std::unique_ptr<AssignExprNode>>(&node)) {
            if (auto propAccess = std::get_if<std::shared_ptr<PropertyAccessNode>>(&(*asn)->target)) {
                std::string fieldName = (*propAccess)->property_name.value;
                
                if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&*(*propAccess)->base)) {
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
                                    }
                                }
                                
                                builder->CreateStore(rhsVal, fieldPtr);
                                return nullptr;
                            }
                        }
                        
                        cg_error(Position(), "Field not found: " + fieldName);
                        return nullptr;
                    }
                    llvm::Value* locAlloc = resolveVariable(varName);
                    if (!locAlloc) {
                        cg_error(Position(), "Unknown variable: " + varName);
                        return nullptr;
                    }
                    
                    llvm::Type* allocTy = getPointeeType(locAlloc);
                    
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
                        }
                    }
                    
                    builder->CreateStore(rhsVal, fieldPtr);
                    return nullptr;
                }
            }
            auto lhsVar = std::get_if<std::unique_ptr<VarAccessNode>>(&(*asn)->target);
            if (!lhsVar) {
                cg_error((*asn)->op_tok.pos,
                        "Only simple variables are supported on left side in compiled mode");
                return nullptr;
            }

            std::string name = (*lhsVar)->var_name_tok.value;
            llvm::Value* alloc = resolveVariable(name);
            if (!alloc) {
                cg_error((*lhsVar)->var_name_tok.pos,
                        "Assigning to undeclared variable '" + name + "' in compiled mode");
                return nullptr;
            }
            llvm::Type* destTy = getPointeeType(alloc);
            for (auto& [unionName, unionTy] : unionTypes) {
                if (destTy == unionTy) {
                    llvm::Value* rhs = emitExpr((*asn)->value);
                    if (!rhs) return nullptr;
                    if (rhs->getType() == unionTy) {
                        builder->CreateStore(rhs, alloc);
                        return nullptr;
                    }
                    int tag = findUnionVariantTag(unionName, (*asn)->value, rhs);
                    
                    if (tag == -1) {
                        cg_error(Position(), 
                                "Value does not match any variant of union " + unionName);
                        return nullptr;
                    }
                    auto& member = userTypes[unionName].members[tag];
                    bool isLiteral = member.type.find(':') != std::string::npos;

                    std::string baseType = isLiteral
                        ? member.type.substr(0, member.type.find(':'))
                        : member.type;

                    llvm::Type* rhsTy = rhs->getType();
                    llvm::Type* memberTy = llvmTypeFor(baseType);

                    if (rhsTy->getTypeID() != memberTy->getTypeID()) {
                        cg_error((*asn)->op_tok.pos,
                            "Union variant payload type mismatch");
                        return nullptr;
                    }
                    llvm::Value* unionVal = llvm::UndefValue::get(unionTy);
                    unionVal = builder->CreateInsertValue(unionVal, builder->getInt32(tag), 0);
                    llvm::Value* dataPtr = storeAndGetPointer(rhs);
                    unionVal = builder->CreateInsertValue(unionVal, dataPtr, 1);
                    
                    builder->CreateStore(unionVal, alloc);
                    return nullptr;
                }
            }
            for (auto& [enumName, enumTy] : enumTypes) {
                if (destTy == enumTy) {
                    llvm::Value* rhs = emitExpr((*asn)->value);
                    if (!rhs) return nullptr;
                    
                    builder->CreateStore(rhs, alloc);
                    return nullptr;
                }
            }
            llvm::Value* oldVal = builder->CreateLoad(destTy, alloc, name);
            llvm::Value* rhsVal = emitExpr((*asn)->value);
            if (!rhsVal) {
                cg_error((*asn)->op_tok.pos,
                        "Failed to compile right-hand side of assignment");
                return nullptr;
            }
            llvm::Type* srcTy = rhsVal->getType();
            for (auto& [unionName, unionTy] : unionTypes) {
                if (srcTy == unionTy) {
                    llvm::Value* dataPtr = builder->CreateExtractValue(rhsVal, 1);
                    
                    if (destTy->isPointerTy()) {
                        rhsVal = builder->CreateBitCast(dataPtr, destTy);
                    } else {
                        llvm::Value* typedPtr = builder->CreateBitCast(
                            dataPtr, 
                            llvm::PointerType::get(context, 0)
                        );
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
                    }
                    else if (srcTy->isDoubleTy() && destTy->isFloatTy()) {
                        rhsVal = builder->CreateFPTrunc(rhsVal, destTy, "d2f");
                        srcTy = destTy;
                    }
                    else if (srcTy->isIntegerTy() && destTy->isIntegerTy()) {
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
                    }
                    else if (srcTy->isIntegerTy() && destTy->isFloatingPointTy()) {
                        rhsVal = builder->CreateSIToFP(rhsVal, destTy, "i2f");
                        srcTy = destTy;
                    }
                    else if (srcTy->isFloatingPointTy() && destTy->isIntegerTy()) {
                        rhsVal = builder->CreateFPToSI(rhsVal, destTy, "f2i");
                        srcTy = destTy;
                    }
                }
            }
            else {
                if (srcTy != destTy) {
                    if (srcTy->isFloatTy() && destTy->isDoubleTy()) {
                        rhsVal = builder->CreateFPExt(rhsVal, destTy, "f2d");
                    }
                    else if (srcTy->isIntegerTy() && destTy->isIntegerTy()) {
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
                    }
                    else if (srcTy->isIntegerTy() && destTy->isFloatTy()) {
                        rhsVal = builder->CreateSIToFP(rhsVal, destTy, "i2f");
                    }
                    else if (srcTy->isIntegerTy() && destTy->isDoubleTy()) {
                        rhsVal = builder->CreateSIToFP(rhsVal, destTy, "i2d");
                    }
                    else if (srcTy->isDoubleTy() && destTy->isFloatTy()) {
                        cg_error((*asn)->op_tok.pos,
                                "Cannot narrow double to float (loses precision)");
                        return nullptr;
                    }
                    else if (srcTy->isFloatingPointTy() && destTy->isIntegerTy()) {
                        cg_error((*asn)->op_tok.pos,
                                "Cannot convert floating point to integer (loses precision)");
                        return nullptr;
                    }
                    else {
                        cg_error((*asn)->op_tok.pos, "Type mismatch in assignment");
                        return nullptr;
                    }
                }
            }
            llvm::Value* newVal = nullptr;
            bool isFloatTy = destTy->isFloatingPointTy();

            switch ((*asn)->op_tok.type) {
                case TokenType::EQ:
                    newVal = rhsVal;
                    break;
                case TokenType::PLUS_EQ:
                    newVal = isFloatTy
                        ? builder->CreateFAdd(oldVal, rhsVal, "fadd")
                        : builder->CreateAdd (oldVal, rhsVal, "add");
                    break;
                case TokenType::MINUS_EQ:
                    newVal = isFloatTy
                        ? builder->CreateFSub(oldVal, rhsVal, "fsub")
                        : builder->CreateSub (oldVal, rhsVal, "sub");
                    break;
                case TokenType::MUL_EQ:
                    newVal = isFloatTy
                        ? builder->CreateFMul(oldVal, rhsVal, "fmul")
                        : builder->CreateMul (oldVal, rhsVal, "mul");
                    break;
                case TokenType::DIV_EQ:
                    newVal = isFloatTy
                        ? builder->CreateFDiv(oldVal, rhsVal, "fdiv")
                        : builder->CreateSDiv(oldVal, rhsVal, "sdiv");
                    break;
                case TokenType::MOD_EQ:
                    newVal = isFloatTy
                        ? builder->CreateFRem(oldVal, rhsVal, "frem")
                        : builder->CreateSRem(oldVal, rhsVal, "srem");
                    break;
                default:
                    cg_error((*asn)->op_tok.pos,
                            "Unsupported compound assignment in compiled mode");
                    return nullptr;
            }
            if ((*asn)->op_tok.type == TokenType::EQ) {
                if (auto structTy = llvm::dyn_cast<llvm::StructType>(destTy)) {
                    if (structTy->hasName()) {
                        std::string className = structTy->getName().str();
                        
                        if (classTypes.find(className) != classTypes.end()) {
                            std::vector<llvm::Value*> args = {rhsVal};
                            llvm::Function* opMethod = findMethodOverload(className, "operator=", args);
                            
                            if (opMethod) {
                                std::vector<llvm::Value*> allArgs = {alloc, rhsVal};
                                builder->CreateCall(opMethod, allArgs);
                                return nullptr;
                            }
                        }
                    }
                }
            }
            builder->CreateStore(newVal, alloc);
            return nullptr;
        }
        else if (auto unary = std::get_if<std::unique_ptr<UnaryOpNode>>(&node)) {
            TokenType op = (*unary)->op_tok.type;

            llvm::Value* operand = emitExpr((*unary)->node);
            if (!operand) return nullptr;
            llvm::Type* operandTy = operand->getType();
            for (auto& [unionName, unionTy] : unionTypes) {
                if (operandTy == unionTy) {
                    llvm::Type* targetTy = nullptr;
                    
                    if (op == TokenType::MINUS) {
                        targetTy = builder->getInt32Ty();
                    }
                    else if (op == TokenType::NOT) {
                        targetTy = builder->getInt1Ty();
                    }
                    else if (op == TokenType::QNOT) {
                        targetTy = builder->getIntNTy(2);
                    }
                    if (targetTy) {
                        llvm::Value* dataPtr = builder->CreateExtractValue(operand, 1);
                        llvm::Value* typedPtr = builder->CreateBitCast(
                            dataPtr, 
                            llvm::PointerType::get(context, 0)
                        );
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
                    }
                    else if (op == TokenType::NOT) {
                        targetTy = builder->getInt1Ty();
                    }
                    else if (op == TokenType::QNOT) {
                        targetTy = builder->getIntNTy(2);
                    }
                    if (targetTy) {
                        llvm::Value* dataPtr = builder->CreateExtractValue(operand, 1);
                        llvm::Value* typedPtr = builder->CreateBitCast(
                            dataPtr, 
                            llvm::PointerType::get(context, 0)
                        );
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
            if ((*unary)->op_tok.type == TokenType::QNOT) {
                if (operand->getType() == builder->getIntNTy(2)) {
                    llvm::Function* fn = module->getFunction("qc_qnot");
                    if (!fn) {
                        llvm::FunctionType* fnTy = llvm::FunctionType::get(
                            builder->getInt8Ty(),
                            {builder->getInt8Ty()},
                            false
                        );
                        fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_qnot", module.get());
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
                }
                else if (operandTy->isFloatingPointTy()) {
                    return builder->CreateFNeg(operand, "fneg");
                }
                else {
                    cg_error((*unary)->op_tok.pos, "- requires numeric operand");
                    return nullptr;
                }
            }
            if ((*unary)->op_tok.type == TokenType::INCREMENT || (*unary)->op_tok.type == TokenType::DECREMENT) {
                auto* varPtr = std::get_if<std::unique_ptr<VarAccessNode>>(&(*unary)->node);
                if (!varPtr) {
                    cg_error((*unary)->op_tok.pos, "++/-- only supported on variables in compiled mode");
                    return nullptr;
                }

                std::string name = (*varPtr)->var_name_tok.value;
                llvm::Value* alloc = resolveVariable(name);
                if (!alloc) {
                    cg_error((*varPtr)->var_name_tok.pos, "Use of undeclared variable '" + name + "'");
                    return nullptr;
                }
                llvm::Type* ty = getPointeeType(alloc);

                if (!ty->isIntegerTy() || ty->getIntegerBitWidth() <= 2) {
                    cg_error((*unary)->op_tok.pos, "++/-- only valid on int-like (not bool/qbool)");
                    return nullptr;
                }

                llvm::Value* oldVal = builder->CreateLoad(ty, alloc, name);
                llvm::Value* one    = llvm::ConstantInt::get(ty, 1);

                llvm::Value* newVal;
                if ((*unary)->op_tok.type == TokenType::INCREMENT) {
                    newVal = builder->CreateAdd(oldVal, one, "inc");
                } else {
                    newVal = builder->CreateSub(oldVal, one, "dec");
                }

                builder->CreateStore(newVal, alloc);

                bool isPostfix = (*unary)->is_postfix;
                return isPostfix ? oldVal : newVal;
            }
            if ((*unary)->op_tok.type == TokenType::AMPERSAND) {
                auto* varPtr = std::get_if<std::unique_ptr<VarAccessNode>>(&(*unary)->node);
                if (!varPtr) {
                    cg_error((*unary)->op_tok.pos, "& only supported on variables");
                    return nullptr;
                }
                std::string name = (*varPtr)->var_name_tok.value;
                if (!locals[name] && !globals[name]) {
                    cg_error((*unary)->op_tok.pos, "cannot & something that doesn't exist.");
                    return nullptr;
                }
                if (locals[name]) {
                    return locals[name];
                } else {
                    return globals[name];
                }
            }
            if ((*unary)->op_tok.type == TokenType::MUL) {
            }
        }
        else if (auto fnPtr = std::get_if<std::shared_ptr<FuncDefNode>>(&node)) {
            llvm::Function* f = emitFuncDef(*(*fnPtr));
            return f;
        }
        else if (auto mapLit = std::get_if<std::unique_ptr<MapLiteralNode>>(&node)) {
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
                llvm::FunctionType* fnTy = llvm::FunctionType::get(
                    ptrTy,
                    {builder->getInt32Ty(), builder->getInt32Ty()},
                    false
                );
                createFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                "qc_create_map", module.get());
            }
            
            llvm::Value* mapPtr = builder->CreateCall(createFn, {
                builder->getInt32(keyTypeCode),
                builder->getInt32(valueTypeCode)
            }, "map_lit_ptr");
            
            llvm::Function* setFn = module->getFunction("qc_map_set");
            if (!setFn) {
                llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                llvm::FunctionType* fnTy = llvm::FunctionType::get(
                    builder->getVoidTy(),
                    {voidPtrTy, voidPtrTy, voidPtrTy},
                    false
                );
                setFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                            "qc_map_set", module.get());
            }
            
            for (auto& pair : (*mapLit)->pairs) {
                llvm::Value* keyVal = emitExpr(pair.first);
                llvm::Value* valueVal = emitExpr(pair.second);
                if (!keyVal || !valueVal) continue;
                
                llvm::AllocaInst* keyAlloc = createEntryAlloca("lit_key", keyVal->getType());
                llvm::AllocaInst* valAlloc = createEntryAlloca("lit_val", valueVal->getType());
                builder->CreateStore(keyVal, keyAlloc);
                builder->CreateStore(valueVal, valAlloc);
                
                llvm::Value* keyPtr = builder->CreateBitCast(keyAlloc, 
                                                            llvm::PointerType::get(context, 0));
                llvm::Value* valPtr = builder->CreateBitCast(valAlloc, 
                                                            llvm::PointerType::get(context, 0));
                
                builder->CreateCall(setFn, {mapPtr, keyPtr, valPtr});
            }
            
            return mapPtr;
        }
        else if (auto arrLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&node)) {
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
                        llvm::FunctionType* mallocTy = llvm::FunctionType::get(
                            builder->getPtrTy(),
                            {builder->getInt64Ty()},
                            false
                        );
                        mallocFn = llvm::Function::Create(mallocTy, llvm::Function::ExternalLinkage,
                                                        "malloc", module.get());
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
                if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&elem)) {
                    llvm::Value* collVal = emitExpr((*spread)->expr);
                    llvm::Value* spreadLen = getCollectionLength(collVal, (*spread)->expr);
                    
                    if (!llvm::isa<llvm::ConstantInt>(spreadLen)) {
                        hasRuntimeSpread = true;
                    }
                    totalSize = builder->CreateAdd(totalSize, spreadLen);
                } else {
                    totalSize = builder->CreateAdd(totalSize, builder->getInt32(1));
                }
            }
            
            if (hasRuntimeSpread) {
                return createRuntimeSizedArray((*arrLit)->elements, totalSize);
            }
            std::vector<llvm::Value*> allElements;
            for (auto& elem : (*arrLit)->elements) {
                if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&elem)) {
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
                std::vector<llvm::Value*> indices = {
                    builder->getInt32(0),
                    builder->getInt32(i)
                };
                llvm::Value* elemPtr = builder->CreateInBoundsGEP(arrTy, alloc, indices, "arr_elem_ptr");
                builder->CreateStore(allElements[i], elemPtr);
            }
            
            std::vector<llvm::Value*> indices = {builder->getInt32(0), builder->getInt32(0)};
            return builder->CreateInBoundsGEP(arrTy, alloc, indices, "arr_ptr");
        }
        else if (auto callPtr = std::get_if<std::unique_ptr<CallNode>>(&node)) {
            CallNode& call = *(*callPtr);
            if (auto* varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&call.node_to_call)) {
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
                    FuncDefNode* funcDef = funcDefIt->second.get();
                    if (funcHasAutoParams(funcDef)) {
                        std::vector<llvm::Value*> argValues;
                        std::vector<std::string> argTypes;
                        
                        for (auto& argNode : call.arg_nodes) {
                            std::string argType = getExpressionType(argNode);
                            llvm::Value* argVal = emitExpr(argNode);
                            if (!argVal) return nullptr;
                            
                            argValues.push_back(argVal);
                            argTypes.push_back(argType);
                        }
                        std::string sig = makeTypeSignature(argTypes);
                        std::string specializedName = funcName + "_" + sig;
                        if (specializedFunctions[funcName].count(sig) == 0) {
                            llvm::Function* specializedFn = generateSpecializedFunction(
                                funcDef, 
                                argTypes, 
                                specializedName
                            );
                            
                            if (!specializedFn) return nullptr;
                            specializedFunctions[funcName][sig] = specializedFn;
                        }
                        llvm::Function* fn = specializedFunctions[funcName][sig];
                        return builder->CreateCall(fn, argValues);
                    }
                }
                auto classIt = userTypes.find(funcName);
                if (classIt != userTypes.end() && classIt->second.kind == UserTypeKind::Class) {
                    llvm::StructType* classTy = classTypes[funcName];
                    
                    llvm::AllocaInst* temp = createEntryAlloca("temp_" + funcName, classTy);
                    std::string ctorName = "";
                    for (auto& method : classIt->second.classMethods) {
                        if (method.is_constructor) {
                            ctorName = method.name_tok.value;
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
                        llvm::Function* ctor = findMethodOverload(funcName, ctorName, ctorArgs);
                        if (!ctor) {
                            cg_error((*varAccess)->var_name_tok.pos, "No matching constructor for " + funcName);
                            return nullptr;
                        }
                        std::vector<llvm::Value*> allArgs = {temp};
                        allArgs.insert(allArgs.end(), ctorArgs.begin(), ctorArgs.end());
                        builder->CreateCall(ctor, allArgs);
                    } else {
                        builder->CreateStore(llvm::Constant::getNullValue(classTy), temp);
                    }
                    
                    return builder->CreateLoad(classTy, temp, funcName + "_inst");
                }
                static const std::unordered_map<std::string, std::string> builtins = {
                    {"time", "qc_time"},
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
                };
                
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
                                        llvm::Value* variantName = builder->CreateGlobalStringPtr(baseType);
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
                                    llvm::Value* typeStr = builder->CreateGlobalStringPtr(type);
                                    builder->CreateStore(typeStr, resultAlloc);
                                    builder->CreateBr(endBB);
                                    switchInst->addCase(builder->getInt32(i), caseBB);
                                }
                                builder->SetInsertPoint(endBB);
                                return builder->CreateLoad(llvm::PointerType::get(context, 0), resultAlloc);
                            }
                        }
                        if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&argNode)) {
                            std::string varName = (*varAccess)->var_name_tok.value;
                            if (hasArrayType(varName)) {
                                return builder->CreateGlobalStringPtr(arrayTypeStrings[varName] + "[]");
                            }
                            if (hasList(varName)) {
                                if (lists.find(varName) != lists.end()) {
                                    int elemTypeCode = lists[varName];
                                    std::string elemType;
                                    if (elemTypeCode == 0) elemType = "int";
                                    else if (elemTypeCode == 1) elemType = "float";
                                    else if (elemTypeCode == 2) elemType = "double";
                                    else if (elemTypeCode == 3) elemType = "char";
                                    else if (elemTypeCode == 4) elemType = "bool";
                                    else if (elemTypeCode == 5) elemType = "qbool";
                                    else if (elemTypeCode == 6) elemType = "string";
                                    else elemType = "auto";
                                    return builder->CreateGlobalStringPtr("list<" + elemType + ">");
                                }
                            }
                        }
                        std::string typeName = "unknown";
                        if (argTy->isIntegerTy(32)) typeName = "int";
                        else if (argTy->isFloatTy()) typeName = "float";
                        else if (argTy->isDoubleTy()) typeName = "double";
                        else if (argTy->isIntegerTy(8)) typeName = "char";
                        else if (argTy->isIntegerTy(1)) typeName = "bool";
                        else if (argTy->isIntegerTy(2)) typeName = "qbool";
                        else if (argTy->isPointerTy()) typeName = "string";
                        if (auto structTy = llvm::dyn_cast<llvm::StructType>(argTy)) typeName = structTy->getName().str();
                        return builder->CreateGlobalStringPtr(typeName);
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
                            auto* fnTy = llvm::FunctionType::get(
                                llvm::PointerType::get(context, 0),
                                {llvm::PointerType::get(context, 0), llvm::PointerType::get(context, 0)},
                                false
                            );
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_fopen", module.get());
                        }
                        return builder->CreateCall(fn, args, "fopen_result");
                    }
                    if (funcName == "fclose") {
                        llvm::Value* arg = emitExpr(call.arg_nodes.front());
                        if (!arg) return nullptr;
                        llvm::Function* fn = module->getFunction("qc_fclose");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(builder->getVoidTy(), {llvm::PointerType::get(context, 0)}, false);
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_fclose", module.get());
                        }
                        builder->CreateCall(fn, {arg});
                        return nullptr;
                    }
                        if (funcName == "fread") {
                        llvm::Value* arg = emitExpr(call.arg_nodes.front());
                        if (!arg) return nullptr;
                        llvm::Function* fn = module->getFunction("qc_fread");
                        if (!fn) {
                            auto* fnTy = llvm::FunctionType::get(
                                llvm::PointerType::get(context, 0),
                                {llvm::PointerType::get(context, 0)},
                                false
                            );
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_fread", module.get());
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
                            auto* fnTy = llvm::FunctionType::get(
                                builder->getVoidTy(),
                                {llvm::PointerType::get(context, 0), llvm::PointerType::get(context, 0)},
                                false
                            );
                            fn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage, "qc_fwrite", module.get());
                        }
                        builder->CreateCall(fn, args);
                        return nullptr;
                    }
                    if (funcName == "random" && !call.arg_nodes.empty()) {
                        if (call.arg_nodes.size() == 1) runtimeName = "qc_random_int";
                        else if (call.arg_nodes.size() == 2) runtimeName = "qc_random_range";
                    }
                    else if (funcName == "qout") {
                        if (call.arg_nodes.empty()) {
                            cg_error((*varAccess)->var_name_tok.pos, "qout requires arguments: " + funcName);
                            return nullptr;
                        }
                        std::vector<AnyNode> goodArgs(std::make_move_iterator(call.arg_nodes.begin()), std::make_move_iterator(call.arg_nodes.end()));
                        int current_arg = 0;
                        std::string fmtString = "";
                        llvm::Value *argVal = emitExpr(goodArgs[0]);
                        llvm::ConstantDataSequential *constArray = nullptr;
                        if (auto *CE = llvm::dyn_cast<llvm::ConstantExpr>(argVal)) {
                            if (CE->getOpcode() == llvm::Instruction::GetElementPtr) {
                                argVal = CE->getOperand(0);
                            }
                        }
                        if (auto *GV = llvm::dyn_cast<llvm::GlobalVariable>(argVal)) {
                            if (GV->hasInitializer()) {
                                constArray = llvm::dyn_cast<llvm::ConstantDataSequential>(GV->getInitializer());
                            }
                        }
                        else {
                            constArray = llvm::dyn_cast<llvm::ConstantDataSequential>(argVal);
                        }
                        if (constArray && constArray->isString()) {
                            fmtString = constArray->getAsString().str();
                        } else {
                            cg_error((*varAccess)->var_name_tok.pos, "qout requires the first argument to be a string: " + funcName);
                            return nullptr;
                        }
                        std::string to_print = "";
                        char c;
                        llvm::Function* printString = module->getFunction("qc_print_string");
                        if (!printString) {
                            llvm::FunctionType* prStrFnTy = llvm::FunctionType::get(builder->getVoidTy(), { llvm::PointerType::get(context, 0) }, false);
                            printString = llvm::Function::Create(
                                    prStrFnTy,
                                    llvm::Function::ExternalLinkage,
                                    "qc_print_string",
                                    module.get()
                                );
                        }
                        llvm::Function* fmtStr = module->getFunction("qc_fmt_string");
                        if (!fmtStr) {
                            llvm::FunctionType* prStrFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), { llvm::PointerType::get(context, 0), builder->getInt32Ty(), builder->getInt1Ty() }, false);
                            fmtStr = llvm::Function::Create(
                                    prStrFnTy,
                                    llvm::Function::ExternalLinkage,
                                    "qc_fmt_string",
                                    module.get()
                                );
                        }
                        llvm::Function* fmtInt = module->getFunction("qc_fmt_int");
                        if (!fmtInt) {
                            llvm::FunctionType* fmtIntFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), { builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt32Ty() }, false);
                            fmtInt = llvm::Function::Create(
                                    fmtIntFnTy,
                                    llvm::Function::ExternalLinkage,
                                    "qc_fmt_int",
                                    module.get()
                                );
                        }
                        llvm::Function* fmtFloat = module->getFunction("qc_fmt_float");
                        if (!fmtFloat) {
                            llvm::FunctionType* fmtFloatFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), { builder->getDoubleTy(), builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt32Ty() }, false);
                            fmtFloat = llvm::Function::Create(
                                    fmtFloatFnTy,
                                    llvm::Function::ExternalLinkage,
                                    "qc_fmt_float",
                                    module.get()
                                );
                        }
                        llvm::Function* fmtDouble = module->getFunction("qc_fmt_double");
                        if (!fmtDouble) {
                            llvm::FunctionType* fmtDoubleFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), { builder->getDoubleTy(), builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt32Ty() }, false);
                                fmtDouble = llvm::Function::Create(
                                    fmtDoubleFnTy,
                                    llvm::Function::ExternalLinkage,
                                    "qc_fmt_double",
                                    module.get()
                                );
                        }
                        llvm::Function* fmtChar = module->getFunction("qc_fmt_char");
                        if (!fmtChar) {
                            llvm::FunctionType* fmtCharFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), { builder->getInt8Ty(), builder->getInt32Ty(), builder->getInt32Ty() }, false);
                            fmtChar = llvm::Function::Create(
                                    fmtCharFnTy,
                                    llvm::Function::ExternalLinkage,
                                    "qc_fmt_char",
                                    module.get()
                                );
                        }
                        llvm::Function* fmtQBool = module->getFunction("qc_fmt_qbool");
                        if (!fmtQBool) {
                            llvm::FunctionType* fmtQBoolFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), { builder->getInt1Ty(), builder->getInt32Ty(), builder->getInt32Ty() }, false);
                                fmtQBool = llvm::Function::Create(
                                    fmtQBoolFnTy,
                                    llvm::Function::ExternalLinkage,
                                    "qc_fmt_qbool",
                                    module.get()
                                );
                        }
                        llvm::Function* fmtBool = module->getFunction("qc_fmt_bool");
                        if (!fmtBool) {
                            llvm::FunctionType* fmtBoolFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), { builder->getInt8Ty(), builder->getInt32Ty(), builder->getInt32Ty() }, false);
                            fmtBool = llvm::Function::Create(
                                    fmtBoolFnTy,
                                    llvm::Function::ExternalLinkage,
                                    "qc_fmt_bool",
                                    module.get()
                                );
                        }
                        llvm::Function* fmtPtr = module->getFunction("qc_fmt_ptr");
                        if (!fmtStr) {
                            llvm::FunctionType* fmtPtrFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), { llvm::PointerType::get(context, 0), builder->getInt32Ty(), builder->getInt1Ty() }, false);
                            fmtPtr = llvm::Function::Create(
                                    fmtPtrFnTy,
                                    llvm::Function::ExternalLinkage,
                                    "qc_fmt_ptr",
                                    module.get()
                                );
                        }
                        llvm::Function* fmtOctal = module->getFunction("qc_fmt_octal");
                        if (!fmtOctal) {
                            llvm::FunctionType* fmtOctalFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), { builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt1Ty() }, false);
                            fmtOctal = llvm::Function::Create(
                                    fmtOctalFnTy,
                                    llvm::Function::ExternalLinkage,
                                    "qc_fmt_octal",
                                    module.get()
                                );
                        }
                        llvm::Function* fmtHex = module->getFunction("qc_fmt_hex");
                        if (!fmtHex) {
                            llvm::FunctionType* fmtHexFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), { builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt1Ty() }, false);
                            fmtHex = llvm::Function::Create(
                                    fmtHexFnTy,
                                    llvm::Function::ExternalLinkage,
                                    "qc_fmt_hex",
                                    module.get()
                                );
                        }
                        llvm::Function* fmtScientific = module->getFunction("qc_fmt_scientific");
                        if (!fmtScientific) {
                            llvm::FunctionType* fmtScientificFnTy = llvm::FunctionType::get(llvm::PointerType::get(context, 0), { builder->getDoubleTy(), builder->getInt32Ty(), builder->getInt32Ty(), builder->getInt32Ty() }, false);
                                fmtScientific = llvm::Function::Create(
                                    fmtScientificFnTy,
                                    llvm::Function::ExternalLinkage,
                                    "qc_fmt_scientific",
                                    module.get()
                                );
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
                                    if (!itgVal->getType()->isIntegerTy(32)) {
                                        cg_error((*varAccess)->var_name_tok.pos, "i formater takes a int: " + funcName);
                                    }
                                    llvm::Value* strVal = builder->CreateGlobalString(to_print);
                                    builder->CreateCall(printString, { strVal });
                                    to_print = "";
                                    builder->CreateCall(printString, { builder->CreateCall(fmtInt, { itgVal, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt32Ty(), precision), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                    break;
                                }
                                case 's': {
                                    current_arg++;
                                    if (goodArgs.size() - 1 < current_arg) {
                                        cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                    }
                                    llvm::Value* stVal = emitExpr(goodArgs[current_arg]);
                                    llvm::Value* strVal = builder->CreateGlobalString(to_print);
                                    builder->CreateCall(printString, { strVal });
                                    to_print = "";
                                    if (i >= fmtString.size()) {
                                    } else if (fmtString[i + 1] == 't') {
                                        i++;
                                        llvm::Type* ty = stVal->getType();
                                        if (auto structTy = llvm::dyn_cast<llvm::StructType>(stVal->getType())) {
                                            if (structTy->hasName()) {
                                                std::string className = structTy->getName().str();
                                                
                                                if (classTypes.find(className) != classTypes.end()) {
                                                    cg_error((*varAccess)->var_name_tok.pos, "st formater takes a struct instance: " + funcName);
                                                    break;
                                                }
                                                else if (structTypes.find(className) != structTypes.end()) {
                                                    llvm::Function* nestedReprFn = module->getFunction(className + "_repr");
                                                    if (nestedReprFn) {
                                                        builder->CreateCall(printString, { builder->CreateCall(nestedReprFn, {stVal}) });
                                                    } else {
                                                        builder->CreateCall(printString, { builder->CreateGlobalString("(unknown struct)") });
                                                    }
                                                } else {
                                                    cg_error((*varAccess)->var_name_tok.pos, "st formater takes a struct instance: " + funcName);
                                                    break;
                                                }
                                            }
                                        } else {
                                            cg_error((*varAccess)->var_name_tok.pos, "st formater takes a struct instance: " + funcName);
                                        }
                                    } else {
                                        if (!stVal->getType()->isPointerTy()) {
                                            cg_error((*varAccess)->var_name_tok.pos, "s formater takes a string: " + funcName);
                                        }
                                        builder->CreateCall(printString, { builder->CreateCall(fmtStr, { stVal, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
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
                                    if (!floatVal->getType()->isFloatTy()) {
                                        cg_error((*varAccess)->var_name_tok.pos, "f formater takes a float: " + funcName);
                                    }
                                    llvm::Value* strVal = builder->CreateGlobalString(to_print);
                                    builder->CreateCall(printString, { strVal });
                                    to_print = "";
                                    builder->CreateCall(printString, { builder->CreateCall(fmtFloat, { builder->CreateFPExt(floatVal, builder->getDoubleTy()), llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt32Ty(), precision), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                    break;
                                }
                                case 'd': {
                                    current_arg++;
                                    if (goodArgs.size() - 1 < current_arg) {
                                        cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                        break;
                                    }
                                    llvm::Value* doubVal = emitExpr(goodArgs[current_arg]);
                                    if (!doubVal->getType()->isDoubleTy()) {
                                        cg_error((*varAccess)->var_name_tok.pos, "d formater takes a double: " + funcName);
                                    }
                                    llvm::Value* strVal = builder->CreateGlobalString(to_print);
                                    builder->CreateCall(printString, { strVal });
                                    to_print = "";
                                    builder->CreateCall(printString, { builder->CreateCall(fmtDouble, { doubVal, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt32Ty(), precision), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                    break;
                                }
                                case 'c': {
                                    current_arg++;
                                    if (goodArgs.size() - 1 < current_arg) {
                                        cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                        break;
                                    }
                                    llvm::Value* strVal = builder->CreateGlobalString(to_print);
                                    builder->CreateCall(printString, { strVal });
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
                                                        
                                                        builder->CreateCall(printString, { builder->CreateCall(reprMethod, args) });
                                                    } else {
                                                        to_print += "(reprless class)";
                                                    }
                                                }
                                            }
                                        } else {
                                            cg_error((*varAccess)->var_name_tok.pos, "cs formater takes a class instance: " + funcName);
                                        }
                                    } else {
                                        if (!cVal->getType()->isIntegerTy(8)) {
                                            cg_error((*varAccess)->var_name_tok.pos, "c formater takes a char: " + funcName);
                                        }
                                        builder->CreateCall(printString, { builder->CreateCall(fmtChar, { cVal, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
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
                                    if (!boolVal->getType()->isIntegerTy(1)) {
                                        cg_error((*varAccess)->var_name_tok.pos, "b formater takes a bool: " + funcName);
                                    }
                                    llvm::Value* strVal = builder->CreateGlobalString(to_print);
                                    builder->CreateCall(printString, { strVal });
                                    to_print = "";
                                    builder->CreateCall(printString, { builder->CreateCall(fmtBool, { boolVal, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                    break;
                                }
                                case 'q': {
                                    current_arg++;
                                    if (goodArgs.size() - 1 < current_arg) {
                                        cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                        break;
                                    }
                                    llvm::Value* qboolVal = emitExpr(goodArgs[current_arg]);
                                    if (!qboolVal->getType()->isIntegerTy(2)) {
                                        cg_error((*varAccess)->var_name_tok.pos, "q formater takes a qbool: " + funcName);
                                    }
                                    llvm::Value* strVal = builder->CreateGlobalString(to_print);
                                    builder->CreateCall(printString, { strVal });
                                    to_print = "";
                                    builder->CreateCall(printString, { builder->CreateCall(fmtQBool, { qboolVal, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                    break;
                                }
                                case 'x': {
                                    current_arg++;
                                    if (goodArgs.size() - 1 < current_arg) {
                                        cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                        break;
                                    }
                                    llvm::Value* itgVal = emitExpr(goodArgs[current_arg]);
                                    if (!itgVal->getType()->isIntegerTy(32)) {
                                        cg_error((*varAccess)->var_name_tok.pos, "x formater takes a int: " + funcName);
                                    }
                                    llvm::Value* strVal = builder->CreateGlobalString(to_print);
                                    builder->CreateCall(printString, { strVal });
                                    to_print = "";
                                    builder->CreateCall(printString, { builder->CreateCall(fmtHex, { itgVal, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                    break;
                                }
                                case 'o': {
                                    current_arg++;
                                    if (goodArgs.size() - 1 < current_arg) {
                                        cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                        break;
                                    }
                                    llvm::Value* itgVal = emitExpr(goodArgs[current_arg]);
                                    if (!itgVal->getType()->isIntegerTy(32)) {
                                        cg_error((*varAccess)->var_name_tok.pos, "o formater takes a int: " + funcName);
                                    }
                                    llvm::Value* strVal = builder->CreateGlobalString(to_print);
                                    builder->CreateCall(printString, { strVal });
                                    to_print = "";
                                    builder->CreateCall(printString, { builder->CreateCall(fmtOctal, { itgVal, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                    break;
                                }
                                case 'p': {
                                    current_arg++;
                                    if (goodArgs.size() - 1 < current_arg) {
                                        cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                    }
                                    llvm::Value* ptVal = emitExpr(goodArgs[current_arg]);
                                    llvm::Value* strVal = builder->CreateGlobalString(to_print);
                                    builder->CreateCall(printString, { strVal });
                                    to_print = "";
                                    if (!ptVal->getType()->isPointerTy()) {
                                        cg_error((*varAccess)->var_name_tok.pos, "p formater takes a pointer: " + funcName);
                                        break;
                                    }
                                    builder->CreateCall(printString, { builder->CreateCall(fmtPtr, { ptVal, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                    break;
                                }
                                case 'e': {
                                    current_arg++;
                                    if (goodArgs.size() - 1 < current_arg) {
                                        cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                        break;
                                    }
                                    llvm::Value* decimalVal = emitExpr(goodArgs[current_arg]);
                                    if (!decimalVal->getType()->isFloatTy() && !decimalVal->getType()->isDoubleTy() && !decimalVal->getType()->isIntegerTy(32)) {
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
                                    builder->CreateCall(printString, { strVal });
                                    to_print = "";
                                    builder->CreateCall(printString, { builder->CreateCall(fmtScientific, { builder->CreateFPExt(decimalVal, builder->getDoubleTy()), llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt32Ty(), precision), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                    break;
                                }
                                case 'a': {
                                    current_arg++;
                                    if (goodArgs.size() - 1 < current_arg) {
                                        cg_error((*varAccess)->var_name_tok.pos, "too few args: " + funcName);
                                    }
                                    llvm::Value* val = emitExpr(goodArgs[current_arg]);
                                    llvm::Type* aTy = val->getType();
                                    llvm::Value* strVal = builder->CreateGlobalString(to_print);
                                    builder->CreateCall(printString, { strVal });
                                    to_print = "";
                                    if (aTy->isIntegerTy(32)) {
                                        builder->CreateCall(printString, { builder->CreateCall(fmtInt, { val, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt32Ty(), precision), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                        break;
                                    }
                                    if (auto structTy = llvm::dyn_cast<llvm::StructType>(aTy)) {
                                        if (structTy->hasName()) {
                                            std::string className = structTy->getName().str();
                                            if (structTypes.find(className) != structTypes.end()) {
                                                llvm::Function* nestedReprFn = module->getFunction(className + "_repr");
                                                if (nestedReprFn) {
                                                    builder->CreateCall(printString, { builder->CreateCall(nestedReprFn, {val}) });
                                                } else {
                                                    builder->CreateCall(printString, { builder->CreateGlobalString("(unknown struct)") });
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    auto* varNode = std::get_if<std::unique_ptr<VarAccessNode>>(&goodArgs[current_arg]);
                                    if ((aTy->isPointerTy() && std::get_if<StringNode>(&goodArgs[current_arg])) || (varNode && hasVarType((*varNode)->var_name_tok.value) && findVarType((*varNode)->var_name_tok.value)->second == std::string("string"))) {
                                        builder->CreateCall(printString, { builder->CreateCall(fmtStr, { val, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                        break;
                                    }
                                    if (aTy->isFloatTy()) {
                                        builder->CreateCall(printString, { builder->CreateCall(fmtFloat, { builder->CreateFPExt(val, builder->getDoubleTy()), llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt32Ty(), precision), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                        break;
                                    }
                                    if (aTy->isDoubleTy()) {
                                        builder->CreateCall(printString, { builder->CreateCall(fmtDouble, { val, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt32Ty(), precision), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
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
                                                    builder->CreateCall(printString, { builder->CreateCall(reprMethod, args) });
                                                } else {
                                                    to_print += "(reprless class)";
                                                }
                                            }
                                        }
                                        if (aTy->isIntegerTy(8)) {
                                            builder->CreateCall(printString, { builder->CreateCall(fmtChar, { val, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                            break;
                                        }
                                        break;
                                    }
                                    if (aTy->isIntegerTy(1)) {
                                        builder->CreateCall(printString, { builder->CreateCall(fmtBool, { val, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                        break;
                                    }
                                    if (aTy->isIntegerTy(2)) {
                                        builder->CreateCall(printString, { builder->CreateCall(fmtQBool, { val, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                        break;
                                    }
                                    if (aTy->isPointerTy()) {
                                        builder->CreateCall(printString, { builder->CreateCall(fmtPtr, { val, llvm::ConstantInt::get(builder->getInt32Ty(), width), llvm::ConstantInt::get(builder->getInt1Ty(), zero_pad)})});
                                        break;
                                    }
                                    break;
                                }     
                                default:
                                    cg_error((*varAccess)->var_name_tok.pos, "invalid formater: " + funcName);
                                    break;
                            }
                        }
                        llvm::Value* strVal = builder->CreateGlobalString(to_print);
                        builder->CreateCall(printString, { strVal });
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
                    llvm::Function* fn = module->getFunction(runtimeName);
                    if (!fn) {
                        cg_error(Position(), "Built-in function not found in runtime: " + runtimeName);
                        return nullptr;
                    }
                    llvm::FunctionType* builtinFnTy = fn->getFunctionType();
                    std::vector<llvm::Value*> args = emitAdaptedArgs(call.arg_nodes, builtinFnTy);
                    if (call.arg_nodes.size() != args.size()) return nullptr;

                    llvm::Type* retTy = fn->getReturnType();
                    return builder->CreateCall(fn, args, retTy->isVoidTy() ? "" : "builtin_call");
                }
            }
            llvm::Value* calleeVal = nullptr;
            if (auto* varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&call.node_to_call)) {
                std::string funcName = (*varAccess)->var_name_tok.value;
                llvm::Function* resolved = resolveFunction(funcName);
                if (resolved) {
                    calleeVal = resolved;
                } else {
                    llvm::Function* direct = module->getFunction(funcName);
                    if (direct) {
                        calleeVal = direct;
                    } else {
                        calleeVal = emitExpr(call.node_to_call);
                    }
                }
            } else {
                calleeVal = emitExpr(call.node_to_call);
            }
            if (!calleeVal) return nullptr;

            llvm::FunctionType* fnTy = nullptr;
            std::string funcName = "";
            if (auto* func = llvm::dyn_cast<llvm::Function>(calleeVal)) {
                fnTy = func->getFunctionType();
                funcName = func->getName().str();
            }
            else if (calleeVal->getType()->isPointerTy()) {
                if (auto* varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&call.node_to_call)) {
                    std::string varName = (*varAccess)->var_name_tok.value;
                    auto it = lambdaTypes.find(varName);
                    if (it != lambdaTypes.end()) {
                        fnTy = it->second;
                    } else {
                        cg_error(Position(), "Unknown lambda type");
                        return nullptr;
                    }
                }
            }

            if (!fnTy) {
                cg_error(Position(), "Could not determine function type");
                return nullptr;
            }
            bool hasSpread = false;
            for (auto& argNode : call.arg_nodes) {
                if (std::holds_alternative<std::unique_ptr<SpreadNode>>(argNode)) {
                    hasSpread = true;
                    break;
                }
            }
            
            if (hasSpread) {
                return emitSpreadFunctionCall(calleeVal, fnTy, call);
            }
            
            std::vector<llvm::Value*> args = emitAdaptedArgs(call.arg_nodes, fnTy);
            if (call.arg_nodes.size() != args.size()) return nullptr;
            auto defIt = functionDefs.find(funcName);
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
            auto* callInst = builder->CreateCall(fnTy, calleeVal, args,
                                                retTy->isVoidTy() ? "" : "calltmp");

            return retTy->isVoidTy() ? nullptr : callInst;
        }
        else if (auto arrAcc = std::get_if<std::unique_ptr<ArrayAccessNode>>(&node)) {
            if (auto varAcc = std::get_if<std::unique_ptr<VarAccessNode>>(&(*arrAcc)->base)) {
                std::string name = (*varAcc)->var_name_tok.value;
                if (hasJaggedArray(name)) {
                    auto jagIt = findJaggedArray(name);
                    llvm::Value* alloc = resolveVariable(name);
                    if (!alloc) {
                        cg_error(Position(), "Unknown jagged array: " + name);
                        return nullptr;
                    }
                    
                    llvm::Value* jaggedPtr = builder->CreateLoad(
                        llvm::PointerType::get(context, 0),
                        alloc,
                        "jagged_ptr"
                    );
                    llvm::ArrayType* indicesArrTy = llvm::ArrayType::get(
                        builder->getInt32Ty(), 
                        (*arrAcc)->indices.size()
                    );
                    llvm::AllocaInst* indicesAlloc = createEntryAlloca("indices_arr", indicesArrTy);
                    
                    for (size_t i = 0; i < (*arrAcc)->indices.size(); i++) {
                        llvm::Value* indexVal = emitExpr((*arrAcc)->indices[i]);
                        if (!indexVal) return nullptr;
                        
                        std::vector<llvm::Value*> indices = {builder->getInt32(0), builder->getInt32(i)};
                        llvm::Value* idxPtr = builder->CreateInBoundsGEP(indicesArrTy, indicesAlloc, indices);
                        builder->CreateStore(indexVal, idxPtr);
                    }
                    llvm::Function* getFn = module->getFunction("qc_jagged_array_get");
                    if (!getFn) {
                        llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                        llvm::Type* intPtrTy = llvm::PointerType::get(context, 0);
                        llvm::FunctionType* fnTy = llvm::FunctionType::get(
                            voidPtrTy,
                            {voidPtrTy, intPtrTy, builder->getInt32Ty()},
                            false
                        );
                        getFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                    "qc_jagged_array_get", module.get());
                    }
                    
                    std::vector<llvm::Value*> idxIndices = {builder->getInt32(0), builder->getInt32(0)};
                    llvm::Value* indicesPtr = builder->CreateInBoundsGEP(indicesArrTy, indicesAlloc, idxIndices);
                    
                    llvm::Value* elemPtr = builder->CreateCall(getFn, {
                        jaggedPtr,
                        indicesPtr,
                        builder->getInt32((*arrAcc)->indices.size())
                    }, "jagged_elem_ptr");
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
                    llvm::Value* alloc = resolveVariable(name);
                    if (!alloc) {
                        cg_error(Position(), "Unknown list: " + name);
                        return nullptr;
                    }
                    
                    llvm::Value* listPtr = builder->CreateLoad(
                        llvm::PointerType::get(context, 0),
                        alloc,
                        "list_ptr"
                    );
                    
                    llvm::Function* getFn = module->getFunction("qc_list_get");
                    if (!getFn) {
                        llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                        llvm::FunctionType* fnTy = llvm::FunctionType::get(
                            voidPtrTy,
                            {voidPtrTy, builder->getInt32Ty()},
                            false
                        );
                        getFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                    "qc_list_get", module.get());
                    }
                    
                    llvm::Value* indexVal = emitExpr((*arrAcc)->indices[0]);
                    if (!indexVal) return nullptr;
                    
                    llvm::Value* elemPtr = builder->CreateCall(getFn, {listPtr, indexVal}, "list_elem_ptr");
                    llvm::Value* nestedPtr = elemPtr;
                    if ((*arrAcc)->indices.size() > 1) {
                        for (size_t i = 1; i < (*arrAcc)->indices.size(); i++) {
                            llvm::Value* idx = emitExpr((*arrAcc)->indices[i]);
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
                    llvm::Value* alloc = resolveVariable(name);
                    if (!alloc) {
                        cg_error(Position(), "Unknown map: " + name);
                        return nullptr;
                    }
                    
                    llvm::Value* mapPtr = builder->CreateLoad(
                        llvm::PointerType::get(context, 0),
                        alloc,
                        "map_ptr"
                    );
                    
                    llvm::Value* keyVal = emitExpr((*arrAcc)->indices[0]);
                    if (!keyVal) return nullptr;

                    llvm::Value* keyPtr;
                    if (keyVal->getType()->isPointerTy()) {
                        keyPtr = keyVal;
                    } else {
                        llvm::AllocaInst* keyAlloc = createEntryAlloca("map_key", keyVal->getType());
                        builder->CreateStore(keyVal, keyAlloc);
                        keyPtr = builder->CreateBitCast(keyAlloc, 
                                                    llvm::PointerType::get(context, 0));
                    }
                    llvm::Function* getFn = module->getFunction("qc_map_get");
                    if (!getFn) {
                        llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                        llvm::FunctionType* fnTy = llvm::FunctionType::get(
                            voidPtrTy,
                            {voidPtrTy, voidPtrTy},
                            false
                        );
                        getFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                    "qc_map_get", module.get());
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
                llvm::Value* alloc = resolveVariable(name);
                if (!alloc) {
                    cg_error(Position(), "Unknown array: " + name);
                    return nullptr;
                }

                llvm::Value* arrAlloc = alloc;
                llvm::Type* arrTy = getPointeeType(arrAlloc);

                if (arrTy->isPointerTy()) {
                    llvm::Value* ptr = builder->CreateLoad(arrTy, arrAlloc, "arr_ptr");
                    llvm::Value* indexVal = emitExpr((*arrAcc)->indices[0]);
                    if (!indexVal) return nullptr;
                    std::string baseType = arrayTypeStrings[name];
                    llvm::Type* elemTy = llvmTypeFor(baseType);
                    
                    llvm::Value* elemPtr = builder->CreateGEP(
                        elemTy,
                        ptr,
                        indexVal,
                        "arr_elem_ptr"
                    );
                    
                    return builder->CreateLoad(elemTy, elemPtr, "arr_elem");
                } else if (arrTy->isArrayTy()) {
                    std::vector<llvm::Value*> indices = {builder->getInt32(0)};
                    
                    for (size_t i = 0; i < (*arrAcc)->indices.size(); i++) {
                        llvm::Value* indexVal = emitExpr((*arrAcc)->indices[i]);
                        if (!indexVal) return nullptr;
                        indices.push_back(indexVal);
                    }
                    
                    llvm::Value* elemPtr = builder->CreateInBoundsGEP(arrTy, arrAlloc, indices, "arr_elem_ptr");
                    llvm::Type* elemTy = arrTy;
                    for (size_t i = 0; i < (*arrAcc)->indices.size(); i++) {
                        if (elemTy->isArrayTy()) {
                            elemTy = elemTy->getArrayElementType();
                        }
                    }
                    
                    return builder->CreateLoad(elemTy, elemPtr, "arr_elem");
                }
            }
            
            cg_error(Position(), "Complex array access not yet supported");
            return nullptr;
        }
        else if (auto propAccess = std::get_if<std::shared_ptr<PropertyAccessNode>>(&node)) {
            std::string propName = (*propAccess)->property_name.value;
            
            std::string baseName = "";
            bool isEnum = false;
            if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&*(*propAccess)->base)) {
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
                if (runtimeIt != runtimeArraySizes.end()) {
                    return builder->CreateLoad(builder->getInt32Ty(), runtimeIt->second, "runtime_len");
                }
                auto it = locals.find(baseName);
                if (it != locals.end()) {
                    llvm::Value* alloc = it->second;
                    llvm::Type* allocTy = getPointeeType(alloc);
                    if (allocTy->isArrayTy()) {
                        return builder->getInt32(allocTy->getArrayNumElements());
                    }
                }
                llvm::Value* baseVal = emitExpr(*(*propAccess)->base);
                if (!baseVal) return nullptr;
                
                llvm::Function* lenFn = module->getFunction("qc_list_length");
                if (!lenFn) {
                    llvm::FunctionType* ty = llvm::FunctionType::get(
                        builder->getInt32Ty(),
                        { llvm::PointerType::get(context, 0) },
                        false
                    );
                    lenFn = llvm::Function::Create(
                        ty,
                        llvm::Function::ExternalLinkage,
                        "qc_list_length",
                        module.get()
                    );
                }
                
                return builder->CreateCall(lenFn, { baseVal }, "list_len");
            }
            if (propName == "size") {
                llvm::Value* baseVal = emitExpr(*(*propAccess)->base);
                if (!baseVal) return nullptr;
                
                llvm::Function* sizeFn = module->getFunction("qc_map_size");
                if (!sizeFn) {
                    llvm::FunctionType* ty = llvm::FunctionType::get(
                        builder->getInt32Ty(),
                        { llvm::PointerType::get(context, 0) },
                        false
                    );
                    sizeFn = llvm::Function::Create(
                        ty,
                        llvm::Function::ExternalLinkage,
                        "qc_map_size",
                        module.get()
                    );
                }
                
                return builder->CreateCall(sizeFn, { baseVal }, "map_size");
            }
            llvm::Value* baseVal = emitExpr(*(*propAccess)->base);
            if (!baseVal) return nullptr;
            
            llvm::Type* baseTy = baseVal->getType();
            if (baseTy->isPointerTy()) {
                if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&*(*propAccess)->base)) {
                    std::string varName = (*varAccess)->var_name_tok.value;
                    llvm::Value* locAlloc = resolveVariable(varName);
                    if (locAlloc) {
                        llvm::Type* allocTy = getPointeeType(locAlloc);
                        
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
                                
                                llvm::Value* fieldPtr = builder->CreateStructGEP(
                                    structTy, 
                                    locAlloc,
                                    fieldIdx, 
                                    propName + "_ptr"
                                );
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
                                if (auto varAcc = std::get_if<std::unique_ptr<VarAccessNode>>(&*(*propAccess)->base)) {
                                    varAlloc = resolveVariable((*varAcc)->var_name_tok.value);
                                }
                                if (!varAlloc) return nullptr;
                                
                                llvm::Value* dataFieldPtr = builder->CreateStructGEP(unionTy, varAlloc, 1, "union_data_ptr");
                                llvm::Value* dataPtr = builder->CreateLoad(
                                    llvm::PointerType::get(context, 0),
                                    dataFieldPtr, "union_data"
                                );
                                
                                llvm::StructType* classTy = classTypes[resolvedVariant];
                                llvm::Value* castedPtr = builder->CreateBitCast(
                                    dataPtr,
                                    llvm::PointerType::get(context, 0)
                                );
                                
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
                                if (auto varAcc = std::get_if<std::unique_ptr<VarAccessNode>>(&*(*propAccess)->base)) {
                                    varAlloc = resolveVariable((*varAcc)->var_name_tok.value);
                                }
                                if (!varAlloc) return nullptr;
                                
                                llvm::Value* dataFieldPtr = builder->CreateStructGEP(unionTy, varAlloc, 1, "union_data_ptr");
                                llvm::Value* dataPtr = builder->CreateLoad(
                                    llvm::PointerType::get(context, 0),
                                    dataFieldPtr, "union_data"
                                );
                                
                                llvm::StructType* structTy = structTypes[resolvedVariant];
                                llvm::Value* castedPtr = builder->CreateBitCast(
                                    dataPtr,
                                    llvm::PointerType::get(context, 0)
                                );
                                
                                llvm::Type* fieldTy = structTy->getElementType(fieldIdx);
                                llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, castedPtr, fieldIdx);
                                return builder->CreateLoad(fieldTy, fieldPtr, propName);
                            }
                        }
                    }
                    
                    cg_error((*propAccess)->property_name.pos, 
                            "No variant of union '" + unionName + "' has field '" + propName + "'");
                    return nullptr;
                }
            }
            cg_error((*propAccess)->property_name.pos, "Unknown property: " + propName);
            return nullptr;
        }
        else if (auto methodCall = std::get_if<std::unique_ptr<MethodCallNode>>(&node)) {
            std::string methodName = (*methodCall)->method_name.value;
            if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&(*methodCall)->base)) {
                if ((*varAccess)->var_name_tok.value == "this" && currentThis && !currentClassName.empty()) {
                    bool isAutoMethod = false;
                    if (autoMethodIndices.find(currentClassName) != autoMethodIndices.end()) {
                        for (size_t methodIdx : autoMethodIndices[currentClassName]) {
                            auto& autoMethod = userTypes[currentClassName].classMethods[methodIdx];
                            if (autoMethod.name_tok.value == methodName && 
                                autoMethod.params.size() == (*methodCall)->args.size()) {
                                std::vector<std::string> argTypes;
                                for (auto& argNode : (*methodCall)->args) {
                                    argTypes.push_back(getExpressionType(argNode));
                                }
                                bool paramsMatch = true;
                                size_t argIdx = 0;
                                for (auto it = autoMethod.params.begin(); it != autoMethod.params.end(); ++it, ++argIdx) {
                                    if (it->type.value != "auto") {
                                        if (argTypes[argIdx] != it->type.value) {
                                            paramsMatch = false;
                                            break;
                                        }
                                    }
                                }
                                
                                if (!paramsMatch) {
                                    continue;
                                }
                                isAutoMethod = true;
                                
                                std::string specializedName = currentClassName + "_" + methodName;
                                for (auto& ty : argTypes) {
                                    specializedName += "_" + ty;
                                }
                                
                                llvm::Function* specialized = module->getFunction(specializedName);
                                if (!specialized) {
                                    specialized = generateSpecializedMethod(currentClassName, methodIdx, argTypes, specializedName);
                                }
                                
                                std::vector<llvm::Value*> allArgs = {currentThis};
                                for (auto& argNode : (*methodCall)->args) {
                                    allArgs.push_back(emitExpr(argNode));
                                }
                                
                                return builder->CreateCall(specialized, allArgs, methodName + "_result");
                            }
                        }
                    }
                    if (!isAutoMethod) {
                        std::vector<llvm::Value*> args;
                        for (auto& argNode : (*methodCall)->args) {
                            llvm::Value* arg = emitExpr(argNode);
                            if (!arg) return nullptr;
                            args.push_back(arg);
                        }
                        
                        llvm::Function* method = findMethodOverload(currentClassName, methodName, args);
                        if (!method) {
                            cg_error(Position(), "No matching overload for " + methodName);
                            return nullptr;
                        }
                        
                        std::vector<llvm::Value*> allArgs = {currentThis};
                        allArgs.insert(allArgs.end(), args.begin(), args.end());
                        
                        return builder->CreateCall(method, allArgs, methodName + "_result");
                    }
                }
            }
            llvm::Value* baseVal = emitExpr((*methodCall)->base);
            if (!baseVal) return nullptr;
            llvm::Type* baseTy = baseVal->getType();
            if (auto structTy = llvm::dyn_cast<llvm::StructType>(baseTy)) {
                if (structTy->hasName()) {
                    std::string structName = structTy->getName().str();
                    
                    auto classIt = classTypes.find(structName);
                    if (classIt != classTypes.end()) {
                        bool isAutoMethod = false;
                        llvm::Function* specialized = nullptr;
                        if (autoMethodIndices.find(structName) != autoMethodIndices.end()) {
                            for (size_t methodIdx : autoMethodIndices[structName]) {
                                auto& autoMethod = userTypes[structName].classMethods[methodIdx];
                                if (autoMethod.name_tok.value == methodName && 
                                    autoMethod.params.size() == (*methodCall)->args.size()) {
                                    std::vector<std::string> argTypes;
                                    for (auto& argNode : (*methodCall)->args) {
                                        std::string ty = getExpressionType(argNode);
                                        argTypes.push_back(ty);
                                    }
                                    bool paramsMatch = true;
                                    size_t argIdx = 0;
                                    for (auto& param : autoMethod.params) {
                                        if (param.type.value != "auto") {
                                            if (argTypes[argIdx] != param.type.value) {
                                                paramsMatch = false;
                                                break;
                                            }
                                        }
                                        argIdx++;
                                    }
                                    
                                    if (!paramsMatch) {
                                        continue;
                                    }
                                    isAutoMethod = true;
                                    std::string methodOwnerClass = structName;
                                    std::string currentClass = structName;
                                    while (!currentClass.empty()) {
                                        auto& classInfo = userTypes[currentClass];
                                        bool found = false;
                                        for (auto& m : classInfo.classMethods) {
                                            if (m.name_tok.value == methodName) {
                                                methodOwnerClass = currentClass;
                                                found = true;
                                                break;
                                            }
                                        }
                                        if (found) break;
                                        currentClass = classInfo.baseClassName;
                                    }

                                    if (!canAccessMethod(currentClassName, methodOwnerClass, methodName)) {
                                        cg_error(Position(), "Cannot access private/protected method in this context");
                                        return nullptr;
                                    }
                                    std::string specializedName = structName + "_" + methodName;
                                    for (auto& ty : argTypes) {
                                        specializedName += "_" + ty;
                                    }
                                    specialized = module->getFunction(specializedName);
                                    if (!specialized) {
                                        specialized = generateSpecializedMethod(structName, methodIdx, argTypes, specializedName);
                                    }
                                    
                                    break;
                                }
                            }
                        }
                        if (isAutoMethod && specialized) {
                            std::vector<llvm::Value*> allArgs;
                            
                            if (auto varAcc = std::get_if<std::unique_ptr<VarAccessNode>>(&(*methodCall)->base)) {
                                std::string varName = (*varAcc)->var_name_tok.value;
                                llvm::Value* locAlloc = resolveVariable(varName);
                                if (locAlloc) {
                                    allArgs.push_back(locAlloc);
                                }
                            } else {
                                llvm::AllocaInst* temp = createEntryAlloca("temp_this", baseTy);
                                builder->CreateStore(baseVal, temp);
                                allArgs.push_back(temp);
                            }
                            
                            for (auto& argNode : (*methodCall)->args) {
                                allArgs.push_back(emitExpr(argNode));
                            }
                            
                            return builder->CreateCall(specialized, allArgs, methodName + "_result");
                        }
                        if (!isAutoMethod) {
                            std::vector<llvm::Value*> methodArgs;
                            for (auto& argNode : (*methodCall)->args) {
                                llvm::Value* arg = emitExpr(argNode);
                                if (!arg) return nullptr;
                                methodArgs.push_back(arg);
                            }
                            
                            llvm::Function* method = findMethodOverload(structName, methodName, methodArgs);
                            if (!method) {
                                cg_error(Position(), "No matching overload for " + methodName);
                                return nullptr;
                            }
                            
                            std::vector<llvm::Value*> allArgs;
                            
                            if (auto varAcc = std::get_if<std::unique_ptr<VarAccessNode>>(&(*methodCall)->base)) {
                                std::string varName = (*varAcc)->var_name_tok.value;
                                llvm::Value* locAlloc = resolveVariable(varName);
                                if (locAlloc) {
                                    allArgs.push_back(locAlloc);
                                } else {
                                    cg_error(Position(), "Unknown variable: " + varName);
                                    return nullptr;
                                }
                            } else {
                                llvm::AllocaInst* temp = createEntryAlloca("temp_this", baseTy);
                                builder->CreateStore(baseVal, temp);
                                allArgs.push_back(temp);
                            }
                            
                            allArgs.insert(allArgs.end(), methodArgs.begin(), methodArgs.end());
                            
                            return builder->CreateCall(method, allArgs, methodName + "_result");
                        }
                    }
                }
            }
            if (auto varAcc = std::get_if<std::unique_ptr<VarAccessNode>>(&(*methodCall)->base)) {
                llvm::Value* varAlloc = resolveVariable((*varAcc)->var_name_tok.value);
                if (varAlloc) {
                    llvm::Type* allocTy = getPointeeType(varAlloc);
                    for (auto& [unionName, unionTy] : unionTypes) {
                        if (allocTy == unionTy) {
                            auto& unionInfo = userTypes[unionName];
                            for (auto& member : unionInfo.members) {
                                std::string resolvedVariant = resolveTypeName(member.type);
                                if (classTypes.find(resolvedVariant) != classTypes.end()) {
                                    if (classMethods[resolvedVariant].find(methodName) != classMethods[resolvedVariant].end()) {
                                        llvm::Value* dataFieldPtr = builder->CreateStructGEP(unionTy, varAlloc, 1, "union_data_ptr");
                                        llvm::Value* dataPtr = builder->CreateLoad(llvm::PointerType::get(context, 0), dataFieldPtr, "union_data");
                                        llvm::StructType* classTy = classTypes[resolvedVariant];
                                        llvm::Value* castedPtr = builder->CreateBitCast(dataPtr, llvm::PointerType::get(context, 0), "union_as_" + resolvedVariant);
                                        std::vector<llvm::Value*> methodArgs;
                                        for (auto& argNode : (*methodCall)->args) {
                                            llvm::Value* arg = emitExpr(argNode);
                                            if (!arg) return nullptr;
                                            methodArgs.push_back(arg);
                                        }
                                        llvm::Function* method = findMethodOverload(resolvedVariant, methodName, methodArgs);
                                        if (!method) {
                                            cg_error(Position(), "No overload for " + methodName + " in " + resolvedVariant);
                                            return nullptr;
                                        }
                                        std::vector<llvm::Value*> allArgs = {castedPtr};
                                        allArgs.insert(allArgs.end(), methodArgs.begin(), methodArgs.end());
                                        return builder->CreateCall(method, allArgs, methodName + "_result");
                                    }
                                }
                            }
                        }
                    }
                }
            }
            std::string baseName = "";
            if (auto varAcc = std::get_if<std::unique_ptr<VarAccessNode>>(&(*methodCall)->base)) {
                baseName = (*varAcc)->var_name_tok.value;
                llvm::Value* resolved = resolveVariable(baseName);
                if (resolved) {
                    for (auto& [key, val] : locals) {
                        if (val == resolved) {
                            baseName = key;
                            break;
                        }
                    }
                }
            } else if (auto propAcc = std::get_if<std::shared_ptr<PropertyAccessNode>>(&(*methodCall)->base)) {
                if (auto varBase = std::get_if<std::unique_ptr<VarAccessNode>>(&*(*propAcc)->base)) {
                    std::string varName = (*varBase)->var_name_tok.value;
                    std::string propName = (*propAcc)->property_name.value;
                    
                    if (varName == "this" && currentThis && !currentClassName.empty()) {
                        baseName = propName;
                    } else {
                        baseName = varName + "." + propName;
                    }
                } else {
                    baseName = (*propAcc)->property_name.value;
                }
            } else {
                cg_error((*methodCall)->method_name.pos, "Method calls only supported on variables or properties");
                return nullptr;
            }
            if (auto propAcc = std::get_if<std::shared_ptr<PropertyAccessNode>>(&(*methodCall)->base)) {
                if (auto varBase = std::get_if<std::unique_ptr<VarAccessNode>>(&*(*propAcc)->base)) {
                    std::string varName = (*varBase)->var_name_tok.value;
                    std::string propName = (*propAcc)->property_name.value;
                    
                    if (varName == "this" && currentThis && !currentClassName.empty()) {
                        int fieldIdx = getFlattenedFieldIndex(currentClassName, propName);
                        if (fieldIdx != -1) {
                            llvm::StructType* classTy = classTypes[currentClassName];
                            llvm::Type* fieldTy = classTy->getElementType(fieldIdx);
                            if (auto fieldStructTy = llvm::dyn_cast<llvm::StructType>(fieldTy)) {
                                if (fieldStructTy->hasName()) {
                                    std::string fieldClassName = fieldStructTy->getName().str();
                                    
                                    if (classTypes.find(fieldClassName) != classTypes.end()) {
                                        llvm::Value* fieldPtr = builder->CreateStructGEP(classTy, currentThis, fieldIdx);
                                        std::vector<llvm::Value*> methodArgs;
                                        for (auto& argNode : (*methodCall)->args) {
                                            llvm::Value* arg = emitExpr(argNode);
                                            if (!arg) return nullptr;
                                            methodArgs.push_back(arg);
                                        }
                                        llvm::Function* method = findMethodOverload(fieldClassName, methodName, methodArgs);
                                        if (!method) {
                                            cg_error(Position(), "No matching overload for " + methodName + " in class " + fieldClassName);
                                            return nullptr;
                                        }
                                        std::vector<llvm::Value*> allArgs = {fieldPtr};
                                        allArgs.insert(allArgs.end(), methodArgs.begin(), methodArgs.end());
                                        
                                        return builder->CreateCall(method, allArgs, methodName + "_result");
                                    }
                                }
                            }
                        }
                    } else {
                        llvm::Value* varAlloc = resolveVariable(varName);
                        if (varAlloc) {
                            llvm::Type* varTy = getPointeeType(varAlloc);
                            if (auto structTy = llvm::dyn_cast<llvm::StructType>(varTy)) {
                                std::string typeName = structTy->getName().str();
                                if (classTypes.find(typeName) != classTypes.end()) {
                                    int fieldIdx = getFlattenedFieldIndex(typeName, propName);
                                    if (fieldIdx != -1) {
                                        llvm::Type* fieldTy = structTy->getElementType(fieldIdx);
                                        
                                        if (auto fieldStructTy = llvm::dyn_cast<llvm::StructType>(fieldTy)) {
                                            if (fieldStructTy->hasName()) {
                                                std::string fieldClassName = fieldStructTy->getName().str();
                                                
                                                if (classTypes.find(fieldClassName) != classTypes.end()) {
                                                    llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, varAlloc, fieldIdx);
                                                    std::vector<llvm::Value*> methodArgs;
                                                    for (auto& argNode : (*methodCall)->args) {
                                                        llvm::Value* arg = emitExpr(argNode);
                                                        if (!arg) return nullptr;
                                                        methodArgs.push_back(arg);
                                                    }
                                                    llvm::Function* method = findMethodOverload(fieldClassName, methodName, methodArgs);
                                                    if (!method) {
                                                        cg_error(Position(), "No matching overload for " + methodName);
                                                        return nullptr;
                                                    }
                                                    std::vector<llvm::Value*> allArgs = {fieldPtr};
                                                    allArgs.insert(allArgs.end(), methodArgs.begin(), methodArgs.end());
                                                    
                                                    return builder->CreateCall(method, allArgs, methodName + "_result");
                                                }
                                            }
                                        }
                                    }
                                }
                                auto userTypeIt = userTypes.find(typeName);
                                if (userTypeIt != userTypes.end() && userTypeIt->second.kind == UserTypeKind::Struct) {
                                    int fieldIdx = -1;
                                    for (size_t i = 0; i < userTypeIt->second.fields.size(); i++) {
                                        if (userTypeIt->second.fields[i].name == propName) {
                                            fieldIdx = i;
                                            break;
                                        }
                                    }
                                    
                                    if (fieldIdx != -1) {
                                        llvm::Type* fieldTy = structTy->getElementType(fieldIdx);
                                        
                                        if (auto fieldStructTy = llvm::dyn_cast<llvm::StructType>(fieldTy)) {
                                            if (fieldStructTy->hasName()) {
                                                std::string fieldClassName = fieldStructTy->getName().str();
                                                
                                                if (classTypes.find(fieldClassName) != classTypes.end()) {
                                                    llvm::Value* fieldPtr = builder->CreateStructGEP(structTy, varAlloc, fieldIdx);
                                                    
                                                    std::vector<llvm::Value*> methodArgs;
                                                    for (auto& argNode : (*methodCall)->args) {
                                                        llvm::Value* arg = emitExpr(argNode);
                                                        if (!arg) return nullptr;
                                                        methodArgs.push_back(arg);
                                                    }
                                                    
                                                    llvm::Function* method = findMethodOverload(fieldClassName, methodName, methodArgs);
                                                    if (!method) {
                                                        cg_error(Position(), "No matching overload for " + methodName);
                                                        return nullptr;
                                                    }
                                                    
                                                    std::vector<llvm::Value*> allArgs = {fieldPtr};
                                                    allArgs.insert(allArgs.end(), methodArgs.begin(), methodArgs.end());
                                                    
                                                    return builder->CreateCall(method, allArgs, methodName + "_result");
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (!baseVal) return nullptr;
            if (methodName == "push") {
                if ((*methodCall)->args.empty()) {
                    cg_error((*methodCall)->method_name.pos, "push() requires 1 argument");
                    return nullptr;
                }
                
                llvm::Value* argVal = emitExpr((*methodCall)->args[0]);
                if (!argVal) return nullptr;
                
                int typeCode = -1;
                llvm::Type* argTy = argVal->getType();
                
                if (argTy->isIntegerTy(32)) typeCode = 0; 
                else if (argTy->isFloatTy()) typeCode = 1;
                else if (argTy->isDoubleTy()) typeCode = 2; 
                else if (argTy->isIntegerTy(8)) typeCode = 3; 
                else if (argTy->isIntegerTy(1)) typeCode = 4;
                else if (argTy->isIntegerTy(2)) typeCode = 5; 
                else if (argTy->isPointerTy()) typeCode = 6; 
                else {
                    cg_error((*methodCall)->method_name.pos, "Unsupported type for push");
                    return nullptr;
                }
                
                llvm::Function* pushFn = module->getFunction("qc_list_push");
                if (!pushFn) {
                    llvm::FunctionType* ty = llvm::FunctionType::get(
                        builder->getVoidTy(),
                        {
                            llvm::PointerType::get(context, 0),  
                            llvm::PointerType::get(context, 0), 
                            builder->getInt32Ty()                      
                        },
                        false
                    );
                    pushFn = llvm::Function::Create(
                        ty,
                        llvm::Function::ExternalLinkage,
                        "qc_list_push",
                        module.get()
                    );
                }
                
                llvm::AllocaInst* argAlloc = createEntryAlloca("push_arg", argVal->getType());
                builder->CreateStore(argVal, argAlloc);
                
                llvm::Value* argPtr = builder->CreateBitCast(
                    argAlloc,
                    llvm::PointerType::get(context, 0),
                    "arg_void_ptr"
                );
                
                builder->CreateCall(pushFn, { baseVal, argPtr, builder->getInt32(typeCode) });
                return nullptr;
            }
            
            if (methodName == "pop") {
                llvm::Function* popFn = module->getFunction("qc_list_pop");
                if (!popFn) {
                    llvm::FunctionType* ty = llvm::FunctionType::get(
                        llvm::PointerType::get(context, 0),
                        { llvm::PointerType::get(context, 0) },
                        false
                    );
                    popFn = llvm::Function::Create(
                        ty,
                        llvm::Function::ExternalLinkage,
                        "qc_list_pop",
                        module.get()
                    );
                }
                return builder->CreateCall(popFn, { baseVal }, "list_pop");
            }
            
            if (methodName == "set") {
                if ((*methodCall)->args.size() != 2) {
                    cg_error((*methodCall)->method_name.pos, "set() requires 2 arguments");
                    return nullptr;
                }
                
                llvm::Value* keyVal = emitExpr((*methodCall)->args[0]);
                llvm::Value* valueVal = emitExpr((*methodCall)->args[1]);
                if (!keyVal || !valueVal) return nullptr;
                
                llvm::AllocaInst* keyAlloc = createEntryAlloca("set_key", keyVal->getType());
                llvm::AllocaInst* valAlloc = createEntryAlloca("set_val", valueVal->getType());
                builder->CreateStore(keyVal, keyAlloc);
                builder->CreateStore(valueVal, valAlloc);
                
                llvm::Value* keyPtr = builder->CreateBitCast(keyAlloc, llvm::PointerType::get(context, 0));
                llvm::Value* valPtr = builder->CreateBitCast(valAlloc, llvm::PointerType::get(context, 0));
                
                llvm::Function* setFn = module->getFunction("qc_map_set");
                if (!setFn) {
                    llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(
                        builder->getVoidTy(),
                        {voidPtrTy, voidPtrTy, voidPtrTy},
                        false
                    );
                    setFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                "qc_map_set", module.get());
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
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(
                        builder->getInt1Ty(),
                        {voidPtrTy, voidPtrTy},
                        false
                    );
                    hasFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                "qc_map_has", module.get());
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
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(
                        builder->getVoidTy(),
                        {voidPtrTy, voidPtrTy},
                        false
                    );
                    removeFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                    "qc_map_remove", module.get());
                }
                
                builder->CreateCall(removeFn, {baseVal, keyPtr});
                return llvm::ConstantInt::get(builder->getInt32Ty(), 0);
            }
            if (methodName == "keys") {
                llvm::Function* keysFn = module->getFunction("qc_map_keys");
                if (!keysFn) {
                    llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(
                        voidPtrTy,
                        {voidPtrTy},
                        false
                    );
                    keysFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                "qc_map_keys", module.get());
                }
                
                return builder->CreateCall(keysFn, {baseVal}, "map_keys");
            }
            
            cg_error((*methodCall)->method_name.pos, "Unknown method: " + methodName);
            return nullptr;
        }
        else if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&node)) {
            cg_error(Position(), "Spread operator can only be used in array/list literals or function calls");
            return nullptr;
        }
        else if (auto fieldAssign = std::get_if<std::unique_ptr<FieldAssignNode>>(&node)) {
            std::string fieldName = (*fieldAssign)->field_name.value;
            std::string targetTypeStr = "";
            if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&(*fieldAssign)->base)) {
                if ((*varAccess)->var_name_tok.value == "this" && !currentClassName.empty()) {
                    targetTypeStr = getFieldType(currentClassName, fieldName);
                }
            }
            llvm::Value* valueVal = nullptr;
            if (auto arrLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&(*fieldAssign)->value)) {
                if ((*arrLit)->elements.empty() && targetTypeStr.find("list<") == 0) {
                    std::string inner = getElementType(targetTypeStr); 
                    int typeCode = getTypeCode(inner);
                    llvm::Function* createListFn = module->getFunction("qc_create_list");
                    if (!createListFn) {
                        llvm::FunctionType* ft = llvm::FunctionType::get(
                            builder->getPtrTy(), 
                            {builder->getInt32Ty()}, 
                            false
                        );
                        createListFn = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "qc_create_list", module.get());
                    }
                    valueVal = builder->CreateCall(createListFn, {builder->getInt32(typeCode)});
                }
            }
            if (!valueVal) {
                valueVal = emitExpr((*fieldAssign)->value);
            }
            if (!valueVal) return nullptr;
            if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&(*fieldAssign)->base)) {
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
            FieldPath path = buildFieldPath((*fieldAssign)->base, fieldName);
            
            if (path.rootVar.empty() || path.path.empty()) {
                cg_error(Position(), "Invalid field assignment");
                return nullptr;
            }
            
            llvm::Value* locAlloc = resolveVariable(path.rootVar);
            if (!locAlloc) {
                cg_error(Position(), "Unknown variable: " + path.rootVar);
                return nullptr;
            }
            
            llvm::Type* allocTy = getPointeeType(locAlloc);
            
            for (auto& [className, classTy] : classTypes) {
                if (allocTy == classTy) {
                    int fieldIdx = getFlattenedFieldIndex(className, fieldName);
                    
                    if (fieldIdx == -1) {
                        cg_error(Position(), "Field not found: " + fieldName);
                        return nullptr;
                    }
                    auto [fieldOwnerClass, fieldAccess] = getFieldOwner(className, fieldName);
                    if (!canAccessField(currentClassName, fieldOwnerClass, fieldAccess)) {
                        cg_error(Position(), "Cannot access " + fieldAccess + " field");
                        return nullptr;
                    }
                    
                    llvm::Value* fieldPtr = builder->CreateStructGEP(classTy, locAlloc, fieldIdx);
                    builder->CreateStore(valueVal, fieldPtr);
                    return nullptr;
                }
            }
            
            auto rootStructTy = llvm::dyn_cast<llvm::StructType>(allocTy);
            if (!rootStructTy) {
                cg_error(Position(), "Not a struct or class");
                return nullptr;
            }
            if (path.path.size() == 1) {
                llvm::Value* fieldPtr = builder->CreateStructGEP(
                    rootStructTy,
                    locAlloc,
                    path.path[0].second,
                    fieldName + "_ptr"
                );
                builder->CreateStore(valueVal, fieldPtr);
                return nullptr;
            }
            llvm::Value* rootVal = builder->CreateLoad(rootStructTy, locAlloc, "root");
            
            llvm::Value* currentVal = rootVal;
            for (size_t i = 0; i < path.path.size() - 1; i++) {
                currentVal = builder->CreateExtractValue(currentVal, path.path[i].second, "extract");
            }
            llvm::Value* modifiedParent = builder->CreateInsertValue(
                currentVal,
                valueVal,
                path.path.back().second,
                "insert"
            );
            for (int i = path.path.size() - 2; i >= 0; i--) {
                rootVal = builder->CreateInsertValue(rootVal, modifiedParent, path.path[i].second, "insert_up");
                if (i > 0) {
                    modifiedParent = rootVal;
                    for (int j = 0; j < i; j++) {
                        modifiedParent = builder->CreateExtractValue(modifiedParent, path.path[j].second, "extract_parent");
                    }
                }
            }
            
            builder->CreateStore(rootVal, locAlloc);
            return nullptr;
        }
        return nullptr;
    }
    llvm::Value* LLVMCompiler::storeAndGetPointer(llvm::Value* val) {
        llvm::Type* ty = val->getType();
        
        if (ty->isPointerTy()) {
            return builder->CreateBitCast(val, llvm::PointerType::get(context, 0));
        }
        
        llvm::Function* mallocFn = module->getFunction("malloc");
        if (!mallocFn) {
            llvm::FunctionType* mallocTy = llvm::FunctionType::get(
                llvm::PointerType::get(context, 0),
                {builder->getInt64Ty()},
                false
            );
            mallocFn = llvm::Function::Create(mallocTy, llvm::Function::ExternalLinkage, "malloc", module.get());
        }
        
        const llvm::DataLayout &DL = module->getDataLayout();
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
                std::string kind     = m.substr(0, colonPos);
                std::string valueStr = m.substr(colonPos + 1);

                if (kind == "int") {
                    if (auto numNode = std::get_if<NumberNode>(&valueNode)) {
                        if (numNode->tok.value == valueStr) {
                            return i;
                        }
                    }
                } else if (kind == "string") {
                    if (auto strNode = std::get_if<StringNode>(&valueNode)) {
                        std::string lit = "\"" + strNode->tok.value + "\"";
                        if (lit == valueStr) {
                            return i;
                        }
                    }
                } else if (kind == "char") {
                    if (auto charNode = std::get_if<CharNode>(&valueNode)) {
                        std::string lit = "'" + charNode->tok.value + "'";
                        if (lit == valueStr) {
                            return i;
                        }
                    }
                } else if (kind == "bool") {
                    if (auto boolNode = std::get_if<BoolNode>(&valueNode)) {
                        if (boolNode->tok.value == valueStr) {
                            return i;
                        }
                    }
                } else if (kind == "qbool") {
                    if (auto qBoolNode = std::get_if<QBoolNode>(&valueNode)) {
                        if (qBoolNode->tok.value == valueStr) {
                            return i;
                        }
                    }
                }
            } else {
                llvm::Type* valTy    = val->getType();
                llvm::Type* memberTy = llvmTypeFor(m);

                if (valTy == memberTy) {
                    return i;
                }
            }
        }

        return -1;
    }
    llvm::Value* LLVMCompiler::callStringConcat(llvm::Value* a, llvm::Value* b) {
        llvm::Function* concatFn = module->getFunction("qc_string_concat");
        if (!concatFn) {
            llvm::FunctionType* ty = llvm::FunctionType::get(
                llvm::PointerType::get(context, 0),
                {
                    llvm::PointerType::get(context, 0),
                    llvm::PointerType::get(context, 0)
                },
                false
            );
            concatFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage,
                                            "qc_string_concat", module.get());
        }
        return builder->CreateCall(concatFn, {a, b});
    }
    void LLVMCompiler::generateStructReprFunctions() {
        llvm::BasicBlock* savedBB = builder->GetInsertBlock();
        
        for (auto& [name, info] : userTypes) {
            if (info.kind != UserTypeKind::Struct) continue;
            
            llvm::StructType* structTy = structTypes[name];
            llvm::FunctionType* reprFnTy = llvm::FunctionType::get(
                llvm::PointerType::get(context, 0),
                {structTy},
                false
            );
            
            llvm::Function* reprFn = llvm::Function::Create(
                reprFnTy,
                llvm::Function::ExternalLinkage,
                name + "_repr",
                module.get()
            );
            llvm::BasicBlock* entryBB = llvm::BasicBlock::Create(context, "entry", reprFn);
            builder->SetInsertPoint(entryBB);
            llvm::Value* structArg = reprFn->arg_begin();
            llvm::Value* result = builder->CreateGlobalStringPtr(name + "(");
            for (size_t i = 0; i < info.fields.size(); i++) {
                auto& field = info.fields[i];
                if (i > 0) {
                    llvm::Value* comma = builder->CreateGlobalStringPtr(", ");
                    result = callStringConcat(result, comma);
                }
                llvm::Value* fieldLabel = builder->CreateGlobalStringPtr(field.name + "=");
                result = callStringConcat(result, fieldLabel);
                llvm::Value* fieldVal = builder->CreateExtractValue(structArg, i);
                llvm::Value* fieldStr = nullptr;
                
                if (field.type == "int") {
                    llvm::Function* toStrFn = module->getFunction("qc_to_string_int");
                    fieldStr = builder->CreateCall(toStrFn, {fieldVal});
                }
                else if (field.type == "float") {
                    llvm::Function* toStrFn = module->getFunction("qc_to_string_float");
                    fieldStr = builder->CreateCall(toStrFn, {fieldVal});
                }
                else if (field.type == "double") {
                    llvm::Function* toStrFn = module->getFunction("qc_to_string_double");
                    fieldStr = builder->CreateCall(toStrFn, {fieldVal});
                }
                else if (field.type == "bool") {
                    llvm::Function* toStrFn = module->getFunction("qc_to_string_bool");
                    fieldStr = builder->CreateCall(toStrFn, {fieldVal});
                }
                else if (field.type == "char") {
                    llvm::Function* toStrFn = module->getFunction("qc_to_string_char");
                    fieldStr = builder->CreateCall(toStrFn, {fieldVal});
                }
                else if (field.type == "string") {
                    fieldStr = fieldVal;
                }
                else if (structTypes.find(field.type) != structTypes.end()) {
                    llvm::Function* nestedReprFn = module->getFunction(field.type + "_repr");
                    if (nestedReprFn) {
                        fieldStr = builder->CreateCall(nestedReprFn, {fieldVal});
                    } else {
                        fieldStr = builder->CreateGlobalStringPtr("?");
                    }
                }
                else {
                    fieldStr = builder->CreateGlobalStringPtr("?");
                }
                
                result = callStringConcat(result, fieldStr);
            }
            llvm::Value* closeParen = builder->CreateGlobalStringPtr(")");
            result = callStringConcat(result, closeParen);
            
            builder->CreateRet(result);
        }
        if (savedBB) {
            builder->SetInsertPoint(savedBB);
        }
    }
    llvm::Value* LLVMCompiler::convertToString(llvm::Value* val, AnyNode& expr) {
        llvm::Type* ty = val->getType();
        
        if (ty->isPointerTy()) {
            if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&expr)) {
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
                        llvm::FunctionType* ty = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0),
                            {llvm::PointerType::get(context, 0)},
                            false
                        );
                        fn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_list_to_string", module.get());
                    }
                    return builder->CreateCall(fn, {val}, "list_str");
                }
                if (hasMap(varName)) {
                    llvm::Function* fn = module->getFunction("qc_map_to_string");
                    if (!fn) {
                        llvm::FunctionType* ty = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0),
                            {llvm::PointerType::get(context, 0)},
                            false
                        );
                        fn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_map_to_string", module.get());
                    }
                    return builder->CreateCall(fn, {val}, "map_str");
                }
                if (hasJaggedArray(varName)) {
                    llvm::Function* fn = module->getFunction("qc_jagged_to_string");
                    if (!fn) {
                        llvm::FunctionType* ty = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0),
                            {llvm::PointerType::get(context, 0)},
                            false
                        );
                        fn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage, "qc_jagged_to_string", module.get());
                    }
                    return builder->CreateCall(fn, {val}, "jagged_str");
                }
            }
            return val;
        }
        std::string fnName;
        if (ty->isIntegerTy(32)) fnName = "qc_to_string_int";
        else if (ty->isFloatTy()) fnName = "qc_to_string_float";
        else if (ty->isDoubleTy()) fnName = "qc_to_string_double";
        else if (ty->isIntegerTy(1)) fnName = "qc_to_string_bool";
        else if (ty->isIntegerTy(2)) fnName = "qc_to_string_qbool";
        else if (ty->isIntegerTy(8)) fnName = "qc_to_string_char";
        else {
            cg_error(Position(), "Cannot convert type to string");
            return nullptr;
        }
        
        llvm::Function* fn = module->getFunction(fnName);
        if (!fn) {
            llvm::FunctionType* fty = llvm::FunctionType::get(
                llvm::PointerType::get(context, 0),
                {val->getType()},
                false
            );
            fn = llvm::Function::Create(fty, llvm::Function::ExternalLinkage, fnName, module.get());
        }
        
        return builder->CreateCall(fn, {val}, "to_str");
    }
    llvm::Value* LLVMCompiler::emitSpreadFunctionCall(
        llvm::Value* calleeVal,
        llvm::FunctionType* fnTy,
        CallNode& call
    ) {
        llvm::Value* totalArgsCount = builder->getInt32(0);
        
        for (auto& argNode : call.arg_nodes) {
            if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&argNode)) {
                llvm::Value* collVal = emitExpr((*spread)->expr);
                llvm::Value* spreadLen = getCollectionLength(collVal, (*spread)->expr);
                totalArgsCount = builder->CreateAdd(totalArgsCount, spreadLen);
            } else {
                totalArgsCount = builder->CreateAdd(totalArgsCount, builder->getInt32(1));
            }
        }
        
        llvm::AllocaInst* argsArray = builder->CreateAlloca(
            llvm::PointerType::get(context, 0),
            totalArgsCount,
            "spread_args_array"
        );
        
        llvm::AllocaInst* typesArray = builder->CreateAlloca(
            builder->getInt32Ty(),
            totalArgsCount,
            "spread_types_array"
        );
        
        llvm::Value* currentIndex = builder->getInt32(0);
        
        for (auto& argNode : call.arg_nodes) {
            if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&argNode)) {
                llvm::Value* collVal = emitExpr((*spread)->expr);
                currentIndex = expandSpreadIntoArrays(
                    collVal, (*spread)->expr,
                    argsArray, typesArray, currentIndex
                );
            } else {
                llvm::Value* argVal = emitExpr(argNode);
                if (!argVal) return nullptr;

                argVal = normalizeValue(argVal, argNode);
                llvm::Type* ty = argVal->getType();

                llvm::Value* argPtr;
                if (ty->isPointerTy()) {
                    argPtr = argVal;
                } else {
                    llvm::AllocaInst* tempAlloc = createEntryAlloca("arg_temp", ty);
                    builder->CreateStore(argVal, tempAlloc);
                    argPtr = builder->CreateBitCast(
                        tempAlloc,
                        llvm::PointerType::get(context, 0)
                    );
                }

                int typeCode = getTypeCodeFromLLVM(ty);

                llvm::Value* slot = builder->CreateGEP(
                    llvm::PointerType::get(context, 0),
                    argsArray,
                    currentIndex
                );
                builder->CreateStore(argPtr, slot);

                llvm::Value* typeSlot = builder->CreateGEP(
                    builder->getInt32Ty(),
                    typesArray,
                    currentIndex
                );
                builder->CreateStore(builder->getInt32(typeCode), typeSlot);

                currentIndex = builder->CreateAdd(currentIndex, builder->getInt32(1));
            }
        }
        
        llvm::Function* spreadFn = module->getFunction("qc_spread_call");
        if (!spreadFn) {
            llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
            llvm::FunctionType* ty = llvm::FunctionType::get(
                builder->getVoidTy(),
                {
                    voidPtrTy,
                    builder->getInt32Ty(),
                    llvm::PointerType::get(context, 0),
                    llvm::PointerType::get(context, 0),
                    builder->getInt32Ty()
                },
                false
            );
            spreadFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage,
                                            "qc_spread_call", module.get());
        }
        
        llvm::Type* retTy = fnTy->getReturnType();
        int retTypeCode = -1;
        if (!retTy->isVoidTy()) {
            retTypeCode = getTypeCodeFromLLVM(retTy);
        }
        
        llvm::Value* funcPtr = builder->CreateBitCast(calleeVal, llvm::PointerType::get(context, 0));
        if (retTy->isVoidTy()) {
            builder->CreateCall(spreadFn, {
                funcPtr,
                totalArgsCount,
                argsArray,
                typesArray,
                builder->getInt32(retTypeCode),
                llvm::ConstantPointerNull::get(llvm::PointerType::get(context, 0))
            });
            return nullptr;
        } else {
            llvm::AllocaInst* retAlloc = createEntryAlloca("spread_ret", retTy);
            llvm::Value* retPtr = builder->CreateBitCast(retAlloc, llvm::PointerType::get(context, 0));
            
            builder->CreateCall(spreadFn, {
                funcPtr,
                totalArgsCount,
                argsArray,
                typesArray,
                builder->getInt32(retTypeCode),
                retPtr
            });
            
            return builder->CreateLoad(retTy, retAlloc, "spread_result");
        }
    }
    void LLVMCompiler::expandSpreadIntoVector(
        llvm::Value* collVal,
        AnyNode& collExpr,
        std::vector<llvm::Value*>& elements
    ) {
        llvm::Value* lengthVal = getCollectionLength(collVal, collExpr);
        if (!lengthVal) return;
        
        if (auto* constLen = llvm::dyn_cast<llvm::ConstantInt>(lengthVal)) {
            int length = constLen->getSExtValue();
            
            bool isList = false;
            int elemTypeCode = 0;
            
            if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&collExpr)) {
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
                        llvm::FunctionType* ty = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0),
                            { 
                                llvm::PointerType::get(context, 0),
                                builder->getInt32Ty()
                            },
                            false
                        );
                        getFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage,
                                                    "qc_list_get", module.get());
                    }
                    llvm::Value* elemPtr = builder->CreateCall(getFn, { collVal, builder->getInt32(i) });
                    
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
    void LLVMCompiler::expandSpreadIntoList(
        llvm::Value* collVal,
        AnyNode& collExpr,
        llvm::Value* listPtr,
        llvm::Function* pushFn,
        int elemTypeCode
    ) {
        llvm::Value* lengthVal = getCollectionLength(collVal, collExpr);
        if (!lengthVal) return;
        
        bool isList = false;
        llvm::Value* actualCollVal = collVal;
        
        if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&collExpr)) {
            std::string collName = (*varAccess)->var_name_tok.value;
            if (hasList(collName)) {
                isList = true;
            } else {
                auto locAlloc = resolveVariable(collName);
                if (locAlloc) {
                    llvm::Type* allocTy = getPointeeType(locAlloc);
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
                llvm::FunctionType* ty = llvm::FunctionType::get(
                    llvm::PointerType::get(context, 0),
                    { 
                        llvm::PointerType::get(context, 0),
                        builder->getInt32Ty()
                    },
                    false
                );
                getFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage,
                                            "qc_list_get", module.get());
            }
            elemPtr = builder->CreateCall(getFn, { collVal, iVal });
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
    llvm::Value* LLVMCompiler::expandSpreadIntoArrays(
        llvm::Value* collVal,
        AnyNode& collExpr,
        llvm::AllocaInst* argsArray,
        llvm::AllocaInst* typesArray,
        llvm::Value* startIndex
    ) {
        llvm::Value* lengthVal = getCollectionLength(collVal, collExpr);
        if (!lengthVal) return startIndex;
        
        bool isList = false;
        int elemTypeCode = 0;
        
        if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&collExpr)) {
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
                llvm::FunctionType* ty = llvm::FunctionType::get(
                    llvm::PointerType::get(context, 0),
                    { 
                        llvm::PointerType::get(context, 0),
                        builder->getInt32Ty()
                    },
                    false
                );
                getFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage,
                                            "qc_list_get", module.get());
            }
            elemPtr = builder->CreateCall(getFn, { collVal, iVal }, "list_elem");
        } else {
            llvm::Type* elemTy = getTypeFromCode(elemTypeCode);
            llvm::Value* arrayPtr = collVal;
            if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&collExpr)) {
                std::string collName = (*varAccess)->var_name_tok.value;
                llvm::Value* locAlloc = resolveVariable(collName);
                if (locAlloc) {
                    llvm::Type* allocTy = getPointeeType(locAlloc);
                    if (allocTy->isPointerTy()) {
                        arrayPtr = builder->CreateLoad(allocTy, locAlloc, "arr_ptr");
                    }
                }
            }
            
            llvm::Value* gepPtr = builder->CreateGEP(elemTy, arrayPtr, iVal, "arr_elem_ptr");
            elemPtr = builder->CreateBitCast(gepPtr, llvm::PointerType::get(context, 0));
        }
        
        llvm::Value* argSlot = builder->CreateGEP(
            llvm::PointerType::get(context, 0),
            argsArray,
            currentIdx
        );
        builder->CreateStore(elemPtr, argSlot);
        
        llvm::Value* typeSlot = builder->CreateGEP(
            builder->getInt32Ty(),
            typesArray,
            currentIdx
        );
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
        if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&collExpr)) {
            std::string collName = (*varAccess)->var_name_tok.value;
            if (hasList(collName)) {
                auto listIt = findList(collName);
                llvm::Function* lenFn = module->getFunction("qc_list_length");
                if (!lenFn) {
                    llvm::FunctionType* ty = llvm::FunctionType::get(
                        builder->getInt32Ty(),
                        { llvm::PointerType::get(context, 0) },
                        false
                    );
                    lenFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage,
                                                "qc_list_length", module.get());
                }
                return builder->CreateCall(lenFn, { collVal }, "list_len");
            }
            if (hasArrayLength(collName)) {
                auto arrLenIt = findArrayLength(collName);
                return builder->getInt32(arrLenIt->second);
            }
            llvm::Value* locAlloc = resolveVariable(collName);
            if (locAlloc) {
                llvm::Type* allocTy = getPointeeType(locAlloc);
                
                if (allocTy && allocTy->isArrayTy()) {
                    return builder->getInt32(allocTy->getArrayNumElements());
                }
                if (allocTy && allocTy->isPointerTy()) {
                    llvm::Function* lenFn = module->getFunction("qc_list_length");
                    if (!lenFn) {
                        llvm::FunctionType* ty = llvm::FunctionType::get(
                            builder->getInt32Ty(),
                            { llvm::PointerType::get(context, 0) },
                            false
                        );
                        lenFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage,
                                                    "qc_list_length", module.get());
                    }
                    return builder->CreateCall(lenFn, { collVal }, "list_len");
                }
            }
        }
        
        if (auto arrLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&collExpr)) {
            return builder->getInt32((*arrLit)->elements.size());
        }
        cg_error(Position(), "Cannot determine collection length for spread");
        return nullptr;
    }
    llvm::Value* LLVMCompiler::copySpreadToArray(
        llvm::Value* collVal,
        AnyNode& collExpr,
        llvm::Value* destArray,
        llvm::Value* startIndex,
        llvm::Type* elemTy,
        int elemTypeCode
    ) {
        llvm::Value* lengthVal = getCollectionLength(collVal, collExpr);
        if (!lengthVal) return startIndex;
        bool isList = false;
        bool isJagged = false;
        if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&collExpr)) {
            std::string rawName = (*varAccess)->var_name_tok.value;
            std::string resolvedName = resolveMetadataName(rawName); // Use the helper!

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
                llvm::FunctionType* ty = llvm::FunctionType::get(
                    llvm::PointerType::get(context, 0),
                    { 
                        llvm::PointerType::get(context, 0),
                        builder->getInt32Ty()
                    },
                    false
                );
                getFn = llvm::Function::Create(ty, llvm::Function::ExternalLinkage,
                                            "qc_list_get", module.get());
            }
            llvm::Value* elemPtr = builder->CreateCall(getFn, { collVal, iVal });
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
    llvm::Value* LLVMCompiler::createRuntimeSizedArray(
        std::vector<AnyNode>& elements,
        llvm::Value* totalSize
    ) {
        llvm::Type* elemTy = nullptr;
        int elemTypeCode = 0;
        for (auto& elem : elements) {
            if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&elem)) {
                if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&(*spread)->expr)) {
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
            llvm::FunctionType* mallocTy = llvm::FunctionType::get(
                llvm::PointerType::get(context, 0),
                {builder->getInt64Ty()},
                false
            );
            mallocFn = llvm::Function::Create(mallocTy, llvm::Function::ExternalLinkage,
                                            "malloc", module.get());
        }
        
        const llvm::DataLayout &DL = module->getDataLayout();
        uint64_t elemSize = DL.getTypeAllocSize(elemTy);
        llvm::Value* totalSizeExt = builder->CreateZExt(totalSize, builder->getInt64Ty());
        llvm::Value* sizeBytes = builder->CreateMul(totalSizeExt, builder->getInt64(elemSize));
        
        llvm::Value* mallocCall = builder->CreateCall(mallocFn, {sizeBytes}, "runtime_arr");
        llvm::Value* arrPtr = builder->CreateBitCast(mallocCall, llvm::PointerType::get(context, 0));
        
        llvm::Value* currentIndex = builder->getInt32(0);
        
        for (auto& elem : elements) {
            if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&elem)) {
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
            
            llvm::GlobalVariable* gv = new llvm::GlobalVariable(
                *module,
                ty,
                false,
                llvm::GlobalValue::ExternalLinkage,
                initVal,
                name
            );
            return reinterpret_cast<llvm::AllocaInst*>(gv);
        }
        llvm::IRBuilder<> tmp(&currentFunction->getEntryBlock(),
                            currentFunction->getEntryBlock().begin());
        return tmp.CreateAlloca(ty, nullptr, name);
    }
    llvm::Function* LLVMCompiler::emitFuncDef(const FuncDefNode& fn) {
        std::string name;
        if (fn.name_tok) {
            name = fn.name_tok->value;
            if (!namespaceStack.empty()) {
                name = getCurrentNamespace() + "::" + name;
            }
        } else {
            name = lambdaName();
        }
        llvm::FunctionType* fTy = llvmFuncTypeFor(fn.return_types, fn.params);
        auto* existing = module->getFunction(name);
        if (existing) return existing;
        functionSignatures[name] = { fTy, {} };
        
        auto* func = llvm::Function::Create(
            fTy,
            llvm::Function::ExternalLinkage,
            name,
            module.get()
        );
        jaggedArraysStack.push_back({});
        arrayTypeStringsStack.push_back({});
        listsStack.push_back({});
        arrayLengthsStack.push_back({});
        mapsStack.push_back({});
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
            std::string t = param.type.value;
            if (t.find("list<") == 0) {
                std::string inner = getElementType(t);
                int code = getTypeCode(inner); 
                lists[param.name.value] = code;
            } 
            else if (t.find("map<") == 0) {
                auto [key, val] = splitMapTypes(t); 
                maps[param.name.value] = std::make_pair(getTypeCode(key), getTypeCode(val));
            }
            else if (t.find("[]") != std::string::npos) {
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
                } else {
                    std::string base = t.substr(0, t.find("[]"));
                    arrayTypeStrings[param.name.value] = base;
                }
            } else {
                varTypes[param.name.value] = t;
            }

            idx++;
        }
        
        for (auto& stmt : fn.body->statements) {
            emitStmt(stmt);
        }
        
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
        
        if (savedInsertBlock) {
            builder->SetInsertPoint(savedInsertBlock);
        }
        
        currentFunction = oldFunction;
        locals = std::move(oldLocals);
        functions[name] = func;
        jaggedArraysStack.pop_back();
        arrayTypeStringsStack.pop_back();
        listsStack.pop_back();
        arrayLengthsStack.pop_back();
        mapsStack.pop_back();
        return func;
    }
    std::string LLVMCompiler::mangleName(const FuncDefNode& fn) {
        std::string base = fn.name_tok ? fn.name_tok->value : "lambda";
        if (!fn.namespace_path.empty()) {
            base = fn.namespace_path + "::" + base;
        }
        return base;
    }
    std::string LLVMCompiler::lambdaName() {
        static int counter = 0;
        return "__lambda_" + std::to_string(counter++);
    }
    void LLVMCompiler::emitStmt(AnyNode& node) {
        if (std::holds_alternative<std::unique_ptr<VarAssignNode>>(node) ||
            std::holds_alternative<std::unique_ptr<AssignExprNode>>(node) ||
            std::holds_alternative<std::unique_ptr<BinOpNode>>(node) ||
            std::holds_alternative<NumberNode>(node) ||
            std::holds_alternative<std::unique_ptr<VarAccessNode>>(node) ||
            std::holds_alternative<BoolNode>(node) ||
            std::holds_alternative<CharNode>(node) ||
            std::holds_alternative<StringNode>(node) ||
            std::holds_alternative<QBoolNode>(node) ||
            std::holds_alternative<std::unique_ptr<UnaryOpNode>>(node) ||
            std::holds_alternative<std::unique_ptr<CallNode>>(node) ||
            std::holds_alternative<std::shared_ptr<FuncDefNode>>(node) ||
            std::holds_alternative<std::unique_ptr<ArrayAccessNode>>(node) ||
            std::holds_alternative<std::shared_ptr<PropertyAccessNode>>(node) ||
            std::holds_alternative<std::unique_ptr<MethodCallNode>>(node) ||
            std::holds_alternative<std::unique_ptr<SpreadNode>>(node) ||
            std::holds_alternative<std::unique_ptr<FieldAssignNode>>(node)) {
            emitExpr(node);
        }
        else if (auto mret = std::get_if<std::unique_ptr<MultiReturnNode>>(&node)) {
            llvm::Type* retTy = currentFunction->getReturnType();

            if (!retTy->isStructTy()) {
                cg_error((*mret)->pos, "Multi-return in non-multi-return function");
                return;
            }

            llvm::Value* agg = llvm::UndefValue::get(retTy);
            llvm::StructType* retStructTy = llvm::cast<llvm::StructType>(retTy);
            for (size_t i = 0; i < (*mret)->values.size(); ++i) {
                llvm::Value* val = nullptr;
                if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&(*mret)->values[i])) {
                    std::string name = (*varAccess)->var_name_tok.value;
                    llvm::Value* alloc = resolveVariable(name);
                    if (alloc) {
                        llvm::Type* allocatedTy = getPointeeType(alloc);
                        if (allocatedTy->isArrayTy()) {
                            val = builder->CreateBitCast(
                                alloc,
                                llvm::PointerType::get(context, 0),
                                "array_ret_ptr"
                            );
                        }
                    }
                }
                if (auto call = std::get_if<std::unique_ptr<CallNode>>(&(*mret)->values[i])) {
                    if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&(*call)->node_to_call)) {
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
                if (auto arrayLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&(*mret)->values[i])) {
                    val = emitExpr((*mret)->values[i]);
                    if (!val) return;
                    
                    llvm::Type* srcTy = val->getType();
                    llvm::Type* destTy = retStructTy->getElementType(i);
                    if (destTy->isPointerTy() && srcTy->isArrayTy()) {
                        llvm::ArrayType* arrayType = llvm::cast<llvm::ArrayType>(srcTy);
                        llvm::Type* i64Ty = builder->getInt64Ty();
                        llvm::Value* size = llvm::ConstantInt::get(i64Ty, 
                            module->getDataLayout().getTypeAllocSize(arrayType));
                        
                        llvm::Function* mallocFn = module->getFunction("malloc");
                        if (!mallocFn) {
                            llvm::FunctionType* mallocTy = llvm::FunctionType::get(
                                builder->getPtrTy(), {i64Ty}, false);
                            mallocFn = llvm::Function::Create(
                                mallocTy, llvm::Function::ExternalLinkage, "malloc", module.get());
                        }
                        
                        llvm::Value* heapPtr = builder->CreateCall(mallocFn, {size});
                        llvm::Value* typedPtr = builder->CreateBitCast(
                            heapPtr, llvm::PointerType::get(context, 0));
                        
                        builder->CreateStore(val, typedPtr);
                        
                        val = builder->CreateBitCast(typedPtr, destTy);
                    }
                }
                if (!val) {
                    val = emitExpr((*mret)->values[i]);
                }
                if (!val) return;
                llvm::Type* srcTy  = val->getType();
                llvm::Type* destTy = retStructTy->getElementType(i);
                for (auto& [unionName, unionTy] : unionTypes) {
                    if (srcTy == unionTy && !isUnionType(destTy)) {
                        llvm::Value* dataPtr = builder->CreateExtractValue(val, 1, "union_data");
                        if (destTy->isPointerTy()) {
                            val = builder->CreateBitCast(dataPtr, destTy);
                        } else {
                            llvm::Value* typedPtr = builder->CreateBitCast(
                                dataPtr,
                                llvm::PointerType::get(context, 0)
                            );
                            val = builder->CreateLoad(destTy, typedPtr);
                        }
                        srcTy = destTy;
                        break;
                    }
                    if (!isUnionType(srcTy) && destTy == unionTy) {
                        int tag = findUnionVariantTag(unionName, (*mret)->values[i], val);
                        if (tag == -1) {
                            cg_error((*mret)->pos, "Return value doesn't match union variant");
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
                            llvm::Value* typedPtr = builder->CreateBitCast(
                                dataPtr,
                                llvm::PointerType::get(context, 0)
                            );
                            val = builder->CreateLoad(destTy, typedPtr);
                        }
                        srcTy = destTy;
                        break;
                    }
                    if (!isEnumType(srcTy) && destTy == enumTy) {
                        int tag = findEnumVariantTag(enumName, (*mret)->values[i], val);
                        if (tag == -1) {
                            cg_error((*mret)->pos, "Return value doesn't match enum variant");
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
        }
        else if (auto ret = std::get_if<std::unique_ptr<ReturnNode>>(&node)) {
            if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&(*ret)->value)) {
                std::string name = (*varAccess)->var_name_tok.value;
                llvm::Value* alloc = resolveVariable(name);
                if (alloc) {
                    llvm::Type* allocatedTy = getPointeeType(alloc);
                    if (allocatedTy->isArrayTy()) {
                        llvm::Value* arrayPtr = builder->CreateBitCast(
                            alloc,
                            llvm::PointerType::get(context, 0),
                            "array_ret_ptr"
                        );
                        builder->CreateRet(arrayPtr);
                        return;
                    }
                }
            }
            if (auto call = std::get_if<std::unique_ptr<CallNode>>(&(*ret)->value)) {
                if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&(*call)->node_to_call)) {
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
            if (auto arrayLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&(*ret)->value)) {
                if (destTy->isPointerTy() && srcTy->isArrayTy()) {
                    llvm::ArrayType* arrayType = llvm::cast<llvm::ArrayType>(srcTy);
                    llvm::Type* i64Ty = builder->getInt64Ty();
                    llvm::Value* size = llvm::ConstantInt::get(i64Ty, module->getDataLayout().getTypeAllocSize(arrayType));
                    llvm::Function* mallocFn = module->getFunction("malloc");
                    if (!mallocFn) {
                        llvm::FunctionType* mallocTy = llvm::FunctionType::get(
                            builder->getPtrTy(), 
                            {i64Ty}, 
                            false
                        );
                        mallocFn = llvm::Function::Create(
                            mallocTy,
                            llvm::Function::ExternalLinkage,
                            "malloc",
                            module.get()
                        );
                    }
                    
                    llvm::Value* heapPtr = builder->CreateCall(mallocFn, {size});
                    llvm::Value* typedPtr = builder->CreateBitCast(
                        heapPtr, 
                        llvm::PointerType::get(context, 0)
                    );
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
                        llvm::Value* typedPtr = builder->CreateBitCast(
                            dataPtr,
                            llvm::PointerType::get(context, 0)
                        );
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
                        llvm::Value* typedPtr = builder->CreateBitCast(
                            dataPtr,
                            llvm::PointerType::get(context, 0)
                        );
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
        }
        else if (auto mv = std::get_if<std::unique_ptr<MultiVarDeclNode>>(&node)) {
            llvm::Value* callVal = emitExpr((*mv)->value);
            if (!callVal) {
                cg_error((*mv)->var_names[0].pos, "Failed to compile multi-var initializer");
                return;
            }

            llvm::Type* retTy = callVal->getType();
            if (!retTy->isStructTy() || retTy->getStructNumElements() != (*mv)->var_names.size()) {
                cg_error((*mv)->var_names[0].pos, "Multi-return arity/type mismatch");
                return;
            }

            for (size_t i = 0; i < (*mv)->var_names.size(); ++i) {
                llvm::Value* field = builder->CreateExtractValue(callVal, i);
                std::string name = (*mv)->var_names[i].value;
                std::string typeStr = (*mv)->type_toks[i].value;
                if (typeStr.find("[]") != std::string::npos) {
                    std::string baseType = typeStr;
                    while (baseType.ends_with("[]")) {
                        baseType = baseType.substr(0, baseType.length() - 2);
                    }
                    arrayTypeStrings[name] = baseType;
                }
                llvm::Type* srcTy  = field->getType();
                llvm::Type* destTy = llvmTypeFor(typeStr);
                for (auto& [unionName, unionTy] : unionTypes) {
                    if (srcTy == unionTy && !isUnionType(destTy)) {
                        llvm::Value* dataPtr = builder->CreateExtractValue(field, 1, "union_data");
                        if (destTy->isPointerTy()) {
                            field = builder->CreateBitCast(dataPtr, destTy);
                        } else {
                            llvm::Value* typedPtr = builder->CreateBitCast(
                                dataPtr,
                                llvm::PointerType::get(context, 0)
                            );
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
                            llvm::Value* typedPtr = builder->CreateBitCast(
                                dataPtr,
                                llvm::PointerType::get(context, 0)
                            );
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
        }
        else if (auto if_node = std::get_if<std::unique_ptr<IfNode>>(&node)) {
            enterScope();
            if ((*if_node)->init.has_value()) {
                emitStmt((*if_node)->init.value());
            }
            llvm::Value* cond = emitExpr((*if_node)->condition);
            if (!cond) return;
            for (auto& [enumName, enumTy] : enumTypes) {
                if (cond->getType() == enumTy) {
                    llvm::Value* dataPtr = builder->CreateExtractValue(cond, 1);
                    
                    llvm::Type* targetTy = builder->getInt1Ty();
                    
                    llvm::Value* typedPtr = builder->CreateBitCast(
                        dataPtr, 
                        llvm::PointerType::get(context, 0)
                    );
                    cond = builder->CreateLoad(targetTy, typedPtr);
                    break;
                }
            }
            cond = normalizeValue(cond, (*if_node)->condition);
            cond = toTruthiness(cond, Position("", "", 0, 0, 0));
            if (!cond) return;
            llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(context, "then", currentFunction);
            llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(context, "ifcont", currentFunction);
            std::vector<std::pair<llvm::BasicBlock*, llvm::BasicBlock*>> elifBlocks;
            for (size_t i = 0; i < (*if_node)->elif_branches.size(); i++) {
                llvm::BasicBlock* elifCondBB = llvm::BasicBlock::Create(context, "elif.cond", currentFunction);
                llvm::BasicBlock* elifBodyBB = llvm::BasicBlock::Create(context, "elif.body", currentFunction);
                elifBlocks.push_back({elifCondBB, elifBodyBB});
            }
            
            llvm::BasicBlock* elseBB = nullptr;
            if ((*if_node)->else_branch) {
                elseBB = llvm::BasicBlock::Create(context, "else", currentFunction);
            }
            llvm::BasicBlock* nextBB = elifBlocks.empty() 
                ? (elseBB ? elseBB : mergeBB)
                : elifBlocks[0].first;
            builder->CreateCondBr(cond, thenBB, nextBB);
            builder->SetInsertPoint(thenBB);
            for (auto& stmt : (*if_node)->then_branch->statements) {
                emitStmt(stmt);
            }
            if (!builder->GetInsertBlock()->getTerminator()) {
                builder->CreateBr(mergeBB);
            }
            for (size_t i = 0; i < elifBlocks.size(); i++) {
                builder->SetInsertPoint(elifBlocks[i].first);
                llvm::Value* elifCond = emitExpr((*if_node)->elif_branches[i].first);
                
                llvm::BasicBlock* nextElifBB = (i + 1 < elifBlocks.size())
                    ? elifBlocks[i + 1].first
                    : (elseBB ? elseBB : mergeBB);
                builder->CreateCondBr(elifCond, elifBlocks[i].second, nextElifBB);
                
                builder->SetInsertPoint(elifBlocks[i].second);
                for (auto& stmt : (*if_node)->elif_branches[i].second->statements) {
                    emitStmt(stmt);
                }
                if (!builder->GetInsertBlock()->getTerminator()) {
                    builder->CreateBr(mergeBB);
                }
            }
            if (elseBB) {
                builder->SetInsertPoint(elseBB);
                for (auto& stmt : (*if_node)->else_branch->statements) {
                    emitStmt(stmt);
                }
                if (!builder->GetInsertBlock()->getTerminator()) {
                    builder->CreateBr(mergeBB);
                }
            }
            exitScope();
            builder->SetInsertPoint(mergeBB);
        }
        else if (auto while_node = std::get_if<std::unique_ptr<WhileNode>>(&node)) {
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
            llvm::Value* cond = emitExpr((*while_node)->condition);
            if (!cond) return;
            for (auto& [enumName, enumTy] : enumTypes) {
                if (cond->getType() == enumTy) {
                    llvm::Value* dataPtr = builder->CreateExtractValue(cond, 1);
                    llvm::Type* targetTy = builder->getInt1Ty();
                    
                    llvm::Value* typedPtr = builder->CreateBitCast(
                        dataPtr, 
                        llvm::PointerType::get(context, 0)
                    );
                    cond = builder->CreateLoad(targetTy, typedPtr);
                    break;
                }
            }
            cond = normalizeValue(cond, (*while_node)->condition);
            cond = toTruthiness(cond, Position("", "", 0, 0, 0));
            if (!cond) return;
            builder->CreateCondBr(cond, bodyBB, endBB);
            builder->SetInsertPoint(bodyBB);
            for (auto& stmt : (*while_node)->body->statements) {
                emitStmt(stmt);
            }
            if (!builder->GetInsertBlock()->getTerminator()) {
                builder->CreateBr(condBB);
            }
            currentBreakBB = oldBreakBB;
            currentContinueBB = oldContinueBB;
            exitScope();
            builder->SetInsertPoint(endBB);
        }
        else if (std::holds_alternative<std::unique_ptr<BreakNode>>(node)) {
            if (currentBreakBB) {
                builder->CreateBr(currentBreakBB);
            } else {
                cg_error(Position(), "break outside of loop/switch");
            }
        }
        else if (std::holds_alternative<std::unique_ptr<ContinueNode>>(node)) {
            if (currentContinueBB) {
                builder->CreateBr(currentContinueBB);
            } else {
                cg_error(Position(), "continue outside of loop");
            }
        }
        else if (auto for_node = std::get_if<std::unique_ptr<ForNode>>(&node)) {
            enterScope();
            if ((*for_node)->init.has_value()) {
                emitStmt((*for_node)->init.value());
            }
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
            llvm::Value* cond = emitExpr((*for_node)->condition);
            if (!cond) return;
            for (auto& [enumName, enumTy] : enumTypes) {
                if (cond->getType() == enumTy) {
                    llvm::Value* dataPtr = builder->CreateExtractValue(cond, 1);
                    llvm::Type* targetTy = builder->getInt1Ty();
                    
                    llvm::Value* typedPtr = builder->CreateBitCast(
                        dataPtr, 
                        llvm::PointerType::get(context, 0)
                    );
                    cond = builder->CreateLoad(targetTy, typedPtr);
                    break;
                }
            }
            cond = normalizeValue(cond, (*for_node)->condition);
            cond = toTruthiness(cond, Position("", "", 0, 0, 0));
            if (!cond) return;
            builder->CreateCondBr(cond, bodyBB, endBB);
            builder->SetInsertPoint(bodyBB);
            for (auto& stmt : (*for_node)->body->statements) {
                emitStmt(stmt);
            }
            if (!builder->GetInsertBlock()->getTerminator()) {
                builder->CreateBr(incBB);
            }
            builder->SetInsertPoint(incBB);
            if ((*for_node)->update.has_value()) {
                emitStmt((*for_node)->update.value());
            }
            builder->CreateBr(condBB);
            currentBreakBB = oldBreakBB;
            currentContinueBB = oldContinueBB;
            exitScope();
            builder->SetInsertPoint(endBB);
        }
        else if (auto switch_node = std::get_if<std::unique_ptr<SwitchNode>>(&node)) {
            enterScope();
            llvm::Value* switchVal = emitExpr((*switch_node)->value);
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
            
            for (auto& section : (*switch_node)->sections) {
                llvm::BasicBlock* bb = llvm::BasicBlock::Create(context, "switch.case", currentFunction);
                sectionBlocks.push_back(bb);
                if (section.is_default) {
                    defaultBB = bb;
                }
            }
            
            if (!defaultBB) {
                defaultBB = endBB;
            }
            
            if (canUseSwitch) {
                llvm::SwitchInst* switchInst = builder->CreateSwitch(switchVal, defaultBB, (*switch_node)->sections.size());
                
                for (size_t i = 0; i < (*switch_node)->sections.size(); i++) {
                    auto& section = (*switch_node)->sections[i];
                    if (section.is_default) continue;
                    
                    for (auto& caseLabel : section.cases) {
                        llvm::Value* caseVal = emitExpr(caseLabel.expr);
                        if (auto constInt = llvm::dyn_cast<llvm::ConstantInt>(caseVal)) {
                            switchInst->addCase(constInt, sectionBlocks[i]);
                        }
                    }
                }
            }
            else {
                llvm::BasicBlock* currentCheckBB = builder->GetInsertBlock();
                
                for (size_t i = 0; i < (*switch_node)->sections.size(); i++) {
                    auto& section = (*switch_node)->sections[i];
                    
                    if (section.is_default) {
                        continue;
                    }
                    llvm::BasicBlock* nextCheckBB = (i + 1 < (*switch_node)->sections.size()) 
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
                        }
                        else if (switchTy->isIntegerTy()) {
                            cmp = builder->CreateICmpEQ(switchVal, caseVal);
                        }
                        else if (switchTy->isFloatingPointTy()) {
                            cmp = builder->CreateFCmpOEQ(switchVal, caseVal);
                        }
                        else {
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
            
            for (size_t i = 0; i < (*switch_node)->sections.size(); i++) {
                builder->SetInsertPoint(sectionBlocks[i]);
                
                for (auto& stmt : (*switch_node)->sections[i].body->statements) {
                    emitStmt(stmt);
                }
                
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
        }
        else if (auto qif_node = std::get_if<std::unique_ptr<QIfNode>>(&node)) {
            enterScope();
            if ((*qif_node)->init.has_value()) {
                emitStmt((*qif_node)->init.value());
            }
            llvm::BasicBlock* endBB = llvm::BasicBlock::Create(context, "qif.end", currentFunction);
            
            llvm::Value* qifCond = emitExpr((*qif_node)->condition);
            for (auto& [enumName, enumTy] : enumTypes) {
                if (qifCond->getType() == enumTy) {
                    llvm::Value* dataPtr = builder->CreateExtractValue(qifCond, 1);
                    llvm::Type* targetTy = builder->getIntNTy(2);
                    
                    llvm::Value* typedPtr = builder->CreateBitCast(
                        dataPtr, 
                        llvm::PointerType::get(context, 0)
                    );
                    qifCond = builder->CreateLoad(targetTy, typedPtr);
                    break;
                }
            }
            qifCond = normalizeValue(qifCond, (*qif_node)->condition);
            llvm::Value* qifBit1 = builder->CreateAnd(qifCond, builder->getIntN(2, 0b10));
            llvm::Value* qif_is_true = builder->CreateICmpNE(qifBit1, builder->getIntN(2, 0));
            
            llvm::BasicBlock* qifBodyBB = llvm::BasicBlock::Create(context, "qif.body", currentFunction);
            llvm::BasicBlock* nextBB = ((*qif_node)->qelif_branches.empty() && !(*qif_node)->qelse_branch)
                ? endBB
                : llvm::BasicBlock::Create(context, "qelif.check", currentFunction);
            
            builder->CreateCondBr(qif_is_true, qifBodyBB, nextBB);
            
            builder->SetInsertPoint(qifBodyBB);
            for (auto& stmt : (*qif_node)->then_branch->statements) {
                emitStmt(stmt);
            }
            if (!builder->GetInsertBlock()->getTerminator()) {
                builder->CreateBr(endBB);
            }
            
            for (size_t i = 0; i < (*qif_node)->qelif_branches.size(); i++) {
                builder->SetInsertPoint(nextBB);
                
                llvm::Value* elifCond = emitExpr((*qif_node)->qelif_branches[i].first);
                llvm::Value* elifBit1 = builder->CreateAnd(elifCond, builder->getIntN(2, 0b10));
                llvm::Value* elif_is_true = builder->CreateICmpNE(elifBit1, builder->getIntN(2, 0));
                
                llvm::BasicBlock* elifBodyBB = llvm::BasicBlock::Create(context, "qelif.body", currentFunction);
                llvm::BasicBlock* nextElifBB = (i + 1 < (*qif_node)->qelif_branches.size() || (*qif_node)->qelse_branch)
                    ? llvm::BasicBlock::Create(context, "qelif.check", currentFunction)
                    : endBB;
                
                builder->CreateCondBr(elif_is_true, elifBodyBB, nextElifBB);
                
                builder->SetInsertPoint(elifBodyBB);
                for (auto& stmt : (*qif_node)->qelif_branches[i].second->statements) {
                    emitStmt(stmt);
                }
                if (!builder->GetInsertBlock()->getTerminator()) {
                    builder->CreateBr(endBB);
                }
                
                nextBB = nextElifBB;
            }
            
            if ((*qif_node)->qelse_branch) {
                builder->SetInsertPoint(nextBB);
                llvm::Value* qifBit0 = builder->CreateAnd(qifCond, builder->getIntN(2, 0b01));
                llvm::Value* all_false = builder->CreateICmpNE(qifBit0, builder->getIntN(2, 0));
                for (auto& qelif : (*qif_node)->qelif_branches) {
                    llvm::Value* elifCond = emitExpr(qelif.first);
                    llvm::Value* elifBit0 = builder->CreateAnd(elifCond, builder->getIntN(2, 0b01));
                    llvm::Value* elif_false = builder->CreateICmpNE(elifBit0, builder->getIntN(2, 0));
                    all_false = builder->CreateAnd(all_false, elif_false);
                }
                
                llvm::BasicBlock* qelseBodyBB = llvm::BasicBlock::Create(context, "qelse.body", currentFunction);
                builder->CreateCondBr(all_false, qelseBodyBB, endBB);
                
                builder->SetInsertPoint(qelseBodyBB);
                for (auto& stmt : (*qif_node)->qelse_branch->statements) {
                    emitStmt(stmt);
                }
                if (!builder->GetInsertBlock()->getTerminator()) {
                    builder->CreateBr(endBB);
                }
            }
            exitScope();
            builder->SetInsertPoint(endBB);
        }
        else if (auto qsw = std::get_if<std::unique_ptr<QSwitchNode>>(&node)) {
            enterScope();
            llvm::Value* qb_val = emitExpr((*qsw)->value);
            if (!qb_val) {
                cg_error(Position("", "", 0, 0, 0), "Failed to compile qswitch value");
                return;
            }
            for (auto& [enumName, enumTy] : enumTypes) {
                if (qb_val->getType() == enumTy) {
                    llvm::Value* dataPtr = builder->CreateExtractValue(qb_val, 1);
                    llvm::Type* targetTy = builder->getIntNTy(2);
                    
                    llvm::Value* typedPtr = builder->CreateBitCast(
                        dataPtr, 
                        llvm::PointerType::get(context, 0)
                    );
                    qb_val = builder->CreateLoad(targetTy, typedPtr);
                    break;
                }
            }
            qb_val = normalizeValue(qb_val, (*qsw)->value);
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
            if ((*qsw)->case_t) {
                case_t_block = llvm::BasicBlock::Create(context, "qsw.case_t", currentFunction);
            }
            if ((*qsw)->case_f) {
                case_f_block = llvm::BasicBlock::Create(context, "qsw.case_f", currentFunction);
            }
            if ((*qsw)->case_n) {
                case_n_block = llvm::BasicBlock::Create(context, "qsw.case_n", currentFunction);
            }
            if ((*qsw)->case_b) {
                case_b_block = llvm::BasicBlock::Create(context, "qsw.case_b", currentFunction);
            }
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
            builder->CreateCondBr(is_both, 
                                case_b_block ? case_b_block : qswitch_end, 
                                check_qtrue);
            builder->SetInsertPoint(check_qtrue);
            builder->CreateCondBr(is_qtrue_only, 
                                case_t_block ? case_t_block : qswitch_end, 
                                check_qfalse);
            builder->SetInsertPoint(check_qfalse);
            builder->CreateCondBr(is_qfalse_only, 
                                case_f_block ? case_f_block : qswitch_end, 
                                check_none_final);
            builder->SetInsertPoint(check_none_final);
            builder->CreateCondBr(is_none, 
                                case_n_block ? case_n_block : qswitch_end, 
                                qswitch_end);
            if (case_t_block && (*qsw)->case_t) {
                builder->SetInsertPoint(case_t_block);
                for (auto& stmt : (*qsw)->case_t->statements) {
                    emitStmt(stmt);
                }
                if (!builder->GetInsertBlock()->getTerminator()) {
                    builder->CreateBr(qswitch_end);
                }
            }
            
            if (case_f_block && (*qsw)->case_f) {
                builder->SetInsertPoint(case_f_block);
                for (auto& stmt : (*qsw)->case_f->statements) {
                    emitStmt(stmt);
                }
                if (!builder->GetInsertBlock()->getTerminator()) {
                    builder->CreateBr(qswitch_end);
                }
            }
            
            if (case_n_block && (*qsw)->case_n) {
                builder->SetInsertPoint(case_n_block);
                for (auto& stmt : (*qsw)->case_n->statements) {
                    emitStmt(stmt);
                }
                if (!builder->GetInsertBlock()->getTerminator()) {
                    builder->CreateBr(qswitch_end);
                }
            }
            if (case_b_block && (*qsw)->case_b) {
                builder->SetInsertPoint(case_b_block);
                for (auto& stmt : (*qsw)->case_b->statements) {
                    emitStmt(stmt);
                }
                if (!builder->GetInsertBlock()->getTerminator()) {
                    builder->CreateBr(qswitch_end);
                }
            }
            exitScope();
            builder->SetInsertPoint(qswitch_end);
        }
        else if (auto arrDecl = std::get_if<std::unique_ptr<ArrayDeclNode>>(&node)) {
            std::string name = (*arrDecl)->var_name_tok.value;
            std::string elemType = (*arrDecl)->type_tok.value;
            arrayTypeStrings[name] = elemType;
            llvm::Type* elemTy = llvmTypeFor(elemType);
            if (!std::holds_alternative<std::unique_ptr<ArrayLiteralNode>>((*arrDecl)->value) &&
                !std::holds_alternative<std::monostate>((*arrDecl)->value)) {
                
                llvm::Value* arrPtr = emitExpr((*arrDecl)->value);
                if (!arrPtr) return;
                
                llvm::AllocaInst* alloc = createEntryAlloca(name, arrPtr->getType());
                builder->CreateStore(arrPtr, alloc);
                locals[name] = alloc;
                
                return;
            }
            if (auto arrLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&(*arrDecl)->value)) {
                bool hasSpread = false;
                for (auto& elem : (*arrLit)->elements) {
                    if (std::holds_alternative<std::unique_ptr<SpreadNode>>(elem)) {
                        hasSpread = true;
                        break;
                    }
                }
                
                if (hasSpread) {
                    llvm::Value* arrPtr = emitExpr((*arrDecl)->value);
                    if (!arrPtr) return;
                    llvm::Value* totalSize = builder->getInt32(0);
                    if (auto arrLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&(*arrDecl)->value)) {
                        for (auto& elem : (*arrLit)->elements) {
                            if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&elem)) {
                                llvm::Value* collVal   = emitExpr((*spread)->expr);
                                llvm::Value* spreadLen = getCollectionLength(collVal, (*spread)->expr);
                                totalSize = builder->CreateAdd(totalSize, spreadLen);
                            } else {
                                totalSize = builder->CreateAdd(totalSize, builder->getInt32(1));
                            }
                        }
                    }

                    if (!(*arrDecl)->sizes.empty() && (*arrDecl)->sizes[0].has_value()) {
                        int userSize = *(*arrDecl)->sizes[0];
                        arrayLengths[name] = userSize;
                    } else if (auto* constSize = llvm::dyn_cast<llvm::ConstantInt>(totalSize)) {
                        arrayLengths[name] = constSize->getSExtValue();
                    } else {
                        llvm::AllocaInst* sizeAlloc =
                            createEntryAlloca(name + "_size", builder->getInt32Ty());
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
                auto [isJagged, depth] = checkJagged((*arrDecl)->value);
                size_t arraySize = (*arrLit)->elements.size();
                arrayLengths[name] = arraySize;
                if (isJagged) {
                    int elemTypeCode = -1;
                    if (elemType == "int") elemTypeCode = 0;
                    else if (elemType == "float") elemTypeCode = 1;
                    else if (elemType == "double") elemTypeCode = 2;
                    else if (elemType == "char") elemTypeCode = 3;
                    else if (elemType == "bool") elemTypeCode = 4;
                    else if (elemType == "qbool") elemTypeCode = 5;
                    else if (elemType == "string") elemTypeCode = 6;
                    
                    llvm::Value* jaggedArr = createJaggedArray((*arrDecl)->value, elemTypeCode, depth - 1);
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
                    if (auto lit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&node)) {
                        if (actualSizes.size() <= depth) {
                            actualSizes.push_back((*lit)->elements.size());
                        }
                        if (!(*lit)->elements.empty()) {
                            inferDims((*lit)->elements[0], depth + 1);
                        }
                    }
                };
                
                inferDims((*arrDecl)->value, 0);
                llvm::Type* arrTy = elemTy;
                for (int i = actualSizes.size() - 1; i >= 0; i--) {     
                    arrTy = llvm::ArrayType::get(arrTy, actualSizes[i]);
                }
                
                bool useHeap = (currentFunction != nullptr);

                llvm::AllocaInst* alloc;
                if (useHeap) {
                    llvm::Function* mallocFn = module->getFunction("malloc");
                    if (!mallocFn) {
                        llvm::FunctionType* mallocTy = llvm::FunctionType::get(
                            llvm::PointerType::get(context, 0),
                            {builder->getInt64Ty()},
                            false
                        );
                        mallocFn = llvm::Function::Create(mallocTy, llvm::Function::ExternalLinkage, "malloc", module.get());
                    }
                    
                    const llvm::DataLayout &DL = module->getDataLayout();
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
                    if (auto lit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&node)) {
                        for (size_t i = 0; i < (*lit)->elements.size(); i++) {
                            indices.push_back(i);
                            
                            if (std::holds_alternative<std::unique_ptr<ArrayLiteralNode>>((*lit)->elements[i])) {
                                initArray(ptr, ty, (*lit)->elements[i], indices);
                            } else {
                                llvm::Value* elemVal = emitExpr((*lit)->elements[i]);
                                if (!elemVal) return;
                                
                                std::vector<llvm::Value*> llvmIndices = useHeap 
                                    ? std::vector<llvm::Value*>{builder->getInt32(0)}
                                    : std::vector<llvm::Value*>{builder->getInt32(0)};
                                    
                                for (auto idx : indices) {
                                    llvmIndices.push_back(builder->getInt32(idx));
                                }
                                
                                llvm::Value* basePtr = useHeap 
                                    ? builder->CreateLoad(llvm::PointerType::get(context, 0), alloc, "heap_ptr")
                                    : static_cast<llvm::Value*>(alloc);
                                
                                llvm::Value* elemPtr = builder->CreateInBoundsGEP(arrTy, basePtr, llvmIndices);
                                builder->CreateStore(elemVal, elemPtr);
                            }
                            
                            indices.pop_back();
                        }
                    }
                };

                std::vector<uint64_t> indices;
                initArray(alloc, arrTy, (*arrDecl)->value, indices);
            }
            if (!(*arrDecl)->sizes.empty() && (*arrDecl)->sizes[0].has_value()) {
                int arraySize = *(*arrDecl)->sizes[0];
                if (std::holds_alternative<std::monostate>((*arrDecl)->value)) {
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
        }
        else if (auto arrAssign = std::get_if<std::unique_ptr<ArrayAssignNode>>(&node)) {
            
            if (auto arrAcc = std::get_if<std::unique_ptr<ArrayAccessNode>>(&(*arrAssign)->array_access)) {
                if (auto varAcc = std::get_if<std::unique_ptr<VarAccessNode>>(&(*arrAcc)->base)) {
                    std::string name = (*varAcc)->var_name_tok.value;
                    if (hasJaggedArray(name)) {
                        auto jagIt = findJaggedArray(name);
                        auto it = locals.find(name);
                        if (it == locals.end()) {
                            cg_error(Position(), "Unknown jagged array: " + name);
                            return;
                        }
                        
                        llvm::Value* jaggedPtr = builder->CreateLoad(
                            llvm::PointerType::get(context, 0),
                            it->second,
                            "jagged_ptr"
                        );
                        llvm::ArrayType* indicesArrTy = llvm::ArrayType::get(
                            builder->getInt32Ty(), 
                            (*arrAcc)->indices.size()
                        );
                        llvm::AllocaInst* indicesAlloc = createEntryAlloca("indices_arr", indicesArrTy);
                        
                        for (size_t i = 0; i < (*arrAcc)->indices.size(); i++) {
                            llvm::Value* indexVal = emitExpr((*arrAcc)->indices[i]);
                            if (!indexVal) return;
                            
                            std::vector<llvm::Value*> indices = {builder->getInt32(0), builder->getInt32(i)};
                            llvm::Value* idxPtr = builder->CreateInBoundsGEP(indicesArrTy, indicesAlloc, indices);
                            builder->CreateStore(indexVal, idxPtr);
                        }
                        
                        llvm::Function* getFn = module->getFunction("qc_jagged_array_get");
                        if (!getFn) {
                            llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                            llvm::Type* intPtrTy = llvm::PointerType::get(context, 0);
                            llvm::FunctionType* fnTy = llvm::FunctionType::get(
                                voidPtrTy,
                                {voidPtrTy, intPtrTy, builder->getInt32Ty()},
                                false
                            );
                            getFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                        "qc_jagged_array_get", module.get());
                        }
                        
                        std::vector<llvm::Value*> idxIndices = {builder->getInt32(0), builder->getInt32(0)};
                        llvm::Value* indicesPtr = builder->CreateInBoundsGEP(indicesArrTy, indicesAlloc, idxIndices);
                        
                        llvm::Value* elemPtr = builder->CreateCall(getFn, {
                            jaggedPtr,
                            indicesPtr,
                            builder->getInt32((*arrAcc)->indices.size())
                        }, "jagged_elem_ptr");
                        
                        llvm::Value* valueVal = emitExpr((*arrAssign)->value);
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
                        
                        llvm::Value* mapPtr = builder->CreateLoad(
                            llvm::PointerType::get(context, 0),
                            it->second,
                            "map_ptr"
                        );
                        
                        llvm::Value* keyVal = emitExpr((*arrAcc)->indices[0]);
                        llvm::Value* valueVal = emitExpr((*arrAssign)->value);
                        if (!keyVal || !valueVal) return;

                        llvm::Value* keyPtr;
                        if (keyVal->getType()->isPointerTy()) {
                            keyPtr = keyVal;
                        } else {
                            llvm::AllocaInst* keyAlloc = createEntryAlloca("map_key", keyVal->getType());
                            builder->CreateStore(keyVal, keyAlloc);
                            keyPtr = builder->CreateBitCast(keyAlloc, 
                                                        llvm::PointerType::get(context, 0));
                        }

                        llvm::Value* valPtr;
                        if (valueVal->getType()->isPointerTy()) {
                            valPtr = valueVal;
                        } else {
                            llvm::AllocaInst* valAlloc = createEntryAlloca("map_val", valueVal->getType());
                            builder->CreateStore(valueVal, valAlloc);
                            valPtr = builder->CreateBitCast(valAlloc, 
                                                        llvm::PointerType::get(context, 0));
                        }
                        llvm::Function* setFn = module->getFunction("qc_map_set");
                        if (!setFn) {
                            llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                            llvm::FunctionType* fnTy = llvm::FunctionType::get(
                                builder->getVoidTy(),
                                {voidPtrTy, voidPtrTy, voidPtrTy},
                                false
                            );
                            setFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                        "qc_map_set", module.get());
                        }
                        
                        builder->CreateCall(setFn, {mapPtr, keyPtr, valPtr});
                        return;
                    }
                    if (hasList(name)) {
                        auto listIt = findList(name);
                        llvm::Value* alloc = resolveVariable(name);
                        if (!alloc) {
                            cg_error(Position(), "Unknown list: " + name);
                            return;
                        }
                        
                        llvm::Value* listPtr = builder->CreateLoad(
                            llvm::PointerType::get(context, 0),
                            alloc,
                            "list_ptr"
                        );
                        
                        llvm::Value* indexVal = emitExpr((*arrAcc)->indices[0]);
                        if (!indexVal) return;
                        
                        llvm::Value* valueVal = emitExpr((*arrAssign)->value);
                        if (!valueVal) return;
                        
                        llvm::AllocaInst* valAlloc = createEntryAlloca("list_set_val", valueVal->getType());
                        builder->CreateStore(valueVal, valAlloc);
                        llvm::Value* valPtr = builder->CreateBitCast(valAlloc, llvm::PointerType::get(context, 0));
                        
                        llvm::Function* setFn = module->getFunction("qc_list_set");
                        if (!setFn) {
                            llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                            llvm::FunctionType* fnTy = llvm::FunctionType::get(
                                builder->getVoidTy(),
                                {voidPtrTy, builder->getInt32Ty(), voidPtrTy},
                                false
                            );
                            setFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                            "qc_list_set", module.get());
                        }
                        
                        builder->CreateCall(setFn, {listPtr, indexVal, valPtr});
                        return;
                    }
                    llvm::Value* alloc = resolveVariable(name);
                    if (!alloc) {
                        cg_error(Position(), "Unknown array: " + name);
                        return;
                    }
                    
                    llvm::Value* arrAlloc = alloc;
                    llvm::Type* arrTy = getPointeeType(arrAlloc);
                    
                    llvm::Value* indexVal = emitExpr((*arrAcc)->indices[0]);
                    if (!indexVal) return;
                    
                    llvm::Value* valueVal = emitExpr((*arrAssign)->value);
                    if (!valueVal) return;
                    if (arrTy->isPointerTy()) {
                        llvm::Value* ptr = builder->CreateLoad(arrTy, arrAlloc, "arr_ptr");
                        llvm::Type* elemTy = valueVal->getType();
                        
                        llvm::Value* elemPtr = builder->CreateGEP(
                            elemTy,
                            ptr,
                            indexVal,
                            "arr_elem_ptr"
                        );
                        
                        builder->CreateStore(valueVal, elemPtr);
                    } else if (arrTy->isArrayTy()) {
                        std::vector<llvm::Value*> indices = {
                            builder->getInt32(0),
                            indexVal
                        };
                        llvm::Value* elemPtr = builder->CreateInBoundsGEP(
                            arrTy,
                            arrAlloc,
                            indices,
                            "arr_elem_ptr"
                        );
                        
                        builder->CreateStore(valueVal, elemPtr);
                    }
                }
            }
            
            return;
        }
        else if (auto listDecl = std::get_if<std::unique_ptr<ListDeclNode>>(&node)) {
            std::string name = (*listDecl)->var_name_tok.value;
            std::string typeStr = (*listDecl)->type_tok.value;
            size_t start = typeStr.find('<');
            size_t end = typeStr.find('>');
            std::string elemType = typeStr.substr(start + 1, end - start - 1);
            
            int elemTypeCode = -1;
            if (elemType == "int") elemTypeCode = 0;
            else if (elemType == "float") elemTypeCode = 1;
            else if (elemType == "double") elemTypeCode = 2;
            else if (elemType == "char") elemTypeCode = 3;
            else if (elemType == "bool") elemTypeCode = 4;
            else if (elemType == "qbool") elemTypeCode = 5;
            else if (elemType == "string") elemTypeCode = 6;
            llvm::Function* createFn = module->getFunction("qc_create_list");
            if (!createFn) {
                llvm::Type* ptrTy = llvm::PointerType::get(context, 0);
                llvm::FunctionType* fnTy = llvm::FunctionType::get(
                    ptrTy,
                    {builder->getInt32Ty()},
                    false
                );
                createFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                "qc_create_list", module.get());
            }
            
            llvm::Value* listPtr = builder->CreateCall(createFn, {builder->getInt32(elemTypeCode)}, "list_ptr");
            if (auto callNode = std::get_if<std::unique_ptr<CallNode>>(&(*listDecl)->value)) {
                listPtr = emitExpr((*listDecl)->value);
                if (!listPtr) return;
            }
            else if (auto arrLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&(*listDecl)->value)) {
                llvm::Function* pushFn = module->getFunction("qc_list_push");
                if (!pushFn) {
                    llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(
                        builder->getVoidTy(),
                        {voidPtrTy, voidPtrTy},
                        false
                    );
                    pushFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                "qc_list_push", module.get());
                }
                
                for (auto& elem : (*arrLit)->elements) {
                    if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&elem)) {
                        llvm::Value* collVal = emitExpr((*spread)->expr);
                        expandSpreadIntoList(collVal, (*spread)->expr, listPtr, pushFn, elemTypeCode);
                    } else {
                        llvm::Value* elemVal = emitExpr(elem);
                        if (!elemVal) continue;
                        
                        llvm::AllocaInst* tempAlloc = createEntryAlloca("temp_elem", elemVal->getType());
                        builder->CreateStore(elemVal, tempAlloc);
                        
                        llvm::Value* elemPtr = builder->CreateBitCast(tempAlloc, 
                                                                    llvm::PointerType::get(context, 0));
                        
                        builder->CreateCall(pushFn, {listPtr, elemPtr, builder->getInt32(elemTypeCode)});
                    }
                }
            }
            else if (auto methodCall = std::get_if<std::unique_ptr<MethodCallNode>>(&(*listDecl)->value)) {
                listPtr = emitExpr((*listDecl)->value);
                if (!listPtr) return;
            }
            else {
                listPtr = emitExpr((*listDecl)->value);
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

        else if (auto foreach = std::get_if<std::unique_ptr<ForeachNode>>(&node)) {
            std::string elemName = (*foreach)->elem_name.value;
            std::string iterName = "__foreach_i_" + elemName;
            
            llvm::Value* collVal = emitExpr((*foreach)->collection);
            if (!collVal) return;
            
            llvm::Value* lengthVal = nullptr;
            bool isArray = false;
            llvm::Value* arrayAlloc = nullptr;
            llvm::Type* arrayElemTy = nullptr;
            
            if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&(*foreach)->collection)) {
                std::string collName = (*varAccess)->var_name_tok.value;
                
                llvm::Value* alloc = resolveVariable(collName);
                if (alloc) {
                    llvm::Type* allocTy = getPointeeType(alloc);
                    
                    if (allocTy->isArrayTy()) {
                        isArray = true;
                        arrayAlloc = alloc;
                        lengthVal = builder->getInt32(allocTy->getArrayNumElements());
                    }
                    else if (allocTy->isPointerTy()) {
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
                    llvm::FunctionType* ty = llvm::FunctionType::get(
                        builder->getInt32Ty(),
                        { llvm::PointerType::get(context, 0) },
                        false
                    );
                    lenFn = llvm::Function::Create(
                        ty,
                        llvm::Function::ExternalLinkage,
                        "qc_list_length",
                        module.get()
                    );
                }
                lengthVal = builder->CreateCall(lenFn, { collVal }, "coll_len");
            }
            enterScope();
            llvm::Type* elemTy = llvmTypeFor((*foreach)->elem_type.value);
            llvm::AllocaInst* iterAlloc = createEntryAlloca(iterName, builder->getInt32Ty());
            llvm::AllocaInst* elemAlloc = createEntryAlloca(elemName, elemTy);
            
            locals[iterName] = iterAlloc;
            locals[elemName] = elemAlloc;
            
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
                llvm::Type* allocTy = getPointeeType(arrayAlloc);
                
                if (allocTy->isArrayTy()) {
                    std::vector<llvm::Value*> indices = { builder->getInt32(0), iVal };
                    llvm::Value* elemPtr = builder->CreateInBoundsGEP(
                        allocTy,
                        arrayAlloc,
                        indices,
                        "elem_ptr"
                    );
                    elemVal = builder->CreateLoad(elemTy, elemPtr, "elem");
                } else if (allocTy->isPointerTy() && arrayElemTy) {
                    llvm::Value* heapPtr = builder->CreateLoad(allocTy, arrayAlloc, "heap_ptr");
                    llvm::Value* elemPtr = builder->CreateGEP(
                        arrayElemTy,
                        heapPtr,
                        iVal,
                        "heap_elem_ptr"
                    );
                    
                    elemVal = builder->CreateLoad(elemTy, elemPtr, "elem");
                }
            } else {
                llvm::Function* getFn = module->getFunction("qc_list_get");
                if (!getFn) {
                    llvm::FunctionType* ty = llvm::FunctionType::get(
                        llvm::PointerType::get(context, 0),
                        { 
                            llvm::PointerType::get(context, 0),
                            builder->getInt32Ty()
                        },
                        false
                    );
                    getFn = llvm::Function::Create(
                        ty,
                        llvm::Function::ExternalLinkage,
                        "qc_list_get",
                        module.get()
                    );
                }
                llvm::Value* elemPtr = builder->CreateCall(getFn, { collVal, iVal }, "elem_ptr");
                if ((*foreach)->elem_type.value == "string") {
                    elemVal = elemPtr;
                } else {
                    llvm::Value* typedPtr = builder->CreateBitCast(
                        elemPtr,
                        llvm::PointerType::get(context, 0)
                    );
                    elemVal = builder->CreateLoad(elemTy, typedPtr, "elem");
                }
            }
            
            builder->CreateStore(elemVal, elemAlloc);
            
            emitStmt((*foreach)->body);
            
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
        }
        else if (auto stmts = std::get_if<std::unique_ptr<StatementsNode>>(&node)) {
            for (auto& stmt : (*stmts)->statements) {
                emitStmt(stmt);
            }
            return;
        }
        
        else if (auto mapDecl = std::get_if<std::unique_ptr<MapDeclNode>>(&node)) {
            std::string name = (*mapDecl)->var_name.value;
            std::string keyType = (*mapDecl)->key_type.value;
            std::string valueType = (*mapDecl)->value_type.value;
            
            int keyTypeCode = getTypeCode(keyType);
            int valueTypeCode = getTypeCode(valueType);
            llvm::Function* createFn = module->getFunction("qc_create_map");
            if (!createFn) {
                llvm::Type* ptrTy = llvm::PointerType::get(context, 0);
                llvm::FunctionType* fnTy = llvm::FunctionType::get(
                    ptrTy,
                    {builder->getInt32Ty(), builder->getInt32Ty()},
                    false
                );
                createFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                "qc_create_map", module.get());
            }
            
            llvm::Value* mapPtr = builder->CreateCall(createFn, {
                builder->getInt32(keyTypeCode),
                builder->getInt32(valueTypeCode)
            }, "map_ptr");
            
            if (!(*mapDecl)->init_pairs.empty()) {
                llvm::Function* setFn = module->getFunction("qc_map_set");
                if (!setFn) {
                    llvm::Type* voidPtrTy = llvm::PointerType::get(context, 0);
                    llvm::FunctionType* fnTy = llvm::FunctionType::get(
                        builder->getVoidTy(),
                        {voidPtrTy, voidPtrTy, voidPtrTy},
                        false
                    );
                    setFn = llvm::Function::Create(fnTy, llvm::Function::ExternalLinkage,
                                                "qc_map_set", module.get());
                }
                
                for (auto& pair : (*mapDecl)->init_pairs) {
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
                        keyPtr = builder->CreateBitCast(keyAlloc, 
                                                    llvm::PointerType::get(context, 0));
                    }
                    
                    if (valueVal->getType()->isPointerTy()) {
                        valPtr = valueVal;
                    } else {
                        llvm::AllocaInst* valAlloc = createEntryAlloca("temp_val", valueVal->getType());
                        builder->CreateStore(valueVal, valAlloc);
                        valPtr = builder->CreateBitCast(valAlloc, 
                                                    llvm::PointerType::get(context, 0));
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
        } else if (auto ns = std::get_if<std::unique_ptr<NamespaceNode>>(&node)) {
            namespaceStack.push_back((*ns)->name);
            for (auto& decl : (*ns)->body) {
                emitStmt(decl);
            }
            namespaceStack.pop_back();
            
            return;
        }
    }
    std::pair<bool, int> LLVMCompiler::checkJagged(AnyNode& node) {
        if (auto lit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&node)) {
            if ((*lit)->elements.empty()) return {false, 0};
            
            auto [firstJagged, firstDepth] = checkJagged((*lit)->elements[0]);
            size_t firstSize = 0;
            if (auto firstLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&(*lit)->elements[0])) {
                firstSize = (*firstLit)->elements.size();
            }
            
            bool isJagged = firstJagged;
            int maxDepth = firstDepth;
            
            for (auto& elem : (*lit)->elements) {
                auto [elemJagged, elemDepth] = checkJagged(elem);
                maxDepth = std::max(maxDepth, elemDepth);
                isJagged = isJagged || elemJagged;
                
                if (auto elemLit = std::get_if<std::unique_ptr<ArrayLiteralNode>>(&elem)) {
                    if ((*elemLit)->elements.size() != firstSize) {
                        isJagged = true;
                    }
                }
            }
            
            return {isJagged, maxDepth + 1};
        }
        return {false, 0};
    }
    std::vector<CTError> LLVMCompiler::compile(StatementsNode* root, const std::string& outPath) {
        errors.clear();
        locals.clear();
        globals.clear();
        functions.clear();
        functionDefs.clear();
        functionSignatures.clear();
        runtimeArraySizes.clear();
        structTypes.clear();
        jaggedArraysStack.clear();
        jaggedArraysStack.push_back({});
        arrayTypeStringsStack.clear();
        arrayTypeStringsStack.push_back({});
        listsStack.clear();
        listsStack.push_back({});
        arrayLengthsStack.clear();
        arrayLengthsStack.push_back({});
        mapsStack.clear();
        mapsStack.push_back({});
        varTypesStack.clear();
        varTypesStack.push_back({});
        
        createUserTypes();
        
        std::function<void(NamespaceNode&)> createGlobals = [&](NamespaceNode& ns) {
            namespaceStack.push_back(ns.name);
            for (auto& decl : ns.body) {
                if (auto va = std::get_if<std::unique_ptr<VarAssignNode>>(&decl)) {
                    std::string fullName = getCurrentNamespace() + "::" + (*va)->var_name_tok.value;
                    llvm::Type* ty = llvmTypeFor((*va)->type_tok.value);
                    auto* gv = new llvm::GlobalVariable(*module, ty, false,
                        llvm::GlobalValue::InternalLinkage,
                        llvm::Constant::getNullValue(ty), fullName);
                    globals[fullName] = gv;
                    varTypes[fullName] = (*va)->type_tok.value;
                }
                else if (auto nested = std::get_if<std::unique_ptr<NamespaceNode>>(&decl)) {
                    createGlobals(**nested);
                }
            }
            namespaceStack.pop_back();
        };

        for (auto& stmt : root->statements) {
            if (auto ns = std::get_if<std::unique_ptr<NamespaceNode>>(&stmt)) {
                createGlobals(**ns);
            }
            else if (auto va = std::get_if<std::unique_ptr<VarAssignNode>>(&stmt)) {
                std::string name = (*va)->var_name_tok.value;
                llvm::Type* ty = llvmTypeFor((*va)->type_tok.value);
                auto* gv = new llvm::GlobalVariable(*module, ty, false,
                    llvm::GlobalValue::InternalLinkage,
                    llvm::Constant::getNullValue(ty), name);
                globals[name] = gv;
                varTypes[name] = (*va)->type_tok.value;
            }
        }
        std::function<void(NamespaceNode&)> scanAutoFunctions = [&](NamespaceNode& ns) {
            namespaceStack.push_back(ns.name);
            
            for (auto& decl : ns.body) {
                if (auto fn = std::get_if<std::shared_ptr<FuncDefNode>>(&decl)) {
                    if ((*fn)->name_tok.has_value()) {
                        std::string funcName = (*fn)->name_tok.value().value;
                        std::string fullName = getCurrentNamespace() + "::" + funcName;
                        functionDefs[fullName] = *fn;
                    }
                }
                else if (auto nested = std::get_if<std::unique_ptr<NamespaceNode>>(&decl)) {
                    scanAutoFunctions(**nested);
                }
            }
            
            namespaceStack.pop_back();
        };

        for (auto& stmt : root->statements) {
            if (auto ns = std::get_if<std::unique_ptr<NamespaceNode>>(&stmt)) {
                scanAutoFunctions(**ns);
            }
            else if (std::holds_alternative<std::shared_ptr<FuncDefNode>>(stmt)) {
                auto fnPtr = std::get<std::shared_ptr<FuncDefNode>>(stmt);
                if (!fnPtr->name_tok.has_value()) continue;
                
                std::string funcName = fnPtr->name_tok.value().value;
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
                
                if (hasAutoParam || hasAutoReturn) {
                    autoMethodIndices[className].push_back(methodIdx);
                }
            }
        }
        std::function<void(NamespaceNode&)> compileNamespaceFunctions = [&](NamespaceNode& ns) {
            namespaceStack.push_back(ns.name);
            
            for (auto& decl : ns.body) {
                if (auto fn = std::get_if<std::shared_ptr<FuncDefNode>>(&decl)) {
                    if ((*fn)->name_tok.has_value()) {
                        if (!funcHasAutoParams(fn->get())) {
                            emitFuncDef(**fn);
                        }
                    }
                }
                else if (auto nested = std::get_if<std::unique_ptr<NamespaceNode>>(&decl)) {
                    compileNamespaceFunctions(**nested);
                }
            }
            
            namespaceStack.pop_back();
        };

        for (auto& stmt : root->statements) {
            if (auto ns = std::get_if<std::unique_ptr<NamespaceNode>>(&stmt)) {
                compileNamespaceFunctions(**ns);
            }
            else if (std::holds_alternative<std::shared_ptr<FuncDefNode>>(stmt)) {
                auto fnPtr = std::get<std::shared_ptr<FuncDefNode>>(stmt);
                if (!fnPtr->name_tok.has_value()) continue;
                if (!funcHasAutoParams(fnPtr.get())) {
                    emitFuncDef(*fnPtr);
                }
            }
        }
        for (auto& [className, info] : userTypes) {
            if (info.kind != UserTypeKind::Class) continue;
            if (!info.namespace_path.empty()) {
                namespaceStack.push_back(info.namespace_path);
            }
            
            for (size_t methodIdx = 0; methodIdx < info.classMethods.size(); methodIdx++) {
                auto& method = info.classMethods[methodIdx];
                if (std::find(autoMethodIndices[className].begin(), 
                            autoMethodIndices[className].end(), 
                            methodIdx) != autoMethodIndices[className].end()) {
                    continue;
                }
                
                llvm::Function* fn = nullptr;
                auto& overloads = classMethods[className][method.name_tok.value];
                
                for (auto* overload : overloads) {
                    if (overload->arg_size() - 1 == method.params.size()) {
                        bool matches = true;
                        for (size_t i = 0; i < method.params.size(); i++) {
                            std::string resolvedType = resolveTypeName(method.params[i].type.value);
                            llvm::Type* expectedType = llvmTypeFor(resolvedType);
                            llvm::Type* actualType = overload->getFunctionType()->getParamType(i + 1);
                            if (expectedType != actualType) {
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
                std::unordered_map<std::string, llvm::AllocaInst*> oldLocals = locals;
                enterScope();
                currentThis = fn->getArg(0);
                varTypes["this"] = className;
                currentClassName = className;
                currentFunction = fn;
                
                for (size_t i = 0; i < method.params.size(); i++) {
                    auto& param = method.params[i];
                    std::string resolvedType = resolveTypeName(param.type.value);
                    llvm::Type* paramTy = llvmTypeFor(resolvedType);
                    llvm::AllocaInst* alloc = createEntryAlloca(param.name.value, paramTy);
                    builder->CreateStore(fn->getArg(i + 1), alloc);
                    locals[param.name.value] = alloc;
                    varTypes[param.name.value] = resolvedType;
                }
                
                size_t bodyStartIdx = 0;
                if (method.is_constructor && !info.baseClassName.empty()) {
                    if (method.body && !method.body->statements.empty()) {
                        auto& firstStmt = method.body->statements[0];
                        if (auto call = std::get_if<std::unique_ptr<CallNode>>(&firstStmt)) {
                            if (auto varAccess = std::get_if<std::unique_ptr<VarAccessNode>>(&(*call)->node_to_call)) {
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
                    for (size_t i = bodyStartIdx; i < method.body->statements.size(); i++) {
                        emitStmt(method.body->statements[i]);
                    }
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
            
            if (!info.namespace_path.empty()) {
                namespaceStack.pop_back();
            }
        }
        llvm::Function* userEntry = module->getFunction(entrypointName);
        if (userEntry) {
            userEntry->setName("__user_entry");
            
            llvm::FunctionType* mainTy = llvm::FunctionType::get(builder->getInt32Ty(), {}, false);
            llvm::Function* realMain = llvm::Function::Create(
                mainTy, llvm::Function::ExternalLinkage, "main", module.get()
            );
            llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", realMain);
            builder->SetInsertPoint(entry);
            currentFunction = realMain;
            llvm::Value* result = builder->CreateCall(userEntry, {}, "entry_result");
            builder->CreateRet(result);
        } else {
            cg_error(Position(), "Entrypoint function '" + entrypointName + "' not defined");
        }

        currentFunction = nullptr;

        if (!errors.empty()) return errors;

        std::error_code EC;
        llvm::raw_fd_ostream out(outPath, EC, llvm::sys::fs::OF_Text);
        if (EC) {
            llvm::errs() << "Failed to open output: " << EC.message() << "\n";
            return errors;
        }
        module->print(out, nullptr);
        return errors;
    }
#endif
//////////////////////////////////////////////////////////////////////////////////////////////
// RUN //////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    std::string collapse_inline_brackets(const std::string& s) {
        std::string out;
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '[') {
                size_t k = out.size();
                char prev = 0;
                while (k > 0) {
                    char c = out[k - 1];
                    if (!std::isspace((unsigned char)c)) { prev = c; break; }
                    --k;
                }

                size_t j = i + 1;
                while (j < s.size() && std::isspace((unsigned char)s[j])) j++;

                bool prev_is_value_starter =
                    (prev == '=' || prev == '(' || prev == ',' ||
                    prev == '{' || prev == '[');

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
                    for (int k = 0; k < (int)part.size(); k++)
                        line[pos + k] = part[k];
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
            }
            else if (c == '{' || c == '[') {
                out += c;
                out += '\n';
                indent++;
                new_line = true;
            }
            else if (c == '}' || c == ']') {
                out += '\n';
                indent = std::max(0, indent - 1);
                new_line = true;
                add_indent();
                out += c;
            }
            else if (c == ',') {
                out += c;
                out += '\n';
                new_line = true;
            }
            else {
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

                for (int j = 0; j < indent; ++j)
                    out += lastChildStack[j] ? "    " : "│   ";

                out += (lastChildStack.empty() || !lastChildStack.back())
                    ? "├─ "
                    : "└─ ";

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
            }
            else if (c == '}' || c == ']') {
                out += '\n';
                indent = std::max(0, indent - 1);
                if (!lastChildStack.empty()) lastChildStack.pop_back();
                new_line = true;
            }
            else if (c == ',') {
                out += '\n';
                new_line = true;
            }
            else {
                out += c;
            }
        }

        out += '\n';
        return out;
    }
    std::string removeExtension(const std::string& filename) {
        size_t lastDot = filename.find_last_of('.');
        if (lastDot == std::string::npos) {
            return filename;
        }
        return filename.substr(0, lastDot);
    }
    Mer run(std::string file, std::string text, RunConfig config = {}) {
        // Check for inline directives
        if (text.find("// @no-context") != std::string::npos) {
            config.use_context = false;
        }
        
        if (text.find("// @looser-types") != std::string::npos) {
            config.looser_types = true;
        }
        
        if (text.find("// @print-ast") != std::string::npos) {
            config.print_ast = true;
        }
        
        if (text.find("// @print-tokens") != std::string::npos) {
            config.print_tokens = true;
        }
        
        if (text.find("// @show-time") != std::string::npos) {
            config.show_time = true;
        }
        
        if (text.find("// @quiet") != std::string::npos) {
            config.quiet_mode = true;
        }
        if (text.find("// @raw-ast") != std::string::npos) {
            config.raw = true;
            config.print_ast = true;
        }
        if (text.find("// @bst-ast") != std::string::npos) {
            config.bst = true;
            config.print_ast = true;
        }
        loose = config.looser_types;
        
        auto start = std::chrono::high_resolution_clock::now();
        try {
            text = preprocess_includes(text, file);
        } catch (std::runtime_error& e) {
            return Mer{Aer{nullptr, nullptr}, Ler{std::vector<Token>{}, std::make_unique<InvalidSyntaxError>("QC-IX01: Include Error", Position())}, ""};
        }
        // Lexer
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
        
        // Print tokens if requested
        if (config.print_tokens) {
            std::cout << "=== TOKENS ===" << std::endl;
            for (const auto& tok : resp.Tkns) {
                std::cout << "Type: " << get_token_name(tok.type) 
                        << " | Value: '" << tok.value << "'" << std::endl;
            }
            std::cout << "==============" << std::endl << std::endl;
        }
        
        // Parser
        Parser parser(resp.Tkns);
        Aer ast = parser.parse();
        
        if (ast.error) {
            return Mer{std::move(ast), std::move(resp), ""};
        }
        
        // Print AST if requested
        if (config.print_ast && config.raw) {
            std::cout << "=== AST ===" << std::endl;
            for (const auto& stmt : ast.statements->statements) {
                std::cout << indent_ast(printAny(stmt));
            }
            std::cout << "===========" << std::endl << std::endl;
        }
        else if (config.print_ast && config.bst) {
            std::cout << "=== AST ===" << std::endl;
            for (const auto& stmt : ast.statements->statements) {
                std::cout << bst_diagram(printAny(stmt));
            }
            std::cout << "===========" << std::endl << std::endl;
        }
        else if (config.print_ast) {
            std::cout << "=== AST ===" << std::endl;
            for (const auto& stmt : ast.statements->statements) {
                std::cout << asciiTreeAST(printAny(stmt));
            }
            std::cout << "===========" << std::endl << std::endl;
        }
        // compiler
        // Interpreter
        if (config.interpret_mode) {
            Context* ctx = new Context();
            for (auto& [name, info] : ast.user_types) {
                ctx->define_user_type(std::move(info), name);
            }
            Interpreter interpreter(ctx);
            std::string output = "";
            int exit_code = 0;
            
            try {
                for (auto& stmt : ast.statements->statements) {
                    if (std::holds_alternative<std::unique_ptr<NamespaceNode>>(stmt)) {
                        interpreter.process(stmt);
                    }
                    if (std::holds_alternative<std::shared_ptr<FuncDefNode>>(stmt)) {
                        interpreter.process(stmt);
                    }
                }

                
                // Call main
                std::shared_ptr<FuncDefNode> main_func = ctx->get_function(entrypointName);
                if (!main_func) {
                    throw RTError("No main() function found", Position());
                }
                
                auto main_call_node = std::make_unique<CallNode>(
                    std::make_unique<VarAccessNode>(Token(TokenType::IDENTIFIER, entrypointName, Position())),
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
                
                auto end = std::chrono::high_resolution_clock::now();
                
                if (!config.quiet_mode) {
                    output = "Program exited with code: " + std::to_string(exit_code);
                }
                
                if (config.show_time) {
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    if (!config.quiet_mode) output += "\n";
                    output += "Execution time: " + std::to_string(duration.count()) + "ms";
                }
                
            } catch (RTError& e) {
                delete ctx;
                std::unique_ptr<Error> err = std::make_unique<RTError>(e);
                ast = Aer(std::move(ast.statements), std::move(err), std::move(ast.user_types));
                return Mer{std::move(ast), std::move(resp), "", interpreter.errors};
            } catch (NumberVariant nv) {
                delete ctx;
                std::unique_ptr<Error> err = std::make_unique<RTError>(interpreter.value_to_string(nv), Position("", "", 0, 0, 0));
                ast = Aer(std::move(ast.statements), std::move(err), std::move(ast.user_types));
                return Mer{std::move(ast), std::move(resp), "", interpreter.errors};
            } catch (...) {
                delete ctx;
                std::unique_ptr<Error> err = std::make_unique<RTError>("Unknown exception", Position("", "", 0, 0, 0));
                ast = Aer(std::move(ast.statements), std::move(err), std::move(ast.user_types));
                return Mer{std::move(ast), std::move(resp), "", interpreter.errors};
            }
            
            delete ctx;
            return Mer{std::move(ast), std::move(resp), output, interpreter.errors};
        }
        #ifdef ENABLE_LLVM
            if (config.compile_mode) {
                LLVMCompiler comp(ast.user_types);
                std::string base_name = config.output_file.empty() ? "out" : removeExtension(config.output_file);
                size_t last_slash = base_name.find_last_of("/\\");
                std::string dir = (last_slash == std::string::npos) ? "" : base_name.substr(0, last_slash + 1);
                std::string stem = (last_slash == std::string::npos) ? base_name : base_name.substr(last_slash + 1);

                std::string ll_file = config.compile_only ? base_name + ".ll" : dir + "temp_" + stem + ".ll";
                std::string obj_file = config.object_only ? base_name + ".o" : dir + "temp_" + stem + ".o";
                
                std::vector<CTError> compile_errors = comp.compile(ast.statements.get(), ll_file);
                auto end = std::chrono::high_resolution_clock::now();
                std::vector<Diagnostic> diagnostics;
                bool error_found = false;
                for (auto& err : compile_errors) {
                    error_found = true;
                    diagnostics.push_back({
                        RTError(err.details, err.pos),
                        "Error"
                    });
                }
                std::string message = "Program exited with code: 0";
                if (error_found) {
                    message = "Program exited with code: 1";
                }
                if (!diagnostics.empty()) {
                    return Mer{std::move(ast), std::move(resp), message, diagnostics};
                }
                if (config.compile_only) {
                    message += ". Compiled to " + ll_file;
                    return Mer{std::move(ast), std::move(resp), message, diagnostics};
                }
                std::string llc_cmd = "llc " + ll_file + " -o " + obj_file + " -filetype=obj -relocation-model=pic";
                if (config.debug) llc_cmd += " --debugger-tune=gdb";
                int llc_result = system(llc_cmd.c_str());
                
                if (llc_result != 0) {
                    diagnostics.push_back({
                        RTError("Failed to compile IR to object file", Position("", "", 0, 0, 0)),
                        "Error"
                    });
                    return Mer{std::move(ast), std::move(resp), message, diagnostics};
                }
                
                if (config.object_only) {
                    std::remove(ll_file.c_str());
                    message += ". Compiled to " + obj_file;
                    return Mer{std::move(ast), std::move(resp), message, diagnostics};
                }
                std::string final_exe = config.output_file.empty() ? "a.out" : config.output_file;
                std::string link_cmd = "gcc " + obj_file + " -o " + final_exe + " -lm -lffi";
                if (config.debug) link_cmd += " -g";
                int link_result = system(link_cmd.c_str());
                if (link_result != 0) {
                    diagnostics.push_back({
                        RTError("Failed to link object file", Position("", "", 0, 0, 0)),
                        "Error"
                    });
                    return Mer{std::move(ast), std::move(resp), message, diagnostics};
                }
                std::remove(ll_file.c_str());
                std::remove(obj_file.c_str());
                
                message += ". Built executable: " + final_exe;
                return Mer{std::move(ast), std::move(resp), message, diagnostics};
            }
        #endif
        return Mer{std::move(ast), std::move(resp), "", std::vector<Diagnostic>{}};
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
            id == "return" || id == "qif" || id == "qelse" || id == "qelif" || id == "qswitch" || 
            id == "const" || id == "default" || id == "class" || id == "struct" || id == "enum" || 
            id == "long" || id == "short" || id == "fn" || id == "continue" || id == "auto" || 
            id == "list" || id == "foreach" || id == "do" || id == "in" || id == "function" ||
            id == "map" || id == "type" || id == "public" || id == "protected" || id == "private" ||
            id == "namespace" || id == "keyword" || id == "operator" || id == "abstract" ||
            id == "final" ||id == "try" || id == "catch" || id == "nullptr") {
            return Token(TokenType::KEYWORD, id, start_pos);
        }
        if (id == "true" || id == "false") {
            return Token(TokenType::BOOL, id, start_pos);
        }
        if (id == "qtrue" || id == "qfalse" || id == "both" || id == "none") {
            return Token(TokenType::QBOOL, id, start_pos);
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
            throw IllegalCharError("QC-IC01: Expected closing single quote", this->pos);
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
                    throw IllegalCharError("QC-IC02: Unclosed brace in f-string", this->pos);

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
                        }  else if (current_char == '>') {
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
                            tokens.push_back(Token(TokenType::RSHIFT, ">>", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::MORE, ">", start_pos));
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
                        if (current_char == '*') {
                            this->advance();
                            tokens.push_back(Token(TokenType::POWER, "^*", start_pos));
                            break;
                        } else if (current_char == '^') {
                            this->advance();
                            tokens.push_back(Token(TokenType::QXOR, "^^", start_pos));
                        } else {
                            tokens.push_back(Token(TokenType::XOR, "^", start_pos));
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
                        tokens.push_back(Token(TokenType::SEMICOLON, ";", start_pos));
                        this->advance();
                        break;
                    case '.':
                        tokens.push_back(Token(TokenType::DOT, ".", start_pos));
                        this->advance();
                        break;
                    
                    default:
                        std::string unknown = std::string(1, this->current_char);
                        return Ler {std::vector<Token>(), std::make_unique<IllegalCharError>("QC-IC03:" + unknown, this->pos)};
                }
            }
        }
        tokens.push_back(Token(TokenType::EOFT, "<eof>", this->pos));
        return Ler {tokens, NULL};

    }

}
///////////////////////////////////////////////////////////////////////////////////////////
// PREPROCCESERS /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}
std::string read_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("QC-IX03: Could not open file: " + path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
std::string resolve_path(const std::string& current_file, const std::string& include_path) {
    std::filesystem::path current(current_file);
    std::filesystem::path include(include_path);
    if (include.is_absolute()) {
        return include.string();
    }
    
    std::filesystem::path resolved = current.parent_path() / include;
    return resolved.string();
}
std::string extract_namespace(const std::string& source, const std::string& ns_name) {
    std::string search = "namespace " + ns_name;
    size_t pos = source.find(search);
    
    if (pos == std::string::npos) {
        throw std::runtime_error("QC-IX02: Namespace '" + ns_name + "' not found in file");
    }
    size_t brace_start = source.find('{', pos);
    if (brace_start == std::string::npos) {
        throw std::runtime_error("QC-N003: Invalid namespace syntax for '" + ns_name + "'");
    }
    int depth = 1;
    size_t i = brace_start + 1;
    while (i < source.size() && depth > 0) {
        if (source[i] == '{') depth++;
        if (source[i] == '}') depth--;
        i++;
    }
    
    if (depth != 0) {
        throw std::runtime_error("QC-N002: Unmatched braces in namespace '" + ns_name + "'");
    }
    
    return source.substr(pos, i - pos);
}
std::string preprocess_includes(const std::string& source, const std::string& current_file) {
    entrypointName = "main";
    std::set<std::pair<std::string, std::string>> included_namespaces;
    std::vector<std::string> exported_blocks;
    std::vector<std::string> namespace_order;
    size_t ep_pos = source.find("#entrypoint");
    if (ep_pos != std::string::npos) {
        bool in_string = false;
        for (size_t check = 0; check < ep_pos; check++) {
            if (source[check] == '"' && (check == 0 || source[check-1] != '\\')) {
                in_string = !in_string;
            }
        }
        if (!in_string) {
            size_t line_end = source.find('\n', ep_pos);
            if (line_end == std::string::npos) line_end = source.size();
            std::string directive = source.substr(ep_pos + 12, line_end - ep_pos - 12);  // +12 for "#entrypoint "
            entrypointName = trim(directive);
        }
    }
    std::function<void(const std::string&, const std::string&)> process_file;
    process_file = [&](const std::string& file_path, const std::string& ns_to_include) {
        std::pair<std::string, std::string> key = {file_path, ns_to_include};
        if (included_namespaces.count(key)) return;
        included_namespaces.insert(key);
        
        std::string file_content = read_file(file_path);
        std::pair<std::string, std::string> exported_key = {file_path, "Exported"};
        if (!included_namespaces.count(exported_key)) {
            included_namespaces.insert(exported_key);
            
            size_t exported_pos = 0;
            bool in_string = false;
            for (size_t scan = 0; scan < file_content.size(); scan++) {
                if (file_content[scan] == '"' && (scan == 0 || file_content[scan-1] != '\\')) {
                    in_string = !in_string;
                }
                if (!in_string && file_content.substr(scan, 18) == "namespace Exported") {
                    exported_pos = scan;
                    break;
                }
            }
            
            if (exported_pos != std::string::npos) {
                size_t brace_start = file_content.find('{', exported_pos);
                int depth = 1;
                size_t i = brace_start + 1;
                size_t content_start = i;
                
                in_string = false;
                while (i < file_content.size() && depth > 0) {
                    if (file_content[i] == '"' && (i == 0 || file_content[i-1] != '\\')) {
                        in_string = !in_string;
                    }
                    if (!in_string) {
                        if (file_content[i] == '{') depth++;
                        if (file_content[i] == '}') depth--;
                    }
                    i++;
                }
                
                std::string exported_content = file_content.substr(content_start, i - content_start - 1);
                
                size_t inc_pos = 0;
                while ((inc_pos = exported_content.find("#include", inc_pos)) != std::string::npos) {
                    bool in_str = false;
                    for (size_t check = 0; check < inc_pos; check++) {
                        if (exported_content[check] == '"' && (check == 0 || exported_content[check-1] != '\\')) {
                            in_str = !in_str;
                        }
                    }
                    if (in_str) {
                        inc_pos++;
                        continue;
                    }
                    
                    size_t start = exported_content.find('<', inc_pos);
                    size_t end = exported_content.find('>', start);
                    
                    std::string directive = exported_content.substr(start + 1, end - start - 1);
                    size_t comma = directive.find(',');
                    
                    std::string dep_ns = trim(directive.substr(0, comma));
                    std::string dep_path = trim(directive.substr(comma + 1));
                    
                    if (!dep_path.empty() && dep_path.front() == '"') {
                        dep_path = dep_path.substr(1);
                    }
                    if (!dep_path.empty() && dep_path.back() == '"') {
                        dep_path = dep_path.substr(0, dep_path.size() - 1);
                    }
                    
                    std::string dep_full_path;
                    if (dep_path == "std") {
                        dep_full_path = "/usr/local/QC/stdlib.qc";
                    } else {
                        dep_full_path = resolve_path(file_path, dep_path);
                    }
                    process_file(dep_full_path, dep_ns);
                    
                    inc_pos = end + 1;
                }
                std::string clean_exported = "";
                size_t last = 0;
                inc_pos = 0;
                while ((inc_pos = exported_content.find("#include", inc_pos)) != std::string::npos) {
                    bool in_str = false;
                    for (size_t check = 0; check < inc_pos; check++) {
                        if (exported_content[check] == '"' && (check == 0 || exported_content[check-1] != '\\')) {
                            in_str = !in_str;
                        }
                    }
                    if (in_str) {
                        inc_pos++;
                        continue;
                    }
                    
                    clean_exported += exported_content.substr(last, inc_pos - last);
                    size_t end = exported_content.find('>', inc_pos);
                    last = end + 1;
                    if (last < exported_content.size() && exported_content[last] == '\n') {
                        last++;
                    }
                    inc_pos = last;
                }
                clean_exported += exported_content.substr(last);
                
                if (clean_exported.find_first_not_of(" \t\n\r") != std::string::npos) {
                    exported_blocks.push_back(clean_exported);
                }
            }
        }
        if (ns_to_include != "Exported" && ns_to_include != "*") {
            size_t ns_pos = 0;
            while (ns_pos < file_content.size()) {
                bool in_string = false;
                size_t search_start = ns_pos;
                for (size_t scan = 0; scan < search_start; scan++) {
                    if (file_content[scan] == '"' && (scan == 0 || file_content[scan-1] != '\\')) {
                        in_string = !in_string;
                    }
                }
                
                ns_pos = file_content.find("namespace " + ns_to_include, ns_pos);
                if (ns_pos == std::string::npos) break;
                
                in_string = false;
                for (size_t check = 0; check < ns_pos; check++) {
                    if (file_content[check] == '"' && (check == 0 || file_content[check-1] != '\\')) {
                        in_string = !in_string;
                    }
                }
                if (in_string) {
                    ns_pos++;
                    continue;
                }
                
                size_t name_end = ns_pos + 10 + ns_to_include.length();
                if (name_end < file_content.size() && 
                    (file_content[name_end] == ' ' || file_content[name_end] == '\t' || 
                    file_content[name_end] == '\n' || file_content[name_end] == '{')) {
                    
                    size_t brace_start = file_content.find('{', ns_pos);
                    int depth = 1;
                    size_t i = brace_start + 1;
                    
                    in_string = false;
                    while (i < file_content.size() && depth > 0) {
                        if (file_content[i] == '"' && (i == 0 || file_content[i-1] != '\\')) {
                            in_string = !in_string;
                        }
                        if (!in_string) {
                            if (file_content[i] == '{') depth++;
                            if (file_content[i] == '}') depth--;
                        }
                        i++;
                    }
                    
                    std::string ns_block = file_content.substr(ns_pos, i - ns_pos);
                    namespace_order.push_back(ns_block);
                    ns_pos = i;
                } else {
                    ns_pos++;
                }
            }
        }
    };
    size_t pos = 0;
    while ((pos = source.find("#include", pos)) != std::string::npos) {
        bool in_string = false;
        for (size_t check = 0; check < pos; check++) {
            if (source[check] == '"' && (check == 0 || source[check-1] != '\\')) {
                in_string = !in_string;
            }
        }
        if (in_string) {
            pos++;
            continue;
        }
        
        size_t start = source.find('<', pos);
        size_t end = source.find('>', start);
        
        std::string directive = source.substr(start + 1, end - start - 1);
        size_t comma = directive.find(',');
        
        std::string ns_name = trim(directive.substr(0, comma));
        std::string path = trim(directive.substr(comma + 1));
        if (!path.empty() && path.front() == '"') {
            path = path.substr(1);
        }
        if (!path.empty() && path.back() == '"') {
            path = path.substr(0, path.size() - 1);
        }
        
        std::string full_path;
        if (path == "std") {
            const char* home = std::getenv("QC_STDLIB");
            if (!home) {
                throw std::runtime_error("QC_STDLIB environment variable not set");
            }
            full_path = std::string(home);
        } else {
            full_path = resolve_path(current_file, path);
        }
        
        process_file(full_path, ns_name);
        
        pos = end + 1;
    }
    std::string result = "";
    size_t last_pos = 0;
    pos = 0;
    while ((pos = source.find("#include", pos)) != std::string::npos) {
        bool in_string = false;
        for (size_t check = 0; check < pos; check++) {
            if (source[check] == '"' && (check == 0 || source[check-1] != '\\')) {
                in_string = !in_string;
            }
        }
        if (in_string) {
            pos++;
            continue;
        }
        
        result += source.substr(last_pos, pos - last_pos);
        size_t end = source.find('>', pos);
        last_pos = end + 1;
        if (last_pos < source.size() && source[last_pos] == '\n') {
            last_pos++;
        }
        pos = last_pos;
    }
    result += source.substr(last_pos);
    pos = 0;
    while ((pos = result.find("#entrypoint", pos)) != std::string::npos) {
        bool in_str = false;
        for (size_t check = 0; check < pos; check++) {
            if (result[check] == '"' && (check == 0 || result[check-1] != '\\')) {
                in_str = !in_str;
            }
        }
        if (!in_str) {
            size_t line_end = result.find('\n', pos);
            if (line_end == std::string::npos) line_end = result.size();
            result.erase(pos, line_end - pos + 1);
        } else {
            pos++;
        }
    }
    size_t exported_start = 0;
    bool in_string = false;
    for (size_t scan = 0; scan < result.size(); scan++) {
        if (result[scan] == '"' && (scan == 0 || result[scan-1] != '\\')) {
            in_string = !in_string;
        }
        if (!in_string && result.substr(scan, 18) == "namespace Exported") {
            exported_start = scan;
            break;
        }
    }
    
    size_t insert_pos = 0;
    
    if (exported_start != std::string::npos) {
        size_t brace_start = result.find('{', exported_start);
        int depth = 1;
        size_t i = brace_start + 1;
        
        in_string = false;
        while (i < result.size() && depth > 0) {
            if (result[i] == '"' && (i == 0 || result[i-1] != '\\')) {
                in_string = !in_string;
            }
            if (!in_string) {
                if (result[i] == '{') depth++;
                if (result[i] == '}') depth--;
            }
            i++;
        }
        
        std::string all_exported = "";
        for (auto& block : exported_blocks) {
            all_exported += "\nnamespace Exported {\n" + block + "\n}\n";
        }
        
        insert_pos = i;
        result.insert(i, all_exported);
        insert_pos += all_exported.length();
    }
    
    for (auto& ns : namespace_order) {
        result.insert(insert_pos, "\n" + ns + "\n");
        insert_pos += ns.length() + 2;
    }
    
    return result;
}; 
