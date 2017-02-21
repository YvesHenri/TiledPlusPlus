#ifndef TPP_IO_FILE_STRUCTURE_TILEIMAGE_H
#define TPP_IO_FILE_STRUCTURE_TILEIMAGE_H

#include "IO\File\Structure\Image.h"

namespace tpp
{
	// Represents the small pieces of an image (crops)
	struct TILEDPP_API CroppedImage // : public tpp::Image
	{
		CroppedImage()
			: x(0) 
			, y(0)
		{}

		int x;
		int y;

		unsigned int width;
		unsigned int height;

		tpp::Image* target;
	};
}

#endif