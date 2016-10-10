#include "files.h"

bool OpenFileForReading(ifstream &file, const string &fileName)
{
    file.open(fileName);
    return file.is_open();
}

bool OpenFileForWriting(ofstream &file, const string &fileName)
{
    file.open(fileName);
    return file.is_open();
}
