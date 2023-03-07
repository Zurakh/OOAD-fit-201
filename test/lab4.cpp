#include <gtest/gtest.h>
#include <vector>
#include <lab4/lab4.h>

using namespace std;

TEST(SQROOTS, OneRoot)
{
	vector<double> p_answer = solve(1, -2, 1);
	EXPECT_EQ(1, p_answer[0]);
	EXPECT_EQ(1, p_answer[1]);
}

TEST(SQROOTS, TwoRoots)
{
	vector<double> p_answer = solve(1, 0, -1);
	vector<double> correct = { -1, 1 };
	if (p_answer[0] == correct[0])
	{
		EXPECT_EQ(correct[0], p_answer[0]);
		EXPECT_EQ(correct[1], p_answer[1]);
	}
	else
	{
		EXPECT_EQ(correct[1], p_answer[0]);
		EXPECT_EQ(correct[0], p_answer[1]);
	}
}

TEST(SQROOTS, NotRealRoots)
{
	EXPECT_THROW(solve(1, 0, 1), NotRealRoots);
}

TEST(SQROOTS, zeroA)
{
	EXPECT_THROW(solve(0, 2, -1), NonSquareEquation);
}
