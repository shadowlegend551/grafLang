#include <stdio.h>
#include <vector>

#include "../include/asttypes.hpp"
#include "../include/token.hpp"
#include "../include/tokentype.hpp"
#include "../include/tokenizer.hpp"

int main()
{
    Tokenizer x = Tokenizer("''Hello World''");
    std::vector<Token> y = x.tokenize();
    TokenValue z = y[0].literal_value;
    
    printf("%s\n", z.string_literal);
    return 0;
}
