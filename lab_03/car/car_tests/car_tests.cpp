#include "stdafx.h"
#include "../Car.h"

struct CarFixture
{
    CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)
    BOOST_AUTO_TEST_CASE(car_engine_is_turned_off_by_default)
    {
        BOOST_CHECK(!car.IsTurnedOn());
    }

    BOOST_AUTO_TEST_SUITE(if_car_engine_is_turned_off)
        BOOST_AUTO_TEST_CASE(engine_can_be_turned_on)
        {
            BOOST_CHECK(car.TurnOnEngine());
        }

        BOOST_AUTO_TEST_CASE(engine_cannot_be_turned_off)
        {
            BOOST_CHECK(!car.TurnOffEngine());
        }
    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
