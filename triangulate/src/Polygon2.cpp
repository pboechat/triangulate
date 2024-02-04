#include <triangulate/CollectionUtils.h>
#include <triangulate/Point2Set.h>
#include <triangulate/Polygon2.h>
#include <triangulate/Vector2.h>
#include <triangulate/Vector3.h>

#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

#ifndef EPSILON
#define EPSILON 0.0001f
#endif

namespace triangulate
{
	Polygon2::Polygon2(const std::vector<Point2>& rEdgePoints)
		:
		mEdgePoints(rEdgePoints)
	{
	}

	Polygon2::PointLocation Polygon2::LocatePoint(const Point2& rP0) const
	{
		Line2 line1(rP0, rP0.Add(Point2(1, 0)));
		int numberOfIntersections = 0;

		for (size_t i = 0; i < mEdgePoints.size(); i++)
		{
			const auto& rP1 = mEdgePoints[i];

			if (rP0 == rP1)
			{
				return PL_ON_THE_EDGE;
			}

			// Wrap around: the last edge point connects to the first.
			const auto& rP2 = (i == mEdgePoints.size() - 1) ? mEdgePoints[0] : mEdgePoints[i + 1];

			Line2 line2(rP1, rP2);

			if (rP1.GetX() != rP2.GetX())
			{
				if (rP1.GetY() != rP2.GetY())
				{
					Point2 intersectionPoint;

					if (!line1.Intersection(line2, intersectionPoint))
					{
						continue;
					}

					if (intersectionPoint.GetX() < rP0.GetX())
					{
						continue;
					}

					if (intersectionPoint.GetX() >= std::min(rP1.GetX(), rP2.GetX()) &&
						intersectionPoint.GetX() <= std::max(rP1.GetX(), rP2.GetX()) &&
						intersectionPoint.GetY() >= std::min(rP1.GetY(), rP2.GetY()) &&
						intersectionPoint.GetY() <= std::max(rP1.GetY(), rP2.GetY()))
					{
						numberOfIntersections++;
					}
				}
				else
				{
					if (rP0.GetY() == rP1.GetY() &&
						rP0.GetX() >= std::min(rP1.GetX(), rP2.GetX()) &&
						rP0.GetX() <= std::max(rP1.GetX(), rP2.GetX()))
					{
						return PL_ON_THE_EDGE;
					}
				}
			}
			else
			{
				if (rP0.GetY() >= std::min(rP1.GetY(), rP2.GetY()) &&
					rP0.GetY() <= std::max(rP1.GetY(), rP2.GetY()))
				{
					if (rP0.GetX() == rP1.GetX())
					{
						return PL_ON_THE_EDGE;
					}
					else if (rP0.GetX() > rP1.GetX())
					{
						numberOfIntersections++;
					}
				}
			}
		}

		// According to the Jordan Curve Theorem, if the number of intersections is even (or zero), the point is
		// located outside of the polygon.
		if (numberOfIntersections % 2 == 0)
		{
			return PL_OUTSIDE;
		}
		else
		{
			return PL_INSIDE;
		}
	}

	Polygon2::PointLocation Polygon2::LocatePointUsingRotationIndex(const Point2& rP0) const
	{
		// Checking if P0 is on the edge.
		for (size_t i = 0; i < mEdgePoints.size(); i++)
		{
			const auto& rP1 = mEdgePoints[i];
			// Wrap around: the last edge point connects to the first.
			const auto& rP2 = (i == mEdgePoints.size() - 1) ? mEdgePoints[0] : mEdgePoints[i + 1];

			if (EdgeContainsPoint(Line2(rP1, rP2), rP0))
			{
				return PL_ON_THE_EDGE;
			}
		}

		float rotationIndex = 0;
		for (size_t i = 0; i < mEdgePoints.size(); i++)
		{
			const auto& rP1 = mEdgePoints[i];
			// Wrap around: the last edge point connects to the first.
			const auto& rP2 = (i == mEdgePoints.size() - 1) ? mEdgePoints[0] : mEdgePoints[i + 1];

			rotationIndex += Vector2(rP0, rP1).GetOrientedAngle(Vector2(rP0, rP2));
		}
		rotationIndex /= (float)(2 * M_PI);

		// According to the Rotation Index Theorem, if the rotation index is zero, the point is outside.

		// FIXME: Precision error!!!
		if (rotationIndex >= -EPSILON && rotationIndex <= EPSILON)
		{
			return PL_OUTSIDE;
		}
		else
		{
			return PL_INSIDE;
		}
	}

	bool Polygon2::IsCounterclockwise() const
	{
		float crossProduct = 0;

		Vector2 v1(mEdgePoints[0], mEdgePoints[1]);
		for (size_t i = 1; i < mEdgePoints.size() - 1; i++)
		{
			const auto& rP1 = mEdgePoints[i];
			// Wrap around: the last edge point connects to the first.
			const auto& rP2 = (i == mEdgePoints.size() - 1) ? mEdgePoints[0] : mEdgePoints[i + 1];

			Vector2 v2(rP1, rP2);
			crossProduct += Vector3(v1).CrossProduct(v2).GetZ();

			v1 = v2;
		}

		return crossProduct > 0;
	}

	bool Polygon2::IsSimple() const
	{
		for (size_t i = 0; i < mEdgePoints.size(); i++)
		{
			const auto& rP1 = mEdgePoints[i];
			// Wrap around: the last edge point connects to the first.
			const auto& rP2 = (i == mEdgePoints.size() - 1) ? mEdgePoints[0] : mEdgePoints[i + 1];

			Line2 edge1(rP1, rP2);
			for (size_t j = 0; j < mEdgePoints.size(); j++)
			{
				const auto& rP3 = mEdgePoints[j];
				// Wrap around: the last edge point connects to the first.
				const auto& rP4 = (j == mEdgePoints.size() - 1) ? mEdgePoints[0] : mEdgePoints[j + 1];

				Line2 edge2(rP3, rP4);

				if (edge1 == edge2)
				{
					continue;
				}

				if (edge1.GetStart() == edge2.GetEnd() ||
					edge1.GetEnd() == edge2.GetStart())
				{
					continue;
				}

				Point2 intersectionPoint;
				if (edge1.Intersection(edge2, intersectionPoint) &&
					EdgeContainsPoint(edge1, intersectionPoint) &&
					EdgeContainsPoint(edge2, intersectionPoint))
				{
					return false;
				}
			}
		}

		return true;
	}

	bool Polygon2::EdgeContainsPoint(const Line2& rEdge, const Point2& rPoint) const
	{
		return rEdge.Contains(rPoint) &&
			rPoint.GetY() >= std::min(rEdge.GetStart().GetY(), rEdge.GetEnd().GetY()) && rPoint.GetY() <= std::max(rEdge.GetStart().GetY(), rEdge.GetEnd().GetY()) &&
			rPoint.GetX() >= std::min(rEdge.GetStart().GetX(), rEdge.GetEnd().GetX()) && rPoint.GetX() <= std::max(rEdge.GetStart().GetX(), rEdge.GetEnd().GetX());
	}

}