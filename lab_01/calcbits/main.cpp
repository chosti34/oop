#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

int AmountOfBits(int &number)
{
    int bits = 0;

    while (number != 0)
    {
        bits += (number & 1);
        number >>= 1;
    }

    return bits;
}

bool InRangeByte(const int &number)
{
    return ((number >= 0) && (number <= 255));
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n"
             << "Usage: calcbits.exe <byte>\n";
        return 1;
    }

    int number;

    try
    {
        number = stoi(argv[1]);
    }
    catch (exception &error)
    {
        cout << "Exception occurred: " << error.what() << endl;
        return 1;
    }

    if (InRangeByte(number))
    {
        cout << AmountOfBits(number) << endl;
    }
    else
    {
        cout << "Out of range!\n";
        return 1;
    }

    return 0;
}