#ifndef TRIANGULATE_MATRIX22_H
#define TRIANGULATE_MATRIX22_H

#include <triangulate/Vector2.h>

namespace triangulate
{
	class Matrix22
	{
	public:
		Matrix22();
		Matrix22(float m11, float m12, float m21, float m22);

		void FromAngle(float angle);
		Vector2 Multiply(const Vector2& rVector) const;

	private:
		float mEntry[4];
	};

}

#endif