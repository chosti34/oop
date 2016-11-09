#pragma once

typedef std::map<std::string, std::string> Dictionary;

Dictionary GetDictionaryFromFile(const std::string &fileName);
void InitializeDictionaryFromFile(std::ifstream &file, Dictionary &dictionary);
void SaveDictionaryInFile(std::ofstream &file, Dictionary &dictionary);
void InsertTranslationIntoDictionary(const std::string &word, const std::string &translation, Dictionary &dictionary);
bool EnterTranslationMainLoop(Dictionary &dictionary, bool &isDictionaryChanged);
void ProcessUnknownWordInDictionary(Dictionary &dictionary, const std::string &word, std::string &translation, bool &isDictionaryChanged, bool &isUserWantsToUseDictionary);
void ProcessChangesInDictionary(Dictionary &dictionary, const std::string &fileName);
bool IsWordInDictionary(const std::string &word, const Dictionary &dictionary);
std::string GetWordTranslationFromDictionary(const std::string &word, const Dictionary &dictionary);
