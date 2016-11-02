#include "stdafx.h"
#include "file_processor.h"
#include "dictionary.h"

int main(int argc, char *argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Dictionary dictionary;
    std::string fileName;

    if (argc == 2)
    {
        fileName = argv[1];
        dictionary = GetDictionaryFromFile(fileName);
    }
    else
    {
        fileName = "dictionary.txt";
    }

    bool isDictionaryChanged = false;
    EnterTranslationMainLoop(dictionary, isDictionaryChanged);

    if (isDictionaryChanged)
    {
        ProcessChangesInDictionary(dictionary, fileName);
    }
    else
    {
        std::cout << "Good bye!" << std::endl;
    }

    return 0;
}
