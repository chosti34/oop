#include "stdafx.h"
#include "html_processor.h"

std::string HtmlDecode(const std::string &str)
{
    std::map<std::string, char> htmlSpecialChars = {
        {"&quot;", '\"'},
        {"&apos;", '\''},
        {"&lt;", '<'},
        {"&gt;", '>'},
        {"&amp;", '&'}
    };

    std::string result = str;

    for (auto iterator = htmlSpecialChars.begin(); iterator != htmlSpecialChars.end(); ++iterator)
    {
        size_t charLength = 1;

        std::string search(iterator->first);
        std::string replace(charLength, iterator->second);

        ReplaceString(result, search, replace);
    }

    return result;
}
