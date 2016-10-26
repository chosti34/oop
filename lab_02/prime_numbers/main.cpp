#include "stdafx.h"
#include "prime_numbers.h"

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

    const int upperBoundMaxValue = 100000000;

    if (upperBound > upperBoundMaxValue)
    {
        std::cout << "Upper bound must be less than " << upperBoundMaxValue << std::endl;
        return 1;
    }
    else if (upperBound < 0)
    {
        std::cout << "Upper bound can't be negative" << std::endl;
        return 1;
    }

    std::set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
    PrintSet(std::cout, primeNumbers);

    std::cout << "Amount of prime numbers in [2 .. " << upperBound << "]: " << primeNumbers.size() << std::endl;

    return 0;
}
