#include "stdafx.h"
#include "file_processor.h"
#include "dictionary.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");

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

    std::map<std::string, std::string> dictionary;
    InitializeDictionaryFromFile(input, dictionary);
    input.close();

    bool IsUserWantsToUseDictionary = true;
    bool IsDictionaryChanged = false;

    std::cout << "Type any word for translation (... for exit):\n";

    while (IsUserWantsToUseDictionary)
    {
        std::string word, translation;

        std::cout << "> ";
        std::getline(std::cin, word);

        if (word == "...")
        {
            IsUserWantsToUseDictionary = false;
        }
        else if (IsWordInDictionary(word, dictionary))
        {
            translation = GetWordTranslationFromDictionary(word, dictionary);
            std::cout << translation << "\n";
        }
        else if (!word.empty())
        {
            std::cout << "Unknown word \"" << word << "\". Enter the translation (empty string to skip).\n> ";
            std::getline(std::cin, translation);

            if ((translation != "...") && (!translation.empty()))
            {
                InsertTranslationIntoDictionary(word, translation, dictionary);
            }
            else if (translation == "...")
            {
                IsUserWantsToUseDictionary = false;
            }
            else
            {
                std::cout << "Word \"" << word << "\" has been ignored.\n";
            }
        }
    }

    return 0;
}
