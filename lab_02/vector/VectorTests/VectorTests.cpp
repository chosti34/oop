#include "stdafx.h"
#include "../VectorProcessor.h"

bool VectorsAreEqualByMod(const std::vector<double> &vect1, const std::vector<double> &vect2)
{
    if (vect1.size() != vect2.size())
    {
        return false;
    }

    for (size_t i = 0; i < vect1.size(); ++i)
    {
        if (vect1[i] == -vect2[i])
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    return true;
}

BOOST_AUTO_TEST_SUITE(ProcessVector_function)
    BOOST_AUTO_TEST_CASE(must_get_all_negative_values)
    {
        std::vector<double> vect = {1, 2, 3};
        std::vector<double> tmp = vect;
        ProcessVector(vect);
        BOOST_CHECK(VectorsAreEqualByMod(vect, tmp));
    }
BOOST_AUTO_TEST_SUITE_END()