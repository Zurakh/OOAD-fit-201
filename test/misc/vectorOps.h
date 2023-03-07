#pragma once

#include <vector>

std::vector<int> operator+(const std::vector<int>& vec1, const std::vector<int>& vec2);

std::vector<int> operator*(const std::vector<int>& vec, const int number);

bool operator==(const std::vector<int>& vec1, const std::vector<int>& vec2);

bool vectorEachValEq(const std::vector<int>& vec, int val);
