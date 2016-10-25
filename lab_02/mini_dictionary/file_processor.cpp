#include "stdafx.h"
#include "file_processor.h"

bool OpenFileForReading(std::ifstream &file, const std::string &fileName)
{
    file.open(fileName);
    return file.is_open();
}

bool OpenFileForWriting(std::ofstream &file, const std::string &fileName)
{
    file.open(fileName);
    return file.is_open();
}

bool IsEndOfFile(std::ifstream &file)
{
    return (file.peek() == std::ifstream::traits_type::eof());
}
