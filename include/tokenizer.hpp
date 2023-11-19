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
        std::string file_name;
        Token current_token;

        char character;
        std::string line;
        int lineno;
        int line_index;

        unsigned int character_stream_iterator;

        char advance();

        void advanceLine();

        char get();

        char last();

        char peek();

        void getLine();

        Token getErrorToken(Error error_code);

        void tokenizeNumericLiteral();

        void tokenizeIdentifierLiteral();

        char getEscapeCharacter();

        void tokenizeStringLiteral();

    public:
        std::vector<Token> tokenize(std::string raw_string, std::string source_file_name);
    
        Tokenizer();
};

#endif
