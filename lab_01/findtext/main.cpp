#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool IsSubStr(const string &substr, const string &str)
{
    return (str.find(substr) != string::npos);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Invalid arguments count\n"
             << "Usage: findtext.exe <file_name> <text_to_search>\n";
        return 1;
    }

    const string strToSearch = argv[2];

    if (strToSearch.length() == 0)
    {
        cout << "Text to search atleast must have one character\n";
        return 1;
    }

    ifstream input(argv[1]);

    if (!input.is_open())
    {
        cout << "Failed to open " << argv[1] << " for reading\n";
        return 1;
    }

    bool found = false;
    string currStr;

    for (int i = 0; !input.eof(); ++i)
    {
        getline(input, currStr);

        if (IsSubStr(strToSearch, currStr))
        {
            cout << "Match found at " << i + 1 << " string!\n";
            found = true; 
        }
    }

    if (!found)
    {
        cout << "Text not found\n";
        return 1;
    }
    else
    {
        return 0;
    }
}