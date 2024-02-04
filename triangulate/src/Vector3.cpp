#include <triangulate/Vector3.h>

namespace triangulate
{
	const Vector3 Vector3::ZERO(0, 0, 0);

	Vector3::Vector3() :
		mX(0),
		mY(0),
		mZ(0)
	{
	}

	Vector3::Vector3(float x, float y, float z) :
		mX(x),
		mY(y),
		mZ(z)
	{
	}

	Vector3::Vector3(const Vector2& rVector2)
	{
		mX = rVector2.GetX();
		mY = rVector2.GetY();
		mZ = 0;
	}

	float Vector3::DotProduct(const Vector3& rVector) const
	{
		return mX * rVector.mX + mY * rVector.mY + mZ * rVector.mZ;
	}

	Vector3 Vector3::CrossProduct(const Vector3& rVector) const
	{
		return Vector3(mY * rVector.mZ - mZ * rVector.mY,  // a2b3 - a3b2
			mZ * rVector.mX - mX * rVector.mZ,  // a3b1 - a1b3
			mX * rVector.mY - mY * rVector.mX); // a1b2 - a2b1
	}

	void Vector3::Add(const Vector3& rVector)
	{
		mX += rVector.mX;
		mY += rVector.mY;
		mZ += rVector.mZ;
	}

	void Vector3::Subtract(const Vector3& rVector)
	{
		mX -= rVector.mX;
		mY -= rVector.mY;
		mZ -= rVector.mZ;
	}

	void Vector3::Multiply(float scalar)
	{
		mX *= scalar;
		mY *= scalar;
		mZ *= scalar;
	}

}