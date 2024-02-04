#ifndef TRIANGULATE_POINT2_H
#define TRIANGULATE_POINT2_H

#include <iostream>

namespace triangulate
{
	class Point2
	{
	public:
		static const Point2 ZERO;

		Point2();
		Point2(const Point2& rPoint);
		Point2(float x, float y);

		Point2 Add(const Point2& rPoint) const;
		Point2 Subtract(const Point2& rPoint) const;

		inline float GetX() const
		{
			return mX;
		}

		inline void SetX(float x)
		{
			this->mX = x;
		}

		inline float GetY() const
		{
			return mY;
		}

		inline void SetY(float y)
		{
			this->mY = y;
		}

		inline bool operator==(const Point2& rPoint) const
		{
			return mX == rPoint.mX && mY == rPoint.mY;
		}

	private:
		float mX;
		float mY;

	};

	void PrintTo(const Point2& rPoint, std::ostream& os);

}

#endif