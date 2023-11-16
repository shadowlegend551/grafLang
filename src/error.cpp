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
    std::string place = "\n\tIn file: "
                        + file_name
                        + ": "
                        + std::to_string(lineno)
                        + ':'
                        + std::to_string(line_index);

    std::string specific_error = "Unknown error";
    std::string suggestion = "";

    std::string line_marker = "\n\t" + std::to_string(lineno) + "| ";

    // -2 to account for newline and vtab.
    int line_marker_length = line_marker.size() - 2;

    std::string erroneous_line = line_marker + erroneous_string;
    std::string error_pointer = "\n\t";

    for(int i = 0; i < line_index+line_marker_length-2; i++)
    {
        error_pointer.push_back('~');
    }
    error_pointer.append("^\n");

    switch(error_code)
    {
        case UNRECOGNIZED_TOKEN:
            specific_error = "\n\tUnrecognized symbol:\n";

            break;
            

        case MISSING_QUOTE:
            specific_error = "\n\tMissing quote after string:\n";
            suggestion = "\n\tSuggestion: Add \" or '.";
            
            break;
        
        default:
            break;
    }

    error_message.append(place)
                 .append(specific_error)
                 .append(erroneous_line)
                 .append(error_pointer)
                 .append(suggestion);

    return error_message;
}