#ifndef TPP_STRUCTURE_IMAGE_H
#define TPP_STRUCTURE_IMAGE_H

#include <string>

#include "Color.h"

namespace tpp
{
	// Represents the <image> tag
	struct Image
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