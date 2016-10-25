#include "stdafx.h"
#include "html_processor.h"

int main()
{
    std::string str, encodedText;

    std::cout << "Enter the text to encode:\n\n";

    while (std::getline(std::cin, str))
    {
        encodedText += HtmlEncode(str) + '\n';
    }

    std::cout << "\nEncoded text:\n" << encodedText;

    return 0;
}
