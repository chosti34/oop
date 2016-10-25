#include "stdafx.h"
#include "file_processor.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid amount of arguments!\n"
                  << "Usage: mini_dictionary.exe <dictionary file>" << std::endl;
        return 1;
    }

    std::ifstream input;

    if (!OpenFileForReading(input, argv[1]))
    {
        std::cout << "Failed to open " << argv[1] << " for reading..." << std::endl;
        return 1;
    }

    return 0;
}
