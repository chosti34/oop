#include "stdafx.h"
#include "vector_processor.h"

int main()
{
    std::cout << "Enter some numbers separated by space:\n";

    std::vector<double> vect = GetVector(std::cin);

    if (!vect.empty())
    {
        ProcessVector(vect);
        SortVector(vect);
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
