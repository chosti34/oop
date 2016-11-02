#include "stdafx.h"
#include "html_processor.h"

int main()
{
    std::string buffer, result;

    std::cout << "Enter the text to decode:\n";

    while (std::getline(std::cin, buffer))
    {
        result += HtmlDecode(buffer) + '\n';
    }

    std::cout << "Decoded text:\n" << result;

    return 0;
}
