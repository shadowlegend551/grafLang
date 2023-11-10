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


Tokenizer::Tokenizer(std::string input)
{
    character_stream = input;
    i = 0;
    lineno = 1;
}


char Tokenizer::advance()
{
    char character = character_stream[i];
    if(character != '\0')
        i++;

    // Implicitly return null if end of string reached.
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


Token Tokenizer::tokenize_error_token(Error error_code, char error_character,  std::string error_string)
{
    std::string error_message = "";
    Token error_token;

    switch(error_code)
    {
        case UNRECOGNIZED_TOKEN:
            error_message.append("Error: unrecognized symbol: \"");
            error_message.push_back(error_character);
            error_message.push_back('"');
            error_message.append(" on line ")
                         .append(std::to_string(lineno));

            error_token = create_token(ERROR_TYPE,
                                            ERROR_TYPE,
                                            error_message);
            break;
            

        case MISSING_QUOTE:
            error_message.append("Error: missing quote after string: \"")
                         .append(error_string)
                         .append(" Suggestion: (Add: \" / ')")
                         .append(" on line ")
                         .append(std::to_string(lineno));

            error_token = create_token(ERROR_TYPE,
                                            ERROR_TYPE,
                                            error_message);
            break;
        
        default:
            error_token = create_token(ERROR_TYPE,
                                            ERROR_TYPE,
                                            "Unknown error.");
            break;
    }

    return error_token;
}


void Tokenizer::tokenize_numeric_literal()
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


void Tokenizer::tokenize_identifier_literal()
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

        case '\'':
            return '\'';

        default:
            return 0;
    }
}


void Tokenizer::tokenize_string_literal()
{
    std::string literal_value = "";

    while(get() != character)
    {
        if(get() == '\\')
        {
            advance();
            literal_value.push_back(get_escape_character());
        }
        else if(!get())
        {
            current_token = tokenize_error_token(MISSING_QUOTE,
                                                    '\0', literal_value);
            return;

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

    char next_char;


    while(get() != '\0')
    {
        character = advance();
        char next_character = get();

        // Skip whitespace.
        if(character == ' ')
            continue;
        
        if(character == '\n')
        {
            lineno++;
            continue;
        }


        // Numeric literal.
        if(isdigit(character))
        {
            tokenize_numeric_literal();
            goto append_token;
        }


        // Identifier literal. Checks for keywords
        if(isalpha(character))
        {
            tokenize_identifier_literal();
            goto append_token;
        }


        // String literal.
        if(character == '"' || character == '\'')
        {
            tokenize_string_literal();
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
            current_token = tokenize_error_token(UNRECOGNIZED_TOKEN,
                                                    character, "");
        }

        append_token:
            token_stream.push_back(current_token);
    }

    return token_stream;
}
