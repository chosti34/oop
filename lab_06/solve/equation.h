#pragma once

struct EquationRoots
{
    int numRoots;
    double root[4];
};

EquationRoots Solve2(double a, double b, double c);
EquationRoots Solve3(double a, double b, double c, double d);
EquationRoots Solve4(double a, double b, double c, double d, double e);

void PrintRoots(std::ostream &strm, const EquationRoots &roots);
