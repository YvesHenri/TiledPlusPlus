#include "IO\File\Structure\Color.h"

namespace tpp
{
	Color::Color(unsigned long argb)
	{
		m_argb = argb;

		m_r = (argb >> 16) & 0xFF;
		m_g = (argb >> 8) & 0xFF;
		m_b = (argb >> 0) & 0xFF;

		// Retrieve the alpha or assign the default value
		m_a = argb >> 24 ? (argb >> 24) & 0xFF : 255;
	}

	Color::Color(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
		: m_r(r)
		, m_g(g)
		, m_b(b)
		, m_a(a)
	{
		m_argb = (a << 24) | (b << 16) | (g << 8) | (r << 0);
	}

	const unsigned long Color::argb()
	{
		return m_argb;
	}

	const unsigned char Color::r()
	{
		return m_r;
	}

	const unsigned char Color::g()
	{
		return m_g;
	}

	const unsigned char Color::b()
	{
		return m_b;
	}

	const unsigned char Color::a()
	{
		return m_a;
	}

	Color& Color::operator=(const char* html)
	{
		return operator=(std::string(html));
	}

	Color& Color::operator=(const std::string& html)
	{
		if (!html.empty())
		{
			auto hashtagOccurrence = html.find_first_of("#");
			auto string = html;

			// Remove the hashtag character (if any)
			if (hashtagOccurrence != std::string::npos) 
				string = html.substr(hashtagOccurrence + 1U);

			// Convert the hexadecimal string
			m_argb = std::stoul(string, 0, 16);

			m_r = (m_argb >> 16) & 0xFF;
			m_g = (m_argb >> 8) & 0xFF;
			m_b = (m_argb >> 0) & 0xFF;

			// Retrieve the alpha or assign the default value
			m_a = m_argb >> 24 ? (m_argb >> 24) & 0xFF : 255;
		}

		return *this;
	}
}