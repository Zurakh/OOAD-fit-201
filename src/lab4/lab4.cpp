#include "lab4.h"

std::vector<double> solve(double a, double b, double c)
{
	if (abs(a) < std::numeric_limits<double>::epsilon())
	{
		throw(NonSquareEquation());
	}

	const double D = b * b - 4 * a * c;

	if (D < 0)
	{
		throw(NotRealRoots());
	}

	std::vector<double> answer = { 0, 0 };
	const double sqrtD = sqrt(D);

	if (sqrtD < std::numeric_limits<double>::epsilon())
	{
		answer[0] = answer[1] = (-1 * b) / (2 * a);
	}
	else
	{
		answer[0] = (-1 * b - sqrtD) / (2 * a);
		answer[1] = (-1 * b + sqrtD) / (2 * a);
	}

	return answer;
}
