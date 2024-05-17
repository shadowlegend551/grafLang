#ifndef TOKENTYPE_HPP
#define TOKENTYPE_HPP

/*
    This file is a part of the graphLang -language.

    This file includes the token type enum for graphLang.
    I have grouped them as logically as a programmer could
    for ease of use and extension.
    Generic types (e.g. UNARY_OPERATOR) are used to 
    mark the general type of a token to help with parsing.
*/


typedef enum GenericTokenType
{
    // Generic boolean type.
    GENERIC_BOOL,

    // Generic keyword type.
    GENERIC_KEYWORD,

    // Generic literal type.
    GENERIC_LITERAL,

    // Generic unary operator type. Usage: <operator> <expr>.
    GENERIC_UNARY_OPERATOR,

    // Generic binary operator type. Usage: <expr> <operator> <expr>.
    GENERIC_BINARY_OPERATOR,

    // Generic grouping type.
    GENERIC_GROUPING,

    // Generic separator type.
    GENERIC_SEPARATOR,

    // Generic miscellaneous type.
    GENERIC_MISC,

    GENERIC_ERROR_TYPE,

} GenericTokenType;


typedef enum TokenType
{

/* ----------------------------*/

    // Booleans.
    BOOL_NULL,                 // null
    BOOL_TRUE,                 // true
    BOOL_FALSE,                // false

/* ----------------------------*/

    // Control keywords.
    KEYWORD_IF,                // if
    KEYWORD_WHILE,             // while
    KEYWORD_FOR,               // for
    KEYWORD_BREAK,             // break
    KEYWORD_CONTINUE,          // continue

/* ----------------------------*/

    // Literal values.
    INTEGER_LITERAL,           // e.g. 3
    FLOAT_LITERAL,             // e.g. 3.5
    STRING_LITERAL,            // List of characters.
    IDENTIFIER_LITERAL,        // e.g. x
    KEYWORD_LITERAL,           // e.g. if

/* ----------------------------*/

    // Logical operators.
    LOGICAL_NOT,               // !
    LOGICAL_INCREMENT,         // ++ (only prefix)
    LOGICAL_DECREMENT,         // -- (only prefix)

/* ----------------------------*/

    // Logical operators.
    LOGICAL_AND,               // &
    LOGICAL_OR,                // |
    LOGICAL_XOR,               // ^

    // Arithmetic operators.
    ARITHMETIC_ADD,            // +
    ARITHMETIC_SUB,            // -
    ARITHMETIC_MUL,            // *
    ARITHMETIC_DIV,            // /
    ARITHMETIC_EXP,            // **
    ARITHMETIC_MOD,            // %

    // Assignment operators.
    ASSIGNMENT,                // =
    ASSIGNMENT_ADD,            // +=
    ASSIGNMENT_SUB,            // -=
    ASSIGNMENT_MUL,            // *=
    ASSIGNMENT_DIV,            // /=

    // Comparison operators
    ASSERT_EQ,                 // ==
    ASSERT_NE,                 // !=
    ASSERT_LT,                 // <
    ASSERT_GT,                 // >
    ASSERT_LE,                 // <=
    ASSERT_GE,                 // >=

/* ----------------------------*/

    // Grouping.
    L_PAREN,                   // (
    L_SBRACKET,                // [
    L_BRACKET,                 // {

    R_PAREN,                   // )
    R_SBRACKET,                // ]
    R_BRACKET,                 // }

    SINGLE_QUOTE,              // '
    DOUBLE_QUOTE,              // "

/* ----------------------------*/

    // Separators.
    DOT,                       // .
    COMMA,                     // ,
    COLON,                     // :
    SEMICOLON,                 // ;

/* ----------------------------*/

    // Misc.
    Q_MARK,                    // ?
    BACKSLASH,                 // \

/* ----------------------------*/

    // Error token.
    ERROR_TYPE,

/* ----------------------------*/

} TokenType;

#endif
