#include <iostream>
#include <string>
#include <vector>

#include "../include/tokenizer.hpp"
#include "../include/error.hpp"
#include "../include/token.hpp"
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


Tokenizer::Tokenizer()
{
    i = 0;
    line_index = 1;
    lineno = 1;
}


char Tokenizer::advance()
{
    char character = character_stream[i];
    if(character != '\0')
        i++;
        line_index++;

    // Implicitly return null if end of string reached.
    return character;
}


void Tokenizer::advanceLine()
{
    lineno++;
    line_index = 1;
    getLine();
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


void Tokenizer::getLine()
{
    int i_offset = 0;
    line = "";

    char next_character = character_stream[i];
    while(next_character != '\n' && next_character != '\0')
    {
        line.push_back(next_character); // Finish this function.
        i_offset++;
        next_character = character_stream[i+i_offset];
    }
}


Token Tokenizer::getErrorToken(Error error_code)
{
    std::string error_message = get_error_message(error_code,
                                                    file_name,
                                                    line,
                                                    lineno,
                                                    line_index);

    Token error_token = create_token(ERROR_TYPE,
                                        ERROR_TYPE,
                                        error_message);

    return error_token;
}


void Tokenizer::tokenizeNumericLiteral()
{
    std::string literal_value;
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


void Tokenizer::tokenizeIdentifierLiteral()
{
    std::string literal_value;
    literal_value.push_back(character);

    while(isalpha(get()) || isdigit(get()) || get() == '_')
    {
        literal_value.push_back(advance());
    }

    if(literal_value == "true")
    {
        current_token = create_token(GENERIC_BOOL, BOOL_TRUE);
    }

    else if(literal_value == "false")
    {
        current_token = create_token(GENERIC_BOOL, BOOL_FALSE);
    }

    else if(literal_value == "null")
    {
        current_token = create_token(GENERIC_BOOL, BOOL_NULL);
    }

    // Handles also keywords.
    else if(literal_value == "if")
    {
        current_token = create_token(GENERIC_KEYWORD, KEYWORD_IF);
    }

    else if(literal_value == "while")
    {
        current_token = create_token(GENERIC_KEYWORD, KEYWORD_WHILE);
    }

    else if(literal_value == "for")
    {
        current_token = create_token(GENERIC_KEYWORD, KEYWORD_FOR);
    }

    else if(literal_value == "break")
    {
        current_token = create_token(GENERIC_KEYWORD, KEYWORD_BREAK);
    }

    else
    {
        current_token = create_token(GENERIC_LITERAL,
                                    IDENTIFIER_LITERAL,
                                    literal_value);
    }
}


char Tokenizer::getEscapeCharacter()
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

        case '\'':
            return '\'';

        case '\n':
            advanceLine();
            return '\n';

        default:
            return escape_code;
    }
}


void Tokenizer::tokenizeStringLiteral()
{
    std::string literal_value = "";

    while(get() && get() != '\n' && get() != character)
    {
        if(get() == '\\')
        {
            advance();
            literal_value.push_back(getEscapeCharacter());
        }
        else
            literal_value.push_back(advance());
    }

    if(get() == character)
    {
        current_token = create_token(GENERIC_LITERAL,
                                    STRING_LITERAL,
                                    literal_value);
        advance();
    }
    else
    {
        current_token = getErrorToken(MISSING_QUOTE);
    }
}


