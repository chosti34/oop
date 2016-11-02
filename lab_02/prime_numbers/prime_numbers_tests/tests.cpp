#include "stdafx.h"
#include "../prime_numbers.h"

BOOST_AUTO_TEST_SUITE(GetPrimeNumbersVector_function)
    BOOST_AUTO_TEST_CASE(makes_empty_vector_when_upperbound_equals_to_zero)
    {
        int upperBound = 0;
        std::vector<bool> emptyVector = {};
        BOOST_CHECK(GetPrimeNumbersVector(upperBound) == emptyVector);
    }

    BOOST_AUTO_TEST_CASE(makes_some_boolean_vector_when_upperbound_equal_to_5)
    {
        int upperBound = 5;
        std::vector<bool> correctResult = {false, false, true, true, false, true};
        BOOST_CHECK(GetPrimeNumbersVector(upperBound) == correctResult);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GeneratePrimeNumbersSet_function)
    BOOST_AUTO_TEST_CASE(makes_empty_set_when_upperbound_equals_to_zero)
    {
        int upperBound = 0;
        std::set<int> emptySet = {};
        BOOST_CHECK(GeneratePrimeNumbersSet(upperBound) == emptySet);
    }

    BOOST_AUTO_TEST_CASE(makes_set_of_prime_numbers_with_15_elements_in_it_when_upper_bound_equals_to_50)
    {
        int upperBound = 50;
        std::set<int> correctSet = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
        BOOST_CHECK(GeneratePrimeNumbersSet(upperBound) == correctSet);
    }

#ifndef _DEBUG
    BOOST_AUTO_TEST_CASE(makes_set_of_prime_numbers_with_5761455_elements_in_it_when_upper_bound_equals_to_100000000)
    {
        int upperBound = 100000000;
        int correctAmountOfElements = 5761455;
        BOOST_CHECK(GeneratePrimeNumbersSet(upperBound).size() == correctAmountOfElements);
    }
#endif
BOOST_AUTO_TEST_SUITE_END()
