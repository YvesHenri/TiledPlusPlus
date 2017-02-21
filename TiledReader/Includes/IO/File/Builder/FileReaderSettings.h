#pragma once

#include "Macros\API.h"

namespace tpp
{
	struct TILEDPP_API FileReaderSettings final
	{
		FileReaderSettings()
			: skipHandlingHiddenObjects(false)
			, skipHandlingBlankTiles(false)
			, storeTilesAfterRead(true)
		{}

		// Whether the reader should not calculate points (rotation, shape points etc) for hidden objects
		bool skipHandlingHiddenObjects;

		// Whether the reader should not process and store blank tiles (no texture/gid)
		bool skipHandlingBlankTiles;

		// Whether the reader should save copies of non-blank tiles after they have been parsed and read
		bool storeTilesAfterRead;
	};
}