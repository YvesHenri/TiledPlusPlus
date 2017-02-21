#ifndef TPP_IO_FILE_STRUCTURE_TILE_H
#define TPP_IO_FILE_STRUCTURE_TILE_H

#include "IO\File\Structure\PropertySet.h"

namespace tpp
{
	// Forward declare the container of this object
	struct TileSet;

	// Forward declare the owner of this object
	struct TileLayer;

	// Represents the <tile> tag
	struct TILEDPP_API Tile final
	{
		Tile();

		static const unsigned FLIPPED_HORIZONTALLY = 0x80000000;
		static const unsigned FLIPPED_VERTICALLY = 0x40000000;
		static const unsigned FLIPPED_DIAGONALLY = 0x20000000;

		unsigned int id; // Linear index within a tile set. Always starts at 0 and ends at TileSet::tilesCount.
		unsigned int gid; // Global ID within the whole collection of tile sets. Starts at 1 (0 means blank tiles).
		unsigned int index; // Linear index within a tile layer. Always starts at 0 and ends at TileLayer::area.
		unsigned int width;
		unsigned int height;

		int x;
		int y;

		bool isFlippedHorizontally;
		bool isFlippedVertically;
		bool isFlippedDiagonally;		
		
		tpp::TileSet* set;
		tpp::TileLayer* owner;
		tpp::PropertySet properties;
	};
}

#endif