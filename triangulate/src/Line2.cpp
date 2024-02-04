#include <triangulate/Line2.h>

#include <algorithm>

#ifndef EPSILON
#define EPSILON 0.0001f
#endif

namespace triangulate
{
	Line2::Line2(const Point2& rStart, const Point2& rEnd)
		:
		mStart(rStart),
		mEnd(rEnd)
	{
	}

	bool Line2::Intersection(const Line2& rLine, Point2& rIntersectionPoint) const
	{
		float x1 = mStart.GetX();
		float y1 = mStart.GetY();
		float x2 = mEnd.GetX();
		float y2 = mEnd.GetY();
		float x3 = rLine.mStart.GetX();
		float y3 = rLine.mStart.GetY();
		float x4 = rLine.mEnd.GetX();
		float y4 = rLine.mEnd.GetY();

		float determinant = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

		if (determinant == 0)
		{
			return false;
		}

		float pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
		float x = (pre * (x3 - x4) - (x1 - x2) * post) / determinant;
		float y = (pre * (y3 - y4) - (y1 - y2) * post) / determinant;

		if (x < std::min(x1, x2) || x > std::max(x1, x2) ||
			x < std::min(x3, x4) || x > std::max(x3, x4))
		{
			return false;
		}

		if (y < std::min(y1, y2) || y > std::max(y1, y2) ||
			y < std::min(y3, y4) || y > std::max(y3, y4))
		{
			return false;
		}

		rIntersectionPoint.SetX(x);
		rIntersectionPoint.SetY(y);

		return true;
	}

	bool Line2::Contains(const Point2& rP) const
	{
		if (mStart.GetX() - mEnd.GetX() == 0) {
			return rP.GetX() == mStart.GetX();
		}

		float difference = ((GetSlope() * rP.GetX() + GetYIntersept()) - rP.GetY());

		// FIXME: Precision error!
		return (difference >= -EPSILON && difference <= EPSILON);
	}

	float Line2::GetSlope() const
	{
		return (mEnd.GetY() - mStart.GetY()) / (mEnd.GetX() - mStart.GetX());
	}

	float Line2::GetYIntersept() const
	{
		return mStart.GetY() - (GetSlope() * mStart.GetX());
	}

	Line2::PointSituation Line2::SituatePoint(const Point2& rP) const
	{
		float situation = (mEnd.GetX() - mStart.GetX()) * (rP.GetY() - mStart.GetY()) - (mEnd.GetY() - mStart.GetY()) * (rP.GetX() - mStart.GetX());

		if (situation > 0)
		{
			return PS_LEFT;
		}
		else if (situation < 0)
		{
			return PS_RIGHT;
		}
		else
		{
			return PS_ON_THE_LINE;
		}
	}

}