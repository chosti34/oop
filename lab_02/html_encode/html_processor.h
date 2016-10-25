#pragma once

std::map<char, std::string> htmlSpecialChars = {
    {'"', "&quot;"},
    {'\'', "&apos;"},
    {'<', "&lt;"},
    {'>', "&gt;"},
    {'&', "&amp;"}
};

bool IsKeyExists(const char key, const std::map<char, std::string> &container)
{
    return (container.find(key) != std::end(container));
}

std::string HtmlEncode(const std::string &text)
{
    std::string result;

    for (size_t i = 0; i < text.length(); ++i)
    {
        if (IsKeyExists(text[i], htmlSpecialChars))
        {
            result += htmlSpecialChars[text[i]];
        }
        else
        {
            result += text[i];
        }
    }

    return result;
}
