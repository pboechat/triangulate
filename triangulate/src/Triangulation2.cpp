#include <triangulate/CollectionUtils.h>
#include <triangulate/Point2Set.h>
#include <triangulate/Triangulation2.h>
#include <triangulate/Vector2.h>
#include <triangulate/Vector3.h>

#include <list>

namespace triangulate
{
	void Triangulation2::EarClippingTriangulation(const Polygon2& rPolygon, TriangleMesh2& rTriangleMesh)
	{
		const std::vector<Point2>& rEdgePoints = rPolygon.GetEdgePoints();

		// Must be a counterclockwise polygon.
		if (!rPolygon.IsCounterclockwise())
		{
			return;
		}

		// Must be a polygon with 4 or more edges.
		if (rEdgePoints.size() < 4)
		{
			return;
		}

		// Copying edge points to a linked list to reduce the cost of removing an edge to a constant.
		// Note: "std::list" is implemented as a doubly-linked list.
		std::list<Point2> edgePointsCopy;
		for (size_t i = 0; i < rEdgePoints.size(); i++)
		{
			edgePointsCopy.push_back(rEdgePoints[i]);
		}

		std::vector<Triangle2> triangles;
		auto currentEdgePoint = edgePointsCopy.begin();
		while (edgePointsCopy.size() > 2)
		{
			const auto& rP1 = (*currentEdgePoint);
			auto nextEdgePoint = CollectionUtils<Point2>::GetNext(currentEdgePoint, &edgePointsCopy);
			const auto& rP2 = (*nextEdgePoint);
			nextEdgePoint = CollectionUtils<Point2>::GetNext(nextEdgePoint, &edgePointsCopy);
			const auto& rP3 = (*nextEdgePoint);

			// Checking if p2 is convex.

			float angle = Vector2(rP2, rP3).GetOrientedAngle(Vector2(rP2, rP1));
			if (angle < 0)
			{
				// If p2 is concave, move to next point.
				currentEdgePoint++;
				continue;
			}

			// Checking if triangle (p1, p2, p3) contains no concave vertex.

			Triangle2 triangle(rP1, rP2, rP3);
			bool isEar = true;
			for (auto edgePointIterator = edgePointsCopy.begin(); edgePointIterator != edgePointsCopy.end(); edgePointIterator++)
			{
				// Checking for every point pb on the polygon, except for p1, p2 and p3.

				const auto& rPb = (*edgePointIterator);

				if (rPb == rP1 || rPb == rP2 || rPb == rP3)
				{
					continue;
				}

				if (triangle.LocatePointUsingRotationIndex(rPb) != Polygon2::PL_OUTSIDE)
				{
					const auto& rPa = (*CollectionUtils<Point2>::GetPrevious(edgePointIterator, &edgePointsCopy));
					const auto& rPc = (*CollectionUtils<Point2>::GetNext(edgePointIterator, &edgePointsCopy));

					// Checking if p1 is concave.

					float angle = Vector2(rPb, rPc).GetOrientedAngle(Vector2(rPb, rPa));
					if (angle < 0)
					{
						// If there's a concave point inside T(P1, P2, P2), it's not an ear.
						isEar = false;
						break;
					}
				}
			}

			if (isEar)
			{
				edgePointsCopy.remove(rP2);
				triangles.push_back(triangle);
			}
			else
			{
				currentEdgePoint++;
			}
		}

		rTriangleMesh.SetTriangles(triangles);
	}

}