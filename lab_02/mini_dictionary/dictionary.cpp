#include "stdafx.h"
#include "dictionary.h"

void InitializeDictionaryFromFile(std::ifstream &file, std::map<std::string, std::string> &dictionary)
{
    std::string word, translation;

    while (file >> word >> translation)
    {
        std::pair<std::string, std::string> wordPair =  make_pair(word, translation);
        dictionary.insert(wordPair);
    }
}

bool IsWordInDictionary(const std::string &word, const std::map<std::string, std::string> &dictionary)
{
    return (dictionary.find(word) != dictionary.end());
}

std::string GetWordTranslationFromDictionary(const std::string &word, const std::map<std::string, std::string> &dictionary)
{
    auto iterator = dictionary.find(word);

    return iterator->second;
}

void InsertTranslationIntoDictionary(const std::string &word, const std::string &translation, std::map<std::string, std::string> &dictionary)
{
    
}
