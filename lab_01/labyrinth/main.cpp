#include <iostream>

#include "labyrinth.h"
#include "files.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Invalid amount of arguments\n"
             << "Usage: labyrinth.exe <input file> <output file>" << endl;
        return 1;
    }

    ifstream input;
    if (!OpenFileForReading(input, argv[1]))
    {
        cout << "Failed to open " << argv[1] << " for reading!" << endl;
        return 1;
    }

    ofstream output;
    if (!OpenFileForWriting(output, argv[2]))
    {
        cout << "Failed to open " << argv[2] << " for writing!" << endl;
        return 1;
    }

    Labyrinth labyrinth;

    if (InitializeLabyrinthFromFile(input, labyrinth))
    {
        SetWaves(labyrinth);
        SetPath(labyrinth);
        DrawLabyrinth(output, labyrinth);
    }
    else
    {
        cout << "Incorrect amount of start and finish points!\n"
             << "Input file must have only 1 A and only 1 B" << endl;
        return 1;
    }

    return 0;
}
