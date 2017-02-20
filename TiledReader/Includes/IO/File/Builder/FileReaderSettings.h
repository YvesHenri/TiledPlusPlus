#pragma once

#include "Macros\API.h"

namespace tpp
{
	struct TILEDPP_API FileReaderSettings final
	{
		FileReaderSettings()
			: skipInvisibleObjects(false)
			, skipTexturelessTiles(false)
		{}

		bool skipInvisibleObjects;
		bool skipTexturelessTiles;
	};
}