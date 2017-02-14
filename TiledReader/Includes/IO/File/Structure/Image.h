#ifndef TPP_STRUCTURE_IMAGE_H
#define TPP_STRUCTURE_IMAGE_H

#include "Color.h"

namespace tpp
{
	// Represents the <image> tag
	struct TILEDPP_API Image final
	{
		Image();

		unsigned int width;
		unsigned int height;

		std::string source;
		tpp::Color transparency;

		operator bool();
	};
}

#endif