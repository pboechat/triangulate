#ifndef TRIANGULATE_POINT2SET_H
#define TRIANGULATE_POINT2SET_H

#include <triangulate/Point2.h>
#include <triangulate/Line2.h>

#include <vector>

namespace triangulate
{
	class Point2Set
	{
	public:
		enum LineSituation
		{
			LS_LEFT,
			LS_CUT,
			LS_RIGHT,
		};

		static Point2 FindCentroid(const std::vector<Point2>& rPoints);
		static std::vector<Point2>::const_iterator GetBottommostPointCursor(const std::vector<Point2>& rPoints);
		static std::vector<Point2>::const_iterator GetLeftmostPointCursor(const std::vector<Point2>& rPoints);
		static std::vector<Point2>::const_iterator GetRightmostPointCursor(const std::vector<Point2>& rPoints);
		static Point2Set::LineSituation SituateLine(const std::vector<Point2>& rPoints, const Line2& rLine);

		Point2Set() = delete;

	};

}

#endif