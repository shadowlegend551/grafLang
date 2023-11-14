#include <string>

#include "../include/error.hpp"
#include "../include/token.hpp"
#include "../include/tokentype.hpp"

std::string get_error_message(Error error_code,
                                std::string file_name,
                                std::string line,
                                int lineno,
                                int line_index,
                                char error_character,
                                std::string erroneous_string)
{
    std::string error_message = "Error: ";

    std::string error_pointer = "";
    for(int i = 0; i < line_index-1; i++)
    {
        error_pointer.push_back('~');
    }
    error_pointer.push_back('^');

    std::string place = "\n\tIn file: "
                        + file_name
                        + ": "
                        + std::to_string(lineno)
                        + ':'
                        + std::to_string(line_index);

    std::string specific_error = "Unknown error";
    std::string suggestion = "";

    switch(error_code)
    {
        /*case UNRECOGNIZED_TOKEN:
            error_message.append("Error: unrecognized symbol: \"");
            error_message.push_back(error_character);
            error_message.push_back('"');
            error_message.append(" on line ")
                         .append(std::to_string(lineno));
            break;*/
            

        case MISSING_QUOTE:
            specific_error = "\n\tMissing quote after string: ";
            specific_error.append(erroneous_string);

            suggestion = "\n\tSuggestion: Add \" or '";
            break;
        
        default:
            break;
    }

    error_message.append(place)
                 .append(specific_error + ';')
                 .append(suggestion + ';');

    return error_message;
}