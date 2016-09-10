#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Invalid arguments count\n"
             << "Usage: compare.exe <file1> <file2>\n";
        return 1;
    }

    ifstream input1(argv[1]);
    ifstream input2(argv[2]);

    if (!input1.is_open())
    {
        cout << "Failed to open " << argv[1] << " for reading\n";
        return 1;
    }

    if (!input2.is_open())
    {
        cout << "Failed to open " << argv[2] << " for reading\n";
        return 1;
    }

    string str1, str2;
    int lineNumber = 0;

    while (!input1.eof() && !input2.eof())
    {
        getline(input1, str1);
        getline(input2, str2);

        ++lineNumber;

        if ((!input1.eof() && input2.eof()) || (input1.eof() && !input2.eof()))
        {
            cout << "Amount of lines in both files is different\n";
            return 1;
        }
        else if (str1 != str2)
        {
            cout << "Files are different. Line number is " << lineNumber << '\n';
            return 1;
        }
    }

    cout << "Files are equal\n";

    return 0;
}