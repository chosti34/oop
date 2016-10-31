#include "stdafx.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    std::string str;
    std::regex regularExpression("(\\+|-)?[[:digit:]]+");

    while (true)
    {
        std::cout << "������� �����:\n";
        std::cin >> str;

        if (str == "q")
        {
            break;
        }
        else if (regex_match(str, regularExpression))
        {
            std::cout << "����� �����!\n\n";
        }
        else
        {
            std::cout << "�� ����� �����!\n\n";
        }
    }

    return 0;
}
