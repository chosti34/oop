#include "stdafx.h"
#include "vector_processor.h"

std::vector<double> GetVector(std::istream &strm)
{
    return { std::istream_iterator<double>(strm), (std::istream_iterator<double>()) };
}

void ProcessVector(std::vector<double> &vect)
{
    if (!vect.empty())
    {
        double maxElement = *std::max_element(vect.begin(), vect.end());
        if (maxElement != 0)
        {
            std::transform(vect.begin(), vect.end(), vect.begin(), [maxElement](double number) { return number / (maxElement / 2); });
        }
    }
}

void SortVector(std::vector<double> &vect)
{
    std::sort(vect.begin(), vect.end());
}

void PrintVector(std::ostream &output, const std::vector<double> &vect)
{
    std::copy(vect.begin(), vect.end(), std::ostream_iterator<double>(output << std::fixed << std::setprecision(3), " "));
}
