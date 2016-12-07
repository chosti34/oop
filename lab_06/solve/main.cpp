#include "stdafx.h"
#include "vector_processor.h"
#include "equation.h"

int Fn(int a)
{
    return a * a;
}

int main()
{
    while (!std::cin.eof())
    {
        std::cout << "Enter 3 coefficients of quadratic equation:\n";
        std::vector<double> coefficients = GetNumbers(std::cin, 3);

        if (coefficients.size() != 3)
        {
            break;
        }

        EquationRoots roots;

        try
        {
            roots = Solve2(coefficients[0], coefficients[1], coefficients[2]);
            PrintRoots(std::cout, roots);
        }
        catch (const std::exception &error)
        {
            std::cerr << error.what() << std::endl;
        }
    }

    return 0;
}
