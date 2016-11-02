#include "stdafx.h"
#include "../vector_processor.h"

bool VectorsAreEqual(const std::vector<double> &x, const std::vector<double> &y)
{
    return (x == y);
}

BOOST_AUTO_TEST_SUITE(ProcessVector_function)
    BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
    {
        std::vector<double> vect;
        ProcessVector(vect);
        BOOST_CHECK(vect.empty());
    }

    BOOST_AUTO_TEST_CASE(divide_each_element_of_the_vector_by_half_of_the_max_element)
    {
        std::vector<double> vect = {0.4, 10, -4, 2};
        ProcessVector(vect);
        BOOST_CHECK(VectorsAreEqual(vect, {0.08, 2, -0.8, 0.4}));
    }

    BOOST_AUTO_TEST_CASE(does_not_change_vector_if_the_max_element_equals_to_zero)
    {
        std::vector<double> vect = {-3, 0, -2};
        ProcessVector(vect);
        BOOST_CHECK(VectorsAreEqual(vect, {-3, 0, -2}));
    }
BOOST_AUTO_TEST_SUITE_END()
