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
        cout << "Failed to open " << fileName << " for reading!" << endl;
        exit(1);
    }

    if (file.eof())
    {
        cout << "File " << fileName << " is empty! Nothing to read..." << endl;
        exit(1);
    }
}

void ReadMatrixFromFile(ifstream &file, double (&matrix)[3][3])
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            file >> matrix[row][col];
        }
    }
}

void PrintMatrix(double (&matrix)[3][3])
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            if (matrix[row][col] != 0)
            {
                cout << fixed << setw(10) << setprecision(3) << matrix[row][col] << " ";
            }
            else
            {
                cout << setw(10) << 0 << " ";
            }
        }
        cout << endl;
    }
}

double GetMinor(const double (&matrix)[3][3], const int i, const int j)
{
    double minorElements[4];
    int currElementIndex = 0;

    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            if ((row != i) && (col != j))
            {
                minorElements[currElementIndex] = matrix[row][col];
                ++currElementIndex;
            }
        }
    }

    return (minorElements[0] * minorElements[3]) - (minorElements[1] * minorElements[2]);
}

double GetDeterminant(double (&matrix)[3][3])
{
    double determinant = 0;
    int sign = 1;
    int row = 0;

    for (int col = 0; col < 3; ++col)
    {
        determinant += sign * matrix[row][col] * GetMinor(matrix, row, col);
        sign *= -1;
    }

    return determinant;
}

void SwapTwo(double &firstOperand, double &secondOperand)
{
    double temporaryElement;

    temporaryElement = firstOperand;
    firstOperand = secondOperand;
    secondOperand = temporaryElement;
}

void TransposeMatrix(double (&matrix)[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = i; j < 3; ++j)
        {
            SwapTwo(matrix[i][j], matrix[j][i]);
        }
    }
}

void MultiplyMatrixWithNumber(double (&matrix)[3][3], const double &number)
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            matrix[row][col] *= number;
        }
    }
}

void InvertMatrix(double (&matrix)[3][3])
{
    double cofactorMatrix[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    int sign = 1;

    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            cofactorMatrix[row][col] = sign * GetMinor(matrix, row, col);
            sign *= -1;
        }
    }

    TransposeMatrix(cofactorMatrix);
    MultiplyMatrixWithNumber(cofactorMatrix, 1 / GetDeterminant(matrix));

    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            matrix[row][col] = cofactorMatrix[row][col];
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Invalid amount of arguments!" << endl;
        cout << "Usage: invert.exe <matrix file>" << endl;

        return 1;
    }

    ifstream input;

    OpenFileForReading(input, argv[1]);

    double matrix[3][3];

    ReadMatrixFromFile(input, matrix);

    if (GetDeterminant(matrix) == 0)
    {
        cout << "Can't invert this matrix. Determinant equals to zero." << endl;
        return 1;
    }

    InvertMatrix(matrix);
    PrintMatrix(matrix);

    return 0;
}
