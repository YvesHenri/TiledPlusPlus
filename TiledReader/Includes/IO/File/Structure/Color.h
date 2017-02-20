#ifndef TPP_STRUCTURE_COLOR_H
#define TPP_STRUCTURE_COLOR_H

#include <string>

#include "Macros\API.h"

namespace tpp
{
	// Wrapper class that enables easy conversion from html color string to a color object.
	// The alpha value must precede the RGB value. Ex.: 0xAARRGGBB, where AA is the alpha value.
	class TILEDPP_API Color final
	{
	public:
		Color(unsigned long argb);
		Color(unsigned char a = 0xFF, unsigned char r = 0xA0, unsigned char g = 0xA0, unsigned char b = 0xA4);

		const unsigned long argb();
		const unsigned char r();
		const unsigned char g();
		const unsigned char b();
		const unsigned char a();

		Color& operator=(const char* html);
		Color& operator=(const std::string& html);

	private:
		unsigned long m_argb;
		unsigned char m_r;
		unsigned char m_g;
		unsigned char m_b;
		unsigned char m_a;
	};
}

#endif