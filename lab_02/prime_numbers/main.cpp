#include "stdafx.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid amount of arguments!\n"
                  << "Usage: prime_numbers.exe <upper bound>" << std::endl;
        return 1;
    }

    int upperBound;

    try
    {
        upperBound = std::stoi(argv[1]);
    }
    catch (const std::exception &error)
    {
        std::cout << "Error occured: " << error.what() << std::endl;
        return 1;
    }

    const int upperBoundMaxValue = 1000000;

    if (upperBound > upperBoundMaxValue)
    {
        std::cout << "Upper bound must be less than " << upperBoundMaxValue << std::endl;
        return 1;
    }

    // std::set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
    // PrintSet(std::cout, primeNumbers);

    return 0;
}
