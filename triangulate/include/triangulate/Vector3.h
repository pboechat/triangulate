#ifndef TRIANGULATE_VECTOR3_H
#define TRIANGULATE_VECTOR3_H

#include <triangulate/Vector2.h>

namespace triangulate
{
	class Vector3
	{
	public:
		static const Vector3 ZERO;

		Vector3();
		Vector3(float x, float y, float z);
		Vector3(const Vector2& rVector2);

		float DotProduct(const Vector3& rVector) const;
		Vector3 CrossProduct(const Vector3& rVector) const;
		void Add(const Vector3& rVector);
		void Subtract(const Vector3& rVector);
		void Multiply(float scalar);

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

		inline float GetZ() const
		{
			return mZ;
		}

		inline void SetZ(float z)
		{
			this->mZ = z;
		}

		inline bool operator==(const Vector3& rVector) const
		{
			return mX == rVector.mX && mY == rVector.mY && mZ == rVector.mZ;
		}

	private:
		float mX;
		float mY;
		float mZ;

	};

}

#endif