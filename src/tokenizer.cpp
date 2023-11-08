#include <string>
#include <vector>

#include "../include/token.hpp"
#include "../include/tokenizer.hpp"
#include "../include/tokentype.hpp"


int isalpha(char c)
{
    // Upper-case letter range in ASCII.
    if(64 < c && c < 91)
        return 1;

    // Lower-case letter range in ASCII.
    if(96 < c && c < 123)
        return 1;

    return 0;
}


int isdigit(char c)
{
    if(47 < c && c < 58)
        return 1;

    return 0;
}


Tokenizer::Tokenizer(std::string input)
{
    character_stream = input;
    i = 0;
}


char Tokenizer::advance()
{
    char character = character_stream[i];
    if(character != '\0')
        i++;

    return character;
}


char Tokenizer::get()
{
    return character_stream[i];
}


char Tokenizer::last()
{
    if(i > 0)
        return character_stream[i-1];

    return '\0';
}


char Tokenizer::peek()
{
    if(character_stream[i] != '\0')
        return character_stream[i+1];

    return '\0';
}


void Tokenizer::tokenize_numeric_literal()
{
    literal_value = "";
    literal_value.push_back(character);

    // Get integer part.
    while(isdigit(get()))
    {
        literal_value.push_back(advance());
    }

    // If decimal point not found -> integer.
    if(get() != '.')
    {
        current_token = create_token(GENERIC_LITERAL,
                                        INTEGER_LITERAL,
                                        literal_value);
    }

    else
    {
        do { literal_value.push_back(advance()); }
        while(isdigit(get()));

        current_token = create_token(GENERIC_LITERAL,
                                        FLOAT_LITERAL,
                                        literal_value);
    }
}


char Tokenizer::get_escape_character()
{
    char escape_code = advance();

    switch(escape_code)
    {
        case 'n':
            return '\n';

        case 't':
            return '\t';

        case '\\':
            return '\\';

        case '"':
            return '"';

        default:
            return 0;
    }
}


void Tokenizer::tokenize_string_literal()
{
    literal_value = "";

    while(get() != '"')
    {
        if(get() == '\\')
        {
            advance();
            literal_value.push_back(get_escape_character());
        }
        else
            literal_value.push_back(advance());
    }

    advance();
    current_token = create_token(GENERIC_LITERAL,
                                    STRING_LITERAL,
                                    literal_value);
}


std::vector<Token> Tokenizer::tokenize()
{
    std::vector<Token> token_stream;
    character_stream.push_back('\0');


    while(get() != '\0')
    {
        character = advance();

        // Skip whitespace.
        if(character == ' ')
            continue;


        // Numeric literal.
        if(isdigit(character))
        {
            tokenize_numeric_literal();
        }

        switch(character)
        {

        // String literal.
        case '"':
            
            break;
            
        // Arithmetic operators.
        case '+':
            if(get() == '=')  // +=
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSIGNMENT_ADD);
                advance();
            }
            else  // +
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ARITHMETIC_ADD);
            }
            break;

        case '-':
            if(get() == '=')  // -=
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSIGNMENT_SUB);
                advance();
            }
            else  // -
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ARITHMETIC_SUB);
            }
            break;

        case '*':
            if(get() == '=')  // *=
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSIGNMENT_MUL);
            advance();
            }
            else  // *
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ARITHMETIC_MUL);
            }
            break;

        case '/':
            if(get() == '=')  // /=
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSIGNMENT_DIV);
                advance();
            }
            else if(get() == '*')  // /* comment */
            {
                do { advance(); }
                while(get() != '*' && peek() != '/');

                advance();  // Skip *
                advance();  // Skip /
                break;
                    
            }
            else  // /
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ARITHMETIC_DIV);
            }
            break;

        case '%':  // %
            current_token = create_token(GENERIC_BINARY_OPERATOR,
                                            ARITHMETIC_MOD);
            break;
        }
        token_stream.push_back(current_token);
    }

    return token_stream;
}
