#include "stdafx.h"
#include "equation.h"

int sign(double value)
{
    return (value < 0) ? -1 : (value == 0) ? 0 : 1;
}

double MySqrt(double x)
{
    if (x < 0)
    {
        throw std::invalid_argument("Can't calculate square root of negative value...");
    }

    return sqrt(x);
}

EquationRoots Solve2(double a, double b, double c)
{
    if (a == 0)
    {
        throw std::invalid_argument("\"a\" coefficient can't be zero...");
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        throw std::domain_error("Equation does not have any real roots...");
    }

    EquationRoots roots;

    if (discriminant == 0)
    {
        roots.numRoots = 1;
        roots.root[0] = -b / (2 * a);
    }
    else if (discriminant > 0)
    {
        roots.numRoots = 2;
        roots.root[0] = (-b + sqrt(discriminant)) / (2 * a);
        roots.root[1] = (-b - sqrt(discriminant)) / (2 * a);
    }

    return roots;
}

EquationRoots Solve3(double a, double b, double c)
{
    EquationRoots roots = Solve2(1, 1, 1);

    double q = (a * a - 3.0 * b) / 9.0;
    double r = (2.0 * pow(a, 3) - 9.0 * a * b + 27.0 * c) / 54.0;
    double s = pow(q, 3.0) - r * r;

    if (s > 0)
    {
        double t = acos(r / pow(q, 3.0 / 2.0)) / 3.0;
        roots.numRoots = 3;
        roots.root[0] = -2.0 * MySqrt(q) * cos(t) - (a / 3.0);
        roots.root[1] = -2.0 * MySqrt(q) * cos(t + (2.0 * M_PI) / 3.0) - (a / 3.0);
        roots.root[2] = -2.0 * MySqrt(q) * cos(t - (2.0 * M_PI) / 3.0) - (a / 3.0);
    }
    else if (s == 0)
    {
        roots.numRoots = 2;
        roots.root[0] = -2.0 * pow(r, 1.0 / 3.0) - (a / 3.0);
        roots.root[1] = pow(r, 1.0 / 3.0) - (a / 3.0);
    }
    else
    {
        double t = acosh(abs(r) / pow(abs(q), 3 / 2)) / 3.0;
        roots.numRoots = 1;
        roots.root[0] = -2.0 * sign(r) * MySqrt(abs(q)) * cosh(t) - a / 3.0;
    }

    return roots;
}

void PrintRoots(std::ostream &strm, const EquationRoots &roots)
{
    switch (roots.numRoots)
    {
    case 0:
        strm << "Equation does not have any real roots..." << std::endl;
        break;
    case 1:
        strm << std::fixed << std::setprecision(3) << "Equation have only one root:\nx = "
             << roots.root[0] << '.' << std::endl;
        break;
    case 2:
        strm << std::fixed << std::setprecision(3) << "Equation have two roots:\nx1 = "
             << roots.root[0] << ";\nx2 = " << roots.root[1] << '.' << std::endl;
        break;
    default:
        strm << "Some error occurred, can't print roots" << std::endl;
        break;
    }
}
