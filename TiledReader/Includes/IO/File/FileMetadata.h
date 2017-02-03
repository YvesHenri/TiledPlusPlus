#pragma once

#include "IO\File\Structure\Header.h"
#include "IO\File\Structure\ImageLayer.h"
#include "IO\File\Structure\TileLayer.h"
#include "IO\File\Structure\ObjectLayer.h"
#include "IO\File\Structure\Tileset.h"

namespace tpp
{
	// Type aliases for known collections
	using TileSets = std::vector<tpp::TileSet>;
	using TileLayers = std::vector<tpp::TileLayer>;
	using ImageLayers = std::vector<tpp::ImageLayer>;
	using ObjectLayers = std::vector<tpp::ObjectLayer>;

	// Represents the content of a Tiled's TMX file, such as header,
	// tile sets, tile layers, image layers and object layers.
	struct TILEDPP_API FileMetadata
	{
		tpp::Header header;
		tpp::TileSets tileSets;
		tpp::TileLayers tileLayers;
		tpp::ImageLayers imageLayers;
		tpp::ObjectLayers objectLayers;
	};
}