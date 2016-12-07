#pragma once

// —читываем в вектор кол-во чисел с потока ввода strm, равное параметру amount
std::vector<double> GetNumbers(std::istream &strm, int amount);

void PrintVector(const std::vector<double> &vect, std::ostream &strm);
