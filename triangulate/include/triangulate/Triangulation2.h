#ifndef TRIANGULATE_TRIANGULATION2_H
#define TRIANGULATE_TRIANGULATION2_H

#include <triangulate/Polygon2.h>
#include <triangulate/TriangleMesh2.h>

namespace triangulate
{
	class Triangulation2
	{
	public:
		static void EarClippingTriangulation(const Polygon2& rPolygon, TriangleMesh2& rTriangleMesh);

		Triangulation2() = delete;

	};

}

#endif