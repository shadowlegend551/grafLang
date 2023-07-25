#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include "checks.h"
#include <vector>
#include <string>
#include <map>

enum TokenType
{
    Number = 1,
    Identifier = 2,
    Equals = 3,
    OpenParen = 4,
    ClosedParen = 5,
    BinaryOperator = 6,
    Let
};

struct Token
{
    std::string value;
    TokenType type;
};

std::map<std::string, TokenType> RESERVED_KEYWORDS = 
{
    {"let", Let},
};

Token create_single_char_token(TokenType type, char value);

Token create_multi_char_token(TokenType type, std::string value);

std::vector<Token> tokenize(std::string src);

#endif