#ifndef TPP_IO_FILE_STRUCTURE_TILE_H
#define TPP_IO_FILE_STRUCTURE_TILE_H

#include "IO\File\Structure\PropertySet.h"

namespace tpp
{
	struct TileSet;
	struct TileLayer;

	// Represents the </tile> tag
	struct TILEDPP_API Tile final
	{
		Tile();

		int x;
		int y;

		unsigned int id; // Linear index within a tile set. Range: [0, TileSet::tilesCount).
		unsigned int gid; // Global ID within the whole collection of tile sets. Starts at 1 (0 means blank tiles).
		unsigned int index; // Linear index within a tile layer. Range: [0, TileLayer::area).
		unsigned int width;
		unsigned int height;
		
		bool isFlippedDiagonally; // Bool uses 1 byte (total of 3), while enum classes use 4 (1 byte shorter).
		bool isFlippedVertically; // Bool uses 1 byte (total of 3), while enum classes use 4 (1 byte shorter).
		bool isFlippedHorizontally; // Bool uses 1 byte (total of 3), while enum classes use 4 (1 byte shorter).

		tpp::TileSet* set;
		tpp::TileLayer* owner;
		tpp::PropertySet properties;
	};
}

#endif