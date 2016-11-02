#include "stdafx.h"
#include "prime_numbers.h"

std::vector<bool> GetPrimeNumbersVector(const int upperBound)
{
    if (upperBound <= 0)
    {
        return {};
    }

    std::vector<bool> isPrimeNumber(upperBound + 1, true);
    isPrimeNumber[0] = isPrimeNumber[1] = false;

    const int minimalPrimeNumber = 2;

    // Решето Эратосфена
    for (int i = minimalPrimeNumber; (i * i) <= upperBound; ++i)
    {
        if (isPrimeNumber[i])
        {
            int position = i;
            while (position <= (upperBound - i))
            {
                position += i;
                isPrimeNumber[position] = false;
            }
        }
    }

    return isPrimeNumber;
}

std::set<int> GeneratePrimeNumbersSet(const int upperBound)
{
    if (upperBound <= 0)
    {
        return {};
    }

    std::vector<bool> isPrimeNumber = GetPrimeNumbersVector(upperBound); // получаем вектор с информацией о простоте чисел

    std::set<int> primeNumbers;

    for (int i = 0; i <= upperBound; ++i)
    {
        if (isPrimeNumber[i])
        {
            primeNumbers.emplace_hint(primeNumbers.end(), i);
        }
    }

    return primeNumbers;
}

void PrintSet(std::ostream &output, std::set<int> &container)
{
    std::copy(container.begin(), container.end(), std::ostream_iterator<int>(output, " "));
}
