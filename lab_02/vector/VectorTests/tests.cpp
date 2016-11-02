#include "stdafx.h"
#include "../VectorProcessor.h"

bool VectorsAreEqual(const std::vector<double> &x, const std::vector<double> &y)
{
    return (x == y);
}

BOOST_AUTO_TEST_SUITE(GetMaxElement_function)
    BOOST_AUTO_TEST_CASE(must_get_max_element_from_positive)
    {
        std::vector<double> vect = {1, 2, 3, 10, 1, 9, 15, 5};
        double max = GetMaxElement(vect);
        BOOST_CHECK(max == 15);
    }

    BOOST_AUTO_TEST_CASE(must_get_max_element_from_negative)
    {
        std::vector<double> vect = {-3, -10, -4, -19};
        double max = GetMaxElement(vect);
        BOOST_CHECK(max == -3);
    }

    BOOST_AUTO_TEST_CASE(must_get_zero)
    {
        std::vector<double> vect = {-3, -10, -4, 0};
        double max = GetMaxElement(vect);
        BOOST_CHECK(max == 0);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GetVector_function)
    BOOST_AUTO_TEST_CASE(checking_function_with_some_correct_string)
    {
        std::string str = "123 1.3 14.3";
        std::vector<double> vect = GetVector(str);
        std::vector<double> correctVect = {123, 1.3, 14.3};
        BOOST_CHECK(vect == correctVect);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ProcessVector_function)
    BOOST_AUTO_TEST_CASE(checking_function_with_empty_vector)
    {
        std::vector<double> vect;
        ProcessVector(vect);
        BOOST_CHECK(vect.empty());
    }

    BOOST_AUTO_TEST_CASE(checking_function_with_some_vector)
    {
        std::vector<double> vect = {5, 10, 20};
        ProcessVector(vect);
        BOOST_CHECK(VectorsAreEqual(vect, {0.5, 1, 2}));
    }

    BOOST_AUTO_TEST_CASE(vector_with_zero_max_element)
    {
        std::vector<double> vect = {-3, 0, -2};
        ProcessVector(vect);
        BOOST_CHECK(VectorsAreEqual(vect, {-3, -2, 0}));
    }
BOOST_AUTO_TEST_SUITE_END()
