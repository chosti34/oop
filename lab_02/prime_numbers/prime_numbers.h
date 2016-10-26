#pragma once

std::set<int> GeneratePrimeNumbersSet(const int upperBound);
std::vector<bool> GetPrimeNumbersVector(const int upperBound);

void PrintSet(std::ostream &output, std::set<int> &container);
