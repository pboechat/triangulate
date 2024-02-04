#ifndef EARCLIPPINGTRIANGULATIONAPPLICATION_H
#define EARCLIPPINGTRIANGULATIONAPPLICATION_H

#include <framework/Application.h>
#include <triangulate/Point2.h>
#include <triangulate/TriangleMesh2.h>

#include <memory>
#include <vector>

using namespace framework;
using namespace triangulate;

class EarClippingTriangulationApplication : public Application
{
public:
	EarClippingTriangulationApplication();

protected:
	bool OnRender() override;
	void OnKeyDown(int key) override;
	void OnMouseButtonDown(char button, int screenX, int screenY, float viewportX, float viewportY) override;

private:
	std::vector<Point2> mEdgePoints;
	std::unique_ptr<TriangleMesh2> mpTriangledPolygon;

	void DrawWarnings();
	void DrawCommands();
	bool DrawPolygon();
	bool DrawTriangledPolygon();
	void Triangulate();
	void StartANewPolygon();
	void DrawPoint(const Point2& rPoint, size_t i = ~0u);

};

#endif