#include "stdafx.h"
#include "VectorProcessor.h"

int main()
{
    std::string str;

    std::cout << "Enter some numbers separated by space:\n";
    std::getline(std::cin, str);

    std::vector<double> vect = GetVector(str);

    if (!vect.empty())
    {
        ProcessVector(vect);
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
