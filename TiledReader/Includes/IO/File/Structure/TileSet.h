#ifndef TPP_STRUCTURE_TILESET_H
#define TPP_STRUCTURE_TILESET_H

#include "IO\File\Structure\Image.h"
#include "IO\File\Structure\Animation.h"
#include "IO\File\Structure\PropertySet.h"

namespace tpp
{
	// Represents the <tileset> tag
	struct TILEDPP_API TileSet final
	{
		TileSet();

		unsigned int firstTileId;
		unsigned int lastTileId;
		unsigned int tilesCount;
		unsigned int tileWidth;
		unsigned int tileHeight;

		tpp::Image image;
		std::string name;

		std::map<unsigned int, tpp::Animation> animations;
		std::map<unsigned int, tpp::PropertySet> tileProperties;
	};
}

#endif