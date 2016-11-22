#pragma once

class CRational final
{
public:
    // Конструирует рациональное число, равное нулю (0 / 1)
    CRational();

    // Конструирует рациональное число, равное (numerator / denominator)
    CRational(int numerator, int denominator = 1);

    ~CRational();

    int GetNumerator() const;
    int GetDenominator() const;

    double ToDouble() const;

    // Реализовать унарный плюс и унарный минус
    const CRational operator+() const;
    const CRational operator-() const;

private:
    int m_numerator;
    int m_denominator;

    void Normalize();

};

// Возвращает наибольший общий делитель чисел a и b
unsigned GCD(unsigned a, unsigned b);
