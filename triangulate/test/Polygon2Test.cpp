#include <triangulate/Point2.h>
#include <triangulate/Polygon2.h>

#include <gtest/gtest.h>

#include <memory>
#include <vector>

namespace triangulate
{
	class Polygon2Test : public ::testing::Test
	{
	protected:
		std::unique_ptr<Polygon2> mpTriangle;
		std::unique_ptr<Polygon2> mpHexagon;
		std::unique_ptr<Polygon2> mpEnneagon;

		virtual void SetUp()
		{
			std::vector<Point2> edgePoints;

			edgePoints.push_back(Point2(0, 1.0f));
			edgePoints.push_back(Point2(-0.866f, -0.5f));
			edgePoints.push_back(Point2(0.866f, -0.5f));

			mpTriangle = std::make_unique<Polygon2>(edgePoints);

			// ---

			edgePoints.clear();
			edgePoints.push_back(Point2(0, 1.0f));
			edgePoints.push_back(Point2(-0.866f, 0.5f));
			edgePoints.push_back(Point2(-0.866f, -0.5f));
			edgePoints.push_back(Point2(0, -1.0f));
			edgePoints.push_back(Point2(0.866f, -0.5f));
			edgePoints.push_back(Point2(0.866f, 0.5f));

			mpHexagon = std::make_unique<Polygon2>(edgePoints);

			// ---

			edgePoints.clear();
			edgePoints.push_back(Point2(0, 1.0f));
			edgePoints.push_back(Point2(-0.643f, 0.766f));
			edgePoints.push_back(Point2(-0.985f, 0.174f));
			edgePoints.push_back(Point2(-0.866f, -0.5f));
			edgePoints.push_back(Point2(-0.342f, -0.94f));
			edgePoints.push_back(Point2(0.342f, -0.94f));
			edgePoints.push_back(Point2(0.866f, -0.5f));
			edgePoints.push_back(Point2(0.985f, 0.174f));
			edgePoints.push_back(Point2(0.643f, 0.766f));

			mpEnneagon = std::make_unique<Polygon2>(edgePoints);
		}

		virtual void TearDown()
		{
			mpTriangle = nullptr;
			mpHexagon = nullptr;
			mpEnneagon = nullptr;
		}

	};

	TEST_F(Polygon2Test, LocatePointInsideAnEquilateralTriangle)
	{
		EXPECT_EQ(Polygon2::PL_INSIDE, mpTriangle->LocatePoint(Point2::ZERO));
	}

	TEST_F(Polygon2Test, LocatePointOutsideAnEquilateralTriangle)
	{
		EXPECT_EQ(Polygon2::PL_OUTSIDE, mpTriangle->LocatePoint(Point2(1.0f, 1.0f)));
	}

	TEST_F(Polygon2Test, LocatePointOnTheEdgeOfAnEquilateralTriangleWhenItBelongsToTheEdgePointsList)
	{
		EXPECT_EQ(Polygon2::PL_ON_THE_EDGE, mpTriangle->LocatePoint(Point2(0, 1)));
	}

	TEST_F(Polygon2Test, LocatePointOnTheEdgeOfAnEquilateralTriangleWhenItDoesntBelongToTheEdgePointsList)
	{
		EXPECT_EQ(Polygon2::PL_ON_THE_EDGE, mpTriangle->LocatePoint(Point2(0, -0.5f)));
	}

	TEST_F(Polygon2Test, LocatePointInsideARegularHexagon)
	{
		EXPECT_EQ(Polygon2::PL_INSIDE, mpHexagon->LocatePoint(Point2::ZERO));
	}

	TEST_F(Polygon2Test, LocatePointOutsideARegularHexagon)
	{
		EXPECT_EQ(Polygon2::PL_OUTSIDE, mpHexagon->LocatePoint(Point2(1.0f, 1.0f)));
	}

	TEST_F(Polygon2Test, LocatePointOnTheEdgeOfARegularHexagonWhenItBelongsToTheEdgePointsList)
	{
		EXPECT_EQ(Polygon2::PL_ON_THE_EDGE, mpHexagon->LocatePoint(Point2(0, 1)));
	}

	TEST_F(Polygon2Test, LocatePointOnTheEdgeOfARegularHexagonWhenItDoesntBelongToTheEdgePointsList)
	{
		EXPECT_EQ(Polygon2::PL_ON_THE_EDGE, mpHexagon->LocatePoint(Point2(-0.866f, 0)));
	}

	TEST_F(Polygon2Test, LocatePointInsideARegularEnneagon)
	{
		EXPECT_EQ(Polygon2::PL_INSIDE, mpEnneagon->LocatePoint(Point2::ZERO));
	}

