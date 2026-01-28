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
#include <unordered_set>
#include <format>
#include <ranges>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <set>
#include <algorithm>
#if defined(_WIN32) || defined(_WIN64)
    #include <print>
#endif
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
    class QOutExprNode;
    class ContinueNode;
    class FuncDefNode;
    class QOutNode;
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
    using AnyNode = std::variant<
        std::monostate, 
        NumberNode, 
        StringNode,
        CharNode,
        BoolNode,
        QOutNode,
        QInNode,
        QBoolNode,
        std::unique_ptr<BinOpNode>, 
        std::unique_ptr<UnaryOpNode>,
        std::unique_ptr<VarAccessNode>,
        std::unique_ptr<VarAssignNode>,
        std::unique_ptr<AssignExprNode>,
        std::unique_ptr<IfNode>,
        std::unique_ptr<QIfNode>,
        std::unique_ptr<StatementsNode>,
        std::unique_ptr<SwitchNode>,
        std::unique_ptr<QSwitchNode>,
        std::unique_ptr<BreakNode>,
        std::unique_ptr<WhileNode>,    
        std::unique_ptr<ForNode>,       
        std::unique_ptr<ContinueNode>,   
        std::unique_ptr<CallNode>,
        std::shared_ptr<FuncDefNode>,
        std::unique_ptr<QOutExprNode>,
        std::unique_ptr<ReturnNode>,
        std::unique_ptr<MultiReturnNode>,
        std::unique_ptr<MultiVarDeclNode>,
        std::unique_ptr<ArrayDeclNode>,  
        std::unique_ptr<ListDeclNode>, 
        std::unique_ptr<ArrayLiteralNode>,     
        std::unique_ptr<ArrayAccessNode>,
        std::unique_ptr<MethodCallNode>,
        std::shared_ptr<PropertyAccessNode>,
        std::unique_ptr<SpreadNode>,
        std::unique_ptr<ForeachNode>,
        std::unique_ptr<MapDeclNode>,
        std::unique_ptr<ArrayAssignNode>,
        std::unique_ptr<SeedCallNode>,
        std::unique_ptr<RandomCallNode>,
        std::unique_ptr<FieldAssignNode>,
        std::unique_ptr<MapLiteralNode>,
        std::unique_ptr<NamespaceNode>,
        std::unique_ptr<TryCatchNode>
    >;

//////////////////////////////////////////////////////////////////////////////////////////////
// ENUMS & CONSTANTS ////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    enum class Keywords {
        INT, STRING, FLOAT, DOUBLE, CHAR, MAP, LIST, ARRAY,
        VOID, ENUM, CLASS, STRUCT, BOOL, QBOOL
    };
    
    inline std::string bad_chars = " \t\n\r";
    inline std::string DIGITS = "0123456789";
    inline std::string LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    inline std::string LETTERSDIGITS = LETTERS + DIGITS;
    
    enum class TokenType {
        INT, STRING, FLOAT, DOUBLE, CHAR, MAP, LIST, ARRAY, VOID, ENUM, CLASS, STRUCT,
        ARROW, BOOL, QBOOL, PLUS, MINUS, MUL, DIV, POWER, LPAREN, RPAREN, LSHIFT, RSHIFT,
        SCOPE, SEMICOLON, DEF, INCREMENT, DECREMENT, IDENTIFIER, KEYWORD, PLUS_EQ, MINUS_EQ,
        MUL_EQ, DIV_EQ, MOD, MOD_EQ, EQ_TO, NOT_EQ, MORE, LESS, MORE_EQ, LESS_EQ, AND, OR, XOR,
        NOT, EQ, FSTRING, SWITCH, CASE, DEFAULT, IF, ELSE, LBRACE, RBRACE, LBRACKET, RBRACKET, COLON, BREAK,
        FUNC, COMMA, DOT, AT, QAND, QOR, COLLAPSE_AND, COLLAPSE_OR, QEQEQ, QNEQ, QNOT, QXOR, PIPE, EOFT
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
        std::vector<Token> Tkns;
        std::unique_ptr<Error> error;
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
        std::unique_ptr<StatementsNode> body;
        bool is_constructor = false;
        std::string access;
        bool is_final = false;
        ClassMethodInfo() = default;

        ClassMethodInfo(ClassMethodInfo&&) = default;
        ClassMethodInfo& operator=(ClassMethodInfo&&) = default;

        ClassMethodInfo(const ClassMethodInfo&) = delete;
        ClassMethodInfo& operator=(const ClassMethodInfo&) = delete;
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
        UserTypeInfo() = default;

        UserTypeInfo(UserTypeInfo&&) = default;
        UserTypeInfo& operator=(UserTypeInfo&&) = default;

        UserTypeInfo(const UserTypeInfo&) = delete;
        UserTypeInfo& operator=(const UserTypeInfo&) = delete;
    };

        
    struct Aer {
        std::unique_ptr<StatementsNode> statements;
        std::unique_ptr<Error> error;
        std::unordered_map<std::string, UserTypeInfo> user_types;
    };
    struct Diagnostic {
        RTError error;
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
    
    class QOutNode {
    public:
        std::string print() { return "std::qout"; }
    };
    class QInNode {
    public:
        QInNode() {}
        
        std::string print() const {
            return "std::qin";
        }
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
        StringNode (Token tok);
        std::string print() const;
    };
    
    class BoolNode {
        public:
        Token tok;
        BoolNode (Token tok);
        std::string print() const;
    };
    class QBoolNode {
        public:
        Token tok;
        QBoolNode (Token tok);
        std::string print() const;
    };

//////////////////////////////////////////////////////////////////////////////////////////////
// StatementsNode ///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    class StatementsNode {
    public:
        std::vector<AnyNode> statements;
        bool is_block = false;

        StatementsNode(std::vector<AnyNode> stmts, bool is_block = false)
            : statements(std::move(stmts)), is_block(is_block) {}

        std::string print() const;
    };

