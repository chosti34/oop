#pragma once

struct EquationRoots
{
    int numRoots;
    double root[2];
};

EquationRoots Solve2(double a, double b, double c);

// Принимает коэффиценты приведённого кубического уравнения
// x^2 + ax^2 + bx + c = 0
EquationRoots Solve3(double a, double b, double c);

double MySqrt(double x);

void PrintRoots(std::ostream &strm, const EquationRoots &roots);
