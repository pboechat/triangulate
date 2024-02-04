#ifndef TRIANGULATE_VECTOR2_H
#define TRIANGULATE_VECTOR2_H

#include <triangulate/Point2.h>

#include <iostream>

namespace triangulate
{
	class Vector2
	{
	public:
		static const Vector2 ZERO;
		static const Vector2 UNIT_X;
		static const Vector2 UNIT_Y;

		Vector2();
		Vector2(float x, float y);
		Vector2(const Vector2& rVector);
		Vector2(const Point2& rPoint);
		Vector2(const Point2& rStart, const Point2& rEnd);

		Vector2 Divide(float scalar) const;
		float DotProduct(const Vector2& rVector) const;
		float Magnitude() const;
		Vector2 Normalized() const;
		float GetAngle(const Vector2& rVector) const;
		float GetOrientedAngle(const Vector2& rVector) const;

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

		inline bool operator==(const Vector2& rVector) const
		{
			return mX == rVector.mX && mY == rVector.mY;
		}

	private:
		float mX;
		float mY;

	};

	void PrintTo(const Vector2& rVector, std::ostream& rOut);

}

#endif