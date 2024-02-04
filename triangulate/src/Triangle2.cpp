#include <triangulate/Triangle2.h>

namespace triangulate
{
	Triangle2::Triangle2(const Point2& rP1, const Point2& rP2, const Point2& rP3)
	{
		mEdgePoints.push_back(rP1);
		mEdgePoints.push_back(rP2);
		mEdgePoints.push_back(rP3);
	}

}