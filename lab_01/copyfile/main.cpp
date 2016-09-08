#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    if (argc != 3)
    {
        std::cout << "������� <�������_����> <��������_����>" << std::endl;
        exit(1);
    }

    std::ifstream infile(argv[1]);

    if (!infile)
    {
        std::cout << "������ �������� ����� ��� ������" << std::endl;
        exit(1);
    }

    std::ofstream outfile(argv[2]);

    if (!outfile)
    {
        std::cout << "������ �������� ����� ��� ������" << std::endl;
        exit(1);
    }

    std::string str;

    while (!infile.eof())
    {
        std::getline(infile, str);

        outfile << str << std::endl;
    }

    std::cout << "���� " << argv[1] << " ��� ���������� � " << argv[2];

    infile.close();
    outfile.close();

    return 0;
}