	TEST_F(Polygon2Test, LocatePointOutsideARegularEnneagon)
	{
		EXPECT_EQ(Polygon2::PL_OUTSIDE, mpEnneagon->LocatePoint(Point2(1.0f, 1.0f)));
	}

	TEST_F(Polygon2Test, LocatePointOnTheEdgeOfARegularEnneagonWhenItBelongsToTheEdgePointsList)
	{
		EXPECT_EQ(Polygon2::PL_ON_THE_EDGE, mpEnneagon->LocatePoint(Point2(0, 1)));
	}

	TEST_F(Polygon2Test, LocatePointOnTheEdgeOfARegularEnneagonWhenItDoesntBelongToTheEdgePointsList)
	{
		EXPECT_EQ(Polygon2::PL_ON_THE_EDGE, mpEnneagon->LocatePoint(Point2(0, -0.94f)));
	}

	TEST_F(Polygon2Test, LocatePointInsideAnEquilateralTriangleUsingRotationIndex)
	{
		EXPECT_EQ(Polygon2::PL_INSIDE, mpTriangle->LocatePointUsingRotationIndex(Point2::ZERO));
	}

	TEST_F(Polygon2Test, LocatePointOutsideAnEquilateralTriangleUsingRotationIndex)
	{
		EXPECT_EQ(Polygon2::PL_OUTSIDE, mpTriangle->LocatePointUsingRotationIndex(Point2(1.0f, 1.0f)));
	}

	TEST_F(Polygon2Test, LocatePointOnTheEdgeOfAnEquilateralTriangleWhenItBelongsToTheEdgePointsListAndUsingRotationIndex)
	{
		EXPECT_EQ(Polygon2::PL_ON_THE_EDGE, mpTriangle->LocatePointUsingRotationIndex(Point2(0, 1)));
	}

	TEST_F(Polygon2Test, LocatePointOnTheEdgeOfAnEquilateralTriangleWhenItDoesntBelongToTheEdgePointsListAndUsingRotationIndex)
	{
		EXPECT_EQ(Polygon2::PL_ON_THE_EDGE, mpTriangle->LocatePointUsingRotationIndex(Point2(0, -0.5f)));
	}

	TEST_F(Polygon2Test, LocatePointIndexInsideARegularHexagonUsingRotationIndex)
	{
		EXPECT_EQ(Polygon2::PL_INSIDE, mpHexagon->LocatePointUsingRotationIndex(Point2::ZERO));
	}

	TEST_F(Polygon2Test, LocatePointOutsideARegularHexagonUsingRotationIndex)
	{
		EXPECT_EQ(Polygon2::PL_OUTSIDE, mpHexagon->LocatePointUsingRotationIndex(Point2(1.0f, 1.0f)));
	}

	TEST_F(Polygon2Test, LocatePointOnTheEdgeOfARegularHexagonWhenItBelongsToTheEdgePointsListAndUsingRotationIndex)
	{
		EXPECT_EQ(Polygon2::PL_ON_THE_EDGE, mpHexagon->LocatePointUsingRotationIndex(Point2(0, 1)));
	}

	TEST_F(Polygon2Test, LocatePointOnTheEdgeOfARegularHexagonWhenItDoesntBelongToTheEdgePointsListAndUsingRotationIndex)
	{
		EXPECT_EQ(Polygon2::PL_ON_THE_EDGE, mpHexagon->LocatePointUsingRotationIndex(Point2(-0.866f, 0)));
	}

	TEST_F(Polygon2Test, LocatePointIndexInsideARegularEnneagonUsingRotationIndex)
	{
		EXPECT_EQ(Polygon2::PL_INSIDE, mpEnneagon->LocatePointUsingRotationIndex(Point2::ZERO));
	}

	TEST_F(Polygon2Test, LocatePointOutsideARegularEnneagonUsingRotationIndex)
	{
		EXPECT_EQ(Polygon2::PL_OUTSIDE, mpEnneagon->LocatePointUsingRotationIndex(Point2(1.0f, 1.0f)));
	}

	TEST_F(Polygon2Test, LocatePointOnTheEdgeOfARegularEnneagonWhenItBelongsToTheEdgePointsListAndUsingRotationIndex)
	{
		EXPECT_EQ(Polygon2::PL_ON_THE_EDGE, mpEnneagon->LocatePointUsingRotationIndex(Point2(0, 1)));
	}

	TEST_F(Polygon2Test, LocatePointOnTheEdgeOfARegularEnneagonWhenItDoesntBelongToTheEdgePointsListAndUsingRotationIndex)
	{
		EXPECT_EQ(Polygon2::PL_ON_THE_EDGE, mpEnneagon->LocatePointUsingRotationIndex(Point2(0, -0.94f)));
	}

}
