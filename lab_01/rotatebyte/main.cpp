#include <iostream>
#include <string>

using namespace std;

enum struct Direction
{
    NONE,
    RIGHT,
    LEFT
};

Direction SetRotateDirection(const string &choice)
{
    if (choice == "R")
    {
        return Direction::RIGHT;
    }
    else if (choice == "L")
    {
        return Direction::LEFT;
    }
    else
    {
        return Direction::NONE;
    }
}

uint8_t RotateBitsInByte(uint8_t byte, unsigned bits, const Direction direction)
{
    bits %= 8;

    switch (direction)
    {
        case Direction::RIGHT:
        {
            byte = (byte >> bits) | (byte << (8 - bits));
            byte &= 255;
            break;
        }
        case Direction::LEFT:
        {
            byte = (byte << bits) | (byte >> (8 - bits));
            byte &= 255;
            break;
        }
    }

    return byte;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "Invalid arguments count!\n"
             << "Usage: rotatebyte.exe <byte> <number of bits> <L / R>\n";
        return 1;
    }

    unsigned byte, bits;

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
        cout << "Error: " << error.what() << endl;
        return 1;
    }

    if ((byte < 0) || (byte > 255))
    {
        cout << "<byte> should be in range [0-255]" << endl;
        return 1;
    }

    string choice = argv[3];
    Direction direction = SetRotateDirection(choice);

    if (direction != Direction::NONE)
    {
        byte = RotateBitsInByte(byte, bits, direction);
        cout << byte << endl;
    }
    else
    {
        cout << "Invalid direction choice\n"
                "Use <R / L> instead of" << argv[3] << endl;
        return 1;
    }

    return 0;
}
