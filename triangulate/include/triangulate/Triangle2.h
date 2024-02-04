#ifndef TRIANGULATE_TRIANGLE2_H
#define TRIANGULATE_TRIANGLE2_H

#include <triangulate/Polygon2.h>
#include <triangulate/Point2.h>

namespace triangulate
{
	class Triangle2 : public Polygon2
	{
	public:
		Triangle2(const Point2& rP1, const Point2& rP2, const Point2& rP3);

		inline const Point2& GetP1() const
		{
			return mEdgePoints[0];
		}

		inline const Point2& GetP2() const
		{
			return mEdgePoints[1];
		}

		inline const Point2& GetP3() const
		{
			return mEdgePoints[2];
		}

	};

}

#endif