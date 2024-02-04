#ifndef TRIANGULATE_POLYGON2_H
#define TRIANGULATE_POLYGON2_H

#include <triangulate/Point2.h>
#include <triangulate/Line2.h>

#include <vector>

namespace triangulate
{
	class Polygon2
	{
	public:
		enum  PointLocation
		{
			PL_INSIDE = -1,
			PL_ON_THE_EDGE,
			PL_OUTSIDE
		};

		Polygon2() = default;
		Polygon2(const std::vector<Point2>& rEdgePoints);
		Polygon2::PointLocation LocatePoint(const Point2& rP) const;
		Polygon2::PointLocation LocatePointUsingRotationIndex(const Point2& rP) const;
		bool IsCounterclockwise() const;
		bool IsSimple() const;

		inline const std::vector<Point2>& GetEdgePoints() const
		{
			return mEdgePoints;
		}

		inline void SetEdgePoints(const std::vector<Point2>& rEdgePoints)
		{
			mEdgePoints = rEdgePoints;
		}

	protected:
		std::vector<Point2> mEdgePoints;

		bool EdgeContainsPoint(const Line2& rEdge, const Point2& rPoint) const;

	};

}

#endif