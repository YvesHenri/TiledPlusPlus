#ifndef TPP_IO_FILE_STRUCTURE_ANIMATION_H
#define TPP_IO_FILE_STRUCTURE_ANIMATION_H

#include <vector>

#include "IO\File\Structure\Frame.h"

namespace tpp
{
	// Represents the <animation> tag
	struct TILEDPP_API Animation final
	{
		std::vector<tpp::Frame> frames;
	};
}

#endif