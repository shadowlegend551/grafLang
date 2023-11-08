#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>


class Tokenizer
{
    private:
        std::string character_stream;
        char character;
        Token current_token;
        std::string literal_value;

        unsigned int i;

        char advance();

        char get();

        char last();

        char peek();

        void tokenize_numeric_literal();

        char get_escape_character();

        void tokenize_string_literal();

    public:
        std::vector<Token> tokenize();
    
        Tokenizer(std::string input);
};

#endif
