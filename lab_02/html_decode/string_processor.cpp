#include "stdafx.h"
#include "string_processor.h"

void ReplaceString(std::string &str, const std::string &search, const std::string &replace)
{
    size_t i = 0;
    size_t position = str.find(search, i);

    std::string newStr;
    newStr.reserve(str.length());

    while ((position != std::string::npos) || (i != str.length()))
    {
        if (i != position)
        {
            newStr += str[i];
            ++i;
        }
        else
        {
            newStr += replace;
            i += search.length();
            position = str.find(search, i);
        }
    }

    str.swap(newStr);
}
