#include <triangulate/Point2Set.h>

namespace triangulate
{
	Point2 Point2Set::FindCentroid(const std::vector<Point2>& rPoints)
	{
		float x = 0;
		float y = 0;
		for (size_t i = 0; i < rPoints.size(); i++)
		{
			x += rPoints[i].GetX();
			y += rPoints[i].GetY();
		}
		x /= rPoints.size();
		y /= rPoints.size();

		return Point2(x, y);
	}

	std::vector<Point2>::const_iterator Point2Set::GetBottommostPointCursor(const std::vector<Point2>& rPoints)
	{
		auto bottommostPointCursor = rPoints.begin();
		for (auto currentPointCursor = rPoints.begin(); currentPointCursor != rPoints.end(); currentPointCursor++)
		{
			if ((*bottommostPointCursor).GetY() > (*currentPointCursor).GetY())
			{
				bottommostPointCursor = currentPointCursor;
			}
		}

		return bottommostPointCursor;
	}

	std::vector<Point2>::const_iterator Point2Set::GetLeftmostPointCursor(const std::vector<Point2>& rPoints)
	{
		auto leftmostPointCursor = rPoints.begin();
		for (auto currentPointCursor = rPoints.begin(); currentPointCursor != rPoints.end(); currentPointCursor++)
		{
			if ((*leftmostPointCursor).GetX() > (*currentPointCursor).GetX())
			{
				leftmostPointCursor = currentPointCursor;
			}
		}

		return leftmostPointCursor;
	}

	std::vector<Point2>::const_iterator Point2Set::GetRightmostPointCursor(const std::vector<Point2>& rPoints)
	{
		auto rightmostPointCursor = rPoints.begin();
		for (auto currentPointCursor = rPoints.begin(); currentPointCursor != rPoints.end(); currentPointCursor++)
		{
			if ((*rightmostPointCursor).GetX() < (*currentPointCursor).GetX())
			{
				rightmostPointCursor = currentPointCursor;
			}
		}

		return rightmostPointCursor;
	}

	Point2Set::LineSituation Point2Set::SituateLine(const std::vector<Point2>& rPoints, const Line2& rLine)
	{
		Line2::PointSituation pointSetCommonSituation = rLine.SituatePoint(rPoints[0]);

		for (size_t i = 1; i < rPoints.size(); i++)
		{
			Line2::PointSituation pointSituation = rLine.SituatePoint(rPoints[i]);

			if (pointSetCommonSituation == Line2::PS_ON_THE_LINE)
			{
				if (pointSituation != Line2::PS_ON_THE_LINE)
				{
					pointSetCommonSituation = pointSituation;
				}
			}
			else if (pointSetCommonSituation == Line2::PS_LEFT)
			{
				if (pointSituation == Line2::PS_RIGHT)
				{
					return LS_CUT;
				}
			}
			else if (pointSetCommonSituation == Line2::PS_RIGHT)
			{
				if (pointSituation == Line2::PS_LEFT)
				{
					return LS_CUT;
				}
			}
		}

		if (pointSetCommonSituation == Line2::PS_LEFT)
		{
			return LS_RIGHT;
		}
		else if (pointSetCommonSituation == Line2::PS_RIGHT)
		{
			return LS_LEFT;
		}
		else
		{
			return LS_CUT;
		}
	}

}
