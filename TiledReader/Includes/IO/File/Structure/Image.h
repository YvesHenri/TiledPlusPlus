#ifndef TPP_IO_FILE_STRUCTURE_IMAGE_H
#define TPP_IO_FILE_STRUCTURE_IMAGE_H

#include "IO/File/Structure/Color.h"

namespace tpp
{
	// Represents the </image> tag
	struct TILEDPP_API Image
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