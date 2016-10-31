#include "stdafx.h"
#include "url_parse.h"

int main()
{
    std::cout << "Input URL: (\"...\" for exit)\n";

    bool isUserWantsToUseApplication = true;
    while (isUserWantsToUseApplication)
    {
        Url url;
        std::string stringBuffer;

        std::cout << "> ";
        std::cin >> stringBuffer;

        if (stringBuffer == "...")
        {
            isUserWantsToUseApplication = false;
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
