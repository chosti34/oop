#include "stdafx.h"
#include "url_parse.h"

int main()
{
    std::cout << "Enter URL: (\"...\" for exit)\n";

    bool doesUserWantsToUseApplication = true;
    while (doesUserWantsToUseApplication)
    {
        Url url;
        std::string stringBuffer;

        std::cout << "> ";
        std::cin >> stringBuffer;

        if ((stringBuffer == "...") || (std::cin.eof()) || (std::cin.fail()))
        {
            doesUserWantsToUseApplication = false;
        }
        else if (ParseURL(stringBuffer, url))
        {
            PrintURL(url);
        }
        else
        {
            std::cout << "Invalid URL!\n";
        }        
    }

    return 0;
}
