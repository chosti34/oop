#pragma once

class CRational final
{
public:
    // Конструирует рациональное число, равное (numerator / denominator)
    CRational(int numerator = 0, int denominator = 1);

    int GetNumerator() const;
    int GetDenominator() const;

    double ToDouble() const;

    std::pair<int, CRational> ToCompoundFraction() const;

    CRational const operator +() const;
    CRational const operator -() const;

    CRational& operator +=(const CRational &rightValue);
    CRational& operator -=(const CRational &rightValue);
    CRational& operator *=(const CRational &rightValue);
    CRational& operator /=(const CRational &rightValue);

private:
    int m_numerator;
    int m_denominator;

    void Normalize();
};

CRational const operator +(const CRational &leftValue, const CRational &rightValue);
CRational const operator -(const CRational &leftValue, const CRational &rightValue);
CRational const operator *(const CRational &leftValue, const CRational &rightValue);
CRational const operator /(const CRational &leftValue, const CRational &rightValue);

bool operator ==(const CRational &leftValue, const CRational &rightValue);
bool operator !=(const CRational &leftValue, const CRational &rightValue);
bool operator >(const CRational &leftValue, const CRational &rightValue);
bool operator >=(const CRational &leftValue, const CRational &rightValue);
bool operator <(const CRational &leftValue, const CRational &rightValue);
bool operator <=(const CRational &leftValue, const CRational &rightValue);

std::ostream& operator <<(std::ostream &strm, const CRational &number);
std::istream& operator >>(std::istream &strm, CRational &number);

// Возвращает наибольший общий делитель чисел a и b
unsigned GCD(unsigned a, unsigned b);
