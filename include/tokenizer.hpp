#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

#include "error.hpp"
#include "token.hpp"


class Tokenizer
{
    private:
        std::string character_stream;
        char character;
        Token current_token;
        int lineno;

        unsigned int i;

        char advance();

        char get();

        char last();

        char peek();

        Token tokenize_error_token(Error error_code,
                                    char error_character,
                                    std::string error_string);

        void tokenize_numeric_literal();

        void tokenize_identifier_literal();

        char get_escape_character();

        void tokenize_string_literal();

    public:
        std::vector<Token> tokenize();
    
        Tokenizer(std::string input);
};

#endif
