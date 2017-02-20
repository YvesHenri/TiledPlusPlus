#include "IO\File\Structure\Header.h"

namespace tpp
{
	Header::Header()
		: orientation(tpp::Orientation::Orthogonal)
		, renderOrder(tpp::RenderOrder::RightDown)
		, staggerAxis(tpp::StaggerAxis::None)
		, staggerIndex(tpp::StaggerIndex::None)
		, backgroundColor(0xC8, 0x80, 0x80, 0x80) // Tiled's default
		, width(0U)
		, height(0U)
		, tileWidth(0U)
		, tileHeight(0U)
		, hexSideLength(0U)
		, tilesCount(0U)
		, objectsCount(0U)
		, tileSetsCount(0U)
		, tileLayersCount(0U)
		, imageLayersCount(0U)
		, objectLayersCount(0U)
	{}
}