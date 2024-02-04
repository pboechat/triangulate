#ifndef TRIANGULATE_CONVEXHULL2_H
#define TRIANGULATE_CONVEXHULL2_H

#include <triangulate/Point2.h>
#include <triangulate/Polygon2.h>
#include <triangulate/Vector2.h>

#include <vector>

namespace triangulate
{
	class ConvexHull2
	{
	public:
		static void BuildUsingGrahamScan(const std::vector<Point2>& rEdgePoints, Polygon2& rPolygon);
		static void BuildUsingDivideAndConquer(const std::vector<Point2>& rEdgePoints, Polygon2& rPolygon);

	private:
		struct GrahamScanSorter
		{
			Point2 mAnchor;

			GrahamScanSorter(const Point2& rAnchor)
			{
				mAnchor = rAnchor;
			}

			// Returns true if the first argument goes before the second argument in the specific order.
			bool operator() (const Point2& rFirst, const Point2& rSecond)
			{
				Vector2 v1(mAnchor, rFirst);
				Vector2 v2(mAnchor, rSecond);
				return Vector2::UNIT_X.GetAngle(v1) < Vector2::UNIT_X.GetAngle(v2);
			}
		};

		struct DivideAndConquerSorter
		{
			// Returns true if the first argument goes before the second argument in the specific order.
			bool operator() (const Point2& rFirst, const Point2& rSecond)
			{
				return rFirst.GetX() < rSecond.GetX();
			}
		};

		ConvexHull2() = default;

		static void DivideAndConquer(std::vector<Point2>& rEdgePointsList);
		static void Merge(const std::vector<Point2>& rSource1, const std::vector<Point2>& rSource2, std::vector<Point2>& rDestination);

	};

}

#endif