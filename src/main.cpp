#include <stdio.h>
#include <vector>

#include "../include/asttypes.hpp"
#include "../include/token.hpp"
#include "../include/tokentype.hpp"
#include "../include/tokenizer.hpp"

int main()
{
    Tokenizer x = Tokenizer("$\n\"Hello world");
    std::vector<Token> y = x.tokenize();
    
    for(Token token : y)
    {
        if(token.generic_type == ERROR_TYPE)
        {
            printf("%s\n", token.literal_value.string_literal);
        }
    }
    return 0;
}
