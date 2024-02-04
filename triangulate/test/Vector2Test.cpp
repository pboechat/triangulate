#include <triangulate/Vector2.h>

#include <gtest/gtest.h>

#define _USE_MATH_DEFINES
#include <math.h>

namespace triangulate
{
	class Vector2Test : public ::testing::Test {};

	TEST_F(Vector2Test, GetOrientedAngle)
	{
		Vector2 v1(1, 0);
		Vector2 v2(0, 1);

		EXPECT_EQ((float)M_PI_2, v1.GetOrientedAngle(v2));

		v1 = Vector2(1, 0);
		v2 = Vector2(-1, 1);

		EXPECT_EQ((float)(M_PI_2 + M_PI_4), v1.GetOrientedAngle(v2));

		v1 = Vector2(1, 0);
		v2 = Vector2(-1, 0);

		EXPECT_EQ((float)M_PI, v1.GetOrientedAngle(v2));

		v1 = Vector2(1, 0);
		v2 = Vector2(-1, -1);

		EXPECT_EQ(-(float)(M_PI_2 + M_PI_4), v1.GetOrientedAngle(v2));

		v1 = Vector2(1, 0);
		v2 = Vector2(0, -1);

		EXPECT_EQ(-(float)M_PI_2, v1.GetOrientedAngle(v2));
	}

}
