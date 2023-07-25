#include <vector>
#include <string>

enum NodeType
{
    Prgrm,
    NumLiteral,
    Ident,
    BinaryExpr,
};


// Single command.
struct Statement
{
    NodeType type;
};


// Array of commands.
struct Program : Statement
{
    Program(){type = Prgrm;};
    std::vector<Statement> body;
};


struct Expression : Statement{};


struct BinaryExpression : Expression
{
    BinaryExpression(){type = BinaryExpr;};

    Expression left;
    Expression right;
    std::string Operator;
};


// E.g. Variable name.
struct Identifier : Expression
{
    Identifier(){type = Ident;};
    std::string symbol;
};


struct NumericLiteral : Expression
{
    NumericLiteral(){type = NumLiteral;};
    std::string value;
};