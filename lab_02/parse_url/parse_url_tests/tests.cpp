#include "stdafx.h"

BOOST_AUTO_TEST_SUITE(test_for_tests)
    BOOST_AUTO_TEST_CASE(compare_two_numbers)
    {
        int x = 5;
        int y = 10;
        BOOST_CHECK(x != y);
    }
BOOST_AUTO_TEST_SUITE_END()
