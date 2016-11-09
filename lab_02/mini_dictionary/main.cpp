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
    }
    else
    {
        fileName = "dictionary.txt";
    }

    dictionary = GetDictionaryFromFile(fileName);

    bool isDictionaryChanged = false;
    bool isUserWorkedWithDictionaryCorrectly = EnterTranslationMainLoop(dictionary, isDictionaryChanged);

    if ((isDictionaryChanged) && (isUserWorkedWithDictionaryCorrectly))
    {
        ProcessChangesInDictionary(dictionary, fileName);
    }
    else
    {
        if (!isUserWorkedWithDictionaryCorrectly)
        {
            std::cout << "Next time type \"...\" for exit. Changes are not saved.\n";
        }
        std::cout << "Good bye!" << std::endl;
    }

    return 0;
}
