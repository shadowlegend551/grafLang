#ifndef CHECKS_H
#define CHECKS_H

std::string numbers = "0123456789";


bool is_alphabetical(char input_char)
{
    return (tolower(input_char) != input_char) || (toupper(input_char) != input_char);
}


bool isint(char input)
{
    for(char j : numbers)
    {
        if(input == j)
        {
            return true;
        }
    }

    return false;
}


bool is_skippable(char input)
{
    return input == ' ' || input == '\n' || input == '\t';
}

#endif