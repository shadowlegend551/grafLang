#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

#include "tokentype.hpp"

// Left uninitialized with non-literal tokens.
typedef union TokenValue
{
    int integer_literal;
    double float_literal;
    const char* string_literal;

} TokenValue;


typedef struct Token
{
    TokenType generic_type;
    TokenType type;
    TokenValue literal_value;

} Token;

Token create_token(TokenType generic_type,
                    TokenType type,
                    std::string literal_value = "");

#endif
