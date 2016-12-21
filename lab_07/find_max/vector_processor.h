#pragma once

template <typename T, typename Less = std::less<T>>
bool FindMax(const std::vector<T> &vect, T &maxValue, const Less &less = Less())
{
    if (vect.empty())
    {
        return false;
    }

    maxValue = vect.front();

    for (const auto &element : vect)
    {
        if (less(maxValue, element))
        {
            maxValue = element;
        }
    }

    return true;
}
