#include "stdafx.h"
#include "VectorProcessor.h"

int main()
{
    std::vector<double> vect = {1, 2, 3};

    ProcessVector(vect);

    for (size_t i = 0; i < vect.size(); ++i)
    {
        std::cout << vect[i] << std::endl;
    }

    return 0;
}
