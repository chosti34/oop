#pragma once

// ��������� � ������ ���-�� ����� � ������ ����� strm, ������ ��������� amount
std::vector<double> GetNumbers(std::istream &strm, int amount);

void PrintVector(const std::vector<double> &vect, std::ostream &strm);
