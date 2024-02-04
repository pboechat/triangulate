#ifndef TRIANGULATE_TRIANGLEMESH2_H
#define TRIANGULATE_TRIANGLEMESH2_H

#include <triangulate/Triangle2.h>

#include <vector>

namespace triangulate
{
	class TriangleMesh2
	{
	public:
		TriangleMesh2() = default;
		TriangleMesh2(const std::vector<Triangle2>& rTriangles);

		inline const std::vector<Triangle2>& GetTriangles() const
		{
			return mTriangles;
		}

		inline void SetTriangles(const std::vector<Triangle2>& rTriangles)
		{
			mTriangles = rTriangles;
		}

	private:
		std::vector<Triangle2> mTriangles;

	};

}

#endif