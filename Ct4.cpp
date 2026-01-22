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
    while(r.size()>=2 && r.substr(r.size()-2)=="[]") r=r.substr(0,r.size()-2);
    size_t pos;
    while((pos=r.find("list<"))!=std::string::npos && r.back()=='>') r=r.substr(pos+5,r.size()-(pos+6));
    return r;
}
bool loose;
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
            case TokenType::POWER:      return "**";

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
                                std::is_same_v<T, FunctionValue>) {
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
        result += "Runtime Error: " + this->details + "\n";
        result += "File " + this->pos.Filename +
                ", line " + std::to_string(this->pos.line + 1) +
                ", col " + std::to_string(this->pos.column + 1) + "\n\n";
        result += this->pos.arrow_string();
        return result;
    }
    std::string MissingSemicolonError::as_string() {
        std::string result;
        result += "Missing Semicolon on ";
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
            else if constexpr (std::is_same_v<T, std::unique_ptr<QOutNode>>) {
                return arg->print();
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<QOutExprNode>>) {
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
            else if constexpr (std::is_same_v<T, QOutNode>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<QOutExprNode>>) {
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
            else if constexpr (std::is_same_v<T, QOutNode>) {
                return Prs{std::move(arg)};
            }
            else if constexpr (std::is_same_v<T, std::unique_ptr<QOutExprNode>>) {
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
        return AnyNode{NumberNode(Token(TokenType::INT, "0", pos))};
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
        if (!(current_tok.type == TokenType::KEYWORD && current_tok.value == "for")) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S035: Expected 'for'", current_tok.pos));
            return res.to_prs();
        }
        advance();

        if (current_tok.type != TokenType::LPAREN) {
            res.failure(std::make_unique<InvalidSyntaxError>("QC-S036: Expected '(' after 'for'", current_tok.pos));
            return res.to_prs();
        }
        advance();

        std::optional<AnyNode> init;
        std::optional<AnyNode> update;
        AnyNode condition;

        if (current_tok.type != TokenType::SEMICOLON) {
            if (current_tok.type == TokenType::KEYWORD &&
                (current_tok.value == "const" ||
                current_tok.value == "int"   ||
                current_tok.value == "float" ||
                current_tok.value == "double"||
                current_tok.value == "bool"  ||
                current_tok.value == "string"||
                current_tok.value == "char")) {

                bool is_const = false;
                Token tok = current_tok;

                if (tok.value == "const") {
                    is_const = true;
                    advance();
                    tok = current_tok;
                    if (tok.type != TokenType::KEYWORD) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "QC-S037: Expected type after 'const' in for-init", current_tok.pos));
                        return res.to_prs();
                    }
                }

                type_tok = tok;
                advance();

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
        advance();

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
        advance();

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
        advance();

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
        if (std::holds_alternative<QOutNode>(left)) {
            std::vector<AnyNode> values;
            
            while (this->current_tok.type == TokenType::LSHIFT) {
                this->advance();  
                AnyNode value = res.reg(this->logical_or());
                if (res.error) return res.to_prs();
                values.push_back(std::move(value));
            }
            return res.success(std::make_unique<QOutExprNode>(std::move(values)));
        }
        
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

        if (tok.value == "std") {
            this->advance();
            if (this->current_tok.type == TokenType::SCOPE) {
                this->advance();
                if (this->current_tok.value == "qout") {
                    this->advance();
                    return res.success(QOutNode());
                }
                if (current_tok.value == "qin") {
                    this->advance();
                    
                    return this->qin_expr(); 
                }

            }
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
        else if (tok.type == TokenType::IDENTIFIER) {
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

            if (this->current_tok.type == TokenType::INCREMENT ||
                this->current_tok.type == TokenType::DECREMENT) {
                Token op = this->current_tok;
                this->advance();
                return res.success(std::make_unique<AssignExprNode>(
                    ident,
                    std::make_unique<UnaryOpNode>(op,
                        std::make_unique<VarAccessNode>(tok))));
            }

            return res.success(std::move(base));
        }
        else if (tok.type == TokenType::LPAREN) {
            this->advance();
            AnyNode any_expr = res.reg(this->logical_or());
            if (res.error) return res.to_prs();

            if (this->current_tok.type == TokenType::RPAREN) {
                this->advance();
                return res.success(std::move(any_expr));
            } else {
                res.failure(std::make_unique<InvalidSyntaxError>("Expected ')'", this->current_tok.pos));
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
                
                if (this->current_tok.type != TokenType::KEYWORD && this->user_types.count(this->current_tok.value) <= 0) {
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

        res.failure(std::make_unique<InvalidSyntaxError>("Expected an atom", tok.pos));
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
            tok.type == TokenType::NOT || tok.type == TokenType::QNOT) {
            
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
                    "Right-hand side of >> must be a variable",
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

            if (!is_var && !is_array_access && !is_prop) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Left side of assignment must be a variable, struct field, or array/map access",
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
                            "Unsupported op for struct fields", op_tok.pos));
                        return res.to_prs();
                }

                auto baseVarForLhs = std::make_unique<VarAccessNode>(prop->base_name_tok);
                AnyNode lhsBase = AnyNode{ std::move(baseVarForLhs) };

                if (binop_type == TokenType::EQ) {
                    return res.success(std::make_unique<FieldAssignNode>(
                        std::move(lhsBase),
                        field,
                        std::move(right)
                    ));
                }
                auto baseVarForRhs = std::make_unique<VarAccessNode>(prop->base_name_tok);
                AnyNode rhsBase = AnyNode{ std::move(baseVarForRhs) };

                auto readProp = std::make_unique<PropertyAccessNode>(
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
                        "Compound assignment (+=, -=, etc.) not supported for array/map access",
                        op_tok.pos
                    ));
                    return res.to_prs();
                }
                
                return res.success(std::make_unique<ArrayAssignNode>(
                    std::move(left),
                    std::move(right)
                ));
            }
            
            Token var = std::get<std::unique_ptr<VarAccessNode>>(left)->var_name_tok;
            
            if (op_tok.type != TokenType::EQ) {
                TokenType binop_type;
                if (op_tok.type == TokenType::PLUS_EQ) binop_type = TokenType::PLUS;
                else if (op_tok.type == TokenType::MINUS_EQ) binop_type = TokenType::MINUS;
                else if (op_tok.type == TokenType::MUL_EQ) binop_type = TokenType::MUL;
                else if (op_tok.type == TokenType::DIV_EQ) binop_type = TokenType::DIV;
                else if (op_tok.type == TokenType::MOD_EQ) binop_type = TokenType::MOD;
                
                Token binop_tok(binop_type, "", op_tok.pos);
                AnyNode var_access = std::make_unique<VarAccessNode>(var);
                AnyNode expanded = std::make_unique<BinOpNode>(
                    std::move(var_access), 
                    binop_tok, 
                    std::move(right)
                );
                
                return res.success(std::make_unique<AssignExprNode>(var, std::move(expanded)));
            }

            return res.success(std::make_unique<AssignExprNode>(var, std::move(right)));
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
                std::is_same_v<T, std::unique_ptr<QOutExprNode>> ||
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
                std::is_same_v<T, std::unique_ptr<NamespaceNode>>
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

            if (param_type.value == "short" || param_type.value == "long") {
                std::string modifier = param_type.value;

                if (this->current_tok.type != TokenType::KEYWORD) {
                    res.failure(std::make_unique<InvalidSyntaxError>("Expected type after 'short'/'long'", this->current_tok.pos));
                    return res.to_prs();
                }
                Token base_type = this->current_tok;
                this->advance();

                param_type.value = modifier + " " + base_type.value;
                param_type.pos = base_type.pos;
            }

            if (param_type.value == "list" && this->current_tok.type == TokenType::LESS) {
                this->advance();

                if (this->current_tok.type != TokenType::KEYWORD && this->user_types.count(this->current_tok.value) <= 0) {
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
                        "Expected ']' after '[' in parameter", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                param_type.value += "[]"; 
            }
            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected parameter name", this->current_tok.pos));
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

                if (param_type.value == "list" && this->current_tok.type == TokenType::LESS) {
                    this->advance(); 

                    if (this->current_tok.type != TokenType::KEYWORD && this->user_types.count(this->current_tok.value) <= 0) {
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
                            "Expected ']' after '[' in parameter", this->current_tok.pos));
                        return res.to_prs();
                    }
                    this->advance();
                    param_type.value += "[]"; 
                }
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected parameter name", this->current_tok.pos));
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
                "Expected ')' after parameters", this->current_tok.pos));
            return res.to_prs();
        }
        this->advance(); 
        if (this->current_tok.type == TokenType::ARROW) {
            this->advance();
            
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
                "Expected '{' to start function body", this->current_tok.pos));
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
            if (res.error) return res.to_prs();
            
            if (this->current_tok.type != TokenType::RPAREN) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected ')' after foreach", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            if (this->current_tok.type != TokenType::LBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected '{' to start foreach body", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            AnyNode body = res.reg(this->statement());
            if (res.error) return res.to_prs();
            if (this->current_tok.type != TokenType::RBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected '}' to end foreach body", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            return res.success(std::make_unique<ForeachNode>(
                elem_type, elem_name, std::move(collection), std::move(body)));
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
                auto base_it = user_types.find(baseName);
                if (base_it != user_types.end() &&
                    base_it->second.kind == UserTypeKind::Class &&
                    base_it->second.is_final_class) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Cannot inherit from final class '" + baseName + "'",
                        class_name.pos));
                    return res.to_prs();
                }
            }    
            if (this->current_tok.type != TokenType::LBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected '{' after class name", this->current_tok.pos));
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
                    "Redefinition of type '" + class_name.value + "'",
                    class_name.pos));
                return res.to_prs();
            }
            dummy.namespace_path = currentNamespace;
            info.namespace_path = currentNamespace;
            user_types[class_name.value] = std::move(dummy);

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
                type_list.push_back(this->current_tok);
                this->advance();

                while (this->current_tok.type == TokenType::COMMA) {
                    this->advance();

                    if (this->current_tok.type != TokenType::KEYWORD &&
                        this->current_tok.type != TokenType::IDENTIFIER) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Expected type after ',' in return type list", this->current_tok.pos));
                        return res.to_prs();
                    }
                    type_list.push_back(this->current_tok);
                    this->advance();
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
                        case TokenType::PLUS:     op_name = "operator+";  break;
                        case TokenType::MINUS:    op_name = "operator-";  break;
                        case TokenType::MUL:      op_name = "operator*";  break;
                        case TokenType::DIV:      op_name = "operator/";  break;
                        case TokenType::EQ_TO:    op_name = "operator=="; break;
                        case TokenType::NOT_EQ:   op_name = "operator!="; break;
                        case TokenType::EQ:       op_name = "operator=";  break;
                        case TokenType::NOT:      op_name = "operator!";  break;
                        case TokenType::AND:      op_name = "operator&&"; break;
                        case TokenType::OR:       op_name = "operator||"; break;
                        case TokenType::MORE:     op_name = "operator>";  break;
                        case TokenType::LESS:     op_name = "operator<";  break;
                        case TokenType::MORE_EQ:  op_name = "operator>="; break;
                        case TokenType::LESS_EQ:  op_name = "operator<="; break;
                        case TokenType::POWER:  op_name = "operator**"; break;
                        case TokenType::MOD: op_name = "operator%"; break;
                        case TokenType::XOR: op_name = "operator^"; break;
                        case TokenType::QNOT:  op_name = "operator!!"; break;
                        case TokenType::QAND: op_name = "operator&&&"; break;
                        case TokenType::QOR:  op_name = "operator|||"; break;
                        case TokenType::QXOR: op_name = "operator^^"; break;
                        case TokenType::COLLAPSE_OR:  op_name = "operator|&|"; break;
                        case TokenType::COLLAPSE_AND: op_name = "operator&|&"; break;
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
                        auto base_it = user_types.find(info.baseClassName);
                        if (base_it != user_types.end() &&
                            base_it->second.kind == UserTypeKind::Class) {

                            auto& baseInfo = base_it->second;
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

                    mi.name_tok = name_tok;
                    mi.params.clear();
                    mi.params.reserve(fn->params.size());
                    for (auto it = fn->params.begin(); it != fn->params.end(); ++it) {
                        mi.params.push_back(std::move(*it)); 
                    }
                    mi.return_types = fn->return_types;
                    mi.body = std::move(fn->body);
                    mi.is_constructor = false;
                    mi.is_final = is_final_method;
                    mi.access = access;

                    info.classMethods.push_back(std::move(mi));
                    continue;
                }
                if (type_list.size() != 1) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Class fields cannot have multiple types", name_tok.pos));
                    return res.to_prs();
                }

                if (this->current_tok.type != TokenType::SEMICOLON) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected ';' after field declaration", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();

                ClassField cf;
                cf.name = name_tok.value;
                cf.type = type_list[0].value;
                cf.access = access;
                info.classFields.push_back(std::move(cf));
            }

            if (this->current_tok.type != TokenType::RBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected '}' at end of class", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            user_types[class_name.value] = std::move(info);
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
                    "Expected '{' after namespace name", current_tok.pos));
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
                    "Expected '}' at end of namespace", current_tok.pos));
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
                    "Expected struct name", this->current_tok.pos));
                return res.to_prs();
            }
            Token struct_name = this->current_tok;
            this->advance();

            if (this->current_tok.type != TokenType::LBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected '{' after struct name", this->current_tok.pos));
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
                                "Expected identifier after '::'", this->current_tok.pos));
                            return res.to_prs();
                        }
                        
                        field_type += "::" + this->current_tok.value;
                        this->advance();
                    }
                }
                else if (this->current_tok.type == TokenType::KEYWORD) {
                    Token base_type = this->current_tok;
                    field_type = base_type.value;
                    this->advance();
                    
                    if (this->current_tok.type == TokenType::LBRACKET) {
                        this->advance();
                        if (this->current_tok.type != TokenType::RBRACKET) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "Expected ']' after '[' in list type", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                        field_type = "list<" + base_type.value + ">";
                    }
                    else if (base_type.value == "map") {
                        if (this->current_tok.type != TokenType::LESS) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "Expected '<' after map for key type", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();
                        
                        if (this->current_tok.type != TokenType::KEYWORD && 
                            this->current_tok.type != TokenType::IDENTIFIER) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "Expected key type in map", this->current_tok.pos));
                            return res.to_prs();
                        }
                        std::string key_type = this->current_tok.value;
                        this->advance();

                        if (this->current_tok.type != TokenType::COMMA) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "Expected ',' between key and value type in map", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();

                        if (this->current_tok.type != TokenType::KEYWORD && 
                            this->current_tok.type != TokenType::IDENTIFIER) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "Expected value type in map", this->current_tok.pos));
                            return res.to_prs();
                        }
                        std::string value_type = this->current_tok.value;
                        this->advance();

                        if (this->current_tok.type != TokenType::MORE) {
                            res.failure(std::make_unique<InvalidSyntaxError>(
                                "Expected '>' after map value type", this->current_tok.pos));
                            return res.to_prs();
                        }
                        this->advance();

                        field_type = "map<" + key_type + "," + value_type + ">";
                    }
                } else {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected field type in struct", this->current_tok.pos));
                    return res.to_prs();
                }

                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected field name in struct", this->current_tok.pos));
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
                            "Expected ']' after '[' in array", this->current_tok.pos));
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
                    "Expected '}' at end of struct", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance(); 

            if (this->current_tok.type == TokenType::SEMICOLON) {
                this->advance();
            }
            if (user_types.contains(struct_name.value)) {
                res.failure(std::make_unique<InvalidSyntaxError>("Redefinition of struct '" + struct_name.value + "'", struct_name.pos));
                return res.to_prs();
            }
            UserTypeInfo info;
            info.kind   = UserTypeKind::Struct;
            info.fields = std::move(fields);
            info.namespace_path = currentNamespace;
            user_types[struct_name.value] = std::move(info);
            return res.success(std::monostate{});
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "type") {
            this->advance();

            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected type name after 'type'", this->current_tok.pos));
                return res.to_prs();
            }
            Token type_name = this->current_tok;
            this->advance();

            if (this->current_tok.type != TokenType::EQ) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected '=' after type name '" + type_name.value + "'",
                    this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();

            auto parse_type_atom = [&](Token tok) -> std::string {
                switch (tok.type) {
                    case TokenType::STRING:
                        return "string:\"" + tok.value + "\"";
                    case TokenType::INT:
                        return "int:" + tok.value;
                    case TokenType::FLOAT:
                        return "float:" + tok.value;
                    case TokenType::DOUBLE:
                        return "double:" + tok.value;
                    case TokenType::CHAR:
                        return "char:" + tok.value;
                    case TokenType::BOOL:
                        return "bool:" + tok.value;
                    case TokenType::QBOOL:
                        return "qbool:" + tok.value;
                    default:
                        return tok.value;
                }
            };

            auto is_type_or_literal_token = [&](TokenType tt) {
                return tt == TokenType::STRING ||
                    tt == TokenType::IDENTIFIER||
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
                    "Expected type or literal in type alias",
                    this->current_tok.pos));
                return res.to_prs();
            }

            std::vector<UnionMember> members;
            Token first_tok = this->current_tok;
            this->advance();
            members.push_back(UnionMember{ parse_type_atom(first_tok) });

            while (this->current_tok.type == TokenType::PIPE) {
                this->advance();

                if (!is_type_or_literal_token(this->current_tok.type)) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected type or literal after '|' in type alias",
                        this->current_tok.pos));
                    return res.to_prs();
                }

                Token t = this->current_tok;
                this->advance();
                members.push_back(UnionMember{ parse_type_atom(t) });
            }

            while (this->current_tok.type == TokenType::PIPE) {
                this->advance();

                if (this->current_tok.type != TokenType::STRING &&
                    this->current_tok.type != TokenType::KEYWORD &&
                    this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected type or literal after '|'",
                        this->current_tok.pos));
                    return res.to_prs();
                }

                Token t = this->current_tok;
                this->advance();
                members.push_back(UnionMember{ parse_type_atom(t) });
            }

            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            if (user_types.contains(type_name.value)) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Redefinition of type '" + type_name.value + "'",
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
            user_types[type_name.value] = std::move(info);
            return res.success(std::monostate{});
        }
        if (tok.type == TokenType::KEYWORD && tok.value == "enum") {
            this->advance();

            if (this->current_tok.type != TokenType::IDENTIFIER) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected enum name", this->current_tok.pos));
                return res.to_prs();
            }
            Token enum_name = this->current_tok;
            this->advance();

            if (this->current_tok.type != TokenType::LBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected '{' after enum name", this->current_tok.pos));
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
                        "Expected enum member name", this->current_tok.pos));
                    return res.to_prs();
                }
                Token member_name = this->current_tok;
                this->advance();

                if (this->current_tok.type != TokenType::EQ) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected '=' after enum member name '" + member_name.value + "'",
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
                        "Expected ';' after enum member", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
            }

            if (this->current_tok.type != TokenType::RBRACE) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Expected '}' at end of enum", this->current_tok.pos));
                return res.to_prs();
            }
            this->advance();
            if (user_types.contains(enum_name.value)) {
                res.failure(std::make_unique<InvalidSyntaxError>(
                    "Redefinition of type '" + enum_name.value + "'",
                    enum_name.pos));
                return res.to_prs();
            }

            UserTypeInfo info;
            info.kind = UserTypeKind::Union;
            info.members = std::move(members);
            info.enumEntries = std::move(entries);
            info.namespace_path = currentNamespace;
            user_types[enum_name.value] = std::move(info);

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
                        "Expected type after 'const'", this->current_tok.pos));
                    return res.to_prs();
                }
            }
            
            Token name_tok;
            Token type_tok = tok;
            this->advance();
            if (type_tok.value == "short" || type_tok.value == "long") {
                std::string modifier = type_tok.value;
                
                if (this->current_tok.type != TokenType::KEYWORD) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected type after " + modifier, this->current_tok.pos));
                    return res.to_prs();
                }
                
                Token base_type = this->current_tok;
                this->advance();
                
                type_tok.value = modifier + " " + base_type.value;
                type_tok.pos = base_type.pos;
            }

            if (type_tok.value == "map" && this->current_tok.type == TokenType::LESS) {
                this->advance();
                
                if (this->current_tok.type != TokenType::KEYWORD) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected key type in map<K, V>", this->current_tok.pos));
                    return res.to_prs();
                }
                Token key_type = this->current_tok;
                this->advance();
                
                if (this->current_tok.type != TokenType::COMMA) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected ',' in map<K, V>", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                
                if (this->current_tok.type != TokenType::KEYWORD) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected value type in map<K, V>", this->current_tok.pos));
                    return res.to_prs();
                }
                Token value_type = this->current_tok;
                this->advance();
                
                if (this->current_tok.type != TokenType::MORE) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected '>' in map<K, V>", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected variable name", this->current_tok.pos));
                    return res.to_prs();
                }
                Token var_name = this->current_tok;
                this->advance();
                
                std::vector<std::pair<AnyNode, AnyNode>> init_pairs;
                
                if (this->current_tok.type == TokenType::EQ) {
                    this->advance();
                    
                    if (this->current_tok.type != TokenType::LBRACE) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Expected '{' for map initialization", this->current_tok.pos));
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
            if (type_tok.value == "list" && this->current_tok.type == TokenType::LESS) {
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
                
                type_tok = Token(
                    TokenType::KEYWORD,
                    "list<" + elem_type.value + ">",
                    type_tok.pos
                );
            }
            bool is_list = false;
            while (this->current_tok.type == TokenType::LBRACKET) {
                this->advance();
                if (this->current_tok.type != TokenType::RBRACKET) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "QC-S049: Expected ']'", this->current_tok.pos));
                    return res.to_prs();
                }
                this->advance();
                type_tok.value += "[]";
                is_list = true;
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
                    
                    if (this->current_tok.type != TokenType::KEYWORD && !(this->user_types.count(this->current_tok.value) > 0)) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Expected type", this->current_tok.pos));
                        return res.to_prs();
                    }
                    
                    return_types.push_back(this->current_tok);
                    this->advance();
                }
                
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected identifier", this->current_tok.pos));
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
                    "Expected identifier", this->current_tok.pos));
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
            if (is_list) {
                AnyNode value;
                if (this->current_tok.type == TokenType::EQ) {
                    this->advance();
                    value = res.reg(this->qout_expr());
                    if (res.error) return res.to_prs();
                } else {
                    if (is_const) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "const variables must be initialized", name_tok.pos));
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
                            "const variables must be initialized", name_tok.pos));
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
            std::vector<Token> var_names = {name_tok};

            while (this->current_tok.type == TokenType::COMMA) {
                this->advance();
                
                if (this->current_tok.type != TokenType::KEYWORD) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected type", this->current_tok.pos));
                    return res.to_prs();
                }
                return_types.push_back(this->current_tok);
                this->advance();
                
                if (this->current_tok.type != TokenType::IDENTIFIER) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Expected identifier", this->current_tok.pos));
                    return res.to_prs();
                }
                var_names.push_back(this->current_tok);
                this->advance();
            }

            AnyNode value;
            if (this->current_tok.type == TokenType::LPAREN) {
                auto func_def = res.reg(this->func_def_multi(return_types, std::make_optional(var_names[0])));
                if (res.error) return res.to_prs();
                return res.success(std::move(func_def));
            }
            if (this->current_tok.type == TokenType::EQ) {
                this->advance();
                value = res.reg(this->qout_expr());
                if (res.error) return res.to_prs();
            } else {
                if (is_const) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "const variables must be initialized", var_names[0].pos));
                    return res.to_prs();
                }
                value = default_value_for_type(type_tok, var_names[0].pos);
            }
            
            if (this->current_tok.type != TokenType::SEMICOLON) {
                res.failure(std::make_unique<MissingSemicolonError>(this->current_tok.pos));
                return res.to_prs();
            }

            this->advance();  
            
            if (return_types.size() > 1 || var_names.size() > 1) {
                if (return_types.size() != var_names.size()) {
                    res.failure(std::make_unique<InvalidSyntaxError>(
                        "Number of types must match number of variables", var_names[0].pos));
                    return res.to_prs();
                }
                return res.success(std::make_unique<MultiVarDeclNode>(
                    is_const, return_types, var_names, std::move(value)));
            } else {
                return res.success(std::make_unique<VarAssignNode>(
                    is_const, return_types[0], var_names[0], std::move(value)));
            }
        }
        if (tok.type == TokenType::IDENTIFIER) {
            size_t saved_index = this->index;
            Token saved_tok = this->current_tok;
            auto maybe_qualified = this->try_parse_qualified_name();
            if (maybe_qualified.has_value()) {
                std::string qualified_name = *maybe_qualified;
                std::string ns_part = "";
                std::string type_name = qualified_name;

                size_t last_colon = qualified_name.rfind("::");
                if (last_colon != std::string::npos) {
                    ns_part = qualified_name.substr(0, last_colon);
                    type_name = qualified_name.substr(last_colon + 2);
                }

                bool is_type = false;
                if (user_types.count(type_name) > 0) {
                    auto& info = user_types[type_name];

                    if (ns_part.empty()) {
                        is_type = (info.namespace_path == currentNamespace);
                    }
                    else {
                        is_type = (info.namespace_path == ns_part);
                    }
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
                    
                    std::vector<Token> return_types;
                    return_types.push_back(first_type);
                    if (this->current_tok.type == TokenType::COMMA) {
                        while (this->current_tok.type == TokenType::COMMA) {
                            this->advance();

                            if (this->current_tok.type == TokenType::KEYWORD) {
                                return_types.push_back(this->current_tok);
                                this->advance();
                            } else if (this->current_tok.type == TokenType::IDENTIFIER) {
                                auto next_qual = this->try_parse_qualified_name();
                                if (next_qual.has_value() && 
                                    (is_known_type(*next_qual) || 
                                    is_known_qualified_type(*next_qual) ||
                                    user_types.count(*next_qual) > 0)) {
                                    return_types.push_back(this->consume_qualified_name());
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
                        }
                    }

                    if (this->current_tok.type != TokenType::IDENTIFIER) {
                        res.failure(std::make_unique<InvalidSyntaxError>(
                            "Expected name after types", this->current_tok.pos));
                        return res.to_prs();
                    }

                    Token name_tok = this->current_tok;
                    this->advance();

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
                    if (arg->name_tok.has_value() && arg->name_tok->value == "main") {
                        if (arg->return_types.empty() || arg->return_types[0].value != "int") {
                            std::string actual = arg->return_types.empty() ? "void" : arg->return_types[0].value;
                            throw InvalidSyntaxError("main() must return int, not " + actual, 
                                                    arg->return_types.empty() ? Position() : arg->return_types[0].pos);
                        }
                        if (!arg->params.empty()) {
                            throw InvalidSyntaxError("main() must have no parameters", 
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
                "Missing main function", 
                "Program must have an 'int main()' function", 
                Position())};
        }
        for (auto& [name, ut] : user_types) {
        if (ut.kind == UserTypeKind::Class && !ut.baseClassName.empty()) {
            auto it = user_types.find(ut.baseClassName);
                if (it == user_types.end() || it->second.kind != UserTypeKind::Class) {
                    throw InvalidSyntaxError("class inherates from a non class or non-existant object", Position()); 
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
    bool Interpreter::is_truthy(const NumberVariant& val) {
        return std::visit([this](auto&& v) -> bool {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, BoolValue>) {
                return v.value;
            } else if constexpr (std::is_same_v<T, QBoolValue>) {
                return v.tval;
            } else if constexpr (std::is_same_v<T, Number<int>> || 
                                std::is_same_v<T, Number<float>> || 
                                std::is_same_v<T, Number<double>>) {
                return v.value != 0;
            } else if constexpr (std::is_same_v<T, StringValue>) {
                return !v.value.empty();
            } else if constexpr (std::is_same_v<T, MultiValue>) { 
                return true; 
            } else if constexpr (std::is_same_v<T, std::shared_ptr<InstanceValue>>) { 
                auto inst = v;
                const std::string& className = inst->class_name;

                ClassMethodInfo* method = find_method_on_class(className, "eval");
                if (!method) {
                    this->errors.push_back({RTError(
                        "Instance of '" + className +
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
        for (auto it = frames.rbegin(); it != frames.rend(); ++it) {
            auto sym_it = it->find(qualify(name));
            if (sym_it != it->end()) {
                if (sym_it->second.is_const) {
                    throw RTError("QC-T001: Cannot assign to const variable '" + name + "'", pos);
                }
                
                std::string expected = sym_it->second.declared_type;
                std::string actual = get_type_name(new_val);
                
                std::string lookup_type = expected;
                auto ut_it = user_types.find(lookup_type);
                
                if (ut_it == user_types.end()) {
                    size_t last_colon = lookup_type.rfind("::");
                    if (last_colon == std::string::npos && !namespaceStack.empty()) {
                        std::string qualified = "";
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
                    
                    sym_it->second.value = std::move(new_val);
                    return;
                }
                
                auto get_base = [](const std::string& t) {
                    size_t pos = t.rfind("::");
                    return (pos != std::string::npos) ? t.substr(pos + 2) : t;
                };
                
                if (get_base(expected) != get_base(actual) && expected != actual) {
                    throw RTError("QC-T003: Type mismatch: cannot assign " + actual + " to " + expected, pos);
                }
                
                sym_it->second.value = std::move(new_val);
                return;
            }
        }
        
        if (name.find("::") != std::string::npos) {
            for (auto it = frames.rbegin(); it != frames.rend(); ++it) {
                auto sym_it = it->find(name);
                if (sym_it != it->end()) {
                    if (sym_it->second.is_const) {
                        throw RTError("QC-T001: Cannot assign to const variable '" + name + "'", pos);
                    }
                    
                    std::string expected = sym_it->second.declared_type;
                    std::string actual = get_type_name(new_val);
                    
                    std::string lookup_type = expected;
                    auto ut_it = user_types.find(lookup_type);
                    
                    if (ut_it == user_types.end()) {
                        size_t last_colon = lookup_type.rfind("::");
                        if (last_colon == std::string::npos && !namespaceStack.empty()) {
                            std::string qualified = "";
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
                        
                        sym_it->second.value = std::move(new_val);
                        return;
                    }
                    
                    auto get_base = [](const std::string& t) {
                        size_t pos = t.rfind("::");
                        return (pos != std::string::npos) ? t.substr(pos + 2) : t;
                    };
                    
                    if (get_base(expected) != get_base(actual) && expected != actual) {
                        throw RTError("QC-T003: Type mismatch: cannot assign " + actual + " to " + expected, pos);
                    }
                    
                    sym_it->second.value = std::move(new_val);
                    return;
                }
            }
        }
        
        throw RTError("QC-C001: Undefined variable: '" + name + "'", pos);
    }
    NumberVariant def_value_for_type(const std::string& type_name) {
        if (type_name == "int") return Number<int>(0);
        else if (type_name == "float") return Number<float>(0.0f);
        else if (type_name == "double") return Number<double>(0.0);
        else if (type_name == "string") return StringValue("");
        else if (type_name == "char") return CharValue("");
        else if (type_name == "bool") return BoolValue("");
        else if (type_name == "qbool") return QBoolValue("");
        if (type_name == "short int")    return Number<short>(0);
        if (type_name == "long int")     return Number<long long>(0);
        if (type_name == "long double")  return Number<long double>(0.0L);
        else return VoidValue();
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
                        "Instance of '" + className +
                        "' printed, but missing repr function: calling base print.", Position()),
                        "Warning"});
                    return v->print();
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
        if (a.index() != b.index()) {
            throw RTError("Cannot compare values of different types in switch/case", pos);
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
                std::is_same_v<T, Number<double>>
            ) {
                return static_cast<double>(v.value)
                    == static_cast<double>(std::get<T>(b).value);
            } else if constexpr (std::is_same_v<T, std::shared_ptr<MultiValue>>) {
                throw RTError("Cannot compare multi-values in switch", pos);
            } else {
                throw RTError("Invalid switch comparison type", pos);
            }
        }, a);
    }
    NumberVariant Interpreter::operator()(std::unique_ptr<NamespaceNode>& node) {
        context->push_namespace(node->name);

        for (auto& stmt : node->body) {
            this->process(stmt);
        }

        context->pop_namespace();
        return VoidValue();
    }

    NumberVariant Interpreter::process(AnyNode& node) {
        try {
            if (this->errors.size() > 50) {
                throw RTError("Too many errors! Execution stopped.", Position());
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
        this->errors.push_back({RTError("Unexpected 'break' outside loop or switch", node->tok.pos), "Warning"});
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
            this->errors.push_back({RTError("Nested struct initializer size mismatch for '" + struct_type + "'", {}), "Error"});
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
                        {}
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
                        {}
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
                        "Expected map initializer for field '" + field.name +
                        "' of type '" + field.type + "'",
                        {}
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
                        {}
                    ), "Error"});
                }
            }

            sv->fields[field.name] = elemVal;
        }

        return sv;
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
                                    "Expected map initializer for field '" + field.name +
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

                if (!ok) {
                    this->errors.push_back({RTError(
                        "QC-T004: Type mismatch: value of type " + valType +
                        " is not assignable to union type '" + node->type_tok.value + "'",
                        Position()
                    ), "Error"});
                }

                actualType = node->type_tok.value;
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
            if (!type_matches) {
                this->errors.push_back({RTError(
                    "QC-T003: Type mismatch: expected " + declaredType + ", got " + actualType,
                    node->var_name_tok.pos
                ), "Error"});
            }
        }

        context->define(node->var_name_tok.value, 
                        declaredType == "auto" ? actualType : declaredType, 
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
        this->errors.push_back({RTError("Unexpected 'continue' outside loop", node ? node->tok.pos : Position()), "Warning"});
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
    NumberVariant Interpreter::operator()(std::unique_ptr<QOutExprNode>& node) {
        if (!node) return Number<int>(0);

        for (auto& val : node->values) {
            NumberVariant result = this->process(val);
            std::cout << this->value_to_string(result);
        }

        return Number<int>(0);
    }
    NumberVariant Interpreter::operator()(QOutNode& node) {
        return std::move(Number<int>(0));
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
    NumberVariant Interpreter::operator()(std::unique_ptr<CallNode>& node) {
        if (!node) return Number<int>(0);

        NumberVariant target_val;
        std::string func_name = "<anonymous>";
        std::vector<NumberVariant> final_args;
        if (std::holds_alternative<std::unique_ptr<VarAccessNode>>(node->node_to_call)) {
            auto& varacc = std::get<std::unique_ptr<VarAccessNode>>(node->node_to_call);
            func_name = varacc->var_name_tok.value;
            if (func_name == "throw") {
                if (node->arg_nodes.size() != 1) {
                    this->errors.push_back({RTError("QC-B001: throw() requires exactly 1 argument", get_pos(target_val)), "Error"});
                }
                
                NumberVariant value = this->process(node->arg_nodes.front());
                std::string msg = std::visit([](auto&& v) -> std::string {
                    if constexpr (requires { v->print(); }) {
                        return v->print();
                    } else {
                        return v.print();
                    }
                }, value);
                throw RTError(msg, get_pos(value));
            }
            if (func_name == "print" || func_name == "println") {
                for (auto& arg : node->arg_nodes)
                    std::cout << this->value_to_string(this->process(arg));
                if (func_name == "println") std::cout << std::endl;
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
                        std::vector<NumberVariant> final_args;
                        for (auto& arg : node->arg_nodes) {
                            if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&arg)) {
                                NumberVariant sv = this->process((*spread)->expr);
                                if (auto arr = std::get_if<std::shared_ptr<ArrayValue>>(&sv)) {
                                    for (auto& e : (*arr)->elements) final_args.push_back(e);
                                } else if (auto lst = std::get_if<std::shared_ptr<ListValue>>(&sv)) {
                                    for (auto& e : (*lst)->elements) final_args.push_back(e);
                                } else {
                                    this->errors.push_back({RTError("QC-I005: Spread target must be array or list", get_pos(sv)), "Error"});
                                }
                            } else {
                                final_args.push_back(this->process(arg));
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
                for (auto& arg : node->arg_nodes) {
                    if (auto spread = std::get_if<std::unique_ptr<SpreadNode>>(&arg)) {
                        NumberVariant sv = this->process((*spread)->expr);
                        if (auto arr = std::get_if<std::shared_ptr<ArrayValue>>(&sv)) {
                            for (auto& e : (*arr)->elements) final_args.push_back(e);
                        } else if (auto lst = std::get_if<std::shared_ptr<ListValue>>(&sv)) {
                            for (auto& e : (*lst)->elements) final_args.push_back(e);
                        } else {
                            this->errors.push_back({RTError("QC-I005: Spread target must be array or list", get_pos(sv)), "Error"});
                        }
                    } else {
                        final_args.push_back(this->process(arg));
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
                }

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

        for (auto& arg : node->arg_nodes) {

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
                    this->errors.push_back({RTError("QC-I005: Spread target must be array or list", get_pos(spread_val)), "Error"});
                }
            }
            else {
                final_args.push_back(this->process(arg));
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
                NumberVariant value;
                auto it_param = func->params.begin();
                std::advance(it_param, i);

                if (i < final_args.size()) {
                    value = final_args[i];
                }
                else if (it_param->default_value.has_value()) {
                    value = this->process(it_param->default_value.value());
                }
                else this->errors.push_back({RTError("QC-C003: Missing argument", Position()), "Error"});

                
                std::string expected_type = it_param->type.value;
                std::string actual_type = context->get_type_name(value);


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
                    }
                    if (!types_compatible) {
                        if (expected_type.find("list<") != std::string::npos && actual_type.find("list<") != std::string::npos) {
                            std::string expected_base = expected_type;
                            std::string actual_base = actual_type;

                            auto clean_type = [](std::string& s) {
                                std::erase_if(s, [](char c) { 
                                    return c == '[' || c == ']' || c == ' '; 
                                });

                                size_t pos;
                                while ((pos = s.find("list<")) != std::string::npos) {
                                    s.erase(pos, 5);
                                }

                                while ((pos = s.find(">")) != std::string::npos) {
                                    s.erase(pos, 1);
                                }
                            };

                            clean_type(expected_base);
                            clean_type(actual_base);


                            if (actual_base == expected_base) {
                                types_compatible = true;
                            }
                        }
                        else if (expected_type.find("[]") != std::string::npos) {
                            size_t bracket_pos = expected_type.find('[');
                            std::string expected_base = expected_type.substr(0, bracket_pos);
                            
                            if (actual_type.find("list<") == std::string::npos &&  
                                actual_type.find(expected_base) == 0) {            
                                types_compatible = true;
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
            return VoidValue{};
        }
        if (method->access == "protected" && !in_class_or_derived_context(className)) {
            this->errors.push_back({RTError(
                "Method '" + mname + "' of class '" + className +
                "' is protected and cannot be called here",
                pos),
                "Error"});
            return VoidValue{};
        }

        context->push_scope();
        context->define("this", className, inst, true);

        if (args.size() > method->params.size()) {
            context->pop_scope();
            this->errors.push_back({RTError(
                "QC-C002: Too many arguments to method '" + mname + "'",
                pos),
                "Error"});
            return VoidValue{};
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

            context->define(it_param->name.value, it_param->type.value, value);
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
        if (!node) return std::move(Number<int>(0));
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
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
                ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, "operator&&");
                if (method) {
                    NumberVariant right = std::move(this->process(node->right_node));
                    return call_instance_method(*inst_ptr, method, {right}, node->op_tok.pos);
                }
            }
            
            if (!is_truthy(left)) return BoolValue("false");
            
            NumberVariant right = std::move(this->process(node->right_node));
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, "operator&&");
                if (method) {
                    return call_instance_method(*inst_ptr, method, {left}, node->op_tok.pos);
                }
            }
            
            return BoolValue(is_truthy(right) ? "true" : "false");
        }

        if (node->op_tok.type == TokenType::OR) {
            NumberVariant left = std::move(this->process(node->left_node));
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
                ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, "operator||");
                if (method) {
                    NumberVariant right = std::move(this->process(node->right_node));
                    return call_instance_method(*inst_ptr, method, {right}, node->op_tok.pos);
                }
            }
            
            if (is_truthy(left)) return BoolValue("true");
            
            NumberVariant right = std::move(this->process(node->right_node));
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, "operator||");
                if (method) {
                    return call_instance_method(*inst_ptr, method, {left}, node->op_tok.pos);
                }
            }
            
            return BoolValue(is_truthy(right) ? "true" : "false");
        }

        if (node->op_tok.type == TokenType::XOR) {
            NumberVariant left = std::move(this->process(node->left_node));
            NumberVariant right = std::move(this->process(node->right_node));
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
                ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, "operator^");
                if (method) {
                    return call_instance_method(*inst_ptr, method, {right}, node->op_tok.pos);
                }
            }
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, "operator^");
                if (method) {
                    return call_instance_method(*inst_ptr, method, {left}, node->op_tok.pos);
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
                std::string mname = "operator&&&";
                if (!mname.empty()) {
                    ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                    if (method) {
                        NumberVariant result = call_instance_method(
                            *inst_ptr,
                            method,
                            std::vector<NumberVariant>{ right },
                            node->op_tok.pos
                        );
                        return result;
                    }
                }
            }
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                std::string mname = "operator&&&";
                if (!mname.empty()) {
                    ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                    if (method) {
                        NumberVariant result = call_instance_method(
                            *inst_ptr,
                            method,
                            std::vector<NumberVariant>{ left },
                            node->op_tok.pos
                        );
                        return result;
                    }
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
                std::string mname = "operator|||";
                if (!mname.empty()) {
                    ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                    if (method) {
                        NumberVariant result = call_instance_method(
                            *inst_ptr,
                            method,
                            std::vector<NumberVariant>{ right },
                            node->op_tok.pos
                        );
                        return result;
                    }
                }
            }
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                std::string mname = "operator|||";
                if (!mname.empty()) {
                    ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                    if (method) {
                        NumberVariant result = call_instance_method(
                            *inst_ptr,
                            method,
                            std::vector<NumberVariant>{ left },
                            node->op_tok.pos
                        );
                        return result;
                    }
                }
            }
            auto l_qb = std::get_if<QBoolValue>(&left);
            auto r_qb = std::get_if<QBoolValue>(&right);
            
            if (l_qb && r_qb) {
                // Quantum OR: if at least one side is both: both
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
                std::string mname = "operator^^";
                if (!mname.empty()) {
                    ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                    if (method) {
                        NumberVariant result = call_instance_method(
                            *inst_ptr,
                            method,
                            std::vector<NumberVariant>{ right },
                            node->op_tok.pos
                        );
                        return result;
                    }
                }
            }
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                std::string mname = "operator^^";
                if (!mname.empty()) {
                    ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                    if (method) {
                        NumberVariant result = call_instance_method(
                            *inst_ptr,
                            method,
                            std::vector<NumberVariant>{ left },
                            node->op_tok.pos
                        );
                        return result;
                    }
                }
            }
            auto l_qb = std::get_if<QBoolValue>(&left);
            auto r_qb = std::get_if<QBoolValue>(&right);
            
            if (l_qb && r_qb) {
                // Quantum XOR: if one side is true or both: both
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
                return QBoolValue(std::string("both"));
            }
        }
        if (node->op_tok.type == TokenType::COLLAPSE_AND) { 
            NumberVariant left = this->process(node->left_node);
            NumberVariant right = this->process(node->right_node);
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
                std::string mname = "operator&|&";
                if (!mname.empty()) {
                    ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                    if (method) {
                        NumberVariant result = call_instance_method(
                            *inst_ptr,
                            method,
                            std::vector<NumberVariant>{ right },
                            node->op_tok.pos
                        );
                        return result;
                    }
                }
            }
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                std::string mname = "operator&|&";
                if (!mname.empty()) {
                    ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                    if (method) {
                        NumberVariant result = call_instance_method(
                            *inst_ptr,
                            method,
                            std::vector<NumberVariant>{ left },
                            node->op_tok.pos
                        );
                        return result;
                    }
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
                std::string mname = "operator|&|";
                if (!mname.empty()) {
                    ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                    if (method) {
                        NumberVariant result = call_instance_method(
                            *inst_ptr,
                            method,
                            std::vector<NumberVariant>{ right },
                            node->op_tok.pos
                        );
                        return result;
                    }
                }
            }
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
                std::string mname = "operator|&|";
                if (!mname.empty()) {
                    ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                    if (method) {
                        NumberVariant result = call_instance_method(
                            *inst_ptr,
                            method,
                            std::vector<NumberVariant>{ left },
                            node->op_tok.pos
                        );
                        return result;
                    }
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
        if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&left)) {
            std::string mname = op_method_name(node->op_tok.type);
            if (!mname.empty()) {
                ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                if (method) {
                    NumberVariant result = call_instance_method(
                        *inst_ptr,
                        method,
                        std::vector<NumberVariant>{ right },
                        node->op_tok.pos
                    );
                    return result;
                }
            }
        }
        if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&right)) {
            std::string mname = op_method_name(node->op_tok.type);
            if (!mname.empty()) {
                ClassMethodInfo* method = find_method_on_class((*inst_ptr)->class_name, mname);
                if (method) {
                    NumberVariant result = call_instance_method(
                        *inst_ptr,
                        method,
                        std::vector<NumberVariant>{ left },
                        node->op_tok.pos
                    );
                    return result;
                }
            }
        }
        return std::visit([this, &node](const auto& L, const auto& R) -> NumberVariant {
            using T1 = std::decay_t<decltype(L)>;
            using T2 = std::decay_t<decltype(R)>;

            if (node->is_f) {
                auto to_string_variant = [this](auto const& v) -> std::string {
                    using T = std::decay_t<decltype(v)>;

                    if constexpr (std::is_same_v<T, Number<int>> ||
                                std::is_same_v<T, Number<double>> ||
                                std::is_same_v<T, Number<float>>) {
                        return std::to_string(v.value);
                    } else if constexpr (std::is_same_v<T, CharValue>) {
                        return std::string(1, v.value);
                    } else if constexpr (std::is_same_v<T, BoolValue>) {
                        return v.value ? "true" : "false";
                    } else if constexpr (std::is_same_v<T, QBoolValue>) {
                        return v.valname;
                    } else if constexpr (std::is_same_v<T, StringValue>) {
                        return v.value;
                    } else if constexpr (std::is_same_v<T, VoidValue>) {
                        return "<void>";
                    } else if constexpr (std::is_same_v<T, std::shared_ptr<ArrayValue>> ||
                                        std::is_same_v<T, std::shared_ptr<ListValue>> ||
                                        std::is_same_v<T, std::shared_ptr<MultiValue>>) {
                        return v ? v->print() : "<null>";
                    } else if constexpr (std::is_same_v<T, std::shared_ptr<InstanceValue>>) {
                        auto inst = v;
                        const std::string& className = inst->class_name;
                        ClassMethodInfo* method = find_method_on_class(className, "repr");
                        if (!method) {
                            this->errors.push_back({RTError(
                                "Instance of '" + className +
                                "' printed, but missing repr function: calling base print.", Position()),
                                "Warning"});
                            return v->print();
                        }
                        NumberVariant result = call_instance_method(
                            inst,
                            method,
                            {},
                            Position()
                        );
                        if (auto s = std::get_if<StringValue>(&result)) {
                            return s->value;
                        }

                        this->errors.push_back({RTError(
                            "repr() on class '" + className + "' must return string",
                            Position()),
                            "Error"});
                        return v->print();
                    } else {
                        return "<unknown>";
                    }
                };

                std::string l_str = to_string_variant(L);
                std::string r_str = to_string_variant(R);
                return std::move(StringValue(l_str + r_str).set_pos(node->op_tok.pos));
            }
            
            if (node->op_tok.type == TokenType::EQ_TO) {
                try {
                    return BoolValue(values_equal(L, R, node->op_tok.pos) ? "true" : "false");
                } catch (RTError& e) {
                    return BoolValue("false");
                } 
            }
            if (node->op_tok.type == TokenType::NOT_EQ) {
                try {
                    return BoolValue(!values_equal(L, R, node->op_tok.pos) ? "true" : "false");
                } catch (RTError& e) {
                    return BoolValue("false");
                }
            }
            if constexpr (std::is_same_v<T1, StringValue> && std::is_same_v<T2, StringValue>) {
                if (node->op_tok.type == TokenType::PLUS) {
                    return std::move(StringValue(L.value + R.value).set_pos(node->op_tok.pos));
                }
                this->errors.push_back({RTError("Only '+' and logical expresions are supported for strings", node->op_tok.pos), "Error"});
            } else if constexpr (std::is_same_v<T1, StringValue> ^ std::is_same_v<T2, StringValue>) {
                this->errors.push_back({RTError("Cannot preform operations on string and number", node->op_tok.pos), "Error"});
            } else if constexpr (std::is_same_v<T1, CharValue> || std::is_same_v<T2, CharValue>) {
                this->errors.push_back({RTError("Cannot preform arithmetic on a Char", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::monostate> || std::is_same_v<T2, std::monostate>) {
                this->errors.push_back({RTError("Operation on uninitialized value", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, BoolValue> || std::is_same_v<T2, BoolValue>) { 
                this->errors.push_back({RTError("Cannot preform arithmetic operations on a Boolean", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, QBoolValue> || std::is_same_v<T2, QBoolValue>) { 
                this->errors.push_back({RTError("Cannot preform arithmetic operations on a Quantum Boolean", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, FunctionValue> || std::is_same_v<T2, FunctionValue>) { 
                this->errors.push_back({RTError("Cannot preform arithmetic operations on a Function", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, VoidValue> || std::is_same_v<T2, VoidValue>) { 
                this->errors.push_back({RTError("Cannot preform arithmetic operations on nothing", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<ArrayValue>> || std::is_same_v<T2, std::shared_ptr<ArrayValue>>) { 
                this->errors.push_back({RTError("Cannot preform arithmetic operations on arrays", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<ListValue>> || std::is_same_v<T2, std::shared_ptr<ListValue>>) { 
                this->errors.push_back({RTError("Cannot preform arithmetic operations on lists", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<MapValue>> || std::is_same_v<T2, std::shared_ptr<MapValue>>) { 
                this->errors.push_back({RTError("Cannot preform arithmetic operations on a map/dict", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<StructValue>> || std::is_same_v<T2, std::shared_ptr<StructValue>>) { 
                this->errors.push_back({RTError("Cannot preform arithmetic operations on a Struct", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<MultiValue>> || 
                            std::is_same_v<T2, std::shared_ptr<MultiValue>>) {
                this->errors.push_back({RTError("Cannot perform arithmetic on multi-return values", node->op_tok.pos), "Error"});
            }
            else if constexpr (std::is_same_v<T1, std::shared_ptr<InstanceValue>> || 
                            std::is_same_v<T2, std::shared_ptr<InstanceValue>>) {
                this->errors.push_back({RTError("Cannot perform arithmetic on classes", node->op_tok.pos), "Error"});
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
    NumberVariant Interpreter::operator()(std::unique_ptr<AssignExprNode>& node) {
        if (!node) return Number<int>(0);
        
        
        NumberVariant value = std::move(this->process(node->value));
        std::string name = node->var_name.value;
        
        if (name.find("::") != std::string::npos) {
            for (auto it = context->frames.rbegin(); it != context->frames.rend(); ++it) {
                auto sym_it = it->find(name);
                if (sym_it != it->end()) {
                    if (sym_it->second.is_const) {
                        throw RTError("QC-T001: Cannot assign to const variable '" + name + "'", node->var_name.pos);
                    }
                    if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&sym_it->second.value)) {
                        std::cerr << "AssignExprNode found class wiht qualification" << '\n';
                        std::string class_name = (*inst_ptr)->class_name;
                        auto ut_it = context->user_types.find(class_name);
                        
                        if (ut_it != context->user_types.end() && 
                            ut_it->second.kind == UserTypeKind::Class) {
                            
                            // Look for operator= method
                            ClassMethodInfo* op_assign = nullptr;
                            for (auto& m : ut_it->second.classMethods) {
                                if (m.name_tok.value == "operator=") {
                                    op_assign = &m;
                                    break;
                                }
                            }
                            
                            if (op_assign) {
                                NumberVariant result = call_instance_method(
                                    *inst_ptr,
                                    op_assign,
                                    std::vector<NumberVariant>{ std::move(value) },
                                    node->var_name.pos
                                );
                                return result;
                            }
                        }
                    }
                    std::string declared_type = sym_it->second.declared_type;
                    std::string actual_type = context->get_type_name(value);
                    
                    std::string lookup_type = declared_type;
                    auto ut_it = context->user_types.find(lookup_type);
                    
                    if (ut_it == context->user_types.end()) {
                        size_t last_colon = lookup_type.rfind("::");
                        if (last_colon == std::string::npos && !context->namespaceStack.empty()) {
                            std::string qualified = "";
                            for (auto& ns : context->namespaceStack) {
                                if (!qualified.empty()) qualified += "::";
                                qualified += ns;
                            }
                            lookup_type = qualified + "::" + declared_type;
                            ut_it = context->user_types.find(lookup_type);
                        }
                    }
                    
                    if (ut_it == context->user_types.end()) {
                        for (auto& [type_name, info] : context->user_types) {
                            if (type_name == declared_type || 
                                type_name.find("::" + declared_type) != std::string::npos) {
                                ut_it = context->user_types.find(type_name);
                                break;
                            }
                        }
                    }
                    
                    if (ut_it != context->user_types.end() && 
                        ut_it->second.kind == UserTypeKind::Union) {
                        
                        auto& members = ut_it->second.members;
                        bool ok = false;
                        
                        for (auto& m : members) {
                            if (value_matches_union_member(m.type, actual_type, value)) {
                                ok = true;
                                break;
                            }
                        }
                        
                        if (!ok) {
                            throw RTError(
                                "QC-T004: Type mismatch: value of type " + actual_type +
                                " is not assignable to union type '" + declared_type + "'",
                                node->var_name.pos
                            );
                        }
                        
                        sym_it->second.value = std::move(value);
                        return value;
                    }
                    
                    auto get_base = [](const std::string& t) {
                        size_t pos = t.rfind("::");
                        return (pos != std::string::npos) ? t.substr(pos + 2) : t;
                    };
                    
                    if (get_base(declared_type) != get_base(actual_type) && 
                        declared_type != actual_type) {
                        throw RTError(
                            "QC-T003: Type mismatch: cannot assign " + actual_type + " to " + declared_type,
                            node->var_name.pos
                        );
                    } // Need to make operrator = work
                    
                    sym_it->second.value = std::move(value);
                    return value;
                }
            }
            throw RTError("QC-C001: Undefined variable: '" + name + "'", node->var_name.pos);
        }
        try {
            NumberVariant existing = context->get(name, node->var_name.pos);
            
            if (auto inst_ptr = std::get_if<std::shared_ptr<InstanceValue>>(&existing)) {
                std::string class_name = (*inst_ptr)->class_name;
                auto ut_it = context->user_types.find(class_name);
                
                if (ut_it != context->user_types.end() && 
                    ut_it->second.kind == UserTypeKind::Class) {
                    ClassMethodInfo* op_assign = nullptr;
                    for (auto& m : ut_it->second.classMethods) {
                        if (m.name_tok.value == "operator=") {
                            op_assign = &m;
                            break;
                        }
                    }
                    
                    if (op_assign) {
                        NumberVariant result = call_instance_method(
                            *inst_ptr,
                            op_assign,
                            std::vector<NumberVariant>{ std::move(value) },
                            node->var_name.pos
                        );
                        return result;
                    }
                }
            }
        } catch (...) {

        }
    
        context->set(name, std::move(value), node->var_name.pos);
        return std::move(value);
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
                this->errors.push_back({RTError("Unary operator not supported for this type",
                            node->op_tok.pos), "Error"});
            }
            return VoidValue();
        }, number));
    }


    NumberVariant Interpreter::operator()(StringNode& node) {
        return std::move(StringValue(node.tok.value).set_pos(node.tok.pos));
    }
    NumberVariant Interpreter::operator()(std::monostate) {
        return std::move(Number<int>(0));
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
        bool is_array = std::holds_alternative<std::shared_ptr<ArrayValue>>(base_value);
        bool is_list  = std::holds_alternative<std::shared_ptr<ListValue>>(base_value);

        if (!is_array && !is_list)
            this->errors.push_back({RTError("QC-I003: Cannot index non-array/list type", Position()), "Error"});

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
            ClassMethodInfo* method = find_method_on_class(className, mname);
            if (!method) {
                this->errors.push_back({RTError(
                    "QC-M001: Class '" + className + "' has no method '" + mname + "'",
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
        if (!node) return Number<int>(0);

        NumberVariant base_val = this->process(node->base);

        NumberVariant rightVal = this->process(node->value);

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

            while (cur) {
                for (auto& f : cur->classFields) {
                    if (f.name == fieldName) {
                        found = true;
                        access = f.access;
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
            (*inst)->fields[fieldName] = rightVal;
            return rightVal;
        }

        if (auto s = std::get_if<std::shared_ptr<StructValue>>(&base_val)) {
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
            std::cerr << "Include error: " << e.what() << std::endl;
            return Mer{Aer{nullptr, nullptr}, Ler{std::vector<Token>{}, std::make_unique<InvalidSyntaxError>("Include Error", Position())}, ""};
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
        
        // Interpreter
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
            std::shared_ptr<FuncDefNode> main_func = ctx->get_function("main");
            if (!main_func) {
                throw RTError("No main() function found", Position());
            }
            
            auto main_call_node = std::make_unique<CallNode>(
                std::make_unique<VarAccessNode>(Token(TokenType::IDENTIFIER, "main", Position())),
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
        }
        
        delete ctx;
        return Mer{std::move(ast), std::move(resp), output, interpreter.errors};
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
            id == "final") {
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
            throw IllegalCharError("Expected closing single quote", this->pos);
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
                    throw IllegalCharError("Unclosed brace in f-string", this->pos);

                exprs.push_back(expr);
            } else {
                current += this->current_char;
                this->advance();
            }
        }

        parts.push_back(current);

        if (this->current_char != '"') throw IllegalCharError("Unterminated f-string", this->pos);
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
                        if (current_char == '*') {
                            this->advance();
                            tokens.push_back(Token(TokenType::POWER, "**", start_pos));
                            break;
                        } else if (current_char == '=') {
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
                            tokens.push_back(Token(TokenType::DEF, "&", start_pos));
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
                        return Ler {std::vector<Token>(), std::make_unique<IllegalCharError>(unknown, this->pos)};
                }
            }
        }
        tokens.push_back(Token(TokenType::EOFT, "<eof>", this->pos));
        return Ler {tokens, NULL};

    }

}
///////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES //////////////////////////////////////////////////////////////////////////////
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
        throw std::runtime_error("Could not open file: " + path);
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
        throw std::runtime_error("Namespace '" + ns_name + "' not found in file");
    }
    size_t brace_start = source.find('{', pos);
    if (brace_start == std::string::npos) {
        throw std::runtime_error("Invalid namespace syntax for '" + ns_name + "'");
    }
    int depth = 1;
    size_t i = brace_start + 1;
    while (i < source.size() && depth > 0) {
        if (source[i] == '{') depth++;
        if (source[i] == '}') depth--;
        i++;
    }
    
    if (depth != 0) {
        throw std::runtime_error("Unmatched braces in namespace '" + ns_name + "'");
    }
    
    return source.substr(pos, i - pos);
}
std::string preprocess_includes(const std::string& source, const std::string& current_file) {
    std::set<std::pair<std::string, std::string>> included_namespaces;
    std::vector<std::string> exported_blocks;
    std::vector<std::string> namespace_order;
    
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
            full_path = "/usr/local/QC/stdlib.qc";
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