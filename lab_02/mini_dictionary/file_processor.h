#pragma once

bool OpenFileForReading(std::ifstream &file, const std::string &fileName);
bool OpenFileForWriting(std::ofstream &file, const std::string &fileName);
bool IsEndOfFile(std::ifstream &file);
