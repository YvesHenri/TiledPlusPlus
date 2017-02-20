#include "IO\File\Structure\TileLayer.h"

namespace tpp
{
	TileLayer::TileLayer() : tpp::Layer(tpp::Material::Tile)
		, area(0U)
		, width(0U)
		, height(0U)
		, tileWidth(0U)
		, tileHeight(0U)
	{}
}