#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>


class Tokenizer
{
    private:
        std::string character_stream;
        char current_character;
        unsigned int i;

        char advance();

        char get();

        char last();

        char peek();

        char get_escape_character();

    public:
        std::vector<Token> tokenize();
    
        Tokenizer(std::string input);
};

#endif