std::vector<Token> Tokenizer::tokenize(std::string raw_string, std::string source_file_name)
{
    std::vector<Token> token_stream;
    raw_string.push_back('\0');
    character_stream = raw_string;
    file_name = source_file_name;

    char next_char;
    getLine();


    while(get() != '\0')
    {
        character = advance();
        char next_character = get();

        // Skip whitespace.
        if(character == ' ')
            continue;
        
        if(character == '\n' || character == ';')
        {
            advanceLine();
            continue;
        }


        // Numeric literal.
        if(isdigit(character))
        {
            tokenizeNumericLiteral();
            goto append_token;
        }


        // Identifier literal. Checks for keywords
        if(isalpha(character))
        {
            tokenizeIdentifierLiteral();
            goto append_token;
        }


        // String literal.
        if(character == '"' || character == '\'')
        {
            tokenizeStringLiteral();
            goto append_token;
        }


        switch(character)
        {

        // Logical operators.
        case '!':
            if(next_character == '=')  // !=
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSERT_NE);
            }
            else  // !
            {
                current_token = create_token(GENERIC_UNARY_OPERATOR,
                                                LOGICAL_NOT);
            }
            break;

        case '&':
            current_token = create_token(GENERIC_BINARY_OPERATOR,
                                            LOGICAL_AND);
            break;

        case '|':
            current_token = create_token(GENERIC_BINARY_OPERATOR,
                                            LOGICAL_OR);
            break;

        case '^':
            current_token = create_token(GENERIC_BINARY_OPERATOR,
                                            LOGICAL_XOR);
            break;

            
        // Arithmetic operators.
        case '+':

            if(next_character == '=')  // +=
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSIGNMENT_ADD);
                advance();
            }
            else if(next_character == '+')  // ++
            {
                current_token = create_token(GENERIC_UNARY_OPERATOR,
                                                LOGICAL_INCREMENT);
            }
            else  // +
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ARITHMETIC_ADD);
            }
            break;

        case '-':
            if(next_character == '=')  // -=
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSIGNMENT_SUB);
                advance();
            }
            else if(next_character == '-')  // --
            {
                current_token = create_token(GENERIC_UNARY_OPERATOR,
                                                LOGICAL_DECREMENT);
                advance();
            }
            else  // -
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ARITHMETIC_SUB);
            }
            break;

        case '*':
            if(next_character == '=')  // *=
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSIGNMENT_MUL);
            advance();
            }
            else if(next_character == '*')  // **
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ARITHMETIC_EXP);
            }
            else  // *
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ARITHMETIC_MUL);
            }
            break;

        case '/':
            if(next_character == '=')  // /=
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSIGNMENT_DIV);
                advance();
            }
            else if(next_character == '*')  // /* comment */
            {
                do { advance(); }
                while(get() != '*' && peek() != '/');

                advance();  // Skip *
                advance();  // Skip /
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


        // Assignment and comparison operators.
        case '=':
            if(next_character == '=')  // ==
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSIGNMENT);
            }
            else  // =
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSERT_EQ);
            }
            break;

        case '<':
            if(next_character == '=')  // <=
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSERT_LE);
            }
            else  // <
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSERT_LT);
            }
            break;

        case '>':
            if(next_character == '=')  // >=
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSERT_GE);
            }
            else  // >
            {
                current_token = create_token(GENERIC_BINARY_OPERATOR,
                                                ASSERT_GE);
            }
            break;


        // Grouping symbols
        case '(':
            current_token = create_token(GENERIC_GROUPING,
                                                L_PAREN);
            break;

        case '[':
            current_token = create_token(GENERIC_GROUPING,
                                                L_SBRACKET);
            break;

        case '{':
            current_token = create_token(GENERIC_GROUPING,
                                                L_BRACKET);
            break;

        case ')':
            current_token = create_token(GENERIC_GROUPING,
                                                R_PAREN);
            break;

        case ']':
            current_token = create_token(GENERIC_GROUPING,
                                                R_SBRACKET);
            break;

        case '}':
            current_token = create_token(GENERIC_GROUPING,
                                                R_BRACKET);
            break;


        // Separator symbols.
        case '.':
            current_token = create_token(GENERIC_SEPARATOR,
                                                DOT);
            break;

        case ',':
            current_token = create_token(GENERIC_SEPARATOR,
                                                COMMA);
            break;

        case ':':
            current_token = create_token(GENERIC_SEPARATOR,
                                                COLON);
            break;

        case ';':
            current_token = create_token(GENERIC_SEPARATOR,
                                                SEMICOLON);
            break;

        case '?':
            current_token = create_token(GENERIC_MISC,
                                                Q_MARK);
            break;

        case '\\':
            current_token = create_token(GENERIC_MISC,
                                                BACKSLASH);
            break;

        // Invalid token.
        default:
            current_token = getErrorToken(UNRECOGNIZED_TOKEN);
        }

        append_token:
            token_stream.push_back(current_token);
    }

    return token_stream;
}
