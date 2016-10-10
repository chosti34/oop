#include <iostream>
#include <iomanip>

#include "field.h"

using namespace std;

void InitializeField(Field &field)
{
    for (int row = 0; row < MAX_HEIGHT; ++row)
    {
        for (int col = 0; col < MAX_WIDTH; ++col)
        {
            field[row][col] = -10;
        }
    }
}

void DrawField(Field &field)
{
    for (int row = 0; row < 30; ++row)
    {
        for (int col = 0; col < 30; ++col)
        {
            cout << setw(3) << field[row][col] << " ";
        }
        cout << endl;
    }
}
