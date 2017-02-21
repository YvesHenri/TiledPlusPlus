#ifndef TPP_IO_FILE_STRUCTURE_FRAME_H
#define TPP_IO_FILE_STRUCTURE_FRAME_H

#include "Macros\API.h"

namespace tpp
{
	// Represents the <frame> tag
	struct TILEDPP_API Frame final
	{
		Frame();

		unsigned int duration;
		unsigned int tileGid;
	};
}

#endif