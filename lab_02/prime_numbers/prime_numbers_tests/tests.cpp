#include "stdafx.h"
#include "../prime_numbers.h"

BOOST_AUTO_TEST_SUITE(GeneratePrimeNumbersSet_function)
    BOOST_AUTO_TEST_CASE(try_to_create_set_with_1_upperbound)
    {
        int upperBound = 1;
        std::set<int> emptySet = {};
        BOOST_CHECK(GeneratePrimeNumbersSet(upperBound) == emptySet);
    }

    BOOST_AUTO_TEST_CASE(try_to_create_set_with_50_upperbound)
    {
        int upperBound = 50;
        std::set<int> correctSet = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
        BOOST_CHECK(GeneratePrimeNumbersSet(upperBound) == correctSet);
    }

    BOOST_AUTO_TEST_CASE(try_to_create_set_with_maximum_upperbound)
    {
        int upperBound = 100000000;
        int correctAmountOfElements = 5761455;
        BOOST_CHECK(GeneratePrimeNumbersSet(upperBound).size() == correctAmountOfElements);
    }
BOOST_AUTO_TEST_SUITE_END()
