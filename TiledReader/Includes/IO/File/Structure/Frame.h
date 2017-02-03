#ifndef TPP_STRUCTURE_FRAME_H
#define TPP_STRUCTURE_FRAME_H

#include "Macros\Exporter.h"

namespace tpp
{
	// Represents the <frame> tag
	struct TILEDPP_API Frame
	{
		Frame();

		unsigned int duration;
		unsigned int tileGid;
	};
}

#endif