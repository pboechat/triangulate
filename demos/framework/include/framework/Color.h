#ifndef FRAMEWORK_COLOR_H
#define FRAMEWORK_COLOR_H

#include <cstdint>

namespace framework
{
	class Application;

	class Color
	{
	public:
		static const Color RED;
		static const Color GREEN;
		static const Color BLUE;
		static const Color YELLOW;
		static const Color PURPLE;
		static const Color WHITE;

		inline uint8_t GetR() const
		{
			return mR;
		}

		inline uint8_t GetG() const
		{
			return mG;
		}

		inline uint8_t GetB() const
		{
			return mB;
		}

		inline uint8_t GetA() const
		{
			return mA;
		}

	private:
		union
		{
			struct
			{
				uint32_t mIndex;
			};
			struct
			{
				uint8_t mR;
				uint8_t mG;
				uint8_t mB;
				uint8_t mA;
			};
		};

		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

		inline uint32_t GetIndex() const
		{
			return mIndex;
		}

		inline void SetIndex(uint32_t index)
		{
			mIndex = index;
		}

		friend class Application;

	};

}

#endif