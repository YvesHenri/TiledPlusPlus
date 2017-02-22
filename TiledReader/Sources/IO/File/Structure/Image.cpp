#include "IO\File\Structure\Image.h"

namespace tpp
{
	Image::Image()
		: width(0U)
		, height(0U)
		, source("")
		, transparency()
	{}

	Image::operator bool()
	{
		// Images are used on both tile sets and image layers, however image layers dont provide sizes
		return !source.empty();
	}
}