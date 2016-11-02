#include "stdafx.h"
#include "VectorProcessor.h"

double GetMaxElement(const std::vector<double> &vect)
{
    return *std::max_element(vect.begin(), vect.end());
}

std::vector<double> GetVector()
{
    return { std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()) };
}

void ProcessVector(std::vector<double> &vect)
{
    if (!vect.empty())
    {
        double maxElement = GetMaxElement(vect);
        if (maxElement != 0)
        {
            std::transform(vect.begin(), vect.end(), vect.begin(), [maxElement](double number) { return number / (maxElement / 2); });
        }
    }
}

void PrintVector(std::ostream &output, const std::vector<double> &vect)
{
    std::copy(vect.begin(), vect.end(), std::ostream_iterator<double>(output << std::fixed << std::setprecision(3), " "));
}
