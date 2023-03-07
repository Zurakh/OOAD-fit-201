#ifdef _MSC_VER
#include <algorithm>
#endif

#include "vectorOps.h"

std::vector<int> operator+(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
	const int dim = std::min(vec1.size(), vec2.size());

	std::vector<int> resVec;
	resVec.reserve(dim);

	for (int i = 0; i < dim; i++)
	{
		resVec.push_back(vec1[i] + vec2[i]);
	}

	return resVec;
}

std::vector<int> operator*(const std::vector<int>& vec, const int number)
{
	const int dim = vec.size();

	std::vector<int> resVec;
	resVec.reserve(dim);

	for (int i = 0; i < dim; i++)
	{
		resVec.push_back(vec[i] * number);
	}

	return resVec;
}

bool operator==(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
	const int dim = vec1.size();

	if (dim != vec2.size())
	{
		return false;
	}

	for (int i = 0; i < dim; i++)
	{
		if (vec1[i] != vec2[i])
		{
			return false;
		}
	}

	return true;
}

bool vectorEachValEq(const std::vector<int>& vec, int val)
{
	for (const int& el : vec)
	{
		if (el != val)
		{
			return false;
		}
	}

	return true;
}
