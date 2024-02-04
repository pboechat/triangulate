#include <triangulate/Point2Set.h>

#include <gtest/gtest.h>

#include <vector>

namespace triangulate
{
	class Point2SetTest : public ::testing::Test {};

	TEST_F(Point2SetTest, FindCentroidOfAScaleneTriangle)
	{
		std::vector<Point2> points;

		points.push_back(Point2(-5, 3));
		points.push_back(Point2(5, 0));
		points.push_back(Point2(3, 0));

		Point2 centroid = Point2Set::FindCentroid(points);

		EXPECT_FLOAT_EQ(1, centroid.GetX());
		EXPECT_FLOAT_EQ(1, centroid.GetY());
	}

}
