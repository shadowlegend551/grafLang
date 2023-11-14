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
        Token current_token;

        char character;
        std::string line;
        int lineno;
        int line_index;

        unsigned int i;

        char advance();

        char get();

        char last();

        char peek();

        void getLine();

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
