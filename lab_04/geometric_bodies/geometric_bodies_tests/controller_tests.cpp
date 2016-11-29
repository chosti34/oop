#include "stdafx.h"
#include "../Body.h"
#include "../Sphere.h"
#include "../AppController.h"
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

// ����������� controller-� �������� � ������������ ���������,
// ����� ������������� �� �������� �� ��������������� ������ controller-�
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

    // ��������������� ������� ��� �������� ������ ������� command
    // ��� ��������� ������� command � ��������� ��������� expectedOutput
    void VerifyCommandHandling(const string &command, const string &expectedOutput)
    {
        output = stringstream();
        input = stringstream();
        BOOST_CHECK(input << command);
        controller.HandleCommand();
        BOOST_CHECK(input.eof());
        BOOST_CHECK_EQUAL(output.str(), expectedOutput);
    }

    void ExpectOperationSuccess(const std::vector<std::shared_ptr<CBody>> &bodies, const size_t expectedVectorSize,
                              const double expectedDensity, const double expectedMass, const double expectedVolume)
    {
        BOOST_CHECK_EQUAL(bodies.size(), expectedVectorSize);
        BOOST_CHECK_EQUAL(bodies.back()->GetDensity(), expectedDensity);
        BOOST_CHECK_EQUAL(bodies.back()->GetMass(), expectedMass);
        BOOST_CHECK_EQUAL(bodies.back()->GetVolume(), expectedVolume);
    }
};

BOOST_FIXTURE_TEST_SUITE(AppController, ControllerFixture)

    BOOST_AUTO_TEST_SUITE(when_handling_commands_by_user)
        BOOST_AUTO_TEST_CASE(can_create_any_available_geometric_body)
        {
            VerifyCommandHandling("CreateCone 1000 12 10", "Cone created!\n");
            ExpectOperationSuccess(bodies, 1, 1000, M_PI * 12 * 12 * 10 / 3 * 1000, M_PI * 12 * 12 * 10 / 3);
            VerifyCommandHandling("CreateSphere 100 1", "Sphere created!\n");
            ExpectOperationSuccess(bodies, 2, 100, (pow(1, 3) * M_PI) * 4 / 3 * 100, (pow(1, 3) * M_PI) * 4 / 3);
            VerifyCommandHandling("CreateCylinder 10 1 2", "Cylinder created!\n");
            ExpectOperationSuccess(bodies, 3, 10, M_PI * pow(1, 2) * 2 * 10, M_PI * pow(1, 2) * 2);
            VerifyCommandHandling("CreateParallelepiped 10 10 10 10", "Parallelepiped created!\n");
            ExpectOperationSuccess(bodies, 4, 10, 10 * 10 * 10 * 10, 10 * 10 * 10);
        }

        BOOST_AUTO_TEST_CASE(cannot_create_bodies_with_negative_parametrs)
        {
            VerifyCommandHandling("CreateSphere 1 -1", "Density and radius can't be negative...\n");
            VerifyCommandHandling("CreateParallelepiped 1 2 -1 1", "Density, width, height and depth can't be negative...\n");
            VerifyCommandHandling("CreateCone -2 1 3", "Density, base radius and height can't be negative...\n");
            VerifyCommandHandling("CreateCylinder 1 2 -3", "Density, base radius and height can't be negative...\n");
            BOOST_CHECK_EQUAL(bodies.size(), 0);
        }

        BOOST_AUTO_TEST_CASE(can_print_alert_messages)
        {
            VerifyCommandHandling(
                "CreateCylinder 1 1 1 1", 
                "Can't create this cylinder\nUsage: CreateCylinder <density> <base radius> <height>\n"
            );
            VerifyCommandHandling(
                "CreateParallelepiped 1 1 2 1 1",
                "Can't create this parallelepiped...\nUsage: CreateParallelepiped <density> <width> <height> <depth>\n"
            );
            VerifyCommandHandling(
                "CreateSphere 12 2 1 1",
                "Can't create this sphere...\nUsage: CreateSphere <density> <radius>\n"
            );
            VerifyCommandHandling(
                "CreateCone 2",
                "Can't create this cone\nUsage: CreateCone <density> <base radius> <height>\n"
            );
            VerifyCommandHandling("CreateSomething", "Unknown command!\n");
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
