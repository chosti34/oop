#include "stdafx.h"
#include "vector_processor.h"

// —читываем в вектор кол-во чисел с потока ввода strm, равное параметру amount
std::vector<double> GetNumbers(std::istream &strm, int amount)
{
    std::vector<double> vect;

    double number;

    for (int i = 0; i < amount; ++i)
    {
        if (strm >> number)
        {
            vect.push_back(number);
        }
        else if (!strm.eof())
        {
            strm.clear();
            strm.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            --i;
        }
    }

    return vect;
}

void PrintVector(const std::vector<double> &vect, std::ostream &strm)
{
    std::copy(vect.begin(), vect.end(), std::ostream_iterator<double>(strm << std::fixed << std::setprecision(3), " "));
    strm << std::endl;
}
