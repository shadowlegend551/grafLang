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
                                std::string line,
                                int lineno,
                                int lineindex,
                                char error_character,
                                std::string erroneous_string);

#endif
