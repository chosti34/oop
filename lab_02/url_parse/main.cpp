#include "stdafx.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    std::string str;
    std::regex regularExpression("(\\+|-)?[[:digit:]]+");

    while (true)
    {
        std::cout << "Введите число:\n";
        std::cin >> str;

        if (str == "q")
        {
            break;
        }
        else if (regex_match(str, regularExpression))
        {
            std::cout << "Целое число!\n\n";
        }
        else
        {
            std::cout << "Не целое число!\n\n";
        }
    }

    return 0;
}
