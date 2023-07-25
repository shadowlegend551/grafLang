#include "tokenizer.hpp"
#include <iostream>
#include <vector>

// E.g. A single parenthesis or a binary operator (+, -, etc...).
Token create_single_char_token(TokenType type, char value)
{
    Token token;
    token.value = "";
    token.value.push_back(value);
    token.type = type;

    return token;
}


// E.g. An integer or a string. Also multi-character operators (<=, ==, etc...).
Token create_multi_char_token(TokenType type, std::string value)
{
    Token token;
    token.value = value;
    token.type = type;

    return token;
}

std::vector<Token> tokenize(std::string src)
{
    std::vector<Token> tokens;

    while(src.size() > 0)
    {
        // If parsing a single-character token.
        switch(src[0])
        {
            case '(':
                tokens.push_back(create_single_char_token(OpenParen, src[0]));
                src.erase(0, 1);

                break;

            case ')':
                tokens.push_back(create_single_char_token(ClosedParen, src[0]));
                src.erase(0, 1);

                break;

            case '+':
                tokens.push_back(create_single_char_token(BinaryOperator,  src[0]));
                src.erase(0, 1);

                break;

            case '-':
                tokens.push_back(create_single_char_token(BinaryOperator,  src[0]));
                src.erase(0, 1);

                break;

            case '*':
                tokens.push_back(create_single_char_token(BinaryOperator,  src[0]));
                src.erase(0, 1);

                break;

            case '/':
                tokens.push_back(create_single_char_token(BinaryOperator,  src[0]));
                src.erase(0, 1);

                break;

            case '=':
                tokens.push_back(create_single_char_token(Equals, src[0]));
                src.erase(0, 1);

                break;

            // If parsing a multi-character token
            default:

                // Integer.
                if(isint(src[0]))
                {
                    std::string int_token = "";

                    while(src.size() > 0 && isint(src[0]))
                    {
                        int_token.push_back(src[0]);
                        src.erase(0, 1);
                    }

                    tokens.push_back(create_multi_char_token(Number, int_token));
                }

                // Identifier.
                else if(is_alphabetical(src[0]))
                {
                    std::string ident_token = "";

                    while(src.size() > 0 && is_alphabetical(src[0]))
                    {
                        ident_token.push_back(src[0]);
                        src.erase(0, 1);
                    }

                    // If it's a reserved keyword.
                    TokenType reserved = RESERVED_KEYWORDS[ident_token];
                    if(reserved == 0)
                    {
                        tokens.push_back(create_multi_char_token(Identifier, ident_token));
                    }
                    else
                    {
                        tokens.push_back(create_multi_char_token(reserved, ident_token));
                    }
                    
                }

                // If it's whitespace etc.
                else if(is_skippable(src[0]))
                {
                    src.erase(0, 1);
                }

                else
                {
                    std::cout << "Unrecognized character: " << "\"" << src[0] << "\"" << std::endl;
                    src.erase(0, 1);
                }
                
        }
    }


    return tokens;
}