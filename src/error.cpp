#include <string>

#include "../include/error.hpp"
#include "../include/token.hpp"
#include "../include/tokentype.hpp"

std::string get_error_message(Error error_code,
                        char error_character,
                        std::string error_string,
                        int lineno)
{
    std::string error_message = "";

    switch(error_code)
    {
        case UNRECOGNIZED_TOKEN:
            error_message.append("Error: unrecognized symbol: \"");
            error_message.push_back(error_character);
            error_message.push_back('"');
            error_message.append(" on line ")
                         .append(std::to_string(lineno));
            break;
            

        case MISSING_QUOTE:
            error_message.append("Error: missing quote after string: \"")
                         .append(error_string)
                         .append(". Suggestion: (Add: \" / ')")
                         .append(" on line ")
                         .append(std::to_string(lineno));
            break;
        
        default:
            error_message = "Unknown error";
            break;
    }

    return error_message;
}