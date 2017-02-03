#ifndef TPP_STRUCTURE_TILE_H
#define TPP_STRUCTURE_TILE_H

#include "IO\File\Structure\PropertySet.h"

namespace tpp
{
	// Forward declare the container of this object
	struct TileSet;

	// Forward declare the owner of this object
	struct TileLayer;

	// Represents the <tile> tag
	struct TILEDPP_API Tile
	{
		Tile();

		static const unsigned FLIPPED_HORIZONTALLY = 0x80000000;
		static const unsigned FLIPPED_VERTICALLY = 0x40000000;
		static const unsigned FLIPPED_DIAGONALLY = 0x20000000;

		unsigned int id;
		unsigned int gid;
		unsigned int index; // Conversion from 2D (row, col) to 1D index
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