#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

typedef double Matrix3x3[3][3];

using namespace std;

bool OpenFileForReading(ifstream &file, const string &fileName)
{
    file.open(fileName);
    return file.is_open();
}

void ReadMatrixFromFile(ifstream &file, Matrix3x3 matrix)
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            file >> matrix[row][col];
        }
    }
}

void PrintMatrix(Matrix3x3 matrix)
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

double GetMinor(Matrix3x3 matrix, const int i, const int j)
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

double GetDeterminant(Matrix3x3 matrix)
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

void TransposeMatrix(Matrix3x3 matrix)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = i; j < 3; ++j)
        {
            SwapTwo(matrix[i][j], matrix[j][i]);
        }
    }
}

void MultiplyMatrixWithNumber(Matrix3x3 matrix, const double &number)
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            matrix[row][col] *= number;
        }
    }
}

void InvertMatrix(Matrix3x3 matrix)
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
        cout << "Invalid amount of arguments!\n"
             << "Usage: invert.exe <matrix file>\n";
        return 1;
    }

    ifstream input;

    if (!OpenFileForReading(input, argv[1]))
    {
        cout << "Failed to open " << argv[1] << " for reading!\n";
        return 1;
    }

    Matrix3x3 matrix;

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
