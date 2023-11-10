#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>

#include "token.hpp"

typedef enum Error
{
    UNRECOGNIZED_TOKEN,
    MISSING_QUOTE,

} Error;

std::string get_error_message(Error error_code,
                        char error_character,
                        std::string error_string,
                        int lineno);

#endif
