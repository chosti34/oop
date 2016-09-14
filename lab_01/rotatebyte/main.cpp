#include <iostream>
#include <string>

void RightBitShift(int &number, const int &position)
{
    number = (number >> position) | (number << (8 - position) & 255);
}

void LeftBitShift(int &number, const int &position)
{
    number = (number << position) | (number >> (8 - position) & 255);
}

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "Invalid argument count!" << endl;
        return 1;
    }

    int number, position;
    string choice;

    try
    {
        number = stoi(argv[1]);
        position = stoi(argv[2]);
        choice = argv[3];
    }
    catch (exception &error)
    {
        cout << error.what() << endl;
        return 1;
    }

    if (choice == "R")
    {
        RightBitShift(number, position);
    }
    else if (choice == "L")
    {
        LeftBitShift(number, position);
    }
    else
    {
        cout << "Invalid 3rd argument..." << endl;
        return 1;
    }

    cout << "Rotated number: " << number << endl;

    return 0;
}