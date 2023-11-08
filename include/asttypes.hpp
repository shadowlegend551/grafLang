#include "token.hpp"
#include "tokentype.hpp"


typedef enum AstExpressionType
{
    EXPRESSION,                // Generic expression.
    LITERAL_EXPRESSION,        // e.g. "Hello World!"
    UNARY_EXPRESSION,          // e.g. "!x"
    BINARY_EXPRESSION,         // e.g. "x = 3"
    GROUPING_EXPRESSION,       // e.g. ()

} AstExpressionType;


typedef struct AstNode AstNode;


typedef struct UnaryExpression
{
    Token oper;
    AstNode* right;

} UnaryExpression;


typedef struct BinaryExpression
{
    AstNode* left;
    Token oper;
    AstNode* right;

} BinaryExpression;


typedef union AstExpression
{
    UnaryExpression unary_expression;
    BinaryExpression binary_expression;

} AstExpression;


typedef struct AstNode
{
    AstNode* parent_node;

    AstExpressionType type;
    AstExpression node;

} AstNode;
