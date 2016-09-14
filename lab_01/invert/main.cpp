#include <iostream>
#include <fstream>
#include <string>

using namespace std;

float MinorDeterminant(float matrix[3][3], int position)
{
    float determinant = 0;

    switch (position)
    {
        case 1:
        {
            determinant = matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2];
            break;
        }
        case 2:
        {
            determinant = matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2];
            break;
        }
        case 3:
        {
            determinant = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];
            break;
        }
        case 4:
        {
            determinant = matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2];
            break;
        }
        case 5:
        {
            determinant = matrix[0][0] * matrix[2][2] - matrix[2][0] * matrix[0][2];
            break;
        }
        case 6:
        {
            determinant = matrix[0][0] * matrix[2][1] - matrix[2][0] * matrix[0][1];
            break;
        }
        case 7:
        {
            determinant = matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2];
            break;
        }
        case 8:
        {
            determinant = matrix[0][0] * matrix[1][2] - matrix[1][0] * matrix[0][2];
            break;
        }
        case 9:
        {
            determinant = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
            break;
        }
    }

    return determinant;
}

void Transpose(float matrix[3][3])
{
    int temp;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = i; j < 3; ++j)
        {
            temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Invalid arguments count\n"
             << "Usage: invert.exe <file>\n";
        return 1;
    }

    ifstream input(argv[1]);

    if (!input.is_open())
    {
        cout << "Failed to open " << argv[1] << " for reading!\n";
        return 1;
    }

    float matrix[3][3];

    // Reading matrix coefficients from file...
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            input >> matrix[i][j];
        }
    }

    float determinant = MinorDeterminant(matrix, 1) - MinorDeterminant(matrix, 2) + MinorDeterminant(matrix, 3);

    if (determinant == 0)
    {
        cout << "Determinant = 0. There is no inverse matrix.\n";
        return 0;
    }

    float newMatrix[3][3];
    int pos = 1;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            newMatrix[i][j] = MinorDeterminant(matrix, pos);
            ++pos;
            if ((pos == 2) || (pos == 4) || (pos == 6) || (pos == 8))
            {
                newMatrix[i][j] *= -1;
            }
        }
    }

    Transpose(newMatrix);

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            newMatrix[i][j] /= determinant;
            cout << newMatrix[i][j];
        }
        cout << endl;
    }

    return 0;
}