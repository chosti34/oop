#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void OpenFileForReading(ifstream &file, const string &fileName)
{
    file.open(fileName);

    if (!file.is_open())
    {
        cout << "Failed to open " << fileName << " for reading" << endl;
        exit(1);
    }

    if (file.eof())
    {
        cout << "File " << fileName << " is empty! Nothing to read..." << endl;
        exit(1);
    }
}

void ReadMatrixFromFile(ifstream &file, double matrix[3][3])
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            file >> matrix[row][col];
        }
    }
}

void MultiplyMatrix(double matrix1[3][3], double matrix2[3][3], double matrix3[3][3])
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            for (int inner = 0; inner < 3; ++inner)
            {
                matrix3[row][col] += matrix1[row][inner] * matrix2[inner][col];
            }
        }
    }
}

void PrintMatrix(double matrix[3][3])
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            cout << setw(10) << fixed << setprecision(3) << matrix[row][col] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Invalid arguments count!" << endl
             << "Usage: multimatrix.exe <file1> <file2>" << endl;
        return 1;
    }

    ifstream input1;
    ifstream input2;

    OpenFileForReading(input1, argv[1]);
    OpenFileForReading(input2, argv[2]);
    
    double matrix1[3][3], matrix2[3][3];

    ReadMatrixFromFile(input1, matrix1);
    ReadMatrixFromFile(input2, matrix2);

    double matrix3[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    MultiplyMatrix(matrix1, matrix2, matrix3);

    PrintMatrix(matrix3);

    return 0;
}
