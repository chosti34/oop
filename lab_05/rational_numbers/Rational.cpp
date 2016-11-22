#include "stdafx.h"
#include "Rational.h"

CRational::CRational()
{
    m_numerator = 0;
    m_denominator = 1;
}

CRational::CRational(int numerator, int denominator)
    : m_numerator(numerator)
    , m_denominator(denominator)
{
    if (denominator == 0)
    {
        throw std::invalid_argument("denominator can't be equal to zero");
    }

    if (denominator < 0)
    {
        m_numerator = -m_numerator;
        m_denominator = -m_denominator;
    }

    Normalize();
}

CRational::~CRational()
{
}

int CRational::GetNumerator() const
{
    return m_numerator;
}

int CRational::GetDenominator() const
{
    return m_denominator;
}

double CRational::ToDouble() const
{
    if (m_denominator == 0)
    {
        throw std::logic_error("denominator can't be equal to zero");
    }
    return static_cast<double>(m_numerator) / m_denominator;
}

void CRational::Normalize()
{
    const int gcd = GCD(abs(m_numerator), m_denominator);
    m_numerator /= gcd;
    m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
    while (b != 0)
    {
        std::swap(a, b);
        b = b % a;
    }
    return (a != 0) ? a : 1;
}
