#include "stdafx.h"
#include "AppController.h"

int main()
{
    std::vector<std::shared_ptr<CBody>> bodies;
    CAppController controller(bodies, std::cin, std::cout);

    while ((!std::cin.eof()) && (!std::cin.fail()))
    {
        std::cout << "> ";
        controller.HandleCommand();
    }

    if (!bodies.empty())
    {
        controller.PrintInfoAboutAllBodies(bodies, std::cout);
        controller.PrintInfoAboutBodyWithMaxMass(bodies, std::cout);
    }
    else
    {
        std::cout << "You didn't enter any body" << std::endl;
    }

    return 0;
}
