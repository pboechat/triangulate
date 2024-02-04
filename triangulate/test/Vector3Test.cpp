#include <triangulate/Vector3.h>

#include <gtest/gtest.h>

namespace triangulate
{
	class Vector3Test : public ::testing::Test {};

	TEST_F(Vector3Test, CrossProduct)
	{
		Vector3 v1(1, 0, 0);
		Vector3 v2(0, 1, 0);

		Vector3 v3 = v1.CrossProduct(v2);

		EXPECT_EQ(Vector3(0, 0, 1), v3);

		v3 = v2.CrossProduct(v1);

		EXPECT_EQ(Vector3(0, 0, -1), v3);
	}

}
