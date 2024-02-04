#include <EarClippingTriangulationApplication.h>
#include <triangulate/Triangulation2.h>

#include <sstream>

EarClippingTriangulationApplication::EarClippingTriangulationApplication() :
	Application(),
	mpTriangledPolygon(nullptr)
{
}

bool EarClippingTriangulationApplication::OnRender()
{
	DrawWarnings();
	DrawCommands();

	if (mpTriangledPolygon == nullptr)
	{
		DrawPolygon();
	}
	else
	{
		DrawTriangledPolygon();
	}

	return true;
}

void EarClippingTriangulationApplication::Triangulate()
{
	// Cannot triangulate a triangle with less than 4 points.
	if (mEdgePoints.size() < 4)
	{
		printf("Cannot triangulate a triangle with less than 4 points.\n");
		return;
	}

	Polygon2 polygon(mEdgePoints);

	// Must be a counterclockwise polygon.
	if (!polygon.IsCounterclockwise())
	{
		printf("Must be a counterclockwise polygon.\n");
		return;
	}

	if (!polygon.IsSimple())
	{
		printf("Must be a simple polygon.\n");
		return;
	}

	mpTriangledPolygon = std::make_unique<TriangleMesh2>();
	Triangulation2::EarClippingTriangulation(polygon, *mpTriangledPolygon);
}

void EarClippingTriangulationApplication::StartANewPolygon()
{
	if (mpTriangledPolygon != nullptr)
	{
		mpTriangledPolygon = nullptr;
	}
	mEdgePoints.clear();
}

void EarClippingTriangulationApplication::OnKeyDown(int key)
{
	if (key == VK_RETURN)
	{
		Triangulate();
	}
	else if (key == VK_SPACE)
	{
		StartANewPolygon();
	}
}

void EarClippingTriangulationApplication::OnMouseButtonDown(char button, int screenX, int screenY, float viewportX, float viewportY)
{
	if (button == 1)
	{
		if (mpTriangledPolygon != nullptr)
		{
			mpTriangledPolygon = nullptr;
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

		if (mpTriangledPolygon != nullptr)
		{
			mpTriangledPolygon = nullptr;
		}

		// Remove the last point.
		mEdgePoints.erase(--mEdgePoints.end());
	}
}

void EarClippingTriangulationApplication::DrawCommands()
{
	DrawText(Point2(-0.98f, 0.98f), "Press 'LEFT MOUSE BUTTON' to add a new point", Color::PURPLE);
	DrawText(Point2(-0.98f, 0.92f), "Press 'RIGHT MOUSE BUTTON' to remove last added point", Color::PURPLE);
	DrawText(Point2(-0.98f, 0.86f), "Press 'SPACE' to start a new polygon", Color::WHITE);
	DrawText(Point2(-0.98f, 0.80f), "Press 'RETURN' to triangulate current polygon", Color::WHITE);
	DrawText(Point2(-0.98f, 0.74f), "Press 'ESC' to close", Color::WHITE);
}

void EarClippingTriangulationApplication::DrawPoint(const Point2& rPoint, size_t i)
{
	std::stringstream pointCoordinates;
	if (i == ~0u)
	{
		pointCoordinates << "P(" << rPoint.GetX() << ", " << rPoint.GetY() << ")";
	}
	else
	{
		pointCoordinates << "P" << i << "(" << rPoint.GetX() << ", " << rPoint.GetY() << ")";
	}
	DrawText(rPoint, pointCoordinates.str().c_str(), Color::WHITE);
	DrawFillCircle(rPoint, 5, Color::RED);
}

bool EarClippingTriangulationApplication::DrawPolygon()
{
	static size_t lastEdgePointsCount = mEdgePoints.size();

	// Draw edge and points.
	for (size_t i = 0; i < mEdgePoints.size(); i++)
	{
		const Point2& rP1 = mEdgePoints[i];
		// Wrap around: the last edge point connects to the first.
		const Point2& rP2 = (i == mEdgePoints.size() - 1) ? mEdgePoints[0] : mEdgePoints[i + 1];

		DrawLine(rP1, rP2, Color::BLUE);
		DrawPoint(rP1, i);
	}

	// Need to update the screen if the last points count is different than current points count.
	bool update = (lastEdgePointsCount != mEdgePoints.size());
	lastEdgePointsCount = mEdgePoints.size();

	return update;
}

bool EarClippingTriangulationApplication::DrawTriangledPolygon()
{
	// Draw edges.

	const auto& rTriangles = mpTriangledPolygon->GetTriangles();
	for (size_t i = 0; i < rTriangles.size(); i++)
	{
		const Point2& rP1 = rTriangles[i].GetP1();
		const Point2& rP2 = rTriangles[i].GetP2();
		const Point2& rP3 = rTriangles[i].GetP3();

		DrawLine(rP1, rP2, Color::BLUE);
		DrawLine(rP2, rP3, Color::BLUE);
		DrawLine(rP3, rP1, Color::BLUE);
	}

	// Draw points.
	for (size_t i = 0; i < mEdgePoints.size(); i++)
	{
		const Point2& rP1 = mEdgePoints[i];
		// Wrap around: the last edge point connects to the first.
		const Point2& rP2 = (i == mEdgePoints.size() - 1) ? mEdgePoints[0] : mEdgePoints[i + 1];

		DrawPoint(rP1, i);
	}

	return true;
}

void EarClippingTriangulationApplication::DrawWarnings()
{
	DrawText(Point2(0.50f, 0.98f), "NOTE: Polygons must be *simple* and", Color::RED);
	DrawText(Point2(0.50f, 0.92f), "drawn in *counterclockwise* order", Color::RED);
}

