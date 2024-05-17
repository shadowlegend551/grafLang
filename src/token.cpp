#include <string>
#include <string.h>

#include "../include/token.hpp"
#include "../include/tokentype.hpp"

Token create_token(GenericTokenType generic_type,
                    TokenType type,
                    std::string literal_value)
{
    TokenValue value;
    Token token;

    token.generic_type = generic_type;
    token.type = type;

    switch(type)
    {
        case INTEGER_LITERAL:
            value.integer_literal = std::stoi(literal_value);
            token.literal_value = value;
            break;
        
        case FLOAT_LITERAL:
            value.float_literal = std::stod(literal_value);
            token.literal_value = value;
            break;

        case STRING_LITERAL:
        case IDENTIFIER_LITERAL:
        case KEYWORD_LITERAL:
        case ERROR_TYPE:
            value.string_literal = strdup(literal_value.c_str());
            token.literal_value = value;
            break;

        // When a non-literal is encountered, literal_value property
        // is left uninitialized.
        default:
            break;
    }

    return token;
}
