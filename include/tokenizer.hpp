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

        Token getErrorToken(Error error_code,
                                char error_character,
                                std::string error_string);

        void tokenizeNumericLiteral();

        void tokenizeIdentifierLiteral();

        char getEscapeCharacter();

        void tokenizeStringLiteral();

    public:
        std::vector<Token> tokenize();
    
        Tokenizer(std::string input);
};

#endif
