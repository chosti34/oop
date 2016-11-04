#include "stdafx.h"
#include "Car.h"
#include "CarController.h"

int main()
{
    CCar car;
    CCarController controller(car, std::cin, std::cout);

    while ((!std::cin.eof()) && (!std::cin.fail()))
    {
        std::cout << "> ";
        if (!controller.HandleCommand())
        {
            std::cout << "Unknown command!\n";
        }
    }

    return 0;
}
