#ifndef FRAMEWORK_APPLICATION_H
#define FRAMEWORK_APPLICATION_H

#include <framework/Color.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <triangulate/Point2.h>

#include <cstdint>

using namespace triangulate;

namespace framework
{
	class Application
	{
	public:
		static const int DEFAULT_SCREEN_WIDTH;
		static const int DEFAULT_SCREEN_HEIGHT;
		static const int DEFAULT_SCREEN_BPP;
		static const int DRAWING_AREA_OFFSET;

		static const int VK_RETURN;
		static const int VK_SPACE;
		static const int VK_TAB;

		virtual ~Application();

		void Run(int argc, char** argv);

	protected:
		int mScreenWidth;
		int mScreenHeight;
		int mScreenBpp;
		int mHalfScreenWidth;
		int mHalfScreenHeight;
		int mDrawingAreaWidth;
		int mDrawingAreaHeight;
		int mHalfDrawingAreaWidth;
		int mHalfDrawingAreaHeight;
		SDL_Surface* mpSDLSurface;
		TTF_Font* mpTTFVerdana12;

		Application();
		Application(int screenWidth, int screenHeight, int screenBpp);

		virtual void ParseCommandLine(int argc, char** argv) {}
		virtual bool OnRender() { return false; }
		virtual void OnKeyDown(int key) {}
		virtual void OnKeyUp(int key) {}
		virtual void OnMouseButtonDown(char button, int screenX, int screenY, float viewportX, float viewportY) {}
		virtual void OnMouseButtonUp(char button, int screenX, int screenY, float viewportX, float viewportY) {}
		virtual void OnMouseMove(int screenX, int screenY, float viewportX, float viewportY) {}
		void DrawPixel(const Point2& rPoint, Color color);
		void DrawFillCircle(const Point2& rCenter, int radius, Color color);
		void DrawLine(const Point2& rStart, const Point2& rEnd, Color color);
		void DrawText(const Point2& rPoint, const char* pText, Color color);

		inline int GetHorizontalOffset() const
		{
			return mHalfScreenWidth - mHalfDrawingAreaWidth;
		}

		inline int GetVerticalOffset() const
		{
			return mHalfScreenHeight - mHalfDrawingAreaHeight;
		}

		inline int GetScreenX(float viewportX) const
		{
			return (int)(viewportX * mHalfDrawingAreaWidth) + mHalfDrawingAreaWidth + GetHorizontalOffset();
		}

		inline int GetScreenY(float viewportY) const
		{
			return mHalfDrawingAreaHeight - (int)(viewportY * mHalfDrawingAreaHeight) + GetVerticalOffset();
		}

		inline float GetViewportX(int screenX) const
		{
			return (screenX - GetHorizontalOffset() - mHalfDrawingAreaWidth) / (float)mHalfDrawingAreaWidth;
		}

		inline float GetViewportY(int screenY) const
		{
			return (-screenY + GetVerticalOffset() + mHalfDrawingAreaHeight) / (float)mHalfDrawingAreaHeight;
		}

	private:
		void Construct(int screenWidth, int screenHeight, int screenBpp);
		void InitializeSDL();
		void OpenTTFFonts();
		void CloseTTFFonts();
		void MapColors();
		void PoolSDLEvents();

	};

}

#endif