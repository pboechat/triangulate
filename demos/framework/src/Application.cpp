#include <framework/Application.h>
#include <SDL_draw.h>

namespace framework
{
	const int Application::DEFAULT_SCREEN_WIDTH = 1024;
	const int Application::DEFAULT_SCREEN_HEIGHT = 768;
	const int Application::DEFAULT_SCREEN_BPP = 0;
	const int Application::DRAWING_AREA_OFFSET = 20;

	const int Application::VK_RETURN = (int)SDLK_RETURN;
	const int Application::VK_SPACE = (int)SDLK_SPACE;
	const int Application::VK_TAB = (int)SDLK_TAB;

	Application::Application()
	{
		Construct(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, DEFAULT_SCREEN_BPP);
	}

	Application::Application(int screenWidth, int screenHeight, int screenBpp)
	{
		Construct(screenWidth, screenHeight, screenBpp);
	}

	void Application::Construct(int screenWidth, int screenHeight, int screenBpp)
	{
		mScreenWidth = screenWidth;
		mHalfScreenWidth = mScreenWidth / 2;
		mDrawingAreaWidth = mScreenWidth - DRAWING_AREA_OFFSET;
		mHalfDrawingAreaWidth = mDrawingAreaWidth / 2;
		mScreenHeight = screenHeight;
		mHalfScreenHeight = mScreenHeight / 2;
		mDrawingAreaHeight = mScreenHeight - DRAWING_AREA_OFFSET;
		mHalfDrawingAreaHeight = mDrawingAreaHeight / 2;
		mScreenBpp = screenBpp;
		mpSDLSurface = nullptr;
	}

	Application::~Application()
	{
		CloseTTFFonts();
	}

	void Application::Run(int argc, char** argv)
	{
		ParseCommandLine(argc, argv);
		InitializeSDL();
		OpenTTFFonts();
		MapColors();
		PoolSDLEvents();
	}

	void Application::MapColors()
	{
		const_cast<Color*>(&Color::RED)->SetIndex(SDL_MapRGB(mpSDLSurface->format, 255, 0, 0));
		const_cast<Color*>(&Color::GREEN)->SetIndex(SDL_MapRGB(mpSDLSurface->format, 0, 255, 0));
		const_cast<Color*>(&Color::BLUE)->SetIndex(SDL_MapRGB(mpSDLSurface->format, 0, 0, 255));
		const_cast<Color*>(&Color::YELLOW)->SetIndex(SDL_MapRGB(mpSDLSurface->format, 255, 255, 0));
		const_cast<Color*>(&Color::PURPLE)->SetIndex(SDL_MapRGB(mpSDLSurface->format, 160, 32, 240));
		const_cast<Color*>(&Color::WHITE)->SetIndex(SDL_MapRGB(mpSDLSurface->format, 255, 255, 255));
	}

	void Application::InitializeSDL()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
			exit(1);
		}

		atexit(SDL_Quit);
		mpSDLSurface = SDL_SetVideoMode(mScreenWidth, mScreenHeight, mScreenBpp, SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF);

		if (mpSDLSurface == nullptr)
		{
			fprintf(stderr, "Couldn't set %dx%dx%d BPP video mode: %s\n", mScreenWidth, mScreenHeight, mScreenBpp, SDL_GetError());
			exit(1);
		}

		TTF_Init();
		atexit(TTF_Quit);
	}

	void Application::PoolSDLEvents()
	{
		bool quit = false;
		bool update = false;

		while (!quit)
		{
			SDL_Event event;
			SDLKey key;
			SDL_FillRect(mpSDLSurface, nullptr, 0x000000);

			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					quit = true;
					break;

				case SDL_KEYDOWN:
					key = event.key.keysym.sym;

					if (key == SDLK_ESCAPE)
					{
						quit = true;
						break;
					}

					OnKeyDown((int)key);
					break;
				case SDL_KEYUP:
					OnKeyUp((int)event.key.keysym.sym);
					break;
				case SDL_MOUSEMOTION:
					OnMouseMove(event.motion.x, event.motion.y, GetViewportX(event.motion.x), GetViewportY(event.motion.y));
					break;
				case SDL_MOUSEBUTTONDOWN:
					OnMouseButtonDown(event.button.button, event.motion.x, event.motion.y, GetViewportX(event.motion.x), GetViewportY(event.motion.y));
					break;
				case SDL_MOUSEBUTTONUP:
					OnMouseButtonUp(event.button.button, event.motion.x, event.motion.y, GetViewportX(event.motion.x), GetViewportY(event.motion.y));
					break;
				default:
					break;
				}
			}

			update = OnRender();

			if (update)
			{
				SDL_UpdateRect(mpSDLSurface, 0, 0, 0, 0);
			}
		}
	}

	void Application::DrawPixel(const Point2& rPoint, Color color)
	{
		Draw_Pixel(mpSDLSurface, GetScreenX(rPoint.GetX()), GetScreenY(rPoint.GetY()), color.GetIndex());
	}

	void Application::DrawFillCircle(const Point2& rCenter, int radius, Color color)
	{
		Draw_FillCircle(mpSDLSurface, GetScreenX(rCenter.GetX()), GetScreenY(rCenter.GetY()), radius, color.GetIndex());
	}

	void Application::DrawLine(const Point2& rStart, const Point2& rEnd, Color color)
	{
		int x1 = GetScreenX(rStart.GetX());
		int y1 = GetScreenY(rStart.GetY());
		int x2 = GetScreenX(rEnd.GetX());
		int y2 = GetScreenY(rEnd.GetY());
		Draw_Line(mpSDLSurface, (Sint16)x1, (Sint16)y1, (Sint16)x2, (Sint16)y2, color.GetIndex());
	}

	void Application::OpenTTFFonts()
	{
		mpTTFVerdana12 = TTF_OpenFont("assets/fonts/verdana.ttf", 12);
		if (mpTTFVerdana12 == nullptr)
		{
			fprintf(stderr, "Couldn't open verdana.tff\n");
			exit(1);
		}
	}

	void Application::CloseTTFFonts()
	{
		if (mpTTFVerdana12 != nullptr)
		{
			TTF_CloseFont(mpTTFVerdana12);
		}
	}

	void Application::DrawText(const Point2& rPoint, const char* pText, Color color)
	{
		SDL_Color sdlColor = { color.GetR(), color.GetG(), color.GetB(), 0 };
		SDL_Surface* pTextSurface = TTF_RenderText_Solid(mpTTFVerdana12, pText, sdlColor);
		SDL_Rect textArea = { (Sint16)GetScreenX(rPoint.GetX()), (Sint16)GetScreenY(rPoint.GetY()), 0, 0 };
		SDL_BlitSurface(pTextSurface, nullptr, mpSDLSurface, &textArea);
		SDL_FreeSurface(pTextSurface);
	}

}