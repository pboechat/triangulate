#include <triangulate/Vector2.h>
#include <triangulate/Vector3.h>

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

namespace triangulate
{
	const Vector2 Vector2::ZERO(0, 0);
	const Vector2 Vector2::UNIT_X(1, 0);
	const Vector2 Vector2::UNIT_Y(0, 1);

	Vector2::Vector2()
		:
		mX(0),
		mY(0)
	{
	}

	Vector2::Vector2(float x, float y)
		:
		mX(x),
		mY(y)
	{
	}

	Vector2::Vector2(const Vector2& rVector)
	{
		mX = rVector.mX;
		mY = rVector.mY;
	}

	Vector2::Vector2(const Point2& rPoint)
	{
		mX = rPoint.GetX();
		mY = rPoint.GetY();
	}

	Vector2::Vector2(const Point2& rStart, const Point2& rEnd)
	{
		Point2 point = rEnd.Subtract(rStart);
		mX = point.GetX();
		mY = point.GetY();
	}

	float Vector2::DotProduct(const Vector2& rVector) const
	{
		return mX * rVector.mX + mY * rVector.mY;
	}

	float Vector2::Magnitude() const
	{
		return (float)sqrt(pow(mX, 2) + pow(mY, 2));
	}

	Vector2 Vector2::Divide(float scalar) const
	{
		return Vector2(mX / scalar, mY / scalar);
	}

	Vector2 Vector2::Normalized() const
	{
		return Divide(Magnitude());
	}

	float Vector2::GetAngle(const Vector2& rVector) const
	{
		float angle = acos(DotProduct(rVector) / (Magnitude() * rVector.Magnitude()));

		if (Vector3(*this).CrossProduct(Vector3(rVector)).GetZ() >= 0)
		{
			return angle;
		}
		else
		{
			return (float)((2.0 * M_PI) - angle);
		}
	}

	float Vector2::GetOrientedAngle(const Vector2& rVector) const
	{
		float angle = acos(DotProduct(rVector) / (Magnitude() * rVector.Magnitude()));

		if (Vector3(*this).CrossProduct(Vector3(rVector)).GetZ() >= 0)
		{
			return angle;
		}
		else
		{
			return -angle;
		}
	}

	void PrintTo(const Vector2& rVector, std::ostream& rOut) {
		rOut << "Vector2(" << rVector.GetX() << ", " << rVector.GetY() << ")";
	}

}