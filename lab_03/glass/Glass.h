#pragma once

class CGlass
{
public:
    // создаём класс заданной вместимости
    CGlass(int capacity);

    ~CGlass();

    // возвращаем вместимость стакана
    int GetCapacity()const;

    // возвращаем количество воды в стакане
    int GetWaterAmount()const;

    // добавляем воду в стакан, возвращая фактически добавленное количество
    int AddWater(int amount);

    // выливаем воду из стакана, возвращая фактически вылитое количество
    int PourWater(int amount);
private:
    int     m_capacity; // вместимость стакана
    int     m_waterAmount; // количество воды
};
