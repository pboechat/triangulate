#include <SDL.h>
#include <SDL_draw.h>
#include <triangulate/Vector2.h>
#include <triangulate/Matrix22.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <vector>

#define DEG_TO_RAD(x) x * ((float)M_PI / 180.0f)

using namespace triangulate;

int DRAWING_AREA_WIDTH = 500;
int HALF_DRAWING_AREA_WIDTH = DRAWING_AREA_WIDTH / 2;
int DRAWING_AREA_HEIGHT = 500;
int HALF_DRAWING_AREA_HEIGHT = DRAWING_AREA_HEIGHT / 2;
int SCREEN_WIDTH = 600;
int HALF_SCREEN_WIDTH = SCREEN_WIDTH / 2;
int SCREEN_HEIGHT = 600;
int HALF_SCREEN_HEIGHT = SCREEN_HEIGHT / 2;
int SCREEN_BPP = 0;

SDL_Surface* g_pSDLSurface;
unsigned int g_colorWhite;
unsigned int g_colorRed;
unsigned int g_colorGreen;

void StartVideo()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	atexit(SDL_Quit);
	g_pSDLSurface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF);

	if (g_pSDLSurface == NULL)
	{
		fprintf(stderr, "Couldn't set %dx%dx%d BPP video mode: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_GetError());
		exit(1);
	}

	g_colorWhite = SDL_MapRGB(g_pSDLSurface->format, 255, 255, 255);
	g_colorRed = SDL_MapRGB(g_pSDLSurface->format, 255, 0, 0);
	g_colorGreen = SDL_MapRGB(g_pSDLSurface->format, 0, 255, 0);
}

short GetScreenX(float viewportX)
{
	return (short)((viewportX * HALF_DRAWING_AREA_WIDTH) + HALF_DRAWING_AREA_WIDTH) + (HALF_SCREEN_WIDTH - HALF_DRAWING_AREA_WIDTH);
}

short GetScreenY(float viewportY)
{
	return (short)(HALF_DRAWING_AREA_HEIGHT - (viewportY * HALF_DRAWING_AREA_HEIGHT)) + (HALF_SCREEN_HEIGHT - HALF_DRAWING_AREA_HEIGHT);
}

void DrawLine(const Vector2& rP1, const Vector2& rP2, int color)
{
	Draw_Line(g_pSDLSurface, GetScreenX(rP1.GetX()), GetScreenY(rP1.GetY()), GetScreenX(rP2.GetX()), GetScreenY(rP2.GetY()), color);
}

void DrawLineFromCenterToStartingPoint(const Vector2& rStartingPoint)
{
	DrawLine(Vector2::ZERO, rStartingPoint, g_colorGreen);
}

void DrawPolygon(std::vector<Vector2> edgePoints)
{
	Draw_Pixel(g_pSDLSurface, GetScreenX(0), GetScreenY(0), g_colorRed);

	for (size_t i = 0; i < edgePoints.size() - 1; i++)
	{
		DrawLine(edgePoints[i], edgePoints[i + 1], g_colorWhite);
	}
	DrawLine(edgePoints[edgePoints.size() - 1], edgePoints[0], g_colorWhite);

	SDL_UpdateRect(g_pSDLSurface, 0, 0, 0, 0);
}

void PoolGraphicsAPIEvents()
{
	bool exit = false;

	while (!exit)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				exit = true;
				break;

			default:
				break;
			}
		}
	}
}

void PrintEdgePoints(std::vector<Vector2>& edgePoints)
{
	for (size_t i = 0; i < edgePoints.size(); i++)
	{
		Vector2 edgePoint = edgePoints[i];
		printf("(%.3ff, %.3ff)\n", edgePoint.GetX(), edgePoint.GetY());
	}
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("Usage: ./polycoords <number of sides> <x,y> [gui]");
		return -1;
	}

	int numberOfSides = atoi(argv[1]);
	float x;
	float y;
	sscanf(argv[2], "%f,%f", &x, &y);
	Vector2 startingPoint(x, y);

	if (startingPoint == Vector2::ZERO)
	{
		startingPoint = Vector2::UNIT_Y;
	}

	else if (startingPoint.Magnitude() != 1)
	{
		startingPoint = startingPoint.Normalized();
	}

	bool useGui = false;
	if (argc > 3)
	{
		if (strcmp(argv[3], "gui") == 0)
		{
			useGui = true;
		}
	}

	// ---

	float innerAngle = (numberOfSides - 2) * 180.0f / numberOfSides;
	float externalAngle = 180 - innerAngle;
	std::vector<Vector2> edgePoints;
	edgePoints.push_back(startingPoint);

	Matrix22 rotate;

	for (int i = 1; i < numberOfSides; i++)
	{
		rotate.FromAngle(DEG_TO_RAD(externalAngle * i));
		edgePoints.push_back(rotate.Multiply(startingPoint));
	}

	PrintEdgePoints(edgePoints);
	if (useGui)
	{
		StartVideo();
		DrawLineFromCenterToStartingPoint(startingPoint);
		DrawPolygon(edgePoints);
		PoolGraphicsAPIEvents();
	}
	else
	{
		system("pause");
	}

	return 0;
}

