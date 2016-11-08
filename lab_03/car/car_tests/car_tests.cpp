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

    BOOST_AUTO_TEST_CASE(gear_is_neutral_by_default)
    {
        BOOST_CHECK(car.GetCurrentGear() == 0);
    }

    BOOST_AUTO_TEST_CASE(speed_equals_to_zero_by_default)
    {
        BOOST_CHECK(car.GetCurrentSpeed() == 0);
    }

    BOOST_AUTO_TEST_CASE(direction_is_none_so_car_is_not_moving_by_default)
    {
        BOOST_CHECK(car.GetCurrentDirection() == "none");
    }

    BOOST_AUTO_TEST_SUITE(if_car_engine_is_turned_off)
        BOOST_AUTO_TEST_CASE(gear_is_neutral)
        {
            BOOST_CHECK(car.GetCurrentGear() == 0);
        }

        BOOST_AUTO_TEST_CASE(speed_equals_to_zero)
        {
            BOOST_CHECK(car.GetCurrentSpeed() == 0);
        }

        BOOST_AUTO_TEST_CASE(direction_is_none_so_car_is_not_moving)
        {
            BOOST_CHECK(car.GetCurrentDirection() == "none");
        }

        BOOST_AUTO_TEST_CASE(engine_can_be_turned_on)
        {
            BOOST_CHECK(car.TurnOnEngine());
        }

        BOOST_AUTO_TEST_CASE(engine_cannot_be_turned_off_again)
        {
            BOOST_CHECK(!car.TurnOffEngine());
        }

        BOOST_AUTO_TEST_CASE(gear_cannot_be_switched_on_any_possible_gear_besides_neutral)
        {
            for (int i = -1; i < 6; ++i)
            {
                if (i != 0)
                {
                    BOOST_CHECK(!car.SetGear(i));
                }
            }
        }

        BOOST_AUTO_TEST_CASE(gear_can_be_switched_on_neutral)
        {
            BOOST_CHECK(car.SetGear(0));
        }

        BOOST_AUTO_TEST_CASE(speed_cannot_be_changed)
        {
            BOOST_CHECK(!car.SetSpeed(10));
        }
    BOOST_AUTO_TEST_SUITE_END()

    struct when_turned_on_ : CarFixture
    {
        when_turned_on_()
        {
            car.TurnOnEngine();
        }
    };

    BOOST_FIXTURE_TEST_SUITE(if_car_engine_is_turned_on, when_turned_on_)
        BOOST_AUTO_TEST_CASE(engine_cannot_be_turned_on_again)
        {
            BOOST_CHECK(!car.TurnOnEngine());
        }

        BOOST_AUTO_TEST_SUITE(TurnOffEngine_function)
            BOOST_AUTO_TEST_CASE(engine_can_be_turned_off_if_gear_is_neutral_and_speed_is_zero_and_direction_is_none)
            {
                BOOST_CHECK(car.TurnOffEngine());
            }

            BOOST_AUTO_TEST_CASE(engine_cannot_be_turned_off_if_gear_not_neutral_or_speed_is_not_zero_or_direction_is_not_none)
            {
                car.SetGear(1);
                car.SetSpeed(10);
                BOOST_CHECK(!car.TurnOffEngine());
            }

            BOOST_AUTO_TEST_CASE(engine_cannot_be_turned_off_on_neutral_gear_if_speed_is_not_zero)
            {
                car.SetGear(1);
                car.SetSpeed(10);
                car.SetGear(0);
                BOOST_CHECK(!car.TurnOffEngine());
            }
        BOOST_AUTO_TEST_SUITE_END()

        BOOST_AUTO_TEST_SUITE(SetGear_function)
            BOOST_AUTO_TEST_CASE(cannot_set_gear_that_does_not_exist)
            {
                BOOST_CHECK(!car.SetGear(-2));
                BOOST_CHECK(!car.SetGear(6));
            }

            BOOST_AUTO_TEST_CASE(can_set_first_or_reverse_gear_when_speed_is_zero)
            {
                BOOST_CHECK(car.SetGear(-1));
                BOOST_CHECK(car.SetGear(1));
            }

            BOOST_AUTO_TEST_CASE(cannot_set_gear_if_the_speed_is_too_low_for_this_gear)
            {
                car.SetGear(1);
                car.SetSpeed(10);
                BOOST_CHECK(!car.SetGear(2));
            }

            BOOST_AUTO_TEST_CASE(can_set_gear_if_speed_allows_to_do_that)
            {
                car.SetGear(1);
                car.SetSpeed(20);
                BOOST_CHECK(car.SetGear(2));
            }
        BOOST_AUTO_TEST_SUITE_END()

        BOOST_AUTO_TEST_SUITE(SetSpeed_function)
            BOOST_AUTO_TEST_CASE(car_cannot_accelerate_when_gear_is_neutral)
            {
                car.SetGear(1);
                car.SetSpeed(10);
                car.SetGear(0);
                BOOST_CHECK(!car.SetSpeed(20));
            }

            BOOST_AUTO_TEST_CASE(car_can_slow_down_when_gear_is_neutral)
            {
                car.SetGear(1);
                car.SetSpeed(10);
                car.SetGear(0);
                BOOST_CHECK(car.SetSpeed(5));
            }

            BOOST_AUTO_TEST_CASE(cannot_set_any_speed_if_gear_does_not_allow_to_do_that)
            {
                car.SetGear(1);
                BOOST_CHECK(!car.SetSpeed(40));
            }
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
