#include <triangulate/Matrix22.h>

#include <cmath>

namespace triangulate
{
	Matrix22::Matrix22()
	{
		mEntry[0] = 0; mEntry[1] = 0; mEntry[2] = 0; mEntry[3] = 0;
	}

	Matrix22::Matrix22(float m11, float m12, float m21, float m22)
	{
		mEntry[0] = m11; mEntry[1] = m12; mEntry[2] = m21; mEntry[3] = m22;
	}

	void Matrix22::FromAngle(float angle)
	{
		mEntry[0] = std::cos(angle);
		mEntry[2] = std::sin(angle);
		mEntry[1] = -mEntry[2];
		mEntry[3] = mEntry[0];
	}

	Vector2 Matrix22::Multiply(const Vector2& rVector) const
	{
		return Vector2(mEntry[0] * rVector.GetX() + mEntry[1] * rVector.GetY(),
			mEntry[2] * rVector.GetX() + mEntry[3] * rVector.GetY());
	}

}