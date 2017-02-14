#pragma once

#include <memory>

#include "IO\File\Structure\Header.h"
#include "IO\File\Structure\ImageLayer.h"
#include "IO\File\Structure\TileLayer.h"
#include "IO\File\Structure\ObjectLayer.h"
#include "IO\File\Structure\Tileset.h"

namespace tpp
{
	// Type aliases for known collections
	using Layers = std::vector<std::unique_ptr<tpp::Layer>>;
	using TileSets = std::vector<tpp::TileSet>;
	using TileLayers = std::vector<tpp::TileLayer>;
	using ImageLayers = std::vector<tpp::ImageLayer>;
	using ObjectLayers = std::vector<tpp::ObjectLayer>;

	// Represents the content of a Tiled's TMX file (header, sets, layers etc). 
	// This struct is non-copyable due to its HUGE size.
	struct TILEDPP_API FileMetadata final
	{
		FileMetadata() = default;
		FileMetadata(tpp::FileMetadata&&) = default;
		FileMetadata(const tpp::FileMetadata&) = delete;

		FileMetadata& operator = (FileMetadata&&) = default;
		FileMetadata& operator = (const FileMetadata&) = delete;

		tpp::Header header;
		tpp::Layers layers;
		tpp::TileSets sets;
	};
}