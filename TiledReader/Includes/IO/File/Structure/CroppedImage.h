#ifndef TPP_IO_FILE_STRUCTURE_TILEIMAGE_H
#define TPP_IO_FILE_STRUCTURE_TILEIMAGE_H

#include "IO\File\Structure\Image.h"

namespace tpp
{
	// Represents the small pieces of an image (crops)
	struct TILEDPP_API CroppedImage : public tpp::Image
	{
		CroppedImage()
			: left(0U)
			, top(0U)
			, right(0U)
			, bottom(0U)
		{}

		unsigned int left;
		unsigned int top;
		unsigned int right;
		unsigned int bottom;
	};
}

#endif