#include <triangulate/Point2.h>

namespace triangulate
{
	const Point2 Point2::ZERO(0, 0);

	Point2::Point2()
		:
		mX(0),
		mY(0)
	{
	}

	Point2::Point2(const Point2& rPoint)
	{
		mX = rPoint.mX;
		mY = rPoint.mY;
	}

	Point2::Point2(float x, float y) :
		mX(x),
		mY(y)
	{
	}

	Point2 Point2::Add(const Point2& rPoint) const
	{
		return Point2(mX + rPoint.mX, mY + rPoint.mY);
	}

	Point2 Point2::Subtract(const Point2& rPoint) const
	{
		return Point2(mX - rPoint.mX, mY - rPoint.mY);
	}

	void PrintTo(const Point2& rPoint, std::ostream& rOut)
	{
		rOut << "Point2(" << rPoint.GetX() << ", " << rPoint.GetY() << ")";
	}

}