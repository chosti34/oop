#include "stdafx.h"
#include "Glass.h"
#include <assert.h>

void TestGlassCreation()
{
    CGlass validGlass(10);

    assert(validGlass.GetCapacity() == 10);
    assert(validGlass.GetWaterAmount() == 0);

    CGlass invalidGlass(-10);

    assert(invalidGlass.GetCapacity() == 0);
    assert(invalidGlass.GetWaterAmount() == 0);

    std::cout << "Glass creation test is ok!\n";
}

void TestAddingWater()
{
    CGlass someGlass(100);

    // добавляем в стакан по миллилитру, убеждаясь в невозможности переполнения
    for (int i = 1; i < 200; ++i)
    {
        const int addedWater = someGlass.AddWater(1);
        if (i <= someGlass.GetCapacity())
        {
            assert(addedWater == 1);
            assert(someGlass.GetWaterAmount() == i);
        }
        else
        {
            assert(addedWater == 0);
            assert(someGlass.GetWaterAmount() == someGlass.GetCapacity());
        }
    }

    CGlass anotherGlass(100);
    anotherGlass.AddWater(10);
    assert(anotherGlass.GetWaterAmount() == 10);

    const int addedWater = anotherGlass.AddWater(-10);
    assert(addedWater == 0);
    assert(anotherGlass.GetWaterAmount() == 10);

    std::cout << "Adding water test is ok!\n";
}

void TestPouringWater()
{

}

int main()
{
    TestGlassCreation();
    TestAddingWater();

    return 0;
}
