#pragma once

template <typename T, typename Less = std::less<T>>
bool FindMax(const std::vector<T> &vect, T &maxValue, const Less &less = Less())
{
    if (vect.empty())
    {
        return false;
    }

    maxValue = *std::max_element(vect.begin(), vect.end(), less);

    return true;
}
