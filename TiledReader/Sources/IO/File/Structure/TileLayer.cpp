#include "IO\File\Structure\TileLayer.h"

namespace tpp
{
	TileLayer::TileLayer() : tpp::Layer(tpp::Material::Tile)
		, width(0U)
		, height(0U)
		, area(0U)
	{}
}