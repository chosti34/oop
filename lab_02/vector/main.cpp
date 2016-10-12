#include <iostream>
#include <iterator>
#include <vector>

void PrintVector(std::vector<int> &vect)
{
    for (int i = 0; i < vect.size(); ++i)
    {
        std::cout << vect[i] << " ";
    }
    std::cout << '\n';
}

int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> vect(arr, arr + 10);

    PrintVector(vect);

    return 0;
}
