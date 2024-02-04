#include <triangulate/Line2.h>

#include <gtest/gtest.h>

namespace triangulate
{
	class Line2Test : public ::testing::Test {};

	TEST_F(Line2Test, Contains)
	{
		Line2 line(Point2(0, 0), Point2(1, 1));

		EXPECT_TRUE(line.Contains(Point2(0.5f, 0.5f)));
	}

	TEST_F(Line2Test, NotContains)
	{
		Line2 line(Point2(0, 0), Point2(1, 1));

		EXPECT_FALSE(line.Contains(Point2(1.0f, 0.5f)));
	}

}
