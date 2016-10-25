#include "stdafx.h"

bool NumbersAreEqual(const int x, const int y)
{
    return (x == y);
}

BOOST_AUTO_TEST_SUITE(some_func)
    BOOST_AUTO_TEST_CASE(must_get_max_element_from_positive)
    {
        int x = 5;
        int y = x;
        BOOST_CHECK(NumbersAreEqual(x, y));
    }
BOOST_AUTO_TEST_SUITE_END()
