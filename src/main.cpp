#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "../include/asttypes.hpp"
#include "../include/token.hpp"
#include "../include/tokentype.hpp"
#include "../include/tokenizer.hpp"

int main()
{
    std::string input;
    Tokenizer x = Tokenizer();
    std::vector<Token> y;

    printf("Exit with \"quit\", \"q\" or \"exit\"\n");
    while(1)
    {
        printf("> ");
        std::getline(std::cin, input, '\n');
        if(input == "quit" || input == "q" || input == "exit")
        {
            break;
        }
        
        y = x.tokenize(input, "REPL");
        
        for(Token token : y)
        {
            if(token.generic_type == ERROR_TYPE)
            {
                printf("%s\n", token.literal_value.string_literal);
            }
        }
    }

    printf("Exiting...\n");
    return 0;
}
