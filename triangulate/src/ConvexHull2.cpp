#include <triangulate/CollectionUtils.h>
#include <triangulate/ConvexHull2.h>
#include <triangulate/Line2.h>
#include <triangulate/Point2Set.h>
#include <triangulate/Vector2.h>

#include <algorithm>

namespace triangulate
{
	void ConvexHull2::BuildUsingGrahamScan(const std::vector<Point2>& rEdgePoints, Polygon2& rPolygon)
	{
		if (rEdgePoints.size() < 3)
		{
			return;
		}

		// Choose the bottom most point as an anchor.
		const auto& rAnchor = (*Point2Set::GetBottommostPointCursor(rEdgePoints));

		std::list<Point2> edgePointsOrderedByTheAngleToTheAnchor;
		for (size_t i = 0; i < rEdgePoints.size(); i++)
		{
			const auto& rP = rEdgePoints[i];

			if (rP == rAnchor)
			{
				continue;
			}

			edgePointsOrderedByTheAngleToTheAnchor.push_back(rP);
		}

		// Sorts all other points based on angles they form about the anchor.
		edgePointsOrderedByTheAngleToTheAnchor.sort(GrahamScanSorter(rAnchor));

		// Add the anchor and the first 2 points to the points list.

		std::list<Point2> edgePointsList;
		edgePointsList.push_back(rAnchor);

		auto p1Cursor = edgePointsOrderedByTheAngleToTheAnchor.begin();
		edgePointsList.push_back(*p1Cursor);

		auto p2Cursor = CollectionUtils<Point2>::GetNext(p1Cursor);
		edgePointsList.push_back(*p2Cursor);

		Vector2 e1(*p1Cursor, *p2Cursor);

		auto p3Cursor = p2Cursor;
		p3Cursor++;
		while (p3Cursor != edgePointsOrderedByTheAngleToTheAnchor.end())
		{
			Vector2 e2(*p2Cursor, *p3Cursor);

			// If the newly added edge (e2) makes a concavity, removes previously added edge points
			// until there's no concavity.
			while (e2.GetOrientedAngle(e1) >= 0)
			{
				edgePointsList.remove(*p2Cursor);
				p2Cursor = p1Cursor;
				p1Cursor--;
				e1 = Vector2(*p1Cursor, *p2Cursor);
				e2 = Vector2(*p2Cursor, *p3Cursor);
			}

			edgePointsList.push_back(*p3Cursor);
			e1 = e2;
			p2Cursor = p3Cursor;
			p1Cursor = CollectionUtils<Point2>::GetPrevious(p2Cursor);
			p3Cursor++;
		}

		// Convert from list back to vector.
		std::vector<Point2> edgePoints;
		auto edgePointIterator = edgePointsList.begin();
		while (edgePointIterator != edgePointsList.end())
		{
			edgePoints.push_back(*edgePointIterator);
			edgePointIterator++;
		}

		rPolygon.SetEdgePoints(edgePoints);
	}

	void ConvexHull2::BuildUsingDivideAndConquer(const std::vector<Point2>& rEdgePoints, Polygon2& rPolygon)
	{
		std::vector<Point2> edgePointsCopy(rEdgePoints);

		// Sorts the points by x-coordinate.
		std::sort(edgePointsCopy.begin(), edgePointsCopy.end(), DivideAndConquerSorter());

		DivideAndConquer(edgePointsCopy);

		rPolygon.SetEdgePoints(edgePointsCopy);
	}

	void ConvexHull2::DivideAndConquer(std::vector<Point2>& rEdgePoints)
	{
		// Edge points lists with 1 or 2 points are sufficiently divided, so exit.
		if (rEdgePoints.size() < 3)
		{
			return;
		}

		auto halfListCursor = rEdgePoints.begin();
		std::advance(halfListCursor, rEdgePoints.size() / 2);

		std::vector<Point2> firstGroup(rEdgePoints.begin(), halfListCursor);
		std::vector<Point2> secondGroup(halfListCursor, rEdgePoints.end());

		DivideAndConquer(firstGroup);
		DivideAndConquer(secondGroup);

		Merge(firstGroup, secondGroup, rEdgePoints);
	}

	void ConvexHull2::Merge(const std::vector<Point2>& rAPointSet, const std::vector<Point2>& rBPointSet, std::vector<Point2>& rMergePointSet)
	{
		// Finding AB lower and upper tangents.

		auto aLowerBoundCursor = Point2Set::GetRightmostPointCursor(rAPointSet);
		auto bLowerBoundCursor = Point2Set::GetLeftmostPointCursor(rBPointSet);
		auto aUpperBoundCursor = aLowerBoundCursor;
		auto bUpperBoundCursor = bLowerBoundCursor;

		Line2 abLowerTangent(*aLowerBoundCursor, *bLowerBoundCursor);
		Line2 abUpperTangent(*aUpperBoundCursor, *bUpperBoundCursor);

		if (rBPointSet.size() > 1)
		{
			// Walk along B in counterclockwise fashion until a lower tangent is found.

			while (Point2Set::SituateLine(rBPointSet, abLowerTangent) != Point2Set::LS_RIGHT)
			{
				bLowerBoundCursor = CollectionUtils<Point2>::GetNext(bLowerBoundCursor, &rBPointSet);
				abLowerTangent = Line2(*aLowerBoundCursor, *bLowerBoundCursor);
			}
		}

		if (rAPointSet.size() > 1)
		{
			// Walk along A in counterclockwise fashion until a left tangent is found.

			while (Point2Set::SituateLine(rAPointSet, abLowerTangent) != Point2Set::LS_RIGHT)
			{
				aLowerBoundCursor = CollectionUtils<Point2>::GetNext(aLowerBoundCursor, &rAPointSet);
				abLowerTangent = Line2(*aLowerBoundCursor, *bLowerBoundCursor);
			}
		}

		if (rBPointSet.size() > 1)
		{
			// Walk along B in clockwise fashion until a upper tangent is found.

			while (Point2Set::SituateLine(rBPointSet, abUpperTangent) != Point2Set::LS_LEFT)
			{
				bUpperBoundCursor = CollectionUtils<Point2>::GetPrevious(bUpperBoundCursor, &rBPointSet);
				abUpperTangent = Line2(*aUpperBoundCursor, *bUpperBoundCursor);
			}
		}

		if (rAPointSet.size() > 1)
		{
			// Walk along A in clockwise fashion until a upper tangent is found.

			while (Point2Set::SituateLine(rAPointSet, abUpperTangent) != Point2Set::LS_LEFT)
			{
				aUpperBoundCursor = CollectionUtils<Point2>::GetPrevious(aUpperBoundCursor, &rAPointSet);
				abUpperTangent = Line2(*aUpperBoundCursor, *bUpperBoundCursor);
			}
		}

		// Making (destination = source1 U source2) using lower and upper bounds as mending points.

		// FIXME:
		rMergePointSet.clear();
		bool hasFoundLowerBound;
		do
		{
			hasFoundLowerBound = aUpperBoundCursor == aLowerBoundCursor;
			rMergePointSet.push_back(*aUpperBoundCursor);
			aUpperBoundCursor = CollectionUtils<Point2>::GetNext(aUpperBoundCursor, &rAPointSet);
		} while (!hasFoundLowerBound);

		bool hasFoundUpperBound;
		do
		{
			hasFoundUpperBound = bLowerBoundCursor == bUpperBoundCursor;
			rMergePointSet.push_back(*bLowerBoundCursor);
			bLowerBoundCursor = CollectionUtils<Point2>::GetNext(bLowerBoundCursor, &rBPointSet);
		} while (!hasFoundUpperBound);
	}

}