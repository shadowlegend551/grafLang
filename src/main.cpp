#include <stdio.h>
#include <vector>

#include "../include/asttypes.hpp"
#include "../include/token.hpp"
#include "../include/tokentype.hpp"
#include "../include/tokenizer.hpp"

int main()
{
    Tokenizer x = Tokenizer("& + 67.5");
    std::vector<Token> y = x.tokenize();
    TokenValue z = y[0].literal_value;
    
    printf("%d\n", y[0].type);
    return 0;
}
