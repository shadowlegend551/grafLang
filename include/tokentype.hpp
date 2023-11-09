#ifndef TOKENTYPE_HPP
#define TOKENTYPE_HPP

/*
    This file is a part of the graphLang -language.

    This file includes the token type enum for graphLang.
    I have grouped them as logically as a programmer could
    for ease of use and extension.
    Generic types (e.g. UNARY_OPERATOR) are used to 
    mark the general type of a token to help with parsing.
    I have defined them here together with the morespecific
    types for the sake of coherence and because I don't want
    to include as many .hpp files.
*/

typedef enum TokenType
{

/* ----------------------------*/

    // Generic boolean type.
    GENERIC_BOOL,

    // Booleans.
    BOOL_NULL,                 // Null
    BOOL_TRUE,                 // True
    BOOL_FALSE,                // False

/* ----------------------------*/

    // Generic keyword type.
    GENERIC_KEYWORD,

    // Control keywords.
    KEYWORD_IF,                // if
    KEYWORD_WHILE,             // while
    KEYWORD_FOR,               // for
    KEYWORD_BREAK,             // break
    KEYWORD_CONTINUE,          // continue

/* ----------------------------*/

    // Generic literal type.
    GENERIC_LITERAL,

    // Literal values.
    INTEGER_LITERAL,           // e.g. 3
    FLOAT_LITERAL,             // e.g. 3.5
    STRING_LITERAL,            // List of characters.
    IDENTIFIER_LITERAL,        // e.g. x
    KEYWORD_LITERAL,           // e.g. if

/* ----------------------------*/

    // Generic unary operator type. Usage: <operator> <expr>.
    GENERIC_UNARY_OPERATOR,

    // Logical operators.
    LOGICAL_NOT,               // !
    LOGICAL_INCREMENT,         // ++ (only prefix)
    LOGICAL_DECREMENT,         // -- (only prefix)

/* ----------------------------*/

    // Generic binary operator type. Usage: <expr> <operator> <expr>.
    GENERIC_BINARY_OPERATOR,

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

    // Generic grouping type.
    GENERIC_GROUPING,

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

    // Generic separator type.
    GENERIC_SEPARATOR,

    // Separators.
    DOT,                       // .
    COMMA,                     // ,
    COLON,                     // :
    SEMICOLON,                 // ;

/* ----------------------------*/

    GENERIC_MISC,

    // Misc.
    Q_MARK,                    // ?
    BACKSLASH,                 // \

/* ----------------------------*/

} TokenType;

#endif
