#pragma once

template <typename T, typename Less = std::less<T>>
bool FindMax(const std::vector<T> &vect, T &maxValue, const Less &less = Less())
{
    if (vect.empty())
    {
        return false;
    }

    // храним адрес текущего максимального элемента,
    // таким образом избегаем копирование
    const T *max = &vect.front();

    for (const auto &element : vect)
    {
        if (less(*max, element))
        {
            max = &element;
        }
    }

    maxValue = *max;

    return true;
}
