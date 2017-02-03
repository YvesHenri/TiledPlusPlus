#include "IO\File\Structure\Header.h"

namespace tpp
{
	Header::Header()
		: orientation(Orientation::Orthogonal)
		, renderOrder(RenderOrder::RightDown)
		, width(0U)
		, height(0U)
		, tileWidth(0U)
		, tileHeight(0U)
		, tilesCount(0U)
		, objectsCount(0U)
		, tileSetsCount(0U)
		, tileLayersCount(0U)
		, imageLayersCount(0U)
		, objectLayersCount(0U)
	{}
}