#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ReplaceString(string &str, const string &searchStr, const string &replaceStr)
{
    int position = 0;

    while ((position = str.find(searchStr, position)) != string::npos)
    {
        str.replace(position, searchStr.length(), replaceStr);
        position += replaceStr.length();
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

    ifstream input(argv[1]);

    if (!input.is_open())
    {
        cout << "Failed to open " << argv[1] << " for reading\n";
        return 1;
    }

    ofstream output(argv[2]);

    if (!input.is_open())
    {
        cout << "Failed to open " << argv[2] << " for writing\n";
        return 1;
    }

    string searchStr = argv[3];
    string replaceStr = argv[4];
    string currStr;

    if (searchStr.length() == 0)
    {
        cout << "String to search cannot be empty!\n";
        return 1;
    }

    while (!input.eof())
    {
        getline(input, currStr);

        ReplaceString(currStr, searchStr, replaceStr);

        output << currStr << endl;
    }

    if (!output.flush())
    {
        cout << "Failed to save data on disk\n";
        return 1;
    }
    else
    {
        cout << "All '" << argv[3] << "' was replaced into '"
             <<  argv[4] << "' from '" << argv[1] << "' to '" << argv[2] << "'!\n";
    }

    return 0;
}