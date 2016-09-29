#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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

void ReplaceString(string &str, const string &searchStr, const string &replaceStr)
{
    size_t i = 0;
    size_t position = str.find(searchStr, i);

    string newStr;
    newStr.reserve(str.length());

    while ((position != string::npos) || (i != str.length()))
    {
        if (i != position)
        {
            newStr += str[i];
            ++i;
        }
        else
        {
            newStr += replaceStr;
            i += searchStr.length();
            position = str.find(searchStr, i);
        }
    }

    str.swap(newStr);
}

bool ReplaceStringsInFile(ifstream &input, ofstream &output, const string &searchStr, const string &replaceStr)
{
    if (searchStr.length() == 0)
    {
        return false;
    }

    string currStr;

    while (getline(input, currStr))
    {
        ReplaceString(currStr, searchStr, replaceStr);
        output << currStr << endl;
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        cout << "Invalid amount of arguments!\n"
             << "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
        return 1;
    }

    ifstream input;
    ofstream output;

    if (!OpenFileForReading(input, argv[1]))
    {
        cout << "Failed to open " << argv[1] << " for reading!\n";
        return 1;
    }

    if (!OpenFileForWriting(output, argv[2]))
    {
        cout << "Failed to open " << argv[2] << " for writing!\n";
        return 1;
    }

    if (!ReplaceStringsInFile(input, output, argv[3], argv[4]))
    {
        cout << "String to search cannot be empty!\n";
        return 1;
    }

    if (!output.flush())
    {
        cout << "Failed to save data on disk\n";
        return 1;
    }

    cout << "All '" << argv[3] << "' was replaced into '" << argv[4] 
         << "' from '" << argv[1] << "' to '" << argv[2] << "'!\n";

    return 0;
}
