#include "stdafx.h"
#include "html_processor.h"
#include "string_processor.h"

const std::array<const std::pair<const std::string, const char>, 5> htmlChars = {
    { {"&quot;", '\"'}, {"&apos;", '\''}, {"&lt;", '<'}, {"&gt;", '>'}, {"&amp;", '&'} },
};

bool FindAndReplaceHtmlChar(const std::string &str, std::string &result, size_t &position)
{
    bool found = false;

    for (auto htmlChar : htmlChars)
    {
        if (IsStrContains(str, htmlChar.first, position))
        {
            result += htmlChar.second;
            position += htmlChar.first.length() - 1;
            found = true;
            break;
        }
    }

    return found;
}

std::string HtmlDecode(const std::string &str)
{
    std::string result;
    result.reserve(str.length());

    for (size_t i = 0; i < str.length(); ++i)
    {
        bool decoded = false;

        if (str[i] == '&')
        {
            decoded = FindAndReplaceHtmlChar(str, result, i);
        }

        if (!decoded)
        {
            result += str[i];
        }
    }

    return result;
}
