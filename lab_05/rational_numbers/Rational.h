#pragma once

class CRational final
{
public:
    // ������������ ������������ �����, ������ ���� (0 / 1)
    CRational();

    // ������������ ������������ �����, ������ (numerator / denominator)
    CRational(int numerator, int denominator = 1);

    ~CRational();

    int GetNumerator() const;
    int GetDenominator() const;

    double ToDouble() const;

    // ����������� ������� ���� � ������� �����
    const CRational operator+() const;
    const CRational operator-() const;

private:
    int m_numerator;
    int m_denominator;

    void Normalize();

};

// ���������� ���������� ����� �������� ����� a � b
unsigned GCD(unsigned a, unsigned b);
