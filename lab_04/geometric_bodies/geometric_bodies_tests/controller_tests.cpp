#include "stdafx.h"
#include "../Body.h"
#include "../Sphere.h"
#include "../AppController.h"
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

// Зависимости controller-а вынесены в родительскую структуру,
// чтобы гарантировать их создание до конструирования самого controller-а
struct ControllerDependencies
{
    vector<shared_ptr<CBody>> bodies;
    stringstream input;
    stringstream output;
};

struct ControllerFixture : ControllerDependencies
{
    CAppController controller;

    ControllerFixture() : controller(bodies, input, output)
    {
    }

    // Вспомогательная функция для проверки работы команды command
    // Она принимает команду command и ожидаемый результат expectedOutput
    void VerifyCommandHandling(const string &command, const string &expectedOutput)
    {
        output = stringstream();
        input = stringstream();
        BOOST_CHECK(input << command);
        controller.HandleCommand();
        BOOST_CHECK(input.eof());
        BOOST_CHECK_EQUAL(output.str(), expectedOutput);
    }
};

BOOST_FIXTURE_TEST_SUITE(AppController, ControllerFixture)

    BOOST_AUTO_TEST_SUITE(when_handling_commands_by_user)
        BOOST_AUTO_TEST_CASE(can_create_some_geometric_body)
        {
            VerifyCommandHandling("CreateCone 1000 12 10", "Cone created\n");
            BOOST_CHECK(bodies.size() == 1);
            BOOST_CHECK(bodies.at(0)->GetDensity() == 1000);
            BOOST_CHECK(bodies.at(0)->GetVolume() == M_PI * 12 * 12 * 10 / 3);
        }

        BOOST_AUTO_TEST_CASE(can_print_alert_messages)
        {
            VerifyCommandHandling(
                "CreateCylinder 1 1 1 1", 
                "Can't create this cylinder\nUsage: CreateCylinder <density> <base radius> <height>\n"
            );
            BOOST_CHECK(bodies.size() == 0);
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(GetBodyWeightInWater_method)
        BOOST_AUTO_TEST_CASE(can_return_negative_value)
        {
            CSphere sphere(900, 10);
            BOOST_CHECK(controller.GetBodyWeightInWater(sphere) < 0);
        }

        BOOST_AUTO_TEST_CASE(can_return_positive_value)
        {
            CSphere sphere(1100, 10);
            BOOST_CHECK(controller.GetBodyWeightInWater(sphere) > 0);
        }

        BOOST_AUTO_TEST_CASE(can_return_zero)
        {
            CSphere sphere(1000, 10);
            BOOST_CHECK(controller.GetBodyWeightInWater(sphere) == 0);
        }
    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
