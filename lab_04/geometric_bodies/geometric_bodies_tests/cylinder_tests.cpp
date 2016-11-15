#include "stdafx.h"

#define _USE_MATH_DEFINES
#include "../Cylinder.h"
#include <math.h>

struct Cylinder_
{
    const double expectedRadius = 10.1;
    const double expectedHeight = 12.3;
    const double expectedDensity = 100.2;
    const double expectedVolume = M_PI * expectedRadius * expectedRadius * expectedHeight;
    const CCylinder cylinder;
    Cylinder_()
        : cylinder(expectedDensity, expectedRadius, expectedHeight)
    {}
};

// �������
BOOST_FIXTURE_TEST_SUITE(Cylinder, Cylinder_)

    // �������� �������� �����
    BOOST_AUTO_TEST_CASE(is_a_body)
    {
        BOOST_CHECK(static_cast<const CBody*>(&cylinder));
    }

    // ����� ������ ���������
    BOOST_AUTO_TEST_CASE(has_a_base_radius)
    {
        BOOST_CHECK_EQUAL(cylinder.GetBaseRadius(), expectedRadius);
    }

    // ����� ������
    BOOST_AUTO_TEST_CASE(has_a_height)
    {
        BOOST_CHECK_EQUAL(cylinder.GetHeight(), expectedHeight);
    }

    // ����� ���������
    BOOST_AUTO_TEST_CASE(has_a_density)
    {
        BOOST_CHECK_EQUAL(static_cast<const CBody &>(cylinder).GetDensity(), expectedDensity);
    }

    // ����� �����
    BOOST_AUTO_TEST_CASE(has_a_volume)
    {
        BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cylinder).GetVolume(), expectedVolume, 1e-7);
    }

    // ����� �����
    BOOST_AUTO_TEST_CASE(has_a_mass)
    {
        BOOST_CHECK_CLOSE_FRACTION(static_cast<const CBody &>(cylinder).GetMass(), expectedVolume * expectedDensity, 1e-7);
    }

    // ����� ��������� �������������
    BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
    {
        const auto expectedString = R"(Cylinder:
	density = 100.2
	volume = 3941.828559
	mass = 394971.2216
	base radius = 10.1
	height = 12.3
)";
        BOOST_CHECK_EQUAL(static_cast<const CBody &>(cylinder).ToString(), expectedString);
    }
BOOST_AUTO_TEST_SUITE_END()
