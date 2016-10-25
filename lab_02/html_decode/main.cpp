#include "stdafx.h"
#include "html_processor.h"

int main()
{
    std::string str, result;

    std::cout << "Enter the text to decode:\n";

    while (std::getline(std::cin, str))
    {
        result += HtmlDecode(str) + '\n';
    }

    std::cout << "Decoded text:\n" << result;

    return 0;
}
