#include <string>

#include "../include/error.hpp"
#include "../include/token.hpp"
#include "../include/tokentype.hpp"

std::string get_error_message(Error error_code,
                                std::string line,
                                int lineno,
                                int lineindex,
                                char error_character,
                                std::string erroneous_string)
{
    std::string error_message = "";
    std::string place = std::to_string(lineno) + ':' + std::to_string(lineindex);
    std::string specific_error = "";

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
                         .append(erroneous_string)
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