#include "stdafx.h"
#include "VectorProcessor.h"

int main()
{
    std::cout << "Enter some numbers separated by space:\n";

    std::vector<double> vect = GetVector();

    if (!vect.empty())
    {
        ProcessVector(vect);
        std::sort(vect.begin(), vect.end());
        std::cout << "Vector has been processed. New vector:\n";
        PrintVector(std::cout, vect);
        std::cout << std::endl;
    }
    else
    {
        std::cout << "You entered an empty vector..." << std::endl;
    }

    return 0;
}
