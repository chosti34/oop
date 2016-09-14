#include <iostream>
#include <fstream>
#include <string>

using namespace std;

float Multyply(float matrix1[3][3], float matrix2[3][3])
{
    float resultMatrix[3][3];

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            resultMatrix[i][j] = 0;

            for (int k = 0; k < 3; k++)
            {
                resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return resultMatrix[3][3];
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Invalid arguments count\n"
             << "Usage: multimatrix.exe <matrix file1> <matrix file2>\n";
        return 1;
    }

    ifstream input1(argv[1]);

    if (!input1.is_open())
    {
        cout << "Failed to open " << argv[1] << " for reading!\n";
        return 1;
    }

    ifstream input2(argv[2]);
    
    if (!input2.is_open())
    {
        cout << "Failed to open " << argv[2] << " for reading!\n";
        return 1;
    }

    float matrix1[3][3], matrix2[3][3];

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            input1 >> matrix1[i][j];
            input2 >> matrix2[i][j];
        }
    }

    float resultMatrix[3][3];

    resultMatrix[3][3] = Multyply(matrix1, matrix2);

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cout << resultMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}