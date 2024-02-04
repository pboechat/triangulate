#include <ConvexHullApplication.h>
#include <triangulate/ConvexHull2.h>

#include <sstream>

ConvexHullApplication::ConvexHullApplication() :
	Application(),
	mpPolygon(nullptr),
	mStrategy(CHBS_GRAHAM_SCAN)
{
}

void ConvexHullApplication::ParseCommandLine(int argc, char** argv)
{
}

bool ConvexHullApplication::OnRender()
{
	DrawCurrentConvexHullBuildingStrategy();
	DrawCommands();

	if (mpPolygon == nullptr)
	{
		DrawPoints();
	}

	else
	{
		DrawPolygon();
	}

	return true;
}

void ConvexHullApplication::BuildConvexHull()
{
	// Cannot build a convex hull with less than 3 points.
	if (mEdgePoints.size() < 3)
	{
		printf("Cannot build a convex hull with less than 3 points.\n");
		return;
	}

	mpPolygon = std::make_unique<Polygon2>();

	if (mStrategy == CHBS_GRAHAM_SCAN)
	{
		ConvexHull2::BuildUsingGrahamScan(mEdgePoints, *mpPolygon);
	}

	else
	{
		ConvexHull2::BuildUsingDivideAndConquer(mEdgePoints, *mpPolygon);
	}
}

void ConvexHullApplication::StartPolygonWithNewPoints()
{
	if (mpPolygon != nullptr)
	{
		mpPolygon = nullptr;
	}
	mEdgePoints.clear();
}

void ConvexHullApplication::OnKeyDown(int key)
{
	if (key == VK_RETURN)
	{
		BuildConvexHull();
	}
	else if (key == VK_SPACE)
	{
		StartPolygonWithNewPoints();
	}
	else if (key == VK_TAB)
	{
		if (mStrategy == CHBS_GRAHAM_SCAN)
		{
			mStrategy = CHBS_DIVIDE_AND_CONQUER;
		}
		else
		{
			mStrategy = CHBS_GRAHAM_SCAN;
		}
	}
}

void ConvexHullApplication::OnMouseButtonDown(char button, int screenX, int screenY, float viewportX, float viewportY)
{
	if (button == 1)
	{
		if (mpPolygon != nullptr)
		{
			return;
		}

		// Add a new point at mouse pointer.
		mEdgePoints.push_back(Point2(viewportX, viewportY));
	}
	else if (button == 3)
	{
		if (mEdgePoints.size() == 0)
		{
			return;
		}

		if (mpPolygon != nullptr)
		{
			return;
		}

		// Remove the last point.
		mEdgePoints.erase(--mEdgePoints.end());
	}
}

void ConvexHullApplication::DrawCommands()
{
	DrawText(Point2(-0.98f, 0.98f), "Press 'LEFT MOUSE BUTTON' to add a new point", Color::PURPLE);
	DrawText(Point2(-0.98f, 0.92f), "Press 'RIGHT MOUSE BUTTON' to remove last added point", Color::PURPLE);
	DrawText(Point2(-0.98f, 0.86f), "Press 'SPACE' to clear all points", Color::WHITE);
	DrawText(Point2(-0.98f, 0.80f), "Press 'RETURN' to build a convex hull from current points", Color::WHITE);
	DrawText(Point2(-0.98f, 0.74f), "Press 'TAB' to iterate between available convex hull building strategies", Color::YELLOW);
	DrawText(Point2(-0.98f, 0.68f), "Press 'ESC' to close", Color::WHITE);
}

void ConvexHullApplication::DrawPoint(const Point2& rPoint, Color color, size_t i)
{
	std::stringstream pointCoordinates;
	if (i == ~0u)
	{
		pointCoordinates << "P(" << rPoint.GetX() << "," << rPoint.GetY() << ")";
	}
	else
	{
		pointCoordinates << "P" << i << "(" << rPoint.GetX() << "," << rPoint.GetY() << ")";
	}
	DrawText(rPoint, pointCoordinates.str().c_str(), Color::WHITE);
	DrawFillCircle(rPoint, 5, color);
}

bool ConvexHullApplication::DrawPoints()
{
	// Draw points.
	for (size_t i = 0; i < mEdgePoints.size(); i++)
	{
		DrawPoint(mEdgePoints[i], Color::GREEN, i);
	}

	return true;
}

bool ConvexHullApplication::DrawPolygon()
{
	const auto& rEdgePoints = mpPolygon->GetEdgePoints();

	// Draw edges and points.
	for (size_t i = 0; i < rEdgePoints.size(); i++)
	{
		const Point2& rP1 = rEdgePoints[i];
		// Wrap around: the last edge point connects to the first.
		const Point2& rP2 = (i == rEdgePoints.size() - 1) ? rEdgePoints[0] : rEdgePoints[i + 1];

		DrawLine(rP1, rP2, Color::BLUE);
	}

	// Draw absent points: points that were not used in the construction of the hull.
	for (size_t i = 0; i < mEdgePoints.size(); i++)
	{
		auto pointLocation = mpPolygon->LocatePoint(mEdgePoints[i]);

		if (pointLocation == Polygon2::PL_INSIDE)
		{
			DrawPoint(mEdgePoints[i], Color::GREEN);
		}
		else if (pointLocation == Polygon2::PL_OUTSIDE)
		{
			DrawPoint(mEdgePoints[i], Color::RED);
		}
		else if (pointLocation == Polygon2::PL_ON_THE_EDGE)
		{
			DrawPoint(mEdgePoints[i], Color::YELLOW);
		}
	}

	return true;
}

void ConvexHullApplication::DrawCurrentConvexHullBuildingStrategy()
{
	DrawText(Point2(0.60f, -0.86f), "Current strategy:", Color::WHITE);
	if (mStrategy == CHBS_GRAHAM_SCAN)
	{
		DrawText(Point2(0.60f, -0.92f), "Graham Scan", Color::YELLOW);
	}
	else
	{
		DrawText(Point2(0.60f, -0.92f), "Divide-and-Conquer", Color::YELLOW);
	}
}

