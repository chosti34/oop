#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void OpenFileForReading(ifstream &file, const string &fileName)
{
    file.open(fileName);

    if (!file.is_open())
    {
        cout << "Failed to open " << fileName << " for reading!" << endl;
        exit(1);
    }

    if (file.eof())
    {
        cout << "File is empty, nothing to read...";
        exit(1);
    }
}

void OpenFileForWriting(ofstream &file, const string &fileName)
{
    file.open(fileName);

    if (!file.is_open())
    {
        cout << "Failed to open " << fileName << " for writing!" << endl;
        exit(1);
    }
}

void ReplaceString(string &str, const string &searchStr, const string &replaceStr)
{
    size_t position = 0;
    size_t i = 0;

    string newStr = "";

    while (((position = str.find(searchStr, position)) != string::npos) || (i != str.length()))
    {
        if (i == position)
        {
            newStr += replaceStr;
            position += searchStr.length();
            i += searchStr.length();
        }
        else
        {
            newStr += str[i];
            ++i;
        }
    }

    str = newStr;
}

void ReplaceStringsInFile(ifstream &input, ofstream &output, const string &searchStr, const string &replaceStr)
{
    if (searchStr.length() == 0)
    {
        cout << "String to search cannot be empty" << endl;
        exit(1);
    }

    string currStr;

    while (getline(input, currStr))
    {
        ReplaceString(currStr, searchStr, replaceStr);

        output << currStr << endl;
    }

    if (!output.flush())
    {
        cout << "Failed to save data on disk\n";
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        cout << "Invalid arguments count\n"
             << "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
        return 1;
    }

    ifstream input;
    ofstream output;

    OpenFileForReading(input, argv[1]);
    OpenFileForWriting(output, argv[2]);

    ReplaceStringsInFile(input, output, argv[3], argv[4]);

    cout << "All '" << argv[3] << "' was replaced into '"
         << argv[4] << "' from '" << argv[1] << "' to '" << argv[2] << "'!\n";

    return 0;
}