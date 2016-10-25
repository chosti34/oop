#pragma once

void InitializeDictionaryFromFile(std::ifstream &file, std::map<std::string, std::string> &dictionary);
void InsertTranslationIntoDictionary(const std::string &word, const std::string &translation, std::map<std::string, std::string> &dictionary);

bool IsWordInDictionary(const std::string &word, const std::map<std::string, std::string> &dictionary);

std::string GetWordTranslationFromDictionary(const std::string &word, const std::map<std::string, std::string> &dictionary);
