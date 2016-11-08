#include "stdafx.h"
#include "../Car.h"
#include "../CarController.h"
#include <sstream>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

// ����������� CarController-� �������� � ������������ ���������,
// ����� ������������� �� �������� �� ��������������� ������ CarController-�
struct CarControllerDependencies
{
    CCar car;
    stringstream input;
    stringstream output;
};

struct CarControllerFixture : CarControllerDependencies
{
    CCarController controller;

    CarControllerFixture()
        : controller(car, input, output) {}

    // ��������������� ������� ��� �������� ������ ������� command
    // ��� ��������� ������� command � ��������� ��������� expectedOutput
    void VerifyCommandHandling(const std::string &command, const std::string &expectedOutput)
    {
        // �������������� ������� ���������� ��������� ������
        input = stringstream();
        output = stringstream();
        BOOST_CHECK(input << command);
        BOOST_CHECK(controller.HandleCommand());
        BOOST_CHECK(input.eof());
        BOOST_CHECK_EQUAL(output.str(), expectedOutput);
    }
};

BOOST_FIXTURE_TEST_SUITE(Car_Controller, CarControllerFixture)
    BOOST_AUTO_TEST_CASE(can_handle_EngineOn_command_if_not_turned_on_yet)
    {
        VerifyCommandHandling("EngineOn", "Car engine is turned on\n");
    }

    BOOST_AUTO_TEST_CASE(can_turn_off_car_engine_which_is_on)
    {
        car.TurnOnEngine();
        VerifyCommandHandling("EngineOff", "Car engine is turned off\n");
    }

    BOOST_AUTO_TEST_CASE(can_print_car_info)
    {
        // ��������� � ������ � ����������� ����������
        car.TurnOffEngine();
        VerifyCommandHandling("Info", "Car engine is off\n");

        // ��������� � ������ � ��������� ����������
        car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(20);
        VerifyCommandHandling(
            "Info", "Car engine is on\nGear: 1\nSpeed: 20\nDirection: forward\n"
        );
    }

    BOOST_AUTO_TEST_CASE(can_print_alert_messages)
    {
        car.TurnOffEngine();
        VerifyCommandHandling(
            "SetSpeed 30", "Speed is out of range for current gear or car engine is turned off\n"
        );
    }
BOOST_AUTO_TEST_SUITE_END()
