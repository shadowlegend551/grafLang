#include <stdio.h>
#include <vector>

#include "../include/asttypes.hpp"
#include "../include/token.hpp"
#include "../include/tokentype.hpp"
#include "../include/tokenizer.hpp"

int main()
{
    Tokenizer x = Tokenizer("00015.56 13 \"Hello World\"");
    std::vector<Token> y = x.tokenize();
    TokenValue z = y[0].literal_value;
    double a = z.float_literal;
    
    printf("%f\n", a);
    return 0;
}
