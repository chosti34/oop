#include "stdafx.h"
#include "file_processor.h"
#include "dictionary.h"

void InitializeDictionaryFromFile(std::ifstream &file, Dictionary &dictionary)
{
    std::string str;

    while (std::getline(file, str))
    {
        std::vector<std::string> vect;
        boost::split(vect, str, boost::is_any_of(":"));
        if (vect.size() == 2)
        {
            std::pair<std::string, std::string> wordPair = make_pair(vect[0], vect[1]);
            dictionary.insert(wordPair);
        }
    }
}

bool IsWordInDictionary(const std::string &word, const Dictionary &dictionary)
{
    return (dictionary.find(word) != dictionary.end());
}

std::string GetWordTranslationFromDictionary(const std::string &word, const Dictionary &dictionary)
{
    auto iterator = dictionary.find(word);

    return iterator->second;
}

void InsertTranslationIntoDictionary(const std::string &word, const std::string &translation, Dictionary &dictionary)
{
    std::pair<std::string, std::string> wordPair = make_pair(word, translation);
    dictionary.insert(wordPair);
}

void SaveDictionaryInFile(std::ofstream &file, Dictionary &dictionary)
{
    for (auto iterator = dictionary.begin(); iterator != dictionary.end(); ++iterator)
    {
        file << iterator->first << ":" << iterator->second << '\n';
    }
    file.close();
}

Dictionary GetDictionaryFromFile(const std::string &fileName)
{
    Dictionary dictionary;

    std::ifstream input;
    OpenFileForReading(input, fileName);
    InitializeDictionaryFromFile(input, dictionary);
    input.close();

    return dictionary;
}

void ProcessUnknownWordInDictionary(Dictionary &dictionary, const std::string &word, std::string &translation, bool &isDictionaryChanged, bool &isUserWantsToUseDictionary)
{
    std::cout << "Unknown word \"" << word << "\". Enter the translation (empty string to skip).\n> ";
    std::getline(std::cin, translation);

    if ((translation != "...") && (!translation.empty()))
    {
        InsertTranslationIntoDictionary(word, translation, dictionary);
        std::cout << "Word \"" << word << "\" saved in dictionary as \"" << translation << "\".\n";
        isDictionaryChanged = true;
    }
    else if (translation == "...")
    {
        isUserWantsToUseDictionary = false;
    }
    else
    {
        std::cout << "Word \"" << word << "\" has been ignored.\n";
    }
}

void EnterTranslationMainLoop(Dictionary &dictionary, bool &isDictionaryChanged)
{
    std::cout << "Type any word for translation (... for exit):\n";

    bool isUserWantsToUseDictionary = true;
    while (isUserWantsToUseDictionary)
    {
        std::string word, translation;

        std::cout << "> ";
        std::getline(std::cin, word);

        if (word == "...")
        {
            isUserWantsToUseDictionary = false;
        }
        else if (IsWordInDictionary(word, dictionary))
        {
            translation = GetWordTranslationFromDictionary(word, dictionary);
            std::cout << translation << "\n";
        }
        else if (!word.empty())
        {
            ProcessUnknownWordInDictionary(dictionary, word, translation, isDictionaryChanged, isUserWantsToUseDictionary);
        }
    }
}

void ProcessChangesInDictionary(Dictionary &dictionary, const std::string &fileName)
{
    char choice;

    std::cout << "Dictionary has been changed. Do you want to save changes? (Y/y): ";
    std::cin >> choice;

    if (tolower(choice) == 'y')
    {
        std::ofstream output;
        OpenFileForWriting(output, fileName);
        SaveDictionaryInFile(output, dictionary);
        std::cout << "Changes saved. Good bye!" << std::endl;
    }
    else
    {
        std::cout << "Changes are not saved. Good bye!" << std::endl;
    }
}
