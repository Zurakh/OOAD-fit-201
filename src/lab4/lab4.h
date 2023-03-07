#pragma once
#include <math.h>
#include <exception>
#include <vector>

class NotRealRoots : public std::exception
{
};

class NonSquareEquation : public std::exception
{
};

std::vector<double> solve(double a, double b, double c);
