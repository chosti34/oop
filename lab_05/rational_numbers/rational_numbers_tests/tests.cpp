#include "stdafx.h"
#include "../Rational.h"

BOOST_AUTO_TEST_CASE(GCD_function_tests)
{
    BOOST_CHECK_EQUAL(GCD(4, 5), 1u);
    BOOST_CHECK_EQUAL(GCD(5, 4), 1u);
    BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
    BOOST_CHECK_EQUAL(GCD(0, 3), 3u);
    BOOST_CHECK_EQUAL(GCD(3, 0), 3u);
    BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
    BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
}

/*
  ������������ �����:
    ����� ���� �� ��������� (0 / 1)
    ����� ���� ������� �� ������ � ������� (n / 1)
    ����� ���� ������ � ��������� ��������� � �����������
    �������� � ��������������� ����
*/

// ��������� �� ��������� ��������� � ����������� � ��������� ���������
void VerifyRational(const CRational &rationalNumber, int expectedNumerator, int expectedDenominator)
{
    BOOST_CHECK_EQUAL(rationalNumber.GetNumerator(), expectedNumerator);
    BOOST_CHECK_EQUAL(rationalNumber.GetDenominator(), expectedDenominator);
}
