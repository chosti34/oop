#include "stdafx.h"
#include "file_processor.h"
#include "dictionary.h"

int main(int argc, char *argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Dictionary dictionary;

    if (argc == 2)
    {
        dictionary = GetDictionaryFromFile(argv[1]);
    }

    bool isDictionaryChanged = false;
    EnterTranslationMainLoop(dictionary, isDictionaryChanged);

    if (isDictionaryChanged)
    {
        ProcessChangesInDictionary(dictionary);
    }
    else
    {
        std::cout << "Good bye!" << std::endl;
    }

    return 0;
}