//////////////////////////////////////////////////////////////////////////////////////////////
// OTHER NODES //////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    struct Parameter {
        Token type;
        Token name;
        std::optional<AnyNode> default_value;

        Parameter() = default;
        Parameter(Parameter&&) = default;
        Parameter& operator=(Parameter&&) = default;
        Parameter(const Parameter&) = delete;
        Parameter& operator=(const Parameter&) = delete;
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
            
        std::string print() const;
    };
    
    class UnaryOpNode {
    public:
        Token op_tok;
        AnyNode node;
        bool is_postfix;

        UnaryOpNode(Token op, AnyNode n, bool postfix = false)
            : op_tok(op), node(std::move(n)), is_postfix(postfix) {}
        std::string print() const;
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
        
        std::string print() const;
    };

    class VarAccessNode {
    public:
        Token var_name_tok;
        
        VarAccessNode(Token name) : var_name_tok(std::move(name)) {}
        
        std::string print() const;
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

        std::string print() const;
    };
    class QIfNode {
    public:
        std::optional<AnyNode> init;
        AnyNode condition;
        std::unique_ptr<StatementsNode> then_branch;
        std::vector<std::pair<AnyNode, std::unique_ptr<StatementsNode>>> qelif_branches;
        std::unique_ptr<StatementsNode> qelse_branch;
        
        QIfNode(std::optional<AnyNode>&& init_stmt,
                AnyNode&& cond,
                std::unique_ptr<StatementsNode>&& then_b,
                std::vector<std::pair<AnyNode, std::unique_ptr<StatementsNode>>>&& qelif_b,
                std::unique_ptr<StatementsNode>&& qelse_b)
            : init(std::move(init_stmt)),
            condition(std::move(cond)),
            then_branch(std::move(then_b)),
            qelif_branches(std::move(qelif_b)),
            qelse_branch(std::move(qelse_b)) {}
        
        std::string print() const {
            return "qif (...)";
        }
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
    class QSwitchNode {
    public:
        AnyNode value;
        std::unique_ptr<StatementsNode> case_t; 
        std::unique_ptr<StatementsNode> case_f; 
        std::unique_ptr<StatementsNode> case_n; 
        std::unique_ptr<StatementsNode> case_b; 
        
        QSwitchNode(AnyNode&& val,
                    std::unique_ptr<StatementsNode>&& t,
                    std::unique_ptr<StatementsNode>&& f,
                    std::unique_ptr<StatementsNode>&& n,
                    std::unique_ptr<StatementsNode>&& b)
            : value(std::move(val)),
            case_t(std::move(t)),
            case_f(std::move(f)),
            case_n(std::move(n)),
            case_b(std::move(b)) {}
        
        std::string print() const {
            return "qswitch (...)";
        }
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
    class TryCatchNode {
    public:
        std::unique_ptr<StatementsNode> try_body;
        std::string catch_var_name;
        std::string catch_var_type;
        std::unique_ptr<StatementsNode> catch_body;
        Token tok;
        Position pos;
        
        TryCatchNode(
            std::unique_ptr<StatementsNode> try_b,
            std::string var_name,
            std::string var_type,
            std::unique_ptr<StatementsNode> catch_b,
            Token t,
            Position p
        ) : try_body(std::move(try_b)),
            catch_var_name(var_name),
            catch_var_type(var_type),
            catch_body(std::move(catch_b)),
            tok(t),
            pos(p) {}
        std::string print() {
            return "try {\n\t" + try_body->print() + "\n} catch {\n\t" + catch_body->print() + "\n}";
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

    class FuncDefNode {
        public:
            std::vector<Token> return_types; 
            std::optional<Token> name_tok;
            std::list<Parameter> params;
            std::unique_ptr<StatementsNode> body;
            std::string namespace_path;
            Position pos;
            
            FuncDefNode(std::vector<Token> ret_types, std::optional<Token> name, 
                        std::list<Parameter> parameters, 
                        std::unique_ptr<StatementsNode> func_body,
                        std::string ns = "") 
                : return_types(std::move(ret_types)),
                name_tok(std::move(name)),
                params(std::move(parameters)),
                body(std::move(func_body)),
                namespace_path(ns) {}
            
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
    class ArrayDeclNode {
    public:
        bool is_const;
        Token type_tok;
        Token var_name_tok;
        AnyNode value;

        int dimensions;
        std::vector<std::optional<int>> sizes;

        ArrayDeclNode(bool is_const, Token type_tok, Token var_name_tok, 
              AnyNode&& value,
              int dims, std::vector<std::optional<int>> sizes)
            : is_const(is_const),
            type_tok(type_tok),
            var_name_tok(var_name_tok),
            value(std::move(value)),
            dimensions(dims),
            sizes(std::move(sizes))
        {}
        std::string print() {
            std::string type_str = type_tok.value;
            std::string name_str = var_name_tok.value;
            for (int i = 0; i < dimensions; ++i) {
                name_str += "[";
                if (sizes[i].has_value())
                    name_str += std::to_string(*sizes[i]);
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

        ListDeclNode(bool is_const, Token type_tok, Token var_name_tok, AnyNode&& value)
            : is_const(is_const),
            type_tok(type_tok),
            var_name_tok(var_name_tok),
            value(std::move(value))
        {}
        
        std::string print() {
            return type_tok.value + " " + var_name_tok.value + " = " + printAny(value);
        }
    };
    class ArrayLiteralNode {
    public:
        std::vector<AnyNode> elements;
        Position pos;
        
        ArrayLiteralNode(std::vector<AnyNode> elems, Position p)
            : elements(std::move(elems)), pos(p) {}
        
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

        MapLiteralNode(std::vector<std::pair<AnyNode, AnyNode>> p, Position pos)
            : pairs(std::move(p)), pos(pos) {}

        std::string print() const { return "map<>"; }
    };
    class ArrayAccessNode {
    public:
        AnyNode base;                    
        std::vector<AnyNode> indices;    

        ArrayAccessNode(AnyNode&& base_node, std::vector<AnyNode>&& idxs)
            : base(std::move(base_node)), indices(std::move(idxs)) {}

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
        
        MethodCallNode(AnyNode&& base_node, Token method, std::vector<AnyNode>&& arguments)
            : base(std::move(base_node)), method_name(method), args(std::move(arguments)) {}
        
        std::string print() {
            return printAny(base) + "." + method_name.value + "(...)";
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
    class PropertyAccessNode {
    public:
        std::shared_ptr<AnyNode> base; 
        Token property_name;
        Token base_name_tok;      
        PropertyAccessNode(AnyNode base_node, Token base_name, Token prop)
            : base(std::make_shared<AnyNode>(std::move(base_node))),
            base_name_tok(base_name),
            property_name(prop) {}

        std::string print() {
            return printAny(*base) + "." + property_name.value;
        }
    };
    class SpreadNode {
    public:
        AnyNode expr;
        
        SpreadNode(AnyNode&& expression)
            : expr(std::move(expression)) {}
        
        std::string print() {
            return "@" + printAny(expr);
        }
    };
    class ForeachNode {
    public:
        Token elem_type;
        Token elem_name;
        AnyNode collection;
        AnyNode body;
        
        ForeachNode(Token type, Token name, AnyNode&& coll, AnyNode&& body_stmt)
            : elem_type(type), elem_name(name), 
            collection(std::move(coll)), body(std::move(body_stmt)) {}
        
        std::string print() {
            return "foreach (" + elem_type.value + " " + elem_name.value + " in ...)";
        }
    };
    class MapDeclNode {
    public:
        bool is_const;
        Token key_type;
        Token value_type;
        Token var_name;
        std::vector<std::pair<AnyNode, AnyNode>> init_pairs;  
        
        MapDeclNode(bool is_const, Token k_type, Token v_type, Token name,
                    std::vector<std::pair<AnyNode, AnyNode>>&& pairs)
            : is_const(is_const), key_type(k_type), value_type(v_type),
            var_name(name), init_pairs(std::move(pairs)) {}
        
        std::string print() const {
            return "map<" + key_type.value + ", " + value_type.value + "> " + var_name.value;
        }
    };
    class FieldAssignNode {
    public:
        AnyNode base;       
        Token field_name;    
        AnyNode value;

        FieldAssignNode(AnyNode&& b, Token f, AnyNode&& v)
            : base(std::move(b)), field_name(f), value(std::move(v)) {}
        std::string print() const {
            return printAny(base) + "." + field_name.value + " = " + printAny(value);
        }
    };
    class ArrayAssignNode {
    public:
        AnyNode array_access;
        AnyNode value;
        
        ArrayAssignNode(AnyNode&& access, AnyNode&& val)
            : array_access(std::move(access)), value(std::move(val)) {}
        
        std::string print() const {
            return "array_assign";
        }
    };
    class RandomCallNode {
    public:
        std::vector<AnyNode> args;
        
        RandomCallNode(std::vector<AnyNode>&& a) : args(std::move(a)) {}
        
        std::string print() const {
            return "random()";
        }
    };

    class SeedCallNode {
    public:
        AnyNode value;
        
        SeedCallNode(AnyNode&& val) : value(std::move(val)) {}
        
        std::string print() const {
            return "seed()";
        }
    };
    class NamespaceNode {
        public:
        std::string name;
        std::vector<AnyNode> body;

        NamespaceNode(std::string name, std::vector<AnyNode> body)
            : name(std::move(name)), body(std::move(body)) {}
        std::string print() {
            return "namespace " + name;
        }
    };

//////////////////////////////////////////////////////////////////////////////////////////////
// PARSE RESULT /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
    class ParseResult;
    using Prs = std::variant<std::monostate, ParseResult, NumberNode, StringNode, CharNode, BoolNode, std::unique_ptr<BinOpNode>, std::unique_ptr<tkz::Error>, std::unique_ptr<UnaryOpNode>, std::unique_ptr<VarAccessNode>, std::unique_ptr<VarAssignNode>, std::unique_ptr<AssignExprNode>, std::unique_ptr<StatementsNode>, std::unique_ptr<IfNode>, std::unique_ptr<BreakNode>, std::unique_ptr<SwitchNode>, std::unique_ptr<WhileNode>, std::unique_ptr<ForNode>, std::unique_ptr<ContinueNode>, std::unique_ptr<CallNode>,
        std::shared_ptr<FuncDefNode>, QOutNode, std::unique_ptr<QOutExprNode>, std::unique_ptr<ReturnNode>,
        std::unique_ptr<MultiReturnNode>,
        std::unique_ptr<MultiVarDeclNode>,
        std::unique_ptr<ArrayDeclNode>,       
        std::unique_ptr<ArrayLiteralNode>,     
        std::unique_ptr<ArrayAccessNode>,
        std::unique_ptr<ListDeclNode>,  
        std::unique_ptr<MethodCallNode>,
        std::shared_ptr<PropertyAccessNode>,
        std::unique_ptr<SpreadNode>,
        std::unique_ptr<ForeachNode>,
        QBoolNode,
        QInNode,
        std::unique_ptr<QIfNode>,
        std::unique_ptr<QSwitchNode>,
        std::unique_ptr<MapDeclNode>,
        std::unique_ptr<ArrayAssignNode>,
        std::unique_ptr<SeedCallNode>,
        std::unique_ptr<RandomCallNode>,
        std::unique_ptr<FieldAssignNode>,
        std::unique_ptr<MapLiteralNode>,
        std::unique_ptr<NamespaceNode>,
        std::unique_ptr<TryCatchNode>
    >;
        
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
        AnyNode default_value_for_type(const Token& type_tok, const Position& pos);
        std::vector<std::string> namespaceStack;
        size_t index = 0;
        int tmp_counter = 0;
        std::unordered_map<std::string, UserTypeInfo> user_types;
        Token current_tok;
        std::vector<Token> tokens;
        std::string currentNamespace;
        Parser(std::vector<Token> tokens);
        std::string qualify_name(const std::string& name);
        bool is_known_type(const std::string& name) const {
            if (user_types.count(name)) return true;
            std::string ns;
            for (int i = (int)namespaceStack.size() - 1; i >= 0; --i) {
                ns = namespaceStack[i] + (ns.empty() ? "" : "::" + ns);
                for (auto& [k, info] : user_types) {
                    if (k == name && info.namespace_path == ns) {
                        return true;
                    }
                }
            }

            return false;
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
            if (current_tok.type != TokenType::IDENTIFIER) {
                throw InvalidSyntaxError("Expected identifier", current_tok.pos);
            }

            Position start_pos = current_tok.pos;
            std::string qualified = current_tok.value;
            this->advance();
            while (current_tok.type == TokenType::SCOPE) {
                this->advance();
                
                if (current_tok.type != TokenType::IDENTIFIER) {
                    throw InvalidSyntaxError("Expected identifier after '::'", current_tok.pos);
                }
                
                qualified += "::" + current_tok.value;
                this->advance();
            }

            return Token(TokenType::IDENTIFIER, qualified, start_pos);
        }
        
        bool is_known_qualified_type(const std::string& full) const {
            auto pos = full.rfind("::");
            if (pos == std::string::npos) return false;

            std::string ns = full.substr(0, pos);
            std::string name = full.substr(pos + 2);

            for (auto& [k, info] : user_types) {
                if (k == name && info.namespace_path == ns) {
                    return true;
                }
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
        Prs bin_op(std::function<Prs()> func, 
                   std::initializer_list<TokenType> ops);
        Prs logical_and();
        Prs qif_expr();
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
                AnyNode any_stmt = prs_to_anynode(std::move(st));
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
    class QBoolValue {
        public:
        bool tval;
        bool fval;
        std::string valname;
        Position pos;
        QBoolValue(std::string val) : pos("", "", 0, 0, 0) {
            if (!val.empty()) {
                this->valname = val;
                if (val == "qtrue") {
                    
                    this->tval = true;
                    this->fval = false;
                } else if (val == "qfalse") {
                    this->fval = true;
                    this->tval = false;
                } else if (val == "both") {
                    this->fval = true;
                    this->tval = true;
                } else if (val == "none") {
                    this->fval = false;
                    this->tval = false;
                } else {
                    throw RTError("Expected Quantum Boolean value to be qtrue qfalse both or none", pos);
                }
            } else {
                this->tval = false;
                this->fval = false;
                this->valname = "none";
            }
        }
        QBoolValue& set_pos(Position p) { 
            this->pos = p; 
            return *this; 
        }
        std::string print() const { 
            return this->valname;
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
    class ArrayValue;
    class ListValue;
    class MapValue;
    class StructValue;
    class InstanceValue;
    template <typename T> class Number;
    
    using NumberVariant = std::variant<
        Number<int>, Number<float>, Number<double>,
        Number<long long>, Number<long double>,
        Number<short>,
        StringValue, CharValue, BoolValue, QBoolValue,
        FunctionValue, VoidValue, std::shared_ptr<MultiValue>, 
        std::shared_ptr<ArrayValue>, std::shared_ptr<ListValue>,
        std::shared_ptr<MapValue>, std::shared_ptr<StructValue>,
        std::shared_ptr<InstanceValue>
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
        std::string print() const;

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
    class InstanceValue {
        public:
        std::string class_name;
        std::unordered_map<std::string, NumberVariant> fields;
        Position pos;
        InstanceValue(std::string class_name, std::unordered_map<std::string, NumberVariant> fields) {
            this->class_name = class_name;
            this->fields = fields;
            this->pos = Position("", "", 0, 0, 0);
        }
        InstanceValue(std::string class_name) {
            this->class_name = class_name;
        }
        bool equals(const InstanceValue& other,
                std::function<bool(const NumberVariant&, const NumberVariant&, const Position&)> value_eq) const {
            if (class_name != other.class_name) {
                return false;
            }
            if (fields.size() != other.fields.size()) {
                return false;
            }
            for (const auto& [field_name, value] : fields) {
                auto it = other.fields.find(field_name);
                if (it == other.fields.end()) {
                    return false;
                }
                if (!value_eq(value, it->second, pos)) {
                    return false;
                }
            }
            
            return true;
        }
        std::string print() const;
    };
    class MultiValue {
    public:
        std::vector<NumberVariant> values;
        Position pos;
        MultiValue(std::vector<NumberVariant>&& vals) : values(std::move(vals)), pos("", "", 0, 0, 0) {}
        
        std::string print() const;
    };
    class ArrayValue {
    public:
        std::string element_type;
        std::vector<NumberVariant> elements;
        std::vector<std::vector<size_t>> nested_sizes;
        Position pos;
        ArrayValue(std::string type, std::vector<NumberVariant> elems)
            : element_type(type), elements(std::move(elems)), pos("", "", 0, 0, 0)
        {
            nested_sizes.resize(elements.size());
            for (size_t i = 0; i < elements.size(); i++) {
                if (auto arr_ptr = std::get_if<std::shared_ptr<ArrayValue>>(&elements[i])) {
                    nested_sizes[i] = (*arr_ptr)->sizes();
                }
            }
        }
        size_t size() const {  
            return elements.size();
        }
        std::vector<size_t> sizes() const {
            std::vector<size_t> result = { elements.size() };
            return result; 
        }

        std::string print() const;
    };
    class ListValue {
    public:
        std::string element_type;
        std::vector<NumberVariant> elements;
        Position pos;
        ListValue(std::string type, std::vector<NumberVariant> elems)
            : element_type(type), elements(std::move(elems)), pos("", "", 0, 0, 0) {}
        
        void push(NumberVariant val) {
            elements.push_back(std::move(val));
        }
        
        NumberVariant pop() {
            if (elements.empty()) 
                throw RTError("Cannot pop from empty list", Position());
            NumberVariant val = std::move(elements.back());
            elements.pop_back();
            return val;
        }
        
        size_t length() const {
            return elements.size();
        }
        
        std::string print() const;
    };
    class MapValue {
    public:
        std::string key_type;
        std::string value_type;
        std::unordered_map<std::string, NumberVariant> data;
        Position pos;
        
        MapValue(std::string k_type, std::string v_type)
            : key_type(k_type), value_type(v_type), pos("", "", 0, 0, 0) {}
        
        MapValue& set_pos(Position p) {
            pos = p;
            return *this;
        }
        
        void set(std::string key, NumberVariant value) {
            data[key] = std::move(value);
        }
        
        NumberVariant get(std::string key) {
            if (data.find(key) == data.end()) {
                throw RTError("Key not found: " + key, pos);
            }
            return data[key];
        }
        
        bool has(std::string key) {
            return data.find(key) != data.end();
        }
        
        void remove(std::string key) {
            data.erase(key);
        }
        
        int size() {
            return data.size();
        }
        
        std::vector<std::string> keys() {
            std::vector<std::string> result;
            for (auto& [key, val] : data) {
                result.push_back(key);
            }
            return result;
        }
        bool equals(const MapValue& other, std::function<bool(const NumberVariant&, const NumberVariant&, const Position&)> value_eq) const {
            if (data.size() != other.data.size()) {
                return false;
            }
            for (const auto& [key, value] : data) {
                if (other.data.find(key) == other.data.end()) {
                    return false;
                }
                if (!value_eq(value, other.data.at(key), pos)) {
                    return false;
                }
            }
            
            return true;
        }
        std::string print() const;
    };
    class StructValue {
        public:
        std::string type_name;
        std::unordered_map<std::string, NumberVariant> fields;
        Position pos;

        StructValue(std::string t) : type_name(std::move(t)), pos("", "", 0, 0, 0) {}

        StructValue& set_pos(Position p) { pos = p; return *this; }
            bool equals(const StructValue& other,
                    std::function<bool(const NumberVariant&, const NumberVariant&, const Position&)> value_eq) const {
            if (type_name != other.type_name) {
                return false;
            }
            if (fields.size() != other.fields.size()) {
                return false;
            }
            for (const auto& [field_name, value] : fields) {
                auto it = other.fields.find(field_name);
                if (it == other.fields.end()) {
                    return false;
                }
                if (!value_eq(value, it->second, pos)) {
                    return false;
                }
            }
            
            return true;
        }
        std::string print() const;
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
        public:
        std::vector<std::string> namespaceStack;
        std::vector<std::unordered_map<std::string, Symbol>> frames;
        std::unordered_map<std::string, std::shared_ptr<FuncDefNode>> functions;
        void push_namespace(const std::string& name) {
            namespaceStack.push_back(name);
        }

        void pop_namespace() {
            namespaceStack.pop_back();
        }
        void define_user_type(UserTypeInfo info, std::string name) {
            std::string fq;

            if (info.namespace_path.empty())
                fq = name;
            else
                fq = info.namespace_path + "::" + name;

            if (user_types.count(fq)) {
                throw RTError(
                    "Redefinition of type '" + fq + "'",
                    Position{}
                );
            }

            user_types[fq] = std::move(info);
        }

        std::string qualify(const std::string& name) const {
            if (namespaceStack.empty()) return name;

            std::string q;
            for (size_t i = 0; i < namespaceStack.size(); ++i) {
                if (i) q += "::";
                q += namespaceStack[i];
            }
            return q + "::" + name;
        }
        std::unordered_map<std::string, UserTypeInfo> user_types;
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
            frames.back()[qualify(name)] = { type, std::move(val), is_const };
        }
        void set(const std::string& name, NumberVariant new_val, Position pos);
        NumberVariant get(const std::string& name, Position pos) {
            for (auto it = frames.rbegin(); it != frames.rend(); ++it) {
                auto sym_it = it->find(qualify(name));
                if (sym_it != it->end()) {
                    return sym_it->second.value;
                }
            }
            
            if (!namespaceStack.empty()) {
                for (int i = namespaceStack.size() - 1; i >= 0; --i) {
                    std::string partial_ns = "";
                    for (int j = 0; j <= i; ++j) {
                        if (j > 0) partial_ns += "::";
                        partial_ns += namespaceStack[j];
                    }
                    
                    std::string qualified_name = partial_ns + "::" + name;
                    
                    for (auto it = frames.rbegin(); it != frames.rend(); ++it) {
                        auto sym_it = it->find(qualified_name);
                        if (sym_it != it->end()) {
                            return sym_it->second.value;
                        }
                    }
                }
            }
            
            if (name.find("::") != std::string::npos) {
                for (auto it = frames.rbegin(); it != frames.rend(); ++it) {
                    auto sym_it = it->find(name);
                    if (sym_it != it->end()) {
                        return sym_it->second.value;
                    }
                }
            }
            
            throw RTError("Undefined variable: '" + name + "'", pos);
        }
        void define_function(const std::string& name, std::shared_ptr<FuncDefNode> func) {
            functions[qualify(name)] = std::move(func);
        }
        
        std::shared_ptr<FuncDefNode> get_function(const std::string& name) {
            if (name.find("::") != std::string::npos) {
                auto it = functions.find(name);
                if (it != functions.end()) return it->second;
                return nullptr;
            }
            
            auto it = functions.find(qualify(name));
            if (it != functions.end()) return it->second;
            return nullptr;
        }
        std::string get_type_name(const NumberVariant& val) {
            return std::visit([](auto&& arg) -> std::string {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, Number<short>>)               return "short int";
                if constexpr (std::is_same_v<T, Number<int>>)                 return "int";
                if constexpr (std::is_same_v<T, Number<long long>>)           return "long int";
                if constexpr (std::is_same_v<T, Number<float>>)               return "float";
                if constexpr (std::is_same_v<T, Number<double>>)              return "double";
                if constexpr (std::is_same_v<T, Number<long double>>)         return "long double";
                if constexpr (std::is_same_v<T, StringValue>)                 return "string";
                if constexpr (std::is_same_v<T, CharValue>)                   return "char";
                if constexpr (std::is_same_v<T, BoolValue>)                   return "bool";
                if constexpr (std::is_same_v<T, QBoolValue>)                  return "qbool";
                if constexpr (std::is_same_v<T, FunctionValue>)               return "function";
                if constexpr (std::is_same_v<T, VoidValue>)                   return "void";
                if constexpr (std::is_same_v<T, std::shared_ptr<MultiValue>>) return "multi";
                if constexpr (std::is_same_v<T, std::shared_ptr<ArrayValue>>) {
                    return arg->element_type + "[]";  
                }
                if constexpr (std::is_same_v<T, std::shared_ptr<ListValue>>) {
                    return "list<" + arg->element_type + ">";
                }
                if constexpr (std::is_same_v<T, std::shared_ptr<MapValue>>) {
                    return "map<" + arg->key_type + ", " + arg->value_type + ">";
                }
                if constexpr (std::is_same_v<T, std::shared_ptr<StructValue>>) {
                    return arg->type_name;
                }
                if constexpr (std::is_same_v<T, std::shared_ptr<InstanceValue>>) {
                    return arg->class_name;
                }
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
        static std::string op_method_name(TokenType t) {
            switch (t) {
                case TokenType::PLUS:   return "operator+";
                case TokenType::MINUS:  return "operator-";
                case TokenType::MUL:    return "operator*";
                case TokenType::DIV:    return "operator/";
                case TokenType::EQ_TO:  return "operator==";
                case TokenType::NOT_EQ: return "operator!=";
                case TokenType::OR:  return "operator||";
                case TokenType::AND: return "operator&&";
                case TokenType::NOT:  return "operator!";
                case TokenType::EQ: return "operator=";
                case TokenType::MORE:  return "operator>";
                case TokenType::LESS: return "operator<";
                case TokenType::MORE_EQ:  return "operator>=";
                case TokenType::LESS_EQ: return "operator<=";
                case TokenType::POWER:  return "operator**";
                case TokenType::MOD: return "operator%";
                case TokenType::QNOT:  return "operator!!";
                case TokenType::QAND: return "operator&&&";
                case TokenType::QOR:  return "operator|||";
                case TokenType::QXOR: return "operator^^";
                case TokenType::COLLAPSE_OR:  return "operator|&|";
                case TokenType::COLLAPSE_AND: return "operator&|&";
                case TokenType::XOR: return "operator^";
                default:                return "";
            }
        }
        std::string value_to_string(const NumberVariant& val);
        Interpreter(Context* ctx = nullptr) : context(ctx) {}
        InterpEer error = InterpEer();
        std::vector<Diagnostic> errors;
        NumberVariant process(AnyNode& node);
        NumberVariant operator()(NumberNode& node);
        NumberVariant call_instance_method(const std::shared_ptr<InstanceValue>& inst, ClassMethodInfo* method, std::vector<NumberVariant> args, const Position& pos);
        NumberVariant operator()(std::unique_ptr<BinOpNode>& node);
        NumberVariant operator()(std::unique_ptr<UnaryOpNode>& node);
        NumberVariant operator()(std::monostate);
        NumberVariant operator()(std::unique_ptr<MapDeclNode>& node);
        NumberVariant operator()(std::unique_ptr<StatementsNode>& node);
        NumberVariant operator()(std::unique_ptr<VarAssignNode>& node);
        NumberVariant operator()(std::unique_ptr<VarAccessNode>& node);
        NumberVariant operator()(StringNode& node);
        NumberVariant operator()(std::shared_ptr<FuncDefNode>& node);
        NumberVariant operator()(std::unique_ptr<CallNode>& node);
        NumberVariant operator()(std::unique_ptr<ReturnNode>& node);
        NumberVariant operator()(CharNode& node);
        NumberVariant operator()(BoolNode& node);
        NumberVariant operator()(QBoolNode& node);
        NumberVariant operator()(QOutNode& node);
        NumberVariant operator()(std::unique_ptr<NamespaceNode>& node);
        NumberVariant operator()(QInNode& node);
        NumberVariant operator()(std::unique_ptr<ArrayAssignNode>& node);
        NumberVariant operator()(std::unique_ptr<MultiVarDeclNode>& node);
        NumberVariant operator()(std::unique_ptr<QOutExprNode>& node);
        bool is_truthy(const NumberVariant& val);
        std::unordered_map<std::string, NumberVariant> make_instance_fields(const std::string& className);
        ClassMethodInfo* find_method_on_class(const std::string& className, const std::string& mname);
        bool field_exists_on_class(const std::string& className, const std::string& fieldName);
        bool in_class_or_derived_context(const std::string& baseName);
        NumberVariant operator()(std::unique_ptr<AssignExprNode>& node);
        NumberVariant operator()(std::unique_ptr<IfNode>& node);
        NumberVariant operator()(std::unique_ptr<QIfNode>& node);
        NumberVariant operator()(std::unique_ptr<TryCatchNode>& node);
        NumberVariant operator()(std::unique_ptr<SwitchNode>& node);
        NumberVariant operator()(std::unique_ptr<QSwitchNode>& node);
        NumberVariant operator()(std::unique_ptr<BreakNode>& node); 
        NumberVariant operator()(std::unique_ptr<ContinueNode>& node);
        NumberVariant operator()(std::unique_ptr<WhileNode>& node);
        NumberVariant operator()(std::unique_ptr<ForNode>& node);
        NumberVariant operator()(std::unique_ptr<SeedCallNode>& node);
        NumberVariant operator()(std::unique_ptr<RandomCallNode>& node);
        NumberVariant operator()(std::unique_ptr<MultiReturnNode>& node);
        NumberVariant operator()(std::unique_ptr<ArrayDeclNode>& node);
        NumberVariant operator()(std::unique_ptr<ArrayLiteralNode>& node);
        NumberVariant operator()(std::unique_ptr<ArrayAccessNode>& node);
        NumberVariant operator()(std::unique_ptr<ListDeclNode>& node);
        NumberVariant operator()(std::unique_ptr<MapLiteralNode>& node);
        NumberVariant operator()(std::unique_ptr<MethodCallNode>& node);
        NumberVariant operator()(std::shared_ptr<PropertyAccessNode>& node);
        NumberVariant operator()(std::unique_ptr<SpreadNode>& node);
        NumberVariant operator()(std::unique_ptr<ForeachNode>& node);
        NumberVariant operator()(std::unique_ptr<FieldAssignNode>& node);
        bool struct_has_field(const std::shared_ptr<StructValue>& sv, const std::string& field);
        bool in_class_context(const std::string& class_name);
        NumberVariant convert_array_to_struct(
            const std::shared_ptr<ArrayValue>& arr, 
            const std::string& struct_type, 
            Context* context
        );
        ExecResult exec_stmt_in_loop_or_switch(QIfNode& ifn);
        ExecResult exec_stmt_in_loop_or_switch(QSwitchNode& qsw);
        ExecResult exec_stmt_in_loop_or_switch(AnyNode& node);
        ExecResult exec_stmt_in_loop_or_switch(StatementsNode& block);
        ExecResult exec_stmt_in_loop_or_switch(IfNode& ifn);
        ExecResult exec_stmt_in_loop_or_switch(SwitchNode& sw);
        ExecResult exec_stmt_in_loop_or_switch(TryCatchNode& tcn);
        std::string run_statements(std::unique_ptr<StatementsNode>& node);
        ClassMethodInfo* find_method_with_args(
            const std::string& className,
            const std::string& mname,
            const std::vector<NumberVariant>& args
        );
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
    };
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
    };
}
std::string trim(const std::string& str);
std::string read_file(const std::string& path);
std::string resolve_path(const std::string& current_file, const std::string& include_path);
std::string extract_namespace(const std::string& source, const std::string& ns_name);
std::string preprocess_includes(const std::string& source, const std::string& current_file);
#endif
    