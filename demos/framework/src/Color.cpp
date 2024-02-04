#include <framework/Color.h>

namespace framework
{
	const Color Color::RED(255, 0, 0, 255);
	const Color Color::GREEN(0, 255, 0, 255);
	const Color Color::BLUE(0, 0, 255, 255);
	const Color Color::YELLOW(255, 255, 0, 255);
	const Color Color::PURPLE(160, 32, 240, 255);
	const Color Color::WHITE(255, 255, 255, 255);

	Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
		mR(r),
		mG(g),
		mB(b),
		mA(a)
	{
	}

}
