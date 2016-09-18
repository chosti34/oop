#include <iostream>
#include <string>

using namespace std;

enum Directions
{
    leftDirection, rightDirection
};

void ShiftBitsInByte(unsigned int &byte, unsigned int &bits, const enum Directions &choice)
{
    bits %= 8;

    switch (choice)
    {
        case rightDirection:
        {
            byte = (byte >> bits) | (byte << (8 - bits));
            byte &= 255;
            break;
        }
        case leftDirection:
        {
            byte = (byte << bits) | (byte >> (8 - bits));
            byte &= 255;
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "Invalid arguments count!" << endl
             << "Usage: rotatebyte.exe <byte> <number of bits> <L / R>" << endl;
        return 1;
    }

    string choice = argv[3];

    if ((choice != "R") && (choice != "L"))
    {
        cout << "Invalid third argument! Usage: <L / R> instead of " << argv[3] << endl;
        return 1;
    }

    unsigned int byte, bits;

    try
    {
        byte = stoi(argv[1]);
        bits = stoi(argv[2]);
    }
    catch (const invalid_argument &error)
    {
        cout << "Error: " << error.what() << endl;
        return 1;
    }
    catch (const out_of_range &error)
    {
        cout << "Error" << error.what() << endl;
        return 1;
    }

    if ((byte < 0) || (byte > 255))
    {
        cout << "<byte> should be in range [0-255]" << endl;
        return 1;
    }

    Directions direction;

    if (choice == "R")
    {
        direction = rightDirection;
    }
    else if (choice == "L")
    {
        direction = leftDirection;
    }

    ShiftBitsInByte(byte, bits, direction);

    cout << byte << endl;

    return 0;
}
