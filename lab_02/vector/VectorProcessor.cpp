#include "stdafx.h"
#include "VectorProcessor.h"

void ProcessVector(std::vector<double> &vect)
{
    for (size_t i = 0; i < vect.size(); ++i)
    {
        vect[i] *= -1;
    }
}
