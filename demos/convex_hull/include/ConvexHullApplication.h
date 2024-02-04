#ifndef CONVEXHULLAPPLICATION_H
#define CONVEXHULLAPPLICATION_H

#include <framework/Color.h>
#include <framework/Application.h>
#include <triangulate/Point2.h>
#include <triangulate/Polygon2.h>

#include <memory>
#include <vector>

using namespace framework;
using namespace triangulate;

class ConvexHullApplication : public Application
{
public:
	ConvexHullApplication();

protected:
	void ParseCommandLine(int argc, char** argv) override;
	bool OnRender() override;
	void OnKeyDown(int key) override;
	void OnMouseButtonDown(char button, int screenX, int screenY, float viewportX, float viewportY) override;

private:
	enum ConvexHullBuildingStrategy
	{
		CHBS_GRAHAM_SCAN,
		CHBS_DIVIDE_AND_CONQUER
	};

	std::vector<Point2> mEdgePoints;
	std::unique_ptr<Polygon2> mpPolygon;
	ConvexHullBuildingStrategy mStrategy;

	void DrawCurrentConvexHullBuildingStrategy();
	void DrawCommands();
	bool DrawPoints();
	bool DrawPolygon();
	void BuildConvexHull();
	void StartPolygonWithNewPoints();
	void DrawPoint(const Point2& rPoint, Color color, size_t i = ~0u);

};

#endif