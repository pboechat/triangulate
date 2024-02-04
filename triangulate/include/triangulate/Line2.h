#ifndef TRIANGULATE_LINE2_H
#define TRIANGULATE_LINE2_H

#include <triangulate/Point2.h>

namespace triangulate
{
	class Polygon2;

	class Line2
	{
	public:
		enum PointSituation
		{
			PS_LEFT = -1,
			PS_ON_THE_LINE,
			PS_RIGHT,
		};

		Line2(const Point2& rStart, const Point2& rEnd);
		bool Intersection(const Line2& rLine, Point2& rIntersectionPoint) const;
		bool Contains(const Point2& rP) const;
		float GetSlope() const;
		float GetYIntersept() const;
		Line2::PointSituation SituatePoint(const Point2& rP) const;

		inline const Point2& GetStart() const
		{
			return mStart;
		}

		inline const Point2& GetEnd() const
		{
			return mEnd;
		}

		bool operator==(const Line2& rLine) const
		{
			return mStart == rLine.mStart && mEnd == rLine.mEnd;
		}

	private:
		Point2 mStart;
		Point2 mEnd;

	};

}

#endif