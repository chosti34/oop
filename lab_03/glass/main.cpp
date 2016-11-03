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
    CGlass glass(100);

    glass.AddWater(glass.GetCapacity());
    assert(glass.GetWaterAmount() == glass.GetCapacity());

    for (int i = glass.GetWaterAmount() - 1; i >= 100; --i)
    {
        const int pouredWater = glass.PourWater(1);

        std::cout << glass.GetWaterAmount() << ": " << i << '\n';

        if (i >= 0)
        {
            assert(pouredWater == 1);
            assert(glass.GetWaterAmount() == i);
        }
        else
        {
            assert(pouredWater == 0);
            assert(glass.GetWaterAmount() == 0);
        }
    }

    CGlass anotherGlass(100);
    anotherGlass.AddWater(10);
    assert(anotherGlass.GetWaterAmount() == 10);

    const int pouredWater = anotherGlass.PourWater(-10);
    assert(pouredWater == 0);
    assert(anotherGlass.GetWaterAmount() == 10);

    std::cout << "Pouring water test is ok!\n";
}

void TestIntegerOverflow()
{
    CGlass glass(100);
    glass.AddWater(10);
    assert(glass.GetWaterAmount() == 10);

    const int addedWater = glass.AddWater(INT_MAX);
    assert(addedWater == glass.GetCapacity() - 10);
    assert(glass.GetWaterAmount() == glass.GetCapacity());

    CGlass anotherGlass(100);

    const int pouredWater = anotherGlass.PourWater(INT_MAX);
    assert(pouredWater == 0);
    assert(anotherGlass.GetWaterAmount() == 0);

    std::cout << "Integer overflow test is ok!\n";
}

int main()
{
    TestGlassCreation();
    TestAddingWater();
    TestPouringWater();
    TestIntegerOverflow();

    return 0;
}
