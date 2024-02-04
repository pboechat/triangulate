#include <triangulate/Triangulation2.h>

#include <gtest/gtest.h>

#include <vector>

namespace triangulate
{
	class Triangulation2Test : public ::testing::Test {};

	TEST_F(Triangulation2Test, EarClippingTriangulationOfASquare)
	{
		std::vector<Point2> edgePoints;

		edgePoints.push_back(Point2(0, 0));
		edgePoints.push_back(Point2(1, 0));
		edgePoints.push_back(Point2(1, 1));
		edgePoints.push_back(Point2(0, 1));

		Polygon2 square(edgePoints);

		TriangleMesh2 triangleMesh;
		Triangulation2::EarClippingTriangulation(square, triangleMesh);

		const std::vector<Triangle2>& triangles = triangleMesh.GetTriangles();

		EXPECT_EQ(2, triangles.size());

		// First triangle.

		EXPECT_EQ(Point2(0, 0), triangles[0].GetP1());
		EXPECT_EQ(Point2(1, 0), triangles[0].GetP2());
		EXPECT_EQ(Point2(1, 1), triangles[0].GetP3());

		// Second triangle.

		EXPECT_EQ(Point2(0, 0), triangles[1].GetP1());
		EXPECT_EQ(Point2(1, 1), triangles[1].GetP2());
		EXPECT_EQ(Point2(0, 1), triangles[1].GetP3());
	}

	TEST_F(Triangulation2Test, EarClippingTriangulationOfAPentagon)
	{
		std::vector<Point2> edgePoints;

		edgePoints.push_back(Point2(0, 1));
		edgePoints.push_back(Point2(-0.951f, 0.309f));
		edgePoints.push_back(Point2(-0.588f, -0.809f));
		edgePoints.push_back(Point2(0.588f, -0.809f));
		edgePoints.push_back(Point2(0.951f, 0.309f));

		Polygon2 pentagon(edgePoints);

		TriangleMesh2 triangleMesh;
		Triangulation2::EarClippingTriangulation(pentagon, triangleMesh);

		const std::vector<Triangle2>& triangles = triangleMesh.GetTriangles();

		EXPECT_EQ(3, triangles.size());

		// First triangle.

		EXPECT_EQ(Point2(0, 1), triangles[0].GetP1());
		EXPECT_EQ(Point2(-0.951f, 0.309f), triangles[0].GetP2());
		EXPECT_EQ(Point2(-0.588f, -0.809f), triangles[0].GetP3());

		// Second triangle.

		EXPECT_EQ(Point2(0, 1), triangles[1].GetP1());
		EXPECT_EQ(Point2(-0.588f, -0.809f), triangles[1].GetP2());
		EXPECT_EQ(Point2(0.588f, -0.809f), triangles[1].GetP3());

		// Third triangle.

		EXPECT_EQ(Point2(0, 1), triangles[2].GetP1());
		EXPECT_EQ(Point2(0.588f, -0.809f), triangles[2].GetP2());
		EXPECT_EQ(Point2(0.951f, 0.309f), triangles[2].GetP3());
	}

}