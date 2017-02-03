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
		return !source.empty();
	}
}