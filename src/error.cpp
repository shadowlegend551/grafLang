#include <string>

#include "../include/error.hpp"
#include "../include/token.hpp"
#include "../include/tokentype.hpp"

std::string get_place(std::string file_name,
                        int lineno,
                        int line_index)
{
    std::string place = "\n\tIn file: "
                        + file_name
                        + ": "
                        + std::to_string(lineno)
                        + ':'
                        + std::to_string(line_index);

    return place;
}

std::string get_formatted_line(std::string line, int lineno)
{
    std::string formatted_line = "\n\t"
                                 + std::to_string(lineno)
                                 + "| "
                                 + line;

    return formatted_line;
}

std::string get_error_squiggle(int lineno, int line_index)
{
    std::string squiggle = "\n\t";

    int squiggle_length = std::to_string(lineno).length()
                          + line_index;

    for(int i = 0; i < squiggle_length; i++)
    {
        squiggle.push_back('~');
    }
    squiggle.push_back('^');

    return squiggle;
}

std::string get_error_message(Error error_type,
                                std::string file_name,
                                std::string line,
                                int lineno,
                                int line_index)
{
    std::string error_message = "Error: ";
    std::string suggestion = "";

    switch(error_type)
    {
        case UNRECOGNIZED_TOKEN:
            error_message.append("Unrecognized symbol");
            break;

        case MISSING_QUOTE:
            error_message.append("Missing quote");
            suggestion = "\n\n\tSuggestion: Add \" or '.";
            break;

        default:
            error_message.append("Unrecognized error");
            break;
    }

    error_message.append(get_place(file_name, lineno, line_index))
                 .append(get_formatted_line(line, lineno))
                 .append(get_error_squiggle(lineno, line_index))
                 .append(suggestion);

    return error_message;
}