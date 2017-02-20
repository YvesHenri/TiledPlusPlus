#include "IO\File\Structure\TileSet.h"

namespace tpp
{
	TileSet::TileSet()
		: name("")
		, firstTileId(0U)
		, lastTileId(0U)
		, tilesCount(0U)
		, tileWidth(0U)
		, tileHeight(0U)
		, columns(0U)
	{}
}