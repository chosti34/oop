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

bool GetMatrixCoefficientsFromFile(ifstream &file, Matrix3x3 matrix)
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            if (file >> matrix[row][col])
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

bool ReadMatrixFromFile(const string &fileName, Matrix3x3 matrix)
{
    ifstream input;

    if (!OpenFileForReading(input, fileName))
    {
        cout << "Failed to open " << fileName << " for reading!\n";
        return false;
    }

    if (!GetMatrixCoefficientsFromFile(input, matrix))
    {
        cout << "Can't read matrix from " << fileName << endl;
        return false;
    }

    return true;
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

void TransposeMatrix(Matrix3x3 matrix)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = i; j < 3; ++j)
        {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}

void MultiplyMatrixWithNumber(Matrix3x3 matrix, const double number)
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            matrix[row][col] *= number;
        }
    }
}

bool InvertMatrix(Matrix3x3 matrix)
{
    if (abs(GetDeterminant(matrix)) < DBL_EPSILON)
    {
        return false;
    }

    Matrix3x3 cofactorMatrix;
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

    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Invalid amount of arguments!\n"
             << "Usage: invert.exe <matrix file>\n";
        return 1;
    }

    Matrix3x3 matrix;

    if (!ReadMatrixFromFile(argv[1], matrix))
    {
        cout << "Please, try another file..." << endl;
        return 1;
    }

    if (!InvertMatrix(matrix))
    {
        cout << "Determinant equals to zero! Can't invert matrix..." << endl;
        return 1;
    }

    PrintMatrix(matrix);

    return 0;
}
